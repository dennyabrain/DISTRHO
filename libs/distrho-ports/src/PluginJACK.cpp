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
 * A copy of the license is included with this software, or can be
 * found online at www.gnu.org/licenses.
 */

#include "PluginBase.h"
#include "UiBase.h"

#if ! DISTRHO_PLUGIN_WANTS_UI
#error JACK Standalone version requires UI
#endif

#include <cstdio>
#include <jack/jack.h>

#include <QtCore/QTimer>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>

#include "ui_PluginJACK.h"

namespace Ui {
class MainWindow;
}

class DistrhoPluginJACK : public QMainWindow
{
    Q_OBJECT

public:
    DistrhoPluginJACK() :
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        m_plugin = createDistrhoPlugin();
        m_plugin->d_init();

        j_client = jack_client_open(m_plugin->d_name(), JackNullOption, 0);

        if (j_client)
        {
            m_plugin->__setSampleRate(jack_get_sample_rate(j_client));
            m_plugin->__setBufferSize(jack_get_buffer_size(j_client));

            char port_name[11] = { 0 };

#if DISTRHO_PLUGIN_NUM_INPUTS > 0
            for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            {
                sprintf(port_name, "input_%i", i);
                jack_port_t* port = jack_port_register(j_client, port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
                j_ains.push_back(port);
            }
#endif

            for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            {
                sprintf(port_name, "output_%i", i);
                jack_port_t* port = jack_port_register(j_client, port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
                j_aouts.push_back(port);
            }

            jack_set_process_callback(j_client, j_process_callback, this);
            jack_activate(j_client);
        }

        m_ui = createDistrhoUI();
        m_ui->setParent(this);

        ui->centralwidget->layout()->addWidget(m_ui);
        setWindowTitle(m_plugin->d_name());
        adjustSize();

        connect(m_ui, SIGNAL(d_parameterChanged(quint32,float)), this, SLOT(pluginParameterChanged(quint32,float)));
        QTimer::singleShot(0, this, SLOT(recheckParameters()));
    }

    ~DistrhoPluginJACK()
    {
        if (j_client)
        {
            jack_deactivate(j_client);
            jack_client_close(j_client);
        }

        j_ains.clear();
        j_aouts.clear();

        m_plugin->d_cleanup();

        delete m_ui;
        delete m_plugin;
    }

    void process(jack_nframes_t nframes)
    {
        float* p_ains[DISTRHO_PLUGIN_NUM_INPUTS];
        float* p_aouts[DISTRHO_PLUGIN_NUM_OUTPUTS];

#if DISTRHO_PLUGIN_NUM_INPUTS > 0
        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            p_ains[i] = (float*)jack_port_get_buffer(j_ains[i], nframes);
#endif

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            p_aouts[i] = (float*)jack_port_get_buffer(j_aouts[i], nframes);

        m_plugin->d_run(p_ains, p_aouts, nframes, 0, nullptr);
    }

    static int j_process_callback(jack_nframes_t nframes, void* arg)
    {
        if (arg)
        {
            DistrhoPluginJACK* _this_ = (DistrhoPluginJACK*)arg;
            _this_->process(nframes);
        }

        return 0;
    }

protected:
    Ui::MainWindow* ui;

protected slots:
    void pluginParameterChanged(quint32 index, float value)
    {
        m_plugin->d_setParameterValue(index, value);
    }

    void recheckParameters()
    {
        if (m_plugin && m_ui)
        {
            const ParameterInfo* info;
            for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++)
            {
                info = m_plugin->d_parameterInfo(i);

                if (info && (info->hints & PARAMETER_IS_OUTPUT) > 0)
                    m_ui->d_setParameterValue(i, m_plugin->d_parameterValue(i));
            }
        }
        QTimer::singleShot(25, this, SLOT(recheckParameters()));
    }

private:
    DistrhoPluginBase* m_plugin;
    DistrhoUiBase* m_ui;

    jack_client_t* j_client;
    std::vector<jack_port_t*> j_ains;
    std::vector<jack_port_t*> j_aouts;
};

#include "PluginJACK.moc"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv, true);
    DistrhoPluginJACK pGui;
    pGui.show();
    app.exec();
}
