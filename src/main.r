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
    2500 * 1024, /* preferred - NOTE: this was previously bumped to 5000K
                     after real IIcx hardware hit mFulErr (-41, "not enough
                     room in the heap zone") on every download while
                     connected via Open Transport (OT's MacTCP-compat layer
                     has a real, well-known heavier memory footprint than
                     native MacTCP). Lowered to 2500K on request - some
                     headroom above the plain 2048K default, but well below
                     the confirmed-working 5000K; if downloads over OT
                     start failing with -41 again on real hardware, this is
                     the first thing to re-check. */
    1536 * 1024       /* minimum - the catalog's fixed-capacity entry array
                          (kMaxCatalogEntries in catalog.h) accounts for a
                          real chunk of this; also bumped up from 768K for
                          some OT headroom on memory-constrained real
                          hardware, though the confirmed fix was specifically
                          the preferred size above, not this floor */
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
    { 80, 80, 220, 420 },
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
        { 110, 250, 130, 320 },
        Button { enabled, "OK" };

        { 10, 10, 100, 320 },
        StaticText { enabled, "Macintosh Garden \xd0 a classic Mac client for browsing and downloading software over FTP. Prototype built with Retro68." };
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
        StaticText { enabled, "Community FTP mirrors change hosts and login details over time \xd0 if Connect stops working, check macintoshgarden.org's forums for the current address." };
    }
};
