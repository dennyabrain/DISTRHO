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

#include "DistrhoDefines.h"

#if defined(DISTRHO_PLUGIN_TARGET_DSSI) && DISTRHO_PLUGIN_HAS_UI

#include "DistrhoUIInternal.h"

#include <QtGui/QApplication>
#include <QtGui/QDialog>
#include <QtGui/QVBoxLayout>

#include <lo/lo.h>

// -------------------------------------------------

START_NAMESPACE_DISTRHO

struct OscData {
    lo_address  addr;
    const char* path;
    lo_server   server;
};

#if DISTRHO_PLUGIN_WANT_STATE
void osc_send_configure(const OscData* oscData, const char* const key, const char* const value)
{
    char targetPath[strlen(oscData->path)+11];
    strcpy(targetPath, oscData->path);
    strcat(targetPath, "/configure");
    lo_send(oscData->addr, targetPath, "ss", key, value);
}
#endif

void osc_send_control(const OscData* oscData, const int32_t index, const float value)
{
    char targetPath[strlen(oscData->path)+9];
    strcpy(targetPath, oscData->path);
    strcat(targetPath, "/control");
    lo_send(oscData->addr, targetPath, "if", index, value);
}

#if DISTRHO_PLUGIN_IS_SYNTH
void osc_send_midi(const OscData* oscData, unsigned char data[4])
{
    char targetPath[strlen(oscData->path)+6];
    strcpy(targetPath, oscData->path);
    strcat(targetPath, "/midi");
    lo_send(oscData->addr, targetPath, "m", data);
}
#endif

void osc_send_update(const OscData* oscData, const char* const url)
{
    char targetPath[strlen(oscData->path)+8];
    strcpy(targetPath, oscData->path);
    strcat(targetPath, "/update");
    lo_send(oscData->addr, targetPath, "s", url);
}

void osc_send_exiting(const OscData* oscData)
{
    char targetPath[strlen(oscData->path)+9];
    strcpy(targetPath, oscData->path);
    strcat(targetPath, "/exiting");
    lo_send(oscData->addr, targetPath, "");
}

class UIDssi : public QObject
{
public:
    UIDssi(const OscData* oscData_, const char* title)
        : dialog(nullptr),
#ifdef DISTRHO_UI_QT4
          vbLayout(&dialog),
#endif
          ui(this, dialog.winId(), changeStateCallback, setParameterValueCallback, uiResizeCallback),
          oscData(oscData_)
    {
#ifdef DISTRHO_UI_QT4
        dialog.setLayout(&vbLayout);
        vbLayout.addWidget(ui.getNativeWidget());
        vbLayout.setContentsMargins(0, 0, 0, 0);
#endif

        dialog.setFixedSize(ui.getWidth(), ui.getHeight());
        dialog.setWindowTitle(title);

        // TODO - block until first sample-rate is received
        // this should be 0, only start when sample-rate is known
        uiTimer = startTimer(30);
    }

    ~UIDssi()
    {
        if (uiTimer)
        {
            killTimer(uiTimer);
            osc_send_exiting(oscData);
        }

        dialog.close();
    }

    // ---------------------------------------------

#if DISTRHO_PLUGIN_WANT_STATE
    void dssiui_configure(const char* key, const char* value)
    {
        ui.stateChanged(key, value);
    }
#endif

    void dssiui_control(unsigned long index, float value)
    {
        // TODO - detect sample-rate parameter
        //ui.setSampleRate(value);

        if (long(index - DISTRHO_PLUGIN_NUM_INPUTS - DISTRHO_PLUGIN_NUM_OUTPUTS) < 0)
            return;

        ui.parameterChanged(index - DISTRHO_PLUGIN_NUM_INPUTS - DISTRHO_PLUGIN_NUM_OUTPUTS, value);
    }

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    void dssiui_program(unsigned long bank, unsigned long program)
    {
        unsigned long index = bank * 128 + program;
        ui.programChanged(index);
    }
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
    void dssiui_midi(unsigned char data[4])
    {
        // TODO
    }
#endif

