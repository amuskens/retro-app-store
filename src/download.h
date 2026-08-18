#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "ftp.h"

/* Bridges ftp.c to disk: connects fresh, RETRs remotePath, writes it into
   an auto-created "Garden Downloads" folder next to the app (no per-file
   Save dialog - see the README on why that's a deliberate UX choice, not
   a missing feature), reporting progress as it goes. The saved file name
   is remotePath's own basename, so it always matches what was actually
   downloaded rather than a catalog title. */

typedef void (*ProgressProc)(void *userData, unsigned long bytesSoFar,
                              unsigned long totalBytes, Boolean totalKnown);

OSErr Download_Fetch(const char *host, tcp_port port, const char *user, const char *pass,
                      const char *remotePath,
                      ProgressProc onProgress, void *progressUserData,
                      GiveTimeProc giveTime, Boolean *cancel);

#endif
