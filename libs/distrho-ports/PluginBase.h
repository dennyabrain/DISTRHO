// distrho base plugin class

#ifndef __DISTRHO_PLUGIN_BASE__
#define __DISTRHO_PLUGIN_BASE__

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <stdint.h>

#include "DistrhoPlugin.h"

#ifndef nullptr
#define nullptr (0)
#endif

#if defined(__WIN32__) || defined(__WIN64__)
# define DISTRHO_PLUGIN_EXPORT extern "C" __declspec (dllexport)
#else
# define DISTRHO_PLUGIN_EXPORT extern "C" __attribute__ ((visibility("default")))
#endif

// Parameter Hints
const uint32_t PARAMETER_IS_ENABLED   = 1 << 1;
const uint32_t PARAMETER_IS_AUTOMABLE = 1 << 2;
const uint32_t PARAMETER_IS_OUTPUT    = 1 << 3;

struct ParameterInfo {
    uint32_t hints;
    const char* name;
    const char* symbol;
    const char* unit;

    struct {
        float def;
        float min;
        float max;
        float step;
        float stepSmall;
        float stepLarge;
    } range;
};

// ---------------------------------------------------------------------------------------------

class DistrhoPluginBase
{
public:
    DistrhoPluginBase(uint32_t parameterCount, uint32_t programCount) :
        m_parameterCount(parameterCount),
        m_programCount(programCount)
    {
        m_sampleRate = 44100;
        m_bufferSize = 512;

        m_audioInputs  = 0;
        m_audioOutputs = 0;

        if (m_parameterCount > 0)
        {
            p_paramsInfo = new ParameterInfo [m_parameterCount];

            for (uint32_t i = 0; i < m_parameterCount; i++)
            {
                p_paramsInfo[i].hints  = 0;
                p_paramsInfo[i].name   = nullptr;
                p_paramsInfo[i].symbol = nullptr;
                p_paramsInfo[i].unit   = nullptr;
                p_paramsInfo[i].range.def = 0.0f;
                p_paramsInfo[i].range.min = 0.0f;
                p_paramsInfo[i].range.max = 1.0f;
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

    virtual ~DistrhoPluginBase()
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
    uint32_t d_parameterCount() const
    {
        return m_parameterCount;
    }

    const ParameterInfo* d_parameterInfo(uint32_t index)
    {
        if (index < m_parameterCount)
            return &p_paramsInfo[index];
        return nullptr;
    }

    // Programs
    uint32_t d_programCount() const
    {
        return m_programCount;
    }

    const char* d_programName(uint32_t index)
    {
        if (index < m_programCount)
            return p_programNames[index];
        return nullptr;
    }

    uint32_t d_audioInputs() const
    {
        return DISTRHO_PLUGIN_MAX_NUM_INPUTS;
    }

    uint32_t d_audioOutputs() const
    {
        return DISTRHO_PLUGIN_MAX_NUM_OUTPUTS;
    }

    // -------------------------------------------------

    void d_setSampleRate(double sampleRate)
    {
        m_sampleRate = sampleRate;
    }

    void d_setBufferSize(uint32_t bufferSize)
    {
        m_bufferSize = bufferSize;
    }

    // -------------------------------------------------

    // Information
    virtual const char* d_name() = 0;
    virtual const char* d_maker() = 0;
    virtual const char* d_license() = 0;
    virtual int32_t     d_version() = 0;
    virtual long        d_uniqueId() = 0;

    // Internal data
    virtual float d_parameterValue(uint32_t index) = 0;
    virtual void  d_setParameterValue(uint32_t index, float value) = 0;
    virtual void  d_setCurrentProgram(uint32_t index) = 0;

    // Init
    virtual bool d_init() = 0;
    virtual bool d_cleanup() = 0;

    // Process stuff
    virtual void d_activate() = 0;
    virtual void d_deactivate() = 0;
    virtual void d_run(float** inputs, float** outputs, uint32_t frames) = 0;

protected:
    ParameterInfo* p_paramsInfo;
    const char**   p_programNames;

    double   m_sampleRate;
    uint32_t m_bufferSize;

private:
    uint32_t m_parameterCount;
    uint32_t m_programCount;
    uint32_t m_audioInputs;
    uint32_t m_audioOutputs;
};

inline void name_to_symbol(char* text)
{
    for (size_t i = 0, len = strlen(text); i < len; i++)
    {
        if (std::isalpha(text[i]))
        {
            // to lower case
            if (text[i] <= 'Z')
                text[i] += ('z' - 'Z');
        }
        else if (std::isdigit(text[i]))
        {
            // cannot start with a digit
            if (i == 0)
                text[i] = '_';
        }
        else
            text[i] = '_';
    }
}

// ---------------------------------------------------------------------------------------------

DistrhoPluginBase* createDistrhoPlugin();

#endif // __DISTRHO_PLUGIN_BASE__
