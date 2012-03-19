/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINEDITOR_H_CC807F53__
#define __PLUGINEDITOR_H_CC807F53__

#include "JuceHeader.h"
#include "JucePluginCharacteristics.h"
#include "PluginProcessor.h"

// UI Elements
#include "Headers/UI/Knob.h"
//#include "Headers/UI/FancyButton.h"

// Background Binary Data
#include "Headers/Binary Data/Backgrounds/thepilgrimbackground.h"

//==============================================================================
/**
*/
class ThePilgrimAudioProcessorEditor  : public AudioProcessorEditor,
										public SliderListener,
										public Timer
{
public:
    ThePilgrimAudioProcessorEditor (ThePilgrimAudioProcessor* ownerFilter);
    ~ThePilgrimAudioProcessorEditor();

    //==============================================================================
    // This is just a standard Juce paint method...
    void paint (Graphics& g);
	void sliderValueChanged (Slider* slider);
	void resized();
	void timerCallback();

	Image backgroundGUI;
	Knob filterKnob;
	Knob wetdryKnob;

	ThePilgrimAudioProcessor* getProcessor() const
    {
        return static_cast <ThePilgrimAudioProcessor*> (getAudioProcessor());
    }
};


#endif  // __PLUGINEDITOR_H_CC807F53__
