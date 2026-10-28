#ifndef THEME_H
#define THEME_H

#include <Quickdraw.h>

/* Shared look-and-feel for the "1995 online service" chrome: a muted
   blue-gray toolbar/sidebar band, Chicago for titles, Geneva for list body
   text, and a handful of small drawing helpers reused by every UI module
   so the app reads as one consistent piece of chrome rather than a
   collection of separately-styled panels. */

extern const RGBColor kThemeChromeFill;   /* toolbar/sidebar band background */
extern const RGBColor kThemeChromeEdge;   /* border under/right of chrome bands */
extern const RGBColor kThemeDivider;      /* thin row/section divider lines */
extern const RGBColor kThemeLedOn;        /* status LED - connected */
extern const RGBColor kThemeLedOff;       /* status LED - not connected */
extern const RGBColor kThemeDescGray;     /* secondary/description text */

#define kToolbarHeight    36
#define kSidebarWidth     132
#define kStatusBarHeight  20
/* 52, not 40 - grown to fit an optional second description line (hardware
   requirement note, e.g. "Requires a 68030 or better") below the regular
   one-line description. See results_view.c's DrawItemRow. */
#define kResultRowHeight  52

void Theme_SetChicago(short size);
void Theme_SetGeneva(short size, Style face);

/* Sets the port's foreground color to the secondary/description gray, or
   back to black - the general-purpose complement to the fill/divider
   helpers below, for modules that just need to draw gray text inline. */
void Theme_SetDescColor(void);
void Theme_SetBlack(void);

/* Fills r with the chrome band color - used for the toolbar, sidebar, and
   status bar backgrounds. */
void Theme_FillChromeBand(const Rect *r);

/* Draws a single hairline divider (theme color, not black) - used between
   list rows and under/beside chrome bands. Horizontal if y1==y2, vertical
   if x1==x2. */
void Theme_DrawDivider(short x1, short y1, short x2, short y2);

/* Selection highlight for a row - standard invert, guaranteed legible on
   any display depth (color and B&W alike) rather than a color-only tint.
   Used for both the sidebar and the results list, for this reason. */
void Theme_HighlightRow(const Rect *r);

/* Small filled oval status indicator (connected = green, not = gray). */
void Theme_DrawStatusLED(const Rect *r, Boolean connected);

/* A small pill-shaped button drawn directly into the current port (not a
   real Control) - used for the per-row "Get" button, where creating/
   disposing a real Control for every visible row on every page turn would
   be more churn than the row-click hit-test already handles for free. */
void Theme_DrawPillButton(const Rect *r, const char *label, Boolean pressed);

/* Simple horizontal progress bar, 0..1000 permille filled (permille rather
   than a float - this toolchain's target has no FPU and classic Mac C
   float support is best avoided in a UI redraw path). knownTotal false
   draws an indeterminate barber-pole-free placeholder (just the frame).
   The fill uses the same hilite-PenMode technique as Theme_HighlightRow,
   guaranteed legible on any display depth - a plain RGB fill (the
   original approach here) rounds to white on a 1-bit/grayscale display,
   which made the bar look permanently empty on real hardware. */
void Theme_DrawProgressBar(const Rect *r, short permilleFilled, Boolean knownTotal);

/* Call whenever the bar's area has been erased or a new transfer starts. */
void Theme_ResetProgressBar(void);

#endif
