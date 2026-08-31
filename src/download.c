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

/* Truncates to HFS's 31-character filename limit while KEEPING the
   extension, by cutting the stem instead of the tail. Real bug fixed
   here: this used to just chop at 31 characters, and since
   GuessTypeCreator runs on the sanitized result, any remote file whose
   basename was longer than that lost the very ".sit"/".img"/".hqx" the
   type/creator lookup depends on - so it fell through to the generic
   default and landed on disk as something double-clicking couldn't
   open. A real-world case from this catalog: a 34-character
   "..._Full_Install.sit" became "..._Full_Instal" and was typed as a
   generic document rather than a StuffIt archive. Long names are common
   on the mirror, so this was not a corner case. */
static void SanitizeName(const char *src, char *dst, short dstSize)
{
    short len = (short)strlen(src);
    const char *dot = (len > 31) ? strrchr(src, '.') : NULL;
    short extLen = 0;
    short stemLen, i, j = 0;

    if (dot != NULL) {
        extLen = (short)strlen(dot);
        /* Only treat it as an extension worth preserving if it's a
           plausible length and isn't the whole name (a leading-dot name
           has no stem to shorten). */
        if (extLen > 8 || extLen >= len) extLen = 0;
    }

    stemLen = (len > 31) ? (short)(31 - extLen) : len;
    if (stemLen < 1) stemLen = 1;

    for (i = 0; i < stemLen && j < dstSize - 1; i++)
        dst[j++] = (src[i] == ':') ? '-' : src[i]; /* ':' is HFS's path separator */
    for (i = 0; i < extLen && j < dstSize - 1; i++)
        dst[j++] = (dot[i] == ':') ? '-' : dot[i];
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
        if (EqualsCI(ext, ".img") || EqualsCI(ext, ".dsk") || EqualsCI(ext, ".image")) { *outType = 'rohd'; *outCreator = 'ddsk'; return; } /* ddsk, not dCpy - see README Gotchas on Garden.img.bin. .image is an older, less common alias for the same raw-disk-image category as .img/.dsk. */
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

    /* Verify we actually received everything the server said was there.
       Real bug, found by checking downloaded files on disk rather than
       trusting the app's own success alert: FTP_Retrieve reports noErr
       whenever the data connection closes, and cannot distinguish "the
       transfer finished" from "the connection dropped early" - so a
       truncated or completely empty transfer was being reported as a
       successful download, the partial file was kept, and the user was
       told it had been saved. This was not hypothetical: a test run left
       6 of 22 files in the downloads folder at 0 bytes, every one of
       them announced as saved, including files the server serves
       perfectly well (confirmed independently with curl). SIZE already
       told us the expected length and bytesSoFar already counted what we
       wrote - nothing was comparing them. Treat a short transfer as the
       failure it is and let the FSpDelete below clean up, rather than
       leaving a corrupt file that looks fine in the Finder. eofErr is
       the honest code: the data ended before it should have.

       Deliberately only the zero-byte case, not a full bytesSoFar ==
       size comparison. Zero bytes is unambiguous: FTP_Retrieve already
       required a 150/125 reply before reading anything, so a RETR the
       server accepted and then delivered nothing for is never a real
       download, and rejecting it cannot cost a good file. An exact
       length match is a stronger check but a riskier one to turn on
       without first confirming that SIZE always agrees byte-for-byte
       with what a TYPE I transfer actually delivers on this server -
       if it ever disagreed, good downloads would start being thrown
       away. Worth revisiting deliberately rather than assuming.

       NOTE: this guard does NOT explain, and does not fix, the
       intermittent zero-length downloads seen while testing - see the
       open item in the README. It only ensures that if a transfer does
       come back empty, the app says so instead of reporting success. */
    if (err == noErr && ctx.bytesSoFar == 0)
        err = eofErr;

    {
        /* Any failure here - a timeout, a dropped connection, a real
           protocol error, or the user canceling (which itself surfaces
           as a non-noErr err from FTP_Retrieve) - means this connection
           has already proven itself unreliable. Always hard-abort the
           disconnect in that case rather than attempting a graceful QUIT
           that could itself sit waiting on the same unresponsive remote
           for its own close timeout - "the download failed" shouldn't
           then also take another 20 seconds to actually let go. Only a
           fully successful transfer gets the polite goodbye. */
        Boolean disconnectHard = (Boolean)(err != noErr);
        FTP_Disconnect(&session, giveTime, &disconnectHard);
    }
    FSClose(refNum);

    if (err != noErr) FSpDelete(&spec); /* don't leave a partial/corrupt file behind */

    return err;
}
