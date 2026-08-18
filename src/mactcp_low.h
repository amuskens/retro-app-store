#ifndef MACTCP_LOW_H
#define MACTCP_LOW_H

#include <Types.h>
#include <Devices.h>

/* Retro68's bundled headers don't include MacTCP.h or OpenTransport.h at
   all (confirmed against this toolchain and Retro68's own README) - Apple's
   real Universal Interfaces aren't freely redistributable, so there's
   nothing to vendor a copy of. This is a from-scratch reconstruction of
   just the pieces this app needs, cross-checked field-for-field against two
   independently-sourced copies of Apple's real MacTCP.h (which agreed
   byte-for-byte) rather than written from memory alone - the csCode values
   in particular are easy to misremember (they aren't sequential from a
   round number) and a wrong one here fails silently against a real driver.
   If Apple's real headers are ever added to this toolchain's
   InterfacesAndLibraries, they'd define the same names - this header
   would just become redundant, not wrong. */

typedef unsigned long ip_addr;
typedef unsigned short tcp_port;
typedef unsigned long StreamPtr;

#define kMacTCPDriverName "\p.IPP"

/* A wds/rds is a list of {length,ptr} pairs terminated by one with
   length==0 - used by TCPSend (write data) and TCPNoCopyRcv (read data). */
struct wdsEntry {
    unsigned short length;
    Ptr ptr;
};
typedef struct wdsEntry wdsEntry;

/* MacTCP return codes, -23000..-23049 (verified against two independent
   copies of Apple's MacTCP.h). inProgress is the "still working" sentinel
   an async call's ioResult holds until the driver overwrites it with the
   real outcome - the poll loops in net.c watch for exactly this. */
enum {
    inProgress              = 1,
    ipBadLapErr             = -23000,
    ipBadCnfgErr            = -23001,
    ipNoCnfgErr             = -23002,
    ipLoadErr               = -23003,
    ipBadAddr               = -23004,
    connectionClosing       = -23005,
    invalidLength           = -23006,
    connectionExists        = -23007,
    connectionDoesntExist   = -23008,
    insufficientResources   = -23009,
    invalidStreamPtr        = -23010,
    streamAlreadyOpen       = -23011,
    connectionTerminated    = -23012,
    invalidBufPtr           = -23013,
    invalidRDS              = -23014,
    invalidWDS              = -23014,
    openFailed              = -23015,
    commandTimeout          = -23016,
    duplicateSocket         = -23017
};

/* DNR-specific codes from the same real error block (-23032..-23048) -
   only cacheFault is actually branched on (see dnr.c's DNR_Resolve), the
   rest are here for completeness/future diagnostics, not currently read. */
enum {
    ipDontFragErr    = -23032,
    ipDestDeadErr    = -23033,
    icmpEchoTimeoutErr = -23035,
    ipNoFragMemErr   = -23036,
    ipRouteErr       = -23037,
    nameSyntaxErr    = -23041,
    cacheFault       = -23042,
    noResultProc     = -23043,
    noNameServer     = -23044,
    authNameErr      = -23045,
    noAnsErr         = -23046,
    dnrErr           = -23047,
    outOfMemory      = -23048
};

/* csCode values for PBControlSync/PBControlAsync on the ".IPP" driver's
   refnum. Numeric, not sequential from TCPCreate - do not renumber. */
enum {
    TCPCreate       = 30,
    TCPPassiveOpen  = 31,
    TCPActiveOpen   = 32,
    TCPSend         = 34,
    TCPNoCopyRcv    = 35,
    TCPRcvBfrReturn = 36,
    TCPRcv          = 37,
    TCPClose        = 38,
    TCPAbort        = 39,
    TCPStatus       = 40,
    TCPExtendedStat = 41,
    TCPRelease      = 42,
    TCPGlobalInfo   = 43
};

typedef struct TCPiopb TCPiopb;

/* Async completion routine and stream-event notifier. This app never
   installs either (always NULL) - see net.c's header comment for why:
   polling ioResult directly avoids needing interrupt-time-safe callback
   code entirely, at the cost of true background operation, which this app
   doesn't need. Declared `pascal` (not plain C) because that's the
   convention the real driver would call them with, if they were ever
   non-NULL - matters for stack layout even though they're unused. */
