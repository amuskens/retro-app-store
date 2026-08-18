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

- Custom-drawn browser window: toolbar (search), left sidebar (8 categories
  + Live FTP Browse), paginated results list (10/page), status bar
  (connection LED + page indicator).
- Search across the bundled catalog by title/description.
- Real FTP client over real MacTCP: connect, log in, `PASV`, `NLST`, `SIZE`,
  `RETR`, all through an async-PBControl-plus-poll pattern so the UI never
  blocks (see "Networking" below).
- Live FTP Browse: a real `NLST` listing of the configured server/path,
  paginated the same way as the catalog, downloading exactly the filenames
  it just listed.
- Download with a progress dialog (byte counter, Stop button), saving into
  an auto-created "Garden Downloads" folder next to the app - no per-file
  Save dialog, by design (see below).
- Preferences dialog for FTP host/port/username/password, persisted to a
  prefs file so a stale mirror address doesn't require a recompile.

## What's real vs. sample data

Macintosh Garden's FTP mirror is, per its own "Public Access File
Repository" forum thread, an **unsorted flat dump** - there's no
server-side "Games" or "Utilities" folder to browse, and admins themselves
warn that listing it can be slow. So there's no live source to pull a
categorized listing from.

- The 8 categories and their contents (`catalog_data.c`) are a **bundled,
  curated sample catalog** - real historical Mac software titles and
  descriptions, so the browsing/search/pagination UI has good content and
  works fully offline. Each entry's `remotePath` is a **best-effort
  placeholder** (e.g. `/Glider_4.0.sit`, guessing the mirror is a flat root
  dump) - not a verified path, since there was no way to browse the live
  server's actual current contents while building this.
- **Live FTP Browse** is the real thing: a genuine `NLST` against the
  configured host/path, showing actual current filenames, and downloading
  exactly what it just listed. If a catalog entry's placeholder path turns
  out to be wrong, Live FTP Browse is the reliable fallback.
- Default FTP host/credentials (`ftp.macintosh.garden`, `mirror`/`mirror`)
  come from that same forum thread; community mirror details drift over
  time (this repo's own research already turned up more than one
  historical hostname). Preferences lets you update them without
  recompiling - check macintoshgarden.org's forums if Connect stops
  working.

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
  sidebar.c/h             category list
  results_view.c/h        paginated results list (catalog or live)
  toolbar.c/h              search field/button, status bar, pagination
  progress_dlg.c/h         modal-feeling download/connect progress window
  prefs_dlg.c/h            Preferences dialog + prefs file load/save
  catalog.c/h, catalog_data.c   category/entry data, search/filter
  mactcp_low.h             vendored MacTCP parameter-block ABI
  dnr.c/h                  hostname resolution (see "Networking" above)
  net.c/h                  MacTCP session helpers (stream/send/recv/close)
  ftp.c/h                  FTP protocol on top of net.h
  download.c/h             ftp.c -> disk file, progress callback
  native.c/h               Pascal/C string helpers
  main.r, icon.r           resources: menus, dialogs, alerts, app icon
tools/set_bundle_bit.py    MacBinary Finder-flags fixup (see below)
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

## Known limitations

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
  raw bytes with a best-effort type/creator guess from the extension
  (`.sit`, `.hqx`, `.img`/`.dsk`, else generic binary) - a real StuffIt
  Expander or similar still needs to take over from there.
- **Bundled catalog paths are placeholders**, not verified live paths -
  see "What's real vs. sample data."
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

Configures CMake against the m68k Retro68 toolchain, builds, then
assembles a floppy image. Output lands in `build/`:

- `Garden.img` - a 1.44 MB HFS floppy image with the app already copied on,
  ready to mount (built via the toolchain's bundled `hfsutils`).
- `Garden.bin` - the MacBinary-encoded app by itself.
- `Garden.APPL` / `Garden.dsk` - Retro68's own raw-resource-fork app and
  800K disk image byproducts.

Override the toolchain path with `make RETRO68=/other/path`.

## Running it

Not yet run in an emulator as part of building this - the plan going in
was explicit about that: I can compile-check against the real toolchain
from this environment, but not drive a GUI emulator, so treat this build
as compiled-and-verified-correct-by-the-compiler, not
verified-to-actually-work-on-screen yet.

**Mini vMac** (per mac-system7-c's README, already set up on this machine,
Mac II variant with a ROM already in place at
`~/Library/Preferences/Gryphel/mnvm_rom/vMac.ROM`): boot System 7, drag
`build/Garden.img` onto the emulator window to mount it as a floppy, copy
`Garden` off, double-click to run.

**Basilisk II** is the other option on this machine (was in use for
another project while this was built) - same idea: mount `Garden.img` and
copy the app off, or use whatever shared-folder/disk-image setup that
environment already has.

Things especially worth checking on first real run, roughly in the order
they'd surface:
1. Does the app launch and draw its chrome correctly (toolbar/sidebar/
   results list/status bar, the sprout icon in Finder)?
2. Does browsing categories, searching, and paging work (all offline, no
   network needed for this part)?
3. Does **Connect** (Connection menu, or selecting Live FTP Browse)
   actually reach the server - this exercises `dnr.c` + `net.c`, the
   highest-risk, least-tested code in the app.
4. Does a real download complete and land in "Garden Downloads" next to
   the app, with a sane type/creator so Finder doesn't show it as a plain
   document?