    void dssiui_show()
    {
        dialog.show();
    }

    void dssiui_hide()
    {
        dialog.hide();
    }

    void dssiui_quit()
    {
        if (uiTimer)
        {
            killTimer(uiTimer);
            uiTimer = 0;
        }
        qApp->quit();
    }

    // ---------------------------------------------

protected:
#if DISTRHO_PLUGIN_WANT_STATE
    void changeState(const char* key, const char* value)
    {
        osc_send_configure(oscData, key, value);
    }
#endif

    void setParameterValue(uint32_t index, float value)
    {
        osc_send_control(oscData, index, value);
    }

    void uiResize(unsigned int width, unsigned int height)
    {
        dialog.setFixedSize(width, height);
    }

    void timerEvent(QTimerEvent* event)
    {
        if (event->timerId() == uiTimer)
        {
            ui.idle();

            while (lo_server_recv_noblock(oscData->server, 0) != 0) {}
        }

        QObject::timerEvent(event);
    }

private:
    // Qt4 stuff
    int uiTimer;
    QDialog dialog;
#ifdef DISTRHO_UI_QT4
    QVBoxLayout vbLayout;
#endif

    // Plugin UI
    UIInternal ui;

    const OscData* const oscData;

    // ---------------------------------------------
    // Callbacks

