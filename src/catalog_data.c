#include "catalog.h"

/* Bundled sample catalog for v1. This is demo/placeholder content, not a
   scrape of the live server: Macintosh Garden's FTP mirror is an unsorted
   flat dump with no server-side categories (see README), so there is no
   live source to pull a categorized listing from. Titles/descriptions here
   are real historical classic Mac software, chosen so the browsing/search/
   pagination UI has honest, recognizable content to show immediately and
   works fully offline - but each entry's `remotePath` is a best-effort
   guess at a flat-root filename, not a verified path. Real, guaranteed-
   correct downloads come through "Live FTP Browse" instead, which lists
   (and downloads) whatever the server actually has right now. */

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
    { kCatFeatured, "Glider 4.0", "Fly a paper airplane through a hazard-filled house. A Mac classic.", "/Glider_4.0.sit", 612000 },
    { kCatFeatured, "KidPix 1.0", "Playful paint program for kids, with sound effects for every tool.", "/KidPix_1.0.sit", 890000 },
    { kCatFeatured, "StuffIt Expander 4.0.1", "Decompresses .sit, .hqx, and .zip archives. Essential utility.", "/StuffIt_Expander_4.0.1.sit", 410000 },
    { kCatFeatured, "ResEdit 2.1.3", "Apple's own resource editor - edit menus, dialogs, icons, and more.", "/ResEdit_2.1.3.sit", 980000 },
    { kCatFeatured, "After Dark 3.0", "The screensaver that made flying toasters famous.", "/After_Dark_3.0.sit", 1450000 },
    { kCatFeatured, "HyperCard 2.4.1", "Build interactive stacks with HyperTalk. The original hypermedia tool.", "/HyperCard_2.4.1.img", 2100000 },
    { kCatFeatured, "Fetch 3.0.3", "The classic drag-and-drop FTP client for the Mac.", "/Fetch_3.0.3.sit", 540000 },
    { kCatFeatured, "Dark Castle", "Gothic platformer classic from Silicon Beach Software.", "/Dark_Castle.sit", 780000 },
    { kCatFeatured, "Disinfectant 3.7", "Free, beloved antivirus utility for classic Mac OS.", "/Disinfectant_3.7.sit", 360000 },
    { kCatFeatured, "GraphicConverter 2.6", "Views and converts nearly every image format under the sun.", "/GraphicConverter_2.6.sit", 1120000 },

    /* -- Games -- */
    { kCatGames, "Glider 4.0", "Fly a paper airplane through a hazard-filled house.", "/Glider_4.0.sit", 612000 },
    { kCatGames, "Dark Castle", "Gothic platformer classic from Silicon Beach Software.", "/Dark_Castle.sit", 780000 },
    { kCatGames, "Beyond Dark Castle", "The sequel - bigger castle, tougher trolls.", "/Beyond_Dark_Castle.sit", 820000 },
    { kCatGames, "Crystal Quest", "Fast-paced arcade shooter with dozens of levels.", "/Crystal_Quest.sit", 540000 },
    { kCatGames, "Bolo", "Networked tank combat game, a pioneer of Mac multiplayer.", "/Bolo_0.99.6.sit", 690000 },
    { kCatGames, "Spectre", "3D networked tank battles rendered in QuickDraw 3D.", "/Spectre_1.1.sit", 1340000 },
    { kCatGames, "Prince of Persia", "Swashbuckling platformer - rescue the princess in 60 minutes.", "/Prince_of_Persia.sit", 430000 },
    { kCatGames, "Oxyd", "Atmospheric puzzle game of stones, switches, and marbles.", "/Oxyd.sit", 960000 },
    { kCatGames, "Spaceward Ho!", "Turn-based galactic conquest strategy game.", "/Spaceward_Ho_4.0.sit", 710000 },
    { kCatGames, "Solarian II", "Vertical-scrolling space shooter with striking vector graphics.", "/Solarian_II.sit", 380000 },
    { kCatGames, "Maelstrom", "Asteroids reborn, with color graphics and a killer soundtrack.", "/Maelstrom_1.4.5.sit", 1780000 },
    { kCatGames, "Lode Runner", "Dig, trap, and outrun enemies in this puzzle-platformer classic.", "/Lode_Runner.sit", 290000 },

    /* -- Utilities -- */
    { kCatUtilities, "ResEdit 2.1.3", "Apple's own resource editor for menus, dialogs, and icons.", "/ResEdit_2.1.3.sit", 980000 },
    { kCatUtilities, "StuffIt Expander 4.0.1", "Decompresses .sit, .hqx, and .zip archives.", "/StuffIt_Expander_4.0.1.sit", 410000 },
    { kCatUtilities, "StuffIt Lite 3.6", "Compress and archive files, freeware sibling of StuffIt Deluxe.", "/StuffIt_Lite_3.6.sit", 560000 },
    { kCatUtilities, "DiskCopy 6.3.3", "Apple's tool for making and restoring disk images.", "/DiskCopy_6.3.3.sit", 310000 },
    { kCatUtilities, "Disinfectant 3.7", "Free, beloved antivirus utility for classic Mac OS.", "/Disinfectant_3.7.sit", 360000 },
    { kCatUtilities, "SCSIProbe 4.3", "Inspect and mount SCSI devices from a control strip module.", "/SCSIProbe_4.3.sit", 90000 },
    { kCatUtilities, "Now Utilities 6.0", "Menu, folder, and startup-manager enhancements bundle.", "/Now_Utilities_6.0.sit", 2050000 },
    { kCatUtilities, "Super Boomerang", "Adds recent-items and folder shortcuts to Open/Save dialogs.", "/Super_Boomerang.sit", 260000 },
    { kCatUtilities, "Flash-It 3.0.2", "Screen capture utility with adjustable compression.", "/Flash-It_3.0.2.sit", 140000 },
    { kCatUtilities, "Compact Pro 1.51", "Fast, efficient archiving utility, a StuffIt alternative.", "/Compact_Pro_1.51.sit", 320000 },
    { kCatUtilities, "TattleTech 2.05", "Reports detailed hardware and system configuration.", "/TattleTech_2.05.sit", 180000 },
    { kCatUtilities, "Default Folder 2.1", "Remembers folders and adds shortcuts to file dialogs.", "/Default_Folder_2.1.sit", 240000 },

    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, "GraphicConverter 2.6", "Views and converts nearly every image format under the sun.", "/GraphicConverter_2.6.sit", 1120000 },
    { kCatGraphicsSound, "KidPix 1.0", "Playful paint program for kids, with sound effects for every tool.", "/KidPix_1.0.sit", 890000 },
    { kCatGraphicsSound, "Color It! 4.0", "Full-featured image editor and paint program.", "/Color_It_4.0.sit", 1890000 },
    { kCatGraphicsSound, "SoundMachine 2.0.1", "Plays and converts sound files in many classic formats.", "/SoundMachine_2.0.1.sit", 250000 },
    { kCatGraphicsSound, "JPEGView 3.3", "Fast, lightweight JPEG and PICT viewer.", "/JPEGView_3.3.sit", 180000 },
    { kCatGraphicsSound, "Swivel 3D Demo", "Interactive 3D modeling and rendering, demo edition.", "/Swivel_3D_Demo.sit", 2340000 },
    { kCatGraphicsSound, "Infini-D Demo", "3D modeling, rendering, and animation, demo edition.", "/InfiniD_Demo.sit", 3100000 },
    { kCatGraphicsSound, "SoundEdit 16 Demo", "Digital audio editing and effects, demo edition.", "/SoundEdit_16_Demo.sit", 1670000 },
    { kCatGraphicsSound, "GIFConverter 2.3.7", "One of the first Mac tools for making and viewing GIFs.", "/GIFConverter_2.3.7.sit", 210000 },
    { kCatGraphicsSound, "Cameraman 1.5", "Screen recording utility for making QuickTime movies.", "/Cameraman_1.5.sit", 470000 },
    { kCatGraphicsSound, "PixelPaint Pro Demo", "Color painting and photo retouching, demo edition.", "/PixelPaint_Pro_Demo.sit", 2560000 },

    /* -- Productivity -- */
    { kCatProductivity, "ClarisWorks 4.0 Demo", "All-in-one word processor, spreadsheet, and database, demo.", "/ClarisWorks_4.0_Demo.sit", 3200000 },
    { kCatProductivity, "WriteNow 4.0", "Fast, lightweight word processor once bundled with NeXT.", "/WriteNow_4.0.sit", 980000 },
    { kCatProductivity, "Nisus Writer Demo", "Word processor known for multilingual and macro support.", "/Nisus_Writer_Demo.sit", 1450000 },
    { kCatProductivity, "FileMaker Pro 3.0 Demo", "Popular flat-file database, demo edition.", "/FileMaker_Pro_3.0_Demo.sit", 2870000 },
    { kCatProductivity, "Dollars and Sense 6.0", "Personal finance and checkbook-balancing software.", "/Dollars_and_Sense_6.0.sit", 1340000 },
    { kCatProductivity, "MacProject II Demo", "Project scheduling with Gantt charts, demo edition.", "/MacProject_II_Demo.sit", 1120000 },
    { kCatProductivity, "Address Book 3.0", "Simple freeware contacts manager.", "/Address_Book_3.0.sit", 210000 },
    { kCatProductivity, "Calendar+ 2.0", "Freeware desk calendar and scheduler desk accessory.", "/Calendar_Plus_2.0.sit", 160000 },
    { kCatProductivity, "QuickLetter 1.2", "Template-driven letter and fax writer.", "/QuickLetter_1.2.sit", 380000 },
    { kCatProductivity, "Business Card Maker", "Design and print business cards from templates.", "/Business_Card_Maker.sit", 290000 },
    { kCatProductivity, "MacSchedule 2.1", "Freeware appointment book and to-do list manager.", "/MacSchedule_2.1.sit", 240000 },

    /* -- System Extensions -- */
    { kCatSystemExt, "After Dark 3.0", "The screensaver that made flying toasters famous.", "/After_Dark_3.0.sit", 1450000 },
    { kCatSystemExt, "Kaleidoscope 1.2.6", "Theming extension for custom window and menu appearances.", "/Kaleidoscope_1.2.6.sit", 620000 },
    { kCatSystemExt, "Aaron 1.1", "Gives System 7 a Mac OS 8 Platinum-style appearance.", "/Aaron_1.1.sit", 340000 },
    { kCatSystemExt, "SoundMaster 1.6.1", "Assigns custom sounds to system events.", "/SoundMaster_1.6.1.sit", 190000 },
    { kCatSystemExt, "Now Menus 6.0", "Hierarchical Apple Menu and menu-bar enhancements.", "/Now_Menus_6.0.sit", 480000 },
    { kCatSystemExt, "Adobe Type Manager 3.8", "Smooths PostScript fonts on screen at any size.", "/ATM_3.8.sit", 560000 },
    { kCatSystemExt, "QuickTime 2.5", "Apple's multimedia extension for movies and sound.", "/QuickTime_2.5.sit", 2450000 },
    { kCatSystemExt, "Speed Doubler 8", "Accelerates file copies and emulated code on PowerPC Macs.", "/Speed_Doubler_8.sit", 890000 },
    { kCatSystemExt, "MenuChoice 1.2", "Adds a searchable menu of open applications.", "/MenuChoice_1.2.sit", 130000 },
    { kCatSystemExt, "Control Strip Modules", "A collection of handy Control Strip add-ons.", "/Control_Strip_Modules.sit", 220000 },
    { kCatSystemExt, "PowerBar 1.0", "Floating palette of one-click system toggles.", "/PowerBar_1.0.sit", 150000 },

    /* -- Internet & Comm -- */
    { kCatInternet, "Fetch 3.0.3", "The classic drag-and-drop FTP client for the Mac.", "/Fetch_3.0.3.sit", 540000 },
    { kCatInternet, "NCSA Telnet 2.6", "Classic freeware Telnet client from NCSA.", "/NCSA_Telnet_2.6.sit", 480000 },
    { kCatInternet, "Netscape Navigator 2.02", "The web browser that defined the mid-90s internet.", "/Netscape_Navigator_2.02.sit", 3400000 },
    { kCatInternet, "Eudora Light 3.1", "Beloved freeware email client.", "/Eudora_Light_3.1.sit", 1560000 },
    { kCatInternet, "ZTerm 1.0", "Popular shareware terminal emulator for modem BBSing.", "/ZTerm_1.0.sit", 260000 },
    { kCatInternet, "NewsWatcher 2.1", "Freeware Usenet newsgroup reader.", "/NewsWatcher_2.1.sit", 390000 },
    { kCatInternet, "Anarchie 1.5", "Fast FTP client with an Archie search front end.", "/Anarchie_1.5.sit", 310000 },
    { kCatInternet, "MacPPP 2.0.1", "Dial-up PPP networking control panel.", "/MacPPP_2.0.1.sit", 220000 },
    { kCatInternet, "Internet Config 1.2", "Shared internet preferences used by many classic apps.", "/Internet_Config_1.2.sit", 340000 },
    { kCatInternet, "MacTCP 2.0.6", "Apple's original TCP/IP control panel for System 7.", "/MacTCP_2.0.6.sit", 180000 },
    { kCatInternet, "Homer 1.7", "Simple freeware web browser for older Macs.", "/Homer_1.7.sit", 610000 },

    /* -- Dev Tools -- */
    { kCatDevTools, "THINK C 5.0", "Symantec's popular C IDE for classic Mac development.", "/THINK_C_5.0.img", 4200000 },
    { kCatDevTools, "THINK Pascal 4.0.2", "Symantec's Pascal IDE, a favorite for teaching Mac programming.", "/THINK_Pascal_4.0.2.img", 3800000 },
    { kCatDevTools, "MPW 3.5", "Apple's Macintosh Programmer's Workshop, free from Apple.", "/MPW_3.5.img", 8900000 },
    { kCatDevTools, "CodeWarrior Gold Lite", "Metrowerks' influential IDE, free Lite edition.", "/CodeWarrior_Gold_Lite.img", 5600000 },
    { kCatDevTools, "HyperCard 2.4.1", "Build interactive stacks with HyperTalk.", "/HyperCard_2.4.1.img", 2100000 },
    { kCatDevTools, "BBEdit Lite 4.1", "The free edition of the legendary Mac text editor.", "/BBEdit_Lite_4.1.sit", 780000 },
    { kCatDevTools, "Resorcerer Demo", "Advanced resource editor, demo edition.", "/Resorcerer_Demo.sit", 1240000 },
    { kCatDevTools, "SpeedyFinder7 3.5", "Collection of Finder speed and productivity hacks.", "/SpeedyFinder7_3.5.sit", 170000 },
    { kCatDevTools, "Anarchie Applet Kit", "Scripting helpers for automating Anarchie transfers.", "/Anarchie_Applet_Kit.sit", 90000 },
    { kCatDevTools, "AppMaker 1.6", "Generates THINK C project skeletons from resource templates.", "/AppMaker_1.6.sit", 430000 },
    { kCatDevTools, "Runtime for HyperCard", "Lets HyperCard stacks run standalone without HyperCard.", "/Runtime_for_HyperCard.sit", 980000 },
};
const short kCatalogEntryCount = sizeof(gCatalogEntries) / sizeof(gCatalogEntries[0]);
