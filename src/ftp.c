#include <string.h>
#include <stdio.h>

#include "ftp.h"
#include "dnr.h"

static OSErr SendCommand(FtpSession *s, const char *cmd, GiveTimeProc giveTime, Boolean *cancel)
{
    char line[560];
    short len;

    strncpy(line, cmd, sizeof(line) - 3);
    line[sizeof(line) - 3] = 0;
    len = (short)strlen(line);
    line[len++] = '\r';
    line[len++] = '\n';

    return Net_Send(&s->control, line, (unsigned short)len, giveTime, cancel);
}

/* Reads one (possibly multi-line, RFC 959 4.2) FTP reply from the control
   connection. outMsg, if non-NULL, receives the final line verbatim (code
   + text) - callers that need to parse a reply's payload (PASV's address
   tuple, SIZE's byte count) read it from there. */
static OSErr ReadReply(FtpSession *s, short *outCode, char *outMsg, short outMsgSize,
                        GiveTimeProc giveTime, Boolean *cancel)
{
    char line[512];
    short code = 0;

    for (;;) {
        if (!LineReader_Next(&s->controlReader, line, sizeof(line), giveTime, cancel)) {
            return (s->controlReader.lastErr != noErr) ? s->controlReader.lastErr : connectionClosing;
        }
        if ((short)strlen(line) < 4) continue; /* blank/malformed line - ignore and keep reading */

        {
            short c = (short)((line[0] - '0') * 100 + (line[1] - '0') * 10 + (line[2] - '0'));
            if (code == 0) code = c;
            if (line[3] == ' ' && c == code) {
                *outCode = code;
                if (outMsg != NULL) {
                    strncpy(outMsg, line, (size_t)(outMsgSize - 1));
                    outMsg[outMsgSize - 1] = 0;
                }
                return noErr;
            }
            /* line[3] == '-' (or a different code entirely): still inside
               a multi-line reply per RFC 959 - keep reading until a line
               with the original code followed by a space. */
        }
    }
}

/* "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)." - the message text
   around the tuple varies by server, so this just finds the first '(' and
   parses six comma-separated numbers rather than matching exact wording. */
static Boolean ParsePasvReply(const char *msg, ip_addr *outAddr, tcp_port *outPort)
{
    const char *paren = strchr(msg, '(');
    unsigned int h1, h2, h3, h4, p1, p2;

    if (paren == NULL) return false;
    if (sscanf(paren + 1, "%u,%u,%u,%u,%u,%u", &h1, &h2, &h3, &h4, &p1, &p2) != 6) return false;
    if (h1 > 255 || h2 > 255 || h3 > 255 || h4 > 255 || p1 > 255 || p2 > 255) return false;

    *outAddr = ((ip_addr)h1 << 24) | ((ip_addr)h2 << 16) | ((ip_addr)h3 << 8) | (ip_addr)h4;
    *outPort = (tcp_port)((p1 << 8) | p2);
    return true;
}

static OSErr OpenPassiveData(FtpSession *s, NetConnection *dataConn, GiveTimeProc giveTime, Boolean *cancel)
{
    OSErr err;
    short code;
    char msg[256];
    ip_addr dataAddr;
    tcp_port dataPort;

    err = SendCommand(s, "PASV", giveTime, cancel);
    if (err != noErr) return err;

    err = ReadReply(s, &code, msg, sizeof(msg), giveTime, cancel);
    if (err != noErr) return err;
    if (code != 227) return openFailed;
    if (!ParsePasvReply(msg, &dataAddr, &dataPort)) return openFailed;

    return Net_Open(dataConn, dataAddr, dataPort, giveTime, cancel);
}

OSErr FTP_Connect(FtpSession *s, const char *hostName, tcp_port port,
                   const char *user, const char *pass,
                   GiveTimeProc giveTime, Boolean *cancel)
{
    ip_addr addr;
    OSErr err;
    short code;
    char cmd[300];

    memset(s, 0, sizeof(*s));

    err = Net_Init();
    if (err != noErr) return err;

    err = DNR_Resolve(hostName, &addr, giveTime, cancel);
    if (err != noErr) return err;

    err = Net_Open(&s->control, addr, port, giveTime, cancel);
    if (err != noErr) return err;
    LineReader_Init(&s->controlReader, &s->control);

    err = ReadReply(s, &code, NULL, 0, giveTime, cancel); /* 220 welcome */
    if (err != noErr) { Net_Abort(&s->control, giveTime); return err; }
    if (code != 220) { Net_Abort(&s->control, giveTime); return openFailed; }

    sprintf(cmd, "USER %.250s", user);
    err = SendCommand(s, cmd, giveTime, cancel);
    if (err == noErr) err = ReadReply(s, &code, NULL, 0, giveTime, cancel);
    if (err != noErr) { Net_Abort(&s->control, giveTime); return err; }

    if (code == 331) {
        sprintf(cmd, "PASS %.250s", pass);
        err = SendCommand(s, cmd, giveTime, cancel);
        if (err == noErr) err = ReadReply(s, &code, NULL, 0, giveTime, cancel);
        if (err != noErr) { Net_Abort(&s->control, giveTime); return err; }
    }
    if (code != 230) { Net_Abort(&s->control, giveTime); return openFailed; }

    err = SendCommand(s, "TYPE I", giveTime, cancel);
    if (err == noErr) err = ReadReply(s, &code, NULL, 0, giveTime, cancel);
    if (err != noErr) { Net_Abort(&s->control, giveTime); return err; }

    s->connected = true;
    return noErr;
}

