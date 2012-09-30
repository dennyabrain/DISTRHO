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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * A copy of the license is included with this software, or can be
 * found online at www.gnu.org/licenses.
 */

#ifndef __DISTRHO_UI_DSSI_H__
#define __DISTRHO_UI_DSSI_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void* DSSIUI_Handle;

typedef struct _DSSIUI_Descriptor {
    DSSIUI_Handle (*instantiate)(const struct _DSSIUI_Descriptor* descriptor, const char* url, const char* title);
    void (*configure)(DSSIUI_Handle handle, const char* key, const char* value);
    void (*control)(DSSIUI_Handle handle, unsigned long index, float value);
    void (*program)(DSSIUI_Handle handle, unsigned long bank, unsigned long program);
    void (*midi)(DSSIUI_Handle handle, unsigned char data[4]);
    void (*sample_rate)(DSSIUI_Handle handle, float srate);
    void (*show)(DSSIUI_Handle handle);
    void (*hide)(DSSIUI_Handle handle);
    void (*quit)(DSSIUI_Handle handle);
} DSSIUI_Descriptor;

const DSSIUI_Descriptor* dssiui_descriptor();

typedef const DSSIUI_Descriptor* (*DSSIUI_Descriptor_Function)();

#ifdef __cplusplus
}
#endif

#endif // __DISTRHO_UI_DSSI_H__
