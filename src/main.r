#include "Types.r"
#include "Dialogs.r"
#include "Processes.r"
#include "icon.r"

resource 'SIZE' (-1) {
    reserved,
    acceptSuspendResumeEvents,
    reserved,
    canBackground,
    doesActivateOnFGSwitch,
    backgroundAndForeground,
    dontGetFrontClicks,
    ignoreChildDiedEvents,
    is32BitCompatible,
    isHighLevelEventAware, /* was notHighLevelEventAware (Retro68's own
                               template default - this app started with
                               zero Apple Event handling, so it was
                               honest at the time). Now that app.c installs
                               real handlers for the 4 required Core Suite
                               events (including kAEQuitApplication), this
                               has to flip too, or the OS has no reason to
                               believe this app can answer a Quit
                               AppleEvent in the first place and may not
                               even bother sending Shut Down/Restart's one -
                               the actual root cause behind Shut Down not
                               completing while this app is still running,
                               not just a missing handler on this app's own
                               side. */
    onlyLocalHLEvents,
    notStationeryAware,
    dontUseTextEditServices,
    reserved,
    reserved,
    reserved,
    2048 * 1024, /* preferred - measured, not extrapolated. The app's real
                     resident footprint is ~820K, from the actual m68k link:
                     .text 100K + .data 664K (almost entirely the compiled-in
                     2,445-entry catalog) + .bss 56K. Confirmed live rather
                     than trusted: with this partition at 2048K, "About This
                     Macintosh" showed ~830K in use after a deliberately
                     heavy workout - a search scanning all 2,445 entries, a
                     200-entry live FTP listing, and a 10.8MB download - i.e.
                     ~1,218K still free. So 2048K is not a tight fit; it is
                     roughly 2.5x the real peak, and the headroom is there
                     for Memory Manager fragmentation, code segment loading
                     and larger window sizes rather than because the app
                     needs it.

                     Earlier values in this file's history (6500K, then
                     5750K) were extrapolated from an old real-hardware note
                     plus catalog-growth arithmetic, never measured, and were
                     far larger than necessary - worse, an oversized
                     preferred size actively hurts, because classic Mac OS
                     grants a launching app all remaining free memory when
                     preferred cannot be met, so Garden was swallowing the
                     entire free pool and leaving Open Transport nothing to
                     grow into for a live connection (the -23 openErr traced
                     in the previous round). Measuring the real number and
                     asking for a sane multiple of it fixes both problems at
                     once. */
    1024 * 1024       /* minimum - deliberately well below preferred, so the
                          app degrades onto genuinely small machines instead
                          of refusing to launch. Verified on a 4MB Mac (the
                          smallest configuration tested): System 7.5.3 plus
                          extensions takes 2,275K there, leaving ~1,650K, so
                          a 2048K *minimum* would have made Garden simply
                          refuse to open ("not enough memory to open Garden
                          (2,048K needed, 1,656K available)" - reproduced
                          exactly). With this 1024K floor it launches into
                          whatever is actually free, and catalog browsing,
                          category filtering, pagination and full-catalog
                          search all work normally there - confirmed live at
                          1400K on that 4MB machine.

                          What does NOT work on a 4MB machine is networking:
                          Connect fails with a DNR error (-23044) because
                          only ~276K is left system-wide once the System and
                          Garden are loaded, and MacTCP's resolver needs more
                          than that. Confirmed this is a system-total limit
                          rather than Garden being greedy by re-testing at a
                          1100K partition - identical failure, so shrinking
                          Garden further does not buy it back. 4MB is fine
                          for offline catalog use; downloading needs 8MB,
                          which was confirmed live with this partition size
                          (Connect plus a full 10.8MB download) - note that
                          8MB only became sufficient once this preferred
                          size came down, for the reason described above. */
};

resource 'MBAR' (128) {
    { 128, 129, 130, 131, 132 }
};

resource 'MENU' (128, preload) {
    128, textMenuProc,
    allEnabled,
    enabled,
    apple,
    {
        "About Macintosh Garden\0xc9", noIcon, noKey, noMark, plain;
    }
};

resource 'MENU' (129, preload) {
    129, textMenuProc,
    allEnabled,
    enabled,
    "File",
    {
        "Preferences\0xc9", noIcon, noKey, noMark, plain;
        "Get Selected Item", noIcon, "G", noMark, plain;
        "Show Downloads Folder", noIcon, noKey, noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Quit", noIcon, "Q", noMark, plain;
    }
};

