#include <Quickdraw.h>
#include <Windows.h>
#include <Fonts.h>
#include <Events.h>
#include <Menus.h>
#include <Dialogs.h>
#include <AppleEvents.h>
#include <OSUtils.h>
#include <string.h>
#include <stdio.h>

#include "app.h"
#include "theme.h"
#include "native.h"
#include "catalog.h"
#include "sidebar.h"
#include "results_view.h"
#include "toolbar.h"
#include "ftp.h"
#include "download.h"
#include "progress_dlg.h"
#include "prefs_dlg.h"

enum { mApple = 128, mFile = 129, mEdit = 130, mGo = 131, mConnection = 132 };
enum { iAbout = 1 };
enum { iPreferences = 1, iGetSelected = 2, iShowDownloads = 3, iQuit = 5 };
enum { iCut = 1, iCopy = 2, iPaste = 3, iClear = 4 };
/* Item 1 is "All" (kAllCategoryIndex). Items 2..9 are the 8 categories, in
   the exact order gCategories is defined in catalog_data.c - item text
   lives in main.r's Go menu and has to be kept in sync by hand if the
   catalog's category list ever changes, the same constraint
   mac-system7-c's Style menu documents (Rez text can't be data-driven from
   the C array). Item 10 is a divider; item 11 is the trailing Live FTP
   Browse row. */
#define kGoAllItem       1
#define kGoCategoryFirst 2
#define kGoLiveBrowse    11
enum { iConnect = 1, iDisconnect = 2, iRefreshListing = 3, iGoUpLevel = 4 };

#define kZoomDocProc 8 /* zoomDocProc - a Rez-only named constant in this toolchain's headers, not exposed to C */
#define kInfoAlertID 129
#define kMaxLiveFetch 200 /* live listing page size cap - see DoRefreshListing */

/* Same floor/ceiling GrowWindow already enforces via gSizeLimits below,
   named so ComputeScreenFitBounds can share them. */
#define kMinWindowWidth  420
#define kMinWindowHeight 260
#define kMaxWindowWidth  900
#define kMaxWindowHeight 780
#define kScreenMargin    8 /* breathing room from the screen/gray-region edges */

static WindowPtr gWindow;
static Boolean gDone = false;
static Boolean gConnected = false;
static Boolean gEverFetchedLive = false;
static char gStatusText[256] = "Not connected - choose Connection > Connect to reach the live server.";
static Rect gSizeLimits;
static GardenPrefs gPrefs;
static FtpSession gBrowseSession;
/* Current Live FTP Browse directory, root-relative, no leading/trailing
   slash, empty = server root - navigated by double-clicking a row (see
   ResultsActivation) or Connection > Go Up a Level. Live listings turned
   out to be all-folders at the root against the real server (confirmed in
   testing), so without this, Live FTP Browse could list folder names but
   never actually reach a downloadable file at all. */
static char gLivePath[200] = "";

/* See App_InBackground/App_HandleOSEvent in app.h. suspendResumeMessage/
   resumeFlag aren't in this stripped-down toolchain's Events.h, so they're
   defined locally - same vendoring precedent as mactcp_low.h for missing
   MacTCP constants, these are stable, well-documented Toolbox values, not
   guessed. */
#define kSuspendResumeMessage 1
#define kResumeFlag 1
static Boolean gInBackground = false;

Boolean App_InBackground(void) { return gInBackground; }
Boolean App_IsQuitting(void) { return gDone; }

void App_HandleOSEvent(const EventRecord *event)
{
    if (((event->message >> 24) & 0xFF) == kSuspendResumeMessage)
        gInBackground = (Boolean)((event->message & kResumeFlag) == 0);
}

static void ToolboxInit(void);
static void SetupMenus(void);
static void CreateMainWindow(void);
static void LayoutBrowser(WindowPtr w, Rect *toolbarR, Rect *sidebarR, Rect *resultsR, Rect *statusR);
static void DrawContent(WindowPtr w);
static void RelayoutAndRedraw(WindowPtr w);
static void RedrawStatusOnly(void);
static void ShowMessage(const char *msg);
static void HandleContentClick(WindowPtr w, Point local, unsigned long when);
static void PerformSearch(void);
static void ShowYearFilterMenu(const Rect *anchor);
static void ShowArchFilterMenu(const Rect *anchor);
static void ShowSystemFilterMenu(const Rect *anchor);
static void OnCategorySelected(short sel);
static void BeginDownload(const DownloadRequest *req);
static void DoConnect(void);
static void DoDisconnect(void);
static void DoRefreshListing(void);
static void LiveNavigateInto(const char *name);
static void LiveNavigateUp(void);
static void ResolveLiveDownloadPath(DownloadRequest *req);
static void HandleMenuChoice(long menuChoice);
static void HandleAppleMenu(short item);
static void HandleFileMenu(short item);
static void HandleEditMenu(short item);
static void HandleGoMenu(short item);
static void HandleConnectionMenu(short item);
static void AdjustMenus(void);
static void InstallAppleEventHandlers(void);

