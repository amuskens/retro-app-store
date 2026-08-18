#include <string.h>

#include "results_view.h"
#include "theme.h"
#include "native.h"
#include "catalog.h"

typedef enum { kModeCategory, kModeSearch, kModeLive } ResultsMode;

#define kPageSize 10
/* ~0.5s at 60 ticks/sec, same convention used for double-click detection
   elsewhere in this codebase (see mac-system7-c) - GetDblTime() isn't
   available for this target. */
#define kDoubleClickTicks 30

static ResultsMode gMode = kModeCategory;
static short gCategory = 0;

static short gIndices[kMaxFilterResults]; /* catalog.c indices, category/search modes */
static short gIndexCount = 0;
static char gLastQuery[256] = ""; /* so ResultsView_RefreshFilter can re-run a search */

static char gLiveNames[kResultsMaxLiveEntries][64];
static unsigned long gLiveSizes[kResultsMaxLiveEntries];
static Boolean gLiveSizeKnown[kResultsMaxLiveEntries];
static short gLiveCount = 0;

static short gPage = 0;
static short gSelectedRow = -1; /* 0..9 within the current page, -1 = none */
static unsigned long gLastClickWhen = 0;
static short gLastClickRow = -1;

static short ItemCount(void)
{
    return (gMode == kModeLive) ? gLiveCount : gIndexCount;
}

static void GetItem(short i, const char **title, const char **desc,
                     unsigned long *size, Boolean *sizeKnown, const char **remotePath)
{
    if (gMode == kModeLive) {
        *title = gLiveNames[i];
        *desc = "Live server entry - Get to download, or double-click if it's a folder.";
        *size = gLiveSizes[i];
        *sizeKnown = gLiveSizeKnown[i];
        *remotePath = gLiveNames[i];
    } else {
        const CatalogEntry *e = &gCatalogEntries[gIndices[i]];
        *title = e->title;
        *desc = e->description;
        *size = e->sizeBytes;
        *sizeKnown = true;
        *remotePath = e->remotePath;
    }
}

static void RowRect(const Rect *bounds, short row, Rect *out)
{
    out->left = bounds->left;
    out->right = bounds->right;
    out->top = (short)(bounds->top + row * kResultRowHeight);
    out->bottom = (short)(out->top + kResultRowHeight);
}

static void GetButtonRect(const Rect *row, Rect *out)
{
    out->right = (short)(row->right - 8);
    out->left = (short)(out->right - 44);
    out->top = (short)(row->top + (kResultRowHeight - 18) / 2);
    out->bottom = (short)(out->top + 18);
}

static void SizeTextRect(const Rect *getBtn, const Rect *row, Rect *out)
{
    out->right = (short)(getBtn->left - 6);
    out->left = (short)(out->right - 56);
    out->top = (short)(row->top + 4);
    out->bottom = (short)(row->top + 16);
}

/* Simple generic-document glyph: a frame with a folded top-right corner -
   cheap to draw with a handful of QuickDraw lines, no icon resources
   needed for a per-row marker. */
static void DrawFileGlyph(const Rect *area)
{
    short fold = 6;
    FrameRect(area);
    MoveTo((short)(area->right - fold), area->top);
    LineTo((short)(area->right - fold), (short)(area->top + fold));
    LineTo(area->right, (short)(area->top + fold));
}

/* Descriptions may carry an optional second line (a hardware requirement
   note, e.g. "Requires a 68030 or better") after a '\r' - classic Mac's
   own line-break convention, same as every STR#/DITL string in this app.
   Splitting here rather than storing it as a separate CatalogEntry field
   keeps the on-disk catalog format untouched: it's still just one
   description string, TruncateCStringToWidth-safe once split, with
   *outLine2 left empty (not touched further by the caller) when there's
   no second line. */
static void SplitDescription(const char *desc, char *line1, short line1Size,
                              char *line2, short line2Size)
{
    const char *br = strchr(desc, '\r');
    if (br == NULL) {
        strncpy(line1, desc, line1Size - 1);
        line1[line1Size - 1] = 0;
        line2[0] = 0;
        return;
    }
    {
        short n = (short)(br - desc);
        if (n > line1Size - 1) n = (short)(line1Size - 1);
        BlockMove((Ptr)desc, line1, n);
        line1[n] = 0;
    }
    strncpy(line2, br + 1, line2Size - 1);
    line2[line2Size - 1] = 0;
}

