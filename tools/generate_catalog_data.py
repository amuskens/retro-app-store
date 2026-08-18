#!/usr/bin/env python3
"""Regenerates src/catalog_data.c (the compiled-in fallback catalog) from
tools/catalog_source.json - the same JSON source build_catalog.py packs
into a loadable "Garden Catalog" file. Keeping both in sync by hand (367
C struct literals) is exactly the kind of thing that silently drifts, so
this script is the only thing that should ever edit catalog_data.c's
entry table - edit catalog_source.json and re-run this instead.

Usage:
    python3 generate_catalog_data.py                     # catalog_source.json -> ../src/catalog_data.c
    python3 generate_catalog_data.py --input mine.json --output somewhere.c
"""
import json
import re
import sys
import argparse
import os

CATEGORIES = [
    "Featured", "Games", "Utilities", "Graphics & Sound", "Productivity",
    "System Extensions", "Internet & Comm", "Dev Tools",
]
CAT_ENUM_NAMES = [
    "kCatFeatured", "kCatGames", "kCatUtilities", "kCatGraphicsSound",
    "kCatProductivity", "kCatSystemExt", "kCatInternet", "kCatDevTools",
]
ARCH_ENUM_NAMES = {"68k": "kArch68k", "ppc": "kArchPPC", "fat": "kArchFat"}

HEADER = '''#include "catalog.h"

/* Compiled-in fallback catalog - used whenever no loadable "Garden
   Catalog" file is found next to the app, or one is found but fails
   validation (see catalog_load.c). {count} entries, each cross-checked
   against a real, full directory listing of the live server's
   apps/manuals/games (fetched directly over FTP, not guessed) - remotePath
   and sizeBytes are real. year/arch/minSystem are historical best-effort
   (release year, 68k/PPC/Fat support, and minimum System version from
   Macintosh Garden's own per-title pages), not independently verified per
   entry the way the download path is; treat them as a curated guide for
   the Year/CPU/System filters, not a certified database.

   This is also exactly the set of entries tools/catalog_source.json ships
   with - running tools/build_catalog.py against that file with no edits
   reproduces this same data as a loadable "Garden Catalog" file, so the
   two paths (compiled-in vs. loaded) normally show identical content.
   Editing catalog_source.json and re-running tools/generate_catalog_data.py
   (for this file) and/or tools/build_catalog.py (for the loadable file) is
   how you'd update the catalog - see the README. Generated, not hand-
   edited - see tools/generate_catalog_data.py. */

enum {{
    kCatFeatured = 0,
    kCatGames,
    kCatUtilities,
    kCatGraphicsSound,
    kCatProductivity,
    kCatSystemExt,
    kCatInternet,
    kCatDevTools
}};

const Category gCategories[] = {{
    {{ "Featured" }},
    {{ "Games" }},
    {{ "Utilities" }},
    {{ "Graphics & Sound" }},
    {{ "Productivity" }},
    {{ "System Extensions" }},
    {{ "Internet & Comm" }},
    {{ "Dev Tools" }},
}};
const short kCategoryCount = sizeof(gCategories) / sizeof(gCategories[0]);

const CatalogEntry gDefaultCatalogEntries[] = {{
'''

FOOTER = '''};
const short kDefaultCatalogEntryCount = sizeof(gDefaultCatalogEntries) / sizeof(gDefaultCatalogEntries[0]);
'''


def c_string(s):
    out = ['"']
    for ch in s:
        if ch == '\\':
            out.append('\\\\')
        elif ch == '"':
            out.append('\\"')
        else:
            out.append(ch)
    out.append('"')
    return "".join(out)


def build(entries):
    lines = []
    last_cat = None
    for e in entries:
        if e["category"] != last_cat:
            lines.append(f"    /* -- {e['category']} -- */")
            last_cat = e["category"]
        cat_enum = CAT_ENUM_NAMES[CATEGORIES.index(e["category"])]
        arch_enum = ARCH_ENUM_NAMES[e["arch"]]
        min_system = int(e.get("minSystem", 0))
        lines.append(
            f"    {{ {cat_enum}, {int(e['year'])}, {arch_enum}, {min_system}, "
            f"{c_string(e['title'])}, {c_string(e['description'])}, "
            f"{c_string(e['remotePath'])}, {int(e['sizeBytes'])} }},"
        )
    return "\n".join(lines) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    here = os.path.dirname(os.path.abspath(__file__))
    ap.add_argument("--input", default=os.path.join(here, "catalog_source.json"))
    ap.add_argument("--output", default=os.path.join(here, "..", "src", "catalog_data.c"))
    args = ap.parse_args()

    with open(args.input, encoding="utf-8") as f:
        data = json.load(f)
    entries = data["entries"]

    out = HEADER.format(count=len(entries)) + build(entries) + FOOTER

    with open(args.output, "w", encoding="utf-8") as f:
        f.write(out)

    print(f"Wrote {len(entries)} entries to {args.output!r}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
