#include <string.h>
#include <stdio.h>
#include <Quickdraw.h>
#include <Windows.h>
#include <Fonts.h>
#include <Events.h>
#include <Menus.h>
#include <AppleEvents.h>

#include "progress_dlg.h"
#include "theme.h"
#include "native.h"
#include "catalog.h"
#include "app.h"

#define kDlgWidth  340
#define kDlgHeight 120

static WindowPtr gWindow = NULL;
static ControlHandle gStopButton;
static Boolean gCancel = false;
static char gTitleText[256];
static char gByteText[64];
static unsigned long gBytesSoFar = 0;
static unsigned long gTotalBytes = 0;
static Boolean gTotalKnown = false;

/* Draws just the progress bar and byte-count text - the two things that
   actually change as bytes come in. Deliberately does NOT touch the title
   or call DrawControls: this runs once per chunk received (many times a
   second on a fast download), and on real hardware repeatedly erasing and
   redrawing the whole window that often reads as a distracting flicker,
   not a smooth progress indicator. The progress bar itself never needs an
   erase first - it only ever grows within its own frame - but the byte
   text does, since new text is usually shorter or differently-shaped than
   what it's replacing. */
static void DrawProgress(void)
{
    Rect r, barR, byteR;
    short permille;

    if (gWindow == NULL) return;
    SetPort(gWindow);
    r = gWindow->portRect;

    barR = r;
    InsetRect(&barR, 16, 0);
    barR.top = 44;
    barR.bottom = 60;
    /* Divide the total down instead of multiplying the byte count up -
       real bug, caught from a screenshot rather than review: the old
       (gBytesSoFar * 1000UL) overflows 32 bits once ~4.29MB have
       arrived, and since this bar deliberately never erases (it "only
       ever grows"), the wrapped-small permille just stopped moving it -
       every download larger than ~4.2MB showed a bar frozen at whatever
       point it had reached when the multiply wrapped (~38% for a 10.8MB
       file, measured), while the byte text underneath kept counting
       up correctly. The divide-first form keeps every intermediate value
       within range for any file size a 32-bit byte count can express;
       the truncation in gTotalBytes/1000 costs at most ~0.1% accuracy,
       which the 1000-clamp below already absorbs. The multiply-first
       form is kept for totals under 1000 bytes (where divide-first
       would divide by zero, and where it cannot overflow anyway). */
    if (gTotalKnown && gTotalBytes >= 1000)
        permille = (short)(gBytesSoFar / (gTotalBytes / 1000UL));
    else if (gTotalKnown && gTotalBytes > 0)
        permille = (short)((gBytesSoFar * 1000UL) / gTotalBytes);
    else
        permille = 0;
    if (permille > 1000) permille = 1000;
    Theme_DrawProgressBar(&barR, permille, gTotalKnown);

    byteR = r;
    InsetRect(&byteR, 16, 0);
    byteR.top = 66;
    byteR.bottom = 80;
    EraseRect(&byteR);
    Theme_SetGeneva(9, normal);
    Theme_SetDescColor();
    DrawCStringInRect(gByteText, &byteR);
    Theme_SetBlack();
}

/* Full redraw - title, progress bar, byte text, and controls - for the
   initial draw and for genuine update events (window actually exposed/
   damaged). Not used for routine progress ticks; see DrawProgress. */
static void DrawContent(void)
{
    Rect r, textR;

    if (gWindow == NULL) return;
    SetPort(gWindow);
    r = gWindow->portRect;
    EraseRect(&r);

    textR = r;
    InsetRect(&textR, 16, 0);
    textR.top = 16;
    textR.bottom = 32;
    Theme_SetGeneva(10, normal);
    DrawCStringInRect(gTitleText, &textR);

    DrawProgress();

    DrawControls(gWindow);
}

void ProgressDlg_Show(const char *title)
{
    Rect bounds, screenBounds, btnR;
    Str255 s;
    short left, top;

    screenBounds = qd.screenBits.bounds;
    left = (short)(((screenBounds.right - screenBounds.left) - kDlgWidth) / 2);
    top = (short)(((screenBounds.bottom - screenBounds.top) - kDlgHeight) / 3);
    SetRect(&bounds, left, top, (short)(left + kDlgWidth), (short)(top + kDlgHeight));

    gWindow = NewWindow(NULL, &bounds, "\pDownloading", true, movableDBoxProc, (WindowPtr)-1L, false, 0);
    SetPort(gWindow);

    strncpy(gTitleText, title, sizeof(gTitleText) - 1);
    gTitleText[sizeof(gTitleText) - 1] = 0;
    strcpy(gByteText, "Connecting\xc9");
    gBytesSoFar = 0;
    gTotalBytes = 0;
    gTotalKnown = false;
    gCancel = false;

    btnR.right = (short)(kDlgWidth - 16);
    btnR.left = (short)(btnR.right - 70);
    btnR.top = 86;
    btnR.bottom = 106;
    CToPascal("Stop", s);
    gStopButton = NewControl(gWindow, &btnR, s, true, 0, 0, 0, pushButProc, 0);

    DrawContent();
}

