#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "catalog.h"

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
    for (i = 0; i < kCatalogEntryCount && count < maxOut; i++) {
        if (gCatalogEntries[i].category == categoryIndex)
            outIndices[count++] = i;
    }
    return count;
}

short Catalog_Search(const char *query, short *outIndices, short maxOut)
{
    short i, count = 0;
    if (query[0] == 0)
        return 0;
    for (i = 0; i < kCatalogEntryCount && count < maxOut; i++) {
        if (ContainsCI(gCatalogEntries[i].title, query) ||
            ContainsCI(gCatalogEntries[i].description, query))
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
