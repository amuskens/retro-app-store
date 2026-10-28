#include <string.h>
#include <stdio.h>
#include <Fonts.h>
#include <TextEdit.h>

#include "toolbar.h"
#include "theme.h"
#include "native.h"

static WindowPtr gWindow;
static TEHandle gSearchTE;
static ControlHandle gSearchBtn, gPrevBtn, gNextBtn;
static Rect gFieldFrame;

void Toolbar_Init(WindowPtr w)
{
    Rect r;
    Str255 t;

    gWindow = w;
    SetPort(w);
    SetRect(&r, 0, 0, 60, 20);

    CToPascal("Search", t);
    gSearchBtn = NewControl(w, &r, t, true, 0, 0, 0, pushButProc, 0);
    CToPascal("<", t);
    gPrevBtn = NewControl(w, &r, t, true, 0, 0, 0, pushButProc, 0);
    CToPascal(">", t);
    gNextBtn = NewControl(w, &r, t, true, 0, 0, 0, pushButProc, 0);

    SetRect(&gFieldFrame, 0, 0, 10, 10);
    gSearchTE = TENew(&gFieldFrame, &gFieldFrame);
}

void Toolbar_Layout(const Rect *toolbarBounds, const Rect *statusBounds)
{
    short btnW = 56, btnH = 20;
    Rect r, viewR;

    r.top = (short)(toolbarBounds->top + (kToolbarHeight - btnH) / 2);
    r.bottom = (short)(r.top + btnH);
    r.right = (short)(toolbarBounds->right - 8);
    r.left = (short)(r.right - btnW);
    MoveControl(gSearchBtn, r.left, r.top);
    SizeControl(gSearchBtn, (short)(r.right - r.left), (short)(r.bottom - r.top));

    gFieldFrame.right = (short)(r.left - 8);
    gFieldFrame.left = (short)(gFieldFrame.right - 170);
    gFieldFrame.top = (short)(toolbarBounds->top + (kToolbarHeight - 18) / 2);
    gFieldFrame.bottom = (short)(gFieldFrame.top + 18);

    viewR = gFieldFrame;
    InsetRect(&viewR, 4, 3);
    (**gSearchTE).viewRect = viewR;
    (**gSearchTE).destRect = viewR;
    TECalText(gSearchTE);

    {
        short pbW = 20, pbH = 16;
        short y = (short)(statusBounds->top + (kStatusBarHeight - pbH) / 2);
        Rect nr, pr;

        nr.top = y; nr.bottom = (short)(y + pbH);
        nr.right = (short)(statusBounds->right - 8 - 16); /* 16: the grow box's corner, see DrawGrowCorner in app.c */
        nr.left = (short)(nr.right - pbW);
        MoveControl(gNextBtn, nr.left, nr.top);
        SizeControl(gNextBtn, pbW, pbH);

        pr.top = y; pr.bottom = (short)(y + pbH);
        pr.right = (short)(nr.left - 96);
        pr.left = (short)(pr.right - pbW);
        MoveControl(gPrevBtn, pr.left, pr.top);
        SizeControl(gPrevBtn, pbW, pbH);
    }
}

void Toolbar_DrawTop(const Rect *bounds)
{
    Rect titleR = *bounds;

    Theme_FillChromeBand(bounds);
    Theme_DrawDivider(bounds->left, (short)(bounds->bottom - 1), bounds->right, (short)(bounds->bottom - 1));

    titleR.left = (short)(titleR.left + 12);
    titleR.right = (short)(gFieldFrame.left - 12);
    Theme_SetChicago(12);
    DrawCStringInRect("Macintosh Garden", &titleR);

    EraseRect(&gFieldFrame);
    FrameRect(&gFieldFrame);
    TEUpdate(&gFieldFrame, gSearchTE);
}

void Toolbar_DrawStatus(const Rect *bounds, Boolean connected, const char *statusText,
                         short page, short pageCount)
{
    Rect ledR, textR, pageR, prevR, nextR;
    char pageStr[32];

    Theme_FillChromeBand(bounds);
    Theme_DrawDivider(bounds->left, bounds->top, bounds->right, bounds->top);

    ledR.left = (short)(bounds->left + 10);
    ledR.top = (short)(bounds->top + (kStatusBarHeight - 9) / 2);
    ledR.right = (short)(ledR.left + 9);
    ledR.bottom = (short)(ledR.top + 9);
    Theme_DrawStatusLED(&ledR, connected);

    textR = *bounds;
    textR.left = (short)(ledR.right + 6);
    textR.right = (short)(bounds->left + 260);
    if (textR.right > (**gPrevBtn).contrlRect.left - 8) textR.right = (short)((**gPrevBtn).contrlRect.left - 8);
    Theme_SetGeneva(9, normal);
    {
        char fitted[200];
        TruncateCStringToWidth(statusText, fitted, sizeof(fitted), (short)(textR.right - textR.left));
        DrawCStringInRect(fitted, &textR);
    }

    prevR = (**gPrevBtn).contrlRect;
    nextR = (**gNextBtn).contrlRect;
    pageR = *bounds;
    pageR.left = (short)(prevR.right + 6);
    pageR.right = (short)(nextR.left - 6);

    sprintf(pageStr, "Page %d of %d", page + 1, pageCount);
    Theme_SetGeneva(9, normal);
    {
        FontInfo info;
        short w = CStringWidth(pageStr);
        short baseline;
        GetFontInfo(&info);
        baseline = (short)(pageR.top + ((pageR.bottom - pageR.top) - (info.ascent + info.descent)) / 2 + info.ascent);
        MoveTo((short)(pageR.left + ((pageR.right - pageR.left) - w) / 2), baseline);
        DrawCString(pageStr);
    }
}

