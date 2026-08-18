#include "Types.r"
#include "Icons.r"

/* A sprout - two leaves and a stem in a small mound of soil, in 4 colors
   from the standard classic Mac OS 16-color icon palette (white
   background, black outline, green leaves, dark green stem, brown soil).
   Pixel data was generated programmatically (ellipse/rotation math, see
   the repo's scratch tooling) rather than hand-plotted, the same reasoning
   mac-system7-c's icon used: accurately hand-plotting this many pixels
   across four resources by hand is exactly the kind of tedious,
   error-prone task a script does more reliably. The palette's index order
   (0=white, 1=yellow, ... 15=black - icl4/ics4 reference colors by index
   into this *fixed system palette*, not an arbitrary embedded one) was
   cross-checked against an independent source rather than trusted from
   memory, since getting an index wrong would silently produce a
   wrong-but-plausible-looking color.

   BNDL's signature ('GRDN') must match the app's own creator code, which
   CMakeLists.txt sets via add_application(... CREATOR "GRDN") - without
   that match, Finder falls back to the generic application icon regardless
   of what icon resources exist in the file. Also see the Makefile's
   set_bundle_bit.py step: Rez's MacBinary writer never sets the Finder
   "has bundle" flag on its own, so without that fixup Finder would never
   even look at these resources in the first place. */

resource 'BNDL' (128) {
    'GRDN', 0,
    {
        'ICN#', { 0, 128 },
        'FREF', { 0, 128 }
    }
};

resource 'FREF' (128) {
    'APPL',
    0,
    ""
};

/* 'ICN#' templates as `array { hex string[128]; };` - i.e. a *list* of
   128-byte strings, not one flat 256-byte field - so the icon bitmap and
   the mask bitmap below are two comma-separated array elements, each its
   own brace-enclosed value, not one continuous blob. Same story for
   'ics#' with 32-byte elements just below. (icl4/ics4 further down really
   are one flat hex string[N] each - no extra wrapping needed there.) */
resource 'ICN#' (128) {
    {
        $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
        $"00 00 00 00 00 07 E0 00 00 0F F0 00 00 1F F8 00"
        $"00 3F FC 00 00 7F FE 00 00 FF FF 00 00 FF FF 00"
        $"01 FF FF 80 01 FF FF 80 01 F9 FF 80 01 F1 EF 80"
        $"00 E1 E7 00 00 01 E0 00 00 01 E0 00 00 01 E0 00"
        $"00 01 E0 00 00 01 E0 00 00 01 E0 00 00 01 E0 00"
        $"00 7F FE 00 03 FF FF C0 07 FF FF E0 0F FF FF F0"
        $"0F FF FF F0 0F FF FF F0 07 FF FF E0 03 FF FF C0",
        $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
        $"00 00 00 00 00 07 E0 00 00 0F F0 00 00 1F F8 00"
        $"00 3F FC 00 00 7F FE 00 00 FF FF 00 00 FF FF 00"
        $"01 FF FF 80 01 FF FF 80 01 F9 FF 80 01 F1 EF 80"
        $"00 E1 E7 00 00 01 E0 00 00 01 E0 00 00 01 E0 00"
        $"00 01 E0 00 00 01 E0 00 00 01 E0 00 00 01 E0 00"
        $"00 7F FE 00 03 FF FF C0 07 FF FF E0 0F FF FF F0"
        $"0F FF FF F0 0F FF FF F0 07 FF FF E0 03 FF FF C0"
    }
};

resource 'ics#' (128) {
    {
        $"00 00 00 00 03 C0 07 E0 0F F0 1F F8 1F F8 1F F8"
        $"1D F8 01 C0 01 C0 03 C0 3F FC 3F FC 3F FC 3F FC",
        $"00 00 00 00 03 C0 07 E0 0F F0 1F F8 1F F8 1F F8"
        $"1D F8 01 C0 01 C0 03 C0 3F FC 3F FC 3F FC 3F FC"
    }
};

resource 'icl4' (128) {
    $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    $"00 00 00 00 00 00 0F FF FF F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 FF 8F F8 FF 00 00 00 00 00 00"
    $"00 00 00 00 00 0F F8 88 88 8F F0 00 00 00 00 00"
    $"00 00 00 00 00 FF 88 88 88 88 FF 00 00 00 00 00"
    $"00 00 00 00 0F F8 88 8F F8 88 8F F0 00 00 00 00"
    $"00 00 00 00 FF 88 88 8F F8 88 88 FF 00 00 00 00"
    $"00 00 00 00 F8 88 88 F9 99 88 88 8F 00 00 00 00"
    $"00 00 00 0F F8 88 8F F9 99 F8 88 8F F0 00 00 00"
    $"00 00 00 0F 88 88 FF FF 99 FF 88 88 F0 00 00 00"
    $"00 00 00 0F 88 8F F0 0F 99 FF F8 88 F0 00 00 00"
    $"00 00 00 0F F8 FF 00 0F 99 F0 FF 8F F0 00 00 00"
    $"00 00 00 00 FF F0 00 0F 99 F0 0F FF 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 00 00 00 0F 99 F0 00 00 00 00 00 00"
    $"00 00 00 00 0F FF FF FF 99 FF FF F0 00 00 00 00"
    $"00 00 00 FF FF AA AA AA 99 AA AA FF FF 00 00 00"
    $"00 00 0F FA AA AA AA AA 99 AA AA AA AF F0 00 00"
    $"00 00 FF AA AA AA AA AA AA AA AA AA AA FF 00 00"
    $"00 00 FA AA AA AA AA AA AA AA AA AA AA AF 00 00"
    $"00 00 FF AA AA AA AA AA AA AA AA AA AA FF 00 00"
    $"00 00 0F FA AA AA AA AA AA AA AA AA AF F0 00 00"
    $"00 00 00 FF FF AA AA AA AA AA AA FF FF 00 00 00"
};

resource 'ics4' (128) {
    $"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    $"00 00 00 FF FF 00 00 00 00 00 0F F8 8F F0 00 00"
    $"00 00 FF 88 88 FF 00 00 00 0F F8 8F F8 8F F0 00"
    $"00 0F 88 FF 9F 88 F0 00 00 0F 8F FF 9F F8 F0 00"
    $"00 0F FF 0F 9F FF F0 00 00 00 00 0F 9F 00 00 00"
    $"00 00 00 0F 9F 00 00 00 00 00 00 FF 9F 00 00 00"
    $"00 FF FF FA 9F FF FF 00 00 FA AA AA 9A AA AF 00"
    $"00 FA AA AA AA AA AF 00 00 FF AA AA AA AA FF 00"
};
