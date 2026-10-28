#ifndef FTP_H
#define FTP_H

#include "net.h"

/* A small FTP client: connect/login, SIZE, NLST, RETR, quit. Pure protocol
   logic on top of net.h - doesn't touch MacTCP directly, so this is the
   part that could move to an OpenTransport backend later without
   changing (see the README's "OpenTransport" note in Known Limitations). */

typedef struct {
    NetConnection control;
    LineReader controlReader;
    Boolean connected;
    Boolean broken; /* a call on the control connection failed or was canceled - see FTP_Disconnect */
} FtpSession;

OSErr FTP_Connect(FtpSession *session, const char *hostName, tcp_port port,
                   const char *user, const char *pass,
                   GiveTimeProc giveTime, Boolean *cancel);

void FTP_Disconnect(FtpSession *session, GiveTimeProc giveTime, Boolean *cancel);

/* Best-effort SIZE query - returns false (not an OSErr) if the server
   doesn't support SIZE or the path doesn't exist. Callers should treat
   false as "show an indeterminate progress bar," not a failure. */
Boolean FTP_GetSize(FtpSession *session, const char *remotePath, unsigned long *outSize,
                     GiveTimeProc giveTime, Boolean *cancel);

/* Lists file names (NLST) at remotePath ("" or "." for the login's default
   directory) into outNames (each up to 63 chars + NUL), up to maxNames
   entries. Returns the count actually found (0 on any failure - there's
   no separate error path since a browse UI just shows "no files"
   either way). */
short FTP_ListNames(FtpSession *session, const char *remotePath,
                     char outNames[][64], short maxNames,
                     GiveTimeProc giveTime, Boolean *cancel);

/* Downloads remotePath, calling onChunk once per chunk received so the
   caller can write it to disk / update a progress UI without this module
   knowing about either. */
typedef void (*FtpChunkProc)(void *userData, const void *buf, unsigned short len);
OSErr FTP_Retrieve(FtpSession *session, const char *remotePath,
                    FtpChunkProc onChunk, void *userData,
                    GiveTimeProc giveTime, Boolean *cancel);

/* Releases the DNR resolver code resource (dnr.c's DNR_Open lazily loads
   it on first hostname lookup and never released it - a real, if minor,
   gap: unlike the MacTCP driver itself, which the OS's own Device
   Manager closes as part of a real Shut Down regardless of what any app
   did, the resolver's loaded code resource and its internal state are
   purely this app's own responsibility to release, nothing else knows to
   do it. Call once, right before the app actually quits - see RunApp). */
void FTP_Shutdown(void);

#endif
