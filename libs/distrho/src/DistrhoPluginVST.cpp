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
 * For a full copy of the license see the GPL.txt file
 */

#ifdef DISTRHO_PLUGIN_TARGET_VST

#include "DistrhoPluginInternal.h"

#if DISTRHO_PLUGIN_HAS_UI
# include "DistrhoUIInternal.h"
#endif

#define VST_FORCE_DEPRECATED 0
#include <pluginterfaces/vst2.x/aeffectx.h>

// -------------------------------------------------

START_NAMESPACE_DISTRHO

#if DISTRHO_PLUGIN_HAS_UI
class UIVst
{
public:
    UIVst(audioMasterCallback callback, AEffect* effect, PluginInternal* plugin, intptr_t winId)
        : m_callback(callback),
          m_effect(effect),
          m_plugin(plugin),
          ui(this, winId, changeStateCallback, setParameterValueCallback, uiResizeCallback)
    {
    }

    ~UIVst()
    {
    }

    // ---------------------------------------------

    void idle()
    {
        ui.idle();
    }

protected:
    intptr_t hostCallback(int32_t opcode, int32_t index, intptr_t value, void* ptr, float opt)
    {
        return m_callback(m_effect, opcode, index, value, ptr, opt);
    }

#if DISTRHO_PLUGIN_WANT_STATE
    void changeState(const char* key, const char* value)
    {
    }
#endif

    void setParameterValue(uint32_t index, float realValue)
    {
        const ParameterRanges* ranges = m_plugin->parameterRanges(index);
        float perValue = 1.0f - (ranges->max - realValue) / (ranges->max - ranges->min);

        hostCallback(audioMasterAutomate, index, 0, nullptr, perValue);
    }

    void uiResize(unsigned int width, unsigned int height)
    {
        hostCallback(audioMasterSizeWindow, width, height, nullptr, 0.0f);
    }

private:
    // Vst stuff
    const audioMasterCallback m_callback;
    AEffect* const m_effect;
    PluginInternal* const m_plugin;

    // Plugin UI
    UIInternal ui;

    // ---------------------------------------------
    // Callbacks

    static void changeStateCallback(void* ptr, const char* key, const char* value)
    {
#if DISTRHO_PLUGIN_WANT_STATE
        UIVst* const _this_ = (UIVst*)ptr;
        assert(_this_);

        _this_->changeState(key, value);
#else
        // unused
        (void)ptr;
        (void)key;
        (void)value;
#endif
    }

    static void setParameterValueCallback(void* ptr, uint32_t index, float value)
    {
        UIVst* const _this_ = (UIVst*)ptr;
        assert(_this_);

        _this_->setParameterValue(index - DISTRHO_PLUGIN_NUM_INPUTS - DISTRHO_PLUGIN_NUM_OUTPUTS, value);
    }

    static void uiResizeCallback(void* ptr, unsigned int width, unsigned int height)
    {
        UIVst* const _this_ = (UIVst*)ptr;
        assert(_this_);

        _this_->uiResize(width, height);
    }

    friend class PluginVst;
};
#endif

class PluginVst
{
public:
    PluginVst(audioMasterCallback audioMaster, AEffect* effect)
        : m_audioMaster(audioMaster),
          m_effect(effect)
    {
#if DISTRHO_PLUGIN_HAS_UI
        vstui = nullptr;
#endif

        curProgram = 0;
        midiEventCount = 0;
    }

    ~PluginVst()
    {
    }

