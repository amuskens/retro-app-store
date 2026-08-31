#ifndef CATALOG_H
#define CATALOG_H

#include <Quickdraw.h> /* Byte, Boolean */

/* The app's own idea of "categories" - Macintosh Garden's live FTP mirror
   is an unsorted flat dump (no server-side folders to browse), so this is
   a catalog the app carries itself, not something read off the server.
   See catalog_data.c and the README for what's real vs. sample data. */

typedef struct {
    const char *title;
} Category;

/* Fixed-size fields, not const char* - the active catalog can come from
   Catalog_Load()'s binary file at runtime as well as the compiled-in
   default array, so entries need real storage, not just pointers into the
   data segment. Sized generously above the largest field in the bundled
   default set (see tools/build_catalog.py, which enforces the same
   limits when packing a custom catalog file). */
#define kCatTitleLen 48
#define kCatDescLen  110
#define kCatPathLen  100

typedef enum {
    kArch68k = 0,  /* 68k only - the common case for pre-PowerMac software */
    kArchPPC  = 1, /* PowerPC only - won't run on a plain 68k Mac at all */
    kArchFat  = 2  /* "fat"/universal binary - runs natively on either */
} CatalogArch;

typedef struct {
    short category;               /* index into gCategories */
    short year;                   /* release year, for the Year filter */
    Byte arch;                    /* CatalogArch, for the CPU filter */
    short minSystem;              /* minimum required System version, as
                                      (major*10 + minor) - e.g. 70 for
                                      System 7.0, 75 for System 7.5, 80 for
                                      Mac OS 8.0. 0 means unknown/not
                                      curated yet. Sourced from Macintosh
                                      Garden's own per-title pages (the
                                      "For System X.x - Y.y" line), not
                                      guessed - see README. For the System
                                      filter, only the lower bound matters:
                                      older software keeps running on newer
                                      systems, so this is "will it run on
                                      my system", not an exact range. */
    char title[kCatTitleLen];
    char description[kCatDescLen]; /* one line, shown under the title in a row */
    char remotePath[kCatPathLen];  /* path for FTP RETR, verified against a
                                       real server listing except where
                                       marked UNVERIFIED - see README */
    unsigned long sizeBytes;
} CatalogEntry;

extern const Category gCategories[];
extern const short kCategoryCount;

/* The active catalog - populated once at startup by Catalog_Load() from
   either a loadable "Garden Catalog" file next to the app or, failing
   that, the compiled-in gDefaultCatalogEntries (catalog_data.c). Nothing
   outside catalog.c/catalog_load.c should need to know which source it
   actually came from - both end up in the same shape here.

   A pointer, not a fixed-size array - real memory bug found and fixed by
   live testing (not just inspection): this used to be a real, always-
   allocated `CatalogEntry gCatalogEntries[kMaxCatalogEntries]` static
   array, separate from and in addition to the compiled-in
   gDefaultCatalogEntries, because Catalog_Load() populated it by copying
   the default array in (or reading a file into it) rather than pointing
   at the default directly. At this catalog's size (2,445 entries * 270
   measured bytes each), that meant ~1.3MB of static data existing
   simultaneously for what, in the common case (no custom "Garden
   Catalog" file - the default since the floppy image stopped bundling
   one), is the exact same data twice. Raising the app's SIZE resource to
   account for that footprint (rather than fixing the footprint) was
   verified LIVE to cause real Open Transport/TCP-IP initialization
   failures on a realistic memory-constrained configuration (8MB total
   RAM, matching what this whole project's own emulator testing has used
   throughout) - a much worse failure mode (networking broken entirely)
   than the problem being solved. Now this just points at
   gDefaultCatalogEntries directly in the common case (no copy, no extra
   allocation at all) and at a heap buffer sized to the actual loaded
   file's real entry count (not kMaxCatalogEntries) in the file-loaded
   case - see catalog_load.c. */
extern const CatalogEntry *gCatalogEntries;
extern short gCatalogEntryCount;
#define kMaxCatalogEntries 2500 /* sanity cap on a *loaded file's* claimed entry count (bounds catalog_load.c's heap allocation against a corrupt/malicious file) - no longer a static array size, so raising this doesn't cost any memory by itself. tools/build_catalog.py's MAX_ENTRIES has to agree. */

