/*
 * DISTHRO Plugin Toolkit (DPT)
 * Copyright (C) 2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * A copy of the license is included with this software, or can be
 * found online at www.gnu.org/licenses.
 */

#ifndef __DISTRHO_PLUGIN_UTILS_H__
#define __DISTRHO_PLUGIN_UTILS_H__

#include "DistrhoIncludes.h"

#if DISTRHO_OS_WINDOWS
# include <windows.h>
#else
# include <unistd.h>
#endif

static inline
float abs_f(float value)
{
    return (value < 0.0) ? -value : value;
}

static inline
long CCONST(int a, int b, int c, int d)
{
    return (a << 24) | (b << 16) | (c << 8) | (d << 0);
}

static inline
void distrho_sleep(unsigned int seconds)
{
#if DISTRHO_OS_WINDOWS
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

static inline
void distrho_msleep(unsigned int mseconds)
{
#if DISTRHO_OS_WINDOWS
    Sleep(mseconds);
#else
    usleep(mseconds * 1000);
#endif
}

static inline
void distrho_usleep(unsigned int useconds)
{
#if DISTRHO_OS_WINDOWS
    Sleep(useconds/1000);
#else
    usleep(useconds);
#endif
}

static inline
void distrho_setenv(const char* key, const char* value)
{
#if DISTRHO_OS_WINDOWS
    SetEnvironmentVariableA(key, value);
#else
    setenv(key, value, 1);
#endif
}

#endif // __DISTRHO_PLUGIN_UTILS_H__
