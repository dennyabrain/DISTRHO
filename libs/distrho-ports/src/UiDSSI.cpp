// distrho lv2 ui

#include "DistrhoPlugin.h"

#if DISTRHO_PLUGIN_WANTS_UI

#include "PluginBase.h"
#include "UiBase.h"

#include <QtCore/QTimer>
#include <QtGui/QApplication>

#include <lo/lo.h>

// ---------------------------------------------------------------------------------------------
// forward declarations

void osc_error_handler(int num, const char* msg, const char* path);
int  osc_message_handler(const char* path, const char* types, lo_arg** argv, int argc, void* data, void* user_data);

// ---------------------------------------------------------------------------------------------

class DistrhoUiDssi : public QObject
{
    Q_OBJECT

public:
    DistrhoUiDssi(const char* osc_url) :
        QObject(nullptr)
    {
        m_ui = createDistrhoUI();

        const char* host = lo_url_get_hostname(osc_url);
        const char* port = lo_url_get_port(osc_url);

        osc_path   = lo_url_get_path(osc_url);
        osc_target = lo_address_new(host, port);

        free((void*)host);
        free((void*)port);

        osc_server_thread = lo_server_thread_new(nullptr, osc_error_handler);
        lo_server_thread_add_method(osc_server_thread, nullptr, nullptr, osc_message_handler, nullptr);
        lo_server_thread_start(osc_server_thread);

        controlPortOffset  = 0;
#if DISTRHO_PLUGIN_IS_SYNTH
        controlPortOffset += 1;
#endif
        controlPortOffset += DISTRHO_PLUGIN_NUM_INPUTS;
        controlPortOffset += DISTRHO_PLUGIN_NUM_OUTPUTS;

        connect(m_ui, SIGNAL(parameterChanged(quint32,float)), this, SLOT(pluginParameterChanged(quint32,float)));

        osc_send_update();
    }

    ~DistrhoUiDssi()
    {
        osc_send_exiting();

        free((void*)osc_path);
        lo_address_free(osc_target);

        lo_server_thread_stop(osc_server_thread);
        lo_server_thread_del_method(osc_server_thread, nullptr, nullptr);
        lo_server_thread_free(osc_server_thread);

        m_ui->close();
        delete m_ui;
    }

    // -----------------------------------------------------------------------------------------

    void osc_handle_control(int param, float value)
    {
        if (param >= 0)
            m_ui->d_setParameterValue(param, value);
    }

    void osc_handle_show()
    {
        m_ui->show();
    }

    void osc_handle_hide()
    {
        m_ui->hide();
    }

    void osc_handle_exit()
    {
        m_ui->close();
    }

    // -----------------------------------------------------------------------------------------

private slots:
    void pluginParameterChanged(quint32 index, float value)
    {
        osc_send_control(index+controlPortOffset, value);
    }

private:
    DistrhoUiBase* m_ui;
    uint32_t controlPortOffset;

    char* osc_path;
    lo_address osc_target;
    lo_server_thread  osc_server_thread;

    void osc_send_update()
    {
        char target_path[strlen(osc_path)+8];
        strcpy(target_path, osc_path);
        strcat(target_path, "/update");
        //lo_send(osc_target, target_path, "s", osc_server_path);
    }

    void osc_send_exiting()
    {
        char target_path[strlen(osc_path)+9];
        strcpy(target_path, osc_path);
        strcat(target_path, "/exiting");
        lo_send(osc_target, target_path, "");
    }

    void osc_send_control(int param, float value)
    {
        char target_path[strlen(osc_path)+9];
        strcpy(target_path, osc_path);
        strcat(target_path, "/control");
        lo_send(osc_target, target_path, "if", param, value);
    }
};

#include "UiDSSI.moc"

// ---------------------------------------------------------------------------------------------

void osc_error_handler(int num, const char* msg, const char* path)
{
    qCritical("osc_error_handler(%i, %s, %s)", num, msg, path);
}

int osc_message_handler(const char* path, const char* types, lo_arg** argv, int argc, void* data, void* user_data)
{
    qDebug("osc_message_handler(%s, %s, %p, %i, %p, %p)", path, types, argv, argc, data, user_data);
    // TODO
    return 0;
}

// ---------------------------------------------------------------------------------------------

DISTRHO_PLUGIN_EXPORT
void dssiui_descriptor(const char* osc_url)
{
    int argc = 0;
    char* argv[] = { nullptr };
    QApplication app(argc, argv, true);
    DistrhoUiDssi pGui(osc_url);
    //app.setQuitOnLastWindowClosed(true);
    app.exec();

    //Q_UNUSED(pGui);
}

#endif // DISTRHO_PLUGIN_WANTS_UI
