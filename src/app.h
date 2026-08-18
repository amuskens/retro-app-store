#ifndef APP_H
#define APP_H

#include <Quickdraw.h> /* Boolean */
#include <Events.h>    /* EventRecord */

/* Initializes the Toolbox, creates the main browser window, and runs the
   event loop until the user quits. */
void RunApp(void);

/* True while Garden is suspended (another process is frontmost) - real
   Mac cooperative multitasking convention is to stop polling/animating
   things like a blinking text caret while in the background, so as not
   to compete for CPU with whatever app the user actually switched to.
   Kept accurate even mid-download: the progress dialog runs its own small
   event loop (ProgressDlg_GiveTime) rather than the main one, so it calls
   App_HandleOSEvent too instead of only the main loop doing so. */
Boolean App_InBackground(void);
void App_HandleOSEvent(const EventRecord *event);

#endif
