#include <Events.h>
#include <Fonts.h>

#include "theme.h"
#include "native.h"

const RGBColor kThemeChromeFill = { 0xCCCC, 0xD9D9, 0xEEEE };
const RGBColor kThemeChromeEdge = { 0x8888, 0x9999, 0xAAAA };
const RGBColor kThemeDivider    = { 0xCCCC, 0xCCCC, 0xCCCC };
const RGBColor kThemeLedOn      = { 0x2222, 0xBBBB, 0x2222 };
const RGBColor kThemeLedOff     = { 0x9999, 0x9999, 0x9999 };
const RGBColor kThemeDescGray   = { 0x5555, 0x5555, 0x5555 };

/* This toolchain's Toolbox headers predate `const` in C, so RGBForeColor
   takes a plain RGBColor* - this cast (and the ones on ClipRect/etc. below)
   just bridges that, once, rather than at every call site. */
static void SetRGB(const RGBColor *c)
{
    RGBForeColor((RGBColor *)c);
}

void Theme_SetChicago(short size)
{
    TextFont(systemFont); /* Chicago, in every System 7-era system font set */
    TextFace(normal);
    TextSize(size);
}

void Theme_SetGeneva(short size, Style face)
{
    TextFont(applFont); /* Geneva */
    TextFace(face);
    TextSize(size);
}

void Theme_SetDescColor(void)
{
    SetRGB(&kThemeDescGray);
}

void Theme_SetBlack(void)
{
    ForeColor(blackColor);
}

void Theme_FillChromeBand(const Rect *r)
{
    SetRGB(&kThemeChromeFill);
    PaintRect(r);
    ForeColor(blackColor);
}

void Theme_DrawDivider(short x1, short y1, short x2, short y2)
{
    SetRGB(&kThemeDivider);
    MoveTo(x1, y1);
    LineTo(x2, y2);
    ForeColor(blackColor);
}

void Theme_HighlightRow(const Rect *r)
{
    PenState saved;
    GetPenState(&saved);
    PenMode(hilite); /* Color QuickDraw's own selection-highlight transfer
                         mode - blends using the user's Color control panel
                         choice (LMGetHiliteRGB) on a color display, and
                         degrades to plain invert automatically on a 1-bit
                         one, same as every stock-highlighted Mac list. */
    PaintRect(r);
    SetPenState(&saved);
}

void Theme_DrawStatusLED(const Rect *r, Boolean connected)
{
    SetRGB(connected ? &kThemeLedOn : &kThemeLedOff);
    PaintOval(r);
    ForeColor(blackColor);
    FrameOval(r);
}

void Theme_DrawPillButton(const Rect *r, const char *label, Boolean pressed)
{
    short arc = (short)(r->bottom - r->top);
    FontInfo info;
    short w, cx, baseline;

    SetRGB(pressed ? &kThemeChromeEdge : &kThemeChromeFill);
    PaintRoundRect(r, arc, arc);
    ForeColor(blackColor);
    FrameRoundRect(r, arc, arc);

    Theme_SetGeneva(9, bold);
    GetFontInfo(&info);
    w = CStringWidth(label);
    cx = (short)(r->left + ((r->right - r->left) - w) / 2);
    baseline = (short)(r->top + ((r->bottom - r->top) - (info.ascent + info.descent)) / 2 + info.ascent);
    MoveTo(cx, baseline);
    DrawCString(label);
}

/* Width in pixels already painted inside the current bar. The fill uses
   hilite PenMode, which XORs against what is underneath - repainting the
   whole fill on every update (what this used to do) therefore flipped the
   already-filled part back and forth, producing the broken striped bar.
   Now only the newly covered slice is painted; the bar is erased and
   restarted when it shrinks or Theme_ResetProgressBar is called (new
   transfer, or the window was erased by an update). */
static short gBarPaintedW = -1;

void Theme_ResetProgressBar(void)
{
    gBarPaintedW = -1;
}

static void PaintHilite(const Rect *r)
{
    PenState saved;
    GetPenState(&saved);
    PenMode(hilite);
    PaintRect(r);
    SetPenState(&saved);
}

void Theme_DrawProgressBar(const Rect *r, short permilleFilled, Boolean knownTotal)
{
    Rect inner = *r;
    short innerW;

    FrameRect(r);
    InsetRect(&inner, 1, 1);
    innerW = (short)(inner.right - inner.left);

    if (knownTotal) {
        short fillW = (short)(((long)innerW * permilleFilled) / 1000);
        Rect slice = inner;

        if (gBarPaintedW < 0 || fillW < gBarPaintedW) {
            EraseRect(&inner);
            gBarPaintedW = 0;
        }
        if (fillW > gBarPaintedW) {
            slice.left = (short)(inner.left + gBarPaintedW);
            slice.right = (short)(inner.left + fillW);
            PaintHilite(&slice);
            gBarPaintedW = fillW;
        }
    } else {
        /* Unknown total: a block sweeping back and forth, rather than a
           bar that can never fill. */
        short blockW = 36, travel = (short)(innerW - blockW);
        short pos = (short)((TickCount() / 2) % (2L * travel));
        Rect block = inner;
        if (pos > travel) pos = (short)(2 * travel - pos);
        EraseRect(&inner);
        block.left = (short)(inner.left + pos);
        block.right = (short)(block.left + blockW);
        PaintHilite(&block);
        gBarPaintedW = -1;
    }
    ForeColor(blackColor);
}
