#include <stdio.h>
#include <string.h>
#include <Files.h>
#include <Resources.h>
#include <Memory.h>
#include <OSUtils.h>
#include <Gestalt.h>

#include "dnr.h"

/* Not defined in this toolchain's Multiverse.h (FindFolder here just takes
   the raw vRefNum/Boolean) - real, stable values from Apple's Folder
   Manager. */
#define kOnSystemDisk (-1)
#define kDontCreateFolder false

/* Same reasoning and same value as net.c's kConnectWatchdogTicks: a real
   MacTCP timeout mechanism (TCPActiveOpen's ulpTimeoutValue there) was
   confirmed live not to reliably bound a stuck operation, so DNR
   resolution gets the identical client-side safety net for the same
   class of failure - a hostname lookup that's hung against an
   unresponsive/unreachable name server has no other bound at all
   otherwise. Not independently reproduced live the way the TCPActiveOpen
   case was (see net.c) - added by inspection/code review as a real gap
   in the same family, not a guess about whether it actually fires in
   practice. */
#define kResolveWatchdogTicks (45UL * 60UL)

/* The resolver's own return-block layout - verified against Apple's
   original DNR.c (via antscode/MacTCPHelper, a Retro68 port of it). The
   SInt8 filler is deliberate, not padding I added: cname[255] leaves the
   struct at an odd offset, and the DNR code resource was built expecting
   addr[] to start on an even boundary. */
struct hostInfo {
    long rtnCode;
    char cname[255];
    SInt8 filler;
    unsigned long addr[4];
};

typedef pascal void (*DNRResultProcPtr)(struct hostInfo *hostInfoPtr, Ptr userDataPtr);

/* Selectors the loaded 'dnrp' code resource dispatches on - its first
   argument, not a MacTCP csCode. Only the four this app actually uses. */
enum {
    kSelOpenResolver  = 1,
    kSelCloseResolver = 2,
    kSelStrToAddr     = 3,
    kSelAddrToStr     = 4
};

/* The resolver's entry points use plain C calling convention (matching
   Apple's uppXxxProcInfo == kCStackBased in AddressXlation.h) - only the
   result callback below is `pascal`. Mixing these up is exactly the kind
   of mistake that corrupts the stack silently on 68K.

   BUG FIXED HERE (found on 2026-08-18 re-review, after a real emulator test
   returned "Connect failed (error -1)" against a boot disk confirmed to
   have MacTCP running): `selector` was declared `short` (2 bytes) in all
   three typedefs below. Apple's real AddressXlation.h declares it
   `UInt32` (4 bytes) - confirmed by both the plain typedef and the
   `STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(UInt32)))` in its
   uppXxxProcInfo constants. Calling through a 2-byte-selector-typed
   function pointer into a real DNR code resource compiled expecting a
   4-byte selector shifts every later argument's stack offset by 2 bytes,
   so the resolver reads hostName/rtnStruct/resultproc/userDataPtr from the
   wrong place entirely - consistent with a fast, wrong error return rather
   than a hang or crash. This was wrong from the first version of this
   file; nothing changed it in the meantime. */
typedef OSErr (*OpenResolverProcPtr)(unsigned long selector, char *fileName);
typedef OSErr (*CloseResolverProcPtr)(unsigned long selector);
typedef OSErr (*StrToAddrProcPtr)(unsigned long selector, char *hostName, struct hostInfo *rtnStruct,
                                   DNRResultProcPtr resultProc, Ptr userDataPtr);

static Handle gDNRHandle = NULL;
static ProcPtr gDNRProc = NULL;

/* hi lives inside this struct (not as DNR_Resolve's own stack local)
   specifically so the whole thing can be heap-allocated - see the
   watchdog comment in DNR_Resolve below for why plain stack storage
   isn't safe once an early bail-out on a deadline is possible, the same
   way it already wasn't safe for a plain early bail on cancel (fixed
   previously - see the history comment below). */
typedef struct {
    Boolean done;
    struct hostInfo hi;
} ResolveState;

/* Sets a per-call done flag via userDataPtr, rather than polling hi's own
   rtnCode directly - matches the pattern real, historically-used code
   (Tcl's tclMacSock.c GetHostFromString) uses, rather than an assumption
   about rtnCode being safe to poll on its own without a callback. */
static pascal void ResolveCallback(struct hostInfo *hi, Ptr userData)
{
    ResolveState *state = (ResolveState *)userData;
    (void)hi;
    if (state != NULL) state->done = true;
}

static void GetSystemFolderLoc(short *vRefNum, long *dirID)
{
    SysEnvRec info;
    long wdProcID;
    if (SysEnvirons(1, &info) != noErr ||
        GetWDInfo(info.sysVRefNum, vRefNum, dirID, &wdProcID) != noErr) {
        *vRefNum = 0;
        *dirID = 0;
    }
}

