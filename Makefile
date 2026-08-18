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

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(DIST_DIR)