resource 'MENU' (130, preload) {
    130, textMenuProc,
    allEnabled,
    enabled,
    "Edit",
    {
        "Cut", noIcon, "X", noMark, plain;
        "Copy", noIcon, "C", noMark, plain;
        "Paste", noIcon, "V", noMark, plain;
        "Clear", noIcon, noKey, noMark, plain;
    }
};

/* Item order/text here must match gCategories in catalog_data.c - see the
   kGoCategoryFirst comment in app.c. */
resource 'MENU' (131, preload) {
    131, textMenuProc,
    allEnabled,
    enabled,
    "Go",
    {
        "All", noIcon, noKey, noMark, plain;
        "Featured", noIcon, noKey, noMark, plain;
        "Games", noIcon, noKey, noMark, plain;
        "Utilities", noIcon, noKey, noMark, plain;
        "Graphics & Sound", noIcon, noKey, noMark, plain;
        "Productivity", noIcon, noKey, noMark, plain;
        "System Extensions", noIcon, noKey, noMark, plain;
        "Internet & Comm", noIcon, noKey, noMark, plain;
        "Dev Tools", noIcon, noKey, noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Live FTP Browse", noIcon, noKey, noMark, plain;
    }
};

resource 'MENU' (132, preload) {
    132, textMenuProc,
    allEnabled,
    enabled,
    "Connection",
    {
        "Connect", noIcon, noKey, noMark, plain;
        "Disconnect", noIcon, noKey, noMark, plain;
        "Refresh Listing", noIcon, "R", noMark, plain;
        "Go Up a Level", noIcon, noKey, noMark, plain;
    }
};

resource 'ALRT' (128) {
    { 80, 80, 250, 420 },
    128,
    {
        OK, visible, silent;
        OK, visible, silent;
        OK, visible, silent;
        OK, visible, silent;
    },
    centerMainScreen
};

resource 'DITL' (128) {
    {
        { 140, 250, 160, 320 },
        Button { enabled, "OK" };

        /* One StaticText, not two, with real carriage returns (\0x0d - the
           classic Mac line break, same convention the catalog's own hwNote
           second line uses) rather than a separate DITL item for the
           credit: the Dialog Manager can't give individual DITL items
           their own font/style anyway, so a second item would buy nothing
           and would renumber the list. Item 1 stays the OK button, which
           is what the ALRT's stage entries above all point at. */
        { 10, 10, 130, 320 },
        StaticText { enabled, "Macintosh Garden \0xd0 a classic Mac client for browsing and downloading software over FTP. Prototype built with Retro68.\0x0d\0x0dCreated by Anders Muskens." };
    }
};

resource 'ALRT' (129) {
    { 100, 70, 230, 410 },
    129,
    {
        OK, visible, silent;
        OK, visible, silent;
        OK, visible, silent;
        OK, visible, silent;
    },
    centerMainScreen
};

resource 'DITL' (129) {
    {
        { 100, 270, 120, 340 },
        Button { enabled, "OK" };

        { 10, 10, 90, 340 },
        StaticText { enabled, "^0" };
    }
};

resource 'DLOG' (130) {
    { 80, 80, 320, 480 },
    dBoxProc,
    visible,
    noGoAway,
    0,
    130,
    "Preferences",
    centerMainScreen
};

resource 'DITL' (130) {
    {
        { 200, 310, 220, 380 },
        Button { enabled, "OK" };

        { 200, 230, 220, 300 },
        Button { enabled, "Cancel" };

        { 16, 16, 32, 100 },
        StaticText { disabled, "FTP Host:" };

        { 16, 110, 32, 384 },
        EditText { enabled, "" };

        { 40, 16, 56, 100 },
        StaticText { disabled, "Port:" };

        { 40, 110, 56, 180 },
        EditText { enabled, "" };

        { 64, 16, 80, 100 },
        StaticText { disabled, "Username:" };

        { 64, 110, 80, 384 },
        EditText { enabled, "" };

        { 88, 16, 104, 100 },
        StaticText { disabled, "Password:" };

        { 88, 110, 104, 384 },
        EditText { enabled, "" };

        { 116, 16, 184, 384 },
        StaticText { enabled, "Community FTP mirrors change hosts and login details over time \0xd0 if Connect stops working, check macintoshgarden.org's forums for the current address." };
    }
};