static void ToolboxInit(void)
{
    InitGraf(&qd.thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(NULL);
    InitCursor();
}

/* The 4 "required" Core Suite Apple Events every System 7+ app is
   expected to handle (Inside Macintosh's own App-readiness checklist) -
   Garden doesn't support opening/printing documents, so those two are
   pure no-ops, but they still have to be installed or a Finder/System
   feature that assumes every app answers them (e.g. drag-launching a
   document to a running app, or - the real-world case that surfaced this
   - Shut Down/Restart, which sends kAEQuitApplication to every running
   app and waits for a reply before actually proceeding) gets silent
   failures instead. Confirmed as a real, deterministic gap, not
   theoretical: nothing anywhere in this app installed any Apple Event
   handler, and the main event loop didn't even have a case for
   kHighLevelEvent, so an incoming Quit AppleEvent was received into the
   event record by WaitNextEvent and then just as silently discarded by
   the switch statement's implicit default - no reply ever sent back to
   whoever asked. */
static pascal OSErr HandleOpenAppAE(const AppleEvent *evt, AppleEvent *reply, int32_t refcon)
{
    (void)evt; (void)reply; (void)refcon;
    return noErr;
}

static pascal OSErr HandleOpenDocsAE(const AppleEvent *evt, AppleEvent *reply, int32_t refcon)
{
    (void)evt; (void)reply; (void)refcon;
    return noErr;
}

static pascal OSErr HandlePrintDocsAE(const AppleEvent *evt, AppleEvent *reply, int32_t refcon)
{
    (void)evt; (void)reply; (void)refcon;
    return noErr;
}

/* Same cleanup the File > Quit menu item and the window's close box
   already both do (see HandleFileMenu/inGoAway) - Shut Down/Restart/Log
   Out and an explicit Finder "Quit" all arrive here instead of through
   the menu, so this needs the identical disconnect-before-exit behavior,
   not a bare gDone = true.

   Unlike the menu item, this can also fire while a download is active -
   the menu can't be reached mid-transfer (progress_dlg.c's own event
   loop owns input then, and never dispatches MenuSelect), but this
   AppleEvent can arrive there too now that progress_dlg.c also calls
   AEProcessAppleEvent. Setting gDone here wouldn't unwind anything by
   itself in that case (we'd be many stack frames deep inside
   Download_Fetch), so this also sets the progress dialog's cancel flag -
   always safe even when nothing is downloading right now, since
   ProgressDlg_Show resets it on every new transfer - which drives the
   same, already-safe cancel path Download_Fetch's Stop button uses (see
   FTP_Disconnect/Net_Abort) to unwind promptly instead of finishing the
   transfer before ever noticing gDone below. */
static pascal OSErr HandleQuitAE(const AppleEvent *evt, AppleEvent *reply, int32_t refcon)
{
    (void)evt; (void)reply; (void)refcon;
    *ProgressDlg_CancelFlag() = true;
    if (gConnected) DoDisconnect();
    gDone = true;
    return noErr;
}

static void InstallAppleEventHandlers(void)
{
    AEInstallEventHandler(kCoreEventClass, kAEOpenApplication, NewAEEventHandlerUPP(HandleOpenAppAE), 0, false);
    AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments, NewAEEventHandlerUPP(HandleOpenDocsAE), 0, false);
    AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments, NewAEEventHandlerUPP(HandlePrintDocsAE), 0, false);
    AEInstallEventHandler(kCoreEventClass, kAEQuitApplication, NewAEEventHandlerUPP(HandleQuitAE), 0, false);
}

static void SetupMenus(void)
{
    MenuHandle m;

    m = GetMenu(mApple); InsertMenu(m, 0);
    m = GetMenu(mFile);  InsertMenu(m, 0);
    m = GetMenu(mEdit);  InsertMenu(m, 0);
    m = GetMenu(mGo);    InsertMenu(m, 0);
    m = GetMenu(mConnection); InsertMenu(m, 0);
    DrawMenuBar();
}

/* NewWindow's boundsRect is the CONTENT rect only - the Window Manager
   draws the title bar itself ABOVE bounds.top, not inside it. Confirmed
   by testing: without reserving this separately, a window positioned
   right at the menu bar's own bottom edge got its title bar drawn
   started that same amount *above* bounds.top, extending back up into
   the menu bar and getting visibly clipped by it. 20 is the standard
   classic Mac title bar height (kZoomDocProc's plain non-tabbed style,
   the only kind this app uses). */
#define kWindowTitleBarHeight 20

/* Fits a preferred w x h window inside the current screen's usable area -
   explicitly below the menu bar (GetMBarHeight(), not assumed - confirmed
   by testing that this toolchain's gray region does NOT already exclude
   it here, unlike real Mac OS's documented behavior, so relying on the
   gray region alone for that clipped the window's title bar right under
   the menu bar) and further inset by the gray region's own bounding box
   on top of that, which on real hardware/systems that have one active
   also shrinks for the Control Strip - taking the tighter of the two on
   each edge means either signal being conservative is enough to keep the
   window off both. Also the fix for a small physical screen: a Mac
   Plus/SE's 512x342 display (~322px tall after the menu bar) is much
   smaller than this app's own preferred 560x460, which would otherwise
   land the window mostly off-screen - this shrinks to fit instead, down
   to kMinWindowWidth/Height, and never grows past preferW/preferH on a
   bigger screen. */
