/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 *
 * Released under the Public Domain
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

    virtual void setParameterValue(uint32_t index, float value);

protected:
    Ui::StereoAudioGainUi* ui;

private:
    Q_SLOT void leftKnobValueChanged(int value);
    Q_SLOT void rightKnobValueChanged(int value);

};

#endif // STEREOAUDIOGAIN_UI_H