void ProgressDlg_Hide(void)
{
    if (gWindow != NULL) {
        DisposeWindow(gWindow);
        gWindow = NULL;
    }
}

Boolean *ProgressDlg_CancelFlag(void)
{
    return &gCancel;
}

void ProgressDlg_UpdateProgress(void *userData, unsigned long bytesSoFar,
                                 unsigned long totalBytes, Boolean totalKnown)
{
    char sizeSoFar[24], sizeTotal[24];
    (void)userData;

    gBytesSoFar = bytesSoFar;
    gTotalBytes = totalBytes;
    gTotalKnown = totalKnown;

    Catalog_FormatSize(bytesSoFar, sizeSoFar, sizeof(sizeSoFar));
    if (totalKnown) {
        Catalog_FormatSize(totalBytes, sizeTotal, sizeof(sizeTotal));
        sprintf(gByteText, "%s of %s", sizeSoFar, sizeTotal);
    } else {
        sprintf(gByteText, "%s received", sizeSoFar);
    }

    DrawProgress();
}

void ProgressDlg_GiveTime(void)
{
    EventRecord event;

    if (gWindow == NULL) return;

    if (WaitNextEvent(everyEvent, &event, 1, NULL)) {
        switch (event.what) {
            case mouseDown: {
                WindowPtr which;
                short part = FindWindow(event.where, &which);
                if (part == inContent && which == gWindow) {
                    Point local = event.where;
                    ControlHandle ctl;
                    SetPort(gWindow);
                    GlobalToLocal(&local);
                    if (FindControl(local, gWindow, &ctl) != 0 && ctl == gStopButton) {
                        if (TrackControl(ctl, local, NULL) != 0) gCancel = true;
                    }
                } else if (part == inDrag) {
                    /* NULL here technically compiles but this ROM doesn't
                       null-check it, silently producing a zero-size drag
                       region (the same real bug already found and fixed
                       for the main window - see app.c) - same fix here. */
                    Rect dragBounds = qd.screenBits.bounds;
                    InsetRect(&dragBounds, 4, 4);
                    DragWindow(which, event.where, &dragBounds);
                } else if (part == inMenuBar) {
                    /* Let MenuSelect actually track the click, rather than
                       just un-highlighting - this is what lets the
                       built-in Application menu (rightmost, switch to a
                       different running app) work correctly, since that
                       switch happens *inside* MenuSelect's own tracking
                       loop, not as a command dispatched from its result
                       afterward. Garden's own menus (File/Edit/Go/
                       Connection) still don't do anything during a
                       transfer - the result is deliberately discarded -
                       only the Application menu's switch has any real
                       effect, and needs no result to be discarded since
                       it already happened by the time MenuSelect returns.
                       Without this, a download with no other app window
                       already visible on screen had no way to switch away
                       at all - the whole point of running it async. */
                    (void)MenuSelect(event.where);
                    HiliteMenu(0);
                }
                break;
            }
            case keyDown:
            case autoKey: {
                char key = (char)(event.message & charCodeMask);
                if (key == '.' && (event.modifiers & cmdKey)) gCancel = true;
                break;
            }
            case updateEvt: {
                WindowPtr w = (WindowPtr)event.message;
                if (w == gWindow) {
                    BeginUpdate(w);
                    DrawContent();
                    EndUpdate(w);
                }
                break;
            }
            case osEvt:
                /* A download can easily outlast the user switching away
                   and back - this dialog runs its own event loop instead
                   of the main one, so it has to track background state
                   itself rather than relying on RunApp's loop to notice. */
                App_HandleOSEvent(&event);
                break;
            case kHighLevelEvent:
                /* Without this, a Quit AppleEvent (Shut Down/Restart, or
                   the Finder's own Quit) arriving while a download is in
                   flight would be silently dropped right here, the same
                   gap RunApp's own loop had - this dialog pumps its own
                   events instead of the main loop's while a transfer is
                   active, so it has to dispatch AppleEvents itself too or
                   the app's Quit handler (app.c) never gets a chance to
                   run until the transfer finishes on its own. */
                AEProcessAppleEvent(&event);
                break;
        }
    }
}