static void ComputeScreenFitBounds(short preferW, short preferH, Rect *outBounds)
{
    Rect avail = qd.screenBits.bounds;
    Rect gray = (**LMGetGrayRgn()).rgnBBox;
    short availW, availH, w, h;

    avail.top = (short)(avail.top + GetMBarHeight());
    if (gray.left > avail.left) avail.left = gray.left;
    if (gray.top > avail.top) avail.top = gray.top;
    if (gray.right < avail.right) avail.right = gray.right;
    if (gray.bottom < avail.bottom) avail.bottom = gray.bottom;

    /* From here on, avail.top is where the window's CONTENT (not title
       bar) may start - the title bar occupies the kWindowTitleBarHeight
       px immediately above it, already-reserved. */
    avail.top = (short)(avail.top + kWindowTitleBarHeight);

    availW = (short)(avail.right - avail.left);
    availH = (short)(avail.bottom - avail.top);
    w = preferW;
    h = preferH;

    if (w > availW - kScreenMargin * 2) w = (short)(availW - kScreenMargin * 2);
    if (h > availH - kScreenMargin * 2) h = (short)(availH - kScreenMargin * 2);
    if (w < kMinWindowWidth) w = kMinWindowWidth;
    if (h < kMinWindowHeight) h = kMinWindowHeight;

    outBounds->left = (short)(avail.left + (availW - w) / 2);
    outBounds->top = (short)(avail.top + (availH - h) / 2);
    outBounds->right = (short)(outBounds->left + w);
    outBounds->bottom = (short)(outBounds->top + h);
}

static void CreateMainWindow(void)
{
    Rect bounds;
    Rect tb, sb, rs, st;

    /* Preferred size 560x460 (height along with kResultRowHeight's 40->52
       in theme.h - keeps roughly the same number of result rows visible
       by default now that rows are taller, fitting an optional second
       description line, rather than showing noticeably fewer at launch),
       shrunk to actually fit the screen - see ComputeScreenFitBounds. */
    ComputeScreenFitBounds(560, 460, &bounds);
    gWindow = NewWindow(NULL, &bounds, "\pMacintosh Garden", true,
                         kZoomDocProc, (WindowPtr)-1L, true, 0);
    SetPort(gWindow);

    SetRect(&gSizeLimits, kMinWindowWidth, kMinWindowHeight, kMaxWindowWidth, kMaxWindowHeight);

    Toolbar_Init(gWindow);
    LayoutBrowser(gWindow, &tb, &sb, &rs, &st);
    Toolbar_Layout(&tb, &st);

    /* All, not Featured - a search typed right after launch (before ever
       touching the sidebar) should cover the whole library, not silently
       come back empty just because Featured's small curated subset
       doesn't happen to contain the term. See kAllCategoryIndex/catalog.h. */
    ResultsView_ShowCategory(kAllCategoryIndex);
}

static void LayoutBrowser(WindowPtr w, Rect *toolbarR, Rect *sidebarR, Rect *resultsR, Rect *statusR)
{
    Rect port = w->portRect;

    toolbarR->left = port.left;
    toolbarR->right = port.right;
    toolbarR->top = port.top;
    toolbarR->bottom = (short)(port.top + kToolbarHeight);

    statusR->left = port.left;
    statusR->right = port.right;
    statusR->bottom = port.bottom;
    statusR->top = (short)(port.bottom - kStatusBarHeight);

    sidebarR->left = port.left;
    sidebarR->right = (short)(port.left + kSidebarWidth);
    sidebarR->top = toolbarR->bottom;
    sidebarR->bottom = statusR->top;

    resultsR->left = sidebarR->right;
    resultsR->right = port.right;
    resultsR->top = toolbarR->bottom;
    resultsR->bottom = statusR->top;

    /* Only ever as many full rows as actually fit - see
       ResultsView_SetPageSize's own comment for why a short results area
       must never draw a partial row bleeding into statusR below. A no-op
       when unchanged, so calling this on every layout pass (not just real
       resizes - LayoutBrowser also runs on every content click, just for
       hit-testing) is cheap. */
    ResultsView_SetPageSize((short)((resultsR->bottom - resultsR->top) / kResultRowHeight));
}

static void DrawContent(WindowPtr w)
{
    Rect tb, sb, rs, st;

    SetPort(w);
    LayoutBrowser(w, &tb, &sb, &rs, &st);

    Toolbar_DrawTop(&tb);
    Sidebar_Draw(&sb);
    ResultsView_Draw(&rs);
    Toolbar_DrawStatus(&st, gConnected, gStatusText, ResultsView_CurrentPage(), ResultsView_PageCount());

    DrawControls(w);
    DrawGrowIcon(w);
}

