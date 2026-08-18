#ifndef NATIVE_H
#define NATIVE_H

#include <Quickdraw.h>

/* Small platform-glue helpers shared across every UI module - mainly the
   C-string/Pascal-string bridging that classic Toolbox calls (DrawString,
   StringWidth, ...) require but C string literals don't naturally have. */

void CToPascal(const char *src, Str255 dst);
void PascalToC(const unsigned char *src, char *dst, short dstSize);

/* Draws src (a plain C string) at the current pen position via DrawString. */
void DrawCString(const char *src);

/* Width in pixels src would draw at, in the port's current font/size/face. */
short CStringWidth(const char *src);

/* Draws src left-aligned in r, vertically centered on r using the current
   font's ascent/descent (the common case for list rows and buttons), and
   clips to r first, so callers don't need font metrics of their own to
   avoid overrunning neighbouring rows. */
void DrawCStringInRect(const char *src, const Rect *r);

/* Truncates a copy of src (into buf, capacity bufSize) with a trailing
   ellipsis so it fits within maxWidth pixels in the port's current font -
   used for list rows, where titles/descriptions are arbitrary length but
   the row layout is fixed. Never truncates below "...". */
void TruncateCStringToWidth(const char *src, char *buf, short bufSize, short maxWidth);

/* Resolves the folder the running application itself lives in, via the
   Process Manager - the standard System 7+ way for an app to find its own
   location without relying on a hardcoded path or the current working
   directory (which the classic Mac OS doesn't really have). Shared by
   download.c (the "Garden Downloads" folder is a sibling of the app) and
   catalog_load.c (the loadable "Garden Catalog" file is too). */
OSErr Native_GetAppFolder(short *outVRefNum, long *outDirID);

#endif
