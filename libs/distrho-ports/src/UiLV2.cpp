// distrho lv2 ui

#include "DistrhoPlugin.h"

#if DISTRHO_PLUGIN_WANTS_UI
#include "PluginBase.h"
#include "UiBase.h"

#ifdef Q_OS_LINUX
#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QSizeGrip>
#include <QtGui/QVBoxLayout>
#include <QtGui/QX11EmbedWidget>
#endif

#include "lv2-sdk/ui.h"

class DistrhoUiLv2 : public QObject
{
    Q_OBJECT

public:
    DistrhoUiLv2(LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, bool isX11) :
        QObject(nullptr),
    #ifdef Q_OS_LINUX
        m_app(nullptr),
        m_x11Container(nullptr),
        m_grip(nullptr),
        m_gripMouseDown(false),
        m_minWidth(10),
        m_minHeight(10),
    #endif
        ui_controller(controller),
        ui_writeFunction(write_function),
        ui_resize(nullptr),
        ui_touch(nullptr)
    {
        // create QApplication if needed
        if (! QApplication::instance())
        {
            static int argc = 0;
            static char* argv[] = { nullptr };
            m_app = new QApplication(argc, argv, true);
            m_app->setQuitOnLastWindowClosed(true);
        }

        m_ui = createDistrhoUI();

        // Get UI Touch feature
        for (quint32 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_UI__touch) == 0 && features[i]->data)
            {
                ui_touch = (LV2UI_Touch*)features[i]->data;
                break;
            }
        }

#ifdef Q_OS_LINUX
        if (isX11)
        {
            // Get UI Resize feature
            for (quint32 i = 0; features[i]; i++)
            {
                if (strcmp(features[i]->URI, LV2_UI__resize) == 0 && features[i]->data)
                {
                    ui_resize = (LV2UI_Resize*)features[i]->data;
                    break;
                }
            }

            // Get parent Id
            WId parent = 0;

            for (quint32 i=0; features[i]; i++)
            {
                if (strcmp(features[i]->URI, LV2_UI__parent) == 0 && features[i]->data)
                {
                    parent = (WId)features[i]->data;
                    break;
                }
            }

            // Create embedable widget
            m_x11Container = new QX11EmbedWidget;
            m_x11Container->resize(10, 10);
            m_x11Container->setLayout(new QVBoxLayout(m_x11Container));
            m_x11Container->layout()->addWidget(m_ui);
            m_x11Container->layout()->setContentsMargins(2, 2, 2, 2);
            m_x11Container->adjustSize();

            // Create resize grip
            if (m_ui->isUiResizable())
            {
                m_grip = new QSizeGrip(m_x11Container);
                m_grip->resize(m_grip->sizeHint());
                m_grip->installEventFilter(this);
            }

            // Embed window
            m_x11Container->embedInto(parent);
            m_x11Container->show();

            // Set size
            m_minWidth  = m_x11Container->width();
            m_minHeight = m_x11Container->height();
            resize_x11(m_minWidth, m_minHeight);

            *widget = (void*)m_x11Container->winId();
        }
        else
#else
        Q_UNUSED(isX11);
#endif
            // Qt4 UI
            *widget = m_ui;

        controlPortOffset  = 0;
#if DISTRHO_PLUGIN_IS_SYNTH
        controlPortOffset += 1;
#endif
        controlPortOffset += DISTRHO_PLUGIN_NUM_INPUTS;
        controlPortOffset += DISTRHO_PLUGIN_NUM_OUTPUTS;

        connect(m_ui, SIGNAL(parameterChanged(uint32_t,float)), this, SLOT(pluginParameterChanged(uint32_t,float)));
    }

    virtual ~DistrhoUiLv2()
    {
        m_ui->close();
        delete m_ui;

#ifdef Q_OS_LINUX
        if (m_grip)
            delete m_grip;

        if (m_x11Container)
        {
            m_x11Container->close();
            delete m_x11Container;
        }
#endif
    }

    void lv2_port_event(uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer)
    {
        if (m_ui)
        {
            if (format == 0 && buffer_size == sizeof(float))
            {
                const float value = *(float*)buffer;
                m_ui->setParameterValue(port_index-controlPortOffset, value);
            }
        }
    }

