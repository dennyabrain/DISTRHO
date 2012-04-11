/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 *
 * Released under the Public Domain
 */

#ifdef AUDIOGAIN_LV2

#include "lv2/lv2.h"
#include "lv2/ui.h"

#include "audiogain.h"
#include "ui_audiogain.h"

#define AUDIOGAIN_URI    "http://kxstudio.sourceforge.net/ns/plugins/audiogain"
#define AUDIOGAIN_UI_URI "http://kxstudio.sourceforge.net/ns/plugins/audiogain#gui"

#ifndef WIN32
inline float abs (float x)
{
    return ( x<0 ? -x:x);
}
#endif

class Lv2AudioGain
{
public:
    enum PortIndex {
        PortInLeft       = 0,
        PortInRight      = 1,
        PortOutLeft      = 2,
        PortOutRight     = 3,
        PortParamLeft    = 4,
        PortParamRight   = 5,
        PortPeakOutLeft  = 6,
        PortPeakOutRight = 7
    };

    Lv2AudioGain()
    {
        in_portL  = in_portR  = 0;
        out_portL = out_portR = 0;
        in_paramL = in_paramR = 0;
        out_peakL = out_peakR = 0;
    }

    ~Lv2AudioGain()
    {
    }

    void lv2_connect_port(uint32_t port, void* data)
    {
        switch((PortIndex)port)
        {
        case PortInLeft:
            in_portL = data;
            break;
        case PortInRight:
            in_portR = data;
            break;
        case PortOutLeft:
            out_portL = data;
            break;
        case PortOutRight:
            out_portR = data;
            break;
        case PortParamLeft:
            in_paramL = data;
            break;
        case PortParamRight:
            in_paramR = data;
            break;
        case PortPeakOutLeft:
            out_peakL = data;
            break;
        case PortPeakOutRight:
            out_peakR = data;
            break;
        default:
            break;
        }
    }

    void lv2_run(uint32_t nframes)
    {
        // LV2 values
        float x_left  = *(float*)in_paramL;
        float x_right = *(float*)in_paramR;

        float v_leftx, v_rightx;
        v_leftx = v_rightx = 0.0f;

        const float* const p_inL = (float*)in_portL;
        const float* const p_inR = (float*)in_portR;
        float* const p_outL = (float*)out_portL;
        float* const p_outR = (float*)out_portR;

        for (uint32_t i=0; i<nframes; i++)
        {
            p_outL[i] = p_inL[i]*x_left;
            p_outR[i] = p_inR[i]*x_right;

            if (abs(p_outL[i]) > v_leftx)
                v_leftx = abs(p_outL[i]);

            if (abs(p_outR[i]) > v_rightx)
                v_rightx = abs(p_outR[i]);
        }

        if (v_leftx > 1.0f)
          v_leftx = 1.0f;

        if (v_rightx > 1.0f)
          v_rightx = 1.0f;

        *(float*)out_peakL = v_leftx;
        *(float*)out_peakR = v_rightx;
    }

private:
    void* in_portL;
    void* in_portR;
    void* out_portL;
    void* out_portR;

    void* in_paramL;
    void* in_paramR;
    void* out_peakL;
    void* out_peakR;
};

class Lv2AudioGainW : public AudioGainW
{
public:
    Lv2AudioGainW(LV2UI_Controller controller_, LV2UI_Write_Function write_function_) :
        AudioGainW(),
        controller(controller_),
        write_function(write_function_)
    {
        v_left = v_right = 0.0f;
    }

    ~Lv2AudioGainW()
    {
    }

    float getPeakValueL()
    {
        return v_left;
    }

    float getPeakValueR()
    {
        return v_right;
    }

    void setProcessValueL(float value)
    {
        write_function(controller, Lv2AudioGain::PortParamLeft, sizeof(float), 0, &value);
    }

    void setProcessValueR(float value)
    {
        write_function(controller, Lv2AudioGain::PortParamRight, sizeof(float), 0, &value);
    }

    void lv2_port_event(uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer)
    {
        if (format == 0 && buffer_size == sizeof(float))
        {
            float value = *(float*)buffer;

            if (port_index == Lv2AudioGain::PortParamLeft)
            {
                // Avoid re-sending value to plugin
                ui->dial_left->blockSignals(true);
                ui->dial_left->setValue((value*50)-50);
                ui->dial_left->blockSignals(false);
            }
            else if (port_index == Lv2AudioGain::PortParamRight)
            {
                // Avoid re-sending value to plugin
                ui->dial_right->blockSignals(true);
                ui->dial_right->setValue((value*50)-50);
                ui->dial_right->blockSignals(false);
            }
            else if (port_index == Lv2AudioGain::PortPeakOutLeft)
                v_left = value;
            else if (port_index == Lv2AudioGain::PortPeakOutRight)
                v_right = value;
        }
    }

private:
    LV2UI_Controller controller;
    LV2UI_Write_Function write_function;

    float v_left, v_right;
};

static LV2_Handle instantiate(const LV2_Descriptor*, double, const char*, const LV2_Feature* const*)
{
    return new Lv2AudioGain();
}

static void connect_port(LV2_Handle instance, uint32_t port, void* data)
{
    Lv2AudioGain* plugin = (Lv2AudioGain*)instance;
    plugin->lv2_connect_port(port, data);
}

static void activate(LV2_Handle)
{
}

static void run(LV2_Handle instance, uint32_t n_samples)
{
    Lv2AudioGain* plugin = (Lv2AudioGain*)instance;
    plugin->lv2_run(n_samples);
}

static void deactivate(LV2_Handle)
{
}

static void cleanup(LV2_Handle instance)
{
    delete (Lv2AudioGain*)instance;
}

static LV2UI_Handle ui_instantiate(const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const*)
{
    Lv2AudioGainW* ui = new Lv2AudioGainW(controller, write_function);
    *widget = ui;
    return ui;
}

static void ui_cleanup(LV2UI_Handle ui)
{
    delete (Lv2AudioGainW*)ui;
}

static void ui_port_event(LV2UI_Handle ui_, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    Lv2AudioGainW* ui = (Lv2AudioGainW*)ui_;
    ui->lv2_port_event(port_index, buffer_size, format, buffer);
}

static const void* extension_data(const char*)
{
    return 0;
}

static const LV2_Descriptor descriptor = {
    AUDIOGAIN_URI,
    instantiate,
    connect_port,
    activate,
    run,
    deactivate,
    cleanup,
    extension_data
};

static const LV2UI_Descriptor ui_descriptor = {
    AUDIOGAIN_UI_URI,
    ui_instantiate,
    ui_cleanup,
    ui_port_event,
    extension_data
};

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    return (index == 0) ? &descriptor : 0;
}

LV2_SYMBOL_EXPORT const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
{
    return (index == 0) ? &ui_descriptor : 0;
}

#endif // AUDIOGAIN_LV2
