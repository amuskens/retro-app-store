#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <Quickdraw.h>

/* The left-hand category list. Custom-drawn (see theme.h) rather than List
   Manager, so row layout/highlight match the rest of the app's chrome. */

void Sidebar_Draw(const Rect *bounds);

/* pt is in window-local coordinates. Returns the newly-selected row index
   (0..kCategoryCount-1 for a real category, kLiveBrowseRowIndex for Live
   FTP Browse), or -1 if the click didn't land on a row (selection
   unchanged). Redraws the affected rows itself. */
short Sidebar_Click(const Rect *bounds, Point pt);

short Sidebar_GetSelected(void);

/* Used by the Go menu to jump categories without a click; redraws. */
void Sidebar_SetSelected(const Rect *bounds, short index);

/* The Year/CPU/System filter pills pinned to the bottom of the sidebar
   (see catalog.h for the filter state itself - the sidebar just draws
   whatever it currently says and reports clicks on the three pills; app.c
   owns actually changing the filter and re-running it). */
typedef enum {
    kSidebarFilterYear = 0,
    kSidebarFilterArch,
    kSidebarFilterSystem
} SidebarFilterKind;

/* pt is window-local; returns true and fills *outKind if the click landed
   on one of the three pills, false (outKind untouched) for everything
   else in the sidebar, including a plain category click. */
Boolean Sidebar_ClickFilter(const Rect *bounds, Point pt, SidebarFilterKind *outKind);
void Sidebar_GetYearFilterRect(const Rect *bounds, Rect *out);
void Sidebar_GetArchFilterRect(const Rect *bounds, Rect *out);
void Sidebar_GetSystemFilterRect(const Rect *bounds, Rect *out);

#endif
