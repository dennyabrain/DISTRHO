/*
 * DISTRHO 3BandEQ Plugin, based on 3BandEQ by Michael Gruhn
 * Copyright (C) 2007 Michael Gruhn <michael-gruhn@web.de>
 * Copyright (C) 2012 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the LGPL.txt file
 */

#ifndef __DISTRHO_PLUGIN_3BANDEQ_H__
#define __DISTRHO_PLUGIN_3BANDEQ_H__

#include "DistrhoPlugin.h"

class DistrhoPlugin3BandEQ : public DISTRHO::Plugin
{
public:
    enum Parameters
    {
        paramLow = 0,
        paramMid,
        paramHigh,
        paramMaster,
        paramLowMidFreq,
        paramMidHighFreq,
        paramCount
    };

    DistrhoPlugin3BandEQ();
    ~DistrhoPlugin3BandEQ();

    // ---------------------------------------------

protected:
    // Information
    const char* d_label()
    {
        return "3BandEQ";
    }

    const char* d_maker()
    {
        return "DISTRHO";
    }

    const char* d_license()
    {
        return "LGPL";
    }

    uint32_t d_version()
    {
        return 0x1000;
    }

    long d_uniqueId()
    {
        return d_cconst('D', '3', 'E', 'Q');
    }

    // Init
    void d_initParameter(uint32_t index, DISTRHO::Parameter& parameter);
    void d_initProgramName(uint32_t index, d_string& programName);

    // Internal data
    float d_parameterValue(uint32_t index);
    void  d_setParameterValue(uint32_t index, float value);
    void  d_setProgram(uint32_t index);

    // Process
    void d_activate();
    void d_deactivate();
    void d_run(const float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, const DISTRHO::MidiEvent* midiEvents);

    // ---------------------------------------------

private:
    float fLow, fMid, fHigh, fMaster, fLowMidFreq, fMidHighFreq;

    float lowVol, midVol, highVol, outVol;
    float freqLP, freqHP;

    float xLP, a0LP, b1LP;
    float xHP, a0HP, b1HP;

    float out1LP, out2LP, out1HP, out2HP;
    float tmp1LP, tmp2LP, tmp1HP, tmp2HP;
};

#endif  // __DISTRHO_PLUGIN_3BANDEQ_H__
