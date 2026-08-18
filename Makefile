# Retro68 cross-toolchain location (override with `make RETRO68=/path/to/toolchain`)
RETRO68 ?= /Users/amuskens/repo/toolchain/Retro68-build/toolchain
TOOLCHAIN_FILE := $(RETRO68)/m68k-apple-macos/cmake/retro68.toolchain.cmake
BUILD_DIR := build
APP_NAME := Garden
IMG := $(BUILD_DIR)/$(APP_NAME).img
IMG_BLOCKS := 1440 # 1440 * 1024 = 1,474,560 bytes: a standard HD 3.5" floppy

.PHONY: all configure clean

all: configure
	cmake --build $(BUILD_DIR)
	@# See tools/set_bundle_bit.py: Rez's MacBinary writer always emits a
	@# zeroed Finder-flags byte, so without this, Finder never looks at
	@# this file's BNDL/icon resources at all - not a caching artifact,
	@# a permanently-missing bit.
	python3 tools/set_bundle_bit.py $(BUILD_DIR)/$(APP_NAME).bin
	rm -f $(IMG)
	dd if=/dev/zero of=$(IMG) bs=1024 count=$(IMG_BLOCKS) status=none
	$(RETRO68)/bin/hformat -l "$(APP_NAME)" $(IMG)
	$(RETRO68)/bin/hmount $(IMG)
	$(RETRO68)/bin/hcopy -m $(BUILD_DIR)/$(APP_NAME).bin :$(APP_NAME)
	$(RETRO68)/bin/humount

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)

clean:
	rm -rf $(BUILD_DIR)
