#include <string.h>
#include <Devices.h>
#include <Memory.h>
#include <OSUtils.h>

#include "net.h"

#define kRcvBufferSize 8192
#define kDefaultTimeoutSecs 20
/* TCPActiveOpen's own ulpTimeoutValue/ulpTimeoutAction below *should*
   already bound how long a connect attempt can take, but verified live
   against a real silently-unreachable address (exactly what a genuinely
   dropped/dead network connection looks like) that it doesn't reliably
   fire - even after 70+ real seconds, the wait never resolved on its
   own. Most likely explanation: ulpTimeoutValue governs the TCP-level
   SYN retransmission/handshake timeout once a packet is actually on the
   wire, not an earlier routing/address-resolution stall, which this
   failure mode seems to get stuck in instead - below the layer that
   field can bound at all. Net_Open's own client-side watchdog (see
   kConnectWatchdogTicks below) is the safety net that guarantees a
   connect attempt can never hang the app indefinitely regardless of
   why MacTCP's own timeout mechanism didn't cover it. */
#define kConnectWatchdogTicks (45UL * 60UL) /* ~45s at 60 ticks/sec - generous headroom above kDefaultTimeoutSecs so MacTCP's own timeout normally wins first when it does fire */

static short gDriverRefNum = 0;
static Boolean gDriverOpen = false;

/* Every stream TCPCreate has handed out and nothing has released yet.
   MacTCP does not reclaim an application's streams when the application
   quits, so one that slips through a cleanup path stays allocated in the
   driver, and Finder's Shut Down can then hang waiting on it. Net_AbortAll
   sweeps whatever is left at exit. Only the StreamPtr is stored, never
   the NetConnection: those are frequently stack locals. */
#define kMaxTrackedStreams 16
static StreamPtr gTrackedStreams[kMaxTrackedStreams];

static void TrackStream(StreamPtr stream)
{
    short i;
    for (i = 0; i < kMaxTrackedStreams; i++) {
        if (gTrackedStreams[i] == 0) { gTrackedStreams[i] = stream; return; }
    }
}

static void UntrackStream(StreamPtr stream)
{
    short i;
    for (i = 0; i < kMaxTrackedStreams; i++) {
        if (gTrackedStreams[i] == stream) gTrackedStreams[i] = 0;
    }
}

/* Issues one MacTCP request asynchronously and polls its completion,
   yielding via giveTime each time around - see net.h's header comment for
   why this is the only pattern used here instead of a completion routine
   or stream notifier. Once cancel fires, this stops touching *pb (MacTCP
   may still complete it later) and the caller is expected to Net_Abort
   the whole connection rather than try to un-block this one call. */
static OSErr DoControlCall(TCPiopb *pb, GiveTimeProc giveTime, Boolean *cancel)
{
    pb->ioCompletion = NULL;
    pb->ioResult = inProgress;
    PBControlAsync((ParmBlkPtr)pb);

    while (pb->ioResult == inProgress) {
        if (cancel != NULL && *cancel) return userCanceledErr;
        if (giveTime != NULL) giveTime();
    }
    return pb->ioResult;
}

/* Like DoControlCall, plus a client-side deadline - used only for
   TCPActiveOpen (see Net_Open and kConnectWatchdogTicks above). Bailing
   out early here on either cancel or the deadline is safe for the exact
   reason DoControlCall's own bailing-out-on-cancel already is (see its
   comment): the caller is expected to follow up with Net_Abort, which
   always waits for its own TCPAbort+TCPRelease to really finish before
   returning - that's what actually tears the stream down at the driver
   level, so nothing is left that could ever complete into this pb again
   afterward, whichever way this returned early. */
static OSErr DoControlCallWithDeadline(TCPiopb *pb, GiveTimeProc giveTime, Boolean *cancel,
                                        unsigned long deadlineTicks)
{
    pb->ioCompletion = NULL;
    pb->ioResult = inProgress;
    PBControlAsync((ParmBlkPtr)pb);

    while (pb->ioResult == inProgress) {
        if (cancel != NULL && *cancel) return userCanceledErr;
        if (TickCount() >= deadlineTicks) return commandTimeout;
        if (giveTime != NULL) giveTime();
    }
    return pb->ioResult;
}

/* Like DoControlCall, but never bails out early on cancel: pb is often a
   caller's stack local (Net_Close/Net_Abort's own conn/pb locals, or a
   caller's whole NetConnection), so letting it go out of scope while
   MacTCP still thinks it owns the address would mean a completion write
   into freed stack space later. cancel is irrelevant to a call whose
   entire job is "this is ending, now clean up" - giveTime is what
   actually matters, so the UI keeps redrawing/responding while this
   finishes rather than freezing. */
static void DoAbortCall(TCPiopb *pb, GiveTimeProc giveTime)
{
    pb->ioCompletion = NULL;
    pb->ioResult = inProgress;
    PBControlAsync((ParmBlkPtr)pb);

    while (pb->ioResult == inProgress) {
        if (giveTime != NULL) giveTime();
    }
}

