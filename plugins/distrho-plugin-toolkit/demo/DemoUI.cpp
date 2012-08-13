// demo plugin

#include "DemoUI.h"
#include "DemoPlugin.h"

// -------------------------------------------------

DemoUI::DemoUI() : DISTRHO::UI(DemoPlugin::PARAMETER_COUNT)
{
    xAngle = 0.0f;
    yAngle = 0.0f;
    dist   = 10.0f;
}

DemoUI::~DemoUI()
{
}

// -------------------------------------------------
// Information

const char* DemoUI::d_title()
{
    return "Stereo Audio Gain";
}

unsigned int DemoUI::d_width()
{
    return width;
}

unsigned int DemoUI::d_height()
{
    return height;
}

// -------------------------------------------------
// DSP Callbacks

void DemoUI::d_parameterChanged(uint32_t index, float value)
{
    (void)index;
    (void)value;
}

void DemoUI::d_programChanged(uint32_t index)
{
    (void)index;
}

#if DISTRHO_PLUGIN_WANT_STATE
void DemoUI::d_stateChanged(const char*, const char*)
{
}
#endif

// -------------------------------------------------
// UI Callbacks

void DemoUI::d_onInit()
{
}

void DemoUI::d_onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // background pic
    glRasterPos2i(0, height);
    glDrawPixels(DistrhoArtwork::backgroundWidth, DistrhoArtwork::backgroundHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::backgroundData);

    // sliders
    glRasterPos2i(49, 157);
    glDrawPixels(DistrhoArtwork::sliderWidth, DistrhoArtwork::sliderHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::sliderData);

    glRasterPos2i(115, 157);
    glDrawPixels(DistrhoArtwork::sliderWidth, DistrhoArtwork::sliderHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::sliderData);

    glRasterPos2i(178, 157);
    glDrawPixels(DistrhoArtwork::sliderWidth, DistrhoArtwork::sliderHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::sliderData);

    glRasterPos2i(282, 157);
    glDrawPixels(DistrhoArtwork::sliderWidth, DistrhoArtwork::sliderHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::sliderData);

    // knobs
    glRasterPos2i(66, 330);
    glDrawPixels(DistrhoArtwork::knobWidth, DistrhoArtwork::knobHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::knobData);

    glRasterPos2i(160, 330);
    glDrawPixels(DistrhoArtwork::knobWidth, DistrhoArtwork::knobHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::knobData);
}

void DemoUI::d_onKeyboard(bool press, uint32_t key)
{
//    fprintf(stderr, "Key %c %s ", (char)key, press ? "down" : "up");
//    printModifiers();
    (void)press;
    (void)key;
}

void DemoUI::d_onMotion(int x, int y)
{
    xAngle = x % 360;
    yAngle = y % 360;
    d_postRedisplay();
}

void DemoUI::d_onMouse(int button, bool press, int x, int y)
{
//    fprintf(stderr, "Mouse %d %s at %d,%d ", button, press ? "down" : "up", x, y);
//    printModifiers();
    (void)button;
    (void)press;
    (void)x;
    (void)y;
}

void DemoUI::d_onReshape(int width, int height)
{
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_TEXTURE_2D);
    //glDisable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_COLOR_LOGIC_OP);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)width, (GLdouble)height, 0.0);

    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    glLoadIdentity();
}

void DemoUI::d_onScroll(float dx, float dy)
{
//    fprintf(stderr, "Scroll %f %f ", dx, dy);
//    printModifiers();
//    dist += dy / 4.0f;
//    d_postRedisplay();
    (void)dx;
    (void)dy;
}

void DemoUI::d_onSpecial(bool press, DISTRHO::Key key)
{
//    fprintf(stderr, "Special key %d %s ", key, press ? "down" : "up");
//    printModifiers();
    (void)press;
    (void)key;
}

void DemoUI::d_onClose()
{
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

UI* createUI()
{
    return new DemoUI;
}

END_NAMESPACE_DISTRHO