static void RelayoutAndRedraw(WindowPtr w)
{
    Rect tb, sb, rs, st;
    SetPort(w);
    LayoutBrowser(w, &tb, &sb, &rs, &st);
    Toolbar_Layout(&tb, &st);
    EraseRect(&w->portRect);
    DrawContent(w);
}

static void RedrawStatusOnly(void)
{
    Rect tb, sb, rs, st;
    SetPort(gWindow);
    LayoutBrowser(gWindow, &tb, &sb, &rs, &st);
    Toolbar_DrawStatus(&st, gConnected, gStatusText, ResultsView_CurrentPage(), ResultsView_PageCount());
    DrawControls(gWindow);
}

static void RedrawResultsAndStatus(void)
{
    Rect tb, sb, rs, st;
    SetPort(gWindow);
    LayoutBrowser(gWindow, &tb, &sb, &rs, &st);
    ResultsView_Draw(&rs);
    Toolbar_DrawStatus(&st, gConnected, gStatusText, ResultsView_CurrentPage(), ResultsView_PageCount());
    DrawControls(gWindow);
}

/* Shared by both StopAlert calls below (the About box and this generic
   message alert) - without it, a Quit AppleEvent arriving while either is
   up would be silently dropped, the same gap the main loop/progress
   dialog/Preferences all had (see app.h's App_IsQuitting comment). Unlike
   Preferences' own loop, StopAlert's internal one only cares about button
   clicks, not gDone, so this also auto-dismisses by reporting the OK
   click itself (item 1 in both this app's ALRT/DITL pairs) once quitting
   is detected, rather than leaving the alert sitting there waiting for a
   click that isn't coming. */
static pascal Boolean AlertQuitFilter(DialogPtr dlg, EventRecord *evt, short *itemHit)
{
    (void)dlg;
    if (evt->what == kHighLevelEvent) {
        AEProcessAppleEvent(evt);
        if (gDone) *itemHit = 1; /* OK - both ALRT/DITL 128 and 129 have it as item 1 */
        return true;
    }
    return false;
}

/* Generic message alert - ALRT/DITL 129 in main.r, a single OK button and
   a "^0"-substituted StaticText, same idiom mac-system7-c's Fail()/Warn()
   use. */
static void ShowMessage(const char *msg)
{
    Str255 s;
    CToPascal(msg, s);
    ParamText(s, "\p", "\p", "\p");
    StopAlert(kInfoAlertID, NewModalFilterUPP(AlertQuitFilter));
}

#define kBriefMessageTicks 180 /* ~3 seconds at 60 ticks/sec */
static unsigned long gBriefMessageShownAt = 0;

/* Same filter as AlertQuitFilter (dispatches AppleEvents so a Quit arriving
   while this is up isn't dropped) plus a second condition: auto-dismiss
   once kBriefMessageTicks have passed, same as if OK had been clicked.
   ModalDialog calls a filter proc on every event it processes internally,
   including idle nullEvents at its own polling rate, so this fires
   regularly on its own without needing any real input. */
static pascal Boolean BriefMessageFilter(DialogPtr dlg, EventRecord *evt, short *itemHit)
{
    (void)dlg;
    if (evt->what == kHighLevelEvent) AEProcessAppleEvent(evt);
    if (gDone || (TickCount() - gBriefMessageShownAt) >= kBriefMessageTicks) {
        *itemHit = 1; /* OK - item 1 in ALRT/DITL 129, same as ShowMessage */
        return true;
    }
    return false;
}

/* Download-completion messages (success or failure alike) use this
   instead of ShowMessage: a Note icon, not Stop, and it goes away on its
   own after a few seconds rather than sitting there demanding a click.
   Explicit request, not a style nitpick - downloads can now finish while
   the user is off in another application entirely (see BeginDownload's
   async note), so an alert styled like an error and requiring an
   explicit dismissal is a bad fit for something that just happened
   quietly in the background, whether it succeeded or not. */
static void ShowBriefMessage(const char *msg)
{
    Str255 s;
    CToPascal(msg, s);
    ParamText(s, "\p", "\p", "\p");
    gBriefMessageShownAt = TickCount();
    NoteAlert(kInfoAlertID, NewModalFilterUPP(BriefMessageFilter));
}

static void PerformSearch(void)
{
    char query[256];
    Toolbar_GetSearchText(query, sizeof(query));
    ResultsView_ShowSearch(query);
    RedrawResultsAndStatus();
}

/* Both filter menus are built fresh on every click rather than kept as
   real MENU resources - the item text is generated (Catalog_*FilterLabel)
   and there's no need for these to exist except while actually open, the
   same reasoning a real "pop-up button" Control would use internally.
   Menu IDs 200/201 are otherwise unused by this app's real (Rez-defined)
   menus, which top out at 132. anchor is the sidebar pill's rect
   (window-local - see Sidebar_Get*FilterRect), converted to global here
   since that's a window/event-loop concern, not a sidebar-drawing one. */