static void DrawItemRow(const Rect *bounds, short rowSlot, short absIndex, Boolean selected)
{
    Rect row, iconR, getBtn, sizeR, titleR, descR, descR2;
    const char *title, *desc, *remotePath;
    unsigned long size;
    Boolean sizeKnown;
    char sizeStr[24];
    char descLine1[220], descLine2[220];

    RowRect(bounds, rowSlot, &row);
    GetItem(absIndex, &title, &desc, &size, &sizeKnown, &remotePath);

    EraseRect(&row);

    iconR.left = (short)(row.left + 8);
    iconR.top = (short)(row.top + 9);
    iconR.right = (short)(iconR.left + 20);
    iconR.bottom = (short)(iconR.top + 20);
    DrawFileGlyph(&iconR);

    GetButtonRect(&row, &getBtn);
    SizeTextRect(&getBtn, &row, &sizeR);

    if (sizeKnown) Catalog_FormatSize(size, sizeStr, sizeof(sizeStr));
    else strcpy(sizeStr, "unknown");

    titleR = row;
    titleR.left = (short)(row.left + 38);
    titleR.right = sizeR.left;
    titleR.top = (short)(row.top + 3);
    titleR.bottom = (short)(row.top + 17);
    Theme_SetGeneva(10, bold);
    {
        char buf[160];
        TruncateCStringToWidth(title, buf, sizeof(buf), (short)(titleR.right - titleR.left));
        DrawCStringInRect(buf, &titleR);
    }

    SplitDescription(desc, descLine1, sizeof(descLine1), descLine2, sizeof(descLine2));

    descR = row;
    descR.left = (short)(row.left + 38);
    descR.right = sizeR.left;
    descR.top = (short)(row.top + 19);
    descR.bottom = (short)(row.top + 31);
    Theme_SetGeneva(9, normal);
    Theme_SetDescColor();
    {
        char buf[220];
        TruncateCStringToWidth(descLine1, buf, sizeof(buf), (short)(descR.right - descR.left));
        DrawCStringInRect(buf, &descR);
    }
    Theme_SetBlack();

    if (descLine2[0] != 0) {
        descR2 = row;
        descR2.left = (short)(row.left + 38);
        descR2.right = sizeR.left;
        descR2.top = (short)(row.top + 31);
        descR2.bottom = (short)(row.top + 43);
        Theme_SetGeneva(9, italic);
        Theme_SetDescColor();
        {
            char buf[220];
            TruncateCStringToWidth(descLine2, buf, sizeof(buf), (short)(descR2.right - descR2.left));
            DrawCStringInRect(buf, &descR2);
        }
        Theme_SetBlack();
    }

    Theme_SetGeneva(9, normal);
    Theme_SetDescColor();
    DrawCStringInRect(sizeStr, &sizeR);
    Theme_SetBlack();

    Theme_DrawPillButton(&getBtn, "Get", false);

    Theme_DrawDivider(row.left, row.bottom - 1, row.right, row.bottom - 1);

    if (selected) Theme_HighlightRow(&row);

    (void)remotePath;
}

void ResultsView_ShowCategory(short categoryIndex)
{
    gMode = kModeCategory;
    gCategory = categoryIndex;
    gIndexCount = Catalog_FilterByCategory(categoryIndex, gIndices, kMaxFilterResults);
    gPage = 0;
    gSelectedRow = -1;
}

void ResultsView_ShowSearch(const char *query)
{
    gMode = kModeSearch;
    strncpy(gLastQuery, query, sizeof(gLastQuery) - 1);
    gLastQuery[sizeof(gLastQuery) - 1] = 0;
    gIndexCount = Catalog_Search(query, gIndices, kMaxFilterResults);
    gPage = 0;
    gSelectedRow = -1;
}

/* Re-runs whichever of category/search is currently active against the
   catalog, picking up any change to the Year/CPU filters (catalog.c
   applies those internally to every Catalog_FilterByCategory/Catalog_Search
   call) without changing what category or search is selected. A no-op in
   live mode - live entries have no year/arch metadata for those filters
   to apply to. */
void ResultsView_RefreshFilter(void)
{
    if (gMode == kModeCategory) {
        gIndexCount = Catalog_FilterByCategory(gCategory, gIndices, kMaxFilterResults);
    } else if (gMode == kModeSearch) {
        gIndexCount = Catalog_Search(gLastQuery, gIndices, kMaxFilterResults);
    } else {
        return;
    }
    gPage = 0;
    gSelectedRow = -1;
}

void ResultsView_ShowLiveListing(char names[][64], const unsigned long sizes[],
                                  const Boolean sizeKnown[], short count)
{
    short i;
    if (count > kResultsMaxLiveEntries) count = kResultsMaxLiveEntries;
    for (i = 0; i < count; i++) {
        BlockMove(names[i], gLiveNames[i], 64);
        gLiveSizes[i] = sizes[i];
        gLiveSizeKnown[i] = sizeKnown[i];
    }
    gLiveCount = count;
    gMode = kModeLive;
    gPage = 0;
    gSelectedRow = -1;
}

Boolean ResultsView_IsLiveMode(void)
{
    return (Boolean)(gMode == kModeLive);
}

void ResultsView_EnterLiveMode(void)
{
    gMode = kModeLive;
    gPage = 0;
    gSelectedRow = -1;
}