/* Folder Manager's FindFolder has been standard since System 7.0, but
   guard with Gestalt anyway (cheap, and matches Apple's original DNR.c) -
   falls back to the System Folder itself, matching how cdevs lived loose
   in the System Folder before a dedicated Control Panels folder existed. */
static void GetCPanelFolderLoc(short *vRefNum, long *dirID)
{
    long feature;
    if (Gestalt(gestaltFindFolderAttr, &feature) == noErr &&
        FindFolder((short)kOnSystemDisk, kControlPanelFolderType, kDontCreateFolder, vRefNum, dirID) == noErr) {
        return;
    }
    GetSystemFolderLoc(vRefNum, dirID);
}

/* Scans one folder's files for a 'cdev' with the given creator that also
   contains a 'dnrp' resource - i.e. the actual MacTCP control panel, found
   by creator/type rather than assuming a file name. Leaves the file's
   resource fork open (as the current top of the search chain) on success;
   the caller is responsible for closing it once it's done with 'dnrp'. */
static short FindDNRInFolder(OSType creator, short vRefNum, long dirID)
{
    HParamBlockRec fi;
    Str255 name;
    short refnum;

    memset(&fi, 0, sizeof(fi));
    fi.fileParam.ioNamePtr = name;
    fi.fileParam.ioVRefNum = vRefNum;
    fi.fileParam.ioDirID = dirID;
    fi.fileParam.ioFDirIndex = 1;

    while (PBHGetFInfoSync((HParmBlkPtr)&fi) == noErr) {
        if (fi.fileParam.ioFlFndrInfo.fdType == 'cdev' &&
            fi.fileParam.ioFlFndrInfo.fdCreator == creator) {
            refnum = HOpenResFile(vRefNum, dirID, name, fsRdPerm);
            if (refnum != -1) {
                if (GetIndResource('dnrp', 1) != NULL) return refnum;
                CloseResFile(refnum);
            }
        }
        fi.fileParam.ioFDirIndex++;
        fi.fileParam.ioDirID = dirID; /* PBHGetFInfo clobbers this each call */
    }
    return -1;
}

/* MacTCP 1.1+ ships as a 'ztcp' cdev in Control Panels; MacTCP 1.0.x
   shipped as an 'mtcp' cdev, either loose in the System Folder or (later)
   in Control Panels - try all three in that order, same as Apple's
   original DNR.c. */
static short FindDNRFile(void)
{
    short vRefNum;
    long dirID;
    short refnum;

    GetCPanelFolderLoc(&vRefNum, &dirID);
    refnum = FindDNRInFolder('ztcp', vRefNum, dirID);
    if (refnum != -1) return refnum;

    GetSystemFolderLoc(&vRefNum, &dirID);
    refnum = FindDNRInFolder('mtcp', vRefNum, dirID);
    if (refnum != -1) return refnum;

    GetCPanelFolderLoc(&vRefNum, &dirID);
    refnum = FindDNRInFolder('mtcp', vRefNum, dirID);
    return refnum;
}

OSErr DNR_Open(void)
{
    short refnum;
    Handle h;
    OpenResolverProcPtr openProc;
    OSErr err;

    if (gDNRProc != NULL) return noErr;

    refnum = FindDNRFile();
    /* Proceed even on failure: GetIndResource below searches the *whole*
       current resource chain, which includes whichever file FindDNRFile
       just opened (if any) as well as the System file - matching Apple's
       original behavior of not treating an explicit-file-search miss as
       fatal on its own. */

    h = GetIndResource('dnrp', 1);
    if (h == NULL) {
        if (refnum != -1) CloseResFile(refnum);
        err = ResError();
        return (err != noErr) ? err : resNotFound;
    }

    DetachResource(h);
    if (refnum != -1) CloseResFile(refnum);

    /* The code resource can't be allowed to move or be purged while
       something might be executing out of it. */
    MoveHHi(h);
    HLock(h);
    gDNRHandle = h;
    gDNRProc = (ProcPtr)*h;

    openProc = (OpenResolverProcPtr)gDNRProc;
    err = openProc(kSelOpenResolver, NULL);
    if (err != noErr) {
        HUnlock(gDNRHandle);
        DisposeHandle(gDNRHandle);
        gDNRHandle = NULL;
        gDNRProc = NULL;
    }
    return err;
}

void DNR_Close(void)
{
    CloseResolverProcPtr closeProc;

    if (gDNRProc == NULL) return;

    closeProc = (CloseResolverProcPtr)gDNRProc;
    closeProc(kSelCloseResolver);

    HUnlock(gDNRHandle);
    DisposeHandle(gDNRHandle);
    gDNRHandle = NULL;
    gDNRProc = NULL;
}

static Boolean TryParseDottedIP(const char *s, ip_addr *out)
{
    unsigned long a, b, c, d;
    char extra;
    int n = sscanf(s, "%lu.%lu.%lu.%lu%c", &a, &b, &c, &d, &extra);
    if (n != 4) return false;
    if (a > 255 || b > 255 || c > 255 || d > 255) return false;
    *out = (a << 24) | (b << 16) | (c << 8) | d;
    return true;
}

