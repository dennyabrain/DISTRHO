
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
    void sliderDragStarted (Slider* caller);
    void sliderDragEnded (Slider* caller);

    //==============================================================================
    void timerCallback();

private:
    FilmStripKnob* sFreq;
    FilmStripKnob* sWidth;
    DistrhoIcon* aboutLogo;

    Image knobImage;
    Image backgroundImage;

    Array<int> slidersDraggedList;

    DistrhoPluginAudioProcessor* getProcessor() const
    {
        return static_cast <DistrhoPluginAudioProcessor*> (getAudioProcessor());
    }
};

#endif  // __DISTRHOPLUGINEDITOR_H__
