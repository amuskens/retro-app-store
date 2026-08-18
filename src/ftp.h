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

#endif
