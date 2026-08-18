#include "sidebar.h"
#include "theme.h"
#include "native.h"
#include "catalog.h"

#define kHeaderHeight 22
#define kRowHeight    24
#define kTotalRows    (kCategoryCount + 1) /* +1 for the trailing Live FTP Browse row */

static short gSelected = 0;

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

    if (index == gSelected) {
        Theme_FillSelectAccent(&row);
    } else {
        EraseRect(&row);
    }

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

    Theme_DrawDivider(bounds->right - 1, bounds->top, bounds->right - 1, bounds->bottom);
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
