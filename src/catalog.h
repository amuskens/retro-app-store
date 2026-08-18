#ifndef CATALOG_H
#define CATALOG_H

/* The app's own idea of "categories" - Macintosh Garden's live FTP mirror
   is an unsorted flat dump (no server-side folders to browse), so this is
   a catalog the app carries itself, not something read off the server.
   See catalog_data.c and the README for what's real vs. sample data. */

typedef struct {
    const char *title;
} Category;

typedef struct {
    short category;           /* index into gCategories */
    const char *title;
    const char *description;  /* one line, shown under the title in a row */
    const char *remotePath;   /* best-effort path for FTP RETR - see README */
    unsigned long sizeBytes;
} CatalogEntry;

extern const Category gCategories[];
extern const short kCategoryCount;

extern const CatalogEntry gCatalogEntries[];
extern const short kCatalogEntryCount;

/* Sidebar shows the real categories plus one trailing "Live FTP Browse"
   row, handled specially (backed by a live NLST, not catalog data) rather
   than as a Category entry - this is that row's sidebar index. */
#define kLiveBrowseRowIndex kCategoryCount

#define kMaxFilterResults 256

/* Both fill outIndices (indices into gCatalogEntries) up to maxOut and
   return the match count. Search matches substrings in title or
   description, case-insensitively. */
short Catalog_FilterByCategory(short categoryIndex, short *outIndices, short maxOut);
short Catalog_Search(const char *query, short *outIndices, short maxOut);

/* Formats bytes as e.g. "340 K" or "1.2 MB" into buf. */
void Catalog_FormatSize(unsigned long bytes, char *buf, short bufSize);

#endif
