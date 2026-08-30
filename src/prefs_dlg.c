#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Dialogs.h>
#include <Files.h>
#include <AppleEvents.h>

#include "prefs_dlg.h"
#include "native.h"
#include "app.h"

/* Not defined in this toolchain's Multiverse.h (FindFolder here just takes
   the raw vRefNum/Boolean) - same real, stable values used in dnr.c. */
#define kOnSystemDisk (-1)
#define kDontCreateFolder false

#define kDefaultHost "ftp.macintosh.garden"
#define kDefaultPort 21
#define kDefaultUser "mirror"
#define kDefaultPass "mirror"

enum {
    kPrefsDialogID = 130,
    iPrefsOK = 1, iPrefsCancel = 2,
    iPrefsHostField = 4, iPrefsPortField = 6, iPrefsUserField = 8, iPrefsPassField = 10
};

static void SetDefaults(GardenPrefs *p)
{
    strcpy(p->host, kDefaultHost);
    p->port = kDefaultPort;
    strcpy(p->user, kDefaultUser);
    strcpy(p->pass, kDefaultPass);
    p->basePath[0] = 0;
}

static OSErr GetPrefsFileSpec(FSSpec *outSpec)
{
    short vRefNum;
    long dirID;
    Str255 name;
    OSErr err;

    err = FindFolder((short)kOnSystemDisk, kPreferencesFolderType, kDontCreateFolder, &vRefNum, &dirID);
    if (err != noErr) return err;

    CToPascal("Garden Preferences", name);
    return FSMakeFSSpec(vRefNum, dirID, name, outSpec);
}

/* Splits *cursor on the first \r, \n, or \r\n, NUL-terminating the line in
   place and advancing *cursor past it - lenient about which convention
   wrote the file, since Prefs_Save uses classic Mac \r but this shouldn't
   choke reading a hand-edited \n file either. Returns NULL at end of
   string. */
static char *NextLine(char **cursor)
{
    char *start = *cursor;
    char *p = start;

    if (*start == 0) return NULL;

    while (*p != 0 && *p != '\n' && *p != '\r') p++;
    if (*p == '\r') {
        *p = 0;
        p++;
        if (*p == '\n') p++;
    } else if (*p == '\n') {
        *p = 0;
        p++;
    }
    *cursor = p;
    return start;
}

void Prefs_Load(GardenPrefs *prefs)
{
    FSSpec spec;
    short refNum;
    long size;
    char buf[512];
    OSErr err;
    char *cursor, *line;
    short field;

    SetDefaults(prefs);

    if (GetPrefsFileSpec(&spec) != noErr) return;
    if (FSpOpenDF(&spec, fsRdPerm, &refNum) != noErr) return; /* no saved prefs yet */

    err = GetEOF(refNum, &size);
    if (err != noErr || size <= 0 || size >= (long)sizeof(buf)) { FSClose(refNum); return; }

    err = FSRead(refNum, &size, buf);
    FSClose(refNum);
    if (err != noErr) return;
    buf[size] = 0;

    cursor = buf;
    field = 0;
    while ((line = NextLine(&cursor)) != NULL) {
        switch (field) {
            case 0: strncpy(prefs->host, line, sizeof(prefs->host) - 1); prefs->host[sizeof(prefs->host) - 1] = 0; break;
            case 1: prefs->port = (tcp_port)atoi(line); break;
            case 2: strncpy(prefs->user, line, sizeof(prefs->user) - 1); prefs->user[sizeof(prefs->user) - 1] = 0; break;
            case 3: strncpy(prefs->pass, line, sizeof(prefs->pass) - 1); prefs->pass[sizeof(prefs->pass) - 1] = 0; break;
            case 4: strncpy(prefs->basePath, line, sizeof(prefs->basePath) - 1); prefs->basePath[sizeof(prefs->basePath) - 1] = 0; break;
        }
        field++;
    }
    if (prefs->port == 0) prefs->port = kDefaultPort;
}

