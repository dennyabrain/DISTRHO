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

#include "DistrhoUIInternal.h"
#include "DistrhoUtils.h"

#ifdef DISTRHO_PLUGIN_TARGET_DSSI

// -------------------------------------------------

START_NAMESPACE_DISTRHO

class UIDssi
{
    UIDssi()
        : ui(this, changeStateCallback, setParameterValueCallback, uiResizeCallback)
    {
        ui.createWindow((PuglNativeWindow)0);
    }

    ~UIDssi()
    {
        ui.destroyWindow();
    }

    // ---------------------------------------------

#if DISTRHO_PLUGIN_WANT_STATE
    void dssiui_configure(const char* const key, const char* const value)
    {
        ui.stateChanged(key, value);
    }
#endif

    void dssiui_control(const uint32_t index, const float value)
    {
        ui.parameterChanged(portIndex - DISTRHO_PLUGIN_NUM_INPUTS - DISTRHO_PLUGIN_NUM_OUTPUTS, value);
    }

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    void dssiui_program(uint32_t bank, uint32_t program)
    {
        const uint32_t index = bank * 128 + program;
        ui.programChanged(index);
    }
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
    void dssiui_midi()
    {
    }
#endif

    // ---------------------------------------------

protected:
    void changeState(const char* key, const char* value)
    {
        // TODO
        (void)key;
        (void)value;
        //lo_send configure
    }

    void setParameterValue(uint32_t index, float value)
    {
        //lo_send(control_ptr->osc_address, control_ptr->osc_control_path, "if", (int)port_index, *(float *)buffer);
    }

    void uiResize(unsigned int, unsigned int)
    {
        // do nothing
    }

private:
    UIInternal ui;

    // ---------------------------------------------
    // Callbacks

    static void changeStateCallback(void* ptr, const char* key, const char* value)
    {
        UIDssi* const _this_ = (UIDssi*)ptr;
        assert(_this_);

        _this_->changeState(key, value);
    }

    static void setParameterValueCallback(void* ptr, uint32_t index, float value)
    {
        UIDssi* const _this_ = (UIDssi*)ptr;
        assert(_this_);

        _this_->setParameterValue(index, value);
    }

    static void uiResizeCallback(void* ptr, unsigned int width, unsigned int height)
    {
        UIDssi* const _this_ = (UIDssi*)ptr;
        assert(_this_);

        _this_->uiResize(width, height);
    }
};

// -------------------------------------------------

#if 0
static DSSIUI_Descriptor uidescriptor = {
    dssiui_configure,
    dssiui_control,
    dssiui_sample_rate
};
#endif

END_NAMESPACE_DISTRHO

// -------------------------------------------------

#if 0
DISTRHO_PLUGIN_EXPORT
const DSSIUI_Descriptor* dssiui_descriptor(uint32_t index)
{
    USE_NAMESPACE_DISTRHO
    return (index == 0) ? &uidescriptor : nullptr;
}
#endif

// -------------------------------------------------

#endif // DISTRHO_PLUGIN_TARGET_DSSI
