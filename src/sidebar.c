#include "sidebar.h"
#include "theme.h"
#include "native.h"
#include "catalog.h"

#define kHeaderHeight 22
#define kRowHeight    24
#define kTotalRows    (kCategoryCount + 1) /* +1 for the trailing Live FTP Browse row */

/* Year/CPU/System filter pills, pinned to the bottom of the sidebar rather
   than flowing after the row list - a fixed footer, same idea as the
   toolbar/status bar being pinned to the window's top/bottom edges, so
   they stay in the same reachable spot regardless of how many categories
   there are or how tall the window is. Originally these lived in a second
   toolbar row instead; moved here since two pill buttons crammed alongside
   the search field read as cluttered, and they're conceptually "narrow the
   list I'm already looking at", closer in spirit to category selection
   than to search. */
#define kFilterFooterHeight 86
#define kFilterPillHeight   18

static short gSelected = 0;

static void FilterRects(const Rect *bounds, Rect *outYear, Rect *outArch, Rect *outSys)
{
    short footerTop = (short)(bounds->bottom - kFilterFooterHeight);

    outYear->left = (short)(bounds->left + 10);
    outYear->right = (short)(bounds->right - 10);
    outYear->top = (short)(footerTop + 10);
    outYear->bottom = (short)(outYear->top + kFilterPillHeight);

    outArch->left = outYear->left;
    outArch->right = outYear->right;
    outArch->top = (short)(outYear->bottom + 8);
    outArch->bottom = (short)(outArch->top + kFilterPillHeight);

    outSys->left = outYear->left;
    outSys->right = outYear->right;
    outSys->top = (short)(outArch->bottom + 8);
    outSys->bottom = (short)(outSys->top + kFilterPillHeight);
}

static void RowRect(const Rect *bounds, short index, Rect *out)
{
    out->left = bounds->left;
    out->right = bounds->right;
    out->top = (short)(bounds->top + kHeaderHeight + index * kRowHeight);
    out->bottom = (short)(out->top + kRowHeight);
}

/* A small generic marker to the left of each row - a filled dot for
   ordinary categories, an open diamond for the live/dynamic one, so Live
   FTP Browse reads as visually different from the static catalog list
   without needing a whole second icon set for a single row. */
static void DrawRowGlyph(const Rect *row, Boolean isLive)
{
    Rect g;
    short cy = (short)((row->top + row->bottom) / 2);
    g.left = (short)(row->left + 12);
    g.right = (short)(g.left + 7);
    g.top = (short)(cy - 3);
    g.bottom = (short)(cy + 4);

    if (isLive) {
        FrameOval(&g);
    } else {
        PaintOval(&g);
    }
}

static void DrawRow(const Rect *bounds, short index)
{
    Rect row;
    Boolean isLive = (Boolean)(index == kLiveBrowseRowIndex);
    const char *title = isLive ? "Live FTP Browse" : gCategories[index].title;

    RowRect(bounds, index, &row);
    EraseRect(&row);

    if (isLive) {
        Theme_DrawDivider(row.left, row.top, row.right, row.top);
    }

    DrawRowGlyph(&row, isLive);

    {
        Rect textR = row;
        textR.left = (short)(row.left + 26);
        textR.right = (short)(row.right - 4);
        Theme_SetGeneva(10, isLive ? italic : normal);
        DrawCStringInRect(title, &textR);
    }

    /* Invert, not a color fill: a light accent tint (originally used here)
       turned out to be indistinguishable from the plain white background
       when actually tested on a display running in black & white - the
       exact reason results_view.c's row selection already used invert
       instead of Theme_FillSelectAccent, a distinction this row drawing
       hadn't followed through on. Invert is guaranteed visible at any
       color depth, so it goes last, over everything already drawn. */
    if (index == gSelected) Theme_HighlightRow(&row);
}

void Sidebar_Draw(const Rect *bounds)
{
    Rect header;
    short i;

    Theme_FillChromeBand(bounds);

    header = *bounds;
    header.bottom = (short)(header.top + kHeaderHeight);
    Theme_SetChicago(10);
    {
        Rect textR = header;
        textR.left = (short)(header.left + 10);
        DrawCStringInRect("Macintosh Garden", &textR);
    }
    Theme_DrawDivider(bounds->left, header.bottom, bounds->right, header.bottom);

    for (i = 0; i < kTotalRows; i++)
        DrawRow(bounds, i);

    {
        Rect yearR, archR, sysR;
        short footerTop = (short)(bounds->bottom - kFilterFooterHeight);
        FilterRects(bounds, &yearR, &archR, &sysR);

        Theme_DrawDivider(bounds->left, footerTop, bounds->right, footerTop);
        Theme_DrawPillButton(&yearR, Catalog_YearFilterLabel(Catalog_GetYearFilter()), false);
        Theme_DrawPillButton(&archR, Catalog_ArchFilterLabel(Catalog_GetArchFilter()), false);
        Theme_DrawPillButton(&sysR, Catalog_SysFilterLabel(Catalog_GetSysFilter()), false);
    }

    Theme_DrawDivider(bounds->right - 1, bounds->top, bounds->right - 1, bounds->bottom);
}

Boolean Sidebar_ClickFilter(const Rect *bounds, Point pt, SidebarFilterKind *outKind)
{
    Rect yearR, archR, sysR;
    FilterRects(bounds, &yearR, &archR, &sysR);

    if (PtInRect(pt, &yearR)) { *outKind = kSidebarFilterYear; return true; }
    if (PtInRect(pt, &archR)) { *outKind = kSidebarFilterArch; return true; }
    if (PtInRect(pt, &sysR))  { *outKind = kSidebarFilterSystem; return true; }
    return false;
}

void Sidebar_GetYearFilterRect(const Rect *bounds, Rect *out)
{
    Rect archR, sysR;
    FilterRects(bounds, out, &archR, &sysR);
}

void Sidebar_GetArchFilterRect(const Rect *bounds, Rect *out)
{
    Rect yearR, sysR;
    FilterRects(bounds, &yearR, out, &sysR);
}

void Sidebar_GetSystemFilterRect(const Rect *bounds, Rect *out)
{
    Rect yearR, archR;
    FilterRects(bounds, &yearR, &archR, out);
}

short Sidebar_Click(const Rect *bounds, Point pt)
{
    short i;

    if (pt.h < bounds->left || pt.h >= bounds->right) return -1;

    for (i = 0; i < kTotalRows; i++) {
        Rect row;
        RowRect(bounds, i, &row);
        if (pt.v >= row.top && pt.v < row.bottom) {
            if (i != gSelected) {
                short old = gSelected;
                gSelected = i;
                DrawRow(bounds, old);
                DrawRow(bounds, i);
            }
            return i;
        }
    }
    return -1;
}

short Sidebar_GetSelected(void)
{
    return gSelected;
}

void Sidebar_SetSelected(const Rect *bounds, short index)
{
    short old = gSelected;
    if (index == old) return;
    gSelected = index;
    DrawRow(bounds, old);
    DrawRow(bounds, index);
}