static void ShowYearFilterMenu(const Rect *anchor)
{
    Rect r = *anchor;
    MenuHandle m;
    Point tl;
    long result;
    short item;

    tl.h = r.left;
    tl.v = r.bottom;
    SetPort(gWindow);
    LocalToGlobal(&tl);

    m = NewMenu(200, "\pYear");
    AppendMenu(m, "\pAny Year;Before 1990;1990-1993;1994-1996;1997 or later");
    InsertMenu(m, -1);

    result = PopUpMenuSelect(m, tl.v, tl.h, (short)(Catalog_GetYearFilter() + 1));
    item = LoWord(result);
    if (item != 0) {
        Catalog_SetYearFilter((CatalogYearFilter)(item - 1));
        ResultsView_RefreshFilter();
        RelayoutAndRedraw(gWindow); /* not just RedrawResultsAndStatus - the
                                        pill button's own label (drawn as
                                        part of the sidebar) needs to
                                        change too, not just the list */
    }

    DeleteMenu(200);
    DisposeMenu(m);
}

static void ShowArchFilterMenu(const Rect *anchor)
{
    Rect r = *anchor;
    MenuHandle m;
    Point tl;
    long result;
    short item;

    tl.h = r.left;
    tl.v = r.bottom;
    SetPort(gWindow);
    LocalToGlobal(&tl);

    m = NewMenu(201, "\pCPU");
    AppendMenu(m, "\pAny CPU;68k;PPC");
    InsertMenu(m, -1);

    result = PopUpMenuSelect(m, tl.v, tl.h, (short)(Catalog_GetArchFilter() + 1));
    item = LoWord(result);
    if (item != 0) {
        Catalog_SetArchFilter((CatalogArchFilter)(item - 1));
        ResultsView_RefreshFilter();
        RelayoutAndRedraw(gWindow);
    }

    DeleteMenu(201);
    DisposeMenu(m);
}

static void ShowSystemFilterMenu(const Rect *anchor)
{
    Rect r = *anchor;
    MenuHandle m;
    Point tl;
    long result;
    short item;

    tl.h = r.left;
    tl.v = r.bottom;
    SetPort(gWindow);
    LocalToGlobal(&tl);

    m = NewMenu(202, "\pSystem");
    AppendMenu(m, "\pAny System;System 6;System 7;System 8+");
    InsertMenu(m, -1);

    result = PopUpMenuSelect(m, tl.v, tl.h, (short)(Catalog_GetSysFilter() + 1));
    item = LoWord(result);
    if (item != 0) {
        Catalog_SetSysFilter((CatalogSysFilter)(item - 1));
        ResultsView_RefreshFilter();
        RelayoutAndRedraw(gWindow);
    }

    DeleteMenu(202);
    DisposeMenu(m);
}

static void OnCategorySelected(short sel)
{
    Toolbar_ClearSearch();

    if (sel == kLiveBrowseRowIndex) {
        ResultsView_EnterLiveMode();
        RedrawResultsAndStatus();
        if (!gEverFetchedLive) {
            gEverFetchedLive = true; /* only auto-fetch the first time - Refresh Listing covers the rest */
            strncpy(gLivePath, gPrefs.basePath, sizeof(gLivePath) - 1);
            gLivePath[sizeof(gLivePath) - 1] = 0;
            DoRefreshListing();
        }
    } else {
        ResultsView_ShowCategory(sel);
        RedrawResultsAndStatus();
    }
}

/* Real download: shows the progress window, lets Download_Fetch drive it
   via ProgressDlg_GiveTime/UpdateProgress, then reports the outcome. Most
   catalog entries now carry a verified remotePath (see catalog_data.c),
   same as a Live FTP Browse entry, so a failure no longer means "this was
   probably just a guessed path" the way it used to - a plain error plus a
   pointer at Live FTP Browse (which always downloads exactly what it just
   listed, so it's the reliable fallback either way) covers both. */
static void BeginDownload(const DownloadRequest *req)
{
    OSErr err;
    Boolean *cancel;

    ProgressDlg_Show(req->title);
    cancel = ProgressDlg_CancelFlag();
    err = Download_Fetch(gPrefs.host, gPrefs.port, gPrefs.user, gPrefs.pass,
                          req->remotePath, ProgressDlg_UpdateProgress, NULL,
                          ProgressDlg_GiveTime, cancel);
    ProgressDlg_Hide();

    if (err == noErr) {
        char msg[300];
        sprintf(msg, "\xd2%.200s\xd3 was saved in the Garden Downloads folder, next to the application.", req->title);
        ShowBriefMessage(msg);
    } else if (err == userCanceledErr) {
        /* the user asked to stop - no need to alert them about their own action */
    } else {
        char msg[400];
        sprintf(msg, "Couldn't download \xd2%.150s\xd3 (error %d). If this keeps happening, try Live FTP Browse instead, which downloads exactly what it just listed.",
                req->title, (int)err);
        ShowBriefMessage(msg);
    }
}

