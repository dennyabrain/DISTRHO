/*
 * DISTRHO Notes Plugin
 * Copyright (C) 2012 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the GPL.txt file
 */

#ifndef __DISTRHO_PLUGIN_NOTES_H__
#define __DISTRHO_PLUGIN_NOTES_H__

#include "DistrhoPlugin.h"

class DistrhoPluginNotes : public DISTRHO::Plugin
{
public:
    DistrhoPluginNotes();
    ~DistrhoPluginNotes();

    // ---------------------------------------------

protected:
    // Information
    const char* d_name()
    {
        return "Notes";
    }

    const char* d_label()
    {
        return "Notes";
    }

    const char* d_maker()
    {
        return "DISTRHO";
    }

    const char* d_license()
    {
        return "GPL v2+";
    }

    uint32_t d_version()
    {
        return 0x1000;
    }

    long d_uniqueId()
    {
        return d_cconst('D', 'N', 'o', 't');
    }

    // Init
    void d_initParameter(uint32_t index, DISTRHO::Parameter& parameter);

    // Internal data
    float d_parameterValue(uint32_t index);
    void  d_setParameterValue(uint32_t index, float value);

    // Process
    void d_activate();
    void d_deactivate();
    void d_run(const float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, const DISTRHO::MidiEvent* midiEvents);

    // Callbacks
    void d_stateChanged(const char* key, const char* value);

private:
    int curPage;
};

// -------------------------------------------------

#endif  // __DISTRHO_PLUGIN_NOTES_H__
