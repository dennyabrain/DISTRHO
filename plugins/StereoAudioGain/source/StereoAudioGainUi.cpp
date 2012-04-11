/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 *
 * Released under the Public Domain
 */

#include "StereoAudioGainUi.h"
#include "ui_StereoAudioGain.h"

StereoAudioGainUi::StereoAudioGainUi() :
    DistrhoUiBase(),
    ui(new Ui::StereoAudioGainUi)
{
    ui->setupUi(this);
}

StereoAudioGainUi::~StereoAudioGainUi()
{
}

void StereoAudioGainUi::setParameterValue(uint32_t /*index*/, float /*value*/)
{
    blockSignals(true);
    blockSignals(false);
}

// ---------------------------------------------------------------------------------------------

DistrhoUiBase* createDistrhoUI()
{
    return new StereoAudioGainUi();
}
