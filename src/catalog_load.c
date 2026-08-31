#include <string.h>
#include <Files.h>
#include <Memory.h>

#include "catalog.h"
#include "native.h"

/* Binary format for a loadable "Garden Catalog" file - see
   tools/build_catalog.py, which is the only other thing that needs to
   agree with this layout. Every multi-byte field is big-endian, which
   happens to be 68k's own native byte order, so nothing here ever
   byte-swaps - it just reads the bytes in the order they already are.

   header (8 bytes):
     0-3  magic 'GCAT'
     4-5  format version (UInt16) - currently 2
     6-7  entry count (UInt16)

   then `entry count` fixed-size records, kEntryDiskSize bytes each:
     0-1                                category index (UInt16)
     2-3                                release year (UInt16)
     4                                  arch: 0=68k, 1=PPC, 2=Fat (1 byte)
     5-6                                minSystem: major*10+minor, 0=unknown (UInt16)
     7..7+kCatTitleLen-1                title, NUL-padded
     +kCatDescLen                       description, NUL-padded
     +kCatPathLen                       remotePath, NUL-padded
     +4                                 sizeBytes (UInt32)

   Version bumped 1->2 to add minSystem - the loader below rejects any
   file whose version doesn't match exactly (see the version check in
   Catalog_Load), so an old-format file just falls back to the compiled-in
   default rather than being misread field-by-field. */

#define kCatalogMagic ((unsigned long)0x47434154UL) /* 'GCAT' */
#define kCatalogVersion 2
#define kCatalogFileName "Garden Catalog"
#define kHeaderDiskSize 8
#define kEntryDiskSize (2 + 2 + 1 + 2 + kCatTitleLen + kCatDescLen + kCatPathLen + 4)

/* The heap buffer behind gCatalogEntries when it's pointing at a loaded
   file's data (NULL when using the compiled-in default directly - see
   UseDefaults). Tracked here, not just left for the caller to manage,
   so a load can safely replace an earlier one (freeing it first) -
   Catalog_Load only actually runs once per launch today, but nothing
   about this module should silently leak if that ever changes. */
static CatalogEntry *gLoadedBuffer = NULL;

/* Points gCatalogEntries directly at the compiled-in default array - no
   copy, no allocation. This is the common case now (the floppy image no
   longer bundles a separate "Garden Catalog" file - see the README), and
   avoiding a copy here is exactly what keeps this app's static memory
   footprint from including the same ~1.3MB of catalog data twice (real
   bug, found live - see catalog.h's comment on gCatalogEntries). */
static void UseDefaults(void)
{
    if (gLoadedBuffer != NULL) {
        DisposePtr((Ptr)gLoadedBuffer);
        gLoadedBuffer = NULL;
    }
    gCatalogEntries = gDefaultCatalogEntries;
    gCatalogEntryCount = kDefaultCatalogEntryCount;
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
    CatalogEntry *buffer;

    if (Native_GetAppFolder(&vRefNum, &dirID) != noErr) {
        UseDefaults();
        return kCatalogLoadedDefault;
    }

    CToPascal(kCatalogFileName, pname);
    if (FSMakeFSSpec(vRefNum, dirID, pname, &spec) != noErr) {
        UseDefaults(); /* fnfErr - no catalog file - the ordinary case */
        return kCatalogLoadedDefault;
    }

    if (FSpOpenDF(&spec, fsRdPerm, &refNum) != noErr) {
        UseDefaults();
        return kCatalogLoadRejected; /* the FSSpec resolved, so something's odd - worth a note */
    }

    got = kHeaderDiskSize;
    err = FSRead(refNum, &got, header);
    if (err != noErr || got != kHeaderDiskSize ||
        ReadU32(header) != kCatalogMagic || ReadU16(header + 4) != kCatalogVersion) {
        FSClose(refNum);
        UseDefaults();
        return kCatalogLoadRejected;
    }

    entryCount = (short)ReadU16(header + 6);
    if (entryCount <= 0 || entryCount > kMaxCatalogEntries) {
        FSClose(refNum);
        UseDefaults();
        return kCatalogLoadRejected;
    }

    /* Sized to this file's own real entry count, not kMaxCatalogEntries -
       that constant is now just a sanity ceiling (bounds how big a
       claimed entry count is allowed to make this allocation), not a
       fixed static array size - see catalog.h. */
    buffer = (CatalogEntry *)NewPtr((Size)sizeof(CatalogEntry) * (Size)entryCount);
    if (buffer == NULL) {
        FSClose(refNum);
        UseDefaults();
        return kCatalogLoadRejected;
    }

    for (i = 0; i < entryCount; i++) {
        CatalogEntry *e;
        short off;

        got = kEntryDiskSize;
        err = FSRead(refNum, &got, entryBuf);
        if (err != noErr || got != kEntryDiskSize) {
            FSClose(refNum);
            DisposePtr((Ptr)buffer);
            UseDefaults();
            return kCatalogLoadRejected;
        }

        e = &buffer[i];
        off = 0;
        e->category  = (short)ReadU16(entryBuf + off); off = (short)(off + 2);
        e->year      = (short)ReadU16(entryBuf + off); off = (short)(off + 2);
        e->arch      = entryBuf[off];                  off = (short)(off + 1);
        e->minSystem = (short)ReadU16(entryBuf + off); off = (short)(off + 2);
        if (e->category < 0 || e->category >= kCategoryCount) e->category = 0;
        if (e->arch != kArch68k && e->arch != kArchPPC && e->arch != kArchFat) e->arch = kArch68k;
        if (e->minSystem < 0) e->minSystem = 0;

        CopyFixedField(entryBuf + off, kCatTitleLen, e->title, sizeof(e->title));
        off = (short)(off + kCatTitleLen);
        CopyFixedField(entryBuf + off, kCatDescLen, e->description, sizeof(e->description));
        off = (short)(off + kCatDescLen);
        CopyFixedField(entryBuf + off, kCatPathLen, e->remotePath, sizeof(e->remotePath));
        off = (short)(off + kCatPathLen);
        e->sizeBytes = ReadU32(entryBuf + off);
    }

    FSClose(refNum);

    if (gLoadedBuffer != NULL) DisposePtr((Ptr)gLoadedBuffer);
    gLoadedBuffer = buffer;
    gCatalogEntries = buffer;
    gCatalogEntryCount = entryCount;
    return kCatalogLoadedFromFile;
}