OSErr Net_Init(void)
{
    ParamBlockRec pb;
    OSErr err;

    if (gDriverOpen) return noErr;

    memset(&pb, 0, sizeof(pb));
    pb.ioParam.ioNamePtr = (StringPtr)kMacTCPDriverName;
    pb.ioParam.ioPermssn = 0; /* fsCurPerm - permission is meaningless for a driver open, but the field exists */
    err = PBOpenSync(&pb);
    if (err != noErr) return err;

    gDriverRefNum = pb.ioParam.ioRefNum;
    gDriverOpen = true;
    return noErr;
}

OSErr Net_Open(NetConnection *conn, ip_addr remoteHost, tcp_port remotePort,
               GiveTimeProc giveTime, Boolean *cancel)
{
    OSErr err;

    memset(conn, 0, sizeof(*conn));

    conn->rcvBuffer = NewPtr(kRcvBufferSize);
    if (conn->rcvBuffer == NULL) return memFullErr;

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPCreate;
    conn->pb.csParam.create.rcvBuff = conn->rcvBuffer;
    conn->pb.csParam.create.rcvBuffLen = kRcvBufferSize;
    conn->pb.csParam.create.notifyProc = NULL;
    conn->pb.csParam.create.userDataPtr = NULL;

    /* DoAbortCall, not DoControlCall: TCPCreate must never be abandoned
       half-done. Real bug, found by review - bailing out of this one on
       cancel did three bad things at once, all of them silent. (1) The
       DisposePtr below handed the 8K block back to the heap while MacTCP
       was still about to install it as the stream's permanent receive
       buffer, so the driver would go on writing incoming packets into
       memory the app had since reused. (2) conn->stream was never
       assigned, and Net_Abort only releases when stream != 0, so the
       stream TCPCreate did go on to create could never be released -
       each cancelled connect permanently burned one of MacTCP's small
       fixed pool of streams until reboot. (3) It left conn->pb pending on
       what is often a caller's stack local (see OpenPassiveData/
       FTP_Retrieve), the exact hazard DoAbortCall exists to prevent.
       Nothing is lost by not honouring cancel here: TCPCreate is a local
       bookkeeping call with no network round-trip, so it completes
       promptly regardless. The TCPActiveOpen below - the part that can
       actually block on a dead network - still honours cancel, and now
       has a real stream to abort. */
    DoAbortCall(&conn->pb, giveTime);
    err = conn->pb.ioResult;
    if (err != noErr) {
        DisposePtr(conn->rcvBuffer);
        conn->rcvBuffer = NULL;
        return err;
    }
    conn->stream = conn->pb.tcpStream;
    TrackStream(conn->stream);

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPActiveOpen;
    conn->pb.tcpStream = conn->stream;
    conn->pb.csParam.open.ulpTimeoutValue = kDefaultTimeoutSecs;
    conn->pb.csParam.open.ulpTimeoutAction = 1; /* abort the connection on timeout */
    conn->pb.csParam.open.validityFlags = 0xC0; /* timeoutValue | timeoutAction, see mactcp_low.h */
    conn->pb.csParam.open.remoteHost = remoteHost;
    conn->pb.csParam.open.remotePort = remotePort;
    conn->pb.csParam.open.localHost = 0;
    conn->pb.csParam.open.localPort = 0;

    err = DoControlCallWithDeadline(&conn->pb, giveTime, cancel, TickCount() + kConnectWatchdogTicks);
    if (err != noErr) {
        Net_Abort(conn, giveTime);
        return err;
    }
    return noErr;
}

OSErr Net_Send(NetConnection *conn, const void *data, unsigned short length,
               GiveTimeProc giveTime, Boolean *cancel)
{
    wdsEntry wds[2];

    wds[0].length = length;
    wds[0].ptr = (Ptr)data;
    wds[1].length = 0;
    wds[1].ptr = NULL;

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPSend;
    conn->pb.tcpStream = conn->stream;
    conn->pb.csParam.send.ulpTimeoutValue = kDefaultTimeoutSecs;
    conn->pb.csParam.send.ulpTimeoutAction = 1;
    conn->pb.csParam.send.validityFlags = 0xC0;
    conn->pb.csParam.send.pushFlag = true;
    conn->pb.csParam.send.urgentFlag = false;
    conn->pb.csParam.send.wdsPtr = (Ptr)wds;

    return DoControlCall(&conn->pb, giveTime, cancel);
}

OSErr Net_Receive(NetConnection *conn, void *buf, unsigned short bufLen, unsigned short *outLen,
                   GiveTimeProc giveTime, Boolean *cancel)
{
    OSErr err;

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPRcv;
    conn->pb.tcpStream = conn->stream;
    conn->pb.csParam.receive.commandTimeoutValue = kDefaultTimeoutSecs;
    conn->pb.csParam.receive.rcvBuff = (Ptr)buf;
    conn->pb.csParam.receive.rcvBuffLen = bufLen;

    err = DoControlCall(&conn->pb, giveTime, cancel);
    *outLen = (err == noErr) ? conn->pb.csParam.receive.rcvBuffLen : 0;
    return err;
}

