#include <Quickdraw.h>
#include <Windows.h>
#include <Fonts.h>
#include <Events.h>
#include <Menus.h>
#include <Dialogs.h>
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

static void CreateMainWindow(void)
{
    Rect bounds;
    Rect tb, sb, rs, st;

    /* Height bumped 380->460 along with kResultRowHeight's 40->52 (see
       theme.h) - keeps roughly the same number of result rows visible by
       default now that rows are taller (fitting an optional second
       description line) rather than showing noticeably fewer at launch. */
    SetRect(&bounds, 40, 60, 40 + 560, 60 + 460);
    gWindow = NewWindow(NULL, &bounds, "\pMacintosh Garden", true,
                         kZoomDocProc, (WindowPtr)-1L, true, 0);
    SetPort(gWindow);

    SetRect(&gSizeLimits, 420, 260, 900, 780);

    Toolbar_Init(gWindow);
    LayoutBrowser(gWindow, &tb, &sb, &rs, &st);
    Toolbar_Layout(&tb, &st);

    ResultsView_ShowCategory(0);
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

/* Generic message alert - ALRT/DITL 129 in main.r, a single OK button and
   a "^0"-substituted StaticText, same idiom mac-system7-c's Fail()/Warn()
   use. */
static void ShowMessage(const char *msg)
{
    Str255 s;
    CToPascal(msg, s);
    ParamText(s, "\p", "\p", "\p");
    StopAlert(kInfoAlertID, NULL);
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
        ShowMessage(msg);
    } else if (err == userCanceledErr) {
        /* the user asked to stop - no need to alert them about their own action */
    } else {
        char msg[400];
        sprintf(msg, "Couldn't download \xd2%.150s\xd3 (error %d). If this keeps happening, try Live FTP Browse instead, which downloads exactly what it just listed.",
                req->title, (int)err);
        ShowMessage(msg);
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
    if (item == iAbout) StopAlert(128, NULL);
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
            }
        }
    }
}
