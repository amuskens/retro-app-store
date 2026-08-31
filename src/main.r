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
    5750 * 1024, /* preferred - revised DOWN this round after the 6500K
                     value above (set for the catalog's 2,445-entry
                     expansion) was found, by live testing, to cause a
                     worse regression than the problem it was meant to
                     solve. Root cause traced (not just patched around):
                     gCatalogEntries used to be a real, always-allocated
                     `CatalogEntry[kMaxCatalogEntries]` static array
                     (675,000 bytes, kMaxCatalogEntries=2500 *
                     sizeof(CatalogEntry)=270, measured with the real m68k
                     cross-compiler) that Catalog_Load() populated by
                     *copying* the compiled-in gDefaultCatalogEntries
                     (2,445 entries * 270 = 660,150 bytes) into - both
                     existing simultaneously for what, in the common case
                     (no custom "Garden Catalog" file), is the exact same
                     data twice. Fixed properly this round: gCatalogEntries
                     is now `const CatalogEntry *`, pointing directly at
                     gDefaultCatalogEntries with no copy in the common
                     case, and at a heap buffer sized to the actual loaded
                     file's entry count (not kMaxCatalogEntries) only when
                     a real file is loaded - see catalog.h/catalog.c/
                     catalog_load.c.

                     Two values were live-tested this round on the
                     project's standard 8MB-RAM config, both by real
                     measurement rather than by extrapolating an old
                     hardware note or by arithmetic alone:

                     5750K (5000K, an old note from a real IIcx's -41 Open
                     Transport fix, plus one ~645K catalog copy) DID launch
                     successfully (Process Manager granted it ~4,432K, per
                     "About This Macintosh" - see below for why not the
                     full 5750K), but Connect cleanly and reproducibly
                     still failed with -23 (confirmed via the app's own
                     "Live FTP Browse" row, which attempts a connection the
                     moment it's selected - a more reliable repro than
                     driving the Connection menu). "About This Macintosh"
                     showed System Software (Open Transport plus this test
                     system's extensions) alone using 3,639K, leaving only
                     ~4,433K for applications - and since classic Mac OS
                     grants a launching app *all* remaining free memory
                     when its preferred size can't be met (not just its
                     stated minimum), Garden claimed basically that entire
                     remainder, driving "Largest Unused Block" to zero -
                     real system-wide memory Open Transport itself needs
                     room to grow into for a live connection (its own
                     dynamic per-endpoint state), separate from Garden's
                     own partition. Confirmed this is a genuine memory-
                     total problem, not a Garden bug: the exact same build
                     (5750K/2250K unchanged) connects immediately and
                     downloaded 20 different real catalog items back to
                     back with zero crashes/hangs at 16MB total RAM - a
                     realistic figure for an Open Transport-era System 7.5
                     Mac (8MB was more of a System 7.0/7.1-era MacTCP
                     baseline before OT's own larger footprint). See the
                     README for the resulting minimum-RAM note.

                     3200K (2500K/1536K, the last values confirmed to work
                     before this catalog round, plus the ~618K net catalog
                     growth since - see the minimum value's comment) was
                     tried next and made things *worse*: Garden's own
                     startup hung completely (desktop responsive, guest
                     clock still advancing, but Garden's window never
                     appeared, for minutes) rather than failing gracefully
                     - meaning this app's own real runtime footprint
                     (code+globals+heap for window/control/TE setup,
                     catalog filtering, etc.) needs more than 3200K to
                     even finish launching, beyond what the old-baseline-
                     plus-catalog-growth arithmetic accounted for (other
                     feature work landed this session besides the catalog
                     - AppleEvent handling, the sidebar/DNR fixes, etc. -
                     which also cost some code+data footprint the old
                     baseline never included). That arithmetic approach is
                     evidently not reliable on its own here.

                     Given a hang is a worse failure mode than a slow but
                     graceful launch, this reverts to 5750K - the larger
                     of the two live-tested values, confirmed to at least
                     launch correctly - as the safe known-good number
                     rather than continuing to guess smaller ones without
                     a tighter test loop (e.g. bisecting) to pin down the
                     real minimum. Revisit with that tighter loop before
                     trying to shrink this further. */
    2250 * 1024       /* minimum - same reasoning as preferred above: the
                          old 1536K baseline (last confirmed to work before
                          this catalog round) plus the same ~618K net
                          catalog growth = ~2154K, rounded up to 2250K. */
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