ToolbarHit Toolbar_Click(Point pt)
{
    ControlHandle ctl;
    short part;

    if (PtInRect(pt, &gFieldFrame)) {
        TEClick(pt, false, gSearchTE);
        return kToolbarHitSearchField;
    }

    part = FindControl(pt, gWindow, &ctl);
    if (part != 0 && ctl != NULL) {
        part = TrackControl(ctl, pt, NULL);
        if (part != 0) {
            if (ctl == gSearchBtn) return kToolbarHitSearchSubmit;
            if (ctl == gPrevBtn) return kToolbarHitPrevPage;
            if (ctl == gNextBtn) return kToolbarHitNextPage;
        }
    }
    return kToolbarHitNone;
}

/* Return/Enter mean "submit this search", so they must NOT also be fed to
   TEKey - real bug, and the explanation for the intermittent "search finds
   nothing" ghost that got written off as non-reproducible twice in earlier
   test rounds. This used to call TEKey unconditionally and only then check
   for the terminator, so pressing Return inserted a literal carriage
   return into the field's text before the search ran: every
   Return-submitted query was actually "<what you typed>\r", which
   correctly matched nothing, while the identical text submitted by
   clicking the Search button matched fine. That's exactly why it looked
   random and why "clicking something else fixed it" - the two submit paths
   genuinely behaved differently, and the CR then stayed in the field to
   poison later searches too (press Return twice, get "\r\r").

   Confirmed by direct A/B on one build: same text, button -> 4 pages of
   matches, Return -> "No items match your search". */
Boolean Toolbar_HandleKey(EventRecord *evt)
{
    char key = (char)(evt->message & charCodeMask);
    if (key == 0x0D || key == 0x03) return true; /* submit - deliberately not inserted */
    TEKey(key, gSearchTE);
    return false;
}

void Toolbar_Idle(void)
{
    TEIdle(gSearchTE);
}

/* Length comes from the TE record's own teLength, not from
   GetHandleSize(TEGetText(...)) as it used to. Those are not the same
   number: TextEdit's text handle is a capacity, grown in chunks and not
   necessarily shrunk back as characters are deleted, so GetHandleSize is
   >= the real text length and only incidentally equal to it. When it's
   larger, the slack bytes get copied in after the real text and the NUL
   lands past them, handing Catalog_Search a query with trailing garbage.

   Latent rather than the cause of any observed failure - the intermittent
   "search finds nothing" bug that prompted this audit turned out to be the
   Return-key CR insertion in Toolbar_HandleKey above, not this - but
   teLength is the authoritative count every TE call maintains, so use it. */
void Toolbar_GetSearchText(char *buf, short bufSize)
{
    CharsHandle h = TEGetText(gSearchTE);
    long len = (long)(**gSearchTE).teLength;
    if (len < 0) len = 0;
    if (len >= bufSize) len = (long)(bufSize - 1);
    HLock((Handle)h);
    BlockMove(*h, buf, len);
    HUnlock((Handle)h);
    buf[len] = 0;
}

void Toolbar_ClearSearch(void)
{
    TESetSelect(0, 32767, gSearchTE);
    TEDelete(gSearchTE);
    EraseRect(&gFieldFrame);
    FrameRect(&gFieldFrame);
    TEUpdate(&gFieldFrame, gSearchTE);
}

/* TECut/TECopy/TEPaste alone (no TEToScrap/TEFromScrap/ZeroScrap): per
   mac-system7-c's README, TEToScrap/TEFromScrap are declared in this
   toolchain but not actually implemented for the 68k target (Carbon-only
   in the headers), so Cut/Copy/Paste work within the app via TE's own
   internal clipboard but won't sync with the host/emulator clipboard. */
void Toolbar_EditCut(void)
{
    TECut(gSearchTE);
}

void Toolbar_EditCopy(void)
{
    TECopy(gSearchTE);
}

void Toolbar_EditPaste(void)
{
    TEPaste(gSearchTE);
}

void Toolbar_EditClear(void)
{
    TEDelete(gSearchTE);
}