static void DoConnect(void)
{
    OSErr err;
    Boolean *cancel;

    if (gConnected) return;

    ProgressDlg_Show("Connecting to Macintosh Garden\xc9");
    cancel = ProgressDlg_CancelFlag();
    err = FTP_Connect(&gBrowseSession, gPrefs.host, gPrefs.port, gPrefs.user, gPrefs.pass,
                       ProgressDlg_GiveTime, cancel);
    ProgressDlg_Hide();

    if (err == noErr) {
        gConnected = true;
        strcpy(gStatusText, "Connected to Macintosh Garden.");
    } else if (err == userCanceledErr) {
        strcpy(gStatusText, "Connect canceled.");
    } else {
        sprintf(gStatusText, "Connect failed (error %d) - check Preferences.", (int)err);
    }
    RedrawStatusOnly();
}

static void DoDisconnect(void)
{
    if (!gConnected) return;
    FTP_Disconnect(&gBrowseSession, NULL, NULL);
    gConnected = false;
    strcpy(gStatusText, "Not connected.");
    RedrawStatusOnly();
}

/* Fetches a real, live NLST at gLivePath into ResultsView's Live FTP
   Browse listing - names only; sizes are deliberately left unknown here
   (shown as "unknown" until the user actually downloads something) rather
   than issuing a SIZE call per listed file, which would turn browsing a
   big directory into one round trip per entry.

   Live listings can't be assumed to be files - the real server's root
   turned out to be all folders (apps/manuals/games) when this was tested,
   so entries here are just as likely to be folders to navigate into
   (double-click) as files to download (Get) - see ResultsActivation. */
static void DoRefreshListing(void)
{
    static char names[kMaxLiveFetch][64];
    static unsigned long sizes[kMaxLiveFetch];
    static Boolean sizeKnown[kMaxLiveFetch];
    short count, i;
    Boolean *cancel;

    if (!gConnected) {
        DoConnect();
        if (!gConnected) return;
    }

    ProgressDlg_Show("Fetching file listing\xc9");
    cancel = ProgressDlg_CancelFlag();
    count = FTP_ListNames(&gBrowseSession, gLivePath, names, kMaxLiveFetch,
                           ProgressDlg_GiveTime, cancel);
    ProgressDlg_Hide();

    for (i = 0; i < count; i++) { sizes[i] = 0; sizeKnown[i] = false; }
    ResultsView_ShowLiveListing(names, sizes, sizeKnown, count);

    {
        const char *pathLabel = (gLivePath[0] != 0) ? gLivePath : "/";
        if (count > 0)
            sprintf(gStatusText, "Connected - %.100s - %d item%s listed.",
                    pathLabel, count, (count == 1) ? "" : "s");
        else
            sprintf(gStatusText, "Connected - %.100s - empty, or not readable.", pathLabel);
    }

    RedrawResultsAndStatus();
}

/* Appends name to the current live path and refreshes - used when a
   double-click on a Live FTP Browse row turns out to be a folder rather
   than something downloadable. */
static void LiveNavigateInto(const char *name)
{
    char newPath[sizeof(gLivePath)];

    if (gLivePath[0] == 0) {
        strncpy(newPath, name, sizeof(newPath) - 1);
        newPath[sizeof(newPath) - 1] = 0;
    } else {
        sprintf(newPath, "%.90s/%.90s", gLivePath, name);
    }
    strcpy(gLivePath, newPath);

    ResultsView_EnterLiveMode();
    DoRefreshListing();
}

/* Connection > Go Up a Level - strips the last path component. */
static void LiveNavigateUp(void)
{
    char *slash = strrchr(gLivePath, '/');
    if (slash != NULL) *slash = 0;
    else gLivePath[0] = 0;

    ResultsView_EnterLiveMode();
    DoRefreshListing();
}

/* A live entry's remotePath is just its bare name (see
   ResultsView_ShowLiveListing) - if we've navigated into a subdirectory,
   the actual FTP path needed for SIZE/RETR is gLivePath + "/" + that name,
   since Download_Fetch always starts a brand new control connection (at
   the login's default directory), not a continuation of the browse
   session's CWD state. A no-op for catalog entries or a live entry at the
   root. */
static void ResolveLiveDownloadPath(DownloadRequest *req)
{
    char full[sizeof(req->remotePath)];

    if (!req->isLiveFile || gLivePath[0] == 0) return;

    sprintf(full, "%.100s/%.100s", gLivePath, req->remotePath);
    strncpy(req->remotePath, full, sizeof(req->remotePath) - 1);
    req->remotePath[sizeof(req->remotePath) - 1] = 0;
}