OSErr Prefs_Save(const GardenPrefs *prefs)
{
    FSSpec spec;
    short refNum;
    char buf[512];
    long len;
    OSErr err;

    err = GetPrefsFileSpec(&spec);
    if (err != noErr) return err;

    FSpDelete(&spec); /* ignore result - fine if it didn't already exist */
    err = FSpCreate(&spec, 'GRDN', 'TEXT', smSystemScript);
    if (err != noErr) return err;

    err = FSpOpenDF(&spec, fsWrPerm, &refNum);
    if (err != noErr) return err;

    sprintf(buf, "%s\r%u\r%s\r%s\r%s\r", prefs->host, prefs->port, prefs->user, prefs->pass, prefs->basePath);
    len = (long)strlen(buf);
    err = FSWrite(refNum, &len, buf);
    FSClose(refNum);
    return err;
}

/* Without this, a Quit AppleEvent (Shut Down/Restart/Finder Quit)
   arriving while Preferences is open would be silently dropped - a plain
   ModalDialog(NULL, ...) never dispatches AppleEvents at all, the same
   gap RunApp's own loop and progress_dlg.c's both had (see app.c). */
static pascal Boolean PrefsModalFilter(DialogPtr dlg, EventRecord *evt, short *itemHit)
{
    (void)dlg; (void)itemHit;
    if (evt->what == kHighLevelEvent) {
        AEProcessAppleEvent(evt);
        return true;
    }
    return false;
}

Boolean PrefsDlg_Run(GardenPrefs *prefs)
{
    DialogPtr dlg;
    short itemType;
    Handle itemH;
    Rect box;
    short itemHit;
    Str255 s;
    GardenPrefs work = *prefs;
    char portStr[16];
    ModalFilterUPP filterUPP = NewModalFilterUPP(PrefsModalFilter);

    dlg = GetNewDialog(kPrefsDialogID, NULL, (WindowPtr)-1L);
    if (dlg == NULL) return false;

    GetDialogItem(dlg, iPrefsHostField, &itemType, &itemH, &box);
    CToPascal(work.host, s);
    SetDialogItemText(itemH, s);

    GetDialogItem(dlg, iPrefsPortField, &itemType, &itemH, &box);
    sprintf(portStr, "%u", work.port);
    CToPascal(portStr, s);
    SetDialogItemText(itemH, s);

    GetDialogItem(dlg, iPrefsUserField, &itemType, &itemH, &box);
    CToPascal(work.user, s);
    SetDialogItemText(itemH, s);

    GetDialogItem(dlg, iPrefsPassField, &itemType, &itemH, &box);
    CToPascal(work.pass, s);
    SetDialogItemText(itemH, s);

    SelectDialogItemText(dlg, iPrefsHostField, 0, 32767);

    for (;;) {
        ModalDialog(filterUPP, &itemHit);
        if (itemHit == iPrefsOK || itemHit == iPrefsCancel) break;
        if (App_IsQuitting()) { itemHit = iPrefsCancel; break; } /* quitting mid-dialog - discard edits, don't hang here waiting for OK/Cancel that's never coming */
    }

    if (itemHit == iPrefsOK) {
        GetDialogItem(dlg, iPrefsHostField, &itemType, &itemH, &box);
        GetDialogItemText(itemH, s);
        PascalToC(s, work.host, sizeof(work.host));

        GetDialogItem(dlg, iPrefsPortField, &itemType, &itemH, &box);
        GetDialogItemText(itemH, s);
        PascalToC(s, portStr, sizeof(portStr));
        work.port = (tcp_port)atoi(portStr);
        if (work.port == 0) work.port = kDefaultPort;

        GetDialogItem(dlg, iPrefsUserField, &itemType, &itemH, &box);
        GetDialogItemText(itemH, s);
        PascalToC(s, work.user, sizeof(work.user));

        GetDialogItem(dlg, iPrefsPassField, &itemType, &itemH, &box);
        GetDialogItemText(itemH, s);
        PascalToC(s, work.pass, sizeof(work.pass));

        DisposeDialog(dlg);
        *prefs = work;
        Prefs_Save(prefs);
        return true;
    }

    DisposeDialog(dlg);
    return false;
}
