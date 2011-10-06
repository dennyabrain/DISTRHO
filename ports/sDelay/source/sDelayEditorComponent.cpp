/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Nov 2008 12:21:51 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "includes.h"
//[/Headers]

#include "sDelayEditorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sDelayEditorComponent::sDelayEditorComponent (DemoJuceFilter* const ownerFilter)
    : AudioProcessorEditor (ownerFilter),
      slider (0),
      feedSlider (0),
      gainSlider (0),
      label (0),
      label2 (0),
      label3 (0),
      label4 (0)
{
    addAndMakeVisible (slider = new Slider (T("delay slider")));
    slider->setRange (0, 3000, 1);
    slider->setSliderStyle (Slider::RotaryVerticalDrag);
    slider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    slider->addListener (this);

    addAndMakeVisible (feedSlider = new Slider (T("feedback slider")));
    feedSlider->setRange (0, 100, 1);
    feedSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    feedSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 30, 20);
    feedSlider->addListener (this);

    addAndMakeVisible (gainSlider = new Slider (T("gain slider")));
    gainSlider->setRange (0, 100, 1);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 30, 20);
    gainSlider->addListener (this);

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("sDelay")));
    label->setFont (Font (T("Arial Black"), 19.1000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (T("new label"),
                                           T("Delay")));
    label2->setFont (Font (T("Arial Black"), 15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label3 = new Label (T("new label"),
                                           T("Feedback")));
    label3->setFont (Font (T("Arial Black"), 15.0000f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label4 = new Label (T("new label"),
                                           T("Gain")));
    label4->setFont (Font (T("Arial Black"), 15.0000f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::white);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
	
	slider->setValue(remap(ownerFilter->getParameter (0), 0.0, 1.0,
														(float)slider->getMinimum(),
														(float)slider->getMaximum()), false);
	feedSlider->setValue(remap(ownerFilter->getParameter (1), 0.0, 1.0,
														(float)feedSlider->getMinimum(),
														(float)feedSlider->getMaximum()), false);
	gainSlider->setValue(remap(ownerFilter->getParameter (2), 0.0, 1.0,
														(float)gainSlider->getMinimum(),
														(float)gainSlider->getMaximum()), false);

    //[/UserPreSize]

    setSize (150, 110);

    //[Constructor] You can add your own custom stuff here..

	ownerFilter->addChangeListener (this);


    //[/Constructor]
}

sDelayEditorComponent::~sDelayEditorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (slider);
    deleteAndZero (feedSlider);
    deleteAndZero (gainSlider);
    deleteAndZero (label);
    deleteAndZero (label2);
    deleteAndZero (label3);
    deleteAndZero (label4);

    //[Destructor]. You can add your own custom destruction code here..

	getFilter()->removeChangeListener (this);
	deleteAllChildren();

    //[/Destructor]
}

//==============================================================================
void sDelayEditorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void sDelayEditorComponent::resized()
{
    slider->setBounds (8, 24, 40, 48);
    feedSlider->setBounds (56, 24, 40, 48);
    gainSlider->setBounds (104, 24, 40, 48);
    label->setBounds (48, 0, 55, 24);
    label2->setBounds (8, 80, 40, 24);
    label3->setBounds (48, 80, 56, 24);
    label4->setBounds (108, 80, 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void sDelayEditorComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..

		getFilter()->setParameterNotifyingHost (0, remap((float)slider->getValue(),
														  (float)slider->getMinimum(),
														  (float)slider->getMaximum(),0.0,1.0));
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == feedSlider)
    {
        //[UserSliderCode_feedSlider] -- add your slider handling code here..

		getFilter()->setParameterNotifyingHost (1, remap((float)feedSlider->getValue(),
														 (float)feedSlider->getMinimum(),
														 (float)feedSlider->getMaximum(),0.0,1.0));
        //[/UserSliderCode_feedSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..

		getFilter()->setParameterNotifyingHost (2, remap((float)gainSlider->getValue(),
														 (float)gainSlider->getMinimum(),
														 (float)gainSlider->getMaximum(),0.0,1.0));
        //[/UserSliderCode_gainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

// This function remaps any value from the range [startIn, endIn] to the range [startOut, endOut]
float sDelayEditorComponent::remap(float val, float startIn, float endIn, float startOut, float endOut)
{
	return startOut + ((endOut - startOut) * ((val - startIn)/(endIn - startIn)));
}

void sDelayEditorComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    // this is the filter telling us that it's changed, so we'll update our
    // display of the time, midi message, etc.
    updateParametersFromFilter();
}

void sDelayEditorComponent::updateParametersFromFilter()
{
    DemoJuceFilter* const filter = getFilter();

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
    filter->getCallbackLock().enter();

    // take a local copy of the info we need while we've got the lock..
    const float newDelay = filter->getParameter (0);
	const float newFeed = filter->getParameter (1);
	const float newGain = filter->getParameter (2);
    // ..release the lock ASAP
    filter->getCallbackLock().exit();

    // ..and after releasing the lock, we're free to do the time-consuming UI stuff..

    /* Update our slider.

       (note that it's important here to tell the slider not to send a change
       message, because that would cause it to call the filter with a parameter
       change message again, and the values would drift out.
	*/
	
	slider->setValue (remap(newDelay, 0.0, 1.0,
							(float)slider->getMinimum(),
							(float)slider->getMaximum()), false);
	feedSlider->setValue (remap(newFeed, 0.0, 1.0,
								(float)feedSlider->getMinimum(),
								(float)feedSlider->getMaximum()), false);

	gainSlider->setValue (remap(newGain, 0.0, 1.0,
								(float)gainSlider->getMinimum(),
								(float)gainSlider->getMaximum()), false);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sDelayEditorComponent" componentName=""
                 parentClasses="public AudioProcessorEditor, public ChangeListener, public SliderListener"
                 constructorParams="DemoJuceFilter* const ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="150" initialHeight="110">
  <BACKGROUND backgroundColour="ff000000"/>
  <SLIDER name="new slider" id="251e506958de0745" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="8 24 40 48" min="0" max="3000" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="feedback slider" id="4f54cafbf297871c" memberName="feedSlider"
          virtualName="" explicitFocusOrder="0" pos="56 24 40 48" min="0"
          max="100" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="gain slider" id="bab1b9cbdbfc0370" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="104 24 40 48" min="0"
          max="100" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="11bd14c0ab9e95d5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="48 0 55 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="sDelay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Arial Black" fontsize="19.1"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a15e5a897bccae9e" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 80 40 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay &#10; (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial Black"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8dfa82905314d010" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="48 80 56 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Arial Black" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b6828a358def63c8" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="108 80 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial Black"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