static void HandleContentClick(WindowPtr w, Point local, unsigned long when)
{
    Rect tb, sb, rs, st;
    LayoutBrowser(w, &tb, &sb, &rs, &st);

    if (PtInRect(local, &tb)) {
        ToolbarHit hit = Toolbar_Click(local);
        if (hit == kToolbarHitSearchSubmit) PerformSearch();
        return;
    }
    if (PtInRect(local, &st)) {
        ToolbarHit hit = Toolbar_Click(local);
        if (hit == kToolbarHitPrevPage) { ResultsView_PrevPage(&rs); RedrawStatusOnly(); }
        else if (hit == kToolbarHitNextPage) { ResultsView_NextPage(&rs); RedrawStatusOnly(); }
        return;
    }
    if (PtInRect(local, &sb)) {
        SidebarFilterKind kind;
        short sel;
        if (Sidebar_ClickFilter(&sb, local, &kind)) {
            Rect r;
            switch (kind) {
                case kSidebarFilterYear:   Sidebar_GetYearFilterRect(&sb, &r);   ShowYearFilterMenu(&r);   break;
                case kSidebarFilterArch:   Sidebar_GetArchFilterRect(&sb, &r);   ShowArchFilterMenu(&r);   break;
                case kSidebarFilterSystem: Sidebar_GetSystemFilterRect(&sb, &r); ShowSystemFilterMenu(&r); break;
            }
            return;
        }
        sel = Sidebar_Click(&sb, local);
        if (sel >= kAllCategoryIndex) OnCategorySelected(sel); /* kAllCategoryIndex (-1) is a real selection now, not "nothing hit" */
        return;
    }
    if (PtInRect(local, &rs)) {
        DownloadRequest req;
        ResultsActivation activation;
        if (ResultsView_Click(&rs, local, when, &req, &activation)) {
            if (activation == kResultsActivationDoubleClick && ResultsView_IsLiveMode()) {
                LiveNavigateInto(req.remotePath); /* bare name; might be a file, might be a folder */
            } else {
                ResolveLiveDownloadPath(&req);
                BeginDownload(&req);
            }
        }
        return;
    }
}

static void HandleAppleMenu(short item)
{
    if (item == iAbout) StopAlert(128, NewModalFilterUPP(AlertQuitFilter));
}

static void HandleFileMenu(short item)
{
    DownloadRequest req;

    switch (item) {
        case iPreferences:
            PrefsDlg_Run(&gPrefs);
            break;
        case iGetSelected:
            if (ResultsView_GetSelected(&req)) {
                ResolveLiveDownloadPath(&req);
                BeginDownload(&req);
            } else {
                ShowMessage("Select an item in the list first, then choose Get Selected Item (or just click its Get button).");
            }
            break;
        case iShowDownloads:
            ShowMessage("Downloaded files are saved in a \xd2Garden Downloads\xd3 folder, created next to the application.");
            break;
        case iQuit:
            if (gConnected) DoDisconnect();
            gDone = true;
            break;
    }
}

static void HandleEditMenu(short item)
{
    switch (item) {
        case iCut:   Toolbar_EditCut();   break;
        case iCopy:  Toolbar_EditCopy();  break;
        case iPaste: Toolbar_EditPaste(); break;
        case iClear: Toolbar_EditClear(); break;
    }
}

static void HandleGoMenu(short item)
{
    Rect tb, sb, rs, st;
    short sel;

    LayoutBrowser(gWindow, &tb, &sb, &rs, &st);

    if (item == kGoAllItem) {
        sel = kAllCategoryIndex;
    } else if (item >= kGoCategoryFirst && item < kGoCategoryFirst + kCategoryCount) {
        sel = (short)(item - kGoCategoryFirst);
    } else if (item == kGoLiveBrowse) {
        sel = kLiveBrowseRowIndex;
    } else {
        return;
    }

    Sidebar_SetSelected(&sb, sel);
    OnCategorySelected(sel);
}

static void HandleConnectionMenu(short item)
{
    switch (item) {
        case iConnect:        DoConnect(); break;
        case iDisconnect:     DoDisconnect(); break;
        case iRefreshListing: DoRefreshListing(); break;
        case iGoUpLevel:      if (gLivePath[0] != 0) LiveNavigateUp(); break;
    }
}

static void AdjustMenus(void)
{
    MenuHandle editMenu = GetMenuHandle(mEdit);
    MenuHandle connMenu = GetMenuHandle(mConnection);
    if (editMenu) {
        EnableItem(editMenu, iCut);
        EnableItem(editMenu, iCopy);
        EnableItem(editMenu, iPaste);
        EnableItem(editMenu, iClear);
    }
    if (connMenu) {
        if (gConnected) {
            EnableItem(connMenu, iDisconnect);
            DisableItem(connMenu, iConnect);
        } else {
            EnableItem(connMenu, iConnect);
            DisableItem(connMenu, iDisconnect);
        }
        if (gLivePath[0] != 0) EnableItem(connMenu, iGoUpLevel);
        else DisableItem(connMenu, iGoUpLevel);
    }
}

static void HandleMenuChoice(long menuChoice)
{
    short menuID = (short)(menuChoice >> 16);
    short item = (short)(menuChoice & 0xFFFF);

    switch (menuID) {
        case mApple:      HandleAppleMenu(item); break;
        case mFile:        HandleFileMenu(item); break;
        case mEdit:        HandleEditMenu(item); break;
        case mGo:          HandleGoMenu(item); break;
        case mConnection:  HandleConnectionMenu(item); break;
    }
    HiliteMenu(0);
}

