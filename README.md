# Garden

A classic Mac OS client for [Macintosh Garden](https://macintoshgarden.org),
targeting System 7 (68k), built with [Retro68](https://github.com/autc04/Retro68).
Browse a categorized, paginated catalog of classic Mac software, search it,
and download files over a real FTP connection via MacTCP - styled like a
restrained, Apple-clean take on a mid-90s online service (AOL-for-Mac /
eWorld-adjacent chrome, not the cartoon skin).

This is a first-version prototype. It's a real, working app - it really
connects to a real FTP server over real MacTCP, really lists and downloads
files - but see "What's real vs. sample data" below before assuming every
part of it is drawing from live data.

## Features

- Custom-drawn browser window: toolbar (search), left sidebar (an **All**
  row + 8 categories + Live FTP Browse + Year/CPU/System filter pills),
  paginated results list (10/page), status bar (connection LED + page
  indicator). Fully draggable and resizable (see Gotchas - dragging in
  particular didn't actually work for a while). Row selection (sidebar and
  results list alike) uses Color QuickDraw's `hilite` pen mode, so it picks
  up whatever highlight color the user has set in the Color control panel
  on a color display, and degrades automatically to plain invert on a
  1-bit one - not a hand-picked app color either way.
- **396-entry bundled catalog**, loadable from an external file so it can
  be updated without recompiling the app - see "The loadable catalog"
  below.
- Results rows can show an optional **second description line** - a short
  hardware/CPU requirement note (e.g. "Requires a 68030 or better"), shown
  in italic under the regular description whenever the catalog has real,
  source-stated data for it. Most entries don't have one and just show the
  usual single line.
- Search matches substrings anywhere in the title or description (plain
  case-insensitive `strstr`, not whole-word-only), and is scoped to
  whichever sidebar row is currently selected - a specific category, or
  the whole catalog via the **All** row. Plus **Year**, **CPU**, and
  **System** filter pills at the bottom of the sidebar (release-year
  buckets; 68k/PPC/Fat, with "68k" and "PPC" each including Fat entries
  since those run natively on either; minimum required System version,
  bucketed as System 6/7/8+ - only the lower bound matters, since older
  software keeps running on newer systems) - all three apply on top of
  whichever category or search is currently showing.
- Real FTP client over real MacTCP: connect, log in, `PASV`, `NLST`, `SIZE`,
  `RETR`, all through an async-PBControl-plus-poll pattern so the UI never
  blocks (see "Networking" below).
- Live FTP Browse: a real `NLST` listing of the configured server/path,
  paginated the same way as the catalog, downloading exactly the filenames
  it just listed. Real listings are frequently all-folders (the live
  server's root is `apps`/`manuals`/`games`, no files directly), so entries
  double-click to navigate into as a folder; Connection > Go Up a Level
  backs out. Get always attempts a download regardless of depth.
- Download with a progress dialog (byte counter, Stop button that actually
  works even mid-hang - see Gotchas), saving into an auto-created "Garden
  Downloads" folder next to the app - no per-file Save dialog, by design
  (see below). Saved files get a real type/creator guessed from their
  extension (cross-checked against historical references, not guessed
  from memory - see Gotchas), so double-clicking one routes to a real
  expander app (StuffIt Expander, DiskCopy, ...) instead of showing up as
  a generic, unopenable document.
- Preferences dialog for FTP host/port/username/password, persisted to a
  prefs file so a stale mirror address doesn't require a recompile.

## What's real vs. sample data

The 8 categories themselves are still curated by hand, not scraped -
Macintosh Garden's FTP mirror has no server-side "Games" or "Utilities"
folder to read a categorized listing from (its real top-level structure
turned out to be `apps`/`manuals`/`games`, discovered by actually
connecting - see Gotchas below, which also covers where the older
"unsorted flat dump" assumption this section used to lead with came from
and why it turned out to be only half right).

- **`catalog_data.c`'s 396 entries are real historical Mac software, and
  (as of this catalog's last update) every entry's `remotePath`/size were
  cross-checked against a real, full directory listing of the live
  server** - fetched directly over FTP from the host shell (`curl
  ftp://...`), not guessed, and verified to exist *verbatim* in that
  listing before being written into the catalog (a small script checked
  all of them programmatically - zero typos reached the actual file). A
  later pass added 30 of these specifically to cover early/classic
  versions of major creative and productivity titles (Adobe Photoshop
  0.63 through 5.02, SuperPaint, Aldus/Adobe PageMaker, MORE, Microsoft
  Word, Excel, and PowerPoint) - see the Gotchas entry on real per-file
  hardware notes for how their `hwNote` data was sourced and sanity-
  checked.
  `year`/`arch` are curatorial best-effort (release year, 68k/PPC/Fat
  support) rather than independently verified per entry the way the
  download path is - treat those two fields as a useful guide for the
  Year/CPU filters, not a certified database. **`minSystem`** (the System
  filter's data) is a step more rigorous than year/arch, though still not
  in the same league as `remotePath`: it's scraped from Macintosh Garden's
  own per-title pages (the "For System X.x - Y.y" line each download
  lists), not estimated from release year or genre. **344 of 396 entries
  (87%) have a real, page-sourced value; the other 52 are honestly left at
  0/"unknown"** where no confidently-matching page or no stated
  requirement could be found - not guessed to fill the gap, same "leave it
  honestly blank rather than invent a plausible-sounding value" policy as
  the old `UNVERIFIED` marker below. Unknown entries fall into the System
  filter's "System 6" bucket (0 counts as "< 70" there) rather than a
  separate "unknown" option - worth knowing if a System 6 search turns up
  more results than expected. An earlier pass over a
  smaller (79-entry) version of this catalog left 5 titles that couldn't
  be matched marked `UNVERIFIED` with an invented placeholder path rather
  than a real one; the 367-entry catalog replaced that set entirely with
  titles chosen specifically because a real match existed, so none of the
  current entries carry that marker - if you add your own via
  `catalog_source.json`, nothing stops you from doing the same (an
  unmatched entry just won't download - Live FTP Browse is always the
  fallback of record regardless). Verified doesn't mean permanent, though -
  it's a community mirror, and file layouts drift over time (this repo's
  own research already turned up more than one historical hostname for
  the mirror itself) - so this is "confirmed present as of last update,"
  not a standing guarantee.
- **Live FTP Browse** is still the reliable fallback of record: a genuine
  `NLST` against the configured host/path, showing actual current
  filenames, and downloading exactly what it just listed, so it's correct
  by construction even after the mirror's contents change.
- Default FTP host/credentials (`ftp.macintosh.garden`, `mirror`/`mirror`)
  come from that same forum thread; community mirror details drift over
  time (this repo's own research already turned up more than one
  historical hostname). Preferences lets you update them without
  recompiling - check macintoshgarden.org's forums if Connect stops
  working.

## The loadable catalog

`catalog_data.c`'s 396 entries are compiled in, but they're a **fallback**,
not the only source - Garden looks for a file named exactly `Garden
Catalog` next to the application at startup (`catalog_load.c`, found the
same way `download.c` finds where to put "Garden Downloads": the Process
Manager, not a hardcoded path) and loads its entries from there instead
if it exists and passes validation. `make` builds and ships one by
default (from `tools/catalog_source.json`, the same 396 entries as the
compiled-in fallback, so day-one behavior is identical either way) - the
point isn't that the file is normally different, it's that **updating the
catalog doesn't require rebuilding the app at all**:

1. Edit `tools/catalog_source.json` (or write your own from scratch - see
   the format below) on any modern machine. No toolchain needed.
2. Run `python3 tools/build_catalog.py --input your.json --output "Garden Catalog"`.
3. Get the resulting file onto the classic Mac, next to Garden - mount a
   disk image with `hfsutils` and `hcopy` it on (same tool this repo's own
   `make` already uses), or drag it in through an emulator's shared-folder/
   drag-and-drop support.

**Binary, not XML/JSON on the Mac side** - deliberately: this parses with
a handful of fixed-size `FSRead` calls and zero string tokenizing, which
matters on real 68k hardware in a way it wouldn't on anything modern. The
format (`catalog_load.c` has the authoritative layout comment) is an
8-byte header (`GCAT` magic, version - currently 2, entry count) followed
by one 269-byte fixed record per entry (category index, year, arch byte,
minSystem, then NUL-padded title/description/remotePath fields, then a
4-byte size) - all integers big-endian, which happens to be 68k's own
native byte order, so the loader never byte-swaps anything. `tools/
build_catalog.py` is the only thing that has to agree with this layout on
the writing side; both it and `catalog_load.c` document the exact field
sizes so the two can't silently drift apart unnoticed (a size mismatch
fails loudly either way - the script errors immediately, the app just
falls back to its compiled-in catalog rather than misreading garbage).
The version number exists specifically for this kind of change: it was
bumped 1->2 when `minSystem` was added, so an old-format file gets
rejected cleanly (falls back to the compiled-in catalog) instead of being
misread field-by-field.

**JSON source format** (see `tools/catalog_source.json` for 396 real
examples): a `version` field plus an `entries` array of objects with
`category` (one of the 8 real category names, spelled exactly as in the
sidebar), `title`, `year`, `arch` (`"68k"`, `"ppc"`, or `"fat"`),
`description`, `remotePath`, `sizeBytes`, and `minSystem` (optional,
defaults to 0/"unknown" - minimum required System version as
major*10+minor, e.g. 75 for System 7.5; powers the System filter pill).
Categories themselves are **not** loadable this way - they're tied to
compiled UI chrome (the sidebar rows and the Go menu's item list both
have to match `gCategories` in `catalog_data.c` by hand, since Rez can't
read a C array, let alone an external JSON file), so adding an actual new
category still needs a recompile. Only the entries within the existing 8
are updatable without one.

**`catalog_data.c` (the compiled-in fallback) is generated, not hand-
written** - `tools/generate_catalog_data.py` reads the same
`catalog_source.json` and emits the C struct literals, so the two catalog
paths can't quietly drift apart the way hand-transcribing 396 entries
into C would risk. Editing the catalog now means: edit the JSON, run
`generate_catalog_data.py` (recompiled-in path) and/or `build_catalog.py`
(loadable-file path), depending on which you're updating.

**Validation, and what happens when it fails**: `Catalog_Load` rejects a
file with the wrong magic/version, more entries than
`kMaxCatalogEntries` (600), or a truncated read, and falls back to the
compiled-in catalog in every case - the app never runs with a half-read
or misinterpreted catalog. If `Garden Catalog` doesn't exist at all
(the common case for a floppy someone built by hand without the Makefile),
that's silent - using the bundled default is completely normal. If it
*does* exist but fails validation, Garden says so once at launch (a
plain alert) rather than silently and confusingly using old/different
data than whatever was just dropped in - something actually went wrong
with the file (corrupted in transfer, wrong format version, hand-edited
into invalid JSON that `build_catalog.py` should have caught but didn't),
worth knowing about rather than papering over.

## Networking

MacTCP, not OpenTransport: System 7 is MacTCP's native era (OT arrived
later, as an option on 7.5.2+), and building one real backend well seemed
more valuable than two partial ones. The interface (`net.h`) is narrow
enough that an OT backend could be added later without touching `ftp.c`.

**Retro68 doesn't bundle MacTCP or OpenTransport headers at all** - neither
on this machine nor in general (confirmed against the actual installed
toolchain, and Retro68's own README); Apple's real Universal Interfaces
aren't freely redistributable. `mactcp_low.h` is a from-scratch
reconstruction of just the parameter-block ABI this app needs
(`TCPiopb`, `csCode` values, `wdsEntry`), cross-checked field-for-field
against two independently-sourced copies of Apple's real `MacTCP.h`
(which agreed byte-for-byte) rather than written from memory alone - the
`csCode` values in particular are easy to misremember, and did in fact
turn out to be non-sequential in a way that doesn't match the "obvious"
guess.

`dnr.c` (hostname resolution) is the trickiest part: MacTCP's DNR isn't a
normal driver call, it's a small relocatable code resource (`'dnrp'` id 1)
that ships *inside the MacTCP control panel file itself* - `DNR_Open`'s
real job is finding that file (by creator code, in Control Panels or the
System Folder) and loading its code resource. This was reconstructed
against Apple's own original `DNR.c` (Steve Falkenburg/Apple MacDTS,
1991, modified by Jim Matthews of Dartmouth - the author of Fetch), not
guessed. If a hostname somehow fails to resolve despite a reachable
server, Preferences accepts a raw dotted-decimal IP address too - that
path never touches the resolver at all.

Every call that waits on the network (`net.c`, `dnr.c`) issues its MacTCP
request asynchronously and polls completion in a loop that yields via a
`GiveTimeProc` callback (wired to `WaitNextEvent`/`SystemTask` - see
`progress_dlg.c`) - not a raw blocking call, and not an interrupt-time
completion routine either (this app never installs one - see
`mactcp_low.h`'s comment on why that's a deliberate simplification, not an
oversight).

**This is the one part of the app I could compile-check against the real
Retro68 toolchain but could not execute** - there's no MacTCP driver to
exercise from this sandbox. Every struct layout and API call was verified
against real reference sources rather than guessed, and it compiles clean,
but the actual "does it successfully talk to a real MacTCP INIT" question
needs a real emulator run. If Connect hangs or crashes in testing, this is
where to look first.

## Structure

```
src/
  main.c, app.c/h       Toolbox init, event loop, menus, window layout
  theme.c/h              palette, fonts, shared drawing helpers
  sidebar.c/h             category list + Year/CPU/System filter pills
  results_view.c/h        paginated results list (catalog or live)
  toolbar.c/h              search field/button, status bar, pagination
  progress_dlg.c/h         modal-feeling download/connect progress window
  prefs_dlg.c/h            Preferences dialog + prefs file load/save
  catalog.c/h              filter/search over the active catalog,
                            year/CPU/System filter state
  catalog_data.c            compiled-in fallback catalog (396 entries) -
                              generated, not hand-written, see
                              tools/generate_catalog_data.py
  catalog_load.c             loads "Garden Catalog" next to the app if
                              present/valid, else copies catalog_data.c's
                              fallback in - see "The loadable catalog"
  mactcp_low.h             vendored MacTCP parameter-block ABI
  dnr.c/h                  hostname resolution (see "Networking" above)
  net.c/h                  MacTCP session helpers (stream/send/recv/close)
  ftp.c/h                  FTP protocol on top of net.h
  download.c/h             ftp.c -> disk file, progress callback,
                            extension -> type/creator guess table
  native.c/h               Pascal/C string helpers, app-folder lookup
  main.r, icon.r           resources: menus, dialogs, alerts, app icon
tools/
  set_bundle_bit.py         MacBinary Finder-flags fixup (see Gotchas)
  build_catalog.py           JSON -> loadable "Garden Catalog" binary
  generate_catalog_data.py    JSON -> src/catalog_data.c (compiled-in
                               fallback) - the only thing that should edit
                               that file's entry table
  catalog_source.json         editable source for the bundled catalog -
                               see "The loadable catalog"
  wrap_macbinary.py           wraps an arbitrary file (the floppy image)
                               in a from-scratch MacBinary header - for
                               things outside Rez's own MacBinary writer
  make_diskcopy42.py          wraps a raw HFS image in a real DiskCopy 4.2
                               header - see the DC42 Gotchas entry
dist/
  Garden.bin                 plain MacBinary copy of the app by itself
  Garden.img.bin              the whole floppy (app + catalog), MacBinary-
                               wrapped so Finder recognizes it as a real
                               DiskCopy image on download - see Build
```

## Gotchas found building this

- **Two real DNR bugs, both found via actual emulator testing, both now
  confirmed fixed by a real successful Connect against the live server:**
  1. **Dispatch calls take a 4-byte selector, not 2.** First real emulator
     test (2026-08-18, boot disk confirmed to have MacTCP running) returned
     "Connect failed (error -1)" on every attempt. Re-checking `dnr.c`
     against Apple's real `AddressXlation.h` line by line turned up the
     cause: `OpenResolverProcPtr`/`CloseResolverProcPtr`/`StrToAddrProcPtr`
     had `selector` declared as `short` (2 bytes); Apple's header declares
     it `UInt32` (4 bytes) - both the plain typedef and the
     `STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(UInt32)))` in its
     `uppXxxProcInfo` agree. Calling into the real DNR code resource
     through a 2-byte-selector-typed function pointer shifts every later
     argument's stack offset by 2 bytes, so the resolver reads
     `hostName`/`rtnStruct`/`resultproc`/`userDataPtr` from the wrong
     place - consistent with a fast, wrong error rather than a hang or
     crash. Fixed by widening `selector` to `unsigned long`. This had only
     ever been verified by reading, never by running against real MacTCP -
     a reminder that compiling clean and matching a reference struct's
     *field list* doesn't guarantee a hand-typed *call signature* is
     right; re-derived the TCP-side structs the same way after finding
     this (diffed programmatically against two independent MacTCP.h
     copies) and those checked out on their own.
  2. **`cacheFault` (-23042) isn't an error, it's the DNR's async-pending
     signal - in two different places.** After fixing (1), Connect failed
     again with a real, specific code: `cacheFault`. Confirmed against a
     real historical implementation (Tcl's `tclMacSock.c`,
     `GetHostFromString`) that this is expected, not a failure: if
     `StrToAddr`'s own immediate return is `cacheFault`, the name wasn't
     cached and a real query just started asynchronously - wait for the
     callback (this app now does, via a `done` flag in the `userDataPtr`
     struct, not by polling `hostInfo.rtnCode` directly - the earlier
     version's assumption that rtnCode alone was safe to poll was never
     actually confirmed, and the reference doesn't rely on it either).
     Separately, if `hostInfo.rtnCode` *itself* comes back `cacheFault`
     once the callback fires, the reference calls `StrToAddr` a second
     time before giving up - this app now does too, capped at two
     attempts like the reference. After both fixes: real Connect, real
     login, and a real live `PASV`+`NLST` directory listing all verified
     working against the actual server in the emulator.
- **A menu item's `"Title/X"` text suffix does not create a `Cmd-X`
  key-equivalent** in this Rez dialect - it just puts a literal slash and
  letter in the visible menu text. Found visually in the emulator: "Get
  Selected Item" (defined with the real key-equivalent field,
  `"G", noIcon, ...`) rendered correctly as "Get Selected Item ⌘G", while
  "Quit/Q" (defined as `"Quit/Q", noIcon, noKey, ...`) rendered as the
  literal text "Quit/Q" with no working shortcut at all - confirmed by
  Cmd-Q genuinely doing nothing. Also affected Cut/Copy/Paste. Fixed by
  moving the letter into the dedicated key-equivalent parameter
  (`"Quit", noIcon, "Q", ...`) for all four items.
- **Rez's `ICN#`/`ics#` templates are arrays, not flat blobs.** This
  toolchain's `Multiverse.r` defines `type 'ICN#' { array { hex
  string[128]; }; };` - i.e. a *list* of 128-byte strings (icon bitmap,
  then mask), not one 256-byte field. `icl4`/`ics4` really are flat
  `hex string[N]` and don't need this - only `ICN#`/`ics#` need the extra
  `{ $"...", $"..." }` wrapping with a comma between the two halves. Get
  this wrong and Rez aborts with an internal assertion failure
  (`ResourceDefinitions.cc:238`) rather than a helpful error message.
- **`TEToScrap`/`TEFromScrap` are declared but don't actually work** on
  this toolchain's 68k target (Carbon-only in the headers) - confirmed by
  mac-system7-c's own README. `toolbar.c`'s Cut/Copy/Paste use
  `TECut`/`TECopy`/`TEPaste` alone (TE's own internal clipboard), so they
  work within the app but don't sync with the host/emulator clipboard.
- **The MacBinary "has bundle" Finder flag** (`0x2000`) is never set by
  Rez's MacBinary writer, so without `tools/set_bundle_bit.py` (copied
  verbatim from mac-system7-c, where it was originally diagnosed) Finder
  never shows the custom icon at all, on every build - not a caching
  artifact.
- Several Toolbox calls exist in this toolchain only under their explicit
  `Sync` suffix even where older reference code omits it (e.g.
  `PBHGetFInfoSync`, not `PBHGetFInfo`), and some convenience constants
  Apple's real headers provide (`kOnSystemDisk`, `kDontCreateFolder`,
  `DirCreate`) aren't defined here - `dnr.c`/`download.c`/`prefs_dlg.c`
  define the couple of values needed locally and use `FSpDirCreate`
  instead of `DirCreate`.
