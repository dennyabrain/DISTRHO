/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#ifndef STEREOAUDIOGAIN_UI_H
#define STEREOAUDIOGAIN_UI_H

#include "UiBase.h"

namespace Ui {
class StereoAudioGainUi;
}

class StereoAudioGainUi : public DistrhoUiBase
{
    Q_OBJECT

public:
    StereoAudioGainUi();
    ~StereoAudioGainUi();

    bool d_isUiResizable();
    void d_setParameterValue(quint32 index, float value);
    void d_setProgram(quint32 index);

protected:
    Ui::StereoAudioGainUi* ui;

private:
    Q_SLOT void leftKnobValueChanged(int value);
    Q_SLOT void rightKnobValueChanged(int value);
};

#endif // STEREOAUDIOGAIN_UI_H
