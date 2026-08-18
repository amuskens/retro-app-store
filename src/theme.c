#include <Fonts.h>

#include "theme.h"
#include "native.h"

const RGBColor kThemeChromeFill = { 0xCCCC, 0xD9D9, 0xEEEE };
const RGBColor kThemeChromeEdge = { 0x8888, 0x9999, 0xAAAA };
const RGBColor kThemeDivider    = { 0xCCCC, 0xCCCC, 0xCCCC };
const RGBColor kThemeSelectFill = { 0x9999, 0xCCCC, 0xFFFF };
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

void Theme_DrawProgressBar(const Rect *r, short permilleFilled, Boolean knownTotal)
{
    Rect inner = *r;

    FrameRect(r);
    InsetRect(&inner, 1, 1);

    SetRGB(&kThemeSelectFill);
    if (knownTotal) {
        short fillW = (short)(((long)(inner.right - inner.left) * permilleFilled) / 1000);
        Rect fillRect = inner;
        fillRect.right = (short)(fillRect.left + fillW);
        PaintRect(&fillRect);
    }
    ForeColor(blackColor);
}
