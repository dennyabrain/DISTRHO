/*
 * DISTRHO Plugin Toolkit (DPT)
 * Copyright (C) 2012-2013 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoUIInternal.hpp"

#ifdef DISTRHO_UI_EXTERNAL
# error DSSI always uses external UI, no wrapper neeed!
#endif

#include <lo/lo.h>

#ifdef DISTRHO_UI_QT
# include <QtGui/QApplication>
# include <QtGui/QMainWindow>
#else
# include "dgl/App.hpp"
# include "dgl/Window.hpp"
#endif

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

struct OscData {
    lo_address  addr;
    const char* path;
    lo_server   server;

    OscData()
        : addr(nullptr),
          path(nullptr),
          server(nullptr) {}

    void idle() const
    {
        if (server == nullptr)
            return;

        while (lo_server_recv_noblock(server, 0) != 0) {}
    }

    void send_configure(const char* const key, const char* const value) const
    {
        char targetPath[std::strlen(path)+11];
        std::strcpy(targetPath, path);
        std::strcat(targetPath, "/configure");
        lo_send(addr, targetPath, "ss", key, value);
    }

    void send_control(const int32_t index, const float value) const
    {
        char targetPath[std::strlen(path)+9];
        std::strcpy(targetPath, path);
        std::strcat(targetPath, "/control");
        lo_send(addr, targetPath, "if", index, value);
    }

    void send_midi(unsigned char data[4]) const
    {
        char targetPath[std::strlen(path)+6];
        std::strcpy(targetPath, path);
        std::strcat(targetPath, "/midi");
        lo_send(addr, targetPath, "m", data);
    }

    void send_update(const char* const url) const
    {
        char targetPath[std::strlen(path)+8];
        std::strcpy(targetPath, path);
        std::strcat(targetPath, "/update");
        lo_send(addr, targetPath, "s", url);
    }

    void send_exiting() const
    {
        char targetPath[std::strlen(path)+9];
        std::strcpy(targetPath, path);
        std::strcat(targetPath, "/exiting");
        lo_send(addr, targetPath, "");
    }
};

// -----------------------------------------------------------------------

#ifdef DISTRHO_UI_QT
class UIDssi : public QMainWindow
#else
class UIDssi
#endif
{
public:
    UIDssi(const OscData& oscData, const char* const uiTitle)
#ifdef DISTRHO_UI_QT
        : QMainWindow(nullptr),
          fUI(this, 0, nullptr, setParameterCallback, setStateCallback, uiSendNoteCallback, uiResizeCallback),
          fHostClosed(false),
          qtTimer(0),
#else
        : fUI(this, 0, nullptr, setParameterCallback, setStateCallback, uiSendNoteCallback, uiResizeCallback),
          fHostClosed(false),
          glApp(fUI.getApp()),
          glWindow(fUI.getWindow()),
#endif
          fOscData(oscData)
    {
#ifdef DISTRHO_UI_QT
        QtUI* const qtUI(fUI.getQt4Ui());

        setCentralWidget(qtUI);
        setWindowTitle(uiTitle);

        if (qtUI->d_resizable())
        {
            adjustSize();
        }
        else
        {
            setFixedSize(qtUI->width(), qtUI->height());
# ifdef DISTRHO_OS_WINDOWS
            setWindowFlags(windowFlags()|Qt::MSWindowsFixedSizeDialogHint);
# endif
        }
#else
        glWindow.setSize(fUI.width(), fUI.height());
        glWindow.setWindowTitle(uiTitle);
#endif
    }

    ~UIDssi()
    {
#ifdef DISTRHO_UI_QT
        if (qtTimer != 0)
        {
            killTimer(qtTimer);
            qtTimer = 0;
        }
#endif

        if (fOscData.server != nullptr && ! fHostClosed)
            fOscData.send_exiting();
    }

    void exec()
    {
#ifdef DISTRHO_UI_QT
        assert(qtTimer == 0);

        qtTimer = startTimer(50);
        qApp->exec();
#else
        while (! glApp.isQuiting())
        {
            fOscData.idle();
            fUI.idle();
            dgl_msleep(50);
        }
#endif
    }

    // -------------------------------------------------------------------

#if DISTRHO_PLUGIN_WANT_STATE
    void dssiui_configure(const char* key, const char* value)
    {
        fUI.stateChanged(key, value);
    }
#endif

    void dssiui_control(unsigned long index, float value)
    {
        fUI.parameterChanged(index, value);
    }

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    void dssiui_program(unsigned long bank, unsigned long program)
    {
        fUI.programChanged(bank * 128 + program);
    }
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
    void dssiui_midi(uint8_t data[4])
    {
        uint8_t status  = data[1] & 0xF0;
        uint8_t channel = data[1] & 0x0F;

        // fix bad note-off
        if (status == 0x90 && data[3] == 0)
            status -= 0x10;

        if (status == 0x80)
        {
            uint8_t note = data[2];
            fUI.noteReceived(false, channel, note, 0);
        }
        else if (status == 0x90)
        {
            uint8_t note = data[2];
            uint8_t velo = data[3];
            fUI.noteReceived(true, channel, note, velo);
        }
    }
#endif

    void dssiui_show()
    {
#ifdef DISTRHO_UI_QT
        show();
#else
        glWindow.show();
#endif
    }

    void dssiui_hide()
    {
#ifdef DISTRHO_UI_QT
        hide();
#else
        glWindow.hide();
#endif
    }

    void dssiui_quit()
    {
        fHostClosed = true;

#ifdef DISTRHO_UI_QT
        if (qtTimer != 0)
        {
            killTimer(qtTimer);
            qtTimer = 0;
        }
        close();
        qApp->quit();
#else
        glWindow.close();
        glApp.quit();
#endif
    }

    // -------------------------------------------------------------------

protected:
    void setParameterValue(uint32_t rindex, float value)
    {
        if (fOscData.server == nullptr)
            return;

        fOscData.send_control(rindex, value);
    }

    void setState(const char* key, const char* value)
    {
        if (fOscData.server == nullptr)
            return;

        fOscData.send_configure(key, value);
    }

    void uiSendNote(bool onOff, uint8_t channel, uint8_t note, uint8_t velocity)
    {
        if (fOscData.server == nullptr)
            return;
        if (channel > 0xF)
            return;

        uint8_t mdata[4] = { 0, channel, note, velocity };
        mdata[1] += onOff ? 0x90 : 0x80;

        fOscData.send_midi(mdata);
    }

    void uiResize(unsigned int width, unsigned int height)
    {
#ifdef DISTRHO_UI_QT
        setFixedSize(width, height);
#else
        glWindow.setSize(width, height);
#endif
    }

#ifdef DISTRHO_UI_QT
    void timerEvent(QTimerEvent* event)
    {
        if (event->timerId() == uiTimer)
        {
            fOscData.idle();
            fUI.idle();
        }

        QMainWindow::timerEvent(event);
    }
#endif

private:
    // Plugin UI
    UIInternal fUI;
    bool fHostClosed;

#ifdef DISTRHO_UI_QT
    // Qt4 stuff
    int qtTimer;
#else
    // OpenGL stuff
    App& glApp;
    Window& glWindow;
#endif

    const OscData& fOscData;

    // -------------------------------------------------------------------
    // Callbacks

    #define uiPtr ((UIDssi*)ptr)

    static void setParameterCallback(void* ptr, uint32_t rindex, float value)
    {
        uiPtr->setParameterValue(rindex, value);
    }

    static void setStateCallback(void* ptr, const char* key, const char* value)
    {
        uiPtr->setState(key, value);
    }

    static void uiSendNoteCallback(void* ptr, bool onOff, uint8_t channel, uint8_t note, uint8_t velocity)
    {
        uiPtr->uiSendNote(onOff, channel, note, velocity);
    }

    static void uiResizeCallback(void* ptr, unsigned int width, unsigned int height)
    {
        uiPtr->uiResize(width, height);
    }

    #undef uiPtr
};

// -----------------------------------------------------------------------

static OscData     gOscData;
static const char* gUiTitle = nullptr;
static UIDssi*     globalUI = nullptr;

static void initUiIfNeeded()
{
    if (globalUI != nullptr)
        return;

    if (d_lastUiSampleRate == 0.0)
        d_lastUiSampleRate = 44100.0;

    globalUI = new UIDssi(gOscData, gUiTitle);
}

// -----------------------------------------------------------------------

int osc_debug_handler(const char* path, const char*, lo_arg**, int, lo_message, void*)
{
    d_debug("osc_debug_handler(\"%s\")", path);
    return 0;
}

void osc_error_handler(int num, const char* msg, const char* path)
{
    d_stderr("osc_error_handler(%i, \"%s\", \"%s\")", num, msg, path);
}

#if DISTRHO_PLUGIN_WANT_STATE
int osc_configure_handler(const char*, const char*, lo_arg** argv, int, lo_message, void*)
{
    const char* const key   = &argv[0]->s;
    const char* const value = &argv[1]->s;
    d_debug("osc_configure_handler(\"%s\", \"%s\")", key, value);

    initUiIfNeeded();

    globalUI->dssiui_configure(key, value);

    return 0;
}
#endif

int osc_control_handler(const char*, const char*, lo_arg** argv, int, lo_message, void*)
{
    const int32_t rindex = argv[0]->i;
    const float   value  = argv[1]->f;
    d_debug("osc_control_handler(%i, %f)", rindex, value);

    int32_t index = rindex - DISTRHO_PLUGIN_NUM_INPUTS - DISTRHO_PLUGIN_NUM_OUTPUTS;

    // latency
#if DISTRHO_PLUGIN_WANT_LATENCY
    index -= 1;
#endif

    if (index < 0)
        return 0;

    initUiIfNeeded();

    globalUI->dssiui_control(index, value);

    return 0;
}

#if DISTRHO_PLUGIN_WANT_PROGRAMS
int osc_program_handler(const char*, const char*, lo_arg** argv, int, lo_message, void*)
{
    const int32_t bank    = argv[0]->i;
    const int32_t program = argv[1]->f;
    d_debug("osc_program_handler(%i, %i)", bank, program);

    initUiIfNeeded();

    globalUI->dssiui_program(bank, program);

    return 0;
}
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
int osc_midi_handler(const char*, const char*, lo_arg** argv, int, lo_message, void*)
{
    d_debug("osc_midi_handler()");

    initUiIfNeeded();

    globalUI->dssiui_midi(argv[0]->m);

    return 0;
}
#endif

int osc_sample_rate_handler(const char*, const char*, lo_arg** argv, int, lo_message, void*)
{
    const int32_t sampleRate = argv[0]->i;
    d_debug("osc_sample_rate_handler(%i)", sampleRate);

    d_lastUiSampleRate = sampleRate;

    return 0;
}

int osc_show_handler(const char*, const char*, lo_arg**, int, lo_message, void*)
{
    d_debug("osc_show_handler()");

    initUiIfNeeded();

    globalUI->dssiui_show();

    return 0;
}

int osc_hide_handler(const char*, const char*, lo_arg**, int, lo_message, void*)
{
    d_debug("osc_hide_handler()");

    if (globalUI != nullptr)
       globalUI->dssiui_hide();

    return 0;
}

int osc_quit_handler(const char*, const char*, lo_arg**, int, lo_message, void*)
{
    d_debug("osc_quit_handler()");

    if (globalUI != nullptr)
        globalUI->dssiui_quit();
#ifdef DISTRHO_UI_QT
    else if (QApplication* app = qApp)
        app->quit();
#endif

    return 0;
}

END_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

int main(int argc, char* argv[])
{
    USE_NAMESPACE_DISTRHO

    // dummy test mode
    if (argc == 1)
    {
#ifdef DISTRHO_UI_QT
        QApplication app(argc, argv, true);
#endif
        gUiTitle = "DSSI UI Test";

        initUiIfNeeded();
        globalUI->dssiui_show();
        globalUI->exec();

        return 0;
    }

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <osc-url> <plugin-dll> <plugin-label> <instance-name>\n", argv[0]);
        return 1;
    }

#ifdef DISTRHO_UI_QT
    QApplication app(argc, argv, true);
#endif

    const char* oscUrl  = argv[1];
    const char* uiTitle = argv[4];

    char* const oscHost = lo_url_get_hostname(oscUrl);
    char* const oscPort = lo_url_get_port(oscUrl);
    char* const oscPath = lo_url_get_path(oscUrl);
    size_t  oscPathSize = strlen(oscPath);
    lo_address  oscAddr = lo_address_new(oscHost, oscPort);
    lo_server oscServer = lo_server_new_with_proto(nullptr, LO_UDP, osc_error_handler);

    char* const oscServerPath = lo_server_get_url(oscServer);

    char pluginPath[strlen(oscServerPath)+oscPathSize];
    strcpy(pluginPath, oscServerPath);
    strcat(pluginPath, oscPath+1);

#if DISTRHO_PLUGIN_WANT_STATE
    char oscPathConfigure[oscPathSize+11];
    strcpy(oscPathConfigure, oscPath);
    strcat(oscPathConfigure, "/configure");
    lo_server_add_method(oscServer, oscPathConfigure, "ss", osc_configure_handler, nullptr);
#endif

    char oscPathControl[oscPathSize+9];
    strcpy(oscPathControl, oscPath);
    strcat(oscPathControl, "/control");
    lo_server_add_method(oscServer, oscPathControl, "if", osc_control_handler, nullptr);

    d_stdout("oscServerPath:  \"%s\"", oscServerPath);
    d_stdout("pluginPath:     \"%s\"", pluginPath);
    d_stdout("oscPathControl: \"%s\"", oscPathControl);

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    char oscPathProgram[oscPathSize+9];
    strcpy(oscPathProgram, oscPath);
    strcat(oscPathProgram, "/program");
    lo_server_add_method(oscServer, oscPathProgram, "ii", osc_program_handler, nullptr);
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
    char oscPathMidi[oscPathSize+6];
    strcpy(oscPathMidi, oscPath);
    strcat(oscPathMidi, "/midi");
    lo_server_add_method(oscServer, oscPathMidi, "m", osc_midi_handler, nullptr);
#endif

    char oscPathSampleRate[oscPathSize+13];
    strcpy(oscPathSampleRate, oscPath);
    strcat(oscPathSampleRate, "/sample-rate");
    lo_server_add_method(oscServer, oscPathSampleRate, "i", osc_sample_rate_handler, nullptr);

    char oscPathShow[oscPathSize+6];
    strcpy(oscPathShow, oscPath);
    strcat(oscPathShow, "/show");
    lo_server_add_method(oscServer, oscPathShow, "", osc_show_handler, nullptr);

    char oscPathHide[oscPathSize+6];
    strcpy(oscPathHide, oscPath);
    strcat(oscPathHide, "/hide");
    lo_server_add_method(oscServer, oscPathHide, "", osc_hide_handler, nullptr);

    char oscPathQuit[oscPathSize+6];
    strcpy(oscPathQuit, oscPath);
    strcat(oscPathQuit, "/quit");
    lo_server_add_method(oscServer, oscPathQuit, "", osc_quit_handler, nullptr);

    lo_server_add_method(oscServer, nullptr, nullptr, osc_debug_handler, nullptr);

    gUiTitle = uiTitle;

    gOscData.addr   = oscAddr;
    gOscData.path   = oscPath;
    gOscData.server = oscServer;
    gOscData.send_update(pluginPath);

    // wait for init
    for (int i=0; i < 100; ++i)
    {
        lo_server_recv(oscServer);

        if (d_lastUiSampleRate != 0.0 || globalUI != nullptr)
            break;

        d_msleep(50);
    }

    int ret = 1;

    if (d_lastUiSampleRate != 0.0 || globalUI != nullptr)
    {
        initUiIfNeeded();

        globalUI->exec();

        delete globalUI;
        globalUI = nullptr;

        ret = 0;
    }

#if DISTRHO_PLUGIN_WANT_STATE
    lo_server_del_method(oscServer, oscPathConfigure, "ss");
#endif
    lo_server_del_method(oscServer, oscPathControl, "if");
#if DISTRHO_PLUGIN_WANT_PROGRAMS
    lo_server_del_method(oscServer, oscPathProgram, "ii");
#endif
#if DISTRHO_PLUGIN_IS_SYNTH
    lo_server_del_method(oscServer, oscPathMidi, "m");
#endif
    lo_server_del_method(oscServer, oscPathSampleRate, "i");
    lo_server_del_method(oscServer, oscPathShow, "");
    lo_server_del_method(oscServer, oscPathHide, "");
    lo_server_del_method(oscServer, oscPathQuit, "");
    lo_server_del_method(oscServer, nullptr, nullptr);

    free(oscServerPath);
    free(oscHost);
    free(oscPort);
    free(oscPath);

    lo_address_free(oscAddr);
    lo_server_free(oscServer);

    return ret;
}
