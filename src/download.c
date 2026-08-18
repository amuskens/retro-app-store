#include <string.h>
#include <ctype.h>
#include <Files.h>
#include <Processes.h>

#include "download.h"
#include "native.h"

typedef struct {
    short fileRefNum;
    unsigned long bytesSoFar;
    unsigned long totalBytes;
    Boolean totalKnown;
    ProgressProc onProgress;
    void *progressUserData;
    OSErr writeErr;
} ChunkContext;

static const char *BaseName(const char *path)
{
    const char *slash = strrchr(path, '/');
    return (slash != NULL) ? slash + 1 : path;
}

static void SanitizeName(const char *src, char *dst, short dstSize)
{
    short len = (short)strlen(src);
    short i, j = 0;
    if (len > 31) len = 31; /* classic HFS filename limit */
    for (i = 0; i < len && j < dstSize - 1; i++)
        dst[j++] = (src[i] == ':') ? '-' : src[i]; /* ':' is HFS's path separator */
    dst[j] = 0;
}

static Boolean EqualsCI(const char *a, const char *b)
{
    while (*a != 0 && *b != 0) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return false;
        a++;
        b++;
    }
    return (Boolean)(*a == 0 && *b == 0);
}

/* Best-effort only - this app never decodes StuffIt/BinHex/disk-image
   contents itself (see the README's Known Limitations), it just labels
   the raw downloaded bytes so Finder routes a double-click to a real
   expander app to take over, same as any FTP/web download always has.
   Creator codes cross-checked against real historical references rather
   than guessed (see README) - SITx (StuffIt Expander) rather than SIT!
   (the full StuffIt compressor) is the deliberate choice for every
   compressed/encoded format below: Expander is the ubiquitous free tool
   that actually auto-detects and unpacks .sit/.hqx/.bin/.sea/.zip alike,
   where the full StuffIt app usually isn't installed at all. Two real
   gaps this can't paper over, called out here rather than left silent:
   .dmg is a Mac OS 9/X-era format with no mounting tool on System 7 at
   all (not the same thing as classic DiskCopy's .img/.dsk despite the
   "disk image" family resemblance), and .pdf has no viewer on System 7
   either - both download fine, neither can actually be opened once
   there. */
static void GuessTypeCreator(const char *name, OSType *outType, OSType *outCreator)
{
    short len = (short)strlen(name);
    const char *ext = NULL;
    short i;

    for (i = (short)(len - 1); i >= 0; i--) {
        if (name[i] == '.') { ext = &name[i]; break; }
    }

    if (ext != NULL) {
        if (EqualsCI(ext, ".sit"))  { *outType = 'SIT!'; *outCreator = 'SITx'; return; }
        if (EqualsCI(ext, ".hqx"))  { *outType = 'TEXT'; *outCreator = 'SITx'; return; }
        if (EqualsCI(ext, ".bin"))  { *outType = 'BINA'; *outCreator = 'SITx'; return; } /* MacBinary */
        if (EqualsCI(ext, ".zip"))  { *outType = 'ZIP ';  *outCreator = 'SITx'; return; } /* Expander 5.5+ */
        if (EqualsCI(ext, ".sea"))  { *outType = 'APPL'; *outCreator = '????'; return; } /* self-extracting - launches itself */
        if (EqualsCI(ext, ".cpt"))  { *outType = 'CPCT'; *outCreator = 'CPCT'; return; } /* Compact Pro */
        if (EqualsCI(ext, ".img") || EqualsCI(ext, ".dsk")) { *outType = 'rohd'; *outCreator = 'dCpy'; return; }
        if (EqualsCI(ext, ".txt"))  { *outType = 'TEXT'; *outCreator = 'ttxt'; return; }
    }
    /* Unrecognized extension (includes .dmg/.pdf, and anything else not
       listed above): still worth pointing at Expander rather than leaving
       creator blank - it auto-detects a wide range of formats by content,
       not just by extension, so this is a real improvement over '????'
       even when the specific format isn't one of the cases above. */
    *outType = 'BINA';
    *outCreator = 'SITx';
}

/* Resolves (creating if needed) a "Garden Downloads" folder as a sibling
   of the running application - see Native_GetAppFolder. */