- **Live FTP Browse downloads all failed, with no way to reach a real
  file.** Reported after real use: every Get attempt against a live entry
  came back "Couldn't download (error -23015)" (`openFailed`). Root cause,
  found by reproducing directly rather than guessing: the real server's
  root listing (`apps`, `manuals`, `games`) is all directories, and `RETR`
  against a directory gets a non-150/125 reply from the server, which
  `FTP_Retrieve` (`ftp.c`) correctly reports as `openFailed` - but there
  was no way to navigate into any of those directories in the first place,
  so no live file was ever reachable. Fixed by adding real navigation:
  double-clicking a live entry (`app.c`'s `LiveNavigateInto`) appends its
  bare name to a tracked current path (`gLivePath`) and re-issues `NLST`
  there; Connection > Go Up a Level (`LiveNavigateUp`) strips the last
  path component. Downloads from within a navigated subdirectory need the
  full path too (`ResolveLiveDownloadPath` joins `gLivePath` + the entry's
  bare name) since `Download_Fetch` always opens a brand new control
  connection at the login's default directory rather than continuing the
  browse session's `CWD` state. Verified end-to-end in the emulator:
  navigated into `apps`, downloaded a real file, confirmed it landed in
  the Garden Downloads folder.
- **Sidebar category selection wasn't visible.** The sidebar's selected
  row used a light-blue accent color fill (`Theme_FillSelectAccent`) to
  show selection, which turned out indistinguishable from the plain white
  background on a black & white/grayscale display - every emulator
  screenshot taken while building this showed no color at all, which is
  also why `results_view.c`'s row selection was already written to use
  plain invert instead. `sidebar.c` just hadn't followed that same
  reasoning through. First fixed by switching the sidebar to plain invert
  too, then upgraded (see below) to use the real system highlight color
  instead of either hand-picked option.
- **Selection highlighting now uses the real OS highlight color, not a
  hand-picked one.** Requested after the plain-invert fix above: color
  displays should show *the user's own* Color-control-panel highlight
  color, the same way the Finder and every other well-behaved color-aware
  Mac app does, not an app-chosen tint (and not just invert). Color
  QuickDraw has a purpose-built mechanism for exactly this that this
  toolchain's headers confirm are real and present (cross-checked in
  `Multiverse.h` rather than assumed from memory, same discipline as the
  MacTCP work): the `hilite` transfer mode (enum value 50) reads the
  low-memory global at $0DA0 (`LMGetHiliteRGB`/`HiliteRGB`, set by the
  Color control panel) and blends the destination through it - and,
  critically, falls back to plain bit-inversion automatically on a 1-bit
  display, with no depth-checking needed on this app's part.
  `Theme_HighlightRow` (shared by the sidebar and the results list) is now
  `GetPenState` / `PenMode(hilite)` / `PaintRect` / `SetPenState` - save
  and restore around it rather than a bare `PenMode` call, since (unlike
  `InvertRect`) this path actually touches the port's pen state and
  shouldn't leave it changed for whatever draws next. Verified in the
  emulator with the guest actually in color mode this time (earlier
  sessions happened to always be in B&W): selecting a row now shows a
  real yellow tint (the test system's configured highlight color) with
  the row's text/icon still legible on top, not a solid overpaint.
- **The same light-blue-accent-invisible-on-B&W bug as above, missed in
  one more place: the download progress bar appeared permanently white
  on real hardware, never showing any fill even while a download was
  actively progressing.** `Theme_DrawProgressBar` was never updated when
  `Theme_HighlightRow` got the `hilite` fix above - it still painted its
  fill with a plain `SetRGB(&kThemeSelectFill)` (the same light pastel
  blue, `{0x99,0xCC,0xFF}`), which rounds to white on a 1-bit/grayscale
  display, exactly like the old sidebar bug. The frame border still drew
  fine (plain `FrameRect`, unaffected), so the bar looked like an
  empty outline the whole time rather than an obviously broken/missing
  control - easy to miss since it's a "the bar just isn't updating"
  report rather than a crash. Fixed the same way: `GetPenState` /
  `PenMode(hilite)` / `PaintRect` / `SetPenState` for the fill portion.
  `kThemeSelectFill` is now unused anywhere in the app (same fate as
  `Theme_FillSelectAccent` above) and was deleted rather than left dead.
  Not independently re-verified in the emulator against a real download
  in forced black & white mode (the emulator's guest normally runs in
  color, which is why this didn't surface there in the first place, and
  switching the guest's display depth via its Monitors control panel
  didn't turn up an actual Monitors panel in the test disk's Control
  Panels folder in a reasonable amount of digging) - confirmed by direct
  code inspection and the exact matching precedent above, but the real
  hardware this was reported on is the natural place to do the final
  visual confirmation.
- **A hung Connect couldn't be canceled - "Stop" appeared to do nothing.**
  Reported after real use, and reproduced for real (not just read into
  existence): pointing Preferences at a real but unresponsive address
  (`192.0.2.1`, a documented non-routed test address - silently dropped
  rather than refused, unlike a real closed port which fails fast with a
  clean error) reliably reproduces "Downloading... Connecting..." stuck
  indefinitely, matching the report exactly. Root cause: every actual
  network wait in this codebase polls MacTCP asynchronously and checks
  the cancel flag every iteration (`net.c`'s `DoControlCall`) - except
  `Net_Abort`, which used `PBControlSync` for its `TCPAbort`/`TCPRelease`
  cleanup calls. `PBControlSync` blocks the entire event loop with no
  yielding at all until MacTCP completes it - so the *cancel check itself*
  always worked fine, but the cleanup that runs immediately afterward
  (`Net_Open` calls `Net_Abort` on any failure, including
  `userCanceledErr`) then froze the whole UI a second time, solid, with
  zero visual feedback and no way to interrupt it - indistinguishable
  from Stop having done nothing at all. Fixed by giving `Net_Abort` the
  same `PBControlAsync`-plus-poll shape as everything else, but
  deliberately *not* cancel-aware the way `DoControlCall` is: its
  `TCPiopb` is stack-allocated, so bailing out early while MacTCP still
  holds that address would mean a completion write into a freed stack
  frame later. It still takes and calls `giveTime` though, so the UI
  keeps redrawing and responding while cleanup finishes rather than
  freezing - the actual point of the fix, since the wait itself is
  normally near-instant. All 12 call sites (`net.c` plus 11 in `ftp.c`)
  updated to pass `giveTime` through. Verified against the same forced
  hang: Stop now dismisses the dialog within about a second, every time.
- **The "unsorted flat dump" research was wrong, and the fix for that
  turned out to double as the fix for catalog downloads never working.**
  The live server's actual top-level structure is three real directories
  (`apps`/`manuals`/`games`, ~67,000 files total, discovered by actually
  connecting - see the navigation Gotchas entry above), not a flat root
  dump - the original research (a forum thread describing the mirror,
  not a live directory listing) turned out to describe an older or
  different layout. Once that was known, the bundled catalog's
  placeholder paths could be checked for real:
  `curl ftp://mirror:mirror@ftp.macintosh.garden/apps/` (and `/manuals/`,
  `/games/`) from the host shell pulled the full real listing in seconds -
  much faster and more thorough than anything achievable by browsing
  through the emulator -
  and a token-based match (product name tokens must all appear in the
  real filename; version numbers scored higher when they matched exactly)
  against all 79 catalog titles found a confident real file for 74 of
  them. Every chosen path was verified to exist **verbatim** in that real
  listing (a small script cross-checked all 74 before touching
  `catalog_data.c` - zero typos survived to the actual edit) and its real
  size pulled from the same listing, replacing the invented placeholder
  size too. The 5 that didn't match anything are left as they were,
  marked `UNVERIFIED` inline. Verified in the emulator afterward: a
  catalog entry's Get button now downloads a real file directly, without
  ever going through Live FTP Browse first - confirmed for both an
  `/apps/` path (`KidPix 1.0`) and a `/games/` path (`Dark Castle`).
  One false alarm along the way worth recording: `Dark Castle` (1.8 MB)
  first failed with error -34 (`dskFulErr`) - not a bad path or a
  network problem, just the 1.44 MB test floppy actually being full
  after several earlier test downloads landed in the same "Garden
  Downloads" folder next to the app. Copying `Garden` to a real hard disk
  (hundreds of MB free) and retrying confirmed the path was fine all
  along. This did catch one real, separate issue: `BeginDownload`'s
  failure message used to unconditionally tell the user a catalog
  entry's path was "a placeholder, not verified" - true when it was
  written, false now that most of them are verified, and actively
  misleading for something like a disk-full error that has nothing to do
  with path accuracy. Simplified to one generic failure message for
  every case (catalog or live) rather than one that guesses wrong about
  *why* it failed.
- **The window couldn't be dragged - `DragWindow`'s third parameter was
  `NULL`.** Reported as "the window is not really draggable or resizable."
  Resize turned out to already work fine (`GrowWindow` was already being
  called with a real, non-NULL `&gSizeLimits` rect the whole time; the
  first few attempts to reproduce a resize problem kept failing because
  the emulator's other open Finder windows overlapped the exact screen
  coordinates being clicked, not because of anything in Garden - moving
  the window to an isolated part of the screen made it resize correctly
  immediately). Drag was a real bug, though: `DragWindow(which,
  event.where, NULL)` compiles fine (the third parameter is just a `const
  Rect*`), but real Mac apps always pass a real constraint rect there, and
  this ROM's `DragWindow` doesn't appear to null-check it - the result
  wasn't a crash, just a silent no-op drag, which looks exactly like "the
  window doesn't move" from the outside. Fixed by passing
  `qd.screenBits.bounds` (inset by a few pixels) instead. Verified by
  dragging the window to several different screen positions in a row and
  confirming each one actually took effect.
- **The Year/CPU filter controls were verified working type/creator, but
  in the wrong *place*.** They shipped in a second toolbar row at first
  (a pill button each, next to the search field), which read as cluttered
  once actually seen on screen, and conceptually they're "narrow the list
  I'm already looking at" - closer to category selection than to search.
  Moved into the sidebar instead, pinned to the bottom below the category
  rows (`kFilterFooterHeight` in `sidebar.c`) rather than flowing after
  them, so they stay reachable regardless of category count or window
  height, and the toolbar went back to its original single-row height.
  One real bug caught while rebuilding this: after picking a filter value
  from the popup menu, the results list updated correctly but the pill's
  own label didn't - `RedrawResultsAndStatus()` (called after the filter
  change) doesn't touch the sidebar at all, only the results list and
  status bar. Fixed by calling the fuller `RelayoutAndRedraw()` instead,
  which redraws everything including the sidebar the pill lives in.
- **Type/creator codes for downloaded files were researched, not
  guessed** - real sources checked rather than trusted from memory, same
  discipline as the MacTCP work: StuffIt archives get creator `SITx`
  (StuffIt *Expander*, the free, ubiquitous decoder - not `SIT!`, the full
  commercial compressor that's much less likely to actually be
  installed), MacBinary (`.bin`) and `.zip` the same, DiskCopy images
  `rohd`/`ddsk` (not the historically-documented `dCpy` - see the DC42
  Gotchas entry below for why) - `.image` is treated the same as `.img`/
  `.dsk` here too, an older and less common alias for the same raw-disk-
  image category rather than a distinct format. `.dmg` and `.pdf` downloads are called out
  explicitly as *not* fixable this way - `.dmg` is a Mac OS 9/X-era format
  with no
  mounting tool on System 7 at all (not the same thing as classic
  DiskCopy's `.img`/`.dsk` despite the "disk image" family resemblance),
  and there's no PDF viewer on System 7 either; both download fine,
  neither can actually be opened once there, and no type/creator trick
  changes that. Verified for real in the emulator (not just "should
  work"): downloaded a `.sit` file, and Finder's Get Info reported "Kind:
  StuffIt Expander™ document" - confirming a double-click would actually
  route to the real, installed StuffIt Expander in that test environment.
- **Wrapping the floppy image for FTP needed a real, from-scratch
  MacBinary encoder, not guesswork.** `dist/Garden.bin` (just the app)
  already came for free - Rez's own MacBinary writer produces it as a
  normal build byproduct. A disk image doesn't go through Rez at all, and
  has no resource fork of its own for that writer to carry, so
  `tools/wrap_macbinary.py` builds a MacBinary header from scratch
  instead. Rather than reconstruct the format from a general spec (real
  risk of a subtly-wrong field, same lesson as the MacTCP structs), the
  header layout and CRC come directly from Retro68's own
  `ResourceFiles/ResourceFile.cc::writeMacBinary` - the exact code that
  already produces `Garden.bin` and that `hcopy -m`/StuffIt Expander
  already know how to read, so there's no second, possibly-incompatible
  implementation of the same format to go wrong. Verified two ways before
  trusting it: `hcopy -m` (a real, independent MacBinary reader, not
  written by me) decoded a wrapped `Garden.img` back out with the correct
  type/creator and the exact original size, and a byte-for-byte `cmp`
  against the original confirmed the extracted data fork matches exactly -
  not just "the header looks right."
- **`dist/Garden.img.bin` didn't actually mount in DiskCopy at first, and
  the bug was two layers deep.** The MacBinary wrapper above is lossless,
  but it was originally wrapping the *raw* HFS block image `hformat`/
  `hcopy` produce - the same bytes BasiliskII/Mini vMac mount directly as a
  virtual floppy, but not what DiskCopy's own "Mount Image" expects, which
  needs its own header/checksums. Feeding it the raw image got exactly the
  error a real user hit live: "(-39) An unexpected end-of-file was
  encountered... which may indicate that it is corrupted or damaged."
  Fixed by adding `tools/make_diskcopy42.py`, a real DiskCopy 4.2 (DC42)
  header/checksum implementation (spec cross-checked against two
  independent real-world tools - `lampmerchant/dsk2dc` and `claunia/
  IDEFileToDC42`'s `DC42_HEADERSIZE` - not reconstructed from memory), used
  to wrap the raw image before it goes through `wrap_macbinary.py`. Getting
  this working end-to-end in the emulator took three real, sequential bugs,
  each one only visible by actually trying to mount the result rather than
  trusting the format on paper:
  1. **Wrong creator code.** `dImg`/`dCpy` (the type/creator generally
     documented for DC42 files) got "the application program that created
     it could not be found" - this environment's actually-installed
     DiskCopy 6.3.3 has creator `ddsk` registered in Finder's desktop
     database, not `dCpy`. Found by using DiskCopy's own "Create Image from
     Disk..." on a real mounted floppy and checking what creator code
     Finder reported for *that* file via Get Info, then using `ddsk`
     instead. (`download.c`'s `GuessTypeCreator` uses the same corrected
     `ddsk` for downloaded `.img`/`.dsk` files, for the same reason.)
  2. **Wrong checksum, from a wrong header size.** With the creator fixed,
     DiskCopy now recognized and tried to mount the file, but failed with
     "(130) The checksum of 'Garden.img' is INVALID" - real DiskCopy even
     showed the expected vs. calculated values. The checksum *algorithm*
     itself (32-bit accumulator, add each big-endian 16-bit word, rotate
     right 1 bit, repeat) was right - it matched both reference
     implementations exactly. The header *size* wasn't: it's 84 bytes, not
     the commonly-assumed 128. The first version padded it to 128 anyway,
     which shifted every data byte DiskCopy read by 44 bytes - so its
     checksum, computed over the wrong window of bytes, could never match
     one computed over the real data. Fixed by making the header exactly
     84 bytes with data starting immediately after.
  3. With both fixed, `dist/Garden.img.bin` (the actual `make`-produced
     artifact, not a hand-built test copy) was placed on a scratch test
     disk, downloaded-and-expanded via StuffIt Expander, and the resulting
     `Garden.img` mounted cleanly via DiskCopy's real "Mount Image..." -
     the mounted volume opened to show exactly the expected `Garden` app
     and `Garden Catalog`, and the app launched correctly from it.
- **Real hardware (a IIcx) surfaced two more things the emulator couldn't
  catch, since it isn't a stand-in for genuinely different System software
  and physical RAM constraints:**
  - The app's custom icon didn't show up at first after mounting
    `Garden.img.bin`'s expanded image on the IIcx, even though the exact
    same file's icon displayed correctly in BasiliskII. Very likely a
    Desktop database quirk, not a Garden bug: the HFS volume is built by
    `hformat`/`hcopy` (host-side hfsutils), not a real Finder format/copy,
    so it may never get a proper "Desktop" file the way a volume made by
    real Finder would - the standard classic Mac fix is holding
    Command+Option while the volume mounts/the Mac boots to force a
    Desktop rebuild.
  - Downloading any catalog entry failed immediately with error **-41**
    (`mFulErr`, "not enough room in the heap zone" - a File Manager memory
    error, not disk-full or network) - happening right at `FSpCreate`/
    `FSpOpenDF` in `download.c`, before any data transfer, on real
    hardware connected via **Open Transport**. OT's MacTCP-compatibility
    layer has a real, well-documented heavier memory footprint than native
    MacTCP; by the time a TCP connection + FTP session buffers were
    allocated, there wasn't enough heap left to open the destination file.
    The emulator never hit this - it ran under native MacTCP with a
    generous 8MB configured. Confirmed fixed live by raising the app's
    memory partition to 5000K via Finder's Get Info; `main.r`'s `SIZE`
    resource preferred size is now that same confirmed-working 5000K (up
    from 2MB), with the minimum also raised to 1536K (from 768K) for some
    default OT headroom, though the confirmed fix was specifically the
    preferred size, not the floor.
- **The download progress dialog flickered distractingly on real
  hardware** (much more visible there than in the emulator). Root cause:
  `DrawContent()` did a full `EraseRect` of the *entire* window plus a
  full `DrawControls` (redrawing the Stop button) on every single call to
  `ProgressDlg_UpdateProgress` - which fires once per chunk received, so
  many times a second on a fast download. Fixed by splitting it into a
  one-time full draw (title, bar, button - for the initial show and real
  update events) and a lightweight `DrawProgress` used for the frequent
  ticks, which only touches the progress bar (never needs erasing first -
  it only ever grows within its own frame) and the byte-count text (which
  does, since new text is usually a different shape than what it's
  replacing).
- **Nothing in the app handled suspend/resume events (`osEvt`) at all** -
  found while investigating a request to make downloads non-blocking so
  other apps could be used during one. The actual backgrounding mechanism
  (`WaitNextEvent`, called on every spin of the network-wait polling loop
  in `net.c`'s `DoControlCall`) was already in place and should already
  let other apps get scheduled under System 7's cooperative multitasking -
  but the app had no idea when it *was* in the background, so
  `Toolbar_Idle()` kept blinking the search field's caret the whole time
  regardless, needlessly competing for CPU with whatever app the user
  switched to. Fixed by tracking background state (`App_InBackground`/
  `App_HandleOSEvent` in app.h) from both the main event loop and the
  download progress dialog's own separate event loop (a download can
  easily outlast a switch away and back), and skipping `Toolbar_Idle()`
  while backgrounded. `suspendResumeMessage`/`resumeFlag` aren't in this
  stripped-down toolchain's headers, so they're defined locally as stable,
  documented Toolbox constants - same vendoring precedent as
  `mactcp_low.h`. Not independently verified against real multi-app
  switching on hardware (needs the user's own real Mac to exercise) - if
  switching away still feels sluggish after this, that's the next thing
  to look at.
- **Real hwNote data caught two data-quality issues worth documenting,
  not just individual facts.** While researching per-file hardware notes
  for the 30 new Photoshop/PageMaker/Word/Excel/etc. entries:
  - Macintosh Garden's own page for **Adobe PageMaker 6.0** states a
    "Year released" of 1997, but every well-established external source
    (Adobe's own release history, Wikipedia) places it in 1995 - kept the
    well-documented real date rather than trusting one field on one page
    that contradicts easily-verified external facts.
  - **Microsoft Excel 5.0 and Excel 1.01** both came back with an
    identical, implausible "For System 1 - 5 - System 7.0 - 7.6" - a
    9-year gap between releases sharing bit-for-bit the same requirement
    text was the tell. Root cause: some Macintosh Garden pages bundle
    *every* version of a product together (a generic "Microsoft Excel"
    page listing 1.01 through 5.0 downloads) and show one shared
    compatibility badge for the whole page rather than a per-file one -
    unlike the dedicated single-title pages (the large majority of this
    catalog) which do show accurate per-file ranges. Both entries'
    `minSystem` were reverted to 0/unknown rather than kept wrong.
  - One flagged localization catch: the German version of PageMaker 5.0
    was the only match initially found - swapped for a plain English
    5.0a release once one turned up in the real FTP listing. Excel 1.01
    had no English copy anywhere on the mirror at all - labeled "(French)"
    in the title rather than silently presenting it as English.
- **Description rows grew a second line for an optional hardware/CPU
  note** (e.g. "Requires a 68030 or better"), stored as its own `hwNote`
  JSON field for readability but merged into the single on-disk
  `description` string with a `\r` (classic Mac's own line-break
  convention) at build time - see `full_description()` in both
  `build_catalog.py` and `generate_catalog_data.py`. `kResultRowHeight`
  grew 40->52 and the default window height 380->460 to fit it without
  the app needing a CatalogEntry struct field or a binary format bump.

- **Doesn't handle the Quit Apple Event**, so it can't cooperate with a
  system-wide Special > Shut Down / Restart (found during real emulator
  testing: Shut Down reported "the application 'Garden' could not quit"
  until it was quit manually first). Quitting Garden directly (File > Quit
  or Cmd-Q) always worked correctly. Fixing this means installing a handler
  for `kAEQuitApplication` via `AEInstallEventHandler` and checking for
  `kHighLevelEvent` in the main event loop - straightforward, just not done
  in this pass.
- **68k only.** This toolchain was deliberately built `--no-ppc` (System 7
  is fundamentally the 68k-Mac era). Adding PPC is a toolchain rebuild +
  re-pointing `CMAKE_TOOLCHAIN_FILE`, not a code change.
- **OpenTransport isn't implemented** - see "Networking" above.
- **No StuffIt/BinHex/MacBinary decoding.** Downloaded files are saved as
  raw bytes with a real type/creator guess from the extension (see
  Gotchas) so a real expander app can take over from a double-click, but
  Garden itself never unpacks anything - `.dmg`/`.pdf` downloads in
  particular have no path to actually being opened on System 7 at all,
  type/creator or not (see the same Gotchas entry).
- **Categories aren't loadable from the catalog file** - only entries
  within the existing 8 are. The category list itself is tied to compiled
  UI (sidebar rows, the Go menu) that Rez has to know about at build time
  - see "The loadable catalog."
- **`Catalog_Load`'s "file exists but is corrupt" alert path isn't
  live-tested** - the straightforward, common paths (no file -> fallback;
  valid file -> loads) both are, but deliberately feeding it a truncated
  or bad-magic file and confirming the alert + fallback both fire hasn't
  been done yet.
- No resumable downloads; a canceled or failed download is deleted rather
  than kept partial.
- Password field in Preferences isn't masked (plain `EditText` - Dialog
  Manager has no built-in password-style item).

## Toolchain

```
/Users/amuskens/repo/toolchain/Retro68            # source checkout
/Users/amuskens/repo/toolchain/Retro68-build       # build dir + installed toolchain
```

68k-only (`--no-ppc`), same toolchain mac-system7-c (Quill) uses.

## Build

```sh
cd /Users/amuskens/repo/retro-app-store
make
```

Configures CMake against the m68k Retro68 toolchain, builds, packs
`tools/catalog_source.json` into a loadable catalog file, then assembles a
floppy image with both on it. Output lands in `build/`:

- `Garden.img` - a 1.44 MB HFS floppy image with the app **and** a
  `Garden Catalog` file already copied on, ready to mount (built via the
  toolchain's bundled `hfsutils`) - the default build's catalog comes from
  the loadable-file path, not the compiled-in fallback, on purpose (see
  "The loadable catalog"), so that path is exercised on every build, not
  just when a user opts into it later.
- `Garden.bin` - the MacBinary-encoded app by itself.
- `Garden Catalog` - the loadable catalog file, standalone (plain data
  fork, no MacBinary needed - see "The loadable catalog" for the format).
- `Garden.APPL` / `Garden.dsk` - Retro68's own raw-resource-fork app and
  800K disk image byproducts.

`make` also produces two files in **`dist/`**, outside `build/` (so `make
clean` doesn't take them with it) - both meant for uploading to an FTP
server for other classic Macs to fetch, in the same MacBinary format
every real file on the actual Macintosh Garden mirror uses:

- `Garden.bin` - just the app, copied straight from `build/`.
- `Garden.img.bin` - the **whole floppy** (app + catalog together), first
  wrapped in a real DiskCopy 4.2 header by `tools/make_diskcopy42.py`
  (needed for DiskCopy's own "Mount Image" to accept it - a bare raw HFS
  image isn't enough, see Gotchas), then MacBinary-wrapped by
  `tools/wrap_macbinary.py` with type/creator `dImg`/`ddsk` so Finder
  recognizes the expanded result as a real disk image, ready to mount with
  DiskCopy, rather than a generic unopenable file. This is the one to hand
  someone who wants everything in a single download - see the Gotchas
  entry on how it's built and verified, since a disk image needs its own
  from-scratch MacBinary wrapper (it has no resource fork of its own for
  Rez's writer to carry).

`make distclean` removes both `build/` and `dist/`.

Override the toolchain path with `make RETRO68=/other/path`.

## Running it

Verified in a real Basilisk II emulator (Quadra ROM, System 7, real
MacTCP + `slirp` NAT networking) - not just compiled-and-hoped-for. Both
Mini vMac and Basilisk II work; Basilisk II is what this was actually
tested in:

**Basilisk II**: boot System 7, drag `build/Garden.img` onto the emulator
window (or mount via its config) to attach it as a floppy, open it, copy
`Garden` to a hard disk (or just run it from the floppy), double-click to
run.

**Mini vMac** (per mac-system7-c's README, already set up on this machine,
Mac II variant with a ROM already in place at
`~/Library/Preferences/Gryphel/mnvm_rom/vMac.ROM`): same idea - drag
`build/Garden.img` onto the emulator window to mount it, copy `Garden`
off, double-click to run.

Confirmed working end-to-end:
1. App launches and draws its chrome correctly (toolbar/sidebar/results
   list/status bar, sidebar selection highlight visible and tracking
   clicks).
2. Browsing all 8 categories, search, and pagination all work fully
   offline.
3. **Connect** (Connection menu, or selecting Live FTP Browse) reaches the
   real server - real MacTCP DNR hostname resolution, real login, real
   `PASV` data connection, all confirmed against the live server (this
   exercised, and caught real bugs in, `dnr.c` + `net.c` - see Gotchas).
4. **Live FTP Browse navigation**: double-clicking a directory entry
   (`apps`, `manuals`, `games` at the real server's root) descends into
   it and lists real contents; Connection > Go Up a Level backs out
   correctly; the menu item is enabled/disabled based on current depth.
5. A real download (a live file inside `apps`) completed and landed in a
   "Garden Downloads" folder, auto-created next to the app.
6. Selection highlighting renders in real color (confirmed with the guest
   actually running in color mode, using the system's configured
   highlight color) with text/icons still legible on top, and falls back
   to plain invert in B&W - see the `hilite` Gotchas entry.
7. A deliberately unreachable host (`192.0.2.1`, silently dropped rather
   than refused) reproduces a genuine hung Connect, and Stop now
   dismisses it within about a second - see the `Net_Abort` Gotchas entry.
   Preferences editing (host/port, both text and numeric fields) confirmed
   working as part of setting this up.
8. A **catalog** entry's Get button (not Live FTP Browse) downloads a real
   file directly, for both an `/apps/` path (`KidPix 1.0`) and a
   `/games/` path (`Dark Castle`) - see the catalog-verification Gotchas
   entry. Confirmed on a real hard disk with room to spare; the same
   attempt on the nearly-full 1.44 MB test floppy failed with a plain
   disk-full error, unrelated to path correctness.
9. **The loadable catalog**: built `Garden.img` with `make` (which now
   ships a real `Garden Catalog` file on it by default), confirmed the
   app actually reads from that file rather than its compiled-in fallback
   by editing one title in the source JSON, rebuilding, and seeing the
   edited title appear on screen. Swapped the real (unedited) file back in
   afterward and confirmed normal content returned.
10. **Year/CPU filter pills** (sidebar, below the category list): both
    popups open, list the expected choices, and applying one narrows the
    visible list correctly and updates the pill's own label - confirmed
    for a Year bucket, a CPU choice, and both combined (correctly showing
    "no items match" for a combination nothing satisfies).
11. **Window drag and resize**: dragged the window to several different
    positions in a row, each one taking effect; resized down toward the
    minimum width with no clipping observed in the results list or status
    bar controls, and up to a larger size with full-width descriptions
    correctly re-wrapping. See the `DragWindow` Gotchas entry for the bug
    this caught.
12. **Downloaded file type/creator**: downloaded a `.sit` file and
    confirmed via Finder's Get Info that its Kind reads "StuffIt
    Expander™ document" - a double-click would route to a real installed
    copy of StuffIt Expander in that test environment, not show up as a
    generic unopenable file.
13. **`dist/Garden.img.bin`** - both the MacBinary layer and the DC42
    layer verified. Host-side: `hcopy -m` decoded it back to the exact
    original bytes (confirmed with `cmp`), with type/creator correctly
    read back as `dImg`/`ddsk`. In the emulator: the actual `make`-produced
    file was placed on a scratch test disk, expanded via StuffIt Expander
    with no error, and the resulting `Garden.img` mounted cleanly through
    DiskCopy's real "Mount Image..." command - the mounted volume showed
    exactly the expected `Garden` app and `Garden Catalog`, and the app
    launched correctly from it. See the DC42 Gotchas entry for the three
    bugs (wrong creator, then wrong header size/checksum) this caught
    along the way.
14. **Real hardware (IIcx, Open Transport, live macintoshgarden.org
    connection)**: `dist/Garden.img.bin` mounted successfully via DiskCopy
    on real hardware, confirming the DC42 fix beyond just the emulator.
    Connect and FTP browsing worked over Open Transport's MacTCP
    compatibility layer with no changes needed. Catalog downloads
    initially failed every time with error -41 (`mFulErr`) until the app's
    memory partition was raised - see the Gotchas entry above; confirmed
    fixed live by the person doing the hardware testing.
15. **System filter pill, with real scraped data**: confirmed in two
    passes. First with all 367 entries still at the `minSystem` default
    (0/unknown) - selecting "System 8+" correctly emptied the Featured
    list ("No items match your search"), confirming the filter mechanism
    itself. Then again after merging in the real macintoshgarden.org-
    sourced data (see "What's real vs. sample data") and a full clean
    rebuild: selecting "System 7" correctly narrowed Featured from 18
    items down to the 7 whose real minimum requirement is System 7,
    dropping the System-6-minimum ones (Glider 4.0, KidPix 1.0, ResEdit
    2.1.3, After Dark 3.0, HyperCard 2.4.1, Fetch 3.0.3) - real filtering
    against real per-title data, not just an empty-list sanity check.

Not yet exercised in the emulator: `Catalog_Load`'s reject-a-corrupt-file
alert path (see Known Limitations), and a full 200+-item live directory's
higher page numbers (only page 1 of the `apps` listing was paged through).
