# Retro68 cross-toolchain location (override with `make RETRO68=/path/to/toolchain`)
RETRO68 ?= /Users/amuskens/repo/toolchain/Retro68-build/toolchain
TOOLCHAIN_FILE := $(RETRO68)/m68k-apple-macos/cmake/retro68.toolchain.cmake
BUILD_DIR := build
DIST_DIR := dist
APP_NAME := Garden
IMG := $(BUILD_DIR)/$(APP_NAME).img
IMG_BLOCKS := 1440 # 1440 * 1024 = 1,474,560 bytes: a standard HD 3.5" floppy
CATALOG_NAME := Garden Catalog
CATALOG_FILE := $(BUILD_DIR)/$(CATALOG_NAME)

.PHONY: all configure clean

all: configure
	cmake --build $(BUILD_DIR)
	@# See tools/set_bundle_bit.py: Rez's MacBinary writer always emits a
	@# zeroed Finder-flags byte, so without this, Finder never looks at
	@# this file's BNDL/icon resources at all - not a caching artifact,
	@# a permanently-missing bit.
	python3 tools/set_bundle_bit.py $(BUILD_DIR)/$(APP_NAME).bin
	@# The loadable catalog (see catalog_load.c) - built from the same
	@# JSON source a user would edit to update their own catalog. Still
	@# built every time (useful on its own - drag it in via a shared
	@# folder to test the load-from-file path, or ship a customized one
	@# separately) but NOT copied onto the floppy image below anymore:
	@# the catalog expansion to 2445 real entries (~640KB) plus the app
	@# itself no longer both fit on a standard 1.44MB floppy with any
	@# real headroom (was down to ~20KB free) - and it doesn't need to,
	@# since catalog_data.c (the compiled-in fallback, always present
	@# regardless of this file) already carries the same full catalog.
	python3 tools/build_catalog.py --input tools/catalog_source.json --output "$(CATALOG_FILE)"
	rm -f $(IMG)
	dd if=/dev/zero of=$(IMG) bs=1024 count=$(IMG_BLOCKS) status=none
	$(RETRO68)/bin/hformat -l "$(APP_NAME)" $(IMG)
	$(RETRO68)/bin/hmount $(IMG)
	$(RETRO68)/bin/hcopy -m $(BUILD_DIR)/$(APP_NAME).bin :$(APP_NAME)
	$(RETRO68)/bin/humount
	@# A plain MacBinary copy of the app, in its own folder outside build/
	@# (which `make clean` wipes) - this is the artifact to upload to an
	@# FTP server for other classic Macs to fetch and expand, the same
	@# .bin format every real file on the actual Macintosh Garden mirror
	@# uses (see README's Networking section) - not something a generic
	@# FTP client or a non-Mac-aware host can produce, since it has to
	@# carry the resource fork (icon, menus, etc.) inside the data
	@# stream. Re-copied fresh from build/ on every `make all`, so this
	@# always reflects the last build, not a stale snapshot.
	mkdir -p $(DIST_DIR)
	cp $(BUILD_DIR)/$(APP_NAME).bin $(DIST_DIR)/$(APP_NAME).bin
	@# Same idea, but for the whole floppy (app + catalog together) rather
	@# than just the bare app. Two wrapping steps, both verified against a
	@# real DiskCopy in the emulator (Mount Image, not just "Create Image
	@# from Disk"), not just a host-side round-trip:
	@#   1. tools/make_diskcopy42.py wraps the raw HFS block dump in a real
	@#      DiskCopy 4.2 header (checksums included) - DiskCopy's Mount
	@#      Image expects its own format, not a bare image; feeding it the
	@#      raw image gets "(-39) unexpected end-of-file", since it's
	@#      trying to read a header structure that was never there.
	@#   2. tools/wrap_macbinary.py then wraps THAT for FTP transport, same
	@#      as the bare app above, but with type/creator dImg/ddsk - the
	@#      type/creator this environment's installed DiskCopy 6.3.3
	@#      actually has registered (dCpy, the type/creator historically
	@#      documented for DC42 files, got "the application program that
	@#      created it could not be found" here).
	python3 tools/make_diskcopy42.py $(IMG) $(BUILD_DIR)/$(APP_NAME)_dc42.img \
		--name "$(APP_NAME)"
	python3 tools/wrap_macbinary.py $(BUILD_DIR)/$(APP_NAME)_dc42.img $(DIST_DIR)/$(APP_NAME).img.bin \
		--type dImg --creator ddsk --name "$(APP_NAME).img"

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(DIST_DIR)