    intptr_t vst_dispatcher(int32_t opcode, int32_t index, intptr_t value, void* ptr, float opt)
    {
        int32_t ret = 0;

        switch (opcode)
        {
        case effSetProgram:
            if (value < plugin.programCount())
            {
                curProgram = value;
                plugin.setProgram(curProgram);
            }
            break;

        case effGetProgram:
            ret = curProgram;
            break;

        case effSetProgramName:
        case effGetProgramName:
            break;

        case effGetParamDisplay:
            if (ptr && index < (int32_t)plugin.parameterCount())
                snprintf((char*)ptr, kVstMaxParamStrLen, "%f", plugin.parameterValue(index));
            return 0;

        case effSetSampleRate:
            // should not happen
            break;

        case effSetBlockSize:
            plugin.setBufferSize(value, true);
            break;

        case effMainsChanged:
            if (value)
                plugin.activate();
            else
                plugin.deactivate();
            break;

#if DISTRHO_PLUGIN_HAS_UI
        case effEditGetRect:
            if (vstui)
            {
                static ERect rect = { 0, 0, (int16_t)vstui->ui.getHeight(), (int16_t)vstui->ui.getWidth() };
                *(ERect**)ptr = &rect;
                ret = 1;
            }
            break;

        case effEditOpen:
            vstui = new UIVst(m_callback, &effect, &plugin, (intptr_t)ptr);
            ret = 1;
            break;

        case effEditClose:
            if (vstui)
            {
                delete vstui;
                ret = 1;
            }
            break;

        case effEditIdle:
            if (vstui)
                vstui->idle();
            break;
#endif

        case effGetChunk:
        case effSetChunk:
            // TODO
            break;

        case effProcessEvents:
            if (ptr)
            {
                //VstEvents* events = (VstEvents*)ptr;
                // TODO
            }
            break;

        case effCanBeAutomated:
            if (index < (int32_t)plugin.parameterCount())
            {
                uint32_t hints = plugin.parameterHints(index);

                // must be automable, and not output
                if ((hints & PARAMETER_IS_AUTOMABLE) > 0 && (hints & PARAMETER_IS_OUTPUT) == 0)
                    ret = 1;
            }
            break;

        case effCanDo:
            break;

        case effStartProcess:
        case effStopProcess:
            break;
        }

        return ret;

        // unused
        (void)opt;
    }

    float vst_getParameter(int32_t index)
    {
        const ParameterRanges* ranges = plugin.parameterRanges(index);
        float realValue = plugin.parameterValue(index);
        float perValue  = (realValue - ranges->min) / (ranges->max - ranges->min);
        return perValue;
    }

    void vst_setParameter(int32_t index, float value)
    {
        const ParameterRanges* ranges = plugin.parameterRanges(index);
        float realValue = ranges->min + (ranges->max - ranges->min) * value;
        plugin.setParameterValue(index, realValue);
    }

    void vst_processReplacing(float** inputs, float** outputs, int32_t sampleFrames)
    {
        plugin.run((const float**)inputs, outputs, sampleFrames, midiEventCount, midiEvents);
    }

    // ---------------------------------------------

private:
    // VST stuff
    audioMasterCallback const m_audioMaster;
    AEffect* const m_effect;

    int32_t curProgram;

    // Plugin
    PluginInternal plugin;

#if DISTRHO_PLUGIN_HAS_UI
    // UI
    UIVst* vstui;
#endif

    uint32_t midiEventCount;
#if DISTRHO_PLUGIN_IS_SYNTH
    MidiEvent midiEvents[MAX_MIDI_EVENTS];
#else
    MidiEvent midiEvents[0];
#endif
};

// -------------------------------------------------

// Create dummy plugin to get data from
static PluginInternal plugin;

