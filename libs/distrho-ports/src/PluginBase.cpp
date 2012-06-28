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

#include "PluginBase.h"

START_NAMESPACE_DISTRHO

#if 0
} /* adjust editor indent */
#endif

DistrhoPluginBase::DistrhoPluginBase(uint32_t parameterCount, uint32_t programCount) :
    m_parameterCount(parameterCount),
    m_programCount(programCount)
{
    m_bufferSize = 512;
    m_sampleRate = 44100;
    m_latency    = 0;

    m_timePos.bpm = 120.0;

    if (m_parameterCount > 0)
    {
        p_paramsInfo = new ParameterInfo [m_parameterCount];

        for (uint32_t i = 0; i < m_parameterCount; i++)
        {
            p_paramsInfo[i].hints  = 0;
            p_paramsInfo[i].name   = nullptr;
            p_paramsInfo[i].symbol = nullptr;
            p_paramsInfo[i].unit   = nullptr;
            p_paramsInfo[i].range.def  = 0.0f;
            p_paramsInfo[i].range.min  = 0.0f;
            p_paramsInfo[i].range.max  = 1.0f;
            p_paramsInfo[i].range.step = 0.001f;
            p_paramsInfo[i].range.stepSmall = 0.00001f;
            p_paramsInfo[i].range.stepLarge = 0.01f;
        }
    }
    else
        p_paramsInfo = nullptr;

    if (m_programCount > 0)
    {
        p_programNames = new const char* [m_programCount];

        for (uint32_t i = 0; i < m_programCount; i++)
            p_programNames[i] = nullptr;
    }
    else
        p_programNames = nullptr;
}

DistrhoPluginBase::~DistrhoPluginBase()
{
    if (m_parameterCount > 0)
    {
        for (uint32_t i = 0; i < m_parameterCount; i++)
        {
            if (p_paramsInfo[i].name)
                free((void*)p_paramsInfo[i].name);
            if (p_paramsInfo[i].symbol)
                free((void*)p_paramsInfo[i].symbol);
            if (p_paramsInfo[i].unit)
                free((void*)p_paramsInfo[i].unit);
        }
        delete[] p_paramsInfo;
    }

    if (m_programCount > 0)
    {
        for (uint32_t i = 0; i < m_programCount; i++)
        {
            if (p_programNames[i])
                free((void*)p_programNames[i]);
        }
        delete[] p_programNames;
    }
}

// -------------------------------------------------

// Parameters
uint32_t DistrhoPluginBase::d_parameterCount() const
{
    return m_parameterCount;
}

const ParameterInfo* DistrhoPluginBase::d_parameterInfo(uint32_t index) const
{
    if (index < m_parameterCount)
        return &p_paramsInfo[index];
    return nullptr;
}

// Programs
uint32_t DistrhoPluginBase::d_programCount() const
{
    return m_programCount;
}

const char* DistrhoPluginBase::d_programName(uint32_t index) const
{
    if (index < m_programCount)
        return p_programNames[index];
    return nullptr;
}

// Host state
double DistrhoPluginBase::d_sampleRate() const
{
    return m_sampleRate;
}

uint32_t DistrhoPluginBase::d_bufferSize() const
{
    return m_bufferSize;
}

const TimePos* DistrhoPluginBase::d_timePos() const
{
    return &m_timePos;
}

void DistrhoPluginBase::d_setLatency(uint32_t samples)
{
    m_latency = samples;
}

// -------------------------------------------------

// internal use only
void DistrhoPluginBase::__setSampleRate(double sampleRate)
{
    m_sampleRate = sampleRate;
}

void DistrhoPluginBase::__setBufferSize(uint32_t bufferSize)
{
    m_bufferSize = bufferSize;
}

uint32_t DistrhoPluginBase::__latency() const
{
    return m_latency;
}

END_NAMESPACE_DISTRHO