/* The compiled-in fallback data, always present regardless of whether a
   loadable catalog file was found - see catalog_data.c. */
extern const CatalogEntry gDefaultCatalogEntries[];
extern const short kDefaultCatalogEntryCount;

typedef enum {
    kCatalogLoadedFromFile,   /* "Garden Catalog" found next to the app, valid, loaded */
    kCatalogLoadedDefault,    /* no such file - the ordinary/expected case, not a problem */
    kCatalogLoadRejected      /* the file existed but failed validation - default used instead */
} CatalogLoadResult;

/* Locates "Garden Catalog" next to the app and loads it into
   gCatalogEntries/gCatalogEntryCount if present and valid; otherwise (not
   found, or found but fails validation) copies gDefaultCatalogEntries in
   instead. Call once at startup, before the first category is shown.
   Deliberately has no UI of its own (no alerts) - app.c decides what, if
   anything, to tell the user based on the result, same separation ftp.c/
   net.c already keep from app.c's error messages. */
CatalogLoadResult Catalog_Load(void);

/* Sidebar shows an "All" row, then the real categories, then one trailing
   "Live FTP Browse" row (handled specially - backed by a live NLST, not
   catalog data - rather than as a Category entry). "All" isn't a real
   gCategories entry either - it's this sentinel, meaning "don't filter by
   category" - passed to Catalog_FilterByCategory/Catalog_Search the same
   way a real category index is. */
#define kAllCategoryIndex ((short)-1)
#define kLiveBrowseRowIndex kCategoryCount

#define kMaxFilterResults kMaxCatalogEntries /* the "All" category/a broad search can match every entry in a ~1500-item catalog - this has to be able to hold all of them, not truncate silently */

typedef enum {
    kYearFilterAny = 0,
    kYearFilterPre1990,
    kYearFilter1990to1993,
    kYearFilter1994to1996,
    kYearFilter1997Plus
} CatalogYearFilter;

typedef enum {
    kArchFilterAny = 0,
    kArchFilter68k, /* 68k-capable: kArch68k or kArchFat entries */
    kArchFilterPPC  /* PPC-capable: kArchPPC or kArchFat entries */
} CatalogArchFilter;

typedef enum {
    kSysFilterAny = 0,
    kSysFilterSystem6,    /* minSystem 0 (unknown) or < 70 - runs on System 6.x up */
    kSysFilterSystem7,    /* minSystem 70-79 - needs System 7 */
    kSysFilterSystem8Plus /* minSystem >= 80 - needs Mac OS 8 or later */
} CatalogSysFilter;

/* Year/CPU/System filters apply on top of whatever category or search is
   active - set once from the sidebar's pill menus, read back by
   Catalog_FilterByCategory/Catalog_Search on every call so the results
   list stays consistent as the user changes categories or searches
   without having to re-pick a filter. */
void Catalog_SetYearFilter(CatalogYearFilter f);
void Catalog_SetArchFilter(CatalogArchFilter f);
void Catalog_SetSysFilter(CatalogSysFilter f);
CatalogYearFilter Catalog_GetYearFilter(void);
CatalogArchFilter Catalog_GetArchFilter(void);
CatalogSysFilter Catalog_GetSysFilter(void);
const char *Catalog_YearFilterLabel(CatalogYearFilter f);
const char *Catalog_ArchFilterLabel(CatalogArchFilter f);
const char *Catalog_SysFilterLabel(CatalogSysFilter f);

/* Both fill outIndices (indices into gCatalogEntries) up to maxOut and
   return the match count. Search matches substrings anywhere in the title
   or description, case-insensitively (plain strstr, not just whole-word)
   - and, like category browsing, only within categoryIndex unless it's
   kAllCategoryIndex, in which case the whole catalog is searched. Both
   also apply the current Year/CPU/System filters (see above) regardless
   of category. */
short Catalog_FilterByCategory(short categoryIndex, short *outIndices, short maxOut);
short Catalog_Search(const char *query, short categoryIndex, short *outIndices, short maxOut);

/* Formats bytes as e.g. "340 K" or "1.2 MB" into buf. */
void Catalog_FormatSize(unsigned long bytes, char *buf, short bufSize);

#endif