OSErr Net_Close(NetConnection *conn, GiveTimeProc giveTime)
{
    OSErr err;

    /* DoAbortCall, not DoControlCall - see the "no cancel parameter"
       comment on this function in net.h. */
    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPClose;
    conn->pb.tcpStream = conn->stream;
    conn->pb.csParam.close.ulpTimeoutValue = kDefaultTimeoutSecs;
    conn->pb.csParam.close.ulpTimeoutAction = 1;
    conn->pb.csParam.close.validityFlags = 0xC0;
    DoAbortCall(&conn->pb, giveTime);
    err = conn->pb.ioResult;

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPRelease;
    conn->pb.tcpStream = conn->stream;
    DoAbortCall(&conn->pb, giveTime);

    if (conn->rcvBuffer != NULL) {
        DisposePtr(conn->rcvBuffer);
        conn->rcvBuffer = NULL;
    }
    UntrackStream(conn->stream);
    conn->stream = 0;
    return err;
}

void Net_Abort(NetConnection *conn, GiveTimeProc giveTime)
{
    TCPiopb pb;

    if (conn->stream != 0) {
        memset(&pb, 0, sizeof(pb));
        pb.ioCRefNum = gDriverRefNum;
        pb.csCode = TCPAbort;
        pb.tcpStream = conn->stream;
        DoAbortCall(&pb, giveTime);

        memset(&pb, 0, sizeof(pb));
        pb.ioCRefNum = gDriverRefNum;
        pb.csCode = TCPRelease;
        pb.tcpStream = conn->stream;
        DoAbortCall(&pb, giveTime);
    }

    if (conn->rcvBuffer != NULL) {
        DisposePtr(conn->rcvBuffer);
        conn->rcvBuffer = NULL;
    }
    UntrackStream(conn->stream);
    conn->stream = 0;
}

void Net_AbortAll(GiveTimeProc giveTime)
{
    TCPiopb pb;
    short i;

    if (!gDriverOpen) return;

    for (i = 0; i < kMaxTrackedStreams; i++) {
        StreamPtr stream = gTrackedStreams[i];
        if (stream == 0) continue;
        gTrackedStreams[i] = 0;

        memset(&pb, 0, sizeof(pb));
        pb.ioCRefNum = gDriverRefNum;
        pb.csCode = TCPAbort;
        pb.tcpStream = stream;
        DoAbortCall(&pb, giveTime);

        memset(&pb, 0, sizeof(pb));
        pb.ioCRefNum = gDriverRefNum;
        pb.csCode = TCPRelease;
        pb.tcpStream = stream;
        DoAbortCall(&pb, giveTime);
    }
}

void LineReader_Init(LineReader *reader, NetConnection *conn)
{
    reader->conn = conn;
    reader->len = 0;
    reader->eof = false;
    reader->lastErr = noErr;
}

Boolean LineReader_Next(LineReader *reader, char *outLine, short outLineSize,
                         GiveTimeProc giveTime, Boolean *cancel)
{
    for (;;) {
        short i;
        for (i = 0; i < reader->len; i++) {
            if (reader->buf[i] == '\n') {
                short lineLen = i;
                short remaining;
                if (lineLen > 0 && reader->buf[lineLen - 1] == '\r') lineLen--;
                if (lineLen >= outLineSize) lineLen = (short)(outLineSize - 1);
                BlockMove(reader->buf, outLine, lineLen);
                outLine[lineLen] = 0;

                remaining = (short)(reader->len - (i + 1));
                BlockMove(reader->buf + i + 1, reader->buf, remaining);
                reader->len = remaining;
                return true;
            }
        }

        if (reader->eof) {
            if (reader->len > 0) {
                short lineLen = reader->len;
                if (lineLen >= outLineSize) lineLen = (short)(outLineSize - 1);
                BlockMove(reader->buf, outLine, lineLen);
                outLine[lineLen] = 0;
                reader->len = 0;
                return true;
            }
            return false;
        }

        if (reader->len >= (short)sizeof(reader->buf))
            reader->len = 0; /* pathologically long line for this protocol - drop and resync */

        {
            unsigned short got;
            OSErr err = Net_Receive(reader->conn, reader->buf + reader->len,
                                     (unsigned short)(sizeof(reader->buf) - reader->len), &got,
                                     giveTime, cancel);
            if (err == connectionClosing || err == connectionDoesntExist) {
                reader->eof = true;
            } else if (err != noErr) {
                reader->lastErr = err;
                reader->eof = true;
            } else if (got == 0) {
                reader->eof = true;
            } else {
                reader->len = (short)(reader->len + got);
            }
        }
    }
}