void RunApp(void)
{
    EventRecord event;

    ToolboxInit();
    InstallAppleEventHandlers();
    Prefs_Load(&gPrefs);
    if (Catalog_Load() == kCatalogLoadRejected)
        ShowMessage("The \xd2Garden Catalog\xd3 file next to this application couldn\xd5t be read, so the built-in catalog is being used instead. Check that it wasn\xd5t corrupted in transfer, or remove it to use the built-in catalog on purpose.");
    SetupMenus();
    CreateMainWindow();
    DrawContent(gWindow);

    while (!gDone) {
        AdjustMenus();
        /* A blinking search-field caret in a window that isn't even
           frontmost is exactly the kind of thing a well-behaved
           background app doesn't do - costs the switched-to app some
           CPU for no visible benefit, since Garden's own window isn't on
           screen (or isn't the active one) to see it blink anyway. */
        if (!gInBackground) Toolbar_Idle();

        if (WaitNextEvent(everyEvent, &event, 15, NULL)) {
            switch (event.what) {
                case mouseDown: {
                    WindowPtr which;
                    short part = FindWindow(event.where, &which);
                    switch (part) {
                        case inMenuBar:
                            HandleMenuChoice(MenuSelect(event.where));
                            break;
                        case inSysWindow:
                            SystemClick(&event, which);
                            break;
                        case inDrag: {
                            /* A NULL boundsRect here technically compiles
                               (DragWindow's third param is just a const
                               Rect*), but real Mac apps always pass a real
                               constraint rect - this ROM's DragWindow
                               doesn't appear to null-check it, so a NULL
                               silently produces a zero-size drag region
                               rather than an error, which looks exactly
                               like "dragging does nothing" (confirmed:
                               this was the actual bug behind that report,
                               not a hit-testing issue - inDrag was already
                               being detected and DragWindow was already
                               being called correctly). qd.screenBits.bounds
                               inset by the title bar height keeps the
                               title bar itself always draggable back into
                               view rather than letting the whole window
                               go off-screen. */
                            Rect dragBounds = qd.screenBits.bounds;
                            InsetRect(&dragBounds, 4, 4);
                            DragWindow(which, event.where, &dragBounds);
                            break;
                        }
                        case inGoAway:
                            if (TrackGoAway(which, event.where)) {
                                if (gConnected) DoDisconnect();
                                gDone = true;
                            }
                            break;
                        case inGrow: {
                            long newSize = GrowWindow(which, event.where, &gSizeLimits);
                            if (newSize != 0) {
                                SizeWindow(which, LoWord(newSize), HiWord(newSize), true);
                                RelayoutAndRedraw(which);
                            }
                            break;
                        }
                        case inZoomIn:
                        case inZoomOut:
                            if (TrackBox(which, event.where, part)) {
                                SetPort(which);
                                ZoomWindow(which, part, true);
                                if (part == inZoomOut) {
                                    /* Growing to the "standard" (larger)
                                       state - ZoomWindow's own guess at
                                       that size can still cover the menu
                                       bar/Control Strip on some setups, so
                                       clamp it back to the same
                                       gray-region-fit bounds the launch
                                       window uses whenever it overshoots. */
                                    Rect fit;
                                    short curW = (short)(which->portRect.right - which->portRect.left);
                                    short curH = (short)(which->portRect.bottom - which->portRect.top);
                                    ComputeScreenFitBounds(kMaxWindowWidth, kMaxWindowHeight, &fit);
                                    if (curW > fit.right - fit.left || curH > fit.bottom - fit.top) {
                                        MoveWindow(which, fit.left, fit.top, false);
                                        SizeWindow(which, (short)(fit.right - fit.left),
                                                   (short)(fit.bottom - fit.top), true);
                                    }
                                }
                                RelayoutAndRedraw(which);
                            }
                            break;
                        case inContent:
                            if (which != FrontWindow()) {
                                SelectWindow(which);
                            } else {
                                Point local = event.where;
                                SetPort(which);
                                GlobalToLocal(&local);
                                HandleContentClick(which, local, event.when);
                            }
                            break;
                    }
                    break;
                }
                case keyDown:
                case autoKey: {
                    char key = (char)(event.message & charCodeMask);
                    if (event.modifiers & cmdKey) {
                        HandleMenuChoice(MenuKey(key));
                    } else {
                        if (Toolbar_HandleKey(&event)) PerformSearch();
                    }
                    break;
                }
                case updateEvt: {
                    WindowPtr w = (WindowPtr)event.message;
                    BeginUpdate(w);
                    DrawContent(w);
                    EndUpdate(w);
                    break;
                }
                case activateEvt: {
                    WindowPtr w = (WindowPtr)event.message;
                    SetPort(w);
                    DrawGrowIcon(w);
                    break;
                }
                case osEvt:
                    App_HandleOSEvent(&event);
                    break;
                case kHighLevelEvent:
                    AEProcessAppleEvent(&event);
                    break;
            }
        }
    }

    FTP_Shutdown();
}
