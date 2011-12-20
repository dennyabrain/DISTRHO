/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  15 Nov 2009 10:21:36 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "WaveDrawWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
WaveDrawWindow::WaveDrawWindow (AudioProcessorEditor* owner_, MrAlias2* plugin_)
    : owner(owner_),
      plugin(plugin_),
      waveDrawer (0),
      sineButton (0),
      sawButton (0),
      squareButton (0),
      triangleButton (0),
      invertButton (0),
      reverseButton (0),
      saveButton (0),
      loadButton (0),
      normalizeButton (0),
      recordButton (0),
      copyButton (0),
      rampButton (0)
{
    addAndMakeVisible (waveDrawer = new WaveDrawer (owner,plugin));
    addAndMakeVisible (sineButton = new TextButton (T("new button")));
    sineButton->setButtonText (T("Sine"));
    sineButton->addButtonListener (this);

    addAndMakeVisible (sawButton = new TextButton (T("new button")));
    sawButton->setButtonText (T("RampUp"));
    sawButton->addButtonListener (this);

    addAndMakeVisible (squareButton = new TextButton (T("new button")));
    squareButton->setButtonText (T("Square"));
    squareButton->addButtonListener (this);

    addAndMakeVisible (triangleButton = new TextButton (T("new button")));
    triangleButton->setButtonText (T("Triangle"));
    triangleButton->addButtonListener (this);

    addAndMakeVisible (invertButton = new TextButton (T("new button")));
    invertButton->setButtonText (T("Invert"));
    invertButton->addButtonListener (this);

    addAndMakeVisible (reverseButton = new TextButton (T("new button")));
    reverseButton->setButtonText (T("Reverse"));
    reverseButton->addButtonListener (this);

    addAndMakeVisible (saveButton = new TextButton (T("new button")));
    saveButton->setButtonText (T("Save"));
    saveButton->addButtonListener (this);

    addAndMakeVisible (loadButton = new TextButton (T("new button")));
    loadButton->setButtonText (T("Load"));
    loadButton->addButtonListener (this);

    addAndMakeVisible (normalizeButton = new TextButton (T("new button")));
    normalizeButton->setButtonText (T("Normalize"));
    normalizeButton->addButtonListener (this);

    addAndMakeVisible (recordButton = new TextButton (T("new button")));
    recordButton->setTooltip (T("Record"));
    recordButton->setButtonText (T("R"));
    recordButton->addButtonListener (this);
    recordButton->setColour (TextButton::buttonColourId, Colours::brown);
    recordButton->setColour (TextButton::buttonOnColourId, Colours::red);

    addAndMakeVisible (copyButton = new TextButton (T("new button")));
    copyButton->setTooltip (T("Copy from other waveform"));
    copyButton->setButtonText (T("Copy"));
    copyButton->addButtonListener (this);

    addAndMakeVisible (rampButton = new TextButton (T("new button")));
    rampButton->setButtonText (T("RampDn"));
    rampButton->addButtonListener (this);


    //[UserPreSize]
	waveNumber=0;
	this->setMouseClickGrabsKeyboardFocus(false);
	sineButton->setMouseClickGrabsKeyboardFocus(false);
	triangleButton->setMouseClickGrabsKeyboardFocus(false);
	squareButton->setMouseClickGrabsKeyboardFocus(false);
	rampButton->setMouseClickGrabsKeyboardFocus(false);
	sawButton->setMouseClickGrabsKeyboardFocus(false);
	loadButton->setMouseClickGrabsKeyboardFocus(false);
	saveButton->setMouseClickGrabsKeyboardFocus(false);
	reverseButton->setMouseClickGrabsKeyboardFocus(false);
	invertButton->setMouseClickGrabsKeyboardFocus(false);
	normalizeButton->setMouseClickGrabsKeyboardFocus(false);
	recordButton->setMouseClickGrabsKeyboardFocus(false);
	copyButton->setMouseClickGrabsKeyboardFocus(false);
	recordButton->setVisible(false);
    //[/UserPreSize]

    setSize (300, 200);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

WaveDrawWindow::~WaveDrawWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (waveDrawer);
    deleteAndZero (sineButton);
    deleteAndZero (sawButton);
    deleteAndZero (squareButton);
    deleteAndZero (triangleButton);
    deleteAndZero (invertButton);
    deleteAndZero (reverseButton);
    deleteAndZero (saveButton);
    deleteAndZero (loadButton);
    deleteAndZero (normalizeButton);
    deleteAndZero (recordButton);
    deleteAndZero (copyButton);
    deleteAndZero (rampButton);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void WaveDrawWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xab7d7d7d));

    g.setColour (Colours::black);
    g.drawRect (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f), 5);

    //[UserPaint] Add your own custom painting code here..
	recordButton->setToggleState(plugin->isRecording(waveNumber+draw1),false);
    //[/UserPaint]
}

