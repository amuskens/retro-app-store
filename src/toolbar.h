#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <Quickdraw.h>
#include <Windows.h>
#include <Events.h>

/* Top search bar + bottom status/pagination bar. Both are thin chrome
   strips owning a couple of real Controls (Search/Prev/Next - few enough,
   and Toolbox-tracked, that FindControl/TrackControl earns its keep here,
   unlike the per-row Get buttons in results_view.c) plus a small embedded
   TextEdit field for search input, the same technique mac-system7-c's
   Quill uses for its document body, just single-line. */

typedef enum {
    kToolbarHitNone = 0,
    kToolbarHitSearchField,
    kToolbarHitSearchSubmit,
    kToolbarHitPrevPage,
    kToolbarHitNextPage
} ToolbarHit;

/* Creates the search field and the three Controls as children of w. Call
   once, right after the window itself is created. */
void Toolbar_Init(WindowPtr w);

/* Repositions the field/Controls for the current window size. Call after
   Init and again on every resize. */
void Toolbar_Layout(const Rect *toolbarBounds, const Rect *statusBounds);

void Toolbar_DrawTop(const Rect *bounds);
void Toolbar_DrawStatus(const Rect *bounds, Boolean connected, const char *statusText,
                         short page, short pageCount);

/* pt is window-local. Handles clicks in the search field (TEClick) and the
   three Controls (FindControl/TrackControl) internally; tells app.c what,
   if anything, it should do next. */
ToolbarHit Toolbar_Click(Point pt);

/* Routes a plain (non-Cmd) keyDown/autoKey to the search field. Returns
   true if the key was Return/Enter (a search submit), same as clicking
   Search - false for every other key (the field was still updated). */
Boolean Toolbar_HandleKey(EventRecord *evt);

/* TEIdle for the caret blink - call every time through the event loop. */
void Toolbar_Idle(void);

void Toolbar_GetSearchText(char *buf, short bufSize);
void Toolbar_ClearSearch(void);

/* Edit menu passthroughs to the search field - the app's only editable
   text, so the Edit menu always targets it. */
void Toolbar_EditCut(void);
void Toolbar_EditCopy(void);
void Toolbar_EditPaste(void);
void Toolbar_EditClear(void);

#endif
