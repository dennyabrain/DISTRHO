
#ifndef __DISTRHOPLUGINEDITOR_H__
#define __DISTRHOPLUGINEDITOR_H__

#include "DistrhoPluginProcessor.h"

#include "../../common/Juce-Widgets/DistrhoIcon.h"
#include "../../common/Juce-Widgets/FilmStripKnob.h"
#include "../../common/Juce-Widgets/ImageSlider.h"

//==================================================================================
class DistrhoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                           public SliderListener,
                                           public Timer
{
public:
    DistrhoPluginAudioProcessorEditor (DistrhoPluginAudioProcessor* ownerFilter);
    ~DistrhoPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics& g);
    void sliderValueChanged (Slider* caller);

    //==============================================================================
    void timerCallback();

private:
    ImageSlider* sLow;
    ImageSlider* sMid;
    ImageSlider* sHigh;
    ImageSlider* sMaster;
    FilmStripKnob* sLowMidFreq;
    FilmStripKnob* sMidHighFreq;
    DistrhoIcon* aboutLogo;

    Image knobImage;
    Image sliderImage;
    Image backgroundImage;

    DistrhoPluginAudioProcessor* getProcessor() const
    {
        return static_cast <DistrhoPluginAudioProcessor*> (getAudioProcessor());
    }
};

#endif  // __DISTRHOPLUGINEDITOR_H__
