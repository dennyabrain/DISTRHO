// distrho base plugin class

#ifndef __DISTRHO_PLUGIN_BASE__
#define __DISTRHO_PLUGIN_BASE__

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "DistrhoPlugin.h"

#ifndef DISTRHO_PLUGIN_IS_SYNTH
#error DISTRHO_PLUGIN_IS_SYNTH undefined!
#endif

#ifndef DISTRHO_PLUGIN_WANTS_UI
#error DISTRHO_PLUGIN_WANTS_UI undefined!
#endif

#ifndef DISTRHO_PLUGIN_NUM_INPUTS
#error DISTRHO_PLUGIN_NUM_INPUTS undefined!
#endif

#ifndef DISTRHO_PLUGIN_NUM_OUTPUTS
#error DISTRHO_PLUGIN_NUM_OUTPUTS undefined!
#endif

#if defined(__WIN32__) || defined(__WIN64__)
#define DISTRHO_PLUGIN_EXPORT extern "C" __declspec (dllexport)
#else
#define DISTRHO_PLUGIN_EXPORT extern "C" __attribute__ ((visibility("default")))
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
    DistrhoPluginBase(uint32_t parameterCount, uint32_t programCount);
    virtual ~DistrhoPluginBase();

    // -------------------------------------------------

    // Information
    virtual const char* d_name()  = 0;
    virtual const char* d_label() = 0;
    virtual const char* d_maker() = 0;
    virtual const char* d_license() = 0;
    virtual uint32_t    d_version() = 0;
    virtual long        d_uniqueId() = 0;

    // Internal data
    virtual float d_parameterValue(uint32_t index) = 0;
    virtual void  d_setParameterValue(uint32_t index, float value) = 0;
    virtual void  d_setCurrentProgram(uint32_t index) = 0;

    // Init
    virtual void d_init() = 0;
    virtual void d_cleanup() = 0;

    // Process stuff
    virtual void d_activate() = 0;
    virtual void d_deactivate() = 0;
    virtual void d_run(float** inputs, float** outputs, uint32_t frames) = 0;

    // -------------------------------------------------

    // Host state
    double d_sampleRate();
    uint32_t d_bufferSize();
    void d_setLatency(uint32_t samples);

    // TODO - time-pos

    // -------------------------------------------------

    // Parameters
    uint32_t d_parameterCount() const;
    const ParameterInfo* d_parameterInfo(uint32_t index);

    // Programs
    uint32_t d_programCount() const;
    const char* d_programName(uint32_t index);

    // -------------------------------------------------

    // internal use only
    void __setSampleRate(double sampleRate);
    void __setBufferSize(uint32_t bufferSize);
    uint32_t __latency();

protected:
    ParameterInfo* p_paramsInfo;
    const char**   p_programNames;

private:
    uint32_t m_parameterCount;
    uint32_t m_programCount;
    double   m_sampleRate;
    uint32_t m_bufferSize;
    uint32_t m_latency;
};

// ---------------------------------------------------------------------------------------------

extern DistrhoPluginBase* createDistrhoPlugin();

#endif // __DISTRHO_PLUGIN_BASE__
