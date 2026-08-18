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

#endif
