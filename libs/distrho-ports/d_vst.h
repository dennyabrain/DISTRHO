// distrho vst redirect handler

#ifndef __DISTRHO_PORT_VST__
#define __DISTRHO_PORT_VST__

#include "PluginBase.h"
#include "DistrhoPlugin.h"

#include <cmath>

// Extra Plugin Hints (VST only)
const uint32_t PLUGIN_CAN_REPLACE = 1 << 3;

// ---------------------------------------------------------------------------------------------

#define vst_strncpy strncpy

#define kVstMaxProgNameLen   24
#define kVstMaxParamStrLen   8
#define kVstMaxVendorStrLen  64
#define kVstMaxProductStrLen 64
#define kVstMaxEffectNameLen 32

enum VstPlugCategory {
  kPlugCategEffect = 0
};

typedef int32_t VstInt32;
typedef void* audioMasterCallback;
typedef DistrhoPluginBase AudioEffect;

extern AudioEffect* createEffectInstance(audioMasterCallback audioMaster);

// ---------------------------------------------------------------------------------------------

class AudioEffectX : public DistrhoPluginBase
{
public:
    AudioEffectX(audioMasterCallback audioMaster, uint32_t programCount, uint32_t parameterCount) :
        DistrhoPluginBase(parameterCount, programCount)
    {
        m_name    = nullptr;
        m_maker   = nullptr;
        m_license = nullptr;
        m_uniqueId = 0;
        m_audioInputs = 0;
        m_audioOutputs = 0;
    }

    ~AudioEffectX()
    {
    }

    // Information
    virtual const char* d_name()
    {
        return m_name;
    }

    virtual const char* d_maker()
    {
        return m_maker;
    }

    virtual const char* d_license()
    {
        return m_license;
    }

    virtual int32_t d_version()
    {
        return getVendorVersion();
    }

    virtual long d_uniqueId()
    {
        return m_uniqueId;
    }

    // Internal data
    virtual float d_parameterValue(uint32_t index)
    {
        if (index < m_parameterCount)
            return getParameter(index);
        return 0.0f;
    }

    virtual void d_setParameterValue(uint32_t index, float value)
    {
        if (index < m_parameterCount)
            setParameter(index, value);
    }

    virtual void d_setCurrentProgram(uint32_t index)
    {
        //if (index < m_programCount)
        // TODO
    }

    // init
    virtual bool d_init()
    {
        char buf_str[255] = { 0 };

        getEffectName(buf_str);
        m_name = strdup(buf_str);

        getVendorString(buf_str);
        m_maker = strdup(buf_str);

        for (uint32_t i = 0; i < m_parameterCount; i++)
        {
            getParameterName(i, buf_str);
            p_paramsInfo[i].name = strdup(buf_str);

            char* symbol = strdup(p_paramsInfo[i].name);
            name_to_symbol(symbol);
            p_paramsInfo[i].symbol = symbol;

            getParameterLabel(i, buf_str);
            p_paramsInfo[i].unit = strdup(buf_str);

            p_paramsInfo[i].hints |= PARAMETER_IS_ENABLED;
            // TODO - set parameter automable
            p_paramsInfo[i].range.def = getParameter(i);
        }

        //for (uint32_t i = 0; i < m_programCount; i++)
        //{
            //buf_str[0] = 0;
            //getProgramName_(i, buf_str);
            //if (buf_str[0] != 0)
            //    p_programs[i] = strdup(buf_str);
        //}

        return true;
    }

    virtual bool d_cleanup()
    {
        if (m_name)
            free((void*)m_name);

        if (m_maker)
            free((void*)m_maker);

        if (m_license)
            free((void*)m_license);

        m_name    = nullptr;
        m_maker   = nullptr;
        m_license = nullptr;

        return true;
    }

    // Process stuff
    virtual void d_activate()
    {
        resume();
    }

    virtual void d_deactivate()
    {
        suspend();
    }

    virtual void d_run(float** inputs, float** outputs, uint32_t frames)
    {
        if (m_hints & PLUGIN_CAN_REPLACE)
            processReplacing(inputs, outputs, frames);
        else
        {
            memset(outputs, 0, sizeof(float)*m_audioOutputs*frames);
            process(inputs, outputs, frames);
        }
    }

    // -------------------------------------------------
    // VST side compatibility calls

#ifdef DISTRHO_BASE_VST_COMPAT
    void canMono()
    {
    }
#endif

    void canProcessReplacing()
    {
        m_hints |= PLUGIN_CAN_REPLACE;
    }

    void canDoubleReplacing()
    {
    }

    void isSynth()
    {
        m_hints |= PLUGIN_IS_SYNTH;
    }

    void setNumInputs(uint32_t numInputs)
    {
        m_audioInputs = numInputs;
    }

    void setNumOutputs(uint32_t numOutputs)
    {
        m_audioOutputs = numOutputs;
    }

    void setUniqueID(long uniqueId)
    {
        m_uniqueId = uniqueId;
    }

    double getSampleRate()
    {
        return m_sampleRate;
    }

    // unused conversion methods
#ifdef DISTRHO_BASE_VST_COMPAT
    virtual void dB2string(float, char*) {}
    virtual void Hz2string(float, char*) {}
    virtual void ms2string(float, char*) {}
    virtual void float2string(float, char*) {}
    virtual void long2string(long, char*) {}
#else
    virtual void dB2string(float, char*, int32_t) {}
    virtual void Hz2string(float, char*, int32_t) {}
    virtual void ms2string(float, char*, int32_t) {}
    virtual void float2string(float, char*, int32_t) {}
    virtual void int2string(int32_t, char*, int32_t) {}
#endif

    // optionally implemented in plugin
    virtual void resume() {}
    virtual void suspend() {}

    // required
    virtual bool getEffectName(char* name) = 0;
    virtual bool getProductString(char* text) = 0;
    virtual bool getVendorString(char* text) = 0;
    virtual void getProgramName (char* name) = 0;

#ifdef DISTRHO_BASE_VST_COMPAT
    virtual long  getVendorVersion() = 0;
    virtual void  setParameter(long index, float value) = 0;
    virtual float getParameter(long index) = 0;
    virtual void  getParameterName(long index, char* text) = 0;
    virtual void  getParameterLabel(long index, char* label) = 0;
    virtual void  process(float** inputs, float** outputs, long sampleFrames) = 0;
    virtual void  processReplacing(float** inputs, float** outputs, long sampleFrames) = 0;
#else
    virtual int32_t getVendorVersion() = 0;
    virtual void  setParameter(int32_t index, float value) = 0;
    virtual float getParameter(int32_t index) = 0;
    virtual void getParameterName(int32_t index, char* text) = 0;
    virtual void getParameterLabel(int32_t index, char* label) = 0;
    virtual void process(float** inputs, float** outputs, int32_t sampleFrames) {} // optional
    virtual void processReplacing(float** inputs, float** outputs, int32_t sampleFrames) = 0;
#endif

private:
    const char* m_name;
    const char* m_maker;
    const char* m_license;
    long m_uniqueId;
};

// ---------------------------------------------------------------------------------------------

DistrhoPluginBase* createDistrhoPlugin()
{
   return createEffectInstance(nullptr);
}

#endif // __DISTRHO_PORT_VST__