/* cacheFault (-23042) isn't really an "error" here - it's the DNR's normal
   "not in the local cache" signal, in two different spots, both confirmed
   against a real, historically-used implementation (Tcl's tclMacSock.c
   GetHostFromString) rather than assumed:
     1. As StrToAddr's own immediate return value: the lookup wasn't
        cached, so a real query was just started asynchronously - wait for
        the callback, same as TCPiopb's inProgress/poll pattern elsewhere
        in this app, just callback-driven instead of field-driven here.
     2. As the *completed* hostInfo.rtnCode, after the callback already
        fired: still not resolved - the resolver wants a second StrToAddr
        call (this looks like it reflects a real two-phase lookup - e.g.
        finding then querying an authoritative server - not a bug to work
        around, just how the DNR documents its own contract). Matching the
        reference, this is retried at most once more before giving up. */
OSErr DNR_Resolve(const char *hostName, ip_addr *outAddr, GiveTimeProc giveTime, Boolean *cancel)
{
    /* Heap-allocated, not a stack local - both this struct's `done` flag
       and the `hi` inside it (see ResolveState's own comment) have to
       survive even if this function returns before the DNR callback
       actually fires, which is now possible (kResolveWatchdogTicks below),
       not just when cancel does. A stack local stopped being safe the
       moment ANY early return became possible while the callback might
       still come later - already fixed once for cancel (see the history
       below), and the same fix has to cover the new watchdog case too. */
    ResolveState *state;
    StrToAddrProcPtr strToAddrProc;
    OSErr err;
    short attempt;

    if (TryParseDottedIP(hostName, outAddr)) return noErr;

    if (gDNRProc == NULL) {
        err = DNR_Open();
        if (err != noErr) return err;
    }

    state = (ResolveState *)NewPtr(sizeof(ResolveState));
    if (state == NULL) return memFullErr;

    strToAddrProc = (StrToAddrProcPtr)gDNRProc;

    for (attempt = 0; attempt < 2; attempt++) {
        unsigned long deadline = TickCount() + kResolveWatchdogTicks;
        state->done = false;
        err = strToAddrProc(kSelStrToAddr, (char *)hostName, &state->hi, ResolveCallback, (Ptr)state);

        if (err == cacheFault) {
            /* Not cached - a real query is running asynchronously; the
               callback (and nothing else) will set state->done. Waiting
               here unconditionally on noErr too would hang forever, since
               an immediate noErr means it was answered synchronously
               (e.g. a cache hit) and the callback may never fire at all -
               matching the reference exactly on this point.

               Real bug fixed here, found while auditing for the same
               stack-safety hazard net.c's Net_Abort/Net_Close already had
               to be written around: this used to return userCanceledErr
               immediately on cancel, abandoning the wait - but `state` was
               a stack-local ResolveState then, and the DNR code resource's
               callback (ResolveCallback) still fires later, writing into
               it, regardless of what the caller does. Bailing out early
               let it write into a stack slot that no longer belonged to
               this call by the time it fired. This still waits for the
               real completion on a cancel (giveTime-only, cancel-blind,
               same pattern as DoAbortCall) and only reports the
               cancellation to the caller afterward.

               Second real gap, found by code review, not reproduced live
               the way net.c's matching TCPActiveOpen case was: nothing
               here bounded a DNR resolution that never completes at all
               (an unresponsive/unreachable name server, the same class of
               failure net.c's own comment describes for TCPActiveOpen).
               kResolveWatchdogTicks is that bound - and *unlike* cancel,
               this genuinely cannot wait for the real completion first,
               since the whole point is "this may never actually
               complete." Now that state is heap-allocated rather than a
               stack local, bailing out here is safe either way: on a
               real timeout, this deliberately leaks the block (the
               callback may still fire into it at some arbitrary later
               point - freeing it first would just reintroduce the exact
               hazard being fixed) rather than risk that write landing in
               memory reused for something else. Should be rare - it only
               happens when DNR resolution itself is stuck, at which point
               something is already badly wrong on the guest. */
            Boolean wasCanceled = false;
            for (;;) {
                if (state->done) break;
                if (cancel != NULL && *cancel) wasCanceled = true;
                if (TickCount() >= deadline) return commandTimeout; /* leaks state - see above */
                if (giveTime != NULL) giveTime();
            }
            if (wasCanceled) { DisposePtr((Ptr)state); return userCanceledErr; }
        } else if (err != noErr) {
            DisposePtr((Ptr)state);
            return err; /* a real, immediate failure */
        }

        if (state->hi.rtnCode != cacheFault) break; /* real answer or real error - done */
    }

    if (state->hi.rtnCode != noErr) {
        OSErr rtnCode = (OSErr)state->hi.rtnCode;
        DisposePtr((Ptr)state);
        return rtnCode;
    }

    *outAddr = state->hi.addr[0];
    DisposePtr((Ptr)state);
    return noErr;
}
