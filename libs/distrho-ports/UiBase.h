// distrho base ui class

#ifndef __DISTRHO_UI_BASE__
#define __DISTRHO_UI_BASE__

#include "DistrhoPlugin.h"

#if DISTRHO_PLUGIN_WANTS_UI
#include <QtGui/QDialog>

#ifndef nullptr
#define nullptr (0)
#endif

class DistrhoUiBase : public QDialog
{
    Q_OBJECT

public:
    DistrhoUiBase(QWidget* parent = nullptr) : QDialog(parent)
    {
    }

    virtual ~DistrhoUiBase()
    {
    }

    virtual bool isUiResizable() = 0;
    virtual void setParameterValue(quint32 index, float value) = 0;

signals:
    void parameterChanged(quint32 index, float value);
};

// ---------------------------------------------------------------------------------------------

extern DistrhoUiBase* createDistrhoUI();
#endif

#endif // __DISTRHO_UI_BASE__
