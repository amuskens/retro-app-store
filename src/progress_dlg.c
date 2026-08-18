#include <string.h>
#include <stdio.h>
#include <Quickdraw.h>
#include <Windows.h>
#include <Fonts.h>
#include <Events.h>
#include <Menus.h>

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
    permille = (gTotalKnown && gTotalBytes > 0)
                   ? (short)((gBytesSoFar * 1000UL) / gTotalBytes)
                   : 0;
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
                    DragWindow(which, event.where, NULL);
                } else if (part == inMenuBar) {
                    HiliteMenu(0); /* menus stay visible but inert during a transfer */
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
        }
    }
}
