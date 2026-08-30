#ifndef RESULTS_VIEW_H
#define RESULTS_VIEW_H

#include <Quickdraw.h>

/* The main paginated, 10-per-page results list - the app's primary content
   area. Backed either by the bundled catalog (category browse or search)
   or by a live FTP directory listing (see ResultsView_ShowLiveListing),
   behind one shared row-drawing/pagination/click implementation. */

typedef struct {
    char title[128];
    char remotePath[256];
    Boolean isLiveFile; /* true: remotePath came from a live NLST just now
                            (exact/real). false: it's a catalog placeholder
                            path - see README. */
} DownloadRequest;

void ResultsView_ShowCategory(short categoryIndex);
void ResultsView_ShowSearch(const char *query);

/* Caps how many rows are drawn/paginated per page - clamped to [1, 10].
   app.c calls this on every layout pass with however many full
   kResultRowHeight rows actually fit in the current results area, so a
   short window (or a small physical screen) shows fewer, complete rows
   per page rather than a truncated row bleeding into the status bar
   below. A no-op when rows matches the current page size, so calling it
   on every ordinary redraw (not just real resizes) is cheap and doesn't
   reset scroll/selection state for no reason. */
void ResultsView_SetPageSize(short rows);

/* Re-applies whatever category or search is currently showing, picking up
   a Year/CPU filter change made since - see catalog.h. No-op in live
   mode. */
void ResultsView_RefreshFilter(void);

/* Populates the Live FTP Browse listing from a just-completed NLST (+
   best-effort SIZE per file). Parallel arrays of length count; copied
   internally, capped at kResultsMaxLiveEntries. */
void ResultsView_ShowLiveListing(char names[][64], const unsigned long sizes[],
                                  const Boolean sizeKnown[], short count);

/* True while the view is showing the (empty, until a Refresh happens)
   live-listing mode - app.c uses this to decide whether a live fetch is
   actually needed on connect. */
Boolean ResultsView_IsLiveMode(void);

/* Switches to live mode without changing any previously-fetched listing
   (so re-selecting "Live FTP Browse" shows cached results instantly; it
   shows the "not connected yet" placeholder only the first time, before
   any fetch has ever completed). */
void ResultsView_EnterLiveMode(void);

void ResultsView_Draw(const Rect *bounds);

typedef enum {
    kResultsActivationGet = 0,    /* the row's Get button */
    kResultsActivationDoubleClick /* double-clicked the row itself */
} ResultsActivation;

/* pt and when are window-local point / event tick count (from
   EventRecord.where/when) - used for click hit-testing and double-click
   detection. Returns true and fills *outReq/*outActivation if the click
   should trigger something (Get button, or a double-click on a row);
   otherwise just updates selection/redraws in place and returns false.

   The Get button always means "download this". A double-click means
   "download" in catalog/search mode, but in live mode the caller should
   treat it as "try navigating into this as a folder" instead - live
   listings are frequently all-folders (see README), so a plain download
   attempt on a double-click there would just fail against something the
   user was trying to browse into, not fetch. outActivation is only
   meaningful when this returns true. */
Boolean ResultsView_Click(const Rect *bounds, Point pt, unsigned long when,
                           DownloadRequest *outReq, ResultsActivation *outActivation);

/* Fills *outReq from whatever row is currently selected (returns false,
   *outReq untouched, if nothing is selected) - used by the File menu's
   "Get Selected Item", the keyboard-reachable equivalent of clicking a
   row's Get button. */
Boolean ResultsView_GetSelected(DownloadRequest *outReq);

short ResultsView_PageCount(void);
short ResultsView_CurrentPage(void); /* 0-based */
void ResultsView_NextPage(const Rect *bounds);
void ResultsView_PrevPage(const Rect *bounds);

#define kResultsMaxLiveEntries 500

#endif