static OSErr GetOrCreateDownloadsFolder(short *outVRefNum, long *outDirID)
{
    short vRefNum;
    long parID;
    FSSpec folderSpec;
    OSErr err;
    long newDirID;
    CInfoPBRec cpb;
    Str255 folderName;

    err = Native_GetAppFolder(&vRefNum, &parID);
    if (err != noErr) return err;

    CToPascal("Garden Downloads", folderName);

    err = FSMakeFSSpec(vRefNum, parID, folderName, &folderSpec);
    if (err != noErr && err != fnfErr) return err;

    err = FSpDirCreate(&folderSpec, smSystemScript, &newDirID);
    if (err == noErr) {
        *outVRefNum = vRefNum;
        *outDirID = newDirID;
        return noErr;
    }
    if (err != dupFNErr) return err;

    /* Already exists - PBGetCatInfoSync with ioFDirIndex 0 resolves a
       named item directly; for a directory, ioDrDirID comes back as that
       folder's own ID rather than its parent's. */
    memset(&cpb, 0, sizeof(cpb));
    cpb.dirInfo.ioNamePtr = folderName;
    cpb.dirInfo.ioVRefNum = vRefNum;
    cpb.dirInfo.ioDrDirID = parID;
    cpb.dirInfo.ioFDirIndex = 0;
    err = PBGetCatInfoSync(&cpb);
    if (err != noErr) return err;

    *outVRefNum = vRefNum;
    *outDirID = cpb.dirInfo.ioDrDirID;
    return noErr;
}

static void HandleChunk(void *userData, const void *buf, unsigned short len)
{
    ChunkContext *ctx = (ChunkContext *)userData;
    long count = len;
    OSErr err;

    if (ctx->writeErr != noErr) return; /* already failed - drain the rest without writing */

    err = FSWrite(ctx->fileRefNum, &count, (Ptr)buf);
    if (err != noErr) { ctx->writeErr = err; return; }

    ctx->bytesSoFar += len;
    if (ctx->onProgress != NULL)
        ctx->onProgress(ctx->progressUserData, ctx->bytesSoFar, ctx->totalBytes, ctx->totalKnown);
}

OSErr Download_Fetch(const char *host, tcp_port port, const char *user, const char *pass,
                      const char *remotePath,
                      ProgressProc onProgress, void *progressUserData,
                      GiveTimeProc giveTime, Boolean *cancel)
{
    FtpSession session;
    OSErr err;
    short vRefNum;
    long dirID;
    char cleanName[64];
    Str255 pname;
    FSSpec spec;
    short refNum;
    ChunkContext ctx;
    OSType type, creator;
    unsigned long size;
    Boolean sizeKnown;

    err = GetOrCreateDownloadsFolder(&vRefNum, &dirID);
    if (err != noErr) return err;

    SanitizeName(BaseName(remotePath), cleanName, sizeof(cleanName));
    CToPascal(cleanName, pname);

    err = FSMakeFSSpec(vRefNum, dirID, pname, &spec);
    if (err != noErr && err != fnfErr) return err;

    FSpDelete(&spec); /* clear out any partial file left by a previous failed attempt */

    GuessTypeCreator(cleanName, &type, &creator);
    err = FSpCreate(&spec, creator, type, smSystemScript);
    if (err != noErr) return err;

    err = FSpOpenDF(&spec, fsWrPerm, &refNum);
    if (err != noErr) { FSpDelete(&spec); return err; }

    err = FTP_Connect(&session, host, port, user, pass, giveTime, cancel);
    if (err != noErr) { FSClose(refNum); FSpDelete(&spec); return err; }

    sizeKnown = FTP_GetSize(&session, remotePath, &size, giveTime, cancel);
    if (!sizeKnown) size = 0;

    memset(&ctx, 0, sizeof(ctx));
    ctx.fileRefNum = refNum;
    ctx.totalBytes = size;
    ctx.totalKnown = sizeKnown;
    ctx.onProgress = onProgress;
    ctx.progressUserData = progressUserData;

    err = FTP_Retrieve(&session, remotePath, HandleChunk, &ctx, giveTime, cancel);
    if (err == noErr) err = ctx.writeErr;

    FTP_Disconnect(&session, giveTime, cancel);
    FSClose(refNum);

    if (err != noErr) FSpDelete(&spec); /* don't leave a partial/corrupt file behind */

    return err;
}
