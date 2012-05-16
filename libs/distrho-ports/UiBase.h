// distrho base ui class

#ifndef __DISTRHO_UI_BASE__
#define __DISTRHO_UI_BASE__

#include "DistrhoPlugin.h"

#if DISTRHO_PLUGIN_WANTS_UI

#include <QtGui/QWidget>

class DistrhoUiBase : public QWidget
{
    Q_OBJECT

public:
    DistrhoUiBase(QWidget* parent = nullptr) : QWidget(parent)
    {
    }

    virtual ~DistrhoUiBase()
    {
    }

    virtual bool d_isUiResizable() = 0;
    virtual void d_setParameterValue(quint32 index, float value) = 0;
    virtual void d_setProgram(quint32 index) = 0;

signals:
    void d_parameterChanged(quint32 index, float value);
};

// ---------------------------------------------------------------------------------------------

extern DistrhoUiBase* createDistrhoUI();

#endif // DISTRHO_PLUGIN_WANTS_UI
#endif // __DISTRHO_UI_BASE__