    static void changeStateCallback(void* ptr, const char* key, const char* value)
    {
#if DISTRHO_PLUGIN_WANT_STATE
        UIDssi* const _this_ = (UIDssi*)ptr;
        assert(_this_);

        _this_->changeState(key, value);
#else
        Q_UNUSED(ptr);
        Q_UNUSED(key);
        Q_UNUSED(value);
#endif
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

void osc_error_handler(const int num, const char* const msg, const char* const path)
{
    qCritical("osc_error_handler(%i, \"%s\", \"%s\")", num, msg, path);
}

#if DISTRHO_PLUGIN_WANT_STATE
int osc_configure_handler(const char* const, const char* const, lo_arg** const argv, const int, const lo_message, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    const char* const key   = &argv[0]->s;
    const char* const value = &argv[1]->s;
    qDebug("osc_configure_handler(\"%s\", \"%s\")", key, value);

    ui->dssiui_configure(key, value);

    return 0;
}
#endif

int osc_control_handler(const char* const, const char* const, lo_arg** const argv, const int, const lo_message, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    const int32_t index = argv[0]->i;
    const float   value = argv[1]->f;
    qDebug("osc_control_handler(%i, %f)", index, value);

    ui->dssiui_control(index, value);

    return 0;
}

#if DISTRHO_PLUGIN_WANT_PROGRAMS
int osc_program_handler(const char* const, const char* const, lo_arg** const argv, const int, const lo_message, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    const int32_t bank    = argv[0]->i;
    const int32_t program = argv[1]->f;
    qDebug("osc_program_handler(%i, %i)", bank, program);

    ui->dssiui_program(bank, program);

    return 0;
}
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
int osc_midi_handler(const char* const path, const char* const types, lo_arg** const argv, const int argc, const lo_message msg, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    const uint8_t* data = argv[0]->m;
    qDebug("osc_midi_handler(%p)", data);

    ui->dssiui_midi(data);

    return 0;
}
#endif

int osc_show_handler(const char* const, const char* const, lo_arg** const, const int, const lo_message, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    qDebug("osc_show_handler()");

    ui->dssiui_show();

    return 0;
}

int osc_hide_handler(const char* const, const char* const, lo_arg** const, const int, const lo_message, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    qDebug("osc_hide_handler()");

    ui->dssiui_hide();

    return 0;
}

int osc_quit_handler(const char* const, const char* const, lo_arg** const, const int, const lo_message, void* const data)
{
    UIDssi* const ui = (UIDssi*)data;

    qDebug("osc_quit_handler()");

    ui->dssiui_quit();
    delete ui;

    return 0;
}

int osc_debug_handler(const char* const path, const char* const, lo_arg** const, const int, const lo_message, void* const)
{
    qDebug("osc_debug_handler(\"%s\")", path);

    return 0;
}

END_NAMESPACE_DISTRHO

int main(int argc, char* argv[])
{
    USE_NAMESPACE_DISTRHO

    if (argc != 5)
    {
        qWarning("Usage: %s <osc-url> <so-file> <plugin-label> <instance-name>", argv[0]);
        return 1;
    }

    const char* oscUrl  = argv[1];
    const char* uiTitle = argv[4];

    char* const oscHost = lo_url_get_hostname(oscUrl);
    char* const oscPort = lo_url_get_port(oscUrl);
    char* const oscPath = lo_url_get_path(oscUrl);
    size_t  oscPathSize = strlen(oscPath);
    lo_address  oscAddr = lo_address_new(oscHost, oscPort);
    lo_server oscServer = lo_server_new(nullptr, osc_error_handler);

    OscData oscData = { oscAddr, oscPath, oscServer };

    QApplication app(argc, argv, true);
    UIDssi* const ui = new UIDssi(&oscData, uiTitle);

#if DISTRHO_PLUGIN_WANT_STATE
    char oscPathConfigure[oscPathSize+11];
    strcpy(oscPathConfigure, oscPath);
    strcat(oscPathConfigure, "/configure");
    lo_server_add_method(oscServer, oscPathConfigure, "ss", osc_configure_handler, ui);
#endif

    char oscPathControl[oscPathSize+9];
    strcpy(oscPathControl, oscPath);
    strcat(oscPathControl, "/control");
    lo_server_add_method(oscServer, oscPathControl, "if", osc_control_handler, ui);

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    char oscPathProgram[oscPathSize+9];
    strcpy(oscPathProgram, oscPath);
    strcat(oscPathProgram, "/program");
    lo_server_add_method(oscServer, oscPathProgram, "ii", osc_program_handler, ui);
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
    char oscPathMidi[oscPathSize+6];
    strcpy(oscPathMidi, oscPath);
    strcat(oscPathMidi, "/midi");
    lo_server_add_method(oscServer, oscPathMidi, "m", osc_midi_handler, ui);
#endif

    char oscPathShow[oscPathSize+6];
    strcpy(oscPathShow, oscPath);
    strcat(oscPathShow, "/show");
    lo_server_add_method(oscServer, oscPathShow, "", osc_show_handler, ui);

    char oscPathHide[oscPathSize+6];
    strcpy(oscPathHide, oscPath);
    strcat(oscPathHide, "/hide");
    lo_server_add_method(oscServer, oscPathHide, "", osc_hide_handler, ui);

    char oscPathQuit[oscPathSize+6];
    strcpy(oscPathQuit, oscPath);
    strcat(oscPathQuit, "/quit");
    lo_server_add_method(oscServer, oscPathQuit, "", osc_quit_handler, ui);

    lo_server_add_method(oscServer, nullptr, nullptr, osc_debug_handler, nullptr);

    char* const serverPath = lo_server_get_url(oscServer);
    char* const pluginPath = strdup(QString("%1%2").arg(serverPath).arg(oscPathSize > 1 ? oscPath + 1 : oscPath).toUtf8().constData());
    free(serverPath);

    osc_send_update(&oscData, pluginPath);

    ui->dssiui_show();

    // TODO - block until first sample-rate is received

    int ret = app.exec();

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
    lo_server_del_method(oscServer, oscPathShow, "");
    lo_server_del_method(oscServer, oscPathHide, "");
    lo_server_del_method(oscServer, oscPathQuit, "");

    delete ui;

    lo_server_free(oscServer);

    free(oscHost);
    free(oscPort);
    free(oscPath);
    free(pluginPath);

    lo_address_free(oscAddr);

    return ret;
}

// -------------------------------------------------

#endif // DISTRHO_PLUGIN_TARGET_DSSI && DISTRHO_PLUGIN_HAS_UI
