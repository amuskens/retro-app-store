#ifndef DNR_H
#define DNR_H

#include "mactcp_low.h"

/* Hostname -> IP address, via MacTCP's Domain Name Resolver. Unlike the
   TCP calls in net.c, the DNR isn't reached through PBControl on the
   ".IPP" driver refnum - it's a small relocatable code resource ('dnrp' id
   1) that ships inside the MacTCP control panel file itself. OpenResolver's
   real job is finding and loading *that*; see dnr.c for the mechanism,
   verified against Apple's own original DNR.c (Steve Falkenburg/Apple
   MacDTS, 1991, modified by Jim Matthews/Dartmouth - the author of Fetch). */

OSErr DNR_Open(void);
void DNR_Close(void);

/* Resolves hostName to *outAddr. If hostName already parses as a dotted-
   decimal IP address, resolves it directly with no driver/network
   involvement at all - a deliberate fallback path, not just an
   optimization: it keeps the app usable even if this resolver
   reconstruction has a bug on some MacTCP version, by letting Preferences
   hold a raw IP instead of a hostname. giveTime is called repeatedly while
   waiting (wire it to SystemTask()); if cancel is non-NULL and becomes
   true, the wait stops early and userCanceledErr is returned. */
OSErr DNR_Resolve(const char *hostName, ip_addr *outAddr, GiveTimeProc giveTime, Boolean *cancel);

#endif
