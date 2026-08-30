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

/* True once something (the Quit menu item, the window's close box, or a
   Quit AppleEvent - Shut Down/Restart/an explicit Finder Quit) has asked
   Garden to exit. RunApp's own loop already exits on this by itself, but
   a modal loop running outside it (Preferences' ModalDialog) has its own
   exit condition and needs to check this explicitly after dispatching a
   kHighLevelEvent, or setting gDone alone wouldn't unstick it - see
   prefs_dlg.c. */
Boolean App_IsQuitting(void);

#endif
