#!/usr/bin/env python3
"""Wraps a raw HFS floppy image in a real DiskCopy 4.2 (DC42) header.

The floppy image `make` builds (via hformat/hcopy) is a bare block dump -
exactly what BasiliskII/Mini vMac mount directly as a virtual floppy, but
*not* the same thing as a file DiskCopy's own "Mount Image" command can
open. DiskCopy expects its own wrapper: a 128-byte header carrying the
disk name, format info, and two checksums, in front of the same raw
sector data. Confirmed the hard way: feeding DiskCopy a bare image gets
"(-39) An unexpected end-of-file was encountered... which may indicate
that it is corrupted or damaged" - DiskCopy is trying to read a header
structure that was never there.

Every modern DiskCopy version's own "Create Image..." defaults to a
different, newer, compressed format (NDIF) instead of DC42 - but DC42
read support goes back to the format DiskCopy 4.2 itself defined, and
every later DiskCopy version has kept reading it for backward
compatibility, which is what "Mount Image" is actually relying on here.

Header layout and checksum algorithm below are the real DC42 spec, cross-
checked against two independent real-world implementations (lampmerchant/
dsk2dc and claunia/IDEFileToDC42's DC42_HEADERSIZE) after a first attempt
padded the header out to 128 bytes and got "(130) The checksum ... is
INVALID" from a real DiskCopy in the emulator: the header is exactly 84
bytes (1 name-length + 63 name + 4 dataSize + 4 tagSize + 4 dataChecksum +
4 tagChecksum + 1 diskFormat + 1 formatByte + 2 private = 84), with the
disk data starting immediately at offset 84, not 128 - that stray 44-byte
pad was shifting every data byte DiskCopy read, so its checksum over the
(wrongly-offset) data never matched the one computed here over the real
data. Big-endian fields throughout; both checksums computed by walking the
relevant byte range as big-endian 16-bit words, adding each into a 32-bit
accumulator (ignoring overflow), then rotating the accumulator right by
one bit after each word.

Usage:
    python3 make_diskcopy42.py <input.img> <output.img> [--name NAME]
"""
import sys
import struct
import argparse


def dc42_checksum(data):
    """data must have even length - pad the caller's data before calling."""
    acc = 0
    for i in range(0, len(data), 2):
        word = (data[i] << 8) | data[i + 1]
        acc = (acc + word) & 0xFFFFFFFF
        acc = ((acc >> 1) | ((acc & 1) << 31)) & 0xFFFFFFFF
    return acc


def wrap_dc42(data, name):
    if len(data) % 2 != 0:
        raise SystemExit(f"error: image size {len(data)} is odd - DC42 checksums "
                          f"are computed over 16-bit words")

    fname = name.encode("mac_roman")
    if len(fname) > 63:
        raise SystemExit(f"error: name {name!r} is {len(fname)} bytes, DC42 allows at most 63")

    if len(data) == 1474560:
        disk_encoding, format_byte = 0x03, 0x22   # 1.44 MB, MFM CAV dshd
    elif len(data) == 819200:
        disk_encoding, format_byte = 0x01, 0x22   # 800 K, GCR CLV dsdd
    elif len(data) == 409600:
        disk_encoding, format_byte = 0x00, 0x02   # 400 K, GCR CLV ssdd
    else:
        raise SystemExit(f"error: {len(data)} bytes doesn't match a standard "
                          f"400K/800K/1.44MB floppy size - add its encoding/format "
                          f"byte here if this is intentional")

    data_checksum = dc42_checksum(data)

    header = bytearray(84)   # DC42_HEADERSIZE - not 128, see module docstring
    header[0] = len(fname)
    header[1:1 + len(fname)] = fname
    struct.pack_into(">I", header, 0x40, len(data))   # data block size
    struct.pack_into(">I", header, 0x44, 0)            # tag size - none
    struct.pack_into(">I", header, 0x48, data_checksum)
    struct.pack_into(">I", header, 0x4C, 0)             # tag checksum - no tags
    header[0x50] = disk_encoding
    header[0x51] = format_byte
    struct.pack_into(">H", header, 0x52, 0x0100)        # private word - fixed magic

    return bytes(header) + data


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("input")
    ap.add_argument("output")
    ap.add_argument("--name", help="disk name stored in the header "
                                    "(default: input's own basename)")
    args = ap.parse_args()

    with open(args.input, "rb") as f:
        data = f.read()

    name = args.name or args.input.rsplit("/", 1)[-1]
    blob = wrap_dc42(data, name)

    with open(args.output, "wb") as f:
        f.write(blob)

    print(f"Wrote DC42 image {name!r} ({len(data)} data bytes, "
          f"checksum computed) -> {args.output!r} ({len(blob)} bytes)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
