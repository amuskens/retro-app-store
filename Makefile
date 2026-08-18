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
	@# JSON source a user would edit to update their own catalog. Shipping
	@# it on the floppy by default means the load-from-file path is what
	@# actually runs day one, not just an opt-in a user has to set up
	@# themselves - the compiled-in catalog_data.c stays as the fallback
	@# for whenever this file is missing or fails validation.
	python3 tools/build_catalog.py --input tools/catalog_source.json --output "$(CATALOG_FILE)"
	rm -f $(IMG)
	dd if=/dev/zero of=$(IMG) bs=1024 count=$(IMG_BLOCKS) status=none
	$(RETRO68)/bin/hformat -l "$(APP_NAME)" $(IMG)
	$(RETRO68)/bin/hmount $(IMG)
	$(RETRO68)/bin/hcopy -m $(BUILD_DIR)/$(APP_NAME).bin :$(APP_NAME)
	$(RETRO68)/bin/hcopy "$(CATALOG_FILE)" ":$(CATALOG_NAME)"
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
	@# than just the bare app - a disk image has no resource fork of its
	@# own to carry, so this can't reuse Rez's MacBinary writer the app
	@# itself goes through; tools/wrap_macbinary.py builds one from
	@# scratch instead, verified byte-for-byte round-trip through hcopy -m
	@# against a real independent MacBinary reader before being trusted
	@# here. rohd/dCpy (DiskCopy's own type/creator - see download.c's
	@# GuessTypeCreator) means Finder recognizes the expanded result as a
	@# real disk image, ready to mount with DiskCopy, not a generic file.
	python3 tools/wrap_macbinary.py $(IMG) $(DIST_DIR)/$(APP_NAME).img.bin \
		--type rohd --creator dCpy --name "$(APP_NAME).img"

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(DIST_DIR)