#ifdef Q_OS_LINUX
protected:
    bool eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mEvent = (QMouseEvent*)event;
            if (mEvent->button() == Qt::LeftButton)
                m_gripMouseDown = true;
            return true;
        }
        else if (event->type() == QEvent::MouseMove)
        {
            if (m_gripMouseDown)
            {
                QMouseEvent* mEvent = (QMouseEvent*)event;
                int width  = m_x11Container->width()  + mEvent->x() - m_grip->width();
                int height = m_x11Container->height() + mEvent->y() - m_grip->height();
                resize_x11(width, height);
            }
            return true;
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* mEvent = (QMouseEvent*)event;
            if (mEvent->button() == Qt::LeftButton)
                m_gripMouseDown = false;
            return true;
        }

        return QObject::eventFilter(obj, event);
    }
#endif

private slots:
    void pluginParameterChanged(uint32_t index, float value)
    {
        if (ui_controller && ui_writeFunction)
            ui_writeFunction(ui_controller, index+controlPortOffset, sizeof(float), 0, &value);
    }

private:
    DistrhoUiBase* m_ui;

#ifdef Q_OS_LINUX
    QApplication* m_app;
    QX11EmbedWidget* m_x11Container;

    QSizeGrip* m_grip;
    bool m_gripMouseDown;
    int m_minWidth, m_minHeight;

    void resize_x11(int width, int height)
    {
        if (width < m_minWidth)
            width = m_minWidth;
        if (height < m_minHeight)
            height = m_minHeight;

        m_x11Container->setFixedSize(width, height);
        m_grip->move(width - m_grip->width(), height - m_grip->height());

        if (ui_resize)
            ui_resize->ui_resize(ui_resize->handle, width, height);
    }
#endif

    LV2UI_Controller ui_controller;
    LV2UI_Write_Function ui_writeFunction;

    LV2UI_Resize* ui_resize;
    LV2UI_Touch* ui_touch;

    uint32_t controlPortOffset;
};

#include "UiLV2.moc"

// ---------------------------------------------------------------------------------------------

static LV2UI_Handle ui_instantiate_qt4(const LV2UI_Descriptor*, const char* plugin_uri, const char*, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    if (strcmp(plugin_uri, DISTRHO_PLUGIN_URI) == 0)
        return new DistrhoUiLv2(write_function, controller, widget, features, false);
    return nullptr;
}

#ifdef Q_OS_LINUX
static LV2UI_Handle ui_instantiate_x11(const LV2UI_Descriptor*, const char* plugin_uri, const char*, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    if (strcmp(plugin_uri, DISTRHO_PLUGIN_URI) == 0)
        return new DistrhoUiLv2(write_function, controller, widget, features, true);
    return nullptr;
}
#endif

static void ui_cleanup(LV2UI_Handle instance)
{
    delete (DistrhoUiLv2*)instance;
}

static void ui_port_event(LV2UI_Handle instance, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    DistrhoUiLv2* ui = (DistrhoUiLv2*)instance;
    ui->lv2_port_event(port_index, buffer_size, format, buffer);
}

static const void* ui_extension_data(const char* /*uri*/)
{
    return nullptr;
}

static const LV2UI_Descriptor uidescriptorQt4 = {
    DISTRHO_PLUGIN_URI "#Qt4UI",
    ui_instantiate_qt4,
    ui_cleanup,
    ui_port_event,
    ui_extension_data
};

#ifdef Q_OS_LINUX
static const LV2UI_Descriptor uidescriptorX11 = {
    DISTRHO_PLUGIN_URI "#X11UI",
    ui_instantiate_x11,
    ui_cleanup,
    ui_port_event,
    ui_extension_data
};
#endif

// ---------------------------------------------------------------------------------------------

DISTRHO_PLUGIN_EXPORT
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &uidescriptorQt4;
#ifdef Q_OS_LINUX
    case 1:
        return &uidescriptorX11;
#endif
    default:
        return nullptr;
    }
}

#endif // DISTRHO_PLUGIN_WANTS_UI
