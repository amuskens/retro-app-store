#ifndef NET_H
#define NET_H

#include "mactcp_low.h"

/* A minimal MacTCP session layer: create a stream, open it, send/receive,
   close it down. Every call that can block on the network issues its
   MacTCP request with PBControlAsync and then polls ioResult in a loop
   calling the caller's GiveTimeProc (wire it to SystemTask()) - the same
   shape antscode/MacTCPHelper's TCPHi.h uses, and the reason nothing here
   needs an interrupt-time completion routine or stream notifier: this app
   never gets async notification of anything, it just never blocks the UI
   while waiting to find out. ftp.c is the only other module that should
   need to know any of this exists. */

typedef struct {
    StreamPtr stream;
    Ptr rcvBuffer;
    TCPiopb pb;
} NetConnection;

/* Opens the MacTCP (".IPP") driver. Call once before anything else here;
   safe to call again (no-ops once already open). */
OSErr Net_Init(void);

/* Creates a stream and actively opens a connection to remoteHost:
   remotePort. On any failure, conn is left fully torn down (no partial
   stream to clean up). */
OSErr Net_Open(NetConnection *conn, ip_addr remoteHost, tcp_port remotePort,
               GiveTimeProc giveTime, Boolean *cancel);

OSErr Net_Send(NetConnection *conn, const void *data, unsigned short length,
               GiveTimeProc giveTime, Boolean *cancel);

/* Reads whatever's available up to bufLen bytes (one TCPRcv, not "fill the
   whole buffer") into *outLen. connectionClosing/connectionDoesntExist
   mean the remote side is done sending - that's an expected end-of-stream
   for ftp.c to check for, not necessarily a failure to report to the
   user. */
OSErr Net_Receive(NetConnection *conn, void *buf, unsigned short bufLen, unsigned short *outLen,
                   GiveTimeProc giveTime, Boolean *cancel);

/* Graceful TCPClose (waits for the remote FIN) then TCPRelease. Releases
   conn's buffer either way, even if the graceful close times out - a
   close that failed to be graceful still needs its stream released, or
   the buffer leaks until the driver itself is torn down.

   No cancel parameter, deliberately - same reasoning as Net_Abort below:
   conn is frequently a caller's local stack variable (e.g. each download's
   own per-transfer session), and bailing out early on a cancel flag while
   TCPClose/TCPRelease are still pending would let MacTCP write into that
   stack slot after the caller has already returned. This used to take a
   cancel flag and check it via the same polling helper Net_Open/Net_Send/
   Net_Receive use - real bug, found by working backwards from a "Shut
   Down hangs" report: canceling a download left its control connection's
   TCPClose/TCPRelease abandoned mid-flight, so the stream never actually
   finished tearing down in MacTCP's own table, and the OS's own shutdown
   sequence hung later waiting on it. Callers that already know the user
   canceled should call Net_Abort instead (see FTP_Disconnect) - not just
   for this safety reason but because a graceful close can itself take up
   to the connection's own close timeout if the remote doesn't respond,
   which "the user already asked to stop" shouldn't have to wait through. */
OSErr Net_Close(NetConnection *conn, GiveTimeProc giveTime);

/* Forceful TCPAbort + TCPRelease, for error/cancel cleanup paths, where
   the point is to tear the stream down without waiting on a graceful FIN
   exchange. Async + polling giveTime, same as every other call here - NOT
   PBControlSync, even though this only ever runs after something has
   already gone wrong: a synchronous call blocks the whole event loop with
   no way to redraw or respond to input until MacTCP completes it, so if a
   cancel arrives while mid-connect, the user would watch the app freeze
   solid a second time, right as it's supposedly cleaning up - confirmed
   as the actual cause of a real "Stop button does nothing" report, not
   the cancel check itself (every wait loop already checked *cancel
   correctly - this cleanup call just wasn't one of them, and unlike
   those, it's not itself cancel-aware: pb is stack-allocated, so it has
   to run to completion rather than bail out from under a still-pending
   async request). */
void Net_Abort(NetConnection *conn, GiveTimeProc giveTime);

/* Buffers Net_Receive output and splits it into CRLF- or LF-terminated
   text lines - FTP is a line-oriented protocol on both its control
   connection (multi-line reply parsing) and its NLST data connection (one
   filename per line), so this is shared rather than duplicated in ftp.c. */
typedef struct {
    NetConnection *conn;
    char buf[512];
    short len;
    Boolean eof;
    OSErr lastErr;
} LineReader;

void LineReader_Init(LineReader *reader, NetConnection *conn);

/* Fills outLine (NUL-terminated, CR/LF stripped) with the next line and
   returns true, or returns false once the connection is exhausted (check
   reader->lastErr to tell clean EOF from a real error). */
Boolean LineReader_Next(LineReader *reader, char *outLine, short outLineSize,
                         GiveTimeProc giveTime, Boolean *cancel);

#endif
