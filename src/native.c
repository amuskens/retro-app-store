#include <string.h>
#include <Fonts.h>
#include <Files.h>
#include <Processes.h>

#include "native.h"

void CToPascal(const char *src, Str255 dst)
{
    size_t len = strlen(src);
    if (len > 255) len = 255;
    dst[0] = (unsigned char)len;
    BlockMove(src, &dst[1], (long)len);
}

void PascalToC(const unsigned char *src, char *dst, short dstSize)
{
    short len = src[0];
    if (len > dstSize - 1) len = (short)(dstSize - 1);
    BlockMove((Ptr)&src[1], dst, len);
    dst[len] = 0;
}

void DrawCString(const char *src)
{
    Str255 p;
    CToPascal(src, p);
    DrawString(p);
}

short CStringWidth(const char *src)
{
    Str255 p;
    CToPascal(src, p);
    return StringWidth(p);
}

void DrawCStringInRect(const char *src, const Rect *r)
{
    FontInfo info;
    RgnHandle savedClip;
    short baseline;

    GetFontInfo(&info);
    baseline = (short)(r->top + ((r->bottom - r->top) - (info.ascent + info.descent)) / 2 + info.ascent);

    savedClip = NewRgn();
    GetClip(savedClip);
    ClipRect((Rect *)r); /* legacy header predates const; r is never modified */

    MoveTo(r->left, baseline);
    DrawCString(src);

    SetClip(savedClip);
    DisposeRgn(savedClip);
}

void TruncateCStringToWidth(const char *src, char *buf, short bufSize, short maxWidth)
{
    size_t len = strlen(src);
    short lastFit;

    if (len >= (size_t)bufSize) len = (size_t)bufSize - 1;
    BlockMove(src, buf, (long)len);
    buf[len] = 0;

    if (CStringWidth(buf) <= maxWidth) return;

    /* Shrink until "<prefix>..." fits, same convention as Finder's name
       truncation - never cut below the ellipsis itself. */
    lastFit = 0;
    while (len > 0) {
        len--;
        buf[len] = 0;
        strncat(buf, "...", (size_t)(bufSize - 1 - (short)len));
        if (CStringWidth(buf) <= maxWidth) { lastFit = 1; break; }
        buf[len] = 0; /* undo the "..." append before trying a shorter prefix */
    }
    if (!lastFit) {
        buf[0] = 0;
        strncat(buf, "...", (size_t)(bufSize - 1));
    }
}

OSErr Native_GetAppFolder(short *outVRefNum, long *outDirID)
{
    ProcessSerialNumber psn;
    ProcessInfoRec info;
    FSSpec appSpec;
    OSErr err;

    err = GetCurrentProcess(&psn);
    if (err != noErr) return err;

    memset(&info, 0, sizeof(info));
    info.processInfoLength = sizeof(info);
    info.processName = NULL;
    info.processAppSpec = &appSpec;
    err = GetProcessInformation(&psn, &info);
    if (err != noErr) return err;

    *outVRefNum = appSpec.vRefNum;
    *outDirID = appSpec.parID;
    return noErr;
}
