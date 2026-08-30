#include "catalog.h"

/* Compiled-in fallback catalog - used whenever no loadable "Garden
   Catalog" file is found next to the app, or one is found but fails
   validation (see catalog_load.c). 2445 entries, each cross-checked
   against a real, full directory listing of the live server's
   apps/manuals/games (fetched directly over FTP, not guessed) - remotePath
   and sizeBytes are real. year/arch/minSystem are historical best-effort
   (release year, 68k/PPC/Fat support, and minimum System version from
   Macintosh Garden's own per-title pages), not independently verified per
   entry the way the download path is; treat them as a curated guide for
   the Year/CPU/System filters, not a certified database.

   This is also exactly the set of entries tools/catalog_source.json ships
   with - running tools/build_catalog.py against that file with no edits
   reproduces this same data as a loadable "Garden Catalog" file, so the
   two paths (compiled-in vs. loaded) normally show identical content.
   Editing catalog_source.json and re-running tools/generate_catalog_data.py
   (for this file) and/or tools/build_catalog.py (for the loadable file) is
   how you'd update the catalog - see the README. Generated, not hand-
   edited - see tools/generate_catalog_data.py. */

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

const CatalogEntry gDefaultCatalogEntries[] = {
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "1st Aid HFS 2.8", "A disk repair and file recovery utility for HFS volumes.", "/apps/1st_Aid_HFS_2.8.sit", 69480 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchPPC, 75, "3D-XplorMath", "Mathematical visualization software for exploring curves, surfaces, and manifolds.", "/apps/3DXplorMath.sit", 11333440 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 70, "4-Sight Fax 3.1", "TDA/AGFA's fax server and modem fax software for sending and receiving faxes from a classic Mac.", "/apps/4-Sight-Fax-3.1.sit", 1572167 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "4D Boxing", "Domark's boxing simulation game for classic Mac OS.", "/games/4D_Boxing_1_0.zip", 6828791 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 70, "4th Dimension", "Powerful relational database development environment.", "/apps/4th_Dimension_6.5.6.sit", 3695395 },
    { kCatProductivity, 1987, kArch68k, 30, "4th Dimension 1.0.1", "ACI's powerful relational database development environment for Macintosh, known as 4D.", "/apps/4th_Dimension_1.0.1.img_.sit_.hqx", 419431 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1991, kArch68k, 60, "4th Dimension 3.5", "Earlier release of the 4th Dimension relational database and application builder.", "/apps/4D_3.5.sit", 9056922 },
    { kCatDevTools, 1996, kArchFat, 70, "4th Dimension 4.2.4 (French)", "French-language release of the 4th Dimension relational database development environment.", "/apps/4e-DIMENSION-FR-4-2-4.sit", 2102705 },
    { kCatDevTools, 1995, kArchFat, 70, "4th Dimension 6.0.6", "ACI's 4D relational database development environment, a mainstay for building custom Mac business", "/apps/aci-4th-dimesion-606.sit", 52286816 },
    { kCatDevTools, 1996, kArchFat, 70, "4th Dimension 6.1", "A later version of ACI's 4D relational database development environment for classic Mac OS.", "/apps/4d-6-1_0.sit", 24941772 },
    { kCatDevTools, 1996, kArchFat, 70, "4th Dimension 6.8.2", "Relational database development environment for building custom Mac applications.", "/apps/4th_Dimension_6.8.2.sea_.bin", 5413632 },
    { kCatDevTools, 1985, kArch68k, 10, "68000 Development System", "Early assembler and development toolset for 68000 assembly programming on the Macintosh.", "/apps/68000_Development_System.sit", 709754 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "68040 Cache", "A control panel for tuning the instruction and data cache settings on 68040-based Macintosh models.", "/apps/68040_Cache.sea_.hqx", 76478 },
    /* -- Games -- */
    { kCatGames, 1985, kArch68k, 20, "A Mind Forever Voyaging", "Infocom's philosophical science-fiction text adventure about a sentient AI.", "/games/a_mind_forever_voyaging.sit", 178589 },
    { kCatGames, 1995, kArch68k, 60, "A-10 Attack!", "Parsoft's detailed A-10 Warthog combat flight simulation.", "/games/A-10_Attack.toast_.sit", 98523775 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArch68k, 0, "Aaron 1.1", "Gives System 7 a Mac OS 8 Platinum-style appearance.", "/apps/aaron-151.hqx", 205138 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "Absoft MacFortran II 2.4", "Absoft's Fortran compiler and development environment for classic Mac OS, widely used in scientific", "/apps/Absoft_MacFortran_2.4.img_.sit", 109634 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "Abuse", "Crack dot Com's side-scrolling run-and-gun action game.", "/games/Abuse_CD.sit", 41518634 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "AccessPC 2.01", "Insignia Solutions' utility for reading, writing, and mounting DOS and Windows formatted disks on classic", "/apps/AccessPC_201.sit", 293012 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArch68k, 70, "ACDSee 1.5.1", "A Macintosh release of ACD Systems' popular image viewing and cataloging software.", "/apps/ACDSee_1.5.1_Installer.sit", 1953276 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "Acrobat Reader 2.0", "Early release of Adobe's PDF viewing software for the classic Mac OS.", "/apps/acrobat_reader_2.0.sit", 1290099 },
    { kCatProductivity, 1990, kArch68k, 60, "Acta Advantage", "Outline processor for organizing notes and ideas.", "/apps/Acta_Advantagetm.img_.sit", 436117 },
    /* -- Games -- */
    { kCatGames, 1996, kArchPPC, 70, "Actua Soccer", "3D football simulation game from Gremlin Interactive.", "/games/Actua_Soccer_101a.sit", 36394203 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 60, "Add Depth 2", "Ray Dream's utility for adding 3D depth and bevel effects to 2D artwork and text.", "/apps/AddDepth2.sit", 4671580 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 0, "Address Book 3.0", "Simple freeware contacts manager.", "/apps/AddressBook_3.6.2.sit", 257320 },
    { kCatProductivity, 1996, kArchFat, 70, "Adobe Acrobat 3.01", "Adobe's PDF creation and viewing suite (Exchange, Distiller, and Reader) for classic Mac OS.", "/apps/AdobeAcrobat301.sit", 250609829 },
    { kCatProductivity, 1999, kArchFat, 75, "Adobe Acrobat 4.0", "PDF authoring and viewing suite CD-ROM including Acrobat Distiller.", "/apps/AdobeAcrobat4CD.ZIP", 210469852 },
    { kCatProductivity, 1999, kArchFat, 70, "Adobe Acrobat 4.05", "Adobe's PDF creation and viewing suite for classic Mac OS, a later version than Acrobat 3.", "/apps/adobe_acrobat_4.05.toast_.sit", 308214324 },
    { kCatProductivity, 2001, kArchPPC, 85, "Adobe Acrobat 5.0", "PDF authoring suite CD-ROM release with improved form and security tools.", "/apps/AdobeAcrobat5CD.ZIP", 326944937 },
    { kCatProductivity, 2001, kArchPPC, 86, "Adobe Acrobat 5.0 (Prerelease)", "A prerelease build of Adobe Acrobat 5, the PDF creation and viewing suite, for Mac OS.", "/apps/Acrobat5_prerelease_install.sit", 78745038 },
    { kCatProductivity, 2001, kArchPPC, 81, "Adobe Acrobat 5.0.10", "PDF authoring and viewing suite, Classic-compatible release of Adobe Acrobat.", "/apps/AdobeAcrobat5.0.10.sit_.bin", 120845568 },
    { kCatProductivity, 1994, kArch68k, 70, "Adobe Acrobat Reader 2.1", "Early version of Adobe's free PDF viewing application for classic Mac OS.", "/apps/acrobatreader21.img_.sit", 4348431 },
    { kCatProductivity, 1996, kArchFat, 70, "Adobe Acrobat Reader 3.0", "PDF viewing application from Adobe for reading Portable Document Format files.", "/apps/Acrobat_Reader_30.iso", 459415552 },
    { kCatProductivity, 2001, kArchPPC, 84, "Adobe Acrobat Reader 5.1", "PDF viewer release with improved rendering and forms support for late classic Mac OS.", "/apps/acroreader51_enu_full.bin", 45730688 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 70, "Adobe After Effects 1.0", "First release of After Effects, the motion graphics and compositing application originally by CoSA.", "/apps/After_Effects_1.0.sit", 874186 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe After Effects 2.0", "An early version of Adobe's professional motion graphics and video compositing application for classic Mac", "/apps/After_Effects_2.sit", 3053156 },
    { kCatGraphicsSound, 1999, kArchPPC, 70, "Adobe After Effects 4.0 (Tryout)", "Trial edition of Adobe's professional motion graphics and video compositing application.", "/apps/AdobeAfter_Effects4.0Tryout.sit", 14138860 },
    { kCatGraphicsSound, 1995, kArchPPC, 70, "Adobe Dimensions 2.0", "Adobe's application for creating and editing 3D vector illustrations (Spanish-language release).", "/apps/Adobe_Dimensions_2.0_ES.sit", 5042008 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Adobe Dimensions 3.0.1", "3D illustration tool for creating and extruding vector artwork for use with Illustrator.", "/apps/AdobeDimensions301.sit", 8276100 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "Adobe FrameMaker 4.0.4 (68k)", "An early 68k-native release of Adobe FrameMaker, the long-document publishing and technical documentation", "/apps/FrameMaker-4.0.4-Mac-68k.sit", 21592543 },
    { kCatProductivity, 1996, kArchPPC, 70, "Adobe FrameMaker 5.0", "Long-document publishing and technical writing software from Adobe.", "/apps/Adobe_FrameMaker_5.0.sit", 17790748 },
    { kCatProductivity, 1999, kArchPPC, 70, "Adobe FrameMaker 6", "Adobe's long-document publishing and technical documentation software, a version predating FrameMaker 7.", "/apps/FrameMaker_6.iso", 174630912 },
    { kCatProductivity, 2002, kArchPPC, 86, "Adobe FrameMaker 7", "Adobe's long-document publishing and technical documentation software.", "/apps/FrameMaker_7.iso_.zip", 540535320 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 81, "Adobe GoLive 4.0 (German)", "Adobe's visual web site design and HTML authoring application, localized for German.", "/apps/Adobe_GoLive_4_0_german.sit", 16383660 },
    { kCatInternet, 2001, kArchPPC, 86, "Adobe GoLive 6.0.1", "Adobe's visual web site design and HTML authoring application, a later version than GoLive CyberStudio 3.", "/apps/Adobe_GoLive_6.0.1.toast_.sit", 16181592 },
    { kCatInternet, 1998, kArchPPC, 70, "Adobe GoLive CyberStudio 3.0", "The original GoLive CyberStudio web site design and HTML authoring application, before full Adobe rebranding.", "/apps/GoLive_CyberStudio_3.0.sit", 6640789 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "Adobe Home Publisher 2.1", "Consumer desktop publishing software from Adobe for greeting cards, flyers, and newsletters.", "/apps/Adobe-HomePublisher-21.sit", 4086664 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1987, kArch68k, 30, "Adobe Illustrator 1.1", "Early release of Adobe's PostScript vector illustration program.", "/apps/Adobe_Illustrator_1.1-_UNR.sit", 107493 },
    { kCatGraphicsSound, 2001, kArchPPC, 85, "Adobe Illustrator 10", "Adobe's professional vector illustration software, version 10.", "/apps/Adobe_Illustrator_10.sit", 62141586 },
    { kCatGraphicsSound, 2000, kArchPPC, 90, "Adobe Illustrator 10.0 (Trial)", "Trial installer of Adobe's vector illustration program with Web graphics tools.", "/apps/Illustrator_10_Tryout.sit", 103788947 },
    { kCatGraphicsSound, 2001, kArchPPC, 91, "Adobe Illustrator 10.0.3", "Late Classic-era Adobe Illustrator release for Mac OS 9.", "/apps/Adobe_Illustrator_10.0.3.toast_.sit", 183186134 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Illustrator 5.0", "Vector illustration software adding gradients and a redesigned toolbox.", "/apps/adobe_illustrator_5.sit", 5304962 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Illustrator 5.0.1", "Later release of Adobe's professional vector illustration application.", "/apps/a-illustrator-501.sit", 5325939 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Adobe Illustrator 5.5", "Vector illustration release adding native PowerPC support alongside 68k code.", "/apps/adobeillustrator55.sit", 8760856 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Adobe Illustrator 6.0", "Adobe's professional vector illustration software, 68k Macintosh release.", "/apps/adobe_illustrator_6.0_68k.sit", 10878884 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Adobe Illustrator 6.0.1", "Adobe's professional vector illustration application.", "/apps/AdobeIllustrator601-68k.sit", 10242870 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Adobe Illustrator 6.0.2", "A mid-1990s release of Adobe Illustrator, the professional vector illustration software, for classic Mac OS.", "/apps/Illustrator_6.0.2.sit", 11690381 },
    { kCatGraphicsSound, 1997, kArchFat, 75, "Adobe Illustrator 7.0", "Adobe's professional vector illustration software, version 7.", "/apps/Illustrator_7.0.zip", 364052259 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Adobe Illustrator 7.0.1", "Vector illustration release with a Photoshop-like layers palette and multiple undo.", "/apps/Adobe_Illustrator_701.sit", 25658157 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Adobe Illustrator 8", "Adobe's professional vector illustration software, version 8.", "/apps/Adobe_Illustrator_8.sit", 29804092 },
    { kCatGraphicsSound, 1998, kArchPPC, 70, "Adobe Illustrator 8 (French)", "Adobe's vector illustration software for classic Mac OS, localized for French.", "/apps/Illustrator8_fr_installer.sit", 41089329 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "Adobe Illustrator 88 (1.6)", "Early Adobe Illustrator release, known informally as Illustrator 88.", "/apps/AdobeIllustrator88_16_dc42.sit", 187176 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "Adobe Illustrator 88 (1.9.5)", "Early Adobe Illustrator release, informally called Illustrator 88, for vector drawing on the Mac.", "/apps/adobeIllustrator88_1_9_5.zip", 990454 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "Adobe Illustrator 88 1.8.3", "An early release of Adobe's vector illustration application, codenamed Illustrator 88.", "/apps/adobeillustrator88_1_8_3.zip", 4572482 },
    { kCatGraphicsSound, 2000, kArchPPC, 86, "Adobe LiveMotion 1.0", "Adobe's Flash-competitor animation and interactive web content authoring tool.", "/apps/adobe_livemotiontm_1.0.img_.bin", 41513088 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArchFat, 70, "Adobe PageMaker 6.0", "The first PageMaker released after Adobe's acquisition of Aldus.", "/apps/adobepagemaker60.sit", 20441720 },
    { kCatProductivity, 1996, kArchPPC, 70, "Adobe PageMaker 6.01", "Page layout software update for Adobe's PageMaker desktop publishing application.", "/apps/Adobe_PageMaker_6.01.sit.hqx", 43629329 },
    { kCatProductivity, 1997, kArchPPC, 75, "Adobe PageMaker 6.5", "Later release of Adobe's page layout and desktop publishing software.", "/apps/Adober_PageMakerr_6.5.img_.zip", 295322557 },
    { kCatProductivity, 2001, kArchPPC, 86, "Adobe PageMaker 7", "A late version of the pioneering desktop publishing software for Power Macintosh.", "/apps/Adobe_PageMaker_7_PPC.sit", 96213287 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArchFat, 71, "Adobe PageMill 3.0", "Adobe's WYSIWYG HTML web page authoring application.", "/apps/Adobe_PageMill_3.0.sit", 6745036 },
    { kCatInternet, 1997, kArchPPC, 75, "Adobe PageMill 3.0 (German)", "Adobe's WYSIWYG HTML web page editor; this is the German-localized release.", "/apps/Adobe_PageMill_3_0_german.sit", 9016261 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArch68k, 70, "Adobe PhotoDeluxe 1.0", "The original release of Adobe's consumer-oriented, simplified photo editing application.", "/apps/Adobe_PhotoDeluxe_1.0.img_.sit", 17771566 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Adobe PhotoDeluxe 1.1", "Adobe's consumer-oriented photo-editing application built on Photoshop technology.", "/apps/PhotoDeluxe_1.1.zip", 376698433 },
    { kCatGraphicsSound, 1997, kArchFat, 70, "Adobe PhotoDeluxe 2.0", "Adobe's consumer-oriented, simplified photo editing application built on Photoshop technology.", "/apps/Adobe_PhotoDeluxe_2.0_SN.sit", 31511735 },
    { kCatGraphicsSound, 1988, kArch68k, 0, "Adobe Photoshop 0.63 (beta)", "A pre-1.0 beta of Thomas Knoll's original image editor.", "/apps/Photoshop_0.63b.sit", 241117 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Adobe Photoshop 1.0", "The first public release of the image editor that became an industry standard.\rRequires 2MB RAM and hard disk", "/apps/Adobe_Photoshop1.sit", 443832 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Adobe Photoshop 1.0.7", "A later 1.x point release, before the 2.0 rewrite.\rRequires 2MB RAM and hard disk", "/apps/Photoshop_1.0.7_CLEAN.sit", 882773 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Adobe Photoshop 2.0.1", "Added paths, CMYK editing, and the first plug-in filter architecture.\rMinimum Mac SE, 2MB RAM, hard drive", "/apps/Adobe_Photoshopr_2.0.1_0.sit", 1618156 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Photoshop 2.5", "Early classic Mac OS release of Adobe's flagship image editing software.", "/apps/Photoshop_2.5.mar", 4536192 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Photoshop 2.5 LE (German)", "The Limited Edition of an early Adobe Photoshop release for classic Mac OS, localized for German.", "/apps/Adobe_PhotoShop_2.5_LE_German.zip", 5255888 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Photoshop 2.5.1", "Added 16-bit and 32-bit color support.\rRequires 68020 CPU or newer", "/apps/Photoshop_2.5.1.sit", 9776924 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Photoshop 2.5.1 LE", "Limited Edition release of Photoshop 2.5, Adobe's pioneering image-editing application.", "/apps/Adobe_Photoshop_2.5.1_LE.sit", 2612317 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "Adobe Photoshop 3.0", "Adobe's image-editing software, this multilingual Deluxe CD-ROM includes an English installer.", "/apps/Photoshop3_EN-FR-DE_Deluxe.iso_.sit", 415769983 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "Adobe Photoshop 3.0.5", "Introduced Layers, still one of Photoshop's defining features.\rRequires 68020+ CPU or Power Mac", "/apps/Adobe_Photoshop_3.0.5.sit", 9593334 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Adobe Photoshop 3.0.5 (Tryout)", "Time-limited tryout demo of Adobe Photoshop 3.0.5 image editing software.", "/apps/AdobePhotoshopTryout_3.0.5.sit", 13213678 },
    { kCatGraphicsSound, 1996, kArchFat, 71, "Adobe Photoshop 4.0", "Introduced Adjustment Layers and the now-familiar single-window UI.\rRequires 68030+ CPU, 16MB RAM", "/apps/Photoshop_4.0.sit", 30386476 },
    { kCatGraphicsSound, 1999, kArchFat, 0, "Adobe Photoshop 5.02", "Added editable type layers, History, and multiple undo.", "/apps/adobe_photoshopr_5.02.sit", 17480724 },
    { kCatGraphicsSound, 2000, kArchPPC, 85, "Adobe Photoshop 6.0", "Professional image editing software adding vector shape and text layers.", "/apps/photoshop-6-iso.zip", 445893967 },
    { kCatGraphicsSound, 2000, kArchPPC, 81, "Adobe Photoshop 6.0 (Tryout)", "Trial version of Photoshop 6.0 adding vector shapes and improved text handling.", "/apps/adobe_photoshopr_6.0_tryout.sit", 37935985 },
    { kCatGraphicsSound, 2002, kArchPPC, 90, "Adobe Photoshop 7.0", "Adobe's professional image editor, the last version to run on Mac OS 9.", "/apps/Photoshop_7.sit", 253024603 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Adobe Photoshop LE", "Limited edition of Adobe's image editing software.", "/apps/Adobe_Photoshop_5.0_LE.sit", 16994871 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Adobe Premiere 2.1", "Early version of Adobe's pioneering desktop video editing application.", "/apps/adobe_premiere_2_1.sit", 3743580 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Adobe Premiere 4.0", "An early version of Adobe's pioneering desktop video editing software for classic Mac OS.", "/apps/Adobe_Premiere_4.0_Floppy_Set.zip", 6647370 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Adobe Premiere 5.0", "Digital video editing software release with expanded real-time preview capabilities.", "/apps/Premiere_5.0_preinstalled.sit", 4302300 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Adobe Premiere 5.1", "Adobe's professional video editing software for the Mac.", "/apps/Adobe-Premiere-5-1-1998.zip", 338496104 },
    { kCatGraphicsSound, 1994, kArchFat, 0, "Adobe Premiere Demo", "Digital video editing software, demo edition.", "/apps/adobe_premiere4.sit", 6645523 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Adobe Streamline 2.1", "Adobe's utility for converting scanned bitmap images into editable vector artwork.", "/apps/Adobe_Streamline_2.1.sit_.hqx", 542459 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Adobe Streamline 3.01", "Automatic bitmap-to-vector image tracing software from Adobe.", "/apps/Adobe_Streamline_3.01.sit", 1572198 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Adobe Streamline 3.1", "Bitmap-to-vector image tracing software from Adobe.", "/apps/Adobe_Streamline_3.1.sit", 1734326 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Adobe Streamline 4.0", "Bitmap-to-vector tracing software update from Adobe.", "/apps/AdobeStreamline_4.0.sit", 3356941 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Adobe TextureMaker 1.0", "Procedural texture generation software for creating tileable surface maps for 3D rendering.", "/apps/Adobe_TextureMaker_1.0.sit", 4047236 },
    { kCatGraphicsSound, 1989, kArch68k, 40, "Adobe Type Manager 1.01", "An early release of Adobe's extension for smoothly scaling PostScript Type 1 fonts on classic Mac OS.", "/apps/Adobe_Type_Manager_1.01.hqx", 1010541 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Adobe Type Manager 1.2", "Adobe's extension for smoothly scaling PostScript Type 1 fonts on screen and to non-PostScript printers.", "/apps/Adobe_Type_Manager_1.2.hqx", 1014869 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 60, "Adobe Type Manager 2.0", "Adobe's font rasterizer that smoothly scales PostScript Type 1 fonts on screen and to non-PostScript", "/apps/Adobe_Type_Manager_2.0.hqx", 1051718 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "Adobe Type Manager 2.02", "System extension that renders smooth PostScript Type 1 fonts on screen and in print.", "/apps/ATM_2.02.sit", 821520 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "Adobe Type Manager 2.03", "Adobe's system extension for smoothly rendering PostScript Type 1 fonts on screen.", "/apps/Adobe_Type_Manager_2.03.hqx", 1096070 },
    { kCatSystemExt, 1994, kArch68k, 60, "Adobe Type Manager 3.8", "Smooths PostScript fonts on screen at any size.", "/apps/atm_3.8.2.sit", 1073618 },
    { kCatSystemExt, 1996, kArchFat, 70, "Adobe Type Manager 3.8.1", "Later release of Adobe's font rendering extension with multiple master font support.", "/apps/ATM_3.8.1_MM_fonts.sit", 4483975 },
    { kCatSystemExt, 1998, kArchPPC, 75, "Adobe Type Manager 4.6", "Font rasterizing system extension from Adobe that smoothed PostScript Type 1 fonts on screen.", "/apps/adobe_type_manager_4.6.sit", 1801624 },
    { kCatSystemExt, 1991, kArch68k, 60, "Adobe Type Reunion 1.01", "Adobe's utility that groups font family styles into cleaner Font menus.", "/apps/Adobe_Type_Reuniontm_1.01_0.dsk", 838484 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 60, "Adobe Type Reunion 1.03", "Adobe's extension that organizes font families into hierarchical submenus in classic Mac OS application Font", "/apps/Adobe_Type_Reuniontm_1.03.dsk", 838484 },
    { kCatGraphicsSound, 1999, kArchPPC, 81, "After Dark (for Mac OS 9)", "Iconic screen saver package from Berkeley Systems, updated for Mac OS 9.", "/apps/After_Dark_for_OS_9_0.SIT", 1571490 },
    /* -- Utilities -- */
    { kCatUtilities, 1989, kArch68k, 40, "After Dark 1.0", "Berkeley Systems' original screensaver application, home of the famous flying toasters.", "/apps/After_Dark_1.0.img_.sit", 45696 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 0, "After Dark 2.0", "Berkeley Systems' iconic modular screen-saver system for classic Macintosh, version 2.0.", "/apps/AfterDark2.0t.sit", 269029 },
    /* -- Featured -- */
    { kCatFeatured, 1993, kArch68k, 60, "After Dark 3.0", "The screensaver that made flying toasters famous.", "/apps/after_dark_3.0.sit", 2847793 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 70, "After Dark 4.0", "Major release of Berkeley Systems' popular After Dark screensaver application.", "/apps/AfterDark_4.0_INT_CD_toast.sit", 191096036 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchFat, 70, "After Dark 4.94 Collection", "A later release of Berkeley Systems' iconic modular screensaver package, bundled with additional modules.", "/apps/After_Dark_4.94_Collection.sit", 129679119 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "After Dark Deluxe", "A bundled deluxe edition of Berkeley Systems' iconic modular screensaver package for classic Mac OS.", "/apps/After_Dark_Deluxe.sit", 2743273 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "After Dark Games", "Berkeley Systems' compilation of original games built around the After Dark screen-saver engine.", "/games/After_Dark_Games.sit", 25378517 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "After Dark: The Simpsons Edition", "Licensed screensaver module pack for After Dark featuring animations from The Simpsons.", "/apps/After_Dark_-_The_Simpsons.sit", 2092764 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "After Effects 1.1", "The Company of Science and Art's original motion-graphics compositing application, later acquired by Adobe.", "/apps/CoSA_After_Effects_1.1.img_.sit", 524159 },
    { kCatGraphicsSound, 1995, kArchFat, 70, "After Effects 3.1", "Adobe's motion-graphics compositing and animation application.", "/apps/Adobe_After_Effectstm_3.1.sit", 190570078 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Air Warrior 2.22b", "Early online multiplayer combat flight simulator hosted on the GEnie network.", "/games/Air_Warrior2.22b.sit", 464328 },
    { kCatGames, 1993, kArch68k, 10, "Airborne!", "Overhead paratrooper action game, popular shareware title.", "/games/Airborne.zip", 250786 },
    { kCatGames, 1996, kArchPPC, 70, "Airburst", "Physics-based bubble-popping puzzle game.", "/games/Airburst_1.053.sit", 11632453 },
    { kCatGames, 1995, kArch68k, 60, "Al Unser Jr. Arcade Racing", "MacPlay's arcade-style racing game for classic Mac OS.", "/games/al_unser_jr._arcade_racing.sit", 14986133 },
    /* -- Utilities -- */
    { kCatUtilities, 2001, kArchFat, 70, "Aladdin Expander 6.0.1", "Aladdin Systems' free decompression utility for StuffIt and other archive formats on Mac OS.", "/apps/Aladdin_Expander_6.0.1.sea_.bin", 2500608 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "Aladdin SITcomm", "Telecommunications and terminal emulation software bundled by Aladdin Systems.", "/apps/Aladdin_SITComm.sit", 1322996 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Alarming Events", "Reminders and alarms control panel.", "/apps/Alarming_Events_dc42.sit", 400674 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "Alchemy", "Early digital sound-editing shareware application.", "/apps/Alchemy26.sit", 625111 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Alchemy 2.51", "Passport Designs' digital audio sample editing software for classic Mac OS.", "/apps/Alchemy251.sea_.sit", 374517 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Alchemy 3.0", "A later version of Passport Designs' digital audio sample editing software for classic Mac OS.", "/apps/alchemy3.0_0.sit", 695775 },
    { kCatGraphicsSound, 1989, kArch68k, 40, "Aldus Digital Darkroom 2.0.1", "Grayscale image editing and scanning software from Aldus.", "/apps/AldusDigitalDarkroom2.0.1.sit", 2021105 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "Aldus Fetch 1.0", "Aldus's digital asset management and media cataloging application, distinct from the FTP client of the same", "/apps/Aldus_Fetch_1.0_Cataloger.hqx", 3630169 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 70, "Aldus Fetch 1.2", "Aldus's media cataloging and asset-management application for images and clips.", "/apps/Aldus_Fetch_v1.2_Disks.zip", 3264412 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "Aldus FreeHand", "Vector illustration application, an Illustrator rival.", "/apps/Aldus-FreeHand-4.sit", 21630283 },
    { kCatGraphicsSound, 1988, kArch68k, 30, "Aldus FreeHand 1.0", "Original release of Aldus's PostScript vector drawing program.", "/apps/freehand_1_0.zip", 2557441 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "Aldus FreeHand 2.02 (Swedish)", "Swedish-language release of Aldus FreeHand vector illustration software.", "/apps/Aldus_Freehand_2.02_Sv.sit", 761749 },
    { kCatGraphicsSound, 1990, kArch68k, 40, "Aldus FreeHand 2.x", "Vector illustration software update from Aldus Corporation.", "/apps/aldusfreehand-2x.sit", 1672717 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Aldus FreeHand 3 (German)", "An early release of the dominant professional vector illustration software for classic Mac OS, localized for", "/apps/Freehand-3_DE.sit", 1355180 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Aldus FreeHand 3.1", "Aldus's professional vector illustration application for classic Macintosh.", "/apps/aldus-freehand-31.zip", 7425341 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Aldus FreeHand 3.1.1", "An early release of the dominant professional vector illustration software for classic Mac OS.", "/apps/aldus-fh-311.sit", 3466556 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Aldus FreeHand 5.0", "The dominant professional vector illustration software for classic Mac OS, a longtime rival to Adobe", "/apps/FreeHand_5.0.x.sit_.hqx", 12038567 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Aldus FreeHand 5.5", "A later release of the dominant professional vector illustration software for classic Mac OS.", "/apps/FreeHand_5.5.img_.bin", 598108288 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "Aldus FreeHand 5.5 (Italian)", "A later release of the dominant professional vector illustration software for classic Mac OS, localized for", "/apps/Freehand_5.5_ITA_installer_0.sit", 11216202 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Aldus IntelliDraw", "Intelligent drawing application with SmartShapes from Aldus.", "/apps/aldus_intellidraw_dc63.sit", 7088101 },
    { kCatGraphicsSound, 1990, kArch68k, 70, "Aldus PageMaker", "Pioneering desktop publishing application.", "/apps/alduspagemaker42.sit", 8309140 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 20, "Aldus PageMaker 0.8 (Beta)", "Pre-release beta of Aldus PageMaker, the program that pioneered desktop publishing.", "/apps/pagemaker_08beta_dsk.zip", 203349 },
    { kCatProductivity, 1986, kArch68k, 30, "Aldus PageMaker 1.1", "Early beta of the desktop publishing program that helped launch the DTP revolution on the Macintosh.", "/apps/Aldus-PM-1-113-beta.sit", 552243 },
    { kCatProductivity, 1987, kArch68k, 21, "Aldus PageMaker 2.0", "An early release of the desktop publishing pioneer.\rRequires 512K RAM", "/apps/pagemaker_2_0a.zip", 5863716 },
    { kCatProductivity, 1988, kArch68k, 40, "Aldus PageMaker 3.0", "Desktop publishing software update adding style sheets and improved text handling.", "/apps/Pagemaker3.0Files.img_.bin", 1195136 },
    { kCatProductivity, 1988, kArch68k, 60, "Aldus PageMaker 3.0.1", "Added style sheets and long-document support.", "/apps/alduspagemaker301.sit", 1009896 },
    { kCatProductivity, 1990, kArch68k, 60, "Aldus PageMaker 3.5", "A refinement of the 3.x line, widely used through the early 90s.", "/apps/aldus_pagemaker_3.5.sit", 1448723 },
    { kCatProductivity, 1990, kArch68k, 60, "Aldus PageMaker 4.01", "Aldus's pioneering desktop-publishing application that helped launch the DTP industry.", "/apps/PageMaker401.sit", 3168408 },
    { kCatProductivity, 1991, kArch68k, 60, "Aldus PageMaker 4.2", "Early 1990s release of Aldus's pioneering desktop publishing software.", "/apps/alduspagemaker_4_2.zip", 8797298 },
    { kCatProductivity, 1993, kArch68k, 60, "Aldus PageMaker 5.0", "Aldus's professional desktop publishing and page layout application.", "/apps/Adobe-PageMaker-5.sit", 79851135 },
    { kCatProductivity, 1993, kArch68k, 60, "Aldus PageMaker 5.0 (Danish)", "Danish-language release of Aldus PageMaker 5.0 desktop publishing software.", "/apps/Aldus_PageMaker_5.0DK.sit_.hqx", 13068078 },
    { kCatProductivity, 1993, kArch68k, 60, "Aldus PageMaker 5.0a", "Added a library palette and multi-page pasteboard editing.\rRequires 68020 CPU, 5MB RAM, 40MB HD", "/apps/Aldus_PageMaker_5.0a.sit", 10011236 },
    { kCatProductivity, 1995, kArchPPC, 70, "Aldus PageMaker 6.0", "Aldus/Adobe's professional desktop publishing application.", "/apps/pagemaker_6_d_1995.sit", 21185832 },
    { kCatProductivity, 1993, kArch68k, 60, "Aldus Personal Press 2.0.2", "Consumer-oriented desktop publishing program from Aldus.", "/apps/aldus_personal_press_2.0.2.sit", 2700457 },
    { kCatProductivity, 1992, kArch68k, 60, "Aldus Persuasion 2.1", "Presentation graphics software from Aldus, a competitor to PowerPoint.", "/apps/aldus_persuasion_2.1.sit", 4241444 },
    { kCatProductivity, 1993, kArch68k, 60, "Aldus Persuasion 3.0", "Aldus's presentation-graphics application, a rival to Microsoft PowerPoint.", "/apps/Persuasion3_0.zip", 10641349 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 30, "Aldus Super 3D 2.5", "Early 3D modeling and rendering software from Aldus.", "/apps/Aldus_Super_3D_2.5.image_.sit", 143508 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Aldus SuperPaint 3.0", "SuperPaint under Aldus after acquiring it from Silicon Beach.\rRequires 2MB RAM (4MB recommended for color)", "/apps/Aldus_SuperPaint_3.0.sit", 2152552 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Aldus SuperPaint 3.5", "A later refinement of the combined bitmap/object paint program.", "/apps/aldussuperpaint3.5.sit", 2331238 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Aldus TypeTwister", "Type effects and distortion utility for creating stylized text graphics.", "/apps/aldus_type_twister.img_.sit", 735904 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Alone in the Dark", "Infogrames' pioneering 3D survival horror adventure game, ported to classic Mac OS.", "/games/AloneInTheDark.img_.sit", 7763995 },
    { kCatGames, 1995, kArch68k, 70, "Alone in the Dark 2", "Survival-horror adventure sequel pitting detective Edward Carnby against pirate ghosts, Macintosh port of", "/games/Alone_in_the_Dark_2.zip", 522904264 },
    { kCatGames, 1995, kArchPPC, 70, "Alone in the Dark 3", "Infogrames's survival horror adventure game, ported to Mac OS.", "/games/AloneInTheDark31.0.3.sit_.bin", 197779328 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArchFat, 70, "Alpha 5.63", "A popular extensible text editor favored by Mac programmers.", "/apps/Alpha_5.63.sit_.bin", 422144 },
    { kCatDevTools, 1997, kArchFat, 70, "Alpha 6.01", "Extensible text editor popular among Mac programmers, scriptable with Tcl.", "/apps/Alpha_6.01.sit_.bin", 1173504 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "Amadeus", "Shareware digital sound editor.", "/apps/amadeus-158-kaleidoscope.sit", 137238 },
    { kCatGraphicsSound, 1999, kArchPPC, 80, "Amapi 3D 4.1", "3D modeling software from TGS.", "/apps/amapi_3d_4.1.sit", 26005758 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Amazing Animation", "Claris/Edmark's kid-friendly animation and multimedia authoring program for classic Mac OS.", "/apps/amanzing_animation.sit", 5271177 },
    { kCatGraphicsSound, 2000, kArchPPC, 86, "Amazing Slow Downer 2.0.1", "A utility for changing the playback tempo of audio recordings without altering pitch, popular with musicians", "/apps/Amazing_Slow_Downer_2.0.1.sit", 255319 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "America Online 2.0.1", "Classic Macintosh client software for the America Online dial-up service.", "/apps/America_Online_2.0.1.img_.hqx", 789859 },
    { kCatInternet, 1993, kArch68k, 60, "America Online 2.1", "An earlier version of the client software for America Online, the dominant consumer online service of the", "/apps/America_Online_2.1.img_.hqx", 1111766 },
    { kCatInternet, 1994, kArch68k, 60, "America Online 2.5.1", "The client software for America Online, the dominant consumer online service of the 1990s.", "/apps/AmericaOnline2.5.1.sit", 1293443 },
    { kCatInternet, 1996, kArchPPC, 70, "America Online 3.0", "Installer for the America Online client software, version 3.0.", "/apps/InstallAOL3.0BPPC.sit", 3632310 },
    { kCatInternet, 1994, kArch68k, 60, "Anarchie 1.21", "Lightweight FTP client for the Macintosh, precursor to Interarchy.", "/apps/Anarchie-121.sit", 129804 },
    { kCatInternet, 1994, kArch68k, 70, "Anarchie 1.5", "Fast FTP client with an Archie search front end.", "/apps/Anarchie-150.sit", 505176 },
    { kCatInternet, 1994, kArch68k, 60, "Anarchie 1.6", "Early version of Peter Lewis's combined FTP client and Archie search tool.", "/apps/Anarchie-160.sit", 522692 },
    { kCatInternet, 1995, kArch68k, 70, "Anarchie 2.0", "Peter Lewis's lightweight FTP client for classic Mac OS, later evolving into Interarchy.", "/apps/anarchie.2.0.sit", 811263 },
    { kCatInternet, 1994, kArchFat, 70, "Anarchie 2.0.1", "Peter Lewis's popular shareware FTP client for classic Mac OS, later renamed Interarchy.", "/apps/Anarchie_2.0.1_FAT.sit", 811339 },
    { kCatInternet, 2001, kArchFat, 81, "Anarchie 3.6.1", "A later release of Peter Lewis's popular shareware FTP client for classic Mac OS.", "/apps/Anarchie_3.6.1_Installer.sit", 1104706 },
    { kCatInternet, 1998, kArchFat, 70, "Anarchie 3.6.2", "FTP client software update from Stairways Software.", "/apps/Anarchie_3.6.2_FAT.sit", 1228485 },
    { kCatInternet, 1997, kArch68k, 70, "Anarchie 3.7", "Stairways Software's popular FTP client, later renamed Interarchy.", "/apps/Anarchie_3.7.sit", 1234462 },
    { kCatInternet, 1997, kArch68k, 70, "Anarchie Pro", "Later, enhanced commercial version of the Anarchie FTP client.", "/apps/Anarchie-140.sit", 360531 },
    { kCatInternet, 1999, kArchFat, 70, "Anarchie Pro 3.5", "The professional edition of Peter Lewis's popular shareware FTP client for classic Mac OS.", "/apps/anarchie-pro-35.hqx", 1513119 },
    /* -- Games -- */
    { kCatGames, 1996, kArchFat, 70, "Angband 2.7.8", "Free dungeon-crawling roguelike game inspired by Tolkien's Middle-earth.", "/games/Angband_2.7.8.sit", 379720 },
    { kCatGames, 1996, kArch68k, 70, "Angst 1.2", "A freeware side-scrolling action platformer for classic Mac OS.", "/apps/angst-12.hqx", 87419 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 70, "AOL Instant Messenger 2.0.531", "AOL's instant messaging client for the classic Mac OS.", "/apps/InstallAIM_2.0.531.sit", 2417091 },
    { kCatInternet, 1996, kArch68k, 70, "AOLpress 1.2.2", "Free WYSIWYG HTML editor originally developed as NaviPress, later distributed by AOL.", "/apps/AOLpress_1.2.2_68k.bin", 2672128 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 40, "Apache Strike 1.1", "Miles Computing's helicopter combat action game.", "/games/ApacheStrike1_1.zip", 378469 },
    { kCatGames, 1994, kArch68k, 60, "Apeiron", "Ambrosia Software's fast-paced arcade shooter inspired by Defender.", "/games/Apeiron_0.bin", 3324032 },
    { kCatGames, 1993, kArch68k, 60, "Apeiron 1.0.3", "Ambrosia Software's fast-paced Asteroids-style arcade shooter.", "/games/Apeiron_1_0_3.zip", 6192008 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "Apollo 1.0", "A classic Mac OS telecommunications or online-service client application.", "/apps/Apollo-1_0.sit", 354068 },
    /* -- Utilities -- */
    { kCatUtilities, 1992, kArch68k, 70, "AppDisk", "Creates a RAM disk from an application without a control panel.", "/apps/AppDisk1.5.sit", 16656 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArchPPC, 0, "Apple Copland (Developer Release)", "Developer preview build of Copland, Apple's cancelled next-generation Mac OS.", "/apps/Copland_DR0-78.sit", 11566622 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 75, "Apple Drive Setup 1.2", "Apple's official hard-drive initialization and partitioning utility.", "/apps/Drive_Setup_1.2.sea_.bin", 184064 },
    { kCatUtilities, 1991, kArch68k, 0, "Apple HD SC Setup", "Apple's own hard disk formatting utility.", "/apps/AppleHDSCSetup.hqx", 36711 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArch68k, 75, "Apple Internet Connect Kit", "Apple's bundled software kit for configuring dial-up Internet access on classic Mac OS.", "/apps/Apple_Internet_Connect_Kit.sit", 12002468 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 70, "Apple Menu Options", "Adds hierarchical submenus to the Apple menu.", "/apps/AppleMenuOptions.hqx", 33912 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchFat, 70, "Apple MoviePlayer 2.5.1", "Apple's standalone QuickTime movie playback application.", "/apps/movieplayer251.sit", 104840 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Apple QuickTake 150 Software (French)", "Software for Apple's early QuickTake 150 digital camera, localized for French.", "/apps/Quicktake150_FR.sit", 4497412 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 70, "Apple Remote Access Client 3.0", "An earlier version of Apple's official dial-up networking client for classic Mac OS.", "/apps/ara_client_3-0.zip", 3880263 },
    { kCatInternet, 1996, kArchFat, 70, "Apple Remote Access Client 3.1.3", "Apple's official dial-up networking client for connecting a Mac to an AppleTalk or TCP/IP network over a", "/apps/ARA_Client_Only_3.1.3.smi_.bin", 1671680 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArch68k, 70, "Apple Scanner Software 2.0", "Driver and scanning application for Apple-branded flatbed scanners.", "/apps/Apple_Scanner_Software_2.0.hqx", 2123684 },
    { kCatUtilities, 1995, kArchFat, 70, "Apple System Profiler", "Reports detailed system configuration information.", "/apps/Apple_System_Profiler_1.0.1.sea_.bin", 311936 },
    { kCatUtilities, 1994, kArch68k, 70, "Apple Video Player", "Software for viewing video-in on AV Macintosh models.", "/apps/Apple_Video_Player_1.7.2.sit", 498153 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 70, "AppleScript 1.1", "Apple's system-level scripting language and automation extension.", "/apps/applescript-11-install.sit", 2158159 },
    { kCatSystemExt, 1998, kArchFat, 70, "AppleScript 1.8.3", "Apple's system-level scripting language and runtime for automating Mac applications.", "/apps/AppleScript_1.8.3.smi_.bin", 1611264 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 70, "AppleScript Developer's Toolkit", "Apple's official toolkit for developing AppleScript-scriptable applications.", "/apps/AppleScript_Developers_Toolkit.zip", 55504539 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1990, kArch68k, 40, "AppleShare 3.0", "Apple's original file server software for AppleTalk networks.", "/apps/AppleShare3.hqx", 980457 },
    { kCatInternet, 1993, kArch68k, 60, "AppleShare 3.9.2", "Apple's client software for connecting to AppleShare file servers.", "/apps/AppleShare_3.9.2.sit", 243494 },
    { kCatInternet, 1994, kArch68k, 70, "AppleShare 3.9.3", "Apple's classic Mac OS file and print server software for AppleTalk networks.", "/apps/AppleShare_3.9.3.sit", 243657 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "AppleShare 4.0", "Apple's classic file and print server software for AppleTalk networks.", "/apps/AppleShare_4.0_Install.sit_.hqx", 7140029 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArch68k, 70, "AppleShare 4.2.2", "Apple's file and print server software for AppleTalk networks.", "/apps/AppleShare_4.2.2.sit", 4785080 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "AppleShare Client", "Client software for connecting to AppleShare file servers.", "/apps/AppleShare_Client383.sit", 5122947 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "AppleShare Client 3.7.2", "Apple's client software that lets a Mac connect to and mount volumes from AppleShare file servers.", "/apps/appleshare_client_3.7.2.sit", 360608 },
    { kCatInternet, 1999, kArchPPC, 81, "AppleShare IP", "Apple's TCP/IP-based file, print, and web server software for Mac OS 9.", "/apps/AppleShare_IP_D-631_OS_9.sit", 20772036 },
    { kCatInternet, 1998, kArchPPC, 75, "AppleShare IP 5.0", "Apple's file, print, mail, and web server software suite for Mac OS-based networks.", "/apps/AppleShare_IP_5.0.zip", 16474419 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 70, "AppleTalk Remote Access", "Apple's dial-up remote networking software.", "/apps/AppleTalk_Remote_Access.sit", 507687 },
    /* -- Productivity -- */
    { kCatProductivity, 1998, kArchPPC, 75, "AppleWorks 5.0", "Integrated office suite CD-ROM, the successor product line to ClarisWorks.", "/apps/AppleWorks503CD.zip", 70065258 },
    { kCatProductivity, 1998, kArchPPC, 75, "AppleWorks 5.0.3", "Apple's integrated office application suite, the rebranded successor to ClarisWorks.", "/apps/appleworks_5.0.3.sit", 25352189 },
    { kCatProductivity, 1999, kArchPPC, 75, "AppleWorks 5.0.3 Update", "Apple's official updater for AppleWorks 5, the integrated office suite that succeeded ClarisWorks.", "/apps/AW503Upd.zip", 1623186 },
    { kCatProductivity, 2000, kArchPPC, 75, "AppleWorks 5.0.4 Update", "Apple's official updater for AppleWorks 5, the integrated office suite that succeeded ClarisWorks.", "/apps/AppleWorks_Updater_5.0.4.smi_.bin", 1343360 },
    { kCatProductivity, 2000, kArchPPC, 81, "AppleWorks 6 (Swedish)", "Apple's integrated office suite for classic Mac OS, this release localized for Swedish.", "/apps/AppleWorks_6_Swedish.dmg_.sit", 28811762 },
    { kCatProductivity, 2001, kArchPPC, 86, "AppleWorks 6.2.3 (Dutch)", "Apple's integrated office suite for classic Mac OS, this update localized for Dutch.", "/apps/AppleWorks_6.2.3_NL.sit", 63473623 },
    { kCatProductivity, 2001, kArchPPC, 81, "AppleWorks 6.2.4", "Integrated word processor, spreadsheet and drawing suite CD-ROM from Apple.", "/apps/AppleWorks624CD.ZIP", 538276617 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "AppMaker 1.6", "Generates THINK C project skeletons from resource templates.", "/apps/AppMaker_1.5.4.sit", 1285361 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 30, "Arashi 1.10", "Fast-paced arcade shoot-'em-up for the original black-and-white Macintosh, inspired by Robotron.", "/games/arashi_110_bw.img", 11064320 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1987, kArch68k, 20, "ArchiCAD 1.0", "Graphisoft's original release of ArchiCAD, the pioneering Mac-native building information modeling (BIM) CAD", "/apps/ArchiCAD_1_0.zip", 259353 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "ArchiCAD 5.0", "Graphisoft's architectural CAD and building modeling application.", "/apps/ArchiCAD_5.0v8_CD.sit", 78112783 },
    { kCatGraphicsSound, 2004, kArchPPC, 86, "ArchiCAD 8.1", "A later version of Graphisoft's pioneering building information modeling (BIM) CAD software.", "/apps/ArchiCAD_8.1_k.zip", 6695814 },
    /* -- Games -- */
    { kCatGames, 1984, kArch68k, 10, "Archon: The Light and the Dark", "Electronic Arts' hybrid chess-and-arcade-combat strategy game, one of EA's first titles.", "/games/Archon.sit", 5358647 },
    { kCatGames, 1996, kArch68k, 70, "Ares", "Ambrosia Software's shareware real-time space combat strategy game for classic Mac OS.", "/games/Ares_1.1.0_Installer.sit", 10315339 },
    { kCatGames, 1997, kArchPPC, 70, "Ares 1.1.1", "Ambrosia Software's real-time space combat strategy game.", "/games/Ares_1.1.1_Installer.sit", 10556523 },
    { kCatGames, 1991, kArch68k, 40, "Armor Alley", "Three-Sixty Pacific's helicopter and tank combat strategy/action game.", "/games/Armor_Alley_w_level_editor.sit", 300739 },
    { kCatGames, 1992, kArch68k, 60, "Armor Alley (Demo)", "Demo of the helicopter and tank combat action game set along a scrolling battlefront.", "/games/ArmorAlley_demo.sit", 318774 },
    { kCatGames, 1997, kArch68k, 70, "Arthur's 1st Grade Adventure", "The Learning Company's educational adventure starring Marc Brown's Arthur the aardvark.", "/games/Arthurs_1st_Grade_2.toast_.sit", 235275634 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchPPC, 70, "Artlantis 3.0", "Abvent's radiosity-based 3D rendering application commonly paired with ArchiCAD and VectorWorks for", "/apps/Abvent_Art-lantis_3.0.sit", 6154207 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "Asante EtherTalk 5.61", "Networking driver software for Asante Ethernet adapters on classic Macintosh.", "/apps/Asante_Ethertalk_561.hqx", 949016 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArchFat, 70, "Ashlar Vellum 2.7", "3D CAD and drafting software for precision technical illustration.", "/apps/Ashlar_Vellum_2.7_3D.sit", 4252132 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 30, "Asteroids", "Shareware clone of the Atari arcade classic Asteroids for Macintosh.", "/games/Asteroids.cpt_.sit", 10314 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 70, "Astound 2.03", "Gold Disk's multimedia presentation-authoring application.", "/apps/Astound2_03.zip", 6721555 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 40, "Astro Chase 3-D", "Arcade space shooter with vector-style 3D graphics.", "/games/astro_chase_3d.sit", 2908300 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "At Ease", "Apple's simplified, icon-based interface shell for restricting access to the Finder.", "/apps/At_Ease.sit", 9127877 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Ataxx 1.02", "A territory-capturing tile strategy puzzle game.", "/games/Ataxx_1.02.sit", 38318 },
    /* -- Utilities -- */
    { kCatUtilities, 2000, kArchPPC, 81, "ATI Displays 4.5", "ATI's display driver and control panel for its Macintosh graphics cards.", "/apps/ATI_Displays_4.5.dmg", 7171484 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 75, "AudioCatalyst", "CD ripping and MP3 encoding software from Xing Technology.", "/apps/AudioCatalyst_MP3_Encoder.sit", 1010772 },
    { kCatGraphicsSound, 2000, kArch68k, 70, "Audion 3.0.2", "An earlier version of Panic Inc's stylish and popular MP3 and audio CD player for classic Mac OS.", "/apps/Audion3.0.2.sit_.bin", 8182400 },
    { kCatGraphicsSound, 2002, kArchPPC, 86, "Audion 4.0", "Panic Inc's stylish and popular MP3 and audio CD player for Mac OS, known for its skinnable interface.", "/apps/Audion-4.0.app_.zip", 4396755 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Audioshop", "Digital audio recording and editing application.", "/apps/Audioshop_1.0.zip", 961031 },
    /* -- Productivity -- */
    { kCatProductivity, 1992, kArch68k, 60, "AutoCAD", "Autodesk's professional CAD software, briefly available for classic Mac OS.", "/apps/AutoCAD.sit_.bin", 12693120 },
    { kCatProductivity, 1993, kArch68k, 60, "AutoCAD Release 12", "Autodesk's professional computer-aided design software, Macintosh release.", "/apps/AutoCAD_Release_12.sit_.hqx", 10531794 },
    /* -- Utilities -- */
    { kCatUtilities, 1992, kArch68k, 60, "AutoDoubler", "Transparent on-the-fly file compression utility.", "/apps/Autodoubler_2.0.sit", 399478 },
    { kCatUtilities, 1992, kArch68k, 60, "AutoDoubler 2.0", "Salient Software's utility for transparently compressing files on disk to save space on classic Mac OS.", "/apps/AutoDoubler_2.0.img_.zip", 400935 },
    /* -- Games -- */
    { kCatGames, 1996, kArchFat, 70, "Avara", "Networked 3D arena combat by Ambrosia Software.", "/games/Avarazines.sit", 2035223 },
    { kCatGames, 2000, kArch68k, 70, "Avernum", "Spiderweb Software's well-known shareware fantasy role-playing game series for classic Mac OS.", "/games/Avernum_1.0.2.sit", 6754135 },
    { kCatGames, 2000, kArchPPC, 70, "Backyard Baseball 2001", "Humongous Entertainment's popular kid-friendly baseball simulation game for classic Mac OS.", "/games/backyard_baseball_2001.zip", 280325326 },
    { kCatGames, 1985, kArch68k, 0, "Balance of Power", "Chris Crawford's Cold War geopolitical strategy simulation.", "/games/Balance_of_Power_A2R.zip", 5555964 },
    { kCatGames, 2001, kArchPPC, 90, "Baldur's Gate II", "BioWare's Advanced Dungeons & Dragons computer role-playing game, Mac port.", "/games/Baldurs_Gate_ll_CD_1.toast_.sit", 570207626 },
    { kCatGames, 2002, kArchPPC, 81, "Baldur's Gate II: Shadows of Amn (CD 2)", "BioWare's acclaimed Infinity Engine role-playing game, ported to classic Mac OS by MacSoft.", "/games/Baldurs_Gate_ll_CD_2.toast_.sit", 638099026 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchFat, 70, "Band-in-a-Box 7.0", "Automatic accompaniment software that generates full backing tracks from chord charts.", "/apps/Band-in-a-Box_7.0.sit", 4121790 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 70, "Barrack", "Overhead tank strategy/action shareware game.", "/games/barrack-103.hqx", 4020150 },
    { kCatGames, 1989, kArch68k, 40, "Battle Chess 1.0.1", "Interplay's animated chess game where captured pieces battle it out, the original classic Mac OS release.", "/games/Battle_Chess_1.0.1.zip", 1423249 },
    { kCatGames, 1989, kArch68k, 40, "Battle Chess 1.0.2", "Chess game with animated battle sequences for captured pieces, Interplay's signature title.", "/games/battlechess_1_0_2.zip", 1893412 },
    { kCatGames, 1992, kArch68k, 60, "Battle Chess Enhanced CD", "Interplay's animated chess game where captured pieces battle it out, for classic Mac OS.", "/games/BattleChessEnhanced.sit", 490007708 },
    { kCatGames, 1991, kArch68k, 60, "Battle Chess Enhanced CD-ROM", "Interplay's animated chess game with battling piece sequences, enhanced CD-ROM edition.", "/games/battle_chess_enh.toast_.sit", 15914872 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "BBEdit 2.1.3", "Bare Bones Software's fast text and HTML editor popular with Mac programmers.", "/apps/bbedit_2.1.3.sit", 100938 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArch68k, 70, "BBEdit 3.1.1 CD", "An early version of Bare Bones Software's BBEdit, the widely used professional text editor for classic Mac", "/apps/BBEdit311CD.ZIP", 15403804 },
    { kCatProductivity, 1997, kArch68k, 70, "BBEdit 4.0.3 Update", "Update for Bare Bones Software's BBEdit, the widely used professional text editor for classic Mac OS.", "/apps/BBEdit_Updater_4.0.3.sit", 1765963 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 70, "BBEdit 4.0.4", "Bare Bones Software's popular text and HTML editor for programmers on classic Macintosh.", "/apps/BBEdit_4.0.4.img_.sit", 9217163 },
    { kCatDevTools, 1998, kArchFat, 70, "BBEdit 5.0.1", "Bare Bones Software's popular text and HTML editor for programmers, version 5.", "/apps/BBEdit_5.0_1.sit", 8409529 },
    { kCatDevTools, 2002, kArchPPC, 90, "BBEdit 7.1.4", "Bare Bones Software's professional text editor, this release still runs under Mac OS 9.", "/apps/BBEdit714.sitx_.bin", 9981824 },
    /* -- Productivity -- */
    { kCatProductivity, 2005, kArchPPC, 86, "BBEdit 8.1 Update", "Update for Bare Bones Software's BBEdit, the widely used professional text editor for Mac OS.", "/apps/BBEdit_8.1_Update.dmg", 12406103 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 60, "BBEdit Lite 3.5.1", "Free version of Bare Bones Software's popular text editor for the classic Mac OS.", "/apps/bbedit_lite_3.5.1.sit", 429595 },
    { kCatDevTools, 1996, kArch68k, 70, "BBEdit Lite 4.1", "The free edition of the legendary Mac text editor.", "/apps/bbedit_lite_4.1.sit", 789735 },
    { kCatDevTools, 1996, kArch68k, 70, "BBEdit Lite 4.6", "Free cut-down edition of BBEdit offering core text-editing features.", "/apps/bbedit-lite-46-smi.sit", 1659501 },
    { kCatDevTools, 2000, kArchFat, 75, "BBEdit Lite 6.1.2", "Free cut-down edition of BBEdit for both classic Mac OS and early Mac OS X.", "/apps/bbedit_lite_612.smi_.bin", 4758400 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArch68k, 70, "BBEdit Lite for OpenDoc 1.0", "A free lightweight edition of Bare Bones Software's BBEdit text editor, built as an OpenDoc component.", "/apps/BBEdit_Lite_for_Open_Doc_1.0.sit", 305231 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "BBS In A Box 16.2", "A widely distributed shareware CD-ROM compilation for Mac BBS sysops, bundling telecom software, doors, and", "/apps/BBS_in_a_Box_16-2.iso", 642183168 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "BeHierarchic", "Adds hierarchical folder menus to the Apple menu.", "/apps/BeHierarchic4.2.sit", 237504 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArchFat, 70, "BetterTelnet 2.0", "Community-developed successor to NCSA Telnet, adding SSH and improved terminal emulation.", "/apps/bettertelnetF2.0fc1.sea_.hqx", 554967 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 10, "Beyond Dark Castle", "The sequel - bigger castle, tougher trolls.", "/games/beyond_darkcastle.zip", 2615910 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArch68k, 70, "Beyond Press 4", "A professional color trapping and imposition XTension used in prepress production with QuarkXPress.", "/apps/beyond-press-4-img.sit", 9542272 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 30, "Beyond Zork", "Infocom text adventure blending RPG elements with the Zork universe.", "/games/Beyond_Zork_ZIP_Z-code.sit", 1149790 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 75, "BIAS Peak 2.6", "Digital audio editing and mastering software from BIAS.", "/apps/Peak_2.6x_folder.sit", 7910219 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 10, "Big Cursor", "Enlarges the mouse cursor for visibility.", "/apps/Big_cursor.sit", 1546 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Bill Elliott's NASCAR Challenge", "Mindscape's NASCAR stock car racing simulation.", "/games/bill_elliott_nascar.sit", 2926037 },
    { kCatGames, 1994, kArch68k, 70, "Blackthorne", "Blizzard's cinematic side-scrolling action-platformer.", "/games/Blackthorne.sit", 3183625 },
    { kCatGames, 1997, kArch68k, 70, "Blades of Exile", "Free scenario-based role-playing engine and editor from Spiderweb Software, built on the Exile series.", "/games/blades_of_exile.sit", 3837211 },
    { kCatGames, 1993, kArch68k, 60, "Bolo", "Networked tank combat game, a pioneer of Mac multiplayer.", "/games/bolo-0997.hqx", 835727 },
    { kCatGames, 1995, kArch68k, 60, "BreakThru!", "Delta Tao's arcade-style brick-breaking action game.", "/games/BreakThru.SIT", 2953738 },
    { kCatGames, 1985, kArch68k, 10, "Brickles", "Simple, addictive breakout-style brick game.", "/games/Brickles_0.sit", 161566 },
    { kCatGames, 1996, kArch68k, 70, "Broken Sword: Shadow of Templars (CD1)", "Revolution Software's point-and-click adventure following an American tourist investigating a Paris murder", "/games/Circle_of_Blood_CD1.sit", 443192864 },
    { kCatGames, 1996, kArchPPC, 70, "Broken Sword: Shadow of Templars (CD2)", "Revolution Software's conspiracy-themed graphic adventure game.", "/games/Broken_Sword_CD2.sit", 447342208 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "Bryce 1.0", "MetaTools' groundbreaking 3D landscape rendering and animation software.", "/apps/KPT_Bryce101.sit", 2279908 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Bryce 2", "MetaCreations' landmark procedural landscape and terrain 3D rendering software for classic Mac OS.", "/apps/Bryce_2_CD.zip", 278407743 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Bryce 3.0", "Later release of the Bryce 3D landscape rendering application.", "/apps/Bryce3.0d23.sit_.bin", 7552640 },
    { kCatGraphicsSound, 1999, kArchPPC, 80, "Bryce 5.01", "3D landscape and terrain rendering software from MetaCreations.", "/apps/Bryce_5.01_Installer.zip", 56108230 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Bryce Classic", "MetaTools' 3D landscape and terrain generation software.", "/apps/bryce_classic.img_.sit", 50062239 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 70, "Bubble Trouble", "Underwater bubble-popping puzzle-arcade game.", "/games/Bubble_Trouble_Fusion.sit", 693534 },
    { kCatGames, 1999, kArchPPC, 80, "Bugdom", "Pangea Software's whimsical bug-world 3D platformer.", "/games/Bugdom.dmg", 50313726 },
    { kCatGames, 1999, kArchPPC, 75, "Bugdom 1.3.3", "3D bug-themed adventure platformer from Pangea Software.", "/games/Bugdom_1.3.3_PPC.dmg", 52258496 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 10, "Business Filevision", "Graphical, map-based database application.", "/apps/Filevisionr_Business_PDS_0.sit", 6160212 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1999, kArchPPC, 75, "Butler SQL 2.1", "SQL database server software for the Macintosh used in client-server development.", "/apps/Butler_SQL_2.1_0.sit", 8644035 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 60, "CacheControl 1.2", "A control panel for managing the processor cache settings on 68030/68040 Macintosh models.", "/apps/CacheControl12.cpt", 6528 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "Cachet Color Editor 1.0.2", "A color-managed bitmap image editing application for classic Mac OS aimed at print production work.", "/apps/Cachet_Color_Editor_1.0.2.sit", 4086462 },
    { kCatGraphicsSound, 1995, kArchPPC, 70, "CADintosh 4.4", "2D computer-aided design application for technical and architectural drawing on the Mac.", "/apps/CADintosh_4.4US_PPC.sit", 2910872 },
    /* -- Games -- */
    { kCatGames, 1995, kArchFat, 70, "Caesar II", "City-building strategy game set in ancient Rome from Impressions Games.", "/games/Caesar_II_Europe.sit", 276966815 },
    { kCatGames, 1999, kArchPPC, 81, "Caesar III", "Impressions Games' city-building strategy game set in ancient Rome, ported to classic Mac OS.", "/games/Caesar_III.toast_.sit", 414417728 },
    { kCatGames, 1998, kArchFat, 70, "Caesar III (Demo)", "Demo of the Roman city-building strategy game from Impressions Games.", "/games/caesariiidemo.img_.bin", 19070336 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "CalcStrip 1.4.2", "A shareware desk-accessory-style calculator that keeps a running paper-tape style log of calculations.", "/apps/CalcStripEv1.4.2.hqx", 22319 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 70, "Cameraman 1.5", "Screen recording utility for making QuickTime movies.", "/apps/cameraman30.sit", 1504464 },
    /* -- Games -- */
    { kCatGames, 1994, kArchFat, 70, "Candy Crisis", "Falling-block puzzle game in the style of Puyo Puyo.", "/games/candycrisis_1_0.zip", 7600931 },
    { kCatGames, 1994, kArch68k, 60, "Cannon Fodder", "Sensible Software's irreverent action-strategy war game, ported to classic Mac OS.", "/games/CannonFodder.SIT", 50947 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "CanOpener", "Extracts text, sound, and pictures from any file.", "/apps/CanOpener.zip", 122066 },
    { kCatUtilities, 1993, kArch68k, 60, "CanOpener 2.5", "Abbott Systems' utility for extracting text and data from damaged or unreadable files on classic Mac OS.", "/apps/CanOpener_2.5.hqx", 312631 },
    { kCatUtilities, 1995, kArchFat, 70, "CanOpener 3.0", "Abbott Systems' utility for viewing and extracting data from damaged or unreadable files.", "/apps/CanOpener_3.0.sit", 337580 },
    { kCatUtilities, 1995, kArch68k, 60, "CanOpener 3.5", "Data recovery and file-viewing utility that could open damaged or unrecognized files.", "/apps/canopener_3.5.sit", 2478752 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "Canvas", "Combined vector illustration and image editing application.", "/apps/canvas_3.sit", 3841277 },
    { kCatGraphicsSound, 1988, kArch68k, 0, "Canvas 1.02", "Deneba Software's original combined illustration and painting application.", "/apps/Canvas_1.02_app_only.sit_.hqx", 225054 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Canvas 2.1", "Deneba Software's vector illustration and technical drawing application for classic Mac OS.", "/apps/Deneba_Canvas_2.1.img_.sit", 1104588 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Canvas 3.0", "Combined vector illustration and bitmap image editing application from Deneba Software.", "/apps/Canvastm_3.0.sit", 1811252 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Canvas 3.0.6", "Deneba Software's combined vector illustration and bitmap paint application.", "/apps/Canvas_3.0.6_Update_f.sit", 715319 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Canvas 3.5.4", "Update to Deneba's Canvas illustration and image-editing application.", "/apps/canvas_3.5.4.sit", 4487776 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Canvas 5.0", "Deneba's combined vector illustration and image-editing application.", "/apps/Deneba-Canvas-5.0-floppies.sit", 14169207 },
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Canvas 6", "Deneba's combined vector illustration and technical drawing application (trial installer).", "/apps/CANVAS6_TRIAL.zip", 367441978 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "Carbon Copy Mac 1.0.4", "Earlier release of the Carbon Copy Mac remote control utility.", "/apps/Carbon_Copy_Mac_1.0.4.hqx", 890331 },
    { kCatUtilities, 1997, kArchPPC, 75, "Carbon Copy Mac 2.0.3", "Remote control software for accessing and operating a Mac over a network.", "/apps/CarbonCopyMac2.0.3_105256.hqx", 1062230 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1999, kArchPPC, 81, "CarbonLib 1.0.4", "An early release of Apple's compatibility library that let Carbon-savvy applications run on classic Mac OS.", "/apps/CarbonLib_104.hqx", 1466391 },
    { kCatSystemExt, 2000, kArchPPC, 86, "CarbonLib 1.4", "Earlier release of the Carbon compatibility runtime library for Mac OS 9.", "/apps/CarbonLib_1.4.smi_.hqx", 3039485 },
    { kCatSystemExt, 2001, kArchPPC, 86, "CarbonLib 1.6", "Apple's compatibility library that let Carbon-savvy applications run on classic Mac OS 8.6 and 9, easing the", "/apps/CarbonLib_1.6.smi_.bin", 3141376 },
    { kCatSystemExt, 2001, kArchPPC, 86, "CarbonLib 1.6.1", "Runtime library that let Carbon applications run under classic Mac OS 9.", "/apps/CarbonLib_161.sit", 1710580 },
    /* -- Games -- */
    { kCatGames, 1998, kArchPPC, 75, "Carmageddon", "Vehicular combat racing game where pedestrians (and zombies) are fair game, ported to Power Macintosh.", "/games/Carmageddon.zip", 195580808 },
    { kCatGames, 1999, kArchPPC, 75, "Carmageddon 2: Carpocalypse Now", "Sequel vehicular-combat racer with more destructible tracks and vehicles.", "/games/Carmageddon_2_Lores_k.sit", 103623 },
    { kCatGames, 1996, kArchFat, 70, "Carmen Sandiego Word Detective", "Educational word-puzzle game in the Carmen Sandiego franchise.", "/games/carmen_word_detective.iso_.sit", 312642095 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 81, "Carrara Studio 1.1", "3D modeling and animation software from MetaCreations, later continued by Eovia.", "/apps/Carrara_Studio_1.1.sit", 56046345 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 30, "Carrier Command", "Rainbird's vehicle-based strategy/action game set aboard a futuristic aircraft carrier.", "/games/Carrier_Command.zip", 247790 },
    { kCatGames, 1991, kArch68k, 60, "Carriers at War", "SSG's operational-level naval wargame simulating carrier battles of the Pacific War, for classic Mac OS.", "/games/Carriers_At_War.img_.sit", 7147741 },
    { kCatGames, 1990, kArch68k, 0, "Casino", "Collection of classic casino card and table games.", "/games/MacCasino.SIT", 74826 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArchFat, 70, "CD-ROM Toolkit", "Driver software required for many third-party CD-ROM drives to work with classic Mac OS.", "/apps/CD-ROM_Device_Driver_3.0.4_QRW1011.sit", 530356 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArchFat, 70, "CD-ROM Toolkit 1.5.9", "FWB's driver and utility software for third-party CD-ROM drives.", "/apps/CD-ROM_Tookit_1.5.9.sit", 547040 },
    { kCatUtilities, 1996, kArchFat, 70, "CDFinder 2.8", "Norbert Heger's shareware utility for cataloging the contents of CD-ROMs and removable media for later", "/apps/CDFinder_2.8.sit", 774148 },
    { kCatUtilities, 2003, kArchPPC, 86, "CDFinder 4.6.2", "A later release of Norbert Heger's shareware utility for cataloging the contents of CDs and removable media.", "/apps/CDFinder_4.6.2.zip", 3915068 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 10, "Centipede", "Classic arcade bug-shooting action port.", "/games/centipede.sit", 40285 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "Central Point MacTools 3.0a", "Central Point Software's disk-utility and backup suite for the Mac.", "/apps/mactools_3_0a.zip", 6704706 },
    { kCatUtilities, 1992, kArch68k, 60, "Central Point MacTools Deluxe 1.1", "Deluxe edition of Central Point's Macintosh disk-utility suite.", "/apps/CP_MacTools_Deluxe_1.1.sit", 1051148 },
    { kCatUtilities, 1993, kArch68k, 70, "Central Point MacTools Pro 4", "Central Point Software's disk-utility and data-recovery suite, a Norton Utilities rival.", "/apps/MacTools-Pro-4-installed.sit", 4511744 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "Chaos Overlords", "New World Computing's turn-based gang warfare strategy game.", "/games/Chaos_Overlords.SIT", 3868479 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "ChemDraw Plus 3.1", "Chemical structure drawing software from CambridgeSoft for the classic Mac OS.", "/apps/ChemDraw_Plus_3.1.sit", 443562 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1999, kArchPPC, 70, "ChemOffice Ultra 4.0.1", "CambridgeSoft's chemistry software suite (ChemDraw, Chem3D, and ChemFinder) for classic Mac OS.", "/apps/cs_chemoffice_ultra_4.0.1.sit", 37653654 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 30, "Chessmaster 2000", "Earlier release of The Software Toolworks' Chessmaster chess simulation series.", "/games/chessmaster2000k.zip", 8727831 },
    { kCatGames, 1991, kArch68k, 60, "Chessmaster 3000", "The Software Toolworks' chess simulation and tutorial software.", "/games/Chessmaster3000.sit_.bin", 18557952 },
    { kCatGames, 1993, kArch68k, 60, "Chessmaster 4000", "The Software Toolworks' chess simulation with adjustable AI opponents.", "/games/Chessmaster4k.sit", 2677974 },
    { kCatGames, 1985, kArch68k, 20, "ChipWits", "An early and influential programming puzzle game for classic Mac OS, where players write simple robot logic", "/games/chipwits_plus.sit", 179475 },
    { kCatGames, 1992, kArch68k, 60, "Christmas Lemmings", "Free holiday-themed special edition of the classic Lemmings puzzle game.", "/games/X-Mas_Lemmings.sit", 614051 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Cinepak Codec", "The widely used QuickTime video compression codec that made playback of digitized video practical on classic", "/apps/Cinepak.sit", 207464 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "Civilization", "Turn-based empire-building strategy game from Sid Meier, the original Macintosh port.", "/games/Civilization.sit", 5178686 },
    { kCatGames, 1996, kArch68k, 70, "Civilization II", "Sequel to Civilization; turn-based strategy of empire building through the ages, Mac CD-ROM release.", "/games/Civilization_II_bin-cue.zip", 620641311 },
    { kCatGames, 1996, kArchPPC, 75, "Civilization II: Gold Edition", "MacSoft's port of Sid Meier's classic turn-based empire-building strategy game.", "/games/Civilization_II_Gold.toast_.zip", 334848727 },
    { kCatGames, 2002, kArchPPC, 81, "Civilization III (German)", "Firaxis's turn-based empire-building strategy game, this classic Mac release localized for German.", "/games/CivilizationIIICD_Ger.sit", 628340624 },
    { kCatGames, 1998, kArch68k, 70, "Clan Lord", "Delta Tao's pioneering graphical massively-multiplayer online role-playing game.", "/games/ClanLord.432.68k.bin_.gz", 302458 },
    /* -- Productivity -- */
    { kCatProductivity, 1989, kArch68k, 60, "Claris CAD", "Computer-aided design application from Claris.", "/apps/ClarisCad.sit", 883839 },
    { kCatProductivity, 1990, kArch68k, 60, "Claris CAD 2.0", "2D computer-aided design application published by Claris for the Macintosh.", "/apps/Claris_CAD_2.0v3.mar", 4193536 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "Claris Emailer", "Popular commercial email client with rules and stationery.", "/apps/Claris-Emailer-2x.sit", 12636176 },
    { kCatInternet, 1997, kArchPPC, 70, "Claris Emailer 2.0v3", "Email client from Claris supporting multiple accounts and AppleScript automation.", "/apps/claris_emailer_2.0v3.sit", 16810561 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "Claris FileMaker Pro 1.0v3", "First version of FileMaker Pro, Claris's flagship relational database application.", "/apps/Claris-FMPro-1.0v3-Eng.sit", 1493450 },
    { kCatProductivity, 1997, kArch68k, 70, "Claris Home Page 2.0", "Claris's WYSIWYG web-page authoring application.", "/apps/Claris_HomePage_2.0_Update.sit", 5074839 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArchPPC, 75, "Claris Home Page 2.0 (German)", "Claris's WYSIWYG web page authoring tool; this is the German-localized CD release.", "/apps/ClarisHomePage2CD_DE.ZIP", 363883194 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 70, "Claris Impact 1.0", "Claris's business-diagramming and idea-visualization application.", "/apps/ClarisImpact1.0Bv1.sit", 5801020 },
    { kCatProductivity, 1994, kArch68k, 70, "Claris Impact 2.0", "Updated version of Claris's business-diagramming application.", "/apps/clarisimpact_2.0v2_install.sit", 14055574 },
    { kCatProductivity, 1989, kArch68k, 60, "Claris MacWrite II", "Successor to MacWrite adding multiple fonts per document, spell checking, and mail merge.", "/apps/Claris-MacWrite-II.sit", 2945716 },
    { kCatProductivity, 1995, kArchFat, 70, "Claris Organizer", "Combined calendar, address book, and to-do manager.", "/apps/ClarisOrganizer2.sit", 3739320 },
    { kCatProductivity, 1994, kArch68k, 70, "Claris Organizer 1.0", "Personal information manager combining calendar, address book, and to-do list.", "/apps/Claris_Organizer_1.0_800k.sit", 1763188 },
    { kCatProductivity, 1991, kArch68k, 60, "Claris Resolve 1.1", "Claris's spreadsheet application with integrated statistical and charting tools.", "/apps/claris_resolve_1.1_d_1991.sit", 3113788 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 0, "ClarisDraw", "Claris's object-based drawing and illustration program.", "/apps/clarisdraw-1-nl.sit", 6424426 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "ClarisDraw 1.0v2 Updater", "Update for Claris's object-oriented vector drawing application for classic Mac OS.", "/apps/ClarisDraw_1.0v2_Updater.sea", 186452 },
    /* -- Productivity -- */
    { kCatProductivity, 1992, kArch68k, 60, "ClarisWorks 1.0", "Integrated office suite combining word processing, spreadsheet, database, and drawing modules.", "/apps/clarisworks_1.0_d_1992.sit", 1437534 },
    { kCatProductivity, 1991, kArch68k, 60, "ClarisWorks 1.0v4 (Japanese)", "A very early release of Claris's integrated office suite for classic Mac OS, localized for Japanese.", "/apps/Clarisworks1v04J.sit", 1365616 },
    { kCatProductivity, 1993, kArch68k, 60, "ClarisWorks 2.0", "Earlier version of Claris's all-in-one office suite.", "/apps/ClarisWorks20Bv1.hqx", 3147779 },
    { kCatProductivity, 1993, kArch68k, 60, "ClarisWorks 2.1", "Claris's integrated word processing, spreadsheet, and database application suite.", "/apps/clarisworks2.1.sit", 2312690 },
    { kCatProductivity, 1993, kArch68k, 60, "ClarisWorks 2.1 (Spanish)", "Claris's integrated office suite for classic Mac OS, localized for Spanish.", "/apps/ClarisWorks_2.1Ev3_ES.sit", 3792932 },
    { kCatProductivity, 1995, kArch68k, 70, "ClarisWorks 3.0", "Integrated office suite release adding a slide show module and PowerPC-ready code.", "/apps/clarisworks-3-full.sit", 5385847 },
    { kCatProductivity, 1995, kArchFat, 70, "ClarisWorks 4 (for Teachers)", "An education-bundled edition of Claris's popular integrated word processor, spreadsheet, database, and", "/apps/ClarisWorks-4-for-Teachers.sit", 55873053 },
    { kCatProductivity, 1996, kArchFat, 70, "ClarisWorks 4.0", "Later release of Claris's popular integrated office suite.", "/apps/ClarisWorks_4.0SC_Installer.sit", 4087315 },
    /* -- Featured -- */
    { kCatFeatured, 1995, kArchFat, 70, "ClarisWorks 4.0 Demo", "All-in-one word processor, spreadsheet, and database, demo.", "/apps/ClarisWorks_4.0.sit", 7861143 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArchFat, 70, "ClarisWorks 5.0", "A major release of Claris's integrated word processor, spreadsheet, database, and drawing suite for Mac OS.", "/apps/ClarisWorks5.0b.iso", 74262528 },
    { kCatProductivity, 1995, kArch68k, 60, "ClarisWorks for Kids", "A kid-friendly edition of Claris's integrated office suite with a simplified interface for classic Mac OS.", "/apps/ClarisWorksforKidsCD.ZIP", 148503197 },
    /* -- Internet & Comm -- */
    { kCatInternet, 2014, kArchPPC, 81, "Classilla 9.3.2", "A continuation of the Mozilla/Gecko browser engine specifically maintained to keep running on classic Mac OS", "/apps/Classilla9.3.2.sit", 24634934 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "ClickBook", "A specialty printing utility for classic Mac OS that reformats documents into booklets, calendars, and other", "/apps/ClickBook.hqx", 1060989 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "ClickChange", "Customizes the appearance of Finder icons and windows.", "/apps/click_change_2.sit", 1759726 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 70, "ClockSync", "Synchronizes system clock over a network.", "/apps/ClockSync_II_1.3.0.sit", 738743 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 70, "Clockwerx", "Rotating gear and track puzzle-strategy game.", "/games/ClockWerx.SIT", 2214421 },
    { kCatGames, 1996, kArch68k, 70, "Close Combat", "Atomic Games/Microsoft's tactical WWII squad-combat simulation, ported to classic Mac OS.", "/games/CloseCombat_0.sit", 21735254 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArchFat, 70, "CodeWarrior", "Metrowerks' dominant integrated development environment for classic Macintosh and PowerPC software", "/apps/CodeWarrior.iso_.zip", 221658468 },
    { kCatDevTools, 1998, kArch68k, 75, "CodeWarrior 5 Gold", "Metrowerks' flagship integrated development environment for classic Mac programming.", "/apps/CodeWarrior_5_Gold.zip", 218918765 },
    { kCatDevTools, 1998, kArchPPC, 75, "CodeWarrior 6", "Metrowerks' C/C++ IDE and compiler suite for Macintosh 68k and PowerPC development.", "/apps/CodeWarrior6.image_.zip", 815731118 },
    { kCatDevTools, 2000, kArchPPC, 81, "CodeWarrior 8 Pro", "Later release of Metrowerks' CodeWarrior IDE, supporting PowerPC and early Carbon development.", "/apps/CodeWarrior_8_Pro.toast", 697247744 },
    { kCatDevTools, 2000, kArchFat, 70, "CodeWarrior 8.1 Update", "Update for Metrowerks CodeWarrior, the dominant integrated development environment for classic Mac OS and", "/apps/CW_8.1_Update_Installer.sit", 9202204 },
    { kCatDevTools, 2001, kArchFat, 70, "CodeWarrior 8.2 Update", "Update for Metrowerks CodeWarrior, the dominant integrated development environment for classic Mac OS.", "/apps/CW_8.2_Update_Installer.sit", 22082445 },
    { kCatDevTools, 1996, kArchFat, 70, "CodeWarrior Discover Programming", "Educational bundle for learning to program with CodeWarrior.", "/apps/CodeWarrior_Discover_Programming_bundled_books.sit", 27177970 },
    { kCatDevTools, 1994, kArch68k, 60, "CodeWarrior Gold (68K)", "Metrowerks CodeWarrior integrated development environment for classic Mac OS programming.", "/apps/CodeWarrior_Gold_68k.sit", 16974940 },
    { kCatDevTools, 1996, kArchFat, 70, "CodeWarrior Lite", "Free, feature-limited edition of Metrowerks CodeWarrior for learning Mac development.", "/apps/CodeWarrior_Lite.toast_.zip", 27042472 },
    { kCatDevTools, 1996, kArchFat, 70, "CodeWarrior Pro 1 Tools", "The developer tools disc for an early release of Metrowerks CodeWarrior Pro, the dominant classic Mac OS IDE.", "/apps/CWPro1Tools.sit", 131685719 },
    { kCatDevTools, 2000, kArchFat, 70, "CodeWarrior Pro 5.1 Updater", "Update for Metrowerks CodeWarrior, the dominant integrated development environment for classic Mac OS.", "/apps/CW_Pro_5.1_updater.bin", 4612736 },
    { kCatDevTools, 1999, kArchPPC, 75, "CodeWarrior Pro 8", "Metrowerks' flagship C/C++/Java IDE for classic Mac OS development.", "/apps/CodeWarrior_8_Pro.toast_.sit", 216776098 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "Color It!", "Image editing and painting software from MicroFrontier for the classic Mac OS.", "/apps/Color-it.sit", 2514276 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Color It! 2.3.2", "MicroFrontier's affordable bitmap image editing application for classic Mac OS.", "/apps/color-it-232-img.sit", 1076048 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Color It! 3.0.6", "A mid-series release of MicroFrontier's affordable bitmap image editing application for classic Mac OS.", "/apps/Color_It_3.0.6.img_.sit", 9649761 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Color It! 3.2.4 Updater", "Update for MicroFrontier's Color It!, the affordable bitmap image editing application for classic Mac OS.", "/apps/Color_It_3.2.4_Updater.sit", 738953 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Color It! 4.0", "Full-featured image editor and paint program.", "/apps/ColorIt_4_0.img", 11488977 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "ColorIt! 3.0.4", "MicroFrontier's popular shareware color painting and image-editing application.", "/apps/ColorIt-3.0.4.sit", 2516552 },
    { kCatGraphicsSound, 1997, kArchFat, 70, "ColorIt! 3.0.8", "Shareware bitmap image editor from MicroFrontier offering layers and painting tools.", "/apps/ColorIt-3.0.8.sit", 5905367 },
    { kCatGraphicsSound, 1993, kArch68k, 90, "Colorizer", "Adds color tinting effects to black-and-white images.", "/games/Colorizer.sea_.hqx", 2685943 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Comanche", "NovaLogic's voxel-based attack helicopter combat simulation.", "/games/Comanche_1_0E17.zip", 126071951 },
    { kCatGames, 1996, kArchFat, 70, "Command & Conquer (Demo)", "Demo of Westwood Studios' genre-defining real-time strategy game.", "/games/Command_Conquer_demo.sit__0.hqx", 37102538 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "Common Ground 1.0", "A cross-platform document viewing and distribution utility, a precursor to PDF workflows.", "/apps/CommonGround1.sit_.hqx", 555109 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Commotion Pro 4.0", "Digital rotoscoping and paint software for frame-by-frame video effects from Puffin Designs.", "/apps/Install_Commotiontm_Pro_4.0.bin", 23612544 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 40, "Compact Pro 1.32", "Bill Goodman's widely used shareware file compression and archiving utility, a longtime rival to StuffIt on", "/apps/Compact_Pro_1.32.sea_.hqx", 164866 },
    { kCatUtilities, 1993, kArch68k, 60, "Compact Pro 1.50", "A later release of Bill Goodman's widely used shareware file compression and archiving utility for classic", "/apps/CompactPro1.50.sit", 148657 },
    { kCatUtilities, 1993, kArch68k, 10, "Compact Pro 1.51", "Fast, efficient archiving utility, a StuffIt alternative.", "/apps/Compact_Pro_1.51_fr.sit", 196834 },
    { kCatUtilities, 1994, kArch68k, 60, "Compact Pro 1.52", "Bill Goodman's popular shareware file compression and archiving utility.", "/apps/Compact_Pro_1.52.hqx", 461071 },
    { kCatUtilities, 1993, kArch68k, 60, "CompactPro 1.34", "Popular shareware compression utility and StuffIt alternative.", "/apps/CompactPro-1.34.sit", 117264 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "CompuServe Information Manager 2.3", "Official Mac client for accessing the CompuServe online service.", "/apps/CompuServe_2.3.sit", 947826 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 85, "Conflict Catcher", "Manages and troubleshoots INIT/extension conflicts.", "/apps/conflict_catcher9.sit", 7513004 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "Conflict Catcher 2", "An early version of Casady & Greene's extension conflict resolution utility for classic Mac OS.", "/apps/Conflict_Catcher_2.img", 838484 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "Conflict Catcher 3", "Casady & Greene's extension and control panel management utility.", "/apps/Conflict_Catcher_3.dsk", 838484 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArch68k, 70, "Conflict Catcher 4", "Casady & Greene's essential extension-conflict troubleshooting utility.", "/apps/Conflict_Catchertm_4.img_.sit", 689056 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 70, "Conflict Catcher 4.0.1", "Extension and control panel management utility for diagnosing system conflicts.", "/apps/Conflict_Catcher_401.img_.sit", 736068 },
    /* -- System Extensions -- */
    { kCatSystemExt, 2000, kArchFat, 70, "Conflict Catcher 9.0.1", "Casady & Greene's essential utility for managing, testing, and resolving conflicts among classic Mac OS", "/apps/conflict_catcher_9.0.1_full.sit", 4681085 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Conflict Catcher II 2.0.2", "Extension and control panel manager for diagnosing and resolving system extension conflicts.", "/apps/Conflict_Catcher_II_2.0.2.dsk_.zip", 351440 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1997, kArchPPC, 75, "Connectix RAM Doubler 8", "Extension that lets classic Mac OS address more usable memory than physically installed.", "/apps/Connectix-RAM-Doubler-801.sit", 218248 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 10, "Continuum", "Multiplayer 2D space combat, forerunner of SubSpace.", "/games/Continuum.sit", 97136 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 0, "Convert It", "Unit and currency conversion desk accessory.", "/apps/Convert_1.3.sit", 36112 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArchPPC, 0, "Copland Developer Release 0", "Early developer preview of Copland, Apple's ambitious and ultimately cancelled next-generation Mac OS", "/apps/Copland-DR0-non-debug.zip", 11176311 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 0, "Copy Agent", "Automates and schedules file-copy operations.", "/apps/CopyAgent1.0.smi_.sit", 1753714 },
    { kCatUtilities, 1993, kArch68k, 60, "CopyCat", "A shareware floppy disk duplication utility for classic Mac OS.", "/apps/CopyCat.sit_.hqx", 305631 },
    { kCatUtilities, 1991, kArch68k, 70, "CopyDoubler", "Speeds up and queues Finder copy operations.", "/apps/CopyDoubler1.0.hqx", 106319 },
    { kCatUtilities, 1993, kArch68k, 60, "CopyDoubler 2.0.6", "Utility that accelerated and enhanced the Finder's file copying operations.", "/apps/CopyDoubler_2.0.6.sit", 111915 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "CopyPaste 3.1.1", "Now Software's system extension for maintaining multiple named clipboards.", "/apps/CopyPaste3_1_1.bin", 256640 },
    { kCatSystemExt, 1998, kArchPPC, 75, "CopyPaste 4.2", "Later release of the system extension for maintaining multiple named clipboards.", "/apps/CopyPaste4_2_sit.hqx", 490906 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 60, "Corel Gallery", "Corel's large clip art, photo, and font collection software for classic Mac OS.", "/apps/Corel_Gallery_1_iso.sit", 681848966 },
    { kCatGraphicsSound, 1999, kArchPPC, 81, "Corel Painter 6", "Natural-media digital painting application, Corel-published edition following MetaCreations.", "/apps/Corel-Painter6-2.zip", 470875805 },
    { kCatGraphicsSound, 1996, kArchPPC, 75, "CorelDRAW 6", "Corel's vector illustration and graphic design suite for Power Macintosh.", "/apps/coreldraw6.sit", 9253710 },
    { kCatGraphicsSound, 1997, kArchPPC, 70, "CorelDRAW Graphics Suite 8", "Corel's vector illustration and graphics suite ported to the Power Macintosh.", "/apps/Corel_Graphics_8_Installer.sit", 69018409 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 40, "Correct Grammar", "Grammar and style checking software for the classic Mac OS.", "/apps/Correct_Grammar.sit_.hqx", 1016630 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 40, "Correct Quotes", "Utility from Baseline that automatically converts straight quotes to curly typographic quotes.", "/apps/Correct_Quotes.sit", 906026 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "CorrectGrammar 2.0.2", "Grammar and style-checking utility that analyzes documents for writing errors.", "/apps/correctgrammar_2_0_2.zip", 1517664 },
    { kCatProductivity, 1993, kArch68k, 60, "CorrectGrammar 3.2", "A grammar and style checking utility for word processing documents.", "/apps/CorrectGrammar3.2.sit", 852613 },
    /* -- Games -- */
    { kCatGames, 1997, kArchPPC, 75, "Creatures", "Artificial-life simulation game where players raise and evolve creatures called Norns.", "/games/creatures.zip", 57896016 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1987, kArch68k, 30, "Cricket Draw 1.0", "Cricket Software's precision vector illustration application.", "/apps/Cricket_Draw_1.0.sit", 173927 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "Cricket Draw 1.1.1", "Updated version of Cricket Software's vector illustration application.", "/apps/Cricket_Draw_1.1.1.img_.sit", 347528 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Cricket Draw III", "Computer Associates/Cricket Software's vector illustration application for classic Mac OS.", "/apps/CA-CricketDrawIII-Disks.hqx", 1507606 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "Cricket Graph 1.3", "Cricket Software's widely used charting and graphing application for classic Mac OS.", "/apps/Cricket_Graph_1.3.sit", 164650 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 40, "Cricket Graph 1.3 (German)", "Cricket Software's popular scientific and business charting application; German-localized release.", "/apps/Cricket_Graph1.3_DE.sit", 188536 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 30, "Cricket Graph 1.3.2", "Charting and graphing application for the classic Mac OS.", "/apps/cricketgraph_1_3_2.zip", 1443068 },
    /* -- Games -- */
    { kCatGames, 2000, kArchPPC, 86, "Cro-Mag Rally", "Pangea Software's prehistoric-themed kart racing game bundled with iMac computers.", "/games/Cro-Mag_Rally.dmg", 133446553 },
    { kCatGames, 2000, kArchPPC, 80, "Cro-Mag Rally (Demo)", "Demo version of Pangea Software's prehistoric-themed kart racing game.", "/games/Cro-Mag_Demo212.sit", 41408100 },
    { kCatGames, 1996, kArch68k, 60, "Crystal Caliburn", "Pinball simulation with a fantasy theme.", "/games/crystal-caliburn-103.zip", 8844595 },
    { kCatGames, 1987, kArch68k, 10, "Crystal Quest", "Fast-paced arcade shooter with dozens of levels.", "/games/crystalquest_2_2_5m.zip", 922884 },
    { kCatGames, 1987, kArch68k, 40, "Crystal Quest 2.2", "Casady & Greene's fast-paced arcade shooter, a Mac shareware classic.", "/games/crystalquest_2_2c.zip", 7813742 },
    { kCatGames, 1990, kArch68k, 60, "Crystal Quest 2.25", "Casady & Greene's fast-paced arcade shooter, a Mac gaming classic.", "/games/Crystal_Quest_225m_CD.sit", 5730040 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 70, "CU-SeeMe", "Early internet videoconferencing software.", "/apps/CU-SeeMeWin.zip", 305491 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 70, "CU-SeeMe 1.0 (Beta 10)", "Early beta of the pioneering CU-SeeMe internet videoconferencing software from Cornell University.", "/apps/CU-SeeMe-1.0b10.hqx", 563745 },
    { kCatInternet, 1998, kArchFat, 70, "CU-SeeMe 3.1", "Internet videoconferencing software supporting group video calls over IP.", "/apps/CU-SeeMe_3.1_Installer.hqx", 6226606 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "Cubase 2.5.1", "Steinberg's professional MIDI sequencing application, a major Performer rival.", "/apps/Cubase_2.5.1r3.hqx", 1301606 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "Cubase 2.51", "Steinberg's MIDI sequencing and music production software for the Macintosh.", "/apps/Cubase-251r3-f.sit", 1239552 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Cubase 3.01", "An early version of Steinberg's Cubase MIDI sequencing and music production software for classic Mac OS.", "/apps/cubase.301.sit", 1702298 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Cubase Score 2.09", "Steinberg's MIDI sequencing and notation software.", "/apps/Cubase_Score2.09k.sit", 2225359 },
    { kCatGraphicsSound, 1999, kArchPPC, 70, "Cubase VST 4", "Steinberg's landmark Virtual Studio Technology digital audio workstation software for Mac OS.", "/apps/cubase_vst_4.img_.bin", 338975488 },
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Cubase VST 4.1r2", "Virtual Studio Technology release of Cubase adding integrated audio recording and effects.", "/apps/CubaseVST_VST24_41r2.sea_.hqx", 11177423 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Cubasis", "Steinberg's entry-level MIDI sequencer aimed at home musicians.", "/apps/cubasis.sit", 931021 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArchFat, 70, "Cyberdog", "Apple's OpenDoc-based internet suite.", "/apps/cyberdog_10.sit", 2171075 },
    { kCatInternet, 1997, kArchPPC, 75, "Cyberdog 1.1", "Apple's OpenDoc-based Internet suite combining web browsing, email, and news.", "/apps/Cyberdog_1.1.sit", 5188627 },
    { kCatInternet, 1996, kArchPPC, 75, "Cyberdog 1.2.1", "Apple's OpenDoc-based Internet suite bundling a web browser, email, and news reader.", "/apps/Cyberdog_1.2.1.zip", 2481399 },
    { kCatInternet, 1997, kArchPPC, 75, "Cyberdog 2.0", "Later release of Apple's OpenDoc-based Internet suite.", "/apps/Cyberdog_2.0.zip", 5531292 },
    /* -- Games -- */
    { kCatGames, 1997, kArch68k, 70, "Cythera", "Story-driven action role-playing game.", "/games/Cythera_Installer.sit", 7056096 },
    { kCatGames, 2000, kArchPPC, 85, "Daikatana", "Ion Storm's first-person shooter spanning multiple historical eras.", "/games/Daikatana_1.3.dmg", 660081496 },
    { kCatGames, 1993, kArch68k, 60, "Damage Incorporated", "Bungie's squad-based tactical action game.", "/games/Damage_Incorporated.sit", 123874988 },
    /* -- Featured -- */
    { kCatFeatured, 1986, kArch68k, 70, "Dark Castle", "Gothic platformer classic from Silicon Beach Software.", "/games/dark_castle_color.sit", 1984007 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 0, "Dark Castle 2.1", "Silicon Beach Software's atmospheric platform-action game.", "/games/Dark_Castle_2.1.image_.hqx", 1144018 },
    { kCatGames, 1996, kArchPPC, 70, "Dark Forces", "Star Wars first-person shooter, PowerPC Mac port.", "/apps/Dark_Forces_FAQ.sit", 85598 },
    { kCatGames, 1992, kArch68k, 60, "Dark Queen of Krynn", "SSI's Dragonlance-based AD&D role-playing game, ported to classic Mac OS.", "/games/dark_queen_of_krynn.sit", 2506942 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1992, kArch68k, 60, "Dartnet", "Early campus networking client software.", "/apps/DartNet.sit", 91420 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArch68k, 60, "Data Desk 5.0", "Data Description Inc's interactive statistical analysis and data visualization software for classic Mac OS.", "/apps/DataDesk_5.0.sit", 2907521 },
    /* -- Utilities -- */
    { kCatUtilities, 2003, kArchPPC, 85, "Data Rescue 3.2.4", "Prosoft Engineering's data recovery utility for damaged or reformatted disks.", "/apps/Data_Rescue_3.2.4.zip", 10349453 },
    { kCatUtilities, 1993, kArch68k, 60, "DataFrame Utilities 8.0", "SuperMac Technology's SCSI hard drive formatting and diagnostic utility for classic Mac OS.", "/apps/DataFrame_Utilities_8.0.i.sit", 316916 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "DateBook Pro", "Personal calendar and scheduling application.", "/apps/datebook-v1.sit", 302496 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArchFat, 75, "DAVE 4.1", "Thursby Software file and print sharing client for Windows networks.", "/apps/DAVE4.1.sit_.hqx", 5009993 },
    { kCatInternet, 2001, kArchPPC, 86, "DAVE 5", "Thursby Software's SMB/CIFS networking software that let a Mac browse and share files with Windows PCs.", "/apps/Dave_5.dmg", 5765193 },
    { kCatInternet, 2001, kArchPPC, 80, "DAVE 6.0", "Updated SMB file and print sharing client letting Macs join Windows networks.", "/apps/dave60.img_.hqx", 11784592 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Day of the Tentacle (German)", "LucasArts' beloved cartoon point-and-click adventure game, this classic Mac CD release localized for German.", "/games/Day_Of_The_Tentacle_CD_Mac_German.zip", 148748516 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 30, "dBASE Mac", "Macintosh version of the dBASE relational database management system.", "/apps/dBase_Mac.sit", 2283879 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "DeBabelizer 1.6", "Equilibrium's batch image processing and format conversion application.", "/apps/debabelizer_1.6.sit", 2259331 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "DeBabelizer 1.6.5", "Batch image processing and format-conversion tool widely used by production artists.", "/apps/DeBabelizer_1.6x_-_1.6.5.sit", 1769029 },
    { kCatGraphicsSound, 1997, kArchPPC, 70, "DeBabelizer 3 (Demo)", "Demo of DeBabelizer 3, the batch image-processing and optimization utility.", "/apps/DeBabelizer_3_Demo.sit", 5239962 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "DeBabelizer 3.01", "Equilibrium's enormously powerful batch image processing and format-conversion application, a staple of", "/apps/DeBabelizer_301.sit", 11939297 },
    { kCatGraphicsSound, 1999, kArchPPC, 75, "DeBabelizer 5", "Later release of Equilibrium's batch image processing and conversion application.", "/apps/DeBabelizer5.zip", 353909334 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "DeBabelizer Lite 1.1.3", "Batch image format conversion and processing utility from Equilibrium.", "/apps/DeBabelizerLite1.1.3LEqtt.sit", 500760 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "DEC Pathworks Macintosh Client 1.3", "Digital Equipment Corporation's networking client software for connecting Macs to DEC Pathworks servers.", "/apps/DEC_Pathworks_Macintosh_Client_1.3.sit", 6509014 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 70, "Deck II 2.1", "OSC/Macromedia's digital audio multitrack recording and editing application.", "/apps/Deck_II_2.1.sit", 2304496 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Deck II 2.6.1", "OSC's digital audio multitrack recording and editing application for Macintosh.", "/apps/DECK_II_2.6.1_UPD.sit", 2016188 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Deck II 2.62", "Digital audio workstation software from BIAS for multitrack recording and editing.", "/apps/BIAS_Deck_2.62.sit", 203722716 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "Default Folder 2.1", "Remembers folders and adds shortcuts to file dialogs.", "/apps/Default-Folder-2.5.1.sit", 121419 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 70, "Default Folder 2.6.1", "St. Clair Software's file-dialog enhancement extension for classic Macintosh.", "/apps/default-folder-261.hqx", 280582 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchFat, 75, "Default Folder 2.7.3", "Utility that enhances Open and Save dialog boxes with folder shortcuts.", "/apps/DefaultFolder2.7.3.sit", 227792 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 10, "Defender of the Crown", "Medieval knight-and-castle action strategy game.", "/games/defender_of_the_crown.sit", 358146 },
    { kCatGames, 1996, kArch68k, 85, "Deimos Rising", "Mars-set 3D shareware shooter.", "/games/win_deimosrising.zip", 35239852 },
    { kCatGames, 1985, kArch68k, 10, "Deja Vu", "Film-noir graphic adventure classic.", "/games/Deja_Vu.SIT", 497953 },
    { kCatGames, 1985, kArch68k, 10, "Deja Vu 2.3", "ICOM Simulations' film-noir point-and-click mystery adventure, an early MacVenture title.", "/games/DejaVu_v2.3_Rubicon_Publishing_-_disinfected.moof", 648941 },
    { kCatGames, 1985, kArch68k, 0, "Deja Vu: A Nightmare Comes True", "ICOM Simulations' film-noir mystery MacVenture adventure game.", "/games/Deja_Vu.img_.zip", 496092 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArchFat, 70, "DeltaGraph 4.5 (Trial)", "Trial version of DeltaGraph, a scientific and business charting application.", "/apps/DeltaGraph_4.5_Trial.sit", 4863554 },
    { kCatProductivity, 1999, kArchPPC, 70, "DeltaGraph 7.1.1", "DeltaPoint's professional charting and graphing application for classic Mac OS.", "/apps/DeltaGraph711MacUpdate.dmg", 44742077 },
    { kCatProductivity, 1990, kArch68k, 0, "DeltaGraph Pro", "Charting and graphing presentation application.", "/apps/DeltaGraph1.5.sit", 427139 },
    { kCatProductivity, 1994, kArch68k, 60, "DeltaGraph Pro 3.5", "DeltaPoint's professional charting and graphing application for classic Mac OS.", "/apps/DeltaGraph_Pro_3.5.sit", 4973159 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1986, kArch68k, 20, "Deluxe Music Construction Set 1.0", "Electronic Arts' early music notation and composition software for the Macintosh.", "/apps/Deluxe_Music_Construction_Set_v1.0_moof-a-day_collection.zip", 476961 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Deneba Canvas 6", "Professional illustration, technical drawing, and image editing software from Deneba.", "/apps/deneba-canvas-6.zip", 79322657 },
    { kCatGraphicsSound, 1999, kArchPPC, 80, "Deneba Canvas 8.0", "Combined vector illustration and image editing application from Deneba Software.", "/apps/canvastm_8.sit", 38397627 },
    { kCatGraphicsSound, 2001, kArchPPC, 85, "Deneba Canvas 9 Pro", "Professional illustration and technical drawing suite from Deneba.", "/apps/Canvas-904-Pro.sit", 55839401 },
    /* -- Games -- */
    { kCatGames, 1995, kArchPPC, 70, "Descent", "Parallax Software's six-degrees-of-freedom 3D space combat game.", "/games/DESCENT_0.sit", 605879239 },
    { kCatGames, 1997, kArchPPC, 70, "Descent II", "Parallax Software's six-degrees-of-freedom 3D space shooter sequel.", "/games/Descent_II_1.2_CD.sit", 221454667 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 70, "DeskPicture 4.51", "Desktop picture and pattern display utility for classic Mac OS.", "/apps/DeskPicture4.51Installer.hqx", 779096 },
    /* -- Games -- */
    { kCatGames, 1997, kArchPPC, 75, "Diablo", "Blizzard's genre-defining dungeon-crawling action RPG, Macintosh release.", "/games/Diablo_1.08_CD.sit", 666197141 },
    { kCatGames, 1997, kArchFat, 70, "Diablo 1.0.9", "Blizzard's dungeon-crawling action role-playing game that defined the loot-driven ARPG genre.", "/games/Diablo_1_0_9.sit", 8534203 },
    { kCatGames, 2000, kArchPPC, 85, "Diablo II", "Blizzard's dark fantasy action role-playing game.", "/games/Diablo_II_Play_Disc.toast_.zip", 597300975 },
    { kCatGames, 2000, kArchPPC, 86, "Diablo II (Demo)", "Playable demo of Blizzard's dark fantasy action role-playing game, Macintosh version.", "/games/Diablo_II_Demo.sit", 35409920 },
    { kCatGames, 2001, kArchPPC, 81, "Diablo II: Lord of Destruction", "Blizzard's expansion to Diablo II, the landmark action role-playing game, for classic Mac OS.", "/games/LOD_1.13d_Carb.sit", 5765959 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1989, kArch68k, 60, "Digital Darkroom", "Early black-and-white photo editing application.", "/apps/Digital_Darkroom_1.0.zip", 926896 },
    { kCatGraphicsSound, 1995, kArchFat, 70, "Digital Performer 1.71", "Mark of the Unicorn's professional MIDI and digital audio sequencer.", "/apps/DigitPerform171.hqx", 9212791 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Digital Performer 2.7.2", "MIDI sequencing and digital audio workstation software from Mark of the Unicorn.", "/apps/Digital_Performer_2.7.2.sit", 25132303 },
    { kCatGraphicsSound, 1997, kArch68k, 81, "Digital Performer 3.0 (Mac OS 9)", "Mark of the Unicorn's professional MIDI and digital audio sequencing software, this version for classic Mac", "/apps/motu_digital_performer_3.0_os9.sit", 29297890 },
    { kCatGraphicsSound, 2004, kArchPPC, 86, "Disc Cover 3.0.11", "A CD and DVD label and jewel-case cover design and printing application for Mac OS.", "/apps/Disc_Cover_3.0.11.dmg", 55830680 },
    { kCatGraphicsSound, 2001, kArchPPC, 86, "Discus 3.13 (Demo)", "Magic Mouse Productions' CD/DVD label and jewel case design and printing software.", "/apps/discus_313_demo_mac.sit", 3128590 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1989, kArch68k, 40, "Disinfectant 1.1", "John Norstad's beloved free antivirus utility for classic Mac OS.", "/apps/Disinfectant_1.1.sit", 55306 },
    { kCatSystemExt, 1989, kArch68k, 0, "Disinfectant 1.2", "Early release of John Norstad's beloved free anti-virus INIT for classic Macintosh.", "/apps/Disinfectant-1.2.sit_.hqx", 73171 },
    { kCatSystemExt, 1991, kArch68k, 60, "Disinfectant 1.7", "Mid-era release of John Norstad's free Macintosh antivirus utility.", "/apps/Disinfectant17.sit_.Hqx", 87351 },
    { kCatSystemExt, 1990, kArch68k, 40, "Disinfectant 2.4", "John Norstad's free and widely trusted antivirus utility for the classic Mac OS.", "/apps/Disinfectant_2.4.sit", 138600 },
    { kCatSystemExt, 1993, kArch68k, 0, "Disinfectant 2.9", "John Norstad's beloved free anti-virus INIT for classic Macintosh.", "/apps/Disinfectant_v2.9.hqx", 238623 },
    { kCatSystemExt, 1992, kArch68k, 60, "Disinfectant 3.2", "John Norstad's free and hugely popular antivirus utility for classic Mac OS, a staple of the pre-web Mac", "/apps/Disinfectant_3.2.sit", 146600 },
    { kCatSystemExt, 1993, kArch68k, 60, "Disinfectant 3.3", "John Norstad's free antivirus utility that detects and removes classic Mac viruses.", "/apps/Disinfectant_3.3.sit", 150761 },
    { kCatSystemExt, 1994, kArch68k, 60, "Disinfectant 3.4.1", "Later, widely used release of the free Disinfectant antivirus utility.", "/apps/Disinfectant_3.4.1.sit", 151429 },
    { kCatSystemExt, 1994, kArch68k, 60, "Disinfectant 3.5", "Free antivirus utility for classic Mac OS written by John Norstad.", "/apps/Disinfectant-35_0.sit", 150181 },
    { kCatSystemExt, 1994, kArch68k, 60, "Disinfectant 3.6", "Later free release of the popular Mac antivirus utility.", "/apps/Disinfectant-3.6.sit", 150829 },
    /* -- Featured -- */
    { kCatFeatured, 1994, kArch68k, 60, "Disinfectant 3.7", "Free, beloved antivirus utility for classic Mac OS.", "/apps/Disinfectant371.bin", 354816 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 60, "Disk Copy 6.1.3", "Apple's official disk image creation and mounting utility for the classic Mac OS.", "/apps/DiskCopy_6.1.3.sea_.hqx", 505154 },
    { kCatUtilities, 1994, kArch68k, 60, "Disk Copy 6.3.1", "Apple's official utility for creating and mounting disk image files on classic Mac OS.", "/apps/Disk-Copy-6.3.1-img.sit", 526596 },
    { kCatUtilities, 1998, kArchPPC, 75, "Disk Copy 6.3.2", "Later release of Apple's official disk image creation and mounting utility.", "/apps/DiskCopy6.3.2.bin", 626560 },
    { kCatUtilities, 1994, kArch68k, 60, "Disk Copy 6.3.3 (French)", "Apple's official utility for creating and mounting disk image files on classic Mac OS, localized for French.", "/apps/Disk-Copy-633-fr-img.sit", 515306 },
    { kCatUtilities, 1997, kArch68k, 70, "Disk Copy 6.4", "A later version of Apple's official utility for creating and mounting disk image files on classic Mac OS.", "/apps/Disk_Copy_6.4_0.sit", 570920 },
    { kCatUtilities, 1994, kArch68k, 60, "Disk Copy 7.0", "Apple's official utility for creating and mounting disk image files on classic Mac OS.", "/apps/DiskCopy-v70.sit", 32551 },
    { kCatUtilities, 1992, kArch68k, 60, "Disk First Aid", "Apple's own disk-checking and repair utility.", "/apps/DiskFirstAid.hqx", 52956 },
    { kCatUtilities, 1990, kArch68k, 60, "Disk First Aid 1.3", "Early version of Apple's built-in disk-verification and repair utility.", "/apps/Disk_First_Aid_v1.3.hqx", 49597 },
    { kCatUtilities, 1997, kArchFat, 70, "Disk First Aid 7.2.2", "Apple's built-in disk verification and repair utility.", "/apps/Disk_First_Aid_7.2.2.sea_.bin", 53760 },
    { kCatUtilities, 1998, kArchFat, 70, "Disk First Aid 8.2", "Apple's official disk verification and repair utility bundled with classic Mac OS.", "/apps/Disk_First_Aid_8.2.smi_.bin", 339712 },
    { kCatUtilities, 1999, kArchPPC, 81, "Disk First Aid 8.6.1", "Apple's built-in disk-repair utility bundled with Mac OS.", "/apps/Disk_First_Aid_8.6.1.smi_.bin", 701824 },
    { kCatUtilities, 1994, kArchFat, 70, "DiskCopy 6.3.3", "Apple's tool for making and restoring disk images.", "/apps/Disk-Copy-633-smi.bin", 771584 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskDoubler 3.12", "Salient Software's popular file-by-file compression utility for classic Mac OS.", "/apps/DiskDoubler312.img_.sit_.bin", 380544 },
    { kCatUtilities, 1991, kArch68k, 60, "DiskDoubler 3.2", "Earlier version of Salient Software's DiskDoubler file-compression utility.", "/apps/DiskDoubler_App_3.2.sit_.hqx", 86407 },
    { kCatUtilities, 1991, kArch68k, 60, "DiskDoubler 3.7", "On-the-fly file compression utility for the classic Mac OS.", "/apps/Disk_Doubler_3.7.cpt", 191373 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskDoubler 3.7.1", "Updated release of the DiskDoubler file-compression utility.", "/apps/DiskDoubler_3.7.1.dsk_.zip", 376873 },
    { kCatUtilities, 1994, kArch68k, 60, "DiskDoubler 3.7.5", "Salient Software's transparent file compression utility.", "/apps/DiskDoubler3.7.5_0.sit", 145449 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskDoubler 3.7.6", "On-the-fly file compression utility that transparently compressed files on disk.", "/apps/DiskDoubler_3.7.6S.mac", 839040 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskDoubler 3.7.7", "Salient Software's transparent file and disk compression utility for Macintosh.", "/apps/DiskDoublertm_Disk_3.7.7.img_.sit", 590959 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskDoubler Expand 4.0", "Salient Software's file expansion companion utility for DiskDoubler-compressed files on classic Mac OS.", "/apps/DD_Expand_4.0_0.sit", 126026 },
    { kCatUtilities, 1994, kArch68k, 70, "DiskDoubler Pro 4.1", "Salient Software's file-compression utility for reclaiming disk space transparently.", "/apps/DiskDoubler_Pro_4.1.sit_.hqx", 1066394 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskDup+", "Fast floppy disk duplication utility.", "/apps/DiskDupPlus2.1.sit", 22112 },
    { kCatUtilities, 1991, kArch68k, 60, "DiskExpress II 2.03", "Earlier version of Alsoft's DiskExpress II defragmentation utility.", "/apps/DiskExpress_II_v2.03.image_.zip", 125740 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskExpress II 2.20", "Alsoft's disk-defragmentation and optimization utility.", "/apps/DiskExpress_II_-_v2.20.img", 419284 },
    { kCatUtilities, 1990, kArch68k, 60, "DiskFit", "SuperMac/Dantz's backup software for classic Mac OS, notable for its efficient incremental backup format.", "/apps/DiskFit.sit_.hqx", 141861 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskFit Direct 1.0", "Dantz Development's straightforward disk-backup utility.", "/apps/DiskFitDirect1.0.sit", 194959 },
    { kCatUtilities, 1991, kArch68k, 60, "DiskFit Pro 1.0", "Dantz Development's automated backup utility for the Mac.", "/apps/DiskFit_Pro_1.0.sit", 200573 },
    { kCatUtilities, 1992, kArch68k, 60, "DiskTools", "Small collection of disk-management utilities.", "/apps/disktools_ii.sit", 48657 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskTop 4.0", "CE Software's desk accessory for browsing and managing files without leaving the current application.", "/apps/DiskTop_4.0_SN_37725.image_.sit", 228311 },
    { kCatUtilities, 1993, kArch68k, 60, "DiskTop 4.5.1", "CE Software's desk accessory for launching applications and managing files without leaving the current", "/apps/DiskTop_4.5.1.dsk_.sit", 397011 },
    { kCatUtilities, 1998, kArchFat, 70, "DiskTracker 1.1.2", "A shareware utility for cataloging the contents of hard drives, CDs, and removable media for offline", "/apps/DiskTracker_1.1.2.sit", 613180 },
    { kCatUtilities, 1997, kArchPPC, 75, "DiskTracker 1.1.4", "A disk and volume cataloging utility for keeping track of files across removable media.", "/apps/DiskTracker_1.1.4.sit", 652576 },
    { kCatUtilities, 1998, kArchFat, 90, "DiskWarrior", "Rebuilds and optimizes corrupted disk directories.", "/apps/DiskWarrior_1.0.2.sea", 748419 },
    { kCatUtilities, 1998, kArchPPC, 75, "DiskWarrior 1.0.3", "Directory rebuilding and disk repair utility from Alsoft.", "/apps/DiskWarrior_1.0.3.sit", 452122 },
    { kCatUtilities, 1998, kArchPPC, 75, "DiskWarrior 2.1.1", "Alsoft's disk directory repair utility that rebuilds corrupted HFS/HFS+ catalogs.", "/apps/diskwarrior-211-install.sit", 2655395 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "DNS Expert", "Domain name system lookup and diagnostic utility.", "/apps/dnsexpertprofessional.hqx", 1986379 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "DOCMaker 4.1", "Freeware stack-based document authoring tool for creating standalone read-only documents.", "/apps/DOCMaker-4.1.sit", 155039 },
    { kCatUtilities, 1994, kArch68k, 70, "DoDelete 1.01", "A shareware secure-deletion utility that overwrites file data before removing it, for classic Mac OS.", "/apps/DoDelete.v101.sit_.bin", 127232 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 10, "Dollars and Sense 6.0", "Personal finance and checkbook-balancing software.", "/apps/Dollars_and_Sense.image_.sit", 188488 },
    /* -- Games -- */
    { kCatGames, 2000, kArchPPC, 70, "DOOM (D!Zone Mac 2000)", "A repackaged release of id Software's classic first-person shooter for classic Mac OS.", "/games/DOOM_DZoneMac2000.zip", 99208213 },
    { kCatGames, 1994, kArch68k, 70, "Doom 1.0.1", "Macintosh port of id Software's original Doom.", "/games/doom-i-101.hqx", 3460040 },
    { kCatGames, 1995, kArch68k, 70, "Doom II", "Macintosh port of id Software's Doom II: Hell on Earth.", "/games/doomII.SIT", 6281034 },
    { kCatGames, 1996, kArchFat, 75, "Doom II for Mac", "Mac port of the classic id Software first-person shooter sequel.", "/games/doomii.cdr_.sit", 19588439 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "DOS Mounter", "Original Alsoft utility for mounting DOS-formatted floppy disks on Macintosh.", "/apps/DOS_Mounter.sit_.hqx", 67791 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "DOS Mounter 2.0.3", "An earlier version of Software Architects' utility for reading and mounting DOS-formatted floppy disks on", "/apps/DOS_Mounter_2.0.3.hqx", 88508 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "DOS Mounter 4.1", "Updated version of Alsoft's DOS Mounter cross-platform disk utility.", "/apps/DOSMounter41.hqx", 417576 },
    { kCatSystemExt, 1996, kArch68k, 70, "DOS Mounter 95 1.0r4", "Alsoft's utility for mounting and reading DOS/Windows-formatted disks on Macintosh.", "/apps/DOSMounter95Folder1.0r4.sit", 449395 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "DOS Mounter Plus 4.1", "Software Architects' utility that lets a classic Mac read, write, and mount MS-DOS formatted floppy disks.", "/apps/DOS_Mounter_Plus_4.1.hqx", 1545998 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 40, "Dragon's Lair", "A Mac port of the famous animated laserdisc arcade game by Don Bluth.", "/games/dragonslair_floppy.zip", 6496795 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "DragStrip 3.0", "St. Clair Software's customizable application-launching toolbar utility for Macintosh.", "/apps/dragstrip-3.0.sit", 821380 },
    { kCatUtilities, 1995, kArch68k, 70, "DragThing", "Customizable floating application/document launcher.", "/apps/dragthing-29.sit", 2290601 },
    { kCatUtilities, 1994, kArch68k, 70, "DragThing 1.01", "James Thomson's shareware application and document launcher docks for classic Mac OS.", "/apps/DragThing-101_0.sit", 150569 },
    { kCatUtilities, 1998, kArchFat, 70, "DragThing 2.1", "A mid-series release of James Thomson's application and document launcher docks for classic Mac OS.", "/apps/DragThing_2.1.sit", 978697 },
    { kCatUtilities, 1999, kArchFat, 70, "DragThing 2.8", "Popular application and document launcher/dock utility for the classic Mac OS.", "/apps/DragThing_2.8.sit", 1945909 },
    { kCatUtilities, 1996, kArch68k, 70, "DragThing 2.9", "Earlier release of the DragThing launcher and dock utility.", "/apps/DragThing_2.9.sit", 2290601 },
    { kCatUtilities, 2001, kArchPPC, 81, "DragThing 4.6.1", "James Thomson's popular dock-style application and document launcher utility for Macintosh.", "/apps/dragthing-461_0.sit", 1614623 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Dreams", "Early 3D animation and rendering application.", "/apps/Dream.sit", 2036447 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "Drive Setup 1.0.5", "Apple's official hard disk initialization and partitioning utility.", "/apps/Drive_Setup_1.0.5.sea_.bin", 179712 },
    { kCatUtilities, 1994, kArch68k, 70, "Drive7", "Casa Blanca Works' third-party hard-drive formatting and driver utility.", "/apps/Drive7.image_.sit", 499196 },
    { kCatUtilities, 1996, kArch68k, 75, "Drive7 4.18", "Updated version of Casa Blanca Works' Drive7 hard-drive utility.", "/apps/Drive7_v4.18_OEM.image_.sea_.sit", 520975 },
    { kCatUtilities, 1996, kArchFat, 70, "Drive7 4.3", "Casa Blanca Works' hard drive formatting and partitioning utility for classic Macintosh.", "/apps/Drive7_v4.3.image_.sit", 517952 },
    { kCatUtilities, 1999, kArchPPC, 75, "DropStuff 5.5", "Drag-and-drop StuffIt archive creation utility from Aladdin Systems.", "/apps/dropstuff-55-installer.sit", 1964916 },
    { kCatUtilities, 2003, kArchPPC, 81, "DropStuff 8.0.2", "Compression utility from Aladdin Systems for creating StuffIt archives.", "/apps/DropStuff_Mac_8.0.2.zip", 4245086 },
    /* -- Games -- */
    { kCatGames, 1985, kArch68k, 20, "Duke It Out in D.C.", "Political satire arcade game where players box famous political figures.", "/games/Duke_it_Out_in_DC.sit", 2985641 },
    { kCatGames, 1996, kArch68k, 70, "Duke Nukem 3D", "First-person shooter port of Duke Nukem 3D for 68k Macintosh.", "/games/DukeNukem3D-68k.sit", 24674468 },
    { kCatGames, 1996, kArch68k, 70, "Duke Nukem 3D (Demo, 68k)", "68k demo version of the MacSoft port of the classic Duke Nukem 3D first-person shooter.", "/games/Duke_Nukem_3D_Demo_68k.sit_.hqx", 8230909 },
    { kCatGames, 1996, kArchPPC, 75, "Duke Nukem 3D: Duke it Out in D.C.", "An expansion pack for 3D Realms' Duke Nukem 3D set in Washington D.C.", "/games/Duke_It_Out_In_D.C.dmg", 180701032 },
    { kCatGames, 1995, kArchFat, 70, "Dungeon Master II (Demo)", "Demo of the real-time first-person dungeon-crawling role-playing game from FTL Games.", "/games/DungeonMasterII_demo.hqx", 8468106 },
    { kCatGames, 1992, kArch68k, 10, "Dungeon of Doom", "Roguelike dungeon crawler for classic Mac.", "/games/Dungeon-of-Doom.zip", 284783 },
    { kCatGames, 1988, kArch68k, 30, "Earl Weaver Baseball", "Baseball simulation game from Electronic Arts featuring managerial strategy.", "/games/earl_weaver_baseball.sit", 202950 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchFat, 70, "EarthBrowser 1.6.2", "An interactive 3D globe application showing real-time weather, time zones, and geographic data.", "/apps/earthbrowser1.6.2.us_.bin", 1848704 },
    { kCatGraphicsSound, 2003, kArchPPC, 86, "EarthBrowser 2.10.2", "A later version of the interactive 3D globe application showing real-time weather and geographic data.", "/apps/earthbrowser2.10.2.dmg", 142954 },
    /* -- Utilities -- */
    { kCatUtilities, 1992, kArch68k, 10, "Easy Envelopes", "Simple utility for printing addressed envelopes.", "/apps/EasyEnvelopes.sit", 51653 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "Eject Me Not 1.0b2", "A shareware INIT that prevents accidental ejection of removable disks from classic Mac OS.", "/apps/Eject-Me-Not-10b2.hqx", 34548 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2000, kArchPPC, 86, "Electric Image Animation System 8.0", "A professional 3D rendering and animation package used in film and broadcast production, popular on Power", "/apps/EIAS80.dmg", 85078371 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "ElectricImage 1.5.1", "High-end 3D rendering and animation software.", "/apps/ElectricImage_1.5.1.sit", 2995314 },
    { kCatGraphicsSound, 1996, kArchPPC, 75, "ElectricImage Animation System 2.8", "Professional 3D rendering and animation package used in film and broadcast production.", "/apps/electricimagetm_film_2.8r.zip", 14196406 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 40, "Emacs 1.1.7", "Port of the Emacs text editor for the classic Mac OS.", "/apps/Emacs_1.1.7.sit", 2014990 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 70, "Empire", "Turn-based strategic wargame of global conquest.", "/games/MedEmpires.sit", 157335 },
    { kCatGames, 1993, kArch68k, 60, "Empire Deluxe", "A turn-based war strategy game of global conquest.", "/games/empire_deluxe.sit", 2397474 },
    { kCatGames, 1993, kArch68k, 10, "Enchanted Scepters", "Point-and-click fantasy graphic adventure.", "/games/Enchanted_Scepters.img_.sit", 247956 },
    { kCatGames, 1983, kArch68k, 20, "Enchanter", "Infocom text adventure casting the player as a young apprentice magician, first in the Enchanter trilogy.", "/games/1_Enchanter_ZIP_Z-code_0.sit", 470201 },
    { kCatGames, 1989, kArch68k, 20, "Enchanter Trilogy", "Compilation of Infocom's Enchanter fantasy text-adventure trilogy.", "/games/enchanter_trilogy.sit", 287540 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArchPPC, 70, "Encore 3.0", "Passport Designs' music notation and score-writing software.", "/apps/Encore3.0-demo.sit", 731300 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Encore 4.1", "GVOX/Passport Designs' music notation and composition software, a longtime rival to Finale on classic Mac OS.", "/apps/Encore_4.1_CD.sit", 2760679 },
    { kCatGraphicsSound, 1996, kArch68k, 60, "Encore 4.1.1", "Music notation and score writing software from Passport Designs/GVOX.", "/apps/Encore4.1.1.sit", 2677022 },
    { kCatGraphicsSound, 1998, kArchFat, 75, "Encore 4.5.5", "GVOX/Passport's music notation and scorewriting software.", "/apps/GVOX_Encore_4.5.5.sit", 9666425 },
    /* -- Productivity -- */
    { kCatProductivity, 1989, kArch68k, 60, "EndNote 1.2b4", "Niles & Associates' bibliography and citation management software widely used by academics and researchers.", "/apps/EndNote1.2b4.sit", 52738 },
    { kCatProductivity, 1999, kArchPPC, 75, "EndNote 4", "Later release of the EndNote citation and bibliography manager.", "/apps/EndNote_4_Installer_VL.sit", 9758024 },
    { kCatProductivity, 1994, kArch68k, 60, "EndNote Plus", "Niles & Associates' bibliography and citation management software for researchers.", "/apps/EndNote_Plus.sit", 501494 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 10, "Enigma", "Puzzle game of navigating a marble through mazes.", "/games/ENIGMA.HQX", 16042 },
    { kCatGames, 2002, kArchPPC, 85, "Enigmo", "Pangea Software's physics-based fluid-flow puzzle game.", "/games/Enigmo.dmg", 20483517 },
    { kCatGames, 1988, kArch68k, 30, "Epyx Winter Games", "Multi-event winter sports simulation from Epyx.", "/games/Winter_Games.dsk_.zip", 241525 },
    { kCatGames, 1994, kArch68k, 60, "Eric's Ultimate Solitaire", "Popular shareware solitaire card game collection.", "/games/erics_ultimate_solitaire_cd.sit", 7822337 },
    { kCatGames, 1996, kArchFat, 70, "Escape Velocity", "Open-ended space trading and combat, an Ambrosia classic.", "/games/Escape_Velocity_OS_X.dmg", 31361759 },
    { kCatGames, 1996, kArchFat, 70, "Escape Velocity 1.0.1", "Space trading and combat game from Ambrosia Software with an extensible plug-in system.", "/games/EscapeVelocity1.0.1_Install.sit", 5459868 },
    { kCatGames, 1996, kArch68k, 70, "Escape Velocity 1.0.2", "Ambrosia Software's space trading, combat, and exploration game.", "/games/Escape_Velocity_1.0.2_Ins.sit", 5422576 },
    { kCatGames, 1996, kArch68k, 70, "Escape Velocity 1.0.5", "Ambrosia Software's open-ended space trading and combat game.", "/games/Escape_Velocity105.bin", 5401984 },
    { kCatGames, 2002, kArchPPC, 86, "Escape Velocity Nova", "Ambrosia Software's acclaimed space trading and combat game, a landmark shareware title for classic Mac OS.", "/games/EV_Nova_1.0.10.sit", 96395399 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArchPPC, 75, "EtherPeek 3.5", "AG Group's Ethernet network protocol analyzer for Mac OS.", "/apps/EtherPeek_3.5.sit", 2440398 },
    { kCatInternet, 1990, kArch68k, 60, "Eudora 1.3", "Early release of the Eudora POP email client for Macintosh.", "/apps/Eudora_1.3.sea_.hqx", 250675 },
    { kCatInternet, 1993, kArch68k, 60, "Eudora 1.3.1", "Early freeware version of the popular Eudora email client.", "/apps/Eudora_1.3.1.sea__0.hqx", 275591 },
    { kCatInternet, 1993, kArch68k, 60, "Eudora 1.4", "Early release of the Eudora email client for the classic Mac OS.", "/apps/Eudora_1.4.sit", 192765 },
    { kCatInternet, 1992, kArch68k, 0, "Eudora 1.4.1", "Original release of Qualcomm's pioneering email client for Macintosh.", "/apps/Eudora_1.4.1.sit", 241664 },
    { kCatInternet, 1992, kArch68k, 60, "Eudora 1.4.2", "A very early version of Qualcomm's popular Eudora email client for classic Mac OS.", "/apps/Eudora1.4.2.sit", 224985 },
    { kCatInternet, 1993, kArch68k, 60, "Eudora 1.4.3", "An early 68k-native release of the Eudora email client.", "/apps/Eudora_1.4.3.sea__0.hqx", 423991 },
    { kCatInternet, 1993, kArch68k, 60, "Eudora 1.5.2", "An early version of Qualcomm's popular Eudora email client for classic Mac OS.", "/apps/Eudora152.sit", 819493 },
    { kCatInternet, 1994, kArchFat, 70, "Eudora 1.5.3", "Qualcomm's widely used POP email client for Macintosh.", "/apps/Eudora1.5.3Fat.sit", 476245 },
    { kCatInternet, 1992, kArch68k, 60, "Eudora 2.0.2", "Email client update adding improved mailbox management.", "/apps/eudora202.hqx", 231491 },
    { kCatInternet, 1994, kArchFat, 60, "Eudora 2.0.3", "An early version of Qualcomm's popular Eudora email client for classic Mac OS.", "/apps/eudora203fat.hqx", 490965 },
    { kCatInternet, 1995, kArchFat, 70, "Eudora 2.1.2", "Earlier fat-binary release of the popular Eudora email client.", "/apps/eudora212fat.hqx", 404189 },
    { kCatInternet, 1994, kArchFat, 60, "Eudora 2.11", "Popular POP email client for the classic Mac OS, fat binary release.", "/apps/eudora211fat.hqx", 673984 },
    { kCatInternet, 1995, kArchFat, 60, "Eudora 2.14", "Popular email client release before Eudora added the Pro branding.", "/apps/eudora214fat.hqx", 600277 },
    { kCatInternet, 1998, kArchPPC, 75, "Eudora 4.3.1", "Qualcomm's popular POP email client for Mac OS.", "/apps/Eudora_431.sit", 5800292 },
    { kCatInternet, 2001, kArch68k, 70, "Eudora 4.3.3 Updater", "Update for Qualcomm's Eudora, one of the most popular email clients for classic Mac OS.", "/apps/eudora_433_updater.hqx", 5372525 },
    { kCatInternet, 2000, kArchPPC, 75, "Eudora 5.0", "Email client release adding improved spam filtering and mailbox management.", "/apps/eudora_5.0_cd.sit", 51894105 },
    { kCatInternet, 2001, kArchPPC, 85, "Eudora 5.1", "Later release of Qualcomm's Eudora email client.", "/apps/Eudora_5.1_Installer.sit", 3465302 },
    { kCatInternet, 2001, kArchPPC, 90, "Eudora 5.1.1", "Late classic-compatible release of Qualcomm's popular email client for Macintosh.", "/apps/Eudora_5.1.1_Classic.sit", 3209463 },
    { kCatInternet, 2003, kArchPPC, 86, "Eudora 6.0.2 (Classic)", "A late classic Mac OS release of Qualcomm's popular Eudora email client.", "/apps/Eudora_6.0.2_Classic.hqx", 5990772 },
    { kCatInternet, 2004, kArchPPC, 90, "Eudora 6.1.1 Classic", "Classic Mac OS build of the Eudora email client.", "/apps/Eudora_6.1.1_Classic.hqx", 5734499 },
    { kCatInternet, 1993, kArch68k, 60, "Eudora Light 1.5.5", "Early free edition of the popular Eudora email client for Macintosh.", "/apps/Eudora_Light_1.5.5.sit_.hqx", 352987 },
    { kCatInternet, 1996, kArch68k, 60, "Eudora Light 3.0.2", "Free, feature-limited edition of the popular Eudora email client for Macintosh.", "/apps/Eudora_Light_3.0.2.sit", 2220989 },
    { kCatInternet, 1996, kArch68k, 70, "Eudora Light 3.1", "Beloved freeware email client.", "/apps/Eudora_Light_3.1.sit", 2221463 },
    { kCatInternet, 1997, kArchFat, 70, "Eudora Light 3.1.1", "Free edition of the Eudora email client for Macintosh.", "/apps/Eudora_lite_3.11.sit", 1742108 },
    { kCatInternet, 1995, kArch68k, 60, "Eudora Pro 2.1.3", "Earlier release of Qualcomm's popular email client for Macintosh, professional edition.", "/apps/Eudora_Pro_2.1.3.sit", 564464 },
    { kCatInternet, 1995, kArch68k, 70, "Eudora Pro 2.1.4", "Commercial 'Pro' edition of the Eudora email client with expanded features.", "/apps/Eudora_Pro_2.1.4.img_.sit", 566495 },
    { kCatInternet, 1997, kArchFat, 70, "Eudora Pro 3.0 (Demo)", "Demo version of Qualcomm's Eudora Pro email client.", "/apps/EudoraPro_3.0_Demo_0.sit", 1814002 },
    { kCatInternet, 1998, kArchFat, 70, "Eudora Pro 4.0.1", "Qualcomm's popular email client for Macintosh, professional edition.", "/apps/Eudora_Pro_4.0.1.sit", 7050696 },
    { kCatInternet, 1994, kArch68k, 60, "eWorld", "Apple's online service client, the successor to AppleLink aimed at consumers.", "/apps/eWorld-1.sit", 2048968 },
    { kCatInternet, 1994, kArch68k, 70, "eWorld Client (1994)", "Client software and user guide for Apple's short-lived eWorld online service.", "/apps/eWorld-Official-UG-Mac-1994.sit", 51473967 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 70, "Excalibur", "Icon and cursor resource editing tool.", "/apps/Excalibur_2.6.dmg", 2621440 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArchFat, 70, "Excalibur 4.0", "A spelling checker and thesaurus add-on for Microsoft Word.", "/apps/Excalibur-4.0.sit_.hqx", 1089132 },
    { kCatProductivity, 1990, kArch68k, 60, "Excel 3.0", "Earlier version of Microsoft's spreadsheet application.", "/apps/Excel_3.0.sit", 2075144 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 60, "Executor 2.0", "PC/DOS emulator that let classic Mac OS users run MS-DOS software without a copy of DOS.", "/apps/executorv2.0.iso__0.zip", 166288681 },
    /* -- Games -- */
    { kCatGames, 1995, kArch68k, 70, "Exile", "Spiderweb Software's tile-based underground fantasy role-playing game.", "/games/Exile_Video_CD.toast_.zip", 288172989 },
    { kCatGames, 1995, kArchFat, 70, "Exile I: Escape from the Pit (1.1.2)", "Spiderweb Software's cult-classic tile-based fantasy role-playing game.", "/games/Exile_1.1.2.sit", 1276428 },
    { kCatGames, 1996, kArch68k, 70, "Exile II: Crystal Souls", "Spiderweb Software's shareware fantasy role-playing game, sequel to Exile.", "/games/Exile2Installer.zip", 2425437 },
    { kCatGames, 1996, kArch68k, 70, "Exile II: Crystal Souls 1.0.1", "Spiderweb Software's tile-based fantasy role-playing game, sequel to Exile.", "/games/exile2v101.sit", 1977754 },
    { kCatGames, 1997, kArch68k, 70, "Exile III: Ruined World", "Spiderweb Software's shareware fantasy role-playing game, third in the Exile trilogy.", "/games/Exile3Installer.zip", 3383465 },
    { kCatGames, 1997, kArchFat, 70, "Exile III: Ruined World (1.0)", "Third installment of Spiderweb Software's Exile role-playing game series.", "/games/Exile_III_v1.0.sit", 2828280 },
    { kCatGames, 1997, kArch68k, 70, "Exile III: Ruined World 1.0.2", "Third installment of Spiderweb Software's Exile role-playing series.", "/games/Exile_III_v1.0.2.sit", 2828769 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchPPC, 70, "eXodus 6.0.1", "An X Window System server that lets a Mac display and run remote Unix X11 applications.", "/apps/eXodus_6.0.1.sit", 6216388 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1985, kArch68k, 20, "ExperLogo", "Implementation of the Logo programming language for the Macintosh, popular in education.", "/apps/ExperLogo_sn016050.hqx", 514918 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 10, "Extensions Manager", "Apple's own control panel for managing startup extensions.", "/apps/Extensions_Manager_200.img_.sit", 24482 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 70, "FaceSpan 2.1", "Visual GUI builder for creating AppleScript-driven application front ends.", "/apps/facespan-21.sit", 2881339 },
    { kCatDevTools, 1996, kArch68k, 70, "FaceSpan 3.0", "AppleScript-based tool for building native Macintosh application interfaces.", "/apps/FaceSpan_3.0.img_.sit", 11474496 },
    { kCatDevTools, 1998, kArch68k, 70, "FaceSpan 3.0.1 Updater", "Update for FaceSpan, a tool for building AppleScript-driven graphical user interfaces on classic Mac OS.", "/apps/FaceSpan_Updater_3.0.1.sit", 476216 },
    { kCatDevTools, 1999, kArchPPC, 75, "FaceSpan 4.3", "A visual application builder for creating AppleScript-driven user interfaces.", "/apps/FaceSpan4.3Lite.dmg", 5513118 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 40, "Falcon", "Spectrum HoloByte's F-16 fighter jet combat flight simulator.", "/games/Falcon_2_2_2.zip", 21285725 },
    { kCatGames, 1998, kArchPPC, 75, "Fallout", "Interplay/MacPlay's post-apocalyptic role-playing game, Macintosh release.", "/games/Fallout_1_1.sit", 575318155 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArch68k, 70, "Fantasm 3.16", "A 2D cel animation and in-betweening application for classic Mac OS.", "/apps/Fantasm_3.16.sit", 876889 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Fantasm 5.3", "Cel-based 2D animation software from Not Just Software for hand-drawn style animation.", "/apps/Fantasm_5.3.sit", 8120897 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "Farallon EtherWave", "Driver software for Farallon's EtherWave Ethernet adapters.", "/apps/Farallon_EtherWave_FENI222.sit", 439448 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "Fastback II 2.10", "Fast Macintosh backup utility from Fifth Generation Systems.", "/apps/Fastback_II_2.10.hqx", 828351 },
    { kCatUtilities, 1992, kArch68k, 60, "Fastback II 2.50", "Later release of the Fastback II backup utility.", "/apps/Fastback_II_2.50.hqx", 1002617 },
    { kCatUtilities, 1991, kArch68k, 60, "Fastback Plus 2.6.1", "A classic Mac OS backup utility from the Fastback Plus family, known for its speed.", "/apps/Fastback_Plus_v2.6.1.hqx", 772214 },
    { kCatUtilities, 1992, kArch68k, 40, "Fastback Plus 3.0.1", "Backup software from Fifth Generation Systems for the classic Mac OS.", "/apps/Fastback_Plus_v3.0.1_-_Disk_2_of_2_1992.dc42", 838484 },
    /* -- Productivity -- */
    { kCatProductivity, 1999, kArchFat, 75, "FastTrack Schedule 5.01", "Project scheduling and Gantt chart software from AEC Software.", "/apps/FastTrack_Schedule_5.01.sit", 4964893 },
    /* -- Games -- */
    { kCatGames, 1993, kArchFat, 60, "Fatty Bear's Birthday Surprise", "Humongous Entertainment point-and-click adventure game for children.", "/games/FattyBearBDaySurpriseCD.sit", 83865786 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "FAXstf 3.1", "STF Technologies' popular fax send-and-receive software for classic Mac OS.", "/apps/faxstf31.sit", 5153676 },
    { kCatInternet, 1994, kArch68k, 60, "FAXstf 3.3", "A later version of STF Technologies' popular fax send-and-receive software for classic Mac OS.", "/apps/FaxSTF_3.3_.sit", 6768520 },
    { kCatInternet, 1997, kArchFat, 70, "FAXstf 5.0", "A major later version of STF Technologies' popular fax send-and-receive software for classic Mac OS.", "/apps/FAXstftm_5.0.toast_.bin", 5447808 },
    { kCatInternet, 1996, kArchFat, 70, "FAXstf Pro 5.03", "Fax send-and-receive software for the Macintosh from STF Technologies.", "/apps/FaxSTF_Pro_503.sit", 4563805 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "Ferazel's Wand", "Colorful side-scrolling platform-puzzle adventure.", "/games/ferazelswand.sit", 22675042 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "Fetch 2.1.2", "Earlier version of the classic drag-and-drop FTP client.", "/apps/Fetch2.1.sit", 125171 },
    { kCatInternet, 1996, kArchFat, 70, "Fetch 3.0.1", "Dartmouth College's widely used FTP client for classic Mac OS.", "/apps/Fetch3.0.1.sit", 335595 },
    /* -- Featured -- */
    { kCatFeatured, 1995, kArch68k, 60, "Fetch 3.0.3", "The classic drag-and-drop FTP client for the Mac.", "/apps/fetch_3.0.sit", 252166 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArchFat, 70, "Fetch 4.0.3", "Popular graphical FTP client for classic Mac OS from Dartmouth College.", "/apps/Fetch_4.0.3.sit", 1343749 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArch68k, 70, "File Buddy", "Swiss-army-knife file and type/creator editing utility.", "/apps/FileBuddy7.sit", 995625 },
    { kCatUtilities, 1997, kArch68k, 60, "File Buddy 3.4.6", "File management utility for inspecting and repairing file types, creators, and resource forks.", "/apps/File_Buddy_3.4.6.sit", 217317 },
    { kCatUtilities, 1997, kArch68k, 70, "File Buddy 5.38", "Earlier release of the File Buddy file management and inspection utility.", "/apps/filebuddy5.38.68k.sit", 688088 },
    { kCatUtilities, 1999, kArchPPC, 75, "File Buddy 7.1", "Advanced file management utility for manipulating file types, creators, and permissions.", "/apps/File_Buddy_7.1_.sit", 936826 },
    { kCatUtilities, 2000, kArchPPC, 75, "File Buddy 7.6.3", "A file management and troubleshooting utility for inspecting file types, creators, and permissions.", "/apps/File_Buddy_7.6.3_.sit", 5920699 },
    { kCatUtilities, 2002, kArchPPC, 85, "File Salvage 3.0", "SubRosaSoft's data recovery utility for retrieving files from damaged or erased disks.", "/apps/FileSalvage_3.0.zip", 4068905 },
    { kCatUtilities, 1994, kArch68k, 60, "FileGuard 2.9.5", "ASD Software's security and access-control utility for restricting and logging access to a classic Mac.", "/apps/FileGuard_2.9.5.sit", 565471 },
    /* -- Productivity -- */
    { kCatProductivity, 2001, kArchFat, 81, "FileMaker Developer 5.5", "The developer edition of FileMaker Pro, letting developers build and distribute standalone runtime database", "/apps/FileMaker_Developer_5.5.toast_.zip", 89284636 },
    { kCatProductivity, 1988, kArch68k, 40, "FileMaker II", "Claris's easy-to-use flat-file database application, predecessor to FileMaker Pro.", "/apps/filemaker_ii.sit", 359492 },
    { kCatProductivity, 1988, kArch68k, 40, "FileMaker II 1.0", "Flat-file database manager from Claris, the direct predecessor to FileMaker Pro.", "/apps/FileMaker-II-1-0.sit", 593282 },
    { kCatProductivity, 1988, kArch68k, 40, "FileMaker II 1.1", "An early release of Claris's FileMaker relational database application.", "/apps/FileMaker-II-1-1v2.sit", 602606 },
    { kCatProductivity, 2001, kArchPPC, 81, "FileMaker Mobile", "Claris/FileMaker Inc's companion software for syncing FileMaker Pro databases with Palm OS handheld devices.", "/apps/FileMaker_Mobile.toast_.sit", 7400980 },
    { kCatProductivity, 1990, kArch68k, 60, "FileMaker Pro 1.0", "First version of Claris's FileMaker Pro flat-file database, successor to FileMaker II.", "/apps/filemaker_pro_1.sit", 883064 },
    { kCatProductivity, 1992, kArch68k, 60, "FileMaker Pro 2.1", "An early version of Claris's widely used flat-file database application for classic Mac OS.", "/apps/FileMaker_Pro_2.1.sit", 1371539 },
    { kCatProductivity, 1993, kArch68k, 60, "FileMaker Pro 2.1v3", "Database management application update adding scripting and layout improvements.", "/apps/filemaker_pro_2.1v3_0.sit", 2051510 },
    { kCatProductivity, 1995, kArchFat, 70, "FileMaker Pro 3.0", "Major FileMaker Pro release adding relational lookups across multiple files.", "/apps/FileMaker_Pro_3-0Bv2_0.zip", 4226877 },
    { kCatProductivity, 1995, kArchFat, 70, "FileMaker Pro 3.0 Demo", "Popular flat-file database, demo edition.", "/apps/FileMaker_Pro_3.0_V2_Fr.sit", 4285514 },
    { kCatProductivity, 1995, kArchFat, 70, "FileMaker Pro 3.0.1", "Claris's relational database application, version 3.0.1.", "/apps/filemaker301_0.sit", 46421476 },
    { kCatProductivity, 1997, kArchFat, 70, "FileMaker Pro 4.0", "Database application update adding Web publishing capability.", "/apps/filemaker_pro_4.0.sit", 23170213 },
    { kCatProductivity, 1998, kArch68k, 75, "FileMaker Pro 4.1", "Later version of the popular FileMaker Pro database application.", "/apps/FileMaker_Pro_41_img.sit", 38088760 },
    { kCatProductivity, 1998, kArchPPC, 70, "FileMaker Pro 4.1 (French)", "Claris/FileMaker Inc's widely used flat-file database application for classic Mac OS, localized for French.", "/apps/FMPRO41_French.ISO", 351723520 },
    { kCatProductivity, 1999, kArchPPC, 75, "FileMaker Pro 5", "Claris/FileMaker's relational database application for building custom data-driven layouts.", "/apps/FileMakerPro5CD.ZIP", 90086884 },
    { kCatProductivity, 2000, kArchPPC, 75, "FileMaker Pro 5.5", "Later release of Claris/FileMaker's relational database application.", "/apps/FileMaker_Pro_5.5_CD.iso", 100642816 },
    { kCatProductivity, 2001, kArchFat, 81, "FileMaker Pro 5.5v2 Updater", "Update for Claris/FileMaker Inc's widely used flat-file database application for Mac OS.", "/apps/FileMaker_Pro_5.5v2_Updater.sea_.sit", 3185666 },
    { kCatProductivity, 2002, kArchPPC, 81, "FileMaker Pro 6", "Database application installer disc for FileMaker Pro 6, the last classic-Mac-OS-era major release.", "/apps/FileMaker_Pro_6.iso", 542400512 },
    { kCatProductivity, 1997, kArchFat, 70, "FileMaker Pro Server 3.0", "Claris's dedicated multi-user server for hosting shared FileMaker Pro databases over a network.", "/apps/filemaker_pro_server_3.0.img_.sit", 588243 },
    { kCatProductivity, 1999, kArchPPC, 81, "FileMaker Pro Server 5.0", "Server edition of FileMaker Pro for hosting shared databases over a network.", "/apps/Filemaker_Pro_5.0v1_Server.toast", 3975168 },
    { kCatProductivity, 1984, kArch68k, 10, "Filevision", "Pictorial database program that lets users organize information as clickable graphic objects.", "/apps/Filevision_ver_1_PDS_2.sit", 2120183 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2001, kArchPPC, 90, "Final Cut Pro 2.0", "Professional non-linear video editing application from Apple.", "/apps/finalcut_pro_2.0.sit", 14402894 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "Final Doom", "id Software's Final Doom expansion campaigns, ported to classic Mac OS.", "/games/Final_DOOM.cdr_.zip", 18407220 },
    /* -- Productivity -- */
    { kCatProductivity, 1998, kArch68k, 70, "Final Draft 4.1.3", "An earlier version of the industry-standard screenwriting software for formatting film and television", "/apps/Final_Draft_4.1.3.sit", 2207106 },
    { kCatProductivity, 2001, kArchPPC, 86, "Final Draft 6", "The industry-standard screenwriting software for formatting film and television scripts.", "/apps/Final_Draft_6-k.app_.sit", 4276766 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 40, "Finale 1.0", "First release of Coda Music's Finale, the professional music notation software.", "/apps/Finale_1.0.mar", 3278336 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Finale 2.0.1", "Update to Coda's Finale music notation and composition software.", "/apps/Finale_2.0.1.hqx", 1570168 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Finale 3.0", "An early release of Coda Music's Finale, the professional music notation and composition software.", "/apps/Finale30.sit", 2026413 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Finale 3.0.1 Updater", "Update for Coda Music's Finale, the professional music notation and composition software.", "/apps/Finale_3.0.1_Updater.sit", 285312 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "Finale 3.2.1 Updater", "Update for Coda Music's Finale, the professional music notation and composition software.", "/apps/Finale_3.2.1_Updater_.sit", 217281 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Finale 3.7", "Music notation software release adding improved MIDI playback and engraving tools.", "/apps/Finale3.7.sit", 4032817 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Finale 98", "Professional music notation and score engraving software.", "/apps/Finale_98.sit", 21551133 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArch68k, 80, "FinderPop", "Adds a hierarchical contextual menu to the Finder.", "/apps/finderpop.hqx", 549879 },
    { kCatUtilities, 1999, kArchFat, 70, "FinderPop 1.8.9", "A widely used freeware extension adding a customizable hierarchical contextual menu to the classic Mac OS", "/apps/FinderPop189F.sit", 514652 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "FirstClass Client", "Client for the popular FirstClass BBS/groupware system.", "/apps/FirstClass_Client_3.51.sit", 1093312 },
    { kCatInternet, 1996, kArchFat, 70, "FirstClass Server 3.5", "Groupware and BBS server software providing email, conferencing, and file sharing.", "/apps/FirstClass_Server_3.5_3.5_In-A-Box_1.0.sit", 2391939 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "FKey Manager 3.0", "A shareware utility for installing, organizing, and running Function-key (FKey) resources on classic Mac OS.", "/apps/FKeyManager3.0.hqx", 128651 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2002, kArchPPC, 81, "Flash Player 6", "Macromedia's browser plug-in for viewing Flash vector animation and interactive content on Mac OS.", "/apps/Flash_Player_6.sit", 663526 },
    /* -- Utilities -- */
    { kCatUtilities, 1992, kArch68k, 60, "Flash-It 3.0.2", "Screen capture utility with adjustable compression.", "/apps/Flash-It3.0.2.sit", 76845 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 0, "Flight Simulator", "Microsoft's classic Mac flight simulator.", "/games/Flight_Simulator_1.SIT", 231298 },
    { kCatGames, 1997, kArch68k, 70, "fMSX 1.5", "Marat Fayzullin's MSX home computer emulator ported to classic Mac OS.", "/apps/fmsx-15.sit_.hqx", 722967 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "FolderBolt Pro 1.0.3", "Kent Marsh's folder-level access control and encryption security software for classic Mac OS.", "/apps/FolderBolt_Pro_1.0.3.hqx", 1052057 },
    { kCatUtilities, 1998, kArchPPC, 75, "Font Reserve 2.0", "Font management utility for organizing and activating fonts on the classic Mac OS.", "/apps/Font-Reserve-2x.sit", 10173382 },
    { kCatUtilities, 1990, kArch68k, 40, "Font/DA Juggler Plus", "ALSoft's utility for managing and switching between font and desk accessory suitcases on classic Mac OS.", "/apps/Font_DA_Juggler_Plus.zip", 311005 },
    { kCatUtilities, 1985, kArch68k, 10, "Font/DA Mover", "Apple's classic utility for installing fonts and desk accessories.", "/apps/FontDAMover41.hqx", 57072 },
    { kCatUtilities, 1987, kArch68k, 20, "Font/DA Mover 3.8", "Apple's original utility for installing fonts and desk accessories into the System file.", "/apps/FontDA_Mover_v3.8.sit", 21655 },
    { kCatUtilities, 1988, kArch68k, 30, "Fontastic", "Bitmap font editing utility for classic Mac OS.", "/apps/Fontastic.img_.bin", 410368 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "Fontographer 2.41", "Font design and editing software from Altsys.", "/apps/Fontographer-v241.zip", 429910 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Fontographer 3.1", "Altsys's professional font design and editing application.", "/apps/Fontographer_3.1_Folder.sit", 502272 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Fontographer 4.0", "Type design software update adding multiple master font support.", "/apps/Fontographer-4-Disk-2.sit", 753864 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "Fontographer 4.1.5", "Macromedia's professional font-design and editing application.", "/apps/Fontographer_4.1.5-Multi.sit", 5709216 },
    { kCatGraphicsSound, 2002, kArchPPC, 86, "Fontographer 4.7.3", "The industry-standard font design and editing application for classic Mac OS, originally by Altsys.", "/apps/Fontographer_4.7.3_Installer.dmg", 32845220 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Fontographer 5.0", "Professional font design and editing software for creating and modifying typefaces.", "/apps/Fontographer_5.0.zip", 14223852 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "form-Z 2.7", "AutoDesSys's advanced solid/surface 3D modeling application for architecture and design.", "/apps/Form-Z_2.7_-_disk_images.sit", 4312649 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "form-Z RenderZone 3.0", "Rendering-focused edition of AutoDesSys's form-Z 3D modeling application.", "/apps/form_z_rz_3.0.sit", 10329161 },
    { kCatGraphicsSound, 1996, kArchPPC, 75, "form•Z 3.0.1", "3D solid and surface modeling CAD software from AutoDesSys.", "/apps/Form-Z_3.0.1.sit", 10329161 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 30, "FoxBASE+/Mac", "dBASE-compatible database management system for the classic Mac OS.", "/apps/FoxBASEMac.image_.sit_.hqx", 1069258 },
    { kCatProductivity, 1988, kArch68k, 40, "FoxBASE+/Mac 2.00", "Relational database management system for the Macintosh, a predecessor to FoxPro.", "/apps/FoxBASE_2.00.img_.sit", 703528 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 70, "Fractal Design Dabbler 2.0", "Beginner-friendly natural-media painting program from Fractal Design.", "/apps/Dabbler_2.0_Installer.sea_.zip", 9950531 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Fractal Design Painter 2.0", "Early release of Fractal Design's natural-media painting software.", "/apps/Painter_2.0_Demo.sit", 1772875 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Fractal Design Painter 3.1 (German)", "Fractal Design's natural-media painting application, prized for its realistic brushes; German-localized", "/apps/Painter31_DE.sit", 17254720 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Fractal Design Painter 5", "Later release of the natural-media digital painting application.", "/apps/Painter_5_CD.zip", 343098139 },
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Fractal Design Painter 6", "Major release of the Painter natural-media painting application.", "/apps/PainterEN6_and_6.1_Inst_pl_No.sit", 80815497 },
    { kCatGraphicsSound, 1995, kArchFat, 70, "Fractal Design Painter Classic (Demo)", "Demo of the natural-media painting program simulating oils, watercolor, and other traditional media.", "/apps/Painter_Classic_Demo.sit", 28154867 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "FrameMaker 3.0", "Long-document publishing software from Frame Technology used for technical documentation.", "/apps/FrameMaker_3.sit__0.bin", 3537664 },
    { kCatProductivity, 1994, kArch68k, 70, "FrameMaker 4.02", "Technical document publishing software update supporting structured document templates.", "/apps/Install-FrameMaker-402-68k.sit", 37112713 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 70, "Freddi Fish (Japanese)", "Humongous Entertainment's underwater point-and-click adventure for kids; Japanese-language release.", "/games/FreddiFish-J.iso_.sit", 125093480 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 70, "FreeHand 5.5", "Macromedia's professional vector illustration application, a longtime Illustrator rival.", "/apps/m-freehand-55.sit", 10782186 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "FreeHand 8.0 (Trial)", "Trial edition of Macromedia FreeHand 8, a later PowerPC-native release.", "/apps/FreeHand_8.0_Trial.sit", 7294773 },
    /* -- Games -- */
    { kCatGames, 1998, kArch68k, 70, "FreeMSX 1.0b", "A freeware MSX computer emulator for classic Mac OS.", "/apps/freeMSX1.0b.sit_.hqx", 245045 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArch68k, 70, "FreePPP 2.5", "A widely used free PPP dial-up networking control panel for connecting classic Mac OS to the internet.", "/apps/FreePPP_2.5.sit", 238887 },
    { kCatInternet, 1998, kArch68k, 70, "FreePPP 2.6.2", "A later release of the widely used free PPP dial-up networking control panel for classic Mac OS.", "/apps/FreePPP_2.6.2.sit_.hqx", 815717 },
    { kCatInternet, 2001, kArchPPC, 81, "Freeway 2.0.3 LE", "Visual web page design and HTML authoring software from SoftPress.", "/apps/Freeway_2.0.3_LE.sit", 19837759 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "Frenzy", "Overhead shoot-em-up with cooperative play.", "/games/Frenzyao.hqx", 27519 },
    { kCatGames, 1998, kArchPPC, 75, "Frogger", "Hasbro Interactive's Macintosh port of the classic arcade road-and-river-crossing game.", "/games/FROGGER.toast", 16052224 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1999, kArchPPC, 81, "Frontier 10.1a6", "UserLand Frontier scripting and web content management environment for Mac OS 9.", "/apps/Frontier_v10.1a6_MacOS9.sit", 627485 },
    { kCatDevTools, 1996, kArch68k, 70, "Frontier 4.2", "UserLand Software's scripting environment and object database for automating classic Mac OS, created by Dave", "/apps/Frontier-42-img.sit", 2158285 },
    { kCatDevTools, 1999, kArchPPC, 75, "Frontier 4.2.1", "Updated release of UserLand's Frontier scripting and content-management environment.", "/apps/Frontier_4.2.1_Upgrade.sit", 149024 },
    { kCatDevTools, 1999, kArchPPC, 75, "Frontier 5.0.1", "UserLand Software's scripting environment and object database for automation and web publishing.", "/apps/Frontier_5.0.1.sit", 2253761 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArch68k, 70, "FTPShare 3.1.4", "Software that turns a classic Mac into an FTP server, letting remote users upload and download files.", "/apps/FTPShare_3.1.4.sit", 148009 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "Full Impact", "Ashton-Tate's high-end spreadsheet application.", "/apps/Full_Impact.sit", 1498562 },
    /* -- Games -- */
    { kCatGames, 1995, kArch68k, 70, "Full Throttle", "LucasArts' biker-gang graphic adventure starring Ben, voiced by Mark Hamill.", "/games/Full_Throttle_iso.sit", 269214642 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "FullWrite 2.06", "Later version of the FullWrite word processor.", "/apps/fullwrite206installer.sit", 1405771 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1988, kArch68k, 10, "FullWrite Professional", "Advanced word processor with page layout features.", "/apps/FullWriteProfessional1.1.zip", 1398356 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 30, "FullWrite Professional 1.0", "Full-featured word processor known for its long-document and outlining tools.", "/apps/FullWrite_Professional_10.zip", 2142072 },
    { kCatProductivity, 1988, kArch68k, 0, "FullWrite Professional 1.1", "Ashton-Tate's advanced word processing application for classic Macintosh.", "/apps/FullWritePro1_1.zip", 1418420 },
    { kCatProductivity, 1989, kArch68k, 40, "FullWrite Professional 1.5", "An early full-featured desktop publishing-style word processor for classic Mac OS.", "/apps/FullWrite_1.5.sit", 2659941 },
    { kCatProductivity, 1989, kArch68k, 60, "FullWrite Professional 2.0.3 (Demo)", "Demo of the Ashton-Tate FullWrite Professional desktop word processor for Mac.", "/apps/FullWrite2.0.3-Demo.sit", 1293478 },
    { kCatProductivity, 1990, kArch68k, 40, "FullWrite Professional Updater", "Updater for FullWrite Professional, an early full-featured desktop publishing-style word processor for", "/apps/FullWrite_1.5-1.7_Upd_f.img_.sit", 41261 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1992, kArch68k, 60, "FutureBasic", "Free/shareware BASIC development environment for the Mac.", "/apps/FutureBASIC_II.sit", 3888074 },
    { kCatDevTools, 1991, kArch68k, 60, "FutureBasic 1.01", "Staz Software's free compiled BASIC development environment for classic Macintosh.", "/apps/futurebasic101.sit", 695952 },
    { kCatDevTools, 1998, kArchFat, 70, "FutureBASIC 3.1.4", "BASIC programming environment for building native Macintosh applications.", "/apps/FutureBASIC_3_1.4.sit", 30076589 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArchFat, 70, "FWB Hard Disk Toolkit", "Third-party SCSI hard disk formatting and driver utility.", "/apps/FWB_Hard_Disk_Toolkittm_2.0.sit", 3980275 },
    { kCatUtilities, 1994, kArch68k, 60, "FWB Hard Disk Toolkit 1.3.2", "An earlier version of FWB Software's widely used SCSI hard drive formatting and partitioning utility.", "/apps/FWB_HDT_1.3.2.img_.sit", 575131 },
    { kCatUtilities, 1994, kArch68k, 70, "FWB Hard Disk ToolKit 1.8", "FWB Software's professional hard-drive formatting and diagnostic utility.", "/apps/FWB_HD_Toolkit_1.8.sit", 1271456 },
    { kCatUtilities, 1996, kArchFat, 70, "FWB Hard Disk ToolKit 2.5", "FWB Software's professional hard drive formatting and management utility.", "/apps/hard_disk_toolkit_25_pe.cdr_.sit", 31362179 },
    { kCatUtilities, 1997, kArchFat, 75, "FWB Hard Disk ToolKit 3.0", "Later release of FWB Software's professional hard drive formatting and management utility.", "/apps/FWB_Hard_Disk_ToolKittm_3.0.img_.sit", 4371084 },
    { kCatUtilities, 1997, kArchFat, 70, "FWB Hard Disk Toolkit 3.0.2", "A later version of FWB Software's widely used SCSI hard drive formatting and partitioning utility.", "/apps/FWB_Hard_Disk_ToolKittm_3.0.2.iso", 102838272 },
    { kCatUtilities, 1997, kArchPPC, 75, "FWB Hard Disk Toolkit 4.0", "Hard disk formatting and partitioning utility from FWB Software.", "/apps/FWB_HDTtm_4.0_Installer.sit", 6375041 },
    { kCatUtilities, 1997, kArchFat, 70, "FWB Hard Disk ToolKit PE 3.0.2", "Disk formatting and partitioning utility from FWB Software.", "/apps/FWB_Hard_Disk_ToolKit_PE_3.0.2.zip", 20311871 },
    /* -- Games -- */
    { kCatGames, 1995, kArch68k, 70, "Gabriel Knight 2: The Beast Within", "Sierra's live-action full-motion-video adventure game, ported to classic Mac OS.", "/games/GK2_CD5.image_.sit", 491870057 },
    { kCatGames, 1993, kArch68k, 70, "Gabriel Knight: Sins of the Fathers", "Sierra's atmospheric graphic adventure following a New Orleans bookstore owner investigating occult murders.", "/games/gabriel_knight_disks.zip", 16617950 },
    { kCatGames, 1993, kArch68k, 70, "Gadget: Invention, Travel & Adventure", "Synergy's surreal steampunk adventure game; Japanese-language Macintosh CD release.", "/games/Gadget94_Mac_Jap_CD_19931128_iso.zip", 356031362 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1998, kArchFat, 75, "Game Sprockets 1.7.5", "Apple's collection of gaming system extensions providing sound, input, and networking APIs for Mac games.", "/apps/IntEN-GameSprockets_1.7.5.smi_.bin", 900608 },
    /* -- Internet & Comm -- */
    { kCatInternet, 2002, kArchPPC, 81, "GameRanger", "Online matchmaking client that let classic Mac gamers find and join multiplayer game sessions over the", "/apps/GameRanger.dmg", 343841 },
    /* -- Utilities -- */
    { kCatUtilities, 1988, kArch68k, 60, "GateKeeper", "Early INIT-based virus protection extension.", "/apps/GateKeeper1.1.1.sit", 79433 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1988, kArch68k, 0, "Gatekeeper 1.2.3", "Chris Johnson's classic Macintosh anti-virus system extension.", "/apps/Gatekeeper1.2.3.sit", 101273 },
    /* -- Games -- */
    { kCatGames, 1985, kArch68k, 20, "Gato", "World War II submarine combat simulation from Spectrum Holobyte.", "/games/gato_1_42.zip", 4063267 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "GCC 2.3.3", "A port of the GNU C Compiler for classic Mac OS, used with MPW for cross-platform C development.", "/apps/GCC-2.3.3r12.img_.sit", 6069200 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 0, "General Controls", "Apple's control panel for date, time, and desktop pattern.", "/apps/GeneralControls701patch.sit", 26367 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Genuine Fractals 2.0.6", "Photoshop plug-in for enlarging digital photos while preserving detail using fractal interpolation.", "/apps/Genuine_Fractals_2.0.6.sit", 1585670 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 60, "Gerry's ICQ (German)", "German-language ICQ instant messaging client clone for the classic Mac OS.", "/apps/GerrysICQd39_Deutsche.sit", 569929 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 70, "GifBuilder", "Freeware tool for building animated GIFs.", "/apps/GifBuilder_1.0.sit", 231220 },
    { kCatGraphicsSound, 1995, kArch68k, 60, "GifBuilder 0.4", "Yves Piguet's freeware tool for assembling animated GIF files on the classic Mac OS.", "/apps/GifBuilder_0.4.sit_.hqx", 196672 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "GIFConverter 2.2.9", "An earlier release of Kevin Mitchell's pioneering shareware image conversion and viewing utility for classic", "/apps/GIFConverter_2.2.9.sit", 167882 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "GIFConverter 2.3.7", "One of the first Mac tools for making and viewing GIFs.", "/apps/GIFConverter_2.3.7_f.sit", 381559 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "GIFConverter 2.4.3", "Kevin Mitchell's shareware application for converting and viewing GIF and other image formats.", "/apps/GIFConverter2.4.3.sit", 1328468 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 30, "Glider 2.02", "John Calhoun's original paper-airplane navigation game.", "/games/glider_2.02.sit", 35960 },
    { kCatGames, 1991, kArch68k, 60, "Glider 3.1.2", "Earlier version of the paper-airplane arcade game Glider.", "/games/Glider312.img_.sit", 94948 },
    /* -- Featured -- */
    { kCatFeatured, 1994, kArch68k, 60, "Glider 4.0", "Fly a paper airplane through a hazard-filled house.", "/games/Glider4.02.sit", 589837 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "Glider 4.06", "Paper-airplane flying game where players glide through a house avoiding hazards.", "/games/Glider_4.06.sit", 609516 },
    { kCatGames, 1994, kArch68k, 60, "Glider 4.09", "Updated release of the classic paper-airplane flying game.", "/games/Glider_4.09.sit", 972640 },
    { kCatGames, 1994, kArch68k, 60, "Glider 4.1", "John Calhoun's paper-airplane navigation game flying through a household full of hazards.", "/games/glider_4_10.zip", 11089062 },
    { kCatGames, 1994, kArch68k, 70, "Glider PRO", "The definitive, editable sequel to Glider.", "/games/Glider_42.SIT", 1380520 },
    { kCatGames, 1994, kArchFat, 70, "Glider PRO 1.1", "Paper-airplane platformer where players glide through a house full of hazards, from Casady & Greene.", "/games/Glider_Pro_upd_1.01_to_1.1.sit", 1501486 },
    { kCatGames, 1994, kArch68k, 60, "Glider PRO 1.1.2", "John Calhoun's iconic paper-airplane flying game through a papercraft house.", "/games/glider_pro_1_1_2.zip", 48677192 },
    { kCatGames, 1997, kArchPPC, 75, "GLQuakeWorld 1.1b3", "OpenGL-accelerated multiplayer QuakeWorld client ported to the Power Macintosh.", "/games/GLQuakeWorld_11b3.sit", 451027 },
    { kCatGames, 1992, kArch68k, 40, "Glypha", "Ambrosia Software's Egyptian-themed side-scrolling arcade shooter.", "/games/Glypha1.dsk", 524288 },
    { kCatGames, 1993, kArch68k, 60, "GNU Chess 3.0", "A free, open-source chess engine ported to classic Mac OS.", "/games/GNUChess3.0.sit", 127504 },
    { kCatGames, 1988, kArch68k, 40, "Gold Rush!", "Sierra On-Line adventure game following a prospector's journey during the California Gold Rush.", "/games/Gold-Rush.img_.sit", 1342271 },
    { kCatGames, 1994, kArch68k, 60, "GolfMeister 1.1", "A shareware golf simulation game for classic Mac OS.", "/apps/GolfMeister_1.1.sit", 137897 },
    { kCatGames, 1996, kArch68k, 60, "GolfMeister 2.0", "A later version of the shareware golf simulation game for classic Mac OS.", "/apps/GolfMeister_2.0.sit", 548187 },
    { kCatGames, 1991, kArch68k, 10, "GoMoku", "Classic five-in-a-row strategy board game.", "/games/GoMoku._v1.0.sit", 9567 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1992, kArch68k, 70, "Gopher for Macintosh", "Client for browsing the pre-web Gopher information system.", "/apps/MacGopher.sit_.hqx", 395945 },
    { kCatInternet, 1993, kArch68k, 60, "GopherApp 1.1b36", "Alternative Macintosh Gopher client application.", "/apps/GopherApp_1.1b36.sit", 172288 },
    { kCatInternet, 1994, kArch68k, 60, "GopherApp 1.3b56", "Client application for browsing Gopher servers on the early Internet.", "/apps/GopherApp_1.3b56.sit", 237824 },
    { kCatInternet, 1994, kArch68k, 60, "GopherApp 2.2b43", "Updated beta version of the GopherApp Internet Gopher client.", "/apps/GopherApp_2.2b43.sit", 306680 },
    /* -- Productivity -- */
    { kCatProductivity, 1992, kArch68k, 60, "Grammatik 5 v1.1", "Grammar and style checking software for the classic Mac OS.", "/apps/Grammatik_5_v1.1.sit", 739171 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchFat, 70, "GraphClick", "Utility for digitizing data points from scanned graphs and charts.", "/apps/graphclick_e.bin", 69760 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "GraphicConverter 1.6.2", "Early release of Lemke Software's shareware image viewing and conversion utility.", "/apps/GraphicConverter-162_2.sit", 159657 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "GraphicConverter 2.2", "Earlier 68k-native version of the popular shareware image conversion application.", "/apps/graphicconverter2.2us.sit_.hqx", 1624184 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "GraphicConverter 2.2 (French)", "An early release of Lemke Software's shareware image viewer and format-conversion utility, localized for", "/apps/graphicconverter2.2fr.sit_.hqx", 1616890 },
    /* -- Featured -- */
    { kCatFeatured, 1995, kArch68k, 70, "GraphicConverter 2.6", "Views and converts nearly every image format under the sun.", "/apps/GraphicConverter-2.0.6.sit", 392869 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchPPC, 70, "GraphicConverter 3.8", "An earlier release of Lemke Software's shareware image viewer and format-conversion utility for Mac OS.", "/apps/gc38usppc.sit", 2014882 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "GraphicConverter 3.8 (German)", "German-language release of the versatile image viewing and format conversion utility.", "/apps/graphicconverter38de.toast_.sit", 54258810 },
    { kCatGraphicsSound, 1997, kArch68k, 70, "GraphicConverter 3.91", "Lemke Software's widely used shareware image viewing and format-conversion utility.", "/apps/graphicconverter_3.91_68k.sit", 2141324 },
    { kCatGraphicsSound, 1999, kArchPPC, 70, "GraphicConverter 4.0", "A mid-series release of Lemke Software's shareware image viewer and format-conversion utility for Mac OS.", "/apps/gc4usppc.sit", 2613184 },
    { kCatGraphicsSound, 1999, kArchFat, 70, "GraphicConverter 4.0.9", "Lemke Software's enormously popular shareware image viewer and format-conversion utility for Mac OS.", "/apps/gc409usppcx.sit", 3333358 },
    { kCatGraphicsSound, 2001, kArchPPC, 81, "GraphicConverter 4.8", "Thorsten Lemke's widely used shareware image conversion and viewing application, Carbon release.", "/apps/GraphicConverter_480_carbon.sit", 4708735 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArchFat, 70, "Graphing Calculator 1.1", "3D function-graphing utility originally bundled with Power Macintosh systems.", "/apps/Graphing_Calculator_1.1.sit", 283748 },
    { kCatProductivity, 1994, kArch68k, 70, "GreatWorks 2.0", "Symantec's integrated office suite combining word processing, spreadsheet, database, and drawing modules for", "/apps/GreatWorks2.0.sit", 1416493 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "Greg's Browser", "Classic Macintosh utility for browsing and managing fonts and FKEYs.", "/apps/Gregs_Browser.sit", 464915 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "Greg's Buttons", "Adds custom appearance buttons to windows and scroll bars.", "/apps/GregsButtons_3.4.sit", 59215 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 70, "GuestPC 1.97", "A software-based PC/DOS emulator for classic Mac OS, a rival to Virtual PC and SoftWindows.", "/apps/GuestPC197.zip", 3980926 },
    /* -- Games -- */
    { kCatGames, 1998, kArchPPC, 75, "Half-Life (PPC Alpha)", "An unofficial PowerPC alpha port of Valve's landmark first-person shooter Half-Life.", "/games/Half-Life_PPC_Alpha_0.dmg", 269611796 },
    { kCatGames, 1993, kArch68k, 40, "Halma", "Classic strategy board game of moving pieces across a checkerboard.", "/games/Halma_1.1.sit", 84747 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 70, "Hard Disk ToolKit PE 1.7.6", "Earlier release of FWB's personal edition hard drive formatting utility.", "/apps/Hard_Disk_ToolKit_PE_1.7.6.sit", 953939 },
    { kCatUtilities, 1997, kArchFat, 70, "Hard Disk ToolKit PE 1.7.8", "FWB's personal edition hard drive formatting and partitioning software.", "/apps/Hard_Disk_ToolKit_PE_1.7.8.sit", 1039040 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 10, "Hardball", "Baseball sports simulation game.", "/games/hardball.sit", 177015 },
    { kCatGames, 1990, kArch68k, 60, "HardBall II", "Accolade's baseball simulation game, sequel to HardBall.", "/games/hardball2.sit", 9142943 },
    { kCatGames, 1989, kArch68k, 60, "Harpoon", "Naval warfare strategy simulation.", "/games/Harpoon1.52.sit", 451644 },
    { kCatGames, 1989, kArch68k, 40, "Harpoon 1.0", "Naval warfare simulation game from Three-Sixty Pacific.", "/games/Harpoon_v1.0.zip", 523788 },
    { kCatGames, 1998, kArchPPC, 75, "Harpoon 3", "Third installment of the Harpoon naval warfare simulation series.", "/games/harpoon3.toast_.sit", 120604933 },
    { kCatGames, 1994, kArchFat, 60, "Harpoon II 1.0.1", "Sequel to the naval warfare simulation Harpoon.", "/games/HarpoonII1.0.1.sit_.bin", 18723328 },
    /* -- Productivity -- */
    { kCatProductivity, 1987, kArch68k, 30, "Helix 1.7", "Odesta's visually-programmed relational database system for the Macintosh.", "/apps/OdestaHelix17.zip", 937458 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Hellcats over the Pacific", "WWII naval combat flight simulator.", "/games/hellcatsoverthepacific.zip", 61249212 },
    { kCatGames, 1996, kArchPPC, 75, "Heretic", "Raven Software's dark-fantasy first-person shooter built on the Doom engine, Mac port.", "/games/Heretic.sit", 6131659 },
    { kCatGames, 1995, kArch68k, 70, "Heroes of Might and Magic", "New World Computing's fantasy turn-based strategy game.", "/games/HeroesOfMightAndMagic.img_.sit", 48600169 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1997, kArch68k, 60, "HexEdit 1.20", "Hexadecimal file editor for viewing and modifying raw binary data.", "/apps/HexEdit-1.20.sit", 112862 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchPPC, 75, "HexEdit 1.91", "Binary and hex file editor for viewing and modifying raw file data.", "/apps/HexEdit_191_Release.zip", 762509 },
    /* -- Games -- */
    { kCatGames, 1998, kArchPPC, 70, "Hexen II", "Raven Software's dark fantasy first-person shooter, ported to classic Mac OS.", "/games/Hexen_II.toast_.sit", 128330840 },
    { kCatGames, 1996, kArch68k, 70, "Hexen: Deathkings of the Dark Citadel", "The expansion pack for Raven Software's dark-fantasy first-person shooter Hexen.", "/games/Hexen_Deathkings.sit", 4143118 },
    { kCatGames, 1988, kArch68k, 60, "Hidden Agenda", "Political simulation of running a fictional country.", "/games/hidden_agenda.sit", 461448 },
    { kCatGames, 1993, kArch68k, 60, "Holiday Lemmings 93/94", "Free seasonal spinoff of Lemmings with holiday-themed levels.", "/games/Holiday_Lemmings_9394.img_.zip", 6088996 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "Homer", "Tom Clark's offline Usenet newsgroup reader for classic Macintosh.", "/apps/homer.img_.sit", 1587667 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "Homer 0.937", "Freeware TCP/IP stack extension for connecting classic Mac OS to the internet.", "/apps/Homer0937TCP.sit_.bin", 397312 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 60, "Homer 1.7", "Simple freeware web browser for older Macs.", "/apps/Homer_2.1.sit", 390151 },
    { kCatInternet, 1997, kArchFat, 70, "Hotline Client", "Popular file-sharing and chat client of the late 90s.", "/apps/HotlineClient185.sit", 4630817 },
    { kCatInternet, 1997, kArch68k, 70, "Hotline Client 1.1", "Hotline Communications' peer-to-peer file sharing and chat client, popular in the late-1990s Mac warez and", "/apps/Hotline1.1IMAGE.sit", 1203927 },
    { kCatInternet, 1998, kArch68k, 75, "Hotline Connect Client 1.9.1", "Client for Hotline, the popular file-sharing and chat network of the late-1990s Mac scene.", "/apps/HotlineConnectClient-Mac-1.9.1.sit", 1644990 },
    { kCatInternet, 1996, kArchPPC, 70, "HoTMetaL 2.0", "HTML authoring tool from SoftQuad for the classic Mac OS.", "/apps/HoTMetaL_2.0_PPC_Installer.bin", 1565568 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1989, kArch68k, 60, "HyperAnimator 1.5.2", "Bright Star Technology's cel animation add-on for HyperCard stacks.", "/apps/HyperAnimator_1.5.2.sit", 595482 },
    /* -- Productivity -- */
    { kCatProductivity, 1987, kArch68k, 40, "HyperCard 1.1", "Apple's original hypermedia authoring environment, an early version.", "/apps/HyperCard11.zip", 1586462 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1989, kArch68k, 40, "HyperCard 1.2.5", "Apple's original scriptable hypermedia authoring and database environment.", "/apps/HyperCard_1.2.5_Disks.sit", 1228417 },
    { kCatDevTools, 1990, kArch68k, 60, "HyperCard 1.2.5 (Italian)", "An early release of Apple's HyperCard hypermedia authoring environment, localized for Italian.", "/apps/HyperCard_1.2.5_ITA.sit", 1445208 },
    { kCatDevTools, 1991, kArch68k, 60, "HyperCard 2.1", "Apple's classic rapid-application-development and hypermedia authoring environment.", "/apps/HyperCard_D1-2.1.sit", 575836 },
    { kCatDevTools, 1996, kArchFat, 70, "HyperCard 2.3", "Later release of Apple's HyperCard scriptable hypermedia authoring environment.", "/apps/HyperCard-23-update.sit", 1371444 },
    { kCatDevTools, 1993, kArch68k, 70, "HyperCard 2.3.5", "Apple's legendary hypermedia authoring environment for building interactive stacks with HyperTalk scripting.", "/apps/hypercard-2.3.5-dc42.zip", 6159241 },
    /* -- Featured -- */
    { kCatFeatured, 1993, kArch68k, 60, "HyperCard 2.4.1", "Build interactive stacks with HyperTalk.", "/apps/HyperCard241.img", 47220224 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "HyperCard Player 2.1", "Runtime player for HyperCard 2.1 stacks.", "/apps/HyperCard_2.1_Player.i.sit_.hqx", 479257 },
    { kCatProductivity, 1993, kArch68k, 70, "HyperCard Player 2.4", "Runtime player for viewing and using HyperCard stacks without the full authoring environment.", "/apps/HyperCard_Player_2.4.smi_.bin", 1707904 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArchPPC, 75, "HyperCard Player 2.4.1", "Runtime player for viewing and using HyperCard stacks without the full authoring environment.", "/apps/HyperCard-Player-2.4.1-smi.sit", 1248416 },
    /* -- Productivity -- */
    { kCatProductivity, 1992, kArch68k, 60, "HyperCard Projects for Kids", "Published collection of educational HyperCard stacks for children.", "/apps/HyperCard_Projects_for_Kids.hqx", 753624 },
    /* -- Utilities -- */
    { kCatUtilities, 1989, kArch68k, 40, "HyperDisk (MacUser 1989)", "RAM disk utility published as a MacUser magazine cover disk tool.", "/apps/HYPERDISK_MacUser89.image_.sit", 520872 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "HyperStudio 3.1", "Multimedia authoring tool widely used in classrooms to build interactive stacks.", "/apps/HyperStudio_3.1_and_Sample.sit", 10996401 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 70, "HyperStudio 3.3", "Roger Wagner's widely used multimedia authoring tool for education, similar to HyperCard but with richer", "/apps/hyperstudio33.sit", 2821325 },
    /* -- Productivity -- */
    { kCatProductivity, 1997, kArchFat, 70, "HyperStudio 4.0", "Multimedia authoring software widely used in K-12 education.", "/apps/HyperStudio_4.sit", 25294423 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1992, kArch68k, 0, "HyperTalk Reference", "Reference stack documenting the HyperTalk language.", "/manuals/HyperTalk_Quick_Reference_Card.pdf", 2253735 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchPPC, 85, "IBM ViaVoice Millennium Edition", "IBM's continuous speech recognition and dictation software for Mac OS.", "/apps/ViaVoice_ME.zip", 56901240 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 81, "iCab (Pre-1.25)", "A pre-release build of iCab, the well-known alternative web browser for classic Mac OS.", "/apps/iCab_Pre1.25_English_PPC.sit", 836086 },
    { kCatInternet, 2003, kArchPPC, 86, "iCab (Pre-2.98)", "A pre-release build of iCab, the well-known alternative web browser for classic Mac OS.", "/apps/iCab_Pre2.98_English_PPC.sit", 2226223 },
    { kCatInternet, 2000, kArchPPC, 81, "iCab 1.1", "An early full release of iCab, the well-known alternative web browser for classic Mac OS.", "/apps/iCab_1.1_PPC_Eng_k.sit", 720473 },
    { kCatInternet, 1999, kArchFat, 71, "iCab 1.25 (Preview)", "Alternative web browser for classic Macintosh known for running well on older, lower-spec Macs.", "/apps/iCab_Pre1.25_k.sit", 730423 },
    { kCatInternet, 1998, kArchPPC, 70, "iCab 1.3a (Pre-release)", "Pre-release build of the lightweight iCab web browser for Mac OS.", "/apps/iCab_Pre1.3a_English_PPC.sit", 1184415 },
    { kCatInternet, 1999, kArchPPC, 75, "iCab 1.4 (Pre-release)", "Earlier prerelease build of the independent iCab web browser for classic Mac OS.", "/apps/iCab_Pre1.4_English_PPC.sit", 862682 },
    { kCatInternet, 2000, kArchPPC, 75, "iCab 1.8 (Pre-release)", "Prerelease build of the independent iCab web browser for classic Mac OS.", "/apps/iCab_Pre1.8_English_PPC.sit", 1137209 },
    { kCatInternet, 1999, kArchPPC, 70, "iCab 2.0 (Pre-release)", "Pre-release build of iCab 2.0 adding improved standards support.", "/apps/iCab_Pre2.0_English_PPC.sit", 1247215 },
    { kCatInternet, 2001, kArchPPC, 75, "iCab 2.71 (Pre-release)", "Later pre-release build of the iCab web browser for classic Mac OS.", "/apps/iCab_Pre2.71_English_PPC.sit", 1822280 },
    { kCatInternet, 1998, kArchPPC, 75, "iCab Preview 1.2", "Early preview build of the alternative iCab web browser for classic Mac OS.", "/apps/iCab_Pre1.2_English_PPC.sit", 724343 },
    /* -- Games -- */
    { kCatGames, 2000, kArchPPC, 85, "Icewind Dale", "Black Isle Studios' Infinity Engine fantasy role-playing game.", "/games/Icewind_Dale_CD_2.toast_.zip", 660728293 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "Icon Machine", "Simple icon-editing utility.", "/apps/iconmachine2.sit", 803180 },
    { kCatUtilities, 1993, kArch68k, 70, "Iconographer", "Advanced Finder icon creation and editing tool.", "/apps/iconographerJ.sit", 564125 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 81, "ICQ 1.1.0 (PPC)", "Mirabilis's ICQ instant messaging client for Power Macintosh.", "/apps/ICQ_PPC_1.1.0.sit", 661970 },
    { kCatInternet, 1998, kArchPPC, 75, "ICQ 1.5.1", "Mirabilis's pioneering instant messaging client, ported to Mac OS.", "/apps/ICQ_PPC_1.5.1.sit", 1033396 },
    { kCatInternet, 1998, kArch68k, 70, "ICQ 1.5.5 (68k)", "Mirabilis's ICQ instant messaging client ported to classic Mac OS.", "/apps/ICQ_68K_1.5.5.sit", 908128 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "id Anthology (Mac)", "A compilation of id Software's classic games (Doom, Quake, and others) for classic Mac OS.", "/games/id_anthology_mac.zip", 265550472 },
    { kCatGames, 2001, kArchFat, 70, "iHam on iRye 2.0", "A shareware word-tile puzzle game for Mac OS in the style of Scrabble.", "/apps/iHam_on_iRye_2.0.sit", 3721273 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 60, "Illustrator 88", "Early version of Adobe's vector illustration software.", "/apps/Adobe_Illustrator_88.sit", 259407 },
    { kCatGraphicsSound, 1989, kArch68k, 10, "ImageStudio", "Grayscale image scanning and editing application.", "/apps/Image_Studio.sit_.hqx", 589298 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Imagine 1.0", "Impulse Inc's 3D modeling, rendering, and animation software for classic Mac OS, ported from the Amiga.", "/apps/Imagine_1.0.sit", 187013 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "In Control", "Outline-based to-do list and task manager.", "/apps/In_Control_2.sit", 705808 },
    { kCatProductivity, 1998, kArchFat, 70, "In Control 4.0.1", "Attain Corporation's outliner-based to-do list and task management application for Mac OS.", "/apps/In_Control_4.0.1_0.sit", 1384988 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 60, "Indiana Jones and the Fate of Atlantis", "LucasArts's globe-trotting graphic adventure game.", "/games/IndyJonesAtlantis_floppy.zip", 17937938 },
    { kCatGames, 1989, kArch68k, 30, "Indiana Jones and the Last Crusade", "LucasFilm Games graphic adventure based on the film.", "/games/Indiana_Jones_and_the_Last_Crusade.SIT", 1543923 },
    { kCatGames, 1995, kArch68k, 70, "IndyCar Racing II", "Papyrus/MacPlay open-wheel racing simulation for the classic Mac OS.", "/games/IndyCar2.cdr_.zip", 97405947 },
    { kCatGames, 1983, kArch68k, 0, "Infidel", "Infocom's text adventure game set in search of a lost pyramid.", "/games/infidel.sit", 76720 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Infini-D 1.0.2", "Early release of Specular International's 3D modeling and animation application.", "/apps/Infini-Dtm_1.0.2.sit", 436519 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Infini-D 2.5.2", "Specular International's 3D modeling, rendering and animation application.", "/apps/infinid_2_5_2.zip", 3762520 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Infini-D 2.6", "Specular International's 3D modeling and animation application.", "/apps/Infini-Dtm_2.6_Folder.sit", 2185081 },
    { kCatGraphicsSound, 1996, kArchPPC, 70, "Infini-D 3.51", "Later release of Specular's 3D modeling and animation application.", "/apps/infini_d_351.sit", 15928131 },
    { kCatGraphicsSound, 1996, kArch68k, 70, "Infini-D 4.5", "Specular International's integrated 3D modeling, rendering, and animation application.", "/apps/Infini-D_4.5_Installer.sit", 21695746 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "Infini-D Demo", "3D modeling, rendering, and animation, demo edition.", "/apps/infini-d_4.5.sit", 21696110 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Infocom Text Adventure Anthology", "Compilation collecting Infocom's classic interactive fiction titles for Macintosh.", "/games/INFOCOMCompleteCollection.sit", 310974700 },
    { kCatGames, 1988, kArch68k, 40, "Infocom's Shogun", "Text adventure game from Infocom based on James Clavell's novel.", "/games/InfocomShogun.zip", 2862248 },
    { kCatGames, 1991, kArch68k, 40, "Infocom: The Lost Treasures", "A compilation of Infocom's classic text adventure games (the Zork series and others) for classic Mac OS.", "/games/InfocomLostTreasures.zip", 14791372 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "INITPicker", "Manages startup extension load order and conflicts.", "/apps/initpicker_v302.zip", 312411 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 70, "Inspiration", "Inspiration Software's concept-mapping and outlining tool widely used in schools on classic Mac OS.", "/apps/Inspiration.sit", 507236 },
    { kCatProductivity, 1997, kArch68k, 70, "Inspiration 4.1", "Inspiration Software's concept-mapping and outlining tool widely used in schools on classic Mac OS.", "/apps/Inspiration4_1.zip", 1806412 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "Installer Maker 2.0.2", "Apple's developer tool for building custom Installer packages for classic Mac OS software.", "/apps/InstallerMakertm_2.0.2_Installer.sit", 1308245 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 0, kArchPPC, 85, "Intaglio 2.8.1", "Purgatory Design's vector illustration application for Mac OS.", "/apps/IntaglioPPC281.dmg_.zip", 3425756 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "IntelliDraw 1.0", "Intelligent drawing application from Aldus that automated diagram and chart creation.", "/apps/IntelliDraw1.0.hqx", 4522496 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "IntelliDraw 2.0", "Vector drawing application with intelligent object linking, from Aldus.", "/apps/IntelliDraw_2.0.img_.zip", 5569067 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Intellihance Pro 4.1", "Automated image correction plug-in from Extensis for Photoshop.", "/apps/Intellihance_Pro_4.1_I.sit", 6755980 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "Interactive Physics SE", "Physics simulation and modeling software used in science education.", "/apps/Interactive_Physics_SE.sit_.hqx", 1508473 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 75, "Interarchy 3.8", "FTP and Internet file transfer client, the renamed successor to Anarchie.", "/apps/Interarchy_3.8.sit", 3033881 },
    { kCatInternet, 1998, kArchPPC, 75, "InterArchy 4.0", "Earlier release of the InterArchy FTP client for the classic Mac OS.", "/apps/Interarchy_4.0.sit", 1705965 },
    { kCatInternet, 2000, kArchFat, 81, "Interarchy 4.1", "Successor to Anarchie; Stairways Software's FTP and Internet file-transfer client.", "/apps/Interarchy_4.1_OSX_OS8-9.sit", 1411435 },
    { kCatInternet, 2001, kArchPPC, 80, "Interarchy 5.0.1", "FTP client update supporting both Mac OS 8/9 and Mac OS X.", "/apps/Interarchy_5.0.1_OSXOS8-9.sit", 2048237 },
    { kCatInternet, 2000, kArchPPC, 81, "InterArchy 6.3", "FTP client for the classic Mac OS, successor to Anarchie, by Stairways Software.", "/apps/Interarchy63.img_.sit_.bin", 2050176 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "Interleaf Publishing 3.5", "Technical document publishing and desktop publishing software for the classic Mac OS.", "/apps/Interleaf_Publishing_3.5.sit", 4375341 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 0, "Internet Config 1.2", "Shared internet preferences used by many classic apps.", "/apps/InternetConfig1.2.sit", 107622 },
    { kCatInternet, 1996, kArchFat, 70, "Internet Config 1.3", "System-wide internet preferences manager used by many classic Mac internet applications.", "/apps/InternetConfig1.3.sit", 115684 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1997, kArch68k, 70, "Internet Config 1.4", "Shared system extension that let classic Mac OS applications share internet settings.", "/apps/InternetConfig1.4.sit", 111568 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 70, "Internet Config 2.0.2", "Peter Lewis's widely used shared internet preferences system letting classic Mac OS internet applications", "/apps/Internet_Config_2.0.2.sit", 178034 },
    { kCatInternet, 1996, kArch68k, 60, "Internet Explorer 2.0", "An early release of Microsoft's web browser for classic Mac OS, from before it became the bundled default.", "/apps/Internet_Explorer_2.0.sit", 1064347 },
    { kCatInternet, 1995, kArchFat, 70, "Internet Explorer 2.0 (Beta 1)", "Beta release of Microsoft's Internet Explorer web browser for the Macintosh.", "/apps/Internet_Explorer_2.0b1.cdr", 11665408 },
    { kCatInternet, 1996, kArch68k, 70, "Internet Explorer 2.0 (Beta)", "Early beta release of Microsoft's web browser for classic Macintosh.", "/apps/Internet_Explorer_2.0b3_0.sit", 755636 },
    { kCatInternet, 1996, kArch68k, 70, "Internet Explorer 2.0b3", "A beta release of Microsoft's early web browser for Mac OS.", "/apps/Internet_Explorer_2.0b3.sit", 755636 },
    { kCatInternet, 1996, kArchFat, 70, "Internet Explorer 2.1", "Update to Microsoft's early Macintosh web browser adding stability fixes.", "/apps/ie21fat.hqx", 2366967 },
    { kCatInternet, 1996, kArchPPC, 70, "Internet Explorer 3.0a", "Microsoft's web browser for the classic Mac OS, an early PowerPC release.", "/apps/IE_3.0a_PPC_Full_Installe.sit", 5841099 },
    { kCatInternet, 1999, kArchPPC, 75, "Internet Explorer 5", "Microsoft's web browser, once the default browser bundled with Mac OS.", "/apps/ie5da.hqx", 10287754 },
    { kCatInternet, 2000, kArchPPC, 81, "Internet Explorer 5.1", "Microsoft's Internet Explorer release for classic Mac OS with improved CSS and standards support.", "/apps/ie51eng.bin", 5656320 },
    { kCatInternet, 2001, kArchPPC, 81, "Internet Explorer 5.1.7", "Later release of Microsoft's web browser for Mac OS 8.1 through 9.", "/apps/Internet_Explorer_5.1.7.smi_.sit", 4578980 },
    { kCatInternet, 1993, kArch68k, 60, "InterNews 1.1", "An early graphical Usenet newsreader for classic Mac OS.", "/apps/InterNews_1.1.sea_.bin", 547328 },
    { kCatInternet, 1993, kArch68k, 60, "InterPoll", "Apple/Neon Software's network diagnostic and AppleTalk device polling utility for classic Mac OS.", "/apps/InterPoll_Admin.sit", 521130 },
    { kCatInternet, 1993, kArch68k, 60, "InterSLIP", "Freeware SLIP networking control panel.", "/apps/InterSLIP-1.0.2d2.sit", 105790 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchFat, 70, "Iomega Tools 5.0.3", "Iomega's driver and management software for Zip and Jaz removable disk drives on Mac OS.", "/apps/IomegaTools503.sit", 1204560 },
    { kCatUtilities, 1997, kArch68k, 75, "IomegaWare 3.5", "Iomega's driver and management software for Zip and Jaz removable-disk drives.", "/apps/IomegaWare_3.5.hqx", 8182507 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArch68k, 70, "IPNetMonitor 1.0c5", "Earlier version of the IPNetMonitor TCP/IP diagnostic utility.", "/apps/IP_NetMonitor68K_10c5.sit", 236419 },
    { kCatInternet, 1997, kArch68k, 70, "IPNetMonitor 1.1.1", "Sustainable Softworks' TCP/IP diagnostic and network-monitoring utility.", "/apps/IPNetMonitor68K_111.sit", 360777 },
    { kCatInternet, 1998, kArchFat, 70, "IPNetMonitor 2.0", "Network diagnostic utility for monitoring TCP/IP traffic and connections.", "/apps/IPNetMonitor_20.sit", 496517 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchPPC, 75, "IPNetMonitor 2.3", "Network diagnostic utility for monitoring TCP/IP traffic and connections.", "/apps/IPNetMonitor_23.sit", 500348 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArch68k, 70, "IPNetRouter 1.5.4", "Sustainable Softworks' NAT router and firewall software that let a classic Mac share one internet connection", "/apps/IPNetRouter68K_154.hqx", 1252728 },
    { kCatInternet, 1999, kArchPPC, 75, "IPNetRouter 1.6.1", "Sustainable Softworks' NAT router and connection-sharing utility.", "/apps/IPNetRouter_161.hqx", 1505736 },
    { kCatInternet, 1993, kArch68k, 60, "ircle 0.4.7", "An early release of the ircle IRC client for Mac OS.", "/apps/ircle_0.4.7.sit_.bin", 50560 },
    { kCatInternet, 1994, kArch68k, 60, "Ircle 1.3.5 (with source)", "Early version of the popular Ircle IRC chat client for classic Mac OS.", "/apps/ircle_1.3.5_Source.sit_.bin", 107648 },
    { kCatInternet, 1993, kArch68k, 60, "ircle 1.51", "Early release of the popular shareware IRC chat client for Macintosh.", "/apps/ircle151.sit__0.bin", 79104 },
    { kCatInternet, 1994, kArch68k, 60, "Ircle 1.56", "Early release of the popular shareware IRC chat client for Macintosh.", "/apps/ircle156.sit_.bin", 51328 },
    { kCatInternet, 1994, kArch68k, 60, "Ircle 2.0", "One of the earliest and most widely used IRC (Internet Relay Chat) clients for classic Mac OS.", "/apps/ircle20f2.sit_.bin", 80896 },
    { kCatInternet, 1996, kArch68k, 70, "Ircle 2.0f4", "IRC chat client release adding scripting and improved channel management.", "/apps/Ircle_2.0f4.sit", 84262 },
    { kCatInternet, 1994, kArch68k, 70, "ircle 2.1.6", "Earlier version of the ircle IRC client for Macintosh.", "/apps/ircle216.sit_.bin", 104832 },
    { kCatInternet, 1996, kArch68k, 70, "Ircle 2.5", "A mid-series release of the popular IRC (Internet Relay Chat) client for classic Mac OS.", "/apps/ircle25US.sit_.bin", 673408 },
    { kCatInternet, 1998, kArchPPC, 70, "Ircle 2.5F", "Update to the Ircle IRC client with expanded server list and DCC file transfer support.", "/apps/ircle25F.sit_.bin", 678144 },
    { kCatInternet, 1998, kArch68k, 70, "Ircle 2.6a18", "A later version of the popular IRC (Internet Relay Chat) client for classic Mac OS.", "/apps/ircle26a18.sit_.bin", 389504 },
    { kCatInternet, 2000, kArchPPC, 81, "Ircle 3.0.1", "IRC chat client release with a modernized interface for late classic Mac OS.", "/apps/Ircle_3.0.1.sit", 1225715 },
    { kCatInternet, 1997, kArchFat, 70, "ircle 3.0.2", "Later release of the popular ircle IRC client.", "/apps/ircle_3.0.2_us.sit", 833094 },
    { kCatInternet, 1996, kArch68k, 70, "ircle 3.0.3", "Popular shareware IRC chat client for classic Macintosh.", "/apps/ircle_3.0.3_US.sit_.Bin", 935040 },
    { kCatInternet, 1997, kArch68k, 70, "Ircle 3.0b10", "A later beta release of the popular IRC (Internet Relay Chat) client for classic Mac OS.", "/apps/ircle30b10US.sit_.bin", 797952 },
    { kCatInternet, 1996, kArch68k, 70, "ircle 3.1.2", "Updated 68k release of the ircle IRC client.", "/apps/ircle31268k.sit_.bin", 550400 },
    { kCatInternet, 1996, kArch68k, 70, "ircle 3.1b14", "Popular shareware IRC (Internet Relay Chat) client for Macintosh.", "/apps/ircle_3.1b14_Eng_68k.sit_.bin", 554752 },
    { kCatInternet, 2001, kArchPPC, 81, "Ircle 3.1b14 (Carbon)", "Popular IRC chat client for the classic Mac OS, Carbon build.", "/apps/ircle_3.1b14_Eng_Carbon.sit_.bin", 611200 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Iron Helix", "3D real-time strategy set aboard a derelict starship.", "/games/IronHelix_Demo.sit", 1654447 },
    { kCatGames, 1990, kArch68k, 60, "Ishido: The Way of Stones", "Meditative tile-matching puzzle game based on an ancient stone-placement concept.", "/games/Ishido_CD.sit", 7233585 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2000, kArchPPC, 80, "iView MediaPro 1.57", "Digital asset management software for cataloging and browsing image and media libraries.", "/apps/iView_MediaPro157.toast", 7340032 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 70, "iVisit 2.3b7", "An early multi-party internet videoconferencing application for classic Mac OS.", "/apps/iVisit23b7.hqx", 537773 },
    { kCatInternet, 1998, kArchFat, 70, "iVisit 2.5 (Beta 2)", "Multi-user video conferencing software for the internet.", "/apps/iVisit25b2.hqx", 616246 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 40, "Jeopardy!", "GameTek's computer adaptation of the television trivia game show, for classic Mac OS.", "/games/Jeopardy.SIT", 1375708 },
    { kCatGames, 1994, kArch68k, 60, "Jewel Box", "Match-three gem puzzle game.", "/games/jewelbox_10_202.sit", 1054580 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArch68k, 70, "Jewel Case Illustrator 1.9", "Utility for designing and printing custom CD jewel case inserts.", "/apps/JewelCaseIllustrator_1.9.sit", 2077723 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 20, "Jinxter", "Magnetic Scrolls' text adventure with graphics, ported to the classic Mac OS.", "/games/jinxter_dsk.sit", 433007 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "JMP 3.1.1", "SAS Institute's interactive statistical discovery software, originally developed on the Macintosh.", "/apps/JMP_3.1.1.sit", 3185051 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArchFat, 60, "JPEGView 3.2.1", "Aaron Giles' popular shareware JPEG image viewer for Macintosh.", "/apps/JPEGView_3.2.1_Fat.sit", 513737 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "JPEGView 3.3", "Fast, lightweight JPEG and PICT viewer.", "/apps/JPEGView_3.3.sit", 554471 },
    /* -- Games -- */
    { kCatGames, 2001, kArchPPC, 85, "JumpStart 4th Grade 2001", "Knowledge Adventure's edutainment title for fourth-grade curriculum skills.", "/games/jumpstart_4th_grade_2001.iso_.sit", 252430675 },
    { kCatGames, 1999, kArchFat, 75, "JumpStart Preschool 99", "Knowledge Adventure's edutainment title for preschool-age learners.", "/games/JumpStartPreschool99.iso_.zip", 222949637 },
    { kCatGames, 1990, kArch68k, 60, "Kaboom!", "Catch falling bombs in this Activision arcade port.", "/apps/kaboom.zip", 42171991 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "Kaboom! 2", "Nova Development's utility for replacing classic Mac OS system sounds with custom sound effect sets.", "/apps/kaboom_v2_cd.zip", 514934173 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "Kai's Power Tools", "Plug-in filter suite for surreal Photoshop effects.", "/apps/Kais_Power_Tools_3_Floppy_Set.zip", 5643650 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Kai's Power Tools 1.0", "HSC Software's groundbreaking and hugely influential set of Photoshop plug-in filters created by Kai Krause.", "/apps/Kais_Power_Tools_1.0.mar", 3291392 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Kai's Power Tools 3", "MetaTools' third release of its influential Photoshop plug-in filter collection, full CD edition.", "/apps/KPT_3_CD.zip", 162419741 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Kai's Power Tools 5", "MetaCreations' celebrated collection of creative Photoshop plug-in filters.", "/apps/KPT_5.zip", 227650554 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "Kai's Power Tools Cool Effects", "MetaTools plug-in filter collection for creating stylized special-effect images.", "/apps/KPT_Cool_Effects.sit", 1170098 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "KaleidaGraph", "Synergy Software's scientific graphing and data analysis application.", "/apps/KaleidaGraphtm.img_.sea_.hqx", 793142 },
    { kCatProductivity, 1993, kArch68k, 60, "KaleidaGraph 2.1.3", "Synergy Software's popular scientific graphing and statistical data analysis application for classic Mac OS.", "/apps/KaleidaGraph_2.1.3.image_.sit", 418447 },
    { kCatProductivity, 1994, kArch68k, 60, "KaleidaGraph 3.0", "Scientific graphing, charting, and curve-fitting software for the classic Mac OS.", "/apps/KaleidaGraphtm_3.0.sit", 445752 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArch68k, 70, "Kaleidoscope 1.0", "The original release of the Kaleidoscope appearance/theming engine for classic Mac OS.", "/apps/kaleidoscope-10.hqx", 446957 },
    { kCatSystemExt, 1994, kArch68k, 70, "Kaleidoscope 1.0.2", "Early version of the Kaleidoscope interface-theming extension.", "/apps/Kaleidoscope-1.0.2_24.zip", 8289695 },
    { kCatSystemExt, 1997, kArchFat, 70, "Kaleidoscope 1.1.6", "Earlier release of the popular Mac OS appearance-theming extension.", "/apps/Kaleidoscope-1.1.6.zip", 11300371 },
    { kCatSystemExt, 1997, kArchFat, 70, "Kaleidoscope 1.1.8", "A widely used appearance/theming engine that let classic Mac OS interfaces be skinned with custom window and", "/apps/Kaleidoscope-1.1.8_57.zip", 9845660 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 70, "Kaleidoscope 1.2.6", "Theming extension for custom window and menu appearances.", "/apps/kaleidoscope16US.sit", 497458 },
    { kCatUtilities, 1998, kArchFat, 70, "Kaleidoscope 1.7.1", "Appearance customization utility for theming the classic Mac OS interface.", "/apps/kaleidoscope171US.sit", 509132 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArch68k, 70, "Kaleidoscope 1.8.2", "Greg Landweber's classic Macintosh appearance and theme manager extension.", "/apps/kaleidoscope182US.sit", 661344 },
    { kCatSystemExt, 1998, kArchFat, 70, "Kaleidoscope 2.0.1", "A later release of the widely used appearance/theming engine for classic Mac OS.", "/apps/kaleidoscope201US.sit", 1341043 },
    { kCatSystemExt, 1998, kArchPPC, 75, "Kaleidoscope 2.1.1", "Appearance and theming engine that let users skin the classic Mac OS interface.", "/apps/Kaleidoscope-2.1.1-219.zip", 26262927 },
    { kCatSystemExt, 1999, kArchPPC, 75, "Kaleidoscope 2.2.2", "Later release of the Kaleidoscope appearance theming engine for Mac OS 8/9.", "/apps/Kaleidoscope222.hqx", 550156 },
    { kCatSystemExt, 1997, kArch68k, 75, "Kaleidoscope 2.3.1", "Later release of the popular Kaleidoscope interface-theming extension.", "/apps/Kaleidoscope231US.bin", 1908736 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArch68k, 60, "Kant Generator Pro 1.3.1", "Novelty shareware program that algorithmically generates postmodern academic-sounding text.", "/apps/Kant_Generator_Pro_1.3.1_f.hqx", 176849 },
    { kCatUtilities, 1997, kArch68k, 75, "Kensington MouseWorks 5.02", "Driver and configuration software for Kensington mice and trackballs.", "/apps/Kensington_MouseWorks_5.02.sit", 735782 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1998, kArchPPC, 75, "Kensington MouseWorks 5.04", "Driver and control panel software for Kensington mice and trackballs.", "/apps/Kensington_MouseWorks_5.04_0.img", 1474560 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "KeyQuencer 1.0.1", "Earlier release of the KeyQuencer macro utility.", "/apps/KeyQuencer_1.01.img", 86010 },
    { kCatUtilities, 1994, kArch68k, 60, "KeyQuencer 1.01", "Binary Software's lightweight keyboard macro utility.", "/apps/KeyQuencer-101.sit", 843474 },
    { kCatUtilities, 1996, kArchFat, 70, "KeyQuencer 1.2.1", "Binary Software's macro and keyboard automation utility.", "/apps/KeyQuencer-121.sit", 256394 },
    { kCatUtilities, 2003, kArchPPC, 86, "KeyStrokes 2.1.1", "An on-screen keyboard accessibility utility for classic Mac OS.", "/apps/KeyStrokes211.sit_.bin", 1131904 },
    { kCatUtilities, 1994, kArch68k, 70, "Kid Desk 1.0", "A simplified, kid-safe desktop shell that restricts access to the Finder and other applications.", "/apps/kid_desk_v1.0.sit", 2213488 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2001, kArchPPC, 81, "Kid Pix Deluxe 3", "Broderbund's beloved children's drawing and painting program, this CD-ROM edition adding animation and", "/apps/kid_pix_deluxe_3_cd.img_.sit", 386695111 },
    { kCatGraphicsSound, 1995, kArchFat, 70, "Kid Pix Studio", "Broderbund's creative paint and multimedia application for children.", "/games/kid_pix_studio_1995.toast_.sit", 241134199 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Kid Pix Studio Deluxe", "Expanded edition of Broderbund's creative paint and multimedia application for children.", "/games/KidPixStudioDeluxeUK.iso", 253376512 },
    /* -- Featured -- */
    { kCatFeatured, 1991, kArch68k, 60, "KidPix 1.0", "Playful paint program for kids, with sound effects for every tool.", "/apps/KidPix.sit", 45728 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 0, "King of Chicago", "Cinemaware's cinematic 1930s gangster-era adventure game.", "/games/king_of_chicago.sit", 376835 },
    { kCatGames, 1990, kArch68k, 60, "King's Bounty", "New World Computing's turn-based fantasy strategy and role-playing game, precursor to Heroes of Might and", "/games/KingsBounty_1_0_k.dsk_.mar", 1474816 },
    { kCatGames, 1984, kArch68k, 0, "King's Quest", "Sierra's pioneering graphical adventure game starring Sir Graham.", "/games/kings_quest_1.sit", 269377 },
    { kCatGames, 1985, kArch68k, 0, "King's Quest II: Romancing the Throne", "Sierra's sequel graphical adventure game.", "/games/kings_quest_2.sit", 467288 },
    { kCatGames, 1990, kArch68k, 40, "King's Quest III", "Sierra graphic adventure game, Mac port of the third King's Quest title.", "/games/kings_quest_3.sit", 481235 },
    { kCatGames, 1990, kArch68k, 60, "King's Quest V", "Sierra's graphic fantasy adventure starring Sir Graham searching for his kidnapped family.", "/games/Kings_Quest_V.mar", 11798784 },
    { kCatGames, 1992, kArch68k, 60, "King's Quest VI", "Sierra's acclaimed point-and-click fantasy adventure game, ported to classic Mac OS.", "/games/kq6.img_.sit", 11519494 },
    { kCatGames, 1992, kArch68k, 60, "Klondike 3.6", "Classic solitaire card game for the Macintosh.", "/games/Klondike3.6.sit", 27977 },
    { kCatGames, 1993, kArch68k, 60, "Klondike 3.6p", "Popular shareware Klondike solitaire card game for classic Mac OS.", "/games/Klondike3.6p.sit", 28102 },
    { kCatGames, 1998, kArchFat, 70, "Klondike 7.7.1", "Later release of the popular Klondike solitaire card game.", "/games/Klondike7.7.1.sea_.sit", 224235 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchFat, 70, "La Cie Silverlining 6.5", "Hard disk formatting and partitioning utility bundled with La Cie storage devices.", "/apps/Silverlining_Software_v6.5.img__0.zip", 9535252 },
    { kCatUtilities, 1998, kArch68k, 75, "La Cie Silverlining Pro 6.5.9.1", "La Cie's hard-drive formatting and partitioning utility.", "/apps/Silverlining_Pro_v6.5.9.1.sit", 5977088 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1992, kArch68k, 0, "Labeler", "Adds custom Finder label colors and names.", "/apps/cd-labeler-fp3.hqx", 55589 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 60, "LabVIEW 2", "An early version of National Instruments' graphical dataflow programming environment for classic Mac OS.", "/apps/LabVIEW_2.sit_.hqx", 16436419 },
    { kCatDevTools, 1994, kArchFat, 70, "LabVIEW 3.1.1", "National Instruments' graphical dataflow programming environment for instrumentation and automation.", "/apps/LabVIEW_3.1.1.sit", 20205474 },
    { kCatDevTools, 1997, kArchPPC, 75, "LabVIEW 4.0", "Graphical programming environment release for building virtual instrumentation applications.", "/apps/LabVIEW_4.0_CD.iso_.zip", 177575391 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArch68k, 70, "LaserWriter 8 v8.1.1", "Apple's PostScript printer driver for LaserWriter and compatible printers.", "/apps/laserwriter8-v811.sit", 2615553 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArchFat, 70, "LaserWriter 8.0", "Apple's PostScript Level 2 printer driver for LaserWriter and compatible printers.", "/apps/LaserWriter_8.0.sit_.hqx", 1012322 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArchFat, 70, "LaserWriter 8.4.1", "Apple's PostScript printer driver for LaserWriter and compatible printers.", "/apps/LaserWriter_8.4.1.sit", 5636006 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 20, "Leather Goddesses of Phobos", "Infocom's tongue-in-cheek science-fiction text adventure.", "/games/LeatherGoddesses.dsk_.sit", 213028 },
    { kCatGames, 1991, kArch68k, 60, "Leisure Suit Larry 5", "Sierra's comedic graphic adventure game, subtitled Passionate Patti Does a Little Undercover Work.", "/games/LeisureSuitLarryV.img_.sit", 8213838 },
    { kCatGames, 1991, kArch68k, 60, "Lemmings 1.4.2 (French)", "Psygnosis's classic puzzle-platformer of guiding lemmings to safety; this is the French-localized release.", "/games/lemmings-french-1.4.2.sit", 1500709 },
    { kCatGames, 1991, kArch68k, 60, "Lemmings 1.5.2", "Guide hordes of lemmings safely to the exit in this Psygnosis puzzle-platformer classic.", "/games/lemmings_1_5_2.zip", 1577604 },
    { kCatGames, 1996, kArch68k, 70, "Lemmings Paintball", "Paintball-combat spinoff of the Lemmings puzzle series.", "/games/lemmings_paintball_mac.zip", 19668540 },
    { kCatGames, 1995, kArch68k, 60, "Leonard Nimoy's Primortals", "An unusual full-motion-video science fiction adventure CD-ROM game starring Leonard Nimoy, for classic Mac", "/games/leonard_nimoys_primortals_hybrid.iso_.sit", 238327385 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 40, "Letraset ColorStudio", "Professional 32-bit image editing and painting program that predated Photoshop.", "/apps/ColorStudio_System_Disk.bin", 819328 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Letraset Design Studio 1.0", "Page layout and design software from Letraset.", "/apps/Letraset_Design_Studio_1.0.zip", 3012191 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "LetraStudio 1.0", "Type design software for warping and shaping text into custom logotypes.", "/apps/LetraStudio10.zip", 1360114 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "LetterPerfect 2.1", "WordPerfect Corporation's compact, entry-level word processor.", "/apps/LetterPerfect2.1.sit", 2013032 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "Lexicross", "Word-based crossword puzzle game show.", "/games/lexicross.zip", 11393120 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 70, "Life Forms 1.0.1", "Credo Interactive's 3D character animation software used for choreography and motion visualization.", "/apps/Life_Forms_1.0.1_f.sit", 1128002 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1985, kArch68k, 20, "Lightspeed C", "Fast incremental C compiler from THINK Technologies, predecessor to THINK C.", "/apps/Lightspeed_C.img_.sit", 930179 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArchPPC, 75, "LightWave 3D 5.0", "NewTek's professional 3D modeling, animation, and rendering application, Mac release.", "/apps/LightWave_5.0_Release_0.sit", 4315425 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "LightWave 3D 5.5", "Updated release of NewTek's professional 3D animation and rendering application.", "/apps/LightWave_5.5_full.sit", 5961840 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "LightWave 3D 5.6", "3D modeling, animation and rendering software widely used in film and television production.", "/apps/LightWave_5.6_k.sit", 6385180 },
    { kCatGraphicsSound, 2000, kArchPPC, 81, "LightWave 3D 6.5", "Later Mac release of NewTek's LightWave 3D with a redesigned interface.", "/apps/LightWave6.5_final.sit", 13354978 },
    /* -- Games -- */
    { kCatGames, 2000, kArchPPC, 86, "Links LS 2000", "Access Software's realistic golf simulation, Macintosh CD-ROM edition.", "/games/links_ls_2000_mac_cd1.zip", 197648636 },
    { kCatGames, 1990, kArch68k, 60, "Links Pro", "Access Software's realistic golf simulation game.", "/games/Links_Pro_1.0_Floppy.sit", 3378588 },
    { kCatGames, 1994, kArch68k, 60, "Links Pro 2.0", "Access Software's realistic golf simulation game.", "/games/Links_Pro_2.0_CD.sit", 14829530 },
    { kCatGames, 1997, kArch68k, 70, "Links: Championship Edition (Disc 1)", "Access Software's realistic golf simulation game series for classic Mac OS.", "/games/Links_CE_Disc1.toast_.sit", 549445840 },
    { kCatGames, 1997, kArch68k, 70, "Links: Championship Edition Updater 1.0.4", "Update for Access Software's Links golf simulation game series on classic Mac OS.", "/games/Links_CE_1.0.4_Updater.sit", 2385585 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArch68k, 70, "Linotype FontExplorer 1.62e", "Linotype's font management and organization utility for classic Mac OS.", "/apps/Linotype_FontExplorer_1.62e.cdr", 721610752 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1992, kArch68k, 60, "Little Smalltalk 3.15", "Compact, freely distributed Smalltalk programming environment for Macintosh.", "/apps/littlesmalltalk3.15.sit_.hqx", 792561 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "Live Picture 1.0", "A high-end professional image editing application built around a resolution-independent IVUE image format", "/apps/livepicturext1.0_folder.sit", 590789 },
    { kCatGraphicsSound, 1996, kArchPPC, 70, "Live Picture 1.5.5", "A high-resolution image editing application using resolution-independent FITS technology.", "/apps/Live_Picture_1.5.5.sit", 1193285 },
    { kCatGraphicsSound, 1994, kArchPPC, 70, "Live Picture 2.0", "High-resolution image editing software using a resolution-independent IVUE image format.", "/apps/LivePicture2.0-MetaTools.sit", 1945065 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "LocalTalk Bridge 2.1", "Apple software for bridging LocalTalk and Ethernet AppleTalk network segments.", "/apps/localtalk_bridge_2.1.smi_.sit", 137831 },
    /* -- Games -- */
    { kCatGames, 1984, kArch68k, 10, "Lode Runner", "Dig, trap, and outrun enemies in this puzzle-platformer classic.", "/games/lode_runner.zip", 244985 },
    { kCatGames, 1984, kArch68k, 10, "Lode Runner 1.0", "Classic run-and-dig platform puzzle game for the original Macintosh.", "/games/LodeRunner1.0.sit_.hqx", 66897 },
    { kCatGames, 1994, kArch68k, 60, "Lode Runner 2", "Sierra's puzzle-platformer sequel to the classic Lode Runner.", "/games/Lode_Runner2Mac.sit", 499872735 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2001, kArchPPC, 91, "Logic Audio Platinum 5.0", "Emagic's flagship professional MIDI and audio sequencing application, later acquired by Apple.", "/apps/logic_audio_platinum_5.0.sit", 31291357 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 60, "Logical Journey of the Zoombinis", "Broderbund/TERC's beloved logic-puzzle adventure game for classic Mac OS.", "/games/zoombiniv11.zip", 68480895 },
    { kCatGames, 1990, kArch68k, 60, "Loom", "LucasArts's music-based graphic adventure game.", "/games/loom_1_0.zip", 23521700 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "Lotus 1-2-3 1.1", "Lotus's classic spreadsheet application, Macintosh release.", "/apps/Lotus1-2-3v1_1.sit", 3019540 },
    { kCatProductivity, 1991, kArch68k, 60, "Lotus 1-2-3 for Mac 1.0", "Lotus's spreadsheet software ported to classic Mac OS, notable as Lotus's attempt to compete with Excel on", "/apps/Lotus_1-2-3_1.0.mar", 5032192 },
    { kCatProductivity, 1985, kArch68k, 10, "Lotus Jazz", "Early integrated office suite for the original 128K/512K Macintosh from Lotus.", "/apps/Lotus_Jazz_MFS_400k.dc42.gz", 238661 },
    { kCatProductivity, 1986, kArch68k, 20, "Lotus Jazz 1.0a", "Lotus's integrated office suite for the original Macintosh combining word processing, spreadsheet, database", "/apps/Lotus_Jazz_1.0a_for_Macintosh_2-18-1986_3.5-800k.zip", 870417 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "LucasArts Game Pack", "Compilation disc bundling several LucasArts adventure and action titles.", "/games/lucasarts_game_pack.sit", 18419553 },
    { kCatGames, 1996, kArch68k, 60, "LucasArts Mac Game Pack I", "A compilation disc of classic LucasArts adventure games for classic Mac OS.", "/games/Lucasarts_Mac_CD_Game_Pack_I.iso", 33861632 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 60, "Mac Oberon 2.32", "Standalone implementation of the Oberon programming language and environment for Macintosh.", "/apps/macoberon_2.32_basics.hqx", 572768 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1997, kArchFat, 76, "Mac OS 7.6", "First release officially branded 'Mac OS' rather than 'System', unifying 68k and PowerPC support.", "/apps/MAC_OS_7-6_RETAIL.ISO", 262455296 },
    { kCatSystemExt, 1997, kArchPPC, 80, "Mac OS 8.0", "Major Mac OS release introducing the Platinum appearance and a multithreaded Finder.", "/apps/MAC_OS_8-0_RETAIL__0.ISO", 346341376 },
    { kCatSystemExt, 1998, kArchPPC, 85, "Mac OS 8.5", "Mac OS release dropping 68k support, adding Sherlock search and improved networking.", "/apps/MAC_OS_8-5_RETAIL_0.ISO", 577830912 },
    { kCatSystemExt, 1999, kArchPPC, 90, "Mac OS 9.0.4", "Update release of Mac OS 9, the final major version of classic Mac OS before Mac OS X.", "/apps/Apple_MacOS_9.0.4_USA.iso", 665770496 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 30, "Mac-A-Mug", "Cartoon face-composing toy program for building caricature portraits.", "/apps/Mac-a-Mug.sit", 167741 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1991, kArch68k, 10, "MacApp", "Apple's object-oriented application framework.", "/apps/macapp1.1.sit", 402366 },
    { kCatDevTools, 1985, kArch68k, 10, "MacBASIC 3.35", "Apple's unreleased but widely circulated native BASIC development environment for the original Macintosh.", "/apps/MacBASIC_335.hqx", 498107 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 70, "MacBench 2.0", "Ziff-Davis benchmarking suite for measuring classic Mac OS system performance.", "/apps/MacBench_2_0.sit", 2026077 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "MacChess 2.0.1", "A classic chess program for classic Mac OS.", "/games/MacChess_2.0.1.sit", 253948 },
    { kCatGames, 1997, kArch68k, 70, "MacChess 5.0", "A later version of the classic chess program for classic Mac OS.", "/games/MacChess_5.0_EN.sit", 364388 },
    /* -- Dev Tools -- */
    { kCatDevTools, 2001, kArchPPC, 86, "MacCVS 3.2b12 (Carbon)", "A graphical CVS version control client for Mac OS, this build running under the Carbon compatibility layer.", "/apps/MacCVS32b12.Carbon.sit", 1989722 },
    { kCatDevTools, 2000, kArch68k, 70, "MacCVS Client 1.4.2", "Client software for accessing CVS version control repositories from the Mac.", "/apps/MacCVSClient-1.4.2-68K.sit_.bin", 421760 },
    { kCatDevTools, 1999, kArchFat, 70, "MacCVS Pro 2.1b2", "A graphical CVS version control client for classic Mac OS developers.", "/apps/MacCVSPro2.1b2_Fat.sit", 97504 },
    { kCatDevTools, 1999, kArchFat, 70, "MacCVS Pro 2.2", "A graphical CVS version control client for classic Mac OS developers.", "/apps/MacCVS_Pro_2.2_Fat.sit", 995108 },
    { kCatDevTools, 1998, kArchFat, 70, "MacCVS Pro 2.2.1", "Graphical CVS version control client for classic Mac OS developers.", "/apps/MacCVS_Pro_2.2.1_Fat.sit", 995652 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 0, "MacDraft 1.2", "Innovative Data Design's precision CAD-style drafting application for Macintosh.", "/apps/MacDraft_1.2a.sit", 107611 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1987, kArch68k, 30, "MacDraft 1.2b", "Precision drafting and CAD-style drawing application for architectural and technical illustration.", "/apps/MacDraft_1.2b.sit", 149803 },
    /* -- Productivity -- */
    { kCatProductivity, 1989, kArch68k, 40, "MacDraft 2.1", "Innovative Data Design's precision drafting and CAD application.", "/apps/MacDraft_2.1.sit_.hqx", 1397163 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArchFat, 70, "MacDraft 3.0", "CAD-style precision drafting application for the Mac.", "/apps/MacDraft_3.0.sit", 661851 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArchFat, 70, "MacDraft 4.1", "Later release of Innovative Data Design's precision CAD-style drafting application.", "/apps/MacDraft_4.1.sit", 1113795 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArchPPC, 70, "MacDraft 4.2.2", "Later release of Innovative Data Design's precision drafting software.", "/apps/MacDraft_4.2.2.sit", 1559109 },
    /* -- Productivity -- */
    { kCatProductivity, 1998, kArchPPC, 75, "MacDraft 5.1", "Later PowerPC-native release of the MacDraft precision drafting application.", "/apps/MacDraft-5-1.zip", 324978685 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 81, "MacDraft 5.5", "Innovative Data Design's precision CAD drafting application for Mac OS.", "/apps/MacDraft_5.5.dmg", 24587474 },
    { kCatGraphicsSound, 1984, kArch68k, 60, "MacDraw", "Apple's classic object-based drawing application.", "/apps/macdrawii.sit", 1399086 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "MacDraw 1.9", "Apple's original object-oriented vector drawing application, one of the defining early Macintosh", "/apps/macdraw_1_9.zip", 2088544 },
    { kCatGraphicsSound, 1988, kArch68k, 30, "MacDraw 1.9.5", "Apple's original object-oriented drawing application for classic Macintosh.", "/apps/MacDraw_v1.9.5_800K.image_.sit", 350574 },
    { kCatGraphicsSound, 1987, kArch68k, 30, "MacDraw II 1.0", "Object-oriented drawing application from Claris.", "/apps/MacDraw_II_1.0E.sit", 156818 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "MacDraw II 1.1", "Claris's enhanced successor to the original MacDraw drawing application.", "/apps/MacDraw_II_1.1.bin", 125312 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "MacDraw II 1.1b", "Object-oriented drawing application and successor to the original MacDraw.", "/apps/MacDraw_II_1-1b.dsk", 1474560 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "MacDraw Pro 1.0", "Claris's professional object-oriented drawing application.", "/apps/MacDraw_Pro_10.sit", 1785739 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "MacDraw Pro 1.0 (Swedish)", "Swedish-language release of Claris MacDraw Pro object-oriented drawing software.", "/apps/MacDraw_Pro_1.0v1_Swedish_.sit", 1729170 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "MacDraw Pro 1.5", "Claris's professional illustration application, the final evolution of the MacDraw line.", "/apps/MacDraw_Pro_1.5v2.sit_.hqx", 3844578 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "MacDraw Pro 1.5.3", "Object-oriented drawing and illustration software from Claris.", "/apps/macdraw-pro-153-us.sit", 1988600 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 10, "MacEnvelope", "Envelope and label printing utility.", "/apps/macenvelope_v52.zip", 498358 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "MacFlow 3.0.1", "Mainstay's flowcharting and diagramming application for classic Mac OS.", "/apps/MacFlow_3.0.1.sit", 105061 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1984, kArch68k, 0, "MacForth Plus", "Classic Macintosh integrated development environment for the Forth programming language.", "/apps/MacForth_Plus_Disk_2_Extended.img", 838484 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArch68k, 60, "MacGhostView 4.3.1", "PostScript and PDF file viewer for the classic Mac OS based on Ghostscript.", "/apps/macghostview431-sitx.bin", 8230400 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "MacGolf Classic", "Simple, popular shareware golf simulation.", "/games/macgolf23.zip", 9574427 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArchFat, 60, "MacGzip 1.1.3", "Classic Macintosh utility for compressing and decompressing gzip archives.", "/apps/MacGzip_FAT_1.1.3.sit_.hqx", 282014 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1995, kArch68k, 70, "MachTen 4.0", "Tenon Intersystems' hybrid Unix operating environment that ran alongside classic Mac OS, including X11", "/apps/MachTen_4.0_X_Window_X11R5.sit", 11153658 },
    { kCatDevTools, 1997, kArchPPC, 70, "MachTen 4.0.3", "Unix operating environment that ran as an application under classic Mac OS, from Tenon Intersystems.", "/apps/MachTen_4.0.3.sit", 41765380 },
    { kCatDevTools, 1997, kArch68k, 70, "MachTen 4.1.1", "Unix operating environment that ran as a hosted OS on top of the classic Mac OS.", "/apps/MachTen4.1.1.sit", 68006987 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "MacHTTP", "Early shareware web server software for the Mac.", "/apps/machttp26.sea_.hqx", 332409 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArchFat, 70, "MacInTalk Pro", "Apple's text-to-speech synthesis software for classic Mac OS.", "/apps/MacInTalk_PRO.sit", 4630348 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 10, "MacInTax", "Personal income tax preparation software.", "/apps/Macintax_88.zip", 341467 },
    { kCatProductivity, 1991, kArch68k, 40, "MacInTax 1991", "Tax preparation software from ChipSoft (later Intuit) for the classic Mac OS.", "/apps/MacInTax_1991.sit", 4332854 },
    { kCatProductivity, 1993, kArch68k, 60, "MacInTax 1993", "ChipSoft's tax preparation software for Macintosh, 1993 tax year edition.", "/apps/MacInTax_1993.sit", 4337705 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "Macintosh Common Lisp 3.0", "Digitool's Common Lisp programming environment for the classic Mac OS.", "/apps/Mac_Common_Lisp_3.0.sit", 625472889 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "Macintosh Easy Open 1.1.1 (German)", "Apple's extension for automatically translating documents between application file formats on classic Mac", "/apps/EasyOpen_1_1_1_ger.hqx", 380729 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1992, kArch68k, 60, "Macintosh Programmer's Workshop", "Apple's command-line based integrated development environment for classic Mac OS software.", "/apps/mpw-gm.img__0.bin", 25109760 },
    { kCatDevTools, 1991, kArch68k, 50, "Macintosh Programmer's Workshop (MPW)", "Apple's official command-line based development environment for classic Mac OS software.", "/apps/MPW_1.0_3.1_3.2_and_68k_Developer_Kit.zip", 45831007 },
    { kCatDevTools, 1989, kArch68k, 60, "Macintosh Programmer's Workshop 2.0.2", "Apple's official command-line development environment for Mac OS, known as MPW.", "/apps/MPW_2.0.2.sit", 2238845 },
    { kCatDevTools, 1992, kArch68k, 60, "Macintosh Programmer's Workshop 3.3", "Apple's official command-line development environment for classic Mac OS.", "/apps/mpw_3.3.sit", 3855152 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1990, kArch68k, 40, "MacKermit", "File transfer and terminal emulation client implementing the Kermit protocol.", "/apps/mackermit.hqx", 703604 },
    { kCatInternet, 1991, kArch68k, 60, "MacKermit 4.0", "A Macintosh implementation of the Kermit file-transfer and terminal protocol.", "/apps/MacKermit_ver40.sit", 184926 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "MacLinkPlus 7", "DataViz's widely used file format translation utility for exchanging documents between Mac and PC", "/apps/maclinkplus7.zip", 1459752 },
    { kCatUtilities, 1994, kArch68k, 60, "MacLinkPlus 7.5", "Earlier release of DataViz's cross-platform file translation utility.", "/apps/MacLinkPlus7.5.sit", 986913 },
    { kCatUtilities, 1997, kArchPPC, 75, "MacLinkPlus 8.02", "DataViz's file format translation utility for cross-platform document exchange.", "/apps/MacLink_Plus_8.02_0.sit", 2640328 },
    { kCatUtilities, 1996, kArch68k, 70, "MacLinkPlus 8.1", "File translation utility for converting documents between Mac and PC application formats.", "/apps/MacLinkPlus_8.1.sit", 159491 },
    { kCatUtilities, 1993, kArch68k, 60, "MacLinkPlus 8.10", "File format translation utility for exchanging documents between Mac and PC applications.", "/apps/MacLink_Plus_8.10_DC42.sit", 3369596 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 70, "MacLynx", "Text-based Web browser client port of Lynx for classic Mac OS.", "/apps/MacLynx_ss1.hqx", 978022 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1992, kArch68k, 60, "MacMETH 3.2.8", "Modula-2 and Oberon programming environment developed at ETH Zurich.", "/apps/MacMETH_3.2.8.sea_.bin", 1188480 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 10, "MacMoney", "Personal finance and budget-tracking software.", "/apps/MacMoney.sit", 373229 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1984, kArch68k, 10, "MacPaint", "Apple's original bitmap paint program.", "/apps/MacPaint.img", 402432 },
    { kCatGraphicsSound, 1984, kArch68k, 10, "MacPaint 1.4", "Apple's iconic original bitmap painting program for the Macintosh.", "/apps/MacPaint_1.4F.sit", 33451 },
    { kCatGraphicsSound, 1984, kArch68k, 10, "MacPaint 1.5", "Early version of Apple's iconic original bitmap-painting application, bundled with the first Macintosh.", "/apps/macpaint_1_5.zip", 9115429 },
    { kCatGraphicsSound, 1988, kArch68k, 30, "MacPaint 2.0", "Later Claris release of Apple's original bitmap-painting application.", "/apps/MacPaint_2.0.bin", 6272 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1992, kArch68k, 60, "MacPerl", "Port of the Perl scripting language for classic Mac OS.", "/apps/mac-perl-418.hqx", 1755872 },
    { kCatDevTools, 1998, kArchFat, 70, "MacPerl 4.1.3", "Native port of the Perl scripting language interpreter for classic Mac OS.", "/apps/MacPerl_4.1.3.sit", 1760616 },
    { kCatDevTools, 1998, kArchFat, 70, "MacPerl 4.1.8", "Native port of the Perl scripting language interpreter for classic Mac OS.", "/apps/MacPerl_4.1.8.sit", 2898283 },
    { kCatDevTools, 1996, kArch68k, 70, "MacPerl 5.0.3", "The classic Mac OS port of the Perl scripting language interpreter.", "/apps/MacPerl_5.0.3.sit", 5958176 },
    { kCatDevTools, 1997, kArchPPC, 75, "MacPerl 5.1.4r4", "Native port of the Perl scripting language for the classic Mac OS.", "/apps/MacPerl_5.1.4r4.sit", 4522764 },
    { kCatDevTools, 1998, kArch68k, 75, "MacPerl 5.15r4", "Native Macintosh port of the Perl scripting language.", "/apps/MacPerl_515r4.sit", 3355180 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "MacPGP", "Classic Mac port of Pretty Good Privacy encryption.", "/apps/macpgp-bundle.sit", 2981961 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "MacPPP 2.0.1", "Dial-up PPP networking control panel.", "/apps/MacPPP201.sea_.hqx", 58189 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArch68k, 60, "MacPPP 2.5.3", "Early dial-up PPP networking extension that brought internet connectivity to the classic Mac OS.", "/apps/MacPPP_2.5.3.sit", 78170 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "MacProject II 2.1", "Claris's project management and scheduling application for Macintosh.", "/apps/macproject-ii-21fv2.sit", 996051 },
    { kCatProductivity, 1991, kArch68k, 10, "MacProject II Demo", "Project scheduling with Gantt charts, demo edition.", "/apps/macproject_ii.sit", 99880 },
    { kCatProductivity, 1993, kArch68k, 60, "MacProject Pro", "Professional project scheduling and management software.", "/apps/MacProject.sit", 50443 },
    { kCatProductivity, 1994, kArchFat, 70, "MacProject Pro 1.5", "Claris's advanced project management application, successor to MacProject II.", "/apps/MacProject-Pro-15v2.sit", 5164335 },
    { kCatProductivity, 1990, kArch68k, 60, "MacProof", "A grammar and writing-style checking utility for classic Mac OS word processing documents.", "/apps/MacProof.zip", 394049 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 70, "MacPython 1.3.3", "An early port of the Python programming language and interpreter to Mac OS.", "/apps/MacPython_1.3.3.sit", 8519973 },
    { kCatDevTools, 1996, kArch68k, 60, "MacPython 1.4", "Native port of the Python programming language for the classic Mac OS.", "/apps/MacPython_1.4.sit", 3747799 },
    { kCatDevTools, 1999, kArch68k, 75, "MacPython 1.5.2", "Early native Macintosh port of the Python programming language.", "/apps/MacPython152src.hqx", 8378946 },
    { kCatDevTools, 2002, kArchPPC, 86, "MacPython 2.2.3", "Native build of the Python interpreter and development tools for classic Mac OS.", "/apps/MacPython223full_0.hqx", 16723456 },
    { kCatDevTools, 2004, kArchPPC, 91, "MacPython 2.3.5", "Later native Macintosh port of Python 2.3, including full toolchain for Classic Mac OS.", "/apps/MacPython235full.bin", 7091840 },
    /* -- Games -- */
    { kCatGames, 1997, kArch68k, 70, "MacQuake 1.0.2", "Community port of id Software's Quake engine to 68k Macintosh.", "/games/MacQuake68k_1.0.2.sit", 287125 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchPPC, 75, "MacRAR 2.0 (Beta 1)", "Utility for extracting RAR compressed archives on classic Mac OS.", "/apps/MacRAR_2.0b1.hqx", 437681 },
    /* -- Dev Tools -- */
    { kCatDevTools, 0, kArchPPC, 70, "MacRenderMan 1.3.4", "Pixar's PhotoRealistic RenderMan 3D rendering software for Mac OS.", "/apps/MacRenderMan_1.3.4.sit", 1024622 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Macromedia Director 3.1", "Macromedia's multimedia authoring and animation application.", "/apps/macromedia_director_3-1.sit", 14189790 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "Macromedia Director 4.0.4", "Macromedia's landmark multimedia authoring and animation tool.", "/apps/Director_4.0.4.img_.sit", 350704392 },
    { kCatGraphicsSound, 1995, kArchPPC, 70, "Macromedia Director 5", "Later release of Macromedia's multimedia authoring software.", "/apps/director_5.zip", 13166321 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1995, kArchFat, 70, "Macromedia Director 5.0", "Macromedia's landmark multimedia authoring tool for building interactive CD-ROM titles and Shockwave content.", "/apps/Director_5_CD.toast_.bin", 353235072 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Macromedia Director 6", "Multimedia authoring software for building interactive CD-ROM titles and animations.", "/apps/Director_6_Authorized.img_.sit", 249474547 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Macromedia Director 6.5", "Further release of Macromedia's multimedia and interactive authoring application.", "/apps/Director_6.5.iso_.zip", 351650396 },
    { kCatGraphicsSound, 2000, kArchPPC, 80, "Macromedia Director 8.0", "Multimedia and interactive content authoring application.", "/apps/Director_8.sit", 20602154 },
    { kCatGraphicsSound, 2001, kArchPPC, 85, "Macromedia Director 8.5", "Later release of Macromedia's multimedia and Shockwave authoring tool (trial installer).", "/apps/Director85G-trial.bin", 28551296 },
    /* -- Dev Tools -- */
    { kCatDevTools, 2001, kArchPPC, 86, "Macromedia Director 8.5.1 Updater", "Update for Macromedia Director, the multimedia authoring tool for building interactive CD-ROM titles and", "/apps/Director_8_5_1_Updater_0.hqx", 5730447 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArchPPC, 70, "Macromedia Dreamweaver 1.0", "The original release of Macromedia's visual HTML editor and web site development tool for classic Mac OS.", "/apps/Dreamweaver_1.0_k.sit", 111542 },
    { kCatInternet, 1998, kArchPPC, 70, "Macromedia Dreamweaver 2.0", "Macromedia's visual HTML editor and web site development tool, an early version of the industry-standard web", "/apps/Dreamweaver_2.0_0.sit", 11971224 },
    { kCatInternet, 2000, kArchPPC, 81, "Macromedia Dreamweaver 4", "A later version of Macromedia's visual HTML editor and web site development tool for Mac OS.", "/apps/Macromedia_Dreamweaver_4.sit", 15828018 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Macromedia Extreme 3D 2.0", "Macromedia's 3D modeling and rendering application.", "/apps/Extreme_3D_2.img_.sit", 271123238 },
    { kCatGraphicsSound, 2000, kArchPPC, 81, "Macromedia Fireworks 4", "Macromedia's web graphics creation and optimization application for Mac OS.", "/apps/Macromedia_Fireworks_4.sit", 20431275 },
    { kCatGraphicsSound, 1999, kArchPPC, 71, "Macromedia Flash 4 (Trial)", "Trial edition of Macromedia's vector animation and interactive web content authoring tool.", "/apps/Flash_4_Trial.sit", 9970922 },
    { kCatGraphicsSound, 1996, kArchPPC, 70, "Macromedia FreeHand 7.0", "Macromedia's professional vector illustration application, successor to Aldus FreeHand.", "/apps/FreeHand-7-RC3-img.bin", 12914816 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Macromedia FreeHand 8", "Vector illustration software release with support for multiple-page documents and Flash export.", "/apps/freehand_8.hqx", 19151055 },
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Macromedia FreeHand 9", "Macromedia's professional vector illustration software.", "/apps/freehand_9.img_.sit", 12792344 },
    { kCatGraphicsSound, 2000, kArchPPC, 75, "Macromedia FreeHand 9.0.1", "Later release of Macromedia's vector illustration software.", "/apps/FreeHand_9.0.1.img_.sit", 371973187 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "MacroMind Director", "Multimedia authoring and animation application.", "/apps/MacroMind_Director_2.sit", 4406745 },
    { kCatGraphicsSound, 1987, kArch68k, 30, "MacroMind Director 1.0", "First release of Director, the score-based multimedia authoring tool that predated Macromedia.", "/apps/MacroMind_Director_1.sit", 2141240 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 10, "MacsBug", "Apple's low-level debugger for the classic Mac OS.", "/apps/MacsBug_IV.sit", 11413 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1991, kArch68k, 60, "MacsBug 5.1", "Apple's low-level machine-language debugger for classic Mac OS.", "/apps/MacsBug_5.1.sit", 15142 },
    { kCatDevTools, 1993, kArch68k, 60, "MacsBug 5.3a5", "Apple's low-level source debugger for diagnosing Macintosh application crashes.", "/apps/MacsBug_5.3A5.sit", 16762 },
    { kCatDevTools, 1994, kArch68k, 70, "MacsBug 6.1", "Apple's low-level source-code debugger for diagnosing crashes on classic Mac OS.", "/apps/MacsBug_6.1.sit", 136648 },
    { kCatDevTools, 1998, kArchFat, 75, "MacsBug 6.5.4", "Later release of Apple's MacsBug low-level debugger.", "/apps/MacsBug_6.5.4a4.sit", 614489 },
    { kCatDevTools, 1994, kArch68k, 60, "MacsBug 6.5.4a3", "Apple's low-level machine-language debugger used to troubleshoot crashes and freezes on classic Mac OS.", "/apps/MacsBug_6.5.4a3c1.sit", 239539 },
    { kCatDevTools, 1998, kArchFat, 0, "MacsBug 6.6.1", "Apple's low-level source and object code debugger for classic Macintosh development.", "/apps/MacsBug_6.6.1.sit_.hqx", 443213 },
    { kCatDevTools, 1998, kArchFat, 70, "MacsBug 6.6.2", "Late release of Apple's MacsBug low-level debugger.", "/apps/MacsBug_6.6.2.sit", 80431 },
    { kCatDevTools, 2000, kArchFat, 70, "MacsBug 6.6.3", "Updated build of Apple's MacsBug low-level debugger.", "/apps/MacsBug_6.6.3.sit", 377002 },
    { kCatDevTools, 1993, kArch68k, 0, "MacsBug Reference", "Reference documentation and tools for the MacsBug debugger.", "/manuals/Macsbug_6.1_Reference_1989.pdf", 5846454 },
    /* -- Utilities -- */
    { kCatUtilities, 2003, kArch68k, 70, "MacScan", "SecureMac's spyware and privacy-risk detection utility for classic Mac OS.", "/apps/MacScan.hqx", 190633 },
    /* -- Productivity -- */
    { kCatProductivity, 1992, kArch68k, 10, "MacSchedule 2.1", "Freeware appointment book and to-do list manager.", "/apps/MacSchedule.zip", 61609 },
    /* -- Games -- */
    { kCatGames, 1995, kArch68k, 70, "MacSki 1.6", "A free downhill skiing game with user-designable slopes.", "/games/MacSki_v1.6.sit", 907569 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1992, kArch68k, 60, "MacSLIP", "Early SLIP dial-up networking control panel.", "/apps/MacSLIP.sit_.hqx", 290683 },
    { kCatInternet, 1998, kArchFat, 70, "MacSOUP 2.8.3", "Offline newsreader for downloading and composing Usenet posts without a live connection.", "/apps/MacSOUP-X-F-2.8.3.zip", 650865 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "MacSpin 2.0", "Interactive 3D statistical data visualization software.", "/apps/MacSpin_2.0.image_.zip", 360265 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArchPPC, 70, "MacSSH", "Free SSH and Telnet terminal client for the classic Mac OS.", "/apps/MacSSHPPC.F.sea_.hqx", 895949 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArch68k, 60, "MacTcl 7.3", "Native implementation of the Tcl/Tk scripting language for the classic Mac OS.", "/apps/MacTcl7.3.sea_.hqx_.Z", 744819 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "MacTCP 2.0.2", "Apple's early TCP/IP networking stack control panel for classic Mac OS.", "/apps/MacTCP_2.0.2.sit", 24639 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1991, kArch68k, 60, "MacTCP 2.0.6", "Apple's original TCP/IP control panel for System 7.", "/apps/MacTCP206.sea_.hqx", 194409 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 60, "MacTCP 2.1", "Apple's classic TCP/IP networking control panel, predecessor to Open Transport.", "/apps/mactcp21patch.sit", 27675 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "MacTCP Watcher 1.1.1", "Network diagnostic utility for monitoring MacTCP connections and statistics.", "/apps/MacTCP_Watcher_1.1.1.sit", 70233 },
    { kCatInternet, 1994, kArch68k, 60, "MacTCP Watcher 1.1.2", "Diagnostic utility for monitoring MacTCP network connections on classic Macintosh.", "/apps/MacTCPWatcher_112.sit", 74129 },
    { kCatInternet, 1990, kArch68k, 60, "MacTEP", "An early terminal emulation program for classic Mac OS used for dial-up and network text sessions.", "/apps/MacTEP.hqx", 11840 },
    { kCatInternet, 1984, kArch68k, 0, "MacTerminal", "Apple's original terminal emulator for connecting to modems and mainframe systems.", "/apps/MacTerminal.hqx", 271041 },
    { kCatInternet, 1988, kArch68k, 30, "MacTerminal 2.2", "One of Apple's earliest terminal emulation applications for the Macintosh.", "/apps/MacTerminal2.2.sit", 56680 },
    { kCatInternet, 1988, kArch68k, 40, "MacTerminal 2.3", "Apple's own early terminal emulation software for connecting classic Macs to mainframes and modems.", "/apps/MacTerminal23.sit_.hqx", 88187 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "MacTest II/IIx 3.1", "Apple's factory hardware diagnostic and burn-in test utility for the Macintosh II and IIx.", "/apps/MacTest_II-IIx_3.1.hqx", 839164 },
    { kCatUtilities, 1996, kArchFat, 0, "MacTest Pro (November 1996)", "Apple's official factory-level hardware diagnostic CD used by service technicians to test Macintosh hardware.", "/apps/MacTest_Pro_PPC_November_1996.iso", 89747456 },
    { kCatUtilities, 1995, kArchFat, 0, "MacTest Pro (October 1995)", "Apple's official factory-level hardware diagnostic CD used by service technicians to test Macintosh logic", "/apps/MacTest_Pro_October_1995.iso", 89440256 },
    { kCatUtilities, 1996, kArchPPC, 0, "MacTest Pro PPC (May 1996)", "Apple's official factory diagnostic CD updated for Power Macintosh hardware testing.", "/apps/MacTest_Pro_PPC_May_1996.iso", 89440256 },
    { kCatUtilities, 1993, kArch68k, 60, "MacTools", "Central Point's disk repair and undelete utility suite.", "/apps/MacTools.hqx", 140890 },
    { kCatUtilities, 1993, kArch68k, 60, "MacTools Optimizer", "Disk optimization component of the Central Point MacTools utility suite.", "/apps/MacTools_Optimizer.sit", 871770 },
    { kCatUtilities, 1994, kArch68k, 60, "MacTools Pro", "Disk utility and file recovery suite from Central Point Software/Symantec.", "/apps/MacTools_Pro.sit", 9383914 },
    { kCatUtilities, 2002, kArchFat, 70, "Mactracker 1.0 (Classic)", "Ian Page's reference database application cataloging Apple hardware specifications, built to run on classic", "/apps/mactracker_1.0_classic.sit", 1128054 },
    { kCatUtilities, 2004, kArchPPC, 86, "Mactracker 1.6.2", "A later version of Ian Page's reference database application cataloging Apple hardware specifications.", "/apps/mactracker162.sit", 2363297 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "MacWeb", "One of the earliest graphical web browsers for the Mac.", "/apps/MacWeb.2.0.sit", 453553 },
    { kCatInternet, 1996, kArchFat, 70, "MacWeb 4.03B2", "Lightweight early web browser developed at MicroWeb by MCC.", "/apps/MacWeb4.03B2.Hqx", 769949 },
    { kCatInternet, 1996, kArch68k, 60, "MacWeb 4.04b1", "Lightweight web browser for the classic Mac OS from MicroDynamics.", "/apps/MacWeb4.04b1.Hqx", 868638 },
    /* -- Utilities -- */
    { kCatUtilities, 1985, kArch68k, 0, "MacWorks Plus II", "Apple's environment for running Lisa Office System software on the Macintosh XL.", "/apps/MacWorks_Plus_II.zip", 577718 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "MacWrite 3.4", "Apple's original bundled word processor for the Macintosh in its later 3.x revision.", "/apps/MacWrite_3.4.sit", 301793 },
    { kCatProductivity, 1988, kArch68k, 40, "MacWrite 4.5", "Claris's word processor bundled with early classic Macs.", "/apps/MacWrite45.sit", 60965 },
    { kCatProductivity, 1992, kArch68k, 60, "MacWrite 4.5 (Italian)", "Claris's classic WYSIWYG word processor for classic Mac OS, localized for Italian.", "/apps/MacWrite4.5ITA.sit", 61165 },
    { kCatProductivity, 1989, kArch68k, 0, "MacWrite 4.6", "Earlier release of Claris's classic Macintosh word processing application.", "/apps/macwrite_4_6.zip", 1203105 },
    { kCatProductivity, 1991, kArch68k, 60, "MacWrite 5.0", "Claris's classic Macintosh word processing application.", "/apps/MacWrite-v5.sit", 213786 },
    { kCatProductivity, 1991, kArch68k, 60, "MacWrite 5.01 (Dutch)", "Claris's classic word processor; this is the Dutch-localized release.", "/apps/MacWrite_5.01-NL_image.sit", 430804 },
    { kCatProductivity, 1989, kArch68k, 60, "MacWrite II", "Claris's classic word processor, sequel to the original MacWrite.", "/apps/macwrite.dmg", 6519390 },
    { kCatProductivity, 1989, kArch68k, 60, "MacWrite II (German)", "Claris's popular WYSIWYG word processor for classic Mac OS, this release localized for German.", "/apps/MacWrite_II_DE.sit", 316483 },
    { kCatProductivity, 1992, kArch68k, 60, "MacWrite Pro 1.0", "Claris word processor combining MacWrite's simplicity with advanced page layout features.", "/apps/MacWrite_Pro_1.0v4_EN-US.sit", 1789920 },
    { kCatProductivity, 1993, kArch68k, 60, "MacWrite Pro 1.0v4", "Word processor from Claris, successor to the original MacWrite.", "/apps/MacWrite-Pro-1.0v4-DC42.sit", 2059480 },
    { kCatProductivity, 1993, kArch68k, 70, "MacWrite Pro 1.5", "Claris's advanced word processor with page layout features, educational-edition build.", "/apps/MacWritePro1.5v3_Edu.sit", 4048678 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1992, kArch68k, 40, "MacWWW (Samba)", "One of the earliest graphical web browsers for the Macintosh, developed at CERN.", "/apps/MacWWW.hqx", 482635 },
    { kCatInternet, 1993, kArch68k, 60, "MacX 1.5", "X Window System client that let a Macintosh display X11 applications from remote Unix hosts.", "/apps/MacX_1.5.sit", 6842812 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 0, "MacZap", "Simple utility to zap the PRAM.", "/apps/MacZap42.hqx", 155959 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArch68k, 70, "MacZoop 2.6.1", "A free C++ application framework wrapping the classic Mac OS Toolbox, used to speed up native Mac software", "/apps/MacZoop_2.6.1.sit", 1559779 },
    /* -- Featured -- */
    { kCatFeatured, 1994, kArchFat, 60, "Maelstrom", "Asteroids reborn, with color graphics and a killer soundtrack.", "/games/Maelstrom_1.3.2.sit", 672743 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 60, "Maelstrom 1.3", "Ambrosia Software's Asteroids-inspired arcade shooter, a Mac classic.", "/games/mac-maelstrom-13.sit", 748546 },
    { kCatGames, 1992, kArch68k, 60, "Maelstrom 1.4.0", "Asteroids-style arcade shooter from Ambrosia Software.", "/games/Maelstrom-140.sit", 677980 },
    { kCatGames, 1997, kArchPPC, 70, "Maelstrom 1.4.2", "Ambrosia Software's beloved Asteroids-inspired arcade shooter.", "/games/maelstrom-142.hqx", 1075335 },
    { kCatGames, 1995, kArchFat, 70, "Maelstrom 1.4.3", "Updated build of Ambrosia Software's Asteroids-style arcade shooter.", "/games/Maelstrom_1.4.3_f.zip", 838008 },
    { kCatGames, 1996, kArchPPC, 70, "Maelstrom 3.0.6", "PowerPC-native release of Ambrosia's popular asteroid-blasting arcade game.", "/games/maelstrom-3.0.6-ppc_0.sit", 840947 },
    { kCatGames, 1986, kArch68k, 0, "Mah-Jongg", "Classic tile-matching solitaire game.", "/games/Mahjongg.dmg", 27330821 },
    { kCatGames, 1994, kArch68k, 70, "Mahjong Palace 1.04", "Shareware Mahjong solitaire tile-matching game for classic Macintosh.", "/games/mahjong-palace-104-classic.sit", 7330715 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 75, "Mailsmith 1.0", "Bare Bones Software's powerful email client built on their text-editing engine.", "/apps/Install_Mailsmith_1.0.sit", 12787500 },
    { kCatInternet, 2000, kArch68k, 70, "Mailsmith 1.1.8 Update", "Update for Bare Bones Software's Mailsmith, a scriptable email client for classic Mac OS.", "/apps/Mailsmith_1.1.8_Update.smi_.sit", 2632394 },
    { kCatInternet, 2000, kArchPPC, 81, "Mailsmith 1.5 (Demo)", "Demo of Bare Bones Software's powerful scriptable email client for classic Mac OS.", "/apps/Mailsmith_1.5_Demo.smi_.bin", 8401792 },
    { kCatInternet, 2003, kArchPPC, 86, "Mailsmith 1.5.3 Update", "Update for Bare Bones Software's Mailsmith, a scriptable email client for Mac OS.", "/apps/Mailsmith_153_Update.smi_.bin", 5209984 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "Managing Your Money 3.0", "Andrew Tobias's personal finance and checkbook management software for the Macintosh.", "/apps/Managing_Your_Money_3.0.sit", 451819 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 60, "Manhole", "Cyan's whimsical explorable children's adventure, precursor to Myst.", "/games/Manhole.SIT", 2383562 },
    { kCatGames, 1988, kArch68k, 0, "Manhunter: New York", "Sierra's dystopian graphic adventure game.", "/games/manhunter-ny-dc42.sit", 1691452 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArchPPC, 75, "Maple V Release 5.1", "Waterloo Maple's symbolic and numeric mathematics computing environment.", "/apps/Maple_V_Release_5.1.zip", 80720609 },
    /* -- Featured -- */
    { kCatFeatured, 1994, kArchFat, 60, "Marathon", "Bungie's landmark sci-fi first-person shooter.", "/games/marathon.sit", 5627676 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 70, "Marathon (Beta)", "A pre-release beta build of Bungie's Marathon, the influential science fiction first-person shooter for", "/games/Marathon_Beta.sit", 764058 },
    { kCatGames, 1995, kArch68k, 60, "Marathon 2: Durandal", "Bungie's science-fiction first-person shooter and sequel to Marathon.", "/games/Marathon_2_DiscImageCreator.zip", 95635229 },
    { kCatGames, 1996, kArchFat, 70, "Marathon Infinity", "Third entry in Bungie's Marathon trilogy, with Forge/Anvil editors.", "/games/marathon_infinity.sit", 37309889 },
    { kCatGames, 1996, kArchFat, 70, "Marathon Infinity (Demo)", "Demo of the third game in Bungie's Marathon science-fiction first-person shooter trilogy.", "/games/Marathon_Infinity_Demo.sit_.hqx", 26833478 },
    { kCatGames, 1994, kArchFat, 70, "Marathon Trilogy", "A compilation of Bungie's Marathon, Marathon 2: Durandal, and Marathon Infinity first-person shooters.", "/games/Marathon_Trilogy_RAW.zip", 521547246 },
    { kCatGames, 2000, kArchFat, 70, "Marathon Trilogy Collection", "Collected release of Bungie's Marathon first-person shooter trilogy for classic Mac OS.", "/games/MarathonCollection.sit_.bin", 164078592 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "Mariah", "Financial spreadsheet modeling application.", "/apps/Mariah.sit", 736502 },
    /* -- Games -- */
    { kCatGames, 1996, kArchPPC, 70, "Marine Doom", "US Marine Corps training modification of id Software's Doom, ported to Mac OS.", "/games/Mac_Marine_Doom.sit", 2181715 },
    /* -- Productivity -- */
    { kCatProductivity, 2003, kArchPPC, 86, "Mariner Write 3.7.2", "Mariner Software's word processor for Mac OS, a spiritual successor to WriteNow.", "/apps/Mariner_Write_Mac_3_7_2.dmg", 10423352 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Mask Pro 2.0", "Extensis Photoshop plug-in for creating precise image masks and cutouts.", "/apps/extensis-mask-pro-2_0.sit", 5864572 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "Master Juggler 1.91", "Font and desk accessory management utility for the classic Mac OS.", "/apps/MasterJuggler.1.91.sit", 392891 },
    /* -- Games -- */
    { kCatGames, 1995, kArch68k, 60, "Master Levels for Doom II", "An official expansion pack of additional levels for id Software's Doom II.", "/games/Master_Levels_for_Doom_II.sit", 155806789 },
    { kCatGames, 1993, kArch68k, 60, "Master of Orion", "MicroProse's 4X space strategy game of galactic empire building.", "/games/Master_Of_Orion.SIT", 4394197 },
    { kCatGames, 1996, kArch68k, 70, "Master of Orion II", "MicroProse's acclaimed 4X space strategy game sequel, ported to classic Mac OS.", "/games/MasterOfOrionII1.4.0.sit_.bin", 207585152 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "Master Tracks Pro 6", "MIDI sequencing software from Passport Designs for the classic Mac OS.", "/apps/MasterTracks_Pro6.sit", 1964930 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 60, "MasterJuggler 1.1.5", "Alsoft's font and desk accessory management utility, a Suitcase competitor.", "/apps/MasterJuggler_v1.1.5.image_.sit", 420208 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "MasterJuggler 1.57b", "ALSoft's font and desk accessory suitcase management utility for classic Mac OS, a rival to Suitcase.", "/apps/MasterJuggler_v1.57b.sit", 198316 },
    { kCatUtilities, 1990, kArch68k, 0, "MasterJuggler 1.58", "ALSoft's classic Macintosh font and desk accessory management utility.", "/apps/MasterJuggler_v1.58.img_.sit", 362638 },
    { kCatUtilities, 1994, kArch68k, 60, "MasterJuggler Pro", "ALSoft's advanced font and suitcase management utility for classic Macintosh.", "/apps/MasterJuggler_Pro.image_.sit", 699073 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 30, "Math Rabbit", "The Learning Company's early-elementary math game starring Math Rabbit and friends.", "/games/Math_Rabbit_v3.sit", 2452389 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArchFat, 70, "Mathcad Plus 6.0", "Engineering and scientific calculation software with live mathematical notation.", "/apps/Mathcad_Plus_6.0.sit__0.zip", 10229785 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 40, "Mathematica 1.22", "A very early version of Wolfram Research's symbolic and numeric computation environment for classic Mac OS.", "/apps/Mathematica_1.22.sit", 1154635 },
    { kCatDevTools, 1993, kArch68k, 60, "Mathematica 2.2", "Earlier 68k-native release of Wolfram's Mathematica computing environment.", "/apps/mathematica_2.2.sit_.hqx", 4307016 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArchFat, 70, "Mathematica 2.2.2", "Wolfram Research's technical computing and symbolic mathematics application.", "/apps/Mathematica_2.2.2_FAT.sit", 9552430 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArchPPC, 70, "Mathematica 3.0", "Wolfram Research's technical computing and symbolic mathematics environment.", "/apps/Mathematica_3.0.img_.sit", 52247076 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2000, kArchPPC, 81, "Mathematica 4.1.5", "Later Classic-compatible release of Wolfram Research's Mathematica.", "/apps/Mathematica_4.1.5.dmg", 49893406 },
    /* -- Dev Tools -- */
    { kCatDevTools, 2002, kArchPPC, 81, "Mathematica 4.2", "A later release of Wolfram Research's symbolic and numeric computation environment for Mac OS.", "/apps/Wolfram_Mathematica_4.2.zip", 752458071 },
    { kCatDevTools, 1996, kArchFat, 70, "Mathematica for Students 3.0", "The discounted student edition of Wolfram Research's Mathematica computation environment for classic Mac OS.", "/apps/Mathematica_for_Students_3.0.img_.sit", 43928009 },
    /* -- Productivity -- */
    { kCatProductivity, 0, kArchPPC, 75, "MathMagic 1.1", "An equation and mathematical formula editor for word processing and DTP documents.", "/apps/MathMagic_XT_1.1.zip", 3101738 },
    { kCatProductivity, 1990, kArch68k, 60, "MathType 2.11", "Design Science's equation editor for creating mathematical notation in documents on classic Mac OS.", "/apps/MathType_2.11.sit__0.hqx", 494473 },
    { kCatProductivity, 1994, kArch68k, 60, "MathType 3.5", "Design Science's equation editor for creating mathematical notation in documents on classic Mac OS.", "/apps/MathType_3.5.image_.sit", 1023139 },
    { kCatProductivity, 1996, kArchFat, 70, "MathType 3.6", "Equation editor for creating mathematical notation in documents.", "/apps/MathType_3.6.sit", 2432200 },
    { kCatProductivity, 2007, kArchPPC, 86, "MathType 6.7a", "Design Science's equation editor for creating mathematical notation in documents on Mac OS.", "/apps/MathTypeMac67a_Installer.dmg", 13446014 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 40, "MATLAB 2.0.2", "Early Macintosh release of the MATLAB numerical computing environment.", "/apps/Matlab_2.0.2.sea_.hqx", 12667145 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "MATLAB 4.2c.1", "MathWorks' numerical computing and matrix-based programming environment.", "/apps/MATLAB_4.2c.1.sit", 6013543 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 40, "Mavis Beacon Teaches Typing 2.01", "The Software Toolworks' widely used touch-typing tutor.", "/games/Mavis_Beacon_201_Installer.sit", 1504448 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "Mavis Beacon Teaches Typing 5", "The Software Toolworks' popular touch-typing tutorial software.", "/apps/Mavis_Beacon_5.sit", 31384465 },
    { kCatProductivity, 2003, kArchPPC, 86, "Mavis Beacon Teaches Typing 9", "A later release of the long-running Mavis Beacon touch-typing tutorial software.", "/apps/Mavis_Beacon9.sit", 309432426 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "Mavis Beacon Teaches Typing for Kids", "Kid-focused edition of the popular touch-typing tutor Mavis Beacon.", "/apps/Mavis-Beacon-for-Kids.zip", 78362648 },
    { kCatGames, 1987, kArch68k, 40, "Mean 18", "Accolade's realistic golf course design and simulation game for classic Mac OS.", "/games/mean18.sit", 4449168 },
    { kCatGames, 1996, kArch68k, 70, "MechWarrior 2", "Activision's 3D mech combat simulation game, ported to classic Mac OS.", "/games/MechWarrior2_v1.2_NetMech.sit", 16886145 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Media Cleaner Pro", "Terran Interactive's QuickTime video compression and optimization application.", "/apps/Media_Cleaner_Pro.img_.sit", 471766392 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "Meeting Maker", "Networked group scheduling and calendaring software.", "/apps/Meeting_Maker_1.5.sit", 512616 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 60, "Menu Clock", "Simple menu bar clock extension.", "/apps/MenuClockv.3.0.sit", 1128 },
    { kCatSystemExt, 1993, kArch68k, 70, "MenuChoice 1.2", "Adds a searchable menu of open applications.", "/apps/MenuChoice1.6.sit", 17351 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArchPPC, 75, "MetaCard 2.3", "Cross-platform HyperCard-like rapid application development environment.", "/apps/MetaCard_2.3.zip", 10136739 },
    { kCatDevTools, 1999, kArchPPC, 75, "MetaCard 2.4.3", "A HyperCard-like rapid application development and scripting environment.", "/apps/MetaCard_2.4.3.zip", 30688441 },
    { kCatDevTools, 1998, kArchFat, 70, "MetaCard 2.5", "A cross-platform HyperCard-like rapid application development environment, later acquired to become the", "/apps/MetaCard_2.5.zip", 29075739 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 75, "MetaSynth 2.0", "U&I Software's image-based additive audio synthesis application.", "/apps/MetaSynth_2.0_f.sit", 1372377 },
    { kCatGraphicsSound, 2001, kArchPPC, 84, "MetaSynth 2.6.1", "Experimental sound synthesis and image-to-audio composition software from U&I Software.", "/apps/MetaSynth_2.6.1SN.sit", 763573 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 80, "MetroNub", "Debugging extension companion to CodeWarrior.", "/apps/CW_Pro_5.3_MetroNub.sit", 103066 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 40, "MicroLeague Baseball II", "Statistically driven baseball management and simulation game.", "/games/microleaguebaseball2.zip", 12658268 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1986, kArch68k, 10, "MicronEye 1.1", "Driver and capture software for the Micron MicronEye, one of the earliest digital cameras sold with", "/apps/MicronEye_1.1.sit", 86152 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1989, kArch68k, 10, "MicroPhone", "Scriptable commercial terminal and communications software.", "/apps/MicroPhone.sit", 129652 },
    { kCatInternet, 1988, kArch68k, 30, "MicroPhone 1.1", "Software Ventures' popular Mac telecommunications and terminal emulation program.", "/apps/MicroPhone1.1DiskImages.hqx", 582723 },
    { kCatInternet, 1988, kArch68k, 40, "MicroPhone 1.5", "Software Ventures' full-featured telecommunications and terminal software.", "/apps/MicroPhone_1.5.hqx", 313250 },
    { kCatInternet, 1988, kArch68k, 40, "MicroPhone 1.7", "Software Ventures' widely used telecommunications and terminal emulation software for classic Mac OS.", "/apps/MicroPhone_1.7.hqx", 373047 },
    { kCatInternet, 1991, kArch68k, 60, "MicroPhone LT 1.0", "Software Ventures' entry-level telecommunications and terminal emulation software.", "/apps/MicroPhoneLT1.0.sit", 614252 },
    { kCatInternet, 1994, kArch68k, 60, "MicroPhone LT 1.0.1", "Telecommunications and terminal emulation software from Software Ventures.", "/apps/MicroPhone_LT_1.0.1.hqx", 858629 },
    { kCatInternet, 1994, kArch68k, 60, "MicroPhone LT 2.0.2", "Telecommunications software from Software Ventures for modem and terminal sessions.", "/apps/MicroPhone_LT_2.0.2.hqx", 1495548 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1985, kArch68k, 20, "Microsoft BASIC v3", "Early Microsoft BASIC interpreter and compiler for the Macintosh.", "/apps/MS-BASIC-v3.sit", 867851 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArchFat, 70, "Microsoft Bookshelf 95", "CD-ROM reference suite bundling a dictionary, encyclopedia, atlas and almanac.", "/apps/Microsoft_Bookshelf_95.sit", 409492151 },
    { kCatProductivity, 1994, kArch68k, 60, "Microsoft Cinemania '95", "Multimedia movie reference and review encyclopedia CD-ROM from Microsoft.", "/apps/Cinemania95_Mac.iso", 580958208 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "Microsoft Creative Writer", "Microsoft's illustrated creative writing tool for children, part of Microsoft Home, for classic Mac OS.", "/apps/Microsoft_Home_Creative_Writer.SIT", 3942284 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "Microsoft Encarta 1994", "Multimedia encyclopedia CD-ROM from Microsoft for the classic Mac OS.", "/apps/Encarta_1994.sit", 524510223 },
    { kCatProductivity, 1996, kArchPPC, 75, "Microsoft Encarta 97", "Microsoft's multimedia encyclopedia on CD-ROM.", "/apps/Encarta97_Disc1of2.zip", 526833390 },
    { kCatProductivity, 1997, kArchFat, 75, "Microsoft Encarta 98", "Multimedia encyclopedia CD-ROM from Microsoft.", "/apps/Encarta-98-Disc-1-toast.zip", 539038303 },
    { kCatProductivity, 1985, kArch68k, 0, "Microsoft Excel 1.01 (French)", "Excel launched on the Mac two years before Windows had a version.", "/apps/Microsoft_Excel_1.01F.sit", 306958 },
    { kCatProductivity, 1986, kArch68k, 30, "Microsoft Excel 1.4", "One of the earliest Mac versions of Microsoft's spreadsheet, predating the Windows release.", "/apps/ms-excel-early-1-4.sit", 7444395 },
    { kCatProductivity, 1987, kArch68k, 20, "Microsoft Excel 1.5 (German)", "A very early release of Microsoft Excel for the Macintosh, localized for German.", "/apps/Excel1.5_DE.sit_.hqx", 587079 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft Excel 4.0", "Added AutoFill, workbooks, and toolbar customization.", "/apps/Excel_4.0.sit", 4830440 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft Excel 4.0 (Spanish)", "Spanish-language release of Microsoft Excel 4.0 spreadsheet software.", "/apps/Excel_4.0_ES.sit", 1621805 },
    { kCatProductivity, 1993, kArch68k, 0, "Microsoft Excel 5.0", "Introduced Visual Basic for Applications macros.", "/apps/Excel_5.0_English.sit", 17179026 },
    { kCatProductivity, 1993, kArchFat, 70, "Microsoft Excel 5.0 (Spanish)", "Microsoft's classic spreadsheet application; this is the Spanish-localized release.", "/apps/Excel_5.0_ES_0.sit", 18271076 },
    { kCatProductivity, 1994, kArchFat, 70, "Microsoft Excel 5.0a (Norwegian)", "Norwegian-language release of Microsoft Excel 5.0a spreadsheet software.", "/apps/Excel5.0A-Norwegian.sit", 17169409 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 40, "Microsoft Flight Simulator 4.0", "Microsoft's early civil aviation flight simulation software.", "/games/MSFlightSimulator_4.0a.sit", 1260169 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArchFat, 70, "Microsoft Internet Explorer 3", "Early Mac release of Microsoft's web browser.", "/apps/Internet_Explorer_3.01.sit", 9263303 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 10, "Microsoft Multiplan 1.11", "Early Microsoft spreadsheet program for the Macintosh, a predecessor to Excel.", "/apps/MS_MULTIPLAN_1.11.image_.sit", 138247 },
    { kCatProductivity, 2001, kArchPPC, 86, "Microsoft Office 2001 9.0.4 Update", "Microsoft's official updater bringing Office 2001 for Mac (Word, Excel, PowerPoint, Entourage) to version", "/apps/Office2001-9.0.4UpdateEN.zip", 27722496 },
    { kCatProductivity, 1994, kArch68k, 70, "Microsoft Office 4.2", "Microsoft's classic Office suite bundling Word, Excel, and PowerPoint for Mac.", "/apps/Microsoft_Office_4.2_floppy.sit", 42562762 },
    { kCatProductivity, 1994, kArch68k, 70, "Microsoft Office 4.2.1 (Dutch)", "Microsoft Office for classic Mac OS, localized for Dutch.", "/apps/Microsoft_Office_4.2.1_NL_CD.zip", 46447403 },
    { kCatProductivity, 1994, kArch68k, 70, "Microsoft Office 4.2.1a", "An update to Microsoft Office for Mac 4.2, bundling Word, Excel, and PowerPoint for classic Mac OS.", "/apps/Office421a_En.sit", 61587110 },
    { kCatProductivity, 1994, kArch68k, 70, "Microsoft Office 4.2.1a (German)", "Microsoft Office for classic Mac OS, localized for German.", "/apps/Office4.2.1A-German.sit", 51690648 },
    { kCatProductivity, 1998, kArchFat, 75, "Microsoft Office 98", "Office suite for Macintosh bundling Word, Excel, PowerPoint and Outlook Express.", "/apps/Microsoft_Office_98.sit", 39056825 },
    { kCatProductivity, 1998, kArchPPC, 70, "Microsoft Office 98 (5-Language Update)", "Microsoft's official multilingual updater for Office 98 Macintosh Edition.", "/apps/off98_5lang_update.sit", 16657686 },
    { kCatProductivity, 1998, kArchPPC, 70, "Microsoft Office 98 (Italian)", "Microsoft's Office 98 Macintosh Edition suite, localized for Italian.", "/apps/Office_98_ITA_1998.sit", 331226845 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArch68k, 70, "Microsoft OLE 2.05 SDK", "Software development kit for implementing Microsoft's Object Linking and Embedding on the Mac.", "/apps/Microsoft_OLE_2.05_SDK.sit", 11936839 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 0, "Microsoft PowerPoint 2.0", "An early release of the presentation software, before Microsoft acquired it fully into Office.", "/apps/PowerPoint_2.0.zip", 884797 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft PowerPoint 2.01", "Microsoft's presentation graphics application for classic Mac OS.", "/apps/PowerPoint_2.01D_English.sit", 1903019 },
    { kCatProductivity, 1993, kArch68k, 60, "Microsoft Project 3", "Project management software for scheduling tasks and tracking Gantt charts.", "/apps/MS_Project_3.sit", 1766609 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1988, kArch68k, 30, "Microsoft QuickBASIC 1.0", "BASIC programming language compiler for the classic Mac OS.", "/apps/MS_QuickBasic_1.0.sit", 790028 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Microsoft TrueType Font Sampler", "A free collection of sample TrueType fonts distributed by Microsoft for classic Mac OS.", "/apps/MSTrueTypeSampler.image_.sit", 706749 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 0, "Microsoft Word 1.0", "The first Mac release of Word, a launch title for the original Macintosh era.", "/apps/Microsoft_Word1.0F.image_.sit", 238874 },
    { kCatProductivity, 1985, kArch68k, 10, "Microsoft Word 1.00", "The original 1985 release of Microsoft Word for the Macintosh, Microsoft's first Mac application.", "/apps/Microsoft_Word_1.00.image_.zip", 234099 },
    { kCatProductivity, 1986, kArch68k, 60, "Microsoft Word 1.05", "An early Mac release of Word, before the 4.0/5.x era most remember.", "/apps/Microsoft_Word_1.05.zip", 5152089 },
    { kCatProductivity, 1987, kArch68k, 60, "Microsoft Word 3.0", "A significant early rewrite, notoriously buggy at launch.", "/apps/Microsoft_Word_3.0.bin", 32896 },
    { kCatProductivity, 1989, kArch68k, 60, "Microsoft Word 4.0", "A stable, widely-used release through the late 80s.", "/apps/MS_Word_4.0.sit", 1150101 },
    { kCatProductivity, 1991, kArch68k, 60, "Microsoft Word 5.0", "Widely regarded as one of the best classic Mac word processors.", "/apps/Word_5.0.sit", 3739421 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft Word 5.1", "A refinement of the well-regarded 5.0 release.\rRequires 1MB RAM (2MB for grammar check)", "/apps/Word_5.1_EN-US.sit", 4223974 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft Word 5.1 (German)", "German-language release of Microsoft Word 5.1, a long-lived classic Mac word processor.", "/apps/D-Word_5.1.sit", 3673030 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft Word 5.1 (Swedish)", "Microsoft's widely used word processor for classic Mac OS, this release localized for Swedish.", "/apps/Microsoft_Word_5.1_sv.sit", 4651246 },
    { kCatProductivity, 1992, kArch68k, 60, "Microsoft Word 5.1a", "Microsoft's classic word processor, the last version before Word 6.0's interface overhaul.", "/apps/Ms-Word-51a-AUS.sit", 5125147 },
    { kCatProductivity, 1994, kArchFat, 70, "Microsoft Word 6 (German)", "Microsoft's widely used word processor for classic Mac OS, localized for German.", "/apps/W6-DE-68k-PPC.sit", 41565668 },
    { kCatProductivity, 1994, kArchFat, 70, "Microsoft Word 6.0", "Shared a rewrite with Windows Word - slower and heavier than 5.1.\rRequires 68030, 4MB RAM (8MB recommended)", "/apps/Word6.sit", 17803034 },
    { kCatProductivity, 1994, kArchFat, 70, "Microsoft Word 6.0.1 (German)", "German-language release of Microsoft Word 6.0.1 for the classic Mac OS.", "/apps/Word6.0.1-german.sit", 20963464 },
    { kCatProductivity, 1994, kArch68k, 70, "Microsoft Word 6.0.1 (Norwegian)", "Microsoft's widely used word processor for classic Mac OS, this release localized for Norwegian.", "/apps/Word6.0.1-Norwegian.sit", 19906412 },
    { kCatProductivity, 1998, kArchPPC, 75, "Microsoft Word 98", "Microsoft's word processor bundled as part of Office 98 Macintosh Edition.", "/apps/Word_98_Special_Edition.cdr_.zip", 258348987 },
    { kCatProductivity, 1998, kArchPPC, 70, "Microsoft Word 98 (French)", "Microsoft's word processor from the Office 98 Macintosh Edition suite, localized for French.", "/apps/Word98_French.sit", 277136590 },
    { kCatProductivity, 1998, kArchPPC, 70, "Microsoft Word 98 (Swedish)", "Microsoft's word processor from the Office 98 Macintosh Edition suite, localized for Swedish.", "/apps/Microsoft_Word_98-SV.iso", 508094464 },
    { kCatProductivity, 1986, kArch68k, 30, "Microsoft Works 1.0", "Microsoft's early all-in-one word processor, spreadsheet, and database suite.", "/apps/MicrosoftWorks_1.0.sit", 372184 },
    { kCatProductivity, 1987, kArch68k, 30, "Microsoft Works 1.1", "Early version of Microsoft's integrated office suite for Macintosh.", "/apps/Microsoft_Works_1.1.sit", 1012014 },
    { kCatProductivity, 1988, kArch68k, 40, "Microsoft Works 2.0", "Integrated word processor, spreadsheet, and database application for the classic Mac OS.", "/apps/Microsoft_Works_v2.img_.sit", 466887 },
    { kCatProductivity, 1988, kArch68k, 40, "Microsoft Works 2.00", "Integrated word processor, spreadsheet, and database suite from Microsoft.", "/apps/microsoftworks2.00b.sit", 311569 },
    { kCatProductivity, 1996, kArchFat, 70, "Microsoft Works 4.0", "Microsoft's integrated word processor, spreadsheet, and database application.", "/apps/ms-works-4b-us.sit", 8326094 },
    { kCatProductivity, 1995, kArchFat, 70, "Microsoft Works 4.0 (German)", "Microsoft's integrated word processor, spreadsheet, and database suite for classic Mac OS, localized for", "/apps/Works4.0B-German.sit", 12021155 },
    { kCatProductivity, 1995, kArchFat, 70, "Microsoft Works 4.0b", "Microsoft's integrated word processor, spreadsheet, and database suite for classic Mac OS.", "/apps/MSWORKS4.0b.sit", 7219804 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 70, "MidiGraphy 1.4.2", "Music notation and MIDI sequencing software.", "/apps/MIDIGraphy_1.4.2.sit", 685016 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 0, "Might and Magic Book One", "New World Computing's first-person fantasy role-playing game, Secret of the Inner Sanctum.", "/games/Might_and_Magic_I.sit", 4910197 },
    { kCatGames, 1991, kArch68k, 40, "Might and Magic II", "New World Computing's classic first-person fantasy role-playing game, ported to classic Mac OS.", "/games/Might_and_Magic_II_0.sit", 2681946 },
    { kCatGames, 1996, kArch68k, 60, "Mighty Math Number Heroes", "Edmark's educational math game for classic Mac OS aimed at upper elementary students.", "/games/MightyMathsNmbrHrs.iso_.sit", 147541987 },
    /* -- Productivity -- */
    { kCatProductivity, 1987, kArch68k, 30, "MindWrite 2.1.7", "Outlining word processor for the classic Mac OS from Aegis Development.", "/apps/mindwrite_2_17.zip", 6647071 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 0, "Mini-Zork I", "A condensed release of Infocom's classic Zork text adventure.", "/games/Mini-Zork_r34-1987.sit", 182788 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 20, "MiniCad 1.0", "Diehl Graphsoft's affordable CAD and drafting application, precursor to Vectorworks.", "/apps/MiniCad_1.0.sit_.hqx", 1949561 },
    { kCatProductivity, 1994, kArch68k, 70, "MiniCad 6.04", "Updater for the MiniCad 2D/3D CAD application, predecessor to VectorWorks.", "/apps/minicad_6.0_to_6.04_up_.sit_.hqx", 1141154 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchFat, 70, "MiniCad 7", "Diehl Graphsoft's 2D/3D CAD and drafting application for classic Mac OS, later renamed VectorWorks.", "/apps/minicad7.sit", 21571441 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArchFat, 70, "Minitab 10.51", "Minitab Inc's statistical analysis software.", "/apps/Minitab_10.51_Xtra_FAT.sit", 12234999 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 0, "Missile Command", "Defend your cities in this arcade shoot-em-up port.", "/games/MissileCommand.img_.sit", 7120 },
    { kCatGames, 1990, kArch68k, 0, "Mixed-Up Mother Goose", "Nursery-rhyme themed children's adventure game.", "/games/mixed_up_mother_goose.sit", 426039 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArch68k, 70, "Monica 3.0 PB1", "A classic Mac OS IRC (Internet Relay Chat) client used for real-time text chat rooms.", "/apps/Monica_3_0PB1.sit", 1288800 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 60, "Monkey Island 2: LeChuck's Revenge", "LucasArts' pirate-themed point-and-click adventure, sequel to The Secret of Monkey Island.", "/games/monkeyisland2.zip", 17826596 },
    { kCatGames, 1995, kArchFat, 70, "Monopoly", "MacSoft's computerized version of the classic Hasbro board game.", "/games/MonopolyMacsoft.toast_.sit", 291237574 },
    { kCatGames, 1998, kArchPPC, 75, "Monopoly (Here & Now Edition)", "Computer adaptation of the classic Monopoly board game.", "/games/Monopoly_Here_Now_-_PPC.zip", 18128104 },
    { kCatGames, 1995, kArchFat, 70, "Monopoly (MacPlay)", "Computer adaptation of the classic Parker Brothers real-estate board game.", "/games/MonopolyMacPlay.img_.sit", 1857867 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArch68k, 60, "Mops 4.0.1", "An object-oriented Forth programming language implementation for classic Mac OS, used widely in education.", "/apps/Mops401.sit_.bin", 3925376 },
    { kCatDevTools, 0, kArch68k, 60, "Mops 5.41", "An object-oriented Forth programming language implementation for Mac OS.", "/apps/Mops541.sit_.bin", 3178880 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 0, "More", "Symantec's classic outlining and presentation tool.", "/apps/MORE.sit", 251324 },
    { kCatProductivity, 1987, kArch68k, 60, "MORE 1.0", "Living Videotext's outline processor, a landmark presentation/idea tool.", "/apps/MORE_1.0_.sit", 201978 },
    { kCatProductivity, 1987, kArch68k, 60, "MORE 1.1", "A refinement of the original outline processor.", "/apps/MORE_1.1.hqx", 798724 },
    { kCatProductivity, 1990, kArch68k, 60, "MORE 3.0", "Under Symantec after their acquisition of Living Videotext.\rRequires 1MB RAM", "/apps/more_3.0.sit", 1303624 },
    { kCatProductivity, 1991, kArch68k, 60, "MORE 3.1", "The final release of the MORE outline processor line.\rRequires 1MB RAM", "/apps/More_3.1.cpt", 1848618 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "More After Dark", "Official expansion pack of additional screensaver modules for After Dark.", "/apps/After_Dark_-_More_After_Dark.sit", 613900 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Moria", "Classic roguelike dungeon-crawl RPG.", "/games/Moria.SIT", 267113 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "Morph 2.5", "Gryphon Software's pioneering image morphing and warping application for classic Mac OS.", "/apps/morph_2_5.zip", 3826556 },
    { kCatGraphicsSound, 1989, kArch68k, 40, "MOTU Performer 1.22", "MIDI sequencing software from Mark of the Unicorn.", "/apps/Performer_1.22.sit_.hqx", 138018 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "MOTU Performer 5.0.2", "MIDI and digital audio sequencing software update from Mark of the Unicorn.", "/apps/Performertm_5.0.2.sit", 3584232 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "MOTU Performer 5.05", "An earlier version of Mark of the Unicorn's professional MIDI sequencing software for classic Mac OS.", "/apps/MOTU_Performer_505.zip", 4641290 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 10, "MountImage", "Extension for automatically mounting disk images at startup.", "/apps/mountimage-11b3.sit", 10214 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArch68k, 70, "MovieDiet 0.31", "A shareware utility for shrinking and recompressing QuickTime movie files.", "/apps/MovieDiet031.hqx", 71373 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "MovieWorks 2.0", "A classic Mac OS multimedia authoring tool for combining video, audio, animation, and text, popular in", "/apps/MovieWorks20.hqx", 5981166 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "MovieWorks Player 4.0.3", "Playback application for multimedia presentations authored in MovieWorks.", "/apps/MovieWorks_Player_4.0.3.sit", 564796 },
    /* -- Internet & Comm -- */
    { kCatInternet, 2000, kArchPPC, 81, "MP3 Rage 3.93", "Utility for searching and downloading MP3 files from early internet file-sharing networks.", "/apps/MP3_Rage_3.93_Carbon.hqx", 3572193 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 40, "MPW 3.0/3.1", "An early release of Apple's Macintosh Programmer's Workshop command-line development environment for classic", "/apps/mpw_3.0_3.1.sea_.bin", 6345344 },
    { kCatDevTools, 1994, kArchFat, 60, "MPW 3.5", "Apple's Macintosh Programmer's Workshop, free from Apple.", "/apps/mpw3-cdrom.zip", 5831362 },
    { kCatDevTools, 1991, kArch68k, 60, "MPW Oberon 2.1106", "Oberon language compiler and tools for Apple's Macintosh Programmer's Workshop.", "/apps/MPW_Oberon_2.1106.sit", 1135844 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArchFat, 70, "MT-NewsWatcher 2.2.2", "Popular fork of NewsWatcher adding MIME and multi-threaded article support.", "/apps/MT-NewsWatcher_2.2.2_.sit", 661812 },
    { kCatInternet, 1996, kArch68k, 70, "MT-NewsWatcher 2.3.5", "An earlier version of the popular Usenet newsreader for classic Mac OS.", "/apps/MT-NewsWatcher_2.3.5_Inst.bin", 872064 },
    { kCatInternet, 1997, kArch68k, 70, "MT-NewsWatcher 3.1", "A mid-series release of the popular Usenet newsreader for classic Mac OS.", "/apps/MT-NewsWatcher31_0.sit", 1407543 },
    { kCatInternet, 1998, kArchFat, 70, "MT-NewsWatcher 3.3b1", "A well-known freeware Usenet newsreader for classic Mac OS, continuing the NewsWatcher/YA-NewsWatcher", "/apps/MT-NewsWatcher33b1.sit", 1347410 },
    { kCatInternet, 1998, kArch68k, 75, "MT-NewsWatcher 3.4", "Multi-threaded fork of the NewsWatcher Usenet newsgroup reader.", "/apps/MT-NewsWatcher34.sit", 1417765 },
    { kCatInternet, 2000, kArchFat, 70, "Mulberry 2.1", "A well-known standards-based IMAP email client for Mac OS.", "/apps/Mulberry-v2.1-install-set.sit", 16281388 },
    { kCatInternet, 1999, kArchPPC, 75, "Mulberry 3.16", "IMAP-focused email client aimed at power users and enterprise mail servers.", "/apps/Mulberry-mail-v316.bin", 10672640 },
    { kCatInternet, 2002, kArchPPC, 85, "Mulberry 4.0.5", "Cyrusoft's standards-based IMAP email client.", "/apps/Mulberry-mail-405.dmg", 13735155 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "MusicShop 2.0.1", "Opcode's entry-level MIDI sequencing software for home musicians.", "/apps/Musicshop-201.sit", 5482251 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "MYOB", "Mind Your Own Business's small-business accounting and bookkeeping software for classic Mac OS.", "/apps/MYOB.sit", 834344 },
    /* -- Featured -- */
    { kCatFeatured, 1993, kArch68k, 70, "Myst", "Cyan's landmark surreal exploration adventure game.", "/games/MYSTy_1.0.sit", 3292147 },
    /* -- Games -- */
    { kCatGames, 1993, kArchFat, 70, "Myst (Preview)", "Preview release of Cyan's landmark point-and-click puzzle adventure game.", "/games/Myst_preview.sit", 30766944 },
    { kCatGames, 2001, kArchPPC, 85, "Myst III: Exile", "Third installment of the Myst adventure game series.", "/games/Myst_III_Installer.zip", 12130658 },
    { kCatGames, 2000, kArchPPC, 75, "Myst: Masterpiece Edition", "Cyan's remastered edition of the landmark puzzle-adventure game Myst.", "/games/myst-masterpiece-iso.zip", 510268838 },
    { kCatGames, 1998, kArchPPC, 75, "Myth II: Soulblighter", "Bungie's tactical real-time strategy game set in a dark fantasy world.", "/games/Myth2_160_Mac.sit", 17331731 },
    { kCatGames, 1998, kArchPPC, 75, "Myth II: Soulblighter (1.4.3)", "Bungie's real-time tactics game with squad-based combat and physics-driven battles.", "/games/MythIISoulblighterMacinv143_0.sit", 14994165 },
    { kCatGames, 1998, kArchPPC, 75, "Myth II: Soulblighter 1.3", "Real-time tactical battle game with physics-based combat, sequel to Myth: The Fallen Lords.", "/games/Myth_II_1.3.sit", 408553909 },
    { kCatGames, 1997, kArchPPC, 75, "Myth: The Fallen Lords", "Bungie's original dark-fantasy real-time tactics game.", "/games/MythArchive.sit_.bin", 314566144 },
    { kCatGames, 1998, kArchPPC, 75, "Nanosaur", "Pangea Software's dinosaur-piloted action game bundled with early iMacs.", "/games/nanosaur-1x.sit", 26326658 },
    { kCatGames, 2004, kArchPPC, 90, "Nanosaur II", "Dinosaur-themed 3D action game from Pangea Software.", "/games/Nanosaur_II_2.1.0.dmg", 109285112 },
    /* -- Internet & Comm -- */
    { kCatInternet, 2000, kArchPPC, 80, "Napster 1.0", "Peer-to-peer music file sharing client for Macintosh.", "/apps/Napster_1.0.sit", 793948 },
    { kCatInternet, 1993, kArch68k, 70, "NCSA Mosaic (Alpha 2)", "Early alpha build of NCSA Mosaic for Macintosh, predating its 1.0 release.", "/apps/MosaicA2.sit_.hqx", 492812 },
    { kCatInternet, 1994, kArch68k, 70, "NCSA Mosaic 1.0", "First Macintosh release of NCSA Mosaic, the pioneering graphical web browser.", "/apps/NCSAMosaicMac.10.sit_.hqx", 663696 },
    { kCatInternet, 1994, kArch68k, 60, "NCSA Mosaic 1.0.2", "One of the first graphical web browsers, ported to the classic Mac OS.", "/apps/NCSA_Mosaic_1.0.2.sit", 339995 },
    { kCatInternet, 1993, kArch68k, 60, "NCSA Mosaic 1.0.3", "Early graphical web browser developed at NCSA that popularized the World Wide Web.", "/apps/NCSAMosaic103.hqx", 463486 },
    { kCatInternet, 1994, kArch68k, 60, "NCSA Mosaic 2.0.0a6", "Early alpha release of one of the first graphical web browsers, Macintosh port.", "/apps/NCSA_Mosaic_2.0.0a6.hqx", 657162 },
    { kCatInternet, 1994, kArchFat, 60, "NCSA Mosaic 2.0.0B5", "An early beta of NCSA Mosaic, the first widely used graphical web browser, for classic Mac OS.", "/apps/NCSAMosaic2.0.0B5FAT.sit_.bin", 1582464 },
    { kCatInternet, 1994, kArch68k, 60, "NCSA Mosaic 2.0.0B9", "A later beta of NCSA Mosaic, the pioneering graphical web browser, for classic Mac OS.", "/apps/NCSAMosaic200B9.68K.hqx", 1220797 },
    { kCatInternet, 1995, kArch68k, 70, "NCSA Mosaic 2.0.1", "University of Illinois' NCSA Mosaic, one of the earliest graphical web browsers.", "/apps/NCSAMosaic201.68K.hqx", 1112990 },
    { kCatInternet, 1995, kArch68k, 70, "NCSA Mosaic 2.0b7", "A version of NCSA Mosaic, the first widely used graphical web browser, for classic Mac OS.", "/apps/NCSAmosaic200b7.sit", 1714188 },
    { kCatInternet, 1995, kArch68k, 60, "NCSA Mosaic 3.0 (Beta 4)", "Later beta release of the pioneering NCSA Mosaic web browser for Macintosh.", "/apps/NCSAMosaic30b4.hqx", 2135438 },
    { kCatInternet, 1995, kArch68k, 70, "NCSA Mosaic 3.0b2", "A beta release of the pioneering NCSA Mosaic graphical web browser.", "/apps/NCSAMosaic30b2.hqx", 2007641 },
    { kCatInternet, 1995, kArch68k, 60, "NCSA Mosaic 3.0b3", "Later beta release of one of the first graphical web browsers, Macintosh port.", "/apps/NCSAMosaic30b3.hqx", 2044707 },
    { kCatInternet, 1996, kArch68k, 60, "NCSA Mosaic 3.0b4", "A later beta of NCSA Mosaic, the pioneering graphical web browser, for classic Mac OS.", "/apps/NCSAMosaic30b4xSym.hqx", 3047638 },
    { kCatInternet, 1993, kArch68k, 60, "NCSA Telnet 2.3", "NCSA's free terminal emulation and telnet client, a Macintosh internet-era staple.", "/apps/telnet23sf.sit", 186368 },
    { kCatInternet, 1994, kArch68k, 60, "NCSA Telnet 2.6", "Classic freeware Telnet client from NCSA.", "/apps/ncsa-telnet-27b4.hqx", 345095 },
    { kCatInternet, 1995, kArch68k, 0, "NetCloak", "Web server plug-in for dynamic HTML content.", "/apps/NetCloak_2.1.2_free_copy.sit", 637393 },
    { kCatInternet, 1994, kArch68k, 60, "NetDoubler", "Vicomsoft's software for sharing a single internet or network connection across multiple classic Macs and", "/apps/netdoubler_macpc.sit", 3147348 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 40, "NetHack 2.3e", "An early Mac port of NetHack, the deep and enduring open-source roguelike dungeon-crawling game.", "/games/NetHack_2.3e.cpt", 213466 },
    { kCatGames, 1993, kArch68k, 60, "NetHack 3.0", "A free, open-source roguelike dungeon exploration game.", "/games/NetHack_3.0iR10.sit", 402665 },
    { kCatGames, 1996, kArch68k, 60, "NetHack 3.1.2", "A classic Mac OS port of NetHack, the deep and enduring open-source roguelike dungeon-crawling game.", "/games/NetHack_3.1.2.sit", 801945 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "NetPresenz", "Turns a Mac into an FTP and Gopher server.", "/apps/NetPresenz_4.1.sit", 744727 },
    { kCatInternet, 1996, kArchFat, 70, "NetPresenz 4.1 (French)", "Peter Lewis's combined FTP, Gopher, and web server for classic Mac OS.", "/apps/netpresenz-41-french.zip", 772584 },
    { kCatInternet, 1998, kArch68k, 75, "Netscape Communicator 4.05 (Polish)", "Netscape's integrated browser and email/news suite; Polish-language release.", "/apps/Netscape_4.05_PL.sit", 9119459 },
    { kCatInternet, 1998, kArchPPC, 75, "Netscape Communicator 4.6", "Netscape's browser suite bundling Navigator, Messenger email, and Composer.", "/apps/Communicatortm_4.6_Complete.sit", 13470822 },
    { kCatInternet, 1994, kArch68k, 60, "Netscape Navigator 0.93", "Pre-1.0 beta release of the Netscape Navigator web browser for Macintosh.", "/apps/Netscape-093b.sit_.bin", 501632 },
    { kCatInternet, 1994, kArch68k, 60, "Netscape Navigator 0.96", "An extremely early public beta of Netscape Navigator for Macintosh, from before the web browser's 1.0", "/apps/netscape096_sea.hqx", 687435 },
    { kCatInternet, 1994, kArch68k, 60, "Netscape Navigator 0.9b", "Pre-release beta build of the Netscape Navigator web browser.", "/apps/Netscape-096b.sit", 506368 },
    { kCatInternet, 1994, kArch68k, 70, "Netscape Navigator 1.0", "First public release of the Netscape Navigator web browser.", "/apps/Navigator_1_0.hqx", 624407 },
    { kCatInternet, 1994, kArch68k, 60, "Netscape Navigator 1.0N", "The original 1.0 release of Netscape Navigator, the web browser that popularized the World Wide Web.", "/apps/Netscape_1.0N.zip", 429921 },
    { kCatInternet, 1994, kArch68k, 60, "Netscape Navigator 1.12", "Early release of the Netscape Navigator web browser for the classic Mac OS.", "/apps/Netscape_1.12_Installer.sit", 1059104 },
    { kCatInternet, 1995, kArch68k, 70, "Netscape Navigator 1.61", "Early release of Netscape Navigator, the web browser that popularized the World Wide Web.", "/apps/NetScrape161.dmg", 801626 },
    { kCatInternet, 1995, kArch68k, 70, "Netscape Navigator 2.0", "Web browser release adding JavaScript, frames and email support.", "/apps/Netscape2.0.hqx", 1996352 },
    { kCatInternet, 1995, kArch68k, 70, "Netscape Navigator 2.0 (Beta 3)", "Beta release of Netscape Navigator 2.0, one of the earliest widely used graphical web browsers.", "/apps/netscape-2.0b3.hqx", 2860303 },
    /* -- Featured -- */
    { kCatFeatured, 1996, kArchFat, 70, "Netscape Navigator 2.02", "The web browser that defined the mid-90s internet.", "/apps/netscape-2.02-de.hqx", 2894598 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 70, "Netscape Navigator 2.0b2", "A beta release of Netscape's pioneering web browser.", "/apps/netscape-2.0b2.hqx", 2593256 },
    { kCatInternet, 1996, kArchFat, 70, "Netscape Navigator 3.0", "Netscape's widely used web browser during the mid-1990s browser wars.", "/apps/netscape3standard.sit", 3771822 },
    { kCatInternet, 1996, kArchFat, 70, "Netscape Navigator 3.01", "Web browser update with improved plug-in and Java support.", "/apps/netscape-navigator301.sit", 4658190 },
    { kCatInternet, 1996, kArchFat, 70, "Netscape Navigator 3.02", "Web browser release adding frames, plug-ins, and Java applet support.", "/apps/netscape3.02_EX.hqx", 5122159 },
    { kCatInternet, 1997, kArchFat, 70, "Netscape Navigator 3.03", "Netscape's web browser, version 3.03, for the classic Mac OS.", "/apps/netscape3.03.hqx", 5123149 },
    { kCatInternet, 1992, kArch68k, 60, "NetWare for Macintosh", "Novell's client software for connecting classic Mac OS to NetWare file and print servers.", "/apps/NetWare_for_Mac.sit", 342217 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Network DiskFit 1.5.1", "Dantz Development's network-aware automated backup utility for Macintosh.", "/apps/Network_DiskFit_1.5.1.sit_.hqx", 177587 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArchPPC, 70, "NewsWatcher", "Usenet newsgroup reader for the Macintosh.", "/apps/NewsWatcher-X.sit", 287500 },
    { kCatInternet, 1992, kArch68k, 60, "NewsWatcher 1.0.2 (with source)", "Early version of the freeware Usenet news reader, distributed with source code.", "/apps/NewsWatcher-1.0.2-with-src.sit", 860956 },
    { kCatInternet, 1993, kArch68k, 60, "NewsWatcher 1.02", "The original freeware Usenet newsreader for classic Mac OS that YA-NewsWatcher and MT-NewsWatcher were later", "/apps/NewsWatcher_102_with_src.sit", 239023 },
    { kCatInternet, 1994, kArch68k, 60, "NewsWatcher 1.3d6", "Popular freeware Usenet newsgroup reader for classic Macintosh.", "/apps/newswatcher_1.3d6_with_src.sit", 508284 },
    { kCatInternet, 1993, kArch68k, 60, "NewsWatcher 1.3d8", "Freeware Usenet newsgroup reader developed at the University of Michigan.", "/apps/newswatcher1.3d8.sea_.hqx", 233423 },
    { kCatInternet, 1994, kArch68k, 70, "NewsWatcher 2.0", "Freeware Usenet news reader developed at the University of Auckland.", "/apps/newswatcher2.0.sit_.hqx", 898885 },
    { kCatInternet, 1994, kArch68k, 70, "NewsWatcher 2.1", "Freeware Usenet newsgroup reader.", "/apps/NewsWatcher2.1.1.hqx", 889261 },
    { kCatInternet, 1995, kArch68k, 60, "NewsWatcher 2.1.6", "Popular freeware Usenet newsgroup reader for classic Macintosh, version 2.1.6.", "/apps/NewsWatcher_2.1.6.sit", 591874 },
    { kCatInternet, 1995, kArchFat, 70, "NewsWatcher 2.2.2", "A free graphical Usenet newsgroup reader for Mac OS.", "/apps/NewsWatcher_2.2.2.sit", 634974 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "Newton Connection Utility 1.0", "Software for synchronizing data between an Apple Newton PDA and a Macintosh.", "/apps/Newton_Connection_Utility_1.0_1.sit", 3701409 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArch68k, 70, "Newton Toolkit 1.0", "Apple's official development environment, running on classic Mac OS, for building applications for the", "/apps/Newton_Toolkit_Version_1.0.zip", 2738614 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 70, "NiftyTelnet SSH 1.1", "Popular free Telnet/SSH terminal client for classic Macintosh.", "/apps/NiftyTelnet_1.1_SSHr3.sit", 399558 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "NIH Image 1.55", "Free scientific image analysis program from the National Institutes of Health, predecessor to ImageJ.", "/apps/nih-image155.hqx", 887720 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArchFat, 70, "Nisus 4.1.4", "Word processor known for multiple undo, non-contiguous selection and macros.", "/apps/Nisus_4.1.4.sit", 3752739 },
    { kCatProductivity, 1994, kArch68k, 60, "Nisus Compact", "Lightweight edition of the Nisus word processor.", "/apps/nisuscompact.sea_.hqx", 1664811 },
    { kCatProductivity, 1990, kArch68k, 50, "Nisus Writer", "Word processor for the classic Mac OS known for its multiple undo and macro features.", "/apps/Nisus.zip", 969052 },
    { kCatProductivity, 1990, kArch68k, 60, "Nisus Writer 2.03", "Word processor known for unlimited undo, PowerTalk support, and non-contiguous text selection.", "/apps/Nisus203.sit", 1203209 },
    { kCatProductivity, 1993, kArch68k, 70, "Nisus Writer 3.06 (Demo)", "Demo version of the Nisus Writer 3.06 word processor for classic Mac OS.", "/apps/Nisus3.06Demo.sit", 523068 },
    { kCatProductivity, 1994, kArch68k, 60, "Nisus Writer 3.48", "Nisus Software's powerful word processor for classic Mac OS, known for its multiple undo and macro", "/apps/Nisus-3.48-WP.sit", 2774848 },
    { kCatProductivity, 1995, kArch68k, 70, "Nisus Writer 4.16", "Nisus Software's word processor known for multilingual text support and macros.", "/apps/nisus-writer-416.sit", 6272948 },
    { kCatProductivity, 2000, kArchPPC, 75, "Nisus Writer 5.0.4", "Nisus Software's powerful word processor known for multiple undo and non-contiguous text selection.", "/apps/NisusWriter5.0.4.img_.bin", 15098112 },
    { kCatProductivity, 1993, kArch68k, 70, "Nisus Writer Demo", "Word processor known for multilingual and macro support.", "/apps/Nisus_Writer_4.03.sit", 4443476 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 40, "Nobunaga's Ambition", "Koei's historical Japanese feudal strategy game.", "/games/NobunagasAmbition.zip", 26007841 },
    /* -- Utilities -- */
    { kCatUtilities, 2001, kArchPPC, 85, "Norton AntiVirus 10.0", "Virus scanning and removal software from Symantec for Mac OS.", "/apps/Norton_AntiVirus_10.0_CD.toast_.zip", 30124608 },
    { kCatUtilities, 1998, kArchFat, 75, "Norton AntiVirus 6.0", "Symantec's virus scanning and protection utility for classic Macintosh.", "/apps/NortonAntivirus6.0CD.img_.bin", 44138880 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1998, kArchFat, 75, "Norton AntiVirus 7.0", "Symantec's antivirus software for classic Mac OS.", "/apps/norton_antivirus_7.0.sit", 5567788 },
    { kCatSystemExt, 2001, kArchPPC, 85, "Norton AntiVirus 9.0", "Symantec's antivirus suite for Mac OS 9 and early Mac OS X.", "/apps/NortonAntivirus9CD.ZIP", 45281703 },
    { kCatSystemExt, 1994, kArch68k, 60, "Norton DiskLock 3.0", "Symantec's disk and file encryption/access-control utility.", "/apps/norton_disklock_3.0.sit", 671916 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchPPC, 75, "Norton SystemWorks 1.0", "Symantec bundle combining Norton Utilities and Norton AntiVirus.", "/apps/NortonSysW101CD.ZIP", 63346295 },
    { kCatUtilities, 2000, kArchPPC, 80, "Norton SystemWorks 2.0", "Bundled disk utility, antivirus and troubleshooting suite from Symantec.", "/apps/NortonSystemWorks2CD.ZIP", 182210628 },
    { kCatUtilities, 1990, kArch68k, 60, "Norton Utilities 1.1.2", "Symantec's classic Macintosh disk repair and file recovery utility suite.", "/apps/Norton_Utilities_1.1.2.sit", 324663 },
    { kCatUtilities, 1991, kArch68k, 60, "Norton Utilities 2.0", "Symantec's classic Macintosh disk repair and file recovery utility suite, version 2.0.", "/apps/Norton_Utilities_v2.sit", 3532162 },
    { kCatUtilities, 1992, kArch68k, 60, "Norton Utilities 3.1", "Symantec's classic Macintosh disk repair and file recovery utility suite, version 3.1.", "/apps/Norton_3.1.sit", 3665673 },
    { kCatUtilities, 1992, kArch68k, 60, "Norton Utilities 4.0.3", "Earlier release of Symantec's disk-repair and recovery utility suite.", "/apps/NortonUtil403CD.ZIP", 91226461 },
    { kCatUtilities, 1993, kArch68k, 60, "Norton Utilities 4.0.4", "Disk repair, optimization and data recovery utility suite from Symantec.", "/apps/Norton_Utilities_4.0.4.cdr_.sit", 53711380 },
    { kCatUtilities, 1993, kArch68k, 60, "Norton Utilities 6.0", "Symantec's classic disk-repair and system-recovery utility suite.", "/apps/NortonUtilities6CD.ZIP", 38040854 },
    { kCatUtilities, 1996, kArchFat, 70, "Norton Utilities 6.0.5", "Symantec's disk repair and data recovery utility suite for classic Mac OS.", "/apps/Norton_Utilities_v6.0.5.sit_.hqx", 12342552 },
    { kCatUtilities, 1993, kArch68k, 60, "Norton Utilities 7", "Symantec's disk repair, recovery, and optimization utility suite for the classic Mac OS.", "/apps/Nortons-Utilities-v7.zip", 83831405 },
    { kCatUtilities, 1996, kArch68k, 75, "Norton Utilities 7.0", "Symantec's essential disk-repair and data-recovery utility suite.", "/apps/norton_utilities_7_cd.toast_.sit", 111598738 },
    { kCatUtilities, 1999, kArchPPC, 75, "Norton Utilities 9", "Later release of Symantec's disk diagnostic and file recovery utility suite.", "/apps/Norton_Utilities_9.toast_.zip", 87695568 },
    { kCatUtilities, 1994, kArchFat, 70, "Norton Utilities for Macintosh", "Symantec's disk repair and optimization suite.", "/apps/nortonutilities321.sit", 3837770 },
    { kCatUtilities, 1990, kArch68k, 60, "Norton Utilities for Macintosh 1.0", "First Macintosh release of Symantec's Norton Utilities disk-repair suite.", "/apps/norton_utilities_1_0.sit", 1173024 },
    { kCatUtilities, 1994, kArch68k, 60, "Norton Utilities for Macintosh 3.5", "Symantec's flagship disk repair, recovery, and optimization utility suite for classic Mac OS.", "/apps/norton_utilities_3.5_cd.toast_.sit", 29355797 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1984, kArch68k, 0, "Note Pad", "Apple's original simple text-note desk accessory.", "/apps/inotepad_0.dmg", 1990908 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArchFat, 70, "Now Contact", "Contact management software with internet syncing.", "/apps/Now_Contact_Demo_1.0.sit", 859264 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArchFat, 70, "Now TouchBase/DateBook Pro", "Now Software's integrated contact management and calendar application suite.", "/apps/NOW_TouchBase_DateBook_Pro_CD.zip", 43950232 },
    { kCatProductivity, 1997, kArchFat, 70, "Now Up-to-Date & Contact 3.6", "Calendar and contact management software from Now Software.", "/apps/nowuptodate__contact_3.6.sit", 4575199 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 70, "Now Utilities 5.0.1", "Suite of Finder and system enhancement utilities from Now Software.", "/apps/Now_Utilitiestm_5.0.1.img_.sit", 1358168 },
    { kCatUtilities, 1994, kArch68k, 70, "Now Utilities 6.0", "Menu, folder, and startup-manager enhancements bundle.", "/apps/Now_Utilities_6.0.sit", 5386182 },
    { kCatUtilities, 1996, kArchFat, 70, "Now Utilities 6.02", "A suite of system utilities including menu, folder, and startup management tools.", "/apps/NowUtilities602.sit_.bin", 6846976 },
    { kCatUtilities, 1997, kArch68k, 70, "Now Utilities 6.5.4", "Now Software's essential utility suite for classic Mac OS, including Now Menus, Now FolderMenus, and Now", "/apps/Now_Utilities_6.5.4_install.sit", 2315348 },
    { kCatUtilities, 1997, kArchFat, 70, "Now Utilities 6.7", "Updated release of Now Software's system utility suite for Mac OS.", "/apps/Now_Utilities_6.7-6.7.1.sit", 2973910 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 60, "Nuntius 2.0.3", "Classic Macintosh NNTP newsreader application for reading Usenet newsgroups.", "/apps/Nuntius2.0.3.sea_.bin", 816256 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 70, "Object Master", "C/C++ source code browser and class hierarchy tool.", "/apps/Object_Master_3.0.2.sit", 2258460 },
    { kCatDevTools, 1996, kArch68k, 70, "ObjectPlant 1.4", "An object-oriented class diagramming and design tool used by Mac Pascal/C++ developers to model application", "/apps/ObjectPlant1.4.sit_.bin", 1535360 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 0, kArchPPC, 75, "ObjectPlant 3.1.9", "A parametric 3D modeling application for Mac OS.", "/apps/ObjectPlant3.1.9.sit", 2193878 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1999, kArchPPC, 75, "ObjectPlant 3.3.0", "UML class diagram and object modeling tool for classic Mac OS software design.", "/apps/ObjectPlant3.3.0.sit", 1678605 },
    { kCatDevTools, 1998, kArch68k, 70, "ObjectPlant 3.3.2", "A later version of the object-oriented class diagramming and design tool for classic Mac OS developers.", "/apps/ObjectPlant3.3.2.sit", 1724721 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 60, "Ofoto", "Simple flatbed scanner control and image-acquire software.", "/apps/ofoto2.sit", 633811 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 60, "Oh No! More Lemmings (Demo)", "Playable demo of the puzzle-platformer sequel to Lemmings, Macintosh version.", "/games/ohnomorelemmings-demo.sit", 491225 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2003, kArchPPC, 86, "OhmBoyz 1.4.2 (Mac OS 9)", "A freeware VST/audio plugin host and rack application, this build made for classic Mac OS 9.", "/apps/OhmBoyz142_rtasmacos9_pro.bin", 1946624 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 30, "Oids", "Fast-paced side-scrolling shoot-em-up rescue game with gravity-based flight physics.", "/games/OIDS_v1.0_A2R_Moof_and_DC42.zip", 12502763 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "OmniPage", "Optical character recognition (OCR) software.", "/apps/OmniPage2.zip", 397152 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 60, "OmniPage 7.0", "Optical character recognition software from Caere for the classic Mac OS.", "/apps/omnipage_7.0.sit", 7219064 },
    { kCatUtilities, 1993, kArch68k, 60, "OmniPage Pro 2.1", "Optical character recognition software for converting scanned documents to editable text.", "/apps/OmniPagePro21.mar", 2950656 },
    { kCatUtilities, 1996, kArchPPC, 70, "OmniPage Pro 5", "Caere's optical character recognition (OCR) software.", "/apps/OmniPagePro5.sit_.hqx", 7413028 },
    { kCatUtilities, 1996, kArch68k, 70, "OmniPage Pro 7", "OCR software release with improved accuracy and layout retention.", "/apps/OmniPagePro7-installed-68k.sit", 3933130 },
    /* -- Productivity -- */
    { kCatProductivity, 1997, kArch68k, 70, "OmniPage Pro 8.0", "A later version of Caere's widely used optical character recognition (OCR) software for classic Mac OS.", "/apps/OmniPage_Pro_8.0.img_.sit", 13835859 },
    { kCatProductivity, 1994, kArch68k, 60, "OmniPage Professional", "Caere's widely used optical character recognition (OCR) software for classic Mac OS.", "/apps/omnipage_professional.sit", 680157 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "OmniPage SE", "Optical character recognition (OCR) software from Caere for the classic Mac OS.", "/apps/OmniPage_SE.zip", 22632276 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "OMS 1.2.3", "Opcode's Open Music System, MIDI driver and patch-management software underpinning most classic Mac music", "/apps/OMS1.2.3.sea_.hqx", 811525 },
    { kCatGraphicsSound, 1997, kArchFat, 70, "OMS 2.3.5", "A later release of Opcode's Open Music System, MIDI driver and patch-management software for classic Mac OS.", "/apps/OMS_2.3.5.hqx", 3389365 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "On Cue II 2.0", "Application and document launcher utility accessible from the menu bar.", "/apps/On_Cue_II_2.0.sit_.hqx", 200557 },
    { kCatUtilities, 1993, kArch68k, 0, "OnCue", "Application and document launcher menu utility.", "/apps/on_cue_v13.sit", 12155 },
    /* -- Games -- */
    { kCatGames, 2001, kArchPPC, 85, "Oni", "Bungie's cel-shaded 3D action game blending martial arts combat and gunplay.", "/games/Oni_1.2.1.zip", 89476710 },
    { kCatGames, 2001, kArchPPC, 84, "Oni (Demo)", "Demo of Bungie's cel-shaded action game combining gunplay and martial arts combat.", "/games/OniDemo.sit", 79260591 },
    { kCatGames, 2001, kArchPPC, 81, "Oni (German)", "Bungie's cel-shaded action game blending martial arts combat and gunplay; this is the German-language", "/games/Oni_Mac_German.toast_.sit", 383859376 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 40, "Opcode Sequencer Plus 2.6", "Opcode's early MIDI sequencing software for the Mac.", "/apps/Opcode_Sequencer_2.6.sit", 950407 },
    { kCatGraphicsSound, 1990, kArch68k, 40, "Opcode Vision 1.02", "Opcode Systems' professional MIDI sequencing application.", "/apps/OpcodeVision102.sit", 401618 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Open Music System (OMS) 2.3.7", "A shared MIDI driver and device management system used by many Mac music applications.", "/apps/oms2_3_7.sit", 2527874 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 70, "Open Prolog 1.0.3d33", "Earlier development build of the Open Prolog logic-programming environment.", "/apps/open-prolog-103d33.hqx", 456492 },
    { kCatDevTools, 1991, kArch68k, 60, "Open Prolog 1.1", "Prolog programming language interpreter for the classic Mac OS.", "/apps/Open_Prolog_1.1.sit_.bin", 712704 },
    { kCatDevTools, 1994, kArch68k, 70, "Open Prolog 1.1b10", "Free Prolog logic-programming implementation for classic Mac OS.", "/apps/Open_Prolog_1.1b10.sea_.hqx", 997672 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArchFat, 71, "Open Transport 1.1.1", "Apple's classic Macintosh networking architecture and control panel, successor to MacTCP.", "/apps/OpenTransport-111.sit", 3809751 },
    { kCatSystemExt, 1996, kArch68k, 70, "Open Transport 1.1.2", "Apple's modern networking architecture extension for classic Mac OS, replacing the older MacTCP stack.", "/apps/OpenTransport-1.1.2.sit", 7124978 },
    { kCatSystemExt, 1999, kArchPPC, 75, "OpenGL for Mac OS 1.0", "Apple's first official implementation of the OpenGL 3D graphics API for Mac OS.", "/apps/OpenGL_1_0.sit_.hqx", 2632695 },
    /* -- Internet & Comm -- */
    { kCatInternet, 2000, kArchPPC, 81, "Opera 5.0", "Opera Software's fast, standards-focused web browser ported to classic Mac OS.", "/apps/Opera5.0Installer.PPC__0.sit", 2101135 },
    { kCatInternet, 2000, kArchPPC, 81, "Opera 5.0 (Beta 4, Classic)", "Earlier beta build of the Opera web browser for Classic Mac OS.", "/apps/Opera5.0b4classic.PPC_.sit", 2057603 },
    { kCatInternet, 2000, kArchPPC, 81, "Opera 5.0 (Beta 5, Classic)", "Beta build of the Opera web browser for Classic Mac OS.", "/apps/Opera5.0b5classic.PPC_.sit", 2105539 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 0, "Oracle for Macintosh", "Client tools for the Oracle relational database.", "/apps/Oracle2.1.0.sit", 173865 },
    /* -- Games -- */
    { kCatGames, 1997, kArchPPC, 75, "Oregon Trail II", "Expanded sequel to the classic educational Oregon Trail simulation.", "/games/OregonTrailII_1.32.sit", 413162354 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1997, kArch68k, 75, "OSA Menu 1.2.2", "Leonard Rosenthol's popular menu-bar utility for launching AppleScript scripts.", "/apps/OSA_Menu_1.2.2_Installer.sit", 246292 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "OtherMenu 1.74", "A shareware Apple menu enhancer that lets users organize hierarchical submenus and launch items quickly.", "/apps/OtherMenu174.sit_.bin", 253440 },
    /* -- Games -- */
    { kCatGames, 2001, kArchPPC, 85, "Otto Matic", "Pangea Software's retro sci-fi action game starring a robot battling alien invaders.", "/games/otto_matic_0.sit", 139570411 },
    { kCatGames, 2001, kArchPPC, 86, "Otto Matic (Demo)", "Playable demo of Pangea Software's retro sci-fi action game about an alien-fighting robot.", "/games/Otto_Matic_Demo_201.sit", 24691161 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 75, "Outlook Express 4.5", "Microsoft's free email and newsgroup client for Macintosh.", "/apps/OutlookExpress4.5Folder.hqx", 1953798 },
    { kCatInternet, 1999, kArchPPC, 70, "Outlook Express 5.0.6", "Microsoft's free email and newsgroup client for classic Mac OS.", "/apps/OutlookExpress506ENU.bin", 9715456 },
    { kCatInternet, 1999, kArchFat, 75, "Outlook Express 5.02", "Microsoft's email and newsgroup client for Macintosh.", "/apps/Outlook_Express_5.02.zip", 11379903 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1998, kArchPPC, 75, "outSPOKEN 8", "Screen-reading accessibility software that spoke the Mac OS interface aloud for blind users.", "/apps/outSPOKEN_8.bin", 255360 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "OverVUE 2.1a", "ProVUE's early flat-file database management application.", "/apps/OverVUE_2.1a.image_.zip", 190816 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "Oxyd", "Atmospheric puzzle game of stones, switches, and marbles.", "/games/oxyd.sit", 684341 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "OzTeX 1.7", "An earlier version of the popular implementation of the TeX typesetting system for classic Mac OS.", "/apps/OzTeX_1.7.sit", 6792450 },
    { kCatDevTools, 1995, kArch68k, 60, "OzTeX 2.1", "TeX typesetting system distribution for the classic Mac OS.", "/apps/OzTeX_2.1.sit", 7367494 },
    { kCatDevTools, 1993, kArch68k, 60, "OzTeX 3.1", "TeX and LaTeX typesetting distribution for classic Mac OS.", "/apps/OzTeX_3.1.sit", 9337562 },
    { kCatDevTools, 1998, kArchFat, 70, "OzTeX 4.0g", "A popular implementation of the TeX typesetting system for classic Mac OS.", "/apps/OzTeX4.0g.smi_.sea_.bin", 13579904 },
    { kCatDevTools, 2000, kArchPPC, 75, "OzTeX 6.0", "TeX typesetting distribution release with updated fonts and PDF output support.", "/apps/OzTeX_6.0.zip", 16356002 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 10, "PageMaker 1.2", "Aldus PageMaker, the software that launched the desktop publishing revolution, running on the original", "/apps/Page_Maker_1.2F.image_.sit", 164404 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 60, "PageSpinner 1.0.1", "Optima System's popular shareware HTML editor for classic Mac OS.", "/apps/PageSpinner_1.0.1.sit", 577371 },
    { kCatInternet, 1995, kArch68k, 60, "PageSpinner 1.1", "Early release of the PageSpinner HTML editor for the classic Mac OS.", "/apps/PageSpinner_1.1.sit", 600031 },
    { kCatInternet, 1997, kArchPPC, 70, "PageSpinner 3.0", "HTML authoring and web page editing tool for the classic Mac OS.", "/apps/PageSpinner_3.0_PPC.sit", 1910567 },
    { kCatInternet, 1998, kArchFat, 70, "PageSpinner 3.1", "Later release of Optima System's shareware HTML web page editor.", "/apps/pagespinner-31.sit", 2262932 },
    { kCatInternet, 1998, kArchPPC, 75, "PageSpinner 3.1.2", "Earlier PowerPC release of the PageSpinner HTML editor.", "/apps/pagespinner-312-ppc.sea__0.hqx", 3083360 },
    { kCatInternet, 2001, kArchFat, 75, "PageSpinner 4.6.2", "Optima System's popular shareware HTML editor for Macintosh.", "/apps/PageSpinner_4.6.2_Install.sit", 3930734 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "Painter 1.0", "Fractal Design's original natural-media digital painting application.", "/apps/Painter1.0.sit", 1108785 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Painter 2.0", "Fractal Design's natural-media painting software, an early version.", "/apps/Painter_2.0.zip", 4321696 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "Painter 3.0", "An early version of Fractal Design Painter, the natural-media digital painting application for classic Mac", "/apps/Painter3.0.sit", 7789326 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Painter 4.0", "Natural-media digital painting software from Fractal Design.", "/apps/Painter_4.0_Installer_English.sit", 11333641 },
    { kCatGraphicsSound, 1998, kArchFat, 70, "Painter 5.0.3 Update", "Update for Fractal Design/MetaCreations Painter, the natural-media digital painting application for Mac OS.", "/apps/Painter_5.0.3_Update.sit_.hqx", 2933644 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Painter 5.5 Web Edition", "Version of Painter tailored for creating Web graphics and animations.", "/apps/painter_5.5_web_edition_c....sit", 263213185 },
    { kCatGraphicsSound, 1999, kArchPPC, 75, "Painter 6", "MetaCreations/Corel's natural-media digital painting software.", "/apps/Corel-Painter6-1.zip", 410781043 },
    { kCatGraphicsSound, 2002, kArchPPC, 86, "Painter 7", "Update package for Painter 7, the natural-media digital painting application.", "/apps/Painter7Update.sit_.bin", 27971328 },
    { kCatGraphicsSound, 2002, kArchPPC, 86, "Painter 7 Update", "Update for Corel/Procreate Painter, the natural-media digital painting application for Mac OS.", "/apps/Painter7Update.sit__0.hqx", 38026312 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "Painter Classic", "Simplified natural-media painting application.", "/apps/painter_5.sit", 34728248 },
    /* -- Games -- */
    { kCatGames, 1998, kArch68k, 70, "Pajama Sam 2: Thunder and Lightning aren't so", "Humongous Entertainment's kids' point-and-click adventure about facing your fears.", "/games/Pajama_Sam_2.iso_.sit", 263491450 },
    /* -- Productivity -- */
    { kCatProductivity, 2000, kArchPPC, 81, "Palm Desktop 4.2.1 (German)", "German-language release of the Palm Desktop organizer software for syncing with PalmPilot devices.", "/apps/PalmDesktopMac421DE.sit", 12466789 },
    /* -- Utilities -- */
    { kCatUtilities, 2000, kArchPPC, 75, "Palm Desktop for Mac 4.2.1", "Companion desktop software for synchronizing Palm OS handhelds with a Macintosh.", "/apps/PalmDesktopMac421EN.sit", 12392169 },
    /* -- Productivity -- */
    { kCatProductivity, 1996, kArchPPC, 70, "Panorama 1.1.1", "ProVUE Development's fast, in-memory relational database application for Mac OS.", "/apps/panorama_1.1.1_carbon.sit", 1663216 },
    { kCatProductivity, 1999, kArchPPC, 70, "Panorama 4.02", "A later version of ProVUE Development's fast, in-memory relational database application for Mac OS.", "/apps/Panorama-4-02-Installer.sit", 3549695 },
    { kCatProductivity, 1998, kArchPPC, 75, "Panorama 5", "ProVUE's high-speed in-memory relational database application.", "/apps/Panorama5MacOSInstaller.sit", 8753219 },
    /* -- Games -- */
    { kCatGames, 1995, kArchPPC, 75, "Panzer General", "SSI's turn-based World War II strategy wargame, Macintosh port.", "/games/Panzer_General.toast", 667353088 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "PaperPort 2.0.1", "Desktop scanning and document management software from Visioneer.", "/apps/PaperPort2.0.1.sit", 2465210 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "PaperPort 3.0", "Visioneer's document scanning and management software.", "/apps/PaperPort3.0.sit", 3090661 },
    { kCatProductivity, 1990, kArch68k, 60, "Papyrus", "A German-developed WYSIWYG word processor for classic Mac OS known for its integrated bibliography tools.", "/apps/PAPYRUS.sit", 7440506 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 60, "Pararena 2", "Fast overhead multiplayer paddle-ball arena game.", "/games/Pararena2.SIT", 607440 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 40, "Passport Master Tracks Pro 4", "MIDI sequencing software from Passport Designs.", "/apps/MasterTracks_Pro4.mac", 839040 },
    /* -- Utilities -- */
    { kCatUtilities, 2001, kArchFat, 75, "Password Wallet 2.7", "Password and confidential information manager for Macintosh.", "/apps/Password_Wallet_2.7.sit", 1170719 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Pathways Into Darkness", "Bungie's atmospheric first-person horror-adventure.", "/games/pathwaysintodarkness.zip", 28087901 },
    { kCatGames, 1993, kArch68k, 70, "Pathways into Darkness 1.1", "Bungie's atmospheric first-person horror/exploration game predating Marathon.", "/games/pathways-i-d-11.sit", 1984866 },
    { kCatGames, 1993, kArch68k, 70, "Pax Imperia", "4X space exploration and conquest strategy game with real-time and turn-based play.", "/games/pax_imperia_cd.sit", 2005787 },
    { kCatGames, 1997, kArchPPC, 70, "Pax Imperia: Eminent Domain", "A Mac-exclusive real-time 4X space strategy and empire-building game.", "/games/Pax_Imperia_2_bin-cue.zip", 558971352 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "PBTool", "PowerBook battery and power-management utility.", "/apps/PBTools10.sit", 60361 },
    { kCatUtilities, 1991, kArch68k, 60, "PC Tools Deluxe for Macintosh", "Central Point Software's disk utility and file recovery suite, ported to classic Mac OS.", "/apps/PC_Tools_Deluxe_Mac.hqx", 543863 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2000, kArchPPC, 86, "Peak 3.21", "BIAS Inc's professional stereo digital audio editing and mastering application for Mac OS.", "/apps/Peak_3.21_Mac_OS_8.6-9.2.sit", 1321988 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "Peek-A-Boo", "Displays running processes and open files, like a task manager.", "/apps/peek-a-boo-15.sit", 275765 },
    { kCatUtilities, 1994, kArch68k, 70, "Peek-A-Boo 1.4", "Utility for viewing and managing running processes and background applications on classic Macintosh.", "/apps/Peek-a-Boo_1.4.sit", 322947 },
    { kCatUtilities, 1996, kArch68k, 70, "Peek-A-Boo 1.5", "Utility that monitors running processes and CPU/memory usage on the classic Mac OS.", "/apps/Peek-a-Boo-1.5.zip", 270896 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Pegleg", "Pirate-themed arcade action game.", "/games/PegLeg.img_.sit", 994548 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 40, "Performer 1.22", "Earlier version of Mark of the Unicorn's MIDI sequencing application, Performer.", "/apps/Performer_1.22_dsk.sit", 110897 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "Performer 1.3", "Early release of Mark of the Unicorn's MIDI sequencing software.", "/apps/Performer_1.3.zip", 2366143 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Performer 2.2.1", "Mark of the Unicorn's professional MIDI sequencing application.", "/apps/performer2.2.1.sit", 26741 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Performer 3.5", "Later version of Mark of the Unicorn's professional MIDI sequencer.", "/apps/Performertm35.sit", 1669298 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "Performer 5.5", "Mark of the Unicorn's professional MIDI sequencing software.", "/apps/Performer_5.5.sit", 5948385 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "Performer 6.0.1", "Mark of the Unicorn's professional MIDI sequencing software for classic Mac OS, predecessor to Digital", "/apps/Performer_6.0.1.sit", 14197870 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 60, "Persuasion 2.0", "Presentation graphics software from Aldus for the classic Mac OS.", "/apps/Persuasion2.0.sit", 2568500 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 40, "PGA Tour Golf", "Electronic Arts Sports golf simulation licensed by the PGA Tour.", "/games/PGA_Tour_Golf.mar", 1678336 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 75, "PGP Freeware 6.0", "Pretty Good Privacy encryption software, freeware Macintosh edition.", "/apps/PGPfreeware-6.sit", 5682702 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1999, kArchPPC, 75, "PGP Freeware 6.0.2", "Pretty Good Privacy's public-key encryption software for securing files and email.", "/apps/PGPfreeware602.bin", 6203338 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchFat, 70, "PGP Freeware 6.0.2i (French)", "The Pretty Good Privacy encryption and digital signature suite for classic Mac OS, this build localized for", "/apps/PGPfreeware602i-fr.sit", 1013203 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1996, kArch68k, 70, "PGPfone 1.0", "Encrypted internet voice-calling software built on Pretty Good Privacy encryption.", "/apps/PGPfone10.sea", 549620 },
    { kCatInternet, 1996, kArch68k, 70, "PGPfone 1.0b7", "Philip Zimmermann's pioneering secure voice-over-IP encryption software for classic Mac OS.", "/apps/PGPFone_1.0b7.sit", 720779 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 70, "PhotoFlash", "Simple consumer image-editing application.", "/apps/PhotoFlash_2.img_.sit", 3974628 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArch68k, 60, "PhotoRealistic RenderMan 1.3.1", "Pixar's high-end 3D rendering software implementing the RenderMan interface.", "/apps/RenderMan_1.3.1_Installer.sit", 1667754 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Pipe Dream", "Puzzle game of connecting pipes before the flow starts.", "/games/pipe_dream.sit", 459570 },
    { kCatGames, 1993, kArch68k, 60, "Pirates! Gold", "Swashbuckling open-world pirate adventure game.", "/games/Pirates-Gold-CD-iso.sit", 29879513 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 60, "Pixar Typestry 1.1.1", "Pixar's consumer application for rendering 3D typography and logos on classic Mac OS.", "/apps/Pixar_Typestry_1.1.1.sit", 2902961 },
    { kCatGraphicsSound, 1988, kArch68k, 0, "PixelPaint", "SuperMac Technology's original color paint application for the Macintosh II.", "/apps/pixelpaint.sit", 359818 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "PixelPaint Pro 2", "SuperMac Technology's professional 24-bit color paint application.", "/apps/PixelPaintPro2.sea_.hqx", 3507193 },
    { kCatGraphicsSound, 1994, kArch68k, 60, "PixelPaint Pro 2.0.1", "24-bit color paint and image editing software for the classic Mac OS.", "/apps/PixelPaintPro201.hqx", 3167933 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "PixelPaint Pro Demo", "Color painting and photo retouching, demo edition.", "/apps/PixelPaint_Pro_3.02.sit", 7204023 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "PlainTalk", "Apple's speech recognition and synthesis extension.", "/apps/PlainTalk_1.5.sit", 8088573 },
    /* -- Games -- */
    { kCatGames, 1983, kArch68k, 10, "Planetfall", "Infocom's science-fiction text adventure about a shipwrecked space bureaucrat and his robot companion Floyd.", "/games/Planetfall_r29_dc42.sit", 195116 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1999, kArchPPC, 75, "PlayerPRO 4.5.9", "Music tracker and MOD file player/composer for classic Mac OS.", "/apps/PlayerPRO_4.5.9.sit", 1068512 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 30, "Pool of Radiance", "SSI's Advanced Dungeons & Dragons Gold Box role-playing game, Macintosh port.", "/games/Pool_Of_Radiance.SIT", 1519532 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArch68k, 60, "PopChar", "Shows and inserts special characters from any font.", "/apps/popchar.sit", 59376 },
    { kCatUtilities, 1998, kArch68k, 60, "PopChar 2.6.2", "Utility that displays a font's full character set for easy insertion of special characters.", "/apps/PopChar_2.6.2.bin", 35456 },
    { kCatUtilities, 2000, kArchFat, 75, "PopChar Pro 1.3.2", "A utility that displays and inserts special characters from any installed font.", "/apps/PopChar_Pro_1.3.2.hqx", 98044 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Populous", "Godlike real-time strategy, shape land and lead followers.", "/games/MacPopulous.sit", 989592 },
    { kCatGames, 1990, kArch68k, 60, "Populous (Demo)", "Demo of Bullfrog's pioneering god game in which players terraform land to grow their civilization.", "/games/PopulousDemo.sit", 530490 },
    { kCatGames, 1991, kArchFat, 60, "Populous II", "Bullfrog's classic god-game sequel, guiding a civilization to power.", "/games/MacPopulous_II.toast_.sit", 177487493 },
    { kCatGames, 1991, kArch68k, 60, "Populous II: Trials of the Olympian Gods", "Bullfrog's mythology-themed god-game strategy sequel.", "/games/Populous_II_image.sit", 3959153 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArchFat, 70, "Poser", "3D human figure posing and rendering application.", "/apps/poser2.sit", 22323746 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "Poser 1.0", "Fractal Design's original release of the 3D human figure posing application.", "/apps/Poser_Install_Disks_1.0.zip", 3710926 },
    { kCatGraphicsSound, 1997, kArchFat, 70, "Poser 2", "3D figure modeling and posing software for character animation.", "/apps/Poser_2_CD.toast_.zip", 79053918 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Poser 3", "MetaCreations' 3D figure design and posing application.", "/apps/POSER3.zip", 298160134 },
    { kCatGraphicsSound, 1999, kArchFat, 70, "Poser 4", "MetaCreations' 3D human figure posing, animation, and rendering application, a further upgrade over Poser 3.", "/apps/Poser_4_Application_CD-ROM_0.zip", 313316429 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArch68k, 60, "PowerBar 1.0", "Floating palette of one-click system toggles.", "/apps/PowerBar1.1.1.sit", 113664 },
    { kCatSystemExt, 1993, kArch68k, 70, "PowerKey", "Extension for controlling a Sophisticated Circuits PowerKey.", "/apps/PowerKey_3-4.sit", 1282092 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 40, "PowerLisp 1.01", "A Common Lisp development environment for classic Mac OS.", "/apps/PowerLisp_1.01.sit_.bin", 264960 },
    /* -- Internet & Comm -- */
    { kCatInternet, 2001, kArchPPC, 81, "PowerMail 4.2.1 (Classic)", "Email client software for the classic Mac OS from CTM Development.", "/apps/PowerMail_4.2.1_classic.sit", 2687281 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 0, "PowerMerge", "File synchronization and backup utility.", "/apps/PowerMerge_2.02.sit", 348631 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "PowerMonger (Demo)", "Demo of Bullfrog's real-time strategy game of medieval conquest.", "/games/PowerMonger_demo.sit", 843493 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1995, kArchFat, 0, "PowerPlant", "Metrowerks' C++ application framework for CodeWarrior.", "/apps/open-powerplant-code-git-svned.zip", 40976090 },
    /* -- Productivity -- */
    { kCatProductivity, 1992, kArch68k, 60, "PowerPoint 3.0", "Earlier version of Microsoft's presentation software.", "/apps/powerpoint_3.0_e_1992.sit", 6741744 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "PowerPrint 2.5.2", "GDT Softworks' universal printer driver software letting classic Mac OS print to a wide range of non-Apple", "/apps/PowerPrint2.5.2.sit", 2706564 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "Practica Musica 2.34", "Music theory and ear-training education software for the classic Mac OS.", "/apps/Practica_Musica_2.34.sit", 280724 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Prince of Persia", "Swashbuckling platformer - rescue the princess in 60 minutes.", "/games/Prince-of-Persia_Optimized.sit", 1452977 },
    { kCatGames, 1994, kArch68k, 60, "Prince of Persia 2", "The Shadow and the Flame - the direct sequel.", "/games/Prince_Of_Persia2.SIT", 7716607 },
    { kCatGames, 1993, kArch68k, 60, "Prince of Persia 2: The Shadow and the Flame", "Sequel platformer continuing the story of the acrobatic hero battling a usurper.", "/games/PoP_2_floppies_uncompressed_version_0.zip", 1408921 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "Pro Tools 1.1", "Early version of Digidesign's Pro Tools digital audio workstation.", "/apps/pro_tools_1.1.sit", 3378586 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Pro Tools 2.51", "Updated early release of Digidesign's Pro Tools digital audio workstation.", "/apps/Pro_Tools_2.51.zip", 43644901 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "Pro Tools 3", "Digidesign's professional digital audio recording and editing workstation software.", "/apps/protools_v3.zip", 5811669 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Pro Tools 4.0", "Digidesign's professional digital audio workstation software.", "/apps/ProTools_4.0_CD_nk.sit", 21502648 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Pro Tools 4.3.1", "Digidesign's professional digital audio workstation software, installer CD image.", "/apps/Pro_Tools_4.3.1_Installer_CD.iso", 546082816 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1991, kArch68k, 60, "Prodigy 2.1.0", "The client software for connecting a classic Mac to the Prodigy online service.", "/apps/Prodigy_2.1.0.sit", 1094861 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1987, kArch68k, 30, "Professional Composer 2.0", "Music notation software from Mark of the Unicorn for engraving printed scores.", "/apps/ProfessionalComposer2.0.sit", 99458 },
    { kCatGraphicsSound, 1988, kArch68k, 30, "Professional Composer 2.3", "Music notation and composition software from Mark of the Unicorn.", "/apps/Professional_Composer_2.3M.dc42.zip", 424356 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1989, kArch68k, 70, "Prograph", "Visual, dataflow-based object-oriented programming environment.", "/apps/PrographCPX.sit", 8314906 },
    { kCatDevTools, 1996, kArchFat, 70, "Prograph Classic 2.6.1", "Prograph International's visual dataflow object-oriented programming environment.", "/apps/Prograph_Classic_2.6.1.sit", 11918517 },
    { kCatDevTools, 1994, kArchFat, 70, "Prograph CPX", "Visual, dataflow-based object-oriented programming environment for the Macintosh.", "/apps/Prograph_CPX.sit", 4218483 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Propellerhead ReCycle 1.6", "Audio loop editing and slicing tool from Propellerhead Software.", "/apps/ReCycle_1.6_PPC.hqx", 1216176 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "Public Utilities", "Freeware collection of small Finder and system utilities.", "/apps/Public_Utilities_1.0.sit", 677377 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "Publish It! 1.2", "Entry-level desktop publishing program for newsletters and simple page layouts.", "/apps/Publish-It_1.2.sit", 1099579 },
    /* -- Games -- */
    { kCatGames, 1997, kArch68k, 70, "Putt-Putt Enters the Race", "Fifth installment of Humongous Entertainment's Putt-Putt series for young children.", "/games/Putt-Putt_5_EntersTheRace.iso_.sit", 419571354 },
    { kCatGames, 1993, kArch68k, 60, "Putt-Putt Joins the Circus", "Humongous Entertainment's point-and-click adventure game for children.", "/games/Putt-PuttJoinsTheCircus.iso_.sit", 310034971 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1984, kArch68k, 70, "Puzzle", "The classic sliding-tile-puzzle desk accessory.", "/games/101_puzzle.sit", 615527 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 60, "Pyst", "Parroty Interactive's satirical parody of Myst, a well-known comedic CD-ROM title for classic Mac OS.", "/games/PYST.toast_.sit", 249220462 },
    { kCatGames, 1997, kArch68k, 70, "Quake", "id Software's landmark 3D first-person shooter, ported to classic Mac OS.", "/games/Quake_1.zip", 602969976 },
    { kCatGames, 1997, kArchPPC, 75, "Quake 1.2.1", "id Software's groundbreaking 3D first-person shooter.", "/games/Quakev1.2.1.dmg_.zip", 3761211 },
    { kCatGames, 1998, kArchPPC, 75, "Quake II", "id Software's science-fiction first-person shooter, Macintosh port.", "/games/Quake2.app_.sit", 98510188 },
    { kCatGames, 1999, kArchPPC, 86, "Quake III Arena (Demo)", "Playable demo of id Software's multiplayer-focused arena shooter, Macintosh port.", "/games/Quake_III_Arena_1.0_Demo.sit", 48006200 },
    { kCatGames, 1988, kArch68k, 30, "Quandary", "Word-puzzle adventure game for the classic Mac OS.", "/games/Quandary.img_.sit", 3135698 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArchPPC, 70, "Quark Immedia 1.01", "Quark's multimedia and interactive presentation authoring add-on for QuarkXPress.", "/apps/QuarkImmediatm_1.01_Updater.sit", 523455 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArchFat, 70, "QuarkImmedia 1.0", "Multimedia authoring extension for QuarkXPress used to build interactive CD-ROM titles.", "/apps/QuarkImmediatm_1.0_Installer.img", 1474644 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "QuarkStyle 1.0", "Simplified desktop publishing program from Quark aimed at business documents rather than professional print.", "/apps/QuarkStyle1.0_0.sit", 1007477 },
    { kCatProductivity, 1988, kArch68k, 40, "QuarkXPress 1.1", "Early version of Quark's professional page-layout application that came to dominate publishing.", "/apps/QuarkXPress1.11_A2R.zip", 33083311 },
    { kCatProductivity, 1991, kArch68k, 60, "QuarkXPress 2.11", "Early 68k-native version of Quark's desktop publishing application.", "/apps/QuarkXpress-211f.sit", 604908 },
    { kCatProductivity, 1991, kArch68k, 60, "QuarkXPress 2.11e", "An early version of Quark's dominant professional page layout and desktop publishing software for classic", "/apps/QuarkXPress-211e.sit", 1048099 },
    { kCatProductivity, 1990, kArch68k, 60, "QuarkXPress 3.0", "Page layout software that became an industry standard for professional print design.", "/apps/QuarkXPress3.0-DC42.sit", 1790603 },
    { kCatProductivity, 1992, kArch68k, 60, "QuarkXPress 3.1", "Page layout application update adding color separation and typography improvements.", "/apps/quarkxpress-31-us.sit", 1534657 },
    { kCatProductivity, 1992, kArch68k, 60, "QuarkXPress 3.1 (Italian)", "Quark's dominant professional page layout and desktop publishing software for classic Mac OS, localized for", "/apps/Quark_XPressr_3.1_ITA.sit", 1670839 },
    { kCatProductivity, 1993, kArch68k, 60, "QuarkXPress 3.11 Updater", "Update for Quark's dominant professional page layout and desktop publishing software for classic Mac OS.", "/apps/QuarkXPress-311-US-Updater.sit", 1915585 },
    { kCatProductivity, 1992, kArch68k, 60, "QuarkXPress 3.2", "Widely used desktop-publishing release of QuarkXPress.", "/apps/QuarkXPress_3.2.zip", 2941410 },
    { kCatProductivity, 1993, kArch68k, 60, "QuarkXPress 3.3 Updater", "Updater package for QuarkXPress 3.3, the industry-standard desktop publishing application.", "/apps/QuarkXPresstm_3.31r5_Updater.dmg", 874372 },
    { kCatProductivity, 1993, kArchFat, 70, "QuarkXPress 3.31", "Maintenance update to QuarkXPress 3.3 professional page layout software.", "/apps/QuarkXPress3.31.sit", 5809811 },
    { kCatProductivity, 1994, kArch68k, 70, "QuarkXPress 3.32", "Refined point release of QuarkXPress 3, long the industry standard in page layout.", "/apps/QuarkXPresstm_3.32.img", 63752992 },
    { kCatProductivity, 1997, kArchFat, 70, "QuarkXPress 4 (French)", "French-language edition of QuarkXPress 4 professional page layout software.", "/apps/QuarkXPress_4_fr_.sit", 11044827 },
    { kCatProductivity, 1997, kArch68k, 75, "QuarkXPress 4.0", "Major QuarkXPress release adding advanced typography and printing features.", "/apps/XPRESS4.0.zip", 31881071 },
    { kCatProductivity, 1997, kArchPPC, 75, "QuarkXPress 4.03", "Quark's professional desktop publishing and page layout application.", "/apps/QuarkXPress_4.03.sit", 10865303 },
    { kCatProductivity, 1998, kArchPPC, 75, "QuarkXPress 4.1", "Page layout software update adding tables and improved typography tools.", "/apps/qxp-4-update-41.sit", 30163913 },
    { kCatProductivity, 1999, kArchPPC, 81, "QuarkXPress 4.1 Update", "Update for Quark's dominant professional page layout and desktop publishing software for Mac OS.", "/apps/QuarkXPress_4.10_Update.sit", 11635173 },
    { kCatProductivity, 2001, kArchPPC, 85, "QuarkXPress 5.0", "Later release of Quark's desktop publishing software.", "/apps/QuarkXPress_5_inst.k256users.sit", 1857993 },
    { kCatProductivity, 2004, kArchPPC, 86, "QuarkXPress 6.1", "A later version of Quark's dominant professional page layout and desktop publishing software.", "/apps/QuarkXPress_6.1.toast_.sit", 252130675 },
    { kCatProductivity, 1993, kArch68k, 60, "QuarkXPress Passport 3.31", "The multilingual edition of QuarkXPress, Quark's dominant professional page layout software, for classic Mac", "/apps/XPress_Passport_3.31.sit", 5338748 },
    /* -- Dev Tools -- */
    { kCatDevTools, 0, kArchPPC, 75, "Quesa", "An open-source reimplementation of Apple's QuickDraw 3D API.", "/apps/Quesa.zip", 655812 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Quest for Glory", "Sierra's hybrid role-playing/graphic adventure game series.", "/games/QuestForGlory-Floppies.sit", 7866298 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "QuickBooks for Mac 3.0", "Intuit's small-business accounting and bookkeeping software for classic Mac OS.", "/apps/QuickBooks_Mac_3.0.hqx", 5099847 },
    { kCatProductivity, 1993, kArch68k, 60, "QuickDEX 1.4A", "Flashcard-style flat-file database and address book utility from Casady & Greene.", "/apps/QuickDEX_1.4A.img_.zip", 105244 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1997, kArchPPC, 75, "QuickDraw 3D 1.5.1", "Apple's cross-platform 3D graphics rendering extension for Mac OS.", "/apps/QuickDraw_3D_v151.sit", 3220281 },
    { kCatSystemExt, 1994, kArchFat, 70, "QuickDraw GX", "Apple's advanced graphics and printing architecture extension.", "/apps/QuickDraw_GX_112.sit", 15353078 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 70, "Quicken", "Personal finance and checkbook management software.", "/apps/quicken4.sit", 750592 },
    { kCatProductivity, 1991, kArch68k, 60, "Quicken 3.0", "Intuit's personal finance and checkbook management application for Macintosh.", "/apps/quicken3.sit", 388568 },
    { kCatProductivity, 1996, kArch68k, 70, "Quicken 5", "Intuit's personal finance and checkbook management software.", "/apps/Quicken_5.sit", 1245240 },
    { kCatProductivity, 1996, kArch68k, 70, "Quicken SE 7", "Intuit's Special Edition personal finance and checkbook management software for classic Mac OS.", "/apps/Quicken_SE_7_BSNG.sit", 3912 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 70, "QuicKeys", "Macro and automation utility for repetitive tasks.", "/apps/quickeys_2.1.2_0.sit", 876954 },
    /* -- Utilities -- */
    { kCatUtilities, 1988, kArch68k, 40, "QuicKeys 1.0", "First release of the QuicKeys macro and keyboard automation utility.", "/apps/Quickeys1.0.sit_.hqx", 78148 },
    { kCatUtilities, 1987, kArch68k, 0, "QuicKeys 1.2", "Early release of CE Software's popular macro recording and automation utility.", "/apps/quickeys12_0.sit", 287288 },
    { kCatUtilities, 1989, kArch68k, 60, "QuicKeys 2.0.1", "CE Software's landmark macro recorder and automation utility for the classic Mac OS.", "/apps/QuicKeys_2_-_v2.0.1_Two_disk_set_Blue_disks.zip", 1954048 },
    { kCatUtilities, 1991, kArch68k, 60, "QuicKeys 2.1.3", "CE Software's widely used macro and keyboard-shortcut automation utility.", "/apps/QuicKeys_2.1.3_for_System_7_Three_disks_Black_label_-_SN_72453.zip", 2369232 },
    { kCatUtilities, 1993, kArch68k, 70, "QuicKeys 3.0", "Macro and keyboard shortcut automation utility from CE Software.", "/apps/Quickeys_3.0_0.sit", 1459718 },
    { kCatUtilities, 1990, kArch68k, 60, "QuicKeys 3.0.1", "Macro and automation utility for the classic Mac OS from CE Software.", "/apps/QuicKeys_v3.0.1_-_Two_disk_set_Green_label_-_SN_1090421.zip", 3158196 },
    { kCatUtilities, 1993, kArch68k, 60, "QuicKeys 3.5", "CE Software's macro recorder and automation utility for classic Mac OS.", "/apps/QuicKeys3.5.sit", 1072003 },
    { kCatUtilities, 1993, kArch68k, 60, "QuicKeys 3.5.1", "CE Software's macro and automation utility, version 3.5.1.", "/apps/QuicKeys351.dsk", 1474560 },
    { kCatUtilities, 1996, kArchFat, 70, "QuicKeys 3.5.2", "CE Software's macro recording and keyboard automation utility.", "/apps/QuicKeys3.5.2.hqx", 1880655 },
    { kCatUtilities, 1995, kArch68k, 70, "QuicKeys 4.0.7", "CE Software's popular macro recording and automation utility for Macintosh.", "/apps/QuicKeys_4.0.7.zip", 27071964 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1992, kArch68k, 60, "QuickLink II Fax 2.0", "Smith Micro's fax send and receive software for Mac OS.", "/apps/QuickLink_II_Fax_2.0_disk.sit", 216148 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "QuickMail", "Networked electronic mail client and server software.", "/apps/QuickMail_v201.sit", 641665 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "QuickTime 1.0", "Apple's original multimedia extension bringing synchronized video and sound playback to Macintosh.", "/apps/quicktime1.0.img_.sit", 232752 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "QuickTime 1.0 (Beta 18)", "Pre-release beta of Apple's original QuickTime multimedia extension.", "/apps/QuickTime_1.0b18.sit", 294813 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "QuickTime 1.0a9", "An early prerelease build of Apple's original QuickTime multimedia extension.", "/apps/QuickTime_1.0a9.sit", 356925 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "QuickTime 1.5", "Early update to Apple's QuickTime system extension for playing digital video and audio.", "/apps/QuickTime_1.5.img_.sit", 564619 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "QuickTime 1.6.2", "An early release of Apple's multimedia extension for playing and authoring digital video and audio on", "/apps/quicktime_1_6_2.zip", 842773 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 60, "QuickTime 2.1", "Apple's multimedia system extension for playing and authoring digital video and audio.", "/apps/QuickTime_2.1.hqx", 1187189 },
    /* -- Featured -- */
    { kCatFeatured, 1996, kArchFat, 60, "QuickTime 2.5", "Apple's multimedia extension for movies and sound.", "/apps/QuickTime_2.5_Installer.sit", 2041510 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1998, kArchFat, 70, "QuickTime 3.0", "A major release of Apple's multimedia extension for playing and authoring digital video and audio on Mac OS.", "/apps/QuickTime_3.0d37e1.sit", 14690271 },
    { kCatSystemExt, 1999, kArchFat, 75, "QuickTime 4.0", "Apple's multimedia framework, this release introduced the QuickTime Player interface redesign and streaming.", "/apps/quicktime4.cdr_.sit", 34398542 },
    { kCatSystemExt, 2001, kArchPPC, 86, "QuickTime 5.0.1 Pro Series", "A later release of Apple's multimedia extension for playing and authoring digital video and audio on Mac OS.", "/apps/QuickTime_5.0.1_ProSeri_F.sit", 9566716 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "QuickTime Conferencing", "Apple's early video-conferencing extension built on QuickTime.", "/apps/QuickTimetm_Conferencing.sit_.hqx", 3156983 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArch68k, 75, "QuickTime VR Authoring Studio", "Apple's toolkit for creating panoramic and object-movie QuickTime VR content.", "/apps/QuickTime_VR_Authoring_Studio.zip", 301290793 },
    /* -- Games -- */
    { kCatGames, 1985, kArch68k, 10, "Racter", "Early artificial-intelligence conversation program marketed as a game.", "/games/racter.zip", 207898 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "RagTime 3.1 (French)", "A page layout and spreadsheet hybrid application for classic Mac OS, localized for French.", "/apps/RagTime-3.1-Fr-4x800Ko.zip", 1350819 },
    { kCatProductivity, 1990, kArch68k, 60, "RagTime 3.17 (US English)", "A page layout and spreadsheet hybrid application originating in Germany, notable for its frame-based", "/apps/RagTime-317-US-English.sit", 973024 },
    { kCatProductivity, 1994, kArch68k, 60, "RagTime 4.1", "Integrated word processor, spreadsheet, and page layout application for the classic Mac OS.", "/apps/Ragtime4.1.sit", 11232358 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "Railroad Tycoon", "Business and strategy simulation of building railroads.", "/games/railroad_tycoon.sit", 1710976 },
    { kCatGames, 1990, kArch68k, 60, "Railroad Tycoon 1.01", "Classic railway-building and economic simulation from MicroProse.", "/games/railroadtycoon_1_01.zip", 9889362 },
    { kCatGames, 1998, kArchPPC, 75, "Railroad Tycoon II", "Sequel railroad simulation/strategy game with expanded scenarios and multiplayer.", "/games/Railroad_Tycoon_II.toast", 260372480 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "RAM Charger", "Dynamically manages application memory allocation.", "/apps/ram_charger_3.0.1.sit", 622866 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1997, kArchFat, 70, "RAM Charger 8.1", "A classic Mac OS memory management extension that dynamically adjusted application memory partitions.", "/apps/RAM_Charger_8.1_Installer.bin", 1223168 },
    { kCatSystemExt, 1994, kArchFat, 60, "RAM Doubler", "Connectix's popular memory-compression extension.", "/apps/Ram_Doubler_1.sit", 47236 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArch68k, 70, "RAM Doubler 1.5.1", "Connectix's popular utility for extending available RAM through software compression.", "/apps/RAMDoubler1.5.1.sit", 54131 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArch68k, 70, "RAM Doubler 1.6 Updater", "Updater for Connectix RAM Doubler, the popular extension that virtually expanded a classic Mac's available", "/apps/RAM_Doubler_1.6US_Updater.image_.zip", 143422 },
    { kCatSystemExt, 1996, kArchFat, 70, "RAM Doubler 1.6.2", "Connectix system extension that effectively doubled available memory through compression.", "/apps/ram_doubler_1.6.2.image_.sit", 118731 },
    { kCatSystemExt, 1996, kArch68k, 70, "RAM Doubler 2 (French)", "Connectix's extension that virtually expanded a classic Mac's available memory, this release localized for", "/apps/RAM_Doubleur_2_k.image_.sit", 223869 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "RamDisk 2.01", "Utility for creating a fast RAM-based virtual disk on classic Mac OS.", "/apps/RamDisk_v2.01.sit", 29184 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "RasterOps VideoVision", "Driver and control software for RasterOps' VideoVision video capture and editing card for the Macintosh.", "/apps/VideoVision.sit", 1987707 },
    { kCatGraphicsSound, 1991, kArch68k, 70, "Ray Dream Designer", "3D modeling and ray-tracing rendering application.", "/apps/Ray_Dream_Designer_3.sit", 5698229 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "Ray Dream Designer 2.0.6", "Ray Dream's approachable 3D modeling and rendering application.", "/apps/ray_dream_designer_206.zip", 2891386 },
    { kCatGraphicsSound, 1993, kArch68k, 60, "Ray Dream Designer 2.04", "Ray Dream's consumer 3D modeling and rendering application, predecessor to Ray Dream Studio and Bryce.", "/apps/ray_dream_designer_v204.sit", 2940646 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Ray Dream Studio 4.11", "An earlier version of MetaCreations' 3D modeling, rendering, and animation application for classic Mac OS.", "/apps/ray_dream_studio_v411.sit", 22705916 },
    { kCatGraphicsSound, 1997, kArchFat, 70, "Ray Dream Studio 5.0", "MetaCreations' 3D modeling, texturing and animation application.", "/apps/Ray_Dream_Studiotm_5.0_Install.sit", 25690690 },
    { kCatGraphicsSound, 1997, kArchPPC, 75, "Ray Dream Studio 5.5", "Ray Dream's 3D modeling, rendering, and animation suite.", "/apps/RayDreamStudio55_PlusPack.zip", 160710826 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 40, "Reader Rabbit", "The Learning Company's classic early-reading educational game series.", "/games/readerrabbit.sit", 1818869 },
    { kCatGames, 1988, kArch68k, 30, "Reader Rabbit 2", "Educational reading game for children from The Learning Company.", "/apps/ReaderRabbit2-v1-DC42.sit", 2245476 },
    { kCatGames, 1991, kArch68k, 60, "Reader Rabbit 2.1", "The Learning Company's reading and phonics edutainment game for children.", "/games/ReaderRabbit2.1.sit_.hqx", 354233 },
    { kCatGames, 1996, kArchFat, 70, "Reader Rabbit Kindergarten", "Educational reading and readiness game for kindergarten-age children.", "/games/reader_rabbit_kindergarten.iso_.sit", 283561587 },
    { kCatGames, 1999, kArchPPC, 75, "Reader Rabbit Toddler", "The Learning Company's early-learning game for toddlers, part of the Reader Rabbit series.", "/games/reader_rabbit_toddler.iso_.sit", 216347969 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 10, "Ready, Set, Go!", "Manhattan Graphics' pioneering Macintosh desktop-publishing and page-layout application.", "/apps/ReadySetGo.zip", 53257 },
    { kCatProductivity, 1987, kArch68k, 30, "Ready,Set,Go! 2.1", "Desktop publishing application from Manhattan Graphics/Letraset for page layout design.", "/apps/readysetgo_2_1.zip", 28108659 },
    { kCatProductivity, 1988, kArch68k, 40, "Ready,Set,Go! 3", "Update to the Ready,Set,Go! desktop publishing application with improved typography tools.", "/apps/readysetgo_3.zip", 26961820 },
    { kCatProductivity, 1988, kArch68k, 40, "Ready,Set,Go! 4.0", "Letraset's page-layout application, version 4.", "/apps/Letraset_ReadySetGo_4.0.zip", 955545 },
    { kCatProductivity, 1988, kArch68k, 40, "Ready,Set,Go! 4.5", "An early Macintosh desktop publishing and page layout application that predates PageMaker's dominance in", "/apps/readysetgo-45.sit", 532484 },
    { kCatProductivity, 1993, kArch68k, 60, "Ready,Set,Go! 6.0.2", "Desktop publishing and page layout software from Manhattan Graphics/Diwan.", "/apps/Ready_Set_Go_6.0.2.sit", 2242851 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArchPPC, 70, "REALbasic", "Visual BASIC-like rapid application development tool.", "/apps/REALbasic2.1.hqx", 3909106 },
    { kCatDevTools, 1998, kArch68k, 75, "REALbasic (Developer Release 1)", "Early pre-1.0 developer preview build of what became REALbasic.", "/apps/REALbasic_DR1r33_k.sit", 1292859 },
    { kCatDevTools, 1998, kArchPPC, 75, "REALbasic (F1 Release)", "Early release of the REALbasic rapid application development environment.", "/apps/REALbasic_F1.sit_.bin", 3772800 },
    { kCatDevTools, 1999, kArchPPC, 81, "REALbasic 2.0.2", "Early release of the REALbasic rapid-application-development environment for Macintosh.", "/apps/REALBasic_2.0.2_CD.sit", 52980944 },
    { kCatDevTools, 2001, kArchFat, 70, "REALbasic 3.x (Classic)", "A version of the REALbasic rapid application development environment targeting classic Mac OS.", "/apps/REALbasic_3.x_Classic.sit", 30023790 },
    { kCatDevTools, 2001, kArchFat, 75, "REALbasic 4.5.2", "Real Software's rapid application development environment using a BASIC-like language.", "/apps/REALbasic_4.5.2_Classic.sit", 8347581 },
    { kCatDevTools, 2002, kArchPPC, 91, "REALbasic 5.2.1", "Updated REALbasic release adding native Mac OS X support.", "/apps/REALbasic_5.2.1_OS_X.sit", 8706006 },
    { kCatDevTools, 2003, kArchFat, 70, "REALbasic 5.5 (Classic)", "A version of the REALbasic rapid application development environment targeting classic Mac OS as well as OS", "/apps/realbasic55classic.sit", 17217870 },
    { kCatDevTools, 2002, kArchPPC, 86, "REALbasic 5.5.2 (Classic)", "Rapid application development environment for building classic Mac OS applications with BASIC syntax.", "/apps/REALbasic555Classic_1.sit", 17865772 },
    { kCatDevTools, 2003, kArchPPC, 91, "REALbasic 5.5.3 Pro", "Professional edition of Real Software's REALbasic development environment.", "/apps/REALbasic_5.5.3_Pro.zip", 19863163 },
    { kCatDevTools, 1998, kArchFat, 70, "REALbasic Plugin SDK", "The software development kit for writing native plugins for the REALbasic (later Xojo) rapid application", "/apps/REALbasic_Plugin_SDK_0.sit", 145004 },
    /* -- Games -- */
    { kCatGames, 2000, kArchPPC, 86, "realMyst", "Cyan's real-time 3D remake of the original Myst adventure game.", "/games/realMYST_Installer.zip", 1572062 },
    { kCatGames, 1996, kArch68k, 70, "Realmz", "Deep fantasy role-playing game with scenario editor.", "/games/Realmz-25.sit", 2814348 },
    { kCatGames, 1995, kArchFat, 70, "Realmz 1.2.2", "Tile-based fantasy role-playing game engine and scenario from Fantasoft.", "/games/Realmz_1.2.2.sit", 2115382 },
    { kCatGames, 1997, kArchFat, 70, "Realmz 2.4", "Tile-based fantasy role-playing game engine from Fantasoft.", "/games/Realmz_2.4.sit", 2840796 },
    { kCatGames, 1996, kArchPPC, 70, "Realmz 3.0", "Fantasoft's tile-based fantasy role-playing game with scenario editor.", "/games/Realmz_3.0.sit", 3184148 },
    { kCatGames, 1999, kArchPPC, 75, "Realmz 4.1.2", "Later release of the Realmz fantasy role-playing game engine with expanded scenarios.", "/games/Realmz_4.1.2.sit", 5206842 },
    { kCatGames, 1998, kArchPPC, 75, "Realmz 6.1.2", "Fantasoft's tile-based fantasy role-playing game engine with scenario support.", "/games/Realmz_6.1.2.sit", 10415370 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArchFat, 0, "RealPlayer", "Streaming audio and video playback client.", "/apps/RealPlayerSP.dmg", 25375946 },
    { kCatInternet, 2000, kArchPPC, 80, "RealPlayer 8", "Streaming audio and video playback client from RealNetworks for Mac OS 8/9.", "/apps/rp8-setup-macos8-9.hqx", 7044016 },
    { kCatInternet, 1998, kArchPPC, 75, "RealPlayer G2", "RealNetworks' streaming audio and video playback software.", "/apps/RealPlayer_G2_Installer.sit", 3231866 },
    { kCatInternet, 1998, kArchFat, 70, "RealPlayer Plus 5.0", "RealNetworks' streaming audio and video player, an early way to watch and listen to internet media on", "/apps/realnetworks-realplayer-plus-5.0.iso", 139044864 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 70, "Rebound", "Automatically restarts the Mac after a system crash.", "/apps/Rebound2.0.sit", 1837930 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Red Baron", "Dynamix's World War I aerial combat flight simulation.", "/games/Red_Baron.img_.sit", 2221107 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1987, kArch68k, 10, "Red Ryder", "Pioneering shareware terminal emulator for the Mac.", "/apps/Red_Ryder_3.sit", 68806 },
    { kCatInternet, 1987, kArch68k, 20, "Red Ryder 4", "Pioneering telecommunications and terminal emulation software for the Macintosh.", "/apps/Red_Ryder_4.sit", 78683 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Redux 1.62", "Microseeds Publishing's shareware file backup and synchronization utility for classic Mac OS.", "/apps/Redux_1.62.hqx", 509290 },
    { kCatUtilities, 1994, kArchFat, 60, "Redux 2.6.2", "Microseeds Publishing's automated backup and file synchronization utility.", "/apps/Redux_2.6.2_fat.sit", 523072 },
    /* -- Productivity -- */
    { kCatProductivity, 1985, kArch68k, 20, "Reflex 1.01", "Early relational database program for the Macintosh known for its graphical query views.", "/apps/Reflex_1.01.sit", 304607 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "ResCompare", "Compares resource forks between two files.", "/apps/ResCompare-26.sit", 177120 },
    { kCatDevTools, 1994, kArch68k, 60, "ResEdit", "Apple's resource editor for modifying icons, dialogs, menus, and other Mac resources.", "/apps/ResEdit_Complete_disk.sit", 616800 },
    { kCatDevTools, 1985, kArch68k, 20, "ResEdit 1.01", "An early release of Apple's official resource editor for classic Mac OS application and system files.", "/apps/ResEdit101.sit", 75783 },
    { kCatDevTools, 1990, kArch68k, 60, "ResEdit 2.0b2", "A beta release of Apple's official resource editor for classic Mac OS application and system files.", "/apps/ResEdit_2.0B2.sit", 279081 },
    /* -- Featured -- */
    { kCatFeatured, 1992, kArch68k, 60, "ResEdit 2.1.3", "Apple's own resource editor - edit menus, dialogs, icons, and more.", "/apps/resedit_2.1.3.sea_.bin", 475904 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArchFat, 70, "ResEdit 3.0", "Apple's official resource editor for viewing and modifying resources inside classic Mac application and", "/apps/resedit_3.0.img_.sea_.bin", 743936 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "ResEdit 3.0d3", "Apple's resource editor for modifying Macintosh application resources and interfaces.", "/apps/ResEdittm_3.0d3.sit", 699824 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1999, kArchPPC, 81, "ResEditX 0.0.4", "Early Carbon-based reimagining of Apple's ResEdit resource editor.", "/apps/ResEditX_0.0.4.sit", 848217 },
    /* -- Productivity -- */
    { kCatProductivity, 1991, kArch68k, 70, "Resolve", "Claris's spreadsheet application.", "/apps/Claris_Resolve_1.1.sit", 2034667 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "Resorcerer 1.2.5", "Resource editor for classic Mac OS development, a rival to Apple's ResEdit.", "/apps/Resorcerer_1.2.5.sit_.Hqx", 1023246 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Resorcerer 2.0", "Mathemaesthetics' professional resource-editing application, a ResEdit alternative.", "/apps/Resorcerer_2.0_iso.zip", 9243275 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArch68k, 70, "Resorcerer 2.4.1", "A powerful commercial resource editor for classic Mac OS, a professional rival to Apple's free ResEdit.", "/apps/Resorcerer2.4.1CD.img_.sit_.hqx", 18803545 },
    { kCatDevTools, 1993, kArch68k, 80, "Resorcerer Demo", "Advanced resource editor, demo edition.", "/apps/Resorcerer_2.4.zip", 14022015 },
    /* -- Utilities -- */
    { kCatUtilities, 1989, kArch68k, 30, "Retrospect 1.3A", "Backup and archiving software from Dantz Development for the classic Mac OS.", "/apps/Dantz_Retrospect_1.3A_1989.zip", 1010534 },
    { kCatUtilities, 1992, kArch68k, 60, "Retrospect 2.1", "Dantz Development's backup and archiving software for Mac OS.", "/apps/Retrospect_2.1.mar", 3278080 },
    { kCatUtilities, 1996, kArchFat, 70, "Retrospect 4.0", "Dantz Development's industry-standard backup and archiving software for classic Mac OS.", "/apps/Retrospect_4.0.sit", 3500249 },
    { kCatUtilities, 2000, kArchFat, 81, "Retrospect 5", "A later version of Dantz Development's industry-standard backup and archiving software for Mac OS.", "/apps/Retrospect5CD.ZIP", 107085605 },
    { kCatUtilities, 1998, kArchPPC, 75, "Retrospect 5.0", "Backup and archiving software from Dantz Development.", "/apps/retrospect_5.0.toast_.sit", 106959664 },
    { kCatUtilities, 2001, kArchPPC, 81, "Retrospect 5.1.177", "Dantz Development's professional backup and archiving application for Macintosh.", "/apps/Retrospect_5.1.177.sit", 26279997 },
    { kCatUtilities, 2002, kArchPPC, 85, "Retrospect 6.1", "Backup and disaster recovery software update from Dantz Development.", "/apps/Retrospect_6.1.zip", 244701541 },
    { kCatUtilities, 1998, kArch68k, 75, "Retrospect Express 4.1a", "Consumer-oriented edition of Dantz Development's Retrospect backup application.", "/apps/Retrospect_Express_4.1A.toast_.sit", 183563603 },
    { kCatUtilities, 1999, kArchFat, 70, "Retrospect Express 5.0", "Dantz Development's consumer-oriented backup software, a lighter edition of Retrospect for classic Mac OS.", "/apps/retrospect_express_update_5.0.238.sit", 10801524 },
    /* -- Games -- */
    { kCatGames, 1993, kArchFat, 70, "Return to Zork (Demo)", "Playable demo of the graphical adventure sequel to the Infocom text classic Zork.", "/games/Return_to_Zork_demo.sit", 94418743 },
    /* -- Productivity -- */
    { kCatProductivity, 1997, kArchPPC, 70, "Reunion 4.0", "Leister Productions' genealogy and family tree software.", "/apps/Reunion_4.0_Mac_Demo.sit", 446569 },
    { kCatProductivity, 1996, kArchFat, 70, "Reunion 4.03", "Genealogy software from Leister Productions for building and charting family trees.", "/apps/Reunion_4.03.sit", 654191 },
    { kCatProductivity, 2002, kArchPPC, 86, "Reunion 6.02 Update", "Update for Leister Productions' Reunion, a widely used genealogy and family tree software for Mac OS.", "/apps/Reunion_6.02_Update.sit", 738635 },
    { kCatProductivity, 1999, kArchPPC, 75, "Reunion 7", "Genealogy and family tree charting software from Leister Productions.", "/apps/Reunion_7_CD.img", 6697902 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 60, "Rinaldi XCMD Collection", "A collection of external HyperCard commands (XCMDs) written by Ray Rinaldi extending HyperTalk's", "/apps/Rinaldi_XCMD_Collection.sit", 3962545 },
    /* -- Games -- */
    { kCatGames, 1996, kArchPPC, 70, "Ripper", "Take-Two Interactive's live-action interactive movie mystery game.", "/games/Ripper_4.toast_.sit", 651135598 },
    { kCatGames, 1990, kArch68k, 60, "Rise of the Dragon", "Dynamix's cyberpunk graphic adventure game.", "/games/rise_of_the_dragon.sit", 7997727 },
    { kCatGames, 1995, kArch68k, 0, "Rise of the Triad", "Fast-paced 90s first-person shooter.", "/games/Rise_of_the_Triad_RottExpr_Intel.dmg", 12584183 },
    { kCatGames, 1992, kArch68k, 60, "Risk", "Computer adaptation of the classic conquest board game.", "/games/Risk.sit", 62667 },
    { kCatGames, 1993, kArch68k, 0, "Risk 2.40", "Classic Macintosh computer adaptation of the Risk world-conquest board game.", "/games/Risk_2.40.sit", 99347 },
    { kCatGames, 1994, kArchFat, 70, "Risk 2.5c", "Shareware computer adaptation of the classic Risk world-conquest board game.", "/games/Risk2.5c.sit", 85263 },
    { kCatGames, 1997, kArch68k, 70, "Riven", "Cyan's acclaimed sequel to Myst, an atmospheric puzzle adventure game for classic Mac OS.", "/games/Riven2.toast_.sit", 496029728 },
    { kCatGames, 1997, kArchPPC, 75, "Riven: The Sequel to Myst", "Cyan's visually stunning sequel to Myst, exploring the collapsing age of Riven.", "/games/Riven4.toast_.sit", 416365144 },
    { kCatGames, 1991, kArch68k, 40, "RoboSport", "Turn-based robot combat strategy game from Maxis.", "/games/RoboSport_Disks_v1.0.sit", 1044736 },
    { kCatGames, 1994, kArchFat, 70, "RoboWar", "Programming-based combat simulation game where players script robot behavior for arena battles.", "/games/RoboWar.sit", 4019575 },
    { kCatGames, 1988, kArch68k, 40, "Rogue", "A classic dungeon-crawling roguelike game, ported to classic Mac OS.", "/games/rogue.sit", 124450 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "Rumpus 1.3c1", "An early version of Maxum Development's dedicated FTP server application for classic Mac OS.", "/apps/Rumpus1.3c1.sit", 781563 },
    { kCatInternet, 1999, kArchPPC, 75, "Rumpus 3.5.6", "FTP server software for hosting file transfer sites on classic Mac OS.", "/apps/Rumpus_3.5.6_0.sit", 2216052 },
    { kCatInternet, 1994, kArch68k, 70, "Rumpus Pro 1.1", "Maxum Development's dedicated FTP server application for hosting file transfer sites from a classic Mac.", "/apps/RumpusPro11.hqx", 766004 },
    { kCatInternet, 1996, kArchPPC, 70, "Rumpus Pro 2.0", "Maxum Development's FTP server software for Mac OS.", "/apps/Rumpus_Pro2.0.sit", 1315312 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 20, "S.D.I.", "Cinemaware's cinematic space-combat action game defending against a satellite laser assault.", "/games/SDI.img_.sit", 341948 },
    { kCatGames, 1995, kArch68k, 60, "Sam & Max Hit the Road", "LucasArts point-and-click adventure game starring the freelance police duo Sam & Max.", "/games/sam_and_max.zip", 115478664 },
    { kCatGames, 1993, kArch68k, 70, "Sam & Max Hit the Road (German)", "LucasArts' comedic buddy-cop adventure starring a dog detective and his hyperkinetic rabbit sidekick", "/games/Sam_and_Max_CD_Mac_ScummVM_data_file_deutsch.zip", 154569107 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1995, kArch68k, 60, "SampleCell Editor 2.03", "Editor software for Digidesign's SampleCell hardware sampler card.", "/apps/SampleCell_Installer_2.03.sit", 664356 },
    { kCatGraphicsSound, 1994, kArchFat, 70, "SampleCell Editor 3.0", "Editor software for Digidesign's SampleCell hardware sampler card.", "/apps/SampleCell_Editor_3.0.hqx", 1357386 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Sargon 4", "Fourth version of the Sargon chess program for Macintosh.", "/games/sargoniv_1_0.zip", 12869992 },
    { kCatGames, 1986, kArch68k, 30, "Sargon III", "Well-regarded Sargon chess-playing program, third Macintosh version.", "/games/Sargon3.img_.sit", 102544 },
    { kCatGames, 1993, kArchFat, 70, "Sargon V", "Chess-playing program from the long-running Sargon series.", "/games/sargonv_1_0.zip", 11463334 },
    { kCatGames, 1994, kArch68k, 60, "Scarab of Ra", "Egyptian-themed match tile puzzle game.", "/games/scarab_of_ra.sit", 91881 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Scenery Animator 1.0", "Landscape rendering software that generated realistic 3D terrain from elevation data.", "/apps/Scenery_Animator_1.0.sit", 811234 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArchPPC, 75, "Scilab 2.1a2", "Free numerical computation environment for scientific and engineering calculations.", "/apps/Scilab21a2.sit_.bin", 5590016 },
    /* -- Games -- */
    { kCatGames, 1993, kArch68k, 60, "Scrabble", "A classic Mac OS computer adaptation of the Scrabble word-tile board game.", "/games/Scrabble.zip", 12083809 },
    { kCatGames, 1993, kArch68k, 0, "Scrabble Deluxe", "Enhanced computer edition of the classic word game.", "/games/Deluxe_Scrabble_1.0_disks.hqx", 2531933 },
    { kCatGames, 1993, kArch68k, 0, "Scrabble for Macintosh", "Official computer version of the word game.", "/games/Scrabble.dmg", 14658980 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "ScrapIt Pro", "Enhanced clipboard/scrapbook management utility.", "/apps/ScrapItPro_3.3.sit", 100944 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1992, kArch68k, 60, "SCSI Accelerator", "Extension for improving SCSI transfer performance.", "/apps/scsiaccelerator7.0.cpt_.hqx", 16946 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "SCSI Director 3.0.4", "Casa Blanca Works' SCSI hard disk driver and formatting utility for classic Mac OS.", "/apps/SCSIDirector3.0.4.cpt__0.hqx", 554631 },
    { kCatUtilities, 1993, kArch68k, 60, "SCSI Probe 3.1", "Control panel utility that scans and mounts SCSI devices on the Mac.", "/apps/SCSIProbe3.1.sit", 9378 },
    { kCatUtilities, 1995, kArch68k, 60, "SCSI Probe 5.2", "Robert Polic's control panel for viewing and mounting SCSI devices.", "/apps/SCSIProbe_v52.hqx", 41291 },
    { kCatUtilities, 1994, kArch68k, 60, "SCSIProbe 4.3", "Inspect and mount SCSI devices from a control strip module.", "/apps/SCSIProbe_4.0.hqx", 15701 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 60, "Sculpt 3D 4.1", "Byte by Byte's early 3D modeling and rendering software for classic Mac OS.", "/apps/sculpt_3d_4.1.sit", 8435204 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 20, "Shadowgate", "ICOM Simulations' point-and-click fantasy adventure game.", "/games/shadowgate_1_0b1.zip", 4173278 },
    { kCatGames, 1988, kArch68k, 30, "Shanghai", "Activision's classic mahjong tile-matching puzzle game.", "/games/Shanghai_1.0.image_.sit", 255517 },
    { kCatGames, 1989, kArch68k, 60, "Shanghai II", "Activision's classic mahjong tile-matching solitaire game.", "/games/ShanghaiII_demo.sit", 401764 },
    { kCatGames, 1990, kArch68k, 60, "Shanghai II 1.05", "Tile-matching Mahjong solitaire game, sequel to the original Shanghai.", "/games/Shanghai_II_1_05.zip", 13976936 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 70, "SharePoints 3.5.1", "A control panel utility that provided fine-grained AppleShare file-sharing privilege management on classic", "/apps/SharePoints351.dmg_.gz", 1121144 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 75, "ShareWay IP 3.0.2", "Sustainable Softworks' utility enabling AppleShare file sharing over TCP/IP networks.", "/apps/ShareWay_IP_3_0_2_Personal_10_days.hqx", 1400116 },
    { kCatInternet, 1995, kArch68k, 70, "Shiva Remote Access Client", "Client software for Shiva's remote-access dial-up networking products.", "/apps/Shiva_Installation.img_.sit_.hqx", 533853 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2005, kArchPPC, 86, "Shockwave Player 10 (for Mac OS 9)", "A late release of Macromedia's Shockwave browser plug-in for playing Director content, built for classic Mac", "/apps/shockwave_player_10_for_os_9.sit", 4911836 },
    /* -- Games -- */
    { kCatGames, 2000, kArchPPC, 85, "Shogo: Mobile Armor Division", "Monolith Productions' anime-inspired first-person shooter with mech combat.", "/games/Shogo_Installer_English.sit", 256474292 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 70, "ShrinkWrap", "Creates and mounts self-mounting disk image files.", "/apps/ShrinkWraptm.hqx", 107709 },
    /* -- Utilities -- */
    { kCatUtilities, 1992, kArch68k, 60, "ShrinkWrap 1.0", "The original release of Aladdin Systems' utility for creating and mounting disk image files on classic Mac", "/apps/ShrinkWrap_1.0.bin", 47360 },
    { kCatUtilities, 1992, kArch68k, 60, "ShrinkWrap 1.3.1", "Aladdin Systems' utility for creating and mounting disk image files on classic Mac OS, a precursor to modern", "/apps/ShrinkWrap_1.3.1.hqx", 139553 },
    { kCatUtilities, 1994, kArch68k, 60, "ShrinkWrap 1.4.1", "Utility for creating and mounting disk image files on the classic Mac OS.", "/apps/ShrinkWrap_1.4.1.sit", 83785 },
    { kCatUtilities, 1996, kArchFat, 70, "ShrinkWrap 3.0 (Trial)", "A later release of Aladdin Systems' utility for creating and mounting disk image files on classic Mac OS.", "/apps/ShrinkWrap_3.0_Trial.sit", 455937 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 10, "Shufflepuck Cafe", "Air-hockey against a cast of alien characters.", "/games/shufflepuck_cafe.sit", 442325 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Sibelius 1.2", "Sibelius Software's professional music notation application.", "/apps/Sibelius_v1.2_w_SN.img_.sit", 11518162 },
    { kCatGraphicsSound, 2003, kArchPPC, 86, "Sibelius 3.1.5 Updater", "Update for Sibelius, the professional music notation and composition software, for classic Mac OS.", "/apps/Sibelius_3.1.5_Updater.zip", 4897382 },
    /* -- Games -- */
    { kCatGames, 1999, kArchPPC, 81, "Sid Meier's Alien Crossfire", "The expansion to Sid Meier's Alpha Centauri, ported to classic Mac OS.", "/games/SidMeiersAlienCrossfire.sit", 471304135 },
    { kCatGames, 1999, kArchPPC, 75, "Sid Meier's Alpha Centauri 1.5.2", "Firaxis's science-fiction turn-based strategy game, spiritual successor to Civilization.", "/games/Alpha_Centauri_1.5.2.sit-binhex_0.hqx", 2157069 },
    { kCatGames, 1991, kArch68k, 60, "Sid Meier's Civilization", "MicroProse's original turn-based empire-building strategy game.", "/games/civilization.zip", 10799121 },
    { kCatGames, 1997, kArchFat, 70, "Sid Meier's Civilization II (1997)", "Turn-based empire-building strategy game spanning history from antiquity to the space age.", "/games/civilization_ii_1997.sit", 24094542 },
    { kCatGames, 1996, kArchPPC, 70, "Sid Meier's Civilization II: Gold Edition", "MicroProse's turn-based empire-building strategy game with the Fantastic Worlds expansion.", "/games/Civ_II_Gold_Rel_PPC_no_depth_check_1.zip", 910321 },
    { kCatGames, 2001, kArchPPC, 85, "Sid Meier's Civilization III", "The Mac port of Firaxis's turn-based empire-building strategy game.", "/games/Civilization3MacRevA.dmg", 44704394 },
    { kCatGames, 1994, kArch68k, 70, "Sid Meier's Colonization", "Turn-based strategy game of exploring and colonizing the New World, from the makers of Civilization.", "/games/colonization.sit", 8774289 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Silverlining", "Third-party SCSI hard disk driver and formatting utility.", "/apps/silver_lining.sit", 147803 },
    { kCatUtilities, 1994, kArch68k, 70, "Silverlining Lite 1.0.5", "Lite edition of La Cie's Silverlining disk-formatting utility.", "/apps/Silverlining_Lite_1.0.5.bin", 74368 },
    { kCatUtilities, 1996, kArchFat, 70, "Silverlining Pro 6.5.9", "La Cie's hard drive formatting and diagnostic utility for Macintosh.", "/apps/Silverlining_Pro_v6.5.9.bin", 6208768 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 60, "Sim City Classic", "The original city-building simulation game.", "/games/SimCity1.0.sit", 205737 },
    { kCatGames, 1993, kArch68k, 60, "Sim Life Classic", "Genetic ecosystem simulation from Maxis.", "/games/SimLifeDemo.sit", 518419 },
    { kCatGames, 1992, kArch68k, 60, "SimAnt", "Simulate and control a colony of ants.", "/games/Simant.sit", 1157776 },
    { kCatGames, 1989, kArch68k, 30, "SimCity", "Maxis' original city-building simulation game.", "/games/Sim_City_original1989.sit", 477570 },
    { kCatGames, 1989, kArch68k, 40, "SimCity 1.1", "Maxis's landmark city-building simulation game, one of the defining titles of the early Macintosh era.", "/games/SimCity1.1May89.hqx", 1304451 },
    { kCatGames, 1989, kArch68k, 0, "SimCity 1.11", "An early 68k release of Maxis's pioneering city-building simulation.", "/games/Sim_City_1.11_Oct1989.sit", 477570 },
    { kCatGames, 1989, kArch68k, 60, "SimCity 1.3", "Maxis's original city-building simulation for classic Macintosh, version 1.3 floppy release.", "/games/SimCity_1.3.dsk_.hqx", 492423 },
    /* -- Featured -- */
    { kCatFeatured, 1994, kArchFat, 70, "SimCity 2000", "The acclaimed sequel with a new isometric view.", "/games/simcity2000.sit", 9196457 },
    /* -- Games -- */
    { kCatGames, 1995, kArchFat, 70, "SimCity 2000 (Special Edition)", "City-building simulation game adding underground infrastructure and isometric graphics.", "/games/SimCity_2K_Special_Edition_cdr.zip", 78908365 },
    { kCatGames, 1989, kArch68k, 40, "SimCity Classic 1.2", "Maxis's original city-building simulation game.", "/games/SimCity1.2C.hqx", 1013551 },
    { kCatGames, 1989, kArch68k, 60, "SimCity Classic 1.5", "Maxis's original city-building simulation game.", "/games/SimCity_Classic_1.5_CD.sit", 30895989 },
    { kCatGames, 1991, kArch68k, 60, "SimEarth", "Planetary ecosystem and evolution simulation.", "/games/SimEarth.zip", 717031 },
    { kCatGames, 1993, kArch68k, 70, "SimEarth 2.0", "Maxis planetary simulation game modeling the evolution of an entire world.", "/games/SimEarth_2.0.sit", 642723 },
    { kCatGames, 1993, kArch68k, 70, "SimFarm", "Maxis agricultural simulation game about running and growing a working farm.", "/games/SimFarm_CD.sit", 8391197 },
    { kCatGames, 1993, kArch68k, 60, "SimLife", "Maxis's evolutionary biology and ecosystem simulation game for classic Mac OS.", "/games/SimLife_1_0_1.zip", 5506309 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArchFat, 70, "SimpleText 1.3", "Apple's lightweight bundled text editor and document viewer for classic Mac OS.", "/apps/SimpleText_1.3.sit", 101639 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "SimTower", "Maxis's skyscraper-building and management simulation game for classic Mac OS.", "/games/SimTower_v1.1_dc42.zip", 1711650 },
    { kCatGames, 1994, kArchFat, 70, "SimTower 1.2", "Skyscraper building and management simulation game.", "/games/SimTower_1.2_Install.sit", 1777105 },
    { kCatGames, 1995, kArch68k, 60, "SimTown", "Maxis's simplified town-building simulation game for young players, on classic Mac OS.", "/games/SimTown_1.1.sit", 21901773 },
    { kCatGames, 1995, kArchPPC, 70, "SimTown 1.1", "Maxis's town-building simulation aimed at younger players.", "/games/SimTown_1.1_CD.sit", 217259061 },
    { kCatGames, 1990, kArch68k, 60, "Sky Shadow", "Side-scrolling helicopter combat game.", "/games/SkyShadow_demo.sit", 525569 },
    { kCatGames, 1984, kArch68k, 10, "SkyFox", "Electronic Arts' early futuristic fighter-jet combat simulation.", "/games/SkyFox.sit", 165039 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 0, "Smalltalk-80", "Classic Smalltalk programming environment for Macintosh.", "/apps/Lisa_Smalltalk_80.zip", 330073 },
    { kCatDevTools, 1988, kArch68k, 40, "Smalltalk/V 1.0", "Digitalk's implementation of the Smalltalk object-oriented programming environment.", "/apps/SmallTalk-V_1.0.sit", 634035 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 60, "Smart Alarms", "Simple reminder and alarm scheduling utility.", "/apps/smartalarms8_Folder.sit", 103352 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "Smartcom Fax", "Hayes' fax-modem communication and fax-sending application.", "/apps/Smartcom_FAX_Disk_1.img_.sit", 362216 },
    { kCatInternet, 1990, kArch68k, 60, "Smartcom II", "Hayes' terminal emulation and modem communications software for classic Mac OS.", "/apps/SmartcomII3.3A.sit", 351187 },
    { kCatInternet, 1990, kArch68k, 40, "Smartcom II 2.2B", "Telecommunications and terminal emulation software from Hayes.", "/apps/Smartcom_II_2.2B.sit_.hqx", 173732 },
    { kCatInternet, 1989, kArch68k, 40, "Smartcom II 3.3", "Hayes's terminal emulation and modem communications software.", "/apps/Smartcom_II_3.3B.sit", 504361 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1994, kArch68k, 70, "SmartScroll 3.7.1", "Alessandro Levi Montalcini's scrollbar-customization system extension for classic Macintosh.", "/apps/Smart-Scroll-3.7.1.sit", 167210 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1999, kArchPPC, 70, "Smile 1.8.8", "Satimage's integrated AppleScript development environment for Mac OS.", "/apps/Smile1.8.8US_0.sit", 1647594 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1999, kArchPPC, 75, "smIRCle 1.0.1a23", "PowerPC-native shareware IRC chat client alternative to Ircle.", "/apps/smIRCle-PPC_1.0.1a23.sit", 594352 },
    { kCatInternet, 1997, kArch68k, 70, "smIRCle 1.0.1a25", "Lightweight freeware IRC client alternative for classic Mac OS.", "/apps/smIRCle101a25.sit_.bin", 623104 },
    { kCatInternet, 1997, kArchPPC, 75, "Snak", "IRC chat client for the classic Mac OS.", "/apps/Snak.sit", 3262552 },
    { kCatInternet, 1997, kArch68k, 70, "Snak 1.31", "An earlier release of the popular Snak IRC (Internet Relay Chat) client for classic Mac OS.", "/apps/Snak131.sit", 538853 },
    { kCatInternet, 1998, kArch68k, 70, "Snak 3.21", "Earlier 68k release of the Snak IRC client.", "/apps/Snak_321_68K.sit_.hqx", 1390734 },
    { kCatInternet, 2000, kArchPPC, 86, "Snak 4.1", "A polished, widely used IRC (Internet Relay Chat) client for classic Mac OS.", "/apps/Snak41PPC_Carbon.sit", 877414 },
    { kCatInternet, 2000, kArchFat, 75, "Snak 4.1.0", "IRC chat client for the Macintosh.", "/apps/Snak410.sit", 2940652 },
    { kCatInternet, 2000, kArchPPC, 75, "Snak 4.11", "A popular shareware IRC client for Mac OS.", "/apps/Snak411.sit", 3098983 },
    { kCatInternet, 2001, kArchPPC, 86, "Snak 5.0.4", "A later release of the popular Snak IRC (Internet Relay Chat) client for Mac OS.", "/apps/Snak504.dmg", 2398076 },
    /* -- Utilities -- */
    { kCatUtilities, 1999, kArchFat, 70, "Snapz Pro 2", "Ambrosia Software's screen capture and screen recording utility for Mac OS.", "/apps/Snapz_Pro_2.sit", 1084965 },
    /* -- Games -- */
    { kCatGames, 2003, kArchPPC, 81, "Snes9x 1.29", "A widely used Super Nintendo (SNES) emulator ported to classic Mac OS.", "/apps/snes9x129.sit_.bin", 369792 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 70, "Snitch", "Displays and edits Finder file information.", "/apps/Snitch_2.1.sit", 258819 },
    { kCatUtilities, 1996, kArch68k, 70, "Snitch 1.0.1", "St. Clair Software's utility for viewing and editing a file's type, creator, and other Finder attributes.", "/apps/Snitch_1.0.1_1.sit", 25201 },
    { kCatUtilities, 1990, kArch68k, 60, "Snitch 2.0", "Utility for inspecting detailed file and volume information on classic Mac OS.", "/apps/Snitch_2.0.sit_.bin", 134272 },
    { kCatUtilities, 1992, kArch68k, 60, "Snitch 2.5", "Classic Macintosh file information and type/creator editing utility.", "/apps/Snitch_2.5_0.sit", 447054 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1992, kArch68k, 60, "SoftPC 3.1", "Insignia Solutions' earlier DOS/Windows 3.1 PC-emulation application, predecessor to SoftWindows.", "/apps/softpc31dos5win31.sit", 6971656 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 60, "SoftRAID 2.2.2", "Disk striping and RAID management utility for the classic Mac OS.", "/apps/softraid222u.sit", 293256 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "Software FPU 2.42", "An extension that emulates a floating-point unit in software for Macs lacking a hardware FPU, letting them", "/apps/SoftwareFPU_2.42.bin", 44800 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "SoftwareFPU", "Software floating-point emulation for FPU-less Macs.", "/apps/softwarefpu201a.sit", 46720 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1995, kArchPPC, 75, "SoftWindows 1.0.1 (PowerPC)", "PowerPC-native release of Insignia Solutions' SoftWindows PC-emulation application.", "/apps/SoftWindows_PPC_1.0.1.sit", 9025955 },
    { kCatSystemExt, 1994, kArch68k, 70, "SoftWindows 1.0.2 (68k)", "Insignia Solutions' PC-emulation application allowing Windows software to run on Macintosh.", "/apps/SoftWindows_68K_1.0.2_full.sit", 8662969 },
    /* -- Utilities -- */
    { kCatUtilities, 1995, kArch68k, 70, "SoftWindows 2 CD", "Insignia Solutions' software-based PC/Windows emulator for classic Mac OS.", "/apps/SoftWindowstm_2_CD.sit_.hqx", 36626121 },
    { kCatUtilities, 1996, kArchPPC, 70, "SoftWindows 95", "Insignia Solutions' PC hardware emulator for running Windows 95 on a Mac.", "/apps/SoftWindows_95.sit", 6046770 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1998, kArchPPC, 75, "SoftWindows 98", "Later SoftWindows release emulating Windows 98 on Power Macintosh.", "/apps/softwindows98.sit", 12567248 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Sokoban 2.2", "Macintosh version of the classic Japanese box-pushing puzzle game.", "/games/Sokoban_2.2.sit", 103993 },
    { kCatGames, 1992, kArch68k, 60, "Sokoban 2.4.2a", "Updated release of the box-pushing puzzle game Sokoban for Macintosh.", "/games/sokoban2.4.2a.hqx", 162205 },
    { kCatGames, 1990, kArch68k, 60, "Solarian II", "Vertical-scrolling space shooter with striking vector graphics.", "/games/Solarian_II_1.1.dmg", 860750 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchPPC, 75, "SonicWORX Studio 2.6", "Digital audio editing and processing workstation software.", "/apps/sonicWORXStudio26.sit", 20649212 },
    { kCatGraphicsSound, 1990, kArch68k, 40, "Sound Designer II", "Digital audio sampling and editing software from Digidesign.", "/apps/Sound_Designer_II.img__0.sit", 760163 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "Sound Designer II 2.6", "Digidesign's professional digital audio sample-editing application.", "/apps/Sound_Designer_II_2.6.bin", 440576 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "Sound Designer II 2.8.3", "Later version of Digidesign's professional digital sample-editing application.", "/apps/sounddesignerii_2.8.3k.sit", 5821634 },
    { kCatGraphicsSound, 1999, kArchFat, 70, "Sound Diver 3", "Emagic's MIDI patch librarian and editor software for controlling hardware synthesizers from a classic Mac.", "/apps/More_SoundDiver3.zip", 290860803 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "SoundApp", "Freeware sound file player and converter.", "/apps/SoundApp_2.3.1.sit", 653628 },
    { kCatGraphicsSound, 1997, kArchPPC, 70, "SoundApp 2.6.1", "Norman Franke's popular shareware sound file player and format converter.", "/apps/SoundAppPPC_2.6.1.hqx", 685431 },
    { kCatGraphicsSound, 1998, kArchFat, 70, "SoundApp 2.7.3", "Popular shareware utility for playing and converting many audio file formats on classic Mac OS.", "/apps/SoundApp2.7.3.sit_.bin", 1235968 },
    { kCatGraphicsSound, 1996, kArch68k, 60, "SoundApp 2.7.3 (German)", "Norman Franke's freeware sound file player and format converter for classic Mac OS, localized for German.", "/apps/SoundApp68K273DE.sit_.bin", 611328 },
    { kCatGraphicsSound, 1989, kArch68k, 40, "SoundEdit 1.1", "MacroMind's early digital sound recording and editing application for classic Mac OS, predecessor to", "/apps/SoundEdit1.1.sit", 591459 },
    { kCatGraphicsSound, 1995, kArch68k, 70, "SoundEdit 16 + Deck II", "Macromedia bundle pairing the SoundEdit 16 waveform editor with the Deck II multitrack recorder.", "/apps/SoundEdit_16_Plus_Deck_II.zip", 441908626 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "SoundEdit 16 1.0.1", "Digital audio editing application from Macromedia for recording and processing sound.", "/apps/SoundEdit_16_1.0.1.sit", 2799731 },
    { kCatGraphicsSound, 1993, kArch68k, 70, "SoundEdit 16 Demo", "Digital audio editing and effects, demo edition.", "/apps/soundedit16.sit", 4657648 },
    { kCatGraphicsSound, 1995, kArchFat, 70, "SoundEdit 16 v1.0.1", "Digital audio recording and editing software from Macromedia.", "/apps/SoundEdit16_v1.0.1_CD.sit", 277340114 },
    { kCatGraphicsSound, 1995, kArchFat, 70, "SoundEdit 16 v2", "Macromedia's digital audio recording and editing application.", "/apps/SoundEdittm16_version_2.img_.sit", 421977361 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "SoundEdit 2.0.1", "Macromedia's digital audio waveform editor.", "/apps/SoundEdit_2.0.1.sea_.bin", 162944 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "SoundEdit 2.0.5", "Farallon's easy-to-use digital sound editing application for Macintosh.", "/apps/SoundEdit_2.0.5.dsk", 838484 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "SoundEdit Pro 1.0.5", "Farallon's digital sound recording and editing application for Macintosh.", "/apps/SoundEditProv1.0.5.sit", 493223 },
    { kCatGraphicsSound, 1998, kArch68k, 70, "SoundHack 0.66", "Experimental digital audio signal processing tool used by electronic musicians.", "/apps/SoundHack.66.sit", 93568 },
    { kCatGraphicsSound, 1998, kArchPPC, 75, "SoundHack 0.888", "Experimental digital sound processing and spectral manipulation software.", "/apps/SoundHack_0.888_PPC.sit_.bin", 252928 },
    { kCatGraphicsSound, 2000, kArchPPC, 81, "SoundJam MP", "Casady & Greene's popular MP3 player and encoder for Mac OS, later acquired by Apple to become the basis of", "/apps/SoundJam_MP_CD.sit", 508251599 },
    { kCatGraphicsSound, 1992, kArch68k, 70, "SoundMachine 2.0.1", "Plays and converts sound files in many classic formats.", "/apps/soundmachine271.sit", 320388 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 0, "SoundMaster 1.6.1", "Assigns custom sounds to system events.", "/apps/SoundMaster1.6.5.sit", 31825 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 60, "Space Ace II: Borf's Revenge", "Interactive animated laserdisc-style arcade action game sequel from ReadySoft.", "/games/Space_Ace_II_Folder.sit", 2928886 },
    { kCatGames, 1988, kArch68k, 0, "Space Quest I", "Sierra On-Line's sci-fi graphic adventure, early Macintosh port.", "/games/space_quest_1.sit", 808508 },
    { kCatGames, 1990, kArch68k, 40, "Space Quest II", "Sierra science-fiction graphic adventure game.", "/games/space_quest_2.sit", 477972 },
    { kCatGames, 1989, kArch68k, 40, "Space Quest III", "Sierra's comedic science-fiction graphic adventure starring janitor-turned-hero Roger Wilco.", "/games/SQ3.img_.sit", 2620027 },
    { kCatGames, 1991, kArch68k, 60, "Space Quest IV: Roger Wilco and the Time", "Sierra's science-fiction comedy graphic adventure game.", "/games/spacequestiv.zip", 36108930 },
    { kCatGames, 1990, kArch68k, 60, "Spaceward Ho!", "Turn-based galactic conquest strategy game.", "/games/Spaceward_Ho_v2.01.zip", 711805 },
    { kCatGames, 1994, kArch68k, 60, "Spaceward Ho! 3.0", "Delta Tao's turn-based galactic conquest strategy game.", "/games/Spaceward_Ho_3.0_Color.img_.zip", 309113 },
    { kCatGames, 1994, kArchFat, 70, "Spaceward Ho! 3.0 (Demo)", "Demo of Delta Tao's minimalist turn-based space conquest strategy game.", "/games/SpacewardHo_v3.0Demo.sit", 401674 },
    { kCatGames, 1990, kArch68k, 60, "Spaceward Ho! 3.0.1", "Delta Tao's turn-based space conquest strategy game.", "/games/SpacewardHo301_0.img", 1048576 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1998, kArchPPC, 75, "Spark LE 2.0", "Digital audio recording and editing software from TC Works.", "/apps/SPARK_LE_2.0.sit", 22107942 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Sparkle", "Freeware MPEG movie player for classic Mac OS.", "/apps/Sparkle245.sit", 763750 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "Sparkle 2.2.0", "Popular freeware MPEG player and video converter for classic Mac OS.", "/apps/Sparkle220_folder.sit", 846368 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "Spectre", "3D networked tank battles rendered in QuickDraw 3D.", "/games/Spectre_1.1.sit", 784179 },
    { kCatGames, 1991, kArch68k, 60, "Spectre 1.0", "Velocity Development's 3D networked tank combat game.", "/games/Spectre_1.0.mar", 3500288 },
    { kCatGames, 1993, kArch68k, 60, "Spectre Supreme", "Enhanced edition of the 3D tank battle game Spectre.", "/games/spectre_supreme.zip", 9046645 },
    { kCatGames, 1994, kArchFat, 70, "Spectre VR 1.0.5", "Sequel to Spectre with virtual-reality-style texture-mapped 3D tank combat.", "/games/SpectreVR1.0.5.sit_.bin", 11352704 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 70, "Specular Collage", "Photo compositing and collage application.", "/apps/Specular_Collage_2.0.2.sit", 800283 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Specular Infini-D 3.1", "3D modeling, rendering and animation software from Specular International.", "/apps/Infini-D_3.1.zip", 252884629 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 0, "Speed Copy", "Accelerates Finder file-copy operations.", "/apps/Speed_Copy_8.1D_Server.sit", 54781 },
    { kCatUtilities, 1995, kArchFat, 70, "Speed Doubler", "Connectix's system-acceleration utility speeding up disk access and 68k emulation on PowerPC Macs.", "/apps/speed_doubler-image.zip", 161574 },
    { kCatUtilities, 1995, kArchPPC, 70, "Speed Doubler 1.1", "Utility from Connectix that accelerated file copying and 68k emulation on Power Macs.", "/apps/SpeedDoubler1.1.sit", 57122 },
    { kCatUtilities, 1995, kArchFat, 70, "Speed Doubler 1.3.1 Update", "Update for Connectix Speed Doubler, which accelerated emulated 68k code and Finder file copies on Power Macs.", "/apps/Speed_Doubler_1.3.1_Update.sit", 182418 },
    { kCatUtilities, 1997, kArchFat, 70, "Speed Doubler 2.0", "Connectix's utility for accelerating file copies and emulated code execution on classic Mac OS.", "/apps/speed_doubler_2.0.x.sit", 673475 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArchFat, 70, "Speed Doubler 8", "Accelerates file copies and emulated code on PowerPC Macs.", "/apps/speed_doubler_8_0.sit", 1834562 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "SpeedyFinder7 1.5.4", "Utility for speeding up and customizing Finder window behavior.", "/apps/SpeedyFinder71.5.4.sit", 33776 },
    { kCatUtilities, 1994, kArch68k, 70, "SpeedyFinder7 3.5", "Collection of Finder speed and productivity hacks.", "/apps/speedyfinder7.sit", 322598 },
    /* -- Games -- */
    { kCatGames, 1985, kArch68k, 20, "Spellbreaker", "Infocom text adventure concluding the Enchanter trilogy as magic itself begins to fail.", "/games/3_Spellbreaker_ZIP_Z-code_0.sit", 515376 },
    /* -- Productivity -- */
    { kCatProductivity, 1994, kArch68k, 60, "Spellcatcher", "Spell-checking and word-completion utility for the classic Mac OS from Casady & Greene.", "/apps/spellcatcher.sit", 2777334 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 60, "Spelunx", "Cyan's whimsical interactive exploration game for children, made by the creators of Myst before Myst.", "/games/Spelunx_Japan.sit", 22021027 },
    { kCatGames, 1991, kArch68k, 60, "Spelunx and the Caves of Mr. Seudo", "Exploratory children's adventure game from Cyan, creators of Myst.", "/games/Spelunx_bw.img_.sit", 2842339 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchPPC, 75, "Spring Cleaning 2.0", "Aladdin's utility for locating and removing unneeded files to reclaim disk space.", "/apps/Spring_Cleaning_2.0.sit", 1684460 },
    /* -- Productivity -- */
    { kCatProductivity, 1995, kArch68k, 70, "SPSS 6.1.1", "Statistical analysis package for the classic Mac OS.", "/apps/SPSS_6.1.1.sit", 11923754 },
    /* -- Games -- */
    { kCatGames, 1997, kArch68k, 70, "Spy Fox 1: Dry Cereal", "Humongous Entertainment's spy-themed point-and-click adventure for kids.", "/games/SpyFox1_2001.sit", 187449424 },
    { kCatGames, 1999, kArchPPC, 75, "Spy Fox 2: Some Assembly Required (German)", "Sequel Spy Fox adventure for kids; German-language Macintosh release.", "/games/SPYFox2_German.sit", 178307214 },
    { kCatGames, 1993, kArch68k, 60, "Spy Hunter", "Classic Mac port of the Bally Midway top-down vehicular combat arcade game.", "/games/SpyHunter1.0.1b1.sit", 7825031 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Spyglass Dicer 2.01", "Spyglass Inc's scientific and technical image processing and visualization application for classic Mac OS.", "/apps/Spyglass_Dicer_2.01.sit", 1224320 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Stacker for Macintosh 1.0", "Real-time disk compression utility ported from the DOS Stacker product.", "/apps/Stacker_1.0.hqx", 2609550 },
    /* -- Games -- */
    { kCatGames, 0, kArch68k, 0, "Star Trek", "An early Macintosh adaptation of the classic text-based Star Trek game.", "/games/Star_Trek.img", 409600 },
    { kCatGames, 1992, kArch68k, 60, "Star Trek: 25th Anniversary", "Point-and-click adventure based on the original series.", "/games/star_trek_25th_anniversary.sit", 5895842 },
    { kCatGames, 1995, kArch68k, 70, "Star Trek: Judgment Rites", "Interplay's episodic graphic adventure based on the original Star Trek series.", "/games/StarTrekJudgment.sit", 639170656 },
    { kCatGames, 1995, kArch68k, 70, "Star Trek: The Next Generation - A Final Unity", "Spectrum HoloByte's graphic adventure starring the TNG cast, with full character voice acting.", "/games/startrektngfinalunity.toast_.2.sit", 278859976 },
    { kCatGames, 1999, kArchPPC, 81, "Star Wars Episode I: Racer", "LucasArts' high-speed podracing game based on The Phantom Menace, for classic Mac OS.", "/games/Star_Wars_Pod_Racer.sit", 379162336 },
    { kCatGames, 1996, kArch68k, 70, "Star Wars: Dark Forces", "LucasArts' first-person shooter starring mercenary Kyle Katarn, Macintosh port.", "/games/DarkForces1.2.sit_.bin", 32545280 },
    { kCatGames, 1998, kArchPPC, 75, "Star Wars: DroidWorks (Demo)", "LucasLearning's Star Wars-themed engineering and robotics edutainment title.", "/games/Star_Wars_DroidWorks_Demo.sit", 28325164 },
    { kCatGames, 2001, kArchPPC, 85, "Star Wars: Galactic Battlegrounds", "LucasArts's Age of Empires II-engine real-time strategy game set in the Star Wars universe.", "/games/Star_Wars_GalacticBattlegrounds.sit", 726353295 },
    { kCatGames, 1993, kArch68k, 60, "Star Wars: Rebel Assault", "LucasArts' cinematic rail-shooter adventure game set in the Star Wars universe, ported to classic Mac OS.", "/games/Rebel_Assault.toast_.zip", 403087257 },
    { kCatGames, 1995, kArch68k, 70, "Star Wars: Rebel Assault II (Japanese)", "LucasArts' cinematic Star Wars action game with full-motion video sequences; Japanese-language CD release.", "/games/RebelAssaultII_JP_CD1.sit", 392378045 },
    { kCatGames, 1994, kArch68k, 60, "Star Wars: TIE Fighter", "LucasArts space combat simulation putting players in the cockpit of Imperial starfighters.", "/games/TIE-Fighter.sit", 287113744 },
    { kCatGames, 1994, kArch68k, 70, "Star Wars: X-Wing", "LucasArts space-combat simulator putting players in the cockpit of a Rebel Alliance starfighter, Macintosh", "/games/X-Wing_1.0.sit", 332597664 },
    { kCatGames, 1994, kArch68k, 70, "Star Wars: X-Wing (Demo)", "Demo of LucasArts' space combat simulator putting players in the cockpit of a Rebel starfighter.", "/games/xwingdemo.sea_.hqx", 8805322 },
    { kCatGames, 1998, kArchPPC, 70, "StarCraft", "Blizzard's classic science-fiction real-time strategy game, Macintosh version 1.15.", "/games/StarCraft_v115_Mac.sit", 12451835 },
    { kCatGames, 1998, kArchFat, 70, "StarCraft (Demo)", "Demo of Blizzard's landmark science-fiction real-time strategy game.", "/games/StarCraft_1.0.5_Demo.sit_.hqx", 41488191 },
    { kCatGames, 1998, kArch68k, 70, "StarCraft 1.11", "Blizzard's landmark real-time strategy game, the original classic Mac OS release.", "/games/StarCraft_v111_Mac.sit", 8450632 },
    { kCatGames, 1998, kArchPPC, 75, "StarCraft 1.15.1 (Patch)", "Patch updater for Blizzard's sci-fi real-time strategy game StarCraft on Macintosh; requires the original CD.", "/games/StarCraft_v1151_Mac.sit", 12452622 },
    { kCatGames, 1998, kArchPPC, 75, "StarCraft: Brood War", "The expansion pack for Blizzard's science-fiction real-time strategy game StarCraft.", "/games/Brood_War_v114_OSX.dmg", 29254248 },
    { kCatGames, 1998, kArchPPC, 81, "StarCraft: Brood War (Classic Mac)", "Blizzard's expansion to StarCraft, the landmark real-time strategy game, for classic Mac OS.", "/games/Brood_War_v115_Mac.sit", 27765435 },
    { kCatGames, 1998, kArchPPC, 75, "StarCraft: Brood War 1.11b", "Expansion pack for Blizzard's real-time strategy game StarCraft.", "/games/Brood_War_v111b_Mac.sit", 7657383 },
    { kCatGames, 1988, kArch68k, 30, "Starflight", "Binary Systems' open-ended space exploration and trading role-playing game.", "/games/starflightone_archive.zip", 15111177 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "Startup Disk", "Apple's own control panel for choosing the boot volume.", "/apps/IIe_Startup_Disk.image_.sit", 811161 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 20, "Stationfall", "Infocom's comedic science-fiction sequel to Planetfall.", "/games/stationfall.sit", 107208 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "StatView", "Statistical analysis and graphing application.", "/apps/STATVIEW.zip", 43006461 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "StatView 4", "Abacus Concepts' statistical analysis and graphing application widely used in scientific research.", "/apps/StatView_4.sit", 6808692 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "StatView II", "Abacus Concepts' statistical analysis and graphing application.", "/apps/StatView2_SEGraphics.zip", 6431348 },
    { kCatProductivity, 1990, kArch68k, 40, "StatView SE", "Statistical analysis software from Abacus Concepts for the classic Mac OS.", "/apps/StatviewSE.img_.sit", 320848 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 60, "Steinberg Cubase 2.51", "MIDI sequencing and music production software from Steinberg.", "/apps/Cubase-251r3-folder.sit", 1180358 },
    { kCatGraphicsSound, 1999, kArchPPC, 80, "Steinberg Cubase VST 4.1", "MIDI and digital audio sequencing software with virtual studio technology.", "/apps/CubaseVST_Standard_41r2.sea_.hqx", 10748781 },
    { kCatGraphicsSound, 2001, kArchPPC, 84, "Steinberg Nuendo 1.52", "Professional multitrack audio production and post-production software from Steinberg.", "/apps/steinberg_nuendo_1.52.sit", 30171824 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 40, "Stellar 7", "First-person tank combat game from Dynamix.", "/games/Stellar7.img_.sit", 992470 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1988, kArch68k, 10, "Stepping Out II", "Extends the desktop beyond the physical screen size.", "/apps/Stepping_Out_II.sit_.hqx", 41595 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 0, "Stone Age", "Prehistoric-themed puzzle-platform game.", "/apps/The_Flintstones_image.sit", 1226964 },
    { kCatGames, 1994, kArch68k, 60, "Storybook Weaver", "MECC's creative writing and illustration program for children, letting kids build illustrated stories.", "/games/Storybook_Weaver_1.1.sit", 4973668 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 2003, kArchPPC, 86, "Strata 3D Pro 3.8.1", "Strata's professional 3D modeling, rendering, and animation package for Mac OS.", "/apps/Strata3DPro3.8.1U.sit", 3133005 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "Strata StudioPro 2.0.1", "Strata's professional 3D modeling, rendering, and animation package for the classic Mac.", "/apps/StudioPro201CD.iso", 488906752 },
    { kCatGraphicsSound, 1994, kArch68k, 70, "StrataStudioPro 1.5.1", "Earlier release of Strata's 3D modeling and rendering application.", "/apps/Strata_Studio_Pro_1.5.1.sit", 10568001 },
    { kCatGraphicsSound, 1996, kArchPPC, 70, "StrataStudioPro 2.5.3", "Strata's professional 3D modeling, rendering, and animation application.", "/apps/Strata_StudioPro_Update_2.5.3.bin", 24480512 },
    { kCatGraphicsSound, 1991, kArch68k, 70, "StrataVision 3D", "Early 3D modeling and ray-tracing application.", "/apps/StrataVision3d26.sit", 5873014 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "StrataVision 3D 1.4.1", "Updated version of Strata's 3D modeling and rendering application.", "/apps/StrataVision3d_1.4.1.sit", 434019 },
    { kCatGraphicsSound, 1996, kArchPPC, 70, "StrataVision Studio Pro 2.5", "3D modeling, rendering, and animation software from Strata Inc.", "/apps/Strata_Studio_Pro_2.5.sit", 76618620 },
    /* -- Games -- */
    { kCatGames, 1995, kArchFat, 10, "Strategic Conquest", "Turn-based war strategy game, a Mac classic.", "/games/StrategicConquest.sit", 347900 },
    { kCatGames, 1993, kArch68k, 60, "Strategic Conquest 3.01", "Turn-based hex-map war and empire strategy game, a Macintosh shareware classic.", "/games/Strategic_Conquest_3.01_0.sit", 256809 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1986, kArch68k, 30, "Studio/8 1.0", "Early color paint program for the Macintosh II published by Electronic Arts.", "/apps/Studio8_1.0.sea_.hqx", 2062728 },
    /* -- Utilities -- */
    { kCatUtilities, 1988, kArch68k, 0, "StuffIt 1.31", "Raymond Lau's original classic Macintosh file compression and archiving application.", "/apps/StuffIt_1.31.sit_.hqx", 50773 },
    { kCatUtilities, 1989, kArch68k, 40, "StuffIt 1.5d1", "Early release of Aladdin's StuffIt file compression and archiving program.", "/apps/StuffIt_1.5d1.sit", 51754 },
    { kCatUtilities, 1989, kArch68k, 40, "StuffIt Classic 1.5.1", "Early version of Raymond Lau's StuffIt compression utility for the Macintosh.", "/apps/stuffit_1.5.1.pit_.bin", 285824 },
    { kCatUtilities, 1995, kArchFat, 0, "StuffIt Deluxe", "The full commercial StuffIt archiving application.", "/apps/StuffItDeluxe8.sit", 13732322 },
    { kCatUtilities, 1990, kArch68k, 50, "StuffIt Deluxe 2.0", "Early release of Aladdin's StuffIt Deluxe file compression and archiving suite.", "/apps/stuffit-deluxe-v2.sit", 1300054 },
    { kCatUtilities, 1994, kArch68k, 60, "StuffIt Deluxe 3.0.7", "Earlier release of Aladdin's StuffIt compression suite.", "/apps/stuffitdeluxe307_dsk.zip", 1454325 },
    { kCatUtilities, 1993, kArch68k, 60, "StuffIt Deluxe 3.5.1", "Aladdin Systems' full-featured file compression and archiving application.", "/apps/stuffit-deluxe-351-sea.bin", 1576704 },
    { kCatUtilities, 1995, kArch68k, 70, "StuffIt Deluxe 4.0.1", "Updated release of Aladdin Systems' StuffIt Deluxe compression application.", "/apps/STUFFITDLX401.SIT", 2995288 },
    { kCatUtilities, 1994, kArch68k, 60, "Stuffit Deluxe 4.01", "An earlier version of Aladdin Systems' complete compression and archive management suite for classic Mac OS.", "/apps/stuffitdeluxe-401.sit", 2988520 },
    { kCatUtilities, 1995, kArch68k, 70, "Stuffit Deluxe 4.5", "Aladdin Systems' complete compression and archive management suite for classic Mac OS.", "/apps/STUFFITDLX45.SIT", 3816530 },
    { kCatUtilities, 1997, kArchFat, 70, "StuffIt Deluxe 5.0", "Aladdin's premier file compression and archive management suite.", "/apps/StuffIt_Deluxetm_5.0.sea", 14464273 },
    { kCatUtilities, 1998, kArchPPC, 75, "StuffIt Deluxe 5.01", "Full-featured file compression and archive management suite from Aladdin Systems.", "/apps/STUFFIT_DLX_SS_501.iso_.zip", 163737870 },
    { kCatUtilities, 1997, kArchFat, 75, "StuffIt Deluxe 5.1.5", "Later release of Aladdin Systems' StuffIt Deluxe compression application.", "/apps/STUFFITDLX515.SIT", 14480776 },
    { kCatUtilities, 1998, kArchPPC, 75, "StuffIt Deluxe 5.5.1", "File compression and archive management suite from Aladdin Systems.", "/apps/stuffitdeluxe-551.sit", 7896920 },
    { kCatUtilities, 1999, kArchFat, 70, "StuffIt Deluxe 6.0.1", "Aladdin Systems' full-featured file compression and archiving suite.", "/apps/STUFFITDLX601.SIT", 16176610 },
    { kCatUtilities, 2001, kArchPPC, 81, "StuffIt Deluxe 7.0.3", "Aladdin Systems' full-featured file compression and archiving application, version 7.", "/apps/stuffitdeluxe_7_0_3.zip", 13108365 },
    /* -- Featured -- */
    { kCatFeatured, 1994, kArch68k, 70, "StuffIt Expander 4.0.1", "Decompresses .sit, .hqx, and .zip archives. Essential utility.", "/apps/stuffit_expander_4.0.2.sea_.bin", 138368 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchFat, 75, "StuffIt Expander 5.5", "Aladdin Systems' free, widely installed archive-decompression utility.", "/apps/stuffit_expander_5.5.bin", 824704 },
    { kCatUtilities, 1990, kArch68k, 60, "StuffIt Lite 3.0", "Aladdin Systems' entry-level compression utility, a scaled-down StuffIt Deluxe.", "/apps/StuffIt-Lite-3.0-install.sit", 573439 },
    { kCatUtilities, 1993, kArch68k, 60, "StuffIt Lite 3.0.5", "Aladdin Systems' streamlined file compression and archiving application.", "/apps/StuffItLite3.0.5.sit", 363293 },
    { kCatUtilities, 1994, kArch68k, 60, "StuffIt Lite 3.0.7", "Simplified, lower-cost version of Aladdin's StuffIt compression software.", "/apps/StuffIt_Lite_3.0.7.hqx", 730376 },
    { kCatUtilities, 1993, kArch68k, 60, "StuffIt Lite 3.5", "An earlier release of Aladdin Systems' lighter-weight StuffIt compression and archiving software for classic", "/apps/stuffitlite3.5.sea_.hqx", 841823 },
    { kCatUtilities, 1993, kArch68k, 60, "StuffIt Lite 3.6", "Compress and archive files, freeware sibling of StuffIt Deluxe.", "/apps/stuffitlite36.img", 673792 },
    { kCatUtilities, 2002, kArchPPC, 86, "StuffIt Lite 6.5.1", "A lighter-weight edition of Aladdin Systems' StuffIt compression and archiving software for Mac OS.", "/apps/StuffIt_Lite_6.5.1_Install.sit", 6332543 },
    /* -- Games -- */
    { kCatGames, 1992, kArch68k, 10, "Stunt Copter", "Side-scrolling helicopter stunt-flying game.", "/games/StuntCopter1.2.sit", 15136 },
    { kCatGames, 1990, kArch68k, 60, "Stunt Copter 1.0", "Shareware helicopter arcade action game for classic Macintosh.", "/games/StuntCopter_1.0.sit", 11861 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1991, kArch68k, 60, "StyleWriter Installer 1.2", "Apple printer driver and installer software for the StyleWriter inkjet printer line.", "/apps/StyleWriterInstallation1.2.sit", 1853270 },
    /* -- Utilities -- */
    { kCatUtilities, 1988, kArch68k, 70, "Suitcase", "Font and desk accessory management utility.", "/apps/Suitcasetm_8.sit", 2847311 },
    { kCatUtilities, 1992, kArch68k, 60, "Suitcase 2.1.2", "Font and sound management utility from Fifth Generation Systems/Symantec.", "/apps/Suitcase_2.1.2_Updater.mar", 62464 },
    { kCatUtilities, 1991, kArch68k, 60, "Suitcase 2.1.3", "Fifth Generation/Symantec's font and desk accessory management utility.", "/apps/Suitcase_2.1.3_Updater.mar", 63360 },
    { kCatUtilities, 1989, kArch68k, 40, "Suitcase 2.1.4", "Original Suitcase font and desk-accessory management utility, predecessor to Suitcase II.", "/apps/suitcasetm_2.1.4.image_.sit", 350232 },
    { kCatUtilities, 1990, kArch68k, 60, "Suitcase 2.1.4 Updater", "Update for Fifth Generation/Symantec's widely used font and desk accessory management utility for classic", "/apps/Suitcase_2.1.4p3Update.mar", 62976 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1989, kArch68k, 40, "Suitcase 2.23", "Early release of the classic font and desk accessory manager from Fifth Generation Systems.", "/apps/suitcase_2.23.sit", 48487 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "Suitcase 3", "Font and desk accessory management utility from Alsoft/Symantec.", "/apps/Suitcase_3_with_Update.hqx", 2431595 },
    { kCatUtilities, 1990, kArch68k, 40, "Suitcase II", "Font and desk accessory management utility from Fifth Generation Systems.", "/apps/suitcasetm_ii_-image.zip", 297768 },
    { kCatUtilities, 1991, kArch68k, 60, "Suitcase II 1.2.5", "Earlier point release of the Suitcase II font management utility.", "/apps/SuitcaseII1.2.5.sit", 25158 },
    { kCatUtilities, 1992, kArch68k, 60, "Suitcase II 1.2.8", "Fifth Generation Systems' popular font and DA management utility.", "/apps/SuitcasetmII_1.2.8_.img_.sit_.hqx", 576212 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "Super ATM 3.5", "Adobe's Adobe Type Manager companion extension that improves on-screen font substitution and PostScript font", "/apps/Super_ATM3.5.sit", 1920902 },
    /* -- Utilities -- */
    { kCatUtilities, 1988, kArch68k, 40, "Super ResEdit 2.4", "Enhanced third-party resource editor building on Apple's ResEdit.", "/apps/super_resedit_2.4.sea_.bin", 528512 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 40, "Super Tetris", "Enhanced version of Tetris for Macintosh from Spectrum Holobyte.", "/games/SuperTetris_floppy.zip", 9473393 },
    /* -- Productivity -- */
    { kCatProductivity, 1989, kArch68k, 0, "SuperCard", "HyperCard-like multimedia authoring environment.", "/apps/SuperCard1.5.sit", 2979806 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1998, kArch68k, 70, "SuperCard 3.52", "An earlier release of the HyperCard-like multimedia and application development environment for classic Mac", "/apps/supercard_352.sit", 7297615 },
    { kCatDevTools, 1999, kArchPPC, 75, "SuperCard 4.5.2", "HyperCard-inspired multimedia authoring and scripting development environment.", "/apps/SuperCard_452_Dev.sit", 20209080 },
    { kCatDevTools, 2004, kArchPPC, 86, "SuperCard 4.52 Developer Edition", "The developer edition of SuperCard, a HyperCard-like multimedia and application development environment for", "/apps/SuperCard_452_DevEd_Installer.zip", 20229562 },
    { kCatDevTools, 2005, kArchPPC, 90, "SuperCard 4.6.3", "HyperCard-inspired multimedia authoring and development environment from Solutions Etc.", "/apps/SuperCard_463_Developer.dmg", 33595184 },
    { kCatDevTools, 2002, kArchFat, 70, "SuperCard 4.7", "A HyperCard-like multimedia and application development environment for building interactive stacks on Mac", "/apps/SuperCardSuite47.dmg", 44318384 },
    { kCatDevTools, 2002, kArchFat, 70, "SuperCard 4.7.1", "A maintenance update to the SuperCard multimedia and application development environment for Mac OS.", "/apps/SuperCardSuite471.dmg", 44334814 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "SuperClock", "Menu-bar clock and calendar utility.", "/apps/SuperClock.hqx", 6059 },
    { kCatUtilities, 1991, kArch68k, 40, "SuperClock! 3.0", "Menu bar clock utility with customizable date and time display.", "/apps/SuperClock3.0.sit", 5856 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1988, kArch68k, 60, "SuperPaint", "Hybrid bitmap and object drawing program.", "/apps/SuperPaint.sit", 92895 },
    { kCatGraphicsSound, 1986, kArch68k, 20, "SuperPaint 1.0", "Combination bitmap and vector paint/draw program from Silicon Beach Software.", "/apps/SuperPaint1.0s.sit", 94728 },
    { kCatGraphicsSound, 1988, kArch68k, 60, "SuperPaint 2.0", "Silicon Beach's combined bitmap/object paint-and-draw program.", "/apps/SuperPaint2.0.sit", 408314 },
    { kCatGraphicsSound, 1988, kArch68k, 40, "SuperPaint 2.0 (Japanese)", "Silicon Beach Software's combined bitmap-and-vector drawing application; Japanese-localized release.", "/apps/SuperPaint2.0J.sit", 279101 },
    /* -- Games -- */
    { kCatGames, 0, kArch68k, 0, "Swamp Gas Visits the USA", "Delta Tao's whimsical classic Macintosh freeware game about a UFO touring America.", "/games/SwampGasVisitstheUSA_dc42.sit", 763830 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1992, kArch68k, 10, "Swivel 3D Demo", "Interactive 3D modeling and rendering, demo edition.", "/apps/swivel3d.zip", 40984429 },
    { kCatGraphicsSound, 1992, kArch68k, 60, "Swivel 3D Professional 2.0.4", "Paracomp/Macromedia's real-time 3D modeling application known for its swivel manipulation tools.", "/apps/SwivelPro204.sea_.hqx", 5818908 },
    { kCatGraphicsSound, 1990, kArch68k, 60, "SwivelArt 1.2.6", "Paracomp's library of pre-built 3D models for use with Swivel 3D.", "/apps/swivelart_1_2_6s.zip", 1602872 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 60, "Sword of Sodan", "Side-scrolling hack-and-slash action game ported to the Macintosh.", "/games/sword-of-sodan.sit", 3909804 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 60, "Symantec AntiVirus for Macintosh (SAM) 4.5", "Virus protection and detection suite from Symantec for the classic Mac OS.", "/apps/SAM_4.5.sit", 1867156 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "Symantec AntiVirus for Macintosh 4.0", "Virus detection and removal control panel from Symantec.", "/apps/SAM_4.sit", 1732531 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "Symantec C++ 6.0", "C/C++ compiler and development environment from Symantec, successor to THINK C.", "/apps/symantec_c60.sit", 3738396 },
    { kCatDevTools, 1994, kArch68k, 60, "Symantec C++ 7.0", "Symantec's integrated C++ development environment for Mac OS.", "/apps/Symantec_C_7.0_Disks.sit_.hqx", 9169431 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 60, "Symantec SAM 2.0", "Symantec AntiVirus for Macintosh, a widely used classic-era virus protection INIT.", "/apps/Symantec_SAM_2.0.sit_.hqx", 639191 },
    /* -- Utilities -- */
    { kCatUtilities, 2002, kArchPPC, 91, "Synchronize Pro X 4.0.1", "Later Qdea file-synchronization application, successor to Synchronize!.", "/apps/Synchronize_Pro_X_4.0.1.zip", 3781395 },
    { kCatUtilities, 1994, kArch68k, 70, "Synchronize! 3.26", "Qdea's file-synchronization utility for keeping folders and disks up to date.", "/apps/Synchronize_326.sit", 182256 },
    /* -- Games -- */
    { kCatGames, 1994, kArchFat, 70, "Syndicate", "Bullfrog's cyberpunk squad-based tactical action game of corporate warfare.", "/games/Syndicate.sit", 15464435 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1988, kArch68k, 60, "System 6.0.1", "Early bundled release of Apple's System Software for compact and modular Macintosh models.", "/apps/System_6.0.1.hqx", 1876959 },
    { kCatSystemExt, 1991, kArch68k, 70, "System 7.0", "Major overhaul of the classic Mac OS introducing virtual memory, file sharing, and TrueType, distributed as", "/apps/system_7_800k.sit", 4403602 },
    { kCatSystemExt, 1992, kArch68k, 71, "System 7.1", "Gold Master release of System 7.1, which introduced the Fonts folder and system enablers.", "/apps/System_7.1_GM.cdr", 343040000 },
    { kCatSystemExt, 1996, kArchFat, 75, "System 7.5.3", "Widely deployed update to System 7.5 adding stability fixes and Open Transport networking.", "/apps/SYSTEM_7-5-3-RETAIL_0.ISO", 267698176 },
    { kCatSystemExt, 1993, kArch68k, 60, "System Picker", "Selects between multiple installed System Folders at startup.", "/apps/system_picker.sit", 25472 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 60, "System Shock", "Looking Glass Studios' immersive sci-fi first-person action/RPG, ported to the Mac by MacPlay.", "/games/System_Shock_bin-cue.zip", 206135202 },
    { kCatGames, 1994, kArchFat, 70, "System Shock (Demo)", "Demo of Looking Glass Studios' influential immersive-sim horror shooter aboard a rogue space station.", "/games/System_Shock_demo.img_.hqx", 53494663 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 40, "Talking Moose 1.2.1", "Novelty extension that makes an animated moose speak comments from the menu bar.", "/apps/Talking_Moose_1.21_.sit", 80005 },
    /* -- Games -- */
    { kCatGames, 1989, kArch68k, 70, "Taskmaker", "Fantasy role-playing dungeon-crawl adventure.", "/games/TaskMaker101.sit", 1320832 },
    { kCatGames, 1993, kArch68k, 60, "TaskMaker 2.1.1", "Shareware first-person role-playing dungeon-crawler for the classic Mac OS.", "/games/TaskMaker_2.1.1.sit", 1589862 },
    { kCatGames, 1995, kArchFat, 70, "TaskMaker 2.2.4", "Sequel to Tomb of the Taskmaker, a real-time dungeon-crawling role-playing game.", "/games/TaskMaker_v2.2.4.img", 2187264 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 60, "TattleTech 2.05", "Reports detailed hardware and system configuration.", "/apps/TattleTech_2.03.sit", 263512 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 70, "TCP/Connect II", "Full internet suite - FTP, Telnet, mail, and news in one app.", "/apps/tcp_connect_ii.sit", 2794379 },
    /* -- Utilities -- */
    { kCatUtilities, 1987, kArch68k, 40, "TeachText 1.1", "Apple's simple bundled plain-text viewer and editor used to display Read Me files on classic Mac OS.", "/apps/TeachText11.hqx", 31137 },
    { kCatUtilities, 1994, kArch68k, 70, "TechTool", "Simple utility to zap the PRAM and rebuild the desktop.", "/apps/TechTool_v109.sit", 198654 },
    { kCatUtilities, 1995, kArch68k, 70, "TechTool 1.1.2", "Updated release of Micromat's free system diagnostic utility.", "/apps/TechTool_1.1.2.sit", 322236 },
    { kCatUtilities, 1994, kArch68k, 60, "TechTool 1.1.8", "Free utility for resetting parameter RAM and checking Mac hardware.", "/apps/Techtool1.1.8.bin", 589440 },
    { kCatUtilities, 1997, kArchFat, 70, "TechTool Lite 3.0.4", "The free diagnostic edition of Micromat's TechTool hardware utility.", "/apps/techtool_lite_304.hqx", 2685251 },
    { kCatUtilities, 1997, kArch68k, 75, "TechTool Pro 1.01", "Micromat's commercial hardware-diagnostic and disk-repair utility suite.", "/apps/TechTool_Pro_1.01.sit", 3563581 },
    { kCatUtilities, 1998, kArchPPC, 75, "TechTool Pro 2", "Micromat's comprehensive hardware and disk diagnostic utility.", "/apps/techtoolr_pro_2.sit", 14407630 },
    { kCatUtilities, 1999, kArchPPC, 75, "TechTool Pro 2.5", "Hardware diagnostic and disk repair utility suite from MicroMat.", "/apps/tech_tool_pro_2.5.sit_.bin", 11899008 },
    { kCatUtilities, 1999, kArchPPC, 75, "TechTool Pro 2.5.1", "MicroMat's comprehensive hardware and disk diagnostic utility for Macintosh.", "/apps/TechToolPro251CD.ZIP", 64286461 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1990, kArch68k, 60, "Telefinder", "Popular BBS client and server software.", "/apps/telefinder.sit", 13264554 },
    { kCatInternet, 1993, kArch68k, 60, "TeleFinder Pro 2.2", "Bulletin board system client and server software for the Macintosh.", "/apps/TeleFindertm_Pro_2.2.sea_.sit_.hqx", 955758 },
    { kCatInternet, 1996, kArch68k, 70, "TeleFinder Server 5.1.3", "Spider Island Software's BBS and online conferencing server for Mac OS.", "/apps/TeleFinder_Server_5.1.3A.sit", 6070500 },
    /* -- Games -- */
    { kCatGames, 1996, kArchPPC, 70, "Tempest 2000", "MacPlay's port of the Atari Jaguar tube-shooter remake of Tempest.", "/games/Tempest2000.zip", 58211327 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArchFat, 70, "Tempo 7.7d3", "Affinity Microsystems' macro recording and workflow automation utility, a rival to QuicKeys on classic Mac", "/apps/Tempo_7.7d3.sit", 9620722 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 0, "Tetris", "The classic falling-block puzzle game.", "/games/Tetris_DA.zip", 608565 },
    { kCatGames, 1993, kArch68k, 60, "Tetris Max", "Popular shareware Tetris clone with color graphics.", "/games/TetrisMax2.1.sit", 603421 },
    { kCatGames, 1994, kArch68k, 60, "Tetris Max 2.8", "Popular shareware Tetris clone for the Macintosh with extensive customization options.", "/games/TetrisMax_2.8.sit", 889144 },
    { kCatGames, 1996, kArchFat, 70, "TetrisMax 2.3", "Updated release of the shareware Tetris clone for Macintosh.", "/games/TetrisMax_2.3.sit", 817285 },
    /* -- Utilities -- */
    { kCatUtilities, 1991, kArch68k, 60, "Tex-Edit 1.1", "An early, pre-Plus release of Tom Bender's lightweight styled-text editor for classic Mac OS.", "/apps/Tex-Edit_1.1.sit", 51653 },
    { kCatUtilities, 1994, kArch68k, 70, "Tex-Edit Plus 3.02 (French)", "Tom Bender's popular lightweight styled-text editor for classic Mac OS, this build localized for French.", "/apps/Tex-Edit_Plus_F_302.sit", 798399 },
    { kCatUtilities, 1995, kArch68k, 60, "TextBridge 2.0.5", "Optical character recognition (OCR) software from Xerox for the classic Mac OS.", "/apps/TextBridge_2.0.5.sit", 3769606 },
    { kCatUtilities, 1999, kArchPPC, 80, "TextBridge Pro 8.0", "Optical character recognition software for converting scanned text to editable documents.", "/apps/TextBridge_Pro_8.sit", 19159994 },
    /* -- Games -- */
    { kCatGames, 1993, kArchFat, 70, "The Amazon Trail", "Educational exploration game following the Oregon Trail formula set on the Amazon River.", "/games/generalmills_amazontrail.sit", 501171643 },
    { kCatGames, 1988, kArch68k, 10, "The Ancient Art of War", "Real-time medieval strategy and tactics game.", "/games/Ancient_Art_of_War.sit", 225623 },
    { kCatGames, 1985, kArch68k, 20, "The Bard's Tale", "Interplay's classic first-person dungeon-crawling role-playing game.", "/games/bards_tale-macintosh.sit_.bin", 682624 },
    { kCatGames, 1999, kArchPPC, 75, "The ClueFinders 5th Grade Adventures", "Educational detective adventure game covering math, science, and language arts.", "/games/ClueFinders_5th_Grade.toast", 657084416 },
    /* -- Productivity -- */
    { kCatProductivity, 1997, kArchFat, 70, "The Digital Frog 2", "A well-known interactive virtual frog dissection and anatomy CD-ROM used in science classrooms.", "/apps/The_Digital_Frog_2.iso_.hqx", 774647477 },
    /* -- Games -- */
    { kCatGames, 1987, kArch68k, 20, "The Fool's Errand", "Cliff Johnson's beloved tarot-themed puzzle adventure game.", "/games/FoolsErrand.img_.sit", 517952 },
    { kCatGames, 1987, kArch68k, 0, "The Guild of Thieves", "Magnetic Scrolls' text-and-graphics fantasy adventure game.", "/games/The_Guild_of_Thieves.img", 419284 },
    { kCatGames, 1993, kArch68k, 60, "The Incredible Machine", "Sierra/Dynamix's Rube Goldberg-style physics puzzle construction game.", "/games/IncredibleMachine_1_0.zip", 2549729 },
    { kCatGames, 1993, kArch68k, 60, "The Journeyman Project", "Time-travel science-fiction adventure game.", "/games/JourneymanProject_Preview.sit", 5583501 },
    { kCatGames, 1993, kArch68k, 60, "The Legend of Kyrandia", "Westwood Studios' fantasy graphic adventure game.", "/games/Legend_of_Kyrandiatm_CD.toast_.sit", 283176995 },
    { kCatGames, 1987, kArch68k, 20, "The Lurking Horror", "Infocom's collegiate horror text adventure.", "/games/lurking_horror.sit", 106584 },
    { kCatGames, 1988, kArch68k, 60, "The Manhole", "Cyan's whimsical point-and-click exploration game for children, an early HyperCard-based adventure.", "/games/The_Manhole_CD.zip", 202275874 },
    { kCatGames, 1990, kArch68k, 0, "The Oregon Trail", "MECC's classic educational wagon-trail simulation for early Macintosh.", "/games/Oregon_Trail.img_.sit", 1096900 },
    { kCatGames, 1993, kArch68k, 60, "The Oregon Trail 1.2", "MECC's classic educational simulation of a 19th-century wagon journey west.", "/games/OregonTrail_v1.2.iso", 575754240 },
    { kCatGames, 1989, kArch68k, 40, "The Playroom", "Broderbund's exploratory activity game for young children.", "/games/the_playroom.sit", 2607110 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "The Print Shop Deluxe 1.1", "Broderbund's greeting card, banner, and sign-making software for the classic Mac OS.", "/apps/Print_Shop_Deluxe_v1.1_Floppy.zip", 4980122 },
    { kCatGraphicsSound, 1994, kArchPPC, 70, "The Print Shop Deluxe 1.1.3", "Broderbund's greeting card, banner, and sign design software.", "/apps/Print_Shop_Deluxe_1.1.3.sit", 19444553 },
    /* -- Games -- */
    { kCatGames, 1990, kArch68k, 40, "The Secret of Monkey Island", "LucasArts' classic point-and-click pirate comedy adventure game.", "/games/SecretofMonkeyIsland.sit", 4025853 },
    { kCatGames, 1996, kArchFat, 75, "The Ultimate Doom (Mac)", "Mac port of id Software's Doom including the fourth episode.", "/games/ultmt-doom-mac.sit", 32987866 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "Theorist 2.0.2", "Prescience Corporation's symbolic math and graphing application.", "/apps/Theorist_v2.0.2.sit", 449110 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1986, kArch68k, 40, "THINK C", "Symantec's landmark integrated C development environment for classic Mac OS, a mainstay of 1980s and 90s Mac", "/apps/THINKC.sit", 2485969 },
    { kCatDevTools, 1986, kArch68k, 0, "THINK C 1.0", "An early release of Symantec's integrated C development environment for classic Mac OS.", "/apps/THINK_C_1.img__0.bin", 819968 },
    { kCatDevTools, 1988, kArch68k, 40, "THINK C 2.0", "Symantec's integrated development environment for C programming on the Macintosh.", "/apps/THINK_C_2.img_.bin", 819968 },
    { kCatDevTools, 1989, kArch68k, 40, "THINK C 3.0.2", "Symantec's popular integrated C development environment for classic Mac OS.", "/apps/thinkc_3-0-2.zip", 633179 },
    /* -- Featured -- */
    { kCatFeatured, 1991, kArch68k, 60, "THINK C 5.0", "Symantec's popular C IDE for classic Mac development.", "/apps/think_c_5-0-2.zip", 2657019 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1991, kArch68k, 60, "THINK C 6.0", "Integrated C development environment from Symantec for classic Mac OS.", "/apps/symantec_think_c_v6.0.sit", 2976713 },
    { kCatDevTools, 1988, kArch68k, 40, "THINK Pascal 2", "Symantec's widely used integrated Pascal development environment for classic Mac OS.", "/apps/Think_Pascal_2.sit", 410479 },
    { kCatDevTools, 1988, kArch68k, 40, "THINK Pascal 2.0", "Symantec's integrated Pascal development environment for classic Mac OS.", "/apps/THINKPascal2.0images.sit", 544335 },
    { kCatDevTools, 1992, kArch68k, 60, "THINK Pascal 3.02", "Symantec's integrated Pascal development environment for classic Mac OS.", "/apps/THINK_Pascal_3.02_Upda.sit_.hqx", 916051 },
    { kCatDevTools, 1991, kArch68k, 60, "THINK Pascal 4.0", "Symantec's integrated Pascal development environment for classic Macintosh.", "/apps/think_pascal_4.sit", 2546627 },
    { kCatDevTools, 1992, kArch68k, 70, "THINK Pascal 4.0.2", "Symantec's Pascal IDE, a favorite for teaching Mac programming.", "/apps/THINK_Pascal_4.5d4.sit", 1600358 },
    { kCatDevTools, 1994, kArch68k, 70, "Think Reference 2.0", "Interactive on-disc reference tool for Macintosh Toolbox and C/Pascal API documentation.", "/apps/ThinkReference2.0images.sit", 3703894 },
    { kCatDevTools, 1993, kArch68k, 0, "ThinkReference", "Electronic Inside Macintosh API reference tool.", "/apps/ThinkReference1.0.sit", 1656318 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 0, "Thread Manager", "System extension adding cooperative threads to the Toolbox.", "/apps/ThreadManagerSDK.sit", 553631 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 70, "Timbuktu", "Remote screen sharing and control over a network.", "/apps/timbuktu4.sit", 23501922 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 70, "Timbuktu 4.0.6", "Remote screen control and file exchange update for Timbuktu.", "/apps/Timbuktu_4.0.6_Update.sit", 3042584 },
    { kCatInternet, 1988, kArch68k, 40, "Timbuktu Pro 1.0", "Early version of the Timbuktu remote-control and file-sharing application.", "/apps/timbuktu_pro_1.0_0.sit", 1145394 },
    { kCatInternet, 1993, kArch68k, 60, "Timbuktu Pro 3.0", "Farallon's classic Macintosh remote control and screen-sharing application.", "/apps/timbuktu_pro_v3.0.sit", 5196385 },
    { kCatInternet, 1998, kArchPPC, 75, "Timbuktu Pro 4", "Farallon's remote control and screen-sharing software for Mac networks.", "/apps/TimbuktuPro4CD.ZIP", 18587818 },
    { kCatInternet, 1996, kArchFat, 70, "Timbuktu Pro 4.0", "Farallon's remote-control and screen-sharing software (demo installer).", "/apps/Timbuktu_Pro_4.0_Demo.sit", 6150399 },
    { kCatInternet, 1999, kArchPPC, 75, "Timbuktu Pro 4.7.1", "Farallon's remote-control and file-sharing software for the Mac.", "/apps/Timbuktu_Pro_4.7.1.sit", 7172948 },
    { kCatInternet, 1997, kArch68k, 75, "Timbuktu Pro 4.8", "Netopia's popular remote-control and screen-sharing application for Macintosh networks.", "/apps/Timbuktu_Pro_4.8.sit", 4964698 },
    { kCatInternet, 1996, kArchFat, 70, "Timbuktu Pro 5.01", "Remote control and file sharing software from Farallon for the Macintosh.", "/apps/Timbuktu_5.01.sit_.hqx", 1154873 },
    { kCatInternet, 1998, kArchPPC, 75, "Timbuktu Pro 5.2.3", "Netopia's remote control and file-sharing software for accessing Macs over a network.", "/apps/timbuktu_pro_v5.2.3_1.sit", 3776909 },
    { kCatInternet, 1998, kArchFat, 70, "Timbuktu Pro 5.2.4", "Netopia's remote control and screen-sharing software for administering and collaborating on Macs over a", "/apps/Timbuktu_Pro_5.2.4.iso_.zip", 10680306 },
    { kCatInternet, 1998, kArchFat, 75, "Timbuktu Pro 6.0.1", "Remote control, file transfer and chat software CD-ROM release from Netopia.", "/apps/TimbuktuPro601CD.ZIP", 10557592 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 40, "TMON 2.8.4", "Interactive machine-language debugger for classic Mac OS development.", "/apps/TMON_2.8.4.image_.sit", 451249 },
    { kCatDevTools, 1990, kArch68k, 60, "TMON Pro 3.0", "Low-level machine-language debugger for classic Mac OS development.", "/apps/TMON_Pro3.0.sit", 1007281 },
    /* -- Utilities -- */
    { kCatUtilities, 1990, kArch68k, 60, "TMON Pro 3.0.1", "Low-level debugger for troubleshooting Macintosh application crashes.", "/apps/TMON_Pro_3.0.1.sit", 894246 },
    { kCatUtilities, 2001, kArchPPC, 86, "Toast 5.1", "Roxio's popular CD and DVD burning application for Mac OS.", "/apps/Toast_51wSN.sit", 3967986 },
    { kCatUtilities, 2003, kArchPPC, 86, "Toast 6 Titanium", "Roxio's CD and DVD burning application for Mac OS, the Titanium-branded release following Toast 5.", "/apps/Toast-6-Titanium-2003.sit", 99549603 },
    { kCatUtilities, 1998, kArch68k, 70, "Toast Deluxe 4.1.3", "A CD recording application for classic Mac OS from the Toast family by Adaptec.", "/apps/Toast_Deluxe_4.1.3_.sit", 3625744 },
    { kCatUtilities, 2003, kArchPPC, 86, "Toast Titanium 5.2", "Roxio's CD and DVD burning application for Mac OS, an earlier Titanium-branded release.", "/apps/Roxio_Toast_Titanium_5.2.sit", 75686676 },
    { kCatUtilities, 2004, kArchPPC, 86, "Toast Titanium 6.1.1", "Roxio's CD and DVD burning application for Mac OS, a later Titanium-branded release.", "/apps/Toast611Titanium.zip", 16707181 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 70, "Tomb of the Taskmaker", "Real-time role-playing adventure game exploring a haunted mansion, from Beyond Software.", "/games/tomb_of_the_taskmaker.sit", 1462269 },
    { kCatGames, 1998, kArchPPC, 75, "Tomb Raider II", "Core Design's action-adventure sequel starring Lara Croft, Macintosh port.", "/games/Tomb_Raider_II.dmg", 636511547 },
    { kCatGames, 1998, kArchPPC, 75, "Tomb Raider III", "Playable demo of Core Design's action-adventure game starring Lara Croft.", "/games/TombRaider_III_mac_demo.sit", 14390398 },
    { kCatGames, 1998, kArchPPC, 81, "Tomb Raider III (German)", "Core Design's action-adventure game starring Lara Croft, this classic Mac release localized for German.", "/games/Tomb_Raider_III_Ger.cdr_.sit", 486125220 },
    { kCatGames, 2000, kArchPPC, 81, "Tomb Raider: Chronicles", "Core Design's action-adventure game starring Lara Croft, this classic Mac release by Aspyr.", "/games/Tomb_Raider_Chronicles.sit", 525459608 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "TouchBase", "Contact management desk accessory companion to DateBook.", "/apps/TouchBase.zip", 391987 },
    /* -- Games -- */
    { kCatGames, 1985, kArch68k, 20, "Transylvania", "Early graphic adventure game of rescuing a princess from a monster-filled realm, from Polarware.", "/games/Transylvania_1985_prot_dsk.zip", 170384 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 0, "Trapeze 3.0", "Data Description's classic Macintosh spreadsheet application known for its graphing features.", "/apps/Trapeze_3.sit", 672642 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 70, "TrashIt! 3.6", "Shareware Trash replacement utility that can empty locked files and offers a more powerful deletion process", "/apps/Trash_It_3.6.hqx", 17637 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 20, "Trinity", "Infocom text adventure exploring the history and horror of nuclear weapons.", "/games/TrinityInfocom.img_.sit", 190052 },
    { kCatGames, 1992, kArch68k, 60, "Troggle Trouble Math 1.0", "The Learning Company's math-practice arcade game starring troll-fighting swamp creatures.", "/games/Troggle_Trouble_Math_1.0.sit", 8088417 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1988, kArch68k, 70, "True BASIC", "Structured BASIC programming language environment.", "/apps/truebasic2.5.sit", 307667 },
    { kCatDevTools, 1986, kArch68k, 30, "True BASIC 1.2", "The structured BASIC programming language and development environment created by BASIC's original authors", "/apps/True_Basic_1.2.sit_.hqx", 160631 },
    { kCatDevTools, 1986, kArch68k, 20, "Turbo Pascal 1.00A", "Borland's Pascal compiler and IDE, ported to the Macintosh.", "/apps/Borland-TP-1.00A-Mac.sit", 494309 },
    { kCatDevTools, 1986, kArch68k, 30, "Turbo Pascal 1.1 for Macintosh", "Borland's Turbo Pascal compiler and development environment ported to the Macintosh.", "/apps/Borland-TP-1.1-Mac.sit", 556352 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1994, kArch68k, 60, "TurboCAD 3.0", "IMSI's 2D/3D computer-aided design application for classic Mac OS.", "/apps/TurboCAD_3.0.sea_.sit", 1811013 },
    { kCatGraphicsSound, 1995, kArch68k, 60, "TurboCAD 3D 3.0", "A 3D computer-aided design application for the Mac.", "/apps/TurboCAD_3D_3.0.sea_.sit", 2804134 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1992, kArch68k, 60, "TurboGopher 1.0.5", "Early release of the TurboGopher client for browsing Gopher servers on the classic Mac OS.", "/apps/TurboGopher_1.0.5.sit", 131584 },
    { kCatInternet, 1993, kArch68k, 60, "TurboGopher 1.0.6b5", "Gopher protocol client from the University of Minnesota.", "/apps/TurboGopher_1.0.6b5.hqx", 418887 },
    { kCatInternet, 1993, kArch68k, 60, "TurboGopher 1.0.7g", "The University of Minnesota's classic Mac OS client for browsing Gopher, the menu-based precursor to the", "/apps/TurboGopher_1.0.7g.sit", 202398 },
    { kCatInternet, 1992, kArch68k, 60, "TurboGopher 1.0.8b4", "Earlier beta release of the TurboGopher Internet Gopher client.", "/apps/TurboGopher1.0.8b4.sit", 149532 },
    { kCatInternet, 1993, kArch68k, 60, "TurboGopher 2.0 (Beta 5)", "University of Minnesota's Gopher protocol client for browsing pre-web internet document menus.", "/apps/TurboGopher_2.0b5.sit", 227103 },
    { kCatInternet, 1993, kArch68k, 60, "TurboGopher 2.0.3", "University of Minnesota's fast native Macintosh Gopher client.", "/apps/TurboGopher_2.0.3.sit", 229363 },
    { kCatInternet, 1994, kArch68k, 60, "TurboGopher 2.0b3", "Gopher client from the University of Minnesota for browsing early internet menu systems.", "/apps/turbo-gopher-2.0b3.sit_.hqx", 253040 },
    { kCatInternet, 1993, kArch68k, 60, "TurboGopher 2.0b8", "University of Minnesota's graphical client for browsing Gopher servers.", "/apps/TurboGopher2.0b8.sit", 193121 },
    { kCatInternet, 1994, kArch68k, 70, "TurboGopher VR 2.1a4", "Experimental 3D-visualization variant of the TurboGopher Internet client.", "/apps/TurboGopherVR_2.1a4.sea_.hqx", 805826 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 50, "TurboSynth 2.22", "Modular digital synthesis and sound design software from Digidesign.", "/apps/Turbosynth_SCtm_2.22.img_.sit", 1210928 },
    /* -- Games -- */
    { kCatGames, 1996, kArchFat, 70, "Type to Learn", "Sunburst's popular educational touch-typing game for classic Mac OS.", "/games/Type_To_Learn.iso", 400181248 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "Type Twister", "Applies distortion effects to typeset text.", "/apps/aldus_type_twister.dmg_.zip", 675331 },
    /* -- Utilities -- */
    { kCatUtilities, 1993, kArch68k, 10, "TypeIt4Me", "Text-expansion typing shortcut utility.", "/apps/TypeIt4Me3.2.sit", 18934 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1990, kArch68k, 40, "TypeStyler 1.5.2", "Broderbund's application for creating stylized 3D and warped type effects.", "/apps/Broderbund_TypeStyler_1.5.2_1990.zip", 1043218 },
    { kCatGraphicsSound, 1995, kArch68k, 60, "TypeStyler 1.9.5 (Demo)", "Strider Software's application for creating custom typographic logos and text effects on classic Mac OS.", "/apps/TypeStyler_1.9.5_demo.dsk_.sit", 229459 },
    { kCatGraphicsSound, 1996, kArchFat, 70, "TypeStyler 3.5.8", "Later release of the TypeStyler type-effects design application.", "/apps/TypeStyler3.5.8.sit", 14022681 },
    /* -- Games -- */
    { kCatGames, 1982, kArch68k, 0, "Ultima II: Revenge of the Enchantress", "Origin Systems' early role-playing game, ported to Mac OS.", "/games/ultimaii.sit", 136807 },
    { kCatGames, 1987, kArch68k, 30, "Ultima III: Exodus", "Origin Systems' early Ultima role-playing game, Macintosh port.", "/games/ultima3-142.hqx", 3835168 },
    { kCatGames, 1988, kArch68k, 0, "Ultima V", "Classic Origin computer role-playing game.", "/games/Ultima_IV_Goodies.zip", 38841292 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1991, kArch68k, 60, "UltraPaint 1.05", "Deneba's combined bitmap and object-drawing application.", "/apps/deneba_ultrapaint_v105.sit", 2178663 },
    /* -- Games -- */
    { kCatGames, 1986, kArch68k, 10, "Uninvited", "Icom Simulations haunted-house graphic adventure.", "/games/uninvited.zip", 4355260 },
    { kCatGames, 1999, kArchPPC, 80, "Unreal", "Epic Games first-person shooter set on an alien prison planet, Mac port.", "/games/Unreal.sit", 479222840 },
    { kCatGames, 1999, kArchPPC, 81, "Unreal Tournament", "Epic Games' landmark multiplayer arena first-person shooter, ported to classic Mac OS.", "/games/Unreal_Tournament.toast", 541538304 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchPPC, 85, "USB Overdrive", "Third-party driver for USB mice and joysticks.", "/apps/usb-overdrive-12.sit", 219674 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1999, kArchPPC, 81, "USB Overdrive 1.4", "Alessandro Levi Montalcini's widely used universal driver for third-party USB mice, trackballs, and game", "/apps/USB_Overdrive_1.4.sit", 231761 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1993, kArch68k, 60, "UserLand Frontier 1.0", "The original release of Dave Winer's scripting environment and object database for automating classic Mac OS.", "/apps/userland_frontier_1.0.sit", 984518 },
    { kCatDevTools, 1996, kArch68k, 70, "UserLand Frontier 1.x", "UserLand Software's scripting environment and object database for Macintosh automation.", "/apps/UserLand-Frontier-1x.sit", 1142387 },
    /* -- Utilities -- */
    { kCatUtilities, 1992, kArch68k, 60, "UULite 1.3", "Utility for encoding and decoding uuencoded files on the classic Mac OS.", "/apps/UULite1.3.hqx", 64906 },
    { kCatUtilities, 1988, kArch68k, 0, "Vaccine", "Simple, early INIT-based virus protection.", "/apps/vaccine43.hqx", 281820 },
    /* -- Productivity -- */
    { kCatProductivity, 2000, kArchPPC, 81, "VectorWorks 8.5.1", "CAD and design drafting application from Diehl Graphsoft/Nemetschek.", "/apps/VectorWorks_8.5.1.sit_.hqx", 276160698 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1990, kArch68k, 60, "VersaTerm", "Terminal emulator supporting multiple protocols.", "/apps/VersaTerm-PRO-5-0.3.sit", 248628 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 70, "VideoShop", "Consumer-level QuickTime video editing application.", "/apps/VideoShop_4_5.sit", 4149594 },
    { kCatGraphicsSound, 1998, kArch68k, 70, "VideoShop 4", "A consumer-level digital video editing application for classic Mac OS.", "/apps/VideoShop_4.iso_.zip", 377789423 },
    { kCatGraphicsSound, 1985, kArch68k, 20, "VideoWorks", "MacroMind's original animation authoring tool, the predecessor to Director.", "/apps/Movies_-VideoWorks.sit", 408336 },
    /* -- Utilities -- */
    { kCatUtilities, 1994, kArch68k, 0, "Virex", "Datawatch's antivirus utility for classic Mac OS.", "/apps/Virex-D.sit", 33835 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "Virex 1.41", "Antivirus scanning software for Macintosh, later published by Datawatch.", "/apps/Virex_1.41.sit_.hqx", 49854 },
    { kCatSystemExt, 1993, kArch68k, 60, "Virex 3.82", "Datawatch's antivirus INIT for detecting and removing Macintosh viruses.", "/apps/Virexr_3.82.sit", 81659 },
    { kCatSystemExt, 1993, kArch68k, 60, "Virex 4.0", "An earlier version of Datawatch's widely used commercial antivirus software for classic Mac OS.", "/apps/Virex_4.0.sit", 180809 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 60, "Virex 5.06", "Anti-virus software for the classic Mac OS from Datawatch/McAfee.", "/apps/Virex_5.06.img", 819284 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1996, kArchFat, 70, "Virex 5.7", "Datawatch's antivirus software for classic Mac OS, version 5.7.", "/apps/Virex_v5.7.sit", 1265853 },
    { kCatSystemExt, 1998, kArch68k, 75, "Virex 5.9", "Datawatch's widely used antivirus utility for classic Mac OS.", "/apps/Virex-5.9-Mac-iso.sit", 43016556 },
    { kCatSystemExt, 1993, kArch68k, 60, "Virtual Desktop 1.7", "A control panel providing multiple virtual desktops (workspaces) on classic Mac OS, predating Spaces by over", "/apps/Virtual-Desktop-1.7_0.sit", 66416 },
    /* -- Utilities -- */
    { kCatUtilities, 1997, kArch68k, 70, "Virtual PC 1.0.1 Update", "Update for Connectix Virtual PC, the original release of the Mac PC emulator.", "/apps/VPC101U.sit", 535099 },
    { kCatUtilities, 1998, kArchPPC, 75, "Virtual PC 2.0 DOS Companion CD", "The bundled MS-DOS installation CD for Connectix Virtual PC 2.0, the Power Mac PC emulator.", "/apps/VPC20_DOSCD.ZIP", 39461327 },
    { kCatUtilities, 1998, kArchPPC, 75, "Virtual PC 2.1.3 Update", "Update for Connectix Virtual PC 2, the Power Mac PC emulator.", "/apps/VPC213U.sit", 1148595 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1999, kArchPPC, 81, "Virtual PC 4.0", "Connectix's PC-emulation application for running Windows on Power Macintosh.", "/apps/Virtual_PCtm_4.0.toast_.sitx", 511897764 },
    /* -- Utilities -- */
    { kCatUtilities, 2001, kArchPPC, 86, "Virtual PC 6", "Connectix's PC emulator that let Power Macintosh users run Windows and DOS operating systems.", "/apps/Virtual_PC_6.toast", 33177600 },
    /* -- System Extensions -- */
    { kCatSystemExt, 2004, kArchPPC, 91, "Virtual PC 7.0 (Beta)", "Beta build of Connectix/Microsoft's Virtual PC emulator.", "/apps/Virtual_PC_7_BETA_040304.sit", 20966448 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1993, kArch68k, 60, "Virtus VR 1.0", "An early real-time 3D modeling and virtual reality authoring application.", "/apps/Virtus_VR_v1.0_Disks.zip", 2444666 },
    { kCatGraphicsSound, 1991, kArch68k, 60, "Virtus WalkThrough", "Virtus Corporation's interactive 3D architectural modeling application.", "/apps/Virtus_Walkthroughtm.sit_.hqx", 1103451 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1988, kArch68k, 60, "Virus Detective 1.1", "Jeffrey Shulman's early rule-based antivirus scanner for classic Mac OS.", "/apps/VirusDetective11.sit_.Hqx", 13011 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1994, kArch68k, 60, "Visual MacStandardBasic 3.1", "A BASIC programming language development environment for classic Mac OS.", "/apps/Visual_MacStandardBasic_3.1.sit", 1509355 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1990, kArch68k, 60, "Voice Navigator", "Early third-party voice-command control software.", "/apps/voice_navigator.zip", 2943274 },
    /* -- Productivity -- */
    { kCatProductivity, 1993, kArch68k, 60, "Voyager II", "Astronomy and planetarium simulation software from Carina Software.", "/apps/voyagerii_1_0.zip", 7638024 },
    /* -- Games -- */
    { kCatGames, 1996, kArchFat, 70, "Warcraft II", "Blizzard's classic orcs-versus-humans real-time strategy game.", "/games/WarcraftII.sit", 18040041 },
    { kCatGames, 1999, kArchPPC, 75, "Warcraft II: Battle.net Edition", "Re-release of Warcraft II with Battle.net online multiplayer support.", "/games/Warcraft_II-Battle.net_.sit", 607054367 },
    { kCatGames, 1996, kArch68k, 70, "Warcraft II: Tides of Darkness", "Blizzard's orc-vs-human real-time strategy sequel.", "/games/Warcraft_II.toast_.sit", 503250838 },
    { kCatGames, 2002, kArchPPC, 85, "Warcraft III: Reign of Chaos", "Blizzard's real-time strategy game blending RPG hero units with base building.", "/games/Warcraft_III.toast_.zip", 634303790 },
    { kCatGames, 2002, kArchPPC, 81, "Warcraft III: Reign of Chaos (CD 1)", "Blizzard's landmark real-time strategy game, ported to classic Mac OS.", "/games/WC3_CD1.toast_.sit", 607384923 },
    { kCatGames, 2002, kArchPPC, 81, "Warcraft III: Reign of Chaos (Polish)", "Blizzard's real-time strategy game introducing heroes and RPG elements; Polish-language Macintosh release.", "/games/Warcraft_III_PL.toast_.sit", 623369757 },
    { kCatGames, 1994, kArch68k, 70, "Warcraft: Orcs & Humans", "Blizzard's original real-time strategy game, Macintosh CD-ROM release.", "/games/Warcraft.toast_.sit", 191407012 },
    { kCatGames, 1990, kArch68k, 60, "Warlords", "Turn-based fantasy conquest strategy game.", "/games/Warlords2.sit", 5511340 },
    { kCatGames, 1995, kArchFat, 70, "Warlords II", "Turn-based fantasy strategy game of conquering armies and rival kingdoms.", "/games/warII_v2.0_full_0.sit", 13684758 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1996, kArchFat, 70, "WASTE 1.3", "Marco Piovanelli's free multi-styled text editing engine library for Mac developers.", "/apps/WASTE_1.3.hqx", 610282 },
    { kCatDevTools, 1998, kArch68k, 70, "WASTE 2.0", "A free, widely embedded rich text editing engine for classic Mac OS used by many third-party text and mail", "/apps/WASTE_2.0.sit", 693881 },
    { kCatDevTools, 1999, kArch68k, 70, "WASTE 2.1b1", "A later beta of the free, widely embedded rich text editing engine used by many third-party classic Mac OS", "/apps/WASTE_2.1b1.sit", 1127595 },
    { kCatDevTools, 2002, kArchPPC, 0, "WASTE SDK 3.0.1", "Software development kit for the WASTE text-editing engine used by many classic Mac email and IRC clients.", "/apps/WASTE_SDK_3.0.1.dmg_.zip", 1226375 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArchPPC, 70, "Waves Gold 3.0", "Waves Audio's bundle of professional audio processing plug-ins.", "/apps/Waves_3.0_Gold.sit", 8207156 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1998, kArch68k, 85, "Web Confidential", "Password and confidential information manager.", "/apps/web-confidential.dmg_.bin", 2725888 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1995, kArch68k, 60, "WebMap", "Tool for creating clickable HTML image maps.", "/apps/WebMap.sit", 125110 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1994, kArch68k, 70, "WebMap 1.0.7d", "An early Mac utility for drawing clickable image maps and generating the HTML coordinates for web pages.", "/apps/WebMap_1.0.7d.sit", 123519 },
    /* -- Graphics & Sound -- */
    { kCatGraphicsSound, 1996, kArchFat, 70, "WebPainter 2.0", "Totally Hip's animated GIF creation tool for web graphics (demo version).", "/apps/WebPainter_2.0_Demo.sit", 3148758 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 70, "WebSTAR", "Popular commercial Macintosh web server software.", "/apps/WEBSTAR.dmg", 20703927 },
    { kCatInternet, 1996, kArch68k, 70, "WebSTAR 2.0", "StarNine's pioneering web server software for classic Mac OS.", "/apps/WEBSTAR_2.SIT_.bin", 3578112 },
    { kCatInternet, 1996, kArch68k, 70, "WebSTAR 2.1.1", "An update to StarNine's dominant web server software for classic Mac OS.", "/apps/WebStar_2.1.1_installer.hqx", 6893840 },
    { kCatInternet, 1996, kArch68k, 75, "WebSTAR 3.0.1", "Earlier version of the popular WebSTAR Macintosh web-server application.", "/apps/webstar-server-301.sit", 11577217 },
    { kCatInternet, 1999, kArchPPC, 75, "WebSTAR Server Suite 4.2", "4th Dimension-powered later release of the WebSTAR web server suite.", "/apps/WebSTAR_Server_Suite_4.2.sit", 8201600 },
    { kCatInternet, 2000, kArchPPC, 81, "WebSTAR Server Suite 4.3", "StarNine/4D's professional Macintosh web-server application suite.", "/apps/WebSTAR_Server_Suite_4.3.sit", 34874598 },
    { kCatInternet, 1999, kArchPPC, 75, "WebSTAR Server Suite 4.5", "Popular web server software for classic Mac OS from StarNine/4D.", "/apps/4D_WebSTAR_Server_Suite_45.sit", 37829869 },
    { kCatInternet, 2001, kArchPPC, 84, "WebSTAR V 5.2.1", "Later release of the WebSTAR web server software for Mac OS.", "/apps/4D_WebSTAR_V_v5.2.1.sit", 65647263 },
    { kCatInternet, 1997, kArch68k, 70, "WebTen 2.1.10", "Tenon Intersystems' Apache-based web server software for classic Mac OS.", "/apps/WebTen_2.1.10_Full.sit", 6895487 },
    { kCatInternet, 1996, kArch68k, 60, "WebWhacker 2.0", "Utility for downloading entire web sites for offline browsing on the classic Mac OS.", "/apps/WebWhacker_2.0_Installer.sit", 1353404 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 30, "Wheel of Fortune", "Computer adaptation of the television game show.", "/games/wheeloffortune_1_0.zip", 1925374 },
    { kCatGames, 1997, kArchPPC, 75, "Where in Time is Carmen Sandiego?", "Broderbund's history-themed edutainment detective game.", "/games/Carmen_Sandiego_Time_1.sit", 268935363 },
    { kCatGames, 1989, kArch68k, 40, "Where in Time is Carmen Sandiego? 1.0", "Broderbund's educational detective game sending players chasing Carmen Sandiego's henchmen through history.", "/games/Where_in_Time_is_Carmen_Sandiego_v1.0_floppies.zip", 1879934 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1993, kArch68k, 60, "White Knight", "Long-running terminal emulator, successor to Red Ryder.", "/apps/WhiteKnight.sit_.hqx", 296252 },
    { kCatInternet, 1993, kArch68k, 60, "White Knight 11.14", "FreeSoft's terminal emulation and telecommunications software for classic Mac OS, a longtime rival to ZTerm.", "/apps/White_Knight_11.14.image_.sit", 294982 },
    { kCatInternet, 1994, kArch68k, 60, "White Knight 12", "Terminal emulation and telecommunications software from FreeSoft for the classic Mac OS.", "/apps/White_Knight_12.sit_.hqx", 560848 },
    /* -- Games -- */
    { kCatGames, 1994, kArchFat, 70, "Widget Workshop", "Maxis edutainment game for building whimsical Rube Goldberg-style machines.", "/games/Widget_Workshop.sit", 2183185 },
    /* -- Productivity -- */
    { kCatProductivity, 1990, kArch68k, 60, "WillMaker 3.0", "Nolo Press software for drafting a legal last will and testament.", "/apps/WillMaker_3.0.img_.zip", 94177 },
    { kCatProductivity, 1993, kArch68k, 60, "WillMaker 5.0.3", "Nolo Press's do-it-yourself legal document and will preparation software for classic Mac OS.", "/apps/WillMaker_5.0.3.sea", 431894 },
    /* -- System Extensions -- */
    { kCatSystemExt, 1993, kArch68k, 60, "WindowShade", "Collapses windows to just their title bar on double-click.", "/apps/WindowShade1.1.sit", 5928 },
    { kCatSystemExt, 1993, kArch68k, 60, "WindowShade 1.3.1", "Control panel that lets windows roll up into their title bar, later built into Mac OS 8.", "/apps/WindowShade1.3.1.sit", 10926 },
    /* -- Games -- */
    { kCatGames, 1991, kArch68k, 0, "Wing Commander", "Space combat simulation with cinematic story missions.", "/games/WingCommanderIV_Demo.sit", 43191247 },
    { kCatGames, 1995, kArch68k, 70, "WingNuts (Demo)", "Freeverse Software's side-scrolling biplane dogfighting shareware game.", "/games/WingNuts_123_Demo.sit", 13971231 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "Wingz", "Informix spreadsheet application known for its HyperScript macro language and business graphics.", "/apps/Wingz_Test_Flight.zip", 588086 },
    /* -- Games -- */
    { kCatGames, 1988, kArch68k, 40, "Winter Games", "Epyx's Olympic winter sports simulation game, ported to classic Mac OS.", "/games/Winter_Games.img_.sit", 1662382 },
    { kCatGames, 1985, kArch68k, 20, "Wishbringer", "Infocom text adventure following a small-town postal worker drawn into a magical quest.", "/games/Wishbringer_1985_r68.app_.sit", 228478 },
    { kCatGames, 1987, kArch68k, 10, "Wizardry", "Classic dungeon-crawling role-playing game series.", "/games/wizardry_i.zip", 10853506 },
    { kCatGames, 1987, kArch68k, 30, "Wizardry 1.0", "Mac port of the classic dungeon-crawling role-playing game series.", "/games/Wizardry_1_10.dsk_.sit", 391660 },
    { kCatGames, 1996, kArchFat, 70, "Wizardry Gold", "Sirtech's combined CD-ROM edition of the classic Wizardry VII dungeon-crawling role-playing game.", "/games/wizardry_gold.cdr_.sit", 266977951 },
    { kCatGames, 1988, kArch68k, 40, "Wizardry II", "Sequel dungeon-crawling role-playing game continuing the Wizardry series on Mac.", "/games/Wizardry_2.img_.sit", 259026 },
    { kCatGames, 1988, kArch68k, 30, "Wizardry II: Knight of Diamonds", "Sequel to the original Wizardry, continuing the dungeon-crawling RPG series on the Macintosh.", "/games/Wizardry_II_Knights_of_Diam.mar", 839296 },
    { kCatGames, 1987, kArch68k, 0, "Wizardry IV: The Return of Werdna", "Sir-Tech's dungeon-crawling role-playing game, fourth in the Wizardry series.", "/games/Wizardry_4_00.dsk_.sit", 396463 },
    { kCatGames, 1990, kArch68k, 60, "Wizardry VI: Bane of the Cosmic Forge", "First-person dungeon-crawling role-playing game, sixth entry in the Wizardry series.", "/games/wizardry6.img_.sit", 1153036 },
    { kCatGames, 1994, kArchFat, 70, "Wolfenstein 3D", "Mac port of id Software's groundbreaking first-person shooter.", "/games/Wolfenstein_3D_v1.0_folder.sit", 1352223 },
    { kCatGames, 1994, kArch68k, 70, "Wolfenstein 3D (Mac)", "Mac port of id Software's pioneering first-person shooter.", "/games/wolfenstein-threed-101.hqx", 1928256 },
    { kCatGames, 1994, kArch68k, 60, "Wolfenstein 3D 1.0.2", "Macintosh port of id Software's pioneering first-person shooter.", "/games/Wolfenstein3D-102.sit", 2669456 },
    { kCatGames, 1994, kArch68k, 60, "Wolfenstein 3D Mac", "Classic Mac port of id Software's pioneering FPS.", "/games/wolfenstein3d_1_0_2.zip", 19180465 },
    { kCatGames, 1994, kArch68k, 60, "Wolfenstein 3D: Spear of Destiny", "The prequel episode to id Software's Wolfenstein 3D.", "/games/Spear_of_Destiny.dsk", 2949120 },
    { kCatGames, 1990, kArch68k, 60, "Wolfpack", "World War II U-boat submarine warfare simulator for Macintosh.", "/games/Wolfpack.sit", 1937359 },
    { kCatGames, 1991, kArch68k, 60, "Word Munchers", "Educational word-recognition arcade game.", "/games/Word_Munchers.img_.sit", 810532 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "WordPerfect 1.0", "First Macintosh release of the WordPerfect word processor ported from the DOS original.", "/apps/word_perfect_1.0.sit", 1169845 },
    { kCatProductivity, 1990, kArch68k, 60, "WordPerfect 2.1 (Australian release)", "Earlier Macintosh release of the WordPerfect word processor.", "/apps/WordPerfect_2.1_AUS.sit", 2424502 },
    { kCatProductivity, 1993, kArch68k, 60, "WordPerfect 3.0 (Dutch)", "WordPerfect Corporation's word processor for classic Mac OS; this is the Dutch-localized release.", "/apps/Word_Perfect_Mac_3.0_Dutch.toast", 8798208 },
    { kCatProductivity, 1993, kArch68k, 60, "WordPerfect 3.1", "WordPerfect Corporation's word processing application for Mac OS.", "/apps/wordperfect-31-novell.sit", 8119660 },
    { kCatProductivity, 1993, kArch68k, 70, "WordPerfect 3.5", "Macintosh version of the popular WordPerfect word processor.", "/apps/WordPerfect_3.5e.sit", 25869112 },
    { kCatProductivity, 1993, kArch68k, 60, "WordPerfect 3.5.1", "Corel/WordPerfect word processor for the classic Mac OS.", "/apps/corel-wordperfect-351.zip", 134518861 },
    { kCatProductivity, 1993, kArch68k, 70, "WordPerfect Demo", "Word processor demo, once a major Word competitor.", "/apps/wordperfect.sit", 927070 },
    { kCatProductivity, 1993, kArch68k, 60, "WordPerfect Works 1.2", "An integrated word processor, spreadsheet, and database works suite from WordPerfect Corporation.", "/apps/wordperfectworks_1_2.zip", 4810459 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchPPC, 70, "Work Faker 1.5.1", "A novelty utility that instantly displays a fake spreadsheet or business document to hide what's really on", "/apps/Work_Faker_1.5.1_PPC.sit", 53103 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1995, kArch68k, 60, "World Wide Web Weaver 1.1.1", "Miracle Software's shareware HTML web page editor.", "/apps/WorldWideWebWeaver1.1.1.sit", 950938 },
    { kCatInternet, 1995, kArch68k, 70, "World Wide Web Weaver 2.1.1", "Miracle Software's HTML authoring application for Macintosh.", "/apps/World_Wide_Web_Weaver_2.1.1.sit", 1301616 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1987, kArch68k, 0, "WorldBuilder", "Silicon Beach Software's tool for creating graphic adventure games without programming.", "/games/WorldBuilder.img_.bin", 2271360 },
    /* -- Productivity -- */
    { kCatProductivity, 1988, kArch68k, 40, "WriteNow 1.0 SE", "Fast, lightweight word processor for the Mac originally developed by NeXT-affiliated T/Maker.", "/apps/writenow_1.00SE.zip", 610794 },
    { kCatProductivity, 1988, kArch68k, 20, "WriteNow 1.2", "An early release of T/Maker's fast, lightweight word processor for classic Mac OS.", "/apps/WriteNow1_2_800k.zip", 645778 },
    { kCatProductivity, 1988, kArch68k, 40, "WriteNow 2.0", "T/Maker's lean, fast word processor for classic Mac OS.", "/apps/WriteNow20.zip", 1891736 },
    { kCatProductivity, 1988, kArch68k, 0, "WriteNow 2.2", "Early release of T/Maker's fast, compact word processing application.", "/apps/WriteNow_2.2.smi_.bin", 1995008 },
    { kCatProductivity, 1990, kArch68k, 60, "WriteNow 3.0", "T/Maker's fast, compact word processing application for Macintosh.", "/apps/WriteNow_3.cpt", 1350118 },
    { kCatProductivity, 1992, kArch68k, 42, "WriteNow 4.0", "Fast, lightweight word processor once bundled with NeXT.", "/apps/WriteNow40_UK.zip", 1453294 },
    { kCatProductivity, 1992, kArch68k, 60, "WriteNow 4.0.2", "Later release of the compact WriteNow word processor.", "/apps/writenow_4_02.zip", 1840802 },
    { kCatProductivity, 1993, kArch68k, 60, "WriteSwell Jr. 1.11", "An educational writing assistant application for classic Mac OS aimed at helping students structure essays.", "/apps/WriteswellJr111.sit_.bin", 50688 },
    /* -- Games -- */
    { kCatGames, 1995, kArch68k, 60, "Xconq", "A free, open-source turn-based strategy game engine with many playable scenarios.", "/games/Xconq.img_.sit", 1991876 },
    /* -- Utilities -- */
    { kCatUtilities, 1996, kArch68k, 60, "XEarth for Mac 1.0.2", "A Mac port of the classic Unix xearth utility that renders a shaded view of the Earth from space.", "/apps/XEarth_for_Mac_1.0.2.sit_.hqx", 318694 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1997, kArch68k, 60, "YA-NewsWatcher 2.3.6", "Yet Another NewsWatcher, a popular Usenet newsgroup reader for the classic Mac OS.", "/apps/YA-NewsWatcher_2.3.6.sit", 1151664 },
    { kCatInternet, 1996, kArch68k, 70, "YA-NewsWatcher 2.4.0", "Popular freeware Usenet newsgroup reader for Macintosh, 'Yet Another' NewsWatcher fork.", "/apps/YA_NewsWatcher_2.4.0.sit", 1068180 },
    { kCatInternet, 1998, kArchPPC, 70, "YA-NewsWatcher 3.1.8", "\"Yet Another\" community fork of the classic NewsWatcher Usenet newsgroup reader.", "/apps/YA-NewsWatcher_3.1.8_PPC.sit", 1289268 },
    { kCatInternet, 1998, kArchFat, 75, "YA-NewsWatcher 4.1.2", "Popular free Usenet newsgroup reader for classic Mac OS.", "/apps/YA-NewsWatcher_4.1.2.sit", 1195059 },
    { kCatInternet, 1998, kArchPPC, 75, "YA-NewsWatcher 4.2.4", "A community-maintained fork of NewsWatcher with added features.", "/apps/YA-NewsWatcher_4.2.4.bin", 1456128 },
    { kCatInternet, 1997, kArchFat, 70, "YA-NewsWatcher 4.2.5", "Popular freeware Usenet newsgroup reader for classic Mac OS.", "/apps/YA-NewsWatcher_4.2.5.bin", 1419648 },
    { kCatInternet, 2000, kArchPPC, 85, "Yahoo! Messenger 3.0 (Beta)", "An early beta release of Yahoo!'s instant messaging client for Mac OS.", "/apps/yahoo_messenger_3.0_beta1r2.dmg", 6508177 },
    { kCatInternet, 2002, kArch68k, 70, "yEnc (68k)", "A yEnc encoder/decoder utility for posting and downloading binary attachments on Usenet from classic Mac OS.", "/apps/yenctz68k.sit_.hqx", 120544 },
    /* -- Games -- */
    { kCatGames, 1995, kArchFat, 70, "You Don't Know Jack", "Irreverent trivia game show, Berkeley Systems.", "/games/You_Dont_Know_Jack_2.sit", 24347747 },
    /* -- Dev Tools -- */
    { kCatDevTools, 1990, kArch68k, 60, "ZBasic", "Zedcor's compiled BASIC development environment for classic Macintosh.", "/apps/zbasic.sit", 1632392 },
    /* -- Games -- */
    { kCatGames, 1994, kArch68k, 0, "Zip! Zap!", "Fast-paced puzzle-action game.", "/games/Zapdos.iso_.zip", 25290113 },
    /* -- Utilities -- */
    { kCatUtilities, 1998, kArchFat, 70, "ZipIt 1.3.8", "Shareware utility for creating and extracting ZIP archives on classic Mac OS.", "/apps/ZipIt_1.3.8.sit_.hqx", 631942 },
    /* -- Games -- */
    { kCatGames, 1996, kArch68k, 70, "Zone Raiders", "Isometric arena combat action game.", "/games/Zone_Raiders_Demo.sit_.hqx", 10698099 },
    { kCatGames, 2001, kArchPPC, 80, "Zoombinis Mountain Rescue", "Logic puzzle adventure game starring the Zoombinis, from Broderbund/TERC.", "/games/zoombinis_mountain.zip", 428602650 },
    { kCatGames, 1995, kArchFat, 70, "Zoop", "Fast-paced puzzle game of shooting colored shapes.", "/games/Zoop.img_.sit", 1353396 },
    { kCatGames, 1993, kArch68k, 60, "Zork Anthology", "Compilation of Infocom's classic Zork text adventure trilogy.", "/games/Zork_Anthology.img_.sit", 1147284 },
    { kCatGames, 1980, kArch68k, 0, "Zork I: The Great Underground Empire", "Infocom's foundational text adventure game.", "/games/1_Zork_I_ZIPs_Z-code_0.sit", 976484 },
    { kCatGames, 1984, kArch68k, 0, "Zork II: The Wizard of Frobozz", "Infocom's classic text adventure, Macintosh floppy disk release.", "/games/zork_ii_moof_dc42.zip", 503541 },
    { kCatGames, 1996, kArchFat, 70, "Zork Nemesis (Demo)", "Demo of the atmospheric first-person adventure game set in the Zork universe.", "/games/ZorkNemesis_demo.sit", 943141 },
    { kCatGames, 1984, kArch68k, 10, "Zork Trilogy", "Infocom's classic text-adventure trilogy: Zork I, II, and III.", "/games/zorktrilogy_dsk.zip", 271705 },
    { kCatGames, 1988, kArch68k, 40, "Zork Zero", "Infocom's graphical prequel to the Zork trilogy, set on the Great Underground Empire.", "/games/Zork_Zero.img_.sit", 588448 },
    /* -- Internet & Comm -- */
    { kCatInternet, 1990, kArch68k, 60, "ZTerm 0.7", "An early beta release of David Alverson's shareware terminal emulation and modem communications program.", "/apps/zterm-0.7.hqx", 152327 },
    { kCatInternet, 1990, kArch68k, 60, "ZTerm 0.8", "David Alverson's popular serial terminal and modem communications program (early beta).", "/apps/zterm-0.8.hqx", 181113 },
    { kCatInternet, 1992, kArch68k, 60, "ZTerm 0.85", "David Alverson's popular shareware terminal emulator for modem communications.", "/apps/zterm-0.85.hqx", 202643 },
    { kCatInternet, 1990, kArch68k, 40, "ZTerm 0.9", "Shareware terminal emulator popular for BBS and modem communications.", "/apps/ZTerm09.hqx", 273656 },
    { kCatInternet, 1993, kArch68k, 60, "ZTerm 1.0", "Popular shareware terminal emulator for modem BBSing.", "/apps/ZTerm1.0.1.sit", 283914 },
    { kCatInternet, 1995, kArch68k, 60, "ZTerm 1.0b3", "David Alverson's widely used shareware terminal emulation and modem communications program for classic Mac", "/apps/ZTerm1.0b3.sit", 280322 },
    { kCatInternet, 1995, kArch68k, 60, "ZTerm 1.1b7", "Updated build of the ZTerm shareware terminal emulator.", "/apps/ZTerm1.1b7.sit", 182874 },
};
const short kDefaultCatalogEntryCount = sizeof(gDefaultCatalogEntries) / sizeof(gDefaultCatalogEntries[0]);
