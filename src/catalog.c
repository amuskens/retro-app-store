#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "catalog.h"

/* The active catalog - see Catalog_Load in catalog_load.c for how this
   gets populated (loaded file or compiled-in default, either way ends up
   here in the same shape). Everything below only ever reads this, never
   gDefaultCatalogEntries directly. */
CatalogEntry gCatalogEntries[kMaxCatalogEntries];
short gCatalogEntryCount = 0;

static CatalogYearFilter gYearFilter = kYearFilterAny;
static CatalogArchFilter gArchFilter = kArchFilterAny;

void Catalog_SetYearFilter(CatalogYearFilter f) { gYearFilter = f; }
void Catalog_SetArchFilter(CatalogArchFilter f) { gArchFilter = f; }
CatalogYearFilter Catalog_GetYearFilter(void) { return gYearFilter; }
CatalogArchFilter Catalog_GetArchFilter(void) { return gArchFilter; }

const char *Catalog_YearFilterLabel(CatalogYearFilter f)
{
    switch (f) {
        case kYearFilterPre1990:    return "Before 1990";
        case kYearFilter1990to1993: return "1990" "\xd1" "1993";
        case kYearFilter1994to1996: return "1994" "\xd1" "1996";
        case kYearFilter1997Plus:   return "1997 or later";
        default:                    return "Any Year";
    }
}

const char *Catalog_ArchFilterLabel(CatalogArchFilter f)
{
    switch (f) {
        case kArchFilter68k: return "68k";
        case kArchFilterPPC: return "PPC";
        default:             return "Any CPU";
    }
}

static Boolean PassesYearFilter(short year)
{
    switch (gYearFilter) {
        case kYearFilterPre1990:    return (Boolean)(year < 1990);
        case kYearFilter1990to1993: return (Boolean)(year >= 1990 && year <= 1993);
        case kYearFilter1994to1996: return (Boolean)(year >= 1994 && year <= 1996);
        case kYearFilter1997Plus:   return (Boolean)(year >= 1997);
        default:                    return true;
    }
}

static Boolean PassesArchFilter(Byte arch)
{
    switch (gArchFilter) {
        case kArchFilter68k: return (Boolean)(arch == kArch68k || arch == kArchFat);
        case kArchFilterPPC: return (Boolean)(arch == kArchPPC || arch == kArchFat);
        default:              return true;
    }
}

static void LowerCopy(const char *src, char *dst, short dstSize)
{
    short i;
    for (i = 0; src[i] != 0 && i < dstSize - 1; i++)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = 0;
}

static Boolean ContainsCI(const char *haystack, const char *needle)
{
    char h[256], n[256];
    LowerCopy(haystack, h, sizeof(h));
    LowerCopy(needle, n, sizeof(n));
    return strstr(h, n) != NULL;
}

short Catalog_FilterByCategory(short categoryIndex, short *outIndices, short maxOut)
{
    short i, count = 0;
    for (i = 0; i < gCatalogEntryCount && count < maxOut; i++) {
        if (gCatalogEntries[i].category == categoryIndex &&
            PassesYearFilter(gCatalogEntries[i].year) &&
            PassesArchFilter(gCatalogEntries[i].arch))
            outIndices[count++] = i;
    }
    return count;
}

short Catalog_Search(const char *query, short *outIndices, short maxOut)
{
    short i, count = 0;
    if (query[0] == 0)
        return 0;
    for (i = 0; i < gCatalogEntryCount && count < maxOut; i++) {
        if ((ContainsCI(gCatalogEntries[i].title, query) ||
             ContainsCI(gCatalogEntries[i].description, query)) &&
            PassesYearFilter(gCatalogEntries[i].year) &&
            PassesArchFilter(gCatalogEntries[i].arch))
            outIndices[count++] = i;
    }
    return count;
}

void Catalog_FormatSize(unsigned long bytes, char *buf, short bufSize)
{
    if (bytes >= 1024UL * 1024UL) {
        unsigned long tenths = (bytes * 10UL) / (1024UL * 1024UL);
        sprintf(buf, "%lu.%lu MB", tenths / 10UL, tenths % 10UL);
    } else if (bytes >= 1024UL) {
        sprintf(buf, "%lu K", (bytes + 512UL) / 1024UL);
    } else {
        sprintf(buf, "%lu bytes", bytes);
    }
    (void)bufSize; /* buf is always sized generously by callers (>=16 bytes) for these formats */
}