void FTP_Disconnect(FtpSession *s, GiveTimeProc giveTime, Boolean *cancel)
{
    if (!s->connected) return;

    if (cancel != NULL && *cancel) {
        /* The user already asked to stop - a graceful QUIT+TCPClose can
           still take up to the control connection's own close timeout if
           the remote doesn't answer, which "Stop" shouldn't have to wait
           through. Net_Abort is both faster and (unlike a plain
           SendCommand/Net_Close here would be) already safe to call with
           a stack-allocated connection regardless of cancel - see net.h. */
        Net_Abort(&s->control, giveTime);
    } else {
        SendCommand(s, "QUIT", giveTime, cancel); /* best-effort - closing regardless */
        Net_Close(&s->control, giveTime);
    }
    s->connected = false;
}

Boolean FTP_GetSize(FtpSession *s, const char *remotePath, unsigned long *outSize,
                     GiveTimeProc giveTime, Boolean *cancel)
{
    char cmd[300], msg[256];
    short code;
    unsigned long size;

    sprintf(cmd, "SIZE %.290s", remotePath);
    if (SendCommand(s, cmd, giveTime, cancel) != noErr) return false;
    if (ReadReply(s, &code, msg, sizeof(msg), giveTime, cancel) != noErr) return false;
    if (code != 213) return false;
    if (sscanf(msg, "%*d %lu", &size) != 1) return false;

    *outSize = size;
    return true;
}

short FTP_ListNames(FtpSession *s, const char *remotePath, char outNames[][64], short maxNames,
                     GiveTimeProc giveTime, Boolean *cancel)
{
    NetConnection data;
    LineReader lr;
    OSErr err;
    short code;
    char cmd[300], line[128];
    short count = 0;

    err = OpenPassiveData(s, &data, giveTime, cancel);
    if (err != noErr) return 0;

    if (remotePath != NULL && remotePath[0] != 0 && strcmp(remotePath, ".") != 0)
        sprintf(cmd, "NLST %.290s", remotePath);
    else
        strcpy(cmd, "NLST");

    err = SendCommand(s, cmd, giveTime, cancel);
    if (err != noErr) { Net_Abort(&data, giveTime); return 0; }

    err = ReadReply(s, &code, NULL, 0, giveTime, cancel);
    if (err != noErr || (code != 150 && code != 125)) { Net_Abort(&data, giveTime); return 0; }

    LineReader_Init(&lr, &data);
    while (LineReader_Next(&lr, line, sizeof(line), giveTime, cancel)) {
        if (line[0] == 0) continue;
        if (count >= maxNames) break;
        strncpy(outNames[count], line, 63);
        outNames[count][63] = 0;
        count++;
    }

    Net_Close(&data, giveTime);
    ReadReply(s, &code, NULL, 0, giveTime, cancel); /* 226 transfer complete */

    return count;
}

OSErr FTP_Retrieve(FtpSession *s, const char *remotePath, FtpChunkProc onChunk, void *userData,
                    GiveTimeProc giveTime, Boolean *cancel)
{
    NetConnection data;
    OSErr err;
    short code;
    char cmd[300];
    char buf[2048];

    err = OpenPassiveData(s, &data, giveTime, cancel);
    if (err != noErr) return err;

    sprintf(cmd, "RETR %.290s", remotePath);
    err = SendCommand(s, cmd, giveTime, cancel);
    if (err != noErr) { Net_Abort(&data, giveTime); return err; }

    err = ReadReply(s, &code, NULL, 0, giveTime, cancel);
    if (err != noErr) { Net_Abort(&data, giveTime); return err; }
    if (code != 150 && code != 125) { Net_Abort(&data, giveTime); return openFailed; }

    for (;;) {
        unsigned short got;
        err = Net_Receive(&data, buf, sizeof(buf), &got, giveTime, cancel);
        if (err == connectionClosing || err == connectionDoesntExist) { err = noErr; break; }
        if (err != noErr) { Net_Abort(&data, giveTime); return err; }
        if (got > 0 && onChunk != NULL) onChunk(userData, buf, got);
    }

    Net_Close(&data, giveTime);
    ReadReply(s, &code, NULL, 0, giveTime, cancel); /* 226 transfer complete - best-effort */

    return noErr;
}

void FTP_Shutdown(void)
{
    DNR_Close();
}
