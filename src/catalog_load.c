#include <string.h>
#include <Files.h>

#include "catalog.h"
#include "native.h"

/* Binary format for a loadable "Garden Catalog" file - see
   tools/build_catalog.py, which is the only other thing that needs to
   agree with this layout. Every multi-byte field is big-endian, which
   happens to be 68k's own native byte order, so nothing here ever
   byte-swaps - it just reads the bytes in the order they already are.

   header (8 bytes):
     0-3  magic 'GCAT'
     4-5  format version (UInt16) - currently 1
     6-7  entry count (UInt16)

   then `entry count` fixed-size records, kEntryDiskSize bytes each:
     0-1                                category index (UInt16)
     2-3                                release year (UInt16)
     4                                  arch: 0=68k, 1=PPC, 2=Fat (1 byte)
     5..5+kCatTitleLen-1                title, NUL-padded
     +kCatDescLen                       description, NUL-padded
     +kCatPathLen                       remotePath, NUL-padded
     +4                                 sizeBytes (UInt32) */

#define kCatalogMagic ((unsigned long)0x47434154UL) /* 'GCAT' */
#define kCatalogVersion 1
#define kCatalogFileName "Garden Catalog"
#define kHeaderDiskSize 8
#define kEntryDiskSize (2 + 2 + 1 + kCatTitleLen + kCatDescLen + kCatPathLen + 4)

static void CopyDefaults(void)
{
    short i, n;
    n = kDefaultCatalogEntryCount;
    if (n > kMaxCatalogEntries) n = kMaxCatalogEntries;
    for (i = 0; i < n; i++)
        gCatalogEntries[i] = gDefaultCatalogEntries[i];
    gCatalogEntryCount = n;
}

static unsigned short ReadU16(const unsigned char *buf)
{
    return (unsigned short)(((unsigned short)buf[0] << 8) | (unsigned short)buf[1]);
}

static unsigned long ReadU32(const unsigned char *buf)
{
    return ((unsigned long)buf[0] << 24) | ((unsigned long)buf[1] << 16) |
           ((unsigned long)buf[2] << 8) | (unsigned long)buf[3];
}

/* Copies up to len bytes from a fixed, possibly-not-NUL-terminated disk
   field into dst (capacity dstSize), then forces a NUL within dst
   regardless of what the file actually contained - a corrupt or
   maliciously-crafted catalog file should never be able to hand a later
   strlen/strcpy an unterminated buffer. */
static void CopyFixedField(const unsigned char *src, short len, char *dst, short dstSize)
{
    short n = len;
    if (n > dstSize - 1) n = (short)(dstSize - 1);
    BlockMove((Ptr)src, dst, n);
    dst[n] = 0;
}

CatalogLoadResult Catalog_Load(void)
{
    short vRefNum;
    long dirID;
    Str255 pname;
    FSSpec spec;
    short refNum;
    OSErr err;
    unsigned char header[kHeaderDiskSize];
    long got;
    short entryCount, i;
    unsigned char entryBuf[kEntryDiskSize];

    if (Native_GetAppFolder(&vRefNum, &dirID) != noErr) {
        CopyDefaults();
        return kCatalogLoadedDefault;
    }

    CToPascal(kCatalogFileName, pname);
    if (FSMakeFSSpec(vRefNum, dirID, pname, &spec) != noErr) {
        CopyDefaults(); /* fnfErr - no catalog file - the ordinary case */
        return kCatalogLoadedDefault;
    }

    if (FSpOpenDF(&spec, fsRdPerm, &refNum) != noErr) {
        CopyDefaults();
        return kCatalogLoadRejected; /* the FSSpec resolved, so something's odd - worth a note */
    }

    got = kHeaderDiskSize;
    err = FSRead(refNum, &got, header);
    if (err != noErr || got != kHeaderDiskSize ||
        ReadU32(header) != kCatalogMagic || ReadU16(header + 4) != kCatalogVersion) {
        FSClose(refNum);
        CopyDefaults();
        return kCatalogLoadRejected;
    }

    entryCount = (short)ReadU16(header + 6);
    if (entryCount <= 0 || entryCount > kMaxCatalogEntries) {
        FSClose(refNum);
        CopyDefaults();
        return kCatalogLoadRejected;
    }

    for (i = 0; i < entryCount; i++) {
        CatalogEntry *e;
        short off;

        got = kEntryDiskSize;
        err = FSRead(refNum, &got, entryBuf);
        if (err != noErr || got != kEntryDiskSize) {
            FSClose(refNum);
            CopyDefaults();
            return kCatalogLoadRejected;
        }

        e = &gCatalogEntries[i];
        off = 0;
        e->category = (short)ReadU16(entryBuf + off); off = (short)(off + 2);
        e->year     = (short)ReadU16(entryBuf + off); off = (short)(off + 2);
        e->arch     = entryBuf[off];                  off = (short)(off + 1);
        if (e->category < 0 || e->category >= kCategoryCount) e->category = 0;
        if (e->arch != kArch68k && e->arch != kArchPPC && e->arch != kArchFat) e->arch = kArch68k;

        CopyFixedField(entryBuf + off, kCatTitleLen, e->title, sizeof(e->title));
        off = (short)(off + kCatTitleLen);
        CopyFixedField(entryBuf + off, kCatDescLen, e->description, sizeof(e->description));
        off = (short)(off + kCatDescLen);
        CopyFixedField(entryBuf + off, kCatPathLen, e->remotePath, sizeof(e->remotePath));
        off = (short)(off + kCatPathLen);
        e->sizeBytes = ReadU32(entryBuf + off);
    }

    FSClose(refNum);
    gCatalogEntryCount = entryCount;
    return kCatalogLoadedFromFile;
}
