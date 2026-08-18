#include "catalog.h"

/* Bundled sample catalog for v1. Categories are still curated by hand, not
   scraped: Macintosh Garden's FTP mirror has no server-side category
   structure (see README), so there's no live source to pull a categorized
   listing from. But every entry's `remotePath`/size below (except the 5
   marked UNVERIFIED) was cross-checked against a real, full directory
   listing of the live server's apps/manuals/games (fetched directly over
   FTP from the host, not guessed or hand-typed) - so browsing/search/
   pagination has honest content AND, unlike v1's launch state, most of it
   actually downloads successfully without needing Live FTP Browse first.
   Community mirror contents can still change over time, so "verified" here
   means "confirmed present as of this catalog's last update," not a
   permanent guarantee - Live FTP Browse remains the fallback of record for
   whatever the server actually has right now. */

enum {
    kCatFeatured = 0,
    kCatGames,
    kCatUtilities,
    kCatGraphicsSound,
    kCatProductivity,
    kCatSystemExt,
    kCatInternet,
    kCatDevTools
};

const Category gCategories[] = {
    { "Featured" },
    { "Games" },
    { "Utilities" },
    { "Graphics & Sound" },
    { "Productivity" },
    { "System Extensions" },
    { "Internet & Comm" },
    { "Dev Tools" },
};
const short kCategoryCount = sizeof(gCategories) / sizeof(gCategories[0]);