void WaveDrawWindow::resized()
{
    waveDrawer->setBounds (proportionOfWidth (0.0733f), proportionOfHeight (0.1900f), proportionOfWidth (0.8533f), proportionOfHeight (0.6400f));
    sineButton->setBounds (proportionOfWidth (0.7233f), proportionOfHeight (0.0500f), proportionOfWidth (0.1333f), proportionOfHeight (0.1000f));
    sawButton->setBounds (proportionOfWidth (0.0267f), proportionOfHeight (0.0500f), proportionOfWidth (0.1800f), proportionOfHeight (0.1000f));
    squareButton->setBounds (proportionOfWidth (0.4000f), proportionOfHeight (0.0500f), proportionOfWidth (0.1600f), proportionOfHeight (0.1000f));
    triangleButton->setBounds (proportionOfWidth (0.5633f), proportionOfHeight (0.0500f), proportionOfWidth (0.1600f), proportionOfHeight (0.1000f));
    invertButton->setBounds (proportionOfWidth (0.0267f), proportionOfHeight (0.8550f), proportionOfWidth (0.1600f), proportionOfHeight (0.1000f));
    reverseButton->setBounds (proportionOfWidth (0.2100f), proportionOfHeight (0.8550f), proportionOfWidth (0.1867f), proportionOfHeight (0.1000f));
    saveButton->setBounds (proportionOfWidth (0.6533f), proportionOfHeight (0.8550f), proportionOfWidth (0.1500f), proportionOfHeight (0.1000f));
    loadButton->setBounds (proportionOfWidth (0.8267f), proportionOfHeight (0.8550f), proportionOfWidth (0.1500f), proportionOfHeight (0.1000f));
    normalizeButton->setBounds (proportionOfWidth (0.4200f), proportionOfHeight (0.8550f), proportionOfWidth (0.2100f), proportionOfHeight (0.1000f));
    recordButton->setBounds (proportionOfWidth (0.0167f), proportionOfHeight (0.1900f), proportionOfWidth (0.0533f), proportionOfHeight (0.1600f));
    copyButton->setBounds (proportionOfWidth (0.8600f), proportionOfHeight (0.0500f), proportionOfWidth (0.1200f), proportionOfHeight (0.1000f));
    rampButton->setBounds (proportionOfWidth (0.2133f), proportionOfHeight (0.0500f), proportionOfWidth (0.1800f), proportionOfHeight (0.1000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void WaveDrawWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == sineButton)
    {
        //[UserButtonCode_sineButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->resetDrawableWave(sine,waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_sineButton]
    }
    else if (buttonThatWasClicked == sawButton)
    {
        //[UserButtonCode_sawButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->resetDrawableWave(rampup,waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_sawButton]
    }
    else if (buttonThatWasClicked == squareButton)
    {
        //[UserButtonCode_squareButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->resetDrawableWave(pulse,waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_squareButton]
    }
    else if (buttonThatWasClicked == triangleButton)
    {
        //[UserButtonCode_triangleButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->resetDrawableWave(triangle,waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_triangleButton]
    }
    else if (buttonThatWasClicked == invertButton)
    {
        //[UserButtonCode_invertButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->invertWave(waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_invertButton]
    }
    else if (buttonThatWasClicked == reverseButton)
    {
        //[UserButtonCode_reverseButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->reverseWave(waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_reverseButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        FileChooser myChooser ("Save wav...", File(plugin->wavePath), "*.wav");

        if (myChooser.browseForFileToSave(true))
        {
            File wavFile (myChooser.getResult());
            if (!wavFile.hasFileExtension("wav")) wavFile = wavFile.withFileExtension("wav");
			plugin->wavePath = wavFile.getParentDirectory().getFullPathName();

            plugin->saveWavFile (wavFile,waveSize,draw1+waveNumber);
        }
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        FileChooser myChooser ("Load wav...", File(plugin->wavePath), "*.wav");

        if (myChooser.browseForFileToOpen())
        {
            File file (myChooser.getResult());
            if (file.hasFileExtension("wav")) {
				plugin->getCallbackLock().enter();
				plugin->readWavFile(file,waveSize,draw1+waveNumber);
				plugin->wavePath = file.getParentDirectory().getFullPathName();
				plugin->getCallbackLock().exit();
			}
		}
		waveDrawer->repaint();
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == normalizeButton)
    {
        //[UserButtonCode_normalizeButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->normalizeWave(waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_normalizeButton]
    }
    else if (buttonThatWasClicked == recordButton)
    {
        //[UserButtonCode_recordButton] -- add your button handler code here..
		plugin->startRecording(waveNumber+draw1);
		recordButton->setToggleState(true,false);
        //[/UserButtonCode_recordButton]
    }
    else if (buttonThatWasClicked == copyButton)
    {
        //[UserButtonCode_copyButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->resetDrawableWave(waveNumber==0?draw2:draw1,waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_copyButton]
    }
    else if (buttonThatWasClicked == rampButton)
    {
        //[UserButtonCode_rampButton] -- add your button handler code here..
		plugin->getCallbackLock().enter();
		plugin->resetDrawableWave(rampdn,waveNumber);
		plugin->getCallbackLock().exit();
		waveDrawer->repaint();
        //[/UserButtonCode_rampButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void WaveDrawWindow::setWave(int index) {
	waveNumber=index;
	waveDrawer->waveNumber=index;
	waveDrawer->setSource(plugin->getDrawableWave(index));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="WaveDrawWindow" componentName=""
                 parentClasses="public Component" constructorParams="AudioProcessorEditor* owner_, MrAlias2* plugin_"
                 variableInitialisers="owner(owner_),&#10;plugin(plugin_)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="300" initialHeight="200">
  <BACKGROUND backgroundColour="ab7d7d7d">
    <RECT pos="0 0 100% 100%" fill="solid: 0" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff000000"/>
  </BACKGROUND>
  <JUCERCOMP name="" id="50880b0498415e91" memberName="waveDrawer" virtualName=""
             explicitFocusOrder="0" pos="7.333% 19% 85.333% 64%" sourceFile="E:/vstdev/juce plugins/mralias/src/WaveDrawer.cpp"
             constructorParams="owner,plugin"/>
  <TEXTBUTTON name="new button" id="e06678d347780d41" memberName="sineButton"
              virtualName="" explicitFocusOrder="0" pos="72.333% 5% 13.333% 10%"
              buttonText="Sine" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="49c3b101f6effb91" memberName="sawButton"
              virtualName="" explicitFocusOrder="0" pos="2.667% 5% 18% 10%"
              buttonText="RampUp" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="65e346b7fb09d040" memberName="squareButton"
              virtualName="" explicitFocusOrder="0" pos="40% 5% 16% 10%" buttonText="Square"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="8a3341a5207e65d6" memberName="triangleButton"
              virtualName="" explicitFocusOrder="0" pos="56.333% 5% 16% 10%"
              buttonText="Triangle" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5d0f2112f61fb084" memberName="invertButton"
              virtualName="" explicitFocusOrder="0" pos="2.667% 85.5% 16% 10%"
              buttonText="Invert" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="763b4a4608595c5f" memberName="reverseButton"
              virtualName="" explicitFocusOrder="0" pos="21% 85.5% 18.667% 10%"
              buttonText="Reverse" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="141c4f11cc26075b" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="65.333% 85.5% 15% 10%"
              buttonText="Save" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="893b71bf8c2aec08" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="82.667% 85.5% 15% 10%"
              buttonText="Load" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="363584b59e51e6bd" memberName="normalizeButton"
              virtualName="" explicitFocusOrder="0" pos="42% 85.5% 21% 10%"
              buttonText="Normalize" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="80217888114296d7" memberName="recordButton"
              virtualName="" explicitFocusOrder="0" pos="1.667% 19% 5.333% 16%"
              tooltip="Record" bgColOff="ffa52a2a" bgColOn="ffff0000" buttonText="R"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b5200b3631f4dc54" memberName="copyButton"
              virtualName="" explicitFocusOrder="0" pos="86% 5% 12% 10%" tooltip="Copy from other waveform"
              buttonText="Copy" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="8d735ce2257433c8" memberName="rampButton"
              virtualName="" explicitFocusOrder="0" pos="21.333% 5% 18% 10%"
              buttonText="RampDn" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
