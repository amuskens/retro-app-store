#!/usr/bin/env python3
"""Wraps an arbitrary file (typically a disk image) in a MacBinary header.

A generic FTP upload of a raw HFS disk image has no type/creator - Finder
on the far end has no way to know it's a DiskCopy image versus any other
blob of bytes. MacBinary fixes that the same way it does for every real
file on the actual Macintosh Garden mirror (see README's Networking
section): it prepends a 128-byte header carrying the real filename, type,
creator, and fork lengths, so a MacBinary-aware tool (StuffIt Expander,
Fetch, ...) can reconstruct the original file - with Finder correctly
recognizing it - on download.

This is *not* a resource-fork-preserving wrapper - a raw disk image
doesn't have a meaningful resource fork of its own, so this always writes
a zero-length one. For wrapping something that does have real resources
(an application, for instance), Retro68's own MacBinary writer already
does that as part of the normal build (see set_bundle_bit.py's docstring)
- this script is specifically for things outside that pipeline.

The header layout and CRC below are transcribed field-for-field from
Retro68's own writer (ResourceFiles/ResourceFile.cc's writeMacBinary),
not reconstructed from a general MacBinary spec - guaranteed to agree
with what the rest of this toolchain already produces and what hfsutils/
StuffIt Expander already know how to read, rather than a second,
possibly-incompatible implementation of the same format.

Usage:
    python3 wrap_macbinary.py <input> <output> --type TYPE --creator CREATOR [--name NAME]
"""
import sys
import struct
import time
import argparse

CRC16_TABLE = [
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0,
]

MAC_EPOCH_OFFSET = 2082844800  # seconds between 1904-01-01 and 1970-01-01 UTC


def crc_macbinary(data):
    crc = 0
    for byte in data:
        crc = ((crc << 8) ^ CRC16_TABLE[(byte ^ (crc >> 8)) & 0xFF]) & 0xFFFF
    return crc


def wrap(data, filename, filetype, creator):
    fname = filename.encode("mac_roman")
    if len(fname) > 63:
        raise SystemExit(f"error: filename {filename!r} is {len(fname)} bytes, "
                          f"MacBinary allows at most 63")
    ftype = filetype.encode("mac_roman")
    fcreator = creator.encode("mac_roman")
    if len(ftype) != 4 or len(fcreator) != 4:
        raise SystemExit("error: type and creator must each be exactly 4 characters")

    mac_time = int(time.time()) + MAC_EPOCH_OFFSET

    header = bytearray(128)
    header[0] = 0                                   # old-format version byte
    header[1] = len(fname)                           # filename length
    header[2:2 + len(fname)] = fname                 # filename (rest of the 63-byte field stays zero)
    header[65:69] = ftype                            # file type
    header[69:73] = fcreator                         # file creator
    # 73: Finder flags high byte, 74: zero fill, 75-80: position/folder ID,
    # 81: protected flag, 82: zero fill - all left zero, matching Retro68's
    # own writer for a plain (non-bundle-icon, non-locked) file.
    struct.pack_into(">I", header, 83, len(data))     # data fork length
    struct.pack_into(">I", header, 87, 0)             # resource fork length - none
    struct.pack_into(">I", header, 91, mac_time)      # creation date
    struct.pack_into(">I", header, 95, mac_time)      # modification date
    # 99-123: get-info comment length, low Finder-flags byte, and the rest
    # of MacBinary's reserved/version fields - left zero, same as Retro68's
    # writer (which never sets MacBinary II's 'mBIN' signature either).

    crc = crc_macbinary(bytes(header[:124]))
    header[124] = (crc >> 8) & 0xFF
    header[125] = crc & 0xFF
    # 126-127 stay zero.

    out = bytes(header) + data
    pad = (-len(out)) % 128
    out += b"\x00" * pad
    # Resource fork: zero bytes, already 128-aligned, so no further padding.
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("input")
    ap.add_argument("output")
    ap.add_argument("--type", required=True, help="4-character file type, e.g. rohd")
    ap.add_argument("--creator", required=True, help="4-character file creator, e.g. dCpy")
    ap.add_argument("--name", help="filename stored inside the MacBinary header "
                                    "(default: input's own basename)")
    args = ap.parse_args()

    with open(args.input, "rb") as f:
        data = f.read()

    name = args.name or args.input.rsplit("/", 1)[-1]
    blob = wrap(data, name, args.type, args.creator)

    with open(args.output, "wb") as f:
        f.write(blob)

    print(f"Wrapped {len(data)} bytes as {name!r} ({args.type}/{args.creator}) "
          f"-> {args.output!r} ({len(blob)} bytes)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
