// distrho lv2 plugin

#include "PluginBase.h"

#include "public.sdk/source/vst2.x/audioeffect.cpp"
#include "public.sdk/source/vst2.x/audioeffectx.cpp"
#include "public.sdk/source/vst2.x/vstplugmain.cpp"

// ---------------------------------------------------------------------------------------------

#if DISTRHO_PLUGIN_WANTS_UI

#include "UiBase.h"
#include "public.sdk/source/vst2.x/aeffeditor.h"

#ifndef Q_OS_LINUX
#error VST GUI is (currently) only available for Linux
#endif

#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QSizeGrip>
#include <QtGui/QVBoxLayout>
#include <QtGui/QX11EmbedWidget>

class DistrhoUiVst :
        public AEffEditor,
        public QObject
{
public:
    DistrhoUiVst(AudioEffectX* effect) :
        AEffEditor(effect),
        QObject(nullptr),
        effectx(effect),
        m_app(nullptr),
        m_x11Container(nullptr),
        m_grip(nullptr),
        m_gripMouseDown(false),
        m_minWidth(10),
        m_minHeight(10)
    {
        // create QApplication if needed
        if (! QApplication::instance())
        {
            static int argc = 0;
            static char* argv[] = { nullptr };
            m_app = new QApplication(argc, argv, true);
            //m_app->setQuitOnLastWindowClosed(true);
        }

        m_ui = createDistrhoUI();

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

        // Set size
        m_minWidth  = m_x11Container->width();
        m_minHeight = m_x11Container->height();

        resize_ui(m_minWidth, m_minHeight, false);

        timerParamCheck = startTimer(50);
        connect(m_ui, SIGNAL(parameterChanged(quint32,float)), this, SLOT(pluginParameterChanged(quint32,float)));
    }

    ~DistrhoUiVst()
    {
        m_ui->close();
        delete m_ui;

        if (m_grip)
            delete m_grip;

        if (m_x11Container)
        {
            m_x11Container->close();
            delete m_x11Container;
        }
    }

    bool getRect(ERect** rect)
    {
        static ERect r = {0, 0, (VstInt16)m_x11Container->height(), (VstInt16)m_x11Container->width()};
        *rect = &r;
        //(*rect)->top  = 0;
        //(*rect)->left = 0;
        //(*rect)->bottom = m_x11Container->height();
        //(*rect)->right  = m_x11Container->width();
        return true;
    }

    bool open(void* ptr)
    {
        AEffEditor::open(ptr);

        WId parent = (WId)ptr;
        m_x11Container->embedInto(parent);
        m_x11Container->show();

        return true;
    }

    void close()
    {
        //m_x11Container->hide();
        //m_x11Container->embedInto(0);
        AEffEditor::close();
    }

    void idle()
    {
        if (m_app)
            m_app->processEvents();
    }

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
                resize_ui(width, height, true);
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

    void timerEvent(QTimerEvent* event)
    {
        if (event->timerId() == timerParamCheck)
        {
            for (uint32_t i=0; i < 4; i++) // FIXME!
                m_ui->setParameterValue(i, effectx->getParameter(i));
        }
        QObject::timerEvent(event);
    }

private slots:
    void pluginParameterChanged(quint32 index, float value)
    {
        qWarning("pluginParameterChanged(%i, %f)", index, value);
        effect->setParameterAutomated(index, value);
    }

private:
    AudioEffectX* effectx;
    DistrhoUiBase* m_ui;

    int timerParamCheck;

    QApplication* m_app;
    QX11EmbedWidget* m_x11Container;

    QSizeGrip* m_grip;
    bool m_gripMouseDown;
    int m_minWidth, m_minHeight;

    void resize_ui(int width, int height, bool updateHost)
    {
        if (width < m_minWidth)
            width = m_minWidth;
        if (height < m_minHeight)
            height = m_minHeight;

        m_x11Container->setFixedSize(width, height);

        if (m_grip)
            m_grip->move(width - m_grip->width(), height - m_grip->height());

        if (updateHost)
            effectx->sizeWindow(width, height);
    }
};

#endif

// ---------------------------------------------------------------------------------------------