const CatalogEntry gCatalogEntries[] = {
    /* -- Featured -- */
    { kCatFeatured, "Glider 4.0", "Fly a paper airplane through a hazard-filled house. A Mac classic.", "/games/Glider4.02.sit", 589837 },
    { kCatFeatured, "KidPix 1.0", "Playful paint program for kids, with sound effects for every tool.", "/apps/KidPix.sit", 45728 },
    { kCatFeatured, "StuffIt Expander 4.0.1", "Decompresses .sit, .hqx, and .zip archives. Essential utility.", "/apps/stuffit_expander_4.0.2.sea_.bin", 138368 },
    { kCatFeatured, "ResEdit 2.1.3", "Apple's own resource editor - edit menus, dialogs, icons, and more.", "/apps/resedit_2.1.3.sea_.bin", 475904 },
    { kCatFeatured, "After Dark 3.0", "The screensaver that made flying toasters famous.", "/apps/after_dark_3.0.sit", 2847793 },
    { kCatFeatured, "HyperCard 2.4.1", "Build interactive stacks with HyperTalk. The original hypermedia tool.", "/apps/HyperCard241.img", 47220224 },
    { kCatFeatured, "Fetch 3.0.3", "The classic drag-and-drop FTP client for the Mac.", "/apps/fetch_3.0.sit", 252166 },
    { kCatFeatured, "Dark Castle", "Gothic platformer classic from Silicon Beach Software.", "/games/dark_castle_color.sit", 1984007 },
    { kCatFeatured, "Disinfectant 3.7", "Free, beloved antivirus utility for classic Mac OS.", "/apps/Disinfectant371.bin", 354816 },
    { kCatFeatured, "GraphicConverter 2.6", "Views and converts nearly every image format under the sun.", "/apps/GraphicConverter-2.0.6.sit", 392869 },

    /* -- Games -- */
    { kCatGames, "Glider 4.0", "Fly a paper airplane through a hazard-filled house.", "/games/Glider4.02.sit", 589837 },
    { kCatGames, "Dark Castle", "Gothic platformer classic from Silicon Beach Software.", "/games/dark_castle_color.sit", 1984007 },
    { kCatGames, "Beyond Dark Castle", "The sequel - bigger castle, tougher trolls.", "/games/beyond_darkcastle.zip", 2615910 },
    { kCatGames, "Crystal Quest", "Fast-paced arcade shooter with dozens of levels.", "/games/crystalquest_2_2_5m.zip", 922884 },
    { kCatGames, "Bolo", "Networked tank combat game, a pioneer of Mac multiplayer.", "/games/bolo-0997.hqx", 835727 },
    { kCatGames, "Spectre", "3D networked tank battles rendered in QuickDraw 3D.", "/games/Spectre_1.1.sit", 784179 },
    { kCatGames, "Prince of Persia", "Swashbuckling platformer - rescue the princess in 60 minutes.", "/games/Prince-of-Persia_Optimized.sit", 1452977 },
    { kCatGames, "Oxyd", "Atmospheric puzzle game of stones, switches, and marbles.", "/games/oxyd.sit", 684341 },
    { kCatGames, "Spaceward Ho!", "Turn-based galactic conquest strategy game.", "/games/Spaceward_Ho_v2.01.zip", 711805 },
    { kCatGames, "Solarian II", "Vertical-scrolling space shooter with striking vector graphics.", "/games/Solarian_II_1.1.dmg", 860750 },
    { kCatGames, "Maelstrom", "Asteroids reborn, with color graphics and a killer soundtrack.", "/games/Maelstrom_1.3.2.sit", 672743 },
    { kCatGames, "Lode Runner", "Dig, trap, and outrun enemies in this puzzle-platformer classic.", "/games/lode_runner.zip", 244985 },

    /* -- Utilities -- */
    { kCatUtilities, "ResEdit 2.1.3", "Apple's own resource editor for menus, dialogs, and icons.", "/apps/resedit_2.1.3.sea_.bin", 475904 },
    { kCatUtilities, "StuffIt Expander 4.0.1", "Decompresses .sit, .hqx, and .zip archives.", "/apps/stuffit_expander_4.0.2.sea_.bin", 138368 },
    { kCatUtilities, "StuffIt Lite 3.6", "Compress and archive files, freeware sibling of StuffIt Deluxe.", "/apps/stuffitlite36.img", 673792 },
    { kCatUtilities, "DiskCopy 6.3.3", "Apple's tool for making and restoring disk images.", "/apps/Disk-Copy-633-smi.bin", 771584 },
    { kCatUtilities, "Disinfectant 3.7", "Free, beloved antivirus utility for classic Mac OS.", "/apps/Disinfectant371.bin", 354816 },
    { kCatUtilities, "SCSIProbe 4.3", "Inspect and mount SCSI devices from a control strip module.", "/apps/SCSIProbe_4.0.hqx", 15701 },
    { kCatUtilities, "Now Utilities 6.0", "Menu, folder, and startup-manager enhancements bundle.", "/apps/Now_Utilities_6.0.sit", 5386182 },
    { kCatUtilities, "Super Boomerang", "Adds recent-items and folder shortcuts to Open/Save dialogs.", "/Super_Boomerang.sit", 260000 }, /* UNVERIFIED - not found on the live server */
    { kCatUtilities, "Flash-It 3.0.2", "Screen capture utility with adjustable compression.", "/apps/Flash-It3.0.2.sit", 76845 },
    { kCatUtilities, "Compact Pro 1.51", "Fast, efficient archiving utility, a StuffIt alternative.", "/apps/Compact_Pro_1.51_fr.sit", 196834 },
    { kCatUtilities, "TattleTech 2.05", "Reports detailed hardware and system configuration.", "/apps/TattleTech_2.03.sit", 263512 },
    { kCatUtilities, "Default Folder 2.1", "Remembers folders and adds shortcuts to file dialogs.", "/apps/Default-Folder-2.5.1.sit", 121419 },

    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, "GraphicConverter 2.6", "Views and converts nearly every image format under the sun.", "/apps/GraphicConverter-2.0.6.sit", 392869 },
    { kCatGraphicsSound, "KidPix 1.0", "Playful paint program for kids, with sound effects for every tool.", "/apps/KidPix.sit", 45728 },
    { kCatGraphicsSound, "Color It! 4.0", "Full-featured image editor and paint program.", "/apps/ColorIt_4_0.img", 11488977 },
    { kCatGraphicsSound, "SoundMachine 2.0.1", "Plays and converts sound files in many classic formats.", "/apps/soundmachine271.sit", 320388 },
    { kCatGraphicsSound, "JPEGView 3.3", "Fast, lightweight JPEG and PICT viewer.", "/apps/JPEGView_3.3.sit", 554471 },
    { kCatGraphicsSound, "Swivel 3D Demo", "Interactive 3D modeling and rendering, demo edition.", "/apps/swivel3d.zip", 40984429 },
    { kCatGraphicsSound, "Infini-D Demo", "3D modeling, rendering, and animation, demo edition.", "/apps/infini-d_4.5.sit", 21696110 },
    { kCatGraphicsSound, "SoundEdit 16 Demo", "Digital audio editing and effects, demo edition.", "/apps/soundedit16.sit", 4657648 },
    { kCatGraphicsSound, "GIFConverter 2.3.7", "One of the first Mac tools for making and viewing GIFs.", "/apps/GIFConverter_2.3.7_f.sit", 381559 },
    { kCatGraphicsSound, "Cameraman 1.5", "Screen recording utility for making QuickTime movies.", "/apps/cameraman30.sit", 1504464 },
    { kCatGraphicsSound, "PixelPaint Pro Demo", "Color painting and photo retouching, demo edition.", "/apps/PixelPaint_Pro_3.02.sit", 7204023 },

    /* -- Productivity -- */
    { kCatProductivity, "ClarisWorks 4.0 Demo", "All-in-one word processor, spreadsheet, and database, demo.", "/apps/ClarisWorks_4.0.sit", 7861143 },
    { kCatProductivity, "WriteNow 4.0", "Fast, lightweight word processor once bundled with NeXT.", "/apps/WriteNow40_UK.zip", 1453294 },
    { kCatProductivity, "Nisus Writer Demo", "Word processor known for multilingual and macro support.", "/apps/Nisus_Writer_4.03.sit", 4443476 },
    { kCatProductivity, "FileMaker Pro 3.0 Demo", "Popular flat-file database, demo edition.", "/apps/FileMaker_Pro_3.0_V2_Fr.sit", 4285514 },
    { kCatProductivity, "Dollars and Sense 6.0", "Personal finance and checkbook-balancing software.", "/apps/Dollars_and_Sense.image_.sit", 188488 },
    { kCatProductivity, "MacProject II Demo", "Project scheduling with Gantt charts, demo edition.", "/apps/macproject_ii.sit", 99880 },
    { kCatProductivity, "Address Book 3.0", "Simple freeware contacts manager.", "/apps/AddressBook_3.6.2.sit", 257320 },
    { kCatProductivity, "Calendar+ 2.0", "Freeware desk calendar and scheduler desk accessory.", "/apps/CalendarMaker2.2.sit", 39073 },
    { kCatProductivity, "QuickLetter 1.2", "Template-driven letter and fax writer.", "/QuickLetter_1.2.sit", 380000 }, /* UNVERIFIED - not found on the live server */
    { kCatProductivity, "Business Card Maker", "Design and print business cards from templates.", "/Business_Card_Maker.sit", 290000 }, /* UNVERIFIED - not found on the live server */
    { kCatProductivity, "MacSchedule 2.1", "Freeware appointment book and to-do list manager.", "/apps/MacSchedule.zip", 61609 },

    /* -- System Extensions -- */
    { kCatSystemExt, "After Dark 3.0", "The screensaver that made flying toasters famous.", "/apps/after_dark_3.0.sit", 2847793 },
    { kCatSystemExt, "Kaleidoscope 1.2.6", "Theming extension for custom window and menu appearances.", "/apps/kaleidoscope16US.sit", 497458 },
    { kCatSystemExt, "Aaron 1.1", "Gives System 7 a Mac OS 8 Platinum-style appearance.", "/apps/aaron-151.hqx", 205138 },
    { kCatSystemExt, "SoundMaster 1.6.1", "Assigns custom sounds to system events.", "/apps/SoundMaster1.6.5.sit", 31825 },
    { kCatSystemExt, "Now Menus 6.0", "Hierarchical Apple Menu and menu-bar enhancements.", "/Now_Menus_6.0.sit", 480000 }, /* UNVERIFIED - not found on the live server */
    { kCatSystemExt, "Adobe Type Manager 3.8", "Smooths PostScript fonts on screen at any size.", "/apps/atm_3.8.2.sit", 1073618 },
    { kCatSystemExt, "QuickTime 2.5", "Apple's multimedia extension for movies and sound.", "/apps/QuickTime_2.5_Installer.sit", 2041510 },
    { kCatSystemExt, "Speed Doubler 8", "Accelerates file copies and emulated code on PowerPC Macs.", "/apps/speed_doubler_8_0.sit", 1834562 },
    { kCatSystemExt, "MenuChoice 1.2", "Adds a searchable menu of open applications.", "/apps/MenuChoice1.6.sit", 17351 },
    { kCatSystemExt, "Control Strip Modules", "A collection of handy Control Strip add-ons.", "/apps/ControlStrip1.4.sit", 20767 },
    { kCatSystemExt, "PowerBar 1.0", "Floating palette of one-click system toggles.", "/apps/PowerBar1.1.1.sit", 113664 },

    /* -- Internet & Comm -- */
    { kCatInternet, "Fetch 3.0.3", "The classic drag-and-drop FTP client for the Mac.", "/apps/fetch_3.0.sit", 252166 },
    { kCatInternet, "NCSA Telnet 2.6", "Classic freeware Telnet client from NCSA.", "/apps/ncsa-telnet-27b4.hqx", 345095 },
    { kCatInternet, "Netscape Navigator 2.02", "The web browser that defined the mid-90s internet.", "/apps/netscape-2.02-de.hqx", 2894598 },
    { kCatInternet, "Eudora Light 3.1", "Beloved freeware email client.", "/apps/Eudora_Light_3.1.sit", 2221463 },
    { kCatInternet, "ZTerm 1.0", "Popular shareware terminal emulator for modem BBSing.", "/apps/ZTerm1.0.1.sit", 283914 },
    { kCatInternet, "NewsWatcher 2.1", "Freeware Usenet newsgroup reader.", "/apps/NewsWatcher2.1.1.hqx", 889261 },
    { kCatInternet, "Anarchie 1.5", "Fast FTP client with an Archie search front end.", "/apps/Anarchie-150.sit", 505176 },
    { kCatInternet, "MacPPP 2.0.1", "Dial-up PPP networking control panel.", "/apps/MacPPP201.sea_.hqx", 58189 },
    { kCatInternet, "Internet Config 1.2", "Shared internet preferences used by many classic apps.", "/apps/InternetConfig1.2.sit", 107622 },
    { kCatInternet, "MacTCP 2.0.6", "Apple's original TCP/IP control panel for System 7.", "/apps/MacTCP206.sea_.hqx", 194409 },
    { kCatInternet, "Homer 1.7", "Simple freeware web browser for older Macs.", "/apps/Homer_2.1.sit", 390151 },

    /* -- Dev Tools -- */
    { kCatDevTools, "THINK C 5.0", "Symantec's popular C IDE for classic Mac development.", "/apps/think_c_5-0-2.zip", 2657019 },
    { kCatDevTools, "THINK Pascal 4.0.2", "Symantec's Pascal IDE, a favorite for teaching Mac programming.", "/apps/THINK_Pascal_4.5d4.sit", 1600358 },
    { kCatDevTools, "MPW 3.5", "Apple's Macintosh Programmer's Workshop, free from Apple.", "/apps/mpw3-cdrom.zip", 5831362 },
    { kCatDevTools, "CodeWarrior Gold Lite", "Metrowerks' influential IDE, free Lite edition.", "/apps/CodeWarrior_Gold_68k.sit", 16974940 },
    { kCatDevTools, "HyperCard 2.4.1", "Build interactive stacks with HyperTalk.", "/apps/HyperCard241.img", 47220224 },
    { kCatDevTools, "BBEdit Lite 4.1", "The free edition of the legendary Mac text editor.", "/apps/bbedit_lite_4.1.sit", 789735 },
    { kCatDevTools, "Resorcerer Demo", "Advanced resource editor, demo edition.", "/apps/Resorcerer_2.4.zip", 14022015 },
    { kCatDevTools, "SpeedyFinder7 3.5", "Collection of Finder speed and productivity hacks.", "/apps/speedyfinder7.sit", 322598 },
    { kCatDevTools, "Anarchie Applet Kit", "Scripting helpers for automating Anarchie transfers.", "/Anarchie_Applet_Kit.sit", 90000 }, /* UNVERIFIED - not found on the live server */
    { kCatDevTools, "AppMaker 1.6", "Generates THINK C project skeletons from resource templates.", "/apps/AppMaker_1.5.4.sit", 1285361 },
    { kCatDevTools, "Runtime for HyperCard", "Lets HyperCard stacks run standalone without HyperCard.", "/apps/HyperCard_Player_2.4.smi_.bin", 1707904 },
};
const short kCatalogEntryCount = sizeof(gCatalogEntries) / sizeof(gCatalogEntries[0]);
