/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#include "StereoAudioGain.h"
#include "StereoAudioGainUi.h"
#include "ui_StereoAudioGain.h"

StereoAudioGainUi::StereoAudioGainUi() :
    DistrhoUiBase(),
    ui(new Ui::StereoAudioGainUi)
{
    ui->setupUi(this);

    int refresh = 30; //miliseconds

    ui->dial_left->setPixmap(2);
    ui->dial_left->setLabel("Left");

    ui->dial_right->setPixmap(2);
    ui->dial_right->setLabel("Right");

    ui->lpeak->setChannels(1);
    ui->lpeak->setMaximumWidth(20);
    ui->lpeak->setRefreshRate(refresh);

    ui->rpeak->setChannels(1);
    ui->rpeak->setMaximumWidth(20);
    ui->rpeak->setRefreshRate(refresh);

    resize(50, 50);

    connect(ui->dial_left, SIGNAL(valueChanged(int)), this, SLOT(leftKnobValueChanged(int)));
    connect(ui->dial_right, SIGNAL(valueChanged(int)), this, SLOT(rightKnobValueChanged(int)));
}

StereoAudioGainUi::~StereoAudioGainUi()
{
}

bool StereoAudioGainUi::isUiResizable()
{
    return true;
}

void StereoAudioGainUi::setParameterValue(quint32 index, float value)
{
    blockSignals(true);

    switch (index)
    {
    case StereoAudioGain::PARAMETER_LEFT:
        ui->dial_left->setValue((value*50)-50);
        break;
    case StereoAudioGain::PARAMETER_RIGHT:
        ui->dial_right->setValue((value*50)-50);
        break;
    case StereoAudioGain::PARAMETER_VU_LEFT:
        ui->lpeak->displayMeter(1, value);
        break;
    case StereoAudioGain::PARAMETER_VU_RIGHT:
        ui->rpeak->displayMeter(1, value);
        break;
    }

    blockSignals(false);
}

void StereoAudioGainUi::leftKnobValueChanged(int value)
{
    emit parameterChanged(StereoAudioGain::PARAMETER_LEFT, (float(value+50)/100)*2);
}

void StereoAudioGainUi::rightKnobValueChanged(int value)
{
    emit parameterChanged(StereoAudioGain::PARAMETER_RIGHT, (float(value+50)/100)*2);
}

// ---------------------------------------------------------------------------------------------

DistrhoUiBase* createDistrhoUI()
{
    return new StereoAudioGainUi();
}
