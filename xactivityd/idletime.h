/*
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef IDLETIME_H
#define IDLETIME_H

#include <X11/Xlib.h>

#ifdef __cplusplus
extern "C"
{
#endif


unsigned long workaroundCreepyXServer(Display *dpy, unsigned long _idleTime );


#ifdef __cplusplus
}
#endif

#endif
