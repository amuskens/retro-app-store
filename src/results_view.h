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

/* pt and when are window-local point / event tick count (from
   EventRecord.where/when) - used for click hit-testing and double-click
   detection. Returns true and fills *outReq if the click should trigger a
   download (Get button, or a double-click on a row); otherwise just
   updates selection/redraws in place and returns false. */
Boolean ResultsView_Click(const Rect *bounds, Point pt, unsigned long when, DownloadRequest *outReq);

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