class DistrhoPluginVst : public AudioEffectX
{
public:
    DistrhoPluginVst(audioMasterCallback audioMaster, DistrhoPluginBase* plugin) :
        AudioEffectX(audioMaster, plugin->d_programCount(), plugin->d_parameterCount()),
        m_plugin(plugin)
    {
        m_plugin->d_init();

        m_plugin->__setSampleRate(getSampleRate());
        m_plugin->__setBufferSize(getBlockSize());

        setInitialDelay(m_plugin->__latency());
        setNumInputs(DISTRHO_PLUGIN_NUM_INPUTS);
        setNumOutputs(DISTRHO_PLUGIN_NUM_OUTPUTS);
        setUniqueID(m_plugin->d_uniqueId());

        canProcessReplacing(true);

#if DISTRHO_PLUGIN_IS_SYNTH
        isSynth();
#endif

#if DISTRHO_PLUGIN_WANTS_UI
        setEditor(new DistrhoUiVst(this));
#endif
    }

    ~DistrhoPluginVst()
    {
        m_plugin->d_cleanup();
        delete m_plugin;
    }

    // --------------------------------------------------------------------------
    // AudioEffect virtual calls

    void suspend()
    {
        AudioEffectX::suspend();
        m_plugin->d_deactivate();
    }

    void resume()
    {
        m_plugin->d_activate();
        setInitialDelay(m_plugin->__latency());
        AudioEffectX::resume();
    }

    void setSampleRate(float sampleRate)
    {
        m_plugin->__setSampleRate(sampleRate);
        AudioEffectX::setSampleRate(sampleRate);
    }

    void setBlockSize(VstInt32 blockSize)
    {
        m_plugin->__setBufferSize(blockSize);
        AudioEffectX::setBlockSize(blockSize);
    }

    void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames)
    {
        m_plugin->d_run(inputs, outputs, sampleFrames, 0, nullptr);
    }

    VstInt32 processEvents(VstEvents* /*events*/)
    {
        return 0;
    }

    void setParameter(VstInt32 index, float value)
    {
        m_plugin->d_setParameterValue(index, value);
    }

    float getParameter(VstInt32 index)
    {
        return m_plugin->d_parameterValue(index);
    }

    void setProgram(VstInt32 program)
    {
        m_plugin->d_setCurrentProgram(program);
        AudioEffectX::setProgram(program);
    }

    void getProgramName(char* name)
    {
        //if (getProgram() >= 0 && getProgram() < m_plugin->d_programCount())
        //    return getProgramNameIndexed(0, getProgram(), name);
        *name = 0;
    }

    virtual void getParameterLabel(VstInt32 index, char* label)
    {
        const char* unit = m_plugin->d_parameterInfo(index)->unit;
        if (unit)
            vst_strncpy(label, unit, 24);
        else
            *label = 0;
    }

    void getParameterName(VstInt32 index, char* text)
    {
        vst_strncpy(text, m_plugin->d_parameterInfo(index)->name, 24);
    }

    // --------------------------------------------------------------------------
    // AudioEffectX virtual calls

    bool canParameterBeAutomated(VstInt32 index)
    {
        return (m_plugin->d_parameterInfo(index)->hints & PARAMETER_IS_AUTOMABLE);
    }

    bool getProgramNameIndexed(VstInt32, VstInt32 index, char* text)
    {
        vst_strncpy(text, m_plugin->d_programName(index), kVstMaxProgNameLen);
        return false;
    }

    bool getEffectName(char* name)
    {
        vst_strncpy(name, m_plugin->d_name(), kVstMaxEffectNameLen);
        return true;
    }

    bool getProductString(char* text)
    {
        vst_strncpy(text, m_plugin->d_label(), kVstMaxProductStrLen);
        return true;
    }

    bool getVendorString(char* text)
    {
        vst_strncpy(text, m_plugin->d_maker(), kVstMaxVendorStrLen);
        return true;
    }

    VstInt32 getVendorVersion()
    {
        return m_plugin->d_version();
    }

    VstInt32 canDo(char* text)
    {
#if DISTRHO_PLUGIN_IS_SYNTH
        if (strcmp(text, "receiveVstEvents") == 0)
            return 1;
        else if (strcmp(text, "receiveVstMidiEvent") == 0)
            return 1;
        else
#else
        (void)text;
#endif
        return -1;
    }

    VstPlugCategory getPlugCategory()
    {
#if DISTRHO_PLUGIN_IS_SYNTH
        return kPlugCategSynth;
#else
        return kPlugCategEffect;
#endif
    }

private:
    DistrhoPluginBase* m_plugin;
};

// ---------------------------------------------------------------------------------------------

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
    return new DistrhoPluginVst(audioMaster, createDistrhoPlugin());
}
