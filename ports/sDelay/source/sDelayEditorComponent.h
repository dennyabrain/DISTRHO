/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  6 Nov 2008 9:28:00 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SDELAYEDITORCOMPONENT_SDELAYEDITORCOMPONENT_4929704F__
#define __JUCER_HEADER_SDELAYEDITORCOMPONENT_SDELAYEDITORCOMPONENT_4929704F__

//[Headers]     -- You can add your own extra header files here --
#include "DemoJuceFilter.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sDelayEditorComponent  : public AudioProcessorEditor,
                               public ChangeListener,
                               public SliderListener
{
public:
    //==============================================================================
    sDelayEditorComponent (DemoJuceFilter* const ownerFilter);
    ~sDelayEditorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback (ChangeBroadcaster* source);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	void updateParametersFromFilter();

	// handy wrapper method to avoid having to cast the filter to a DemoJuceFilter
    // every time we need it..
    DemoJuceFilter* getFilter() const throw()       { return (DemoJuceFilter*) getAudioProcessor(); }

    //[/UserVariables]

    //==============================================================================
    Slider* slider;
    Slider* feedSlider;
    Slider* gainSlider;
    Label* label;
    Label* label2;
    Label* label3;
    Label* label4;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sDelayEditorComponent (const sDelayEditorComponent&);
    const sDelayEditorComponent& operator= (const sDelayEditorComponent&);
};


#endif   // __JUCER_HEADER_SDELAYEDITORCOMPONENT_SDELAYEDITORCOMPONENT_4929704F__