static intptr_t vst_dispatcherCallback(AEffect* effect, int32_t opcode, int32_t index, intptr_t value, void* ptr, float opt)
{
    switch (opcode)
    {
    case effOpen:
        if (! effect->object)
        {
            audioMasterCallback audioMaster = (audioMasterCallback)effect->user;
            d_lastBufferSize = audioMaster(effect, audioMasterGetBlockSize, 0, 0, nullptr, 0.0f);
            d_lastSampleRate = audioMaster(effect, audioMasterGetSampleRate, 0, 0, nullptr, 0.0f);
            effect->object   = new PluginVst(audioMaster, effect);
            return 1;
        }
        return 0;

    case effClose:
        if (effect->object)
        {
            delete (PluginVst*)effect->object;
            effect->object = nullptr;
            delete effect;
            return 1;
        }
        return 0;

    case effGetParamLabel:
        if (ptr && index < (int32_t)plugin.parameterCount())
        {
            strncpy((char*)ptr, plugin.parameterUnit(index), kVstMaxParamStrLen);
            return 1;
        }
        return 0;

    case effGetParamName:
        if (ptr && index < (int32_t)plugin.parameterCount())
        {
            strncpy((char*)ptr, plugin.parameterName(index), kVstMaxParamStrLen);
            return 1;
        }
        return 0;

    case effGetProgramNameIndexed:
        if (index < (int32_t)plugin.programCount())
        {
            strncpy((char*)ptr, plugin.programName(index), kVstMaxProgNameLen);
            return 1;
        }
        return 0;

    case effGetPlugCategory:
#if DISTRHO_PLUGIN_IS_SYNTH
        return kPlugCategSynth;
#else
        return kPlugCategUnknown;
#endif

    case effGetEffectName:
        strncpy((char*)ptr, plugin.name(), kVstMaxProductStrLen);
        return 1;

    case effGetVendorString:
        strncpy((char*)ptr, plugin.maker(), kVstMaxVendorStrLen);
        return 1;

    case effGetProductString:
        strncpy((char*)ptr, plugin.label(), kVstMaxEffectNameLen);
        return 1;

    case effGetVendorVersion:
        return plugin.version();

    case effGetVstVersion:
        return kVstVersion;
    };

    PluginVst* _this_ = (PluginVst*)effect->object;
    assert(_this_);

    if (_this_)
        return _this_->vst_dispatcher(opcode, index, value, ptr, opt);

    return 0;
}

static float vst_getParameterCallback(AEffect* effect, int32_t index)
{
    PluginVst* _this_ = (PluginVst*)effect->object;
    assert(_this_);

    if (_this_)
        return _this_->vst_getParameter(index);

    return 0.0f;
}

static void vst_setParameterCallback(AEffect* effect, int32_t index, float value)
{
    PluginVst* _this_ = (PluginVst*)effect->object;
    assert(_this_);

    if (_this_)
        _this_->vst_setParameter(index, value);
}

static void vst_processCallback(AEffect* effect, float** inputs, float** outputs, int32_t sampleFrames)
{
    PluginVst* _this_ = (PluginVst*)effect->object;
    assert(_this_);

    if (_this_)
        _this_->vst_processReplacing(inputs, outputs, sampleFrames);
}

static void vst_processReplacingCallback(AEffect* effect, float** inputs, float** outputs, int32_t sampleFrames)
{
    PluginVst* _this_ = (PluginVst*)effect->object;
    assert(_this_);

    if (_this_)
        _this_->vst_processReplacing(inputs, outputs, sampleFrames);
}

END_NAMESPACE_DISTRHO

// -------------------------------------------------

DISTRHO_PLUGIN_EXPORT
const AEffect* VSTPluginMain(audioMasterCallback audioMaster)
{
    USE_NAMESPACE_DISTRHO

    // old version
    if (! audioMaster(nullptr, audioMasterVersion, 0, 0, nullptr, 0.0f))
        return nullptr;

    AEffect* effect = new AEffect;
    memset(effect, 0, sizeof(AEffect));

    // vst fields
    effect->magic    = kEffectMagic;
    effect->uniqueID = plugin.uniqueId();
    effect->version  = plugin.version();

    // plugin fields
    effect->numParams   = plugin.parameterCount();
    effect->numPrograms = plugin.programCount();
    effect->numInputs   = DISTRHO_PLUGIN_NUM_INPUTS;
    effect->numOutputs  = DISTRHO_PLUGIN_NUM_OUTPUTS;

    // static calls
    effect->dispatcher   = vst_dispatcherCallback;
    effect->process      = vst_processCallback;
    effect->getParameter = vst_getParameterCallback;
    effect->setParameter = vst_setParameterCallback;
    effect->processReplacing = vst_processReplacingCallback;
    effect->processDoubleReplacing = nullptr;

    // plugin flags
    effect->flags |= effFlagsCanReplacing;
#if DISTRHO_PLUGIN_HAS_UI
    effect->flags |= effFlagsHasEditor;
#endif
#if DISTRHO_PLUGIN_WANT_STATE
    effect->flags |= effFlagsProgramChunks;
#endif

    // pointers
    effect->object = nullptr;
    effect->user   = (void*)audioMaster;

    return effect;
}

// -------------------------------------------------

#endif // DISTRHO_PLUGIN_TARGET_VST
