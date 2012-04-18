// distrho base ui class

#ifndef __DISTRHO_UI_BASE__
#define __DISTRHO_UI_BASE__

#include <QtGui/QDialog>
#include <stdint.h>

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

    virtual void setParameterValue(uint32_t index, float value) = 0;

signals:
    void parameterChanged(uint32_t index, float value);
};

// ---------------------------------------------------------------------------------------------

extern DistrhoUiBase* createDistrhoUI();

#endif // __DISTRHO_UI_BASE__