void ResultsView_Draw(const Rect *bounds)
{
    short count = ItemCount();
    short start = (short)(gPage * kPageSize);
    short slot;

    EraseRect(bounds);

    if (count == 0) {
        Rect msgR = *bounds;
        InsetRect(&msgR, 14, 14);
        Theme_SetGeneva(10, italic);
        Theme_SetDescColor();
        DrawCStringInRect(
            gMode == kModeLive
                ? "Not connected yet. Use the Connection menu to fetch a live listing."
                : "No items match your search.",
            &msgR);
        Theme_SetBlack();
        return;
    }

    for (slot = 0; slot < kPageSize; slot++) {
        short idx = (short)(start + slot);
        if (idx >= count) break;
        DrawItemRow(bounds, slot, idx, (Boolean)(slot == gSelectedRow));
    }
}

Boolean ResultsView_Click(const Rect *bounds, Point pt, unsigned long when,
                           DownloadRequest *outReq, ResultsActivation *outActivation)
{
    short count = ItemCount();
    short start = (short)(gPage * kPageSize);
    short slot;
    Rect row, getBtn;

    if (pt.h < bounds->left || pt.h >= bounds->right) return false;
    if (pt.v < bounds->top || pt.v >= bounds->bottom) return false;

    slot = (short)((pt.v - bounds->top) / kResultRowHeight);
    if (slot < 0 || slot >= kPageSize) return false;

    {
        short absIdx = (short)(start + slot);
        if (absIdx >= count) return false;

        RowRect(bounds, slot, &row);
        GetButtonRect(&row, &getBtn);

        if (PtInRect(pt, &getBtn)) {
            const char *title, *desc, *remotePath;
            unsigned long size;
            Boolean sizeKnown;
            GetItem(absIdx, &title, &desc, &size, &sizeKnown, &remotePath);
            strncpy(outReq->title, title, sizeof(outReq->title) - 1);
            outReq->title[sizeof(outReq->title) - 1] = 0;
            strncpy(outReq->remotePath, remotePath, sizeof(outReq->remotePath) - 1);
            outReq->remotePath[sizeof(outReq->remotePath) - 1] = 0;
            outReq->isLiveFile = (Boolean)(gMode == kModeLive);
            *outActivation = kResultsActivationGet;
            return true;
        }

        if (slot == gLastClickRow && (when - gLastClickWhen) <= kDoubleClickTicks) {
            const char *title, *desc, *remotePath;
            unsigned long size;
            Boolean sizeKnown;
            GetItem(absIdx, &title, &desc, &size, &sizeKnown, &remotePath);
            strncpy(outReq->title, title, sizeof(outReq->title) - 1);
            outReq->title[sizeof(outReq->title) - 1] = 0;
            strncpy(outReq->remotePath, remotePath, sizeof(outReq->remotePath) - 1);
            outReq->remotePath[sizeof(outReq->remotePath) - 1] = 0;
            outReq->isLiveFile = (Boolean)(gMode == kModeLive);
            *outActivation = kResultsActivationDoubleClick;
            gLastClickRow = -1;
            return true;
        }

        if (slot != gSelectedRow) {
            short old = gSelectedRow;
            gSelectedRow = slot;
            if (old >= 0 && old < kPageSize) {
                short oldAbs = (short)(start + old);
                if (oldAbs < count) DrawItemRow(bounds, old, oldAbs, false);
            }
            DrawItemRow(bounds, slot, absIdx, true);
        }
        gLastClickRow = slot;
        gLastClickWhen = when;
    }

    return false;
}

Boolean ResultsView_GetSelected(DownloadRequest *outReq)
{
    short start = (short)(gPage * kPageSize);
    short absIdx;
    const char *title, *desc, *remotePath;
    unsigned long size;
    Boolean sizeKnown;

    if (gSelectedRow < 0) return false;
    absIdx = (short)(start + gSelectedRow);
    if (absIdx >= ItemCount()) return false;

    GetItem(absIdx, &title, &desc, &size, &sizeKnown, &remotePath);
    strncpy(outReq->title, title, sizeof(outReq->title) - 1);
    outReq->title[sizeof(outReq->title) - 1] = 0;
    strncpy(outReq->remotePath, remotePath, sizeof(outReq->remotePath) - 1);
    outReq->remotePath[sizeof(outReq->remotePath) - 1] = 0;
    outReq->isLiveFile = (Boolean)(gMode == kModeLive);
    return true;
}

short ResultsView_PageCount(void)
{
    short count = ItemCount();
    short pages = (short)((count + kPageSize - 1) / kPageSize);
    return (pages < 1) ? 1 : pages;
}

short ResultsView_CurrentPage(void)
{
    return gPage;
}

void ResultsView_NextPage(const Rect *bounds)
{
    if (gPage + 1 < ResultsView_PageCount()) {
        gPage++;
        gSelectedRow = -1;
        ResultsView_Draw(bounds);
    }
}

void ResultsView_PrevPage(const Rect *bounds)
{
    if (gPage > 0) {
        gPage--;
        gSelectedRow = -1;
        ResultsView_Draw(bounds);
    }
}
