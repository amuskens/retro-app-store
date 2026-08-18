#!/usr/bin/env python3
"""Builds a loadable "Garden Catalog" file from a JSON source.

Garden (the classic Mac app this ships with) reads its software catalog
from a small binary file named "Garden Catalog", if one exists next to the
application - see src/catalog_load.c for the loader and the on-disk format
it expects, and src/catalog.h for the field-size constants (kCatTitleLen/
kCatDescLen/kCatPathLen/kMaxCatalogEntries) this script has to agree with
byte-for-byte. If you change those on the C side, update FIELD_SIZES and
MAX_ENTRIES here to match, or the app will just reject the file it
produces (safely - it falls back to its own built-in catalog, see
catalog_data.c - but your update won't take effect).

Usage:
    python3 build_catalog.py                    # catalog_source.json -> "Garden Catalog"
    python3 build_catalog.py --input mine.json --output "My Catalog"

Workflow for updating the catalog without recompiling the app: edit
catalog_source.json (or your own copy) on a modern machine, run this
script, then get the resulting "Garden Catalog" file onto the classic Mac
next to Garden - e.g. mount build/Garden.img with hfsutils and hcopy it
on, or drag it in through a shared folder in an emulator. Rez/CMake/the
Retro68 toolchain are never involved in this path, which is the point:
updating the catalog this way needs nothing but Python.

Category names (must match one of these exactly, case-sensitive - see
gCategories in catalog_data.c and the Go menu in main.r, both of which
define this same 8-category list independently and would need updating
by hand if it ever changed):
    Featured, Games, Utilities, Graphics & Sound, Productivity,
    System Extensions, Internet & Comm, Dev Tools

minSystem (optional per entry, defaults to 0/"unknown" if omitted): the
minimum classic Mac OS System version the title needs, as major*10+minor
- e.g. 60 for System 6.0, 70 for System 7.0, 75 for System 7.5, 80 for
Mac OS 8.0. Powers the System filter pill; only the lower bound matters
there (older software keeps running on newer systems).
"""
import json
import struct
import sys
import argparse

CATEGORIES = [
    "Featured", "Games", "Utilities", "Graphics & Sound", "Productivity",
    "System Extensions", "Internet & Comm", "Dev Tools",
]
ARCH_CODES = {"68k": 0, "ppc": 1, "fat": 2}

# Must match catalog.h exactly (kCatTitleLen/kCatDescLen/kCatPathLen count
# the NUL, so the usable text length is one less than each of these).
TITLE_SIZE = 48
DESC_SIZE = 110
PATH_SIZE = 100
MAX_ENTRIES = 600  # kMaxCatalogEntries in catalog.h

MAGIC = b"GCAT"
VERSION = 2  # bumped from 1 when minSystem was added - see catalog_load.c


def pack_fixed_string(s, size, field_name, entry_desc):
    b = s.encode("mac_roman", errors="replace")
    if len(b) > size - 1:
        print(f"warning: {entry_desc}: {field_name} is {len(b)} bytes, "
              f"truncating to fit {size - 1}", file=sys.stderr)
        b = b[: size - 1]
    return b + b"\x00" * (size - len(b))


def build(entries):
    if len(entries) > MAX_ENTRIES:
        raise SystemExit(
            f"error: {len(entries)} entries exceeds the app's compiled-in "
            f"limit of {MAX_ENTRIES} (kMaxCatalogEntries in catalog.h) - "
            f"trim the source or raise the limit on both sides and rebuild the app"
        )

    out = bytearray()
    out += MAGIC
    out += struct.pack(">HH", VERSION, len(entries))

    for e in entries:
        desc = f"{e.get('title', '?')!r}"
        try:
            cat_index = CATEGORIES.index(e["category"])
        except ValueError:
            raise SystemExit(
                f"error: {desc}: unknown category {e['category']!r} - "
                f"must be one of {CATEGORIES}"
            )
        try:
            arch_code = ARCH_CODES[e["arch"]]
        except KeyError:
            raise SystemExit(
                f"error: {desc}: unknown arch {e.get('arch')!r} - must be one of "
                f"{list(ARCH_CODES)} (68k/fat run on a real 68k Mac; ppc does not)"
            )

        out += struct.pack(">HHBH", cat_index, int(e["year"]), arch_code,
                            int(e.get("minSystem", 0)))
        out += pack_fixed_string(e["title"], TITLE_SIZE, "title", desc)
        out += pack_fixed_string(e["description"], DESC_SIZE, "description", desc)
        out += pack_fixed_string(e["remotePath"], PATH_SIZE, "remotePath", desc)
        out += struct.pack(">I", int(e["sizeBytes"]))

    return bytes(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--input", default="catalog_source.json",
                     help="JSON source file (default: catalog_source.json)")
    ap.add_argument("--output", default="Garden Catalog",
                     help='output file (default: "Garden Catalog")')
    args = ap.parse_args()

    with open(args.input, encoding="utf-8") as f:
        data = json.load(f)

    entries = data["entries"]
    blob = build(entries)

    with open(args.output, "wb") as f:
        f.write(blob)

    print(f"Wrote {len(entries)} entries ({len(blob)} bytes) to {args.output!r}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
