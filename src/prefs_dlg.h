#ifndef PREFS_DLG_H
#define PREFS_DLG_H

#include "net.h" /* tcp_port */

/* FTP connection settings, editable without recompiling - community mirror
   hostnames/credentials drift over time (already true of Macintosh
   Garden's own mirror across the sources checked while building this),
   so this shouldn't be a value the app is silently stuck with forever. */
typedef struct {
    char host[128];
    tcp_port port;
    char user[64];
    char pass[64];
    char basePath[128]; /* default path for Live FTP Browse */
} GardenPrefs;

/* Fills *prefs from the saved prefs file (Preferences folder, "Garden
   Preferences"), or compiled-in defaults if there isn't one yet. */
void Prefs_Load(GardenPrefs *prefs);
OSErr Prefs_Save(const GardenPrefs *prefs);

/* Runs the modal Preferences dialog, pre-filled from *prefs. On OK,
   updates *prefs, saves them, and returns true. On Cancel, *prefs is left
   untouched and this returns false. */
Boolean PrefsDlg_Run(GardenPrefs *prefs);

#endif