typedef pascal void (*TCPNotifyProcPtr)(StreamPtr tcpStream, unsigned short eventCode,
                                         Ptr userDataPtr, unsigned short terminReason,
                                         void *icmpMsg);
typedef pascal void (*TCPIOCompletionProcPtr)(TCPiopb *iopb);

struct TCPCreatePB {
    Ptr rcvBuff;
    unsigned long rcvBuffLen;
    TCPNotifyProcPtr notifyProc;
    Ptr userDataPtr;
};

struct TCPOpenPB {
    SInt8 ulpTimeoutValue;
    SInt8 ulpTimeoutAction;
    SInt8 validityFlags;
    SInt8 commandTimeoutValue;
    ip_addr remoteHost;
    tcp_port remotePort;
    ip_addr localHost;
    tcp_port localPort;
    SInt8 tosFlags;
    SInt8 precedence;
    Boolean dontFrag;
    SInt8 timeToLive;
    SInt8 security;
    SInt8 optionCnt;
    SInt8 options[40];
    Ptr userDataPtr;
};

struct TCPSendPB {
    SInt8 ulpTimeoutValue;
    SInt8 ulpTimeoutAction;
    SInt8 validityFlags;
    Boolean pushFlag;
    Boolean urgentFlag;
    SInt8 filler;
    Ptr wdsPtr;
    unsigned long sendFree;
    unsigned short sendLength;
    Ptr userDataPtr;
};

struct TCPReceivePB {
    SInt8 commandTimeoutValue;
    Boolean markFlag;
    Boolean urgentFlag;
    SInt8 filler;
    Ptr rcvBuff;
    unsigned short rcvBuffLen;
    Ptr rdsPtr;
    unsigned short rdsLength;
    unsigned short secondTimeStamp;
    Ptr userDataPtr;
};

struct TCPClosePB {
    SInt8 ulpTimeoutValue;
    SInt8 ulpTimeoutAction;
    SInt8 validityFlags;
    SInt8 filler;
    Ptr userDataPtr;
};

struct TCPAbortPB {
    Ptr userDataPtr;
};

struct TCPStatusPB {
    SInt8 ulpTimeoutValue;
    SInt8 ulpTimeoutAction;
    long unused;
    ip_addr remoteHost;
    tcp_port remotePort;
    ip_addr localHost;
    tcp_port localPort;
    SInt8 tosFlags;
    SInt8 precedence;
    SInt8 connectionState;
    SInt8 filler;
    unsigned short sendWindow;
    unsigned short rcvWindow;
    unsigned short amtUnackedData;
    unsigned short amtUnreadData;
    Ptr securityLevelPtr;
    unsigned long sendUnacked;
    unsigned long sendNext;
    unsigned long congestionWindow;
    unsigned long rcvNext;
    unsigned long srtt;
    unsigned long lastRTT;
    unsigned long sendMaxSegSize;
    Ptr connStatPtr;
    Ptr userDataPtr;
};

struct TCPGlobalInfoPB {
    Ptr tcpParamPtr;
    Ptr tcpStatsPtr;
    Ptr tcpCDBTable[1];
    Ptr userDataPtr;
    unsigned short maxTCPConnections;
};

/* Same header shape as the generic Device Manager CntrlParam (qLink..
   csCode, fill12 covers the first four fields), followed by tcpStream and
   the real per-call parameter union in place of a plain csParam[11] -
   TCP calls need more than 11 words, which is why MacTCP defines its own
   parameter block instead of reusing CntrlParam directly. */
struct TCPiopb {
    SInt8 fill12[12];
    TCPIOCompletionProcPtr ioCompletion;
    short ioResult;
    Ptr ioNamePtr;
    short ioVRefNum;
    short ioCRefNum;
    short csCode;
    StreamPtr tcpStream;
    union {
        struct TCPCreatePB create;
        struct TCPOpenPB open;
        struct TCPSendPB send;
        struct TCPReceivePB receive;
        struct TCPClosePB close;
        struct TCPAbortPB abort;
        struct TCPStatusPB status;
        struct TCPGlobalInfoPB globalInfo;
    } csParam;
};

/* Cooperative-multitasking hook: every blocking-feeling operation in
   net.c/dnr.c polls a driver call's completion in a loop that calls this
   (typically wired to SystemTask()/WaitNextEvent()) each time around, so
   the app never freezes waiting on the network - see net.c. */
typedef void (*GiveTimeProc)(void);

#endif
