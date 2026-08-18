#ifndef PROGRESS_DLG_H
#define PROGRESS_DLG_H

#include "net.h" /* GiveTimeProc */

/* A small modal-feeling download window: title, progress bar, byte
   counter, Stop button. Not Dialog-Manager-based (no DLOG/DITL) - it's a
   plain custom-drawn Window, same technique as the rest of this app's
   chrome, since the progress bar itself needs custom drawing anyway (see
   theme.h - classic Mac has no stock progress control).

   It isn't modal via ModalDialog() - it can't be, since Download_Fetch
   (download.h) is the thing actually driving the wait, not this module.
   ProgressDlg_GiveTime *is* the event pump, called from inside
   Download_Fetch's polling loop via its GiveTimeProc parameter - the same
   role ModalDialog's own internal event loop would play, just under this
   app's control instead of the Dialog Manager's. */

void ProgressDlg_Show(const char *title);
void ProgressDlg_Hide(void);

/* Wire these directly into Download_Fetch's giveTime/onProgress params. */
void ProgressDlg_GiveTime(void);
void ProgressDlg_UpdateProgress(void *userData, unsigned long bytesSoFar,
                                 unsigned long totalBytes, Boolean totalKnown);

/* Set by ProgressDlg_GiveTime when Stop is clicked or Cmd-. is pressed -
   pass this straight through as Download_Fetch's cancel parameter. */
Boolean *ProgressDlg_CancelFlag(void);

#endif
