#include <string.h>
#include <Devices.h>
#include <Memory.h>

#include "net.h"

#define kRcvBufferSize 8192
#define kDefaultTimeoutSecs 20

static short gDriverRefNum = 0;
static Boolean gDriverOpen = false;

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

    err = DoControlCall(&conn->pb, giveTime, cancel);
    if (err != noErr) {
        DisposePtr(conn->rcvBuffer);
        conn->rcvBuffer = NULL;
        return err;
    }
    conn->stream = conn->pb.tcpStream;

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

    err = DoControlCall(&conn->pb, giveTime, cancel);
    if (err != noErr) {
        Net_Abort(conn);
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

OSErr Net_Close(NetConnection *conn, GiveTimeProc giveTime, Boolean *cancel)
{
    OSErr err;

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPClose;
    conn->pb.tcpStream = conn->stream;
    conn->pb.csParam.close.ulpTimeoutValue = kDefaultTimeoutSecs;
    conn->pb.csParam.close.ulpTimeoutAction = 1;
    conn->pb.csParam.close.validityFlags = 0xC0;
    err = DoControlCall(&conn->pb, giveTime, cancel);

    memset(&conn->pb, 0, sizeof(conn->pb));
    conn->pb.ioCRefNum = gDriverRefNum;
    conn->pb.csCode = TCPRelease;
    conn->pb.tcpStream = conn->stream;
    DoControlCall(&conn->pb, giveTime, cancel);

    if (conn->rcvBuffer != NULL) {
        DisposePtr(conn->rcvBuffer);
        conn->rcvBuffer = NULL;
    }
    conn->stream = 0;
    return err;
}

void Net_Abort(NetConnection *conn)
{
    TCPiopb pb;

    if (conn->stream != 0) {
        memset(&pb, 0, sizeof(pb));
        pb.ioCRefNum = gDriverRefNum;
        pb.csCode = TCPAbort;
        pb.tcpStream = conn->stream;
        PBControlSync((ParmBlkPtr)&pb);

        memset(&pb, 0, sizeof(pb));
        pb.ioCRefNum = gDriverRefNum;
        pb.csCode = TCPRelease;
        pb.tcpStream = conn->stream;
        PBControlSync((ParmBlkPtr)&pb);
    }

    if (conn->rcvBuffer != NULL) {
        DisposePtr(conn->rcvBuffer);
        conn->rcvBuffer = NULL;
    }
    conn->stream = 0;
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
