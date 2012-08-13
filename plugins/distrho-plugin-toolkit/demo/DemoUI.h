// demo plugin

#ifndef __DEMO_UI_H__
#define __DEMO_UI_H__

#include <cstdio>

#include "DistrhoUI.h"

#include "DemoPlugin.h"
#include "DistrhoArtwork.h"

// -------------------------------------------------

class DemoUI : public DISTRHO::UI
{
public:
    DemoUI();
    ~DemoUI();

    // ---------------------------------------------
protected:

    // Information
    const char*  d_title();
    unsigned int d_width();
    unsigned int d_height();

    // DSP Callbacks
    void d_parameterChanged(uint32_t index, float value);
    void d_programChanged(uint32_t index);
#if DISTRHO_PLUGIN_WANT_STATE
    void d_stateChanged(const char* key, const char* value);
#endif

    // UI Callbacks
    void d_onInit();
    void d_onDisplay();
    void d_onKeyboard(bool press, uint32_t key);
    void d_onMotion(int x, int y);
    void d_onMouse(int button, bool press, int x, int y);
    void d_onReshape(int width, int height);
    void d_onScroll(float dx, float dy);
    void d_onSpecial(bool press, DISTRHO::Key key);
    void d_onClose();

private:
    float xAngle, yAngle, dist;

    void printModifiers()
    {
        int mods = d_getModifiers();
        fprintf(stderr, "Modifiers:%s%s%s%s\n",
                (mods & DISTRHO::MOD_SHIFT) ? " Shift"   : "",
                (mods & DISTRHO::MOD_CTRL)  ? " Ctrl"    : "",
                (mods & DISTRHO::MOD_ALT)   ? " Alt"     : "",
                (mods & DISTRHO::MOD_SUPER) ? " Super" : "");
    }

    static const int width  = DistrhoArtwork::backgroundWidth;
    static const int height = DistrhoArtwork::backgroundHeight;
};

// -------------------------------------------------

#endif // __DEMO_UI_H__
