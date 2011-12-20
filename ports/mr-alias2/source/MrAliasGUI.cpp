/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Nov 2009 10:35:07 am

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
#include "JucePluginCharacteristics.h"
//[/Headers]

#include "MrAliasGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MrAlias2Editor::MrAlias2Editor (MrAlias2* const ownerFilter)
    : AudioProcessorEditor (ownerFilter),
      aspectRatio(1.5),
      patchBox (0),
      sAlias (0),
      sCutoff (0),
      sDivide (0),
      sAtt (0),
      sRate (0),
      sSineMix (0),
      sSineRes (0),
      sPostDivide (0),
      sClip (0),
      sAInertia (0),
      sDec (0),
      sSus (0),
      sRel (0),
      sDivEnv (0),
      sRes (0),
      sBRMix (0),
      sVolume (0),
      sSineFreq (0),
      sVelSens (0),
      sFiltEnv (0),
      sFVSens (0),
      sPBRange (0),
      sInputGain (0),
      sWet (0),
      sOscGain (0),
      sThresh (0),
      sFreq1 (0),
      sRingMod (0),
      sFAtt (0),
      sFDec (0),
      sFSus (0),
      sFRel (0),
      audioled (0),
      sStereo (0),
      sOscMix (0),
      clipled (0),
      sMode (0),
      sStereo2 (0),
      sM1 (0),
      sPhMod (0),
      sDivMix (0),
      info (0),
      pizButton (0),
      sFKeyFollow (0),
      nextButton (0),
      prevButton (0),
      sReset (0),
      sOPLP (0),
      sPostDivMix (0),
      sSavePatch (0),
      sSavePatch2 (0),
      info3 (0),
      info2 (0),
      loadButton (0),
      filterModeBox (0),
      sOctave1 (0),
      comboBox (0),
      sOctave2 (0),
      comboBox2 (0),
      sChannel (0),
      sOctave (0),
      sUseProgCh (0),
      sM1Mix (0),
      randomButton (0),
      limiterButton (0),
      sExp (0),
      sFExp (0),
      midiled (0),
      saveSnapshotButtonB (0),
      recallSnapshotButtonB (0),
      sMorph (0),
      saveSnapshotButtonA (0),
      recallSnapshotButtonA (0),
      aboutbox (0),
      sPitchShift (0),
      resizer (0),
      cachedImage_mralias2_png (0)
{
    addAndMakeVisible (patchBox = new PizComboBox (T("Program Select")));
    patchBox->setTooltip (T("Select Patch"));
    patchBox->setEditableText (false);
    patchBox->setJustificationType (Justification::centredLeft);
    patchBox->setTextWhenNothingSelected (String::empty);
    patchBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    patchBox->addItem (T("dummy1"), 1);
    patchBox->addItem (T("dummy2"), 2);
    patchBox->addListener (this);

    addAndMakeVisible (sAlias = new Slider (T("Alias")));
    sAlias->setTooltip (T("Alias"));
    sAlias->setRange (0, 102, 0.01);
    sAlias->setSliderStyle (Slider::LinearHorizontal);
    sAlias->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAlias->addListener (this);

    addAndMakeVisible (sCutoff = new Slider (T("Filter Cutoff")));
    sCutoff->setTooltip (T("Filter Cutoff"));
    sCutoff->setRange (0, 99, 0);
    sCutoff->setSliderStyle (Slider::RotaryVerticalDrag);
    sCutoff->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sCutoff->setColour (Slider::backgroundColourId, Colour (0x0));
    sCutoff->setColour (Slider::rotarySliderFillColourId, Colour (0xffae0000));
    sCutoff->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sCutoff->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sCutoff->addListener (this);

    addAndMakeVisible (sDivide = new Slider (T("Divide")));
    sDivide->setTooltip (T("Divide"));
    sDivide->setRange (0, 100, 1);
    sDivide->setSliderStyle (Slider::LinearHorizontal);
    sDivide->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDivide->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    sDivide->addListener (this);
    sDivide->setSkewFactor (0.5);

    addAndMakeVisible (sAtt = new Slider (T("Amp Env Attack")));
    sAtt->setTooltip (T("Amp Env Attack"));
    sAtt->setRange (0, 100, 0);
    sAtt->setSliderStyle (Slider::LinearVertical);
    sAtt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAtt->addListener (this);

    addAndMakeVisible (sRate = new Slider (T("Downsample Rate")));
    sRate->setTooltip (T("Downsample Rate"));
    sRate->setRange (0, 100, 0.1);
    sRate->setSliderStyle (Slider::LinearHorizontal);
    sRate->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRate->addListener (this);

    addAndMakeVisible (sSineMix = new Slider (T("Sine Mix")));
    sSineMix->setTooltip (T("Sine Mix"));
    sSineMix->setRange (0, 99, 0);
    sSineMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sSineMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSineMix->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sSineMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sSineMix->addListener (this);

    addAndMakeVisible (sSineRes = new Slider (T("Sine Resolution")));
    sSineRes->setTooltip (T("Sine Resolution"));
    sSineRes->setRange (0, 100, 0.1);
    sSineRes->setSliderStyle (Slider::LinearHorizontal);
    sSineRes->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSineRes->addListener (this);

    addAndMakeVisible (sPostDivide = new Slider (T("Post Divide")));
    sPostDivide->setTooltip (T("Post Divide"));
    sPostDivide->setRange (0, 100, 1);
    sPostDivide->setSliderStyle (Slider::LinearHorizontal);
    sPostDivide->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPostDivide->addListener (this);
    sPostDivide->setSkewFactor (0.5);

    addAndMakeVisible (sClip = new Slider (T("Clipper")));
    sClip->setTooltip (T("Clipper"));
    sClip->setRange (0, 100, 0.1);
    sClip->setSliderStyle (Slider::LinearHorizontal);
    sClip->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sClip->addListener (this);

    addAndMakeVisible (sAInertia = new Slider (T("Inertia")));
    sAInertia->setTooltip (T("Inertia"));
    sAInertia->setRange (0, 99, 0);
    sAInertia->setSliderStyle (Slider::RotaryVerticalDrag);
    sAInertia->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAInertia->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sAInertia->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sAInertia->addListener (this);

    addAndMakeVisible (sDec = new Slider (T("Amp Env Decay")));
    sDec->setTooltip (T("Amp Env Decay"));
    sDec->setRange (0, 100, 0);
    sDec->setSliderStyle (Slider::LinearVertical);
    sDec->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDec->addListener (this);

    addAndMakeVisible (sSus = new Slider (T("Amp Env Sustain")));
    sSus->setTooltip (T("Amp Env Sustain"));
    sSus->setRange (0, 100, 0);
    sSus->setSliderStyle (Slider::LinearVertical);
    sSus->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSus->addListener (this);

    addAndMakeVisible (sRel = new Slider (T("Amp Env Release")));
    sRel->setTooltip (T("Amp Env Release"));
    sRel->setRange (0, 100, 0);
    sRel->setSliderStyle (Slider::LinearVertical);
    sRel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRel->addListener (this);

    addAndMakeVisible (sDivEnv = new Slider (T("AmpEnv -> Divider")));
    sDivEnv->setTooltip (T("AmpEnv -> Divider"));
    sDivEnv->setRange (0, 99, 0);
    sDivEnv->setSliderStyle (Slider::RotaryVerticalDrag);
    sDivEnv->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDivEnv->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sDivEnv->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sDivEnv->addListener (this);

    addAndMakeVisible (sRes = new Slider (T("Filter Resonance")));
    sRes->setTooltip (T("Filter Resonance"));
    sRes->setRange (0, 99, 0);
    sRes->setSliderStyle (Slider::RotaryVerticalDrag);
    sRes->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRes->setColour (Slider::rotarySliderFillColourId, Colour (0x7f001786));
    sRes->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sRes->addListener (this);

    addAndMakeVisible (sBRMix = new Slider (T("Downsampler Mix")));
    sBRMix->setTooltip (T("Downsampler Mix"));
    sBRMix->setRange (0, 99, 0.1);
    sBRMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sBRMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sBRMix->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sBRMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sBRMix->addListener (this);

    addAndMakeVisible (sVolume = new Slider (T("Main Volume")));
    sVolume->setTooltip (T("Main Volume"));
    sVolume->setRange (0, 99, 0);
    sVolume->setSliderStyle (Slider::RotaryVerticalDrag);
    sVolume->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sVolume->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff7900));
    sVolume->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sVolume->addListener (this);

    addAndMakeVisible (sSineFreq = new Slider (T("Sine Frequency")));
    sSineFreq->setTooltip (T("Sine Frequency"));
    sSineFreq->setRange (0, 100, 0.1);
    sSineFreq->setSliderStyle (Slider::LinearHorizontal);
    sSineFreq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSineFreq->addListener (this);

    addAndMakeVisible (sVelSens = new Slider (T("Velocity Sensitivity")));
    sVelSens->setTooltip (T("Amp Velocity Sensitivity"));
    sVelSens->setRange (0, 99, 0);
    sVelSens->setSliderStyle (Slider::RotaryVerticalDrag);
    sVelSens->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sVelSens->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sVelSens->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sVelSens->addListener (this);

    addAndMakeVisible (sFiltEnv = new Slider (T("Filter Env Amount")));
    sFiltEnv->setTooltip (T("Filter Env Amount"));
    sFiltEnv->setRange (0, 99, 0);
    sFiltEnv->setSliderStyle (Slider::RotaryVerticalDrag);
    sFiltEnv->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFiltEnv->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sFiltEnv->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sFiltEnv->addListener (this);

    addAndMakeVisible (sFVSens = new Slider (T("Filter Velocity Sens")));
    sFVSens->setTooltip (T("Filter Velocity Sensitivity"));
    sFVSens->setRange (0, 99, 0);
    sFVSens->setSliderStyle (Slider::RotaryVerticalDrag);
    sFVSens->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFVSens->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sFVSens->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sFVSens->addListener (this);

    addAndMakeVisible (sPBRange = new Slider (T("Pitchbend Range")));
    sPBRange->setTooltip (T("Pitchbend Range"));
    sPBRange->setRange (0, 24, 1);
    sPBRange->setSliderStyle (Slider::RotaryVerticalDrag);
    sPBRange->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPBRange->setColour (Slider::thumbColourId, Colour (0xbbbbff));
    sPBRange->setColour (Slider::trackColourId, Colour (0xffffff));
    sPBRange->setColour (Slider::rotarySliderFillColourId, Colour (0xff));
    sPBRange->setColour (Slider::rotarySliderOutlineColourId, Colour (0x0));
    sPBRange->setColour (Slider::textBoxTextColourId, Colours::white);
    sPBRange->addListener (this);

    addAndMakeVisible (sInputGain = new Slider (T("Input Gain")));
    sInputGain->setTooltip (T("Input Gain"));
    sInputGain->setRange (0, 99, 0);
    sInputGain->setSliderStyle (Slider::RotaryVerticalDrag);
    sInputGain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sInputGain->setColour (Slider::backgroundColourId, Colour (0x0));
    sInputGain->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sInputGain->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sInputGain->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sInputGain->addListener (this);

    addAndMakeVisible (sWet = new Slider (T("Wet/Dry")));
    sWet->setTooltip (T("Wet/Dry"));
    sWet->setRange (-99, 99, 0);
    sWet->setSliderStyle (Slider::RotaryVerticalDrag);
    sWet->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sWet->setColour (Slider::backgroundColourId, Colour (0x0));
    sWet->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sWet->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sWet->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sWet->addListener (this);

    addAndMakeVisible (sOscGain = new Slider (T("Synth Gain")));
    sOscGain->setTooltip (T("Synth Gain"));
    sOscGain->setRange (0, 99, 0);
    sOscGain->setSliderStyle (Slider::RotaryVerticalDrag);
    sOscGain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOscGain->setColour (Slider::backgroundColourId, Colour (0x0));
    sOscGain->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sOscGain->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sOscGain->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sOscGain->addListener (this);

    addAndMakeVisible (sThresh = new Slider (T("Div Threshold")));
    sThresh->setTooltip (T("Div Threshold"));
    sThresh->setRange (0, 100, 0.1);
    sThresh->setSliderStyle (Slider::LinearHorizontal);
    sThresh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sThresh->setColour (Slider::backgroundColourId, Colour (0xff));
    sThresh->addListener (this);

    addAndMakeVisible (sFreq1 = new Slider (T("Detune")));
    sFreq1->setTooltip (T("Detune"));
    sFreq1->setRange (-99, 99, 0);
    sFreq1->setSliderStyle (Slider::RotaryVerticalDrag);
    sFreq1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFreq1->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sFreq1->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sFreq1->addListener (this);

    addAndMakeVisible (sRingMod = new Slider (T("Ring Modulation")));
    sRingMod->setTooltip (T("Ring Modulation"));
    sRingMod->setRange (0, 99, 0);
    sRingMod->setSliderStyle (Slider::RotaryVerticalDrag);
    sRingMod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRingMod->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sRingMod->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sRingMod->addListener (this);

    addAndMakeVisible (sFAtt = new Slider (T("Filter Env Attack")));
    sFAtt->setTooltip (T("Filter Env Attack"));
    sFAtt->setRange (0, 100, 0);
    sFAtt->setSliderStyle (Slider::LinearVertical);
    sFAtt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFAtt->addListener (this);

    addAndMakeVisible (sFDec = new Slider (T("Filter Env Decay")));
    sFDec->setTooltip (T("Filter Env Decay"));
    sFDec->setRange (0, 100, 0);
    sFDec->setSliderStyle (Slider::LinearVertical);
    sFDec->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFDec->addListener (this);

    addAndMakeVisible (sFSus = new Slider (T("Filter Env Sustain")));
    sFSus->setTooltip (T("Filter Env Sustain"));
    sFSus->setRange (0, 100, 0);
    sFSus->setSliderStyle (Slider::LinearVertical);
    sFSus->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFSus->addListener (this);

    addAndMakeVisible (sFRel = new Slider (T("Filter Env Release")));
    sFRel->setTooltip (T("Filter Env Release"));
    sFRel->setRange (0, 100, 0);
    sFRel->setSliderStyle (Slider::LinearVertical);
    sFRel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFRel->addListener (this);

    addAndMakeVisible (audioled = new LED());
    addAndMakeVisible (sStereo = new Slider (T("Osc Separation")));
    sStereo->setTooltip (T("Osc Separation"));
    sStereo->setRange (-99, 99, 0);
    sStereo->setSliderStyle (Slider::RotaryVerticalDrag);
    sStereo->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sStereo->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sStereo->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sStereo->addListener (this);

    addAndMakeVisible (sOscMix = new Slider (T("Osc Mix")));
    sOscMix->setTooltip (T("Osc Mix"));
    sOscMix->setRange (-99, 99, 0);
    sOscMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sOscMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOscMix->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sOscMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sOscMix->addListener (this);

    addAndMakeVisible (clipled = new LED());
    addAndMakeVisible (sMode = new TextButton (T("Polyphony")));
    sMode->setTooltip (T("Mono Mode"));
    sMode->setButtonText (T("Mono"));
    sMode->addButtonListener (this);
    sMode->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sMode->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (sStereo2 = new Slider (T("Stereo")));
    sStereo2->setTooltip (T("Stereo"));
    sStereo2->setRange (0, 100, 0.1);
    sStereo2->setSliderStyle (Slider::LinearHorizontal);
    sStereo2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sStereo2->addListener (this);

    addAndMakeVisible (sM1 = new Slider (T("M Factor")));
    sM1->setTooltip (T("M Factor"));
    sM1->setRange (0, 100, 0.001);
    sM1->setSliderStyle (Slider::LinearHorizontal);
    sM1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sM1->addListener (this);
    sM1->setSkewFactor (0.5);

    addAndMakeVisible (sPhMod = new Slider (T("Phase Mod")));
    sPhMod->setTooltip (T("Phase Mod"));
    sPhMod->setRange (0, 99, 0);
    sPhMod->setSliderStyle (Slider::RotaryVerticalDrag);
    sPhMod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPhMod->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sPhMod->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sPhMod->addListener (this);
    sPhMod->setSkewFactor (0.5);

    addAndMakeVisible (sDivMix = new Slider (T("Divider Mix")));
    sDivMix->setTooltip (T("Divider Mix"));
    sDivMix->setRange (0, 99, 0.1);
    sDivMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sDivMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDivMix->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sDivMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sDivMix->addListener (this);

    addAndMakeVisible (info = new Label (T("new label"),
                                         String::empty));
    info->setFont (Font (11.0000f, Font::plain));
    info->setJustificationType (Justification::centredLeft);
    info->setEditable (false, false, false);
    info->setColour (Label::textColourId, Colour (0x6affffff));
    info->setColour (TextEditor::textColourId, Colours::black);
    info->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (pizButton = new PizButton());
    addAndMakeVisible (sFKeyFollow = new Slider (T("Filter Key Follow")));
    sFKeyFollow->setTooltip (T("Filter Key Follow"));
    sFKeyFollow->setRange (0, 99, 0);
    sFKeyFollow->setSliderStyle (Slider::RotaryVerticalDrag);
    sFKeyFollow->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFKeyFollow->setColour (Slider::rotarySliderFillColourId, Colour (0x0));
    sFKeyFollow->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff));
    sFKeyFollow->setColour (Slider::textBoxTextColourId, Colours::white);
    sFKeyFollow->addListener (this);

    addAndMakeVisible (nextButton = new TextButton (T("next")));
    nextButton->setTooltip (T("Next Preset"));
    nextButton->setButtonText (T(">"));
    nextButton->addButtonListener (this);
    nextButton->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    nextButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    nextButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (prevButton = new TextButton (T("previous")));
    prevButton->setTooltip (T("Previous Preset"));
    prevButton->setButtonText (T("<"));
    prevButton->addButtonListener (this);
    prevButton->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    prevButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    prevButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (sReset = new TextButton (T("Reset")));
    sReset->setTooltip (T("Reset all parameters"));
    sReset->addButtonListener (this);
    sReset->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    sReset->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sReset->setColour (TextButton::textColourOnId, Colour (0xffb7b7b7));

    addAndMakeVisible (sOPLP = new Slider (T("Harshness")));
    sOPLP->setTooltip (T("Harshness"));
    sOPLP->setRange (0, 99, 0);
    sOPLP->setSliderStyle (Slider::RotaryVerticalDrag);
    sOPLP->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOPLP->setColour (Slider::rotarySliderFillColourId, Colour (0x0));
    sOPLP->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff));
    sOPLP->setColour (Slider::textBoxTextColourId, Colours::white);
    sOPLP->addListener (this);

    addAndMakeVisible (sPostDivMix = new Slider (T("Post Divider Mix")));
    sPostDivMix->setTooltip (T("Post Divider Mix"));
    sPostDivMix->setRange (0, 99, 0.1);
    sPostDivMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sPostDivMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPostDivMix->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sPostDivMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sPostDivMix->addListener (this);

    addAndMakeVisible (sSavePatch = new TextButton (T("Save Patch")));
    sSavePatch->setTooltip (T("Save patch"));
    sSavePatch->setButtonText (T("Save patch"));
    sSavePatch->addButtonListener (this);
    sSavePatch->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    sSavePatch->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sSavePatch->setColour (TextButton::textColourOnId, Colour (0xc5ffffff));

    addAndMakeVisible (sSavePatch2 = new TextButton (T("Save Bank")));
    sSavePatch2->setTooltip (T("Save bank"));
    sSavePatch2->setButtonText (T("Save bank"));
    sSavePatch2->addButtonListener (this);
    sSavePatch2->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    sSavePatch2->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sSavePatch2->setColour (TextButton::textColourOnId, Colour (0xc5ffffff));

    addAndMakeVisible (info3 = new Label (T("new label"),
                                          T("128:")));
    info3->setFont (Font (11.0000f, Font::plain));
    info3->setJustificationType (Justification::centred);
    info3->setEditable (false, false, false);
    info3->setColour (Label::textColourId, Colours::white);
    info3->setColour (TextEditor::textColourId, Colours::black);
    info3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (info2 = new Label (T("new label"),
                                          T("patch name")));
    info2->setTooltip (T("Rename Patch"));
    info2->setFont (Font (11.0000f, Font::plain));
    info2->setJustificationType (Justification::centredLeft);
    info2->setEditable (false, true, false);
    info2->setColour (Label::textColourId, Colours::white);
    info2->setColour (TextEditor::textColourId, Colour (0xffffff9f));
    info2->setColour (TextEditor::backgroundColourId, Colour (0x0));
    info2->setColour (TextEditor::highlightColourId, Colour (0x7bffff00));
    info2->addListener (this);

    addAndMakeVisible (loadButton = new TextButton (T("Load Patch")));
    loadButton->setTooltip (T("Load bank/patch"));
    loadButton->setButtonText (T("Load"));
    loadButton->addButtonListener (this);
    loadButton->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    loadButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    loadButton->setColour (TextButton::textColourOnId, Colour (0xffb7b7b7));

    addAndMakeVisible (filterModeBox = new ComboBox (T("Filter Mode")));
    filterModeBox->setTooltip (T("Filter Mode"));
    filterModeBox->setEditableText (false);
    filterModeBox->setJustificationType (Justification::centredLeft);
    filterModeBox->setTextWhenNothingSelected (T("Formant"));
    filterModeBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    filterModeBox->addItem (T("Off"), 1);
    filterModeBox->addItem (T("Low24"), 2);
    filterModeBox->addItem (T("Low"), 3);
    filterModeBox->addItem (T("Band"), 4);
    filterModeBox->addItem (T("Notch"), 5);
    filterModeBox->addItem (T("High"), 6);
    filterModeBox->addItem (T("Formant"), 7);
    filterModeBox->addListener (this);

    addAndMakeVisible (sOctave1 = new Slider (T("Osc 1 Octave")));
    sOctave1->setTooltip (T("Osc 1 Octave"));
    sOctave1->setRange (-12, 6, 1);
    sOctave1->setSliderStyle (Slider::RotaryVerticalDrag);
    sOctave1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOctave1->setColour (Slider::rotarySliderFillColourId, Colour (0x0));
    sOctave1->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff));
    sOctave1->setColour (Slider::textBoxTextColourId, Colours::white);
    sOctave1->addListener (this);

    addAndMakeVisible (comboBox = new ComboBox (T("Waveform1")));
    comboBox->setTooltip (T("Waveform1"));
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (T("???????"));
    comboBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBox->addItem (T("RampUp"), 1);
    comboBox->addItem (T("RampDown"), 2);
    comboBox->addItem (T("Square"), 3);
    comboBox->addItem (T("Triangle"), 4);
    comboBox->addItem (T("Sine"), 5);
    comboBox->addItem (T("Minkowski"), 6);
    comboBox->addItem (T("Weierstrass"), 7);
    comboBox->addItem (T("AutoAlias"), 8);
    comboBox->addItem (T("Eight"), 9);
    comboBox->addItem (T("OddEight"), 10);
    comboBox->addItem (T("Computer"), 11);
    comboBox->addItem (T("Funnel"), 12);
    comboBox->addItem (T("Grate"), 13);
    comboBox->addItem (T("Noise"), 14);
    comboBox->addItem (T("Sine+"), 15);
    comboBox->addItem (T("Narrow"), 16);
    comboBox->addItem (T("Octaves"), 17);
    comboBox->addItem (T("Ughhh"), 18);
    comboBox->addListener (this);

    addAndMakeVisible (sOctave2 = new Slider (T("Osc 2 Octave")));
    sOctave2->setTooltip (T("Osc 2 Octave"));
    sOctave2->setRange (-12, 6, 1);
    sOctave2->setSliderStyle (Slider::RotaryVerticalDrag);
    sOctave2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOctave2->setColour (Slider::rotarySliderFillColourId, Colour (0x0));
    sOctave2->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff));
    sOctave2->setColour (Slider::textBoxTextColourId, Colours::white);
    sOctave2->addListener (this);

    addAndMakeVisible (comboBox2 = new ComboBox (T("Waveform2")));
    comboBox2->setTooltip (T("Waveform2"));
    comboBox2->setEditableText (false);
    comboBox2->setJustificationType (Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected (T("???????"));
    comboBox2->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBox2->addItem (T("RampUp"), 1);
    comboBox2->addItem (T("RampDown"), 2);
    comboBox2->addItem (T("Square"), 3);
    comboBox2->addItem (T("Triangle"), 4);
    comboBox2->addItem (T("Sine"), 5);
    comboBox2->addItem (T("Minkowski"), 6);
    comboBox2->addItem (T("Weierstrass"), 7);
    comboBox2->addItem (T("AutoAlias"), 8);
    comboBox2->addItem (T("Eight"), 9);
    comboBox2->addItem (T("OddEight"), 10);
    comboBox2->addItem (T("Computer"), 11);
    comboBox2->addItem (T("Funnel"), 12);
    comboBox2->addItem (T("Grate"), 13);
    comboBox2->addItem (T("Noise"), 14);
    comboBox2->addItem (T("Sine+"), 15);
    comboBox2->addItem (T("Narrow"), 16);
    comboBox2->addItem (T("Octaves"), 17);
    comboBox2->addItem (T("Ughhh"), 18);
    comboBox2->addListener (this);

    addAndMakeVisible (sChannel = new Slider (T("MIDI Channel")));
    sChannel->setTooltip (T("MIDI Channel"));
    sChannel->setRange (0, 16, 1);
    sChannel->setSliderStyle (Slider::RotaryVerticalDrag);
    sChannel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sChannel->setColour (Slider::thumbColourId, Colour (0xbbbbff));
    sChannel->setColour (Slider::trackColourId, Colour (0xffffff));
    sChannel->setColour (Slider::rotarySliderFillColourId, Colour (0xff));
    sChannel->setColour (Slider::rotarySliderOutlineColourId, Colour (0x0));
    sChannel->setColour (Slider::textBoxTextColourId, Colours::white);
    sChannel->addListener (this);

    addAndMakeVisible (sOctave = new Slider (T("Osc 2 Harmonic")));
    sOctave->setTooltip (T("Osc 2 Harmonic"));
    sOctave->setRange (0, 12, 1);
    sOctave->setSliderStyle (Slider::RotaryVerticalDrag);
    sOctave->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOctave->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sOctave->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sOctave->addListener (this);

    addAndMakeVisible (sUseProgCh = new TextButton (T("UseProgCh")));
    sUseProgCh->setTooltip (T("Use Program Change"));
    sUseProgCh->setButtonText (T("Use ProgCh"));
    sUseProgCh->addButtonListener (this);
    sUseProgCh->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sUseProgCh->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sUseProgCh->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (sM1Mix = new Slider (T("M Effect Mix")));
    sM1Mix->setTooltip (T("M Effect Mix"));
    sM1Mix->setRange (0, 99, 0.1);
    sM1Mix->setSliderStyle (Slider::RotaryVerticalDrag);
    sM1Mix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sM1Mix->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    sM1Mix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sM1Mix->addListener (this);

    addAndMakeVisible (randomButton = new TextButton (T("Randomize")));
    randomButton->setTooltip (T("Randomize all parameters"));
    randomButton->addButtonListener (this);
    randomButton->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    randomButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    randomButton->setColour (TextButton::textColourOnId, Colour (0xc5ffffff));

    addAndMakeVisible (limiterButton = new TextButton (T("Limiter")));
    limiterButton->setTooltip (T("Limiter"));
    limiterButton->addButtonListener (this);
    limiterButton->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    limiterButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    limiterButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (sExp = new TextButton (T("Envelope Curve")));
    sExp->setTooltip (T("Percussive Envelope"));
    sExp->setButtonText (T("P"));
    sExp->addButtonListener (this);
    sExp->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sExp->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (sFExp = new TextButton (T("Filter Envelope Curve")));
    sFExp->setTooltip (T("Percussive Envelope"));
    sFExp->setButtonText (T("P"));
    sFExp->addButtonListener (this);
    sFExp->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sFExp->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (midiled = new LED());
    addAndMakeVisible (saveSnapshotButtonB = new TextButton (T("Save Snapshot")));
    saveSnapshotButtonB->setTooltip (T("Save Snapshot B"));
    saveSnapshotButtonB->setButtonText (T("S"));
    saveSnapshotButtonB->addButtonListener (this);
    saveSnapshotButtonB->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    saveSnapshotButtonB->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    saveSnapshotButtonB->setColour (TextButton::textColourOnId, Colour (0xffb7b7b7));

    addAndMakeVisible (recallSnapshotButtonB = new TextButton (T("Recall Snapshot")));
    recallSnapshotButtonB->setTooltip (T("Recall Snapshot B"));
    recallSnapshotButtonB->setButtonText (T("R"));
    recallSnapshotButtonB->addButtonListener (this);
    recallSnapshotButtonB->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    recallSnapshotButtonB->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    recallSnapshotButtonB->setColour (TextButton::textColourOnId, Colour (0xffb7b7b7));

    addAndMakeVisible (sMorph = new Slider (T("Morph")));
    sMorph->setTooltip (T("Morph"));
    sMorph->setRange (-100, 100, 0);
    sMorph->setSliderStyle (Slider::LinearHorizontal);
    sMorph->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sMorph->setColour (Slider::thumbColourId, Colour (0x20ababab));
    sMorph->setColour (Slider::trackColourId, Colour (0xffffff));
    sMorph->setColour (Slider::rotarySliderFillColourId, Colour (0x360000ff));
    sMorph->addListener (this);

    addAndMakeVisible (saveSnapshotButtonA = new TextButton (T("Save Snapshot")));
    saveSnapshotButtonA->setTooltip (T("Save Snapshot A"));
    saveSnapshotButtonA->setButtonText (T("S"));
    saveSnapshotButtonA->addButtonListener (this);
    saveSnapshotButtonA->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    saveSnapshotButtonA->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    saveSnapshotButtonA->setColour (TextButton::textColourOnId, Colour (0xffb7b7b7));

    addAndMakeVisible (recallSnapshotButtonA = new TextButton (T("Recall Snapshot")));
    recallSnapshotButtonA->setTooltip (T("Recall Snapshot A"));
    recallSnapshotButtonA->setButtonText (T("R"));
    recallSnapshotButtonA->addButtonListener (this);
    recallSnapshotButtonA->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    recallSnapshotButtonA->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    recallSnapshotButtonA->setColour (TextButton::textColourOnId, Colour (0xffb7b7b7));

    addAndMakeVisible (aboutbox = new AboutBox());
    addAndMakeVisible (sPitchShift = new TextButton (T("Pitch Shift Input")));
    sPitchShift->setTooltip (T("Pitch Shift Input"));
    sPitchShift->setButtonText (T("PitchShift"));
    sPitchShift->addButtonListener (this);
    sPitchShift->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sPitchShift->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));

    drawable1 = Drawable::createFromImageData (alias_svg2, alias_svg2Size);
    cachedImage_mralias2_png = ImageCache::getFromMemory (mralias2_png, mralias2_pngSize);
    drawable4 = Drawable::createFromImageData (whitetitle_svg, whitetitle_svgSize);
    drawable7 = Drawable::createFromImageData (title_svg2, title_svg2Size);

    //[UserPreSize]

    resizer->setMouseClickGrabsKeyboardFocus(false);
    resizeLimits.setFixedAspectRatio (aspectRatio);
    resizeLimits.setSizeLimits (200, 150, 1024, 768);

    sAlias->setMouseClickGrabsKeyboardFocus(false);
    sAlias->setSliderSnapsToMousePosition(false);
    sAlias->addMouseListener(this,false);
    sAlias->setDoubleClickReturnValue(true,0.0);
    sAlias->setMouseDragSensitivity(204);

    sCutoff->setMouseClickGrabsKeyboardFocus(false);
    sCutoff->setSliderSnapsToMousePosition(false);
    sCutoff->setDoubleClickReturnValue(true,sCutoff->getMaximum());
    sCutoff->addMouseListener(this,false);

    sDivide->setMouseClickGrabsKeyboardFocus(false);
    sDivide->setSliderSnapsToMousePosition(false);
    sDivide->setDoubleClickReturnValue(true,0.0);
    sDivide->addMouseListener(this,false);

    sRate->setMouseClickGrabsKeyboardFocus(false);
    sRate->setSliderSnapsToMousePosition(false);
    sRate->setDoubleClickReturnValue(true,sRate->getMaximum());
    sRate->addMouseListener(this,false);

    sSineMix->setMouseClickGrabsKeyboardFocus(false);
    sSineMix->setSliderSnapsToMousePosition(false);
    sSineMix->setDoubleClickReturnValue(true,0);
    sSineMix->addMouseListener(this,false);

    sSineRes->setMouseClickGrabsKeyboardFocus(false);
    sSineRes->setSliderSnapsToMousePosition(false);
    sSineRes->setDoubleClickReturnValue(true,20);
    sSineRes->addMouseListener(this,false);

    sPostDivide->setMouseClickGrabsKeyboardFocus(false);
    sPostDivide->setSliderSnapsToMousePosition(false);
    sPostDivide->setDoubleClickReturnValue(true,0);
    sPostDivide->addMouseListener(this,false);

    sClip->setMouseClickGrabsKeyboardFocus(false);
    sClip->setSliderSnapsToMousePosition(false);
    sClip->setDoubleClickReturnValue(true,0);
    sClip->addMouseListener(this,false);

    sAInertia->setMouseClickGrabsKeyboardFocus(false);
    sAInertia->setSliderSnapsToMousePosition(false);
    sAInertia->setDoubleClickReturnValue(true,0);
    sAInertia->addMouseListener(this,false);

    sAtt->setMouseClickGrabsKeyboardFocus(false);
    sAtt->setSliderSnapsToMousePosition(false);
    sAtt->setDoubleClickReturnValue(true,1.0);
    sAtt->addMouseListener(this,false);

    sDec->setMouseClickGrabsKeyboardFocus(false);
    sDec->setSliderSnapsToMousePosition(false);
    sDec->setDoubleClickReturnValue(true,1);
    sDec->addMouseListener(this,false);

    sSus->setMouseClickGrabsKeyboardFocus(false);
    sSus->setSliderSnapsToMousePosition(false);
    sSus->setDoubleClickReturnValue(true,100);
    sSus->addMouseListener(this,false);

    sRel->setMouseClickGrabsKeyboardFocus(false);
    sRel->setSliderSnapsToMousePosition(false);
    sRel->setDoubleClickReturnValue(true,1);
    sRel->addMouseListener(this,false);

    sFAtt->setMouseClickGrabsKeyboardFocus(false);
    sFAtt->setSliderSnapsToMousePosition(false);
    sFAtt->setDoubleClickReturnValue(true,0);
    sFAtt->addMouseListener(this,false);

    sFDec->setMouseClickGrabsKeyboardFocus(false);
    sFDec->setSliderSnapsToMousePosition(false);
    sFDec->setDoubleClickReturnValue(true,0);
    sFDec->addMouseListener(this,false);

    sFSus->setMouseClickGrabsKeyboardFocus(false);
    sFSus->setSliderSnapsToMousePosition(false);
    sFSus->setDoubleClickReturnValue(true,100);
    sFSus->addMouseListener(this,false);

    sFRel->setMouseClickGrabsKeyboardFocus(false);
    sFRel->setSliderSnapsToMousePosition(false);
    sFRel->setDoubleClickReturnValue(true,100);
    sFRel->addMouseListener(this,false);

    sDivEnv->setMouseClickGrabsKeyboardFocus(false);
    sDivEnv->setSliderSnapsToMousePosition(false);
    sDivEnv->setDoubleClickReturnValue(true,0);
    sDivEnv->addMouseListener(this,false);

    sRes->setMouseClickGrabsKeyboardFocus(false);
    sRes->setSliderSnapsToMousePosition(false);
    sRes->setDoubleClickReturnValue(true,0);
    sRes->addMouseListener(this,false);

    sBRMix->setMouseClickGrabsKeyboardFocus(false);
    sBRMix->setSliderSnapsToMousePosition(false);
    sBRMix->setDoubleClickReturnValue(true,0);
    sBRMix->addMouseListener(this,false);

    sVolume->setMouseClickGrabsKeyboardFocus(false);
    sVolume->setSliderSnapsToMousePosition(false);
    sVolume->setDoubleClickReturnValue(true,50);
    sVolume->addMouseListener(this,false);

    sSineFreq->setMouseClickGrabsKeyboardFocus(false);
    sSineFreq->setSliderSnapsToMousePosition(false);
    sSineFreq->setDoubleClickReturnValue(true,50);
    sSineFreq->addMouseListener(this,false);

    sPBRange->setMouseClickGrabsKeyboardFocus(false);
    sPBRange->setSliderSnapsToMousePosition(false);
    sPBRange->setDoubleClickReturnValue(true,2);
    sPBRange->setMouseDragSensitivity(100);
    sPBRange->addMouseListener(this,false);

    sThresh->setMouseClickGrabsKeyboardFocus(false);
    sThresh->setSliderSnapsToMousePosition(false);
    sThresh->setDoubleClickReturnValue(true,50);
    sThresh->addMouseListener(this,false);

    sFreq1->setMouseClickGrabsKeyboardFocus(false);
    sFreq1->setSliderSnapsToMousePosition(false);
    sFreq1->setDoubleClickReturnValue(true,0);
    sFreq1->addMouseListener(this,false);

    sRingMod->setMouseClickGrabsKeyboardFocus(false);
    sRingMod->setSliderSnapsToMousePosition(false);
    sRingMod->setDoubleClickReturnValue(true,0);
    sRingMod->addMouseListener(this,false);

    sVelSens->setMouseClickGrabsKeyboardFocus(false);
    sVelSens->setSliderSnapsToMousePosition(false);
    sVelSens->setDoubleClickReturnValue(true,50);
    sVelSens->addMouseListener(this,false);

    sInputGain->setMouseClickGrabsKeyboardFocus(false);
    sInputGain->setSliderSnapsToMousePosition(false);
    sInputGain->setDoubleClickReturnValue(true,50);
    sInputGain->addMouseListener(this,false);

    sWet->setMouseClickGrabsKeyboardFocus(false);
    sWet->setSliderSnapsToMousePosition(false);
    sWet->setDoubleClickReturnValue(true,0);
    sWet->addMouseListener(this,false);

    sOscGain->setMouseClickGrabsKeyboardFocus(false);
    sOscGain->setSliderSnapsToMousePosition(false);
    sOscGain->setDoubleClickReturnValue(true,50);
    sOscGain->addMouseListener(this,false);

    sFiltEnv->setMouseClickGrabsKeyboardFocus(false);
    sFiltEnv->setSliderSnapsToMousePosition(false);
    sFiltEnv->setDoubleClickReturnValue(true,0);
    sFiltEnv->addMouseListener(this,false);

    sOscMix->setMouseClickGrabsKeyboardFocus(false);
    sOscMix->setSliderSnapsToMousePosition(false);
    sOscMix->setDoubleClickReturnValue(true,0);
    sOscMix->addMouseListener(this,false);

    sStereo->setMouseClickGrabsKeyboardFocus(false);
    sStereo->setSliderSnapsToMousePosition(false);
    sStereo->setDoubleClickReturnValue(true,0);
    sStereo->addMouseListener(this,false);

    sStereo2->setMouseClickGrabsKeyboardFocus(false);
    sStereo2->setSliderSnapsToMousePosition(false);
    sStereo2->setDoubleClickReturnValue(true,100);
    sStereo2->addMouseListener(this,false);

    sOctave->setMouseClickGrabsKeyboardFocus(false);
    sOctave->setSliderSnapsToMousePosition(false);
    sOctave->setDoubleClickReturnValue(true,0);
    sOctave->addMouseListener(this,false);

    sOctave1->setMouseClickGrabsKeyboardFocus(false);
    sOctave1->setSliderSnapsToMousePosition(false);
    sOctave1->setDoubleClickReturnValue(true,0);
    sOctave1->addMouseListener(this,false);

    sOctave2->setMouseClickGrabsKeyboardFocus(false);
    sOctave2->setSliderSnapsToMousePosition(false);
    sOctave2->setDoubleClickReturnValue(true,0);
    sOctave2->addMouseListener(this,false);

    sFVSens->setMouseClickGrabsKeyboardFocus(false);
    sFVSens->setSliderSnapsToMousePosition(false);
    sFVSens->setDoubleClickReturnValue(true,0);
    sFVSens->addMouseListener(this,false);

    sM1->setMouseClickGrabsKeyboardFocus(false);
    sM1->setSliderSnapsToMousePosition(false);
    sM1->setDoubleClickReturnValue(true,0);
    sM1->addMouseListener(this,false);

    sPhMod->setMouseClickGrabsKeyboardFocus(false);
    sPhMod->setSliderSnapsToMousePosition(false);
    sPhMod->setDoubleClickReturnValue(true,0);
    sPhMod->addMouseListener(this,false);

    sDivMix->setMouseClickGrabsKeyboardFocus(false);
    sDivMix->setSliderSnapsToMousePosition(false);
    sDivMix->setDoubleClickReturnValue(true,99);
    sDivMix->addMouseListener(this,false);

    sFKeyFollow->setMouseClickGrabsKeyboardFocus(false);
    sFKeyFollow->setSliderSnapsToMousePosition(false);
    sFKeyFollow->setDoubleClickReturnValue(true,0);
    sFKeyFollow->addMouseListener(this,false);

    sOPLP->setMouseClickGrabsKeyboardFocus(false);
    sOPLP->setSliderSnapsToMousePosition(false);
    sOPLP->setDoubleClickReturnValue(true,89);
    sOPLP->addMouseListener(this,false);

    sPostDivMix->setMouseClickGrabsKeyboardFocus(false);
    sPostDivMix->setSliderSnapsToMousePosition(false);
    sPostDivMix->setDoubleClickReturnValue(true,99);
    sPostDivMix->addMouseListener(this,false);

    sChannel->setMouseClickGrabsKeyboardFocus(false);
    sChannel->setSliderSnapsToMousePosition(false);
    sChannel->setDoubleClickReturnValue(true,0);
    //sChannel->addMouseListener(this,false);

    sM1Mix->setMouseClickGrabsKeyboardFocus(false);
    sM1Mix->setSliderSnapsToMousePosition(false);
    sM1Mix->setDoubleClickReturnValue(true,99);
    sM1Mix->addMouseListener(this,false);

    sMorph->setMouseClickGrabsKeyboardFocus(false);
    sMorph->setSliderSnapsToMousePosition(true);
    sMorph->setDoubleClickReturnValue(true,-100);
    sMorph->addMouseListener(this,false);
    sMorph->setColour(Slider::textBoxTextColourId,Colours::transparentWhite);

    comboBox->setMouseClickGrabsKeyboardFocus(false);
    comboBox->addMouseListener(this,false);
    comboBox2->setMouseClickGrabsKeyboardFocus(false);
    comboBox2->addMouseListener(this,false);
    filterModeBox->setMouseClickGrabsKeyboardFocus(false);
    filterModeBox->addMouseListener(this,false);

    info->setMouseClickGrabsKeyboardFocus(false);
    info->addListener(this);
    info2->setMouseClickGrabsKeyboardFocus(true);
    info3->setMouseClickGrabsKeyboardFocus(false);

    midiled->setMouseClickGrabsKeyboardFocus(false);
    audioled->setMouseClickGrabsKeyboardFocus(false);
    clipled->setMouseClickGrabsKeyboardFocus(false);

    pizButton->setTooltip(T("Insert Piz Here-> Mr. Alias ") + String(T(JucePlugin_VersionString)));
    pizButton->addButtonListener(this);
    pizButton->setMouseClickGrabsKeyboardFocus(false);

    aboutbox->setVisible(false);
    aboutbox->addButtonListener(this);
    aboutbox->setMouseClickGrabsKeyboardFocus(false);

    //parameter buttons
    sExp->setMouseClickGrabsKeyboardFocus(false);
    sExp->addMouseListener(this,false);
    sFExp->setMouseClickGrabsKeyboardFocus(false);
    sFExp->addMouseListener(this,false);
    sMode->setMouseClickGrabsKeyboardFocus(false);
    sMode->addMouseListener(this,false);
    limiterButton->setMouseClickGrabsKeyboardFocus(false);
    limiterButton->addMouseListener(this,false);

    //patch controls
    sUseProgCh->setMouseClickGrabsKeyboardFocus(false);
    sReset->setMouseClickGrabsKeyboardFocus(false);
    randomButton->setMouseClickGrabsKeyboardFocus(false);
	randomButton->addMouseListener(this,false);
    nextButton->setMouseClickGrabsKeyboardFocus(false);
    prevButton->setMouseClickGrabsKeyboardFocus(false);
    sSavePatch->setMouseClickGrabsKeyboardFocus(false);
    sSavePatch2->setMouseClickGrabsKeyboardFocus(false);
    loadButton->setMouseClickGrabsKeyboardFocus(false);
    saveSnapshotButtonA->setMouseClickGrabsKeyboardFocus(false);
    saveSnapshotButtonB->setMouseClickGrabsKeyboardFocus(false);
    recallSnapshotButtonA->setMouseClickGrabsKeyboardFocus(false);
    recallSnapshotButtonB->setMouseClickGrabsKeyboardFocus(false);
    patchBox->clear();
    for (int i=0;i<numPrograms;i++) {
        patchBox->addItem (String(i+1)+". "+ownerFilter->getProgramName(i), i+1);
    }
    //cc mapping sliders for right-click menus
    for (int i=0;i<numParams;i++) {
        oldccmap[i] = ownerFilter->getCCMapping(i);
        addAndMakeVisible (ccmapbox[i] = new CCMapSlider (String(i)));
        ccmapbox[i]->setRange (-1, 130, 1);
        ccmapbox[i]->setSliderStyle (Slider::IncDecButtons);
        ccmapbox[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 100, 20);
        ccmapbox[i]->setColour (Slider::textBoxTextColourId,Colours::black);
        ccmapbox[i]->addListener (this);
        ccmapbox[i]->setValue ((double)oldccmap[i],false);
        ccmapbox[i]->setIncDecButtonsMode(Slider::incDecButtonsDraggable_AutoDirection);
    }

    init=true;
    #if 0
    //[/UserPreSize]

    setSize (480, 320);

    //[Constructor] You can add your own custom stuff here..
    #endif
     static PizLookAndFeel Look;
     LookAndFeel::setDefaultLookAndFeel (&Look);
     setMouseClickGrabsKeyboardFocus(false);

     setSize ((int)(ownerFilter->lastUIHeight*aspectRatio),
             ownerFilter->lastUIHeight);

//    params = new float[numParams];
//    ccmap = new int[numParams];

    ownerFilter->editorIsShowing=true;
    ownerFilter->addChangeListener (this);
    ownerFilter->leds->addChangeListener (this);
    updateParametersFromFilter();
    ownerFilter->dispatchPendingMessages();
    logDebugString("GUI created");
    repaint();
    //[/Constructor]
}

MrAlias2Editor::~MrAlias2Editor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    if(getFilter()) {
		getFilter()->dispatchPendingMessages();
		getFilter()->editorIsShowing=false;
		getFilter()->removeChangeListener (this);
		getFilter()->leds->removeChangeListener (this);
    }
    //[/Destructor_pre]

    deleteAndZero (patchBox);
    deleteAndZero (sAlias);
    deleteAndZero (sCutoff);
    deleteAndZero (sDivide);
    deleteAndZero (sAtt);
    deleteAndZero (sRate);
    deleteAndZero (sSineMix);
    deleteAndZero (sSineRes);
    deleteAndZero (sPostDivide);
    deleteAndZero (sClip);
    deleteAndZero (sAInertia);
    deleteAndZero (sDec);
    deleteAndZero (sSus);
    deleteAndZero (sRel);
    deleteAndZero (sDivEnv);
    deleteAndZero (sRes);
    deleteAndZero (sBRMix);
    deleteAndZero (sVolume);
    deleteAndZero (sSineFreq);
    deleteAndZero (sVelSens);
    deleteAndZero (sFiltEnv);
    deleteAndZero (sFVSens);
    deleteAndZero (sPBRange);
    deleteAndZero (sInputGain);
    deleteAndZero (sWet);
    deleteAndZero (sOscGain);
    deleteAndZero (sThresh);
    deleteAndZero (sFreq1);
    deleteAndZero (sRingMod);
    deleteAndZero (sFAtt);
    deleteAndZero (sFDec);
    deleteAndZero (sFSus);
    deleteAndZero (sFRel);
    deleteAndZero (audioled);
    deleteAndZero (sStereo);
    deleteAndZero (sOscMix);
    deleteAndZero (clipled);
    deleteAndZero (sMode);
    deleteAndZero (sStereo2);
    deleteAndZero (sM1);
    deleteAndZero (sPhMod);
    deleteAndZero (sDivMix);
    deleteAndZero (info);
    deleteAndZero (pizButton);
    deleteAndZero (sFKeyFollow);
    deleteAndZero (nextButton);
    deleteAndZero (prevButton);
    deleteAndZero (sReset);
    deleteAndZero (sOPLP);
    deleteAndZero (sPostDivMix);
    deleteAndZero (sSavePatch);
    deleteAndZero (sSavePatch2);
    deleteAndZero (info3);
    deleteAndZero (info2);
    deleteAndZero (loadButton);
    deleteAndZero (filterModeBox);
    deleteAndZero (sOctave1);
    deleteAndZero (comboBox);
    deleteAndZero (sOctave2);
    deleteAndZero (comboBox2);
    deleteAndZero (sChannel);
    deleteAndZero (sOctave);
    deleteAndZero (sUseProgCh);
    deleteAndZero (sM1Mix);
    deleteAndZero (randomButton);
    deleteAndZero (limiterButton);
    deleteAndZero (sExp);
    deleteAndZero (sFExp);
    deleteAndZero (midiled);
    deleteAndZero (saveSnapshotButtonB);
    deleteAndZero (recallSnapshotButtonB);
    deleteAndZero (sMorph);
    deleteAndZero (saveSnapshotButtonA);
    deleteAndZero (recallSnapshotButtonA);
    deleteAndZero (aboutbox);
    deleteAndZero (sPitchShift);
    deleteAndZero (resizer);
    deleteAndZero (drawable1);
    //ImageCache::release (cachedImage_mralias2_png);
    deleteAndZero (drawable4);
    deleteAndZero (drawable7);

    //[Destructor]. You can add your own custom destruction code here..
    for (int i=0;i<numParams;i++) deleteAndZero (ccmapbox[i]);
//    if (params) delete [] params;
//    if (ccmap) delete [] ccmap;
    logDebugString("GUI destroyed");
    //[/Destructor]
}

//==============================================================================
void MrAlias2Editor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..

    //int w=getWidth(), h=getHeight();
    //getFilter()->logDebugString("paint()");

    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float>(0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f)),
                               RectanglePlacement::stretchToFit, 0);

    g.setColour (Colours::black.withAlpha (0.0750f));
    g.drawImageWithin (cachedImage_mralias2_png,
                       0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f),
                       RectanglePlacement::centred,
                       false);

    g.setColour (Colour (0x68a74848));
    g.fillPath (internalPath2);

    g.setColour (Colour (0x68a58d2a));
    g.fillRect (proportionOfWidth (0.0078f), proportionOfHeight (0.1711f), proportionOfWidth (0.3078f), proportionOfHeight (0.2923f));

    g.setColour (Colour (0x687aa52a));
    g.fillRect (proportionOfWidth (0.6830f), proportionOfHeight (0.2660f), proportionOfWidth (0.3090f), proportionOfHeight (0.4830f));

    g.setColour (Colour (0x682a8da5));
    g.fillPath (internalPath3);

    g.setColour (Colour (0x68a56b2a));
    g.fillRect (proportionOfWidth (0.3454f), proportionOfHeight (0.3796f), proportionOfWidth (0.3092f), proportionOfHeight (0.2153f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.3532f), proportionOfHeight (0.8212f), proportionOfWidth (0.2922f), proportionOfHeight (0.1404f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.0169f), proportionOfHeight (0.4961f), proportionOfWidth (0.2896f), proportionOfHeight (0.2365f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.3708f), proportionOfHeight (0.1719f), proportionOfWidth (0.1375f), proportionOfHeight (0.0469f));

    g.setColour (Colours::black);
    jassert (drawable4 != 0);
    if (drawable4 != 0)
        drawable4->drawWithin (g, Rectangle<float>(proportionOfWidth (0.0250f), proportionOfHeight (0.0375f), proportionOfWidth (0.7583f), proportionOfHeight (0.0781f)),
                               RectanglePlacement::centred, 0);

    g.setColour (Colour (0x9bff9a9a));
    g.fillPath (internalPath5);

    g.setColour (Colour (0x62ffffff));
    g.fillPath (internalPath6);
    g.setColour (Colours::black);
    g.strokePath (internalPath6, PathStrokeType (1.6000f));

    g.setColour (Colours::black.withAlpha (0.9060f));
    jassert (drawable7 != 0);
    if (drawable7 != 0)
        drawable7->drawWithin (g, Rectangle<float>(proportionOfWidth (0.0292f), proportionOfHeight (0.0437f), proportionOfWidth (0.7583f), proportionOfHeight (0.0781f)),
                               RectanglePlacement::centred, 0);

    g.setColour (Colour (0x6877657e));
    g.fillRect (proportionOfWidth (0.0078f), proportionOfHeight (0.5038f), proportionOfWidth (0.3078f), proportionOfHeight (0.2442f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.6957f), proportionOfHeight (0.5116f), proportionOfWidth (0.2878f), proportionOfHeight (0.2245f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.5313f), proportionOfHeight (0.1312f), proportionOfWidth (0.4521f), proportionOfHeight (0.0906f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.6542f), proportionOfHeight (0.1375f), proportionOfWidth (0.2479f), proportionOfHeight (0.0406f));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MrAlias2Editor::resized()
{
    patchBox->setBounds (proportionOfWidth (0.8833f), proportionOfHeight (0.1375f), proportionOfWidth (0.0208f), proportionOfHeight (0.0375f));
    sAlias->setBounds (proportionOfWidth (0.0167f), proportionOfHeight (0.3875f), proportionOfWidth (0.2333f), proportionOfHeight (0.0531f));
    sCutoff->setBounds (proportionOfWidth (0.0229f), proportionOfHeight (0.5313f), proportionOfWidth (0.1167f), proportionOfHeight (0.1844f));
    sDivide->setBounds (proportionOfWidth (0.3562f), proportionOfHeight (0.3938f), proportionOfWidth (0.2333f), proportionOfHeight (0.0531f));
    sAtt->setBounds (proportionOfWidth (0.6938f), proportionOfHeight (0.2844f), proportionOfWidth (0.0500f), proportionOfHeight (0.2125f));
    sRate->setBounds (proportionOfWidth (0.0188f), proportionOfHeight (0.8125f), proportionOfWidth (0.2167f), proportionOfHeight (0.0531f));
    sSineMix->setBounds (proportionOfWidth (0.5646f), proportionOfHeight (0.6531f), proportionOfWidth (0.0854f), proportionOfHeight (0.1063f));
    sSineRes->setBounds (proportionOfWidth (0.3562f), proportionOfHeight (0.6469f), proportionOfWidth (0.2146f), proportionOfHeight (0.0531f));
    sPostDivide->setBounds ((proportionOfWidth (0.3562f)) + roundFloatToInt ((proportionOfWidth (0.2333f)) * 0.0000f), ((proportionOfHeight (0.3938f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f), roundFloatToInt ((proportionOfWidth (0.2333f)) * 1.0000f), proportionOfHeight (0.0531f));
    sClip->setBounds (proportionOfWidth (0.6854f), proportionOfHeight (0.8031f), proportionOfWidth (0.1708f), proportionOfHeight (0.0531f));
    sAInertia->setBounds (proportionOfWidth (0.2521f), proportionOfHeight (0.3719f), proportionOfWidth (0.0542f), proportionOfHeight (0.0875f));
    sDec->setBounds (proportionOfWidth (0.7521f), (proportionOfHeight (0.2844f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0500f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f));
    sSus->setBounds (proportionOfWidth (0.8104f), ((proportionOfHeight (0.2844f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0500f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f));
    sRel->setBounds (proportionOfWidth (0.8708f), (((proportionOfHeight (0.2844f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0500f)) * 1.0000f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    sDivEnv->setBounds (proportionOfWidth (0.9250f), proportionOfHeight (0.3313f), proportionOfWidth (0.0562f), proportionOfHeight (0.0938f));
    sRes->setBounds (proportionOfWidth (0.1854f), (proportionOfHeight (0.5313f)) + roundFloatToInt ((proportionOfHeight (0.1844f)) * 0.0000f), proportionOfWidth (0.1167f), proportionOfHeight (0.1844f));
    sBRMix->setBounds ((proportionOfWidth (0.0188f)) + roundFloatToInt ((proportionOfWidth (0.2167f)) * 1.0481f), (proportionOfHeight (0.8125f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * -0.4118f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    sVolume->setBounds (proportionOfWidth (0.8625f), proportionOfHeight (0.8031f), proportionOfWidth (0.1167f), proportionOfHeight (0.1563f));
    sSineFreq->setBounds ((proportionOfWidth (0.3562f)) + roundFloatToInt ((proportionOfWidth (0.2146f)) * 0.0000f), (proportionOfHeight (0.6469f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f), roundFloatToInt ((proportionOfWidth (0.2146f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.0000f));
    sVelSens->setBounds (proportionOfWidth (0.9250f), proportionOfHeight (0.4125f), proportionOfWidth (0.0562f), proportionOfHeight (0.0938f));
    sFiltEnv->setBounds (proportionOfWidth (0.9250f), proportionOfHeight (0.5688f), proportionOfWidth (0.0562f), proportionOfHeight (0.0938f));
    sFVSens->setBounds (proportionOfWidth (0.9250f), proportionOfHeight (0.6469f), proportionOfWidth (0.0562f), proportionOfHeight (0.0938f));
    sPBRange->setBounds (proportionOfWidth (0.3667f), proportionOfHeight (0.1563f), proportionOfWidth (0.0562f), proportionOfHeight (0.0781f));
    sInputGain->setBounds (proportionOfWidth (0.3604f), proportionOfHeight (0.8375f), proportionOfWidth (0.0812f), proportionOfHeight (0.1125f));
    sWet->setBounds (proportionOfWidth (0.4583f), proportionOfHeight (0.8375f), proportionOfWidth (0.0812f), proportionOfHeight (0.1125f));
    sOscGain->setBounds (proportionOfWidth (0.5562f), proportionOfHeight (0.8375f), proportionOfWidth (0.0812f), proportionOfHeight (0.1125f));
    sThresh->setBounds ((proportionOfWidth (0.3562f)) + roundFloatToInt ((proportionOfWidth (0.2333f)) * 0.0000f), (proportionOfHeight (0.3938f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f), roundFloatToInt ((proportionOfWidth (0.2333f)) * 1.2768f), proportionOfHeight (0.0531f));
    sFreq1->setBounds (proportionOfWidth (0.0125f), proportionOfHeight (0.2625f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    sRingMod->setBounds (proportionOfWidth (0.1333f), proportionOfHeight (0.6563f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    sFAtt->setBounds (proportionOfWidth (0.6938f), proportionOfHeight (0.5156f), proportionOfWidth (0.0500f), roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f));
    sFDec->setBounds (proportionOfWidth (0.7521f), (proportionOfHeight (0.5156f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0500f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f));
    sFSus->setBounds (proportionOfWidth (0.8104f), ((proportionOfHeight (0.5156f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0500f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    sFRel->setBounds (proportionOfWidth (0.8708f), (((proportionOfHeight (0.5156f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0500f)) * 1.0000f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    audioled->setBounds (proportionOfWidth (0.3750f), proportionOfHeight (0.2844f), proportionOfWidth (0.0208f), proportionOfHeight (0.0281f));
    sStereo->setBounds (proportionOfWidth (0.0708f), (proportionOfHeight (0.2625f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    sOscMix->setBounds (proportionOfWidth (0.1354f), (proportionOfHeight (0.2625f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    clipled->setBounds (proportionOfWidth (0.9083f), proportionOfHeight (0.9312f), proportionOfWidth (0.0208f), proportionOfHeight (0.0281f));
    sMode->setBounds (proportionOfWidth (0.4396f), proportionOfHeight (0.1719f), proportionOfWidth (0.0646f), proportionOfHeight (0.0469f));
    sStereo2->setBounds (proportionOfWidth (0.6854f), (proportionOfHeight (0.8031f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.1177f), proportionOfWidth (0.1708f), proportionOfHeight (0.0531f));
    sM1->setBounds ((proportionOfWidth (0.0188f)) + roundFloatToInt ((proportionOfWidth (0.2167f)) * 0.0000f), (proportionOfHeight (0.8125f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.5882f), roundFloatToInt ((proportionOfWidth (0.2167f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.0000f));
    sPhMod->setBounds (proportionOfWidth (0.2562f), ((proportionOfHeight (0.2625f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0303f), roundFloatToInt ((proportionOfWidth (0.0562f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.1031f)) * 1.0000f));
    sDivMix->setBounds (proportionOfWidth (0.5875f), proportionOfHeight (0.3750f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    info->setBounds (proportionOfWidth (0.0125f), proportionOfHeight (0.1406f), proportionOfWidth (0.3313f), proportionOfHeight (0.0313f));
    pizButton->setBounds (proportionOfWidth (0.4146f), proportionOfHeight (0.2375f), proportionOfWidth (0.1688f), proportionOfHeight (0.1344f));
    sFKeyFollow->setBounds (proportionOfWidth (0.2604f), proportionOfHeight (0.6812f), proportionOfWidth (0.0562f), proportionOfHeight (0.0688f));
    nextButton->setBounds (proportionOfWidth (0.5771f), proportionOfHeight (0.1344f), proportionOfWidth (0.0313f), proportionOfHeight (0.0406f));
    prevButton->setBounds (proportionOfWidth (0.5375f), proportionOfHeight (0.1344f), proportionOfWidth (0.0313f), proportionOfHeight (0.0406f));
    sReset->setBounds (proportionOfWidth (0.9104f), proportionOfHeight (0.1813f), proportionOfWidth (0.0688f), proportionOfHeight (0.0406f));
    sOPLP->setBounds (proportionOfWidth (0.0083f), proportionOfHeight (0.6812f), proportionOfWidth (0.0562f), proportionOfHeight (0.0688f));
    sPostDivMix->setBounds (proportionOfWidth (0.5875f), proportionOfHeight (0.5031f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    sSavePatch->setBounds (proportionOfWidth (0.5375f), proportionOfHeight (0.1813f), proportionOfWidth (0.1000f), proportionOfHeight (0.0406f));
    sSavePatch2->setBounds (proportionOfWidth (0.6500f), proportionOfHeight (0.1813f), proportionOfWidth (0.1000f), proportionOfHeight (0.0406f));
    info3->setBounds (proportionOfWidth (0.6104f), proportionOfHeight (0.1344f), proportionOfWidth (0.0500f), proportionOfHeight (0.0406f));
    info2->setBounds (proportionOfWidth (0.6521f), proportionOfHeight (0.1344f), proportionOfWidth (0.2271f), proportionOfHeight (0.0406f));
    loadButton->setBounds (proportionOfWidth (0.9104f), proportionOfHeight (0.1344f), proportionOfWidth (0.0688f), proportionOfHeight (0.0406f));
    filterModeBox->setBounds (proportionOfWidth (0.1187f), proportionOfHeight (0.5156f), proportionOfWidth (0.0896f), roundFloatToInt ((proportionOfHeight (0.0406f)) * 1.0000f));
    sOctave1->setBounds (proportionOfWidth (-0.0021f), proportionOfHeight (0.1813f), proportionOfWidth (0.0562f), proportionOfHeight (0.0688f));
    comboBox->setBounds (proportionOfWidth (0.0458f), proportionOfHeight (0.1969f), proportionOfWidth (0.1125f), proportionOfHeight (0.0406f));
    sOctave2->setBounds (proportionOfWidth (0.2688f), proportionOfHeight (0.1813f), proportionOfWidth (0.0562f), proportionOfHeight (0.0688f));
    comboBox2->setBounds (proportionOfWidth (0.1646f), (proportionOfHeight (0.1969f)) + roundFloatToInt ((proportionOfHeight (0.0406f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.1125f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.0406f)) * 1.0000f));
    sChannel->setBounds (proportionOfWidth (0.4583f), proportionOfHeight (0.1063f), proportionOfWidth (0.0562f), proportionOfHeight (0.0781f));
    sOctave->setBounds (proportionOfWidth (0.1958f), (proportionOfHeight (0.2625f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    sUseProgCh->setBounds (proportionOfWidth (0.3708f), proportionOfHeight (0.1250f), proportionOfWidth (0.0958f), proportionOfHeight (0.0406f));
    sM1Mix->setBounds ((proportionOfWidth (0.0188f)) + roundFloatToInt ((proportionOfWidth (0.2167f)) * 1.0481f), ((proportionOfHeight (0.8125f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.5882f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.0000f)) * -0.4118f), proportionOfWidth (0.0562f), proportionOfHeight (0.1031f));
    randomButton->setBounds (proportionOfWidth (0.7604f), proportionOfHeight (0.1813f), proportionOfWidth (0.1396f), proportionOfHeight (0.0406f));
    limiterButton->setBounds (proportionOfWidth (0.7500f), proportionOfHeight (0.9281f), proportionOfWidth (0.0958f), proportionOfHeight (0.0406f));
    sExp->setBounds (proportionOfWidth (0.9333f), proportionOfHeight (0.2875f), proportionOfWidth (0.0396f), proportionOfHeight (0.0469f));
    sFExp->setBounds (proportionOfWidth (0.9333f), proportionOfHeight (0.5219f), proportionOfWidth (0.0396f), proportionOfHeight (0.0469f));
    midiled->setBounds (proportionOfWidth (0.6042f), proportionOfHeight (0.2844f), proportionOfWidth (0.0208f), proportionOfHeight (0.0281f));
    saveSnapshotButtonB->setBounds (proportionOfWidth (0.9729f), proportionOfHeight (0.0000f), proportionOfWidth (0.0313f), proportionOfHeight (0.0406f));
    recallSnapshotButtonB->setBounds (proportionOfWidth (0.9729f), proportionOfHeight (0.0469f), proportionOfWidth (0.0313f), proportionOfHeight (0.0406f));
    sMorph->setBounds (proportionOfWidth (0.0333f), proportionOfHeight (-0.0188f), proportionOfWidth (0.9250f), proportionOfHeight (0.0531f));
    saveSnapshotButtonA->setBounds (proportionOfWidth (-0.0063f), proportionOfHeight (0.0000f), proportionOfWidth (0.0313f), proportionOfHeight (0.0406f));
    recallSnapshotButtonA->setBounds (proportionOfWidth (-0.0063f), proportionOfHeight (0.0469f), proportionOfWidth (0.0313f), proportionOfHeight (0.0406f));
    aboutbox->setBounds (proportionOfWidth (0.5010f) - ((proportionOfWidth (0.5271f)) / 2), proportionOfHeight (0.1344f), proportionOfWidth (0.5271f), proportionOfHeight (0.4906f));
    sPitchShift->setBounds (proportionOfWidth (0.3562f), proportionOfHeight (1.0187f), proportionOfWidth (0.0833f), proportionOfHeight (0.0406f));
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    internalPath2.clear();
    internalPath2.startNewSubPath ((float) (proportionOfWidth (0.3487f)), (float) (proportionOfHeight (0.2300f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.3479f)), (float) (proportionOfHeight (0.1359f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.0094f)), (float) (proportionOfHeight (0.1359f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.0094f)), (float) (proportionOfHeight (0.1016f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.9927f)), (float) (proportionOfHeight (0.1016f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.9927f)), (float) (proportionOfHeight (0.2300f)));
    internalPath2.closeSubPath();

    internalPath3.clear();
    internalPath3.startNewSubPath ((float) (proportionOfWidth (0.0103f)), (float) (proportionOfHeight (0.9839f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.0103f)), (float) (proportionOfHeight (0.7810f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.3457f)), (float) (proportionOfHeight (0.7810f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.3457f)), (float) (proportionOfHeight (0.6300f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.6543f)), (float) (proportionOfHeight (0.6300f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.6543f)), (float) (proportionOfHeight (0.7810f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.9918f)), (float) (proportionOfHeight (0.7810f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.9918f)), (float) (proportionOfHeight (0.9842f)));
    internalPath3.closeSubPath();

    internalPath5.clear();
    internalPath5.startNewSubPath ((float) (proportionOfWidth (0.9348f)), (float) (proportionOfHeight (0.0569f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.8377f)), (float) (proportionOfHeight (0.0569f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.8377f)), (float) (proportionOfHeight (0.0377f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.9632f)), (float) (proportionOfHeight (0.0377f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.9632f)), (float) (proportionOfHeight (0.0900f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.8659f)), (float) (proportionOfHeight (0.0900f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.8659f)), (float) (proportionOfHeight (0.1040f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.9632f)), (float) (proportionOfHeight (0.1040f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.9632f)), (float) (proportionOfHeight (0.1230f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.8377f)), (float) (proportionOfHeight (0.1230f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.8377f)), (float) (proportionOfHeight (0.0709f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.9348f)), (float) (proportionOfHeight (0.0709f)));
    internalPath5.closeSubPath();

    internalPath6.clear();
    internalPath6.startNewSubPath ((float) (proportionOfWidth (0.9276f)), (float) (proportionOfHeight (0.0442f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.8288f)), (float) (proportionOfHeight (0.0442f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.8288f)), (float) (proportionOfHeight (0.0251f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.9564f)), (float) (proportionOfHeight (0.0251f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.9564f)), (float) (proportionOfHeight (0.0773f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.8575f)), (float) (proportionOfHeight (0.0773f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.8575f)), (float) (proportionOfHeight (0.0914f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.9564f)), (float) (proportionOfHeight (0.0914f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.9564f)), (float) (proportionOfHeight (0.1104f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.8288f)), (float) (proportionOfHeight (0.1104f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.8288f)), (float) (proportionOfHeight (0.0583f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.9276f)), (float) (proportionOfHeight (0.0583f)));
    internalPath6.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    logDebugString("resized()");
//    int w = getWidth();
//    int h = getHeight();

    info->setFont (Font (0.85f*(float)info->getHeight(), Font::plain));
    info2->setFont (Font (0.85f*(float)info2->getHeight(), Font::plain));
    info3->setFont (Font (0.85f*(float)info3->getHeight(), Font::plain));

    // if we've been resized, tell the filter so that it can store the new size
    // in its settings
    if (!init) {
       getFilter()->lastUIWidth = getWidth();
       getFilter()->lastUIHeight = getHeight();
    }
    init=false;
    //[/UserResized]
}

void MrAlias2Editor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
#if 0
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == patchBox)
    {
        //[UserComboBoxCode_patchBox] -- add your combo box handling code here..
#endif
    if (comboBoxThatHasChanged == (ComboBox*)patchBox)
    {
        getFilter()->wait=true;
        getFilter()->setCurrentProgram(patchBox->getSelectedId()-1);
        //[/UserComboBoxCode_patchBox]
    }
    else if (comboBoxThatHasChanged == filterModeBox)
    {
        //[UserComboBoxCode_filterModeBox] -- add your combo box handling code here..
        if (filterModeBox->getText()==String("Off")) getFilter()->setParameterNotifyingHost(kFilterPower,0.0f);
        else {
            getFilter()->setParameterNotifyingHost(kFilterPower,1.0f);
            if (filterModeBox->getText()==String("Low24")) getFilter()->setParameterNotifyingHost(kFMode,(float)lpf24/(float)(numFilterModes-1));
            else if (filterModeBox->getText()==String("Low")) getFilter()->setParameterNotifyingHost(kFMode,(float)svlow/(float)(numFilterModes-1));
            else if (filterModeBox->getText()==String("Band")) getFilter()->setParameterNotifyingHost(kFMode,(float)svband/(float)(numFilterModes-1));
            else if (filterModeBox->getText()==String("Notch")) getFilter()->setParameterNotifyingHost(kFMode,(float)svnotch/(float)(numFilterModes-1));
            else if (filterModeBox->getText()==String("High")) getFilter()->setParameterNotifyingHost(kFMode,(float)svhigh/(float)(numFilterModes-1));
            else if (filterModeBox->getText()==String("Formant")) getFilter()->setParameterNotifyingHost(kFMode,(float)formant/(float)(numFilterModes-1));
        }
        //[/UserComboBoxCode_filterModeBox]
    }
    else if (comboBoxThatHasChanged == comboBox)
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        getFilter()->setParameterNotifyingHost(kWaveform1,(float)comboBox->getSelectedItemIndex()/(float)(numWaveforms-1));
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2)
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        getFilter()->setParameterNotifyingHost(kWaveform2,(float)comboBox2->getSelectedItemIndex()/(float)(numWaveforms-1));
        //[/UserComboBoxCode_comboBox2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void MrAlias2Editor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sAlias)
    {
        //[UserSliderCode_sAlias] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kAlias,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sAlias]
    }
    else if (sliderThatWasMoved == sCutoff)
    {
        //[UserSliderCode_sCutoff] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kCut,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sCutoff]
    }
    else if (sliderThatWasMoved == sDivide)
    {
        //[UserSliderCode_sDivide] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kDivide,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDivide]
    }
    else if (sliderThatWasMoved == sAtt)
    {
        //[UserSliderCode_sAtt] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kAtt,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sAtt]
    }
    else if (sliderThatWasMoved == sRate)
    {
        //[UserSliderCode_sRate] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kRate,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sRate]
    }
    else if (sliderThatWasMoved == sSineMix)
    {
        //[UserSliderCode_sSineMix] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kSineMix,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sSineMix]
    }
    else if (sliderThatWasMoved == sSineRes)
    {
        //[UserSliderCode_sSineRes] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kSineRes,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sSineRes]
    }
    else if (sliderThatWasMoved == sPostDivide)
    {
        //[UserSliderCode_sPostDivide] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kPostDivide,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sPostDivide]
    }
    else if (sliderThatWasMoved == sClip)
    {
        //[UserSliderCode_sClip] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kClip,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sClip]
    }
    else if (sliderThatWasMoved == sAInertia)
    {
        //[UserSliderCode_sAInertia] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kAInertia,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sAInertia]
    }
    else if (sliderThatWasMoved == sDec)
    {
        //[UserSliderCode_sDec] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            getFilter()->setParameterNotifyingHost(kSus,0.f);
            getFilter()->setParameterNotifyingHost(kAtt,0.f);
            getFilter()->setParameterNotifyingHost(kRel,mapToVSTRange(sliderThatWasMoved));
            sExp->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kExp,1.f);
        }
        getFilter()->setParameterNotifyingHost(kDec,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDec]
    }
    else if (sliderThatWasMoved == sSus)
    {
        //[UserSliderCode_sSus] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kSus,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sSus]
    }
    else if (sliderThatWasMoved == sRel)
    {
        //[UserSliderCode_sRel] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            getFilter()->setParameterNotifyingHost(kSus,0.f);
            getFilter()->setParameterNotifyingHost(kAtt,0.f);
            getFilter()->setParameterNotifyingHost(kDec,mapToVSTRange(sliderThatWasMoved));
            sExp->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kExp,1.f);
        }
        getFilter()->setParameterNotifyingHost(kRel,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sRel]
    }
    else if (sliderThatWasMoved == sDivEnv)
    {
        //[UserSliderCode_sDivEnv] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kDivEnv,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDivEnv]
    }
    else if (sliderThatWasMoved == sRes)
    {
        //[UserSliderCode_sRes] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kRes,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sRes]
    }
    else if (sliderThatWasMoved == sBRMix)
    {
        //[UserSliderCode_sBRMix] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kBRMix,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sBRMix]
    }
    else if (sliderThatWasMoved == sVolume)
    {
        //[UserSliderCode_sVolume] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kVolume,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sVolume]
    }
    else if (sliderThatWasMoved == sSineFreq)
    {
        //[UserSliderCode_sSineFreq] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kSineFreq,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sSineFreq]
    }
    else if (sliderThatWasMoved == sVelSens)
    {
        //[UserSliderCode_sVelSens] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kVelSens,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sVelSens]
    }
    else if (sliderThatWasMoved == sFiltEnv)
    {
        //[UserSliderCode_sFiltEnv] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kFiltEnv,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFiltEnv]
    }
    else if (sliderThatWasMoved == sFVSens)
    {
        //[UserSliderCode_sFVSens] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kFVSens,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFVSens]
    }
    else if (sliderThatWasMoved == sPBRange)
    {
        //[UserSliderCode_sPBRange] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kPBRange,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sPBRange]
    }
    else if (sliderThatWasMoved == sInputGain)
    {
        //[UserSliderCode_sInputGain] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kInputGain,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sInputGain]
    }
    else if (sliderThatWasMoved == sWet)
    {
        //[UserSliderCode_sWet] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kWet,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sWet]
    }
    else if (sliderThatWasMoved == sOscGain)
    {
        //[UserSliderCode_sOscGain] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kOscGain,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOscGain]
    }
    else if (sliderThatWasMoved == sThresh)
    {
        //[UserSliderCode_sThresh] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kThresh,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sThresh]
    }
    else if (sliderThatWasMoved == sFreq1)
    {
        //[UserSliderCode_sFreq1] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kFreq1,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFreq1]
    }
    else if (sliderThatWasMoved == sRingMod)
    {
        //[UserSliderCode_sRingMod] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kRingMod,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sRingMod]
    }
    else if (sliderThatWasMoved == sFAtt)
    {
        //[UserSliderCode_sFAtt] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kFAtt,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFAtt]
    }
    else if (sliderThatWasMoved == sFDec)
    {
        //[UserSliderCode_sFDec] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            getFilter()->setParameterNotifyingHost(kFSus,0.f);
            getFilter()->setParameterNotifyingHost(kFAtt,0.f);
            getFilter()->setParameterNotifyingHost(kFRel,mapToVSTRange(sliderThatWasMoved));
            sFExp->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kFExp,1.f);
        }
        getFilter()->setParameterNotifyingHost(kFDec,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFDec]
    }
    else if (sliderThatWasMoved == sFSus)
    {
        //[UserSliderCode_sFSus] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kFSus,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFSus]
    }
    else if (sliderThatWasMoved == sFRel)
    {
        //[UserSliderCode_sFRel] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            getFilter()->setParameterNotifyingHost(kFSus,0.f);
            getFilter()->setParameterNotifyingHost(kFAtt,0.f);
            getFilter()->setParameterNotifyingHost(kFDec,mapToVSTRange(sliderThatWasMoved));
            sFExp->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kFExp,1.f);
        }
        getFilter()->setParameterNotifyingHost(kFRel,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFRel]
    }
    else if (sliderThatWasMoved == sStereo)
    {
        //[UserSliderCode_sStereo] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kStereo,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sStereo]
    }
    else if (sliderThatWasMoved == sOscMix)
    {
        //[UserSliderCode_sOscMix] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kOscMix,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOscMix]
    }
    else if (sliderThatWasMoved == sStereo2)
    {
        //[UserSliderCode_sStereo2] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kStereo2,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sStereo2]
    }
    else if (sliderThatWasMoved == sM1)
    {
        //[UserSliderCode_sM1] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kM1,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sM1]
    }
    else if (sliderThatWasMoved == sPhMod)
    {
        //[UserSliderCode_sPhMod] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kPhMod,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sPhMod]
    }
    else if (sliderThatWasMoved == sDivMix)
    {
        //[UserSliderCode_sDivMix] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kDivMix,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDivMix]
    }
    else if (sliderThatWasMoved == sFKeyFollow)
    {
        //[UserSliderCode_sFKeyFollow] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kFKeyFollow,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sFKeyFollow]
    }
    else if (sliderThatWasMoved == sOPLP)
    {
        //[UserSliderCode_sOPLP] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kOPLP,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOPLP]
    }
    else if (sliderThatWasMoved == sPostDivMix)
    {
        //[UserSliderCode_sPostDivMix] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kPostDivMix,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sPostDivMix]
    }
    else if (sliderThatWasMoved == sOctave1)
    {
        //[UserSliderCode_sOctave1] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            float diff = mapToVSTRange(sliderThatWasMoved)-getFilter()->getParameter(kOctave1);
            getFilter()->setParameterNotifyingHost(kOctave2,jlimit(0.f,1.f,diff+getFilter()->getParameter(kOctave2)));
        }
        getFilter()->setParameterNotifyingHost(kOctave1,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOctave1]
    }
    else if (sliderThatWasMoved == sOctave2)
    {
        //[UserSliderCode_sOctave2] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            float diff = mapToVSTRange(sliderThatWasMoved)-getFilter()->getParameter(kOctave2);
            getFilter()->setParameterNotifyingHost(kOctave1,jlimit(0.f,1.f,diff+getFilter()->getParameter(kOctave1)));
        }
        getFilter()->setParameterNotifyingHost(kOctave2,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOctave2]
    }
    else if (sliderThatWasMoved == sChannel)
    {
        //[UserSliderCode_sChannel] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kChannel,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sChannel]
    }
    else if (sliderThatWasMoved == sOctave)
    {
        //[UserSliderCode_sOctave] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kOctave,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOctave]
    }
    else if (sliderThatWasMoved == sM1Mix)
    {
        //[UserSliderCode_sM1Mix] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kM1Mix,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sM1Mix]
    }
    else if (sliderThatWasMoved == sMorph)
    {
        //[UserSliderCode_sMorph] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kMorph,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sMorph]
    }

    //[UsersliderValueChanged_Post]
    else {
        //must be a cc mapping slider
        getFilter()->setCCMapping(sliderThatWasMoved->getName().getIntValue(),roundDoubleToInt(sliderThatWasMoved->getValue()));
    }
    //[/UsersliderValueChanged_Post]
}

void MrAlias2Editor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == sMode)
    {
        //[UserButtonCode_sMode] -- add your button handler code here..
        if (ModifierKeys::getCurrentModifiers().isCommandDown()
            || ModifierKeys::getCurrentModifiers().isShiftDown()) {
            sMode->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kMode,1.f);
            //getFilter()->setParameterNotifyingHost(kMicrocomputer,1.f);
            sMode->setButtonText("micro");
        }
        else {
            sMode->setButtonText("Mono");
            //getFilter()->setParameterNotifyingHost(kMicrocomputer,0.f);
            sMode->setToggleState(!sMode->getToggleState(),false);
            if (sMode->getToggleState()) getFilter()->setParameterNotifyingHost(kMode,0.7f);
            else getFilter()->setParameterNotifyingHost(kMode,0.f);
        }
        //[/UserButtonCode_sMode]
    }
    else if (buttonThatWasClicked == nextButton)
    {
        //[UserButtonCode_nextButton] -- add your button handler code here..
        getFilter()->next();
        //[/UserButtonCode_nextButton]
    }
    else if (buttonThatWasClicked == prevButton)
    {
        //[UserButtonCode_prevButton] -- add your button handler code here..
        getFilter()->prev();
        //[/UserButtonCode_prevButton]
    }
    else if (buttonThatWasClicked == sReset)
    {
        //[UserButtonCode_sReset] -- add your button handler code here..
        getFilter()->progReset();
        //[/UserButtonCode_sReset]
    }
    else if (buttonThatWasClicked == sSavePatch)
    {
        //[UserButtonCode_sSavePatch] -- add your button handler code here..
        FileChooser myChooser ("Save current patch...",
            File(getFilter()->currentPath + File::separatorString + info2->getText() + ".MrAliasPatch"),
                               "*.MrAliasPatch;*.MrAliasCCMap");

        if (myChooser.browseForFileToSave(true))
        {
            bool saveccmap=false;
            File mooseFile (myChooser.getResult());
            if (mooseFile.hasFileExtension("MrAliasCCMap")) saveccmap=true;
            else if (!mooseFile.hasFileExtension("MrAliasPatch")) mooseFile = mooseFile.withFileExtension("MrAliasPatch");

            getFilter()->savePatch (mooseFile,saveccmap);
        }
        //[/UserButtonCode_sSavePatch]
    }
    else if (buttonThatWasClicked == sSavePatch2)
    {
        //[UserButtonCode_sSavePatch2] -- add your button handler code here..
        FileChooser myChooser ("Save current bank...",
            File(getFilter()->currentPath),
                               "*.MrAliasBank");

        if (myChooser.browseForFileToSave(true))
        {
            File mooseFile (myChooser.getResult());
            if (!mooseFile.hasFileExtension("MrAliasBank")) mooseFile = mooseFile.withFileExtension("MrAliasBank");

            getFilter()->saveBank (mooseFile);
        }
        //[/UserButtonCode_sSavePatch2]
    }
    else if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        FileChooser myChooser ("Load bank/patch...",
                               File(getFilter()->currentPath),
                               "*.MrAliasBank;*.MrAliasPatch;*.fxb;*.fxp;*.MrAliasCCMap");

        if (myChooser.browseForFileToOpen())
        {
            File file (myChooser.getResult());
            if (file.hasFileExtension("MrAliasBank")) {
                getFilter()->loadBank(file);
            }
            else if (file.hasFileExtension("MrAliasPatch") || file.hasFileExtension(".MrAliasCCMap")) {
                getFilter()->loadPatch(file);
            }
            else if (file.hasFileExtension("fxb")) {
                MemoryBlock bank = MemoryBlock(0,true);
                file.loadFileAsData(bank);
                bank.removeSection(0,0xA0);
                getFilter()->setStateInformation(bank.getData(), bank.getSize());
            }
            else if (file.hasFileExtension("fxp")) {
                MemoryBlock bank = MemoryBlock(0,true);
                file.loadFileAsData(bank);
                bank.removeSection(0,0x3C);
                getFilter()->setCurrentProgramStateInformation(bank.getData(), bank.getSize());
            }
        }
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == sUseProgCh)
    {
        //[UserButtonCode_sUseProgCh] -- add your button handler code here..
        sUseProgCh->setToggleState(!sUseProgCh->getToggleState(),false);
        if (sUseProgCh->getToggleState()) getFilter()->setParameterNotifyingHost(kUseProgCh,1.f);
        else getFilter()->setParameterNotifyingHost(kUseProgCh,0.f);
        //[/UserButtonCode_sUseProgCh]
    }
    else if (buttonThatWasClicked == randomButton)
    {
        //[UserButtonCode_randomButton] -- add your button handler code here..
		if (!ModifierKeys::getCurrentModifiers().isPopupMenu())
		{
			const String alphabet = "abbccddeeffgghhijjkkllmmnnoppqqrrssttuvwxyz ";
			const String vowels = "aeiou";
			float strength = 0.005f;
			String newName;
			if (ModifierKeys::getCurrentModifiers().isCommandDown()) {
				getFilter()->randomize(strength);
				newName = getFilter()->getProgramName(getFilter()->getCurrentProgram());
				int i=JUCE_NAMESPACE::Random::getSystemRandom().nextInt(newName.length());
				char o=newName[i];
				char n=o;
				while (o==n) n=alphabet[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(alphabet.length())];
				//newName[i] = n; //FIXME
			}
			else {
				Point<int> xy = randomButton->getMouseXYRelative();
				int x = xy.getX();
				int y = xy.getY();
				strength=(float)x/(float)randomButton->getWidth();
				getFilter()->randomize(strength);
				newName = String::empty;
				if (JUCE_NAMESPACE::Random::getSystemRandom().nextBool()) newName << vowels.toUpperCase()[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(5)];
				else newName << alphabet.toUpperCase()[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(alphabet.length()-1)];
				for (int i=0;i<4;i++) {
					newName << vowels[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(5)];
					newName << alphabet[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(alphabet.length())];
					if (JUCE_NAMESPACE::Random::getSystemRandom().nextBool()) newName << alphabet[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(alphabet.length())];
				}
				if (JUCE_NAMESPACE::Random::getSystemRandom().nextBool()) newName << vowels[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(5)];
			}
			newName.replace(T("  "),T(" ")).trim();
			getFilter()->changeProgramName(getFilter()->getCurrentProgram(),newName);
		}
        //[/UserButtonCode_randomButton]
    }
    else if (buttonThatWasClicked == limiterButton)
    {
        //[UserButtonCode_limiterButton] -- add your button handler code here..
        limiterButton->setToggleState(!limiterButton->getToggleState(),false);
        if (limiterButton->getToggleState()) getFilter()->setParameterNotifyingHost(kLimiter,1.f);
        else getFilter()->setParameterNotifyingHost(kLimiter,0.f);
        //[/UserButtonCode_limiterButton]
    }
    else if (buttonThatWasClicked == sExp)
    {
        //[UserButtonCode_sExp] -- add your button handler code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()
            || ModifierKeys::getCurrentModifiers().isCommandDown()) {
            sExp->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kExp,1.f);
            sExp->setButtonText("P!");
        }
        else {
            sExp->setButtonText("P");
            sExp->setToggleState(!sExp->getToggleState(),false);
            if (sExp->getToggleState()) getFilter()->setParameterNotifyingHost(kExp,0.75f);
            else getFilter()->setParameterNotifyingHost(kExp,0.f);
        }
        //[/UserButtonCode_sExp]
    }
    else if (buttonThatWasClicked == sFExp)
    {
        //[UserButtonCode_sFExp] -- add your button handler code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()
            || ModifierKeys::getCurrentModifiers().isCommandDown()) {
            sFExp->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kFExp,1.f);
            sFExp->setButtonText("P!");
        }
        else {
            sFExp->setButtonText("P");
            sFExp->setToggleState(!sFExp->getToggleState(),false);
            if (sFExp->getToggleState()) getFilter()->setParameterNotifyingHost(kFExp,0.75f);
            else getFilter()->setParameterNotifyingHost(kFExp,0.f);
        }
        //[/UserButtonCode_sFExp]
    }
    else if (buttonThatWasClicked == saveSnapshotButtonB)
    {
        //[UserButtonCode_saveSnapshotButtonB] -- add your button handler code here..
        bool state = saveSnapshotButtonB->getToggleState();
        if (ModifierKeys::getCurrentModifiers().isShiftDown()
            || ModifierKeys::getCurrentModifiers().isCommandDown()) {
                getFilter()->setSnapshotFollowsPreset(!state,1);
                saveSnapshotButtonB->setToggleState(!state,false);
        }
        else {
            //getFilter()->setSnapshotFollowsPreset(false,1);
            //saveSnapshotButtonB->setToggleState(false,false);
            getFilter()->saveSnapshot(true);
            sMorph->setValue(100,false);
        }
        //[/UserButtonCode_saveSnapshotButtonB]
    }
    else if (buttonThatWasClicked == recallSnapshotButtonB)
    {
        //[UserButtonCode_recallSnapshotButtonB] -- add your button handler code here..
        getFilter()->recallSnapshot(true);
        sMorph->setValue(100,false);
        //[/UserButtonCode_recallSnapshotButtonB]
    }
    else if (buttonThatWasClicked == saveSnapshotButtonA)
    {
        //[UserButtonCode_saveSnapshotButtonA] -- add your button handler code here..
        bool state = saveSnapshotButtonA->getToggleState();
        if (ModifierKeys::getCurrentModifiers().isShiftDown()
            || ModifierKeys::getCurrentModifiers().isCommandDown()) {
                getFilter()->setSnapshotFollowsPreset(!state,0);
                saveSnapshotButtonA->setToggleState(!state,false);
        }
        else {
            //getFilter()->setSnapshotFollowsPreset(false,0);
            //saveSnapshotButtonA->setToggleState(false,false);
            getFilter()->saveSnapshot();
            sMorph->setValue(-100,false);
        }
        //[/UserButtonCode_saveSnapshotButtonA]
    }
    else if (buttonThatWasClicked == recallSnapshotButtonA)
    {
        //[UserButtonCode_recallSnapshotButtonA] -- add your button handler code here..
        getFilter()->recallSnapshot();
        sMorph->setValue(-100,false);
        //[/UserButtonCode_recallSnapshotButtonA]
    }
    else if (buttonThatWasClicked == sPitchShift)
    {
        //[UserButtonCode_sPitchShift] -- add your button handler code here..
        sPitchShift->setToggleState(!sPitchShift->getToggleState(),false);
        if (sPitchShift->getToggleState()) getFilter()->setParameterNotifyingHost(kPitchShift,1.f);
        else getFilter()->setParameterNotifyingHost(kPitchShift,0.f);
        //[/UserButtonCode_sPitchShift]
    }

    //[UserbuttonClicked_Post]
    else if (buttonThatWasClicked == pizButton)
    {
        if (ModifierKeys::getCurrentModifiers().isCommandDown()) {
            if (getLookAndFeel().findColour(Slider::textBoxTextColourId).isTransparent()) {
                getLookAndFeel().setColour(Slider::textBoxTextColourId,Colours::white);
            }
            else {
                getLookAndFeel().setColour(Slider::textBoxTextColourId,Colours::transparentWhite);
            }
            repaint();
        }
        else if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
        }
        else aboutbox->setVisible(true);
    }

    else if (buttonThatWasClicked == aboutbox)
    {
        aboutbox->setVisible(false);
    }
    //[/UserbuttonClicked_Post]
}

void MrAlias2Editor::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == info2)
    {
        //[UserLabelCode_info2] -- add your label text handling code here..
        getFilter()->changeProgramName(getFilter()->getCurrentProgram(),info2->getText());
        getFilter()->updateHostDisplay();
        //[/UserLabelCode_info2]
    }

    //[UserlabelTextChanged_Post]
    else if (labelThatHasChanged == info)
    {
        //[UserLabelCode_info] -- add your label text handling code here..
        //log?
        logDebugString("info: " + info->getText());
        //[/UserLabelCode_info]
    }
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================
void MrAlias2Editor::mouseDown (const MouseEvent& e)
{
    if (e.eventComponent!=this) {
        int componentType;
        int index;
        getComponentIndexAndType(e.eventComponent,index,componentType);

        if (e.mods.isMiddleButtonDown()) {
            //middle-click midi learn
            getFilter()->setCCMapping(index,midiLearn);
            oldccmap[index]=midiLearn;
            if (componentType==sliderType) e.eventComponent->setColour(Slider::backgroundColourId, Colour (0x66ffff00));
        }
    }
}

void MrAlias2Editor::buttonStateChanged(Button* buttonThatWasClicked) {
    int index;
	int componentType;
    getComponentIndexAndType(buttonThatWasClicked,index,componentType);

	if (componentType==buttonType) {
		if (buttonThatWasClicked->isDown()) {
			if (ModifierKeys::getCurrentModifiers().isMiddleButtonDown()) {
				//middle-click midi learn
				getFilter()->setCCMapping(index,midiLearn);
				oldccmap[index]=midiLearn;
			}
			else if (ModifierKeys::getCurrentModifiers().isPopupMenu()) {
				showControlMenu(buttonThatWasClicked);
			}
		}
	}
}

void MrAlias2Editor::mouseUp (const MouseEvent& e)
{
    if (e.mods.isPopupMenu()) {
        if (e.eventComponent==this) {
            //clicked on background, show global options only
            PopupMenu m;
		    m.addSectionHeader("CC Mapping");
            m.addItem (3, String(T("Use CC Mapping")), true, getFilter()->isCCMappingEnabled());
            m.addItem (4, String(T("Clear All CC Mapping")));
			m.addItem (43, String(T("Apply All to Bank Now")));
			m.addItem (44, String(T("Apply All to Bank by Default")), true, getFilter()->CCMappingToBankByDefault);
            m.addItem (88, String(T("Save CC Map to File")));
            int result = m.show();
            if (result != 0)
            {
                if (result==3) {
                    getFilter()->enableCCMapping(!getFilter()->isCCMappingEnabled());
                }
                else if (result==4) {
                    getFilter()->enableCCMapping(false, true);
                }
				else if (result==43) {
					getFilter()->applyAllCCsToBank();
				}
				else if (result==44) {
					getFilter()->CCMappingToBankByDefault = !getFilter()->CCMappingToBankByDefault;
				}
                else if (result==88) {
                    FileChooser chooser ("Save current CC Map...",
                        File(getFilter()->currentPath + File::separatorString/* + info2->getText() + ".MrAliasCCMap"*/),
                                           "*.MrAliasCCMap");
                    if (chooser.browseForFileToSave(true))
                    {
                        File ccFile (chooser.getResult());
                        if (!ccFile.hasFileExtension("MrAliasCCMap")) ccFile = ccFile.withFileExtension("MrAliasCCMap");
                        getFilter()->savePatch (ccFile,true);
                    }
                }
            }
        }
        else {
			showControlMenu(e.eventComponent);
        }
    }
}

void MrAlias2Editor::sliderDragStarted (Slider* slider)
{
     getFilter()->beginParameterChangeGesture(getSliderIndex(slider));
     // mousedown
     if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
        //set decay & release the same
        if (slider==sDec) {
           getFilter()->setParameterNotifyingHost(kRel,mapToVSTRange(slider));
           getFilter()->setParameterNotifyingHost(kSus,0.f);
        }
        else if (slider==sRel) {
           getFilter()->setParameterNotifyingHost(kDec,mapToVSTRange(slider));
           getFilter()->setParameterNotifyingHost(kSus,0.f);
        }
        else if (slider==sFRel) {
           getFilter()->setParameterNotifyingHost(kFDec,mapToVSTRange(slider));
           getFilter()->setParameterNotifyingHost(kFSus,0.f);
        }
        else if (slider==sFDec) {
           getFilter()->setParameterNotifyingHost(kFRel,mapToVSTRange(slider));
           getFilter()->setParameterNotifyingHost(kFSus,0.f);
        }
     }
}

void MrAlias2Editor::sliderDragEnded (Slider* slider)
{
    getFilter()->endParameterChangeGesture(getSliderIndex(slider));
}

void MrAlias2Editor::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
	for (int i=0;i<filenames.size();i++)
	{
		File file = File(filenames[i]);
		if (file.hasFileExtension(".MrAliasBank")) {
			getFilter()->loadBank(file);
		}
		else if (file.hasFileExtension(".MrAliasPatch")) {
			getFilter()->loadPatch(file);
			if (i!=filenames.size()-1) getFilter()->next();
		}
		else if (file.hasFileExtension(".MrAliasCCMap")) {
			getFilter()->loadPatch(file);
		}
		else if (file.hasFileExtension("fxb")) {
			MemoryBlock bank = MemoryBlock(0,true);
			file.loadFileAsData(bank);
			bank.removeSection(0,0xA0);
			getFilter()->setStateInformation(bank.getData(), bank.getSize());
		}
		else if (file.hasFileExtension("fxp")) {
			MemoryBlock bank = MemoryBlock(0,true);
			file.loadFileAsData(bank);
			bank.removeSection(0,0x3C);
			getFilter()->setCurrentProgramStateInformation(bank.getData(), bank.getSize());
			if (i!=filenames.size()-1) getFilter()->next();
		}
	}
}

bool MrAlias2Editor::isInterestedInFileDrag (const StringArray& files){
    File file = File(files[0]);
    if (   file.hasFileExtension("MrAliasBank")
        || file.hasFileExtension("MrAliasPatch")
        || file.hasFileExtension("MrAliasCCMap")
        || file.hasFileExtension("fxb")
        || file.hasFileExtension("fxp") )
    {
        return true;
    }
    return false;
}

void MrAlias2Editor::changeListenerCallback (ChangeBroadcaster* source)
{
    //logDebugString("changeListenerCallback " + String((int)&source));
	MrAlias2* const f = getFilter();
    if (source==f) {
        //logDebugString("source==getFilter()");
        updateParametersFromFilter();
    }
    else if (source==(f->leds)) {
        updateParametersFromFilter();
        //logDebugString("source==leds");
		f->getCallbackLock().enter();
        clipled->setToggleState(f->clipped,false);
        midiled->setToggleState(f->ledon,false);
        audioled->setToggleState(f->aledon,false);
        if (info->getText().compare(f->infoString)) info->setText(f->infoString,true);
		f->getCallbackLock().exit();
    }
    else {
        info->setText("huh??????????",true);
    }
}

//==============================================================================
void MrAlias2Editor::updateParametersFromFilter()
{
    MrAlias2* const filter = getFilter();
    float params[numParams];
    int ccmap[numParams];

    filter->getCallbackLock().enter();
    filter->wait=true;
    // take a local copy of the info we need while we've got the lock..
    for (int i=0;i<numParams;i++) {
        params[i] = filter->getParameter(i);
        ccmap[i] = filter->getCCMapping(i);
    }
    //const int w=filter->lastUIWidth;
    const int h=filter->lastUIHeight;
    const String text=filter->infoString;
    const int patchnum=filter->getCurrentProgram();
    const String patchname=filter->getProgramName(patchnum);
    const int fmode = filter->filtermode;
    const bool clipped = filter->clipped;
    const bool ledon = filter->ledon;
    const bool aledon = filter->aledon;

    // ..release the lock ASAP
    filter->getCallbackLock().exit();

    // ..and after releasing the lock, we're free to do the time-consuming UI stuff..
    setVSTSlider(sAlias,params[kAlias]);
    setVSTSlider(sVolume,params[kVolume]);
    setVSTSlider(sFreq1,params[kFreq1]);
    setVSTSlider(sRingMod,params[kRingMod]);
    setVSTSlider(sPBRange,params[kPBRange]);
    setVSTSlider(sCutoff,params[kCut]);
    setVSTSlider(sRes,params[kRes]);
    setVSTSlider(sDivide,params[kDivide]);
    setVSTSlider(sThresh,params[kThresh]);
    setVSTSlider(sDivEnv,params[kDivEnv]);
    setVSTSlider(sAtt,params[kAtt]);
    setVSTSlider(sDec,params[kDec]);
    setVSTSlider(sSus,params[kSus]);
    setVSTSlider(sRel,params[kRel]);
    setVSTSlider(sFAtt,params[kFAtt]);
    setVSTSlider(sFDec,params[kFDec]);
    setVSTSlider(sFSus,params[kFSus]);
    setVSTSlider(sFRel,params[kFRel]);
    setVSTSlider(sPostDivide,params[kPostDivide]);
    setVSTSlider(sRate,params[kRate]);
    setVSTSlider(sBRMix,params[kBRMix]);
    setVSTSlider(sSineFreq,params[kSineFreq]);
    setVSTSlider(sSineRes,params[kSineRes]);
    setVSTSlider(sSineMix,params[kSineMix]);
    setVSTSlider(sAInertia,params[kAInertia]);
    setVSTSlider(sClip,params[kClip]);
    setVSTSlider(sVelSens,params[kVelSens]);
    setVSTSlider(sInputGain,params[kInputGain]);
    setVSTSlider(sOscGain,params[kOscGain]);
    setVSTSlider(sFiltEnv,params[kFiltEnv]);
    setVSTSlider(sWet,params[kWet]);
    setVSTSlider(sOctave,params[kOctave]);
    setVSTSlider(sOctave1,params[kOctave1]);
    setVSTSlider(sOctave2,params[kOctave2]);
    setVSTSlider(sStereo,params[kStereo]);
    setVSTSlider(sStereo2,params[kStereo2]);
    setVSTSlider(sOscMix,params[kOscMix]);
    setVSTSlider(sFVSens,params[kFVSens]);
    setVSTSlider(sM1,params[kM1]);
    setVSTSlider(sPhMod,params[kPhMod]);
    setVSTSlider(sDivMix,params[kDivMix]);
    setVSTSlider(sFKeyFollow,params[kFKeyFollow]);
    setVSTSlider(sOPLP,params[kOPLP]);
    setVSTSlider(sPostDivMix,params[kPostDivMix]);
    setVSTSlider(sChannel,params[kChannel]);
    setVSTSlider(sM1Mix,params[kM1Mix]);
    setVSTSlider(sMorph,params[kMorph]);

    sMode->setToggleState(params[kMode]>=0.5f,false);
    if (params[kMode]==1.f) sMode->setButtonText("micro");
    else sMode->setButtonText("Mono");

    sUseProgCh->setToggleState(params[kUseProgCh]>=0.5f,false);
    limiterButton->setToggleState(params[kLimiter]>=0.5f,false);
    sPitchShift->setToggleState(params[kPitchShift]>=0.5f,false);
    saveSnapshotButtonA->setToggleState(getFilter()->getSnapshotFollowsPreset(0),false);
    saveSnapshotButtonB->setToggleState(getFilter()->getSnapshotFollowsPreset(1),false);

    sExp->setToggleState(params[kExp]>=0.5f,false);
    if (params[kExp]==1.f) sExp->setButtonText("P!");
    else sExp->setButtonText("P");
    sFExp->setToggleState(params[kFExp]>=0.5f,false);
    if (params[kFExp]==1.f) sFExp->setButtonText("P!");
    else sFExp->setButtonText("P");

    switch(roundFloatToInt(params[kWaveform1]*((float)numWaveforms-1.f))) {
        case rampup: comboBox->setText("RampUp",true); break;
        case rampdn: comboBox->setText("RampDown",true); break;
        case pulse: comboBox->setText("Square",true); break;
        case triangle: comboBox->setText("Triangle",true); break;
        case sine: comboBox->setText("Sine",true); break;
        case minko: comboBox->setText("Minkowski",true); break;
        case weier: comboBox->setText("Weierstrass",true); break;
        case comb: comboBox->setText("AutoAlias",true); break;
        case 8: comboBox->setText("Eight",true); break;
        case 9: comboBox->setText("OddEight",true); break;
        case computer: comboBox->setText("Computer",true); break;
        case 11: comboBox->setText("Funnel",true); break;
        case 12: comboBox->setText("Grate",true); break;
        case 13: comboBox->setText("Noise",true); break;
        case 14: comboBox->setText("Sine+",true); break;
        case 15: comboBox->setText("Narrow",true); break;
        case 16: comboBox->setText("Octaves",true); break;
        case 17: comboBox->setText("Ughhh",true); break;
        default: comboBox->setText(String(roundFloatToInt(params[kWaveform1]*((float)numWaveforms-1.f))),true); break;
    }
    switch(roundFloatToInt(params[kWaveform2]*((float)numWaveforms-1.f))) {
        case rampup: comboBox2->setText("RampUp",true); break;
        case rampdn: comboBox2->setText("RampDown",true); break;
        case pulse: comboBox2->setText("Square",true); break;
        case triangle: comboBox2->setText("Triangle",true); break;
        case sine: comboBox2->setText("Sine",true); break;
        case minko: comboBox2->setText("Minkowski",true); break;
        case weier: comboBox2->setText("Weierstrass",true); break;
        case comb: comboBox2->setText("AutoAlias",true); break;
        case 8: comboBox2->setText("Eight",true); break;
        case 9: comboBox2->setText("OddEight",true); break;
        case computer: comboBox2->setText("Computer",true); break;
        case 11: comboBox2->setText("Funnel",true); break;
        case 12: comboBox2->setText("Grate",true); break;
        case 13: comboBox2->setText("Noise",true); break;
        case 14: comboBox2->setText("Sine+",true); break;
        case 15: comboBox2->setText("Narrow",true); break;
        case 16: comboBox2->setText("Octaves",true); break;
        case 17: comboBox2->setText("Ughhh",true); break;
        default: comboBox2->setText(String(roundFloatToInt(params[kWaveform2]*((float)numWaveforms-1.f))),true); break;
    }

    sCutoff->setTooltip(T("Filter Cutoff"));
    sRes->setTooltip(T("Filter Resonance"));
    if (params[kFilterPower]<0.5f) filterModeBox->setText("Off",true);
    else if (fmode==lpf24) filterModeBox->setText("Low24",true);
    else if (fmode==svlow) filterModeBox->setText("Low",true);
    else if (fmode==svband) filterModeBox->setText("Band",true);
    else if (fmode==svnotch) filterModeBox->setText("Notch",true);
    else if (fmode==svhigh) filterModeBox->setText("High",true);
    else if (fmode==formant) {
        filterModeBox->setText("Formant",true);
        sCutoff->setTooltip(T("Vowel (U/O/A/E/I)"));
        sRes->setTooltip(T("Pre-filter gain"));
    }

    if (info->getText().compare(text)) info->setText(text,true);
    //info->setText(text,false);
    info2->setText(patchname,false);
    info3->setText(String(patchnum+1)+":",false);
    patchBox->setSelectedItemIndex(patchnum,true);
    patchBox->changeItemText(patchnum+1,patchname);
    if (filter->newbank) {
        patchBox->clear(true);
        for (int i=0;i<numPrograms;i++) {
            patchBox->addItem (filter->getProgramName(i), i+1);
        }
        filter->newbank=false;
    }

    clipled->setToggleState(clipped,false);
    midiled->setToggleState(ledon,false);
    audioled->setToggleState(aledon,false);

    for (int i=0;i<numParams;i++) {
        if (ccmap[i]!=oldccmap[i]) {
           oldccmap[i] = ccmap[i];
           getSliderByIndex(i)->setColour(Slider::backgroundColourId, Colours::transparentBlack);
           ccmapbox[i]->setValue(ccmap[i],false);
        }
    }

    if (h!=getHeight()) {
        setSize ((int)(h*aspectRatio), h);
    }
    filter->getCallbackLock().enter();
    filter->wait=false;
    filter->getCallbackLock().exit();
}

inline float MrAlias2Editor::mapToVSTRange(Slider* source) {
    //maps a slider of arbitrary range to [0..1]
//    double min = source->getMinimum();
//    double max = source->getMaximum();
//    double x = source->getValue();
//    return (float)((x-min)/(max-min));
    return (float)((source->getValue() - source->getMinimum())/(source->getMaximum() - source->getMinimum()));
}

inline void MrAlias2Editor::setVSTSlider(Slider* slider, float x) {
    if (x!=mapToVSTRange(slider)) {
//        double min = slider->getMinimum();
//        double max = slider->getMaximum();
//        double value = min + x*(max-min);
//        slider->setValue(value,false,false);
        slider->setValue(slider->getMinimum() + x*(slider->getMaximum() - slider->getMinimum()),false,false);
    }
}

inline int MrAlias2Editor::getSliderIndex(Slider* slider) {
    if (slider==sAlias)      return kAlias;
    if (slider==sVolume)     return kVolume;
    if (slider==sFreq1)      return kFreq1;
    if (slider==sRingMod)    return kRingMod;
    if (slider==sPBRange)    return kPBRange;
    if (slider==sCutoff)     return kCut;
    if (slider==sRes)        return kRes;
    if (slider==sDivide)     return kDivide;
    if (slider==sThresh)     return kThresh;
    if (slider==sDivEnv)     return kDivEnv;
    if (slider==sAtt)        return kAtt;
    if (slider==sDec)        return kDec;
    if (slider==sSus)        return kSus;
    if (slider==sRel)        return kRel;
    if (slider==sFAtt)       return kFAtt;
    if (slider==sFDec)       return kFDec;
    if (slider==sFSus)       return kFSus;
    if (slider==sFRel)       return kFRel;
    if (slider==sPostDivide) return kPostDivide;
    if (slider==sRate)       return kRate;
    if (slider==sBRMix)      return kBRMix;
    if (slider==sSineFreq)   return kSineFreq;
    if (slider==sSineRes)    return kSineRes;
    if (slider==sSineMix)    return kSineMix;
    if (slider==sAInertia)   return kAInertia;
    if (slider==sClip)       return kClip;
    if (slider==sVelSens)    return kVelSens;
    if (slider==sInputGain)  return kInputGain;
    if (slider==sOscGain)    return kOscGain;
    if (slider==sFiltEnv)    return kFiltEnv;
    if (slider==sWet)        return kWet;
    if (slider==sOctave)     return kOctave;
    if (slider==sOctave1)    return kOctave1;
    if (slider==sOctave2)    return kOctave2;
    if (slider==sStereo)     return kStereo;
    if (slider==sStereo2)    return kStereo2;
    if (slider==sOscMix)     return kOscMix;
    if (slider==sFVSens)     return kFVSens;
    if (slider==sM1)         return kM1;
    if (slider==sPhMod)      return kPhMod;
    if (slider==sDivMix)     return kDivMix;
    if (slider==sFKeyFollow) return kFKeyFollow;
    if (slider==sOPLP)       return kOPLP;
    if (slider==sPostDivMix) return kPostDivMix;
    if (slider==sChannel)    return kChannel;
    if (slider==sM1Mix)      return kM1Mix;
    if (slider==sMorph)      return kMorph;
    return -1;
}

Slider* MrAlias2Editor::getSliderByIndex(int index) {
    switch(index)
    {
    case kAlias:      return sAlias;
    case kVolume:     return sVolume;
    case kFreq1:      return sFreq1;
    case kRingMod:    return sRingMod;
    case kPBRange:    return sPBRange;
    case kCut:        return sCutoff;
    case kRes:        return sRes;
    case kDivide:     return sDivide;
    case kThresh:     return sThresh;
    case kDivEnv:     return sDivEnv;
    case kAtt:        return sAtt;
    case kDec:        return sDec;
    case kSus:        return sSus;
    case kRel:        return sRel;
    case kFAtt:       return sFAtt;
    case kFDec:       return sFDec;
    case kFSus:       return sFSus;
    case kFRel:       return sFRel;
    case kPostDivide: return sPostDivide;
    case kRate:       return sRate;
    case kBRMix:      return sBRMix;
    case kSineFreq:   return sSineFreq;
    case kSineRes:    return sSineRes;
    case kSineMix:    return sSineMix;
    case kAInertia:   return sAInertia;
    case kClip:       return sClip;
    case kVelSens:    return sVelSens;
    case kInputGain:  return sInputGain;
    case kOscGain:    return sOscGain;
    case kFiltEnv:    return sFiltEnv;
    case kWet:        return sWet;
    case kOctave:     return sOctave;
    case kOctave1:    return sOctave1;
    case kOctave2:    return sOctave2;
    case kStereo:     return sStereo;
    case kStereo2:    return sStereo2;
    case kOscMix:     return sOscMix;
    case kFVSens:     return sFVSens;
    case kM1:         return sM1;
    case kPhMod:      return sPhMod;
    case kDivMix:     return sDivMix;
    case kFKeyFollow: return sFKeyFollow;
    case kOPLP:       return sOPLP;
    case kPostDivMix: return sPostDivMix;
    case kChannel:    return sChannel;
    case kM1Mix:      return sM1Mix;
    case kMorph:      return sMorph;
    default:          return sMorph;
    }
}

inline void MrAlias2Editor::getComponentIndexAndType(Component* c, int &index, int &type) {
    //buttons
    if      (c==sExp) {type=buttonType; index=kExp;}
    else if (c==sFExp) {type=buttonType; index=kFExp;}
    else if (c==sMode) {type=buttonType; index=kMode;}
    else if (c==sPitchShift) {type=buttonType; index=kPitchShift;}
    else if (c==limiterButton) {type=buttonType; index=kLimiter;}
    else if (c==randomButton) {type=buttonType; index=kRandomize;}
    //combo boxes
    else if (c==comboBox) {type=comboBoxType; index=kWaveform1;}
    else if (c==comboBox2) {type=comboBoxType; index=kWaveform2;}
    else if (c==filterModeBox) {type=comboBoxType; index=kFMode;}
    //sliders
    else {
        type=sliderType;
        index = getSliderIndex((Slider*)c);
    }
}

void MrAlias2Editor::showControlMenu(Component* c) {
    int componentType;
    int index;
    getComponentIndexAndType(c,index,componentType);

    const float value = getFilter()->getParameter(index);
    PopupMenu m;
    m.addSectionHeader("- " + c->getName() + " -");
	m.addItem(-1,getFilter()->getParameterText(index),false);
    m.addSeparator();
    m.addSectionHeader("CC Mapping");
    m.addCustomItem(-1,ccmapbox[index],100,20,false);
    m.addItem (1, String(T("MIDI Learn")));
    m.addItem (2, String(T("Clear CC Mapping")));
    m.addItem (97, String(T("Set Min")));
    m.addItem (98, String(T("Set Max")));
    m.addItem (99, String(T("Reverse")),true,getFilter()->isCCRangeReversed(index));
    m.addItem (33, String(T("Apply to Bank")));
    m.addItem (34, String(T("Clear from Bank")));
    m.addSeparator();
    m.addSectionHeader("Snapshots");
    m.addItem (55, String(T("Apply Value to A & B")));
    m.addSeparator();
    m.addSectionHeader("Global");
    m.addItem (3, String(T("Use CC Mapping")), true, getFilter()->isCCMappingEnabled());
    m.addItem (4, String(T("Clear All CC Mapping")));
    m.addItem (43, String(T("Apply All to Bank Now")));
	m.addItem (44, String(T("Apply All to Bank by Default")), true, getFilter()->CCMappingToBankByDefault);
    m.addItem (88, String(T("Save CC Map to File")));
    int result = m.show();
    if (result > 0)
    {
        if (result==1) {
            getFilter()->setCCMapping(index,midiLearn);
            oldccmap[index]=midiLearn;
            if (componentType==sliderType) c->setColour(Slider::backgroundColourId, Colour (0x66ffff00));
			//else if (componentType==buttonType) e.eventComponent->setColour(TextButton::buttonColourId, Colour (0x66ffff00));
			//else if (componentType==comboBoxType) e.eventComponent->setColour(ComboBox::outlineColourId, Colour (0x66ffff00));
        }
        else if (result==2) {
            getFilter()->setCCMapping(index,-1);
        }
        else if (result==3) {
            getFilter()->enableCCMapping(!getFilter()->isCCMappingEnabled());
        }
        else if (result==4) {
            getFilter()->enableCCMapping(false, true);
        }
        else if (result==97) {
            getFilter()->setCCLo(index,value);
        }
        else if (result==98) {
            getFilter()->setCCHi(index,value);
        }
        else if (result==99) {
            getFilter()->flipCCRange(index);
        }
        else if (result==33) {
            getFilter()->applyCCToBank(index);
        }
        else if (result==34) {
            getFilter()->clearCCFromBank(index);
        }
        else if (result==43) {
            getFilter()->applyAllCCsToBank();
        }
        else if (result==44) {
			getFilter()->CCMappingToBankByDefault = !getFilter()->CCMappingToBankByDefault;
        }
        else if (result==55) {
            getFilter()->applyValueToSnapshots(index,value,true,true);
        }
        else if (result==88) {
            FileChooser chooser ("Save current CC Map...",
                File(getFilter()->currentPath + File::separatorString/* + info2->getText() + ".MrAliasCCMap"*/),
                                   "*.MrAliasCCMap");
            if (chooser.browseForFileToSave(true))
            {
                File ccFile (chooser.getResult());
                if (!ccFile.hasFileExtension("MrAliasCCMap")) ccFile = ccFile.withFileExtension("MrAliasCCMap");
                getFilter()->savePatch (ccFile,true);
            }
        }
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MrAlias2Editor" componentName=""
                 parentClasses="public AudioProcessorEditor, public ChangeListener, public FileDragAndDropTarget, public PizComboBoxListener"
                 constructorParams="MrAlias2* const ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter),&#10;aspectRatio(1.5)"
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0"
                 fixedSize="1" initialWidth="480" initialHeight="320">
  <BACKGROUND backgroundColour="ffffffff">
    <IMAGE pos="0 0 100% 100%" resource="alias_svg2" opacity="1" mode="0"/>
    <IMAGE pos="0 0 100% 100%" resource="mralias2_png" opacity="0.075" mode="1"/>
    <PATH pos="0 0 100 100" fill="solid: 68a74848" hasStroke="0" nonZeroWinding="1">s 34.865% 23% l 34.792% 13.594% l 0.938% 13.594% l 0.938% 10.156% l 99.271% 10.156% l 99.271% 23% x</PATH>
    <RECT pos="0.779% 17.115% 30.779% 29.231%" fill="solid: 68a58d2a" hasStroke="0"/>
    <RECT pos="68.304% 26.596% 30.903% 48.298%" fill="solid: 687aa52a"
          hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: 682a8da5" hasStroke="0" nonZeroWinding="1">s 1.029% 98.394% l 1.029% 78.102% l 34.568% 78.102% l 34.568% 63% l 65.432% 63% l 65.432% 78.102% l 99.177% 78.102% l 99.177% 98.416% x</PATH>
    <RECT pos="34.539% 37.963% 30.921% 21.528%" fill="solid: 68a56b2a"
          hasStroke="0"/>
    <RECT pos="35.325% 82.115% 29.221% 14.038%" fill="solid: 36000000"
          hasStroke="0"/>
    <RECT pos="1.688% 49.615% 28.961% 23.654%" fill="solid: 36000000" hasStroke="0"/>
    <RECT pos="37.083% 17.188% 13.75% 4.688%" fill="solid: 36000000" hasStroke="0"/>
    <IMAGE pos="2.5% 3.75% 75.833% 7.812%" resource="whitetitle_svg" opacity="1"
           mode="1"/>
    <PATH pos="0 0 100 100" fill="solid: 9bff9a9a" hasStroke="0" nonZeroWinding="1">s 93.484% 5.687% l 83.773% 5.687% l 83.773% 3.772% l 96.316% 3.772% l 96.316% 8.995% l 86.587% 8.995% l 86.587% 10.4% l 96.316% 10.4% l 96.316% 12.302% l 83.773% 12.302% l 83.773% 7.091% l 93.484% 7.091% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 62ffffff" hasStroke="1" stroke="1.60000002, mitered, butt"
          strokeColour="solid: ff000000" nonZeroWinding="1">s 92.757% 4.423% l 82.884% 4.423% l 82.884% 2.509% l 95.637% 2.509% l 95.637% 7.732% l 85.746% 7.732% l 85.746% 9.137% l 95.637% 9.137% l 95.637% 11.038% l 82.884% 11.038% l 82.884% 5.828% l 92.757% 5.828% x</PATH>
    <IMAGE pos="2.917% 4.375% 75.833% 7.812%" resource="title_svg2" opacity="0.906"
           mode="1"/>
    <RECT pos="0.779% 50.385% 30.779% 24.423%" fill="solid: 6877657e" hasStroke="0"/>
    <RECT pos="69.572% 51.157% 28.783% 22.454%" fill="solid: 36000000"
          hasStroke="0"/>
    <RECT pos="53.125% 13.125% 45.208% 9.062%" fill="solid: 36000000" hasStroke="0"/>
    <RECT pos="65.417% 13.75% 24.792% 4.062%" fill="solid: 36000000" hasStroke="0"/>
  </BACKGROUND>
  <COMBOBOX name="Program Select" id="42cfeb77ae238add" memberName="patchBox"
            virtualName="PizComboBox" explicitFocusOrder="0" pos="88.333% 13.75% 2.083% 3.75%"
            tooltip="Select Patch" editable="0" layout="33" items="dummy1&#10;dummy2"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="Alias" id="643c9f76ae9fecfc" memberName="sAlias" virtualName=""
          explicitFocusOrder="0" pos="1.667% 38.75% 23.333% 5.312%" tooltip="Alias"
          min="0" max="102" int="0.01" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Cutoff" id="95d9e283adc46234" memberName="sCutoff"
          virtualName="" explicitFocusOrder="0" pos="2.292% 53.125% 11.667% 18.438%"
          tooltip="Filter Cutoff" bkgcol="0" rotarysliderfill="ffae0000"
          rotaryslideroutline="66ffffff" textboxoutline="b2888888" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Divide" id="e15284b871cb9580" memberName="sDivide" virtualName=""
          explicitFocusOrder="0" pos="35.625% 39.375% 23.333% 5.312%" tooltip="Divide"
          rotaryslideroutline="66000000" min="0" max="100" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Amp Env Attack" id="98f08232c4ccc1db" memberName="sAtt"
          virtualName="" explicitFocusOrder="0" pos="69.375% 28.438% 5% 21.25%"
          tooltip="Amp Env Attack" min="0" max="100" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Downsample Rate" id="67291950d5f1ae5c" memberName="sRate"
          virtualName="" explicitFocusOrder="0" pos="1.875% 81.25% 21.667% 5.312%"
          tooltip="Downsample Rate" min="0" max="100" int="0.1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sine Mix" id="9c7fc02f68f62bb7" memberName="sSineMix" virtualName=""
          explicitFocusOrder="0" pos="56.458% 65.312% 8.542% 10.625%" tooltip="Sine Mix"
          rotarysliderfill="7f000000" rotaryslideroutline="66ffffff" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sine Resolution" id="2c5c4d3bc0769a2b" memberName="sSineRes"
          virtualName="" explicitFocusOrder="0" pos="35.625% 64.688% 21.458% 5.312%"
          tooltip="Sine Resolution" min="0" max="100" int="0.1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Post Divide" id="f6f5cffc22cfc5df" memberName="sPostDivide"
          virtualName="" explicitFocusOrder="0" pos="0% 123.529% 100% 5.312%"
          posRelativeX="e15284b871cb9580" posRelativeY="835be6a95912d3cf"
          posRelativeW="e15284b871cb9580" tooltip="Post Divide" min="0"
          max="100" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Clipper" id="20c26f0e7b36dd30" memberName="sClip" virtualName=""
          explicitFocusOrder="0" pos="68.542% 80.312% 17.083% 5.312%" tooltip="Clipper"
          min="0" max="100" int="0.1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Inertia" id="439a364155b8a9a1" memberName="sAInertia" virtualName=""
          explicitFocusOrder="0" pos="25.208% 37.188% 5.417% 8.75%" tooltip="Inertia"
          rotarysliderfill="e3000000" rotaryslideroutline="66ffffff" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Decay" id="45d621746fcf224f" memberName="sDec"
          virtualName="" explicitFocusOrder="0" pos="75.208% 0% 100% 100%"
          posRelativeY="98f08232c4ccc1db" posRelativeW="98f08232c4ccc1db"
          posRelativeH="98f08232c4ccc1db" tooltip="Amp Env Decay" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Sustain" id="7e37ae1d9e9c0614" memberName="sSus"
          virtualName="" explicitFocusOrder="0" pos="81.042% 0% 100% 100%"
          posRelativeY="45d621746fcf224f" posRelativeW="45d621746fcf224f"
          posRelativeH="45d621746fcf224f" tooltip="Amp Env Sustain" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Release" id="93deecf83421a9aa" memberName="sRel"
          virtualName="" explicitFocusOrder="0" pos="87.083% 0% 100% 100%"
          posRelativeY="7e37ae1d9e9c0614" posRelativeW="7e37ae1d9e9c0614"
          posRelativeH="7e37ae1d9e9c0614" tooltip="Amp Env Release" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="AmpEnv -&gt; Divider" id="f57d520d0d29459" memberName="sDivEnv"
          virtualName="" explicitFocusOrder="0" pos="92.5% 33.125% 5.625% 9.375%"
          tooltip="AmpEnv -&gt; Divider" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Resonance" id="a1fe1c4479e68a76" memberName="sRes"
          virtualName="" explicitFocusOrder="0" pos="18.542% 0% 11.667% 18.438%"
          posRelativeY="95d9e283adc46234" tooltip="Filter Resonance" rotarysliderfill="7f001786"
          rotaryslideroutline="66ffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Downsampler Mix" id="b44fe15f624d0449" memberName="sBRMix"
          virtualName="" explicitFocusOrder="0" pos="104.808% -41.176% 5.625% 10.312%"
          posRelativeX="67291950d5f1ae5c" posRelativeY="67291950d5f1ae5c"
          tooltip="Downsampler Mix" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Main Volume" id="7cfebe5576414d20" memberName="sVolume"
          virtualName="" explicitFocusOrder="0" pos="86.25% 80.312% 11.667% 15.625%"
          tooltip="Main Volume" rotarysliderfill="7fff7900" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sine Frequency" id="a0fd508eebf3b240" memberName="sSineFreq"
          virtualName="" explicitFocusOrder="0" pos="0% 123.529% 100% 100%"
          posRelativeX="2c5c4d3bc0769a2b" posRelativeY="2c5c4d3bc0769a2b"
          posRelativeW="2c5c4d3bc0769a2b" posRelativeH="2c5c4d3bc0769a2b"
          tooltip="Sine Frequency" min="0" max="100" int="0.1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Velocity Sensitivity" id="7ddc354c5ee1fba6" memberName="sVelSens"
          virtualName="" explicitFocusOrder="0" pos="92.5% 41.25% 5.625% 9.375%"
          tooltip="Amp Velocity Sensitivity" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Amount" id="892c3c51db89d048" memberName="sFiltEnv"
          virtualName="" explicitFocusOrder="0" pos="92.5% 56.875% 5.625% 9.375%"
          tooltip="Filter Env Amount" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Velocity Sens" id="f12eb2f0344129ea" memberName="sFVSens"
          virtualName="" explicitFocusOrder="0" pos="92.5% 64.688% 5.625% 9.375%"
          tooltip="Filter Velocity Sensitivity" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pitchbend Range" id="f8d35e4737e52ab5" memberName="sPBRange"
          virtualName="" explicitFocusOrder="0" pos="36.667% 15.625% 5.625% 7.812%"
          posRelativeW="b4cfea27308348d9" tooltip="Pitchbend Range" thumbcol="bbbbff"
          trackcol="ffffff" rotarysliderfill="ff" rotaryslideroutline="0"
          textboxtext="ffffffff" min="0" max="24" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Input Gain" id="f41463c86a598835" memberName="sInputGain"
          virtualName="" explicitFocusOrder="0" pos="36.042% 83.75% 8.125% 11.25%"
          tooltip="Input Gain" bkgcol="0" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Wet/Dry" id="d8fa16ddd92f185b" memberName="sWet" virtualName=""
          explicitFocusOrder="0" pos="45.833% 83.75% 8.125% 11.25%" tooltip="Wet/Dry"
          bkgcol="0" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="-99" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Synth Gain" id="c3be568e2a93f6a3" memberName="sOscGain"
          virtualName="" explicitFocusOrder="0" pos="55.625% 83.75% 8.125% 11.25%"
          tooltip="Synth Gain" bkgcol="0" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Div Threshold" id="835be6a95912d3cf" memberName="sThresh"
          virtualName="" explicitFocusOrder="0" pos="0% 123.529% 127.679% 5.312%"
          posRelativeX="e15284b871cb9580" posRelativeY="e15284b871cb9580"
          posRelativeW="e15284b871cb9580" tooltip="Div Threshold" bkgcol="ff"
          min="0" max="100" int="0.1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Detune" id="cc4dac9a4a740ea3" memberName="sFreq1" virtualName=""
          explicitFocusOrder="0" pos="1.25% 26.25% 5.625% 10.312%" tooltip="Detune"
          rotarysliderfill="e3000000" rotaryslideroutline="66ffffff" min="-99"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Ring Modulation" id="d43d8133b340635a" memberName="sRingMod"
          virtualName="" explicitFocusOrder="0" pos="13.333% 65.625% 5.625% 10.312%"
          tooltip="Ring Modulation" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Attack" id="6a2e40edea06a000" memberName="sFAtt"
          virtualName="" explicitFocusOrder="0" pos="69.375% 51.562% 5% 100%"
          posRelativeH="98f08232c4ccc1db" tooltip="Filter Env Attack" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Decay" id="2375d21ea14c41f8" memberName="sFDec"
          virtualName="" explicitFocusOrder="0" pos="75.208% 0% 100% 100%"
          posRelativeY="6a2e40edea06a000" posRelativeW="6a2e40edea06a000"
          posRelativeH="6a2e40edea06a000" tooltip="Filter Env Decay" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Sustain" id="cc2b4987ae45a26e" memberName="sFSus"
          virtualName="" explicitFocusOrder="0" pos="81.042% 0% 100% 100%"
          posRelativeY="2375d21ea14c41f8" posRelativeW="2375d21ea14c41f8"
          posRelativeH="2375d21ea14c41f8" tooltip="Filter Env Sustain"
          min="0" max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Release" id="e91c901bfee60a50" memberName="sFRel"
          virtualName="" explicitFocusOrder="0" pos="87.083% 0% 100% 100%"
          posRelativeY="cc2b4987ae45a26e" posRelativeW="cc2b4987ae45a26e"
          posRelativeH="cc2b4987ae45a26e" tooltip="Filter Env Release"
          min="0" max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <JUCERCOMP name="" id="7c27853901fd2a9d" memberName="audioled" virtualName=""
             explicitFocusOrder="0" pos="37.5% 28.438% 2.083% 2.812%" sourceFile="led.cpp"
             constructorParams=""/>
  <SLIDER name="Osc Separation" id="75c6111f14c56688" memberName="sStereo"
          virtualName="" explicitFocusOrder="0" pos="7.083% 0% 5.625% 10.312%"
          posRelativeY="cc4dac9a4a740ea3" tooltip="Osc Separation" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="-99" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc Mix" id="8adc900b8b11e514" memberName="sOscMix" virtualName=""
          explicitFocusOrder="0" pos="13.542% 0% 5.625% 10.312%" posRelativeY="cc4dac9a4a740ea3"
          tooltip="Osc Mix" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="-99" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <JUCERCOMP name="" id="1645d1f6e255ba56" memberName="clipled" virtualName=""
             explicitFocusOrder="0" pos="90.833% 93.125% 2.083% 2.812%" sourceFile="led.cpp"
             constructorParams=""/>
  <TEXTBUTTON name="Polyphony" id="252f162c02937bbc" memberName="sMode" virtualName=""
              explicitFocusOrder="0" pos="43.958% 17.188% 6.458% 4.688%" tooltip="Mono Mode"
              bgColOff="af8f8f9e" bgColOn="c9faff44" buttonText="Mono" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Stereo" id="cbcc3c037ba6f0a6" memberName="sStereo2" virtualName=""
          explicitFocusOrder="0" pos="68.542% 111.765% 17.083% 5.312%"
          posRelativeY="20c26f0e7b36dd30" tooltip="Stereo" min="0" max="100"
          int="0.1" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="M Factor" id="46d8858795d0c45" memberName="sM1" virtualName=""
          explicitFocusOrder="0" pos="0% 158.824% 100% 100%" posRelativeX="67291950d5f1ae5c"
          posRelativeY="67291950d5f1ae5c" posRelativeW="67291950d5f1ae5c"
          posRelativeH="67291950d5f1ae5c" tooltip="M Factor" min="0" max="100"
          int="0.001" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Phase Mod" id="1d749f6879590691" memberName="sPhMod" virtualName=""
          explicitFocusOrder="0" pos="25.625% 3.03% 100% 100%" posRelativeY="8adc900b8b11e514"
          posRelativeW="8adc900b8b11e514" posRelativeH="8adc900b8b11e514"
          tooltip="Phase Mod" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Divider Mix" id="2e215e4f2ed1f863" memberName="sDivMix"
          virtualName="" explicitFocusOrder="0" pos="58.75% 37.5% 5.625% 10.312%"
          tooltip="Divider Mix" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="587aa06a37f3589c" memberName="info" virtualName=""
         explicitFocusOrder="0" pos="1.25% 14.062% 33.125% 3.125%" textCol="6affffff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="33"/>
  <JUCERCOMP name="" id="f4ad4dc211f498e4" memberName="pizButton" virtualName=""
             explicitFocusOrder="0" pos="41.458% 23.75% 16.875% 13.438%" sourceFile="PizButton.cpp"
             constructorParams=""/>
  <SLIDER name="Filter Key Follow" id="dbd7d6b2284ee89b" memberName="sFKeyFollow"
          virtualName="" explicitFocusOrder="0" pos="26.042% 68.125% 5.625% 6.875%"
          tooltip="Filter Key Follow" rotarysliderfill="0" rotaryslideroutline="ffffff"
          textboxtext="ffffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="next" id="2401d40242c71fcc" memberName="nextButton" virtualName=""
              explicitFocusOrder="0" pos="57.708% 13.438% 3.125% 4.062%" tooltip="Next Preset"
              bgColOff="478f8f9e" bgColOn="c9faff44" textCol="ffffffff" buttonText="&gt;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="previous" id="b18b281b256254b0" memberName="prevButton"
              virtualName="" explicitFocusOrder="0" pos="53.75% 13.438% 3.125% 4.062%"
              tooltip="Previous Preset" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffffffff" buttonText="&lt;" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Reset" id="d0d8a64702e81217" memberName="sReset" virtualName=""
              explicitFocusOrder="0" pos="91.042% 18.125% 6.875% 4.062%" tooltip="Reset all parameters"
              bgColOff="478f8f9e" bgColOn="c9faff44" textCol="ffb7b7b7" buttonText="Reset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Harshness" id="7b535f3a8eb8d3ed" memberName="sOPLP" virtualName=""
          explicitFocusOrder="0" pos="0.833% 68.125% 5.625% 6.875%" tooltip="Harshness"
          rotarysliderfill="0" rotaryslideroutline="ffffff" textboxtext="ffffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Post Divider Mix" id="1af37757abf958e" memberName="sPostDivMix"
          virtualName="" explicitFocusOrder="0" pos="58.75% 50.313% 5.625% 10.312%"
          tooltip="Post Divider Mix" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Save Patch" id="c423ebfec56b25d4" memberName="sSavePatch"
              virtualName="" explicitFocusOrder="0" pos="53.75% 18.125% 10% 4.062%"
              tooltip="Save patch" bgColOff="478f8f9e" bgColOn="c9faff44" textCol="c5ffffff"
              buttonText="Save patch" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Save Bank" id="acdc62fb20065374" memberName="sSavePatch2"
              virtualName="" explicitFocusOrder="0" pos="65% 18.125% 10% 4.062%"
              tooltip="Save bank" bgColOff="478f8f9e" bgColOn="c9faff44" textCol="c5ffffff"
              buttonText="Save bank" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="512bea4aaf67435" memberName="info3" virtualName=""
         explicitFocusOrder="0" pos="61.042% 13.438% 5% 4.062%" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="128:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="94e887826c3824bb" memberName="info2" virtualName=""
         explicitFocusOrder="0" pos="65.208% 13.438% 22.708% 4.062%" tooltip="Rename Patch"
         textCol="ffffffff" edTextCol="ffffff9f" edBkgCol="0" hiliteCol="7bffff00"
         labelText="patch name" editableSingleClick="0" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Load Patch" id="eaec04d5a8153bf0" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="91.042% 13.438% 6.875% 4.062%"
              tooltip="Load bank/patch" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffb7b7b7" buttonText="Load" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="Filter Mode" id="7435cbde124ae4de" memberName="filterModeBox"
            virtualName="" explicitFocusOrder="0" pos="11.875% 51.562% 8.958% 100%"
            posRelativeH="bc6289c05f44be1a" tooltip="Filter Mode" editable="0"
            layout="33" items="Off&#10;Low24&#10;Low&#10;Band&#10;Notch&#10;High&#10;Formant" textWhenNonSelected="Formant"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc 1 Octave" id="a31407cc9477bc24" memberName="sOctave1"
          virtualName="" explicitFocusOrder="0" pos="-0.208% 18.125% 5.625% 6.875%"
          tooltip="Osc 1 Octave" rotarysliderfill="0" rotaryslideroutline="ffffff"
          textboxtext="ffffffff" min="-12" max="6" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Waveform1" id="bc6289c05f44be1a" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="4.583% 19.688% 11.25% 4.062%"
            tooltip="Waveform1" editable="0" layout="33" items="RampUp&#10;RampDown&#10;Square&#10;Triangle&#10;Sine&#10;Minkowski&#10;Weierstrass&#10;AutoAlias&#10;Eight&#10;OddEight&#10;Computer&#10;Funnel&#10;Grate&#10;Noise&#10;Sine+&#10;Narrow&#10;Octaves&#10;Ughhh"
            textWhenNonSelected="???????" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc 2 Octave" id="16bb23adebfca409" memberName="sOctave2"
          virtualName="" explicitFocusOrder="0" pos="26.875% 18.125% 5.625% 6.875%"
          tooltip="Osc 2 Octave" rotarysliderfill="0" rotaryslideroutline="ffffff"
          textboxtext="ffffffff" min="-12" max="6" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Waveform2" id="52decd564aac4c47" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="16.458% 0% 100% 100%"
            posRelativeY="bc6289c05f44be1a" posRelativeW="bc6289c05f44be1a"
            posRelativeH="bc6289c05f44be1a" tooltip="Waveform2" editable="0"
            layout="33" items="RampUp&#10;RampDown&#10;Square&#10;Triangle&#10;Sine&#10;Minkowski&#10;Weierstrass&#10;AutoAlias&#10;Eight&#10;OddEight&#10;Computer&#10;Funnel&#10;Grate&#10;Noise&#10;Sine+&#10;Narrow&#10;Octaves&#10;Ughhh"
            textWhenNonSelected="???????" textWhenNoItems="(no choices)"/>
  <SLIDER name="MIDI Channel" id="b7a8ffcec56914e5" memberName="sChannel"
          virtualName="" explicitFocusOrder="0" pos="45.833% 10.625% 5.625% 7.812%"
          posRelativeW="b4cfea27308348d9" tooltip="MIDI Channel" thumbcol="bbbbff"
          trackcol="ffffff" rotarysliderfill="ff" rotaryslideroutline="0"
          textboxtext="ffffffff" min="0" max="16" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 2 Harmonic" id="1967b716efd6939b" memberName="sOctave"
          virtualName="" explicitFocusOrder="0" pos="19.583% 0% 5.625% 10.312%"
          posRelativeY="cc4dac9a4a740ea3" tooltip="Osc 2 Harmonic" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="12" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="UseProgCh" id="32af558b7d0377d0" memberName="sUseProgCh"
              virtualName="" explicitFocusOrder="0" pos="37.083% 12.5% 9.583% 4.062%"
              tooltip="Use Program Change" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="Use ProgCh" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="M Effect Mix" id="34b1a1b115a46f1a" memberName="sM1Mix"
          virtualName="" explicitFocusOrder="0" pos="104.808% -41.176% 5.625% 10.312%"
          posRelativeX="67291950d5f1ae5c" posRelativeY="46d8858795d0c45"
          tooltip="M Effect Mix" rotarysliderfill="7f000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Randomize" id="b33dbbb86b9227ef" memberName="randomButton"
              virtualName="" explicitFocusOrder="0" pos="76.042% 18.125% 13.958% 4.062%"
              tooltip="Randomize all parameters" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="c5ffffff" buttonText="Randomize" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Limiter" id="5968edc0e0163352" memberName="limiterButton"
              virtualName="" explicitFocusOrder="0" pos="75% 92.812% 9.583% 4.062%"
              tooltip="Limiter" bgColOff="af8f8f9e" bgColOn="c9faff44" textCol="ff000000"
              buttonText="Limiter" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Envelope Curve" id="1f96516861dcce44" memberName="sExp"
              virtualName="" explicitFocusOrder="0" pos="93.333% 28.75% 3.958% 4.688%"
              tooltip="Percussive Envelope" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="P" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Filter Envelope Curve" id="2c92bb97805a786b" memberName="sFExp"
              virtualName="" explicitFocusOrder="0" pos="93.333% 52.188% 3.958% 4.688%"
              tooltip="Percussive Envelope" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="P" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="1f5c15f3cb510b21" memberName="midiled" virtualName=""
             explicitFocusOrder="0" pos="60.417% 28.438% 2.083% 2.812%" sourceFile="led.cpp"
             constructorParams=""/>
  <TEXTBUTTON name="Save Snapshot" id="95c28f5c22f1a6ea" memberName="saveSnapshotButtonB"
              virtualName="" explicitFocusOrder="0" pos="97.292% 0% 3.125% 4.062%"
              tooltip="Save Snapshot B" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffb7b7b7" buttonText="S" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Recall Snapshot" id="cce0eb45b4f9a834" memberName="recallSnapshotButtonB"
              virtualName="" explicitFocusOrder="0" pos="97.292% 4.688% 3.125% 4.062%"
              tooltip="Recall Snapshot B" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffb7b7b7" buttonText="R" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="Morph" id="b61f633600f68112" memberName="sMorph" virtualName=""
          explicitFocusOrder="0" pos="3.333% -1.875% 92.5% 5.312%" tooltip="Morph"
          thumbcol="20ababab" trackcol="ffffff" rotarysliderfill="360000ff"
          min="-100" max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Save Snapshot" id="6228cbbb6bb2b857" memberName="saveSnapshotButtonA"
              virtualName="" explicitFocusOrder="0" pos="-0.625% 0% 3.125% 4.062%"
              tooltip="Save Snapshot A" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffb7b7b7" buttonText="S" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Recall Snapshot" id="7208f7c435615e0f" memberName="recallSnapshotButtonA"
              virtualName="" explicitFocusOrder="0" pos="-0.625% 4.688% 3.125% 4.062%"
              tooltip="Recall Snapshot A" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffb7b7b7" buttonText="R" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <JUCERCOMP name="" id="44c6a61eea081d43" memberName="aboutbox" virtualName=""
             explicitFocusOrder="0" pos="50.104%c 13.438% 52.708% 49.062%"
             sourceFile="AboutBox.cpp" constructorParams=""/>
  <TEXTBUTTON name="Pitch Shift Input" id="b8dbd9871b5f3e25" memberName="sPitchShift"
              virtualName="" explicitFocusOrder="0" pos="35.625% 101.875% 8.333% 4.062%"
              tooltip="Pitch Shift Input" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="PitchShift" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="872770bb2d2498d9" memberName="resizer" virtualName=""
                    explicitFocusOrder="0" pos="16R 16R 16 16" class="ResizableCornerComponent"
                    params="this, &amp;resizeLimits"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: mralias2_png, 127623, "../../../../My Documents/My Pictures/mralias2.png"
static const unsigned char resource_MrAlias2Editor_mralias2_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,224,0,0,1,64,8,2,0,0,0,235,170,56,44,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,
0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,9,22,23,3,51,199,79,217,240,0,0,0,25,116,69,88,116,67,111,109,109,101,110,116,0,67,114,101,97,116,101,100,32,119,105,116,
104,32,71,73,77,80,87,129,14,23,0,0,32,0,73,68,65,84,120,218,188,189,121,176,92,87,117,61,220,243,60,191,121,150,158,164,167,217,150,100,91,150,100,97,121,192,54,21,97,130,99,3,198,16,18,136,73,42,142,
3,20,101,147,241,71,168,130,36,24,18,66,8,149,57,193,129,4,76,138,193,96,3,9,113,8,102,112,108,201,178,6,203,154,229,167,55,207,67,79,175,231,238,239,143,133,23,219,251,220,190,239,217,85,249,238,31,170,
86,191,238,219,247,158,123,206,62,123,175,189,246,218,206,209,209,209,198,43,135,195,56,156,78,39,94,120,189,94,167,56,248,39,252,139,239,58,157,78,151,203,229,247,251,93,46,87,163,209,112,185,92,14,135,
195,227,241,184,221,110,199,107,63,106,181,90,163,209,112,58,157,141,70,227,187,223,253,238,232,232,168,203,229,114,185,92,110,183,27,63,228,116,58,221,110,247,39,63,249,201,243,231,207,243,26,44,175,
159,127,194,23,147,201,100,79,79,143,252,24,175,223,227,241,212,235,245,134,56,234,245,58,174,1,239,215,235,117,126,160,94,175,39,18,137,13,27,54,212,106,181,90,173,54,57,57,121,241,226,69,158,77,254,
43,255,203,239,54,26,141,246,246,246,251,239,191,63,22,139,249,124,190,122,189,142,187,243,122,189,62,159,207,235,245,122,189,222,120,60,126,219,109,183,53,94,125,96,112,106,181,154,121,126,62,20,121,
184,92,174,231,159,127,254,187,223,253,238,197,139,23,95,122,233,165,225,225,225,251,239,191,127,227,198,141,234,246,213,0,250,124,62,62,125,158,182,209,104,116,116,116,116,119,119,171,159,224,29,225,
24,25,25,153,152,152,224,149,56,28,14,60,59,249,92,240,62,231,134,156,90,14,135,227,177,199,30,27,31,31,119,56,28,177,88,44,153,76,22,139,197,227,199,143,243,51,181,90,77,77,66,121,169,245,122,29,31,192,
252,49,39,179,252,10,135,84,62,160,106,181,106,249,248,254,243,63,255,243,208,161,67,229,114,185,82,169,84,171,85,183,219,93,171,213,240,115,245,87,14,57,85,120,1,114,124,48,26,141,70,35,149,74,37,147,
73,121,126,53,117,229,5,171,117,97,46,216,122,189,94,42,149,176,238,2,129,128,215,235,85,83,162,82,169,84,42,21,92,6,62,96,206,28,243,50,154,77,102,156,199,242,51,60,66,161,144,199,227,49,255,36,135,253,
216,177,99,120,241,79,255,244,79,95,248,194,23,60,175,62,240,73,76,158,124,62,95,169,84,228,115,87,207,84,94,146,57,170,150,147,220,188,114,53,91,96,100,60,30,143,235,213,71,181,90,173,86,171,176,66,88,
98,120,52,114,209,225,128,1,196,210,118,185,92,109,109,109,219,182,109,195,9,221,110,55,78,142,23,145,72,36,18,137,20,139,197,84,42,21,143,199,113,30,15,102,149,141,129,163,149,228,45,113,77,242,30,104,
46,61,30,15,135,140,54,122,213,3,23,160,6,29,195,237,114,185,234,245,250,173,183,222,250,213,175,126,181,86,171,169,97,114,58,157,139,139,139,152,238,188,200,59,238,184,99,105,105,233,200,145,35,234,87,
240,188,49,83,121,107,188,35,204,57,172,58,121,54,252,87,14,5,255,228,116,58,83,169,84,181,90,197,23,97,146,204,135,109,78,2,220,154,207,231,123,219,219,222,230,247,251,241,117,90,43,185,206,59,58,58,
44,167,154,188,120,190,163,254,36,63,127,237,181,215,158,58,117,42,20,10,109,223,190,189,82,169,12,13,13,121,60,158,108,54,155,203,229,44,39,174,52,16,202,76,192,126,113,106,202,199,141,99,105,105,105,
120,120,88,218,92,60,68,101,76,165,125,228,73,120,90,254,220,210,210,210,236,236,172,207,231,147,215,224,118,187,57,105,229,141,171,249,41,223,151,150,200,52,70,150,75,212,114,69,240,77,175,215,43,109,
165,220,122,229,94,85,171,213,56,133,240,87,140,134,195,225,152,159,159,15,133,66,234,214,212,239,154,54,26,247,142,237,89,77,137,96,48,136,11,51,183,85,92,9,239,189,80,40,96,6,202,133,176,234,33,63,233,
114,185,120,13,242,125,185,58,176,226,228,69,90,90,106,252,11,231,70,77,15,12,23,190,30,14,135,179,217,44,134,206,242,218,48,50,234,204,54,143,114,45,7,198,173,86,171,97,195,224,197,96,111,150,227,140,
37,172,30,25,159,56,255,20,143,199,49,201,105,160,105,205,202,229,242,212,212,84,46,151,155,156,156,108,109,109,237,238,238,142,68,34,30,206,39,211,157,148,35,142,159,49,215,131,116,184,228,234,162,165,
80,151,171,102,30,156,17,238,150,252,185,114,185,140,239,226,242,124,62,223,77,55,221,244,163,31,253,72,154,102,220,225,226,226,162,220,48,14,28,56,112,203,45,183,172,172,172,116,116,116,60,249,228,147,
242,70,248,216,114,185,92,38,147,113,185,92,240,82,113,95,220,42,112,54,204,3,44,45,115,242,241,33,69,163,209,122,189,94,169,84,178,217,108,62,159,183,241,59,228,18,197,57,223,241,142,119,196,98,49,188,
15,147,215,104,52,16,31,96,5,186,221,238,254,254,126,75,7,132,238,179,218,6,44,31,13,254,180,111,223,190,39,159,124,18,191,30,10,133,18,137,68,107,107,107,169,84,202,102,179,184,248,98,177,200,207,123,
60,30,76,56,117,42,167,211,9,195,132,129,194,204,147,214,176,90,173,158,60,121,178,90,173,74,235,108,233,221,211,219,53,125,91,250,137,197,98,17,151,129,61,149,7,38,0,126,69,109,75,120,33,205,71,163,209,
216,181,107,151,215,235,125,254,249,231,45,247,155,181,172,97,156,246,208,161,67,24,115,140,143,233,51,42,75,77,127,220,220,69,112,76,77,77,13,12,12,52,115,93,45,61,104,220,190,180,8,184,95,44,245,102,
123,173,178,38,46,151,11,99,27,10,133,204,197,110,233,162,153,103,86,31,86,207,130,43,218,50,22,49,255,52,61,61,109,198,127,106,167,137,68,34,217,108,86,25,40,115,141,155,110,165,205,101,175,186,39,225,
5,92,230,114,185,236,247,251,147,201,100,32,16,152,157,157,229,200,48,220,55,215,139,218,150,34,145,136,105,154,241,95,167,211,89,40,20,240,98,113,113,49,155,205,182,180,180,120,228,134,111,121,125,252,
85,174,37,105,133,225,195,203,64,6,127,117,191,114,152,6,90,62,72,24,232,114,185,236,118,187,17,215,99,123,231,34,164,163,212,223,223,63,48,48,48,53,53,69,111,221,229,114,141,142,142,202,149,185,117,235,
214,7,31,124,176,86,171,205,205,205,237,218,181,203,239,247,127,239,123,223,43,151,203,230,14,180,188,188,12,52,3,255,245,249,124,184,90,191,223,239,118,187,3,129,0,60,110,123,151,42,145,72,212,106,181,
106,181,10,124,163,89,108,104,58,14,141,70,227,214,91,111,109,107,107,163,195,85,171,213,128,114,96,55,34,70,148,72,36,44,151,174,244,209,214,226,5,56,28,142,109,219,182,157,56,113,226,244,233,211,133,
66,1,17,58,22,109,56,28,14,4,2,169,84,170,84,42,229,114,185,92,46,151,207,231,93,46,23,109,162,90,39,112,40,148,95,204,203,56,117,234,84,161,80,80,214,89,206,28,21,188,75,136,67,70,241,201,100,242,220,
185,115,120,214,150,126,61,38,158,180,194,234,74,104,163,59,59,59,175,186,234,170,106,181,154,76,38,143,30,61,154,201,100,236,221,43,155,144,130,115,30,11,146,113,222,170,54,90,97,65,92,77,133,66,97,126,
126,190,165,165,197,92,35,42,182,48,109,180,215,235,229,51,146,145,171,165,1,34,40,36,135,171,90,173,174,172,172,192,70,175,197,113,54,1,67,27,92,81,58,242,166,141,54,23,197,165,75,151,248,184,205,208,
141,175,131,193,32,236,131,77,112,211,108,207,80,81,197,90,236,178,57,14,229,114,57,28,14,251,253,254,245,235,215,47,44,44,192,169,135,131,101,154,56,25,157,195,16,135,195,97,238,166,202,82,23,10,5,216,
28,250,46,243,243,243,30,76,53,19,190,145,99,196,160,76,69,145,0,76,113,46,66,28,248,201,85,67,36,76,26,186,33,64,208,202,229,50,110,149,198,17,176,6,94,239,219,183,239,63,254,227,63,112,171,248,185,114,
185,204,121,191,110,221,186,223,249,157,223,193,79,183,180,180,192,53,142,199,227,95,253,234,87,139,197,162,218,234,213,252,192,7,228,17,12,6,177,103,192,118,91,6,131,177,88,12,160,94,185,92,94,90,90,
50,231,174,242,112,121,108,218,180,105,203,150,45,28,115,184,66,242,3,120,96,189,189,189,230,119,137,144,190,86,3,221,104,52,246,239,223,255,204,51,207,84,42,149,169,169,169,64,32,128,48,141,40,42,102,
191,223,239,7,110,83,44,22,97,202,205,39,136,103,68,116,158,191,50,58,58,58,57,57,169,224,111,60,17,75,124,195,18,141,193,132,132,215,201,89,199,32,81,218,44,196,55,114,147,48,61,41,175,215,123,243,205,
55,87,42,149,90,173,22,137,68,246,237,219,119,250,244,105,128,81,54,40,164,229,168,238,220,185,211,198,136,155,166,25,67,74,164,142,211,88,61,187,217,217,89,44,120,211,125,54,99,80,51,154,193,3,170,86,
171,52,136,205,76,170,60,15,87,180,105,163,215,104,188,76,184,79,238,145,88,194,150,83,209,210,131,158,154,154,106,230,59,171,108,1,252,39,68,123,205,130,33,27,227,163,102,236,90,236,187,58,218,218,218,
96,91,220,110,119,119,119,119,62,159,71,178,68,142,137,165,95,223,104,52,194,225,176,140,206,165,153,150,86,94,174,20,15,147,27,205,46,142,190,146,26,47,56,206,240,248,124,62,223,218,147,129,124,144,197,
98,241,217,103,159,253,244,167,63,253,153,207,124,166,191,191,191,86,171,149,74,37,88,94,132,72,106,54,123,189,222,189,123,247,30,59,118,140,121,66,100,14,17,179,255,254,239,255,126,60,30,135,241,2,248,
0,183,226,254,251,239,127,236,177,199,102,103,103,85,192,98,57,129,120,203,52,217,116,130,112,131,176,107,110,183,59,22,139,49,206,93,88,88,96,188,105,137,105,202,187,72,36,18,140,148,177,33,215,235,245,
96,48,168,48,16,151,203,213,215,215,103,57,141,148,215,182,70,3,141,141,173,189,189,125,108,108,44,155,205,174,172,172,48,41,10,107,194,3,143,216,239,247,99,91,42,22,139,229,114,25,123,39,176,44,124,12,
219,164,4,142,78,159,62,45,177,105,186,207,202,119,150,166,71,90,94,57,15,165,217,165,215,105,218,104,60,2,211,145,167,25,186,249,230,155,153,210,129,209,223,182,109,91,42,149,58,115,230,140,229,35,179,
57,82,169,148,77,190,87,2,208,42,42,149,193,190,244,160,121,158,241,241,241,13,27,54,40,96,208,222,58,75,27,141,17,176,201,136,202,173,84,218,80,218,232,82,169,164,118,8,27,39,186,89,194,67,62,101,51,
249,100,179,153,1,223,48,99,44,121,71,210,131,244,120,60,184,235,102,63,209,236,81,42,183,224,117,96,29,193,96,48,145,72,200,105,92,173,86,83,169,84,54,155,69,224,40,135,133,215,207,200,32,26,141,74,11,
46,193,141,82,169,132,45,86,230,246,156,78,167,135,9,232,102,55,35,247,91,134,222,129,64,32,16,8,112,13,175,253,38,57,34,207,60,243,204,159,252,201,159,192,161,251,163,63,250,163,127,248,135,127,40,20,
10,116,52,136,177,226,234,249,44,59,59,59,187,187,187,23,22,22,96,199,97,208,157,78,231,167,62,245,169,158,158,158,74,165,34,243,170,126,191,191,167,167,199,235,245,222,125,247,221,223,254,246,183,129,
66,208,7,180,207,139,154,230,15,80,204,202,202,10,222,207,102,179,221,221,221,112,247,36,190,97,239,91,121,60,158,219,110,187,77,162,147,116,153,37,129,164,94,175,123,60,30,75,15,218,116,159,109,38,25,
215,161,203,229,202,229,114,115,115,115,135,14,29,250,215,127,253,87,196,46,245,122,125,101,101,133,35,12,208,3,99,142,89,193,107,246,120,60,225,112,184,94,175,23,139,69,216,59,185,138,48,56,199,143,31,
39,244,204,16,71,162,94,156,75,114,168,153,254,86,183,67,155,162,200,30,150,22,10,236,5,211,97,60,112,224,192,224,224,32,182,79,220,29,110,60,145,72,92,125,245,213,23,46,92,0,220,177,42,184,129,227,240,
225,195,54,136,179,180,212,52,208,50,102,55,63,204,179,173,172,172,204,206,206,182,181,181,241,215,113,191,42,255,97,239,71,43,39,186,25,156,77,26,9,119,53,140,127,165,82,49,65,9,123,196,217,116,162,101,
122,198,30,127,80,190,203,137,19,39,76,203,163,146,94,242,235,126,191,223,220,182,29,255,247,71,107,107,171,116,65,96,151,93,46,87,44,22,11,135,195,75,75,75,229,114,217,231,243,153,160,10,99,110,19,168,
128,29,83,52,39,254,213,67,194,128,137,130,73,63,5,139,60,24,12,70,163,81,0,181,175,251,38,39,39,39,255,242,47,255,242,43,95,249,10,92,122,151,203,245,253,239,127,255,169,167,158,218,191,127,191,156,199,
146,204,0,27,129,191,238,220,185,243,217,103,159,197,16,188,244,210,75,78,167,243,195,31,254,240,208,208,16,119,26,25,249,186,221,238,182,182,54,183,219,125,215,93,119,125,255,251,223,191,116,233,146,
141,111,203,29,200,102,161,242,77,120,235,245,122,29,79,197,146,81,103,174,231,67,135,14,225,249,209,125,198,108,6,164,64,108,199,225,112,180,183,183,43,199,193,244,157,215,226,65,211,222,141,141,141,
33,71,49,52,52,132,4,17,28,103,184,240,120,160,140,202,45,247,108,120,16,62,159,15,87,43,221,231,23,95,124,17,217,90,102,14,8,88,43,66,158,137,149,217,128,12,107,241,34,93,46,151,207,231,227,35,224,135,
123,123,123,247,238,221,139,57,6,235,44,205,180,199,227,217,188,121,243,248,248,56,48,153,102,206,23,47,96,211,166,77,160,196,89,62,92,211,52,99,159,227,58,146,31,48,159,163,215,235,101,8,197,228,135,
229,115,108,54,20,240,40,45,199,170,89,186,222,76,134,175,209,70,243,79,116,215,76,148,73,218,7,75,148,79,153,233,92,46,103,143,5,243,132,28,58,191,223,143,48,87,102,200,94,71,26,112,237,246,61,18,137,
4,131,65,78,242,82,169,4,174,1,31,119,123,123,59,146,10,88,41,50,49,0,251,25,143,199,205,93,138,12,46,114,147,164,115,236,129,187,202,5,169,6,218,233,116,134,66,161,100,50,25,141,70,45,147,9,171,238,240,
242,200,229,114,159,252,228,39,191,254,245,175,211,213,133,179,230,114,185,254,250,175,255,122,223,190,125,202,85,228,88,19,40,7,206,176,115,231,206,211,167,79,123,60,158,149,149,149,95,253,213,95,61,
124,248,48,227,92,220,36,221,55,188,142,199,227,30,143,231,246,219,111,15,6,131,47,190,248,162,122,156,10,89,179,164,94,240,224,156,38,61,110,122,122,186,92,46,51,60,105,102,154,27,141,198,238,221,187,
19,137,4,151,104,169,84,194,82,228,61,150,203,101,36,127,26,141,6,221,103,57,47,77,94,151,250,81,181,8,233,62,47,46,46,174,172,172,96,50,29,60,120,240,7,63,248,65,237,213,7,35,36,34,24,150,83,214,239,
247,35,34,150,216,244,196,196,4,178,181,138,4,42,65,12,69,222,224,245,211,85,84,211,9,91,5,62,105,239,13,192,199,39,85,17,167,13,4,2,111,126,243,155,171,213,106,165,82,9,6,131,153,76,70,122,208,188,235,
246,246,118,191,223,63,62,62,94,169,84,44,115,48,120,177,110,221,186,214,214,86,108,153,150,207,87,26,14,140,36,105,200,140,62,21,253,142,31,110,111,111,151,100,74,19,121,51,253,95,203,229,134,65,104,
150,221,50,105,33,150,204,7,56,128,171,154,57,229,30,50,63,214,236,121,89,238,55,210,82,95,186,116,201,105,28,146,85,197,41,196,223,170,213,106,126,191,191,84,42,189,38,247,121,213,253,190,25,0,237,116,
58,219,219,219,37,64,183,176,176,96,46,249,80,40,212,223,223,191,188,188,60,63,63,239,241,120,130,193,96,56,28,38,9,82,81,60,241,26,118,0,214,92,209,151,29,14,199,207,33,14,89,148,225,241,120,146,201,
36,106,4,44,55,67,251,45,200,28,130,124,62,255,216,99,143,253,235,191,254,235,210,210,18,121,114,48,166,248,239,177,99,199,158,122,234,169,219,111,191,93,146,109,229,150,66,158,114,189,94,143,70,163,201,
100,50,155,205,110,221,186,245,189,239,125,47,41,95,60,33,185,204,180,215,126,191,127,96,96,192,237,118,7,131,65,80,164,101,94,187,25,75,223,50,52,195,135,67,161,16,104,55,243,243,243,146,242,217,140,
188,209,219,219,59,48,48,32,183,31,101,173,48,29,225,156,130,96,39,191,78,198,97,51,3,109,114,138,57,191,171,213,234,248,248,56,83,201,94,175,119,104,104,40,147,201,208,96,225,204,112,193,176,95,42,86,
150,220,41,107,181,218,202,202,10,127,177,80,40,188,248,226,139,138,25,45,217,144,106,201,153,196,237,102,36,10,174,118,201,131,180,156,93,240,167,72,254,115,56,28,119,222,121,39,114,200,176,188,88,201,
150,54,58,16,8,128,29,4,74,120,163,209,184,239,190,251,222,240,134,55,124,252,227,31,71,242,7,229,36,213,106,21,6,218,50,2,147,69,76,146,209,68,216,74,34,206,252,74,56,28,30,24,24,144,92,20,197,122,90,
213,227,83,31,110,86,118,96,218,98,245,21,249,69,123,63,218,196,178,77,90,173,229,134,106,19,246,129,194,97,242,238,155,241,88,48,193,224,220,128,47,168,88,225,175,143,239,108,255,1,88,66,98,86,243,243,
243,228,47,200,192,2,151,212,222,222,158,74,165,38,38,38,50,153,76,54,155,13,133,66,177,88,44,22,139,153,167,69,233,13,57,23,230,45,123,124,62,223,202,202,10,230,86,52,26,77,165,82,192,83,86,69,220,109,
54,115,245,167,47,125,233,75,95,253,234,87,151,151,151,43,149,10,44,38,94,96,249,17,232,248,228,39,63,201,170,57,186,204,146,153,36,205,196,192,192,192,23,190,240,133,183,189,237,109,128,111,248,216,20,
75,154,27,0,158,104,95,95,159,207,231,139,197,98,63,252,225,15,9,134,72,55,199,38,219,128,208,158,169,9,96,178,200,61,194,224,50,50,53,231,98,52,26,221,189,123,183,68,192,193,171,195,38,129,47,114,37,
215,106,181,174,174,46,34,33,150,39,92,21,134,150,143,121,106,106,74,82,113,29,14,199,230,205,155,143,28,57,2,110,3,89,28,120,16,249,124,158,184,179,195,170,94,20,57,67,254,208,115,207,61,7,24,142,206,
78,51,3,45,163,16,149,174,49,51,251,242,137,203,50,4,155,37,20,10,133,112,241,215,95,127,125,103,103,39,114,6,4,103,57,236,230,1,64,201,239,247,47,44,44,68,163,209,79,125,234,83,241,120,252,77,111,122,
211,231,63,255,249,175,126,245,171,45,45,45,248,110,103,103,167,13,232,140,23,120,106,116,162,21,129,85,186,65,253,253,253,50,235,40,195,190,181,251,125,175,213,31,100,252,103,73,172,230,188,66,105,194,
90,24,105,150,24,84,179,210,135,102,30,52,50,204,216,156,204,189,220,230,231,0,186,58,28,14,100,134,214,232,74,191,14,180,218,231,243,37,147,73,90,231,229,229,101,0,146,114,171,102,65,10,134,206,239,247,
111,220,184,113,105,105,105,124,124,28,211,82,25,85,130,4,32,194,57,140,202,190,159,121,208,94,175,183,179,179,51,28,14,71,163,81,110,125,107,164,7,172,106,169,127,240,131,31,252,219,191,253,219,248,248,
56,22,63,253,89,185,128,49,41,93,46,215,244,244,244,55,190,241,141,123,238,185,135,14,166,154,79,18,193,244,251,253,191,240,11,191,240,207,255,252,207,141,70,163,175,175,111,195,134,13,129,64,64,178,178,
248,67,210,100,212,106,181,150,150,150,235,174,187,174,209,104,28,61,122,148,8,169,9,138,41,127,1,220,100,38,48,97,91,235,245,250,204,204,12,119,66,153,216,145,39,12,133,66,7,14,28,144,211,14,129,164,
164,63,43,71,12,149,232,38,130,225,241,120,72,235,182,132,56,204,117,91,40,20,102,102,102,228,10,132,167,182,101,203,150,231,159,127,94,90,103,204,48,58,212,8,208,56,41,113,78,192,74,196,55,206,158,61,
75,126,161,42,40,165,209,193,179,80,185,126,105,47,148,9,80,118,156,100,158,85,45,145,211,233,244,249,124,137,68,226,186,235,174,131,105,230,129,112,120,101,101,133,238,51,34,6,248,1,48,211,161,80,200,
229,114,189,255,253,239,7,189,61,26,141,62,244,208,67,239,126,247,187,191,248,197,47,254,247,127,255,55,18,212,50,179,39,89,55,184,128,64,32,64,47,94,114,144,228,199,32,15,208,211,211,35,221,76,188,126,
125,121,157,181,48,61,84,9,143,68,66,44,105,230,116,56,44,109,116,179,108,161,101,165,134,61,178,129,119,78,158,60,105,242,64,236,45,169,226,225,169,90,179,102,171,216,190,146,203,230,104,105,105,225,
66,40,22,139,217,108,214,76,86,73,240,157,147,63,145,72,196,227,241,137,137,9,167,211,25,139,197,84,180,97,114,201,200,200,252,185,7,189,105,211,38,203,106,180,102,241,145,61,53,146,175,143,29,59,246,
232,163,143,194,119,131,93,230,191,178,86,155,30,52,204,244,39,63,249,201,219,111,191,61,30,143,163,142,78,57,206,184,103,122,106,3,3,3,215,95,127,253,15,127,248,195,51,103,206,156,60,121,178,165,165,
101,211,166,77,221,221,221,52,7,116,165,165,103,231,116,58,195,225,240,254,253,251,147,201,228,79,126,242,19,212,188,54,243,227,240,47,234,86,104,169,81,127,85,175,215,211,233,52,124,73,220,50,252,14,
101,235,189,94,239,193,131,7,227,241,56,19,181,192,223,73,123,100,101,32,30,21,46,190,181,181,245,204,153,51,145,72,36,145,72,4,2,1,57,225,96,163,215,72,228,104,52,26,224,252,114,123,199,139,233,233,233,
137,137,9,144,184,21,12,77,48,183,82,169,20,10,5,191,223,15,39,133,149,159,116,111,23,23,23,81,92,32,29,94,206,1,146,226,229,30,108,50,91,149,54,128,188,35,137,95,219,44,30,48,16,64,4,12,135,195,127,245,
87,127,245,223,255,253,223,210,58,51,238,65,186,92,33,239,242,223,222,222,222,223,253,221,223,165,201,118,58,157,109,109,109,31,252,224,7,111,186,233,166,255,252,207,255,180,1,160,37,9,71,42,186,168,155,
242,120,60,235,214,173,11,135,195,166,153,144,210,25,175,201,137,126,125,54,90,185,35,150,24,8,214,224,218,253,104,75,152,69,18,206,154,17,57,200,177,179,172,133,177,180,221,242,147,240,141,152,53,161,
27,107,153,235,126,77,174,39,115,131,76,191,213,106,53,228,0,21,227,136,174,9,113,69,184,131,120,191,191,191,223,231,243,201,60,48,166,156,52,77,234,170,184,91,123,154,105,250,188,14,4,7,67,118,225,194,
133,199,31,127,252,165,151,94,34,160,65,223,89,217,104,12,43,179,121,136,175,31,125,244,209,7,30,120,64,153,99,105,169,101,113,218,205,55,223,124,252,248,241,153,153,153,122,189,62,57,57,57,50,50,18,8,
4,214,173,91,183,117,235,86,22,203,171,231,138,107,240,122,189,219,183,111,79,36,18,63,248,193,15,230,230,230,248,216,170,213,42,235,148,48,112,112,204,229,115,69,122,112,124,124,124,121,121,89,174,16,
73,13,166,71,188,107,215,174,84,42,197,205,70,214,7,19,21,225,99,198,103,90,91,91,157,78,231,202,202,74,62,159,71,229,100,44,22,11,133,66,168,226,199,98,6,177,172,25,162,199,185,187,180,180,132,68,51,
198,208,229,114,77,77,77,29,57,114,164,90,173,118,116,116,152,145,62,237,53,167,114,185,92,206,229,114,145,72,4,129,216,228,228,228,204,204,76,36,18,241,251,253,23,46,92,32,12,103,35,231,66,67,76,147,
141,83,53,163,28,72,154,157,42,181,151,216,58,204,46,236,47,223,127,252,241,199,111,186,233,166,209,209,209,19,39,78,224,175,52,208,216,2,9,116,240,78,73,3,175,215,235,191,253,219,191,237,16,66,84,4,253,
183,109,219,118,213,85,87,89,34,75,76,235,209,64,72,174,155,252,124,91,91,27,106,71,77,125,43,51,27,241,127,234,71,175,29,30,81,54,186,89,46,218,6,238,104,86,216,34,7,1,6,218,158,213,103,94,179,244,24,
176,41,42,102,52,93,81,147,153,46,115,143,246,230,206,229,114,165,82,41,126,114,110,110,78,198,124,82,36,78,178,254,153,156,103,176,2,9,57,149,31,82,101,41,138,212,244,51,96,214,50,209,244,90,17,46,252,
198,226,226,226,151,191,252,229,179,103,207,74,64,3,255,242,133,44,115,228,206,67,15,218,229,114,125,233,75,95,122,231,59,223,25,143,199,149,178,140,140,136,101,80,121,239,189,247,254,197,95,252,5,31,
64,58,157,62,118,236,216,179,207,62,187,97,195,134,193,193,65,152,33,238,225,76,127,225,190,214,173,91,119,215,93,119,125,253,235,95,159,159,159,183,156,13,72,188,202,5,137,235,1,250,108,194,214,196,214,
185,38,203,229,50,24,14,14,33,158,128,104,26,12,86,212,248,36,18,9,112,197,124,62,223,186,117,235,150,151,151,101,58,145,151,23,137,68,162,209,40,138,179,149,141,54,121,169,40,64,151,155,223,169,83,167,
206,157,59,7,106,189,153,49,195,30,163,116,242,112,143,197,98,49,16,8,68,34,145,149,149,149,82,169,84,44,22,211,233,52,128,14,89,32,103,147,144,224,206,196,109,18,48,119,48,24,148,178,106,146,197,161,
50,102,72,93,240,130,205,25,248,209,143,126,244,166,155,110,170,86,171,247,220,115,207,228,228,228,149,43,87,104,193,145,42,132,141,46,20,10,166,105,174,215,235,215,92,115,205,61,247,220,195,10,64,89,
133,207,248,134,49,31,87,7,161,42,130,149,14,67,112,46,24,12,118,117,117,209,71,54,23,206,90,146,213,171,174,199,181,219,104,211,158,218,164,254,168,80,214,236,10,109,220,103,75,35,46,215,47,139,188,205,
234,65,105,211,77,242,9,223,161,190,29,182,70,234,160,41,111,20,14,41,30,156,244,63,86,181,111,241,120,156,116,201,229,229,101,89,186,172,144,61,170,21,209,248,202,172,12,229,42,233,6,73,232,89,94,140,
26,79,79,51,21,62,105,146,86,53,205,233,116,250,169,167,158,58,122,244,40,51,126,180,206,84,114,193,127,149,237,166,122,28,179,121,249,124,254,207,254,236,207,62,241,137,79,152,196,70,238,93,82,8,116,
112,112,16,17,168,92,117,141,70,227,220,185,115,167,79,159,142,199,227,219,182,109,235,233,233,97,200,35,39,89,173,86,139,197,98,239,124,231,59,191,255,253,239,159,61,123,86,77,59,32,176,150,122,158,216,
27,0,143,152,101,126,140,140,80,10,8,206,131,252,36,10,85,105,164,188,94,239,242,242,178,215,235,197,127,251,250,250,210,233,180,101,197,96,54,155,77,167,211,48,4,40,101,140,68,34,38,234,141,235,156,153,
153,193,140,92,89,89,57,115,230,204,229,203,151,201,125,6,44,64,115,12,251,133,205,64,169,27,242,228,149,74,37,151,203,1,34,40,20,10,36,114,152,62,145,41,86,103,46,87,162,216,212,93,161,244,34,76,97,36,
18,129,79,180,178,178,178,178,178,82,40,20,100,102,210,156,129,55,222,120,227,199,62,246,49,26,211,187,239,190,251,115,159,251,28,85,71,232,53,211,250,155,6,250,131,31,252,160,98,130,75,94,51,119,17,84,
147,194,202,171,220,50,51,132,114,237,180,181,181,89,166,239,77,235,188,22,27,189,198,131,164,201,181,216,104,155,215,50,69,111,230,175,76,247,217,210,86,88,150,102,200,13,187,153,7,221,204,25,151,14,
190,230,60,120,60,74,117,68,49,17,97,109,36,127,201,102,24,189,94,111,44,22,131,253,205,231,243,153,76,198,44,204,145,18,28,102,14,140,175,101,245,131,28,76,101,238,149,179,213,20,226,104,6,81,89,210,
68,126,252,227,31,255,239,255,254,175,194,154,233,20,115,150,19,208,144,110,181,242,160,241,239,183,190,245,173,15,124,224,3,189,189,189,170,236,202,100,116,224,194,126,225,23,126,225,200,145,35,211,211,
211,42,116,133,106,210,83,79,61,229,118,187,55,108,216,176,109,219,54,96,199,196,10,177,198,64,145,14,4,2,199,143,31,231,34,68,202,213,146,27,139,137,72,242,150,41,203,11,42,219,198,141,27,205,216,80,
205,123,249,92,241,186,181,181,53,30,143,195,64,75,161,9,133,102,150,74,37,16,72,74,165,82,56,28,6,241,70,86,117,22,139,69,24,232,43,87,174,92,186,116,137,149,235,152,214,200,161,209,64,195,47,224,208,
89,210,69,240,69,184,246,18,5,90,35,38,166,168,72,38,214,166,18,158,233,116,122,120,120,216,198,40,203,105,25,139,197,190,249,205,111,98,225,193,22,119,116,116,28,62,124,248,139,95,252,34,220,103,137,
228,120,189,94,16,179,24,249,214,106,181,91,111,189,117,255,254,253,242,77,218,110,10,117,170,205,219,235,245,98,135,198,227,163,239,204,143,129,19,165,56,130,202,114,89,38,6,109,0,223,181,56,125,24,189,
106,181,138,210,196,181,83,238,154,9,85,218,51,222,44,11,97,86,61,40,13,234,112,56,46,95,190,172,100,102,237,79,21,8,4,144,23,65,96,23,12,6,57,236,161,80,136,114,225,224,212,58,28,142,147,39,79,42,239,
129,80,27,228,37,154,253,16,170,186,97,229,150,150,150,76,36,93,17,57,232,71,75,248,2,51,4,40,182,10,121,205,170,5,147,193,105,103,160,237,49,245,114,185,124,242,228,201,99,199,142,229,114,57,153,244,
147,204,54,249,38,223,135,163,4,131,46,49,101,222,152,203,229,250,220,231,62,247,200,35,143,240,177,169,106,58,101,160,3,129,192,251,222,247,190,143,127,252,227,138,145,74,91,92,40,20,78,158,60,249,194,
11,47,180,183,183,111,223,190,189,175,175,79,105,217,56,28,142,3,7,14,180,183,183,63,249,228,147,208,217,80,174,80,51,123,132,168,202,28,162,141,27,55,74,154,90,51,254,169,180,125,184,253,235,174,187,
14,70,208,50,154,49,51,224,62,159,47,151,203,193,173,6,43,62,149,74,5,2,129,145,145,145,225,225,225,225,225,97,20,13,74,224,27,62,53,125,103,164,10,17,0,74,248,213,4,133,97,214,101,220,96,22,113,189,214,
131,112,129,244,106,65,156,183,119,153,229,127,191,249,205,111,38,18,9,26,98,220,200,158,61,123,78,159,62,253,211,159,254,84,122,208,100,19,42,91,252,71,127,244,71,146,220,41,125,103,124,210,148,52,192,
46,94,42,149,86,86,86,224,95,115,163,69,253,170,165,186,133,18,18,177,129,62,95,199,168,114,46,165,211,233,98,177,104,105,160,87,77,254,55,243,232,233,78,53,35,240,173,101,135,150,95,241,122,189,229,114,
57,159,207,111,218,180,9,171,190,167,167,7,153,52,167,211,137,202,56,238,148,173,173,173,124,178,84,86,1,161,8,123,176,114,146,84,205,78,51,228,221,134,57,19,10,133,192,14,168,215,235,11,11,11,74,207,
68,106,19,42,196,217,132,185,157,78,231,197,139,23,161,199,31,143,199,205,130,111,122,99,146,52,133,89,215,84,81,211,94,246,240,204,153,51,199,142,29,67,143,3,73,158,147,20,58,211,100,243,175,140,53,8,
174,75,15,218,229,114,125,235,91,223,186,235,174,187,246,237,219,71,34,61,215,128,165,124,229,230,205,155,239,186,235,174,199,30,123,76,101,231,85,183,139,241,241,241,209,209,209,96,48,184,105,211,166,
109,219,182,65,149,138,62,227,186,117,235,14,29,58,116,234,212,169,98,177,200,241,181,220,159,148,20,142,41,249,230,247,251,45,251,119,40,95,67,98,124,68,66,179,217,172,204,108,152,14,184,124,34,176,209,
80,50,42,20,10,133,66,97,110,110,110,116,116,244,194,133,11,160,139,152,147,0,7,99,127,118,217,160,184,160,170,47,231,145,207,231,115,185,156,116,18,155,229,220,215,152,180,104,52,26,165,82,201,148,159,
95,123,125,23,161,103,133,167,227,197,219,223,254,246,75,151,46,141,140,140,224,78,185,13,200,76,58,192,141,190,190,62,54,94,224,39,165,19,221,204,77,65,215,155,74,165,66,71,44,26,141,70,163,209,85,19,
122,107,65,14,45,97,132,85,211,122,197,98,17,163,58,51,51,131,26,69,85,28,180,22,218,178,165,163,205,66,140,215,186,115,88,138,17,98,234,174,95,191,254,35,31,249,136,37,69,157,83,148,204,34,105,28,165,
9,150,97,138,89,173,215,204,73,146,169,93,115,240,41,108,4,45,7,27,36,74,57,109,170,32,128,33,111,185,92,94,92,92,196,156,105,105,105,65,37,96,60,30,143,68,34,166,31,70,62,130,251,15,254,224,15,154,113,
105,29,86,237,39,70,71,71,127,244,163,31,189,252,242,203,212,208,50,67,117,85,12,230,16,50,146,178,211,4,29,58,203,91,29,27,27,187,235,174,187,28,175,200,193,72,206,163,101,44,182,125,251,246,35,71,142,
44,46,46,74,36,90,69,178,120,81,42,149,198,198,198,94,120,225,5,32,191,216,168,81,206,224,247,251,193,145,144,154,179,114,40,88,212,167,34,29,147,103,66,218,163,189,123,194,178,40,151,203,21,14,135,239,
187,239,190,197,197,69,75,182,128,34,225,74,15,139,96,220,252,252,252,249,243,231,47,94,188,152,207,231,11,133,2,100,248,249,164,232,72,130,107,72,36,26,81,161,4,160,213,38,132,127,151,150,150,76,9,49,
27,211,105,159,47,146,21,210,150,241,25,102,179,201,158,150,111,30,58,116,232,11,95,248,2,73,205,116,150,249,98,104,104,232,167,63,253,169,212,30,33,140,131,157,41,20,10,253,205,223,252,13,136,237,210,
190,19,170,198,209,217,217,105,67,94,34,65,37,145,72,32,172,94,149,99,187,42,101,216,82,114,211,126,168,177,247,44,45,45,1,209,42,149,74,173,173,173,170,70,70,141,146,66,180,204,70,57,150,21,216,175,117,
39,110,246,4,145,33,92,88,88,48,37,206,101,35,17,69,195,192,11,108,66,210,254,72,78,45,189,70,80,47,154,165,28,155,37,156,145,18,119,187,221,133,66,65,42,106,201,159,112,216,234,86,91,254,151,104,126,
173,86,203,100,50,115,115,115,19,19,19,19,19,19,139,139,139,144,79,32,125,0,95,76,36,18,30,147,39,216,12,140,94,88,88,56,125,250,244,252,252,60,203,19,233,35,99,152,20,169,14,219,38,71,74,14,28,121,163,
228,0,72,63,26,246,238,249,231,159,127,238,185,231,174,191,254,122,126,198,82,77,88,122,211,191,245,91,191,245,129,15,124,64,113,123,229,107,165,193,116,238,220,185,179,103,207,38,147,201,237,219,183,
111,219,182,173,181,181,53,155,205,122,60,158,13,27,54,68,34,145,209,209,81,217,96,69,82,211,77,252,7,8,59,107,190,231,231,231,81,156,102,174,73,21,40,73,63,122,255,254,253,80,141,105,166,96,101,105,184,
225,104,148,203,229,133,133,133,76,38,3,126,5,63,80,169,84,0,185,74,229,79,214,205,171,253,198,220,98,121,131,192,55,94,43,211,203,116,52,94,211,97,35,225,6,232,249,27,223,248,134,204,249,152,162,72,177,
88,236,189,239,125,239,103,62,243,25,115,62,192,162,125,248,195,31,134,238,149,252,0,97,31,66,115,171,102,228,252,126,127,40,20,106,150,20,53,111,4,99,190,170,204,136,41,49,220,108,24,113,22,78,136,62,
0,0,32,0,73,68,65,84,25,181,90,45,151,203,17,57,93,92,92,68,189,98,179,11,224,221,209,109,66,141,18,133,36,105,146,20,125,240,117,68,75,150,0,151,233,26,219,63,116,201,230,226,229,89,38,6,41,73,26,14,
135,1,195,154,147,176,89,232,134,216,186,82,169,64,56,179,89,88,35,209,12,89,103,192,32,73,254,156,74,164,209,158,32,13,62,51,51,195,110,0,173,173,173,189,189,189,109,109,109,225,112,216,253,123,191,247,
123,166,117,86,189,47,151,151,151,207,156,57,115,241,226,69,226,143,202,167,147,77,34,164,139,39,121,39,38,55,64,70,46,14,43,185,244,231,158,123,238,125,239,123,31,79,98,9,197,200,135,10,198,226,241,227,
199,165,203,108,137,117,72,99,157,207,231,135,135,135,79,157,58,149,201,100,66,161,16,194,153,80,40,20,141,70,33,178,99,18,72,45,211,104,80,187,231,212,169,84,42,208,63,147,179,220,210,13,225,95,223,243,
158,247,16,112,48,113,6,203,5,140,158,85,40,39,133,13,133,170,28,253,68,250,29,40,229,64,112,80,171,213,0,246,17,181,52,91,180,168,215,200,59,173,221,164,90,118,249,91,251,122,86,30,180,229,79,124,231,
59,223,217,178,101,139,165,105,150,190,112,44,22,171,86,171,231,206,157,83,57,100,52,192,253,187,191,251,59,34,27,18,30,1,58,143,48,28,43,28,220,21,150,38,210,180,113,113,154,74,26,150,5,95,150,169,161,
102,6,215,62,161,167,172,173,211,233,204,100,50,172,189,194,226,111,107,107,179,201,254,153,138,248,60,27,100,97,138,197,34,40,249,144,149,128,132,27,126,194,94,66,186,89,196,192,223,66,76,115,238,220,
57,244,138,83,246,132,27,24,41,31,210,137,230,50,81,36,2,115,173,53,26,141,197,197,69,89,80,38,7,161,89,115,22,191,223,239,247,251,231,231,231,229,83,80,92,195,181,196,199,38,35,158,4,109,75,149,74,148,
242,206,206,206,94,186,116,233,220,185,115,231,206,157,115,163,116,74,198,17,140,122,144,23,122,249,229,151,145,107,50,213,94,28,70,9,153,52,124,242,156,28,98,249,21,76,116,155,118,56,153,76,166,167,167,
103,219,182,109,14,171,206,102,106,246,99,56,174,186,234,170,103,158,121,6,124,114,86,244,214,95,125,168,135,141,175,151,74,165,145,145,145,82,169,4,77,28,184,12,241,120,28,141,69,148,39,104,94,173,219,
237,222,180,105,83,107,107,43,123,36,22,139,69,116,202,112,54,57,28,175,110,110,237,118,187,63,244,161,15,141,141,141,201,192,83,102,225,76,69,14,108,188,179,179,179,100,43,206,205,205,97,238,178,24,140,
207,148,49,62,167,254,202,202,10,192,107,217,231,80,177,74,184,150,50,153,204,218,77,173,13,117,97,141,71,169,84,130,90,88,51,191,242,163,31,253,232,175,254,234,175,170,196,145,122,65,222,244,186,117,
235,70,70,70,38,39,39,85,68,245,79,255,244,79,189,189,189,205,78,130,70,10,216,201,240,38,4,193,243,249,124,58,157,94,90,90,154,153,153,225,79,160,188,83,22,70,170,201,105,182,250,116,188,90,85,217,134,
56,108,111,8,164,90,63,102,190,164,147,67,203,212,102,31,101,117,149,92,203,100,37,74,237,39,4,82,192,205,208,29,77,41,208,175,221,76,115,30,158,58,117,74,161,25,74,136,21,43,17,89,19,218,50,18,67,21,
107,64,185,65,48,169,11,11,11,178,29,184,84,193,182,76,68,163,60,13,171,67,157,202,126,155,52,171,114,76,155,102,22,115,91,150,62,65,210,185,90,173,186,31,126,248,97,2,49,210,244,148,74,165,201,201,201,
177,177,49,185,33,51,77,169,106,25,76,101,47,105,206,76,242,22,1,98,76,107,185,115,170,239,158,57,115,230,151,126,233,151,192,34,148,225,149,66,102,100,135,142,29,59,118,160,51,150,138,91,77,136,195,108,
219,113,227,141,55,74,12,200,237,118,67,194,181,80,40,168,100,145,242,55,7,7,7,227,241,56,108,58,42,12,193,23,134,255,162,140,178,202,134,227,105,29,60,120,112,112,112,112,121,121,153,198,148,30,43,63,
207,241,169,213,106,75,75,75,19,19,19,112,135,225,187,229,114,57,180,212,148,69,174,8,0,233,244,113,144,131,193,32,245,160,145,93,164,100,43,186,59,126,226,19,159,184,254,250,235,81,255,230,245,122,175,
92,185,226,248,255,241,176,241,160,29,14,199,141,55,222,248,232,163,143,154,136,170,165,141,198,127,55,109,218,116,244,232,81,36,57,49,56,215,93,119,221,67,15,61,212,12,191,70,1,39,187,19,40,114,52,61,
107,76,69,184,213,24,70,164,254,149,245,180,241,37,215,78,128,115,52,41,228,163,117,70,176,172,54,87,233,68,219,236,13,230,26,148,49,1,151,173,100,88,214,106,181,124,62,143,81,122,173,108,19,76,233,90,
173,246,210,75,47,41,153,70,26,7,201,114,1,65,158,33,142,204,120,43,124,89,29,104,85,33,251,100,74,39,192,12,10,57,56,204,250,218,243,255,86,5,100,204,244,190,52,208,166,117,230,146,143,199,227,129,64,
192,253,240,195,15,43,91,3,31,123,120,120,24,93,145,36,62,229,16,189,136,76,63,75,37,178,248,25,185,221,201,47,98,241,52,235,120,143,95,73,167,211,30,143,103,239,222,189,42,96,148,59,132,26,20,8,3,158,
62,125,154,18,183,18,220,48,27,94,240,191,241,120,124,239,222,189,204,216,146,136,158,72,36,98,177,88,38,147,145,55,34,111,188,171,171,171,163,163,131,37,67,177,88,12,5,251,208,66,194,50,86,17,37,159,
16,247,131,251,238,187,15,54,157,214,89,166,58,233,167,163,245,239,252,252,252,210,210,18,111,10,57,174,185,185,57,122,223,106,59,145,204,95,8,81,33,53,42,55,75,184,129,72,86,236,216,177,227,150,91,110,
105,107,107,219,177,99,199,190,125,251,110,191,253,246,247,191,255,253,135,14,29,58,112,224,192,192,192,64,52,26,245,249,124,54,6,244,255,212,64,199,98,177,103,159,125,54,16,8,216,155,102,245,194,225,
112,172,91,183,238,216,177,99,168,181,169,215,235,255,252,207,255,220,214,214,166,80,17,252,215,231,243,145,227,37,107,11,233,163,160,243,25,171,141,100,13,39,122,23,41,49,29,51,227,106,9,122,40,162,149,
165,225,48,251,94,242,235,18,134,146,63,13,39,218,198,245,179,148,13,144,122,132,164,171,170,29,2,77,121,18,137,196,107,229,2,210,137,110,107,107,131,130,38,250,35,75,239,88,130,227,172,219,4,252,69,111,
195,44,215,48,155,171,193,223,55,161,9,106,224,153,254,47,235,141,237,147,126,171,190,105,73,243,48,13,180,201,173,128,80,159,219,237,246,200,169,3,4,115,126,126,158,118,83,138,160,171,242,24,148,174,
226,77,196,215,236,37,42,211,134,164,145,145,76,198,90,21,196,131,234,49,80,152,31,118,196,237,118,127,241,139,95,124,207,123,222,131,114,44,14,58,204,144,137,10,225,197,125,247,221,247,226,139,47,190,
248,226,139,104,182,102,182,180,96,66,82,174,189,27,110,184,193,33,250,68,200,148,110,52,26,13,6,131,23,46,92,96,70,152,223,74,36,18,74,92,31,52,190,75,151,46,213,235,245,137,137,137,100,50,73,78,180,
52,205,50,209,236,112,56,246,236,217,115,228,200,17,83,133,135,108,113,199,43,26,20,43,43,43,232,37,44,167,102,46,151,35,142,36,83,31,108,123,168,184,25,114,191,84,241,19,154,66,201,190,86,120,177,113,
227,198,141,27,55,30,60,120,144,79,225,216,177,99,83,83,83,147,147,147,199,142,29,155,156,156,180,44,9,123,29,135,233,236,200,133,244,248,227,143,227,242,44,169,117,54,102,26,213,43,95,254,242,151,27,
141,198,61,247,220,179,99,199,14,201,143,230,191,232,187,44,99,62,156,22,19,198,235,245,146,215,207,245,134,24,156,105,186,165,165,37,62,116,9,113,52,19,35,195,154,156,154,154,114,187,221,201,100,18,102,
200,230,147,18,177,149,109,54,65,172,148,25,42,2,95,148,54,53,57,103,106,34,73,191,65,82,59,192,154,88,149,168,176,70,235,76,31,11,210,243,169,84,170,94,175,111,216,176,1,247,181,180,180,4,91,132,160,
144,32,50,22,163,215,235,205,100,50,203,203,203,102,46,71,181,52,228,189,192,251,150,188,50,147,220,105,169,87,110,38,231,204,112,65,38,6,101,245,160,121,49,242,217,201,38,112,38,83,131,220,106,15,159,
244,226,226,226,244,244,52,133,131,29,205,43,238,121,82,150,147,195,52,72,82,7,95,112,199,48,109,52,184,101,164,112,16,8,195,104,146,13,146,207,231,63,255,249,207,255,238,239,254,174,4,55,45,133,31,229,
144,61,248,224,131,31,253,232,71,61,30,15,100,215,41,3,40,243,212,18,10,104,52,26,215,94,123,237,204,204,12,215,21,110,10,237,248,42,149,74,42,149,218,186,117,107,48,24,68,176,207,196,224,250,245,235,
213,224,130,188,5,27,141,229,209,213,213,101,178,151,232,191,163,176,165,80,40,80,94,195,33,116,65,41,72,132,249,4,247,89,34,236,110,183,187,82,169,160,188,133,139,77,130,251,82,181,131,180,4,214,82,154,
129,109,163,209,216,190,125,187,156,9,205,168,87,187,118,237,218,181,107,23,58,243,98,147,184,112,225,194,133,11,23,38,39,39,241,162,89,43,163,215,77,212,3,235,121,85,112,163,153,225,222,189,123,247,153,
51,103,206,159,63,255,240,195,15,75,187,76,53,146,104,52,170,210,48,28,82,56,206,106,172,164,92,53,233,4,72,214,69,163,81,213,105,219,36,240,240,223,203,151,47,231,114,185,171,175,190,26,30,34,108,180,
217,18,76,78,51,224,170,84,145,135,42,183,242,208,121,241,249,124,30,145,156,233,2,91,66,171,42,139,128,232,202,242,121,217,147,190,155,1,235,210,39,48,45,84,75,75,139,199,227,233,232,232,160,195,81,44,
22,23,22,22,178,217,44,216,105,144,235,130,106,190,67,180,88,52,145,67,156,25,184,147,116,153,237,139,84,109,88,225,205,108,180,217,40,195,236,100,175,72,83,230,189,203,62,179,63,51,134,208,60,155,157,
157,69,3,86,137,120,54,187,92,108,212,112,114,57,10,170,139,45,227,35,26,110,85,186,34,133,40,149,208,29,233,95,252,240,151,190,244,165,119,191,251,221,61,61,61,88,0,178,245,181,233,65,227,205,158,158,
158,183,188,229,45,95,255,250,215,59,58,58,38,38,38,136,56,163,196,147,57,7,14,250,53,215,92,131,184,85,245,70,193,155,116,150,175,190,250,234,104,52,122,254,252,121,244,61,89,191,126,189,244,142,233,
23,128,212,60,52,52,116,233,210,165,185,185,185,150,150,150,64,32,32,247,76,133,74,191,233,77,111,26,29,29,37,187,75,181,215,226,227,47,22,139,64,54,36,182,30,143,199,51,153,140,223,239,39,62,40,109,52,
208,82,41,127,172,178,184,18,44,226,35,70,147,117,51,233,97,153,225,228,139,96,48,72,147,141,3,52,207,35,71,142,92,186,116,105,108,108,236,217,103,159,149,14,20,5,61,28,66,156,204,36,243,241,170,32,184,
129,88,205,222,16,219,188,56,124,248,240,225,195,135,251,251,251,165,218,42,246,108,212,254,154,193,150,196,64,77,199,74,238,91,82,247,50,151,203,169,250,123,75,58,115,189,94,63,115,230,76,165,82,217,
188,121,51,245,240,240,67,210,113,81,48,160,68,26,241,25,172,95,26,86,9,49,123,60,30,24,104,179,32,214,172,198,50,227,122,140,155,101,81,146,203,229,66,157,197,107,242,157,229,245,91,162,186,136,206,81,
2,70,251,0,36,164,189,189,125,221,186,117,8,23,114,185,220,232,232,232,153,51,103,114,185,28,187,206,91,214,4,2,80,134,84,22,158,187,89,92,166,220,80,75,137,84,73,146,91,245,126,149,234,147,244,65,37,
237,196,146,151,73,136,204,19,10,133,134,135,135,29,175,72,189,200,96,71,46,90,218,86,233,93,74,4,67,126,69,230,178,100,1,183,242,160,241,36,232,33,58,94,209,58,145,66,75,52,226,159,255,252,231,255,248,
143,255,152,126,129,228,111,202,25,192,46,209,243,243,243,103,206,156,65,193,136,219,237,190,124,249,50,123,77,210,184,83,220,174,209,104,188,225,13,111,32,164,32,135,44,26,141,114,185,6,2,129,214,214,
214,158,158,158,141,27,55,62,253,244,211,137,68,2,147,94,146,139,57,255,220,110,55,253,232,217,217,217,129,129,1,75,90,59,110,249,224,193,131,79,61,245,148,100,185,72,253,82,44,60,232,222,69,34,17,224,
212,82,120,190,88,44,6,131,65,164,158,225,137,51,220,198,120,130,17,69,24,90,14,29,64,103,185,141,163,51,172,172,158,50,139,92,77,164,207,242,205,142,142,142,142,142,142,107,174,185,134,239,156,60,121,
242,202,149,43,39,78,156,56,113,226,196,149,43,87,78,157,58,181,70,32,47,22,139,61,254,248,227,14,81,146,254,250,94,36,18,137,187,239,190,91,250,206,148,45,148,228,45,9,133,73,76,67,97,107,14,163,130,
95,146,151,37,29,205,108,55,135,15,160,208,177,187,187,91,234,5,19,199,227,42,80,152,21,254,196,36,30,122,248,74,133,72,106,60,209,142,23,10,5,170,51,170,43,151,126,156,188,5,199,43,37,254,62,159,15,54,
78,41,19,133,66,161,102,173,196,87,229,119,59,172,228,156,40,223,170,122,134,89,30,126,191,127,221,186,117,29,29,29,16,54,144,131,195,44,78,185,92,14,133,66,217,108,22,89,71,200,126,34,169,107,90,103,
211,238,53,179,209,246,98,41,52,8,102,79,44,69,174,183,116,159,29,66,214,195,3,119,233,194,133,11,42,167,97,54,126,151,41,93,62,81,27,72,90,1,249,50,122,162,7,77,148,67,214,191,74,135,154,198,244,137,
39,158,120,247,187,223,189,121,243,102,52,217,83,26,125,42,168,249,206,119,190,243,196,19,79,240,2,208,144,112,120,120,88,118,33,146,95,31,24,24,216,186,117,43,154,131,200,125,8,79,180,92,46,227,74,64,
155,131,236,122,111,111,111,62,159,71,21,144,101,242,135,82,147,155,54,109,66,0,75,78,146,34,108,14,14,14,150,74,37,182,191,148,254,47,149,18,89,22,132,138,126,230,103,74,165,18,132,56,224,62,248,124,
62,175,215,27,14,135,11,133,66,54,155,197,100,229,56,16,140,43,20,10,195,195,195,146,46,34,41,86,187,119,239,38,111,84,57,98,50,121,210,204,76,219,27,238,237,219,183,239,216,177,227,206,59,239,228,59,
79,63,253,244,149,43,87,70,70,70,126,248,195,31,94,185,114,101,108,108,204,210,165,250,214,183,190,133,94,39,175,219,52,227,5,66,37,9,107,160,192,68,198,46,156,183,82,160,14,11,134,123,30,235,56,212,67,
87,209,6,70,146,54,90,218,130,82,169,52,60,60,92,40,20,66,161,80,107,107,171,217,27,155,6,87,186,234,120,208,8,52,33,180,128,38,18,202,58,179,107,31,205,68,54,155,181,228,219,113,191,177,116,12,177,79,
115,151,34,122,137,219,167,87,254,154,220,103,213,26,92,113,141,233,33,73,27,45,69,8,84,18,197,237,118,247,245,245,37,147,201,139,23,47,102,179,89,168,66,210,143,196,130,5,161,27,160,80,189,94,135,150,
131,13,206,6,44,11,170,147,150,159,49,113,103,203,42,155,80,40,228,247,251,169,30,140,239,178,7,27,35,9,51,20,163,174,178,7,205,178,34,145,8,42,26,165,170,142,108,129,161,240,41,194,32,116,159,1,29,168,
130,125,83,187,90,254,55,155,205,58,157,206,108,54,139,65,68,229,15,171,13,149,238,146,219,237,126,228,145,71,254,241,31,255,81,34,107,166,47,51,62,62,254,149,175,124,101,124,124,92,17,54,252,126,255,
246,237,219,135,135,135,209,31,76,57,74,119,221,117,87,71,71,71,34,145,200,231,243,144,60,117,188,162,7,45,27,56,65,183,158,146,255,184,230,142,142,142,76,38,51,51,51,211,236,113,6,2,129,245,235,215,79,
79,79,163,248,219,124,150,187,118,237,186,124,249,50,24,135,178,168,135,112,60,122,181,96,73,200,13,217,235,245,2,86,195,197,200,12,97,34,145,104,105,105,89,89,89,89,88,88,152,155,155,67,0,72,187,19,139,
197,90,90,90,46,92,184,160,186,78,96,76,54,110,220,168,82,17,216,128,113,102,118,35,123,173,102,90,189,195,25,114,240,224,65,36,30,255,223,255,251,127,80,221,61,121,242,228,169,83,167,198,198,198,78,159,
62,125,246,236,217,124,62,255,240,195,15,31,58,116,72,82,39,215,248,66,97,211,241,120,124,203,150,45,28,7,60,92,9,208,113,74,112,180,165,177,32,59,152,249,9,179,174,85,46,13,82,32,192,12,145,179,34,157,
78,163,217,13,210,24,54,93,84,84,66,143,11,68,226,179,210,185,1,72,34,251,213,50,168,101,206,220,252,9,153,21,148,214,153,62,53,152,66,188,59,220,154,105,241,87,181,206,14,171,134,147,252,105,186,207,
42,203,135,22,192,202,64,203,12,129,223,239,223,178,101,203,194,194,194,216,216,24,53,38,25,27,1,211,247,122,189,80,96,135,220,141,61,73,110,112,112,112,122,122,26,149,132,205,4,121,236,229,185,25,97,
116,119,119,47,46,46,146,1,169,202,130,204,147,203,141,249,103,195,209,215,215,247,210,75,47,153,56,151,2,100,85,130,146,131,171,186,104,203,74,66,254,18,145,92,122,208,116,7,170,213,106,52,26,149,178,
65,10,24,193,105,143,31,63,126,252,248,241,221,187,119,99,39,148,244,15,196,131,223,255,254,247,159,121,230,25,69,248,197,95,193,154,26,24,24,184,114,229,10,243,105,248,0,123,6,130,245,28,10,133,32,72,
159,205,102,35,145,8,113,91,204,30,184,84,196,25,161,139,20,141,70,211,233,52,96,1,216,89,181,171,65,100,46,147,201,64,192,80,29,183,221,118,219,143,127,252,99,213,200,74,250,8,185,92,46,149,74,201,106,
40,38,3,224,245,203,195,253,202,129,173,55,24,12,118,119,119,79,79,79,207,206,206,206,206,206,130,16,221,221,221,13,229,176,233,233,105,116,140,148,40,103,91,91,27,171,249,233,49,209,119,86,36,164,215,
231,74,75,1,0,229,90,70,163,209,27,110,184,129,92,145,103,158,121,230,207,255,252,207,63,242,145,143,200,146,238,53,210,54,204,143,221,112,195,13,178,182,200,241,106,249,118,94,9,35,45,211,34,200,52,23,
237,184,170,229,85,205,139,153,211,35,26,176,184,184,56,53,53,133,207,119,119,119,171,186,50,27,85,79,213,60,87,22,4,208,83,145,54,142,128,12,243,237,178,252,207,228,99,200,51,179,226,137,161,30,93,16,
124,17,152,155,189,34,241,218,117,104,205,102,149,242,235,152,210,38,207,85,177,167,193,29,158,155,155,3,21,13,75,79,33,236,244,192,76,61,13,117,181,61,61,61,225,112,24,25,172,215,84,120,69,155,67,173,
90,172,41,74,180,155,117,118,150,72,247,207,60,104,140,117,91,91,27,36,134,77,141,8,211,125,118,88,233,82,227,191,108,44,100,122,208,114,115,96,22,53,24,12,34,17,172,158,147,132,95,233,80,63,242,200,35,
95,255,250,215,185,228,232,65,143,143,143,63,249,228,147,146,222,32,213,224,128,59,227,119,7,6,6,192,172,224,163,221,183,111,31,148,131,216,77,206,231,243,165,82,169,104,52,202,122,95,106,254,86,42,21,
164,13,225,144,6,2,129,114,185,12,162,8,168,139,40,22,7,197,91,110,99,48,208,166,236,64,71,71,7,120,211,38,85,28,215,140,82,20,128,107,234,113,162,110,208,44,219,99,240,197,119,218,218,218,90,90,90,122,
123,123,103,103,103,71,70,70,122,123,123,81,122,147,74,165,226,241,248,226,226,226,204,204,12,221,138,193,193,65,26,104,80,33,73,72,146,28,199,181,96,208,205,222,177,100,50,88,170,234,204,206,206,62,250,
232,163,76,85,189,86,218,134,124,209,223,223,223,211,211,99,10,210,202,46,16,210,15,181,23,122,37,62,75,169,95,58,19,150,217,96,24,29,183,219,61,62,62,78,138,119,36,18,129,5,49,13,132,18,126,179,36,87,
40,47,24,174,162,116,62,100,251,90,120,196,210,137,86,82,206,146,74,139,117,36,183,31,217,67,22,255,178,83,223,26,181,56,100,22,221,44,55,149,77,205,45,5,252,16,176,202,122,66,75,120,218,237,118,183,182,
182,70,34,145,201,201,73,52,2,85,116,186,106,181,10,3,109,95,16,72,245,136,112,56,60,50,50,34,19,218,171,38,6,177,199,19,18,116,188,210,209,184,191,191,31,4,65,213,109,213,84,128,160,205,244,112,254,117,
116,116,64,10,78,77,77,102,42,148,111,47,173,0,61,104,165,29,42,73,93,0,197,148,65,113,58,157,237,237,237,132,65,85,46,81,57,212,110,183,251,194,133,11,255,254,239,255,126,231,157,119,210,112,172,172,
172,60,247,220,115,23,46,92,0,134,171,20,11,17,133,41,159,186,167,167,7,4,3,92,222,187,223,253,110,254,73,246,193,147,74,214,212,79,1,128,27,12,6,73,114,194,174,32,211,247,126,191,31,24,22,28,106,62,12,
244,241,114,188,186,225,197,246,237,219,175,92,185,66,247,89,89,7,152,81,52,138,85,79,20,170,8,244,170,84,91,51,69,12,130,145,2,32,211,214,214,134,115,134,195,97,92,97,50,153,132,240,200,252,252,252,242,
242,242,142,29,59,48,116,76,168,154,86,149,22,252,245,129,27,102,3,217,102,204,144,253,251,247,163,137,48,143,215,13,64,31,60,120,80,37,0,57,56,100,53,41,143,204,97,165,118,45,173,27,241,189,102,59,150,
196,115,42,149,202,19,79,60,209,214,214,134,62,56,30,143,167,189,189,93,193,214,205,176,14,230,102,204,70,186,74,109,81,198,55,178,73,38,86,71,38,147,161,78,180,178,206,50,175,5,250,166,233,195,74,127,
89,213,76,174,170,112,212,204,167,150,173,73,204,34,97,233,118,160,71,26,184,155,166,124,152,234,207,219,221,221,141,18,21,165,41,10,71,196,172,252,110,118,241,161,80,104,243,230,205,99,99,99,168,62,91,
227,129,60,135,244,105,72,250,142,197,98,203,203,203,8,71,76,187,10,31,17,207,162,88,44,122,8,213,251,124,190,246,246,246,169,169,41,51,136,160,212,131,196,40,84,182,87,162,251,228,132,203,190,42,50,95,
193,111,129,240,200,4,177,156,85,82,63,90,218,232,127,248,135,127,56,124,248,48,62,57,54,54,6,178,45,224,5,85,25,232,114,185,66,161,144,146,57,197,159,32,184,49,50,50,178,115,231,206,142,142,14,102,29,
21,237,79,46,84,68,88,56,27,144,95,72,8,229,243,121,89,62,35,193,41,2,235,146,38,145,74,165,230,231,231,93,46,215,220,220,220,204,204,204,135,62,244,161,23,94,120,65,2,208,124,90,82,55,67,210,54,113,242,
153,153,25,73,118,86,173,34,36,71,202,84,245,131,100,48,61,62,228,0,60,30,79,44,22,195,214,194,148,96,51,32,2,33,240,218,233,28,210,163,148,124,53,75,175,153,175,253,126,127,87,87,151,34,35,59,68,115,
219,181,219,232,29,59,118,196,98,49,165,90,41,181,98,212,68,53,215,188,162,51,203,59,98,247,9,203,36,48,142,108,54,251,196,19,79,204,204,204,12,15,15,95,115,205,53,145,72,164,189,189,93,10,129,169,148,
172,68,78,148,147,43,129,5,38,172,56,253,76,45,1,166,157,145,90,84,60,107,199,171,165,162,129,198,152,174,58,118,20,198,133,16,139,120,29,221,165,155,169,135,171,125,162,153,135,11,54,58,46,99,213,231,
229,245,122,163,209,104,62,159,103,39,73,26,232,102,142,179,12,86,28,162,3,11,20,46,109,4,15,164,31,195,56,70,70,159,124,94,160,120,163,0,199,4,178,121,95,213,106,181,84,42,121,36,145,185,163,163,99,97,
97,65,149,75,40,121,86,41,68,141,68,162,212,193,96,73,133,116,69,153,238,163,89,135,40,115,52,26,141,68,34,4,148,37,160,161,216,120,242,205,153,153,153,191,255,251,191,127,231,59,223,249,147,159,252,164,
209,104,224,36,129,64,32,159,207,47,44,44,44,45,45,225,122,188,94,47,54,49,243,225,225,70,146,201,164,203,229,122,211,155,222,36,239,136,241,160,217,8,21,49,11,158,52,179,16,203,203,203,100,89,168,8,142,
7,100,166,97,100,129,126,120,60,30,72,238,37,147,201,91,110,185,5,189,96,148,83,32,9,185,232,173,37,67,150,108,54,75,64,80,126,139,23,134,124,136,108,62,47,205,52,212,253,81,137,238,120,181,246,110,111,
111,47,251,6,169,78,175,202,248,98,2,172,106,145,217,114,129,185,105,169,15,217,204,113,198,45,200,203,147,85,215,48,82,14,209,73,214,222,70,187,92,174,235,175,191,94,37,135,149,129,174,84,42,32,140,171,
201,111,230,93,84,242,253,231,9,119,143,71,162,127,114,40,230,231,231,191,246,181,175,225,145,213,235,245,23,94,120,225,150,91,110,129,28,138,73,211,84,99,40,227,45,174,94,76,69,250,182,178,107,162,195,
74,223,85,129,54,150,238,45,191,5,142,129,89,247,8,130,26,249,9,142,181,245,16,176,41,253,224,5,40,112,67,157,214,180,233,88,218,74,138,207,97,165,52,137,189,4,248,45,108,52,164,114,86,245,250,73,160,
226,209,217,217,25,143,199,207,157,59,199,146,145,102,12,57,9,110,88,150,200,54,26,13,52,128,158,157,157,85,120,139,92,203,78,167,211,163,30,100,79,79,207,229,203,151,205,39,173,10,37,149,54,54,169,63,
102,255,42,213,42,133,239,251,124,62,20,236,242,12,210,101,150,70,153,223,229,191,95,254,242,151,61,30,79,111,111,47,154,89,112,75,111,111,111,143,70,163,75,75,75,185,92,14,187,189,90,141,74,173,169,173,
173,237,23,127,241,23,161,159,203,167,162,224,45,142,23,24,148,88,246,0,52,102,103,103,165,158,11,83,70,150,37,164,160,69,7,131,65,216,208,174,174,174,241,241,241,59,238,184,227,244,233,211,148,101,49,
183,67,169,130,194,57,141,186,65,75,181,104,249,116,97,119,232,83,179,207,147,236,24,75,6,33,254,20,137,68,164,33,195,109,202,94,171,202,28,203,114,112,211,70,195,55,167,168,136,156,157,210,64,91,90,106,
84,250,56,94,45,200,103,202,198,130,94,194,217,2,232,223,4,169,175,185,230,26,191,223,47,235,116,44,157,104,176,178,36,5,83,114,27,148,90,130,57,38,74,243,158,38,245,252,249,243,79,63,253,180,12,19,177,
56,139,197,162,164,223,73,172,131,169,69,158,159,219,192,207,75,24,60,30,32,30,205,104,185,166,112,135,234,95,101,227,63,42,240,132,65,36,253,80,201,86,94,187,60,180,73,37,52,11,237,84,195,160,102,5,62,
166,63,110,163,112,139,49,119,185,92,179,179,179,102,48,218,12,81,81,29,251,144,114,220,181,107,215,185,115,231,192,109,181,204,235,34,195,108,233,251,115,244,104,21,59,58,58,202,229,50,250,169,74,7,17,
4,217,104,52,234,81,150,27,14,41,162,0,83,233,67,85,34,202,164,31,139,179,73,54,144,212,58,5,43,163,126,68,129,206,252,138,172,221,84,223,194,28,205,231,243,231,207,159,223,181,107,23,61,56,198,116,62,
159,175,179,179,211,231,243,45,47,47,163,183,128,210,93,149,181,221,7,14,28,128,221,204,231,243,170,209,173,73,130,145,254,184,199,227,129,252,166,201,243,83,61,253,228,216,210,251,11,4,2,3,3,3,193,96,
240,13,111,120,3,122,83,41,117,27,165,60,37,173,36,92,0,66,34,166,141,150,82,3,168,97,97,13,33,88,210,126,191,31,6,154,27,18,94,247,247,247,199,227,113,208,105,164,218,3,219,113,153,254,50,74,179,84,68,
47,121,211,216,35,85,135,7,179,99,153,89,68,30,143,199,101,46,219,236,226,170,196,190,97,50,144,191,5,112,79,99,29,10,133,246,237,219,103,105,148,205,243,99,10,73,45,27,69,11,83,21,7,150,114,148,210,125,
57,125,250,244,143,127,252,99,204,67,198,203,123,246,236,105,52,26,128,71,193,84,147,182,216,68,147,121,114,89,64,107,22,55,91,154,90,203,94,221,150,6,186,25,254,32,13,16,253,36,83,238,103,141,57,52,75,
217,213,215,10,149,32,18,109,38,62,165,114,48,252,152,199,227,65,174,111,237,237,108,216,172,64,82,224,119,238,220,57,58,58,58,58,58,106,105,214,37,203,203,236,15,199,251,37,196,143,228,97,58,157,94,88,
88,224,215,1,67,13,14,14,122,204,56,162,187,187,251,252,249,243,205,70,77,110,110,220,7,100,99,20,166,92,232,240,202,118,177,146,113,41,251,239,90,162,28,138,37,66,241,98,151,203,245,63,255,243,63,111,
124,227,27,193,90,147,86,30,76,184,74,165,130,106,253,149,149,149,185,185,57,26,83,165,186,119,251,237,183,227,170,66,161,16,122,46,16,131,150,219,56,123,26,33,53,231,118,187,65,122,103,45,34,81,14,174,
40,217,251,142,136,146,12,243,157,78,103,87,87,215,155,223,252,230,143,125,236,99,180,182,138,194,193,209,150,68,87,84,184,54,155,247,74,112,93,138,180,65,28,18,47,48,74,145,72,4,86,201,239,247,15,14,
14,162,222,1,111,154,172,50,210,34,149,243,139,45,217,76,247,145,143,200,167,204,92,182,212,220,177,180,209,84,177,48,177,8,10,101,52,243,169,49,33,97,100,97,172,15,29,58,164,208,45,213,11,77,250,227,
120,190,10,233,178,36,141,97,227,193,15,153,228,110,28,63,250,209,143,46,92,184,160,196,149,134,134,134,48,200,46,151,107,101,101,5,202,45,178,193,133,68,54,36,253,89,230,111,240,56,100,47,208,181,39,
235,154,185,189,54,221,185,100,225,95,54,155,133,114,217,235,0,160,45,85,125,212,32,19,171,145,79,77,86,84,161,109,2,228,159,84,254,95,146,14,161,133,221,214,214,6,135,20,166,227,195,31,254,240,133,11,
23,16,124,240,240,251,253,160,12,226,209,179,230,64,5,133,0,238,177,241,247,247,247,71,34,145,11,23,46,168,112,185,89,183,95,150,215,169,237,16,6,199,227,241,36,18,137,72,36,2,101,84,236,61,235,214,173,
139,197,98,30,243,217,4,131,193,84,42,5,185,244,102,66,45,156,142,180,209,24,44,156,186,153,133,149,244,103,74,121,208,118,203,202,102,165,173,1,216,151,78,31,206,240,228,147,79,254,242,47,255,178,252,
48,42,65,104,58,49,166,29,29,29,208,104,94,88,88,144,160,199,174,93,187,208,42,24,63,129,53,131,5,67,236,73,225,74,108,195,138,122,22,126,140,133,145,180,206,204,25,210,9,53,85,196,156,78,231,195,15,63,
124,241,226,197,100,50,9,213,105,83,175,21,128,32,130,18,12,59,192,13,229,44,88,230,12,56,167,101,197,32,163,254,114,185,12,18,72,127,127,255,150,45,91,136,154,117,116,116,152,28,38,114,111,73,71,149,
143,213,4,97,248,64,25,152,211,28,160,222,193,134,111,7,237,64,14,172,229,193,80,198,6,0,193,37,245,244,244,12,14,14,170,53,220,236,5,54,120,176,116,164,158,148,105,221,112,119,50,49,168,64,231,74,165,
242,163,31,253,232,202,149,43,244,84,128,246,196,227,113,16,61,57,49,0,121,193,71,227,147,149,123,158,44,66,193,98,230,238,37,215,249,218,157,104,26,125,249,45,27,144,132,51,170,84,42,229,114,185,149,
149,21,213,161,241,53,9,218,169,43,129,157,181,217,27,212,235,98,177,72,26,134,37,37,23,252,63,9,230,200,100,210,255,252,207,255,32,85,128,97,164,141,86,129,184,101,96,199,20,37,46,35,149,74,65,123,139,
32,178,73,233,51,205,166,148,14,86,110,174,207,231,219,176,97,195,194,194,194,200,200,72,42,149,234,236,236,116,185,92,238,135,30,122,200,20,56,247,120,60,20,29,85,178,68,14,43,33,90,94,150,98,192,56,
140,150,43,42,114,52,15,51,167,135,50,104,254,34,193,175,209,209,209,253,251,247,179,117,19,138,118,76,178,20,229,213,99,177,24,140,44,60,214,183,191,253,237,157,157,157,74,72,144,116,11,21,130,1,232,
196,23,211,233,180,10,210,29,70,75,74,229,134,51,74,80,89,32,16,153,207,157,59,247,226,139,47,206,204,204,192,52,208,47,32,83,144,65,83,62,159,95,89,89,145,1,126,51,31,83,117,126,146,175,37,154,185,107,
215,174,190,190,190,82,169,148,207,231,75,165,82,44,22,27,26,26,82,198,75,238,1,74,111,132,115,3,13,119,248,21,162,4,210,3,162,254,159,154,15,170,217,4,148,181,73,31,146,174,174,84,7,181,124,193,148,32,
168,65,168,76,1,209,216,114,98,144,77,47,81,96,88,34,184,75,150,206,190,204,43,160,233,176,98,16,150,203,229,71,31,125,116,124,124,156,60,69,214,52,237,221,187,215,36,174,96,78,178,212,144,157,19,76,75,
129,108,179,37,249,193,18,83,110,102,230,84,109,139,101,226,78,214,140,128,246,131,175,96,18,58,94,173,107,188,170,141,54,147,147,107,105,197,162,46,166,90,173,170,202,44,19,158,230,6,166,234,54,112,13,
111,125,235,91,183,108,217,82,169,84,198,199,199,233,47,43,41,55,37,238,166,24,101,76,122,99,79,237,232,232,40,22,139,102,229,139,130,89,236,107,14,137,117,32,154,223,177,99,199,13,55,220,48,53,53,245,
179,142,42,114,33,201,158,199,203,203,203,232,39,95,42,149,208,233,39,159,207,163,9,233,242,242,50,68,118,80,213,142,207,160,170,66,194,91,82,139,67,37,1,28,175,238,143,37,213,215,232,69,18,66,229,25,
164,239,224,112,56,70,71,71,247,237,219,39,187,227,72,4,86,173,70,212,103,35,63,147,76,38,239,187,239,62,101,32,168,177,32,107,76,184,180,96,157,179,217,172,18,205,50,31,131,169,174,75,3,173,112,70,208,
245,226,241,248,252,252,252,196,196,196,248,248,248,153,51,103,208,245,138,170,102,100,98,84,42,149,76,38,163,90,121,177,145,149,36,126,152,224,134,60,176,152,99,177,216,141,55,222,152,72,36,164,96,127,
60,30,239,239,239,167,29,148,219,179,60,191,36,150,50,1,136,77,148,122,246,202,4,99,244,224,72,90,214,185,226,157,206,206,78,249,136,193,34,151,6,90,217,98,245,95,86,15,97,192,251,250,250,182,108,217,
162,240,13,213,110,134,177,157,2,79,96,163,149,140,175,249,172,137,179,19,235,152,157,157,253,171,191,250,43,136,14,162,172,137,182,108,235,214,173,209,104,84,86,127,176,167,4,172,143,148,211,83,219,191,
219,237,134,95,223,172,194,120,237,109,77,86,237,66,45,25,126,92,218,28,43,228,175,208,171,16,235,221,36,60,216,19,236,214,114,205,166,229,173,86,171,233,116,90,145,154,205,187,160,251,172,196,225,112,
116,116,116,92,127,253,245,239,122,215,187,30,120,224,129,107,175,189,54,24,12,230,243,121,40,181,82,187,149,10,174,210,70,171,244,0,55,3,143,199,211,218,218,234,243,249,144,81,176,25,112,123,136,28,115,
9,147,225,125,239,123,223,214,173,91,59,59,59,207,157,59,247,243,176,93,89,244,100,50,185,176,176,0,244,83,162,177,236,33,13,206,16,22,70,58,157,134,17,199,179,164,28,26,102,57,230,28,24,193,120,156,94,
175,23,188,49,199,171,213,162,101,155,94,144,210,36,214,73,102,46,161,237,139,23,47,94,186,116,169,191,191,31,98,175,108,0,40,59,139,43,237,83,12,196,45,183,220,130,215,42,250,100,0,0,32,0,73,68,65,84,
34,64,121,54,124,11,43,74,145,37,49,2,0,112,154,205,69,88,70,86,184,72,0,209,210,137,32,50,80,44,22,251,251,251,235,245,58,10,204,210,233,244,201,147,39,129,53,181,182,182,110,219,182,13,9,104,64,111,
150,123,175,82,132,144,246,90,134,252,28,189,77,155,54,237,218,181,75,150,59,98,124,160,155,46,163,25,12,87,107,107,107,60,30,167,202,129,165,190,56,147,129,204,166,74,121,10,252,144,4,160,85,194,13,239,
228,114,57,150,63,40,164,197,178,177,164,121,119,248,9,144,222,118,238,220,185,42,79,150,237,216,165,94,40,78,149,78,167,187,187,187,85,49,5,158,44,167,46,58,168,22,139,69,208,78,134,135,135,191,249,205,
111,194,193,244,249,124,16,128,77,36,18,46,151,171,189,189,189,165,165,133,136,7,61,21,166,136,225,30,6,2,1,37,96,203,210,39,243,137,175,177,144,218,252,176,100,245,89,86,39,98,139,98,138,72,170,131,6,
2,1,146,232,81,75,85,46,151,81,88,176,198,139,105,70,50,177,249,98,181,90,133,66,131,172,8,51,75,231,100,130,215,148,186,148,71,52,26,189,227,142,59,222,244,166,55,57,28,142,115,231,206,61,255,252,243,
79,61,245,212,241,227,199,85,95,58,211,217,87,169,84,132,107,7,14,28,216,191,127,255,247,190,247,61,52,244,88,213,89,230,124,166,192,50,215,209,91,223,250,86,40,76,244,247,247,223,127,255,253,238,15,124,
224,3,200,233,171,238,124,248,109,86,39,203,105,193,148,52,151,25,44,47,187,23,194,238,192,160,160,233,106,161,80,200,137,67,138,212,40,15,154,250,153,82,4,3,214,202,97,213,182,117,110,110,110,239,222,
189,184,30,32,119,240,50,204,188,144,252,185,183,191,253,237,160,205,41,55,95,21,149,202,25,160,42,68,85,56,35,253,86,149,97,160,249,147,21,210,16,51,195,30,134,117,178,188,188,172,122,12,3,121,175,84,
42,243,243,243,24,55,89,105,173,252,65,165,74,161,92,75,190,227,243,249,110,190,249,230,173,91,183,90,14,206,230,205,155,153,57,148,65,213,246,237,219,227,241,120,103,103,167,199,227,129,72,158,105,43,
145,145,35,121,89,89,19,246,96,85,244,44,181,132,16,45,34,144,71,33,181,188,71,201,173,150,100,65,122,214,48,139,120,61,56,56,8,8,203,100,46,114,222,210,20,74,48,135,193,13,188,224,84,42,5,15,145,202,
139,204,105,179,217,29,158,230,200,200,200,211,79,63,141,18,77,174,106,120,51,169,84,106,243,230,205,170,152,5,247,72,138,11,156,18,208,228,101,99,20,164,187,87,117,205,154,249,13,205,250,233,97,189,76,
78,78,162,97,21,103,38,106,101,9,130,171,184,30,239,48,205,67,88,96,213,178,239,102,29,188,214,226,227,3,87,52,107,196,77,17,143,72,36,98,67,11,145,142,133,252,137,214,214,214,171,174,186,234,174,187,
238,122,207,123,222,179,126,253,122,84,9,96,211,53,75,231,100,158,31,23,227,247,251,251,250,250,98,177,216,246,237,219,209,145,202,146,178,162,140,12,161,72,82,170,92,46,215,246,237,219,33,244,248,115,
7,226,67,31,250,16,85,5,148,44,55,170,63,36,9,76,241,129,152,80,134,33,230,39,1,90,41,193,82,254,139,103,9,165,68,101,58,177,111,179,60,154,3,42,155,65,40,87,104,97,97,161,165,165,165,187,187,155,129,
54,115,220,204,209,41,75,180,103,207,30,40,20,179,1,154,9,172,3,78,193,29,97,88,114,185,156,217,250,76,233,223,211,176,154,37,185,220,39,101,75,52,68,136,14,135,227,202,149,43,150,45,248,0,172,99,111,
88,89,89,201,100,50,20,17,149,213,201,146,156,192,238,130,18,192,197,251,61,61,61,111,126,243,155,81,91,175,48,37,188,51,52,52,4,190,176,180,191,93,93,93,61,61,61,124,118,221,221,221,30,143,39,157,78,
75,235,73,79,25,219,158,196,169,232,145,65,18,203,50,218,85,210,2,217,108,150,88,147,217,133,157,23,38,197,84,113,179,44,235,119,58,157,123,246,236,81,34,68,150,253,51,201,199,144,92,142,90,173,134,42,
175,108,54,11,186,139,100,46,209,217,71,211,78,28,80,184,150,121,170,100,50,201,14,44,27,55,110,164,150,161,228,74,35,79,142,207,48,21,140,249,134,193,76,36,18,166,229,85,101,17,146,102,179,170,141,150,
121,163,225,225,225,165,165,165,214,214,86,108,84,217,108,118,114,114,210,241,138,176,176,101,181,58,243,168,196,1,240,194,222,64,43,157,107,27,61,22,203,189,100,113,113,145,184,162,28,64,69,176,243,251,
253,4,208,214,14,245,168,98,180,205,155,55,223,126,251,237,7,14,28,88,191,126,125,107,107,43,250,217,171,235,148,108,99,135,195,209,215,215,7,60,218,231,243,237,220,185,51,20,10,93,188,120,209,230,231,
104,154,101,27,110,143,199,211,210,210,242,254,247,191,95,137,86,186,31,124,240,65,185,35,209,155,102,206,93,161,242,178,247,179,204,137,73,42,27,52,227,45,91,171,129,49,14,227,187,188,188,76,224,152,
136,179,170,253,227,174,104,83,41,52,62,62,126,211,77,55,73,141,55,214,194,170,220,35,94,220,121,231,157,169,84,202,178,125,159,2,200,252,126,63,64,118,90,82,51,187,109,57,27,144,104,85,233,32,105,160,
209,120,13,119,125,238,220,57,34,42,234,8,135,195,36,105,225,185,0,22,68,91,66,41,107,171,138,185,101,83,40,24,175,253,251,247,223,113,199,29,100,209,155,202,244,96,182,40,247,185,209,104,236,217,179,
71,150,150,65,36,15,100,143,229,229,101,105,67,225,32,203,253,91,17,75,164,124,176,25,126,202,207,231,243,249,99,199,142,181,181,181,169,125,72,178,169,48,91,120,144,8,81,175,215,183,111,223,158,76,38,
205,166,162,202,33,144,224,12,199,193,229,114,165,211,105,140,45,60,128,84,42,197,201,140,245,3,79,159,117,222,199,142,29,155,152,152,160,239,66,191,18,217,142,193,193,193,84,42,69,215,152,59,55,151,18,
128,2,105,149,106,181,90,50,153,76,38,147,150,229,200,150,114,157,246,40,176,137,59,79,78,78,194,244,96,174,190,252,242,203,83,83,83,16,175,0,222,221,172,102,157,128,149,204,170,217,235,142,74,146,143,
165,153,150,31,70,191,77,169,252,39,99,89,179,241,30,79,178,106,127,113,27,181,19,245,177,100,50,217,219,219,219,210,210,50,52,52,116,205,53,215,116,116,116,32,110,144,245,7,24,129,68,34,17,143,199,165,
139,221,223,223,191,97,195,134,51,103,206,168,6,190,138,4,161,182,91,183,219,253,192,3,15,36,147,73,181,1,187,31,124,240,65,36,58,240,219,108,255,74,1,120,106,201,59,68,39,52,53,214,12,63,37,118,204,186,
44,121,149,129,64,0,110,5,46,98,105,105,137,4,9,182,161,146,183,17,137,68,104,109,45,109,52,92,209,80,40,180,110,221,58,62,45,20,200,201,84,36,143,120,60,206,32,130,222,150,205,211,146,11,88,250,95,171,
62,105,42,157,43,212,5,103,128,131,86,173,86,47,92,184,208,76,72,26,225,173,132,104,229,5,99,184,86,86,86,224,202,177,62,74,181,64,5,248,112,239,189,247,238,220,185,83,57,161,202,33,133,220,157,250,83,
107,107,235,186,117,235,204,193,199,212,236,234,234,106,52,26,48,211,216,78,216,166,200,212,92,5,78,101,217,175,199,180,209,14,135,227,185,231,158,59,122,244,104,123,123,59,6,65,237,40,48,208,132,149,
0,112,51,219,177,107,215,46,27,22,179,188,71,22,32,72,195,189,176,176,32,127,110,102,102,6,54,154,36,13,72,153,99,146,63,247,220,115,224,164,202,248,9,219,115,48,24,12,135,195,3,3,3,129,64,0,247,46,109,
19,102,8,42,86,228,106,66,122,19,126,137,229,228,84,220,146,181,24,104,229,62,167,211,233,153,153,25,188,70,151,75,202,228,130,69,90,42,149,34,145,8,221,100,83,11,84,38,120,80,253,100,83,61,168,158,133,
77,113,205,210,210,82,169,84,66,252,141,230,176,54,170,249,82,178,13,35,108,169,8,104,102,236,45,59,61,154,188,128,206,206,206,64,32,176,180,180,20,141,70,209,211,163,167,167,39,20,10,1,48,64,146,176,
179,179,83,38,21,161,173,31,14,135,15,28,56,128,176,216,114,158,155,145,208,221,119,223,189,99,199,14,149,152,113,56,28,238,7,30,120,0,149,29,204,254,49,137,129,169,31,12,6,33,112,225,120,69,167,220,12,
175,216,251,14,44,28,78,116,178,226,248,21,84,136,73,111,23,196,94,89,210,134,13,3,149,199,0,52,21,241,195,92,207,195,195,195,55,222,120,35,251,20,96,246,19,238,148,234,157,183,222,122,43,146,138,170,
78,215,82,162,133,108,10,126,126,45,209,19,63,195,66,118,2,199,152,220,128,41,108,172,51,243,156,10,207,53,169,157,228,159,128,42,7,72,74,210,132,251,251,251,127,227,55,126,3,116,125,147,71,44,207,150,
72,36,58,58,58,36,127,195,233,116,238,222,189,155,27,170,18,68,197,18,141,199,227,48,211,172,63,148,90,178,210,130,16,40,176,175,146,224,125,29,57,114,164,82,169,156,61,123,22,197,83,166,188,36,60,26,
92,48,92,1,220,218,158,61,123,100,251,40,211,244,51,51,195,254,106,82,249,100,110,110,78,242,229,113,107,227,227,227,136,100,75,165,18,195,157,108,54,123,244,232,81,180,128,112,188,186,229,27,242,251,
193,96,176,175,175,143,142,51,10,34,224,145,96,133,195,26,170,248,18,69,67,205,28,76,147,38,68,62,201,26,227,250,114,185,60,58,58,218,76,101,133,154,27,153,76,6,217,126,213,233,152,75,131,210,87,232,107,
97,99,160,77,52,195,178,94,145,59,61,154,129,85,42,21,4,22,54,250,33,212,252,65,38,214,38,43,104,82,12,21,10,103,121,68,163,81,180,175,68,21,5,104,96,61,61,61,40,187,237,235,235,35,233,11,131,131,238,
163,177,88,12,218,115,64,249,45,25,120,242,161,111,221,186,245,109,111,123,155,165,207,231,126,240,193,7,189,94,47,181,239,224,214,17,143,38,152,139,66,59,196,26,52,31,72,166,193,115,193,20,207,102,179,
236,158,7,251,75,250,17,197,165,164,207,95,42,149,128,199,99,203,146,192,46,250,75,153,9,37,89,18,45,221,85,159,207,55,52,52,100,138,114,57,94,221,199,232,222,123,239,149,224,184,169,222,194,216,141,126,
40,233,125,102,171,118,251,76,8,109,180,140,197,64,235,41,149,74,151,46,93,50,173,179,92,42,178,73,141,37,65,199,97,37,183,200,196,108,169,84,122,235,91,223,122,247,221,119,243,226,77,58,176,60,67,91,
91,91,50,153,148,160,80,50,153,28,26,26,114,24,221,211,101,207,23,122,211,157,157,157,120,154,220,122,149,77,239,233,233,81,89,80,203,204,62,203,217,175,92,185,130,7,49,61,61,61,53,53,5,6,158,146,40,129,
228,19,0,107,182,28,4,149,187,217,18,53,137,13,244,160,17,141,205,205,205,145,80,207,16,45,155,205,130,212,1,111,23,21,67,82,134,208,241,106,101,78,56,242,221,221,221,209,104,212,100,212,194,82,59,28,
142,76,38,35,37,131,187,186,186,250,251,251,205,240,191,153,178,62,233,207,74,44,201,254,64,123,98,211,47,150,245,35,48,118,192,45,65,239,147,172,6,148,143,226,77,228,135,108,72,205,150,114,181,38,6,66,
10,29,247,45,64,160,178,127,166,234,192,34,187,21,195,141,88,181,36,82,109,84,184,11,251,133,12,114,94,87,87,87,58,157,134,202,2,174,179,175,175,111,239,222,189,67,67,67,93,93,93,72,173,251,124,190,80,
40,4,195,24,12,6,33,210,212,214,214,246,242,203,47,147,167,97,22,115,198,98,177,251,239,191,191,89,243,48,247,7,62,240,1,37,36,196,101,12,142,1,82,67,24,62,148,8,83,157,146,169,48,64,34,153,76,134,233,
93,120,127,96,146,2,163,192,165,144,91,138,175,96,43,166,104,25,170,141,29,66,82,185,25,244,108,6,14,224,68,83,100,75,202,22,243,142,118,239,222,189,99,199,14,37,92,98,166,11,100,184,160,76,137,217,115,
218,126,78,56,68,19,57,132,147,229,114,121,101,101,5,141,156,155,69,160,82,59,212,82,169,71,54,100,178,36,42,164,82,169,135,30,122,136,176,134,148,249,110,118,172,95,191,158,157,13,224,62,3,60,53,187,
138,152,173,185,176,122,227,241,120,50,153,132,99,171,58,148,251,253,254,245,235,215,163,129,144,205,136,241,205,165,165,165,233,233,105,66,156,133,66,225,242,229,203,177,88,140,61,124,89,24,5,247,153,
151,125,253,245,215,171,160,173,217,79,72,165,58,222,227,200,200,72,169,84,146,171,189,82,169,192,201,5,151,160,165,165,197,225,112,76,79,79,191,248,226,139,210,182,170,254,76,80,92,233,234,234,66,214,
84,169,128,177,151,32,160,94,160,34,155,55,111,198,201,87,205,155,73,81,1,85,34,176,150,35,22,139,33,228,106,166,94,45,101,40,192,191,2,120,37,63,128,11,8,133,66,146,224,97,67,127,182,49,226,80,169,150,
254,22,178,44,224,26,192,70,219,35,18,64,129,87,93,137,234,91,96,157,201,84,132,205,108,9,4,2,149,74,229,202,149,43,48,92,224,170,98,242,120,189,94,20,136,30,58,116,40,149,74,177,112,1,79,188,179,179,
115,211,166,77,104,182,103,118,70,111,52,26,135,15,31,222,186,117,107,51,244,220,3,118,148,212,204,52,165,190,171,213,42,84,140,217,249,91,117,192,101,225,22,59,227,73,85,101,20,185,150,74,37,136,207,
177,64,14,126,132,203,229,66,245,7,212,247,225,128,131,107,201,85,199,202,90,169,236,161,164,242,74,165,210,147,79,62,249,43,191,242,43,202,224,202,130,242,3,7,14,176,246,223,50,57,206,239,178,167,53,
225,99,56,11,110,183,91,101,77,77,172,211,210,70,35,240,199,156,123,233,165,151,154,49,126,84,93,162,76,216,74,134,166,124,95,210,4,113,92,123,237,181,191,254,235,191,78,217,92,41,158,171,42,172,228,193,
178,55,130,245,236,48,160,162,22,83,207,158,223,242,120,60,125,125,125,237,237,237,104,166,69,118,121,44,22,67,114,216,100,233,155,29,239,225,90,186,221,110,56,44,78,167,115,113,113,177,88,44,190,240,
194,11,133,66,1,11,224,252,249,243,233,116,250,139,95,252,34,194,44,184,14,110,183,123,98,98,98,96,96,128,121,11,155,90,9,78,18,216,80,120,247,45,45,45,83,83,83,82,67,14,235,10,235,103,118,118,22,29,209,
208,217,86,150,141,152,10,194,61,61,61,176,245,164,231,59,68,175,44,50,171,192,95,76,165,82,202,177,194,191,108,100,103,89,139,43,29,73,83,17,197,70,164,187,171,171,203,225,112,28,63,126,92,138,202,171,
8,82,126,113,106,106,42,149,74,65,161,215,239,247,167,82,41,214,73,219,151,17,154,146,211,234,224,254,199,119,242,249,252,210,210,18,151,231,210,210,82,34,145,144,18,216,138,187,6,128,197,242,113,219,
92,27,35,60,146,104,225,116,54,187,242,106,181,122,230,204,25,214,3,19,220,224,90,192,59,157,157,157,93,93,93,78,167,51,159,207,47,46,46,62,255,252,243,197,98,113,104,104,232,55,126,227,55,30,127,252,
241,211,167,79,83,0,131,237,156,152,248,177,54,208,76,107,112,184,233,115,201,162,181,96,48,8,215,15,214,83,109,236,110,183,155,212,40,69,109,198,215,253,126,63,218,133,161,84,198,239,247,131,196,6,106,
20,245,239,193,30,139,199,227,24,47,246,221,97,39,45,182,12,55,219,30,110,217,178,229,166,155,110,146,36,127,110,51,56,91,123,123,59,216,120,212,108,106,150,28,151,140,75,154,24,110,164,169,84,10,148,
184,181,152,102,201,146,198,166,125,226,196,9,75,53,194,102,248,29,106,103,36,67,75,234,126,240,170,104,172,239,189,247,222,91,111,189,149,60,30,86,18,50,150,151,181,133,146,236,129,78,43,180,188,157,
157,157,44,146,110,230,125,115,251,84,155,132,215,235,237,237,237,77,38,147,47,191,252,50,150,31,210,211,225,112,152,171,113,102,102,6,31,30,31,31,199,169,174,92,185,130,75,186,116,233,18,44,178,18,66,
146,85,118,184,163,246,246,118,120,118,204,108,47,47,47,175,172,172,244,245,245,65,222,196,166,140,77,226,105,32,47,23,139,197,68,34,1,229,44,208,70,193,61,135,158,20,30,193,240,240,112,51,193,69,78,45,
116,50,195,156,129,247,131,7,100,217,60,27,52,0,21,188,170,202,219,102,41,53,217,175,107,213,74,66,21,32,118,118,118,222,124,243,205,39,79,158,164,195,161,58,155,40,140,5,60,125,228,205,144,146,85,242,
15,107,47,95,148,200,164,170,45,0,214,193,210,83,188,185,184,184,216,210,210,66,172,67,197,187,4,7,44,33,142,102,27,131,108,117,132,207,83,229,194,84,206,105,52,26,39,79,158,132,15,138,95,132,140,15,215,
11,36,233,229,110,29,10,133,208,72,15,227,214,210,210,242,192,3,15,252,199,127,252,199,183,191,253,109,38,249,122,123,123,65,145,130,219,33,13,17,5,215,60,112,61,72,32,229,74,86,33,21,118,221,145,145,
17,52,48,7,208,1,231,5,44,52,114,39,185,98,73,41,37,166,140,237,14,242,243,136,47,0,76,7,131,65,248,47,94,175,55,153,76,194,223,100,217,165,236,240,45,169,211,180,11,157,157,157,191,246,107,191,182,113,
227,70,20,47,88,214,255,212,106,181,171,174,186,74,170,164,90,192,61,175,96,211,178,251,167,233,104,251,253,254,150,150,22,230,103,215,94,225,58,63,63,255,220,115,207,41,202,145,121,236,217,179,135,68,
108,51,163,162,250,3,200,127,59,59,59,223,245,174,119,117,118,118,74,178,157,169,94,79,126,49,203,106,176,41,74,203,27,14,135,17,164,155,176,181,132,128,153,246,148,204,226,106,181,10,160,22,121,90,180,
90,119,56,28,47,190,248,226,228,228,228,229,203,151,85,13,186,20,113,198,127,149,32,151,68,15,72,33,192,127,219,219,219,115,185,28,169,126,236,89,158,78,167,51,153,12,50,54,246,37,106,146,112,130,42,190,
124,62,15,112,9,125,93,113,145,160,135,75,31,147,100,83,179,167,92,44,22,131,64,29,198,4,113,33,208,12,105,20,100,227,40,117,30,149,98,49,141,181,66,249,86,21,237,84,238,36,86,83,32,16,216,183,111,223,
165,75,151,46,95,190,204,139,63,119,238,28,61,104,89,232,139,187,190,116,233,18,18,206,168,227,160,99,183,123,247,110,188,175,122,137,41,39,70,198,112,192,49,100,82,26,73,5,148,95,200,148,120,181,90,157,
158,158,110,105,105,33,36,45,11,5,148,251,108,239,74,115,24,201,76,83,35,12,228,135,58,221,228,92,93,185,114,5,168,93,173,86,235,235,235,163,239,204,86,39,108,223,42,103,5,218,73,195,88,119,116,116,244,
247,247,95,119,221,117,127,254,231,127,158,78,167,131,193,224,29,119,220,1,59,134,72,139,2,144,180,192,141,70,195,67,181,7,85,85,161,200,206,160,124,161,127,12,118,27,228,88,81,48,45,123,101,74,207,151,
245,20,32,193,144,150,139,160,18,201,73,88,109,92,98,75,75,11,19,232,160,196,55,99,134,193,58,183,183,183,191,229,45,111,57,112,224,128,84,76,230,35,148,97,90,189,94,159,152,152,0,23,213,82,12,151,161,
3,155,13,218,204,117,175,215,75,63,218,222,52,115,186,12,15,15,31,57,114,196,241,90,164,191,76,193,95,238,174,102,226,101,223,190,125,111,123,219,219,0,226,203,157,95,66,58,50,236,144,37,218,178,175,46,
190,27,10,133,136,72,168,62,0,72,75,80,61,135,228,80,176,163,168,183,5,119,3,220,118,48,166,65,10,84,104,134,25,135,42,108,7,41,23,66,222,146,217,221,104,52,142,31,63,190,113,227,70,57,230,201,100,18,
92,236,70,163,49,61,61,237,243,249,90,91,91,215,94,101,135,190,95,184,206,182,182,54,143,199,51,58,58,42,43,3,77,99,170,224,75,72,71,42,163,185,178,178,2,89,75,74,11,240,132,243,243,243,93,93,93,202,27,
229,34,183,172,108,118,88,245,28,81,148,50,75,18,139,210,198,195,18,99,135,83,22,76,242,224,127,249,1,144,2,218,218,218,16,4,243,112,185,92,183,222,122,171,20,108,49,105,191,242,146,144,140,145,11,4,232,
31,85,155,149,123,84,171,213,22,22,22,146,201,36,253,54,24,28,204,210,102,40,144,37,139,28,174,131,89,52,47,255,69,23,61,194,250,167,78,157,162,3,17,143,199,81,59,198,123,196,60,81,10,42,48,62,112,124,
49,224,168,227,221,183,111,223,191,252,203,191,124,252,227,31,223,181,107,87,52,26,5,156,128,4,30,24,110,202,247,250,121,65,7,215,170,92,216,50,133,138,62,32,232,183,194,201,7,7,30,181,185,220,117,169,
16,77,130,17,56,149,102,24,130,201,1,246,18,173,179,108,12,40,61,104,9,109,7,131,193,91,111,189,245,150,91,110,1,135,68,53,60,84,105,34,138,133,254,215,127,253,215,109,183,221,102,18,146,200,190,98,208,
106,185,164,213,36,104,109,109,93,94,94,110,214,177,70,206,149,75,151,46,189,86,235,236,104,210,174,194,108,69,17,12,6,239,187,239,62,236,82,20,167,150,246,87,218,101,213,22,82,54,184,225,39,145,104,69,
67,38,201,110,60,117,234,148,90,120,146,8,161,88,213,242,26,184,121,35,46,86,114,163,166,185,172,215,235,209,104,148,201,40,88,124,203,254,91,144,127,97,44,21,8,4,16,87,18,112,40,151,203,99,99,99,241,
120,28,133,124,150,191,200,36,39,135,55,20,10,81,129,175,187,187,27,1,62,123,247,152,33,154,116,195,1,212,154,14,29,60,125,114,117,165,21,94,92,92,108,109,109,181,20,39,1,95,16,21,255,74,248,219,236,175,
218,204,70,43,65,74,169,46,173,152,157,205,168,211,114,31,69,40,204,185,209,108,207,176,137,87,80,67,235,16,237,22,169,24,197,70,60,249,124,158,172,127,152,8,12,20,228,73,225,2,198,98,49,233,62,43,4,191,
25,155,19,28,71,213,233,81,57,61,200,204,193,122,142,141,141,65,192,18,19,32,149,74,177,73,16,46,47,149,74,201,232,74,85,89,163,216,77,106,193,7,131,193,63,253,211,63,173,86,171,35,35,35,115,115,115,112,
116,74,165,18,101,18,228,236,242,152,141,172,164,99,197,255,226,236,140,238,153,251,194,111,163,122,29,243,15,137,93,100,108,184,104,163,209,168,201,127,224,122,246,249,124,61,61,61,100,162,80,46,93,34,
206,50,97,120,240,224,193,119,189,235,93,236,226,42,67,48,75,94,61,235,182,23,22,22,30,123,236,177,55,190,241,141,20,180,149,155,144,236,208,108,62,87,203,188,162,153,88,48,225,206,243,231,207,255,244,
167,63,125,29,154,185,14,219,150,66,248,211,186,117,235,126,243,55,127,179,175,175,79,134,147,202,112,168,221,203,178,141,175,228,204,96,219,103,241,174,76,3,90,182,182,107,6,169,115,13,147,44,232,116,
58,19,137,68,54,155,69,108,43,173,0,23,33,236,17,158,23,130,74,211,187,148,128,41,200,179,45,45,45,48,142,210,208,240,238,210,233,116,58,157,78,38,147,116,184,84,153,149,170,75,2,212,8,177,42,148,219,
249,253,254,116,58,141,34,55,121,13,170,65,76,56,28,38,79,73,69,66,16,195,74,165,82,132,179,165,120,116,46,151,99,197,172,73,61,68,166,145,188,111,155,116,156,249,117,153,10,147,94,191,101,183,114,75,
42,136,180,209,40,22,149,204,168,85,69,145,212,129,174,17,146,247,201,240,151,95,68,174,130,165,255,40,25,5,38,83,171,213,218,219,219,201,125,182,36,116,89,250,209,82,8,91,245,243,84,155,34,135,2,218,
211,223,251,222,247,208,7,189,82,169,48,79,195,28,91,79,79,143,217,194,141,204,22,180,142,66,64,70,124,146,142,38,20,60,128,27,163,102,146,52,30,122,201,30,153,127,231,28,149,93,81,212,61,183,181,181,
101,179,89,140,41,192,53,86,232,131,64,237,114,185,162,209,40,125,165,90,173,198,122,101,218,95,41,247,238,241,120,0,240,81,41,77,122,202,184,121,186,72,123,246,236,121,199,59,222,145,76,38,81,178,168,
212,82,232,154,73,147,77,22,7,174,249,220,185,115,231,207,159,223,184,113,99,60,30,15,135,195,200,50,145,99,96,73,237,104,22,32,67,238,139,229,48,150,153,168,255,253,223,255,133,239,108,95,70,181,42,110,
104,230,247,29,14,199,157,119,222,249,222,247,190,151,172,24,41,193,99,153,77,53,183,61,118,87,96,69,12,44,117,32,16,0,233,88,161,207,114,93,201,19,42,106,135,242,200,144,63,225,28,245,122,189,225,112,
152,41,23,89,117,2,103,217,146,100,102,194,32,224,33,220,115,207,61,47,191,252,114,38,147,217,178,101,11,174,217,220,161,41,175,145,203,229,146,201,164,236,217,97,202,44,80,220,213,231,243,133,195,225,
88,44,150,201,100,50,153,12,144,101,244,113,87,107,132,51,153,218,208,14,163,151,2,106,46,22,23,23,19,137,4,32,126,249,211,144,136,146,146,185,202,56,130,62,65,51,45,123,185,89,58,143,252,174,101,206,
195,166,128,22,27,140,201,188,134,205,98,58,154,183,198,37,96,90,103,229,206,163,130,223,244,250,21,15,15,17,12,53,3,120,49,144,27,93,92,92,156,155,155,235,232,232,104,111,111,95,89,89,33,249,111,85,62,
9,47,9,64,138,165,62,181,234,173,238,247,251,191,251,221,239,130,188,177,97,195,134,174,174,174,112,56,12,167,16,46,124,40,20,138,199,227,82,242,91,102,50,113,167,108,13,108,201,118,13,4,2,67,67,67,115,
115,115,227,227,227,112,216,37,252,237,114,185,60,114,31,147,75,75,18,36,28,175,86,122,3,229,142,74,49,204,165,194,69,135,161,196,40,128,139,211,209,209,193,187,146,148,12,246,220,101,171,8,105,14,248,
25,188,216,182,109,219,155,223,252,102,100,2,217,221,195,36,108,152,29,22,36,79,142,0,250,229,203,151,55,111,222,92,46,151,17,13,112,165,65,224,6,89,83,64,177,205,124,1,136,58,201,222,72,230,103,158,124,
242,201,151,94,122,201,70,56,102,141,21,137,38,185,61,24,12,62,252,240,195,215,95,127,189,217,160,86,214,130,83,202,74,241,234,48,170,146,203,1,17,56,240,13,148,104,6,127,26,205,42,233,227,208,166,171,
228,56,96,104,152,90,144,168,20,166,76,246,2,62,6,115,99,70,217,150,101,20,38,227,16,133,18,176,110,200,121,154,101,71,4,61,208,160,51,20,10,161,89,154,89,245,32,219,11,56,94,233,32,147,76,38,195,225,
240,220,220,28,188,182,80,40,4,61,116,89,91,107,106,65,72,110,34,117,210,1,199,3,244,83,119,148,205,102,17,1,88,22,181,242,53,86,25,220,64,234,71,90,210,239,100,16,99,83,227,103,162,213,150,30,9,20,145,
44,207,102,83,97,43,175,68,214,24,55,35,65,242,89,132,66,33,214,163,170,13,35,159,207,143,142,142,6,2,129,98,177,8,233,8,86,3,57,94,173,20,106,22,185,64,33,64,226,27,10,160,151,51,97,105,105,201,227,241,
68,163,209,249,249,249,19,39,78,96,3,102,0,81,175,215,33,151,40,211,131,140,150,232,2,179,112,84,50,85,20,44,19,141,70,135,134,134,166,166,166,0,118,189,42,41,194,161,225,207,200,13,193,204,89,35,117,
62,59,59,203,119,216,138,148,122,152,184,68,36,133,186,187,187,81,189,142,253,83,93,25,162,90,240,246,37,214,172,106,46,238,188,243,206,157,59,119,170,177,150,204,121,34,155,116,150,165,31,77,217,141,
116,58,13,195,84,46,151,47,94,188,184,117,235,86,41,56,9,160,144,170,117,92,15,184,59,162,25,200,219,72,53,62,19,247,168,86,171,95,249,202,87,76,235,188,118,158,102,51,25,95,135,195,49,56,56,248,137,79,
124,162,173,173,77,9,75,201,104,78,102,20,36,59,69,209,168,249,4,165,247,4,218,144,77,73,11,188,224,181,240,11,77,194,12,159,154,130,56,76,119,198,228,243,154,18,57,240,80,220,110,247,224,224,32,26,187,
0,94,83,103,147,14,7,138,47,138,197,98,52,26,5,28,39,145,80,170,29,72,61,82,184,17,189,189,189,233,116,122,126,126,222,235,245,182,180,180,20,10,5,180,118,102,38,0,142,185,217,111,8,21,179,108,93,207,
149,143,173,133,214,4,185,41,148,218,174,138,231,98,103,2,249,21,112,173,201,85,96,29,172,141,43,48,48,48,48,50,50,98,246,90,132,89,145,17,140,169,13,34,127,75,170,145,152,54,26,37,14,166,195,97,201,190,
192,236,69,155,58,203,34,29,252,34,200,54,40,37,45,20,10,160,255,130,212,33,107,149,21,140,14,50,149,44,174,145,136,132,138,126,206,158,61,235,245,122,175,189,246,218,19,39,78,148,74,165,76,38,115,250,
244,233,150,150,150,246,246,246,90,173,150,74,165,152,57,144,154,183,166,120,116,48,24,4,80,214,108,51,195,199,32,59,163,148,232,61,50,119,175,138,211,148,120,46,205,119,165,82,137,197,98,249,124,30,37,
221,20,238,32,211,150,107,47,30,143,111,218,180,9,229,133,136,157,73,188,151,231,39,130,161,58,45,5,2,129,183,188,229,45,123,247,238,37,28,41,5,145,165,40,162,10,108,77,135,17,155,24,137,95,32,246,159,
61,123,118,199,142,29,54,37,88,108,128,68,152,31,198,93,182,46,148,122,35,8,2,170,213,234,183,191,253,237,43,87,174,172,69,58,75,241,49,100,186,82,201,176,225,51,239,120,199,59,62,248,193,15,146,198,160,
240,7,238,76,10,252,65,0,174,10,196,249,87,4,49,142,87,122,58,212,235,117,178,238,28,70,187,113,199,43,218,220,150,185,41,135,33,236,41,119,119,162,28,102,87,39,213,63,201,44,60,179,84,170,60,118,236,
24,128,120,178,80,129,188,33,146,51,139,122,228,110,145,205,102,233,180,178,24,129,169,42,203,40,7,157,61,103,103,103,179,217,44,234,53,114,185,92,54,155,165,181,181,44,153,67,52,73,168,1,91,5,90,56,43,
63,26,236,23,6,185,102,242,74,13,59,150,21,234,122,76,200,85,217,2,197,60,193,155,253,253,253,35,35,35,170,168,202,244,160,129,201,216,248,200,170,122,75,157,16,35,224,176,234,164,99,89,139,64,137,15,
40,76,40,84,4,193,10,188,61,52,72,35,137,40,157,78,195,82,55,139,240,176,79,72,241,82,90,103,204,76,138,80,142,143,143,179,172,255,218,107,175,157,157,157,157,158,158,174,215,235,227,227,227,115,115,115,
61,61,61,59,118,236,96,181,145,148,11,199,218,68,128,5,43,145,72,36,80,217,36,167,129,196,196,101,82,49,30,143,151,203,101,186,137,63,143,208,185,189,59,172,4,115,37,244,81,40,20,218,219,219,145,24,228,
60,128,4,132,92,60,209,104,20,237,229,89,7,8,66,9,126,8,180,10,180,102,144,108,13,216,184,104,52,186,111,223,190,27,110,184,129,42,89,178,147,30,51,93,102,159,86,105,178,29,162,71,6,216,184,120,240,248,
64,161,80,64,169,207,190,125,251,86,45,147,149,186,198,185,92,78,74,197,67,232,178,179,179,19,166,57,155,205,62,246,216,99,103,207,158,37,140,208,172,70,200,198,107,134,195,46,53,248,249,153,67,135,14,
145,100,98,10,251,153,41,65,233,77,99,75,51,5,99,113,54,130,206,44,167,86,71,56,28,206,100,50,84,124,182,47,3,145,228,101,217,161,220,33,218,254,42,55,205,210,113,150,97,80,179,114,97,212,163,203,80,175,
88,44,50,226,145,8,163,130,8,97,89,48,87,193,129,109,6,124,243,226,81,131,147,201,100,192,218,196,147,2,187,81,217,62,199,43,226,206,148,173,80,235,11,54,154,244,18,54,69,37,219,215,198,58,171,152,221,
52,196,164,64,88,230,153,77,6,39,203,110,21,219,138,105,76,89,45,101,195,83,84,134,155,185,37,71,19,205,66,203,127,73,34,54,41,82,72,105,80,97,2,201,85,121,90,48,94,96,217,67,161,80,40,20,226,231,29,175,
72,83,169,142,233,114,123,96,145,200,240,240,48,159,87,52,26,5,85,3,69,85,165,82,9,84,104,184,158,100,1,177,105,42,67,76,140,0,178,238,116,170,44,75,43,21,237,15,5,171,181,90,205,163,156,86,211,41,147,
175,193,62,129,183,146,72,36,22,23,23,149,158,22,31,188,199,227,185,250,234,171,209,99,141,89,62,234,198,102,50,25,16,194,97,134,0,23,80,87,236,218,107,175,189,249,230,155,225,196,17,158,102,42,140,202,
191,244,8,36,238,163,252,38,142,56,156,119,154,45,212,17,225,118,142,29,59,118,195,13,55,56,172,90,207,153,244,12,32,239,202,197,64,120,139,29,235,111,255,246,111,39,39,39,149,155,191,22,137,37,83,108,
1,88,51,172,12,132,93,74,165,210,199,62,246,177,47,127,249,203,160,58,169,203,176,12,125,76,66,14,182,40,217,66,16,231,161,219,174,138,86,100,179,27,137,135,52,43,10,80,187,133,172,76,227,44,82,11,67,
129,203,216,83,213,106,111,214,113,89,18,173,36,16,199,189,211,228,147,41,207,180,90,173,78,78,78,162,72,74,9,158,41,209,84,190,136,197,98,225,112,120,102,102,102,108,108,12,57,112,85,251,192,120,25,124,
50,236,70,102,77,230,252,252,60,100,163,101,6,101,101,101,133,254,248,170,133,121,164,127,41,112,121,45,82,109,234,3,138,48,35,255,4,32,69,22,103,174,90,37,200,128,192,70,157,195,254,242,208,233,77,250,
94,124,31,112,92,185,92,158,153,153,1,13,193,50,226,47,22,139,112,237,35,145,8,168,253,233,116,90,9,38,115,183,150,212,195,203,151,47,211,136,99,15,110,52,26,219,183,111,175,84,42,99,99,99,193,96,112,
243,230,205,224,225,97,237,243,235,220,57,184,37,195,94,119,119,119,143,142,142,178,124,204,158,135,67,119,234,85,73,66,233,68,171,22,206,100,68,32,42,36,109,35,153,76,50,182,34,145,3,55,191,103,207,30,
150,183,42,124,25,50,49,216,127,248,156,240,197,245,235,215,31,62,124,24,30,156,156,49,20,235,146,65,1,69,73,104,184,205,168,150,216,58,50,51,16,196,144,14,56,40,226,39,78,156,184,246,218,107,213,108,
51,105,146,0,197,76,26,53,182,232,114,185,252,217,207,126,118,98,98,130,119,36,133,108,214,238,74,75,147,202,170,116,36,67,112,193,143,60,242,200,39,62,241,9,90,76,85,49,97,217,175,196,68,84,80,97,196,
41,72,184,6,196,32,75,139,15,208,201,82,20,194,38,17,170,186,19,201,138,77,181,23,170,215,74,65,205,210,76,191,240,194,11,156,36,146,33,202,105,83,46,151,89,144,169,90,80,75,251,187,184,184,8,39,32,30,
143,35,104,147,245,244,138,230,193,141,161,187,187,59,149,74,205,204,204,192,209,163,146,1,191,5,63,128,192,189,234,243,128,23,115,115,115,244,163,249,91,168,219,178,44,17,84,214,144,20,46,229,182,55,
51,1,54,21,225,38,181,67,181,58,74,167,211,80,225,88,139,117,38,33,71,121,136,150,141,26,96,55,217,184,142,227,159,78,167,95,126,249,101,14,35,28,249,84,42,5,129,61,252,244,194,194,66,119,119,55,171,60,
20,21,13,111,102,50,153,92,46,55,51,51,195,205,76,81,209,37,51,185,215,93,8,0,0,32,0,73,68,65,84,2,98,217,178,104,155,183,185,123,247,110,200,61,203,66,21,143,199,19,8,4,164,202,5,245,130,152,166,106,
105,105,25,30,30,166,24,6,75,103,37,190,161,128,193,159,81,36,84,23,122,37,8,192,91,69,6,28,242,131,188,195,84,42,133,204,172,108,213,234,116,58,55,111,222,28,141,70,213,251,204,210,192,218,18,199,132,
153,238,232,232,184,238,186,235,182,108,217,194,101,35,153,97,142,87,90,92,203,96,196,84,32,52,45,53,157,107,52,115,100,82,85,121,97,211,211,211,47,188,240,194,222,189,123,77,41,22,190,0,129,193,50,193,
141,132,242,35,143,60,66,235,44,169,145,76,142,73,116,222,6,140,70,213,22,118,32,206,194,72,36,242,161,15,125,232,137,39,158,56,123,246,236,217,179,103,159,124,242,201,195,135,15,91,146,2,37,178,97,174,
34,25,73,129,99,131,48,141,51,9,253,229,76,59,82,175,215,99,177,152,212,11,181,220,6,84,109,139,73,164,101,128,133,57,106,67,161,179,132,158,77,163,128,161,206,231,243,192,73,101,201,21,41,25,188,65,53,
218,88,69,133,66,33,26,141,194,195,77,167,211,94,175,23,178,139,102,89,144,226,26,35,117,134,44,255,244,244,52,156,12,41,173,199,225,82,203,79,145,163,96,163,89,155,227,120,165,67,152,212,103,176,36,197,
99,63,80,131,195,85,108,201,74,102,221,128,37,232,33,151,63,107,122,185,100,74,165,18,40,110,54,54,122,118,118,22,189,217,10,133,2,232,22,244,37,103,103,103,177,216,97,13,160,135,69,132,147,234,14,144,
232,4,74,0,176,158,147,48,153,76,66,210,71,121,250,19,19,19,200,120,153,212,17,86,171,35,153,212,76,79,138,120,49,52,97,56,62,240,226,229,13,94,125,245,213,145,72,4,120,52,141,50,170,4,49,103,100,195,
70,22,106,37,18,9,196,58,50,134,131,235,13,235,42,219,92,208,240,54,26,141,87,117,110,101,221,33,182,62,204,15,60,39,172,1,153,47,226,15,67,67,146,24,197,186,117,235,192,62,145,65,40,117,57,28,66,45,151,
249,135,29,59,118,12,14,14,58,28,142,229,229,101,180,200,84,21,177,156,40,74,35,148,152,14,141,50,145,13,137,111,164,211,105,246,160,50,195,85,184,165,147,147,147,71,143,30,221,191,127,191,101,4,135,158,
234,205,12,226,244,244,244,159,253,217,159,161,59,140,148,242,49,123,104,41,153,83,75,27,93,169,84,192,76,96,22,116,112,112,240,247,126,239,247,218,219,219,183,109,219,246,91,191,245,91,197,98,241,107,
95,251,218,142,29,59,6,6,6,152,98,101,68,98,122,76,210,40,155,249,22,169,58,141,90,15,19,221,194,36,65,32,105,95,80,211,12,128,86,41,104,86,111,115,72,215,146,18,180,177,227,217,108,118,100,100,100,104,
104,72,186,231,114,143,167,234,200,207,131,71,143,7,238,146,215,235,37,129,76,42,216,97,30,90,182,109,163,125,199,95,209,177,123,100,100,4,49,22,206,207,82,11,69,178,86,18,178,236,18,160,252,104,224,126,
38,175,89,142,128,105,157,205,8,218,124,100,178,176,240,192,129,3,63,249,201,79,228,134,65,7,80,126,30,233,34,24,32,0,155,170,243,198,240,240,240,31,254,225,31,226,177,30,61,122,20,165,237,112,53,192,
11,4,80,0,15,9,7,215,35,189,25,186,147,180,149,169,84,42,20,10,1,93,1,16,132,165,97,14,197,228,228,164,219,237,86,120,180,164,78,170,86,215,205,242,174,211,211,211,216,86,225,70,16,208,163,77,111,109,
109,69,112,51,57,57,201,177,226,150,70,195,200,68,17,119,107,152,245,102,82,48,64,81,168,113,70,195,235,254,245,95,255,117,201,108,131,249,103,70,146,51,9,197,41,14,163,97,98,32,16,128,38,47,166,84,123,
123,251,134,13,27,228,218,160,37,37,181,94,58,197,187,118,237,218,191,127,127,42,149,98,60,139,252,155,236,160,99,242,171,108,232,177,234,53,174,118,98,98,130,88,152,77,91,7,148,138,13,12,12,96,124,121,
128,182,33,105,6,114,6,140,143,143,127,234,83,159,98,108,65,16,74,177,20,164,65,180,135,222,122,122,122,144,131,198,101,220,122,235,173,15,61,244,80,60,30,135,239,115,213,85,87,61,253,244,211,181,90,237,
226,197,139,183,221,118,155,100,4,35,197,106,38,121,44,83,94,82,87,68,54,21,235,232,232,96,57,178,204,76,192,136,67,34,202,242,60,50,143,74,122,53,30,153,20,111,98,172,134,7,77,240,71,181,39,87,45,195,
101,154,68,17,49,247,236,217,211,221,221,237,114,185,94,126,249,229,209,209,81,20,43,170,249,128,98,40,191,223,31,14,135,195,225,48,2,82,64,118,148,108,103,197,44,69,51,176,22,100,202,206,212,120,147,
137,214,150,150,150,88,44,134,189,156,202,18,68,39,153,164,149,93,162,37,152,3,201,4,89,167,192,72,185,217,84,161,12,164,76,202,53,227,8,89,2,193,63,253,233,79,159,121,230,25,110,90,150,135,100,143,209,
21,64,10,14,134,130,146,73,165,82,233,232,209,163,232,7,166,72,108,28,97,218,47,57,170,18,130,135,180,144,228,128,178,71,162,44,240,49,21,105,16,69,169,176,131,59,153,42,216,105,150,163,131,90,33,46,137,
244,106,254,34,246,9,150,210,64,120,207,33,26,27,193,24,202,62,33,180,6,181,90,13,48,180,84,145,84,77,68,49,87,49,170,63,195,79,212,74,0,208,169,2,85,148,113,43,124,147,179,7,48,28,60,172,205,155,55,155,
216,34,27,89,17,178,169,215,235,155,54,109,26,28,28,132,105,160,237,6,71,106,110,110,14,125,101,204,98,36,122,94,38,97,67,45,24,34,12,232,239,41,221,231,102,125,133,157,78,231,216,216,216,179,207,62,123,
240,224,65,153,85,231,215,37,173,5,118,112,116,116,244,179,159,253,44,29,25,86,151,153,30,180,196,76,168,39,101,185,234,96,32,112,61,15,62,248,224,205,55,223,76,179,213,104,52,122,123,123,239,189,247,
222,175,125,237,107,75,75,75,79,63,253,52,72,29,82,126,15,180,116,240,252,203,229,178,74,241,155,7,102,3,31,40,120,184,38,96,194,126,55,14,219,70,130,50,55,213,12,95,102,102,79,86,121,168,236,156,141,
251,108,233,1,97,193,20,10,133,11,23,46,204,204,204,236,220,185,19,149,83,240,224,84,102,133,81,17,173,51,67,31,250,191,236,243,139,106,8,75,169,117,165,103,141,116,255,246,237,219,103,102,102,208,169,
75,86,0,91,194,65,210,223,7,214,129,147,240,43,82,166,195,44,15,145,21,210,42,23,109,211,94,68,46,97,126,165,89,222,130,20,20,245,38,160,140,193,193,65,222,96,38,147,121,238,185,231,184,192,101,195,48,
213,140,201,172,80,149,55,194,192,23,63,218,209,209,1,186,11,113,103,73,154,84,232,205,232,232,104,127,127,63,51,37,236,218,193,187,224,92,53,245,224,232,20,227,99,178,143,23,127,14,50,88,56,73,107,107,
171,203,229,26,27,27,163,9,165,64,46,176,114,180,97,99,103,181,214,214,86,118,161,116,24,221,97,216,21,72,85,210,122,148,147,162,170,227,240,14,50,254,170,21,133,212,217,64,67,132,173,91,183,42,0,84,13,
55,206,220,217,217,9,226,42,71,22,2,164,160,118,224,195,185,92,110,116,116,180,183,183,87,81,199,101,201,184,163,137,42,185,90,201,40,10,80,210,163,166,83,201,23,163,163,163,207,60,243,204,141,55,222,
136,71,11,157,107,162,19,18,134,30,29,29,253,244,167,63,141,126,93,116,121,154,85,85,169,77,139,172,106,179,102,12,91,104,91,91,219,71,62,242,145,129,129,1,181,199,214,235,245,155,110,186,233,242,229,
203,255,31,107,95,30,221,214,89,230,45,219,242,34,91,146,229,69,222,247,216,217,19,39,105,18,210,36,64,105,83,186,77,15,45,101,10,167,133,161,103,104,11,12,7,232,97,88,122,134,1,6,230,27,90,160,5,122,
96,74,97,78,105,161,208,66,59,83,74,105,155,238,109,154,166,217,247,56,177,29,47,177,29,111,178,37,89,171,101,121,251,254,248,209,31,15,207,123,175,18,230,251,244,71,142,45,43,210,213,189,239,125,222,
103,249,45,208,168,109,106,106,66,163,67,242,33,201,58,65,164,70,148,161,152,156,25,160,101,61,132,73,151,188,111,49,27,148,33,201,14,182,161,248,105,166,226,182,12,250,146,136,124,145,125,12,75,162,4,
31,0,144,98,241,236,223,191,127,249,242,229,237,237,237,150,120,65,192,179,208,67,144,144,3,58,217,75,228,9,97,18,164,144,153,210,160,127,165,110,227,116,214,213,213,21,23,23,119,116,116,112,242,97,169,
175,100,57,134,5,174,131,172,144,68,34,1,172,152,25,163,149,120,147,29,157,53,51,199,111,116,116,212,238,149,108,223,219,141,1,83,169,84,79,79,207,146,37,75,32,170,169,162,51,226,50,255,101,130,79,145,
91,149,210,50,179,81,125,3,167,211,73,129,248,12,162,31,156,249,51,70,115,129,161,223,194,120,165,124,174,185,86,99,177,24,169,49,64,97,171,52,156,93,29,62,89,86,86,86,84,84,116,230,204,25,76,68,19,137,
4,129,194,232,24,131,231,77,233,174,226,226,226,64,32,32,207,39,171,94,230,169,82,16,124,97,97,33,231,246,219,111,151,202,211,16,228,116,8,217,126,153,130,201,225,161,108,116,184,92,174,138,138,10,242,
208,216,142,144,185,45,96,249,112,198,37,36,67,214,101,220,106,80,4,225,204,154,170,5,150,157,10,203,24,141,149,1,232,162,101,183,193,206,79,40,20,10,69,163,209,198,198,70,220,45,178,34,227,99,215,174,
93,63,249,201,79,20,244,219,82,146,194,238,176,21,21,149,143,37,75,150,108,222,188,249,91,223,250,86,121,121,185,140,203,242,135,213,171,87,15,13,13,205,206,206,142,142,142,174,92,185,210,178,57,46,247,
106,184,242,128,200,78,116,54,75,72,30,158,207,231,99,27,212,241,174,235,4,84,32,112,101,81,42,57,12,91,110,217,18,97,190,79,41,21,249,144,205,52,42,187,74,39,114,78,93,204,46,135,229,175,181,181,181,
219,183,111,47,44,44,156,159,159,167,187,241,194,194,194,216,216,216,224,224,160,223,239,71,117,44,47,144,148,166,147,8,16,89,96,202,22,51,239,8,135,208,179,183,124,240,191,192,33,105,98,98,66,54,52,236,
114,8,245,26,116,123,81,178,36,18,9,220,231,42,80,154,138,198,38,127,58,3,37,4,143,161,161,161,93,187,118,65,0,154,29,24,74,81,74,58,174,60,60,232,1,144,220,20,141,70,67,161,16,108,40,228,203,84,27,71,
130,8,56,184,179,164,137,154,184,195,188,188,60,176,148,45,217,76,230,190,18,139,197,80,63,129,189,108,39,252,164,158,31,28,28,228,245,229,1,240,62,133,196,133,121,185,243,242,242,74,74,74,38,38,38,162,
209,40,219,12,14,97,211,33,175,203,204,204,204,208,208,144,188,23,8,241,146,164,7,202,234,206,207,207,103,243,150,224,173,133,52,86,234,72,41,25,73,83,115,114,243,230,205,240,93,150,147,22,153,89,20,22,
22,46,91,182,108,229,202,149,76,13,24,154,89,221,0,191,66,228,32,226,8,232,0,242,164,80,194,84,26,95,201,159,229,3,189,99,148,186,148,181,85,15,249,36,127,238,234,234,250,241,143,127,172,222,141,154,185,
187,118,237,122,232,161,135,164,229,171,68,59,152,149,166,101,55,0,143,166,166,166,239,125,239,123,157,157,157,44,108,63,249,201,79,126,243,155,223,196,222,43,59,86,18,68,153,159,159,127,217,101,151,97,
9,238,221,187,215,242,206,55,233,30,104,5,148,149,149,53,55,55,67,252,5,94,200,124,129,180,244,197,125,72,37,82,78,116,29,86,206,226,138,157,143,31,228,182,97,242,95,241,87,234,45,92,16,188,97,249,43,
54,15,96,81,33,104,39,191,114,36,18,121,225,133,23,14,31,62,44,151,16,220,53,17,41,164,18,0,86,17,250,33,178,115,170,210,52,41,183,109,118,204,248,152,158,158,238,236,236,52,191,136,34,128,56,12,163,122,
60,130,193,160,4,204,96,194,33,223,77,162,131,21,124,208,14,241,162,114,246,88,44,214,215,215,7,157,54,213,120,145,8,57,203,88,134,219,196,237,118,59,157,206,80,40,116,248,240,97,116,195,149,122,187,106,
101,200,103,208,200,86,219,176,68,143,176,143,63,57,57,73,243,29,70,21,22,181,150,13,122,8,252,3,215,32,253,218,249,38,112,22,150,173,2,200,126,114,183,38,101,137,43,36,3,6,188,168,168,104,213,170,85,
32,200,164,141,7,5,103,210,233,116,85,85,21,197,103,240,67,34,145,64,117,43,197,194,248,235,204,204,140,147,52,4,121,82,8,31,65,234,4,154,53,27,225,220,0,113,136,43,86,172,240,249,124,46,151,11,194,67,
144,1,147,102,139,176,92,83,177,76,142,251,184,64,177,239,97,105,242,29,38,38,38,32,0,38,55,52,69,61,178,236,71,67,228,155,220,205,11,166,207,18,133,250,135,63,252,1,74,234,87,95,125,181,154,26,191,250,
234,171,63,253,233,79,51,119,48,50,252,9,191,86,87,87,95,117,213,85,31,251,216,199,214,173,91,135,45,225,134,27,110,248,227,31,255,248,232,163,143,222,112,195,13,50,101,150,117,159,108,226,23,23,23,111,
217,178,229,220,185,115,225,112,184,183,183,119,201,146,37,25,14,131,95,65,138,94,249,253,254,202,202,74,244,253,1,20,5,2,90,166,222,116,36,49,233,75,166,162,169,170,88,237,58,33,178,33,195,198,130,236,
252,152,97,90,94,122,213,161,102,137,90,90,90,10,188,163,172,145,29,14,71,87,87,215,249,243,231,183,110,221,234,247,251,25,157,149,58,146,2,75,152,208,8,217,142,148,29,82,147,101,131,31,96,41,155,193,
159,91,237,160,166,114,36,192,18,178,78,151,10,86,18,196,41,121,113,150,98,114,102,19,99,110,110,174,179,179,51,43,43,11,1,90,54,45,89,214,200,8,32,255,59,245,0,22,22,22,198,199,199,199,198,198,200,123,
2,131,129,69,189,122,168,8,174,52,148,29,66,253,21,54,178,96,130,112,90,174,232,127,60,255,128,108,154,146,117,221,221,221,64,109,75,209,193,138,138,10,96,248,178,178,178,202,202,202,0,171,0,12,151,35,
92,44,203,88,44,86,88,88,8,20,7,93,216,237,98,116,97,97,225,182,109,219,222,126,251,109,74,69,227,38,165,54,28,158,204,207,207,247,120,60,184,178,60,171,177,88,12,253,94,89,29,242,87,167,52,15,228,131,
88,113,204,79,115,115,115,49,110,50,163,106,67,67,67,117,117,53,228,208,170,170,170,186,186,186,208,197,195,53,174,168,168,128,61,165,73,74,84,235,137,63,128,73,76,104,58,241,21,8,223,44,57,229,20,142,
107,66,77,14,177,171,203,169,238,69,70,234,55,223,124,115,114,114,210,225,112,252,240,135,63,116,58,157,215,93,119,29,215,199,75,47,189,244,192,3,15,40,118,156,229,56,216,114,46,228,118,187,47,191,252,
242,155,110,186,105,219,182,109,136,203,92,187,95,253,234,87,191,253,237,111,55,54,54,178,44,82,97,26,63,208,254,38,39,39,167,161,161,97,122,122,58,16,8,156,58,117,170,188,188,92,33,159,76,137,34,37,124,
204,124,193,237,118,67,29,233,98,248,102,102,91,195,242,215,204,24,109,2,90,104,238,110,153,29,91,118,15,212,85,219,183,111,223,23,191,248,69,156,240,170,170,170,112,56,140,28,132,121,10,248,162,175,189,
246,90,117,117,181,196,225,153,8,72,222,24,150,249,187,57,216,177,91,81,131,131,131,64,125,89,182,224,44,223,77,237,118,248,95,114,124,130,80,133,222,160,52,69,204,92,185,155,44,106,28,249,208,208,16,
250,203,132,102,202,113,22,113,177,166,116,134,244,182,31,24,24,128,187,43,145,75,177,88,12,32,7,21,163,85,78,45,213,238,217,230,150,146,26,136,63,64,22,179,217,34,197,114,57,144,39,108,87,237,82,233,
116,26,178,227,245,245,245,80,231,168,174,174,46,47,47,151,137,133,207,231,67,110,62,54,54,198,146,78,94,148,233,233,233,217,217,89,186,11,89,174,4,94,53,159,207,119,197,21,87,188,243,206,59,32,76,76,
78,78,246,247,247,159,61,123,246,204,153,51,63,250,209,143,80,115,100,103,103,215,213,213,225,67,185,222,128,206,150,179,83,249,175,83,222,255,124,64,8,9,170,134,88,10,0,0,33,235,230,214,87,89,89,185,
108,217,50,246,61,42,42,42,58,58,58,0,114,170,172,172,164,145,79,6,30,148,76,100,120,249,177,103,178,101,142,7,12,41,80,104,72,30,138,210,55,144,247,67,52,26,181,164,165,100,134,115,192,124,151,71,248,
253,239,127,223,233,116,94,127,253,245,243,243,243,247,220,115,207,139,47,190,168,38,69,42,161,51,77,231,240,184,230,154,107,46,187,236,178,29,59,118,160,145,162,46,70,118,118,246,170,85,171,8,165,84,
77,39,6,107,105,119,139,215,180,180,180,196,227,241,100,50,185,127,255,254,15,124,224,3,230,32,69,230,179,242,200,205,0,106,41,244,174,122,106,69,69,69,160,146,154,82,100,106,80,33,189,33,84,228,149,89,
60,10,67,101,245,43,59,152,150,106,253,118,154,74,144,64,67,100,148,98,8,40,48,71,71,71,199,199,199,151,47,95,14,223,101,230,146,50,23,83,223,200,78,252,211,52,82,225,35,157,78,239,221,187,119,122,122,
218,235,245,74,232,139,37,56,207,92,138,106,42,46,31,144,196,147,28,19,169,112,32,233,112,150,64,14,54,16,6,7,7,143,29,59,134,250,26,41,164,116,25,183,228,235,203,209,46,222,228,220,185,115,232,31,74,
237,223,133,133,133,120,60,174,24,67,50,167,182,180,194,194,51,201,100,18,253,98,64,33,145,228,201,15,85,126,111,156,34,230,229,229,85,87,87,43,40,81,36,18,65,172,200,203,203,91,179,102,13,230,16,42,121,
2,23,52,16,8,96,54,206,97,157,10,89,88,201,236,163,154,77,118,233,21,91,80,80,240,228,147,79,118,118,118,78,78,78,210,17,244,200,145,35,239,127,255,251,81,211,215,214,214,238,221,187,87,109,153,241,120,
28,165,170,121,138,156,202,195,155,173,103,138,172,75,49,70,68,109,100,61,133,133,133,107,214,172,145,119,111,118,118,246,154,53,107,134,134,134,154,155,155,217,211,48,213,218,50,219,21,75,236,151,84,
37,199,14,31,137,68,48,197,82,43,64,113,11,113,106,102,102,102,44,65,145,150,89,15,254,61,118,236,216,241,227,199,213,193,124,247,187,223,117,58,157,135,14,29,66,116,206,32,166,97,14,106,182,108,217,178,
125,251,246,247,191,255,253,62,159,15,113,217,4,246,194,72,151,115,115,82,108,84,116,150,209,74,162,101,218,218,218,30,120,224,1,184,219,221,114,203,45,234,253,9,206,145,62,158,57,57,57,242,2,89,166,90,
178,181,197,53,128,156,212,12,199,178,69,136,25,61,44,81,236,74,66,98,135,77,20,132,37,111,208,228,34,90,102,244,228,251,42,200,60,184,242,56,123,221,221,221,129,64,96,249,242,229,228,178,74,181,73,165,
235,100,66,226,44,15,149,24,106,176,207,161,232,15,234,128,84,233,148,47,179,67,238,203,111,93,90,90,10,153,74,201,94,65,18,173,190,160,233,18,128,55,1,88,5,246,161,232,3,164,211,105,224,232,101,81,98,
41,142,161,24,197,36,61,205,207,207,15,12,12,160,99,43,27,187,188,154,168,92,193,37,206,156,68,3,58,141,131,228,149,130,221,37,19,121,9,191,147,24,86,9,155,147,177,133,132,59,128,223,65,131,144,198,149,
114,201,121,189,222,112,56,92,81,81,193,148,197,204,75,168,10,11,120,143,89,222,29,58,116,232,212,169,83,39,78,156,232,236,236,132,54,22,69,248,112,132,221,221,221,219,183,111,199,177,249,124,190,130,
130,2,14,21,28,239,234,187,74,20,150,220,186,156,230,233,131,213,133,92,169,18,149,2,206,66,97,97,225,166,77,155,148,121,18,176,129,110,183,123,116,116,116,98,98,194,239,247,23,23,23,75,217,57,75,167,
6,149,170,72,27,121,108,6,74,165,48,22,139,129,127,169,218,217,42,161,6,120,249,111,106,110,236,221,187,247,169,167,158,98,247,77,30,231,119,190,243,29,21,139,21,76,194,33,236,192,161,226,120,249,229,
151,127,240,131,31,132,197,36,219,118,42,122,162,115,202,227,204,201,201,33,104,79,74,20,81,123,196,82,205,202,229,114,97,251,61,126,252,120,123,123,251,202,149,43,137,107,150,205,40,217,197,226,196,195,
12,202,42,219,146,246,107,232,12,2,138,47,81,37,10,123,15,145,254,137,137,9,78,63,160,79,11,183,114,25,142,161,210,137,75,108,194,185,236,102,134,106,92,182,127,255,126,36,131,128,73,153,253,7,25,140,
48,210,89,88,88,232,237,237,109,104,104,160,155,156,201,140,55,53,136,101,223,211,204,136,241,204,232,232,104,71,71,7,143,13,51,118,8,249,95,80,10,78,229,203,229,229,229,168,87,84,243,122,255,254,253,
91,182,108,49,145,188,217,217,217,241,120,28,100,43,132,60,12,147,248,192,248,29,190,242,60,33,125,125,125,106,159,147,253,4,115,133,128,237,173,162,179,10,211,40,219,33,234,194,254,131,68,221,49,181,
164,137,176,204,60,176,150,192,91,70,132,149,97,90,170,116,42,210,10,39,156,152,111,243,132,199,98,49,96,239,76,88,30,32,164,32,142,90,234,138,144,145,64,132,27,154,78,61,61,61,221,221,221,103,206,156,
57,121,242,36,130,50,123,53,57,57,57,48,198,100,239,238,212,169,83,114,145,215,213,213,29,63,126,92,158,97,120,201,131,206,170,210,29,167,162,111,97,140,8,165,40,137,126,101,224,195,198,181,118,237,90,
75,187,70,76,96,243,242,242,162,209,232,192,192,64,118,118,54,244,173,149,4,154,226,243,88,86,145,82,102,72,173,18,26,184,73,4,165,106,116,192,14,199,12,196,196,129,171,72,125,254,252,249,39,158,120,66,
230,83,25,180,141,236,26,205,197,197,197,87,93,117,213,230,205,155,171,170,170,204,184,172,162,115,126,126,126,101,101,165,138,11,170,44,96,103,67,237,133,42,152,18,6,247,135,63,252,161,166,166,6,112,
122,187,212,149,162,1,153,229,141,44,3,10,212,144,51,36,197,160,56,7,131,65,69,195,1,27,147,8,28,135,225,23,254,183,66,161,229,34,238,238,238,230,26,86,78,219,42,58,35,81,194,95,135,135,135,99,177,88,
69,69,5,198,30,138,107,163,82,123,148,5,188,171,21,235,129,47,123,245,213,87,37,143,14,47,67,103,22,133,191,228,1,51,110,202,245,70,226,76,52,26,149,166,69,84,203,124,248,225,135,243,242,242,214,175,95,
159,76,38,199,198,198,2,129,64,60,30,159,154,154,154,152,152,128,184,10,254,69,193,174,130,254,201,147,39,99,177,24,142,45,157,78,191,249,230,155,227,227,227,106,1,72,11,43,153,115,160,199,130,118,45,
219,11,230,26,96,38,135,150,52,234,93,41,33,36,203,65,185,24,204,65,58,196,248,233,132,64,33,80,102,51,68,227,200,77,142,36,100,121,5,225,39,192,24,205,37,132,174,41,82,126,83,159,132,210,143,120,4,2,
129,193,193,193,254,254,254,142,142,14,98,45,164,207,156,236,129,128,127,128,24,61,56,56,56,62,62,14,212,108,118,118,118,125,125,253,193,131,7,21,99,72,66,78,45,2,52,235,95,68,88,244,239,32,169,165,124,
190,231,231,231,151,47,95,14,133,39,69,115,68,112,7,235,28,19,216,133,133,133,64,32,16,8,4,202,203,203,75,75,75,41,79,126,49,238,191,50,15,146,117,150,244,177,151,108,23,25,169,9,77,191,72,228,198,224,
224,224,15,127,248,67,181,127,40,222,135,93,164,134,62,103,123,123,251,182,109,219,154,154,154,216,201,202,192,78,94,88,88,40,43,43,131,183,141,10,142,176,170,148,210,69,50,156,217,197,104,118,72,22,23,
23,159,122,234,169,59,239,188,211,196,96,241,203,42,227,84,75,226,137,202,82,51,39,182,242,255,130,96,102,190,97,42,149,58,125,250,52,56,23,152,49,88,90,149,95,48,46,155,248,45,181,61,72,37,48,185,96,
40,36,32,113,153,169,84,106,100,100,164,180,180,20,16,87,9,62,145,23,203,78,97,71,149,186,123,247,238,133,91,135,217,101,198,57,145,24,83,53,104,146,1,139,178,21,234,227,134,135,135,119,238,220,25,12,
6,191,247,189,239,173,92,185,18,66,125,48,205,224,12,138,33,204,156,67,134,195,97,72,23,65,185,98,231,206,157,72,240,205,37,45,181,56,200,22,73,165,82,48,253,146,141,5,149,62,43,167,49,64,146,129,41,102,
18,141,119,179,164,92,155,134,220,20,157,199,23,148,4,22,185,176,41,199,172,212,83,85,140,94,92,92,108,108,108,84,181,2,136,187,152,212,169,237,54,55,55,55,153,76,14,15,15,247,245,245,13,13,13,97,12,198,
154,158,249,178,212,26,229,15,200,163,41,131,113,234,212,41,112,223,230,231,231,171,170,170,80,43,243,128,177,35,198,227,113,152,184,75,84,162,51,26,141,18,114,59,59,59,27,10,133,16,163,163,209,104,118,
118,54,128,123,82,172,160,189,189,29,195,80,249,70,20,45,34,9,162,184,184,24,105,20,190,109,56,28,14,135,195,5,5,5,126,191,31,55,131,229,120,208,242,87,137,159,83,92,243,201,201,73,191,223,111,114,70,
167,167,167,165,99,161,165,58,146,164,240,75,202,137,73,195,177,51,118,203,203,203,91,177,98,197,198,141,27,129,169,68,26,75,199,69,133,155,145,157,220,198,198,70,0,218,204,224,136,212,9,111,165,128,195,
202,84,219,204,160,241,137,83,83,83,123,246,236,129,194,53,151,41,191,8,22,122,102,108,134,188,51,85,27,218,82,184,135,229,60,196,121,77,170,55,49,148,96,99,71,163,81,44,24,102,121,150,192,9,203,184,108,
242,128,176,250,87,173,90,197,232,44,83,96,246,49,217,66,81,126,149,72,249,33,15,207,145,50,113,47,114,164,97,57,184,147,105,242,145,35,71,50,64,185,33,6,233,243,249,212,184,73,118,63,208,43,199,246,28,
8,4,130,193,224,153,51,103,66,161,208,240,240,240,232,232,104,65,65,1,54,128,156,156,156,99,199,142,45,91,182,140,36,61,146,125,164,130,35,255,69,109,113,244,232,81,36,88,123,247,238,61,120,240,96,6,205,
32,229,3,139,204,29,36,32,19,198,103,217,232,144,163,179,161,161,33,220,245,166,140,159,146,142,178,196,5,74,201,127,130,145,144,62,131,239,87,82,82,66,200,166,73,212,146,49,26,162,178,208,144,144,119,
144,215,235,133,226,27,49,236,19,19,19,147,147,147,129,64,0,156,38,178,31,101,238,207,141,208,188,154,252,23,161,117,97,97,225,204,153,51,239,125,239,123,121,91,53,52,52,72,36,130,130,54,201,165,238,124,
248,225,135,209,41,134,191,11,228,254,240,157,161,122,142,37,133,85,213,208,208,208,220,220,44,117,220,213,64,86,46,178,133,133,5,84,22,188,174,201,100,242,220,185,115,67,67,67,21,21,21,244,78,207,32,
147,111,78,255,205,77,18,221,37,185,151,2,163,35,119,233,12,180,130,100,50,249,127,254,207,255,81,142,106,38,164,87,21,116,43,86,172,0,239,134,144,12,114,91,73,235,84,72,97,154,120,173,88,177,66,226,196,
85,200,67,113,42,123,241,118,254,9,242,25,57,242,94,88,88,56,120,240,96,99,99,99,109,109,173,73,86,84,53,71,6,20,135,169,145,6,109,35,204,27,213,248,40,28,14,79,77,77,41,12,165,60,99,208,204,149,58,3,
24,220,99,233,231,231,231,179,45,163,160,193,150,11,44,67,186,173,154,146,166,1,152,204,85,105,86,61,63,63,31,139,197,92,46,151,73,240,165,71,6,211,52,179,15,238,112,56,94,124,241,69,50,29,236,176,219,
156,160,40,101,24,30,9,108,134,112,72,183,223,126,187,228,79,229,230,230,38,18,9,144,12,17,112,135,134,134,0,202,68,194,33,237,113,37,208,13,159,114,250,244,105,148,228,207,63,255,188,164,119,219,93,110,
185,18,176,167,218,161,170,45,37,53,40,80,12,126,51,208,29,244,142,81,146,176,178,185,108,134,105,220,89,56,45,200,126,144,100,120,60,30,236,169,20,126,179,235,64,202,63,1,179,81,86,86,38,85,22,208,227,
10,133,66,225,112,120,114,114,50,20,10,97,18,206,160,172,122,253,150,24,80,153,80,51,20,112,173,30,62,124,88,22,43,141,141,141,199,142,29,147,185,38,61,81,145,68,51,70,59,251,250,250,242,243,243,1,137,
195,187,131,53,139,83,22,10,133,16,172,129,105,135,133,149,42,48,45,83,48,92,24,96,221,148,163,229,252,252,252,200,200,200,200,200,72,89,89,25,181,211,236,200,29,166,115,187,252,20,159,207,215,219,219,
219,219,219,219,212,212,196,146,71,194,182,46,216,220,184,247,222,123,149,39,155,101,209,141,83,95,87,87,215,212,212,212,214,214,6,66,141,93,19,67,205,93,153,49,85,86,86,46,89,178,196,18,202,35,239,121,
56,129,170,216,164,12,50,204,12,90,105,232,188,254,250,235,31,253,232,71,1,148,228,248,20,27,173,227,66,15,59,252,175,186,103,56,204,25,29,29,85,102,34,14,195,238,0,153,242,138,21,43,0,79,38,72,25,48,
59,42,233,40,28,52,18,37,174,76,121,74,101,79,147,142,68,10,206,175,96,194,232,251,99,33,81,61,71,202,186,162,41,7,196,149,29,14,90,193,48,200,153,134,20,184,157,189,128,188,153,81,219,154,100,98,252,
138,254,15,69,130,100,53,147,72,36,56,107,2,237,222,227,241,64,178,71,109,57,106,205,15,15,15,79,78,78,142,142,142,62,255,252,243,202,79,196,174,113,71,148,49,184,230,230,124,66,161,247,36,59,140,40,11,
156,70,108,30,208,251,247,120,60,196,147,73,105,29,57,119,129,202,7,85,44,120,60,192,102,192,45,23,155,28,217,46,148,252,182,99,117,203,123,109,112,112,16,104,10,199,187,38,209,193,96,48,16,8,192,52,0,
11,131,4,5,46,18,222,65,204,223,229,243,236,68,203,208,12,70,34,142,112,122,122,122,96,96,160,190,190,30,199,80,83,83,67,94,56,91,184,127,65,110,136,217,85,78,73,73,201,220,220,28,113,130,224,44,72,252,
135,207,231,203,203,203,43,46,46,6,82,196,206,28,203,116,21,194,214,68,18,173,178,2,195,101,152,152,152,192,236,72,78,93,51,128,144,44,11,76,24,119,186,221,110,196,62,52,43,44,59,167,234,150,187,239,190,
251,246,237,219,119,193,80,229,245,122,87,172,88,241,222,247,190,119,233,210,165,21,21,21,74,171,65,137,73,170,39,249,239,170,85,171,26,27,27,45,193,255,234,8,209,239,187,200,220,153,107,142,163,39,28,
222,252,252,124,36,18,89,178,100,137,252,226,178,132,183,59,51,74,196,93,170,24,82,205,135,7,16,12,6,207,159,63,47,153,169,144,105,79,38,147,0,249,243,118,69,202,3,243,64,37,181,193,201,135,66,127,75,
137,24,51,242,202,141,176,170,170,106,253,250,245,38,234,64,197,62,169,131,76,217,7,26,31,75,193,91,170,212,95,240,129,11,58,53,53,181,114,229,202,138,138,138,146,146,18,64,199,24,179,228,59,75,81,23,
116,144,153,155,227,22,0,237,13,207,28,56,112,0,34,209,228,245,129,1,33,151,77,52,26,45,41,41,33,61,93,29,24,187,19,93,93,93,135,14,29,122,245,213,87,213,142,165,218,125,234,234,51,188,170,166,182,221,
76,66,154,126,200,205,73,21,16,179,179,179,84,19,181,172,126,22,23,23,161,77,168,34,64,97,97,161,215,235,245,122,189,148,146,151,62,217,82,236,55,3,115,7,241,33,157,78,71,34,145,193,193,193,80,40,68,81,
67,6,83,58,46,89,222,107,170,176,147,100,125,213,12,132,152,45,223,164,162,162,162,165,165,133,42,8,99,99,99,19,19,19,132,50,75,25,94,4,250,63,247,85,80,128,32,113,128,28,176,60,56,36,164,133,133,133,
59,118,236,144,13,108,187,208,108,158,17,54,224,41,209,45,173,104,112,219,196,98,49,112,5,1,86,205,140,18,85,63,228,230,230,162,19,15,177,127,165,83,101,71,62,206,202,202,122,228,145,71,158,126,250,233,
12,209,185,160,160,96,233,210,165,107,215,174,93,177,98,133,223,239,103,92,150,61,68,21,136,149,224,47,182,116,151,203,181,118,237,90,96,233,101,241,37,231,48,106,164,67,213,65,75,218,136,153,26,12,15,
15,51,25,68,13,8,244,187,203,229,226,40,50,179,178,176,37,240,75,134,78,126,92,34,145,192,52,24,44,115,75,233,72,204,184,193,10,75,38,147,176,40,46,46,46,246,251,253,42,46,19,201,39,57,11,234,193,78,154,
12,217,50,161,94,191,126,61,106,59,69,30,81,243,67,34,58,56,80,193,128,200,212,117,145,13,43,121,207,155,250,62,89,89,89,193,96,16,43,220,237,118,151,151,151,55,52,52,248,253,126,64,152,84,222,45,47,61,
147,47,208,136,225,58,38,143,97,114,114,242,228,201,147,82,148,28,117,134,204,88,113,239,0,11,100,121,120,11,11,11,29,29,29,79,63,253,52,136,221,150,155,177,146,84,148,62,27,132,186,170,212,202,114,174,
104,158,37,165,18,12,244,253,204,204,76,56,28,134,8,140,157,164,123,97,97,161,148,85,42,44,44,132,216,131,132,162,115,193,32,188,202,219,220,140,206,51,51,51,177,88,44,20,10,133,66,33,244,3,149,65,48,
233,2,102,151,220,188,221,164,60,134,138,212,252,53,26,141,82,102,14,79,166,82,169,109,219,182,241,197,233,116,186,179,179,83,6,104,41,162,196,34,245,207,156,105,116,136,208,59,166,51,33,50,211,100,50,
249,171,95,253,10,176,115,187,208,108,201,7,229,62,12,126,23,126,198,45,129,132,11,47,0,98,100,126,126,126,98,98,34,24,12,122,189,222,242,242,114,233,169,99,217,158,230,51,121,121,121,62,159,47,22,139,
193,17,125,207,158,61,55,223,124,179,101,115,67,170,140,62,255,252,243,143,62,250,168,229,106,131,236,78,109,109,45,16,202,100,253,169,125,210,196,105,152,243,192,249,249,249,210,210,210,213,171,87,3,
182,136,101,74,216,162,18,192,147,223,52,47,47,15,11,40,179,199,32,127,144,134,141,242,172,158,61,123,182,178,178,18,123,240,5,163,179,89,0,217,105,123,70,163,81,104,233,73,253,44,19,51,167,196,60,167,
167,167,85,115,89,190,57,250,125,150,8,7,203,142,167,57,136,147,209,80,118,81,213,20,78,150,162,102,154,44,89,151,216,35,165,96,191,121,162,166,167,167,97,119,41,159,164,164,36,111,51,164,69,224,106,203,
129,18,242,83,238,253,82,226,3,182,68,252,178,82,153,203,241,174,6,60,140,163,250,250,250,218,218,218,168,160,68,210,48,56,20,191,254,245,175,37,159,219,146,207,98,249,224,168,208,227,241,196,98,49,138,
119,203,174,177,106,250,155,132,0,41,42,139,122,26,227,241,243,231,207,87,87,87,115,24,46,99,28,219,89,136,212,232,56,33,83,100,238,40,23,21,96,133,74,195,83,125,151,129,129,1,236,19,53,53,53,156,0,201,
188,155,224,25,73,238,101,219,68,250,169,202,230,140,106,46,177,1,77,182,186,220,117,206,158,61,139,110,15,62,189,181,181,149,173,115,21,90,231,230,230,216,8,202,88,35,207,204,0,0,32,0,73,68,65,84,129,
8,3,62,27,167,12,0,198,64,32,128,20,253,75,95,250,210,170,85,171,44,153,69,25,244,12,149,82,159,227,93,239,65,166,189,200,92,84,91,0,125,192,72,36,130,112,166,136,218,118,189,14,96,86,178,179,179,255,
240,135,63,124,225,11,95,240,249,124,239,121,207,123,236,184,0,14,135,227,245,215,95,255,250,215,191,110,146,161,75,74,74,234,234,234,154,155,155,203,203,203,33,240,40,19,43,37,189,168,82,105,19,27,144,
149,149,213,218,218,10,218,8,238,118,202,177,90,50,152,149,101,31,208,69,25,48,136,242,123,65,234,69,61,112,134,167,166,166,40,24,157,57,95,54,211,43,83,9,12,34,59,48,134,176,164,44,114,103,34,215,6,141,
14,220,159,141,141,141,42,89,144,15,222,6,38,145,82,78,164,37,42,148,175,252,187,191,251,59,203,211,197,235,130,215,203,89,31,185,97,230,67,102,130,138,208,175,150,226,232,232,168,41,179,121,242,228,73,
76,255,217,50,230,152,157,139,4,97,165,176,176,16,91,41,74,31,90,199,1,2,248,242,203,47,227,255,218,249,153,225,43,3,110,204,21,203,143,56,112,224,192,35,143,60,34,101,149,44,27,11,106,36,40,151,1,123,
241,69,69,69,216,143,237,106,101,75,147,35,153,213,66,161,148,191,122,189,222,68,34,193,237,74,93,44,152,112,211,221,202,92,189,100,72,75,162,185,234,254,203,35,132,142,80,109,109,173,156,207,171,158,
187,44,38,228,178,79,165,82,143,61,246,152,207,231,67,162,163,98,160,36,211,98,41,198,98,177,201,201,73,201,222,224,15,126,191,159,170,159,57,57,57,157,157,157,104,91,217,169,10,207,207,207,59,121,210,
193,79,13,6,131,114,175,190,245,214,91,119,236,216,161,200,69,142,140,54,13,150,15,143,199,3,178,141,74,126,113,51,144,98,32,101,74,64,212,246,249,124,178,39,110,25,104,10,10,10,10,11,11,83,169,20,146,
226,187,239,190,251,196,137,19,15,61,244,144,229,114,236,236,236,252,198,55,190,33,255,123,105,105,169,207,231,195,208,192,206,183,208,60,215,234,161,166,88,217,217,217,235,215,175,135,80,20,27,247,51,
51,51,228,233,218,193,84,100,107,200,210,12,197,140,206,216,240,44,53,33,177,225,117,119,119,47,93,186,212,241,183,60,76,6,54,16,47,103,207,158,133,143,187,170,242,148,14,9,82,84,213,210,201,140,116,54,
11,133,204,140,21,245,12,154,125,234,138,203,38,3,37,253,100,175,223,18,179,172,0,206,14,225,37,168,62,61,24,12,154,174,128,176,77,162,174,180,165,228,19,10,115,92,32,9,208,166,223,85,118,118,54,172,227,
200,185,183,235,45,32,11,59,121,242,228,214,173,91,249,5,23,22,22,222,126,251,237,103,158,121,198,78,147,192,14,228,96,55,42,4,9,11,80,98,5,98,51,123,14,82,130,131,59,61,230,213,60,128,185,185,57,144,
72,33,26,193,211,194,57,182,228,164,88,170,199,64,19,6,49,68,249,194,168,107,135,123,28,155,162,29,251,140,82,22,160,242,114,24,120,242,228,201,223,255,254,247,169,84,42,16,8,124,246,179,159,101,131,65,
101,111,204,175,129,3,161,36,158,10,35,103,206,156,89,191,126,61,79,233,234,213,171,135,135,135,45,59,19,200,231,28,14,135,147,124,68,32,112,229,65,95,121,229,149,183,222,122,43,231,60,138,40,105,199,
64,179,203,212,74,74,74,112,129,21,62,95,42,173,200,209,138,227,93,63,118,12,0,209,150,178,11,40,110,183,251,248,241,227,84,224,253,237,111,127,59,52,52,244,248,227,143,147,26,195,113,246,199,63,254,113,
104,178,120,189,94,196,101,142,35,88,40,89,202,74,41,138,182,66,110,120,189,94,218,208,121,60,158,109,219,182,113,95,33,96,158,98,55,150,183,13,214,25,207,143,203,229,194,77,75,201,108,243,245,170,197,
161,196,76,120,186,198,198,198,170,171,171,165,151,213,69,82,132,100,199,96,108,108,172,175,175,143,110,243,230,120,132,137,48,139,247,12,226,109,166,190,168,36,46,75,64,155,57,60,176,12,211,185,185,185,
148,40,80,27,152,68,149,72,175,101,108,198,153,103,30,102,251,88,202,98,224,86,84,192,202,209,209,81,75,72,159,10,214,232,132,166,82,41,212,179,0,45,0,128,132,23,120,60,30,183,219,141,21,37,17,90,132,
180,203,94,196,204,204,204,241,227,199,55,111,222,204,230,245,158,61,123,228,109,171,180,12,51,67,56,100,35,5,237,111,228,79,236,188,93,80,236,80,234,132,80,111,83,154,154,74,23,205,233,233,105,176,156,
25,166,57,153,180,108,151,193,132,15,9,165,227,93,47,61,179,33,70,40,183,203,229,106,109,109,61,123,246,172,221,25,96,81,203,118,63,238,214,167,158,122,234,192,129,3,136,12,233,116,250,197,23,95,188,238,
186,235,24,187,113,84,216,59,217,101,134,132,39,240,54,56,111,156,39,65,68,16,132,137,100,50,185,176,176,208,218,218,250,194,11,47,216,209,208,16,103,254,242,221,74,74,74,228,23,104,105,105,249,231,127,
254,103,222,117,248,194,202,161,210,97,229,172,97,151,245,0,120,23,137,68,76,196,146,212,44,86,87,23,47,67,66,157,159,159,143,73,183,153,68,204,204,204,60,252,240,195,242,116,191,253,246,219,215,94,123,
237,19,79,60,1,223,44,116,78,239,188,243,206,185,185,185,218,218,218,178,178,50,9,197,87,24,29,211,81,141,53,132,37,138,0,247,124,110,110,46,196,175,215,172,89,131,84,200,20,52,128,59,134,93,9,194,230,
41,251,39,68,233,41,220,152,58,213,242,156,176,56,229,182,55,59,59,123,252,248,241,45,91,182,100,48,13,82,251,171,140,209,243,243,243,93,93,93,96,145,89,178,34,37,226,2,89,161,114,99,162,204,136,29,114,
153,99,107,229,151,97,23,214,85,5,125,228,200,17,164,159,244,105,253,11,206,223,233,36,183,83,53,163,165,254,145,221,0,48,3,122,1,138,157,236,125,241,53,163,163,163,150,136,55,147,43,200,235,142,49,23,
128,76,178,15,211,218,218,122,242,228,73,51,125,38,35,76,2,105,131,193,224,217,179,103,157,78,231,192,192,0,104,111,118,136,213,139,199,89,34,80,202,250,195,229,114,81,174,221,242,13,85,64,96,230,139,
88,79,80,29,182,112,254,23,26,63,146,38,206,61,73,57,99,161,89,138,48,146,147,147,19,139,197,232,17,174,224,40,120,1,162,51,24,240,200,142,45,143,153,71,229,114,185,82,169,212,224,224,224,47,126,241,139,
80,40,36,123,152,189,189,189,39,78,156,88,181,106,149,36,100,179,43,133,22,185,203,229,194,146,163,126,63,53,248,179,179,179,199,199,199,171,171,171,65,80,192,130,223,185,115,103,111,111,47,203,77,121,
139,193,229,203,137,11,0,193,61,222,255,85,85,85,247,221,119,159,194,66,41,214,131,37,74,44,131,106,42,62,5,26,46,102,5,170,230,51,18,20,197,87,206,205,205,37,147,73,210,91,113,33,145,52,197,227,241,39,
159,124,82,181,11,78,157,58,181,117,235,214,23,95,124,113,229,202,149,145,72,228,35,31,249,72,103,103,231,234,213,171,205,56,165,152,108,50,107,150,218,184,118,9,53,99,250,218,181,107,235,235,235,45,13,
226,184,242,204,98,217,100,171,179,5,196,160,38,225,86,252,104,57,18,84,151,0,227,23,132,60,212,74,93,93,93,171,86,173,50,167,127,150,233,51,159,193,12,138,52,1,132,96,19,129,68,61,114,41,109,35,7,101,
146,45,162,198,119,10,205,162,208,14,23,217,229,192,15,128,12,241,198,150,233,152,108,46,75,100,180,217,9,145,87,193,196,24,224,5,193,96,48,22,139,153,112,123,212,43,23,204,157,153,110,243,12,72,48,9,
183,150,182,182,182,19,39,78,216,229,125,72,152,164,245,201,217,179,103,193,56,51,161,253,23,51,21,180,107,166,41,78,111,97,97,33,152,235,150,254,238,28,71,243,174,65,134,139,248,37,89,209,92,27,216,158,
193,192,224,181,51,57,232,76,224,194,225,48,179,25,160,108,105,219,70,230,36,206,161,223,239,111,105,105,193,97,20,21,21,145,145,104,71,133,67,93,181,115,231,206,103,159,125,86,249,182,224,5,187,119,239,
174,169,169,129,8,148,148,161,87,43,150,171,218,92,90,71,142,28,241,251,253,188,137,86,175,94,221,217,217,105,7,61,248,179,229,21,192,6,140,197,46,151,235,219,223,254,118,97,97,161,74,142,144,249,155,
69,141,29,238,221,50,25,241,120,60,114,50,35,151,178,130,25,65,102,27,219,35,209,99,248,249,153,103,158,249,216,199,62,246,157,239,124,135,251,231,207,127,254,115,25,220,25,110,162,209,232,213,87,95,253,
196,19,79,252,235,191,254,235,233,211,167,29,239,106,255,91,206,172,9,39,146,49,218,52,199,51,103,98,40,163,222,247,190,247,1,136,46,5,183,204,56,110,215,79,52,183,58,41,251,34,235,9,224,1,138,139,139,
65,158,166,254,81,238,187,15,220,237,200,179,0,225,130,79,205,248,248,184,36,55,94,144,150,50,61,61,13,23,122,28,140,169,131,193,129,6,94,128,244,153,88,99,89,171,90,146,253,212,67,214,103,23,35,3,109,
30,54,78,133,90,87,106,130,167,158,55,81,7,138,17,110,166,213,208,219,52,233,115,132,112,200,255,171,14,128,115,23,217,219,161,143,187,124,229,226,226,98,89,89,89,230,144,138,251,66,62,51,51,51,211,211,
211,115,49,20,164,139,236,114,152,211,23,224,222,44,9,83,230,132,141,124,46,172,4,229,188,39,237,234,33,110,135,151,241,245,10,124,54,55,55,23,12,6,49,174,68,90,138,183,130,110,34,223,25,47,46,43,43,131,
233,56,222,92,250,209,216,229,70,19,19,19,223,250,214,183,158,125,246,217,12,70,122,187,118,237,34,105,69,138,112,217,65,209,205,201,45,53,123,29,14,199,142,29,59,230,108,30,120,153,19,59,152,199,227,
97,45,243,239,255,254,239,205,205,205,42,125,150,5,108,6,116,129,195,202,200,85,213,17,94,175,87,170,220,102,184,99,85,241,24,141,70,31,123,236,177,159,252,228,39,67,67,67,120,230,129,7,30,248,208,135,
62,244,141,111,124,227,55,191,249,141,106,86,114,219,143,70,163,159,253,236,103,121,204,80,110,178,91,247,127,198,30,58,157,148,53,176,204,157,249,87,252,90,83,83,179,99,199,14,172,69,181,157,114,177,
242,174,163,76,224,5,239,31,236,231,76,145,76,173,75,143,199,227,245,122,231,230,230,160,14,174,132,129,84,158,14,231,8,140,251,229,125,165,26,190,124,49,80,204,242,101,0,11,154,91,20,64,244,210,167,89,
237,118,150,109,13,203,236,56,195,198,111,9,125,225,11,142,30,61,186,126,253,122,102,163,168,60,76,159,29,197,158,144,55,143,165,47,143,37,18,127,96,96,128,233,57,151,7,222,28,13,104,121,87,203,55,148,
20,39,89,61,216,129,73,26,26,26,6,7,7,73,63,179,140,164,24,91,241,153,115,231,206,89,226,61,20,12,206,241,183,63,228,166,14,218,17,173,27,148,52,7,175,163,148,189,69,208,145,13,104,118,144,229,48,48,149,
74,1,72,198,158,181,20,13,142,70,163,224,211,75,238,27,222,25,168,39,164,210,243,243,243,213,213,213,109,109,109,114,157,23,23,23,15,13,13,101,24,183,188,250,234,171,63,251,217,207,160,179,102,233,150,
139,31,66,161,208,254,253,251,183,110,221,42,191,172,37,43,66,17,103,240,120,231,157,119,96,254,13,210,70,75,75,75,121,121,249,200,200,136,234,111,20,22,22,110,220,184,113,227,198,141,206,249,249,121,
120,160,224,207,255,242,47,255,210,222,222,110,238,93,180,43,148,222,4,234,246,83,124,77,59,76,43,174,46,165,20,237,114,22,249,235,217,179,103,31,127,252,241,123,238,185,71,221,183,8,217,136,206,14,27,
255,121,245,51,32,138,126,191,127,126,126,30,4,10,115,45,74,116,148,12,199,132,151,202,232,188,121,243,230,173,91,183,90,246,112,165,142,135,84,167,132,76,160,195,198,46,203,236,84,152,133,164,67,184,
210,129,132,38,137,127,150,45,20,252,223,243,231,207,47,89,178,68,201,239,170,208,73,148,186,218,48,242,243,243,227,241,184,4,134,35,217,65,34,79,210,45,224,58,50,178,155,200,75,115,72,200,200,126,65,
89,59,85,54,170,0,138,211,69,122,148,37,69,91,141,251,212,237,100,250,164,200,207,138,70,163,129,64,192,82,253,117,97,97,129,13,104,51,137,166,148,176,250,238,236,62,155,110,29,160,218,198,98,177,37,75,
150,72,54,191,234,8,113,177,141,143,143,171,57,255,255,99,163,67,133,48,25,169,17,98,100,167,219,97,56,34,170,179,36,173,123,153,109,16,94,201,147,156,74,165,128,11,80,203,38,22,139,97,48,200,249,1,167,
44,164,83,227,191,44,89,178,4,10,253,202,66,136,13,116,245,206,137,68,226,7,63,248,193,158,61,123,20,245,95,38,58,242,130,246,245,245,65,235,70,42,145,73,15,57,19,119,43,241,105,208,34,79,165,82,32,145,
173,93,187,118,112,112,16,167,168,178,178,242,210,75,47,221,182,109,91,125,125,253,159,39,127,185,185,185,21,21,21,8,55,55,223,124,243,85,87,93,101,2,84,121,67,98,127,179,164,60,152,238,197,150,109,104,
135,176,34,197,108,196,97,227,117,196,166,207,147,79,62,185,111,223,62,105,159,158,217,161,53,243,207,108,152,160,39,0,179,116,203,183,82,98,175,114,102,40,249,63,117,117,117,138,224,39,163,51,97,237,
14,225,150,77,185,187,11,170,68,65,156,40,131,168,141,76,67,80,65,95,16,164,49,49,49,81,89,89,105,138,156,16,135,46,91,198,170,51,91,84,84,4,72,41,235,9,184,19,145,58,40,129,40,153,155,18,118,42,207,118,
83,65,203,245,102,137,187,39,67,143,219,140,29,54,35,3,204,206,174,169,210,213,213,101,142,218,249,51,98,183,249,182,140,206,170,187,194,63,89,102,208,24,241,167,82,169,51,103,206,212,213,213,145,20,106,
153,68,39,147,201,12,42,72,127,19,69,37,179,18,11,79,5,144,39,16,83,54,223,211,52,190,0,70,133,3,45,19,88,130,177,24,94,9,1,123,210,133,56,24,84,194,44,204,156,136,238,104,111,111,111,105,105,49,191,2,
116,44,100,128,198,227,248,241,227,247,221,119,223,216,216,152,132,69,170,18,71,174,22,188,219,190,125,251,46,191,252,114,24,48,170,6,154,229,186,146,67,227,147,39,79,214,213,213,33,65,156,155,155,187,
244,210,75,59,58,58,174,185,230,154,117,235,214,53,55,55,39,18,9,8,97,35,222,58,239,191,255,254,193,193,193,158,158,158,250,250,250,47,124,225,11,150,113,89,114,4,152,253,101,158,16,94,112,158,3,96,141,
93,46,19,10,133,222,126,251,237,23,95,124,113,96,96,96,106,106,10,64,162,204,139,207,196,44,155,209,217,237,118,23,21,21,133,66,161,202,202,74,132,191,146,146,146,88,44,166,104,90,50,187,36,92,140,11,
130,49,26,183,226,51,207,60,243,153,207,124,6,93,127,213,234,81,118,209,72,117,101,127,195,50,67,177,156,215,91,134,114,90,43,56,222,117,248,189,152,230,227,244,244,116,50,153,196,234,151,175,73,38,147,
145,72,4,220,45,187,176,88,80,80,64,31,207,133,133,5,200,137,165,82,41,44,41,75,238,18,14,219,229,114,213,212,212,216,197,101,41,236,105,122,173,94,12,56,250,240,225,195,112,108,145,205,52,20,203,230,
178,148,21,155,165,137,145,93,152,62,119,238,156,84,235,150,58,200,120,80,15,90,126,156,165,118,62,63,17,37,169,10,4,217,217,217,195,195,195,156,123,67,181,49,30,143,215,213,213,153,123,48,16,17,231,206,
157,83,188,228,12,139,65,213,28,106,34,119,49,32,22,170,221,99,229,168,24,45,177,128,18,254,196,239,142,196,25,17,89,190,51,9,35,179,179,179,88,165,185,185,185,115,115,115,160,34,75,248,13,147,104,78,
65,22,23,23,215,173,91,87,82,82,2,196,151,58,69,208,64,158,152,152,144,207,255,236,103,63,123,250,233,167,81,223,224,26,89,10,57,200,11,228,120,215,187,224,181,215,94,187,241,198,27,45,101,237,84,235,
89,197,238,253,251,247,95,125,245,213,236,179,111,216,176,225,231,63,255,57,71,169,50,1,234,239,239,119,22,20,20,172,90,181,106,203,150,45,59,118,236,80,32,42,51,82,67,1,4,55,176,93,66,100,71,75,51,99,
55,216,37,106,213,158,61,123,246,237,183,223,222,189,123,55,130,99,52,26,197,71,155,91,159,157,115,182,169,108,130,243,85,86,86,134,91,11,22,109,24,116,228,228,228,248,124,190,100,50,105,214,134,114,14,
70,116,186,164,123,34,160,204,204,204,156,62,125,122,237,218,181,150,122,214,204,38,164,254,139,221,166,98,169,188,170,96,158,10,166,74,131,133,139,79,136,48,7,135,248,3,211,103,212,143,8,223,51,51,51,
176,73,180,156,236,1,57,158,78,167,193,217,5,201,62,131,174,161,211,233,132,131,176,165,3,153,250,213,108,185,152,93,17,147,246,130,251,10,119,178,34,206,129,94,172,16,65,150,178,206,23,124,36,147,201,
158,158,30,210,65,205,254,6,96,209,234,198,102,223,217,172,20,229,216,208,204,191,158,122,234,41,117,249,66,161,80,44,22,131,152,162,60,21,232,125,35,201,176,179,40,50,147,232,11,198,113,179,115,109,234,
192,204,206,206,150,148,148,80,178,217,52,57,82,73,52,193,96,52,190,178,68,127,177,107,65,35,40,224,216,36,187,149,113,31,183,167,203,229,218,178,101,75,117,117,245,220,220,28,28,191,148,49,5,248,144,
252,185,167,167,231,7,63,248,65,111,111,47,85,198,236,80,55,102,250,60,63,63,15,229,159,147,39,79,66,149,91,33,134,21,25,85,117,249,78,159,62,77,241,94,156,34,168,140,229,229,229,193,232,11,127,141,68,
34,137,68,194,9,134,232,7,63,248,65,26,22,224,132,202,84,90,5,110,116,162,45,179,179,12,109,13,243,102,131,37,10,16,130,169,84,234,216,177,99,47,191,252,242,192,192,0,115,246,72,36,66,163,107,89,233,91,
94,84,83,116,74,54,79,171,170,170,80,134,211,64,128,147,104,135,195,81,84,84,148,159,159,31,14,135,85,187,67,161,125,89,65,163,207,195,211,5,109,170,202,202,74,211,109,0,35,111,100,61,42,203,176,116,249,
50,191,29,52,130,205,151,81,22,75,217,81,95,228,236,126,106,106,170,172,172,12,81,30,125,30,137,213,67,31,25,219,167,138,44,48,18,68,213,41,217,4,150,116,97,183,219,13,11,109,89,215,91,166,207,252,43,
209,208,153,135,132,50,111,194,18,71,30,199,196,132,152,25,137,153,35,168,28,167,78,226,168,20,81,158,236,80,182,167,158,125,246,217,209,209,81,16,13,208,40,91,181,106,149,60,51,144,224,144,55,54,141,
81,236,114,20,169,145,164,194,244,239,126,247,59,51,128,206,206,206,162,221,81,85,85,37,219,226,74,208,220,146,207,98,134,230,11,246,58,44,99,186,82,1,157,155,155,43,47,47,15,4,2,68,38,88,26,98,201,22,
31,239,38,19,188,44,241,215,120,6,106,151,120,144,141,44,175,11,166,250,87,92,113,5,201,192,200,192,64,31,83,219,124,113,113,113,52,26,125,250,233,167,127,253,235,95,195,182,84,38,206,25,210,103,105,113,
137,116,62,63,63,191,191,191,191,162,162,130,102,102,102,199,217,196,114,160,4,63,120,240,224,198,141,27,201,77,195,183,136,199,227,82,92,1,3,103,103,110,110,238,251,223,255,126,68,103,226,13,176,254,
72,205,82,35,123,152,176,92,76,68,182,180,246,81,178,38,241,120,252,249,231,159,127,251,237,183,19,137,132,28,72,66,67,157,159,110,218,37,216,33,49,85,152,46,47,47,247,249,124,8,241,114,186,8,99,5,62,
242,242,242,252,126,127,56,28,150,237,14,75,104,29,21,112,152,74,35,187,41,44,44,148,155,54,58,182,44,181,76,147,17,75,39,70,59,196,171,44,66,85,107,72,78,186,255,38,100,85,50,153,132,159,136,227,175,
13,68,248,130,177,177,177,231,158,123,110,195,134,13,176,61,70,197,0,67,226,204,74,44,120,67,16,130,96,126,102,201,214,51,211,103,179,225,131,23,4,131,65,208,145,36,90,75,202,29,236,222,189,27,163,90,
121,147,176,243,195,49,157,12,208,248,149,221,97,179,234,146,71,123,248,240,225,243,231,207,227,138,163,77,79,173,109,41,196,42,111,102,213,214,176,76,44,8,136,84,185,219,127,255,247,127,159,63,127,222,
238,194,13,15,15,71,34,145,214,214,86,80,251,6,6,6,16,188,204,24,45,59,0,102,221,105,215,91,179,116,8,180,108,100,35,137,206,201,201,169,172,172,12,4,2,60,6,69,187,103,212,150,150,140,28,156,2,24,142,
107,129,29,75,34,130,36,247,10,244,90,56,117,49,88,229,228,228,92,117,213,85,37,37,37,188,47,48,20,65,140,150,254,156,120,159,111,125,235,91,123,246,236,145,182,141,92,36,18,191,97,137,86,152,155,155,
3,10,155,47,59,122,244,40,16,29,118,1,221,114,254,113,250,244,233,237,219,183,75,201,4,199,95,139,29,65,205,163,181,181,213,185,105,211,166,226,226,98,75,241,83,132,233,116,58,157,74,165,216,25,65,39,
158,9,151,93,127,195,178,197,97,202,47,96,7,62,124,248,48,98,177,12,208,208,105,229,125,104,182,56,46,136,220,204,201,201,169,175,175,119,187,221,200,250,85,11,44,26,141,162,131,38,217,110,229,229,229,
212,62,85,49,90,54,248,164,42,21,50,113,80,200,224,73,136,98,138,77,118,243,192,236,8,178,118,33,149,93,14,165,165,201,68,233,127,145,65,59,222,149,175,82,77,64,213,254,14,133,66,175,189,246,90,101,101,
229,178,101,203,242,243,243,129,172,202,207,207,199,234,55,109,4,240,131,207,231,107,106,106,66,171,78,101,22,23,132,54,179,13,109,246,199,20,164,140,220,25,41,75,166,0,227,252,92,53,154,151,82,100,153,
209,68,248,22,187,119,239,86,112,96,84,24,64,160,115,147,230,167,72,48,128,221,249,7,114,209,244,76,202,206,206,254,221,239,126,151,185,91,149,76,38,59,58,58,90,91,91,199,199,199,51,83,159,48,145,150,
69,152,93,90,99,121,47,43,57,51,52,235,36,101,33,43,43,11,50,205,45,45,45,123,247,238,101,161,169,114,82,217,24,148,189,38,181,164,77,126,138,10,211,224,169,33,56,0,42,190,99,199,14,2,198,185,109,0,179,
145,74,165,66,161,80,105,105,41,222,231,133,23,94,248,220,231,62,7,134,145,50,240,149,191,154,49,154,65,131,209,89,162,188,78,158,60,73,57,57,179,227,236,176,242,121,56,125,250,52,151,141,73,182,64,115,
255,218,107,175,109,108,108,116,162,48,49,163,51,159,113,58,157,133,133,133,192,45,1,73,14,167,21,32,1,254,23,73,180,92,37,78,167,179,172,172,236,243,159,255,252,215,191,254,117,130,31,145,47,67,170,138,
61,166,11,54,55,212,15,69,69,69,13,13,13,25,244,22,226,241,184,233,126,157,149,149,85,92,92,92,80,80,64,45,109,169,127,36,153,232,44,211,88,106,1,104,220,214,214,134,217,174,221,172,50,67,81,169,28,57,
85,117,198,245,109,158,1,37,183,248,55,209,19,50,252,21,228,160,116,58,189,119,239,222,103,159,125,182,190,190,254,170,171,174,42,42,42,202,160,0,158,147,147,211,220,220,92,83,83,51,51,51,67,161,94,213,
197,179,236,114,72,220,139,73,27,81,164,112,243,188,69,163,209,201,201,73,40,35,43,133,110,199,95,203,246,219,37,233,25,198,241,207,61,247,28,220,155,212,23,167,211,7,44,4,165,188,162,41,118,108,158,103,
104,185,153,205,141,225,225,225,125,251,246,101,48,44,230,78,214,211,211,195,104,152,33,17,6,146,15,24,118,51,70,219,237,79,138,4,207,142,185,60,108,250,134,64,251,233,107,95,251,218,143,127,252,99,186,
6,171,174,23,25,40,234,228,152,130,83,12,136,150,183,60,120,61,169,84,170,164,164,228,178,203,46,171,168,168,176,91,192,232,160,130,177,125,223,125,247,253,236,103,63,99,170,46,231,129,234,87,185,179,
202,53,19,8,4,100,150,134,87,98,237,141,142,142,150,149,149,89,226,65,45,155,30,131,131,131,19,19,19,85,85,85,230,37,115,185,92,171,86,173,90,190,124,249,159,21,69,142,28,57,50,54,54,118,201,37,151,200,
232,166,216,98,232,222,130,168,130,14,81,36,18,241,251,253,166,231,185,165,176,161,195,198,224,128,171,164,169,169,233,227,31,255,56,164,17,17,142,193,146,96,71,198,18,101,145,65,171,197,239,247,163,73,
167,146,77,229,70,97,119,231,20,20,20,212,214,214,78,76,76,32,239,102,138,42,201,223,12,154,51,51,51,104,69,85,84,84,20,20,20,196,227,113,143,199,147,161,3,112,145,93,63,203,150,162,221,189,170,50,232,
139,36,140,93,48,166,103,103,103,119,119,119,143,142,142,98,237,6,2,129,39,158,120,162,173,173,173,181,181,213,242,56,221,110,247,170,85,171,96,154,103,89,185,103,70,200,153,96,59,249,122,120,217,64,252,
12,169,86,113,113,49,106,11,204,45,79,156,56,81,86,86,182,106,213,42,24,118,72,115,79,153,40,153,100,153,204,40,142,193,193,193,238,238,110,37,214,35,57,238,88,6,135,14,29,122,253,245,215,91,90,90,214,
172,89,163,70,70,150,107,0,190,33,166,74,109,118,118,246,253,247,223,255,191,88,36,236,231,90,250,165,2,46,130,59,203,174,143,97,2,153,85,76,144,210,93,42,43,138,199,227,151,93,118,217,230,205,155,239,
189,247,222,187,239,190,91,213,187,156,154,160,110,83,12,44,132,20,59,9,73,51,140,0,219,87,85,85,245,190,247,189,15,195,97,187,152,128,252,242,244,233,211,95,249,202,87,58,59,59,169,28,45,39,4,124,40,
99,29,149,243,142,143,143,75,195,120,194,111,240,65,3,3,3,240,19,176,43,13,205,247,60,117,234,20,3,52,78,111,65,65,65,91,91,91,83,83,211,95,93,214,172,172,172,161,161,161,197,197,69,233,55,72,14,37,69,
217,37,234,19,187,104,44,22,99,237,112,193,196,57,26,141,194,250,65,133,18,174,146,107,174,185,230,248,241,227,239,188,243,14,98,52,154,89,220,30,236,48,118,102,104,206,206,206,110,106,106,114,187,221,
138,152,160,140,18,112,153,195,225,48,190,130,37,138,179,170,170,42,20,10,97,70,161,236,138,165,209,31,208,160,145,72,4,50,76,83,83,83,240,230,177,75,153,51,223,123,202,14,70,30,207,197,7,232,139,143,
209,25,162,54,164,4,71,70,70,200,26,199,250,235,239,239,239,239,239,47,47,47,111,105,105,65,31,22,47,110,110,110,110,106,106,146,211,84,25,163,41,164,105,89,77,215,213,213,97,177,225,7,152,199,35,219,
90,190,124,249,226,226,226,51,207,60,195,210,106,110,110,110,124,124,92,209,133,113,24,19,19,19,187,119,239,94,182,108,25,4,236,37,243,69,245,61,136,146,52,199,247,42,55,124,246,217,103,21,173,217,242,
209,211,211,3,60,79,111,111,111,115,115,243,186,117,235,224,201,105,201,69,100,117,98,70,132,120,60,14,248,243,223,74,249,83,33,207,50,154,163,63,128,22,165,26,132,200,154,79,98,93,164,170,134,20,45,80,
241,212,233,116,174,89,179,102,126,126,190,169,169,233,155,223,252,230,87,191,250,85,51,8,224,63,18,90,39,55,15,68,109,51,152,168,225,19,30,137,68,162,185,185,249,170,171,174,194,180,223,178,158,227,251,
255,248,199,63,126,224,129,7,16,199,21,9,133,3,118,179,221,193,238,4,114,228,177,177,49,179,136,39,6,3,95,173,183,183,183,181,181,85,102,220,202,208,64,113,166,78,156,56,177,99,199,14,162,24,106,106,106,
96,172,58,59,59,43,183,28,103,86,86,22,60,198,59,58,58,32,166,167,252,223,76,223,82,124,210,244,244,180,4,141,219,237,117,161,80,40,18,137,192,73,193,178,85,202,55,252,194,23,190,208,213,213,53,50,50,
130,252,203,227,241,0,96,43,245,43,50,140,53,208,14,110,104,104,224,62,201,202,130,83,123,21,49,163,209,168,42,76,212,163,162,162,98,116,116,20,165,186,132,178,200,96,141,201,6,206,236,208,208,144,219,
237,158,157,157,109,107,107,35,114,227,34,67,176,124,129,229,243,193,96,80,157,106,199,187,50,73,129,64,96,104,104,136,228,76,203,4,4,182,149,202,223,90,153,150,14,15,15,159,63,127,190,163,163,99,114,
114,82,130,28,136,70,224,235,199,198,198,2,129,64,85,85,85,67,67,131,215,235,93,185,114,101,81,81,17,241,79,92,226,80,2,153,157,157,133,120,230,242,229,203,33,106,136,201,59,4,20,1,122,101,146,133,171,
15,82,134,165,4,57,102,241,193,96,208,114,248,54,51,51,115,248,240,225,174,174,174,173,91,183,194,80,85,209,88,120,108,20,246,180,180,250,38,100,53,18,137,168,242,197,210,205,186,191,191,159,32,206,115,
231,206,13,12,12,84,84,84,108,216,176,161,174,174,206,114,25,96,244,111,154,60,188,248,226,139,84,220,254,155,56,126,25,218,208,170,213,203,59,75,37,206,114,229,112,149,202,252,134,221,82,135,225,36,183,
113,227,198,177,177,177,242,242,242,133,133,133,85,171,86,125,233,75,95,250,209,143,126,100,182,233,164,76,146,180,30,103,32,86,30,137,14,33,209,142,142,199,236,236,236,210,165,75,175,185,230,26,124,180,
18,209,149,153,214,249,243,231,191,242,149,175,236,223,191,31,171,23,25,6,57,226,170,239,44,231,132,170,27,54,53,53,101,194,1,165,4,60,15,123,116,116,20,141,95,179,28,148,23,26,223,122,239,222,189,184,
106,21,21,21,232,70,0,190,173,70,214,206,239,126,247,187,13,13,13,128,54,119,117,117,253,211,63,253,19,210,34,21,154,205,109,10,206,46,112,17,148,83,44,28,86,34,145,8,135,195,112,3,194,183,189,160,30,
113,97,97,225,55,190,241,141,59,238,184,131,147,122,144,235,189,94,175,130,151,91,38,164,101,101,101,85,85,85,166,56,14,167,189,38,62,26,76,30,169,161,161,214,211,240,240,48,0,158,144,10,146,12,111,233,
41,39,143,36,149,74,141,140,140,164,211,105,202,230,201,83,39,207,146,37,22,5,175,1,131,86,165,87,3,3,3,221,221,221,242,166,202,202,202,194,120,228,143,127,252,163,234,21,200,204,17,223,157,196,72,115,
12,130,31,198,199,199,143,31,63,14,163,82,217,134,179,20,158,199,189,58,54,54,182,108,217,178,43,174,184,130,30,204,216,224,121,12,40,134,216,142,88,185,114,165,227,175,197,2,229,217,96,214,134,212,216,
78,56,27,61,40,151,203,133,179,196,81,51,196,101,240,206,193,96,240,185,231,158,91,177,98,197,134,13,27,136,130,146,141,99,5,173,179,228,20,140,141,141,189,249,230,155,172,159,76,207,45,222,29,231,206,
157,35,113,142,90,116,129,64,96,231,206,157,69,69,69,155,54,109,106,107,107,83,238,245,32,10,153,138,78,63,248,193,15,36,34,237,226,57,217,230,139,85,204,149,187,29,252,74,72,163,85,169,180,37,171,128,
66,113,166,248,242,210,165,75,253,126,127,58,157,158,152,152,168,168,168,200,202,202,186,226,138,43,178,178,178,126,248,195,31,90,194,87,104,166,37,151,162,4,179,242,179,28,194,45,5,124,156,182,182,182,
171,174,186,138,119,180,199,227,145,248,122,30,243,203,47,191,252,229,47,127,25,202,4,50,10,3,55,194,22,165,138,203,18,243,131,99,6,124,8,147,24,82,31,228,224,71,106,109,71,34,17,151,203,69,230,145,156,
123,59,12,85,91,68,200,45,91,182,112,136,133,52,84,18,145,178,178,178,114,54,110,220,72,68,112,60,30,63,122,244,104,75,75,11,179,33,25,166,77,56,103,44,22,243,249,124,42,105,74,38,147,131,131,131,68,206,
83,99,12,228,61,75,136,15,127,40,41,41,41,42,42,122,231,157,119,168,74,5,84,77,40,20,202,96,91,153,157,157,93,87,87,87,82,82,98,87,177,146,190,108,142,131,242,242,242,112,66,101,49,130,83,63,54,54,198,
241,197,194,194,66,81,81,145,108,173,242,77,106,106,106,240,14,178,56,194,64,181,164,164,68,125,95,149,197,203,58,8,75,39,149,74,113,219,80,117,177,207,231,99,51,148,203,26,58,94,103,207,158,37,31,140,
211,54,46,56,92,123,165,224,195,216,132,80,242,214,91,111,29,61,122,20,192,59,86,181,102,78,193,133,235,116,58,151,44,89,242,165,47,125,105,219,182,109,80,74,114,185,92,69,69,69,180,6,86,81,21,175,145,
77,55,135,149,65,50,159,196,251,240,77,96,175,41,95,239,116,58,97,201,198,184,44,225,74,136,2,67,67,67,93,93,93,197,197,197,48,212,144,122,158,38,240,153,32,60,158,168,223,253,238,119,177,88,204,142,1,
232,112,56,202,203,203,241,204,241,227,199,7,6,6,100,222,196,26,14,9,245,201,147,39,49,154,71,66,227,118,187,61,30,15,63,148,41,222,254,253,251,127,241,139,95,112,19,202,207,207,119,185,92,224,106,202,
70,191,203,229,66,27,13,142,19,37,37,37,101,101,101,229,229,229,32,124,243,234,227,205,33,112,8,109,72,40,170,99,123,43,42,42,242,251,253,196,89,58,172,228,39,205,190,188,57,142,46,42,42,218,182,109,27,
158,199,224,14,31,186,100,201,18,16,169,45,1,93,20,92,117,24,90,105,106,10,34,61,33,111,186,233,166,235,175,191,190,190,190,30,130,247,56,60,248,207,50,76,69,163,209,175,127,253,235,223,255,254,247,49,
123,96,80,102,6,205,211,46,207,191,249,87,130,59,29,239,58,4,169,3,171,168,168,48,115,136,68,34,129,17,136,234,67,40,216,62,94,140,4,66,102,102,224,215,252,149,74,254,37,151,92,34,63,0,132,17,176,149,
100,154,99,182,41,227,241,248,224,224,32,66,42,132,53,64,112,200,207,207,47,45,45,133,100,26,5,107,202,202,202,36,183,216,156,2,241,231,101,203,150,117,118,118,246,245,245,209,109,115,118,118,54,28,14,
103,32,31,215,213,213,225,254,151,27,160,140,41,80,186,178,212,163,73,167,211,8,163,60,239,216,96,71,71,71,85,93,51,63,63,95,94,94,142,105,190,188,81,171,170,170,96,158,166,220,11,225,159,130,212,219,
18,3,78,160,21,124,157,147,201,100,40,20,146,140,44,101,209,84,80,80,80,90,90,58,54,54,38,97,152,88,76,64,194,202,5,199,165,166,48,191,114,189,58,157,206,209,209,209,215,95,127,253,208,161,67,137,68,130,
5,7,247,66,122,170,170,65,95,118,118,246,77,55,221,244,153,207,124,134,85,17,97,103,202,178,158,223,29,129,9,155,180,227,175,205,220,44,1,136,144,84,101,90,132,0,77,93,74,252,128,224,34,53,192,228,144,
57,157,78,207,204,204,204,204,204,116,117,117,77,78,78,214,215,215,131,147,69,18,138,25,145,229,6,182,103,207,158,131,7,15,90,194,173,120,78,208,31,203,206,206,222,189,123,183,156,57,83,157,71,90,215,
15,15,15,31,57,114,100,106,106,170,160,160,160,165,165,5,128,95,117,93,238,187,239,190,142,142,142,188,188,60,183,219,45,253,49,228,204,77,250,248,169,175,128,122,92,38,107,102,248,83,183,128,199,227,
41,45,45,77,38,147,248,125,141,0,0,0,32,0,73,68,65,84,178,139,104,246,130,101,181,167,84,21,223,247,190,247,177,219,78,28,20,94,179,118,237,90,24,241,152,119,186,169,205,109,154,109,114,5,226,215,47,126,
241,139,87,94,121,165,207,231,195,102,19,141,70,113,177,160,6,131,133,180,111,223,190,79,126,242,147,7,14,28,224,230,36,111,7,254,202,55,55,119,104,226,226,67,161,144,194,116,178,52,196,128,23,60,47,179,
161,49,61,61,237,241,120,168,122,42,235,42,217,246,92,92,92,76,38,147,31,254,240,135,37,112,147,141,193,191,12,159,214,172,89,163,66,222,252,252,124,71,71,135,219,237,166,136,146,57,112,143,199,227,24,
107,2,218,113,252,248,113,116,235,106,107,107,145,248,20,20,20,248,124,62,248,115,167,211,233,202,202,74,238,189,153,29,163,231,230,230,54,109,218,244,210,75,47,65,130,3,227,74,151,203,5,52,187,244,161,
64,82,105,122,206,155,25,52,154,179,102,81,143,169,180,207,231,99,90,154,151,151,55,59,59,43,241,52,114,129,206,205,205,129,145,40,117,41,37,215,147,208,46,60,19,143,199,139,139,139,185,253,202,51,0,32,
32,238,210,84,42,53,58,58,74,105,61,190,70,149,222,80,133,133,85,29,122,71,92,88,131,131,131,88,202,50,248,18,109,130,95,105,60,129,127,71,70,70,94,122,233,165,125,251,246,197,227,113,85,139,41,133,76,
28,6,146,122,204,96,191,254,245,175,95,122,233,165,150,91,38,130,163,84,134,147,148,57,137,136,178,244,134,151,43,4,227,172,72,36,18,14,135,97,221,166,150,59,46,31,160,159,82,187,156,65,156,192,196,169,
169,169,142,142,142,133,133,133,230,230,102,50,187,228,173,171,246,245,153,153,153,71,30,121,132,65,86,234,48,200,147,131,0,157,149,149,181,115,231,78,211,125,66,21,203,120,126,98,98,226,240,225,195,175,
188,242,74,118,118,246,170,85,171,228,1,140,142,142,126,241,139,95,44,46,46,70,69,43,191,169,52,108,5,126,86,138,154,242,176,115,115,115,3,129,64,102,252,128,137,174,201,207,207,71,199,159,210,116,118,
50,91,50,122,226,26,45,95,190,124,233,210,165,252,44,12,99,144,245,227,43,108,217,178,101,124,124,156,49,58,3,232,203,92,78,140,164,46,151,235,187,223,253,110,123,123,187,76,86,184,169,16,151,125,223,
125,247,125,233,75,95,130,23,173,101,58,194,95,209,213,84,207,83,116,30,185,51,77,174,165,224,137,220,38,89,63,153,13,28,208,184,229,200,106,126,126,94,218,232,96,113,14,13,13,125,254,243,159,119,8,111,
73,196,10,41,72,103,17,160,241,121,125,125,125,94,175,215,239,247,155,127,77,36,18,140,206,83,83,83,231,206,157,195,24,48,20,10,197,227,241,198,198,70,137,61,192,86,195,13,51,131,78,60,135,182,121,121,
121,27,54,108,248,253,239,127,143,14,38,149,133,101,197,237,243,249,238,189,247,222,59,238,184,163,174,174,174,166,166,6,46,15,220,226,148,130,37,218,175,150,189,87,156,107,160,62,114,115,115,147,201,
228,228,228,100,6,53,175,116,58,13,107,106,130,124,49,123,149,113,89,62,18,137,4,18,10,14,208,212,181,28,31,31,159,152,152,144,5,148,76,187,136,102,151,19,173,170,170,170,198,198,70,96,245,177,176,32,
144,45,151,35,225,101,50,58,35,52,227,215,223,252,230,55,82,90,94,126,186,156,98,231,230,230,206,207,207,99,120,152,147,147,115,235,173,183,222,117,215,93,32,22,102,184,153,81,247,16,54,203,53,167,32,
171,38,190,133,91,20,152,175,96,33,206,205,205,141,141,141,81,114,64,78,107,115,114,114,64,64,229,147,82,165,64,118,123,230,231,231,207,159,63,127,246,236,217,138,138,10,92,17,153,126,170,70,228,147,79,
62,57,60,60,108,217,124,151,11,12,141,245,243,231,207,159,57,115,198,242,5,210,82,139,143,241,241,241,238,238,238,55,222,120,227,233,167,159,142,197,98,171,87,175,6,66,235,209,71,31,133,37,138,234,46,
34,64,115,133,16,251,161,38,4,200,16,67,161,144,26,63,88,170,170,170,42,19,116,4,143,199,19,141,70,45,169,34,150,82,104,110,183,123,251,246,237,84,8,64,243,4,93,29,80,1,240,250,45,91,182,28,63,126,92,
238,28,114,52,98,222,98,146,6,226,112,56,174,189,246,218,111,127,251,219,240,95,150,143,226,226,226,88,44,6,37,254,209,209,209,27,111,188,241,217,103,159,101,82,108,6,101,213,205,224,242,86,233,51,140,
95,217,113,86,156,82,182,200,65,60,182,3,19,195,240,154,94,242,40,97,161,226,34,87,233,226,226,226,242,229,203,91,90,90,232,140,131,175,60,63,63,207,190,171,69,128,230,150,14,97,114,140,161,37,170,28,
9,166,34,192,224,80,38,39,39,163,209,40,161,124,25,52,89,44,247,76,78,243,203,202,202,22,22,22,246,238,221,139,12,90,217,223,109,222,188,249,153,103,158,89,191,126,125,101,101,101,123,123,251,214,173,
91,175,190,250,234,143,126,244,163,87,94,121,101,115,115,115,101,101,37,50,2,144,107,176,184,149,88,187,92,175,72,240,243,242,242,98,177,216,212,212,148,29,74,23,225,21,167,181,186,186,58,39,39,103,122,
122,218,229,114,53,52,52,100,192,105,225,106,1,117,39,89,24,168,66,130,193,32,154,134,25,136,151,36,197,74,102,99,110,110,110,67,67,131,207,231,3,241,122,112,112,80,174,63,206,97,100,104,86,15,151,203,
213,209,209,161,112,226,102,146,21,141,70,71,70,70,82,169,84,125,125,253,131,15,62,120,195,13,55,176,254,178,27,114,242,238,146,62,205,136,35,114,191,183,164,71,73,68,23,138,68,116,42,32,147,162,122,214,
156,164,129,211,36,133,56,216,145,87,65,106,122,122,250,212,169,83,99,99,99,75,150,44,41,40,40,144,147,125,134,185,83,167,78,189,245,214,91,236,35,73,176,191,122,184,221,238,220,220,220,206,206,206,145,
145,17,59,36,181,169,99,215,219,219,139,187,49,30,143,31,56,112,224,177,199,30,59,119,238,220,250,245,235,31,120,224,1,42,79,169,134,59,70,50,12,208,242,50,225,196,242,43,128,225,101,201,190,49,9,56,106,
161,58,157,78,160,78,165,180,111,6,44,230,101,151,93,6,41,121,136,83,242,192,28,66,163,28,87,118,195,134,13,199,142,29,99,251,69,65,251,165,66,55,143,28,142,95,95,251,218,215,174,191,254,122,204,87,205,
49,126,105,105,233,252,252,252,195,15,63,252,233,79,127,26,27,170,25,145,237,178,105,37,247,202,23,68,34,145,233,233,105,59,31,97,44,66,196,22,140,67,29,54,162,172,16,44,226,42,197,87,144,233,5,110,82,
159,207,183,125,251,118,246,151,168,112,205,131,180,13,208,184,183,113,184,240,116,64,102,196,92,70,217,57,51,76,7,2,129,169,169,169,186,186,186,139,20,136,144,141,105,28,104,48,24,60,127,254,252,246,
237,219,15,31,62,12,203,37,217,97,188,235,174,187,238,191,255,126,137,171,229,59,20,21,21,181,180,180,172,93,187,118,233,210,165,173,173,173,141,141,141,107,215,174,197,56,37,63,63,31,165,144,50,85,194,
21,130,132,10,120,204,118,205,110,46,113,140,28,253,126,63,18,159,234,234,106,53,255,149,205,104,250,180,163,1,42,49,76,137,68,130,117,186,101,116,198,139,97,97,165,96,30,156,23,213,214,214,130,218,207,
117,198,8,110,249,96,200,110,108,108,60,120,240,32,154,155,150,13,86,150,68,139,139,139,159,255,252,231,31,123,236,177,165,75,151,18,18,99,39,43,172,8,214,156,150,224,216,164,162,177,169,6,71,184,149,
52,241,161,134,34,186,243,42,64,83,13,25,72,121,162,56,100,39,221,204,34,79,158,60,249,202,43,175,212,213,213,213,215,215,171,238,243,204,204,204,207,127,254,115,250,13,50,213,82,106,147,120,43,175,215,
155,155,155,123,248,240,97,116,240,237,76,188,36,234,6,172,51,197,238,9,6,131,143,63,254,184,20,57,49,31,148,185,48,243,122,197,176,8,133,66,230,148,207,206,13,3,255,11,105,16,197,29,189,94,111,56,28,
182,244,146,231,226,92,185,114,37,155,123,152,193,200,119,70,18,45,225,40,91,183,110,61,122,244,168,140,209,170,75,46,23,127,67,67,195,29,119,220,113,195,13,55,172,92,185,82,10,135,154,88,183,219,110,
187,237,161,135,30,2,182,218,50,22,155,63,243,25,10,28,210,230,20,178,124,10,59,47,111,16,182,124,81,135,89,210,220,200,89,159,155,155,131,225,6,210,97,179,4,196,101,189,241,198,27,165,151,46,43,245,63,
67,15,84,128,230,74,197,228,10,10,120,225,112,184,166,166,102,126,126,62,16,8,112,28,169,204,173,165,183,88,32,16,232,235,235,91,190,124,185,93,140,182,12,208,124,231,254,254,254,233,233,233,96,48,248,
158,247,188,231,153,103,158,193,157,57,63,63,239,118,187,31,123,236,177,191,255,251,191,183,235,63,112,136,81,84,84,84,85,85,85,93,93,157,151,151,55,57,57,185,184,184,136,121,119,89,89,89,69,69,69,121,
121,57,96,70,24,106,103,103,103,143,141,141,153,227,105,59,196,8,122,148,152,228,148,149,149,97,86,96,41,87,200,38,50,78,55,106,28,166,195,192,96,48,64,219,209,47,165,218,3,67,158,60,158,210,210,210,246,
246,246,68,34,17,137,68,128,214,200,16,151,241,64,91,118,106,106,106,104,104,200,50,165,130,54,52,63,232,187,223,253,238,138,21,43,20,125,78,229,209,150,238,171,106,179,225,144,80,246,88,101,128,150,115,
69,25,158,34,145,200,204,204,140,137,44,34,228,35,145,72,96,227,196,65,50,211,81,82,203,248,21,225,254,224,193,131,3,3,3,43,87,174,116,187,221,188,124,207,60,243,76,87,87,151,148,184,83,212,103,121,153,
188,94,111,94,94,222,158,61,123,50,235,148,202,239,219,211,211,3,5,93,52,79,107,107,107,33,13,104,238,61,234,103,21,160,149,107,20,143,191,160,160,128,27,64,134,81,33,255,59,224,137,68,233,81,162,26,150,
31,152,193,154,228,79,175,215,11,185,122,175,215,91,81,81,33,241,90,178,63,198,36,26,218,82,219,182,109,123,249,229,151,165,227,187,153,62,151,149,149,221,124,243,205,31,255,248,199,27,26,26,90,90,90,
50,72,207,163,186,122,229,149,87,206,156,57,35,227,47,86,59,99,177,140,218,234,103,130,121,168,88,130,82,160,176,176,80,250,175,42,73,69,44,45,128,103,44,99,133,28,250,193,37,128,16,76,217,139,195,15,
227,227,227,119,220,113,7,132,203,85,173,6,52,136,14,208,136,206,121,239,62,176,183,192,245,78,34,61,25,160,229,164,82,206,217,99,177,88,79,79,207,202,149,43,77,120,102,134,241,32,36,207,193,65,192,54,
226,243,249,246,236,217,51,63,63,255,158,247,188,231,185,231,158,91,178,100,73,102,55,63,217,84,113,58,157,62,159,207,227,241,96,70,33,239,180,188,188,60,100,214,5,5,5,253,253,253,241,120,156,8,115,137,
81,119,88,249,4,226,5,201,100,18,252,31,175,215,75,229,29,213,211,148,97,122,102,102,166,184,184,152,166,142,4,186,227,91,19,165,111,138,255,121,189,94,83,100,74,193,30,242,243,243,151,47,95,222,208,208,
0,154,79,110,198,71,50,153,28,26,26,74,167,211,53,53,53,199,142,29,147,141,123,68,127,196,47,249,173,223,124,243,205,219,110,187,141,37,155,234,167,103,216,216,228,151,197,39,218,177,242,20,246,78,166,
159,192,78,73,185,46,213,229,192,157,70,126,135,132,220,89,178,108,17,34,241,195,209,163,71,23,22,22,150,45,91,150,147,147,51,60,60,252,171,95,253,202,220,107,29,134,241,60,65,184,161,80,168,191,191,223,
84,174,176,212,48,155,155,155,59,125,250,52,41,145,24,129,198,227,113,22,7,18,46,166,190,38,175,8,167,17,106,84,64,84,207,212,212,148,52,151,178,36,227,80,142,89,25,0,241,224,221,110,119,77,77,141,199,
227,129,221,165,186,190,31,249,200,71,150,44,89,2,242,17,132,244,164,63,58,214,63,72,249,56,60,124,144,211,233,92,183,110,221,59,239,188,131,14,175,2,132,20,20,20,124,240,131,31,252,135,127,248,7,188,
51,114,103,75,116,175,195,225,136,197,98,104,68,92,118,217,101,191,250,213,175,184,230,205,76,217,132,217,241,73,137,132,225,97,131,119,134,233,130,169,86,207,46,71,113,113,49,3,180,201,198,116,8,231,
92,40,92,202,38,173,138,209,237,237,237,151,94,122,169,50,50,7,88,69,247,160,113,133,16,154,33,122,139,0,157,149,149,117,240,224,193,174,174,46,200,77,72,189,14,229,42,43,127,142,197,98,221,221,221,24,
85,95,48,58,51,125,30,24,24,96,250,51,61,61,93,83,83,147,151,151,183,102,205,154,47,127,249,203,0,219,90,14,127,51,208,136,15,29,58,68,8,148,236,124,229,230,230,198,227,241,147,39,79,66,71,216,229,114,
33,155,150,77,106,187,9,9,174,104,50,153,44,45,45,5,124,80,54,109,247,239,223,63,54,54,22,137,68,130,193,32,200,226,24,154,161,193,13,199,63,224,17,157,78,39,214,153,44,132,29,127,109,130,206,33,140,105,
60,161,208,23,197,197,197,27,55,110,196,45,138,194,141,87,16,153,197,226,226,98,127,127,127,48,24,68,150,141,75,137,248,194,118,60,160,114,234,91,71,34,17,204,97,28,86,186,207,25,154,66,160,246,161,19,
13,38,183,41,233,105,210,34,84,18,141,3,64,128,86,20,42,73,193,7,115,74,174,126,213,226,96,130,143,225,18,123,184,189,189,189,39,79,158,172,174,174,254,245,175,127,13,76,139,201,40,179,44,11,188,94,239,
240,240,240,196,196,196,69,74,254,143,141,141,141,141,141,169,146,57,157,78,163,250,1,177,139,206,214,242,12,96,78,200,118,129,137,71,98,39,26,48,0,44,120,135,141,29,179,217,255,161,48,49,126,198,154,
129,235,224,146,37,75,146,201,36,186,127,248,239,171,87,175,222,188,121,51,12,40,184,169,179,67,194,187,3,239,9,77,71,54,208,125,62,223,166,77,155,118,239,222,173,48,18,27,55,110,188,237,182,219,218,219,
219,243,243,243,189,94,239,186,117,235,236,212,11,210,233,244,228,228,36,119,32,48,164,128,171,99,250,108,142,4,205,95,241,131,66,196,243,121,212,199,197,197,197,80,4,82,83,244,185,185,185,146,146,18,
25,160,205,169,12,91,207,160,110,171,160,44,127,245,120,60,215,95,127,61,232,84,88,192,46,151,11,66,155,58,64,35,243,103,115,131,209,249,212,169,83,137,68,98,102,102,166,183,183,183,166,166,6,148,13,160,
35,168,140,46,83,105,25,163,187,186,186,214,174,93,43,217,62,118,1,26,4,176,80,40,196,123,117,110,110,174,168,168,168,189,189,29,62,182,241,120,28,140,21,96,182,50,199,5,188,73,58,157,222,183,111,159,
101,235,32,26,141,118,116,116,80,4,0,247,155,66,20,89,138,172,203,2,19,170,126,232,193,177,137,9,168,50,130,50,76,84,147,201,100,60,30,135,223,232,228,228,228,196,196,68,40,20,26,31,31,159,156,156,140,
199,227,152,113,161,249,37,209,236,168,0,228,1,168,121,145,37,59,188,174,174,110,233,210,165,56,249,12,205,185,185,185,195,195,195,253,253,253,240,133,99,236,174,173,173,61,120,240,32,109,223,164,34,171,
58,177,39,78,156,104,111,111,95,177,98,133,229,236,55,195,150,137,239,130,116,128,179,120,75,98,158,250,85,170,67,76,77,77,161,234,148,138,230,92,120,88,117,46,151,11,72,30,78,149,77,96,12,51,104,20,46,
216,242,1,182,121,235,173,183,64,75,145,93,105,75,37,13,46,24,143,199,211,211,211,195,153,210,5,31,29,29,29,208,95,53,207,33,223,28,112,114,44,24,0,117,40,57,194,186,80,77,252,136,234,101,146,8,230,173,
37,2,90,158,94,85,91,48,139,7,5,166,180,180,180,162,162,162,180,180,116,249,242,229,69,69,69,40,206,60,30,207,149,87,94,9,53,93,185,123,33,217,84,45,62,226,205,153,27,130,196,191,108,217,178,215,94,123,
13,255,183,185,185,249,182,219,110,219,186,117,43,34,84,77,77,205,134,13,27,136,210,83,139,42,28,14,43,30,64,86,86,214,218,181,107,31,127,252,113,9,155,51,83,102,203,166,7,240,69,234,101,18,248,88,80,
80,128,169,9,226,166,116,84,169,170,170,98,12,53,235,69,10,106,242,158,229,112,200,148,215,63,119,238,220,93,119,221,5,144,162,203,229,74,167,211,28,63,46,46,46,254,37,64,179,89,174,250,27,93,93,93,228,
212,206,206,206,246,245,245,193,217,143,218,205,150,163,30,118,165,81,69,54,55,55,163,84,183,211,229,193,13,51,56,56,136,114,143,199,99,138,123,196,227,241,137,137,9,128,163,45,195,180,252,249,252,249,
243,35,35,35,106,188,131,92,166,179,179,147,202,135,248,106,192,205,152,50,96,38,239,145,235,47,59,59,123,124,124,188,185,185,153,157,193,153,153,25,88,59,43,206,146,76,202,40,111,40,229,137,213,105,4,
81,141,30,154,177,88,44,26,141,2,118,102,38,146,138,230,148,151,151,7,215,97,160,2,98,177,24,102,232,72,142,100,174,129,160,6,23,27,187,173,14,111,232,241,120,142,28,57,114,235,173,183,194,240,215,210,
244,214,242,29,24,160,23,23,23,77,38,97,6,141,11,25,223,217,131,86,57,8,151,31,206,88,94,94,222,212,212,84,6,145,104,194,162,105,23,137,64,195,52,220,28,36,88,162,193,8,179,59,125,250,180,217,205,176,
84,184,77,165,82,157,157,157,50,196,219,161,155,228,238,72,125,40,211,79,64,170,203,243,202,194,193,7,98,255,118,98,167,150,231,164,160,160,160,164,164,164,186,186,186,177,177,177,190,190,30,164,71,14,
213,203,203,203,91,91,91,39,39,39,183,111,223,14,114,3,206,27,135,108,172,60,212,244,5,34,109,108,128,96,159,174,172,172,172,172,172,60,125,250,244,135,63,252,225,107,174,185,198,235,245,226,245,205,205,
205,155,54,109,226,205,101,46,197,64,32,192,94,45,191,184,203,229,170,174,174,126,227,141,55,228,218,70,32,150,42,28,150,35,68,92,116,147,222,37,159,41,46,46,46,43,43,75,38,147,232,50,225,72,234,234,234,
88,58,91,98,70,233,24,39,93,220,44,99,116,50,153,188,246,218,107,209,98,5,215,65,110,222,127,9,208,50,58,227,203,204,205,205,245,244,244,76,78,78,50,37,193,138,31,26,26,66,18,174,132,238,44,65,29,243,
243,243,137,68,226,200,145,35,203,150,45,83,14,52,170,96,143,199,227,152,111,112,54,109,73,106,34,94,106,98,98,2,70,94,202,70,83,158,169,67,135,14,17,210,40,133,126,224,205,172,146,83,84,253,153,99,180,
194,3,97,173,76,78,78,130,161,131,34,5,250,156,196,150,41,142,181,180,118,103,219,139,83,26,182,80,138,138,138,128,75,5,80,58,145,72,144,255,109,166,159,138,69,138,127,221,110,119,107,107,107,52,26,125,
253,245,215,145,56,203,65,10,150,239,59,239,188,243,198,27,111,72,253,101,147,168,137,86,35,220,105,59,58,58,200,125,50,131,169,101,66,77,109,138,156,156,28,194,236,204,119,200,156,68,35,131,86,181,33,
157,235,120,6,176,104,33,176,101,90,18,75,111,42,30,36,26,77,82,129,239,226,3,52,56,77,23,153,62,159,59,119,142,195,21,169,238,118,65,184,177,169,176,129,168,157,74,165,144,95,147,129,6,176,57,168,179,
18,159,99,55,36,68,134,88,87,87,215,210,210,210,208,208,80,90,90,234,241,120,168,215,163,136,175,249,249,249,43,86,172,128,160,2,136,8,210,24,133,49,4,97,4,85,56,44,134,241,164,140,152,133,133,133,151,
93,118,217,135,62,244,161,120,60,206,243,220,214,214,70,246,147,165,26,20,230,102,244,246,150,123,204,234,213,171,159,125,246,217,233,233,105,102,30,178,31,173,58,24,50,83,166,100,157,29,255,27,7,12,166,
34,124,60,208,162,68,128,182,211,165,66,131,72,126,11,228,130,102,22,139,133,186,100,201,146,77,155,54,153,170,194,127,201,160,113,117,33,124,17,137,68,48,226,135,179,142,82,237,65,52,28,29,29,93,92,92,
44,45,45,165,213,136,37,44,154,71,3,141,177,229,203,151,155,35,47,148,117,14,135,227,220,185,115,156,132,80,118,39,243,48,16,8,217,68,34,129,5,161,18,183,116,58,221,217,217,169,34,123,87,87,215,192,192,
128,101,251,130,6,57,38,161,198,210,25,0,103,3,61,169,201,201,73,48,86,100,6,173,218,91,82,202,93,198,110,234,87,49,34,236,217,179,199,237,118,79,78,78,198,98,49,118,235,104,115,99,218,206,90,78,156,113,
69,106,107,107,223,255,254,247,199,98,49,108,27,92,154,129,64,224,151,191,252,229,225,195,135,45,65,126,104,195,193,77,81,226,85,71,70,70,124,62,223,186,117,235,76,89,228,12,195,91,180,107,28,14,135,93,
128,182,236,123,200,78,52,50,104,185,184,185,216,20,101,188,160,160,0,136,14,57,201,84,177,73,114,145,200,43,83,60,38,162,26,184,113,154,72,155,68,34,97,7,176,51,19,213,3,7,14,72,203,133,12,122,252,23,
175,28,139,59,31,93,236,233,233,105,112,98,177,75,97,14,97,230,209,46,151,171,162,162,162,190,190,190,181,181,181,185,185,185,188,188,188,168,168,72,182,77,72,37,103,50,193,182,158,4,80,66,115,131,43,
28,119,49,87,187,82,118,197,219,66,51,164,165,165,165,177,177,177,184,184,24,229,212,249,243,231,179,179,179,55,109,218,244,158,247,188,199,174,123,38,197,15,156,78,39,179,117,121,134,27,27,27,95,123,
237,53,70,85,137,95,162,183,150,101,140,150,93,14,179,79,141,159,231,230,230,186,186,186,96,44,133,97,64,67,67,3,181,43,212,5,146,16,17,185,176,225,13,102,98,150,224,136,125,203,45,183,168,0,253,231,30,
17,8,181,137,68,34,16,8,160,209,140,19,58,61,61,13,16,152,98,28,113,250,57,57,57,153,72,36,252,126,63,178,15,115,103,80,49,58,149,74,29,56,112,96,213,170,85,170,119,195,244,121,120,120,152,79,210,59,249,
98,86,112,58,157,14,133,66,225,112,24,45,69,62,63,58,58,138,102,28,175,98,87,87,23,122,88,10,229,131,243,146,78,167,161,170,99,215,51,145,22,53,106,53,163,221,188,121,243,230,177,177,177,145,145,17,83,
37,75,97,60,20,197,0,87,238,228,201,147,127,250,211,159,30,122,232,161,178,178,178,101,203,150,153,117,19,166,213,150,178,174,234,190,149,78,116,185,185,185,107,215,174,93,179,102,205,196,196,68,52,26,
157,157,157,221,179,103,207,83,79,61,37,169,189,50,166,112,89,203,208,204,15,218,187,119,239,149,87,94,89,94,94,110,7,189,48,47,16,238,1,24,41,88,42,165,153,178,162,106,106,58,53,53,197,0,45,229,56,36,
166,136,255,23,125,27,137,90,85,167,139,1,154,117,183,201,227,48,245,161,28,134,177,47,133,40,45,125,187,101,246,61,50,50,66,247,19,158,201,191,73,238,249,130,137,118,81,81,17,196,170,16,143,56,141,196,
9,41,47,47,111,104,104,104,107,107,107,110,110,174,168,168,0,197,198,97,24,127,48,231,144,141,105,75,119,24,240,185,229,151,77,165,82,166,182,9,180,62,124,62,223,210,165,75,203,203,203,203,202,202,136,
107,206,202,202,170,175,175,143,68,34,151,92,114,137,164,113,203,125,218,28,204,130,125,198,211,206,227,108,105,105,57,126,252,248,228,228,164,140,191,236,10,96,39,54,9,223,144,118,176,27,39,178,91,114,
242,228,201,112,56,76,104,144,195,225,104,106,106,2,62,82,165,68,88,78,242,94,144,139,86,202,171,130,239,118,229,149,87,222,126,251,237,159,249,204,103,128,27,49,47,174,19,70,197,185,185,185,165,165,165,
40,145,48,112,159,158,158,86,36,40,220,186,114,158,0,93,205,149,43,87,154,96,100,19,19,6,84,198,253,247,223,255,217,207,126,22,209,71,190,120,112,112,16,179,126,14,148,76,5,0,71,70,199,248,153,153,153,
193,193,65,136,210,162,254,26,31,31,199,1,163,12,60,118,236,88,36,18,177,132,102,35,130,0,152,33,5,128,56,19,144,212,12,42,52,202,176,8,57,208,93,187,118,193,224,145,201,29,255,53,183,77,250,174,143,141,
141,157,58,117,234,240,225,195,152,195,20,22,22,94,115,205,53,44,222,213,215,15,135,195,126,191,159,85,139,180,14,144,211,90,6,125,78,126,170,170,170,238,188,243,206,183,223,126,251,19,159,248,132,220,
11,177,231,187,92,46,14,187,24,109,149,49,46,183,195,187,239,190,251,153,103,158,225,16,156,2,73,52,228,54,53,112,21,42,198,68,38,89,106,219,51,178,155,190,65,150,181,63,169,61,62,159,47,20,10,1,243,67,
60,25,153,138,178,165,195,153,135,90,171,166,195,131,36,58,226,73,216,66,203,62,143,9,31,196,147,104,10,75,172,107,230,254,198,255,34,179,206,205,205,69,43,146,242,53,8,142,165,165,165,20,92,181,4,38,
201,61,140,103,219,148,23,86,46,110,128,246,203,241,21,255,87,81,81,17,146,101,150,203,192,65,35,244,203,212,210,225,112,92,119,221,117,170,133,200,181,173,70,17,252,190,149,149,149,195,195,195,170,153,
187,184,184,120,231,157,119,222,117,215,93,74,98,5,191,194,251,138,13,25,249,215,194,194,66,52,0,165,250,24,94,137,76,37,16,8,16,168,195,171,95,89,89,201,250,94,241,90,233,75,192,159,37,17,177,184,184,
120,219,182,109,219,183,111,223,184,113,35,102,230,25,76,203,28,14,71,14,212,124,192,38,194,45,10,0,160,165,178,4,211,55,222,42,16,175,0,1,193,76,159,77,181,189,217,217,217,119,222,121,167,172,172,12,
236,68,156,220,169,169,169,193,193,65,214,194,230,148,192,110,250,100,214,65,128,241,6,131,65,80,210,73,79,239,232,232,64,53,106,2,239,165,56,17,146,104,213,155,86,77,21,246,4,100,37,133,179,60,57,57,
89,80,80,48,53,53,197,107,44,199,20,146,94,8,64,222,222,189,123,95,126,249,101,192,242,96,23,15,144,41,52,43,84,78,74,124,2,70,58,146,133,65,230,232,244,244,180,132,0,171,93,109,110,110,174,174,174,238,
182,219,110,67,53,3,216,83,109,109,237,138,21,43,202,203,203,193,87,118,88,25,111,155,214,1,201,100,242,125,239,123,159,37,52,219,124,61,183,94,197,36,180,156,13,90,38,209,102,139,195,18,111,199,250,17,
222,99,216,96,48,90,64,116,160,101,178,220,155,17,71,50,164,207,150,29,246,100,50,137,222,154,221,216,141,103,114,118,118,246,237,183,223,150,219,161,156,235,254,127,9,211,208,144,67,82,140,137,110,77,
77,77,121,121,185,199,227,81,25,177,157,55,46,249,26,202,89,81,54,100,228,166,139,14,152,234,156,52,53,53,45,91,182,12,218,191,8,223,24,226,65,66,147,111,46,231,76,170,248,96,68,179,67,64,83,149,9,253,
107,121,72,53,53,53,253,253,253,200,56,21,228,142,160,82,149,95,83,49,195,76,156,241,88,92,92,220,183,111,159,57,227,145,216,10,37,52,104,210,142,22,22,22,86,172,88,177,101,203,150,235,175,191,254,166,
155,110,250,240,135,63,12,122,148,244,163,177,243,180,115,170,38,6,64,187,80,73,86,49,154,239,162,198,56,211,211,211,199,142,29,91,189,122,53,118,12,217,220,144,41,137,220,34,30,125,244,81,135,195,1,187,
114,116,159,209,68,231,81,74,152,167,162,69,88,170,221,75,217,108,36,185,189,189,189,131,131,131,64,107,2,222,164,176,59,150,169,4,54,18,211,91,140,243,116,38,182,200,244,1,248,147,73,65,79,79,143,210,
110,87,67,219,169,169,169,254,254,254,211,167,79,199,98,177,252,252,124,206,100,178,178,178,252,126,127,110,110,238,234,213,171,41,176,194,205,128,130,206,136,86,232,27,74,153,61,192,132,153,56,203,106,
17,20,9,254,213,237,118,127,255,251,223,191,235,174,187,254,237,223,254,13,28,113,192,128,42,42,42,176,165,41,127,47,138,148,51,233,155,157,157,125,228,145,71,174,184,226,138,141,27,55,242,235,51,185,
144,121,52,27,238,38,174,92,37,209,166,24,49,239,88,52,196,205,8,104,169,232,207,91,8,91,14,51,50,16,16,112,174,148,59,212,204,204,12,162,137,234,128,51,37,84,107,134,61,64,137,39,179,203,157,23,23,23,
101,189,130,154,224,255,87,116,230,244,200,227,241,148,148,148,96,45,113,66,37,191,99,230,134,161,41,47,39,107,118,249,14,116,16,135,75,108,117,117,117,105,105,41,62,26,19,75,249,158,12,115,84,20,145,
102,78,102,70,207,59,93,77,158,205,93,31,245,1,24,12,178,171,251,185,207,125,238,200,145,35,166,136,40,97,115,236,141,200,63,169,228,90,162,62,142,31,63,174,152,92,220,90,228,56,1,216,95,178,7,241,189,
26,27,27,107,106,106,26,26,26,160,31,199,202,163,175,175,15,196,40,201,148,177,187,52,57,28,44,80,50,149,222,54,200,210,73,82,82,243,34,121,57,49,148,0,173,136,114,10,68,116,88,46,199,163,71,143,150,149,
149,213,213,213,133,195,97,24,133,200,16,41,197,103,149,19,243,69,186,237,65,91,57,28,14,159,56,113,130,23,64,85,223,150,56,115,184,152,155,141,75,40,91,58,222,245,223,44,46,46,70,116,150,130,56,236,54,
72,161,78,206,25,206,158,61,251,230,155,111,238,218,181,235,220,185,115,216,5,89,151,80,141,236,230,155,111,198,190,45,111,18,58,52,242,60,72,193,48,208,28,148,92,189,172,12,82,169,20,219,50,146,173,123,
195,13,55,180,181,181,29,63,126,28,205,232,220,220,92,148,114,230,29,171,218,11,120,171,195,135,15,223,116,211,77,88,151,234,163,25,163,213,13,198,234,196,236,75,88,130,163,185,207,205,204,204,64,186,
196,18,240,111,25,31,177,115,0,119,44,117,178,208,10,192,217,195,137,37,122,199,82,84,72,233,166,242,104,97,133,69,52,85,134,199,174,93,187,164,160,243,5,187,207,25,218,56,50,186,129,178,0,9,1,50,77,164,
252,191,140,44,153,237,113,205,210,193,172,6,16,1,60,30,79,75,75,203,250,245,235,47,189,244,210,181,107,215,86,85,85,145,75,197,197,79,26,20,35,157,114,33,225,241,155,85,172,82,36,206,96,66,93,88,88,8,
184,142,252,10,30,143,39,24,12,14,13,13,201,244,89,102,211,204,59,249,39,122,28,171,215,231,228,228,64,165,214,92,165,14,135,99,221,186,117,178,182,224,100,174,180,180,180,181,181,245,146,75,46,185,230,
154,107,86,173,90,213,216,216,8,75,19,121,197,49,193,70,85,65,111,29,187,11,237,180,236,96,48,47,0,240,22,14,14,50,75,146,183,19,239,147,158,158,158,134,134,6,18,52,101,167,15,211,82,229,11,249,232,163,
143,202,87,50,117,69,124,15,135,195,85,85,85,108,5,154,125,49,187,46,36,226,23,16,211,231,207,159,103,130,201,166,132,229,133,103,100,137,68,34,178,18,231,77,5,93,130,252,252,124,40,120,41,78,135,218,
78,101,87,231,244,233,211,195,195,195,67,67,67,210,172,65,106,67,211,46,125,195,134,13,101,101,101,184,153,201,0,146,89,12,158,4,114,49,26,141,186,92,46,200,75,74,188,129,44,110,192,131,98,90,45,251,239,
120,217,246,237,219,161,236,250,200,35,143,128,251,14,194,52,155,18,150,173,91,108,201,3,3,3,119,223,125,247,131,15,62,168,98,34,1,112,92,48,44,41,254,119,13,86,168,46,88,114,2,45,33,168,76,243,233,187,
97,118,54,209,124,68,153,172,108,170,77,38,58,81,113,18,183,158,78,167,161,150,101,242,206,229,214,18,141,70,161,94,148,249,104,255,38,147,95,169,97,45,207,18,118,226,233,233,233,194,194,66,176,36,236,
184,154,114,179,81,89,23,159,41,40,40,64,254,155,159,159,95,91,91,91,83,83,83,89,89,137,41,186,132,163,72,7,94,228,167,116,90,144,158,15,204,114,104,8,105,185,237,73,105,124,203,91,91,246,253,74,75,75,
39,38,38,164,132,203,194,194,194,237,183,223,126,244,232,81,168,1,75,164,29,83,37,116,165,36,240,20,244,16,133,229,88,92,92,148,118,48,242,81,86,86,70,228,21,8,41,149,149,149,181,181,181,126,191,31,111,
46,91,88,38,138,20,194,109,64,103,49,76,219,205,6,254,74,76,214,82,67,0,53,32,27,79,172,160,149,161,28,126,56,119,238,92,101,101,37,60,86,100,116,166,137,159,44,18,231,230,230,30,124,240,193,156,156,156,
229,203,151,151,150,150,122,189,94,8,245,98,99,56,112,224,64,69,69,197,250,245,235,153,185,43,109,76,153,104,171,125,24,162,122,19,19,19,88,7,68,173,34,5,166,38,167,229,169,193,189,39,107,49,184,23,98,
206,134,253,86,49,173,77,1,51,108,87,147,147,147,168,178,77,133,67,249,141,112,90,160,63,0,233,100,168,207,240,180,243,104,101,187,124,100,100,132,56,77,217,179,99,56,150,172,101,121,222,88,168,226,79,
46,151,235,31,255,241,31,175,187,238,186,7,30,120,32,26,141,74,69,11,230,68,84,219,146,113,54,157,78,191,252,242,203,175,188,242,202,142,29,59,84,140,198,43,81,129,177,75,126,241,49,72,157,85,176,159,
205,169,35,86,148,84,233,98,55,9,168,36,57,211,147,35,117,220,255,224,172,226,5,72,237,165,220,135,66,16,74,28,139,236,56,93,176,197,113,234,212,169,255,23,32,157,229,72,220,52,210,53,249,208,180,88,3,
2,85,141,230,204,232,140,152,14,17,49,192,27,74,75,75,171,171,171,171,170,170,234,235,235,165,117,0,79,154,204,94,241,113,18,67,165,76,224,76,37,126,203,232,44,251,221,25,82,49,130,92,189,94,47,4,23,185,
80,93,46,215,245,215,95,255,199,63,254,209,108,113,200,103,16,34,145,149,34,94,169,23,244,244,244,32,171,147,42,43,56,152,252,252,124,183,219,77,190,37,96,105,44,140,204,162,80,62,227,245,122,235,235,
235,233,104,170,226,140,121,41,157,178,191,108,73,33,101,114,13,238,50,194,180,242,157,163,207,91,86,86,214,232,232,40,196,191,57,60,145,89,152,220,240,179,178,178,192,221,28,24,24,160,116,97,89,89,153,
207,231,131,166,207,200,200,72,34,145,88,191,126,61,149,253,228,149,86,59,185,252,146,231,207,159,15,135,195,118,42,22,8,127,12,211,106,16,49,55,55,23,141,70,165,180,124,50,153,244,251,253,30,143,7,109,
31,229,145,172,2,52,90,204,253,253,253,232,170,163,0,84,47,147,193,154,50,58,235,214,173,163,209,3,240,212,8,112,42,155,70,255,20,25,37,71,5,120,158,33,82,246,163,25,161,72,135,225,13,38,221,249,252,126,
255,61,247,220,243,209,143,126,244,246,219,111,7,120,92,70,25,185,241,72,188,125,58,157,254,234,87,191,250,167,63,253,137,154,171,124,67,222,207,150,83,95,187,97,175,25,173,166,167,167,233,183,96,10,239,
153,173,0,120,32,96,66,40,233,118,42,137,78,38,147,224,53,160,5,132,102,5,210,195,120,60,46,155,155,230,97,211,227,145,150,143,38,11,148,191,74,195,167,11,118,147,149,84,161,221,89,178,228,7,41,132,53,
174,53,74,201,84,42,69,230,8,123,184,110,183,27,214,116,224,34,81,251,213,194,254,162,0,0,32,0,73,68,65,84,20,50,144,245,245,245,18,160,194,123,77,217,167,18,254,132,243,44,193,157,180,4,178,164,201,152,
240,36,140,55,105,239,109,137,131,86,11,18,61,13,58,142,242,252,95,125,245,213,175,189,246,26,113,217,210,46,86,70,97,232,120,96,152,4,88,4,31,201,100,18,125,87,9,145,98,103,198,239,247,99,66,78,126,25,
213,166,148,133,155,2,120,212,213,213,121,189,94,82,183,72,220,147,3,118,181,254,157,232,96,100,208,36,100,64,65,22,67,1,54,168,41,201,243,66,71,231,96,48,56,61,61,77,35,21,133,87,147,173,213,137,137,
137,100,50,137,251,161,173,173,13,126,19,19,19,19,225,112,56,16,8,56,157,78,183,219,221,215,215,247,222,247,190,183,181,181,85,190,149,210,156,147,164,231,145,145,145,88,44,166,90,25,170,161,12,5,97,170,
218,171,150,43,189,83,193,122,42,45,45,149,158,52,252,56,217,123,73,167,211,195,195,195,99,99,99,67,67,67,178,80,136,199,227,16,85,81,228,67,213,10,132,73,10,206,30,142,10,187,183,108,35,226,180,211,240,
27,42,98,28,160,225,60,204,206,206,202,196,153,133,139,140,77,210,151,79,133,236,246,246,246,195,135,15,255,199,127,252,199,79,126,242,19,137,146,54,35,53,207,118,52,26,253,218,215,190,246,219,223,254,
150,111,46,227,62,107,73,211,143,241,98,194,52,120,1,14,43,3,39,179,109,138,104,30,8,4,40,14,199,126,61,238,7,217,172,136,197,98,114,203,73,38,147,156,242,163,80,157,153,153,137,197,98,244,33,83,211,11,
206,180,229,64,88,193,194,80,69,101,240,145,82,203,146,140,24,83,107,197,14,24,103,210,71,101,247,150,251,98,126,126,126,73,73,137,207,231,43,44,44,244,251,253,149,149,149,168,172,233,74,83,86,86,214,
218,218,90,93,93,237,118,187,249,62,156,6,201,62,27,218,113,88,120,42,141,227,90,34,164,193,212,161,53,137,63,114,246,67,153,61,203,189,220,110,10,229,243,249,130,193,32,190,11,14,195,229,114,125,226,
19,159,120,236,177,199,76,228,28,139,78,206,3,241,165,16,172,249,74,52,55,216,189,97,201,139,61,9,161,207,140,194,118,93,50,212,199,16,31,103,112,160,163,180,172,125,205,47,235,140,197,98,24,152,88,138,
19,178,196,54,241,67,144,100,67,151,157,247,36,128,77,232,81,4,131,65,16,67,205,129,56,210,132,161,161,33,168,100,45,46,46,142,143,143,207,207,207,183,182,182,82,143,152,74,67,225,112,24,41,246,135,62,
244,33,12,115,164,64,162,4,39,206,205,205,193,77,156,71,165,220,90,205,11,143,72,205,61,150,79,38,147,201,202,202,74,143,199,131,190,30,129,180,204,77,176,37,206,204,204,68,34,145,201,201,201,233,233,
105,218,68,42,132,181,140,209,114,254,43,239,162,141,27,55,178,244,38,145,15,164,33,226,70,232,35,37,151,11,123,38,216,12,232,100,172,114,100,233,41,206,127,29,194,199,68,118,174,238,190,251,238,91,111,
189,245,222,123,239,125,252,241,199,205,224,40,123,232,136,254,71,143,30,125,240,193,7,63,251,217,207,170,53,42,5,37,240,250,190,190,62,37,167,101,249,3,30,67,67,67,96,7,0,250,2,19,79,218,189,163,173,
129,235,130,38,245,240,240,176,4,56,42,19,88,137,116,68,98,91,84,84,196,150,26,50,98,9,243,2,213,13,210,128,224,112,201,59,71,10,119,100,64,64,247,246,246,94,48,107,166,168,172,116,248,134,100,168,195,
112,244,128,13,174,165,136,190,188,171,65,17,196,4,15,169,226,188,120,68,163,209,153,153,153,213,171,87,195,123,8,40,67,73,92,230,106,145,131,122,153,72,82,102,72,222,215,210,180,30,107,82,65,69,217,146,
150,91,29,21,160,136,100,128,168,128,188,143,236,190,38,59,242,48,220,144,49,122,203,150,45,59,119,238,12,135,195,82,92,65,206,237,37,96,3,164,80,58,151,30,60,120,240,240,225,195,234,19,49,132,195,230,
209,212,212,132,25,172,242,164,55,241,102,184,209,252,126,127,89,89,153,228,85,161,73,96,130,20,44,122,208,208,190,170,172,172,100,236,51,167,49,132,73,153,155,24,176,13,100,55,202,151,165,82,169,64,32,
0,187,88,201,248,66,13,30,139,197,8,63,194,235,161,60,219,216,216,152,155,155,27,141,70,105,250,71,37,176,225,225,225,143,125,236,99,96,136,154,49,110,102,102,102,120,120,24,125,91,233,230,167,232,73,
38,156,11,17,25,31,135,107,134,66,175,178,178,18,95,205,28,1,205,205,205,65,201,23,194,149,8,139,118,236,3,176,231,97,48,42,187,201,210,118,22,194,38,204,151,129,30,69,234,7,213,64,172,30,214,212,200,
7,241,110,216,144,208,79,144,45,102,245,175,36,53,153,47,99,25,139,245,90,91,91,251,224,131,15,222,114,203,45,119,223,125,247,233,211,167,101,27,154,218,158,228,226,207,206,206,254,244,167,63,189,252,
242,203,219,218,218,100,62,46,73,104,236,93,50,2,90,10,12,241,214,29,25,25,129,234,2,119,2,243,66,48,223,140,199,227,189,189,189,168,82,237,10,76,217,226,232,237,237,165,236,56,122,175,208,105,147,54,
61,4,8,214,213,213,53,53,53,37,147,73,112,68,113,81,24,88,21,240,84,142,7,83,169,212,233,211,167,47,152,11,227,90,171,82,207,239,247,39,18,9,41,242,41,97,239,170,97,88,85,85,5,246,118,125,125,189,223,
239,111,104,104,224,236,11,20,127,182,77,10,11,11,139,139,139,49,237,168,168,168,160,196,26,41,36,42,169,151,253,10,137,80,226,200,84,22,148,92,81,220,254,21,254,199,18,189,234,120,215,24,80,70,115,146,
110,44,53,217,205,71,65,65,65,58,157,198,26,99,219,243,35,31,249,200,47,127,249,75,75,177,58,83,62,169,178,178,50,24,12,98,90,248,198,27,111,40,61,116,199,95,59,234,74,81,70,69,67,35,196,8,199,92,84,84,
84,91,91,171,210,109,217,83,186,32,5,47,7,59,103,50,153,164,115,182,34,107,82,198,144,19,94,19,136,131,44,6,178,153,4,30,57,222,53,33,199,176,91,78,225,166,166,166,78,157,58,69,147,8,217,112,156,154,154,
42,46,46,134,228,171,194,84,77,79,79,31,58,116,8,51,101,197,161,156,158,158,30,26,26,226,66,196,249,53,167,34,38,186,78,89,73,229,230,230,46,91,182,12,188,27,228,29,170,209,57,53,53,53,57,57,57,58,58,
138,26,89,182,219,240,101,149,159,27,169,10,0,30,73,77,72,44,142,188,188,188,237,219,183,43,21,118,230,218,169,84,10,131,187,12,2,202,204,178,105,247,144,1,193,102,137,25,50,127,192,137,109,108,108,252,
212,167,62,85,92,92,124,224,192,1,37,224,43,59,30,184,111,79,156,56,113,221,117,215,153,28,125,254,23,42,109,218,201,215,241,231,209,209,209,169,169,41,217,232,159,153,153,161,201,133,186,112,125,125,
125,221,221,221,114,138,40,195,153,41,157,60,51,51,211,211,211,35,201,138,169,84,106,114,114,178,187,187,251,232,209,163,131,131,131,176,98,40,41,41,161,152,3,130,93,101,101,229,178,101,203,74,75,75,169,
208,79,155,84,203,246,224,209,163,71,251,251,251,47,216,122,198,170,48,45,186,97,237,65,205,35,102,15,88,75,205,205,205,87,92,113,197,246,237,219,111,186,233,166,173,91,183,94,114,201,37,75,151,46,173,
174,174,38,106,150,193,40,149,74,121,189,222,170,170,170,166,166,166,170,170,42,216,191,53,54,54,34,33,83,210,107,38,192,201,114,214,162,64,117,150,125,12,101,205,44,105,47,114,63,150,209,89,213,22,146,
134,103,153,90,201,63,229,230,230,74,181,185,236,236,236,234,234,234,254,254,254,104,52,170,180,252,229,175,146,198,2,234,227,127,253,215,127,41,158,173,249,216,186,117,107,123,123,187,229,174,44,65,217,
126,191,191,174,174,78,37,22,46,151,11,170,153,150,76,78,115,102,150,195,76,51,30,143,195,75,84,213,134,64,251,202,106,206,238,129,180,23,18,151,146,165,19,143,199,1,138,196,71,38,18,137,254,254,254,241,
241,113,203,230,227,236,236,108,36,18,33,242,215,132,190,158,61,123,182,175,175,111,197,138,21,236,42,78,77,77,141,141,141,161,115,39,229,146,229,144,61,3,180,142,47,174,168,168,88,187,118,45,78,8,230,
129,20,61,73,36,18,83,83,83,227,227,227,240,144,150,3,70,166,138,24,235,153,1,26,255,226,182,135,47,162,28,46,3,90,103,9,83,133,254,53,58,27,102,231,209,140,149,108,143,34,43,193,200,139,30,16,150,99,
25,101,216,42,79,53,255,180,105,211,166,79,125,234,83,227,227,227,0,36,152,247,6,222,57,20,10,165,211,105,12,79,164,78,105,113,113,49,165,174,217,186,205,176,73,140,141,141,1,73,194,18,13,59,16,145,9,
114,59,223,183,111,159,244,38,55,139,63,19,152,132,16,108,86,96,48,8,15,135,195,125,125,125,135,14,29,218,189,123,119,103,103,103,40,20,2,122,135,215,171,184,184,248,209,71,31,221,189,123,119,36,18,169,
172,172,164,107,170,249,120,225,133,23,46,232,190,10,246,132,178,8,224,35,47,47,207,231,243,225,234,83,165,221,235,245,186,221,110,159,207,119,213,85,87,149,151,151,51,226,40,36,47,30,152,124,194,57,136,
167,206,231,243,85,85,85,241,42,40,72,178,195,198,159,200,28,72,114,213,201,97,160,195,176,67,180,187,28,248,82,25,148,87,101,71,59,51,199,85,38,52,242,83,252,126,255,241,227,199,149,130,163,116,198,82,
234,187,57,57,57,13,13,13,221,221,221,16,137,179,187,100,55,222,120,99,115,115,179,186,89,100,20,206,207,207,111,106,106,2,172,0,101,49,224,52,69,69,69,208,86,205,140,220,144,63,228,228,231,231,179,40,
136,199,227,96,112,74,89,31,106,24,202,61,211,114,233,35,31,164,124,29,142,12,173,150,68,34,129,208,63,63,63,127,230,204,153,177,177,49,134,96,115,118,207,32,107,41,97,1,61,138,253,251,247,215,214,214,
194,214,122,124,124,92,206,229,184,135,43,140,135,101,238,140,127,203,203,203,1,99,36,163,12,64,8,182,32,233,75,100,57,215,194,62,132,254,160,164,36,168,53,157,72,36,144,191,48,70,67,25,206,18,153,0,177,
39,116,45,80,86,155,170,8,118,138,204,144,98,0,94,10,156,43,116,228,101,171,151,231,147,172,34,197,159,150,1,52,63,63,255,186,235,174,187,238,186,235,186,187,187,1,45,87,31,202,36,122,203,150,45,117,117,
117,40,41,224,250,136,213,57,61,61,77,77,47,185,107,170,207,10,4,2,28,75,200,228,26,44,53,249,173,187,187,187,15,30,60,200,164,233,130,161,153,230,144,200,106,77,191,62,105,41,130,115,53,53,53,213,211,
211,243,230,155,111,62,253,244,211,123,247,238,29,24,24,72,36,18,185,185,185,240,88,10,6,131,135,15,31,62,123,246,44,194,40,21,151,240,137,227,227,227,111,189,245,214,5,199,131,72,192,165,80,156,50,115,
41,42,42,106,107,107,43,42,42,162,50,39,93,49,55,108,216,32,169,131,166,68,189,162,234,241,122,33,143,54,121,198,23,115,179,168,114,65,98,195,25,4,204,120,170,240,87,20,42,202,64,101,80,115,51,59,174,
169,58,72,10,123,226,149,165,165,165,129,64,0,10,60,50,16,179,185,193,192,77,21,192,242,242,242,15,124,224,3,195,195,195,144,79,49,31,91,182,108,89,189,122,117,99,99,163,73,146,194,77,90,86,86,214,208,
208,192,196,25,233,57,174,20,36,7,50,32,226,213,109,149,149,149,149,131,91,136,221,37,240,143,209,148,192,168,74,186,233,72,13,48,179,150,132,72,13,182,8,220,249,180,80,114,58,157,80,150,1,72,3,34,115,
118,200,42,57,72,180,84,90,192,155,195,36,24,158,58,102,33,47,201,229,50,34,168,36,218,235,245,214,213,213,185,221,238,236,236,108,8,74,49,58,3,17,65,233,44,73,110,52,199,143,8,64,152,46,102,192,183,70,
163,81,74,161,35,125,150,194,231,210,7,0,181,75,56,28,230,52,82,182,98,212,222,38,151,53,112,120,248,70,242,84,96,235,45,44,44,164,128,20,233,248,153,251,30,252,183,162,162,2,234,210,118,121,116,78,78,
206,190,125,251,110,185,229,22,114,44,121,67,210,140,10,49,90,226,47,249,47,244,17,29,86,214,65,178,48,74,167,211,47,189,244,82,111,111,175,18,92,149,203,131,190,98,220,53,19,137,68,48,24,132,39,189,202,
13,169,17,136,187,72,102,85,140,158,241,120,252,220,185,115,7,14,28,216,185,115,39,187,13,40,140,206,158,61,187,107,215,46,216,96,151,148,148,96,23,220,191,127,127,48,24,36,215,25,205,16,128,67,164,194,
50,167,59,166,8,117,97,97,97,85,85,21,228,223,160,121,20,14,135,229,139,43,43,43,253,126,191,236,165,42,204,175,37,100,194,225,112,96,84,192,243,108,82,183,84,75,193,14,109,205,96,141,75,111,217,9,97,
159,154,208,35,134,148,204,178,77,10,194,235,176,177,84,150,73,9,10,119,218,123,82,134,244,208,161,67,188,16,150,233,51,30,168,84,64,36,222,177,99,135,215,235,61,120,240,160,58,194,213,171,87,87,85,85,
109,217,178,165,188,188,220,116,248,205,203,203,107,104,104,192,26,64,1,228,114,185,8,250,134,202,130,29,20,199,110,139,202,33,237,135,227,90,204,67,33,8,71,125,59,169,183,36,129,98,114,77,80,176,149,
173,18,228,149,176,240,193,61,54,57,57,57,54,54,38,141,239,44,119,81,89,116,91,194,89,112,31,246,247,247,15,13,13,213,212,212,208,41,81,201,110,217,89,44,243,231,154,154,26,228,248,112,138,68,143,69,241,
80,36,156,78,134,81,57,6,164,132,21,171,90,203,201,6,210,255,202,202,202,188,188,188,186,186,186,198,198,70,105,15,161,116,72,10,10,10,64,26,100,60,53,165,114,37,242,1,105,38,206,173,199,227,177,219,159,
177,147,187,221,110,148,74,196,66,88,134,105,249,111,36,18,249,228,39,63,73,115,60,165,148,237,118,187,63,253,233,79,223,115,207,61,216,126,84,136,199,30,195,203,199,187,136,185,124,40,20,98,150,173,92,
32,164,119,79,111,111,239,255,252,207,255,68,34,17,162,65,8,237,64,47,8,65,57,253,238,35,37,30,10,6,35,9,180,202,254,156,86,97,108,20,176,195,128,7,254,138,125,8,235,39,24,12,118,119,119,119,116,116,76,
77,77,249,124,190,93,187,118,113,163,149,201,163,244,126,181,140,206,244,164,47,47,47,103,177,197,39,233,166,152,157,157,237,118,187,91,90,90,44,149,142,17,137,76,134,8,240,94,156,113,73,122,170,217,193,
176,179,190,53,187,31,146,6,161,110,49,238,112,244,57,188,72,190,146,138,209,118,181,47,238,68,150,152,142,119,77,27,248,87,151,203,133,86,161,148,64,50,195,52,170,52,57,66,108,111,111,191,236,178,203,
246,238,221,203,59,186,170,170,170,165,165,197,225,112,108,218,180,137,4,110,198,34,88,31,32,96,194,166,64,129,140,75,75,75,205,49,160,29,233,95,7,104,117,109,18,137,4,44,160,80,26,203,250,75,41,171,154,
151,144,111,232,116,58,35,145,8,24,210,8,49,208,155,134,216,191,29,174,83,150,189,82,187,192,140,206,88,19,225,112,120,120,120,216,235,245,2,1,110,18,43,21,38,84,93,105,200,50,64,170,152,66,34,150,112,
75,114,225,84,234,199,219,158,48,228,204,244,48,200,207,87,87,87,67,105,200,108,25,73,148,152,199,227,153,152,152,192,55,149,150,34,8,76,64,34,34,118,75,231,58,105,13,147,1,66,139,236,169,176,176,208,
227,241,160,214,198,90,183,75,162,191,250,213,175,30,59,118,204,204,182,60,30,207,231,62,247,185,255,252,207,255,196,180,147,118,127,127,133,183,119,58,65,40,224,5,165,21,52,232,245,100,241,41,192,9,15,
32,30,143,239,220,185,115,247,238,221,166,113,98,6,31,97,249,43,198,224,40,51,205,104,139,110,158,68,98,153,211,63,53,210,0,154,69,202,18,165,211,233,241,241,113,40,236,88,94,125,246,100,36,158,135,239,
86,84,84,84,81,81,1,32,182,74,132,81,3,161,125,148,72,36,144,253,180,183,183,203,184,44,113,190,42,64,243,223,186,186,58,8,25,203,37,129,154,67,2,51,236,98,165,73,54,145,140,4,126,168,164,117,16,122,240,
127,121,251,242,224,72,175,234,250,150,186,181,244,170,181,181,47,163,217,247,197,51,227,193,227,61,6,219,49,46,131,193,152,34,134,144,84,65,150,170,148,33,44,129,20,129,20,69,146,138,227,42,8,182,9,5,
129,224,194,44,182,33,94,48,216,198,91,60,30,143,237,217,60,251,72,242,140,52,218,151,86,239,139,212,234,110,73,191,63,142,125,114,231,190,239,251,70,6,242,235,63,84,173,86,171,251,91,222,187,239,190,
115,207,57,247,221,106,41,29,96,113,201,51,193,194,175,238,17,151,49,36,209,96,34,85,86,86,250,253,126,121,223,121,235,209,102,87,81,59,26,26,26,110,189,245,214,225,225,97,216,174,109,221,186,21,199,112,
217,101,151,213,213,213,73,30,125,119,119,55,26,212,41,67,59,206,29,218,61,95,50,58,171,228,210,163,248,0,60,195,153,153,25,159,207,7,129,31,14,29,55,158,253,116,45,1,89,106,237,225,22,13,170,3,36,103,
56,103,128,27,242,32,148,169,166,165,105,131,76,105,213,180,12,6,131,139,139,139,251,247,239,239,236,236,188,242,202,43,101,106,169,160,125,38,194,216,206,32,148,32,204,5,2,129,64,32,128,228,11,133,65,
153,193,209,73,85,209,135,233,28,79,106,145,101,239,40,179,52,55,59,59,219,219,219,123,227,141,55,114,112,115,73,71,156,202,229,114,149,149,149,153,76,70,90,191,98,254,171,18,174,34,59,211,108,140,141,
238,213,10,167,76,162,121,228,216,83,19,223,228,149,33,15,239,244,233,211,191,248,197,47,20,31,182,173,173,237,239,254,238,239,110,190,249,102,220,5,44,18,224,5,98,7,38,239,172,223,239,39,229,156,172,
121,122,57,177,108,192,99,150,101,216,209,209,209,31,255,248,199,44,30,42,149,163,233,234,96,153,170,56,152,129,40,174,2,135,138,101,25,195,92,12,148,81,201,114,204,52,100,46,2,187,100,24,219,43,66,133,
185,126,175,89,179,166,177,177,177,191,191,63,149,74,149,74,37,150,136,164,180,154,137,170,154,167,110,183,219,236,69,45,201,221,216,239,50,226,155,9,141,172,54,203,177,68,62,15,78,13,97,206,57,40,59,
164,14,118,156,113,181,253,7,125,75,194,101,236,201,73,146,50,144,171,157,59,119,30,59,118,76,181,37,148,186,65,254,74,108,29,51,200,235,245,174,94,189,250,192,129,3,240,152,52,189,53,106,106,106,160,
64,49,185,28,124,155,207,231,163,71,199,37,67,179,50,233,117,155,13,253,100,159,96,144,69,36,18,77,174,174,25,134,152,199,21,139,197,169,169,41,108,13,228,90,151,207,231,65,97,49,59,128,72,116,194,52,
175,161,138,84,157,60,122,163,129,97,115,254,252,249,243,231,207,119,119,119,195,173,201,114,77,166,21,175,116,14,42,149,74,232,250,42,203,80,146,1,170,0,110,174,144,92,189,249,95,153,76,134,142,119,150,
116,17,217,126,34,145,72,108,217,178,69,130,134,71,142,28,65,207,239,116,58,13,42,11,84,200,68,9,32,82,119,0,34,200,190,52,65,6,151,85,171,86,75,59,77,108,234,65,16,38,135,228,238,187,239,38,253,8,137,
24,4,135,160,211,44,24,15,208,43,213,197,151,93,81,104,12,107,58,237,169,177,241,244,211,79,255,250,215,191,150,212,14,211,230,223,142,58,41,43,207,68,243,236,146,53,185,41,84,222,132,102,107,21,132,69,
28,188,236,181,225,252,152,159,159,87,20,52,16,93,80,185,193,231,208,27,71,45,198,124,30,8,4,90,91,91,51,153,76,125,125,61,118,126,236,248,199,34,161,132,203,120,204,193,96,144,50,2,135,212,21,75,44,185,
155,150,8,131,101,78,141,236,135,0,203,239,233,164,106,233,2,207,23,11,133,2,231,154,169,248,167,163,44,94,12,135,195,231,206,157,35,2,46,47,20,170,193,60,114,217,143,177,172,172,236,248,241,227,79,62,
249,228,150,45,91,64,215,1,126,114,227,141,55,98,199,217,222,222,222,222,222,78,213,152,157,194,27,78,47,150,187,210,75,46,90,30,51,221,0,123,31,53,214,116,58,61,48,48,128,170,130,20,98,161,59,42,238,
34,54,71,80,232,3,204,197,252,84,108,89,100,229,178,27,147,233,134,110,25,65,88,29,198,94,94,222,143,218,218,90,185,47,142,70,163,79,60,241,196,158,61,123,214,174,93,107,103,248,141,243,98,233,82,130,
101,52,174,85,60,7,5,137,202,254,94,28,148,14,140,122,243,4,17,61,79,156,56,177,180,180,116,215,93,119,73,146,140,42,145,203,165,66,202,187,165,186,132,122,16,233,246,9,164,88,141,21,9,166,115,133,83,
166,28,114,65,34,198,242,216,99,143,29,61,122,20,151,171,189,189,253,239,255,254,239,63,246,177,143,241,214,19,32,86,63,129,198,202,120,234,243,249,224,144,32,183,135,184,236,150,236,145,209,209,209,159,
254,244,167,236,82,102,14,95,74,132,76,175,6,149,74,155,72,171,29,189,73,133,99,187,160,127,201,174,175,151,12,58,144,68,177,142,196,67,5,22,84,44,22,165,155,168,162,169,248,124,190,203,47,191,156,60,
125,9,97,203,78,128,50,131,198,158,221,146,219,106,167,211,195,97,40,98,137,148,77,74,189,220,31,36,40,47,231,2,2,228,161,144,205,82,94,8,172,149,179,160,178,178,242,138,43,174,192,24,86,233,51,187,165,
48,99,224,242,150,72,36,158,120,226,137,117,235,214,129,20,79,72,4,86,195,112,111,71,160,147,73,155,154,116,202,98,215,174,159,189,157,158,208,195,169,200,218,8,1,1,168,4,209,156,112,205,154,53,88,145,
208,75,216,244,245,224,115,233,159,32,39,76,169,84,146,226,14,6,59,229,188,110,105,4,195,234,22,150,4,252,9,246,211,248,21,198,55,197,98,113,126,126,254,149,87,94,25,31,31,191,226,138,43,236,244,81,96,
128,129,100,178,180,180,84,91,91,123,232,208,161,235,174,187,78,1,220,230,115,212,187,17,20,112,239,73,213,148,17,240,146,233,6,235,141,39,79,158,236,234,234,194,87,195,34,150,46,63,244,205,225,249,130,
108,128,74,154,146,2,210,8,9,207,233,178,164,106,173,82,234,45,53,235,150,254,91,140,218,197,98,241,159,255,249,159,93,46,215,85,87,93,245,165,47,125,105,239,222,189,204,176,204,78,193,242,49,51,51,3,
166,29,111,1,6,24,59,105,241,72,36,58,68,157,228,51,207,60,243,244,211,79,95,50,215,160,159,170,131,223,27,175,164,93,16,97,59,30,54,199,81,44,29,201,198,51,133,118,203,15,76,84,109,248,253,126,84,83,
213,14,64,202,113,153,250,84,87,87,51,103,146,251,87,72,213,21,253,131,203,176,98,37,151,151,151,19,223,176,244,33,178,100,28,179,212,15,119,117,244,178,82,239,124,87,80,198,37,241,141,75,122,182,96,87,
103,238,29,53,255,65,8,152,209,57,251,220,185,115,244,66,64,152,70,83,102,202,128,37,60,224,114,185,30,122,232,33,122,221,145,57,234,243,249,234,234,234,144,106,208,140,129,70,102,156,140,88,116,65,84,
119,222,239,114,146,90,158,184,7,133,17,149,204,210,8,10,191,166,82,169,99,199,142,97,72,41,6,149,203,202,213,158,145,81,254,140,197,98,172,191,41,83,65,37,33,117,242,118,242,120,112,69,24,100,73,178,
225,6,164,188,188,124,96,96,32,149,74,93,121,229,149,172,156,154,0,14,192,187,133,133,133,249,249,249,167,158,122,202,231,243,237,222,189,155,125,2,237,34,181,204,200,36,145,94,42,155,157,83,39,185,253,
132,138,103,114,114,178,173,173,141,221,36,93,194,125,152,215,4,135,138,117,20,168,52,81,90,85,73,199,213,192,167,201,17,99,103,108,175,2,183,74,162,93,46,215,200,200,200,142,29,59,190,242,149,175,92,
117,213,85,50,107,54,219,155,49,100,19,1,28,26,26,130,191,138,172,26,209,118,138,49,90,105,97,103,102,102,190,247,189,239,245,247,247,43,148,201,238,33,55,100,46,171,70,142,206,40,138,26,30,202,135,75,
153,125,59,104,192,150,147,253,209,97,89,89,200,90,46,6,140,212,200,169,231,230,230,0,61,177,90,32,251,103,83,16,111,217,158,3,73,55,116,158,166,22,212,46,143,230,34,4,61,122,42,149,130,199,91,75,75,75,
123,123,59,219,191,254,97,179,99,187,205,40,254,138,189,111,85,85,21,171,154,150,241,142,87,27,73,24,30,59,118,236,56,118,236,24,33,142,197,197,197,104,52,138,193,73,124,153,6,6,143,61,246,88,34,145,104,
107,107,131,218,211,239,247,131,201,227,243,249,2,129,128,50,23,229,214,7,61,34,56,173,96,187,198,66,52,210,112,170,79,45,187,190,153,17,207,99,134,48,124,25,117,62,184,79,240,156,195,150,7,59,47,179,
66,136,247,88,170,129,129,111,152,127,162,82,92,117,44,181,84,169,211,228,16,52,23,252,23,69,192,220,164,67,216,246,235,95,255,122,215,174,93,27,54,108,80,35,143,131,15,61,123,158,124,242,201,197,197,
197,95,252,226,23,219,182,109,195,73,57,228,209,188,56,18,233,227,8,80,214,101,102,18,205,202,30,10,41,239,123,223,251,224,248,49,50,50,210,222,222,30,8,4,160,195,164,122,91,102,109,72,219,97,196,42,221,
197,24,172,25,139,81,200,53,85,130,118,117,12,217,251,85,37,209,101,101,101,155,54,109,122,230,153,103,44,179,102,179,73,160,116,50,66,246,55,49,49,129,254,147,12,208,180,179,144,174,231,252,151,87,94,
121,229,193,7,31,196,206,209,185,168,162,98,180,180,128,144,147,220,185,191,148,180,151,97,22,67,134,134,204,69,204,144,45,179,233,101,70,103,215,197,237,220,44,9,160,118,118,37,184,179,112,67,133,113,
51,118,39,118,61,200,213,190,141,153,175,25,157,237,118,21,74,55,8,218,117,77,77,13,56,12,166,217,239,31,42,70,155,251,78,58,58,184,68,43,0,250,117,88,46,159,18,232,144,166,37,233,116,26,203,24,140,39,
169,81,146,59,224,227,199,143,159,62,125,186,167,167,39,24,12,162,229,46,80,126,229,154,226,192,146,194,17,226,176,209,56,66,205,56,100,186,8,214,48,17,4,75,90,89,25,187,209,121,193,82,6,141,9,47,7,16,
26,53,225,91,185,130,209,236,138,209,217,148,126,78,79,79,67,33,230,188,175,49,43,132,234,9,220,129,49,58,121,170,146,85,205,22,59,56,201,233,233,233,100,50,9,183,98,181,210,226,230,165,211,233,170,170,
170,174,174,174,153,153,153,82,169,132,118,227,166,147,150,204,145,81,11,85,233,27,30,211,211,211,80,72,90,74,179,176,150,210,182,230,154,107,174,65,130,143,63,101,179,89,180,195,80,132,107,57,81,9,124,
203,106,161,235,98,199,66,85,10,179,43,77,216,141,45,190,14,159,85,164,108,76,226,164,153,156,12,199,178,131,140,220,100,192,85,10,73,159,76,19,16,218,36,179,98,105,105,41,147,201,220,123,239,189,79,62,
249,36,103,148,188,242,210,185,197,178,139,171,76,165,85,121,144,166,60,150,52,94,121,155,200,9,147,155,24,89,36,144,65,16,206,92,36,249,56,135,30,148,206,184,50,73,96,87,61,161,7,142,157,51,31,142,132,
61,65,208,247,153,69,66,5,24,242,94,180,181,181,97,51,81,124,231,81,16,15,254,10,103,174,76,38,35,89,246,192,247,176,187,175,174,174,150,74,5,202,157,126,127,160,195,161,54,88,44,22,229,52,87,18,24,75,
202,182,185,245,65,117,45,26,141,86,84,84,100,50,153,72,36,98,70,91,4,141,39,159,124,18,118,128,20,130,72,136,169,183,183,183,191,191,127,104,104,40,30,143,79,77,77,69,34,145,88,44,150,72,36,200,184,159,
159,159,167,82,204,110,255,7,136,53,151,203,101,179,217,88,44,22,139,197,80,245,213,245,42,182,230,117,89,181,239,116,93,220,236,21,80,50,7,58,166,40,240,32,132,12,211,220,22,111,187,112,225,130,76,79,
236,98,132,130,56,212,177,66,128,0,111,70,9,65,114,6,34,230,66,110,206,24,151,201,100,70,70,70,154,154,154,56,176,248,201,232,169,94,94,94,94,93,93,189,106,213,170,153,153,153,181,107,215,74,220,64,217,
111,211,45,196,174,158,57,61,61,45,197,199,106,232,176,53,76,48,24,188,234,170,171,208,157,158,205,111,64,9,128,77,132,221,48,197,123,60,30,143,220,169,200,35,145,12,1,19,214,119,160,115,200,143,10,6,
131,77,77,77,88,213,233,227,1,33,12,185,116,102,104,230,79,66,114,192,145,208,150,161,169,169,201,108,120,44,127,221,183,111,223,223,254,237,223,14,15,15,91,46,141,136,71,151,12,208,38,214,36,249,21,146,
71,165,210,17,201,226,167,178,142,133,83,194,172,42,221,166,170,216,117,113,135,86,75,132,129,181,59,51,218,202,250,30,143,80,178,56,76,46,7,162,60,76,16,225,75,39,73,8,38,73,3,109,153,44,51,107,249,126,
236,208,73,136,70,93,170,186,186,90,42,226,84,121,144,155,39,153,177,253,14,65,217,161,126,75,253,151,169,246,150,146,72,7,41,35,131,143,215,235,205,231,243,115,115,115,189,189,189,50,20,112,51,145,207,
231,127,249,203,95,2,122,70,134,203,182,24,202,96,4,65,15,65,9,138,4,144,20,231,231,231,235,234,234,128,92,219,237,92,45,53,210,21,21,21,164,87,255,47,252,136,15,178,100,206,217,1,193,180,130,229,129,
166,211,105,228,182,212,25,74,136,109,114,114,82,153,143,72,120,203,146,242,108,70,13,46,161,20,100,83,147,70,40,138,115,9,251,125,233,31,52,52,52,4,207,13,9,24,193,62,152,123,195,186,186,186,66,161,208,
220,220,108,246,244,98,110,200,234,132,218,71,227,249,228,228,36,178,42,115,232,147,209,88,95,95,191,107,215,46,116,4,111,110,110,134,176,30,205,3,177,137,147,229,2,165,169,197,19,2,29,150,12,57,5,161,
90,146,237,212,182,128,65,45,28,14,183,182,182,134,66,33,66,159,146,175,50,55,55,135,229,112,193,254,97,162,210,164,163,129,168,196,122,8,99,116,58,157,126,224,129,7,238,187,239,62,248,20,203,25,46,75,
202,203,9,208,178,170,97,198,77,170,254,44,3,40,23,81,116,76,71,60,146,129,143,113,22,175,168,154,146,58,60,62,130,193,32,123,22,75,99,110,203,0,45,31,76,186,213,219,248,43,186,162,0,187,160,196,70,118,
159,144,23,167,177,177,81,90,92,90,86,248,41,185,98,55,41,24,3,168,210,183,233,217,66,136,137,250,169,119,75,130,182,11,211,152,113,216,175,91,86,146,100,6,233,44,128,228,127,133,66,161,3,7,14,72,203,
23,137,171,60,249,228,147,185,92,14,44,126,244,134,151,29,229,149,209,133,165,123,126,77,77,77,107,107,171,57,203,46,121,250,72,215,84,248,246,88,10,192,85,100,84,250,34,248,106,210,248,3,6,111,174,119,
186,73,65,235,193,201,176,176,176,0,154,148,101,81,194,164,155,40,32,130,156,71,48,210,161,78,38,62,75,34,170,164,154,81,8,175,218,206,195,156,12,193,177,84,42,77,77,77,1,97,144,232,71,50,153,132,106,
0,123,58,46,125,0,118,8,245,90,42,146,145,125,216,109,217,144,75,182,180,180,108,218,180,9,135,218,208,208,64,222,107,56,28,206,102,179,104,92,141,107,78,56,5,11,12,249,42,32,171,96,2,224,137,244,252,
131,49,46,89,189,10,98,86,109,176,165,250,166,185,185,185,181,181,85,86,156,137,56,171,221,3,193,98,5,67,91,106,62,225,116,142,102,163,178,128,206,242,224,161,67,135,190,244,165,47,77,77,77,81,164,59,
55,55,55,55,55,135,157,144,101,86,165,186,158,187,46,182,212,49,247,28,202,64,198,46,46,112,207,7,88,80,57,205,74,191,26,181,112,186,46,110,238,39,31,181,181,181,224,216,50,182,42,23,1,151,97,120,235,
186,184,121,149,101,151,113,90,181,224,197,185,185,57,244,220,48,79,144,243,154,253,59,44,139,114,228,69,96,218,66,110,103,135,74,91,246,223,146,111,0,186,250,123,194,208,164,141,91,170,34,84,121,150,
132,13,7,251,61,178,75,97,244,56,61,61,45,89,88,120,243,145,35,71,198,199,199,81,24,228,253,82,206,242,36,53,152,218,102,172,220,157,157,157,150,238,64,170,1,177,157,18,71,245,23,245,216,221,3,249,10,
29,200,228,55,177,39,147,41,93,129,55,52,104,225,211,211,211,150,187,63,187,36,218,12,217,200,157,113,184,176,167,32,193,147,201,157,162,49,226,61,104,205,32,175,81,52,26,125,249,229,151,119,238,220,57,
50,50,130,14,91,220,4,241,61,35,35,35,171,87,175,166,242,135,209,89,26,144,154,109,20,92,239,120,224,89,102,118,24,178,157,157,157,43,86,172,192,63,2,222,149,9,56,108,36,211,233,52,213,195,240,246,230,
254,128,39,91,89,89,137,22,77,48,77,166,124,11,177,155,74,63,197,104,182,36,117,84,85,85,117,116,116,168,6,116,56,41,165,193,65,100,196,98,44,3,189,250,233,18,61,218,43,42,42,26,26,26,234,235,235,253,
126,63,187,93,72,107,173,111,125,235,91,247,221,119,159,196,103,164,102,26,149,88,100,175,96,100,171,153,102,185,97,84,192,171,131,155,176,101,238,198,110,176,150,245,64,213,61,86,121,173,153,131,252,
138,43,174,248,237,111,127,107,54,186,85,58,38,187,102,125,16,215,168,94,95,124,39,125,74,9,44,168,69,130,67,139,133,4,243,32,177,53,1,121,9,15,153,235,88,162,145,146,109,101,122,127,75,99,97,59,6,234,
50,31,236,171,98,18,183,77,62,171,100,106,218,109,146,152,91,92,119,221,117,111,189,245,22,149,56,184,47,195,195,195,7,14,28,128,215,60,205,52,96,148,111,102,247,188,230,178,17,68,89,89,89,79,79,143,217,
39,222,236,134,101,153,86,51,230,112,155,85,89,89,233,177,188,109,102,143,25,208,230,213,205,224,134,212,196,245,168,151,27,25,25,145,198,222,234,114,219,101,208,124,32,58,83,32,167,38,158,229,162,196,
2,20,134,11,55,71,76,12,15,31,62,220,212,212,68,66,146,178,89,72,165,82,188,43,178,168,133,217,98,73,142,150,102,131,106,157,167,177,239,202,149,43,41,226,170,174,174,102,27,92,213,171,187,179,179,51,
30,143,195,25,0,59,18,164,222,108,87,200,125,55,232,247,80,166,201,254,123,114,130,201,0,173,90,154,86,87,87,111,216,176,161,171,171,75,189,78,50,187,20,182,202,106,4,214,0,203,0,253,191,251,50,143,39,
28,14,163,84,0,149,63,128,221,249,249,121,228,167,67,67,67,247,220,115,207,83,79,61,101,118,210,147,3,128,203,63,38,140,76,250,204,232,236,60,250,157,195,4,239,2,153,27,108,46,195,215,85,205,86,245,18,
53,63,249,150,91,110,25,26,26,50,237,144,236,122,238,169,169,199,239,101,233,66,181,117,70,236,54,173,114,92,134,193,33,193,37,245,0,114,74,22,157,210,115,59,240,103,24,236,84,12,34,125,208,68,213,222,
21,229,3,153,150,132,15,203,95,92,0,0,32,0,73,68,65,84,254,213,213,54,25,117,92,252,156,21,246,40,53,87,86,86,94,118,217,101,111,188,241,6,67,97,169,84,58,124,248,48,140,191,201,94,3,60,128,190,125,150,
7,201,147,226,243,100,50,73,203,98,203,188,193,252,16,57,191,184,32,17,17,245,88,166,204,118,234,79,214,79,44,213,86,170,68,238,118,187,39,39,39,217,106,86,174,243,150,12,121,153,141,242,75,73,87,192,
202,172,76,24,120,23,25,178,25,137,200,66,129,199,163,252,58,244,14,151,172,100,105,95,224,114,185,166,166,166,160,69,100,254,98,25,157,45,133,67,38,193,206,231,243,173,89,179,70,18,54,154,155,155,149,
74,77,206,252,154,154,26,175,215,27,141,70,89,154,83,113,1,61,46,17,236,216,115,30,39,139,0,173,228,94,28,133,184,128,62,159,111,251,246,237,116,28,55,203,134,116,199,55,85,0,240,6,147,221,216,84,238,
236,245,122,27,27,27,49,70,25,244,179,217,44,22,36,132,254,125,251,246,221,123,239,189,217,108,54,28,14,143,143,143,203,235,70,251,33,115,23,69,228,202,101,213,132,197,101,211,62,85,185,5,216,217,195,
203,219,129,54,202,210,251,24,254,36,82,189,130,242,160,3,247,96,237,218,181,91,183,110,133,55,169,242,180,187,100,156,146,206,112,216,72,201,40,47,251,28,209,51,218,161,52,7,185,132,58,78,162,186,188,
32,40,44,57,111,103,101,164,147,121,15,145,13,44,162,150,229,107,22,30,47,217,197,138,94,96,178,93,11,217,114,138,162,110,30,152,93,140,150,244,161,178,178,178,157,59,119,30,62,124,24,91,135,133,133,133,
253,251,247,163,179,1,10,125,242,114,205,206,206,74,86,130,249,153,18,69,156,153,153,201,229,114,220,146,94,242,74,202,191,146,165,142,218,236,219,61,9,121,81,36,49,206,242,54,171,218,160,114,151,55,119,
109,139,139,139,210,184,78,214,19,228,63,218,225,89,232,113,197,121,43,27,11,176,112,199,39,76,87,205,242,40,241,104,126,114,125,125,61,138,60,148,77,42,20,114,110,110,46,147,201,4,2,129,159,255,252,231,
233,116,250,19,159,248,4,186,25,152,192,171,105,171,164,174,97,69,69,197,166,77,155,80,204,193,43,77,77,77,170,129,133,169,196,169,170,170,106,107,107,75,167,211,136,134,236,21,64,49,11,224,248,108,54,
91,85,85,5,221,10,229,24,72,253,144,183,74,145,247,210,210,82,107,107,235,250,245,235,177,246,152,73,40,111,1,206,212,50,15,69,116,144,230,206,252,137,94,62,216,74,203,171,129,39,185,92,14,205,213,46,
92,184,240,236,179,207,194,47,52,16,8,32,121,145,73,132,3,109,25,103,205,174,49,210,185,148,182,209,118,53,25,181,12,88,234,83,184,179,70,169,131,201,154,236,70,47,241,104,187,0,221,212,212,244,254,247,
191,255,204,153,51,150,61,200,9,67,203,235,175,44,231,165,104,144,138,4,57,245,80,12,116,187,221,193,96,144,234,71,75,36,151,248,6,167,21,234,234,178,197,40,19,64,75,241,177,229,10,68,3,101,110,207,45,
163,179,101,202,233,172,11,101,178,133,18,11,203,179,152,179,150,247,78,94,67,9,87,170,7,198,45,38,81,85,85,213,31,253,209,31,189,252,242,203,75,75,75,39,78,156,136,197,98,225,112,24,130,20,76,127,6,168,
92,46,199,253,174,9,151,185,46,182,238,2,206,57,52,52,212,210,210,66,42,176,66,252,45,199,39,3,58,51,209,183,95,119,240,3,51,171,150,0,97,85,89,217,101,229,208,10,169,8,33,69,158,3,198,186,188,79,234,
57,223,44,211,94,76,75,85,63,52,171,7,150,99,2,59,110,246,235,3,254,107,18,113,148,82,118,114,114,178,80,40,252,236,103,63,43,43,43,235,235,235,251,220,231,62,7,59,27,75,145,33,158,68,34,17,115,39,184,
113,227,70,98,88,144,167,171,98,186,169,100,225,129,161,170,27,143,199,105,130,42,219,88,84,85,85,65,176,0,67,87,150,22,233,108,43,83,152,238,238,238,189,123,247,162,124,97,233,122,193,159,240,150,83,
177,91,34,15,85,85,85,169,84,74,70,231,234,234,234,112,56,12,0,74,154,86,75,128,133,192,220,244,244,116,77,77,141,188,23,104,126,102,18,158,28,50,44,185,3,35,196,36,73,87,102,139,69,215,59,38,80,50,195,
146,90,109,126,175,204,212,72,39,85,249,135,89,21,100,92,168,172,172,188,233,166,155,202,203,203,223,122,235,45,19,223,112,168,181,200,143,101,134,206,144,205,40,140,129,202,214,116,108,161,100,87,3,164,
29,10,62,150,192,171,165,99,137,154,194,118,196,100,146,107,137,108,56,228,206,174,139,93,98,28,8,30,210,151,28,75,53,41,216,74,96,97,74,222,156,153,212,168,55,74,85,247,200,200,200,233,211,167,209,158,
120,120,120,184,170,170,42,157,78,151,74,165,230,230,102,72,166,97,139,143,144,5,181,189,29,251,133,91,16,94,144,133,133,133,201,201,201,218,218,90,105,27,109,89,191,149,153,28,163,179,252,171,199,188,
67,202,139,64,9,159,0,116,168,190,144,234,136,241,250,240,240,176,106,107,36,111,146,36,57,114,228,241,246,144,14,65,201,141,57,160,101,100,87,182,24,210,139,71,45,80,245,245,245,116,148,87,219,88,121,
178,185,92,238,27,223,248,6,198,196,232,232,232,215,190,246,181,79,125,234,83,155,55,111,246,120,60,232,157,97,70,106,85,184,64,73,51,157,78,115,10,185,221,110,54,145,116,25,45,56,101,231,99,126,78,117,
117,117,75,75,11,218,253,169,123,4,239,142,88,44,86,93,93,13,202,29,225,29,94,115,143,199,211,213,213,117,253,245,215,119,119,119,83,83,96,9,11,240,146,178,167,137,105,180,132,147,10,133,66,51,51,51,192,
242,124,62,95,67,67,3,86,32,203,208,140,205,41,6,55,56,236,163,163,163,225,112,24,83,17,121,55,107,131,252,34,187,36,90,209,228,45,145,13,203,87,84,170,161,144,4,153,86,227,152,155,155,155,229,49,144,
36,74,108,20,37,25,153,66,210,62,237,234,171,175,174,173,173,205,102,179,23,46,92,48,53,126,14,249,163,66,153,100,194,53,63,63,239,245,122,37,220,76,238,23,70,151,195,39,3,205,227,238,94,158,166,2,10,
164,197,171,203,166,147,6,138,138,74,17,103,71,94,180,140,68,180,21,84,239,81,160,54,235,159,168,87,103,179,89,180,112,91,166,116,83,189,13,114,62,92,165,76,38,243,234,171,175,158,58,117,10,30,185,189,
189,189,60,235,124,62,63,61,61,13,205,4,136,85,40,128,161,38,239,252,117,88,75,100,217,16,180,81,118,28,117,190,50,208,1,153,245,57,143,89,42,81,45,56,93,70,143,43,48,37,76,136,67,30,68,36,18,1,49,206,
146,157,67,122,172,148,122,51,210,73,174,49,108,212,21,244,108,169,160,115,224,252,114,239,80,44,22,161,42,84,72,186,75,52,78,198,151,254,240,135,63,132,45,58,94,204,231,243,223,253,238,119,223,247,190,
247,125,224,3,31,104,104,104,64,167,109,149,71,203,193,205,41,148,72,36,114,185,28,72,108,61,61,61,170,208,234,50,26,249,152,168,17,186,217,230,243,249,100,50,137,84,154,181,89,26,146,128,212,41,139,21,
60,247,219,110,187,173,182,182,150,232,135,131,110,133,140,73,229,162,103,102,46,104,234,211,220,220,28,8,4,128,102,42,247,225,183,199,150,199,3,88,131,193,110,102,102,102,108,108,12,128,21,129,148,80,
40,20,143,199,229,130,103,55,148,165,205,147,101,92,54,151,28,57,90,84,47,24,187,153,134,222,108,44,78,44,44,44,72,8,18,31,8,209,19,166,52,44,206,49,158,87,175,94,189,114,229,202,98,177,120,254,252,121,
165,66,164,41,163,217,204,222,174,175,27,87,235,165,165,37,34,161,12,208,144,20,209,167,223,242,116,160,49,145,46,140,220,19,152,146,49,203,244,89,237,93,200,97,87,200,134,203,177,95,154,218,70,75,199,
56,214,24,204,251,194,173,54,96,55,212,235,192,93,49,209,81,187,232,140,159,137,68,2,139,235,169,83,167,142,30,61,10,11,208,165,165,165,163,71,143,170,108,160,88,44,34,70,7,2,1,84,131,50,153,12,28,202,
28,242,116,89,97,150,52,170,66,161,48,51,51,83,91,91,203,1,99,23,163,17,157,77,137,150,71,177,68,205,238,144,42,131,70,130,195,226,178,233,240,130,51,25,30,30,230,122,98,185,243,98,75,20,201,101,70,158,
37,135,11,229,127,166,125,135,203,198,240,69,141,120,73,90,92,177,98,69,40,20,146,67,223,108,45,234,118,187,95,122,233,165,115,231,206,41,245,173,219,237,222,183,111,223,224,224,224,159,255,249,159,163,
175,32,234,120,156,78,202,18,72,218,152,204,204,204,224,102,155,54,205,38,91,211,178,24,128,38,176,137,68,2,187,84,212,49,64,89,149,64,135,172,87,224,241,220,115,207,221,113,199,29,138,23,104,134,51,12,
95,166,207,14,36,33,136,47,128,170,227,99,85,15,26,28,0,52,14,156,210,248,223,177,177,49,148,251,188,94,111,44,22,163,186,90,9,61,156,241,13,7,124,198,228,51,217,117,215,117,217,183,172,118,185,92,201,
100,146,65,153,2,57,75,150,133,76,144,235,234,234,118,238,220,137,205,193,228,228,164,194,55,204,29,146,29,245,138,56,21,121,26,174,119,186,50,210,119,69,226,27,50,215,81,151,171,166,166,198,212,98,200,
165,206,18,148,183,203,248,36,58,129,81,100,105,59,126,73,147,10,185,141,70,206,97,249,47,102,111,185,120,60,14,6,212,37,115,118,57,32,225,175,121,242,228,73,84,5,209,185,198,231,243,29,59,118,76,154,
140,203,127,143,70,163,11,11,11,88,15,188,94,111,58,157,198,2,105,217,57,143,123,29,185,189,227,152,193,14,128,166,196,118,162,21,84,122,205,180,195,67,195,13,75,82,129,101,55,123,162,69,210,221,92,142,
242,137,137,9,212,247,212,66,173,46,159,140,188,42,199,193,95,49,64,205,194,130,74,201,77,192,222,78,76,185,114,229,74,191,223,15,250,176,146,48,112,80,142,143,143,163,117,136,84,223,242,49,53,53,117,
255,253,247,223,113,199,29,107,215,174,13,6,131,32,210,227,198,16,103,144,236,61,242,234,86,174,92,25,139,197,208,0,84,245,170,176,236,102,107,137,80,135,195,97,84,48,216,50,10,237,242,0,10,203,170,32,
99,49,156,84,49,81,45,115,79,222,2,248,52,89,134,63,41,160,144,117,45,169,214,147,54,129,72,115,148,105,137,203,229,26,29,29,197,2,19,12,6,37,210,13,125,205,37,169,87,138,117,238,114,108,71,224,208,50,
217,217,220,18,58,44,210,174,9,221,240,118,200,156,139,51,162,178,178,242,170,171,174,66,103,50,44,69,150,70,160,150,28,59,115,184,210,68,65,214,42,225,102,71,62,217,226,226,34,52,159,116,224,50,207,133,
6,208,118,76,62,187,196,240,146,91,114,21,196,45,247,181,206,174,199,10,211,176,131,164,128,204,248,253,126,164,32,112,63,14,4,2,118,220,65,243,152,251,250,250,94,123,237,53,76,213,82,169,132,212,97,120,
120,120,116,116,212,65,202,8,69,2,26,89,213,213,213,169,4,194,178,13,152,89,90,167,246,7,195,94,237,54,228,117,147,185,236,69,219,80,0,17,84,148,130,178,74,120,78,253,164,155,173,228,180,170,70,109,46,
151,107,112,112,80,85,114,236,148,66,138,249,104,118,204,147,27,118,245,129,170,169,179,229,62,87,14,250,214,214,86,168,120,155,155,155,163,209,168,153,59,131,184,253,221,239,126,151,201,130,101,140,46,
20,10,15,63,252,240,21,87,92,177,97,195,6,26,51,193,68,220,110,100,191,231,61,239,33,80,27,141,70,81,42,52,41,95,146,114,111,215,88,222,239,247,195,248,17,121,52,78,164,186,186,26,188,8,197,89,4,89,231,
185,231,158,251,208,135,62,164,116,40,106,160,204,205,205,201,166,174,106,148,168,76,193,101,116,212,69,18,237,241,120,224,96,64,144,68,217,228,159,63,127,30,81,187,174,174,78,206,79,176,20,150,227,127,
127,73,95,17,59,67,116,103,105,184,250,43,233,67,140,197,118,60,84,94,135,13,27,54,16,149,6,187,84,229,206,118,189,41,44,241,13,218,33,73,124,207,245,78,207,51,80,125,2,129,0,171,65,150,3,15,16,147,229,
94,205,156,140,42,229,4,54,229,252,102,75,96,193,117,113,103,44,101,118,108,202,38,157,201,224,244,20,148,41,63,122,160,228,114,185,250,250,122,234,21,44,227,236,210,210,210,235,175,191,126,236,216,49,
100,126,72,11,144,17,159,60,121,210,89,113,142,104,16,141,70,27,26,26,208,148,221,231,243,57,164,17,60,54,101,9,233,241,120,56,156,104,15,128,245,9,149,54,89,30,96,219,67,94,70,15,243,112,106,139,81,204,
161,220,139,63,49,219,73,0,66,18,39,9,100,124,178,109,219,182,254,254,254,68,34,177,76,82,186,25,157,37,43,208,101,223,41,195,101,99,219,102,57,226,59,58,58,232,165,208,220,220,156,201,100,148,67,99,121,
121,249,67,15,61,20,139,197,248,186,178,217,149,238,98,135,14,29,26,24,24,184,250,234,171,209,115,214,237,118,175,93,187,150,125,218,229,225,109,222,188,25,68,84,142,176,217,217,217,66,161,0,208,195,92,
81,77,149,148,235,226,246,119,110,183,187,177,177,17,54,90,8,232,155,55,111,126,237,181,215,88,189,97,116,198,44,61,116,232,208,53,215,92,131,158,229,118,9,114,58,157,118,128,119,77,229,167,236,218,135,
97,135,149,67,86,11,25,130,113,240,32,198,0,31,67,219,29,249,69,44,117,58,115,176,236,34,175,90,78,100,174,42,255,133,92,126,135,152,5,44,94,6,104,83,233,43,197,126,176,95,0,53,5,31,59,49,49,97,230,55,
102,140,54,243,89,204,50,12,81,136,62,224,65,140,184,64,90,52,178,45,54,97,178,35,69,72,254,134,157,78,88,253,154,203,229,34,145,8,220,7,157,235,111,203,81,108,187,236,155,115,94,50,38,40,134,149,153,
117,161,253,180,207,231,131,87,148,101,84,25,27,27,59,120,240,32,100,168,152,116,225,112,184,188,188,252,212,169,83,208,27,59,231,4,184,224,177,88,172,161,161,1,166,102,161,80,40,147,201,48,66,210,61,
145,19,1,242,105,12,126,212,90,100,227,55,150,82,84,212,226,61,53,113,5,143,105,95,39,159,83,146,0,106,58,56,176,28,70,248,172,96,48,40,109,142,65,140,175,170,170,74,36,18,195,195,195,202,38,201,78,133,
105,154,254,216,37,218,14,76,117,75,22,7,158,215,213,213,193,205,150,214,174,129,64,128,221,110,48,55,94,126,249,229,19,39,78,200,172,89,198,104,90,68,18,119,75,36,18,207,61,247,220,174,93,187,214,173,
91,183,115,231,206,135,31,126,216,212,239,214,214,214,110,219,182,77,86,228,249,60,149,74,205,205,205,213,215,215,43,159,19,147,204,175,198,58,118,121,85,85,85,173,173,173,145,72,4,71,216,209,209,113,
254,252,121,51,115,193,103,62,255,252,243,183,223,126,187,93,109,48,157,78,19,92,178,52,240,83,36,7,245,6,175,215,11,4,141,88,135,100,40,243,188,206,157,59,135,2,3,246,122,240,18,145,86,94,14,4,59,9,237,
57,67,156,230,118,91,61,183,99,143,193,38,201,239,247,7,2,1,134,39,105,152,101,183,141,171,170,170,66,213,148,73,6,124,44,77,108,80,254,42,187,151,170,46,121,242,97,110,252,1,104,194,53,76,66,115,10,20,
102,128,94,102,112,132,253,230,236,236,44,246,55,191,67,116,182,187,5,230,0,94,166,121,16,22,66,108,23,44,203,75,152,131,241,120,188,171,171,11,249,135,92,86,139,197,34,124,204,137,116,87,87,87,87,84,
84,12,13,13,193,112,109,102,102,70,54,103,161,67,33,19,118,70,128,116,58,141,129,1,103,87,40,48,213,109,197,253,66,130,203,249,34,19,124,147,107,200,87,192,152,118,89,181,66,245,88,86,78,44,73,96,38,217,
30,246,225,212,227,209,199,14,9,72,40,20,218,190,125,251,252,252,252,91,111,189,21,143,199,237,106,53,102,69,130,154,17,187,2,163,2,55,28,30,44,58,163,61,185,36,42,85,87,87,55,53,53,197,227,113,156,212,
196,196,196,47,127,249,75,83,59,107,162,28,210,25,107,97,97,225,205,55,223,4,119,210,28,187,149,149,149,55,222,120,35,96,16,89,149,146,170,129,153,153,25,212,220,248,177,210,174,211,20,185,1,137,99,19,
197,142,142,14,128,149,29,29,29,195,195,195,148,180,40,17,252,225,195,135,65,255,50,99,116,169,84,194,77,116,96,119,152,3,131,60,28,112,146,164,34,137,233,179,236,114,224,114,185,134,135,135,217,246,27,
59,116,84,89,249,213,80,174,59,239,180,236,202,107,114,104,17,151,176,12,211,210,32,165,90,60,48,195,165,13,191,89,65,49,151,16,183,219,29,14,135,81,8,162,202,113,251,246,237,211,211,211,168,44,169,24,
141,149,73,49,160,236,64,57,197,227,148,219,205,166,166,38,36,73,236,131,108,118,77,149,49,203,97,187,57,63,63,159,76,38,145,21,162,147,147,165,83,210,187,125,56,243,217,149,172,95,213,162,228,42,232,
48,211,153,228,94,184,112,33,24,12,118,119,119,35,154,227,242,30,57,114,4,150,9,48,65,131,53,93,36,18,201,102,179,128,10,161,2,195,174,78,246,61,160,220,95,54,126,131,233,62,106,245,48,45,65,182,193,86,
41,166,139,30,232,188,38,188,198,15,183,28,198,242,201,69,102,73,118,58,84,73,42,80,197,104,140,57,96,246,204,176,176,5,224,240,109,104,104,184,234,170,171,162,209,104,127,127,127,44,22,51,57,215,46,225,
230,35,211,103,203,21,219,36,111,56,39,209,120,52,52,52,192,143,88,213,109,130,193,96,101,101,101,44,22,203,231,243,223,255,254,247,77,232,153,229,114,25,163,37,108,13,63,160,147,39,79,198,98,177,55,222,
120,67,109,65,246,236,217,83,95,95,47,155,239,153,92,52,214,61,66,161,16,172,95,217,52,94,142,81,244,48,86,124,9,252,108,110,110,246,120,60,169,84,106,227,198,141,135,15,31,86,253,43,193,243,95,92,92,
124,238,185,231,110,191,253,118,19,186,77,38,147,166,195,181,41,81,145,134,42,56,193,186,186,186,218,218,90,2,160,82,251,107,150,7,11,133,66,36,18,145,158,209,181,181,181,145,72,68,25,134,44,19,16,179,
139,206,46,123,23,14,100,148,141,141,141,129,64,0,120,162,93,246,199,36,148,144,133,101,59,30,210,36,216,187,128,167,236,245,122,87,172,88,129,108,55,153,76,198,98,49,244,97,144,90,103,59,181,186,101,
140,86,18,92,56,14,147,188,97,234,235,84,250,108,23,61,231,231,231,209,125,85,82,164,209,147,201,245,135,126,56,83,27,85,76,231,53,87,29,129,237,58,1,149,149,149,141,142,142,238,219,183,111,205,154,53,
87,93,117,85,89,89,89,36,18,217,191,127,63,46,81,58,157,174,172,172,236,232,232,200,231,243,137,68,130,198,220,88,195,170,171,171,19,137,4,67,150,157,92,16,249,104,44,22,131,233,35,220,75,80,33,176,163,
118,168,174,246,248,19,119,69,50,16,51,209,134,75,40,146,241,183,111,135,60,121,89,11,54,121,29,118,155,53,56,21,192,223,29,91,6,102,239,28,148,77,77,77,77,77,77,209,104,180,183,183,151,97,90,246,212,
144,24,43,17,28,7,69,147,226,117,57,39,209,112,248,148,65,150,7,31,10,133,22,22,22,254,253,223,255,61,30,143,203,45,2,99,177,100,218,241,170,81,205,85,87,87,135,183,205,204,204,192,51,147,7,217,217,217,
185,123,247,110,85,154,51,45,164,153,169,101,179,217,66,161,0,226,20,249,24,152,252,185,92,14,132,121,203,10,59,98,77,56,28,14,6,131,145,72,100,104,104,200,180,253,172,168,168,64,18,77,222,21,7,4,188,
255,29,114,103,54,88,163,229,169,223,239,111,107,107,147,61,121,225,79,77,25,177,66,3,136,111,72,159,104,159,207,103,250,49,81,238,225,92,30,116,78,162,37,135,193,235,245,134,66,161,154,154,26,234,53,
44,25,5,230,98,111,73,31,50,247,127,0,28,184,137,86,188,79,36,40,13,13,13,197,98,17,9,53,52,196,206,41,51,1,116,105,45,32,179,170,197,197,69,144,76,44,237,218,47,25,160,37,49,148,45,34,205,32,242,135,
122,56,20,108,21,95,214,37,44,198,228,130,45,219,117,154,99,160,84,42,189,245,214,91,216,141,161,50,116,195,13,55,60,247,220,115,200,114,0,99,182,180,180,184,221,238,241,241,113,246,202,225,199,194,150,
61,157,78,179,240,224,80,54,156,159,159,79,167,211,72,236,208,91,82,66,121,178,108,110,242,154,113,181,45,225,29,236,93,26,27,27,67,161,144,186,248,30,103,142,183,93,47,25,105,159,72,115,119,180,155,147,
232,4,140,149,121,161,155,155,155,155,155,155,179,217,108,111,111,47,92,238,44,123,178,73,245,154,93,233,192,196,248,148,51,28,135,123,93,93,93,115,115,179,233,122,206,255,61,120,240,224,169,83,167,24,
139,101,4,55,127,229,137,251,253,126,48,49,84,195,121,220,251,202,202,202,59,239,188,83,26,221,73,141,128,92,189,36,232,188,184,184,152,72,36,96,4,129,189,54,58,226,152,171,180,20,32,209,133,170,169,169,
233,134,27,110,248,201,79,126,34,27,101,202,111,127,225,133,23,62,240,129,15,200,16,44,85,145,14,209,153,31,242,210,75,47,189,244,210,75,95,254,242,151,105,131,71,239,105,28,167,221,180,28,25,25,1,161,
152,1,26,99,195,172,239,57,131,146,14,91,66,151,203,213,216,216,88,83,83,19,10,133,106,107,107,229,82,196,15,151,117,33,254,181,171,171,43,28,14,15,14,14,50,218,18,79,119,206,254,160,106,1,137,149,148,
21,187,42,11,54,28,46,151,107,197,138,21,83,83,83,147,147,147,14,132,125,245,43,104,21,156,74,48,147,81,218,113,185,49,181,196,55,84,161,149,54,229,112,175,101,175,53,135,242,224,255,93,250,108,214,255,
149,101,93,48,24,68,215,105,153,129,46,44,44,68,34,145,137,137,137,108,54,203,73,20,139,197,30,126,248,97,12,87,24,67,118,119,119,135,66,161,169,169,41,229,120,199,95,1,232,251,253,254,84,42,197,150,5,
118,71,155,207,231,193,150,35,17,139,54,18,178,21,58,118,195,114,0,88,46,123,29,29,29,29,29,29,109,109,109,150,116,20,139,0,109,9,234,155,186,21,215,197,42,112,236,112,97,125,201,255,245,120,60,129,64,
0,157,16,101,158,18,12,6,111,186,233,166,133,133,133,215,95,127,189,183,183,87,173,1,170,71,131,221,182,87,94,14,179,27,5,202,128,248,204,173,91,183,34,89,83,128,50,158,15,15,15,255,236,103,63,83,240,
52,243,101,249,128,158,16,182,41,168,35,73,208,67,138,190,74,165,210,45,183,220,194,22,144,14,237,180,101,152,150,38,229,224,62,34,154,208,146,223,242,58,192,139,139,122,203,234,234,234,91,111,189,245,
249,231,159,39,235,78,166,237,135,15,31,222,187,119,47,144,104,212,133,100,40,183,68,54,100,194,85,87,87,247,232,163,143,142,142,142,126,228,35,31,217,179,103,207,23,190,240,133,189,123,247,226,22,120,
189,94,201,97,55,67,167,10,208,128,243,44,23,6,59,190,157,101,250,28,14,135,225,120,80,95,95,47,17,118,75,190,188,229,3,244,27,159,207,215,209,209,49,58,58,218,223,223,159,207,231,165,111,162,203,202,
25,89,78,141,133,133,133,76,38,131,13,175,221,119,73,30,106,87,87,87,87,87,87,121,121,249,228,228,100,36,18,153,153,153,177,27,33,204,163,165,70,191,172,172,12,184,191,157,67,63,74,211,206,26,31,149,27,
98,60,103,179,89,180,74,112,224,32,254,14,160,179,130,155,45,69,128,14,236,44,70,27,224,197,136,209,101,101,101,232,227,87,42,149,170,170,170,164,234,130,223,152,203,229,82,169,148,219,237,110,111,111,
135,238,87,25,198,86,85,85,1,121,167,237,123,56,28,158,157,157,69,73,198,142,15,206,198,111,48,143,99,3,26,12,108,105,140,44,199,24,165,15,216,206,182,183,183,119,116,116,52,55,55,75,119,70,203,34,129,
71,57,18,56,196,107,121,122,204,64,25,166,161,109,67,183,111,174,102,224,29,43,114,174,223,239,7,176,112,227,141,55,238,217,179,231,141,55,222,232,235,235,83,140,102,73,123,144,62,141,210,137,209,76,150,
185,45,101,112,175,171,171,187,230,154,107,36,203,91,102,109,115,115,115,247,221,119,31,164,189,74,52,104,246,241,204,231,243,23,46,92,184,236,178,203,32,220,148,52,15,92,13,110,145,194,225,112,50,153,
156,156,156,236,232,232,96,130,108,105,243,47,225,87,158,78,161,80,64,111,67,216,162,18,231,178,28,253,200,67,89,142,128,47,210,198,141,27,199,198,198,166,166,166,164,107,18,6,226,139,47,190,120,219,109,
183,33,147,82,212,58,51,52,75,197,112,75,75,203,129,3,7,166,166,166,112,178,135,15,31,70,152,254,252,231,63,127,229,149,87,98,61,102,23,46,245,33,177,88,12,173,106,100,111,89,72,168,193,197,92,78,77,31,
171,17,246,67,117,117,117,129,64,0,13,220,148,212,72,90,161,90,2,32,234,187,86,172,88,129,157,31,54,194,173,173,173,227,227,227,231,206,157,163,207,173,201,165,49,69,10,174,119,76,166,36,255,193,50,192,
129,187,194,54,84,225,112,184,172,172,44,26,141,198,98,49,112,105,8,62,200,159,72,162,89,248,105,107,107,51,221,151,28,240,13,85,85,179,108,214,12,93,34,219,36,253,62,153,178,93,173,207,242,123,237,120,
214,38,65,155,62,16,201,100,18,245,61,34,162,176,20,86,68,73,68,231,173,91,183,66,49,192,253,43,27,216,179,185,143,236,149,19,8,4,252,126,63,238,133,37,24,141,99,192,254,140,106,79,140,127,218,90,201,
228,3,185,221,226,226,162,207,231,107,111,111,111,106,106,234,232,232,176,67,237,76,178,188,135,204,106,187,106,161,29,170,128,120,135,222,122,96,131,18,238,148,51,74,138,65,151,150,150,252,126,127,109,
109,45,7,95,48,24,188,225,134,27,118,237,218,117,248,240,225,254,254,126,179,105,13,54,50,172,123,202,50,130,4,236,152,121,81,191,15,180,20,177,131,168,83,32,16,32,183,169,190,190,254,31,255,241,31,7,
7,7,233,102,160,44,119,101,88,247,120,60,231,206,157,91,88,88,72,36,18,109,109,109,44,30,202,12,26,11,175,215,235,221,177,99,135,199,227,25,24,24,200,102,179,235,215,175,7,116,203,72,205,46,83,102,33,
8,185,24,54,34,184,223,209,104,20,173,148,217,106,75,1,163,248,28,98,97,96,176,109,222,188,57,26,141,118,119,119,79,79,79,19,98,198,13,58,122,244,232,222,189,123,107,106,106,80,27,180,12,208,50,165,133,
245,62,122,172,61,245,212,83,44,176,224,48,14,31,62,124,231,157,119,34,76,183,183,183,39,147,73,75,69,217,232,232,40,1,104,82,14,22,22,22,188,94,47,92,56,236,128,17,249,88,179,102,205,53,215,92,99,73,
219,144,3,70,210,156,205,94,4,248,118,121,245,218,219,219,25,49,241,9,205,205,205,45,45,45,131,131,131,195,195,195,148,21,152,44,61,9,143,226,121,50,153,204,231,243,96,218,218,45,117,152,222,10,148,171,
171,171,107,104,104,128,41,79,52,26,77,38,147,152,80,228,152,151,151,151,231,114,57,240,7,96,28,72,152,206,98,83,44,240,13,5,31,153,79,212,66,114,73,231,163,119,27,166,29,120,208,206,29,91,204,247,35,
73,138,199,227,144,188,130,51,71,201,49,10,0,248,153,203,229,210,233,180,199,227,89,181,106,21,188,16,88,62,97,14,199,42,151,105,143,7,16,9,14,77,150,162,65,120,87,81,11,194,142,10,72,165,209,126,140,
40,66,93,93,93,91,91,91,123,123,59,86,205,75,110,88,245,14,143,172,9,231,78,136,140,92,48,39,3,2,139,130,184,235,157,190,133,92,163,168,48,100,171,52,252,201,239,247,179,175,184,92,58,42,42,42,214,175,
95,191,102,205,154,129,129,1,203,114,170,221,205,54,253,52,228,139,181,181,181,31,252,224,7,101,123,102,116,186,67,248,123,246,217,103,191,253,237,111,75,58,42,232,50,38,190,225,118,187,103,102,102,64,
232,206,102,179,171,87,175,174,172,172,84,220,85,183,219,125,244,232,81,151,203,117,197,21,87,212,214,214,226,175,243,243,243,137,68,2,138,126,133,218,43,71,42,72,69,18,137,4,74,172,46,225,210,89,42,149,
210,233,52,120,129,178,131,34,174,27,184,98,80,24,3,54,197,2,94,42,149,82,169,20,138,212,72,55,24,167,242,249,124,71,71,7,124,145,204,150,175,242,167,223,239,95,185,114,37,90,71,31,59,118,236,71,63,250,
145,57,72,202,202,202,198,199,199,31,125,244,209,227,199,143,187,221,238,150,150,22,243,99,143,31,63,14,211,84,252,10,192,14,214,31,224,63,201,13,129,215,235,109,104,104,200,231,243,10,232,88,191,126,
61,151,70,181,125,145,79,136,45,242,58,203,59,197,177,138,71,123,123,123,40,20,178,236,214,88,83,83,131,175,35,175,81,213,57,112,41,48,135,89,229,71,217,0,163,200,78,242,131,191,154,223,136,229,176,166,
166,166,165,165,5,99,6,204,16,238,80,225,141,5,221,19,219,218,154,194,138,242,242,242,108,54,139,182,167,150,122,84,7,125,179,234,216,251,174,32,14,135,194,224,114,98,186,67,85,9,231,53,54,54,54,61,61,
77,198,17,59,117,185,68,3,1,44,114,72,20,66,161,208,234,213,171,211,233,52,107,72,42,175,135,61,180,4,108,229,87,83,135,9,205,132,12,53,32,68,203,238,204,4,21,48,128,185,82,186,221,238,155,110,186,169,
165,165,133,237,172,46,169,128,85,193,250,34,18,184,221,253,67,80,134,111,8,67,24,131,5,75,43,4,49,138,197,34,54,221,18,121,241,249,124,200,157,93,70,19,54,92,229,218,218,218,238,238,238,120,60,142,202,
152,20,121,179,184,193,124,92,58,49,73,121,155,204,70,175,189,246,90,246,46,146,12,71,183,219,61,48,48,240,47,255,242,47,76,156,57,231,113,77,9,27,225,81,44,22,193,208,64,184,60,117,234,212,222,189,123,
153,113,243,195,145,229,161,94,204,251,93,42,149,206,156,57,179,114,229,202,230,230,102,75,168,17,161,57,147,201,0,210,226,241,51,101,198,85,130,121,63,16,15,201,172,64,29,146,86,138,188,32,107,214,172,
25,29,29,93,88,88,8,4,2,61,61,61,160,127,34,4,28,62,124,184,167,167,7,218,10,19,19,231,29,239,236,236,68,34,134,161,255,227,31,255,88,166,207,100,23,16,122,59,118,236,216,145,35,71,26,27,27,111,191,253,
246,171,175,190,90,14,187,11,23,46,200,184,143,255,130,158,16,203,137,207,231,11,6,131,210,76,170,178,178,114,100,100,68,142,96,148,179,204,49,45,233,22,170,133,157,89,100,150,146,45,48,103,1,202,161,
214,111,38,1,237,237,237,205,205,205,168,233,73,29,163,101,200,99,197,41,22,139,97,167,108,153,94,176,28,162,72,190,178,21,50,26,155,54,54,54,98,25,195,62,3,46,134,93,93,93,178,112,205,111,207,102,179,
137,68,98,118,118,182,171,171,11,102,0,76,134,44,211,103,103,148,127,57,178,251,229,87,5,237,176,233,229,151,19,1,64,99,179,142,65,130,213,11,18,18,72,231,230,231,231,193,147,1,172,183,109,219,182,108,
54,75,96,83,54,18,145,121,183,169,27,144,63,145,226,32,77,230,97,192,168,64,117,68,115,189,99,94,198,101,24,31,59,61,61,141,46,180,14,125,127,8,224,168,152,86,86,86,230,49,129,54,12,17,175,215,139,77,
132,236,232,110,230,128,8,13,138,39,199,174,222,156,33,149,149,149,50,58,203,73,142,197,10,163,191,165,165,37,153,76,134,195,225,134,134,134,100,50,9,15,32,41,177,165,188,71,158,131,140,203,124,120,189,
222,109,219,182,21,139,69,121,216,152,27,115,115,115,95,255,250,215,51,153,12,142,147,172,67,249,156,73,183,219,237,30,28,28,148,247,108,100,100,100,199,142,29,72,147,101,140,174,169,169,217,185,115,167,
210,31,226,249,248,248,120,62,159,239,238,238,102,234,68,251,14,152,136,178,15,158,234,108,224,122,167,201,8,174,213,204,204,12,236,150,128,108,96,173,158,157,157,165,2,130,160,16,116,253,111,190,249,
38,174,88,91,91,91,42,149,154,153,153,41,149,74,145,72,228,137,39,158,248,147,63,249,19,215,197,222,67,156,69,236,240,205,100,243,204,153,51,167,79,159,230,250,193,125,183,68,252,49,70,227,241,248,127,
254,231,127,62,246,216,99,183,221,118,219,222,189,123,93,46,23,178,30,25,160,25,229,3,129,192,150,45,91,44,103,114,99,99,227,228,228,164,50,92,86,117,112,7,61,161,37,220,9,35,39,236,69,188,94,111,83,83,
147,36,171,41,178,148,188,227,45,45,45,225,112,120,116,116,20,14,124,118,94,75,114,111,14,126,49,27,125,73,52,150,87,85,245,91,145,19,158,62,253,136,17,53,53,53,8,64,107,214,172,145,221,85,240,105,241,
120,28,168,8,154,167,96,84,196,227,113,4,104,203,208,44,87,5,57,234,46,9,64,91,230,125,42,57,64,232,68,54,32,209,72,14,251,185,185,57,58,243,113,108,131,216,83,91,91,139,37,19,31,53,59,59,11,76,3,101,
64,84,98,49,79,17,79,234,234,234,144,62,214,213,213,221,119,223,125,232,85,13,97,26,75,127,28,168,72,182,48,116,41,103,117,104,150,40,35,33,186,24,131,248,0,222,164,66,189,64,48,205,102,179,48,99,162,
148,97,116,116,20,8,161,165,237,162,10,208,106,184,190,109,55,138,35,6,19,128,242,42,34,179,242,4,228,54,196,237,118,211,30,136,111,240,120,60,96,159,208,201,27,223,36,221,212,148,161,151,28,19,45,45,
45,23,46,92,32,64,17,12,6,83,169,20,32,39,57,106,185,66,72,12,90,93,226,157,59,119,50,58,75,172,102,97,97,225,91,223,250,86,127,127,191,41,174,101,140,6,142,137,184,137,172,68,173,177,71,142,28,249,227,
63,254,99,38,224,152,93,119,223,125,55,188,231,241,34,139,15,176,0,6,37,179,187,187,27,200,111,161,80,0,10,140,43,204,144,199,149,6,252,57,86,66,248,129,240,171,69,137,140,109,203,105,78,68,29,29,252,
58,234,235,235,193,239,134,176,211,231,243,141,140,140,76,76,76,76,77,77,189,247,189,239,69,18,45,5,205,94,175,183,187,187,27,12,33,217,199,250,145,71,30,145,123,23,217,240,66,54,150,230,145,196,227,241,
31,253,232,71,79,62,249,228,251,223,255,126,148,224,36,132,2,179,2,59,252,145,175,180,182,182,34,137,102,128,150,240,168,115,87,83,73,172,70,234,77,245,23,202,146,110,183,27,220,30,14,108,51,64,171,124,
10,101,247,169,169,41,41,139,181,12,208,252,192,100,50,137,178,135,156,123,8,208,76,23,56,50,41,5,162,34,87,105,196,188,94,239,45,183,220,114,217,101,151,161,162,56,62,62,30,139,197,216,79,7,5,121,252,
196,56,201,231,243,166,228,132,137,145,242,228,155,159,159,159,154,154,234,233,233,145,187,94,90,127,168,200,98,138,27,145,195,18,228,193,169,161,130,17,17,238,78,0,0,32,0,73,68,65,84,45,191,145,15,182,
140,225,175,139,139,139,157,157,157,40,178,81,43,11,91,49,252,175,229,221,151,68,35,96,205,112,42,111,108,108,140,199,227,204,144,88,126,231,39,227,10,203,70,166,150,192,14,29,129,128,106,206,205,205,
121,60,158,243,231,207,199,227,241,93,187,118,225,248,37,113,19,106,134,234,234,106,238,116,135,134,134,118,237,218,101,167,69,114,25,173,176,228,77,95,90,90,242,80,14,135,116,82,178,122,113,26,108,6,
168,186,171,192,190,143,76,64,172,111,146,84,199,93,24,248,79,42,225,101,191,34,217,33,24,105,41,141,40,1,36,65,148,73,127,119,147,203,105,110,78,171,170,170,246,236,217,83,110,245,248,205,111,126,243,
171,95,253,74,249,31,201,232,204,24,141,175,155,152,152,48,39,255,200,200,200,212,212,212,138,21,43,36,171,15,125,60,125,62,31,113,79,37,71,196,207,142,142,14,24,8,176,67,37,139,84,184,158,136,20,178,
184,42,189,179,49,88,81,75,100,7,98,6,62,96,80,152,39,46,151,107,227,198,141,251,247,239,151,108,101,210,239,158,126,250,233,143,124,228,35,28,22,128,143,161,183,36,238,137,219,218,223,223,223,219,219,
43,155,224,112,148,99,65,226,18,46,215,209,165,165,165,68,34,241,208,67,15,85,85,85,181,180,180,52,52,52,224,174,49,24,57,228,194,248,4,38,209,248,107,40,20,146,254,89,14,145,26,247,2,113,89,25,22,163,
33,14,62,77,234,233,165,64,198,146,233,69,172,169,173,173,173,177,177,113,102,102,6,73,171,124,167,212,245,242,134,146,129,199,201,143,50,3,231,148,226,137,34,175,228,79,38,1,72,26,22,22,22,230,230,230,
230,230,230,114,185,92,32,16,160,73,14,2,49,128,68,38,179,137,68,162,181,181,149,67,136,201,178,93,21,135,222,17,102,206,107,103,76,42,253,37,144,96,206,207,207,227,139,232,195,103,6,104,110,134,112,10,
104,22,3,186,129,29,139,92,34,227,150,170,104,30,112,40,20,90,179,102,77,42,149,130,149,60,165,240,72,237,153,123,73,176,91,81,227,229,37,226,114,149,74,165,0,51,242,114,205,204,204,180,180,180,112,217,
35,66,5,101,38,8,139,200,217,39,39,39,155,154,154,236,20,164,178,207,181,5,205,142,67,193,178,212,38,213,16,82,231,138,132,159,209,217,237,118,195,252,80,178,106,64,217,97,17,198,116,142,198,224,83,173,
146,234,234,234,168,0,230,9,132,66,161,64,32,192,48,77,167,52,169,4,149,181,251,203,47,191,28,60,101,185,162,160,214,119,255,253,247,43,208,153,89,182,52,175,65,65,230,244,233,211,118,234,131,195,135,
15,175,90,181,138,81,24,219,5,126,136,140,251,236,226,184,180,180,52,62,62,126,230,204,153,234,234,234,198,198,70,122,78,21,10,133,76,38,3,7,22,153,98,240,185,219,237,70,87,20,54,205,131,89,82,46,151,
155,155,155,131,127,57,169,223,152,162,144,116,186,92,174,85,171,86,13,14,14,114,198,246,247,247,227,174,29,61,122,244,218,107,175,197,206,166,166,166,166,187,187,27,251,50,233,19,139,139,191,127,255,
126,233,64,162,120,96,8,232,114,254,203,89,141,206,191,23,46,92,24,27,27,3,114,133,45,167,201,136,176,76,132,145,68,191,189,215,243,120,100,42,170,82,30,228,200,152,228,166,86,77,189,130,77,177,12,175,
200,103,151,105,142,12,166,71,125,125,253,216,216,88,50,153,180,115,149,225,255,34,149,33,75,154,91,64,229,157,68,221,4,174,45,189,249,25,161,234,234,234,206,158,61,59,58,58,218,220,220,12,173,26,182,
219,176,91,64,212,166,39,76,46,151,155,152,152,128,159,129,164,186,74,134,137,156,236,112,15,118,217,55,246,116,118,58,36,14,139,225,1,92,148,139,22,105,8,10,66,113,54,230,118,54,241,80,238,248,128,197,
206,159,63,191,123,247,110,240,20,100,97,28,51,130,41,51,17,15,101,229,172,14,172,188,188,28,64,43,54,241,204,177,240,158,68,34,129,27,33,83,108,76,91,12,45,36,58,30,143,103,104,104,168,177,177,209,212,
142,154,130,82,229,155,246,182,80,133,81,192,132,210,248,4,240,60,113,43,40,143,57,184,3,129,0,47,61,207,185,186,186,26,204,18,75,201,172,84,148,202,213,163,169,169,9,61,132,212,118,195,237,118,135,66,
161,80,40,4,14,13,195,129,172,221,19,103,188,242,202,43,185,120,72,152,248,235,95,255,58,88,207,50,16,75,38,0,95,172,168,168,136,70,163,14,86,124,19,19,19,131,131,131,16,145,35,101,147,255,174,240,19,
136,154,192,100,128,184,118,122,122,26,187,22,210,75,224,60,5,195,13,115,246,82,91,56,63,63,15,30,30,16,70,0,217,64,30,17,244,169,189,70,151,179,205,155,55,79,78,78,226,126,29,56,112,64,2,77,47,188,240,
194,135,63,252,97,232,172,80,22,87,133,105,240,252,94,123,237,53,105,85,168,132,200,172,190,178,223,143,170,7,112,95,15,104,165,181,181,21,190,175,38,51,71,77,87,170,231,169,104,103,27,42,238,169,137,
93,40,93,137,115,150,45,193,13,51,196,88,70,100,203,216,221,217,217,89,91,91,59,54,54,198,150,99,230,123,232,45,5,187,125,240,160,165,144,85,197,101,152,34,108,216,176,33,28,14,55,54,54,174,93,187,246,
47,255,242,47,11,133,66,52,26,5,2,16,143,199,209,192,169,166,166,102,229,202,149,56,119,224,164,146,133,13,213,201,133,11,23,2,129,64,85,85,21,82,28,160,4,118,70,160,118,98,54,21,202,149,75,140,244,136,
199,181,149,197,73,7,39,32,249,87,203,241,224,28,166,89,42,164,10,188,178,178,114,231,206,157,216,241,35,248,226,46,35,254,240,178,115,171,138,243,101,193,137,177,18,59,84,0,223,82,163,167,90,68,197,98,
49,108,26,152,211,224,235,240,138,172,135,247,247,247,239,216,177,195,101,88,241,89,102,208,214,61,9,233,197,229,178,105,22,0,181,24,70,112,46,151,227,216,66,9,94,70,73,110,247,96,130,172,228,61,42,141,
151,7,135,11,77,60,68,117,195,149,108,16,175,215,139,114,45,22,43,172,210,28,241,123,247,238,5,206,160,172,145,190,255,253,239,15,12,12,40,53,10,34,41,46,171,196,55,92,46,23,106,131,14,143,151,94,122,
105,235,214,173,50,166,203,148,156,47,102,50,25,72,158,8,47,178,226,7,93,50,107,0,32,81,98,163,64,168,129,127,165,26,2,31,75,240,26,165,218,133,133,133,250,250,122,238,43,121,157,43,42,42,46,191,252,242,
125,251,246,157,62,125,26,116,61,217,84,9,41,173,100,158,41,231,194,167,158,122,74,34,224,188,212,52,133,224,246,8,233,3,161,85,138,113,101,116,91,92,92,28,31,31,71,152,6,221,197,50,70,199,98,49,152,71,
203,171,221,220,220,140,24,205,205,202,37,145,104,203,88,128,251,98,246,90,38,184,228,28,157,213,175,94,175,119,205,154,53,217,108,118,114,114,18,206,136,150,1,154,179,12,67,139,107,225,202,149,43,91,
90,90,86,174,92,217,211,211,211,212,212,4,139,37,222,157,104,52,122,242,228,201,82,169,4,50,123,123,123,59,63,13,219,211,177,177,49,120,56,160,108,32,247,10,168,170,229,114,57,244,253,153,153,153,137,
68,34,8,211,129,64,64,222,71,26,37,18,159,116,80,6,226,21,245,206,119,69,179,51,203,140,206,44,64,231,7,77,62,75,165,210,202,149,43,41,60,33,224,64,237,18,227,38,17,9,165,174,64,134,148,74,165,136,99,
176,200,105,26,130,99,161,141,70,163,225,112,216,101,213,1,67,46,249,233,116,58,18,137,48,163,114,217,59,71,66,28,112,17,205,142,67,7,21,109,75,139,41,217,205,8,242,51,132,96,80,163,164,69,8,39,57,6,129,
34,213,185,140,70,229,68,24,121,196,149,149,149,62,159,15,93,157,28,154,101,32,101,152,157,157,69,69,66,26,172,236,222,189,91,214,94,16,145,15,30,60,248,216,99,143,153,208,179,178,228,103,230,123,238,
220,57,220,84,59,239,30,92,247,161,161,161,117,235,214,33,166,171,12,26,120,28,56,12,216,86,75,158,60,27,12,23,10,133,198,198,70,82,53,88,29,205,102,179,144,51,241,68,208,185,18,64,4,60,184,229,44,66,
27,214,249,249,121,244,52,145,49,26,38,44,167,78,157,146,158,21,187,119,239,14,6,131,253,253,253,219,183,111,151,189,239,36,42,154,76,38,143,28,57,34,63,13,95,202,154,1,171,154,200,89,100,145,211,164,
151,201,48,61,54,54,54,57,57,217,210,210,210,210,210,194,141,20,184,219,196,157,105,9,134,189,60,56,203,14,145,247,146,212,14,22,162,57,3,229,220,35,218,230,178,111,29,98,103,183,95,93,93,221,211,211,
19,14,135,225,9,101,167,185,128,201,206,170,85,171,62,254,241,143,195,151,70,237,115,113,97,33,98,70,187,188,165,165,165,64,32,144,76,38,87,174,92,137,20,10,215,132,112,109,62,159,31,27,27,131,194,0,188,
93,208,36,112,46,88,209,137,147,228,114,57,88,242,7,131,65,152,95,203,61,181,37,133,195,146,96,176,124,83,36,231,246,87,204,171,126,79,218,53,230,44,92,51,39,38,38,184,161,225,13,5,240,205,186,55,83,93,
160,181,116,28,84,194,105,117,204,146,242,129,63,197,227,113,216,10,42,176,197,44,204,142,141,141,41,179,95,229,56,164,252,212,254,55,131,198,117,41,20,10,14,174,208,202,187,11,97,162,190,190,158,35,70,
218,216,195,40,4,120,150,3,174,45,141,143,213,207,154,154,26,46,3,150,130,49,217,203,174,170,170,10,86,47,72,223,118,239,222,141,157,190,36,35,71,163,209,111,126,243,155,178,100,39,159,48,125,198,163,
162,162,34,149,74,197,98,49,242,213,237,250,153,86,85,85,193,192,91,126,32,62,100,113,113,17,204,89,228,197,204,73,101,205,132,172,140,169,169,41,100,178,82,3,137,41,132,141,66,177,88,196,180,71,49,0,
87,152,92,67,172,231,164,94,36,147,73,216,105,202,154,65,87,87,23,78,164,178,178,242,154,107,174,217,180,105,83,161,80,64,225,62,157,78,3,161,146,90,121,28,240,11,47,188,32,241,98,89,98,150,101,25,90,
62,73,177,181,165,5,179,26,181,200,166,91,90,90,80,115,135,31,41,68,158,136,203,204,38,88,226,123,87,123,103,243,21,176,229,84,171,80,214,9,45,235,13,206,125,158,84,131,227,45,91,182,32,253,135,93,159,
207,231,67,229,22,117,48,252,203,117,215,93,183,105,211,38,186,160,201,62,59,145,72,36,149,74,73,123,185,165,165,165,182,182,182,225,225,225,158,158,30,12,96,180,46,85,107,64,62,159,159,156,156,172,174,
174,70,23,40,144,95,241,33,217,108,182,174,174,78,149,4,115,185,28,190,206,231,243,65,116,6,211,96,59,11,17,37,160,144,14,104,118,109,121,151,217,150,76,182,6,253,29,180,48,234,82,132,195,225,112,56,60,
63,63,15,60,13,210,121,5,132,18,163,31,25,25,233,239,239,103,183,101,231,251,107,201,59,194,205,82,29,120,205,37,10,125,17,55,108,216,96,9,226,43,22,135,90,5,255,55,121,145,130,116,147,51,4,16,7,152,75,
40,20,66,186,173,178,102,60,193,159,72,207,80,21,60,203,169,37,69,192,75,75,75,245,245,245,146,95,37,187,144,152,6,96,72,186,145,174,150,74,165,29,59,118,48,58,243,168,254,233,159,254,137,134,27,202,62,
84,245,182,80,224,134,221,193,227,21,56,34,161,203,153,228,234,161,218,139,208,172,172,217,149,129,31,153,127,165,82,9,142,104,178,81,38,250,72,129,131,9,95,80,110,154,240,102,153,251,200,124,4,56,181,
207,231,3,30,7,9,242,21,87,92,17,137,68,174,185,230,26,196,110,200,65,203,203,203,103,102,102,252,126,63,118,223,178,47,112,50,153,68,127,25,121,193,85,191,53,26,25,114,140,74,214,157,196,121,77,79,6,
210,189,199,198,198,18,137,68,32,16,0,195,79,182,17,225,53,111,105,105,193,93,94,102,80,182,123,177,187,187,27,54,138,150,84,1,7,83,42,59,197,135,217,182,24,230,77,230,104,231,86,12,13,22,36,255,58,22,
139,65,159,101,25,242,2,129,64,177,88,92,179,102,13,106,128,150,34,64,74,144,167,166,166,188,94,47,197,26,136,197,176,90,53,223,191,176,176,128,141,218,216,216,152,195,78,209,117,169,174,5,118,84,28,213,
57,193,228,153,73,65,131,233,109,111,119,0,150,126,88,242,215,170,170,170,158,158,30,232,179,166,166,166,162,209,40,77,120,112,178,83,83,83,217,108,182,84,42,193,113,197,65,173,110,74,72,100,178,2,57,
56,111,138,93,99,76,212,114,82,169,20,222,41,125,83,101,55,47,51,173,121,155,7,205,189,146,66,57,228,151,161,60,5,251,30,88,67,20,10,5,166,150,76,87,177,188,179,228,104,178,244,29,170,195,36,3,32,45,165,
187,174,203,198,60,151,98,54,202,100,203,203,203,127,250,211,159,150,151,151,239,218,181,139,135,244,131,31,252,96,96,96,192,84,12,146,194,172,208,137,145,145,17,72,182,76,171,85,57,50,118,237,218,181,
113,227,70,150,119,240,9,8,163,36,21,72,4,156,121,7,121,242,228,23,162,175,26,205,248,101,16,199,16,7,57,189,161,161,33,147,201,192,151,43,18,137,48,223,7,225,196,92,228,193,241,168,170,170,26,31,31,95,
90,90,218,189,123,55,45,37,37,227,133,58,23,98,115,56,96,51,58,51,254,154,101,125,169,123,4,221,216,114,211,42,1,95,172,61,32,186,202,40,105,57,2,221,110,55,184,249,14,169,202,37,21,198,96,142,163,158,
105,87,119,226,86,210,52,140,118,14,88,150,78,173,150,63,65,215,113,185,92,153,76,6,165,99,83,185,32,63,193,239,247,175,91,183,174,182,182,150,218,37,115,85,144,43,107,38,147,137,70,163,128,10,81,219,
159,157,157,5,187,67,117,242,230,43,133,66,1,46,163,42,70,56,168,16,157,155,67,154,206,80,230,68,86,62,24,206,166,131,191,155,196,60,24,12,250,124,190,238,238,238,177,177,177,179,103,207,246,245,245,33,
46,179,165,175,131,205,147,37,32,99,134,175,104,52,10,175,5,174,112,118,9,196,216,216,216,234,213,171,85,16,147,173,112,232,6,133,194,239,69,25,180,101,128,150,225,53,159,207,163,43,1,75,130,126,191,63,
159,207,99,64,51,58,179,35,181,98,200,75,133,165,186,79,178,169,15,171,159,193,96,16,165,106,69,126,180,108,5,36,113,131,92,46,135,174,175,120,28,58,116,232,201,39,159,180,108,91,101,233,44,154,203,229,
198,198,198,76,79,0,151,232,49,236,114,185,106,106,106,174,191,254,122,144,228,112,111,220,110,55,50,92,182,106,69,66,202,0,45,149,147,10,76,104,111,111,231,206,145,137,167,210,16,35,54,33,59,203,102,
179,72,138,137,111,32,238,200,26,61,161,183,115,231,206,33,244,203,116,70,69,129,137,137,137,174,174,46,220,53,118,111,57,118,236,152,20,158,50,131,86,117,93,105,58,131,131,65,115,107,179,21,67,69,69,
5,92,119,161,132,82,122,37,41,163,48,205,175,131,193,160,20,166,46,63,46,75,122,89,87,87,151,220,124,152,68,96,248,150,88,38,83,150,61,185,93,151,106,31,46,247,136,252,53,153,76,142,142,142,38,18,9,101,
192,102,23,160,27,27,27,215,175,95,143,93,57,26,197,154,90,71,9,20,160,237,25,112,63,44,129,40,21,170,160,44,131,17,236,217,20,161,216,50,95,150,169,134,169,17,55,151,49,196,104,51,79,196,120,112,6,193,
44,153,36,150,109,240,236,34,41,9,30,157,157,157,93,93,93,151,93,118,217,201,147,39,223,124,243,77,170,123,92,86,141,232,20,182,99,102,235,114,254,38,18,9,150,187,237,230,23,126,29,24,24,232,233,233,49,
59,105,112,119,197,40,161,139,132,56,20,135,118,112,115,115,115,62,159,175,171,171,139,180,48,60,2,129,0,122,229,2,26,147,205,247,148,192,204,117,169,246,219,84,124,178,221,70,36,18,161,158,93,165,33,
42,166,203,127,220,179,103,207,77,55,221,132,195,139,199,227,223,254,246,183,85,104,182,36,111,32,158,122,60,158,254,254,126,105,179,107,206,4,4,202,219,111,191,29,110,41,108,10,135,126,5,172,179,33,118,
51,64,51,144,153,63,219,218,218,112,221,136,108,48,152,18,65,150,178,73,236,121,125,62,95,62,159,71,243,121,80,122,129,240,32,215,102,147,180,104,52,138,21,212,178,147,55,207,43,145,72,132,195,97,192,
208,200,253,251,250,250,16,142,149,247,30,183,162,4,16,37,6,199,22,21,185,92,78,114,43,113,34,91,182,108,145,133,7,135,162,147,154,240,168,16,74,30,52,39,158,252,119,66,183,50,205,39,35,181,181,181,21,
95,13,253,130,74,36,241,9,32,207,170,162,183,107,25,125,182,150,147,205,49,249,56,125,250,52,150,195,75,214,51,137,188,111,216,176,1,144,69,54,155,69,22,101,215,38,28,59,39,6,208,98,177,152,74,165,102,
103,103,235,234,234,88,207,87,110,115,220,182,154,139,165,114,45,127,87,156,13,30,60,91,172,202,41,79,74,178,28,84,151,196,88,236,162,179,186,35,60,114,86,155,185,212,221,112,195,13,239,125,239,123,251,
251,251,143,28,57,114,230,204,25,19,11,54,215,36,133,236,169,235,128,182,97,170,117,183,37,230,62,56,56,40,203,51,204,120,164,207,162,217,22,249,127,153,200,48,132,84,75,1,2,119,67,67,67,75,75,139,178,
186,103,91,63,28,31,28,212,120,244,82,244,101,217,33,209,132,146,101,192,173,171,171,59,113,226,68,101,101,37,125,164,228,204,180,116,2,91,92,92,108,111,111,255,212,167,62,197,40,124,255,253,247,147,245,
236,16,157,249,202,232,232,40,192,13,53,1,76,187,175,129,129,129,13,27,54,72,2,181,52,144,66,128,150,54,126,82,253,33,131,47,124,141,41,178,50,177,20,202,201,56,97,248,54,108,96,81,21,64,36,194,219,16,
172,49,81,71,71,71,81,170,226,82,199,91,172,70,79,36,18,105,107,107,227,224,128,53,29,219,143,241,154,147,240,39,53,226,244,232,160,220,81,186,139,241,68,82,169,84,48,24,52,19,19,103,251,30,48,130,224,
163,132,243,50,153,164,106,91,134,177,39,161,67,143,199,67,41,151,76,135,101,20,198,96,86,214,69,206,81,216,57,194,58,100,211,50,96,57,84,165,240,43,54,28,68,117,11,133,2,67,173,185,170,177,53,162,42,
219,142,143,143,55,53,53,249,253,126,73,213,144,138,15,220,26,203,211,100,137,72,118,80,50,19,127,133,158,201,90,58,214,12,25,133,37,90,101,105,133,97,7,179,56,63,80,21,84,32,184,185,44,173,89,179,102,
237,218,181,169,84,234,135,63,252,225,241,227,199,129,254,155,233,188,124,69,81,251,229,244,201,100,50,80,33,57,11,29,145,68,163,21,17,231,14,111,150,212,170,144,192,90,44,22,61,242,4,160,52,87,247,6,
244,38,105,253,195,73,200,97,205,172,68,234,8,100,142,163,42,149,114,51,37,85,15,92,67,16,154,193,66,3,163,206,14,217,96,2,94,87,87,247,197,47,126,145,135,247,232,163,143,158,58,117,74,65,207,166,132,
132,185,243,252,252,252,208,208,144,137,59,187,172,250,203,28,62,124,120,116,116,244,163,31,253,40,172,197,164,59,18,227,190,138,206,210,98,141,196,76,88,220,73,215,11,252,73,229,212,106,239,134,215,113,
121,189,94,111,115,115,51,58,115,3,95,3,42,93,40,20,6,6,6,138,197,98,46,151,147,46,201,40,12,42,24,122,105,105,41,149,74,53,52,52,0,74,62,125,250,180,108,93,38,205,25,84,241,29,111,83,124,123,36,209,116,
209,2,153,18,86,9,136,128,150,222,61,14,65,48,155,205,226,30,89,134,99,169,40,163,80,80,77,12,88,8,88,46,189,174,139,91,201,33,154,44,63,47,182,140,200,150,193,151,191,214,215,215,183,182,182,142,141,
141,93,18,52,231,122,35,41,52,0,27,229,60,149,122,57,116,134,84,206,153,176,69,109,108,108,204,102,179,96,149,72,99,38,216,2,47,103,79,128,165,5,232,132,76,129,149,81,187,194,28,224,78,5,207,91,154,124,
201,224,117,201,244,217,18,5,86,45,62,76,207,47,216,1,169,78,134,242,32,131,193,224,134,13,27,234,235,235,83,169,212,192,192,0,88,31,230,21,48,249,118,170,213,14,200,118,118,1,90,126,245,192,192,64,123,
123,187,108,48,98,2,244,197,98,17,249,56,14,198,35,199,40,96,104,126,65,117,117,117,103,103,167,236,54,34,27,247,169,154,131,188,130,82,51,106,9,229,168,189,182,29,217,14,10,203,92,46,7,122,175,93,91,
32,236,91,255,234,175,254,10,209,199,227,241,244,246,246,62,252,240,195,166,251,190,153,74,51,131,62,121,242,164,130,155,85,69,69,133,236,72,36,242,195,31,254,240,253,239,127,255,181,215,94,43,59,204,
82,162,162,120,117,170,107,81,89,89,25,204,237,144,76,169,36,130,91,120,70,37,226,27,202,113,28,154,218,242,242,242,218,218,90,200,44,97,134,0,174,2,135,62,212,225,40,18,86,85,85,193,12,19,26,51,138,217,
146,201,100,83,83,211,194,194,194,217,179,103,205,24,103,86,104,161,110,32,179,130,55,14,19,82,134,102,254,123,117,117,53,53,168,206,62,229,242,130,163,157,21,229,130,170,209,181,34,125,179,185,12,207,
171,188,188,28,158,9,148,186,73,94,141,220,191,131,98,172,40,158,191,51,166,225,240,206,237,219,183,175,93,187,182,175,175,111,120,120,216,89,185,199,217,4,136,28,118,63,196,148,205,154,30,74,190,38,188,
62,63,63,143,92,7,44,105,154,123,224,193,14,44,42,184,192,144,211,100,182,152,125,44,157,5,220,72,131,242,249,60,6,45,27,145,56,84,134,205,18,130,101,141,206,210,53,201,196,64,212,86,73,70,109,16,168,
54,109,218,180,105,211,166,241,241,241,233,233,233,153,153,25,197,174,83,57,150,186,77,115,115,115,48,198,177,140,111,242,231,224,224,224,222,189,123,101,201,93,241,32,80,237,163,242,171,162,162,226,162,
124,89,146,78,90,90,90,234,235,235,229,62,93,58,34,74,114,130,51,108,175,104,37,38,46,161,166,55,161,186,134,134,6,100,25,8,4,249,124,158,125,206,77,54,241,135,63,252,97,244,121,131,160,227,158,123,238,
81,45,81,28,66,115,69,69,5,250,78,154,85,65,203,182,50,128,204,106,106,106,124,62,223,193,131,7,39,39,39,63,246,177,143,129,232,42,155,127,51,58,171,149,12,175,180,183,183,67,153,201,170,160,180,44,0,
226,65,187,47,194,193,74,248,179,184,184,72,232,31,255,2,43,113,244,202,164,80,10,15,224,33,184,29,160,141,163,73,7,130,53,220,44,23,23,23,225,34,237,186,216,173,201,156,186,212,98,113,59,166,50,104,149,
135,98,143,2,187,53,202,40,156,247,176,24,111,16,91,54,55,55,99,23,165,160,64,197,120,43,43,43,67,107,18,153,214,133,66,33,41,49,128,121,133,153,59,227,17,10,133,70,71,71,127,207,12,218,249,191,16,242,
208,121,103,253,250,245,103,206,156,25,26,26,178,251,71,44,39,172,203,17,230,2,187,75,161,4,88,155,205,14,162,120,66,252,154,228,200,68,34,193,1,96,126,53,221,211,176,192,171,38,71,150,133,53,135,181,
22,156,2,12,114,217,136,207,33,58,91,114,171,21,16,236,140,141,216,249,119,75,41,138,156,161,237,237,237,109,109,109,185,92,110,114,114,242,194,133,11,216,172,168,133,80,229,163,136,164,116,65,81,147,
69,85,74,22,22,22,166,167,167,235,235,235,21,199,78,98,134,18,162,121,27,131,230,65,195,5,173,178,178,114,195,134,13,84,46,200,76,196,164,55,88,90,125,82,230,100,73,12,52,147,101,25,154,65,50,7,109,80,
202,171,176,82,33,76,83,121,140,127,188,233,166,155,246,238,221,203,112,124,239,189,247,194,120,80,57,213,153,138,18,236,212,138,197,34,60,78,205,170,189,137,117,64,3,2,100,28,17,121,98,98,226,59,223,
249,206,135,62,244,161,205,155,55,51,49,225,198,159,190,201,132,50,128,176,215,215,215,75,183,73,215,59,6,149,4,206,240,58,185,134,18,65,226,71,97,115,42,61,49,240,167,72,36,210,221,221,13,15,38,234,242,
97,159,68,152,152,141,42,224,57,0,9,117,177,88,60,126,252,184,84,69,91,38,44,12,199,216,66,170,194,0,128,23,21,112,145,170,195,137,209,231,243,33,161,179,3,94,165,208,182,181,181,21,141,123,232,170,40,
231,137,124,197,117,113,199,38,66,49,104,104,107,199,121,80,55,26,108,182,255,211,12,90,50,85,188,94,239,174,93,187,186,187,187,79,157,58,21,137,68,44,3,52,217,77,210,253,103,110,110,142,150,235,156,225,
244,142,80,97,136,61,31,218,218,218,100,11,249,201,201,73,108,107,110,188,241,70,53,91,165,244,12,247,14,217,155,101,213,84,213,117,45,141,119,176,19,34,255,146,199,160,242,0,7,173,135,75,152,165,56,139,
209,29,136,210,102,89,152,85,116,41,223,95,185,114,165,199,227,129,80,139,51,154,202,6,185,75,163,200,136,188,53,103,24,186,175,175,111,247,238,221,56,119,185,41,148,215,228,162,6,237,102,84,218,185,115,
103,32,16,64,222,174,92,123,36,6,45,41,220,14,165,85,229,112,102,214,3,17,197,166,167,167,71,71,71,103,102,102,168,112,197,215,41,254,60,246,119,68,36,23,23,23,119,237,218,117,235,173,183,74,40,99,207,
158,61,125,125,125,150,25,180,244,205,96,152,62,115,230,140,20,212,152,66,18,210,81,107,106,106,164,217,133,108,155,242,203,95,254,114,124,124,252,230,155,111,70,222,65,186,130,235,226,6,228,144,213,116,
116,116,40,155,112,230,209,76,195,185,182,19,151,39,93,143,97,218,239,247,211,26,156,254,103,67,67,67,56,89,244,119,160,243,11,59,182,144,183,46,39,27,52,141,103,207,158,77,36,18,210,63,94,117,168,147,
195,136,87,128,91,69,201,228,11,133,66,210,233,13,90,30,208,129,240,95,21,21,21,118,77,102,9,188,6,131,65,216,128,225,76,157,169,20,168,116,169,18,40,219,247,73,130,135,229,210,43,77,190,160,21,190,100,
20,222,184,113,163,76,241,32,99,35,193,209,239,247,195,91,131,119,185,167,167,7,121,150,210,43,133,195,225,27,110,184,97,122,122,250,196,137,19,211,211,211,242,82,87,87,87,179,27,122,69,69,5,101,111,40,
27,96,143,203,172,22,6,147,50,46,75,41,25,188,79,129,150,130,192,203,12,78,249,63,96,202,152,183,3,102,3,151,44,217,201,246,37,50,32,96,186,113,27,71,23,173,82,169,100,169,50,87,98,104,7,69,159,90,57,
156,165,76,242,168,188,94,175,18,81,243,13,231,206,157,163,205,161,236,42,192,192,229,245,122,49,7,253,126,127,169,84,146,62,4,230,166,147,207,7,6,6,96,156,36,3,177,92,135,100,207,191,178,178,50,143,114,
167,110,104,104,64,250,83,83,83,3,62,172,234,158,39,33,33,19,241,145,228,62,151,149,201,55,67,246,226,226,34,132,243,147,147,147,164,30,43,244,77,118,243,148,39,140,100,208,227,241,180,181,181,125,248,
195,31,150,209,185,188,188,252,131,31,252,224,206,157,59,255,237,223,254,13,132,104,229,203,204,48,141,214,12,145,72,36,145,72,216,77,87,156,111,77,77,77,125,125,61,193,86,89,26,150,100,234,195,135,15,
87,86,86,238,221,187,151,241,87,114,159,249,129,88,156,165,202,206,236,253,40,147,38,153,118,145,156,135,55,212,213,213,177,170,142,55,36,18,9,232,119,165,11,96,67,67,3,58,212,0,217,112,189,227,16,107,
118,78,154,152,152,192,200,195,189,0,243,82,30,158,188,203,178,91,57,150,7,122,239,34,93,146,1,26,129,41,159,207,211,253,11,183,6,133,77,53,61,144,8,151,149,149,173,89,179,6,200,6,124,29,157,133,0,128,
215,21,59,10,51,159,124,65,121,35,128,194,203,219,13,63,166,158,158,30,28,57,226,41,67,176,223,239,239,233,233,81,144,160,101,182,72,58,129,185,15,51,165,164,124,52,53,53,221,120,227,141,83,83,83,71,143,
30,157,156,156,132,26,64,82,104,128,141,200,44,39,30,143,135,195,97,217,151,68,237,113,213,96,206,102,179,176,236,65,186,141,245,12,18,21,137,29,169,46,210,68,60,144,42,18,187,83,153,153,93,62,43,223,
70,167,114,146,240,48,42,96,105,173,184,213,150,92,14,75,169,167,210,251,57,208,34,85,160,167,170,83,157,2,90,32,218,57,131,227,57,168,41,104,68,7,215,223,214,214,86,110,112,85,241,137,135,148,78,167,
147,201,36,224,41,201,113,226,249,34,67,253,223,22,40,114,49,169,174,174,134,35,23,110,48,252,16,82,169,148,68,162,153,143,72,43,6,133,22,73,170,172,170,7,206,205,205,245,247,247,143,140,140,140,143,143,
99,247,109,153,122,155,124,64,243,81,42,149,176,67,81,194,147,242,242,242,213,171,87,63,240,192,3,223,249,206,119,14,31,62,44,219,134,50,52,211,17,237,236,217,179,184,175,106,64,227,191,176,92,89,82,44,
185,135,224,151,54,55,55,123,60,158,125,251,246,173,90,181,234,61,239,121,143,165,41,96,119,119,183,207,231,83,33,91,246,27,230,229,37,0,34,157,225,24,247,145,14,99,13,103,236,46,20,10,131,131,131,248,
119,53,199,144,93,54,52,52,196,98,49,121,204,114,109,67,203,90,85,14,197,69,150,221,82,120,72,108,89,36,167,52,131,96,115,115,115,36,18,129,220,20,126,217,139,139,139,184,89,18,180,9,133,66,64,174,184,
78,192,37,21,41,2,236,132,176,237,80,249,136,169,106,131,212,80,142,25,28,185,220,230,163,184,242,167,127,250,167,202,89,148,63,165,229,216,114,168,205,102,158,168,228,12,118,59,51,203,135,203,229,106,
110,110,94,181,106,213,133,11,23,22,23,23,27,27,27,41,249,1,131,66,17,105,209,102,30,148,124,148,254,204,97,44,159,128,74,1,183,25,86,242,225,58,41,89,164,102,88,100,140,246,249,124,48,21,178,36,74,154,
172,39,105,9,146,76,38,177,145,146,132,72,149,71,91,26,70,155,142,131,166,112,70,225,212,118,54,32,102,12,49,33,14,151,203,53,52,52,164,232,207,150,163,5,255,8,8,40,18,137,52,53,53,201,171,109,146,244,
49,133,135,135,135,215,173,91,39,77,31,149,242,75,30,201,219,166,218,244,138,197,94,152,197,253,138,138,10,244,9,148,147,83,225,200,114,128,82,86,207,145,132,111,29,26,26,234,237,237,29,30,30,158,153,
153,49,119,64,106,244,75,164,220,225,81,81,81,49,52,52,116,207,61,247,220,118,219,109,55,223,124,179,68,156,1,206,126,245,171,95,125,230,153,103,126,244,163,31,241,79,21,21,21,240,105,100,54,29,14,135,
167,167,167,213,176,174,172,172,108,110,110,174,169,169,241,120,60,216,134,171,52,86,238,151,93,239,152,105,65,114,82,89,89,217,215,215,119,250,244,233,143,127,252,227,184,140,172,80,193,229,93,241,234,
84,164,102,97,16,98,119,70,67,28,21,76,54,176,177,128,109,5,254,5,185,213,192,192,0,74,192,132,14,148,169,121,60,30,199,27,76,184,9,109,98,16,14,226,241,56,229,118,202,154,142,104,198,236,236,44,54,49,
184,176,107,215,174,85,130,67,56,183,225,175,184,224,220,22,40,104,27,148,74,244,180,69,92,230,192,157,155,155,3,193,0,255,110,6,101,249,34,51,65,133,98,115,98,43,101,138,37,153,18,222,111,203,49,133,
144,189,142,236,2,147,140,209,178,247,144,218,162,169,30,202,251,247,239,71,185,15,123,103,185,6,171,12,122,105,105,41,153,76,162,241,174,244,140,53,109,99,25,169,1,140,144,62,143,186,168,92,89,157,109,
137,152,71,75,187,78,231,70,7,0,187,167,167,167,33,64,99,131,62,238,252,200,154,7,133,31,65,220,117,113,51,104,151,85,143,96,151,189,141,218,50,99,52,173,208,100,140,198,92,0,70,172,118,60,170,157,133,
76,88,83,169,148,220,91,91,110,242,144,12,141,141,141,173,95,191,30,103,45,1,67,46,186,23,29,97,85,85,21,112,58,30,68,58,157,150,126,202,104,134,148,78,167,41,53,84,8,178,137,111,224,249,248,248,248,249,
243,231,7,6,6,250,250,250,44,217,139,102,85,129,114,154,229,68,103,100,112,115,115,115,143,60,242,200,235,175,191,254,215,127,253,215,171,87,175,150,136,51,224,142,93,187,118,221,115,207,61,201,100,146,
189,233,164,220,102,251,246,237,251,246,237,99,196,12,4,2,77,77,77,236,169,78,48,142,167,44,173,132,37,151,174,174,174,46,28,14,83,233,55,53,53,117,255,253,247,223,114,203,45,240,45,67,248,232,234,234,
146,165,66,153,221,72,202,179,20,124,179,244,135,234,4,90,106,193,136,14,248,6,7,202,244,244,116,44,22,147,58,2,174,37,18,35,6,250,100,198,104,164,69,152,180,116,160,230,93,150,17,7,9,47,119,130,24,223,
60,90,41,74,2,159,164,88,44,82,166,8,91,40,80,57,213,93,246,249,124,24,120,64,213,231,231,231,51,153,76,111,111,239,53,215,92,131,173,137,221,160,231,174,92,105,172,0,119,216,249,50,218,137,69,85,137,
198,146,216,43,199,170,249,225,16,115,130,126,46,107,27,178,238,47,89,4,42,197,62,122,244,40,50,6,184,83,2,42,97,6,13,148,153,243,14,215,19,74,125,89,254,53,235,249,252,10,164,177,178,198,197,12,218,153,
134,193,217,90,81,81,17,8,4,16,13,212,170,105,58,98,230,243,249,225,225,97,240,101,65,135,165,52,131,246,129,128,26,112,53,74,165,18,10,21,217,108,246,228,201,147,157,157,157,237,237,237,210,55,66,158,
190,249,80,242,11,59,81,31,31,108,255,42,31,112,133,86,180,57,203,58,182,44,210,44,44,44,204,204,204,192,125,212,161,90,232,114,185,226,241,248,236,236,44,103,162,90,87,164,41,121,89,89,153,27,230,156,
242,214,250,124,62,168,203,37,76,9,127,103,217,203,150,179,87,150,236,242,249,124,111,111,239,107,175,189,246,196,19,79,188,252,242,203,231,207,159,143,70,163,102,246,33,143,91,98,160,203,140,206,156,
141,124,115,58,157,126,241,197,23,103,103,103,55,110,220,136,241,71,29,74,83,83,211,157,119,222,9,188,155,202,20,224,27,48,148,241,251,253,224,190,116,118,118,182,182,182,114,113,2,64,198,72,170,16,76,
133,26,175,94,189,154,247,6,58,145,82,169,212,215,215,55,57,57,185,106,213,42,159,207,183,106,213,42,201,60,85,5,43,69,149,81,184,63,32,2,190,2,112,3,186,18,140,200,82,169,4,246,133,60,36,245,28,61,244,
148,83,54,23,42,66,31,210,18,94,209,117,192,164,150,189,37,249,19,232,27,111,40,107,167,201,100,114,118,118,118,197,138,21,52,246,171,168,168,104,108,108,148,254,174,220,220,192,230,24,105,20,133,221,
249,124,126,237,218,181,108,255,168,218,96,243,248,81,88,231,159,40,22,85,185,143,37,2,160,126,46,51,131,94,92,92,132,178,145,51,162,178,178,18,132,69,170,120,152,182,91,230,119,220,163,72,14,236,195,
15,63,140,166,118,77,77,77,144,158,179,217,46,228,72,32,246,224,127,185,0,36,18,9,7,32,103,213,0,0,32,0,73,68,65,84,176,9,135,134,134,210,233,116,125,125,189,93,164,198,24,96,107,240,234,234,234,182,182,
54,53,13,47,41,185,86,117,87,187,22,45,209,104,116,104,104,8,172,74,60,160,231,164,9,37,167,48,86,122,188,7,133,178,241,241,113,52,56,238,235,235,139,199,227,240,64,71,208,148,40,135,121,204,92,57,236,
76,214,228,35,153,76,190,249,230,155,138,179,123,225,194,133,84,42,37,185,128,14,202,85,159,207,71,176,8,218,96,37,202,51,55,61,139,139,139,62,159,143,5,6,246,204,197,233,103,50,153,77,155,54,145,56,224,
49,201,191,128,161,205,209,28,10,133,188,94,111,52,26,101,42,206,164,114,112,112,240,236,217,179,195,195,195,232,81,164,20,50,106,215,163,224,11,210,77,236,108,151,205,69,82,10,216,229,232,255,245,175,
127,125,240,224,193,47,125,233,75,116,179,171,169,169,9,135,195,110,183,251,158,123,238,249,239,255,254,239,159,252,228,39,128,65,185,221,112,187,221,171,86,173,106,108,108,4,107,197,220,33,178,179,142,
162,61,200,36,218,239,247,211,93,1,139,106,93,93,29,234,171,163,163,163,223,251,222,247,190,240,133,47,64,210,45,241,13,9,54,17,251,83,62,74,160,199,73,46,7,66,191,199,227,1,88,4,187,241,135,31,126,184,
191,191,31,183,121,124,124,28,157,27,191,241,141,111,200,241,4,117,128,57,92,96,172,3,75,13,178,173,37,105,4,181,98,28,6,178,30,229,101,97,66,222,116,143,43,22,139,200,40,99,177,216,216,216,216,186,117,
235,230,231,231,21,11,83,142,120,152,95,3,41,98,186,145,76,38,77,50,150,201,250,80,22,16,202,109,3,176,155,73,61,50,17,100,83,146,96,231,208,196,91,9,238,160,60,72,244,79,144,154,49,203,42,180,218,65,
31,56,112,0,255,5,140,142,118,198,178,26,79,168,68,114,102,144,116,123,189,222,209,209,81,143,199,147,207,231,105,223,161,242,104,236,129,2,129,0,213,116,174,75,57,241,91,230,209,20,145,91,26,42,1,105,
77,36,18,114,129,65,201,132,55,72,158,84,101,101,165,196,18,93,46,23,117,125,96,62,156,63,127,126,105,105,105,197,138,21,61,61,61,109,109,109,170,91,158,37,176,224,208,71,81,246,186,53,195,14,90,238,145,
195,102,87,147,228,126,130,47,198,227,241,21,43,86,152,166,251,38,132,59,58,58,10,103,5,203,101,131,95,90,44,22,61,38,24,10,255,67,21,170,92,239,88,68,122,189,222,233,233,233,92,46,151,76,38,167,166,166,
34,145,200,241,227,199,85,119,34,75,22,36,211,10,147,65,105,169,86,114,248,52,147,187,206,243,159,158,158,254,252,231,63,127,213,85,87,253,235,191,254,107,71,71,7,209,155,242,242,242,59,239,188,115,247,
238,221,223,252,230,55,135,135,135,85,43,238,134,134,6,232,241,209,50,89,101,181,44,88,91,246,19,43,47,47,95,183,110,29,219,199,224,157,200,164,96,111,82,81,81,241,192,3,15,220,116,211,77,119,220,113,
135,157,133,130,132,53,89,14,98,247,88,215,197,221,233,177,90,176,207,236,241,227,199,255,231,127,254,7,38,12,120,15,229,91,60,224,108,54,43,29,51,212,3,90,106,146,49,216,73,0,76,184,183,37,167,30,15,
227,154,89,220,80,67,153,16,7,208,146,19,39,78,16,221,70,209,85,170,78,56,22,193,157,32,12,197,55,96,109,80,61,174,76,104,79,85,186,212,165,86,130,67,75,86,44,34,139,154,93,118,136,7,116,61,40,164,203,
61,22,223,80,85,85,197,130,129,217,117,72,229,64,48,23,126,245,213,87,145,149,135,195,97,204,11,169,201,146,133,89,121,43,33,227,234,235,235,131,245,51,10,39,167,79,159,94,187,118,109,48,24,148,73,52,
134,40,152,24,184,32,150,18,149,229,132,105,110,230,76,160,163,80,40,140,142,142,162,232,135,154,22,6,109,93,93,29,75,83,240,95,84,112,1,99,37,28,213,9,134,240,195,207,159,63,127,238,220,185,197,197,197,
181,107,215,118,119,119,131,197,104,198,7,19,55,176,68,165,25,160,229,250,20,139,197,136,218,201,62,244,118,201,129,4,223,80,179,149,125,15,100,88,147,255,62,53,53,133,224,160,106,69,10,189,41,149,74,
58,131,246,120,60,213,213,213,169,84,42,28,14,171,232,140,75,63,60,60,60,54,54,214,215,215,7,33,137,165,199,57,89,180,220,58,97,193,183,51,204,91,126,116,150,238,22,118,186,79,216,117,199,227,113,180,
122,146,115,117,229,202,149,247,222,123,239,3,15,60,112,240,224,65,148,176,8,134,208,154,25,120,63,178,105,66,192,18,81,81,247,187,178,178,18,205,226,164,156,52,26,141,194,72,12,159,191,184,184,248,248,
227,143,31,61,122,244,179,159,253,44,46,172,44,5,168,108,90,133,24,121,25,37,54,141,217,59,55,55,247,232,163,143,90,202,106,48,7,112,185,96,182,103,185,225,194,14,148,141,219,165,228,68,2,211,188,209,
224,99,72,58,129,148,27,240,44,98,177,216,208,208,16,221,104,241,98,52,26,93,177,98,5,152,33,242,166,231,114,185,76,38,67,72,13,41,54,71,42,96,119,50,222,236,220,42,204,44,85,226,134,114,24,88,118,241,
176,228,30,152,211,146,33,24,248,152,233,104,204,217,14,32,85,210,251,84,113,88,106,116,23,23,23,95,125,245,85,152,125,131,152,44,253,29,77,157,173,12,220,224,102,60,243,204,51,153,76,230,227,31,255,56,
114,14,192,29,173,173,173,160,22,240,56,113,29,208,63,133,172,149,75,146,190,157,209,15,229,70,132,182,94,234,61,88,155,225,22,130,91,70,38,34,51,0,54,157,66,53,91,233,21,185,124,46,45,45,245,246,246,
158,61,123,182,162,162,2,198,252,43,87,174,180,163,21,59,199,232,174,174,46,229,227,140,244,84,142,1,38,73,102,95,74,108,149,228,85,74,36,18,76,62,28,88,161,165,82,9,221,217,21,204,37,3,52,38,184,135,
188,5,236,43,145,140,48,64,227,173,145,72,100,116,116,116,106,106,10,57,14,238,55,18,4,5,9,41,173,20,29,42,192,92,118,253,126,15,85,174,181,116,26,188,250,234,171,63,253,233,79,183,180,180,0,141,41,20,
10,93,93,93,146,187,227,241,120,62,251,217,207,238,223,191,255,145,71,30,1,3,12,176,99,125,125,125,34,145,64,60,69,15,11,182,143,148,53,101,115,87,14,174,174,100,173,32,202,212,212,212,100,179,89,172,
16,200,125,38,39,39,191,240,133,47,252,205,223,252,205,229,151,95,46,119,184,36,56,187,68,171,11,153,14,168,198,187,50,26,62,242,200,35,8,130,166,241,30,101,126,32,74,202,132,90,6,232,104,52,42,163,179,
165,28,223,36,237,96,131,207,84,142,44,139,98,177,56,61,61,125,238,220,57,233,218,195,123,55,63,63,15,39,107,208,230,112,118,241,120,124,110,110,142,237,211,192,79,151,27,11,196,95,104,92,77,51,4,83,77,
227,178,234,244,10,136,67,73,117,237,88,7,178,250,106,89,250,39,254,227,224,109,15,204,1,240,145,37,217,78,178,203,11,133,194,27,111,188,193,221,36,174,164,10,205,196,43,149,219,65,54,155,61,124,248,240,
228,228,100,89,89,217,171,175,190,122,235,173,183,18,217,135,169,122,75,75,139,42,123,100,179,217,218,218,218,112,56,172,132,151,203,244,18,113,144,168,184,108,122,29,208,78,136,214,34,230,191,23,10,5,
236,197,251,250,250,176,229,82,158,16,174,139,29,248,138,197,226,153,51,103,78,159,62,93,89,89,185,126,253,250,141,27,55,162,80,47,123,137,57,199,104,137,172,98,47,146,74,165,44,73,132,50,122,202,62,150,
234,211,16,57,249,69,104,69,102,41,170,42,22,139,123,246,236,97,45,65,10,68,126,246,179,159,209,48,221,131,205,184,66,51,16,155,50,153,76,42,149,138,68,34,201,100,82,213,28,92,239,120,168,155,6,231,10,
187,112,110,165,243,59,4,104,75,222,140,219,237,222,180,105,211,93,119,221,181,101,203,22,18,60,96,89,112,238,220,185,230,230,230,166,166,38,233,52,127,245,213,87,247,244,244,60,244,208,67,83,83,83,212,
22,134,66,161,249,249,121,38,113,62,159,111,98,98,130,235,188,228,111,200,219,15,241,130,218,4,161,172,138,69,78,134,54,183,219,253,173,111,125,107,207,158,61,127,241,23,127,65,47,14,201,148,144,73,22,
217,29,146,35,33,251,6,156,60,121,242,236,217,179,118,182,168,140,200,96,167,0,15,81,214,84,168,204,48,64,91,234,239,205,18,135,132,80,144,208,97,91,141,221,21,12,125,204,45,48,209,82,246,63,45,22,139,
137,68,2,28,21,158,26,187,41,242,34,135,195,97,86,252,73,63,144,225,210,14,40,52,113,54,7,112,195,65,119,46,163,188,196,82,148,28,212,60,128,96,48,136,50,169,37,166,193,101,163,188,188,252,197,23,95,68,
186,13,52,32,22,139,129,145,105,58,158,203,204,26,215,112,124,124,252,205,55,223,196,151,246,246,246,174,94,189,122,251,246,237,44,192,230,243,121,52,126,148,85,214,165,165,165,134,134,6,154,100,58,83,
235,150,249,80,21,126,75,164,200,65,210,2,106,22,184,179,18,8,165,180,66,218,237,202,168,13,94,233,145,35,71,142,28,57,2,108,125,251,246,237,96,79,57,60,36,103,148,119,147,209,217,236,229,100,233,199,
36,251,96,17,169,203,102,179,76,171,229,53,81,79,8,178,155,105,144,108,157,227,225,77,146,113,33,157,78,31,57,114,132,99,8,228,24,197,214,68,130,128,11,234,250,191,127,88,222,84,28,67,103,103,231,173,
183,222,122,249,229,151,211,54,136,153,59,120,181,126,191,31,136,170,220,206,116,116,116,124,238,115,159,123,252,241,199,143,29,59,134,116,163,182,182,54,30,143,115,28,167,211,233,202,202,74,20,91,1,56,
170,229,97,113,113,177,171,171,11,148,97,51,179,11,133,66,85,85,85,51,51,51,178,91,32,228,97,111,190,249,230,221,119,223,253,153,207,124,102,203,150,45,146,154,110,39,51,147,21,33,30,222,220,220,220,79,
127,250,83,211,83,130,33,0,124,118,236,114,32,1,96,10,198,236,44,153,76,18,155,150,187,45,231,159,146,196,10,167,152,183,222,122,107,108,108,140,30,79,60,17,73,165,194,69,128,203,10,2,58,170,127,136,185,
52,247,160,152,158,115,3,184,42,230,18,181,39,46,163,235,232,37,153,63,150,213,63,135,166,92,50,107,83,29,146,28,24,71,10,140,246,251,253,217,108,86,145,148,165,139,0,170,62,7,14,28,32,238,9,231,131,238,
238,110,110,203,120,107,152,65,243,118,196,98,177,231,159,127,94,102,199,207,63,255,124,103,103,103,71,71,7,225,59,20,190,106,106,106,0,107,184,221,238,21,43,86,216,149,118,151,131,105,216,93,97,246,76,
48,83,40,101,114,235,176,48,192,150,93,13,72,59,175,8,245,60,145,72,156,57,115,230,107,95,251,26,52,198,31,250,208,135,192,81,145,111,86,40,37,51,104,8,113,205,55,216,29,39,245,83,42,232,167,211,105,80,
36,93,162,137,132,25,160,103,103,103,99,177,88,40,20,50,115,160,139,86,38,226,167,138,149,165,126,165,176,77,198,190,242,242,242,217,217,89,20,61,255,127,62,144,103,161,255,211,214,173,91,63,250,209,143,
162,231,177,228,96,85,87,87,55,55,55,175,88,177,2,32,131,156,81,178,61,202,150,45,91,26,27,27,209,163,150,134,65,30,143,7,253,122,49,75,65,107,99,55,47,158,190,219,237,222,185,115,39,66,134,202,112,23,
23,23,65,254,133,112,211,228,60,149,74,165,103,159,125,214,237,118,163,207,136,201,216,53,139,180,12,121,56,157,31,252,224,7,240,93,179,203,115,183,111,223,222,220,220,204,254,26,188,125,21,21,21,48,41,
197,128,150,127,146,55,221,249,65,151,225,241,241,241,68,34,129,245,219,178,211,179,57,178,43,42,42,32,50,38,79,14,172,71,128,75,220,158,83,2,186,117,235,86,80,24,165,231,159,226,59,58,104,243,76,153,
181,212,22,170,235,44,159,243,186,225,202,88,138,185,45,99,153,252,222,138,138,138,68,34,1,125,144,89,53,194,189,251,237,111,127,59,53,53,133,220,25,143,217,217,89,4,104,68,100,172,169,224,65,147,146,
133,159,143,63,254,56,146,0,57,246,38,38,38,246,238,221,75,59,48,60,193,248,175,170,170,106,107,107,3,160,79,235,146,223,33,137,182,219,181,72,199,118,151,141,71,182,201,134,146,5,198,67,135,14,129,82,
101,25,130,47,153,58,204,207,207,247,247,247,103,179,217,67,135,14,61,248,224,131,207,63,255,252,252,252,124,99,99,35,217,247,234,216,78,156,56,1,141,9,168,247,239,42,16,81,24,169,68,131,80,11,163,210,
110,10,47,229,243,134,134,6,89,90,192,24,104,107,107,99,84,113,183,183,183,155,162,35,197,165,69,27,80,233,10,205,119,22,10,133,255,159,1,26,94,198,13,13,13,126,191,191,165,165,229,189,239,125,239,142,
29,59,144,166,177,73,107,48,24,92,181,106,213,154,53,107,100,31,54,187,178,6,56,188,219,182,109,67,175,88,159,207,7,244,153,240,52,235,42,116,58,103,58,92,95,95,191,110,221,58,105,202,65,102,30,252,139,
225,223,102,74,188,8,173,246,246,246,30,60,120,112,199,142,29,202,20,66,61,151,52,9,132,167,23,94,120,225,133,23,94,80,37,126,245,235,245,215,95,31,14,135,51,153,140,101,132,5,60,197,136,47,125,154,76,
21,184,26,24,216,131,79,78,78,162,168,69,96,81,241,139,237,114,213,84,42,85,91,91,139,94,7,180,100,115,187,221,224,65,75,187,65,252,132,123,151,50,27,48,163,170,93,200,176,196,58,76,67,78,69,221,177,12,
244,242,67,136,125,217,5,44,105,123,32,103,190,74,232,18,137,196,227,143,63,142,137,45,35,178,50,146,197,139,24,78,124,28,58,116,232,228,201,147,114,189,193,19,216,130,111,218,180,137,49,154,107,94,75,
75,11,9,251,224,120,216,1,208,118,115,199,82,96,45,243,104,213,85,67,50,23,101,239,14,203,79,30,29,29,29,29,29,197,158,67,110,29,236,192,55,115,243,151,78,167,7,6,6,120,41,98,177,216,254,253,251,31,122,
232,161,23,94,120,1,139,147,74,123,143,28,57,18,141,70,129,111,16,90,113,0,70,148,186,74,37,37,184,95,216,5,226,57,29,166,76,10,96,169,84,106,111,111,87,172,173,133,133,133,250,250,122,166,149,30,19,23,
83,76,126,188,88,85,85,69,36,212,108,29,180,124,30,229,239,246,128,92,152,173,178,49,105,183,109,219,6,130,4,206,42,155,205,54,53,53,109,223,190,189,161,161,193,217,45,197,236,50,89,83,83,243,233,79,127,
122,223,190,125,39,78,156,168,173,173,157,158,158,102,116,70,138,193,248,8,93,242,220,220,28,248,228,100,215,73,244,57,28,14,67,109,129,54,169,208,197,114,227,175,14,105,108,108,236,139,95,252,226,39,
63,249,201,235,175,191,158,246,208,10,238,144,37,196,242,242,242,233,233,233,167,158,122,202,140,44,234,142,64,47,35,107,131,50,119,64,82,6,17,54,138,156,200,209,84,109,74,250,34,161,30,53,51,51,147,74,
165,232,1,45,43,129,68,42,36,57,65,53,245,193,135,71,34,17,197,92,6,40,100,217,121,7,118,251,138,149,104,25,62,44,89,140,138,108,126,201,93,188,100,46,57,140,28,217,160,192,153,240,80,95,95,15,102,170,
165,53,199,139,47,190,136,184,32,5,11,165,82,41,18,137,4,2,1,233,163,230,122,167,167,9,175,225,43,175,188,226,178,233,79,120,224,192,129,245,235,215,35,125,161,188,182,189,189,189,166,166,6,219,29,162,
31,151,36,102,152,0,14,24,62,202,3,79,238,144,200,17,228,37,149,189,129,236,210,243,178,178,178,177,177,49,100,193,38,31,212,196,58,20,0,130,231,116,16,35,103,20,127,58,127,254,252,87,191,250,213,165,
165,165,235,174,187,238,250,235,175,191,246,218,107,145,83,83,13,203,72,234,208,142,64,253,74,231,47,21,211,209,41,20,178,32,135,207,73,167,211,104,151,165,150,31,152,20,97,30,121,26,26,26,16,230,37,31,
72,237,100,129,24,144,32,44,89,74,153,76,198,82,8,251,135,122,112,253,103,97,189,171,171,235,61,239,121,15,198,46,147,20,196,232,43,174,184,2,85,2,115,138,218,185,205,202,65,115,237,181,215,118,117,117,
189,252,242,203,77,77,77,0,163,89,208,87,217,22,242,145,246,246,118,137,186,146,42,222,216,216,24,137,68,160,84,132,46,22,46,145,106,217,231,147,249,249,249,255,248,143,255,120,227,141,55,238,190,251,
110,80,145,84,181,80,201,243,31,124,240,65,147,185,97,198,104,88,59,154,158,179,44,55,147,157,130,195,32,21,154,187,105,30,33,52,129,83,83,83,152,57,184,38,146,55,45,251,180,242,95,208,199,150,241,154,
3,12,189,127,36,63,137,138,44,203,50,172,217,18,9,184,147,235,82,126,237,234,13,36,114,56,108,216,21,48,226,16,118,45,91,33,91,142,52,112,132,146,201,36,175,18,215,128,153,153,25,212,247,200,138,225,35,
30,143,119,118,118,74,75,94,166,90,80,117,254,230,55,191,113,57,250,47,255,252,231,63,223,188,121,51,52,150,240,138,97,83,112,213,125,244,93,85,233,185,109,119,120,160,224,65,155,11,222,122,137,236,155,
55,11,228,51,20,174,85,228,53,133,151,118,241,26,155,6,149,107,203,158,203,251,247,239,223,183,111,223,210,210,210,181,215,94,123,237,181,215,98,107,194,37,193,164,33,216,89,152,242,92,204,55,195,143,
158,119,205,65,180,50,49,49,209,222,222,78,0,150,26,64,102,126,158,245,235,215,115,95,12,192,20,129,24,235,9,177,69,160,25,170,204,34,185,165,206,152,250,239,156,56,51,128,162,9,214,142,29,59,128,201,
240,28,88,244,92,88,88,56,113,226,196,85,87,93,181,156,254,102,106,106,241,91,186,187,187,63,242,145,143,60,251,236,179,175,190,250,170,52,125,86,90,131,76,38,179,117,235,86,164,243,18,220,172,168,168,
192,225,177,220,95,93,93,93,91,91,11,243,10,14,80,203,136,9,150,244,103,62,243,153,205,155,55,91,202,204,240,129,207,62,251,44,156,106,21,96,205,37,132,49,136,137,146,25,245,144,47,75,146,144,140,2,24,
223,120,79,54,155,141,197,98,177,88,12,188,122,121,199,149,3,31,194,10,236,156,114,185,156,37,123,135,255,59,59,59,59,53,53,213,217,217,201,188,27,120,148,201,101,148,170,63,53,196,45,203,131,206,205,
167,157,73,23,206,228,78,245,6,150,40,100,202,98,154,112,226,209,212,212,52,60,60,204,150,196,196,106,158,126,250,105,126,142,212,34,161,235,2,237,235,36,76,137,159,207,63,255,60,96,19,203,117,154,13,
46,190,247,189,239,125,249,203,95,118,187,221,210,97,198,117,113,231,198,119,165,79,201,229,114,210,93,200,225,186,97,185,165,121,136,137,191,155,176,254,232,232,40,194,186,9,146,88,102,205,74,102,73,
78,20,76,46,25,148,21,229,131,255,248,234,171,175,190,242,202,43,193,96,80,154,134,47,39,52,203,30,246,38,118,65,190,160,234,97,111,185,44,77,77,77,129,13,45,151,19,134,214,165,165,37,143,234,247,3,175,
31,149,173,32,165,98,149,86,26,131,217,17,66,127,103,170,134,116,219,33,77,216,237,118,175,91,183,110,237,218,181,224,183,3,6,229,57,224,57,154,233,129,203,177,76,209,170,82,22,224,117,191,223,15,201,
31,10,235,230,28,64,115,44,112,227,177,127,100,104,35,231,154,110,33,32,192,248,124,62,120,7,203,236,201,220,187,197,98,177,175,124,229,43,119,222,121,231,93,119,221,37,189,249,25,121,99,177,216,175,126,
245,43,135,250,152,60,224,137,137,137,206,206,78,229,252,128,95,177,239,145,210,100,140,78,148,233,192,238,0,61,11,54,8,216,49,72,4,70,6,83,188,159,85,29,194,26,230,157,149,39,126,254,252,121,48,20,177,
63,51,201,27,124,242,224,131,15,2,232,144,125,87,253,126,255,170,85,171,184,225,184,100,252,53,33,142,75,214,187,236,36,45,18,226,32,21,146,56,190,101,140,174,168,168,168,173,173,29,31,31,151,71,50,58,
58,10,91,81,84,240,24,163,249,72,36,18,44,55,81,28,84,42,149,78,156,56,1,234,148,3,242,142,39,111,189,245,214,83,79,61,245,201,79,126,18,185,179,100,164,72,7,162,229,60,208,35,141,203,191,41,182,54,47,
20,238,14,61,160,85,160,48,143,92,226,27,150,89,179,131,187,5,159,228,243,249,186,186,186,120,60,110,137,92,203,84,154,222,9,156,104,224,249,73,21,171,249,132,103,13,124,195,50,64,131,1,205,219,234,208,
64,32,145,72,192,19,66,30,36,218,229,188,205,146,82,163,214,146,31,131,44,12,212,40,89,172,116,189,227,90,253,123,70,103,53,206,252,126,127,107,107,235,224,224,32,238,107,75,75,203,250,245,235,125,62,
31,2,49,146,53,122,71,32,124,96,64,207,205,205,245,245,245,109,221,186,85,45,239,150,40,135,105,24,34,95,185,227,142,59,178,217,236,153,51,103,32,201,231,95,243,249,124,161,80,88,191,126,61,141,64,9,85,
135,195,97,68,55,25,11,0,242,214,214,214,162,16,33,87,114,147,122,140,235,252,240,195,15,191,246,218,107,95,255,250,215,209,94,143,97,177,188,188,252,191,254,235,191,16,232,77,82,173,89,46,155,158,158,
150,37,102,185,129,66,143,43,179,162,237,245,122,67,161,16,58,176,192,125,148,229,50,44,207,200,202,201,223,228,14,142,230,182,72,31,44,243,41,101,127,216,223,223,127,235,173,183,178,137,59,121,226,174,
139,221,77,121,240,177,88,140,67,52,155,205,6,2,129,104,52,122,229,149,87,154,64,170,101,179,112,200,175,160,87,100,151,122,36,146,206,97,221,129,246,43,157,61,228,228,151,49,154,35,170,179,179,115,100,
100,68,34,87,47,191,252,50,124,145,164,241,191,12,208,177,88,140,184,147,132,239,95,127,253,117,151,149,179,135,203,202,90,228,248,241,227,127,246,103,127,102,182,18,117,144,168,152,211,115,118,118,150,
30,182,82,140,38,85,72,150,226,67,0,44,80,75,72,136,201,204,160,139,197,34,122,144,98,187,105,137,62,171,44,216,242,57,55,112,44,6,18,132,84,57,181,114,7,67,190,79,54,4,138,252,46,43,131,105,34,54,38,
124,193,247,176,113,140,37,29,83,201,190,27,27,27,101,64,152,158,158,230,108,242,168,162,159,242,224,151,128,64,117,117,53,237,187,112,185,147,201,36,188,147,126,79,206,156,252,46,120,49,87,85,85,117,
116,116,140,141,141,181,180,180,172,92,185,146,229,38,201,36,33,140,192,12,186,188,188,252,216,177,99,8,208,203,169,91,202,156,75,94,50,76,188,91,110,185,165,84,42,161,119,36,189,2,160,121,131,157,171,
12,31,129,64,0,238,242,56,78,218,42,98,21,1,97,156,142,251,174,139,123,153,203,92,0,184,205,212,212,212,63,252,195,63,124,240,131,31,188,249,230,155,57,3,159,126,250,233,183,222,122,203,36,30,216,53,61,
192,32,51,247,137,0,178,44,211,132,133,133,5,128,128,62,159,175,187,187,123,98,98,2,197,9,245,93,24,124,178,18,40,147,71,75,201,168,217,100,126,112,112,16,19,24,229,95,5,59,42,85,148,188,59,208,16,97,
23,117,246,236,217,109,219,182,89,74,76,205,3,72,167,211,216,120,98,117,151,157,65,72,212,33,101,5,102,126,133,66,1,139,25,1,1,92,85,222,74,78,84,187,24,205,35,15,4,2,161,80,104,114,114,18,20,26,248,139,
169,224,226,122,167,87,47,38,246,204,204,12,166,46,183,104,197,98,17,27,59,187,242,131,10,151,221,221,221,187,118,237,250,205,111,126,243,137,79,124,130,136,28,105,60,203,201,156,224,175,38,149,35,210,
158,194,12,241,38,114,8,155,127,80,134,236,230,35,203,131,18,226,80,73,180,229,166,211,140,221,152,125,216,249,193,34,92,54,219,53,99,180,229,145,51,23,97,192,49,179,105,25,45,45,3,180,108,176,235,32,
251,142,199,227,146,13,141,69,26,249,83,161,80,112,95,125,245,213,46,43,11,115,179,220,76,13,37,110,243,224,224,224,129,3,7,126,79,1,183,50,131,46,47,47,111,107,107,131,21,67,40,20,10,133,66,185,92,14,
74,25,181,169,151,186,3,201,17,44,20,10,208,176,186,28,251,98,216,177,175,228,213,247,251,253,209,104,148,253,146,193,97,112,185,92,157,157,157,221,221,221,50,130,84,86,86,174,88,177,2,135,4,52,0,182,
182,68,105,113,106,52,166,144,2,36,203,61,20,54,182,199,143,31,31,28,28,188,236,178,203,170,170,170,166,167,167,239,187,239,62,164,243,166,192,204,124,44,44,44,108,216,176,161,161,161,161,186,186,154,
4,68,4,101,158,20,111,235,252,252,60,94,164,59,12,192,235,96,48,152,207,231,149,70,73,38,200,150,27,127,203,10,146,101,35,165,173,91,183,54,55,55,135,66,33,20,118,164,125,168,114,59,226,159,224,211,200,
54,102,249,124,30,157,171,236,236,226,228,157,77,38,147,88,12,228,26,143,162,63,214,120,137,48,178,175,77,36,18,153,155,155,203,229,114,179,179,179,48,241,73,167,211,176,214,82,251,51,203,18,147,188,80,
62,159,239,194,133,11,248,228,231,159,127,62,18,137,40,113,32,17,103,160,207,133,66,1,135,199,156,186,183,183,151,105,184,235,98,87,107,51,76,183,183,183,239,220,185,19,10,251,84,42,181,97,195,6,73,157,
68,163,41,229,194,170,110,25,254,81,82,17,248,132,189,55,237,240,13,121,48,168,243,75,110,134,73,150,232,235,235,75,167,211,197,98,49,147,201,216,5,98,51,46,171,216,189,184,184,8,95,23,56,5,33,29,86,74,
105,182,99,230,140,112,160,105,74,75,3,166,86,178,16,234,44,159,161,235,167,195,186,146,207,231,193,212,224,139,53,53,53,151,93,118,217,219,34,12,185,206,155,75,132,58,86,40,211,10,133,194,193,131,7,65,
54,92,190,123,198,114,10,119,173,173,173,94,175,151,140,99,80,53,98,177,152,108,32,128,203,202,172,89,186,220,2,238,56,123,246,236,250,245,235,157,77,35,21,238,97,166,105,120,126,229,149,87,142,142,142,
214,215,215,87,87,87,15,12,12,224,157,91,183,110,149,173,145,151,150,150,160,93,150,246,219,16,139,83,26,128,238,24,224,219,201,42,45,31,44,120,50,64,35,44,30,61,122,244,174,187,238,138,70,163,107,215,
174,197,246,69,77,78,75,147,7,156,5,134,123,60,30,239,232,232,144,228,13,202,214,23,22,22,102,103,103,227,241,56,152,252,24,112,114,177,172,168,168,232,238,238,158,158,158,166,3,173,12,181,10,143,102,
137,223,206,165,193,180,49,234,239,239,223,177,99,7,105,70,170,201,161,169,170,130,103,180,60,113,100,226,181,181,181,118,170,101,126,87,177,88,132,145,158,12,28,53,53,53,94,175,23,159,137,197,79,86,8,
0,74,98,92,73,195,35,238,24,36,137,72,230,89,248,82,105,112,136,23,27,27,27,195,225,240,204,204,204,208,208,208,248,248,120,121,121,185,185,157,151,173,44,51,153,204,248,248,56,134,16,156,225,198,198,
198,88,57,183,164,96,243,121,32,16,88,191,126,61,29,45,250,250,250,222,124,243,205,61,123,246,72,25,14,208,97,218,27,32,140,242,188,50,153,12,14,207,228,42,184,172,108,236,21,233,69,77,61,220,101,6,95,
19,224,158,152,152,128,35,182,76,36,213,183,155,206,21,106,11,2,33,143,44,44,97,29,98,123,101,214,99,89,209,181,188,122,38,228,139,131,145,200,149,67,247,119,89,66,179,60,95,249,10,24,59,53,53,53,10,224,
70,25,223,35,169,205,118,50,77,222,6,164,114,175,188,242,10,103,172,195,158,229,146,210,123,245,182,166,166,166,96,48,136,0,205,117,190,189,189,125,120,120,24,180,89,75,142,182,130,161,23,22,22,208,240,
176,173,173,77,109,144,101,151,26,203,115,84,98,51,160,225,59,119,238,60,114,228,8,218,130,204,204,204,52,252,63,206,190,60,184,173,243,186,30,36,192,5,4,64,0,4,23,16,92,69,82,27,37,75,148,100,217,150,
173,56,118,226,37,222,38,78,106,59,211,166,78,236,100,154,196,105,211,164,147,102,239,56,201,100,210,73,218,102,154,105,227,52,233,164,227,184,137,183,137,237,102,18,47,173,45,219,178,150,200,218,23,138,
162,36,82,220,23,112,1,64,98,33,64,144,32,127,127,156,248,248,250,126,15,144,242,195,31,26,8,36,129,135,247,190,119,191,123,207,61,247,156,64,128,22,65,184,192,181,181,181,144,143,144,29,3,101,198,138,
142,129,199,227,193,2,149,218,2,102,235,195,233,116,178,245,116,246,236,217,190,190,190,213,213,213,129,129,129,27,110,184,65,54,69,243,141,180,240,173,208,60,200,229,114,169,84,10,151,31,218,117,48,94,
0,208,140,27,184,166,166,6,90,189,42,164,226,9,16,39,40,14,115,140,94,70,103,249,117,50,153,76,225,0,45,203,151,75,151,46,145,222,39,83,33,213,26,34,20,6,166,135,106,135,66,128,162,179,179,147,188,61,
51,173,147,132,101,158,180,138,138,10,26,78,66,134,5,162,25,210,210,12,229,17,40,204,56,42,198,113,130,33,54,161,196,162,104,227,234,30,129,114,203,196,196,196,91,111,189,5,81,111,19,216,145,18,84,184,
118,144,150,78,167,211,19,19,19,52,12,179,148,22,145,3,20,219,182,109,67,226,194,23,223,124,243,77,136,41,75,30,45,75,22,25,134,162,209,232,145,35,71,202,202,202,188,94,175,199,227,241,251,253,166,48,
133,170,250,11,200,51,240,30,132,105,164,52,189,227,3,110,197,136,176,220,158,1,151,153,46,7,249,72,208,182,119,148,231,176,78,100,206,11,179,30,148,230,128,47,120,252,82,160,252,74,226,24,215,70,97,112,
217,100,241,214,214,214,194,175,0,219,39,180,82,161,248,218,217,217,9,57,138,178,178,178,250,250,122,57,173,237,144,28,94,121,25,204,85,190,178,178,210,219,219,251,198,27,111,176,84,55,213,247,11,204,
236,217,242,203,138,194,210,180,182,182,22,35,200,52,52,193,234,233,232,232,232,239,239,159,153,153,169,175,175,151,194,249,236,143,75,24,26,155,228,185,115,231,26,26,26,36,79,35,159,253,140,202,166,205,
70,226,166,77,155,142,30,61,138,252,174,182,182,118,247,238,221,252,34,112,68,134,199,26,129,45,201,146,161,46,48,181,119,65,94,148,77,48,5,77,160,138,47,42,42,26,30,30,62,113,226,4,220,84,87,86,86,102,
102,102,70,70,70,112,119,217,222,145,213,54,33,72,150,201,96,113,208,45,205,231,243,217,237,246,249,249,249,116,58,29,143,199,209,240,225,252,30,32,176,2,147,99,72,81,199,199,199,1,200,42,173,84,158,64,
20,230,5,186,106,4,88,233,108,143,113,30,147,83,165,242,23,32,78,170,243,38,117,205,7,7,7,161,222,133,65,118,60,145,9,157,92,57,104,168,144,173,68,149,90,52,129,213,167,72,233,125,238,76,102,225,101,153,
76,73,189,58,234,91,62,243,204,51,115,115,115,88,171,208,216,148,132,66,90,119,35,118,39,18,9,36,83,82,192,94,30,140,217,21,172,168,168,216,188,121,179,233,110,151,74,165,94,120,225,133,207,124,230,51,
178,30,53,29,130,14,31,62,124,228,200,17,192,238,76,171,129,55,122,60,30,184,118,72,72,65,77,9,218,12,219,64,121,108,14,135,163,186,186,26,254,132,242,10,98,171,182,189,163,178,77,97,44,222,80,42,143,
41,156,65,43,117,80,28,88,58,157,206,102,179,110,183,27,184,135,237,79,49,216,179,12,89,141,141,141,180,193,108,105,105,193,216,14,84,168,176,165,173,172,172,92,123,237,181,48,213,180,204,125,21,170,41,
59,124,44,40,29,106,196,192,100,52,147,189,240,250,235,175,119,119,119,171,94,240,149,112,72,37,10,169,148,3,137,156,180,183,183,203,153,99,102,208,248,172,182,182,182,75,151,46,205,207,207,99,74,85,210,
236,0,216,41,167,234,158,158,30,12,179,152,16,126,97,249,46,115,232,160,164,164,228,246,219,111,223,179,103,79,36,18,9,4,2,59,118,236,136,199,227,131,131,131,56,128,182,182,54,146,97,165,76,165,4,154,
17,14,176,171,185,221,110,164,105,74,29,95,118,69,230,231,231,143,28,57,130,46,135,20,30,234,238,238,134,38,31,81,29,73,218,67,197,42,3,71,38,147,1,19,104,117,117,117,102,102,198,237,118,159,59,119,14,
225,128,204,19,135,195,81,83,83,35,111,167,124,155,168,211,233,236,232,232,232,237,237,149,244,91,181,245,230,211,251,102,128,150,50,26,184,157,198,198,198,234,234,234,176,208,243,5,104,108,132,133,251,
7,153,76,6,113,7,28,21,96,232,152,114,130,142,46,153,112,40,4,45,133,234,225,86,5,144,157,223,206,229,114,129,64,66,186,33,67,42,167,76,45,29,160,57,197,174,240,52,40,98,35,254,210,136,143,126,158,4,193,
136,168,122,60,158,169,169,41,74,58,40,86,56,81,62,146,231,214,175,95,79,146,149,188,169,237,118,251,248,248,248,235,175,191,126,239,189,247,50,125,70,62,142,255,198,227,241,151,94,122,9,206,112,228,210,
225,48,32,111,41,227,53,116,190,104,119,103,222,101,170,108,149,49,186,166,166,6,218,35,120,61,157,78,83,92,30,21,152,162,45,228,171,171,136,84,240,95,186,200,91,14,25,225,124,50,226,1,22,87,61,48,179,
51,132,79,116,185,92,59,119,238,116,58,157,125,125,125,185,92,238,51,159,249,204,214,173,91,9,146,40,241,110,18,156,104,211,85,0,156,224,127,9,138,190,231,170,221,124,243,205,38,133,150,117,43,66,228,
244,244,244,11,47,188,48,48,48,160,54,219,124,243,248,249,166,179,164,4,190,108,32,128,224,204,160,172,16,49,52,9,225,228,130,42,73,49,25,20,34,198,200,46,13,23,174,68,62,81,169,151,241,117,191,223,143,
102,212,150,45,91,144,75,6,2,129,133,133,133,166,166,38,106,154,152,204,89,180,173,217,39,196,141,196,53,161,194,144,199,227,9,6,131,237,237,237,253,253,253,167,78,157,66,57,143,249,67,190,51,46,57,25,
57,114,114,129,13,31,46,148,213,213,213,170,170,170,235,175,191,62,151,203,197,227,241,112,56,188,188,188,76,25,120,94,136,186,186,58,101,53,98,9,155,112,174,161,170,170,10,211,10,102,131,23,74,117,5,
188,23,104,228,42,87,69,67,67,195,218,181,107,189,94,47,55,102,202,131,80,169,3,66,28,114,121,200,10,157,235,4,95,80,102,15,28,155,6,15,7,63,82,209,89,37,80,82,192,26,7,83,82,82,66,195,70,252,2,235,238,
124,21,125,113,113,49,144,58,51,96,173,174,174,182,183,183,63,251,236,179,240,73,192,181,32,243,151,25,12,175,35,0,226,72,36,34,19,70,9,179,42,92,11,4,80,155,161,46,207,87,70,70,70,224,189,137,81,111,
158,201,222,222,222,39,159,124,18,91,145,138,80,166,109,246,210,210,82,93,93,29,93,4,37,129,210,146,19,101,14,160,57,157,78,8,6,192,164,13,100,176,197,197,69,104,174,74,126,151,44,41,44,185,119,242,83,
50,153,12,242,146,112,56,108,182,254,120,77,249,230,148,220,145,224,175,249,87,171,171,171,157,157,6,213,133,77,0,0,32,0,73,68,65,84,157,77,77,77,240,24,90,89,89,249,208,135,62,132,170,20,21,188,162,48,
72,82,60,84,53,242,41,142,73,90,26,175,136,172,189,28,82,142,71,1,255,120,253,240,225,195,208,51,52,143,32,159,220,98,190,48,45,103,168,152,0,214,215,215,75,217,48,62,145,73,52,172,31,192,63,35,39,65,
158,110,89,195,98,125,163,37,66,97,120,83,4,195,196,137,204,231,44,166,54,108,216,112,250,244,233,181,107,215,178,114,92,183,110,157,92,40,202,146,93,93,117,216,95,1,134,3,195,196,239,247,131,31,93,86,
86,6,149,241,87,94,121,229,201,39,159,156,159,159,119,185,92,208,7,96,250,204,43,50,48,48,80,91,91,139,128,197,202,134,70,174,166,150,77,36,18,161,213,219,220,220,92,48,24,12,133,66,72,88,210,233,116,
117,117,53,82,54,137,90,48,97,97,150,65,99,70,40,82,181,181,181,121,60,158,75,151,46,225,27,241,59,98,147,48,215,3,255,86,2,187,92,190,16,228,3,84,101,42,168,64,78,214,20,66,203,199,160,79,167,211,48,
217,83,186,72,92,36,37,37,37,196,157,243,61,24,238,249,87,78,167,19,123,210,31,245,107,28,14,137,132,168,248,238,116,58,145,239,171,145,48,158,222,178,178,178,155,111,190,249,133,23,94,96,32,102,218,110,
73,200,33,32,80,120,30,178,184,184,120,221,186,117,4,250,64,37,196,250,103,118,143,67,122,241,197,23,215,173,91,231,243,249,112,108,75,75,75,175,190,250,234,190,125,251,160,76,96,201,44,66,178,108,19,
22,54,178,89,45,117,95,165,111,175,132,224,21,165,181,180,180,180,185,185,121,116,116,20,85,20,43,48,233,209,163,252,185,205,164,216,84,109,150,94,227,230,14,33,21,199,100,207,80,81,220,248,21,164,146,
123,99,99,35,190,169,207,231,203,102,179,152,83,227,87,150,16,37,237,74,24,28,212,80,143,9,113,208,167,145,27,24,139,42,135,156,42,86,127,153,78,167,127,247,187,223,93,184,112,193,4,170,76,227,143,203,
38,209,138,21,228,245,122,151,150,150,60,30,15,70,24,40,71,135,22,22,172,66,35,145,200,7,63,248,193,138,138,10,108,215,48,32,135,151,21,127,147,239,76,0,26,57,78,34,145,56,122,244,232,238,221,187,85,139,
217,220,87,76,0,90,98,106,244,131,224,4,54,141,10,105,126,33,99,180,252,67,36,116,160,250,98,2,21,46,39,18,173,43,46,46,190,112,225,194,175,127,253,235,75,151,46,225,166,226,26,37,173,66,30,127,79,79,
207,174,93,187,112,242,193,211,80,253,73,158,115,232,105,144,72,4,93,115,136,2,187,92,46,48,97,112,75,76,79,79,255,239,255,254,47,20,248,104,136,183,178,178,2,63,164,178,178,50,140,152,178,61,216,216,
216,232,247,251,143,29,59,70,202,29,222,220,114,1,224,61,113,81,72,240,100,216,234,237,237,45,41,41,73,167,211,148,208,85,173,127,197,211,47,32,232,67,184,0,121,186,234,39,83,54,246,74,136,70,180,26,224,
148,13,97,104,0,17,200,127,185,147,33,2,66,72,75,153,130,75,30,27,103,91,30,122,232,161,231,159,127,158,178,71,220,137,77,155,43,19,211,199,39,170,215,17,157,9,4,217,222,235,111,137,96,4,75,10,88,170,
99,188,176,184,184,120,102,102,230,165,151,94,154,156,156,164,125,170,217,6,148,187,11,99,49,137,137,202,68,152,253,24,83,216,71,229,164,14,135,163,165,165,229,252,249,243,236,156,99,57,177,10,193,93,
86,90,90,202,192,109,123,175,144,158,233,123,34,47,25,208,18,53,217,136,230,4,126,25,154,68,50,0,114,55,98,242,135,208,84,85,85,5,101,37,244,147,49,125,166,6,148,212,100,3,173,24,178,217,44,109,191,45,
133,62,212,94,206,217,64,92,59,135,148,31,147,251,213,228,228,228,179,207,62,75,133,23,165,182,76,24,244,10,67,179,162,169,2,20,199,109,143,3,2,207,52,149,74,197,227,113,136,231,210,23,61,16,8,148,150,
150,2,76,216,189,123,119,127,127,63,130,29,151,32,117,39,176,104,200,115,60,117,234,20,122,122,133,37,147,108,239,117,73,176,229,113,11,173,173,173,149,107,145,59,132,148,233,34,54,2,233,31,153,190,241,
61,57,79,133,252,247,249,231,159,223,191,127,191,100,101,50,131,48,69,47,161,78,213,215,215,231,116,58,37,124,102,51,236,38,109,239,56,51,201,164,56,145,72,84,86,86,210,47,6,37,97,60,30,199,81,97,128,
197,102,179,177,206,165,192,8,138,175,138,138,10,68,118,183,219,93,90,90,122,213,85,87,29,59,118,12,56,12,124,187,45,81,93,238,67,72,187,148,128,201,236,236,108,44,22,67,31,85,93,32,197,156,43,92,153,
113,105,97,78,65,166,2,88,96,104,30,94,9,31,212,92,210,30,143,103,102,102,70,186,201,32,70,115,25,216,237,118,164,26,60,219,150,61,118,58,101,52,52,52,116,118,118,158,56,113,130,107,88,117,35,36,133,214,
50,64,23,142,206,102,39,201,233,116,194,7,14,203,117,96,96,96,239,222,189,46,151,235,181,215,94,67,56,0,131,86,86,144,114,167,49,35,53,143,141,79,100,121,45,143,141,231,77,69,15,252,116,237,218,181,103,
207,158,5,196,129,29,130,165,27,181,142,201,215,150,221,84,203,123,153,172,21,153,215,59,157,78,228,70,114,85,179,85,40,175,23,15,149,190,31,248,44,200,205,227,163,129,112,146,236,152,175,153,68,120,154,
19,194,5,98,52,247,51,57,62,102,163,171,183,226,9,21,21,21,253,225,15,127,120,229,149,87,148,172,157,66,159,45,103,216,10,88,189,41,234,40,202,106,24,18,195,58,218,82,210,123,118,118,118,203,150,45,146,
20,1,82,7,88,107,40,85,184,113,201,36,26,4,234,51,103,206,64,17,223,156,30,182,52,6,181,20,115,97,198,39,99,171,170,223,149,232,40,135,59,44,239,127,92,206,215,95,127,125,239,222,189,241,120,92,154,105,
201,137,18,42,8,202,124,100,117,117,117,104,104,168,185,185,25,185,179,204,77,8,77,226,209,215,215,199,21,198,195,3,45,26,91,35,246,57,120,4,171,170,153,139,155,82,194,88,100,108,60,226,197,173,91,183,
238,219,183,175,175,175,47,223,140,168,76,124,120,233,85,30,212,211,211,211,216,216,152,203,229,232,182,201,9,236,2,193,212,178,195,193,188,65,81,158,1,61,95,201,216,148,60,3,139,139,139,153,76,6,48,145,
2,85,153,83,59,28,14,191,223,143,217,113,185,199,43,3,17,229,7,90,92,92,252,240,195,15,159,56,113,130,55,179,234,213,75,221,156,203,62,44,163,51,35,105,121,121,121,48,24,132,244,179,244,51,124,253,245,
215,169,24,147,203,229,208,190,86,173,218,124,99,244,78,167,147,26,79,132,37,153,160,40,92,88,138,201,72,23,105,182,46,239,185,231,158,23,94,120,33,22,139,73,235,100,246,39,177,29,42,253,0,165,49,205,
87,24,70,0,215,64,97,92,201,231,242,126,145,9,144,18,255,97,27,31,119,107,83,83,147,44,212,214,173,91,135,251,66,190,179,204,163,21,23,208,38,156,151,45,69,53,148,106,54,166,189,230,230,230,210,233,180,
67,53,133,145,211,245,246,246,90,38,206,106,15,52,107,207,194,210,248,188,45,139,139,139,35,145,136,12,154,166,202,12,142,56,18,137,32,147,98,36,178,219,237,107,214,172,25,26,26,194,202,192,70,199,44,
79,194,61,185,92,238,240,225,195,230,228,183,100,231,176,192,177,100,236,90,238,49,102,76,167,180,160,9,183,153,103,166,168,168,104,100,100,228,217,103,159,157,157,157,149,152,134,249,64,45,102,170,148,
1,92,14,4,2,139,139,139,244,245,32,154,41,143,214,239,247,163,63,46,157,94,193,85,144,47,78,79,79,179,215,44,79,11,67,51,195,52,231,253,200,145,184,237,182,219,90,91,91,209,165,48,155,174,166,46,135,194,
46,87,87,87,207,156,57,115,247,221,119,47,45,45,145,117,163,200,15,151,45,206,84,32,192,5,149,221,155,43,25,107,70,194,34,69,241,161,213,203,138,88,2,178,136,248,197,197,197,13,13,13,228,14,202,60,78,
85,63,127,28,219,125,103,115,90,89,89,217,181,107,87,67,67,195,192,192,128,228,171,201,78,160,76,159,21,14,35,111,147,230,230,102,25,157,213,178,172,174,174,6,205,11,180,107,75,249,42,20,55,197,197,197,
94,175,87,122,62,169,76,92,126,65,156,40,217,240,151,209,89,182,185,36,156,197,33,88,25,205,177,32,63,242,145,143,60,253,244,211,50,201,147,139,4,18,105,124,93,102,211,202,124,25,134,30,46,151,203,235,
245,206,206,206,202,206,7,169,177,146,242,164,106,92,101,87,134,143,192,240,170,188,49,59,58,58,100,105,40,69,77,149,105,6,101,70,76,229,147,124,196,187,165,165,37,132,102,236,76,239,209,226,8,135,195,
191,250,213,175,104,131,148,47,70,243,95,185,227,21,102,67,171,245,167,148,22,44,147,14,156,160,104,52,138,59,65,134,120,167,211,217,216,216,8,158,175,4,91,8,93,49,148,192,254,167,190,190,94,118,21,242,
57,66,230,19,55,144,67,71,5,210,58,41,107,71,165,21,117,85,146,201,228,235,175,191,222,211,211,67,116,56,223,3,232,27,207,137,130,35,227,241,184,203,229,162,158,22,136,80,128,95,137,108,0,58,39,120,138,
195,240,249,124,201,100,18,156,98,73,192,226,14,207,215,25,157,45,195,180,124,190,101,203,150,134,134,134,167,158,122,202,82,38,41,95,17,202,199,249,243,231,113,186,48,80,99,182,209,175,60,119,86,141,
123,220,141,5,162,51,135,155,232,39,45,73,114,124,206,9,35,153,70,53,52,52,80,142,199,44,194,88,201,201,129,11,105,226,94,94,94,126,231,157,119,62,246,216,99,156,85,145,65,217,52,247,179,196,202,155,155,
155,171,171,171,205,208,92,92,92,236,247,251,165,189,52,153,197,68,87,137,162,128,156,83,82,82,82,83,83,131,177,82,32,167,64,240,40,240,192,45,28,11,134,1,154,68,8,38,212,74,80,69,197,104,249,132,185,
69,89,89,217,167,62,245,169,23,94,120,1,234,216,102,79,8,134,162,196,106,229,134,129,8,142,146,107,237,218,181,8,142,196,151,169,53,38,187,71,170,61,200,215,101,172,231,41,149,233,51,14,166,174,174,78,
74,78,43,237,105,9,119,48,64,75,229,200,124,76,59,208,141,150,150,150,128,209,33,247,122,87,245,252,224,193,131,191,255,253,239,243,193,26,210,247,200,50,188,42,124,67,237,192,234,166,50,69,176,242,161,
34,110,183,27,48,180,106,199,35,47,152,157,157,229,209,82,21,90,210,218,86,86,86,206,158,61,139,249,14,201,115,84,58,103,38,248,168,190,11,149,86,212,14,111,74,46,200,108,90,77,19,28,61,122,244,196,137,
19,11,11,11,8,109,242,234,170,96,141,87,80,58,40,193,70,126,86,52,26,13,133,66,212,113,199,93,4,57,102,222,78,110,183,27,20,108,44,104,183,219,141,74,63,145,72,224,4,178,136,147,251,52,167,16,233,10,72,
172,67,250,39,200,144,29,10,133,190,244,165,47,61,241,196,19,83,83,83,87,130,36,200,147,214,223,223,159,201,100,8,142,75,60,167,0,167,222,146,20,104,250,132,153,2,32,20,153,196,208,90,97,231,29,150,83,
30,143,7,91,29,26,12,224,92,171,25,10,203,47,136,232,192,4,66,230,203,247,222,123,239,175,127,253,107,160,219,172,93,136,66,228,35,29,153,188,61,245,5,253,126,127,117,117,181,233,114,64,130,138,148,33,
196,149,229,170,198,240,14,112,91,46,12,22,190,92,210,148,139,98,248,150,179,154,202,94,71,94,14,117,237,184,252,176,188,63,242,145,143,172,174,174,158,56,113,66,137,26,146,216,32,65,51,36,254,112,25,
102,82,76,123,57,100,42,120,91,42,43,0,14,149,35,11,28,142,149,109,58,53,125,35,1,104,124,116,99,99,35,163,188,108,138,74,184,67,129,90,106,203,87,79,208,174,7,4,143,0,66,171,110,199,199,62,246,49,252,
106,117,117,245,246,237,219,139,138,138,230,231,231,207,156,57,67,201,218,177,177,177,124,121,180,101,92,51,99,150,153,215,168,25,80,243,191,210,20,57,22,139,129,182,161,168,32,32,35,3,236,55,93,72,248,
24,26,26,74,165,82,44,3,37,19,78,137,9,228,139,206,42,239,94,94,94,142,70,163,129,64,0,187,168,153,218,32,76,35,123,197,18,9,135,195,251,246,237,131,185,42,229,91,213,248,28,219,214,252,5,56,216,130,205,
102,126,74,54,155,157,159,159,135,92,137,169,79,132,219,230,193,7,31,220,189,123,247,198,141,27,235,235,235,93,46,151,203,229,34,63,7,115,119,88,73,227,227,227,178,143,33,217,232,76,142,100,214,44,19,
106,114,111,202,202,202,190,248,197,47,62,247,220,115,39,78,156,40,172,130,98,51,140,72,78,158,60,121,235,173,183,74,238,68,129,81,230,194,209,217,178,59,162,48,65,9,70,169,161,56,249,87,184,159,25,101,
92,46,87,46,151,83,62,126,166,100,171,148,13,32,225,65,70,1,226,140,45,45,45,215,95,127,253,111,127,251,91,53,20,151,79,36,222,220,228,70,70,70,86,87,87,153,68,59,157,206,80,40,164,8,139,184,76,114,158,
136,247,17,160,24,54,99,49,197,10,209,103,201,179,148,242,100,92,12,178,169,43,207,30,191,136,242,142,145,248,6,47,19,187,166,252,23,25,134,137,3,16,228,229,84,4,58,22,156,232,193,187,81,181,28,118,174,
50,131,150,253,24,105,4,44,113,39,226,206,68,78,42,42,42,48,22,200,120,221,210,210,34,149,160,101,56,150,14,91,244,172,225,127,81,111,169,107,10,45,20,68,9,137,83,191,187,125,194,112,197,102,179,125,226,
19,159,144,215,207,68,250,14,30,60,136,243,56,54,54,54,54,54,134,80,62,61,61,29,14,135,231,231,231,99,177,88,119,119,247,101,103,85,200,202,52,193,89,115,179,197,253,0,247,41,149,182,227,73,75,75,11,134,
250,136,103,145,83,197,42,198,233,116,246,246,246,94,125,245,213,249,196,92,242,25,208,229,235,25,34,163,236,235,235,243,120,60,129,64,64,245,103,228,134,233,245,122,231,231,231,15,30,60,8,10,157,44,18,
101,41,36,249,27,50,149,182,244,37,146,167,107,110,110,14,169,92,190,17,190,84,42,245,218,107,175,253,223,255,253,95,107,107,235,29,119,220,177,97,195,6,160,105,24,251,134,62,42,122,65,114,92,69,246,6,
177,142,203,203,203,119,238,220,57,48,48,16,143,199,21,30,141,47,197,120,253,241,143,127,124,227,198,141,79,61,245,84,1,157,44,179,27,124,236,216,177,59,239,188,19,55,146,108,15,230,91,138,5,162,51,102,
46,70,70,70,38,38,38,70,70,70,110,191,253,246,235,174,187,78,117,222,136,225,200,90,135,173,93,6,119,76,37,112,65,34,41,51,231,220,242,25,96,74,251,71,6,95,57,165,181,186,186,122,207,61,247,236,217,179,
135,30,143,196,28,242,117,147,76,242,236,200,200,72,58,157,238,232,232,192,64,166,76,48,113,129,20,13,67,69,82,50,208,37,255,21,131,57,44,236,120,79,17,7,160,111,6,202,59,185,99,65,155,80,13,133,146,254,
36,65,106,115,216,231,217,103,159,61,126,252,56,121,132,12,163,32,66,120,60,30,232,105,72,144,87,205,31,200,33,35,110,45,252,202,56,12,10,42,113,37,152,130,80,188,88,141,141,141,170,186,173,173,173,229,
148,3,183,49,217,129,148,169,180,132,146,148,252,44,120,141,156,95,83,244,243,119,61,9,21,7,94,149,210,242,102,184,230,154,107,240,124,231,206,157,249,238,22,252,21,156,204,241,252,173,183,222,194,143,
134,135,135,135,135,135,177,32,168,105,107,57,110,36,251,254,21,21,21,50,64,47,47,47,15,13,13,5,131,65,42,22,181,180,180,12,15,15,19,242,99,104,230,142,93,90,90,58,54,54,182,101,203,22,206,164,94,225,
136,141,12,229,138,141,91,85,85,21,139,197,18,137,68,50,153,116,58,157,112,225,85,247,213,242,242,242,165,75,151,78,159,62,13,49,45,48,1,20,154,81,192,218,135,147,69,166,166,160,124,30,139,197,192,179,
182,196,127,153,77,120,60,158,35,71,142,28,57,114,164,166,166,166,171,171,107,205,154,53,192,124,33,212,201,110,62,199,71,229,44,31,18,189,146,146,146,234,234,106,92,56,133,111,200,191,114,56,28,215,95,
127,125,125,125,253,99,143,61,38,117,232,77,18,155,12,211,199,143,31,7,12,77,179,193,203,130,206,50,58,143,140,140,140,140,140,140,142,142,14,15,15,195,15,140,210,90,207,63,255,252,186,117,235,144,4,73,
131,56,238,181,146,253,66,214,20,206,9,50,104,60,49,89,37,170,251,100,137,69,144,203,204,37,135,251,139,196,231,91,110,185,37,20,10,161,53,135,6,81,129,220,217,50,82,151,148,148,128,67,70,11,87,80,125,
205,169,101,137,240,200,224,235,114,185,228,249,172,168,168,0,213,85,17,51,36,118,44,77,36,164,110,20,168,71,114,170,94,62,212,222,131,237,144,255,61,112,224,192,177,99,199,228,9,68,78,227,243,249,188,
94,175,140,203,120,128,230,72,63,85,40,34,65,170,31,112,129,244,0,98,4,199,181,102,170,75,56,84,42,190,2,33,193,155,195,175,14,148,89,156,204,186,186,58,233,112,102,170,167,170,65,71,164,50,178,41,69,
143,118,25,154,77,99,141,63,78,54,42,198,187,92,196,249,18,22,75,94,179,68,60,58,59,59,249,11,208,96,51,223,240,192,129,3,247,222,123,111,190,230,41,185,210,21,21,21,185,92,110,126,126,62,16,8,164,211,
233,139,23,47,98,30,180,171,171,139,233,94,93,93,29,196,27,21,208,129,253,28,45,160,254,254,254,206,206,78,53,146,116,89,95,53,75,34,1,150,105,109,109,45,198,73,179,217,236,244,244,116,36,18,241,249,124,
28,189,159,153,153,57,121,242,36,148,110,248,161,144,113,144,73,180,169,19,196,244,138,250,74,16,161,206,151,132,130,134,140,181,104,57,212,128,58,3,69,89,113,113,241,236,236,236,235,175,191,94,84,84,
180,102,205,154,117,235,214,237,222,189,27,18,13,212,100,80,19,246,215,92,115,13,12,19,108,54,91,77,77,205,85,87,93,117,254,252,121,162,31,228,153,168,22,98,103,103,231,247,191,255,253,31,255,248,199,
163,163,163,150,185,191,108,6,20,23,23,95,188,120,17,179,42,178,234,180,28,69,161,122,195,249,243,231,71,71,71,145,44,75,74,56,84,126,24,229,151,150,150,254,235,191,254,235,239,254,238,239,100,87,64,134,
9,252,166,201,226,2,24,5,2,190,204,125,212,150,147,79,99,65,134,123,9,158,48,109,103,209,118,247,221,119,15,13,13,37,18,137,124,232,179,121,235,50,71,134,64,154,195,225,64,62,196,102,184,26,124,48,73,
165,108,122,195,211,93,21,166,126,191,31,50,167,12,97,204,100,113,78,8,245,42,244,3,141,107,254,84,93,101,150,206,74,95,16,227,87,251,247,239,199,42,197,16,16,82,221,141,27,55,226,142,70,145,177,188,188,
12,123,76,96,229,210,164,17,145,26,104,18,177,50,165,185,40,53,248,45,145,52,30,45,142,132,86,3,11,11,11,216,2,75,75,75,219,218,218,228,240,151,162,102,243,46,198,47,155,12,49,121,132,5,226,242,187,76,
71,149,219,115,156,41,95,140,150,28,44,245,35,53,237,83,184,62,45,60,228,34,135,118,168,148,143,187,29,80,206,249,243,231,33,115,76,245,91,106,69,114,176,16,247,42,238,144,193,193,65,108,27,106,228,244,
202,189,142,20,36,226,243,249,32,152,203,119,131,137,122,105,105,233,196,196,68,44,22,67,235,86,238,249,184,96,116,14,195,139,188,78,210,134,7,43,128,147,254,150,44,93,190,152,78,167,49,34,101,105,79,
217,212,212,196,241,57,249,211,185,185,185,161,161,161,112,56,188,118,237,90,34,149,82,242,162,190,190,254,250,235,175,199,157,192,143,94,187,118,45,108,100,153,98,227,60,35,94,67,80,5,143,96,48,248,221,
239,126,247,87,191,250,213,155,111,190,89,160,88,33,213,225,194,133,11,24,251,84,19,167,92,111,253,253,253,23,47,94,68,154,204,161,24,10,90,241,215,36,16,129,179,157,203,229,222,126,251,109,148,125,150,
23,157,49,90,145,183,56,111,169,194,186,37,122,163,114,115,75,132,90,150,71,124,242,192,3,15,60,254,248,227,208,183,147,113,95,222,252,230,9,172,170,170,106,108,108,148,213,6,99,52,122,101,252,106,178,
187,174,38,158,1,58,155,21,9,60,16,230,231,231,229,208,179,148,154,66,8,102,252,197,249,7,53,69,89,204,72,114,173,140,134,0,94,241,98,111,111,239,107,175,189,198,41,83,8,46,66,124,110,104,104,8,28,121,
158,22,68,225,108,54,11,181,88,114,1,216,185,145,217,58,115,53,222,107,146,80,97,169,228,35,161,18,169,84,3,115,178,53,107,214,4,2,1,166,189,114,118,134,127,136,28,133,249,1,151,135,44,206,242,45,15,115,
229,56,76,53,110,144,108,36,44,101,198,89,236,48,230,143,100,14,88,24,61,100,129,35,123,196,236,110,225,203,184,221,110,244,139,199,198,198,252,126,63,81,118,156,122,36,173,212,166,129,232,12,201,209,
120,145,249,66,50,153,28,26,26,130,19,74,225,201,111,203,41,112,203,31,213,214,214,142,142,142,202,105,209,104,52,26,14,135,21,167,71,209,113,176,45,203,6,2,106,91,186,213,200,59,220,231,243,1,238,183,
229,113,231,164,136,23,202,40,149,9,134,66,33,140,80,171,89,199,186,186,58,176,56,50,153,204,165,75,151,146,201,36,68,42,128,241,21,21,21,109,221,186,149,3,62,106,111,216,186,117,43,60,241,100,251,136,
209,89,246,15,43,43,43,191,248,197,47,118,116,116,252,226,23,191,176,100,188,112,164,21,146,47,212,237,66,220,9,135,195,151,46,93,154,158,158,70,207,131,142,215,140,8,230,190,5,159,7,134,33,151,203,133,
111,84,93,93,109,102,166,138,36,128,179,65,241,13,186,106,33,61,151,162,201,230,60,142,165,8,137,204,173,164,40,130,228,9,20,23,23,7,131,193,173,91,183,130,16,125,37,246,158,46,151,171,181,181,213,114,
238,6,49,26,57,181,162,94,112,0,90,245,114,136,111,168,77,177,182,182,54,26,141,202,92,91,114,27,24,160,121,47,83,230,24,201,175,74,162,85,15,9,183,42,62,235,194,133,11,175,189,246,154,116,77,195,12,26,
90,178,139,139,139,82,228,50,30,143,179,151,158,76,38,51,153,12,67,132,148,239,80,114,20,68,99,136,111,240,194,201,170,197,52,139,1,157,174,172,172,12,32,18,180,133,41,31,42,131,131,57,206,174,6,41,101,
220,47,128,105,152,74,85,22,1,26,223,1,214,6,150,40,7,54,34,83,52,139,139,94,233,177,90,10,164,205,206,206,50,145,204,151,174,66,205,7,233,182,188,39,169,180,13,155,12,98,103,106,92,27,112,24,143,225,
236,217,179,173,173,173,50,137,190,18,137,59,155,149,179,140,237,29,251,2,191,223,143,81,233,68,34,49,53,53,197,97,4,70,19,34,182,102,152,38,251,10,217,132,34,186,81,222,193,210,238,214,196,187,177,51,
129,141,196,36,11,109,64,249,135,165,165,165,161,80,72,74,82,0,226,167,80,167,211,233,188,243,206,59,3,129,64,190,74,200,110,183,111,222,188,249,226,197,139,164,1,80,59,216,146,58,253,209,143,126,116,
195,134,13,143,62,250,40,74,28,57,73,44,183,249,67,135,14,77,78,78,158,61,123,118,255,254,253,85,85,85,193,96,48,30,143,35,70,72,18,174,101,148,196,41,66,227,158,253,61,168,136,85,87,87,223,118,219,109,
24,129,81,60,66,115,50,190,172,172,44,155,205,2,167,194,101,42,43,43,75,36,18,156,130,139,199,227,229,229,229,102,91,152,13,15,51,167,150,30,17,92,3,114,166,191,164,164,228,236,217,179,38,61,220,124,148,
148,148,180,182,182,74,53,40,179,47,157,74,165,224,230,110,146,20,45,165,212,32,188,165,8,112,88,120,129,64,96,102,102,70,38,194,220,143,101,252,69,62,11,191,24,74,57,19,76,96,12,225,251,80,54,167,168,
168,40,28,14,191,241,198,27,146,231,42,163,10,220,102,201,165,89,88,88,128,221,132,12,184,208,9,192,37,35,79,67,34,27,252,101,10,72,73,168,64,38,179,92,90,128,125,74,75,75,119,236,216,33,149,115,160,117,
252,228,147,79,250,124,62,167,211,233,245,122,67,161,16,182,195,194,101,183,196,154,44,211,100,153,131,171,8,238,200,231,117,79,243,102,117,127,34,4,200,41,21,203,100,153,155,106,190,94,226,153,51,103,
100,59,219,82,251,60,16,8,72,143,116,78,211,243,32,209,163,227,226,195,20,6,221,140,212,248,98,50,153,156,158,158,174,169,169,185,194,244,217,82,241,78,97,169,126,191,63,18,137,76,76,76,32,250,48,1,228,
202,160,134,189,100,215,241,177,180,180,196,4,141,234,7,171,171,171,216,186,86,87,87,209,123,204,23,154,229,30,142,105,37,130,42,229,229,229,96,107,202,27,213,231,243,153,250,162,182,119,148,139,237,118,
123,87,87,215,206,157,59,89,168,202,121,48,153,77,215,212,212,196,98,177,120,60,206,49,78,78,114,74,169,88,134,233,237,219,183,63,241,196,19,223,252,230,55,251,251,251,201,113,68,219,135,199,240,135,63,
252,97,231,206,157,184,117,253,126,255,247,190,247,61,143,199,83,90,90,10,39,23,234,234,41,193,69,190,3,248,176,120,243,170,170,42,168,133,132,66,161,107,175,189,214,242,154,158,57,115,166,190,190,158,
4,53,38,206,96,34,74,197,75,126,232,244,244,52,18,186,96,48,168,18,88,70,112,37,182,37,161,15,44,6,121,102,248,21,30,122,232,161,175,125,237,107,5,86,32,232,4,242,104,149,62,170,156,61,201,102,179,163,
163,163,77,77,77,114,166,153,3,92,202,216,147,36,98,105,83,64,37,216,153,153,25,41,90,64,218,134,228,182,50,214,163,223,163,68,51,100,224,99,156,130,188,234,220,220,220,107,175,189,38,195,55,69,4,201,
135,195,175,97,12,2,130,212,100,94,3,178,64,135,105,102,102,6,18,178,228,62,171,254,36,142,42,147,201,48,125,150,238,116,182,119,164,192,241,254,200,54,154,154,154,176,97,115,86,219,227,241,96,166,166,
170,170,170,173,173,13,210,187,151,141,27,74,94,195,18,211,80,3,223,239,9,208,150,102,22,220,228,101,46,44,9,234,178,99,147,79,118,131,124,70,75,95,75,213,251,54,91,34,85,85,85,228,201,227,192,212,224,
22,158,196,227,241,234,234,106,174,149,80,40,4,59,46,240,19,20,110,126,241,226,197,218,218,90,5,63,93,73,116,182,204,181,115,185,92,56,28,158,154,154,146,209,89,1,91,76,168,37,197,24,58,191,241,120,28,
91,58,59,188,80,25,69,3,90,94,8,226,245,5,60,223,136,112,97,7,133,1,130,252,147,166,166,38,147,106,194,158,73,105,105,233,45,183,220,210,222,222,78,224,130,172,30,233,237,196,203,183,110,221,186,238,238,
110,84,12,128,125,243,77,30,226,11,54,54,54,254,252,231,63,255,215,127,253,215,23,95,124,145,234,210,172,106,37,151,11,243,253,253,253,253,109,109,109,37,37,37,245,245,245,201,100,18,105,172,165,156,63,
190,50,160,12,143,199,3,61,185,146,146,146,174,174,46,92,107,245,149,151,150,150,246,238,221,155,205,102,97,131,132,27,155,141,35,115,29,66,194,155,161,42,151,203,77,77,77,213,213,213,41,58,32,91,70,54,
97,213,33,145,1,41,173,69,186,17,126,244,185,207,125,238,252,249,243,255,253,223,255,109,182,121,101,39,80,189,142,211,107,201,146,94,92,92,68,140,86,38,24,36,159,225,69,224,27,74,192,128,45,65,187,221,
94,87,87,55,58,58,106,234,185,51,64,203,241,8,175,215,11,169,22,188,194,34,91,145,89,145,151,68,163,209,61,123,246,80,208,131,65,28,10,180,110,183,27,9,22,170,150,186,186,58,208,51,16,127,73,248,33,124,
1,120,7,51,120,148,20,151,135,77,225,73,217,60,132,17,4,41,76,203,239,60,240,254,45,45,45,148,12,90,93,93,109,110,110,222,180,105,83,40,20,242,122,189,18,156,44,16,58,208,230,241,251,253,48,141,179,140,
209,150,145,90,226,4,14,211,66,134,255,45,45,45,149,22,115,28,230,177,25,174,54,150,105,50,112,146,124,191,32,25,69,150,186,95,85,85,85,138,218,77,19,35,245,149,82,169,84,101,101,37,180,81,96,76,37,49,
50,46,65,240,135,210,233,52,4,78,243,141,62,94,22,223,192,31,70,34,17,88,64,145,76,38,163,152,165,113,28,190,53,126,45,26,141,74,46,61,48,104,230,215,236,248,65,38,109,110,110,174,128,178,162,4,58,112,
138,214,175,95,47,171,13,135,195,177,126,253,122,183,219,189,184,184,200,12,133,66,75,217,108,182,161,161,225,246,219,111,231,24,139,105,30,40,51,32,158,207,246,246,246,179,103,207,226,91,48,7,151,207,
85,54,237,243,249,190,255,253,239,183,180,180,60,254,248,227,18,25,80,247,63,78,194,161,67,135,160,190,189,178,178,2,40,121,110,110,78,217,75,227,171,185,92,46,159,207,135,165,130,17,118,152,34,147,118,
38,31,11,11,11,7,14,28,0,187,38,151,203,245,244,244,236,216,177,67,218,223,152,147,129,69,69,69,51,51,51,44,234,113,107,76,79,79,195,102,87,206,182,73,26,153,210,139,176,9,89,112,226,0,108,94,229,114,
185,175,124,229,43,207,63,255,60,133,55,9,82,213,215,215,91,194,205,236,175,228,91,186,139,139,139,227,227,227,173,173,173,82,149,159,204,104,6,104,208,84,32,57,34,53,179,240,164,181,181,117,114,114,18,
120,177,188,241,73,130,102,122,14,175,31,236,64,116,218,149,231,83,238,1,145,72,132,206,121,242,19,51,153,204,249,243,231,225,155,142,146,168,168,168,104,106,106,106,195,134,13,169,84,138,49,151,3,226,
18,202,112,56,28,240,32,71,143,135,133,11,115,106,124,28,252,31,80,240,49,37,146,82,171,236,112,52,55,55,163,181,227,118,187,171,170,170,110,191,253,118,78,255,170,157,210,146,2,11,50,204,111,127,251,
219,201,201,73,220,209,53,53,53,240,176,175,171,171,107,104,104,128,246,97,62,46,208,187,52,59,75,171,112,9,144,129,171,207,131,203,39,88,97,9,119,148,148,148,64,59,212,252,17,137,210,42,20,162,18,196,
60,165,76,153,113,48,150,8,14,48,38,164,135,232,13,214,213,213,113,181,225,226,33,161,182,217,108,125,125,125,144,79,42,64,196,182,229,215,245,103,228,154,156,156,140,68,34,20,110,151,61,22,217,233,178,
124,79,88,208,146,14,41,109,70,169,194,193,118,179,211,233,156,155,155,51,33,14,75,5,190,92,46,7,152,146,82,0,46,151,171,163,163,131,18,116,10,182,42,41,41,217,182,109,27,126,65,134,36,89,52,88,94,107,
172,191,230,230,230,249,249,121,115,248,91,61,151,57,245,151,190,244,165,109,219,182,125,235,91,223,74,38,147,170,76,150,165,244,161,67,135,30,120,224,1,106,147,162,135,25,139,197,208,26,65,88,193,32,
59,115,28,244,166,58,59,59,225,249,100,74,58,204,205,205,237,221,187,23,108,1,106,162,95,188,120,113,221,186,117,114,140,72,54,96,193,161,196,189,45,39,241,16,101,168,75,206,28,28,75,87,1,202,18,96,229,
88,179,18,63,107,104,104,184,246,218,107,247,238,221,139,11,228,114,185,154,154,154,232,252,98,94,107,26,60,90,26,187,16,14,154,152,152,192,125,68,36,4,6,225,24,146,134,69,8,17,18,42,119,75,72,122,205,
154,53,103,207,158,149,1,26,65,141,191,128,184,233,247,251,229,4,57,222,74,57,97,179,231,129,171,192,89,12,220,80,201,100,242,204,153,51,160,39,172,172,172,12,12,12,180,183,183,195,206,102,100,100,132,
140,20,89,148,72,83,5,146,178,211,233,52,212,102,192,241,192,229,70,215,81,166,222,148,79,48,89,55,14,135,163,181,181,213,239,247,35,31,135,94,160,37,75,170,64,217,141,47,181,110,221,186,233,233,105,220,
242,163,163,163,48,225,4,236,89,82,82,18,10,133,26,26,26,2,129,64,83,83,19,68,175,76,68,193,97,74,126,40,163,16,226,107,92,88,249,252,164,45,193,232,210,210,210,116,58,45,19,16,252,168,183,183,215,76,
81,169,205,102,179,217,130,193,32,3,180,212,15,50,115,28,40,198,178,246,41,47,47,71,143,8,254,99,104,191,242,211,39,38,38,54,110,220,40,173,88,44,185,83,133,153,209,241,120,28,123,143,92,202,234,129,204,
69,170,56,201,174,49,87,39,67,51,41,31,136,149,196,163,37,17,202,108,245,170,135,207,231,11,133,66,192,181,145,34,181,183,183,75,176,66,122,4,123,189,222,174,174,46,70,129,194,35,212,106,212,30,143,230,
230,230,161,161,33,228,83,5,148,149,36,111,218,110,183,223,122,235,173,107,214,172,249,234,87,191,218,223,223,47,117,123,213,29,251,246,219,111,223,124,243,205,44,39,203,202,202,154,155,155,165,118,37,
46,61,137,86,37,37,37,215,92,115,77,109,109,173,233,47,179,186,186,58,54,54,118,244,232,81,70,103,18,25,225,232,209,220,220,172,102,189,112,134,195,225,48,231,239,149,200,87,46,151,139,197,98,48,250,177,
9,165,111,121,219,155,76,167,146,146,18,64,127,60,108,38,209,247,223,127,255,242,242,242,200,200,8,188,148,10,216,239,42,117,58,37,248,32,81,105,155,205,54,53,53,213,218,218,234,245,122,65,77,1,145,3,
135,4,91,144,76,38,131,168,33,199,157,248,53,27,27,27,71,70,70,34,145,136,114,169,231,54,128,239,136,118,17,71,66,104,128,171,110,213,229,229,229,183,223,126,91,226,218,248,205,201,201,73,4,4,70,30,140,
164,181,181,181,37,18,137,115,231,206,81,147,82,213,238,28,223,199,34,100,187,27,248,33,72,23,8,229,8,139,108,221,155,228,96,158,204,154,154,154,157,59,119,130,176,136,11,218,210,210,98,73,180,200,199,
15,230,73,168,170,170,170,170,170,130,191,40,71,186,89,46,244,245,245,157,63,127,30,7,6,116,187,169,169,169,165,165,165,166,166,166,173,173,173,173,173,205,233,116,58,212,48,155,82,45,192,52,122,54,155,
229,61,175,90,186,178,28,206,7,73,35,31,36,21,201,148,5,160,206,158,140,185,129,64,192,116,30,67,128,150,82,126,116,226,73,36,18,128,173,81,231,162,211,69,178,157,60,212,161,161,161,142,142,14,203,209,
152,203,162,28,11,11,11,241,120,28,117,119,85,85,21,12,13,84,20,35,204,199,228,145,44,58,53,219,45,149,1,100,30,77,148,131,68,40,181,115,88,90,168,148,151,151,183,180,180,128,107,136,123,0,99,62,184,219,
229,191,54,155,173,163,163,3,178,182,210,112,64,93,65,203,12,87,118,243,237,118,59,98,180,74,156,45,129,14,201,244,216,188,121,243,111,126,243,155,175,125,237,107,175,190,250,170,220,51,164,178,193,158,
61,123,110,185,229,22,156,1,183,219,237,247,251,153,213,38,147,73,4,20,30,188,223,239,223,181,107,23,157,149,85,145,49,48,48,0,167,106,121,108,8,238,229,229,229,11,11,11,128,149,229,106,196,205,92,91,
91,59,59,59,203,209,233,86,122,0,0,32,0,73,68,65,84,109,64,129,206,96,17,160,185,47,197,213,44,103,62,121,71,192,34,68,226,27,248,243,7,30,120,224,47,255,242,47,223,124,243,205,127,249,151,127,65,239,
75,222,50,106,137,154,172,15,230,4,104,115,133,66,33,183,219,13,19,238,210,210,82,159,207,199,141,31,199,131,219,4,140,5,36,167,137,68,34,28,14,35,237,144,23,122,195,134,13,251,246,237,35,122,14,185,59,
6,104,184,214,73,154,132,44,109,21,215,168,187,187,155,118,16,92,99,231,206,157,155,152,152,80,179,90,16,42,232,239,239,79,167,211,139,139,139,219,182,109,83,204,57,38,206,116,234,64,54,128,251,5,35,33,
51,51,51,217,108,54,24,12,50,251,102,143,49,95,13,74,15,107,40,74,131,157,34,29,226,175,240,129,75,182,176,176,208,210,210,66,126,151,199,227,65,152,134,143,40,158,164,211,105,124,181,133,133,133,158,
158,30,176,39,160,114,81,83,83,227,192,45,42,135,211,165,222,7,144,32,167,211,201,38,137,202,25,205,62,128,37,220,1,28,141,68,43,245,47,49,32,169,163,136,25,19,213,189,148,117,40,238,118,121,55,166,211,
105,12,98,226,157,153,56,43,150,254,224,224,32,240,77,53,174,82,88,205,110,121,121,25,22,83,54,97,120,154,74,165,164,91,4,143,138,237,77,201,124,164,5,145,100,59,49,82,179,127,72,167,31,92,20,233,112,
42,59,188,106,68,8,58,226,164,220,225,247,49,5,203,208,79,215,212,45,91,182,200,6,154,42,38,20,226,172,156,50,20,167,181,162,162,34,24,12,206,205,205,17,110,150,255,50,100,19,161,230,235,85,85,85,96,26,
72,241,60,185,174,162,209,104,34,145,128,239,173,108,205,3,48,197,18,199,226,105,107,107,219,180,105,147,148,39,228,239,175,174,174,30,63,126,252,226,197,139,142,247,62,136,66,226,180,167,82,169,100,50,
9,33,36,68,22,118,11,170,171,171,51,153,76,34,145,48,183,168,133,133,133,233,233,105,191,223,95,95,95,143,118,147,233,149,167,154,28,50,241,228,72,52,59,177,123,246,236,121,234,169,167,216,113,1,101,34,
95,104,144,40,1,222,7,237,196,202,202,202,170,170,42,210,81,176,0,22,22,22,16,163,9,200,64,62,144,55,75,105,105,105,77,77,13,88,243,232,202,242,43,215,214,214,214,213,213,77,76,76,72,47,18,169,117,87,
87,87,199,227,145,138,149,178,22,89,94,94,190,120,241,34,167,4,24,178,207,156,57,3,50,165,178,41,160,195,61,152,78,233,116,90,150,122,44,32,240,137,228,240,44,137,7,87,81,36,18,169,171,171,3,125,203,148,
196,50,251,114,237,237,237,178,129,1,181,162,43,164,123,169,231,209,104,244,212,169,83,114,71,65,86,193,84,137,62,21,28,55,167,206,226,194,194,194,236,236,172,131,194,125,88,148,20,174,197,93,237,245,
122,209,34,240,249,124,0,83,228,101,96,129,99,9,113,168,87,192,51,133,249,166,205,102,155,156,156,36,172,97,86,115,82,148,75,105,216,75,197,34,165,254,133,2,54,31,102,74,56,108,105,105,105,124,124,60,
20,10,93,225,48,33,210,115,96,241,242,13,193,49,192,194,101,87,221,148,238,147,42,177,8,232,114,152,91,9,36,49,137,166,161,61,136,241,234,182,55,189,220,145,14,179,22,97,1,40,175,23,128,163,77,155,54,
153,222,2,50,178,40,45,5,5,119,152,194,85,53,53,53,152,179,50,3,180,9,122,240,68,61,247,220,115,191,248,197,47,120,29,101,241,193,119,222,187,119,239,238,221,187,165,64,154,28,111,1,92,176,97,195,6,110,
54,38,43,185,187,187,187,191,191,95,197,101,236,22,248,151,4,190,88,44,6,54,8,117,18,136,105,52,54,54,14,13,13,169,166,22,88,158,139,139,139,83,83,83,177,88,172,162,162,2,67,13,52,6,51,9,254,178,214,65,
178,66,220,105,255,254,253,207,61,247,220,244,244,180,204,196,201,201,177,140,14,176,244,108,108,108,4,225,189,186,186,90,154,192,73,234,61,94,73,38,147,24,205,197,87,38,205,73,58,51,225,121,117,117,53,
72,205,80,155,73,165,82,87,95,125,245,243,207,63,143,9,102,124,10,18,59,92,148,80,40,36,29,99,185,54,232,239,12,225,61,92,92,200,117,193,12,247,220,185,115,232,139,154,169,24,253,67,16,185,134,134,134,
186,186,186,152,65,83,186,128,69,21,101,155,204,125,20,192,81,56,28,110,109,109,53,1,61,117,167,59,28,14,14,115,175,174,174,6,2,1,132,254,43,196,63,229,213,57,126,252,56,92,205,164,133,163,205,240,77,
150,249,4,78,26,203,220,119,155,132,140,238,88,16,192,130,65,244,227,13,239,118,187,161,229,79,148,67,14,128,42,209,103,115,194,144,188,75,80,149,167,167,167,21,172,33,31,240,44,48,197,71,176,68,164,44,
156,60,119,78,167,51,155,205,66,83,216,150,199,80,28,187,217,165,75,151,176,49,230,99,113,200,153,84,56,114,33,113,131,158,6,65,52,16,128,88,244,153,18,37,140,209,8,124,96,98,42,101,6,9,70,203,60,130,
162,163,234,192,76,129,133,150,150,22,217,97,144,146,76,188,210,165,165,165,87,95,125,53,96,92,208,66,164,62,153,185,81,41,163,50,21,163,213,139,161,80,8,112,173,34,111,80,41,70,134,102,187,221,126,225,
194,133,111,127,251,219,210,125,3,146,23,236,154,186,221,238,59,238,184,227,99,31,251,152,92,214,28,73,231,152,37,168,120,102,227,20,12,162,195,135,15,131,41,143,147,201,184,172,200,200,36,159,161,113,
45,169,223,140,248,176,160,150,26,20,232,71,177,146,205,100,50,52,32,199,82,132,146,140,100,178,203,190,43,56,182,137,68,226,212,169,83,123,247,238,157,153,153,145,180,7,213,241,35,241,3,4,255,150,150,
150,218,218,218,230,230,102,0,238,216,110,101,95,78,122,215,162,31,40,85,112,75,74,74,186,187,187,1,113,200,251,87,114,18,240,185,126,191,31,0,78,34,145,184,238,186,235,14,29,58,196,45,159,17,167,185,
185,89,73,212,75,53,8,28,246,216,216,24,236,231,217,110,13,135,195,39,78,156,224,104,168,105,89,128,176,75,95,221,254,254,254,29,59,118,224,205,233,188,204,41,92,118,95,149,156,189,44,109,23,22,22,206,
156,57,83,83,83,211,218,218,74,109,0,101,239,139,5,137,113,54,106,26,91,226,212,18,6,52,195,215,204,204,204,161,67,135,104,242,169,148,73,36,29,51,159,102,0,206,195,242,242,178,67,197,56,128,217,75,75,
75,149,149,149,244,152,192,89,70,29,129,69,41,171,24,203,110,155,250,87,82,86,61,30,79,44,22,3,174,159,111,255,1,196,97,74,67,229,114,57,106,42,154,95,18,214,112,139,139,139,28,96,181,220,45,209,26,138,
197,98,104,32,228,219,24,153,73,97,234,87,66,234,104,170,32,91,111,109,109,189,120,241,98,62,156,135,69,52,12,253,76,199,44,245,93,8,73,115,218,16,76,50,74,38,153,251,89,109,109,45,70,153,37,164,206,184,
140,83,87,93,93,189,115,231,78,175,215,75,113,81,21,232,45,225,29,133,57,152,171,159,15,12,158,37,18,9,9,110,40,117,14,190,158,74,165,254,234,175,254,42,149,74,65,162,154,183,49,238,249,13,27,54,220,127,
255,253,119,220,113,7,110,78,197,93,67,58,179,178,178,82,93,93,93,95,95,159,175,240,76,165,82,7,14,28,192,27,66,167,133,251,132,164,3,226,65,7,28,250,234,154,139,1,104,251,196,196,4,155,49,64,15,101,87,
16,219,12,193,37,2,122,192,208,221,110,183,199,227,145,123,243,91,111,189,245,243,159,255,60,151,203,53,55,55,75,52,0,241,148,78,43,32,177,53,55,55,55,54,54,214,213,213,209,206,3,9,175,154,90,42,208,227,
149,166,83,4,100,20,115,159,50,64,18,233,194,82,191,245,214,91,171,171,171,231,230,230,150,150,150,160,88,132,149,128,74,148,177,85,22,136,56,165,163,163,163,152,49,65,211,222,102,179,13,15,15,159,59,
119,206,82,189,68,70,94,220,101,248,105,127,127,63,186,14,102,238,105,185,32,77,98,21,254,59,57,57,25,14,135,155,155,155,145,159,73,39,42,60,124,62,31,214,24,208,69,204,160,22,70,51,20,238,52,56,56,56,
56,56,136,238,23,11,98,197,226,87,158,147,50,136,17,242,125,119,146,80,254,6,4,137,130,193,160,236,7,50,3,7,200,45,231,56,153,68,91,46,17,149,86,75,15,161,2,152,78,125,125,61,92,77,45,41,128,150,132,104,
100,214,124,29,86,231,38,216,194,162,181,184,184,120,120,120,152,1,218,180,134,161,112,23,27,50,242,50,163,249,134,123,181,162,162,162,182,182,118,102,102,38,223,68,56,238,198,92,46,183,176,176,160,246,
91,78,178,240,91,200,33,96,116,213,145,28,145,81,164,198,217,93,46,87,99,99,99,1,112,38,151,203,109,216,176,97,227,198,141,82,149,201,233,116,194,216,69,17,57,229,80,153,185,184,37,61,64,221,252,20,14,
164,31,185,236,10,50,32,34,137,254,251,191,255,251,162,162,162,246,246,118,58,78,33,233,219,189,123,247,125,247,221,135,215,229,84,46,207,36,234,83,20,46,5,150,80,44,22,131,248,14,135,86,16,98,20,189,
68,14,110,200,21,187,176,176,32,113,127,89,129,53,53,53,77,79,79,195,135,97,126,126,94,41,159,96,3,198,154,145,120,75,38,147,129,249,44,230,167,42,42,42,176,181,111,219,182,109,211,166,77,169,84,170,166,
166,198,239,247,163,114,69,90,144,205,102,27,27,27,155,155,155,155,154,154,170,171,171,209,103,6,26,11,132,36,95,55,242,178,60,28,66,4,38,126,37,153,172,124,19,128,87,72,173,48,66,217,208,208,224,112,
56,226,241,248,208,208,208,248,248,120,67,67,3,103,169,169,145,196,58,123,124,124,28,67,70,144,183,181,217,108,189,189,189,144,151,145,161,86,234,185,227,163,57,194,199,199,133,11,23,182,109,219,38,149,
152,148,95,184,233,201,39,243,104,73,206,187,112,225,194,232,232,232,218,181,107,17,103,228,13,216,220,220,156,78,167,65,157,10,6,131,5,56,27,230,35,30,143,131,199,77,82,32,196,73,112,65,45,43,36,243,
205,165,11,129,205,102,115,40,94,81,105,105,41,52,3,229,201,98,140,70,133,53,51,51,99,19,54,125,102,183,205,18,143,150,143,217,217,217,155,110,186,233,224,193,131,166,21,8,102,222,152,62,155,4,237,76,
38,67,189,18,249,13,169,81,192,63,228,180,136,138,62,184,57,225,221,64,60,196,188,33,89,64,40,49,48,130,224,120,19,236,40,84,35,147,106,144,18,37,64,250,32,223,74,126,41,201,226,144,95,28,59,124,93,93,
29,140,145,212,133,44,41,41,105,107,107,43,192,140,46,43,43,187,238,186,235,170,170,170,36,139,3,178,21,152,33,50,197,101,204,205,76,46,3,9,241,155,247,63,60,106,37,163,78,198,65,96,11,63,249,201,79,166,
167,167,43,43,43,217,151,14,6,131,31,253,232,71,111,191,253,118,159,207,199,68,76,58,21,224,72,112,207,148,148,148,160,41,159,175,117,62,50,50,114,232,208,33,204,236,44,47,47,187,221,110,187,221,142,158,
143,101,116,150,146,240,108,12,0,40,179,172,171,48,6,53,55,55,23,143,199,205,218,11,141,10,196,104,102,211,114,2,43,22,139,77,79,79,51,179,190,254,250,235,15,29,58,132,194,31,228,1,216,12,54,55,55,35,
82,35,46,51,37,2,170,139,210,202,150,199,162,222,236,193,200,126,181,164,99,147,102,46,127,170,12,76,165,75,17,212,235,113,141,42,43,43,187,186,186,48,230,35,73,95,82,33,40,26,141,242,6,79,38,147,217,
108,246,212,169,83,208,174,161,171,161,132,146,229,40,144,98,128,216,108,182,243,231,207,111,223,190,93,230,10,236,183,231,67,222,10,120,55,199,227,241,195,135,15,215,215,215,131,227,204,0,141,201,213,
76,38,19,12,6,57,186,101,50,61,204,196,25,138,228,230,97,35,63,3,247,28,2,129,151,157,33,164,139,216,187,90,28,252,165,170,170,42,69,100,81,34,203,80,41,139,197,98,20,138,85,222,186,87,146,65,67,252,247,
131,31,252,224,190,125,251,136,212,240,215,90,91,91,17,160,205,232,76,48,23,173,79,214,68,224,18,89,98,5,74,252,151,151,176,163,163,131,102,63,133,217,117,249,60,203,81,197,32,201,13,133,66,195,195,195,
220,207,213,111,162,39,43,167,206,20,164,160,216,208,4,245,64,182,163,36,177,82,96,88,187,118,45,101,143,148,0,130,228,62,99,167,193,81,97,77,43,83,12,51,196,75,112,141,223,72,222,207,170,144,100,127,
195,231,243,1,79,144,125,57,98,208,251,247,239,223,183,111,31,239,165,247,191,255,253,187,118,237,218,186,117,43,32,11,233,73,241,158,105,87,135,3,33,143,100,187,124,143,209,209,209,227,199,143,35,244,
112,78,183,172,172,12,19,58,106,142,134,60,72,147,74,8,252,77,162,219,38,183,135,237,110,181,102,208,102,80,86,56,178,96,231,137,77,167,211,161,80,232,170,171,174,242,251,253,157,157,157,152,46,3,123,
135,165,189,194,253,145,102,182,181,181,77,79,79,35,210,89,250,55,218,242,56,129,73,65,81,4,125,220,2,102,17,140,76,72,109,222,229,229,229,200,21,242,137,13,200,21,24,141,70,23,22,22,56,200,55,53,53,117,
244,232,81,0,35,76,149,100,174,45,109,1,112,108,42,131,30,28,28,52,193,28,181,32,37,209,168,64,19,133,63,133,165,223,218,181,107,129,50,121,189,94,170,24,162,138,202,103,57,166,240,180,177,177,49,78,147,
41,220,82,118,224,208,28,230,164,62,185,137,242,158,37,184,241,199,166,139,34,0,150,150,150,38,18,9,115,114,65,110,164,200,191,16,113,232,11,32,17,238,203,106,197,113,202,224,250,235,175,63,120,240,32,
63,17,143,77,155,54,73,10,135,132,108,216,12,81,83,182,64,247,84,76,71,41,103,201,237,45,41,41,161,213,88,97,9,14,51,61,81,95,10,144,116,69,69,5,70,114,44,247,109,108,66,242,128,149,218,131,77,24,237,
144,66,131,0,141,177,67,211,8,170,177,177,145,5,154,42,29,100,209,141,105,230,21,227,129,195,102,95,69,233,48,168,12,26,185,179,137,90,154,183,7,37,144,16,145,49,139,133,200,50,54,54,246,159,255,249,159,
64,84,111,190,249,230,93,187,118,33,201,37,81,76,137,213,241,204,160,249,230,245,122,165,138,147,205,240,45,59,119,238,220,208,208,16,186,115,24,6,97,175,95,217,190,144,7,41,133,41,164,128,42,73,202,166,
120,30,56,27,16,12,202,87,38,66,20,80,106,36,201,54,189,124,210,212,212,212,216,216,8,180,125,108,108,12,167,174,252,157,7,119,17,149,166,36,147,201,134,134,134,138,138,10,16,171,204,27,205,114,148,76,
6,47,168,29,32,20,210,155,88,138,112,82,14,84,230,167,14,135,35,16,8,0,134,230,116,177,164,190,209,146,53,149,74,1,217,0,211,102,106,106,234,216,177,99,210,245,149,171,78,10,141,50,212,72,124,86,14,175,
247,246,246,110,220,184,81,110,6,108,184,153,163,188,50,167,182,164,109,80,115,162,187,187,123,96,96,160,179,179,115,235,214,173,88,177,101,101,101,161,80,72,234,5,169,169,84,134,187,72,36,50,57,57,169,
202,95,203,116,27,243,204,156,172,150,201,22,90,32,116,30,144,162,225,14,201,220,66,190,102,185,152,228,149,40,46,46,38,24,77,34,167,154,184,183,52,252,86,82,50,136,110,187,118,237,58,121,242,36,182,101,
252,180,163,163,67,33,0,242,122,144,20,200,148,25,148,114,211,215,0,183,7,243,32,121,217,208,46,83,58,94,150,240,177,37,195,65,237,147,248,136,198,198,198,254,254,126,19,13,196,228,161,44,253,88,78,74,
186,155,98,221,177,58,193,40,129,74,223,234,234,234,168,8,170,54,15,54,103,16,124,207,157,59,71,207,39,217,129,193,229,150,86,229,42,131,86,77,78,246,103,242,17,239,248,220,237,118,131,123,79,221,28,224,
176,63,252,225,15,119,236,216,241,254,247,191,191,189,189,157,147,93,132,62,229,62,33,201,227,72,192,189,94,175,172,193,205,203,209,221,221,77,119,99,132,99,84,15,40,165,137,54,200,196,57,95,219,83,206,
52,43,203,49,0,20,50,125,182,212,212,5,37,95,14,7,203,53,6,21,92,124,119,130,108,82,244,46,30,143,195,95,24,169,46,244,136,37,119,62,149,74,193,8,170,188,188,124,102,102,6,124,240,2,45,122,21,164,104,
169,199,116,85,94,92,228,206,234,202,202,5,16,10,133,152,204,226,252,32,154,32,235,7,85,9,66,11,184,82,99,99,99,151,46,93,130,90,14,24,80,50,232,75,189,108,70,76,51,125,198,67,5,104,233,83,165,34,117,
1,75,120,75,42,240,252,252,252,254,253,251,51,153,12,198,140,215,172,89,83,120,104,16,64,196,220,220,28,24,92,16,102,184,236,168,33,178,13,230,163,166,57,53,210,231,247,56,160,50,58,83,173,81,169,169,
202,3,146,140,58,128,209,170,168,151,140,102,203,24,141,243,8,24,142,179,39,219,183,111,63,115,230,12,152,209,27,55,110,100,155,69,169,221,75,112,153,218,84,104,73,171,2,95,101,223,102,162,71,20,219,12,
208,166,166,168,25,115,101,135,157,84,249,64,32,16,143,199,103,103,103,213,37,137,68,34,228,213,203,233,88,57,66,146,15,131,70,132,34,73,3,159,94,89,89,41,9,12,74,120,94,102,127,248,147,163,71,143,222,
122,235,173,146,51,142,247,103,193,101,19,214,139,166,1,32,190,157,50,208,177,196,160,165,76,26,197,204,16,16,143,31,63,254,232,163,143,122,189,94,100,148,76,153,81,40,32,128,42,54,18,66,45,50,98,5,194,
200,171,182,188,188,124,236,216,49,184,217,242,207,129,65,51,88,19,44,146,176,134,233,85,111,202,179,72,223,222,249,249,249,241,241,113,34,170,42,151,87,74,141,203,203,203,137,68,194,100,19,33,65,67,211,
15,64,10,193,110,211,197,24,98,155,108,190,1,0,41,47,47,7,119,24,169,9,250,31,8,136,182,130,214,116,114,4,84,90,110,203,24,141,35,55,47,40,54,54,28,158,219,237,118,58,157,40,22,229,236,50,91,68,144,213,
71,52,56,119,238,28,248,151,64,213,144,216,165,211,233,68,34,33,225,90,254,62,225,56,203,73,119,110,12,248,169,12,205,178,58,148,116,198,124,138,20,38,106,81,92,92,124,246,236,217,239,124,231,59,247,222,
123,239,53,215,92,99,242,172,100,160,88,88,88,224,87,224,235,84,197,40,32,98,229,116,58,45,25,89,160,21,146,247,253,110,190,245,205,111,126,147,109,13,82,172,217,31,147,169,40,163,59,59,239,80,209,182,
20,44,150,0,49,67,33,207,230,216,216,24,234,2,22,245,213,213,213,169,84,42,149,74,237,218,181,107,231,206,157,202,126,73,181,116,104,58,7,33,46,73,190,49,27,5,74,160,0,79,192,124,80,23,210,146,147,167,
242,181,165,165,37,22,41,234,179,128,206,207,206,206,226,118,98,164,8,135,195,106,42,47,159,196,115,62,87,133,149,149,149,190,190,62,100,22,78,167,179,181,181,85,65,156,178,131,36,239,115,118,50,171,170,
170,160,240,32,31,112,96,49,199,32,101,142,201,184,96,50,237,10,60,228,9,71,246,71,231,45,75,201,174,210,210,82,5,166,147,182,33,189,5,204,205,50,147,201,156,58,117,10,44,46,30,51,81,96,34,209,136,140,
28,79,151,7,41,95,177,132,110,240,89,169,84,106,114,114,146,92,154,241,241,113,120,250,240,253,25,236,164,30,47,82,31,94,122,217,75,192,102,60,58,58,26,12,6,45,103,52,20,26,198,144,132,61,27,245,43,62,
29,13,24,130,18,106,239,49,47,25,58,132,92,165,50,96,177,141,36,255,80,78,93,178,189,57,60,60,204,42,141,59,101,42,149,66,31,12,88,234,185,115,231,176,115,16,32,69,208,128,9,175,116,27,193,59,64,82,2,
47,90,114,112,49,151,4,0,93,101,208,156,196,83,207,165,218,137,252,19,25,205,101,156,133,198,225,222,189,123,91,91,91,101,26,36,115,166,249,249,121,88,214,74,46,54,158,75,249,17,128,81,28,123,150,228,
107,74,49,243,114,115,80,153,33,254,143,13,24,41,218,141,175,161,160,37,69,124,145,76,53,44,14,16,182,248,13,121,37,44,53,189,36,154,172,34,96,103,103,103,105,105,233,182,109,219,168,136,100,54,9,89,183,
2,211,128,84,136,153,62,155,172,67,194,139,0,221,164,137,3,210,135,124,194,167,220,223,50,153,12,6,234,149,192,160,194,163,215,172,89,115,233,210,37,190,3,230,113,36,150,173,248,9,188,87,165,48,163,156,
63,4,12,237,241,120,0,250,55,55,55,75,229,57,73,41,81,20,102,25,101,122,122,122,234,235,235,137,246,240,214,50,13,64,85,233,35,157,97,205,236,204,196,55,72,18,40,47,47,71,166,60,55,55,231,243,249,84,47,
136,233,179,37,135,151,171,139,214,206,102,50,130,190,235,201,147,39,233,38,195,30,29,119,38,74,56,209,163,82,234,165,168,237,220,18,222,97,23,8,190,1,132,152,17,137,112,120,80,218,148,147,135,220,176,
113,235,130,110,200,46,2,43,113,151,203,117,234,212,41,218,31,155,217,46,14,24,223,133,55,5,2,25,32,65,183,219,13,60,208,233,116,214,215,215,71,163,81,137,29,171,124,92,189,179,108,63,96,171,67,25,205,
239,194,19,37,247,24,58,204,5,2,129,217,217,89,82,131,236,118,123,52,26,157,153,153,97,78,208,219,219,203,70,43,144,70,57,117,12,160,18,47,66,173,9,227,23,74,46,195,124,156,56,113,226,246,219,111,151,
179,209,10,186,101,120,81,42,67,230,221,170,114,35,198,61,200,131,60,248,224,131,247,220,115,207,183,190,245,45,218,241,32,176,194,109,64,233,42,51,31,82,224,70,48,24,228,141,204,17,202,229,229,101,12,
61,201,163,157,158,158,70,117,165,6,71,29,210,161,139,161,65,86,46,16,109,201,229,114,24,67,80,170,17,78,167,147,42,77,146,206,33,197,16,108,134,245,150,169,214,159,205,102,49,142,73,136,195,146,194,193,
157,128,210,136,114,170,208,242,175,36,250,188,176,176,144,205,102,67,161,144,50,73,177,68,162,213,36,33,11,67,203,113,59,190,18,8,4,162,209,40,102,210,178,217,108,52,26,149,235,155,40,179,90,28,12,88,
150,200,59,68,105,167,166,166,154,154,154,136,6,200,93,193,28,57,145,1,8,223,226,226,197,139,93,93,93,92,19,52,146,96,199,92,154,46,243,128,233,40,166,92,145,242,225,27,96,92,224,182,44,41,41,233,233,
233,57,117,234,212,199,63,254,113,165,254,44,119,80,51,47,230,184,32,22,6,250,13,234,186,68,163,209,190,190,62,14,106,75,76,223,228,210,89,102,148,201,100,18,58,51,170,203,164,212,102,146,201,228,133,
11,23,160,194,131,195,14,135,195,240,130,194,13,57,55,55,135,177,105,137,219,200,97,13,86,168,252,166,168,24,138,139,139,239,191,255,254,217,217,217,170,170,42,121,77,89,175,72,57,11,75,50,37,201,224,
56,84,204,10,129,208,153,111,67,229,14,42,43,6,10,36,113,244,92,149,101,166,42,75,123,123,123,52,26,37,121,127,121,121,25,184,229,202,202,202,204,204,76,95,95,159,12,148,139,139,139,32,59,73,86,213,226,
226,34,5,223,225,89,5,100,95,146,88,44,97,104,224,117,102,46,108,70,103,245,176,28,63,86,150,11,56,9,120,60,247,220,115,47,189,244,210,223,254,237,223,126,234,83,159,194,82,180,212,168,194,237,134,116,
132,163,185,38,172,196,213,5,134,2,36,238,112,50,179,217,44,61,175,149,3,139,195,212,68,70,135,23,14,96,216,211,136,64,49,78,73,66,152,219,237,6,82,70,34,151,148,205,181,156,151,11,135,195,50,133,28,29,
29,29,29,29,133,83,111,115,115,179,121,54,77,77,84,162,207,128,23,37,160,172,254,138,228,21,148,243,232,68,43,172,153,130,21,138,106,50,51,51,131,38,128,233,4,92,192,146,188,169,169,9,165,205,212,212,
84,225,9,81,147,218,44,187,246,148,83,112,56,28,32,108,128,158,104,19,110,58,146,92,168,228,128,121,31,226,198,24,29,29,93,179,102,13,104,148,242,151,121,147,152,211,234,8,34,133,67,51,239,88,140,20,43,
241,172,225,225,225,238,238,110,53,207,102,249,144,158,106,44,137,150,150,150,6,7,7,223,126,251,237,143,124,228,35,48,124,66,234,52,59,59,59,60,60,76,241,44,41,131,73,69,55,73,167,99,196,231,201,1,215,
21,202,127,76,27,77,38,64,50,153,60,113,226,4,238,46,204,37,69,34,17,84,247,252,80,160,94,116,72,32,88,196,249,91,156,97,222,159,0,232,240,69,120,210,100,218,97,217,178,54,99,10,29,209,228,143,160,145,
157,72,36,36,231,85,85,39,108,12,32,24,81,201,158,148,112,116,143,185,201,153,221,96,236,220,205,205,205,80,106,94,90,90,66,108,197,21,71,102,141,40,129,136,70,91,78,166,189,16,72,96,156,5,60,194,137,
48,76,26,83,202,67,194,244,243,243,243,145,72,132,238,180,12,211,102,207,48,95,212,182,60,147,210,112,22,237,107,188,79,44,22,251,135,127,248,135,95,253,234,87,143,62,250,40,237,211,84,62,46,43,18,212,
187,4,184,164,166,10,89,43,185,92,206,235,245,166,82,41,96,18,43,43,43,100,127,153,242,255,14,53,103,137,175,13,59,6,94,33,233,128,37,103,145,153,207,98,22,153,88,140,194,112,109,121,140,108,209,64,131,
162,32,214,211,213,87,95,77,153,77,147,76,163,108,55,153,170,3,207,50,163,51,142,13,243,87,20,24,242,120,60,114,158,85,230,221,82,100,150,146,102,150,216,180,165,32,148,212,97,8,133,66,227,227,227,62,
159,111,110,110,206,116,92,231,109,76,150,168,116,246,98,86,194,85,85,82,82,2,61,160,169,169,169,116,58,221,210,210,2,93,30,19,45,225,189,39,65,124,190,216,215,215,119,221,117,215,169,214,4,4,36,153,186,
74,38,34,179,39,53,233,32,233,1,8,112,132,65,148,94,204,237,183,223,126,234,212,169,72,36,2,254,178,57,124,204,115,200,136,128,239,178,176,176,112,234,212,169,193,193,65,220,183,39,78,156,216,186,117,
43,196,97,38,39,39,103,103,103,149,161,23,144,7,102,202,230,52,10,197,163,161,139,196,70,37,108,73,85,70,73,52,172,183,183,151,24,37,251,66,40,37,101,135,153,137,139,220,200,25,98,40,85,12,48,151,137,
139,244,18,147,186,140,87,40,9,79,122,79,89,89,25,153,124,184,53,252,126,63,138,69,85,228,169,171,137,21,46,219,128,18,223,96,116,54,81,44,60,90,90,90,38,38,38,114,185,28,236,78,86,87,87,7,7,7,193,174,
163,154,132,164,139,16,227,82,220,92,54,253,16,61,210,233,52,114,115,115,52,12,71,120,230,204,153,235,174,187,46,95,166,172,128,14,25,151,45,127,153,217,9,67,31,27,102,220,78,206,156,57,243,242,203,47,
43,127,75,246,249,229,173,33,251,64,210,131,6,80,155,236,60,251,253,254,217,217,89,156,141,84,42,37,157,31,222,3,188,200,145,33,214,32,96,107,35,192,19,88,161,94,148,28,166,144,205,22,234,19,90,70,103,
5,68,36,147,201,190,190,62,176,187,165,242,44,85,70,217,233,182,148,76,162,214,40,86,33,6,198,84,192,197,132,37,71,10,241,224,164,131,218,72,40,203,43,47,0,110,188,124,161,57,31,100,9,133,198,112,56,92,
94,94,190,97,195,134,161,161,33,110,108,50,211,151,205,95,101,246,140,239,194,243,176,178,178,130,41,187,162,162,34,140,216,174,95,191,158,200,172,162,88,41,158,47,43,101,135,195,145,72,36,38,38,38,160,
66,128,180,69,142,84,40,232,25,74,2,5,70,179,144,253,73,118,135,154,195,196,215,124,240,193,7,187,187,187,223,255,254,247,43,95,43,229,90,0,46,7,170,171,139,23,47,78,76,76,160,212,69,42,58,48,48,208,216,
216,136,247,196,176,162,205,112,26,164,68,39,155,129,202,133,15,71,5,101,84,25,122,18,137,4,58,168,242,11,46,47,47,159,58,117,138,65,31,170,196,64,201,76,53,21,180,224,217,172,150,53,1,73,17,100,136,74,
232,169,0,137,211,148,129,87,15,76,82,160,202,129,134,151,180,190,116,187,221,217,108,22,189,44,19,186,1,227,77,138,220,43,102,11,177,35,57,253,161,198,64,160,112,11,161,237,100,50,57,58,58,154,78,167,
137,65,75,75,70,54,204,41,234,143,203,74,2,130,100,67,75,155,61,75,9,236,55,223,124,243,154,107,174,49,123,128,102,116,206,7,73,155,177,91,138,99,80,65,159,121,180,219,237,254,202,87,190,34,203,95,185,
155,114,122,128,13,3,57,82,128,247,132,111,39,34,45,234,164,202,202,202,68,34,177,180,180,148,76,38,85,64,120,15,196,1,1,76,126,0,78,43,132,113,37,140,141,15,166,32,55,238,40,250,96,177,115,45,193,104,
115,34,131,173,200,222,222,222,222,222,94,53,35,95,84,84,116,221,117,215,73,25,104,151,203,197,206,164,148,0,103,213,192,211,154,78,167,113,10,36,118,44,3,16,151,41,229,81,212,220,20,169,169,150,181,252,
21,202,12,202,223,12,6,131,131,131,131,16,157,8,135,195,169,84,74,65,174,92,238,182,119,76,208,105,76,197,48,141,255,58,28,142,154,154,26,252,33,252,98,6,7,7,91,90,90,164,139,32,3,171,73,213,160,7,168,
221,110,31,27,27,171,169,169,65,96,149,19,128,108,199,83,108,196,178,251,71,52,131,193,200,18,136,7,90,135,175,22,10,133,32,84,162,184,213,114,85,32,139,159,156,156,28,27,27,75,36,18,114,153,225,180,160,
45,70,108,77,1,68,72,111,101,250,47,201,63,146,5,49,62,62,190,180,180,212,208,208,32,193,104,180,1,37,213,26,58,197,233,116,26,103,9,95,7,23,34,22,139,169,155,147,183,171,52,10,193,249,81,250,159,224,
87,129,203,33,165,215,164,57,178,101,246,96,185,210,170,170,170,16,157,109,239,88,146,227,253,37,150,141,192,173,224,14,178,77,24,148,101,250,44,247,15,75,199,6,126,226,220,220,28,84,129,82,169,212,232,
232,40,220,200,176,180,176,146,129,43,50,254,146,206,65,133,35,197,223,197,3,125,206,2,143,137,137,9,228,236,38,15,218,12,217,5,32,105,190,46,103,220,8,185,96,211,197,251,252,251,191,255,187,215,235,53,
181,164,37,123,152,147,144,18,3,144,202,171,56,96,153,91,84,87,87,79,77,77,97,227,231,105,87,97,211,161,106,13,10,110,240,88,85,242,75,207,105,122,200,162,46,192,130,88,88,88,32,236,43,107,118,254,27,
141,70,99,177,88,127,127,63,134,77,212,8,201,230,205,155,25,160,113,58,96,117,202,115,167,164,147,149,149,28,143,7,151,92,74,85,209,168,5,230,146,166,78,66,62,193,170,194,185,115,190,123,41,155,205,86,
86,86,122,60,30,220,51,32,171,82,152,92,14,49,179,186,103,44,150,170,73,60,21,232,240,86,86,86,178,160,25,24,24,8,6,131,64,102,153,242,80,64,142,216,171,242,117,134,18,55,121,248,108,113,40,182,56,185,
46,50,136,224,134,55,21,78,212,57,1,166,196,176,181,178,178,178,117,235,214,108,54,43,5,122,24,163,17,154,161,170,14,221,9,89,159,201,127,39,39,39,235,235,235,85,219,25,159,8,154,157,210,100,96,215,139,
200,210,200,200,8,146,163,100,50,89,85,85,69,195,23,44,176,84,42,5,248,171,168,168,232,252,249,243,20,147,2,62,72,239,62,180,127,37,190,193,206,18,255,69,138,132,77,87,14,115,33,233,169,172,172,228,128,
53,73,111,138,241,118,217,33,99,24,111,42,196,223,229,114,33,15,144,196,118,100,57,104,38,201,69,43,153,115,114,145,240,191,210,138,76,241,64,210,233,244,197,139,23,135,134,134,108,54,219,220,220,220,
236,236,44,161,18,148,65,100,226,99,239,167,130,190,178,227,97,90,205,52,69,42,216,21,142,209,219,183,111,143,197,98,200,47,37,139,87,197,229,43,201,163,233,15,41,13,127,57,125,179,105,211,166,206,206,
78,41,232,108,57,82,207,77,151,48,180,156,216,144,186,137,92,186,62,159,111,98,98,130,138,196,166,200,251,187,106,118,38,243,215,227,241,164,82,41,112,126,249,190,220,91,16,38,24,217,161,242,140,124,141,
52,108,201,246,71,33,57,59,59,11,166,26,143,91,225,27,152,200,144,39,17,214,232,216,135,77,146,3,97,29,41,32,32,35,157,138,158,168,12,104,37,89,56,47,54,39,17,44,71,0,44,201,121,88,175,205,205,205,180,
94,244,249,124,229,229,229,156,205,229,87,163,205,138,195,225,64,113,199,165,35,29,11,87,86,86,174,189,246,218,190,190,62,153,103,97,251,173,175,175,199,88,32,126,95,202,77,152,246,46,30,143,135,125,66,
41,50,201,205,12,191,134,182,15,241,101,164,204,138,185,149,207,28,135,42,201,106,55,146,247,39,190,96,54,155,141,199,227,36,201,224,238,146,226,194,242,30,195,226,65,7,91,105,92,216,132,163,40,7,41,149,
211,205,228,228,36,244,248,193,51,65,26,203,63,65,241,135,24,221,211,211,19,14,135,193,187,32,177,146,55,24,120,190,60,117,210,189,155,81,9,95,13,132,63,38,200,172,231,98,177,152,215,235,149,248,190,76,
96,37,66,34,165,195,229,163,170,170,170,185,185,89,129,248,20,135,1,44,35,175,47,118,86,206,166,19,6,145,115,252,114,111,227,189,99,38,206,203,203,203,151,46,93,26,30,30,198,85,155,157,157,5,126,42,141,
196,76,126,49,8,124,146,75,231,112,56,162,209,104,38,147,137,197,98,168,244,145,233,23,118,98,228,227,240,225,195,187,119,239,118,56,28,62,159,47,30,143,131,95,104,226,21,102,195,208,140,215,54,97,175,
46,1,79,54,228,190,252,229,47,79,76,76,140,143,143,7,131,65,185,41,42,29,124,72,144,115,190,90,206,191,160,190,1,215,80,222,23,64,132,120,167,91,182,130,29,74,139,142,228,1,12,10,130,28,35,25,17,88,178,
50,140,226,191,229,229,229,184,165,25,104,248,73,75,75,75,232,110,17,140,183,156,240,217,188,121,51,183,1,101,115,133,100,89,82,184,45,73,120,146,138,136,251,65,2,26,4,236,8,46,91,250,117,73,206,22,154,
197,146,134,104,62,76,124,22,233,39,74,138,134,134,6,80,86,128,27,52,54,54,130,25,141,226,0,119,2,179,27,5,28,201,175,182,188,188,220,212,212,212,223,223,47,171,84,168,124,44,46,46,66,94,138,177,152,44,
96,53,230,19,12,6,107,107,107,37,20,32,51,26,137,53,225,36,100,50,25,152,103,155,19,252,150,187,20,160,6,75,6,130,12,1,72,169,112,135,51,121,148,244,77,249,156,23,20,30,213,29,29,29,196,245,240,4,76,12,
169,42,73,253,13,167,211,233,114,185,86,86,86,198,199,199,201,132,227,36,24,213,153,217,52,70,59,40,18,137,160,26,165,71,12,99,52,174,157,12,205,82,149,23,247,2,182,40,244,202,136,227,43,94,205,242,242,
178,215,235,101,92,86,28,109,153,149,75,28,12,255,86,85,85,181,180,180,228,211,243,67,40,52,231,164,209,84,160,41,51,7,241,37,231,71,6,107,105,146,191,158,101,183,0,0,32,0,73,68,65,84,203,31,13,14,14,
66,151,121,126,126,30,188,58,146,208,65,247,230,204,39,175,2,187,208,139,139,139,201,100,18,150,219,232,63,1,203,98,153,94,96,250,206,124,28,61,122,148,113,182,188,188,188,182,182,54,157,78,199,227,241,
249,249,249,194,225,88,126,28,91,124,178,141,47,163,115,46,151,251,198,55,190,113,221,117,215,13,14,14,194,134,105,120,120,216,239,247,195,40,157,145,19,195,177,72,255,37,126,64,68,78,182,254,36,62,22,
143,199,145,112,48,112,189,7,220,112,56,154,154,154,28,166,244,4,222,174,166,166,102,122,122,154,5,32,16,25,100,239,170,95,71,218,41,212,130,200,167,193,191,177,88,140,58,79,136,179,202,150,130,205,34,
137,111,152,2,208,64,84,44,135,191,229,43,50,181,65,34,67,90,46,69,73,88,137,147,65,108,70,103,252,139,241,119,153,200,152,91,139,218,102,112,93,121,167,213,214,214,70,163,81,10,7,67,45,115,118,118,22,
66,245,188,169,148,177,55,171,66,204,197,194,166,12,127,98,174,224,197,197,197,190,190,190,181,107,215,122,189,94,73,251,37,57,193,110,183,215,215,215,75,183,111,243,248,21,155,10,89,51,70,13,231,230,
230,16,77,242,217,229,240,9,29,26,205,18,132,125,14,124,53,70,97,214,248,249,18,103,249,239,196,196,196,250,245,235,101,135,3,195,59,4,49,192,47,70,247,18,23,119,97,97,1,115,67,10,199,195,97,144,113,140,
227,153,154,154,130,125,181,28,11,144,143,112,56,172,66,179,212,87,65,36,154,159,159,79,165,82,168,60,204,17,86,6,104,112,173,204,104,40,81,38,242,217,249,98,107,107,43,204,148,77,241,113,9,61,75,27,57,
121,57,104,136,39,117,189,101,203,84,54,84,37,100,52,50,50,210,221,221,141,232,3,2,46,244,111,37,169,17,31,141,45,19,235,22,123,112,60,30,199,135,210,87,27,226,130,180,54,190,66,239,102,245,56,114,228,
200,150,45,91,100,227,17,174,99,48,144,132,179,115,1,142,29,127,36,241,13,73,130,206,229,114,141,141,141,95,248,194,23,42,43,43,193,237,195,153,4,164,227,241,120,130,193,32,100,85,248,182,136,81,18,127,
195,105,33,130,36,67,112,42,149,2,92,204,32,46,183,168,64,32,0,167,71,135,74,118,24,233,189,94,47,183,71,170,71,162,199,138,203,143,90,70,206,137,16,182,47,45,45,197,110,6,225,43,174,60,64,51,176,245,
53,117,12,110,188,241,70,211,135,80,74,80,202,83,105,25,157,77,133,101,252,52,147,201,96,123,87,86,88,18,232,200,231,152,32,99,183,106,154,89,34,36,156,146,103,118,214,212,212,116,233,210,37,57,73,72,
47,49,190,27,218,80,160,70,194,63,9,13,10,210,167,138,139,139,43,42,42,48,183,105,30,237,202,202,202,249,243,231,91,91,91,81,249,202,12,218,231,243,181,182,182,86,86,86,34,205,81,59,138,68,30,16,44,80,
254,203,242,2,226,244,114,234,218,210,124,18,58,56,150,48,209,220,220,220,175,127,253,235,205,155,55,195,165,219,148,84,55,19,103,243,95,52,15,166,167,167,97,191,141,37,14,216,74,78,252,75,174,66,50,153,
60,123,246,172,196,16,228,177,65,22,149,151,32,18,137,76,76,76,16,142,87,83,239,120,192,51,208,244,178,192,59,199,227,113,64,88,72,138,81,174,201,137,33,249,134,136,44,24,208,48,57,112,120,32,138,177,
199,219,210,210,226,247,251,165,110,114,190,24,173,74,105,213,111,96,102,167,82,102,198,89,121,26,39,38,38,78,158,60,25,14,135,33,191,147,203,229,32,253,65,20,27,91,29,176,11,136,62,51,192,97,245,146,
206,172,100,8,165,138,197,159,148,62,51,137,222,180,105,147,228,195,81,197,162,172,172,204,239,247,103,50,25,88,43,168,232,172,98,8,1,55,217,36,196,91,253,240,135,63,132,202,252,218,181,107,97,43,140,
239,8,251,133,161,161,33,175,215,139,155,139,128,187,148,162,148,250,77,74,74,9,210,46,0,27,8,202,17,111,108,110,110,198,123,230,114,57,135,101,95,2,81,31,251,33,243,86,92,93,104,57,210,34,136,228,104,
70,19,12,185,160,211,202,191,146,102,189,230,164,13,174,217,182,109,219,10,68,94,73,71,43,28,157,85,197,196,210,70,230,5,106,54,196,12,181,140,242,10,20,51,73,29,242,95,203,137,68,175,215,235,241,120,
164,164,170,212,41,199,103,77,77,77,97,149,83,36,129,149,145,20,35,173,173,173,69,103,198,242,49,56,56,152,78,167,33,199,5,174,69,40,20,170,169,169,65,1,1,192,167,188,188,188,178,178,82,106,192,203,0,
109,106,138,242,23,32,227,2,171,36,19,118,135,138,130,165,200,220,99,143,61,246,210,75,47,197,227,241,79,124,226,19,183,221,118,155,9,104,16,229,144,5,132,164,129,203,12,96,124,124,28,182,138,168,111,
148,189,180,172,9,18,137,196,201,147,39,9,79,203,169,92,73,157,118,187,221,152,75,28,29,29,181,228,41,242,9,129,11,165,126,142,112,60,53,53,69,179,2,78,61,168,47,171,224,14,132,48,236,157,148,244,83,172,
243,197,197,69,52,24,54,110,220,8,192,77,254,180,64,140,134,29,79,190,134,10,135,98,148,82,135,12,205,233,116,250,208,161,67,23,46,92,224,151,194,128,123,44,22,147,69,42,117,29,16,175,233,121,138,204,
140,35,118,178,50,144,244,1,89,73,95,33,0,141,199,241,227,199,31,124,240,65,69,88,150,173,66,156,4,143,199,83,86,86,182,176,176,0,54,155,57,91,40,65,106,142,86,228,114,185,187,238,186,235,174,187,238,
98,229,209,210,210,114,224,192,1,218,63,18,208,235,237,237,117,58,157,104,215,131,25,44,109,143,212,224,46,131,18,124,89,209,24,144,45,13,159,207,135,6,62,143,199,145,47,250,144,169,7,197,119,201,58,32,
207,156,153,53,51,154,76,38,51,62,62,190,176,176,32,71,69,120,190,120,6,77,250,90,81,81,209,246,237,219,55,111,222,188,121,243,230,27,110,184,225,170,171,174,146,174,87,249,210,228,43,204,166,177,140,
136,159,72,183,121,75,45,93,121,138,47,219,18,148,175,75,206,181,252,229,214,214,214,238,238,110,25,160,213,251,112,118,75,206,53,73,81,17,220,63,129,64,224,210,165,75,102,136,228,35,28,14,39,147,201,
27,110,184,161,166,166,166,166,166,134,115,225,212,251,134,202,48,90,100,150,97,58,31,6,34,199,88,85,54,4,55,47,117,36,79,61,245,212,147,79,62,121,240,224,65,18,3,14,30,60,152,47,125,150,49,90,114,90,
222,149,140,121,135,114,0,38,12,91,97,74,121,156,143,169,169,169,179,103,207,226,94,226,222,172,212,159,129,254,35,178,176,128,53,113,124,134,167,161,161,33,41,119,46,119,130,201,201,73,133,210,16,194,
54,241,13,37,214,14,119,18,94,110,211,168,201,110,183,175,91,183,14,213,52,183,144,43,9,97,64,168,242,153,78,16,184,51,193,141,229,229,229,254,254,254,158,158,30,128,147,184,232,216,128,145,147,154,187,
29,255,43,117,111,8,167,200,101,166,134,254,77,89,140,43,124,100,50,153,243,231,207,175,89,179,198,82,38,73,105,144,194,216,211,110,183,3,117,145,60,49,249,203,100,16,120,60,158,31,252,224,7,114,23,9,
6,131,27,54,108,232,239,239,247,251,253,55,223,124,51,252,206,17,106,81,201,205,205,205,57,157,78,208,207,233,117,192,137,1,121,215,35,133,229,120,42,206,27,42,164,64,32,32,143,103,121,121,217,161,134,
208,228,25,247,251,253,163,163,163,37,37,37,200,133,169,164,69,77,47,37,96,8,144,186,165,165,37,145,72,0,179,199,228,149,180,124,101,31,201,180,157,29,31,31,31,29,29,125,241,197,23,241,89,240,100,123,
223,251,222,119,213,85,87,109,221,186,21,150,7,255,223,241,90,186,65,115,0,132,52,41,51,228,229,83,215,45,60,220,149,143,153,87,86,86,214,216,216,8,74,141,229,91,33,223,145,243,144,178,57,198,162,187,
173,173,109,255,254,253,104,197,152,152,29,217,11,35,35,35,178,143,196,95,3,48,202,124,10,136,173,244,96,84,50,20,114,140,155,120,189,156,228,100,58,32,61,77,158,122,234,169,103,158,121,6,9,41,177,133,
226,226,226,201,201,201,238,238,238,77,155,54,89,246,3,169,223,100,234,211,171,51,54,60,60,12,133,32,121,144,178,100,30,30,30,62,125,250,52,85,126,164,155,140,217,51,64,163,6,39,223,18,214,224,43,195,
195,195,42,197,203,229,114,211,211,211,76,156,101,116,198,127,83,169,20,2,171,66,57,248,197,217,89,193,212,137,226,29,131,36,7,255,10,217,216,40,176,67,171,245,0,173,21,75,33,64,170,217,40,248,174,175,
175,175,167,167,135,131,63,108,167,227,167,193,96,16,213,158,10,23,42,67,68,30,205,65,24,83,26,48,159,82,252,159,132,68,159,58,117,10,222,96,50,58,115,166,65,70,109,38,164,148,148,147,68,6,165,108,151,
203,229,62,247,185,207,53,53,53,41,212,120,243,230,205,145,72,4,239,0,196,111,117,117,149,33,149,34,124,114,134,14,164,50,78,210,227,72,232,173,140,198,30,132,28,58,58,58,72,128,161,78,250,210,210,146,
195,18,207,98,190,205,139,199,25,110,41,55,37,21,190,1,208,224,122,84,86,86,86,86,86,98,58,121,126,126,30,145,58,30,143,131,25,74,26,150,106,75,42,125,165,209,209,209,225,225,225,183,222,122,11,159,85,
89,89,185,99,199,142,27,111,188,113,203,150,45,87,18,175,205,87,56,235,197,187,139,129,70,206,164,146,30,64,202,193,149,68,103,73,198,176,124,212,215,215,71,34,17,146,240,201,132,97,128,150,88,149,196,
244,165,142,18,154,183,51,51,51,150,49,186,184,184,184,174,174,206,239,247,219,237,246,195,135,15,111,217,178,165,185,185,89,201,230,169,90,1,205,64,182,239,164,14,56,181,70,137,36,168,83,135,224,75,65,
197,63,252,225,15,8,205,5,102,31,94,121,229,149,205,155,55,203,130,154,233,51,145,104,217,60,48,135,81,225,58,216,218,218,106,138,196,226,201,208,208,208,209,163,71,217,22,230,138,167,3,52,190,35,169,
117,123,246,236,185,112,225,194,71,63,250,81,242,20,21,184,193,84,122,100,100,68,182,64,103,102,102,32,41,39,165,7,205,190,19,176,11,179,73,136,247,71,40,7,7,192,116,62,173,171,171,107,111,111,39,96,194,
138,74,238,178,5,80,14,202,68,40,98,162,236,61,200,43,59,59,59,123,236,216,49,12,31,226,252,148,149,149,145,104,200,27,36,20,10,77,76,76,152,36,84,37,115,129,243,32,147,57,174,88,108,135,234,80,45,21,
250,41,13,68,133,31,249,56,125,250,244,93,119,221,165,178,102,21,157,165,176,6,95,167,60,8,126,138,129,26,212,82,232,13,126,227,27,223,176,236,72,93,115,205,53,231,206,157,179,164,66,19,47,194,0,51,222,
31,36,34,178,126,217,88,246,120,60,156,140,171,172,172,244,249,124,64,56,105,68,137,206,89,81,81,209,123,48,104,85,186,122,189,94,176,73,42,42,42,208,21,37,241,8,160,7,118,0,4,29,169,145,36,183,38,183,
219,237,114,185,32,122,11,169,173,229,229,229,72,36,66,117,21,201,241,54,135,247,152,179,196,227,241,55,223,124,115,239,222,189,132,95,186,186,186,110,186,233,166,214,214,214,45,91,182,108,217,178,229,
74,226,53,78,28,231,229,57,71,96,186,205,75,117,55,147,148,110,238,106,74,205,195,242,209,218,218,122,225,194,5,203,31,33,64,75,90,174,244,189,149,73,116,123,123,251,208,208,16,21,177,37,55,214,231,243,
145,96,94,84,84,116,230,204,153,88,44,182,115,231,78,19,94,71,209,199,169,19,78,64,97,128,130,70,83,36,11,155,163,83,88,106,61,61,61,118,187,253,173,183,222,250,217,207,126,214,211,211,147,47,46,243,191,
175,190,250,234,87,191,250,85,203,14,161,210,15,224,69,33,227,158,55,127,58,157,158,154,154,194,208,138,42,147,251,250,250,14,31,62,204,193,72,69,232,84,38,35,54,155,237,159,255,249,159,159,127,254,121,
155,205,182,115,231,206,142,142,14,19,119,230,243,72,36,66,126,113,54,155,29,28,28,196,90,82,30,146,210,103,79,146,7,148,14,53,67,179,252,111,89,89,153,220,11,131,193,96,91,91,155,220,87,240,233,108,255,
92,73,210,192,47,171,192,25,41,114,11,253,128,211,167,79,207,206,206,178,130,225,116,34,132,238,216,17,193,59,52,53,53,133,195,97,174,121,98,95,146,73,166,108,106,17,169,193,65,84,165,12,79,151,101,250,
76,76,18,233,173,108,68,207,207,207,143,141,141,85,87,87,23,214,131,150,49,154,29,41,196,65,16,78,72,225,197,31,254,244,167,63,181,204,229,129,173,109,216,176,193,114,16,95,161,55,164,171,41,41,96,233,
135,176,188,188,220,222,222,142,123,22,119,31,41,115,40,191,74,75,75,29,5,44,156,139,138,138,170,171,171,145,175,65,175,14,43,169,180,180,20,45,35,188,29,43,53,197,145,48,135,214,93,46,23,168,48,176,206,
157,155,155,67,26,50,55,55,103,162,159,200,240,205,115,132,247,143,199,227,251,246,237,219,183,111,31,247,246,247,189,239,125,91,183,110,221,242,206,163,64,188,198,161,202,113,41,166,132,4,85,77,145,226,
2,179,115,184,105,11,220,54,120,209,237,118,67,62,201,108,201,178,27,201,173,66,101,211,76,160,218,219,219,95,127,253,245,68,34,225,245,122,169,62,24,8,4,80,28,48,241,196,165,28,29,29,77,38,147,55,221,
116,19,229,46,241,38,21,21,21,80,216,49,5,122,152,53,131,98,152,15,73,40,42,42,186,112,225,194,55,191,249,205,183,222,122,11,145,75,78,94,152,94,203,120,192,238,62,20,10,169,14,161,140,203,82,160,67,42,
147,240,74,217,237,246,201,201,201,80,40,164,10,231,190,190,190,131,7,15,50,14,202,110,135,124,142,95,94,88,88,120,228,145,71,192,43,183,219,237,191,252,229,47,127,240,131,31,152,208,51,159,140,140,140,
96,145,140,142,142,134,195,97,74,208,73,223,100,181,205,72,254,128,164,60,202,111,45,33,233,249,249,121,191,223,143,51,182,97,195,134,250,250,122,14,122,176,151,131,24,97,169,110,124,217,24,109,78,60,
32,238,39,18,9,88,61,97,104,40,155,205,226,222,164,81,172,153,110,67,123,128,230,65,32,246,73,6,155,68,77,217,36,132,151,2,2,162,105,44,41,187,62,74,207,139,144,14,97,43,126,202,192,192,0,76,235,77,64,
67,70,106,198,104,36,148,96,73,33,93,85,81,226,206,59,239,124,223,251,222,167,16,33,9,116,160,171,108,70,103,37,9,137,115,139,68,152,4,95,174,67,72,244,1,176,150,229,17,213,211,8,36,58,84,35,72,197,148,
202,202,202,153,153,25,187,221,94,91,91,155,76,38,233,36,4,29,22,110,14,138,95,37,173,33,201,133,32,130,137,11,6,16,167,182,182,22,196,201,88,44,134,96,205,118,205,101,71,242,101,200,94,93,93,69,188,230,
42,185,241,198,27,187,186,186,182,108,217,210,210,210,114,227,141,55,90,90,131,179,55,194,73,113,206,94,23,32,120,152,101,53,59,12,151,189,97,160,68,106,210,209,164,222,49,227,145,138,83,120,14,173,244,
72,36,178,176,176,224,245,122,43,43,43,97,89,160,210,55,30,94,52,26,125,241,197,23,111,187,237,54,176,211,192,213,179,228,83,203,113,112,75,229,67,155,48,99,238,237,237,221,190,125,187,154,5,183,156,183,
86,81,123,207,158,61,15,61,244,208,101,9,118,230,22,37,9,112,179,179,179,153,76,6,56,15,142,246,224,193,131,61,61,61,188,124,114,178,81,34,114,248,208,222,222,222,159,254,244,167,211,211,211,252,220,222,
222,222,223,255,254,247,247,221,119,31,167,49,85,140,238,237,237,133,123,11,110,45,6,95,30,161,132,242,37,15,135,121,28,110,22,25,154,101,200,198,95,97,118,169,163,163,3,89,161,41,205,40,5,12,254,212,
24,109,62,199,228,8,223,217,239,247,7,2,1,94,172,212,59,143,112,56,140,1,16,137,135,96,47,137,70,163,188,136,74,220,92,206,43,242,42,196,98,49,74,250,113,207,200,215,77,81,232,156,12,205,12,193,39,79,
158,220,190,125,187,82,238,87,51,132,24,33,65,230,142,241,2,75,117,127,212,229,255,241,31,255,97,57,144,85,248,84,75,148,67,250,242,40,58,38,199,190,193,100,165,247,35,111,55,234,205,162,62,251,163,22,
7,67,103,60,30,143,68,34,77,77,77,140,23,213,213,213,3,3,3,96,171,224,59,3,154,80,167,207,4,106,77,201,5,73,44,147,12,51,176,88,2,129,128,223,239,111,107,107,195,108,75,56,28,158,158,158,142,70,163,104,
71,40,241,86,165,206,101,54,28,138,138,138,16,175,73,116,235,236,236,220,252,206,99,247,238,221,170,7,37,143,7,74,123,64,102,109,5,237,38,21,247,249,74,110,149,210,210,210,218,218,90,118,11,229,3,5,142,
4,58,100,84,146,36,135,206,206,206,125,251,246,101,50,25,200,30,153,65,153,137,18,169,90,47,189,244,210,135,62,244,161,173,91,183,50,209,38,39,135,145,130,116,122,115,96,71,234,228,34,231,186,249,230,
155,37,41,66,202,125,88,198,101,254,247,232,209,163,15,63,252,176,25,157,21,247,78,238,73,178,41,199,42,103,124,124,124,221,186,117,56,182,215,94,123,237,252,249,243,180,60,102,254,34,7,240,88,84,190,
242,202,43,47,191,252,50,16,60,228,254,56,230,39,159,124,242,238,187,239,198,176,143,74,165,139,139,139,247,237,219,119,230,204,25,152,167,48,177,149,122,35,220,93,164,90,186,12,217,146,212,193,182,33,
74,79,68,31,196,253,174,174,174,202,202,74,202,69,153,49,154,226,200,87,24,154,45,163,222,210,210,210,220,220,28,241,101,75,246,142,199,227,129,128,212,134,13,27,162,209,232,193,131,7,101,18,189,186,186,
90,85,85,181,188,188,12,73,41,37,224,142,239,194,161,54,252,21,10,110,234,195,72,34,7,174,154,101,123,16,40,173,28,33,145,63,66,74,87,81,81,97,162,28,208,233,198,3,113,153,11,216,50,58,175,174,174,126,
237,107,95,131,196,118,190,237,77,86,6,178,47,34,119,26,233,214,36,147,30,108,21,37,37,37,236,204,91,18,186,56,237,242,110,128,134,61,45,9,52,241,120,156,18,60,168,157,229,12,91,89,89,25,100,209,101,84,
50,5,239,101,18,45,241,41,197,34,50,243,163,149,149,21,100,133,45,45,45,51,51,51,71,142,28,177,4,4,56,25,41,243,23,203,252,26,213,104,111,111,111,79,79,207,51,207,60,131,235,177,105,211,166,45,91,182,
108,222,188,249,170,171,174,66,69,35,225,57,40,142,163,213,153,207,153,130,87,14,87,221,148,103,203,103,108,200,110,161,217,226,227,97,240,108,200,36,154,186,95,91,182,108,57,112,224,64,113,113,113,56,
28,6,100,196,40,96,217,119,181,219,237,13,13,13,147,147,147,118,187,125,219,182,109,202,201,69,69,85,41,6,45,85,168,160,102,137,244,231,238,187,239,38,79,72,77,3,43,223,63,51,76,239,219,183,47,30,143,
195,77,85,49,22,76,172,67,166,210,82,226,14,58,36,235,215,175,47,42,42,122,233,165,151,122,123,123,177,172,249,197,137,120,202,127,23,23,23,127,243,155,223,116,119,119,227,205,49,184,196,112,156,203,229,
254,241,31,255,241,71,63,250,145,76,156,29,14,199,196,196,196,215,191,254,245,211,167,79,131,63,174,144,13,53,72,197,83,42,127,1,23,2,113,153,141,95,54,102,241,149,157,78,167,211,233,236,236,236,132,85,
152,44,23,228,199,1,42,49,93,14,174,60,70,67,245,66,70,22,98,98,150,141,22,82,9,149,193,57,14,35,24,12,98,49,203,36,26,7,9,38,28,98,52,190,44,106,110,89,165,201,66,71,29,170,132,31,165,249,156,249,149,
135,135,135,215,175,95,207,209,24,57,127,139,160,44,231,188,77,153,127,70,234,182,182,182,207,127,254,243,5,202,14,19,12,84,251,10,3,180,73,199,68,128,118,185,92,106,134,200,210,123,5,77,84,228,34,14,
48,103,229,219,205,205,205,213,212,212,240,125,235,235,235,83,169,20,132,41,98,177,24,24,87,243,243,243,164,88,74,19,45,83,213,80,86,154,202,241,72,133,105,243,23,98,177,24,49,68,121,142,168,93,112,89,
70,14,125,148,229,200,80,81,81,209,185,115,231,122,122,122,120,131,53,53,53,93,117,213,85,215,94,123,237,159,253,217,159,53,55,55,167,82,41,151,203,5,72,206,229,114,65,198,33,223,166,10,82,138,186,114,
87,210,45,84,17,92,25,244,177,239,4,164,12,171,205,110,183,119,117,117,133,66,161,231,159,127,30,150,234,19,19,19,77,77,77,140,107,178,95,129,247,241,249,124,193,96,176,162,162,98,105,105,105,104,104,
40,153,76,94,127,253,245,232,253,170,238,188,196,49,228,184,29,84,108,16,154,237,118,251,223,252,205,223,92,184,112,129,153,172,233,76,42,231,107,164,150,38,159,31,63,126,252,166,155,110,82,89,51,99,153,
153,57,42,183,111,252,55,155,205,78,79,79,191,253,246,219,64,54,76,73,57,9,116,128,33,254,228,147,79,198,98,49,57,65,87,89,89,9,136,16,159,187,111,223,190,253,251,247,223,122,235,173,60,212,39,158,120,
226,199,63,254,49,250,7,184,177,97,212,36,99,177,10,205,18,73,103,135,80,78,64,200,110,33,246,188,242,242,242,242,242,242,174,174,46,52,6,212,198,204,179,10,0,218,102,88,143,219,254,196,135,10,13,114,
38,64,5,14,254,137,156,208,145,69,9,206,225,208,208,16,98,10,155,207,132,107,51,153,12,185,91,80,71,129,82,77,121,121,57,160,6,50,14,36,6,37,71,96,164,116,134,37,87,186,175,175,15,237,113,48,128,9,98,
228,131,59,216,6,7,7,137,239,255,215,127,253,215,133,53,184,229,62,161,96,13,179,95,133,166,31,101,196,33,63,39,47,25,249,36,230,216,17,143,208,225,112,216,63,249,201,79,154,176,3,207,32,230,143,225,114,
86,90,90,58,55,55,7,192,219,227,241,192,175,23,243,14,156,67,163,8,139,137,15,240,200,48,39,170,170,6,201,80,14,4,2,93,93,93,119,220,113,199,169,83,167,40,255,166,22,162,211,233,196,23,150,230,237,150,
1,218,231,243,153,67,49,106,239,138,199,227,23,47,94,124,243,205,55,127,250,211,159,190,252,242,203,193,96,176,165,165,5,159,27,143,199,147,201,36,42,80,179,12,68,220,148,186,104,150,10,100,234,21,136,
150,80,187,14,209,36,149,74,197,98,177,108,54,139,121,31,12,124,75,1,176,250,250,250,206,206,78,16,102,167,166,166,16,226,177,243,41,245,84,98,38,161,80,8,82,244,18,189,25,25,25,169,171,171,131,195,94,
62,227,103,12,235,207,206,206,66,56,148,148,143,95,252,226,23,63,249,201,79,148,108,158,194,160,165,167,137,180,158,162,188,103,89,89,217,77,55,221,100,105,148,99,50,160,17,22,9,201,201,76,240,141,55,
222,192,92,165,2,254,204,196,228,244,233,211,79,60,241,4,198,106,101,197,128,44,143,108,141,229,229,229,147,39,79,222,119,223,125,46,151,43,28,14,63,242,200,35,79,63,253,116,32,16,192,157,47,7,83,11,120,
6,153,94,139,171,249,31,232,10,212,215,215,111,221,186,85,18,147,21,179,158,207,57,23,122,217,142,116,190,7,190,59,1,110,37,96,32,103,178,229,235,195,195,195,100,248,202,11,141,2,206,237,118,3,249,4,209,
94,73,47,33,135,99,178,5,197,18,88,221,83,104,9,49,71,253,173,156,197,69,203,154,194,173,242,12,199,98,177,179,103,207,218,237,246,186,186,58,9,101,44,191,243,144,133,169,180,199,3,12,130,20,251,234,171,
175,254,250,215,191,78,253,172,124,130,51,138,132,174,72,16,242,194,225,204,112,52,140,87,77,142,119,41,205,38,6,110,249,158,246,135,30,122,72,238,87,164,12,151,149,149,81,111,27,138,130,176,118,39,47,
141,228,104,196,8,57,146,96,78,163,202,73,33,24,175,168,186,192,235,245,174,93,187,246,186,235,174,187,247,222,123,239,186,235,174,29,59,118,172,89,179,230,203,95,254,178,226,23,203,200,232,245,122,49,
186,131,14,169,101,164,46,47,47,71,15,173,112,128,150,249,221,212,212,212,203,47,191,60,62,62,222,209,209,225,243,249,240,182,136,167,208,15,146,127,142,117,201,97,57,85,6,22,184,103,220,110,119,52,26,
197,234,193,100,81,56,28,134,106,34,183,86,214,98,149,149,149,109,109,109,129,64,128,77,231,229,229,229,253,251,247,19,98,134,138,166,92,55,85,85,85,144,33,149,181,54,50,184,108,54,59,52,52,228,116,58,
171,171,171,85,79,15,167,49,147,201,204,207,207,67,201,133,143,146,146,146,195,135,15,63,242,200,35,170,193,69,169,44,53,211,204,112,44,127,132,243,51,57,57,249,201,79,126,50,95,56,54,59,28,116,111,227,
42,207,102,179,47,190,248,226,192,192,0,156,116,44,13,22,112,243,44,45,45,189,250,234,171,111,189,245,150,77,24,233,74,77,40,200,228,114,184,0,5,251,224,224,224,23,190,240,133,193,193,193,166,166,38,16,
153,10,8,133,23,8,199,182,247,186,8,217,222,235,85,15,5,231,96,48,184,121,243,102,222,125,188,255,77,99,101,155,205,6,55,28,217,185,202,215,251,177,212,111,144,162,137,82,245,201,164,96,171,64,121,236,
216,49,228,1,138,33,94,94,94,206,137,167,76,38,67,38,143,172,174,74,74,74,160,139,201,77,113,98,98,2,221,197,194,39,74,14,100,184,221,110,124,138,211,233,44,123,231,33,125,185,86,87,87,215,172,89,195,
160,44,213,41,164,147,17,127,65,70,240,242,242,242,71,30,121,100,227,198,141,0,160,11,68,103,179,56,86,99,235,68,14,145,51,41,89,87,185,167,42,247,110,169,214,244,30,72,154,2,58,200,17,192,11,89,94,94,
134,97,48,96,47,104,134,193,2,121,102,102,166,188,188,28,56,55,180,163,242,209,122,36,194,197,212,70,162,51,30,143,167,182,182,182,161,161,161,185,185,25,48,2,160,79,252,244,192,129,3,106,60,95,145,90,
34,145,8,4,159,192,216,69,212,70,73,206,191,2,206,40,207,160,178,32,144,111,40,145,150,115,231,206,61,250,232,163,55,220,112,195,61,247,220,3,192,7,162,169,21,21,21,62,159,15,141,26,140,9,225,155,34,191,
190,242,146,19,221,194,241,241,113,212,92,56,141,242,30,102,208,15,133,66,216,216,193,228,195,241,95,125,245,213,240,83,199,95,77,77,77,97,114,7,73,77,109,109,45,7,62,57,189,42,27,6,203,203,203,123,247,
238,141,70,163,239,123,223,251,20,89,13,125,51,4,229,138,138,138,202,202,74,92,253,137,137,137,135,31,126,88,153,212,41,95,18,89,73,40,9,30,196,29,96,101,169,84,234,216,177,99,219,183,111,87,27,36,145,
116,89,218,99,89,226,9,180,37,179,217,236,255,252,207,255,64,118,46,30,143,67,222,154,152,134,12,208,145,72,100,239,222,189,72,214,100,66,192,35,135,50,20,161,21,244,198,159,120,226,9,252,90,99,99,35,
204,61,165,122,12,141,46,201,209,150,122,208,138,139,66,241,88,201,238,192,21,129,51,206,218,181,107,67,161,80,34,145,112,58,157,200,160,1,161,16,176,146,0,32,138,39,213,39,87,4,124,75,71,80,179,138,5,
87,143,122,20,249,92,132,168,57,133,64,182,176,176,192,40,137,128,192,226,12,169,253,228,228,164,121,0,236,94,72,222,52,207,146,20,72,224,25,150,156,104,172,124,74,17,1,160,167,3,17,9,81,32,254,114,8,
133,85,142,228,222,153,141,68,156,219,251,239,191,191,162,162,66,238,88,249,166,207,45,113,15,73,210,167,127,138,229,222,169,134,176,228,202,167,205,13,231,188,222,99,26,139,31,3,89,135,142,109,50,153,
172,169,169,65,47,8,204,127,192,208,96,74,194,115,44,18,137,160,125,68,165,71,42,162,209,224,89,242,103,49,183,134,145,243,96,48,8,127,16,206,116,49,52,227,16,17,160,121,232,166,38,33,90,1,180,125,194,
49,148,148,148,84,86,86,98,200,50,157,78,63,244,208,67,209,104,116,207,158,61,242,14,145,120,180,20,240,163,156,19,120,132,118,187,253,208,161,67,7,15,30,252,240,135,63,124,199,29,119,112,118,62,18,137,
64,114,8,51,235,160,190,229,75,175,10,60,96,179,18,143,199,165,27,175,76,52,124,62,31,28,20,165,119,28,135,230,55,111,222,124,252,248,113,214,19,179,179,179,193,96,48,16,8,224,54,38,31,158,229,185,153,
209,31,63,126,124,122,122,250,195,31,254,48,139,12,64,246,208,35,244,249,124,224,177,185,92,174,217,217,217,79,127,250,211,108,12,154,146,17,42,231,98,173,74,184,3,50,96,215,94,123,173,207,231,219,176,
97,131,28,168,49,37,182,229,220,57,213,100,16,163,231,230,230,126,251,219,223,98,164,2,83,230,168,114,204,121,212,193,193,193,3,7,14,0,98,150,96,159,210,30,113,187,221,24,189,197,178,231,111,182,180,180,
224,84,36,18,9,229,160,136,35,103,251,75,42,142,170,223,148,58,42,242,44,161,145,211,222,222,94,89,89,137,20,30,28,59,110,204,100,131,72,41,90,6,104,203,102,154,42,85,77,86,143,233,201,194,185,15,203,
184,204,255,98,98,130,233,45,116,221,28,14,71,125,125,61,11,35,187,221,94,83,83,147,205,102,33,165,36,51,98,224,254,216,213,56,205,47,199,29,212,23,49,37,238,22,23,23,27,26,26,128,245,145,55,178,184,184,
232,243,249,2,129,128,219,237,198,38,77,145,13,203,185,21,203,199,234,234,234,250,245,235,111,184,225,6,124,132,164,183,90,86,36,150,103,146,155,174,156,222,44,48,54,129,7,213,172,44,21,214,56,247,235,
32,111,159,6,16,104,89,36,18,9,168,237,64,112,43,30,143,83,244,125,118,118,22,209,16,59,48,208,76,116,108,153,254,128,83,204,184,236,118,187,189,94,175,207,231,3,33,132,25,22,161,9,229,233,128,12,90,126,
103,5,198,227,84,198,98,49,4,23,149,32,128,121,114,205,53,215,124,224,3,31,40,46,46,110,106,106,122,252,241,199,165,122,175,84,237,81,21,10,238,22,74,181,22,21,21,189,253,246,219,67,67,67,59,119,238,220,
181,107,23,8,61,32,186,219,237,118,104,93,218,254,127,31,77,77,77,231,206,157,163,17,12,207,70,89,89,89,32,16,224,44,137,25,191,28,14,199,142,29,59,142,31,63,206,195,46,45,45,173,170,170,194,159,0,231,
197,229,183,164,60,75,1,188,199,31,127,252,254,251,239,231,220,7,166,84,188,94,175,228,253,60,245,212,83,253,253,253,210,36,201,244,42,148,161,22,119,111,67,67,195,250,245,235,235,235,235,219,218,218,
240,95,219,123,29,132,101,72,149,18,204,188,73,64,15,96,176,91,90,90,122,250,233,167,35,145,8,231,68,150,151,151,147,201,36,6,103,229,152,214,137,19,39,206,159,63,47,249,157,230,112,7,3,52,74,4,214,13,
104,26,227,178,34,30,73,137,81,169,137,97,242,136,76,214,160,73,101,1,131,179,163,163,195,227,241,160,117,198,169,4,90,202,146,177,71,39,51,64,177,249,212,233,100,131,151,131,33,74,221,66,57,180,1,96,
65,39,201,212,47,84,109,112,136,253,43,114,20,160,57,230,209,208,201,132,163,152,28,138,129,125,53,6,220,128,45,240,102,87,20,47,75,94,160,116,25,71,231,9,133,29,14,9,243,38,132,158,45,211,228,2,207,115,
185,220,167,63,253,105,19,245,86,97,250,178,15,238,163,8,119,87,98,94,138,108,114,121,121,25,185,191,37,223,110,101,101,197,17,143,199,227,241,56,100,36,177,122,128,43,1,44,14,4,2,240,158,128,91,74,113,
113,113,48,24,132,175,4,49,123,132,3,24,18,74,247,63,247,59,15,76,70,72,145,98,158,17,26,104,153,6,37,167,79,159,150,2,111,150,108,118,152,59,176,13,200,164,24,86,173,127,241,23,127,129,88,188,107,215,
174,166,166,166,127,250,167,127,2,33,129,235,94,129,134,166,182,86,58,157,134,7,68,58,157,238,235,235,123,250,233,167,111,185,229,150,251,238,187,15,14,50,126,191,159,181,204,21,182,104,212,13,230,118,
187,107,106,106,166,166,166,112,145,176,112,253,126,63,82,114,130,239,138,240,128,63,239,234,234,98,42,84,91,91,91,86,86,22,139,197,170,171,171,97,158,43,181,19,11,47,148,72,36,242,203,95,254,242,206,
59,239,4,108,2,102,161,98,121,111,221,186,149,73,1,179,60,41,108,191,115,231,206,198,198,70,68,228,202,202,202,171,175,190,218,132,23,21,165,93,178,244,164,236,9,223,147,155,19,126,58,49,49,241,187,223,
253,110,122,122,26,136,16,138,116,36,209,114,98,37,147,201,28,57,114,4,45,169,2,51,26,92,102,20,144,194,135,34,141,32,160,143,155,95,37,149,82,176,31,98,55,132,65,37,86,38,131,53,3,52,192,211,142,142,
14,104,1,35,203,193,237,141,125,130,200,137,210,243,3,120,149,15,205,160,36,14,4,103,10,171,41,73,132,164,178,178,82,138,46,240,219,73,204,33,147,201,144,124,205,43,8,37,107,116,26,48,107,70,66,39,13,
100,169,202,224,114,185,162,209,232,252,252,60,98,180,172,235,37,170,96,10,137,20,21,21,173,93,187,182,173,173,109,203,150,45,144,183,100,44,38,139,78,50,55,254,164,232,188,178,178,242,217,207,126,246,
198,27,111,28,24,24,224,88,156,218,122,175,252,142,166,214,232,21,74,89,145,236,129,48,189,184,184,40,229,97,223,125,219,153,153,25,176,202,169,238,193,27,111,126,126,30,119,62,195,183,221,110,247,122,
189,152,80,164,178,29,205,20,96,79,233,114,185,144,87,74,181,7,213,55,144,195,220,108,44,200,199,217,179,103,227,241,184,44,52,212,72,165,244,124,194,90,145,12,152,80,40,244,240,195,15,203,87,26,27,27,
191,243,157,239,252,228,39,63,25,29,29,229,73,148,236,122,197,66,95,92,92,188,112,225,2,9,58,56,45,171,171,171,191,255,253,239,15,30,60,248,224,131,15,62,240,192,3,42,49,185,236,192,161,229,163,185,185,
25,18,154,69,69,69,53,53,53,200,161,24,155,84,106,201,124,16,249,72,75,75,75,38,147,1,66,141,232,134,100,71,6,101,75,11,78,213,164,77,38,147,221,221,221,55,223,124,179,28,99,229,159,167,211,233,29,59,
118,124,224,3,31,216,191,127,127,81,81,81,67,67,67,48,24,188,246,218,107,43,43,43,55,110,220,184,97,195,6,37,12,139,141,211,178,1,168,114,103,90,131,203,60,87,178,86,153,62,79,77,77,61,254,248,227,64,
225,113,62,241,77,1,62,194,5,24,155,77,119,119,119,32,16,248,209,143,126,244,131,31,252,0,202,39,18,227,179,156,200,112,185,92,64,222,203,203,203,219,219,219,231,230,230,120,53,73,25,150,161,77,61,136,
117,152,120,180,12,211,8,196,69,69,69,29,29,29,232,192,83,20,69,78,187,160,21,47,231,137,72,109,42,76,173,3,255,215,4,61,44,217,117,210,80,130,205,12,185,146,165,112,238,194,194,130,180,130,148,134,109,
18,126,229,35,16,8,140,142,142,42,166,96,93,93,157,199,227,129,40,213,169,206,0,0,32,0,73,68,65,84,15,33,170,19,176,12,9,4,51,38,4,2,129,117,235,214,53,52,52,180,183,183,7,131,65,70,100,75,134,6,159,195,
222,144,34,174,180,37,146,141,65,21,157,221,110,247,183,191,253,109,143,199,67,101,136,203,178,18,11,71,91,137,137,255,73,148,71,196,73,52,90,101,87,175,168,168,200,33,103,40,9,23,240,100,197,227,113,
159,207,7,80,146,232,126,115,115,115,127,127,63,60,35,160,157,10,77,122,196,241,104,52,106,50,159,44,59,236,144,39,181,116,246,59,112,224,64,129,129,119,197,76,140,68,34,80,206,35,115,227,225,135,31,70,
110,34,115,100,191,223,255,149,175,124,229,137,39,158,128,82,176,202,80,228,237,167,238,103,52,78,193,234,91,89,89,137,197,98,255,246,111,255,246,204,51,207,124,250,211,159,190,243,206,59,85,20,102,115,
86,250,6,96,63,195,53,72,38,147,178,86,133,31,85,119,119,119,83,83,83,89,89,217,236,236,172,156,215,224,172,188,44,123,121,84,183,220,114,203,27,111,188,129,234,30,6,11,112,126,67,199,178,0,157,83,134,
146,154,154,154,207,127,254,243,157,157,157,210,169,154,245,50,134,146,138,138,138,30,123,236,177,129,129,1,40,197,168,200,43,195,113,62,26,131,12,223,178,103,160,176,17,57,26,203,174,221,216,216,216,
207,126,246,51,186,211,147,223,146,78,167,17,151,83,169,148,195,225,24,27,27,27,30,30,254,236,103,63,251,200,35,143,228,114,185,239,126,247,187,127,254,231,127,206,78,186,234,255,200,220,179,188,188,124,
113,113,209,237,118,215,214,214,66,117,128,161,138,166,19,42,50,170,72,173,196,29,85,75,144,3,190,62,159,111,237,218,181,88,249,166,55,16,16,3,100,172,4,223,184,74,229,132,155,9,58,83,45,96,97,97,33,159,
229,74,190,248,130,42,16,229,154,132,71,240,209,36,243,16,226,0,29,27,125,66,197,157,199,191,110,183,187,185,185,121,112,112,144,18,125,168,48,80,79,71,163,81,135,195,225,118,187,161,127,137,207,218,184,
113,227,250,245,235,67,161,208,186,117,235,160,113,138,28,153,105,178,138,206,204,151,101,164,166,118,157,101,4,151,207,241,228,123,223,251,30,56,196,224,195,177,137,101,41,46,150,111,240,79,129,209,150,
94,213,5,234,24,73,2,65,23,4,252,102,136,202,173,172,172,56,200,144,67,0,146,210,42,176,82,70,197,237,118,187,145,101,96,51,132,135,19,202,252,242,242,114,234,5,131,141,24,139,197,148,37,154,186,55,40,
44,103,182,152,240,100,255,254,253,38,130,38,129,45,25,125,82,169,20,38,157,144,146,119,117,253,191,230,190,53,184,173,235,186,26,36,193,23,64,144,0,4,130,79,81,36,37,82,239,183,44,57,142,237,216,169,
19,213,78,227,86,126,36,109,220,142,157,105,199,109,51,99,123,50,142,147,62,39,233,140,157,54,147,186,147,182,211,116,218,25,103,242,234,100,166,73,154,186,182,211,58,113,172,214,174,99,201,209,219,148,
40,74,20,197,55,9,18,0,241,32,1,18,4,200,239,199,138,87,182,247,57,247,138,82,218,47,189,63,56,32,72,0,23,247,158,179,207,62,107,175,189,214,158,23,94,120,1,125,28,177,88,108,106,106,234,59,223,249,14,
99,247,239,255,254,239,127,247,187,223,125,245,213,87,165,141,163,186,1,242,10,0,232,92,88,88,64,158,40,213,38,63,255,249,207,191,244,210,75,143,60,242,8,189,209,24,59,36,134,197,247,65,17,21,34,174,242,
104,106,106,130,9,22,37,11,56,183,37,115,128,13,105,68,150,218,219,219,49,27,33,110,135,107,158,74,165,160,56,122,205,142,6,159,207,247,224,131,15,254,202,175,252,138,60,103,54,86,224,106,48,167,70,57,
133,203,143,53,4,203,118,121,23,230,25,51,62,228,254,178,99,16,147,153,69,81,24,197,254,245,95,255,53,186,129,84,183,36,98,180,207,231,3,10,183,97,195,134,191,255,251,191,111,110,110,198,12,220,184,113,
227,111,255,246,111,63,247,220,115,74,32,66,137,190,35,16,248,253,126,164,168,172,57,179,54,163,224,53,229,34,47,131,50,229,183,212,18,136,75,26,10,133,54,108,216,128,132,78,198,53,118,82,240,14,18,119,
150,65,28,229,98,119,10,29,74,121,78,186,157,106,36,40,251,21,169,126,35,191,32,92,204,177,189,32,147,53,28,14,75,112,79,154,203,224,153,250,250,250,245,235,215,79,76,76,144,21,202,218,96,36,18,9,135,
195,59,118,236,168,173,173,245,249,124,219,182,109,107,107,107,35,154,140,136,140,159,56,168,106,132,121,161,194,177,76,141,149,49,136,41,153,36,49,16,72,170,77,76,76,152,250,33,8,20,136,212,68,192,64,
124,192,114,46,149,115,220,107,182,107,236,188,87,169,58,194,41,194,206,79,187,75,64,168,96,81,149,175,204,229,114,240,162,7,124,65,198,104,107,107,235,212,212,148,180,158,148,173,138,205,205,205,233,
116,218,244,64,226,255,160,253,65,150,35,20,6,13,226,170,90,193,76,130,36,31,199,227,113,140,206,186,186,186,99,199,142,73,135,74,213,255,227,241,120,238,187,239,190,246,246,246,111,124,227,27,50,158,
34,19,164,114,188,82,254,134,240,133,164,106,130,220,242,246,219,111,127,242,147,159,220,181,107,215,195,15,63,188,115,231,78,150,31,249,182,242,202,72,125,56,5,242,114,48,129,185,40,91,239,100,203,31,
69,145,48,123,195,225,112,125,125,61,229,94,249,206,115,115,115,192,229,157,134,69,101,101,229,67,15,61,244,193,15,126,16,90,101,138,143,137,96,33,55,185,68,217,192,222,177,6,95,110,26,92,194,183,122,
21,194,171,66,57,164,176,209,208,208,208,231,63,255,121,54,251,73,174,36,89,155,232,246,252,173,223,250,173,219,110,187,77,233,255,62,240,192,3,47,190,248,98,44,22,83,211,32,151,203,73,79,166,117,235,
214,145,0,203,132,26,228,1,39,4,223,26,166,49,126,100,163,44,85,59,90,91,91,163,209,40,152,194,178,237,155,14,203,146,177,14,168,90,58,233,65,120,192,137,72,39,79,3,224,201,13,212,171,169,72,167,114,169,
84,42,53,51,51,3,168,19,255,128,244,217,220,88,168,155,27,137,68,150,151,151,161,120,39,45,135,176,47,249,242,151,191,156,78,167,135,134,134,178,217,172,140,206,50,52,203,231,165,207,161,202,154,241,36,
170,56,184,95,82,211,206,201,222,251,15,255,240,15,57,44,89,213,132,194,42,198,57,166,149,116,170,83,123,47,20,222,228,3,4,113,108,74,164,244,188,187,202,155,11,168,13,91,97,47,224,36,233,64,46,27,181,
97,97,27,10,133,72,228,64,154,60,51,51,35,225,99,37,244,222,216,216,8,51,24,101,186,10,244,144,1,8,189,109,180,159,192,118,245,252,249,243,232,62,151,233,134,98,236,155,101,95,128,45,88,231,61,134,85,
160,42,206,30,60,120,176,181,181,245,139,95,252,34,246,176,74,41,81,114,21,25,8,80,152,226,147,120,128,121,213,215,215,247,195,31,254,112,215,174,93,82,93,68,37,83,178,204,98,18,158,238,186,235,174,233,
233,233,201,201,73,204,19,86,240,165,246,185,34,114,224,2,246,244,244,156,59,119,78,141,33,232,25,129,149,101,14,130,67,135,14,61,254,248,227,228,185,91,15,68,40,238,215,36,145,83,214,127,204,75,231,222,
184,161,182,62,168,239,201,97,67,105,139,242,242,242,163,71,143,254,205,223,252,141,50,123,149,16,25,158,57,124,248,240,19,79,60,225,247,251,77,241,223,154,154,154,79,127,250,211,79,62,249,36,56,94,108,
203,148,93,51,202,239,3,73,52,64,6,0,208,214,76,71,133,102,249,53,165,174,0,243,21,80,63,73,2,99,63,27,85,171,228,32,7,230,43,141,143,209,215,170,228,246,157,206,7,107,128,123,30,109,61,124,62,31,110,
174,188,32,169,84,106,101,101,101,122,122,26,10,57,232,34,86,254,41,242,118,200,65,219,222,222,94,42,149,50,153,140,9,3,158,59,119,110,251,246,237,219,182,109,27,29,29,29,28,28,100,56,94,126,247,193,156,
26,147,154,89,151,9,92,16,122,230,50,224,146,71,63,242,200,35,205,205,205,82,42,15,247,26,225,184,178,178,18,122,188,128,62,156,96,34,167,32,206,78,180,158,158,30,119,72,100,45,185,182,23,157,120,146,
227,37,129,8,143,199,51,51,51,211,214,214,134,32,78,24,186,185,185,121,112,112,208,99,216,194,203,199,161,80,8,38,114,20,178,169,168,168,64,179,56,74,216,188,148,202,177,240,248,241,227,107,41,175,153,
186,177,40,115,155,95,126,126,126,30,90,10,242,122,181,183,183,63,245,212,83,95,249,202,87,80,208,48,201,255,114,10,149,151,151,167,82,41,182,189,16,5,70,77,207,231,243,61,242,200,35,50,190,200,116,18,
167,202,244,217,252,94,200,74,186,187,187,187,187,187,247,238,221,251,198,27,111,92,190,124,121,126,126,94,10,101,40,105,74,134,179,104,52,170,208,36,126,101,86,104,121,236,216,177,227,161,135,30,66,73,
196,201,188,81,45,81,234,34,87,85,85,129,118,166,72,102,24,250,166,164,131,21,149,230,97,181,62,194,16,122,229,149,87,160,91,100,106,183,243,34,183,180,180,124,246,179,159,221,187,119,47,23,114,106,177,
115,207,187,109,219,182,93,187,118,189,252,242,203,236,128,53,77,17,225,122,5,80,149,10,200,184,134,106,125,178,170,42,42,48,81,70,79,175,215,219,221,221,141,117,93,70,46,105,30,102,93,204,0,233,112,70,
68,34,17,107,7,138,9,97,93,151,0,169,201,154,160,164,162,84,225,64,28,4,157,177,163,163,131,172,127,243,228,61,239,182,83,129,236,204,208,208,80,62,159,87,253,26,195,195,195,168,103,116,116,116,52,52,
52,156,63,127,30,78,90,100,101,144,63,199,159,216,93,241,230,170,232,140,253,144,220,245,42,139,66,30,77,77,77,15,60,240,128,90,96,152,111,97,255,1,250,150,204,148,241,115,237,12,141,235,13,95,142,173,
249,31,255,248,199,205,235,43,55,254,216,234,134,66,33,168,5,178,209,19,12,39,54,245,146,69,71,137,6,116,115,162,200,3,125,9,72,44,225,146,17,36,53,49,190,87,94,121,5,18,28,74,100,235,154,151,3,73,147,
140,47,152,3,59,119,238,108,108,108,52,199,119,67,67,195,161,67,135,134,135,135,33,66,109,229,129,202,106,91,36,18,145,170,199,172,116,125,244,163,31,125,207,123,222,99,18,185,228,214,65,54,179,152,110,
44,204,119,42,43,43,187,187,187,15,30,60,216,211,211,3,218,191,44,206,200,227,234,213,171,231,207,159,63,123,246,44,97,7,101,103,190,180,180,132,85,1,149,192,71,31,125,244,247,126,239,247,26,27,27,173,
118,51,114,3,40,147,65,149,28,225,39,88,219,60,104,235,46,187,182,248,182,114,158,200,155,194,36,23,87,70,158,192,139,47,190,248,204,51,207,40,41,94,53,78,30,125,244,209,191,252,203,191,196,250,164,28,
52,168,177,128,124,121,223,190,125,223,254,246,183,165,108,188,121,44,47,47,147,170,84,89,89,137,141,185,234,240,118,73,130,76,252,29,19,187,171,171,75,133,51,243,177,53,159,146,189,100,216,244,184,224,
158,138,108,167,122,136,93,232,134,38,1,137,38,100,36,216,93,188,120,17,131,19,160,115,62,159,15,4,2,104,36,54,151,58,243,10,99,159,78,221,30,28,67,67,67,203,203,203,224,98,34,203,105,105,105,169,170,
170,138,197,98,96,155,201,194,32,210,103,204,2,167,162,159,130,65,220,123,85,62,243,153,207,160,84,43,191,59,182,14,116,148,87,68,38,200,223,195,97,114,141,49,26,173,12,238,129,107,45,75,169,215,196,7,
101,224,192,131,177,177,177,206,206,78,40,81,17,119,134,237,13,51,59,41,57,38,131,93,125,125,125,111,111,239,240,240,48,250,238,84,183,62,229,252,57,44,202,203,203,47,95,190,108,213,250,115,18,246,102,
254,146,203,229,192,185,118,111,172,242,188,219,206,245,201,39,159,252,234,87,191,250,227,31,255,88,145,249,201,211,148,240,25,59,86,121,84,86,86,222,127,255,253,166,119,151,60,97,181,81,50,179,33,217,
76,140,199,145,72,228,67,31,250,16,140,75,224,227,137,12,98,124,124,28,166,30,18,106,52,191,23,73,56,77,77,77,247,221,119,223,125,247,221,71,16,64,133,9,83,177,72,238,108,100,159,11,235,39,153,76,70,138,
234,154,50,26,106,80,169,29,137,204,55,211,233,52,172,97,56,183,95,120,225,133,207,125,238,115,82,244,64,145,124,246,239,223,255,244,211,79,179,24,168,242,35,76,66,192,199,56,106,107,107,31,127,252,241,
47,124,225,11,238,230,229,115,115,115,232,87,70,23,204,202,202,74,91,91,219,226,226,34,114,11,151,84,90,133,87,214,27,64,118,150,119,22,165,81,25,157,101,222,13,220,3,223,2,84,28,196,104,232,41,186,100,
91,28,78,232,123,148,173,91,78,154,183,102,43,179,220,65,210,51,12,28,30,143,112,179,132,112,82,36,18,105,110,110,38,2,99,205,240,248,237,124,62,95,111,111,239,208,208,144,212,45,138,197,98,106,139,217,
222,222,190,110,221,186,147,39,79,94,190,124,89,193,208,114,87,100,53,132,101,55,178,59,235,121,101,101,229,189,239,125,47,229,224,229,121,98,145,38,111,202,233,58,163,208,165,128,38,43,103,6,5,240,107,
170,194,186,124,28,254,228,85,88,149,154,96,132,119,39,39,39,195,225,48,155,125,145,56,135,66,33,16,131,184,7,55,189,142,208,176,212,219,219,123,241,226,69,41,33,45,169,175,114,209,158,152,152,48,181,
146,173,59,50,121,113,165,187,26,234,221,242,242,169,0,173,40,198,43,43,43,15,63,252,240,230,205,155,191,246,181,175,201,106,134,71,120,200,227,29,176,132,202,100,22,64,219,220,220,28,218,228,204,126,
95,124,47,153,254,152,55,140,248,128,169,173,10,162,126,79,79,207,29,119,220,241,223,255,253,223,223,255,254,247,193,111,177,94,19,243,193,93,119,221,245,137,79,124,2,134,144,4,1,36,221,205,221,197,17,
44,117,115,226,249,124,190,185,185,57,37,118,174,186,176,204,72,109,58,36,64,44,80,10,138,126,245,171,95,125,230,153,103,100,63,142,36,167,215,213,213,253,209,31,253,209,145,35,71,156,90,18,164,54,152,
212,156,252,224,7,63,248,239,255,254,239,88,228,204,232,204,197,32,149,74,69,163,81,108,119,16,34,171,171,171,81,110,157,159,159,135,51,178,202,79,85,104,198,131,80,40,180,126,253,122,201,57,145,192,174,
98,194,72,219,73,121,61,177,49,194,150,220,165,184,36,81,142,108,54,235,210,151,100,141,206,214,38,67,94,252,185,185,57,213,134,131,85,4,14,141,29,29,29,204,60,212,0,48,1,89,52,176,16,127,67,113,139,83,
149,11,195,254,253,251,219,218,218,142,29,59,54,51,51,67,58,29,224,14,156,91,241,221,7,219,2,228,182,204,169,48,232,243,249,30,123,236,49,235,90,194,24,98,77,144,221,41,210,86,9,120,151,132,236,186,224,
145,138,143,125,236,99,10,14,147,7,191,237,226,226,98,119,119,183,12,208,136,200,169,84,138,122,102,74,97,146,194,37,56,251,198,198,70,236,95,136,132,152,62,5,16,136,128,111,174,146,5,112,90,169,148,175,
10,146,62,41,166,142,166,187,150,150,22,107,41,150,177,184,163,163,99,203,150,45,103,207,158,101,172,68,147,143,162,169,96,72,201,30,135,155,110,186,233,210,165,75,123,246,236,225,56,86,128,32,248,188,
106,215,41,79,0,116,122,133,120,72,253,57,228,8,27,55,110,188,251,238,187,239,189,247,222,150,150,150,217,217,89,58,194,89,5,225,246,239,223,255,165,47,125,9,42,48,114,212,74,95,119,115,4,43,172,3,249,
178,185,199,242,122,189,153,76,134,214,65,242,205,77,199,10,229,20,167,62,174,88,44,214,214,214,194,252,248,177,199,30,251,187,191,251,59,143,205,227,213,227,241,28,57,114,228,185,231,158,3,163,81,85,
138,228,3,105,6,136,137,141,191,238,216,177,227,133,23,94,176,66,28,82,159,15,231,83,44,22,81,249,145,59,45,159,207,23,10,133,26,26,26,176,72,59,33,9,225,112,184,171,171,203,132,134,20,31,201,26,209,100,
226,73,226,202,129,3,7,36,205,223,9,220,99,116,38,11,222,227,44,57,47,139,231,138,21,46,99,202,196,196,132,116,245,230,116,192,133,74,36,18,104,24,86,28,89,243,34,67,72,164,188,188,28,221,146,80,7,237,
238,238,6,182,46,91,123,138,197,98,85,85,213,166,77,155,74,165,18,16,15,194,29,100,236,201,146,32,18,26,48,210,84,178,108,130,209,31,251,216,199,144,62,155,57,40,70,139,84,80,145,249,19,132,125,114,185,
28,74,139,230,130,100,70,231,250,250,122,18,151,111,0,232,248,25,226,244,190,247,189,79,138,54,40,27,24,126,147,165,165,37,170,83,50,58,251,253,126,248,116,40,117,96,170,235,202,140,181,178,178,50,26,
141,66,104,73,150,191,84,50,248,242,203,47,195,44,78,170,219,56,9,151,80,75,80,62,89,40,20,24,86,240,45,162,209,232,214,173,91,157,196,24,25,28,35,145,200,142,29,59,70,71,71,41,202,174,154,244,151,151,
151,215,173,91,39,179,176,237,219,183,7,2,129,98,177,56,57,57,185,115,231,78,229,177,70,149,12,243,36,229,153,144,23,129,243,97,145,68,230,2,60,213,64,32,176,123,247,238,143,124,228,35,191,246,107,191,
182,186,186,58,51,51,3,53,31,190,188,165,165,229,153,103,158,249,228,39,63,25,14,135,149,90,185,28,184,172,65,57,29,0,254,32,115,97,66,34,21,21,21,52,122,151,146,234,102,22,99,162,16,234,255,65,116,251,
157,223,249,157,127,250,167,127,50,171,94,232,93,252,135,127,248,135,143,127,252,227,96,10,155,92,43,134,102,185,17,70,243,5,255,7,81,181,191,191,223,10,149,74,141,99,196,232,68,34,97,237,14,7,35,184,
190,190,62,24,12,210,30,158,151,168,163,163,163,181,181,213,154,165,170,82,158,83,3,17,227,38,183,17,247,222,123,175,85,100,92,70,16,16,197,72,246,55,241,19,83,140,95,201,16,203,237,38,153,142,163,163,
163,82,181,70,202,153,81,232,110,113,113,145,62,97,78,1,26,79,214,215,215,131,186,222,215,215,7,23,189,238,238,110,179,236,129,241,31,141,70,187,187,187,97,85,202,155,72,3,35,174,142,28,12,168,93,19,12,
49,129,142,104,52,250,244,211,79,59,213,54,41,78,137,221,60,90,69,50,153,76,42,149,202,102,179,64,204,2,129,0,172,166,172,228,101,21,91,91,91,91,185,111,150,220,1,119,5,37,51,208,121,193,36,5,82,1,153,
36,86,150,84,133,122,108,108,172,187,187,91,170,139,121,189,222,104,52,138,14,75,235,141,161,185,22,159,233,237,237,141,197,98,19,19,19,18,168,149,48,244,208,208,144,236,31,245,216,12,193,152,98,48,79,
87,35,18,68,37,133,65,203,45,167,185,173,99,116,123,252,241,199,191,254,245,175,95,185,114,197,108,63,195,78,2,128,32,244,98,218,219,219,113,86,99,99,99,39,78,156,216,191,127,191,188,25,236,227,116,223,
242,48,172,0,116,147,117,72,69,170,147,143,163,209,232,83,79,61,245,233,79,127,122,96,96,224,27,223,248,198,43,175,188,82,86,86,246,216,99,143,61,252,240,195,100,53,200,173,159,116,203,149,132,98,133,
84,152,214,186,214,36,29,8,41,200,73,214,84,209,169,159,208,35,156,207,240,152,173,213,20,165,99,220,89,93,93,125,242,201,39,63,245,169,79,1,111,177,226,143,202,53,67,133,126,180,162,224,79,71,142,28,
121,235,173,183,96,8,105,98,208,146,82,73,14,187,217,194,138,116,21,3,27,243,133,178,45,208,214,144,8,146,140,122,76,247,120,229,233,36,34,195,19,3,52,222,173,169,169,73,242,127,156,162,179,28,216,102,
199,128,249,77,77,219,1,169,181,68,89,90,37,134,35,229,107,248,51,147,201,92,188,120,177,171,171,139,142,33,238,234,96,80,246,64,244,231,232,82,50,76,136,209,53,53,53,31,248,192,7,186,187,187,95,125,245,
213,100,50,73,166,29,37,177,76,164,75,142,4,53,84,158,122,234,41,246,97,155,85,55,168,59,96,157,75,36,18,52,157,226,76,148,149,124,119,233,74,167,165,215,73,181,238,26,69,66,137,106,33,82,3,95,102,47,
13,143,209,209,209,182,182,54,197,30,237,232,232,0,115,78,106,75,82,203,152,148,94,25,113,218,218,218,106,107,107,177,56,115,212,2,72,154,155,155,51,205,188,21,30,45,213,173,212,150,13,191,146,46,110,
22,60,101,139,32,202,2,38,72,82,85,85,245,232,163,143,126,251,219,223,62,113,226,132,236,163,97,202,64,233,137,221,187,119,203,143,120,245,213,87,215,175,95,223,216,216,40,197,31,204,232,108,222,203,153,
153,25,194,65,146,171,167,160,124,243,39,169,208,79,63,253,244,159,255,249,159,99,253,151,132,51,5,98,16,182,50,89,7,230,182,9,175,2,21,132,27,76,25,100,195,225,240,200,200,136,217,192,173,222,220,9,149,
230,237,203,102,179,241,120,252,185,231,158,91,93,93,253,230,55,191,201,139,115,203,45,183,124,249,203,95,238,232,232,144,45,9,38,217,217,220,34,72,152,8,132,78,230,212,191,241,27,191,241,236,179,207,
154,209,217,84,218,132,214,135,218,12,73,98,190,74,121,2,129,0,60,124,129,248,163,9,192,42,193,40,211,85,169,43,205,43,201,152,88,93,93,221,209,209,225,50,120,104,48,152,203,229,32,233,181,188,188,188,
109,219,54,37,159,96,206,5,171,232,18,86,65,190,10,161,192,186,139,55,67,210,208,208,80,99,99,35,242,21,151,100,191,162,162,98,203,150,45,208,200,140,199,227,74,223,131,35,132,74,117,43,43,43,235,215,
175,255,232,71,63,122,226,196,137,215,94,123,141,125,91,10,187,32,150,197,225,193,236,4,79,222,124,243,205,91,183,110,165,254,137,220,14,162,59,166,88,44,94,188,120,17,58,248,178,225,197,35,68,247,157,
20,78,172,97,215,170,1,123,77,48,218,172,189,121,205,37,133,226,220,176,7,103,179,35,22,189,174,174,46,201,125,134,238,159,76,241,164,119,139,213,242,25,125,46,193,96,16,87,132,229,193,242,242,242,193,
193,65,165,255,41,133,210,37,96,194,233,45,67,115,69,69,5,156,23,240,182,252,206,28,10,50,151,193,253,99,137,70,46,143,171,171,171,15,60,240,64,107,107,235,191,253,219,191,201,85,4,212,93,156,33,180,104,
149,151,229,75,47,189,244,208,67,15,97,39,72,139,54,235,205,147,47,236,237,237,157,159,159,199,116,69,54,141,2,145,52,114,84,97,154,207,112,77,146,159,168,152,109,146,188,33,163,54,23,3,149,120,74,170,
127,62,159,135,176,164,153,20,131,207,159,74,165,76,247,50,185,85,151,65,65,113,129,249,255,125,125,125,119,222,121,231,179,207,62,123,246,236,217,190,190,190,186,186,186,103,159,125,246,225,135,31,198,
174,194,164,181,202,169,104,194,56,50,64,99,62,131,33,186,178,178,178,105,211,166,59,238,184,67,21,90,173,213,14,175,215,59,59,59,11,118,38,47,14,123,160,76,55,19,12,200,229,229,229,169,169,169,222,222,
94,160,171,185,92,46,155,205,206,207,207,179,238,109,178,119,204,34,42,227,245,226,226,98,87,87,151,19,159,47,149,74,13,14,14,102,50,25,232,35,87,190,115,156,63,127,30,6,146,242,0,203,155,208,34,189,217,
56,162,112,170,240,13,192,75,142,31,63,126,244,232,81,74,167,109,217,178,133,145,200,235,245,162,209,73,158,216,204,204,204,149,43,87,58,58,58,100,73,28,45,136,170,104,20,141,70,161,196,48,54,54,70,17,
90,53,65,234,234,234,16,133,48,80,15,28,56,176,126,253,250,211,167,79,131,13,98,242,231,100,128,86,248,134,207,231,123,226,137,39,200,122,194,160,130,91,160,84,163,6,7,28,89,182,82,62,64,222,195,46,77,
197,226,80,59,123,60,137,125,182,90,210,72,56,89,59,123,218,107,102,251,82,71,2,156,68,116,46,122,189,222,43,87,174,108,218,180,73,49,159,218,219,219,199,199,199,85,116,102,219,52,205,70,149,117,180,223,
239,223,182,109,219,197,139,23,209,181,133,227,242,229,203,74,114,65,202,131,48,200,202,154,27,75,168,62,159,15,156,83,137,153,226,231,236,236,44,114,121,217,134,11,11,116,39,237,130,213,213,213,91,110,
185,37,20,10,253,243,63,255,51,153,42,8,211,208,78,235,233,233,81,215,20,212,239,31,253,232,71,119,223,125,183,82,157,55,9,176,234,62,81,242,130,182,141,204,101,76,215,2,46,24,216,232,152,107,0,174,54,
20,193,225,103,161,146,104,217,207,173,210,103,69,142,206,229,114,160,193,73,35,56,30,144,250,85,170,38,78,253,41,234,35,84,51,212,149,43,87,94,127,253,245,221,187,119,31,58,116,232,47,254,226,47,96,161,
109,109,58,48,89,207,170,14,201,53,64,166,138,168,196,174,172,172,28,62,124,248,39,63,249,137,236,140,55,129,102,20,121,38,38,38,208,1,32,67,179,41,5,67,63,29,10,249,95,189,122,181,187,187,27,77,119,232,
214,133,213,64,54,155,165,148,152,71,24,220,56,117,201,47,46,46,98,186,49,178,0,72,41,22,139,87,175,94,189,112,225,2,68,27,144,16,184,64,85,128,230,164,253,152,156,86,216,196,36,18,9,4,86,222,157,87,94,
121,5,101,213,178,178,178,238,238,110,122,142,120,132,77,137,132,149,120,53,104,245,32,175,45,62,154,237,212,128,70,167,167,167,81,189,183,18,99,234,235,235,81,173,197,71,132,195,225,199,31,127,252,237,
183,223,254,218,215,190,6,162,167,90,167,21,15,154,145,250,193,7,31,4,191,11,37,71,22,96,192,171,83,74,38,178,225,133,160,19,61,180,84,128,150,12,52,147,93,110,174,226,82,165,224,250,32,14,249,142,106,
59,3,240,129,238,168,147,147,147,216,118,241,114,71,34,145,201,201,73,22,91,16,245,168,173,101,34,170,92,183,235,234,234,246,238,221,251,246,219,111,179,23,30,221,137,172,88,170,237,51,30,40,202,154,231,
29,3,89,133,19,41,159,93,76,3,233,229,174,190,166,26,214,184,238,91,183,110,253,221,223,253,221,175,127,253,235,82,162,47,155,205,110,216,176,1,243,150,161,153,65,225,237,183,223,238,237,237,221,184,113,
163,132,89,93,168,142,120,128,1,71,1,13,229,220,110,61,208,119,235,174,173,5,144,20,37,254,92,46,199,225,165,0,7,6,95,147,221,33,157,4,212,85,194,80,11,6,131,184,56,86,42,180,85,208,142,247,136,119,57,
155,205,126,226,19,159,136,70,163,159,250,212,167,118,239,222,173,100,201,214,18,160,37,164,35,13,94,73,49,206,231,243,152,102,85,85,85,15,62,248,224,183,190,245,45,247,194,58,202,65,233,116,26,180,66,
115,27,199,0,39,85,23,40,250,138,214,1,62,233,245,122,27,27,27,155,154,154,128,146,37,147,201,76,38,3,109,3,149,71,203,123,26,14,135,139,197,226,165,75,151,146,201,100,125,125,61,229,12,47,92,184,48,62,
62,78,189,14,115,137,117,113,224,133,75,39,82,69,156,246,196,196,4,188,172,36,89,214,227,241,12,12,12,112,220,110,218,180,201,9,48,145,38,24,68,165,11,133,66,56,28,38,120,200,45,56,223,1,226,151,169,84,
202,99,19,100,231,217,134,66,161,229,229,101,148,163,1,28,221,118,219,109,251,247,239,255,202,87,190,242,131,31,252,128,3,0,95,199,100,61,151,74,165,214,214,214,221,187,119,143,143,143,155,165,60,188,
68,250,112,99,125,101,128,102,50,135,244,14,168,139,89,110,81,50,112,102,125,75,170,181,160,33,211,29,249,124,87,178,245,161,15,125,200,202,232,84,27,106,62,137,109,151,4,157,41,31,1,216,26,219,67,82,
199,149,143,178,170,246,86,84,84,68,163,81,248,33,37,147,201,23,95,124,81,46,236,74,183,147,2,149,82,41,49,28,14,195,207,80,101,106,242,198,7,131,193,3,7,14,48,28,203,198,80,165,243,96,14,193,64,32,112,
224,192,129,203,151,47,179,47,121,117,117,245,142,59,238,96,199,141,236,42,68,128,187,122,245,234,150,45,91,36,219,201,26,61,101,145,112,118,118,22,61,17,72,136,74,165,18,116,212,204,254,64,212,166,96,
150,186,198,123,140,72,93,81,81,49,63,63,47,251,172,104,87,104,242,46,248,124,161,80,64,168,50,201,24,56,171,154,154,154,68,34,161,186,4,85,125,210,124,33,171,112,68,186,247,237,219,247,185,207,125,14,
157,129,200,110,76,65,28,147,90,103,13,226,214,125,46,96,101,252,26,14,135,97,209,43,41,28,202,161,188,166,166,6,13,83,112,117,145,42,148,18,214,48,239,50,238,17,50,53,191,223,47,231,45,145,229,96,48,
216,212,212,4,111,117,236,83,25,46,229,36,111,106,106,26,27,27,187,122,245,106,44,22,131,35,168,199,227,57,125,250,244,232,232,168,156,71,106,138,153,21,123,217,68,214,208,208,80,245,206,177,186,186,58,
53,53,149,201,100,48,97,49,246,200,151,125,250,233,167,37,151,84,169,155,113,104,113,34,43,239,133,165,165,165,218,218,90,124,144,226,201,224,242,66,113,116,227,198,141,78,85,101,42,132,0,145,64,207,17,
76,214,15,30,60,184,115,231,206,193,193,193,201,201,73,196,77,178,158,120,247,49,42,62,242,145,143,160,69,75,14,30,46,231,178,161,9,191,82,59,87,218,71,224,124,96,245,41,119,105,18,12,100,114,80,42,149,
234,235,235,77,94,47,227,231,236,236,44,184,137,86,237,26,77,84,187,231,158,123,212,127,88,5,154,137,88,21,10,133,104,52,138,0,193,255,172,174,174,198,30,138,118,9,100,149,58,69,103,121,107,35,145,200,
210,210,210,235,175,191,126,230,204,25,178,137,205,141,15,152,3,60,117,144,82,249,61,165,227,170,10,235,185,92,238,206,59,239,228,84,1,194,171,150,34,167,232,134,194,41,248,64,177,88,12,144,14,240,56,
83,22,185,80,40,204,207,207,199,227,241,241,241,241,131,7,15,90,29,225,164,48,35,78,105,122,122,154,82,244,185,92,14,216,11,85,156,228,1,130,151,12,10,107,212,54,196,54,150,41,152,180,244,85,113,217,108,
147,133,101,56,246,119,102,119,56,73,184,138,63,103,6,101,243,73,124,139,112,56,124,248,240,225,125,251,246,73,134,159,140,209,138,227,44,39,155,53,64,227,87,197,240,35,170,139,95,161,193,109,218,137,
145,125,180,180,180,148,74,165,80,178,6,237,82,42,184,34,11,113,114,59,195,77,201,231,243,84,219,145,101,12,66,240,16,203,143,68,34,235,215,175,71,220,193,16,98,230,213,213,213,5,89,115,36,143,205,205,
205,167,78,157,26,27,27,147,169,174,124,96,214,42,228,78,23,9,13,213,110,81,200,129,77,26,137,176,164,204,158,60,121,242,249,231,159,199,127,110,219,182,13,252,95,105,16,44,131,142,244,214,97,184,0,179,
5,133,10,53,241,43,42,42,176,41,241,249,124,208,2,114,234,146,163,253,91,62,159,7,51,29,222,108,64,183,239,184,227,142,108,54,59,56,56,152,78,167,37,6,205,7,59,119,238,60,120,240,160,185,229,146,107,63,
150,82,4,46,80,158,185,201,6,66,21,12,6,155,155,155,91,91,91,89,140,81,116,82,243,103,117,117,53,207,83,181,107,224,86,230,243,121,105,93,100,22,39,56,143,188,38,163,206,122,72,64,96,108,108,172,185,185,
153,176,119,38,147,201,102,179,88,28,80,244,119,177,22,181,118,217,130,80,60,58,58,250,205,111,126,83,194,26,210,6,9,5,16,252,9,194,90,86,130,151,245,11,195,233,10,233,45,162,51,191,11,150,16,179,20,187,
176,176,0,193,20,94,150,195,135,15,183,180,180,252,240,135,63,236,233,233,129,86,156,244,61,202,102,179,108,8,246,122,189,163,163,163,3,3,3,148,183,119,233,233,204,100,50,96,239,243,180,105,203,43,55,
134,120,192,196,217,108,115,112,34,35,18,249,2,81,84,169,148,168,199,50,168,73,248,18,124,6,245,42,198,154,134,134,134,120,60,206,18,185,187,96,191,124,166,166,166,102,247,238,221,157,157,157,204,62,20,
97,206,201,199,200,100,185,202,224,110,110,161,8,91,81,183,204,239,247,223,114,203,45,240,136,145,183,3,162,119,8,94,161,80,8,16,135,199,227,73,38,147,145,72,132,119,196,212,57,83,195,15,53,152,209,209,
81,212,211,56,158,101,69,65,202,133,67,28,185,189,189,29,141,118,185,92,46,147,201,64,227,151,106,33,255,250,175,255,202,174,107,166,62,12,46,42,110,74,213,108,150,94,160,118,45,11,27,88,32,215,173,91,
7,180,151,10,250,18,223,232,238,238,86,109,135,178,192,104,154,112,75,38,37,180,150,228,165,3,38,201,213,78,2,104,230,0,70,109,19,231,0,28,95,122,70,79,78,78,222,127,255,253,183,221,118,219,159,253,217,
159,189,253,246,219,158,119,43,65,215,212,212,220,119,223,125,144,157,178,214,132,41,246,139,199,62,159,47,24,12,194,61,21,77,164,138,244,41,241,16,115,59,37,155,144,9,178,41,182,15,26,223,59,58,58,230,
230,230,18,137,196,186,117,235,76,99,73,85,175,210,173,222,172,168,96,244,75,157,92,190,120,100,100,100,199,142,29,8,46,160,31,96,137,192,20,229,201,97,107,99,26,63,155,246,131,248,136,3,7,14,252,201,
159,252,201,95,253,213,95,201,38,46,170,212,99,157,199,69,36,63,201,186,39,178,70,67,140,0,124,47,220,114,2,175,196,10,64,90,64,215,144,121,230,185,92,238,214,91,111,109,105,105,153,154,154,34,215,130,
52,91,197,168,171,172,172,4,236,139,208,102,165,221,0,104,142,197,98,166,231,8,130,254,242,242,50,61,71,112,196,227,113,217,84,230,222,95,43,239,52,122,148,229,202,175,10,119,86,90,30,158,196,106,47,5,
142,205,203,30,14,135,193,47,86,108,16,185,185,81,6,99,208,132,194,162,43,73,81,50,10,179,99,219,170,136,100,242,94,101,176,182,182,89,18,140,134,132,214,133,11,23,24,130,57,93,153,18,42,3,176,120,60,
30,137,68,40,108,118,205,222,95,196,208,225,225,97,89,97,99,96,50,243,21,78,52,191,223,15,165,11,8,97,227,37,99,99,99,80,0,151,50,164,106,187,237,190,52,98,250,48,138,169,149,9,150,2,52,253,235,239,239,
199,155,172,95,191,30,205,168,10,78,5,16,39,177,90,25,244,37,100,95,40,20,98,177,88,99,99,35,178,102,204,101,190,213,194,194,66,36,18,225,184,146,41,39,163,51,142,205,155,55,159,63,127,158,66,96,163,163,
163,88,153,26,27,27,239,191,255,254,246,246,246,255,250,175,255,74,167,211,28,192,71,142,28,129,249,150,18,166,151,94,148,213,213,213,16,96,193,13,149,223,145,129,219,186,213,118,138,212,196,84,149,4,
163,202,59,241,149,225,172,237,210,240,233,241,120,42,238,190,251,110,114,215,144,62,128,77,137,136,134,93,143,218,40,45,46,46,130,92,69,105,93,182,226,72,164,201,243,142,237,169,66,160,204,0,141,80,149,
203,229,182,108,217,114,235,173,183,190,252,242,203,146,13,141,173,80,85,85,85,36,18,193,190,128,123,16,53,10,85,47,150,252,211,47,253,210,47,158,233,127,164,0,0,32,0,73,68,65,84,161,212,105,86,237,193,
230,193,154,198,74,154,185,104,21,139,197,80,40,20,137,68,130,193,32,144,47,44,69,74,172,25,223,180,179,179,51,26,141,102,50,25,240,180,204,70,35,124,125,142,30,115,162,82,15,87,206,61,176,247,229,74,
176,70,136,3,60,22,238,239,204,230,108,119,135,77,196,5,140,90,107,131,120,117,117,117,34,145,144,107,128,138,242,18,122,174,169,169,121,255,251,223,15,186,174,204,220,213,46,85,226,18,78,174,69,166,209,
17,123,201,172,30,207,24,231,100,182,52,54,54,94,188,120,81,222,62,234,4,97,167,143,226,146,196,187,224,182,238,30,154,101,124,196,222,5,73,180,19,55,92,237,75,240,233,124,178,88,44,162,187,149,201,187,
57,149,164,162,164,83,62,4,219,13,217,138,98,237,170,7,24,221,214,214,182,180,180,212,223,223,191,99,199,142,80,40,164,254,159,168,183,212,160,144,83,64,225,162,184,116,200,82,129,120,72,52,38,26,141,
50,189,99,247,128,138,206,120,31,120,146,121,189,222,137,137,9,204,83,172,121,103,207,158,245,249,124,216,176,142,142,142,174,174,174,118,119,119,255,234,175,254,42,254,10,57,138,202,202,74,191,223,223,
208,208,208,208,208,16,137,68,80,165,172,169,169,193,57,56,57,130,203,133,223,108,139,117,42,86,71,34,17,202,103,90,27,130,120,169,173,73,253,187,22,206,15,124,224,3,48,3,70,108,98,239,156,116,137,199,
43,1,176,2,27,93,88,88,232,232,232,80,176,29,182,117,178,225,91,246,140,57,217,209,19,218,198,203,155,154,154,110,191,253,246,179,103,207,38,18,9,12,223,186,186,186,80,40,20,14,135,77,11,65,171,162,174,
25,157,177,252,42,7,238,229,229,101,196,229,185,185,57,124,186,185,109,145,61,44,216,52,85,87,87,215,212,212,180,182,182,78,78,78,210,5,67,149,107,202,203,203,183,109,219,6,43,222,197,197,69,218,125,170,
133,33,155,205,194,163,218,154,79,1,6,149,213,54,28,133,66,1,249,236,218,163,115,161,80,72,36,18,102,20,38,159,95,105,40,171,120,135,138,188,138,137,42,131,227,76,176,214,3,229,51,187,119,239,190,235,
174,187,234,234,234,20,211,0,205,99,38,136,65,165,1,171,64,187,2,160,173,213,66,51,70,3,245,42,149,74,216,150,205,206,206,114,192,147,95,15,98,236,212,212,148,146,31,130,189,150,140,29,214,208,44,71,32,
208,3,44,114,102,93,72,141,97,165,246,151,207,231,71,70,70,184,78,67,198,128,108,57,66,198,124,70,54,133,169,56,14,149,2,190,149,147,250,40,126,6,131,193,187,238,186,235,254,251,239,71,39,26,147,80,169,
175,192,16,35,71,175,12,190,170,121,13,155,66,240,14,165,101,7,122,187,40,35,85,85,85,133,125,167,149,159,94,95,95,63,55,55,151,78,167,229,149,60,121,242,36,18,249,134,134,134,150,150,150,92,46,119,239,
189,247,98,215,130,157,1,22,39,148,202,89,27,119,10,175,78,123,53,19,119,182,70,234,98,177,24,141,70,33,113,5,138,186,233,56,177,118,197,209,138,189,123,247,202,230,40,85,112,64,169,58,149,74,129,69,40,
249,237,32,183,241,54,208,119,93,178,158,165,170,128,147,150,10,149,103,209,54,2,55,128,123,239,189,247,181,215,94,195,166,18,13,90,214,118,97,110,102,21,255,201,36,63,244,246,246,162,21,21,140,17,217,
98,47,121,35,46,125,241,168,11,97,219,139,147,76,38,147,216,164,168,74,122,125,125,125,87,87,23,205,189,80,127,87,243,97,101,101,101,116,116,148,206,176,166,233,1,50,47,217,212,135,111,74,90,250,218,3,
116,50,153,132,201,147,85,254,205,170,229,40,143,229,229,101,200,122,72,145,101,240,118,228,185,85,86,86,206,207,207,163,251,203,138,150,52,53,53,221,115,207,61,64,156,77,153,83,54,115,171,198,19,198,
104,54,4,154,74,73,78,209,89,158,134,156,66,136,5,56,213,96,48,56,50,50,130,233,141,59,136,78,31,252,154,78,167,145,250,169,214,106,198,104,211,154,192,148,174,71,140,46,20,10,108,134,118,65,33,64,4,100,
116,30,31,31,87,154,115,196,112,165,134,145,220,164,202,36,137,115,13,218,23,178,153,222,26,41,36,217,31,78,181,93,93,93,55,223,124,115,48,24,204,231,243,233,116,90,102,232,170,211,85,166,204,78,197,39,
64,127,178,113,6,149,21,214,96,101,233,213,108,242,100,37,6,227,144,179,242,220,185,115,128,158,124,62,95,87,87,215,254,253,251,129,182,59,237,8,229,6,75,69,91,85,142,86,137,130,75,226,44,227,251,174,
93,187,252,126,127,58,157,70,141,93,134,23,179,189,208,106,100,252,179,0,125,235,173,183,170,133,151,63,23,23,23,19,137,4,146,8,120,192,200,8,187,188,188,220,214,214,198,255,7,94,166,86,114,217,55,97,
213,35,149,141,76,156,30,104,99,57,114,228,8,188,118,204,158,43,9,192,75,219,118,179,119,153,71,119,119,55,230,27,188,132,77,145,85,153,23,88,213,59,241,117,136,46,33,70,147,27,39,149,252,58,58,58,0,197,
224,133,200,158,148,139,235,244,244,52,224,123,107,250,140,189,63,85,144,20,137,109,105,105,9,205,35,238,26,193,60,0,154,91,197,203,77,237,2,25,239,248,164,223,239,103,87,11,169,254,114,23,207,214,68,
69,185,195,225,245,122,223,251,222,247,222,114,203,45,12,61,86,222,46,58,187,172,58,235,212,187,176,38,209,46,1,218,105,54,2,225,5,4,215,208,208,192,78,43,26,51,35,177,128,102,155,41,127,129,254,29,151,
196,217,172,246,160,134,44,139,219,102,26,33,155,224,243,249,252,196,196,132,68,117,137,236,193,183,84,165,207,38,159,149,193,20,111,130,178,182,181,121,82,61,207,54,107,46,66,77,77,77,123,246,236,217,
181,107,215,226,226,34,88,201,242,133,44,192,90,223,144,32,39,56,124,152,236,203,203,203,100,130,1,124,192,23,167,44,148,2,85,228,27,86,85,85,5,131,193,64,32,16,14,135,215,175,95,95,85,85,117,230,204,
25,250,61,185,232,114,88,67,170,178,155,176,74,121,48,61,90,11,196,177,178,178,130,146,102,161,80,88,183,110,157,20,186,82,17,198,90,105,84,243,218,107,34,164,43,43,43,220,68,160,87,45,24,12,18,232,224,
106,0,181,39,150,236,24,104,212,198,74,202,74,168,37,87,201,30,74,169,210,138,138,138,112,56,140,101,214,36,2,203,159,149,149,149,166,124,135,138,83,43,43,43,233,116,26,134,85,196,91,76,129,2,73,165,144,
226,38,92,12,10,133,194,226,226,162,36,87,109,218,180,201,239,247,143,141,141,177,151,193,227,241,40,1,223,82,169,116,229,202,149,109,219,182,241,173,64,197,147,8,157,185,114,86,85,85,177,185,134,197,
110,238,4,103,103,103,163,209,168,187,43,7,181,119,169,44,108,238,212,60,194,61,199,84,179,227,147,11,11,11,248,130,192,242,36,193,70,98,74,62,159,47,16,8,48,229,196,215,217,184,113,227,129,3,7,24,154,
21,161,147,93,157,170,251,203,156,30,192,28,144,149,88,19,109,213,76,200,73,165,204,168,164,234,27,56,85,193,96,48,26,141,202,118,27,58,63,169,58,161,20,32,156,156,156,108,105,105,113,79,159,85,154,12,
233,71,212,238,21,105,74,66,139,144,201,134,156,44,49,4,57,189,211,233,52,48,34,147,81,170,154,69,113,109,7,7,7,239,188,243,78,233,104,108,173,171,75,244,143,157,192,82,47,44,16,8,220,115,207,61,133,66,
97,112,112,240,216,177,99,144,117,150,99,88,129,144,42,244,160,73,130,72,17,180,125,106,107,107,177,116,153,130,215,230,236,160,168,30,78,6,87,32,153,76,2,143,54,145,92,89,217,83,170,12,114,217,83,225,
200,42,129,164,28,229,157,88,28,8,134,176,199,11,133,66,170,33,69,25,10,90,37,225,60,194,117,250,103,90,28,120,205,194,194,66,58,157,6,113,29,203,157,207,231,243,251,253,164,200,40,21,208,153,153,25,244,
11,177,33,197,68,48,8,67,59,109,124,100,115,182,84,46,253,222,247,190,247,31,255,241,31,82,59,198,201,7,211,235,245,162,228,170,182,204,178,52,28,139,197,84,220,84,110,223,208,189,149,23,78,18,95,8,77,
102,50,25,197,191,105,105,105,105,104,104,184,112,225,2,248,194,128,216,212,146,184,176,176,48,50,50,66,235,79,42,151,187,171,246,84,85,85,129,32,104,170,203,79,79,79,135,66,33,211,238,196,100,140,0,125,
86,244,53,5,62,168,189,155,169,230,76,117,64,92,10,185,233,83,227,44,26,141,14,15,15,203,241,186,117,235,86,211,134,70,209,93,249,110,74,43,82,37,56,200,194,128,117,88,179,36,83,214,206,244,16,144,251,
202,154,154,26,80,134,182,111,223,254,198,27,111,72,200,56,30,143,103,179,89,180,186,57,241,202,185,24,175,37,76,99,141,153,152,152,192,78,92,197,92,121,164,211,233,100,50,73,42,136,116,141,32,7,52,147,
201,132,195,97,83,214,67,222,208,242,242,242,133,133,133,177,177,177,150,150,22,169,199,100,174,85,138,148,9,196,159,246,64,100,205,19,166,216,182,109,219,246,237,219,199,199,199,251,251,251,251,251,251,
153,238,144,87,110,54,208,82,165,93,158,51,180,33,21,35,64,129,27,152,77,236,11,147,21,90,146,252,164,19,136,25,49,25,136,20,28,42,185,143,214,194,187,124,67,134,50,119,22,7,70,96,103,103,39,173,217,173,
218,82,106,255,97,138,40,225,139,151,74,37,47,80,2,212,202,56,7,80,201,173,175,175,231,166,195,106,11,59,51,51,211,221,221,13,109,42,74,243,73,16,3,195,194,236,243,86,78,22,232,133,149,33,254,251,223,
255,254,151,190,244,37,174,246,50,121,116,170,135,202,86,34,115,54,170,248,142,111,173,242,104,62,99,246,209,243,242,193,74,82,141,108,159,207,183,111,223,62,104,63,145,6,167,214,255,233,233,233,112,56,
28,8,4,166,166,166,104,174,99,238,55,85,178,64,101,69,137,77,227,241,248,248,248,250,245,235,61,54,155,115,201,102,145,196,35,151,254,17,165,227,172,14,8,90,202,165,75,217,130,200,113,230,243,249,40,228,
230,241,120,222,120,227,13,217,12,101,134,105,201,176,118,226,59,243,175,213,213,213,160,66,90,131,50,69,51,172,77,207,230,14,3,87,18,62,18,193,96,240,228,201,147,232,75,90,123,239,15,122,61,214,152,71,
227,36,175,92,185,210,211,211,131,101,94,205,85,172,229,202,97,139,189,109,178,232,159,76,38,225,29,193,60,26,86,129,204,171,106,107,107,75,165,210,204,204,76,111,111,239,230,205,155,107,106,106,8,19,
75,9,114,107,175,4,20,193,176,135,147,39,169,230,111,91,91,91,123,123,251,161,67,135,250,251,251,47,94,188,72,245,59,25,175,149,232,174,180,186,247,251,253,152,44,216,155,162,172,194,102,25,108,217,25,
55,77,9,7,198,125,20,249,205,73,167,102,19,226,157,140,134,74,34,195,201,87,143,17,198,26,16,20,0,197,127,6,30,224,164,74,106,213,81,50,183,245,21,21,21,222,241,241,241,76,38,67,154,14,64,6,112,80,152,
207,34,112,155,56,105,121,121,249,204,204,76,107,107,171,172,18,88,171,94,170,3,85,165,141,72,192,89,93,60,122,244,232,147,79,62,201,86,43,172,153,228,223,168,24,45,89,7,166,51,169,34,60,57,53,91,115,
103,71,90,162,140,122,178,55,4,240,153,170,209,225,84,183,108,217,18,139,197,164,57,172,60,73,40,141,244,244,244,76,79,79,43,97,41,39,86,44,90,203,156,86,199,88,44,6,90,174,19,217,11,188,105,153,147,170,
189,133,75,143,223,202,202,10,186,129,170,171,171,225,137,39,169,211,148,230,81,153,41,174,112,48,24,36,147,189,172,172,44,145,72,156,61,123,118,199,142,29,214,140,27,25,171,106,207,181,146,157,121,182,
129,64,0,12,116,43,252,231,162,253,36,207,31,140,82,180,132,192,139,4,125,176,107,143,206,56,230,230,230,48,95,220,201,118,170,102,56,52,52,180,113,227,70,234,223,203,107,133,80,226,243,249,32,229,129,
64,70,113,5,180,116,17,138,109,107,107,147,226,7,170,177,98,121,121,25,54,199,18,168,81,2,17,102,236,0,202,15,226,63,154,191,21,175,89,13,197,64,32,112,240,224,193,67,135,14,13,12,12,12,12,12,76,77,77,
49,39,147,27,80,229,54,7,191,115,191,223,143,49,6,159,26,39,184,79,238,104,205,100,19,20,82,137,155,89,115,219,66,161,192,232,161,98,52,241,58,217,108,162,18,103,41,188,229,100,237,168,182,191,238,42,
240,46,218,15,239,130,7,50,153,140,44,47,212,214,214,54,52,52,208,219,6,33,91,57,47,200,248,50,61,61,29,141,70,173,138,72,18,128,118,233,39,164,186,27,98,244,192,192,192,103,62,243,25,105,139,135,38,111,
116,18,242,29,64,217,145,51,147,226,253,214,140,18,249,181,218,237,42,103,216,66,161,128,54,72,115,169,148,211,59,157,78,67,158,66,141,33,192,139,40,163,97,71,38,53,224,113,122,131,131,131,166,100,168,
12,202,242,87,191,223,143,241,100,114,60,240,233,87,175,94,149,162,122,230,23,143,197,98,4,248,172,64,51,131,26,152,230,190,119,14,89,205,147,76,18,143,225,251,174,150,64,58,5,3,28,192,217,94,188,120,
113,195,134,13,170,62,70,205,10,73,37,148,149,73,179,80,195,53,0,90,119,10,143,182,58,209,201,3,37,4,28,210,4,154,199,214,173,91,223,124,243,205,235,149,84,143,199,227,88,54,92,210,231,125,251,246,241,
241,230,205,155,235,235,235,107,106,106,66,161,208,134,13,27,80,31,243,120,60,161,80,72,2,38,78,44,29,5,86,154,30,20,140,206,44,102,152,178,233,166,6,25,95,11,214,57,222,25,92,29,176,134,164,200,176,117,
243,135,84,125,126,126,254,196,137,19,195,195,195,220,143,34,125,129,80,15,136,170,229,229,229,187,118,237,66,149,245,154,132,51,211,164,85,30,88,78,200,15,182,122,196,200,86,6,108,254,148,97,188,34,8,
168,101,128,217,146,122,210,106,194,91,86,86,214,217,217,201,233,191,22,129,255,107,168,217,201,186,92,125,125,61,75,171,180,182,146,231,36,107,172,8,46,165,82,41,145,72,192,13,203,148,107,65,81,213,202,
82,144,132,95,230,206,3,3,3,191,249,155,191,9,122,131,92,234,49,169,88,44,38,129,79,33,104,248,56,235,200,70,147,168,132,53,136,211,201,62,239,66,161,128,20,152,177,27,171,174,220,9,226,251,154,107,99,
38,147,129,108,19,251,107,21,17,157,159,232,212,248,174,22,127,191,223,15,48,196,122,13,177,207,77,167,211,84,230,85,179,26,70,241,214,102,110,184,231,96,147,84,95,95,143,77,186,25,227,228,202,36,43,138,
56,31,211,16,132,191,250,253,254,185,185,57,158,204,210,210,210,241,227,199,223,247,190,247,153,42,122,148,223,117,225,147,100,50,25,166,36,60,171,134,134,6,160,1,78,94,136,244,175,195,90,110,141,200,
138,248,225,245,122,161,157,123,189,49,58,145,72,128,31,102,134,230,19,39,78,184,16,34,149,71,137,220,29,90,187,249,85,140,224,190,88,230,58,204,69,168,243,105,245,95,86,85,56,190,51,246,136,156,206,184,
182,133,66,129,154,195,10,146,86,135,223,239,191,227,142,59,150,151,151,199,199,199,47,93,186,132,66,171,106,237,137,70,163,42,58,155,80,184,181,184,98,110,121,87,86,86,134,135,135,149,205,180,137,22,
42,216,90,21,108,212,86,198,44,114,90,203,140,214,230,6,220,68,217,114,241,115,58,201,254,148,163,227,243,249,234,235,235,85,147,146,204,139,173,180,71,124,64,34,145,128,23,178,106,97,114,225,75,170,250,
53,114,231,92,46,247,199,127,252,199,216,99,170,129,174,156,76,137,242,152,222,207,94,175,23,53,7,83,225,26,219,88,6,26,185,196,73,1,123,4,2,234,154,171,86,90,200,69,98,50,203,39,243,249,252,252,252,60,
251,6,137,122,99,122,88,135,178,217,173,163,168,135,216,93,74,147,11,217,245,131,139,63,50,50,178,109,219,54,107,128,142,199,227,202,62,21,104,102,56,28,110,108,108,132,65,28,20,194,84,92,150,246,216,
166,250,190,178,82,182,18,203,128,144,200,36,122,102,102,102,98,98,2,110,35,12,244,120,43,9,179,42,62,28,72,199,184,224,168,173,73,194,254,250,245,235,47,95,190,12,124,92,178,166,152,85,149,214,124,48,
82,183,180,180,196,227,113,197,43,88,203,49,51,51,211,212,212,132,91,166,26,190,93,50,98,213,102,102,106,192,91,149,45,149,206,178,140,65,160,199,73,141,99,171,26,140,53,45,101,158,193,189,17,109,159,
40,0,130,91,47,197,157,229,176,148,82,7,221,221,221,221,221,221,169,84,42,30,143,39,147,73,73,226,134,228,136,75,175,188,75,102,45,13,66,177,14,65,221,84,93,70,19,232,144,191,90,21,156,175,249,15,18,145,
55,209,103,245,90,167,187,230,185,78,147,111,47,9,109,50,207,87,45,155,146,140,98,222,149,165,165,165,92,46,87,95,95,239,68,115,54,159,84,96,107,69,69,197,194,194,194,35,143,60,114,241,226,69,126,103,
25,38,60,134,225,38,251,182,101,164,150,164,14,243,166,74,154,145,233,226,202,42,217,194,194,2,10,56,10,170,147,227,56,153,76,202,98,224,242,242,114,50,153,68,199,32,75,121,197,98,177,166,166,70,90,115,
42,220,121,112,112,112,112,112,240,166,155,110,106,107,107,115,186,68,181,181,181,115,115,115,78,155,143,178,178,50,168,158,55,54,54,154,196,219,177,177,49,20,211,84,3,8,156,56,58,59,59,161,212,5,66,149,
25,160,101,30,45,83,87,6,83,122,134,201,68,155,39,224,247,251,65,152,229,132,121,235,173,183,14,31,62,76,147,4,36,224,166,16,135,132,161,161,25,132,103,32,66,0,214,16,111,77,103,103,231,133,11,23,100,
15,139,123,142,124,205,3,30,75,16,26,189,174,99,117,117,53,22,139,65,145,82,6,104,94,34,107,204,5,119,72,250,254,185,68,103,43,115,22,45,66,212,96,80,68,46,211,207,208,37,118,144,182,15,96,68,246,142,
155,132,69,73,181,54,207,153,227,19,99,108,105,105,41,30,143,195,216,8,250,162,78,64,129,251,97,70,103,246,160,170,119,179,198,104,105,46,42,81,102,243,170,90,107,137,18,88,119,2,163,203,202,202,208,164,
102,94,16,39,238,179,123,212,246,66,43,196,76,114,85,251,159,41,48,40,35,69,42,149,10,6,131,214,4,153,213,91,23,41,59,175,215,251,196,19,79,92,186,116,9,215,78,150,251,212,120,50,103,5,118,175,4,100,172,
227,155,237,21,42,119,86,2,8,212,227,39,233,93,57,69,242,124,226,241,184,236,181,159,155,155,243,122,189,104,78,97,150,129,124,28,181,99,83,219,175,172,172,172,191,191,127,106,106,106,114,114,50,20,10,
29,58,116,168,171,171,139,165,118,254,155,223,239,119,105,7,199,49,52,52,4,153,27,185,158,37,18,9,48,217,157,184,25,169,84,10,40,68,83,83,19,135,148,164,214,89,93,84,100,183,180,164,168,155,202,130,56,
121,72,17,81,229,245,236,217,179,123,247,238,197,237,144,75,130,68,162,25,82,243,249,124,42,149,146,218,26,8,196,152,240,139,139,139,185,92,14,27,151,235,202,145,93,14,42,128,55,54,54,206,206,206,222,
64,140,158,153,153,161,208,163,68,45,156,98,46,144,113,217,100,224,36,119,101,18,105,153,175,121,222,241,60,85,81,15,41,151,85,76,81,241,112,101,139,10,202,48,138,151,198,125,155,220,51,97,48,88,247,217,
138,157,130,122,102,91,91,27,125,117,77,220,220,61,82,43,113,74,249,117,6,7,7,201,178,181,170,23,89,35,53,21,201,121,137,84,23,137,2,247,149,40,177,181,48,171,72,195,107,25,48,215,92,156,188,170,119,83,
181,36,57,73,190,202,7,21,21,21,208,99,149,109,132,46,68,5,249,60,128,227,63,253,211,63,61,117,234,20,17,28,39,74,175,233,168,36,255,68,33,93,101,121,133,183,202,100,50,18,229,144,12,124,117,32,89,3,218,
163,84,16,57,44,98,177,216,166,77,155,176,176,77,78,78,174,172,172,160,143,22,213,21,89,35,229,22,65,45,111,179,179,179,35,35,35,184,170,169,84,234,71,63,250,145,207,231,219,187,119,239,214,173,91,33,
172,67,167,122,9,113,224,201,96,48,24,10,133,252,126,63,20,194,142,30,61,122,254,252,121,153,152,120,60,158,201,201,73,74,23,89,3,52,151,192,177,177,49,114,179,128,21,202,40,172,204,100,165,39,139,106,
114,49,111,19,54,34,4,208,87,87,87,71,70,70,218,218,218,26,26,26,20,227,130,194,55,12,208,133,66,33,149,74,153,77,131,137,68,2,128,47,165,80,175,11,202,112,10,214,106,237,111,105,105,65,75,228,13,196,
232,217,217,217,72,36,194,209,123,226,196,9,105,46,172,132,222,137,26,57,217,59,184,8,22,50,20,42,25,25,62,96,85,214,44,109,89,147,104,236,5,77,234,164,44,8,243,29,8,9,226,150,153,136,168,25,134,176,35,
180,110,185,204,96,237,4,113,32,237,32,43,127,117,117,21,121,134,181,124,39,85,152,77,21,7,124,89,22,81,85,117,81,37,209,242,173,92,164,236,72,30,119,138,197,78,76,21,167,72,237,181,118,151,152,22,221,
46,161,150,170,5,236,166,179,22,190,20,3,129,0,244,103,63,251,217,23,94,120,65,118,84,203,162,156,19,145,219,106,98,166,122,79,84,214,32,177,33,117,62,242,196,32,98,27,14,135,205,64,47,127,157,155,155,
139,70,163,192,121,1,226,75,245,119,70,100,62,169,174,240,169,83,167,192,234,227,29,205,231,243,111,189,245,214,169,83,167,182,111,223,190,101,203,150,150,150,22,202,248,5,2,129,166,166,38,176,44,90,90,
90,164,88,1,170,231,175,191,254,122,123,123,59,97,241,98,177,8,167,112,229,108,162,68,236,248,15,32,2,163,54,139,226,33,233,1,100,22,155,250,150,88,92,9,122,154,245,49,143,199,227,247,251,161,160,68,145,
154,87,95,125,245,195,31,254,240,234,234,234,244,244,244,234,234,106,99,99,35,224,14,230,227,136,206,137,68,2,253,108,86,213,58,72,234,64,30,214,197,87,101,45,145,218,26,133,189,94,111,103,103,231,208,
208,144,231,250,15,248,85,3,138,97,161,82,141,34,37,136,202,212,213,44,253,187,108,31,153,208,64,176,155,202,180,28,198,36,30,88,115,103,83,138,8,234,2,76,50,216,29,83,42,149,216,106,196,8,37,25,205,18,
33,116,74,168,165,236,165,71,216,148,56,85,222,172,207,64,63,71,246,247,98,180,184,56,99,152,5,67,201,117,161,175,144,41,243,160,172,171,205,88,239,212,168,221,219,219,107,50,163,221,211,103,151,60,218,
107,229,225,74,88,195,42,134,162,34,120,121,121,121,50,153,4,33,90,225,36,210,228,208,60,94,121,229,149,151,94,122,73,110,157,144,183,154,61,23,214,70,3,247,95,205,153,99,93,63,136,235,211,173,167,88,
44,66,8,219,164,251,144,221,49,51,51,83,83,83,131,234,182,215,235,245,251,253,230,218,38,177,123,57,232,11,133,194,153,51,103,172,152,126,169,84,234,239,239,191,124,249,114,71,71,199,230,205,155,123,122,
122,142,28,57,66,184,25,220,178,249,249,121,16,72,151,151,151,175,92,185,114,236,216,177,124,62,15,127,0,92,129,201,201,73,179,131,195,236,165,230,147,185,92,14,96,37,130,117,38,147,65,108,149,58,253,
50,179,150,99,87,106,101,152,213,39,66,61,120,97,46,151,91,90,90,58,115,230,204,134,13,27,166,167,167,209,2,211,210,210,2,40,22,10,56,153,76,134,184,179,169,136,196,39,23,23,23,217,85,120,195,184,179,
203,128,9,6,131,126,191,159,62,103,215,27,163,231,230,230,192,141,33,66,42,115,103,115,85,64,168,194,93,176,230,95,214,199,184,14,120,0,140,81,70,103,151,46,53,51,207,197,243,208,13,151,34,13,176,245,
194,208,165,241,174,236,16,102,51,158,4,7,240,66,151,42,162,60,19,171,191,159,181,45,136,45,60,124,201,192,192,128,236,243,182,198,59,89,180,80,182,56,184,59,42,1,245,216,4,229,145,67,56,245,253,42,84,
192,105,153,185,38,18,109,9,208,230,242,34,211,73,162,51,146,210,168,82,66,86,23,209,126,106,6,29,169,35,33,31,76,77,77,253,193,31,252,129,84,175,39,144,162,122,82,93,146,8,229,212,101,10,249,75,5,12,
68,28,121,53,205,164,30,7,100,70,156,64,149,213,213,213,225,225,97,84,132,42,42,42,100,116,54,161,33,115,59,114,252,248,113,112,165,185,102,120,132,174,52,230,192,196,196,68,44,22,59,119,238,220,206,157,
59,123,122,122,168,32,142,48,58,53,53,117,225,194,133,193,193,65,234,174,13,14,14,66,217,64,226,27,86,79,85,217,176,71,169,13,2,238,252,166,0,25,128,123,48,76,155,90,198,140,251,102,119,47,97,244,84,42,
5,237,45,56,184,159,58,117,42,155,205,214,214,214,130,84,14,92,18,25,113,161,80,200,100,50,204,157,173,114,207,60,100,250,124,189,208,243,90,224,139,206,206,206,254,254,254,27,0,58,144,17,167,211,105,
80,101,36,145,195,204,157,101,18,93,44,22,217,224,96,122,135,171,41,0,194,50,175,57,150,109,206,56,248,51,89,163,176,233,128,199,44,152,25,52,2,25,251,212,232,137,197,221,45,215,108,206,92,185,205,151,
234,34,74,133,227,6,112,88,52,88,98,168,75,108,164,84,42,165,211,105,37,224,110,198,89,185,12,224,219,169,24,237,212,192,45,19,50,39,88,67,70,15,114,93,136,46,170,224,185,246,232,204,155,238,117,113,118,
144,196,103,5,2,72,180,154,15,230,230,230,128,190,169,40,111,109,107,206,100,50,255,242,47,255,98,202,238,145,94,109,98,109,230,126,77,41,239,160,222,40,89,177,242,59,47,44,44,128,64,46,69,79,156,2,116,
50,153,148,252,98,245,0,89,103,54,155,133,148,45,3,180,169,164,110,61,78,156,56,33,101,121,233,60,205,22,112,110,187,178,217,236,91,111,189,213,215,215,215,212,212,212,209,209,81,91,91,59,61,61,221,215,
215,55,60,60,108,46,147,3,3,3,59,119,238,156,159,159,7,125,194,201,11,74,73,143,163,124,135,133,77,161,243,72,91,114,185,28,60,153,164,20,14,175,60,250,209,101,181,80,45,207,112,208,0,103,25,195,61,149,
74,245,247,247,239,221,187,215,243,142,59,70,34,145,8,133,66,80,253,7,35,208,20,224,183,10,243,223,24,238,188,198,32,91,93,93,221,210,210,50,49,49,225,185,161,3,156,138,211,167,79,67,72,158,116,111,151,
2,32,40,204,210,216,219,202,134,38,111,82,46,147,233,116,26,242,243,212,29,83,175,149,20,96,143,205,171,20,20,38,166,207,72,129,17,209,36,164,203,76,66,98,181,82,107,95,118,208,96,74,186,152,88,59,137,
217,171,213,14,125,106,42,47,70,79,47,34,172,180,221,114,146,245,240,24,194,194,228,221,90,229,153,84,85,214,236,35,151,63,241,86,101,101,101,216,200,98,243,132,45,166,84,111,118,218,76,56,225,90,94,83,
127,206,138,23,203,52,94,18,60,100,140,46,20,10,249,124,30,205,26,10,104,86,40,202,194,194,2,54,242,153,76,6,37,35,217,123,194,171,102,37,234,91,159,36,227,88,217,166,201,48,205,34,158,252,70,106,121,
148,183,33,149,74,153,61,32,20,234,69,199,74,107,107,171,215,235,165,111,177,178,86,177,194,250,39,78,156,152,153,153,81,67,86,66,28,138,244,134,62,157,75,151,46,157,61,123,54,157,78,3,13,144,187,25,178,
146,71,71,71,163,209,40,10,182,178,49,207,90,30,68,35,47,174,15,238,154,52,228,102,15,5,77,167,160,184,162,124,211,165,235,135,21,86,163,7,29,154,152,113,85,139,197,98,58,157,158,152,152,0,110,142,151,
163,86,9,160,195,244,76,177,198,217,27,8,211,215,149,14,195,55,214,243,115,28,244,39,98,39,167,59,61,3,137,48,26,136,92,42,228,176,151,52,95,142,22,170,82,169,84,87,87,199,59,69,20,66,101,187,38,176,144,
205,102,49,186,208,242,199,233,195,173,45,30,72,158,146,18,167,100,155,6,1,107,26,92,173,145,245,108,70,103,185,255,144,209,25,83,108,100,100,68,70,88,54,64,170,246,116,73,68,49,219,152,157,210,231,107,
182,143,123,222,109,95,167,252,24,205,194,172,18,239,119,239,156,252,41,207,93,105,64,43,97,104,21,92,148,122,136,234,103,241,122,189,217,108,22,36,4,107,62,78,13,251,115,231,206,121,60,158,243,231,207,
99,248,194,83,135,204,30,83,112,195,41,255,103,64,49,69,20,101,71,131,226,219,242,242,41,89,91,117,218,201,100,18,30,110,242,170,145,192,235,241,120,166,166,166,246,237,219,71,209,18,107,116,86,250,36,
48,47,231,0,34,246,77,105,36,233,235,78,190,48,169,254,52,175,193,71,72,183,45,44,132,253,253,253,169,84,138,216,177,137,111,240,73,228,119,248,166,192,10,148,57,161,172,17,65,38,162,182,182,22,235,10,
199,34,94,82,81,81,65,227,46,107,78,4,69,233,92,46,7,69,255,218,218,218,154,154,154,84,42,213,214,214,198,175,9,243,92,170,252,72,110,134,213,180,219,61,118,187,176,232,214,120,76,78,78,66,139,252,231,
60,80,128,85,237,78,46,5,64,228,209,117,117,117,214,153,140,173,155,236,122,151,47,135,171,6,212,26,80,130,182,150,112,76,12,144,253,144,224,98,161,186,40,163,51,43,73,228,191,203,225,173,226,53,167,36,
148,58,214,72,115,182,254,27,238,169,245,79,56,61,66,28,18,2,166,245,173,226,240,73,245,5,252,84,134,226,10,220,88,93,93,173,173,173,133,117,20,172,0,96,249,4,117,192,182,182,182,214,214,214,195,135,15,
35,155,81,106,30,234,49,67,179,217,25,100,246,46,201,115,240,154,196,3,83,252,91,245,22,202,112,198,231,43,43,43,97,15,108,146,118,229,182,183,84,42,157,63,127,30,101,253,254,254,126,220,221,100,50,25,
12,6,165,20,150,162,184,57,229,255,63,51,39,247,122,61,14,246,22,242,230,249,253,126,108,231,77,154,186,25,166,115,185,220,194,194,2,251,119,121,239,185,153,66,147,27,244,104,92,86,56,124,199,133,133,
133,92,46,55,57,57,121,233,210,37,169,4,173,154,3,49,175,240,165,242,249,124,38,147,73,36,18,38,15,132,183,92,85,5,222,124,243,205,92,46,215,217,217,89,85,85,5,89,119,19,235,144,228,13,217,109,68,132,
84,54,245,49,91,33,155,138,178,12,166,20,142,245,102,97,254,212,213,213,33,239,11,133,66,204,224,198,198,198,58,58,58,144,86,195,243,37,149,74,65,236,216,35,100,176,204,58,161,181,114,232,18,172,215,104,
61,195,98,212,240,240,176,105,77,121,99,7,108,207,220,135,177,249,36,58,248,21,238,92,42,149,208,69,162,94,206,187,207,182,120,44,231,0,127,97,145,5,217,35,198,29,235,167,207,207,207,179,24,192,82,161,
42,8,49,47,102,140,150,213,96,230,88,120,16,8,4,100,7,153,25,137,152,206,59,69,103,37,193,108,238,101,37,139,131,17,80,201,67,43,182,156,220,64,135,66,33,148,109,154,155,155,145,105,117,119,119,163,61,
103,203,150,45,168,255,227,39,31,240,87,196,28,20,15,185,138,236,217,179,199,108,245,84,217,237,90,32,248,159,65,70,102,222,39,65,12,229,163,163,34,2,13,17,106,107,107,67,161,16,251,44,156,142,82,169,
116,230,204,25,248,116,93,188,120,81,94,193,84,42,85,95,95,143,193,129,100,220,138,114,152,213,18,146,64,157,252,44,228,128,128,158,0,230,12,242,26,149,68,171,237,12,184,116,178,233,128,209,25,207,204,
206,206,246,246,246,90,109,58,153,50,47,44,44,192,38,188,162,162,226,205,55,223,148,11,62,25,14,4,157,217,53,7,251,71,230,251,102,140,102,218,34,197,184,207,157,59,55,61,61,189,126,253,122,64,228,96,158,
178,223,87,70,234,165,165,37,170,91,96,53,98,143,31,225,17,57,63,165,92,137,42,14,35,19,145,17,141,151,20,185,12,202,140,80,204,225,75,202,203,203,231,231,231,225,26,131,18,16,155,86,178,217,44,164,110,
157,74,133,215,12,208,55,150,56,23,139,197,241,241,113,42,247,255,143,28,231,206,157,123,240,193,7,175,217,31,104,173,115,16,97,195,190,19,226,224,234,63,65,139,196,53,196,85,37,119,30,232,45,218,58,72,
67,70,164,6,79,73,205,17,244,148,34,214,152,86,200,234,25,143,80,241,150,29,134,252,21,97,193,37,36,49,81,144,13,22,42,65,118,66,132,57,62,57,161,56,109,9,100,193,39,23,76,103,168,180,215,213,213,5,131,
65,175,215,27,10,133,66,161,16,86,35,6,95,198,95,60,80,84,125,83,37,209,243,142,183,67,46,151,147,202,66,60,103,201,99,89,251,114,174,112,66,175,10,43,74,139,67,37,212,242,128,58,12,84,234,81,163,47,22,
139,249,124,30,188,28,124,121,169,244,95,86,86,118,225,194,133,249,249,121,156,247,192,192,0,157,219,89,65,198,14,151,180,89,57,28,173,58,173,184,25,136,44,78,121,129,82,13,199,122,91,83,83,3,80,21,157,
14,170,13,148,33,102,110,110,14,183,86,130,179,242,13,97,24,44,221,100,24,118,193,79,144,153,200,226,226,226,177,99,199,100,221,21,183,83,17,209,0,215,162,164,102,26,57,82,127,74,62,137,201,3,214,221,
234,234,234,185,115,231,182,110,221,202,86,14,176,134,1,215,200,230,61,126,83,236,142,193,90,97,222,170,200,51,86,28,144,80,117,77,77,141,53,229,4,9,100,101,101,101,106,106,170,170,170,138,178,144,76,
100,206,156,57,3,216,84,30,133,66,97,106,106,10,60,63,167,4,121,45,253,41,215,149,56,199,227,241,241,241,241,27,227,108,184,195,113,82,12,211,115,45,177,58,153,121,0,77,198,96,32,225,143,103,136,222,34,
142,162,202,202,202,124,62,143,109,19,46,145,185,47,132,7,74,121,121,249,200,200,200,200,200,72,99,99,99,99,99,99,67,67,67,91,91,219,186,117,235,22,22,22,228,126,87,70,100,166,201,210,102,133,249,138,
25,199,203,202,202,164,159,128,9,101,152,212,108,153,42,57,85,11,164,33,11,102,61,58,120,145,204,114,227,229,243,249,16,103,17,127,249,147,79,162,180,168,4,161,36,135,74,226,129,102,199,172,156,17,221,
221,221,103,206,156,145,16,188,66,86,205,228,210,105,197,82,172,240,159,234,104,155,46,188,166,77,181,196,88,161,165,93,87,87,135,108,200,220,206,227,250,210,165,27,59,98,76,69,136,231,226,227,47,93,186,
84,91,91,155,203,229,100,230,11,175,101,92,104,69,26,55,111,21,181,208,172,236,2,115,14,72,185,31,153,83,32,184,192,64,214,36,183,207,205,205,173,91,183,206,202,93,69,119,201,226,226,162,52,207,93,88,
88,128,203,148,9,64,191,246,218,107,92,237,205,196,121,113,113,17,14,179,208,18,145,116,61,185,119,81,182,235,242,175,125,125,125,248,235,201,147,39,59,59,59,153,5,32,28,207,207,207,163,98,3,152,155,139,
13,38,3,80,54,228,188,178,37,65,85,87,172,116,78,44,213,184,233,120,159,165,234,0,0,17,64,73,68,65,84,248,58,248,20,254,231,236,236,44,242,110,88,73,241,173,226,241,248,169,83,167,54,108,216,208,214,214,
134,215,130,106,6,83,218,120,60,94,93,93,141,44,82,229,203,82,154,206,154,74,95,111,49,112,120,120,248,198,40,207,107,12,208,215,149,59,171,23,210,32,149,255,0,157,116,68,40,153,1,160,179,137,171,190,
100,10,41,248,174,80,40,20,10,133,153,153,153,100,50,217,212,212,196,142,124,69,10,160,76,46,42,13,28,15,156,236,184,155,252,149,56,53,251,221,93,16,103,214,51,212,236,6,65,222,239,247,83,136,213,132,
2,136,176,55,53,53,193,148,93,254,39,175,9,46,5,208,24,249,164,108,185,96,134,36,123,109,204,184,172,18,103,137,4,202,12,111,207,158,61,214,153,98,21,14,52,251,39,77,25,88,175,213,114,219,26,151,43,43,
43,3,129,0,116,2,93,248,100,10,0,193,7,127,241,139,95,252,214,183,190,213,210,210,2,209,216,173,91,183,14,14,14,34,215,134,176,145,20,8,6,0,71,148,67,201,21,73,121,13,143,16,108,188,102,81,17,228,51,108,
198,213,154,6,46,51,102,190,180,148,133,230,125,67,67,131,181,35,6,155,196,137,137,9,168,209,167,211,105,58,137,48,173,150,125,222,199,143,31,87,85,65,140,30,120,217,16,175,48,161,61,185,165,48,139,186,
124,109,127,127,63,7,104,95,95,31,206,74,238,203,10,133,2,182,99,176,64,102,239,9,26,70,100,51,36,97,68,151,190,91,117,77,144,44,67,246,23,8,18,97,34,40,20,146,69,131,181,33,157,78,159,57,115,166,88,44,
94,190,124,25,17,71,34,24,136,212,64,225,81,67,38,223,14,225,219,5,119,254,133,20,3,93,144,86,83,47,105,45,209,153,246,87,114,204,35,4,227,222,73,122,3,136,198,16,252,35,58,12,164,152,105,135,132,95,235,
234,234,48,239,186,186,186,170,171,171,85,129,75,150,208,57,18,24,172,21,220,161,26,91,202,203,203,163,209,168,244,237,116,63,84,45,116,114,114,50,157,78,123,189,222,249,249,249,202,202,74,170,108,170,
232,12,226,157,215,235,61,115,230,140,26,153,212,71,148,121,12,78,82,102,102,236,243,36,149,144,92,3,50,169,84,217,70,201,221,224,104,106,106,146,32,184,217,88,239,177,25,120,91,163,51,147,54,89,186,243,
90,97,101,185,91,199,78,42,18,137,0,242,71,116,99,0,50,107,140,50,172,3,110,255,193,15,126,240,252,243,207,251,124,190,185,185,185,99,199,142,193,252,13,241,23,37,56,92,38,185,128,160,169,196,105,237,
149,219,70,169,168,235,4,116,240,37,24,172,240,250,83,208,42,14,108,127,150,223,57,144,107,92,189,122,149,118,130,242,36,253,126,255,202,202,202,229,203,151,155,154,154,88,112,115,178,45,63,126,252,56,
140,98,137,223,33,139,49,241,101,213,221,163,162,176,18,69,225,165,158,155,155,147,182,167,125,125,125,224,77,171,22,109,242,246,176,19,196,69,70,142,70,78,30,190,32,68,115,148,153,128,59,107,88,202,10,
34,131,134,185,95,177,88,68,139,154,220,121,244,247,247,115,53,58,118,236,216,237,183,223,78,236,162,40,14,40,142,134,66,33,0,98,220,156,253,252,44,186,255,217,98,160,211,113,233,210,37,245,17,107,140,
206,102,61,220,231,243,161,204,99,146,26,145,15,34,150,225,230,114,242,178,2,44,75,100,216,171,245,244,244,96,59,101,149,194,144,64,135,34,234,201,24,205,140,21,255,19,8,4,32,235,120,99,187,141,150,150,
150,166,166,38,104,96,229,114,185,100,50,57,51,51,19,8,4,130,193,32,125,97,176,215,193,53,177,18,54,100,83,133,74,156,217,156,130,10,7,49,13,38,206,178,99,203,250,83,133,154,230,230,102,172,136,106,155,
190,70,154,138,42,153,178,196,202,203,238,61,119,238,220,190,125,251,172,41,176,215,235,141,68,34,88,15,21,7,208,44,39,90,225,14,236,235,255,246,111,255,86,214,169,212,55,68,18,45,113,67,146,115,37,103,
83,2,29,50,81,50,37,155,157,50,104,10,35,32,184,83,122,74,174,123,204,92,176,73,95,90,90,26,26,26,42,47,47,239,232,232,80,161,31,75,110,54,155,205,100,50,123,247,238,69,29,76,126,125,25,70,193,175,144,
75,5,135,139,12,196,242,129,164,46,153,196,71,217,118,136,7,151,47,95,86,88,80,95,95,223,190,125,251,120,113,148,205,21,118,42,208,50,69,230,139,226,45,255,103,113,113,17,91,28,182,95,174,113,142,193,
142,26,229,196,137,137,137,108,54,11,228,138,131,106,101,101,101,104,104,72,90,241,166,211,233,179,103,207,110,222,188,153,1,90,9,113,76,78,78,6,131,65,228,122,86,233,253,95,120,49,208,253,227,214,158,
59,91,155,253,42,43,43,225,164,225,242,53,81,16,242,188,35,137,46,71,11,110,174,68,165,235,234,234,32,25,161,222,208,218,35,71,236,66,14,15,5,116,96,80,85,86,86,186,104,61,175,145,255,139,206,47,191,223,
63,63,63,63,57,57,137,116,109,97,97,193,235,245,6,131,193,96,48,8,182,9,198,179,18,138,82,171,11,66,39,131,56,183,2,236,101,147,194,35,132,28,25,169,77,121,53,51,130,161,102,195,79,63,112,224,128,123,
56,118,130,161,229,133,229,207,178,178,50,239,243,207,63,95,40,20,110,191,253,118,137,105,64,148,39,18,137,72,71,50,201,233,97,16,199,36,148,172,236,68,34,1,19,32,168,47,126,231,59,223,153,155,155,195,
170,46,73,175,248,245,208,161,67,116,131,53,91,42,24,163,37,15,28,123,70,82,88,156,244,58,204,209,191,178,178,2,206,128,106,100,183,202,181,224,223,146,201,36,208,213,120,60,78,73,207,229,229,229,197,
197,197,112,56,76,100,112,114,114,18,214,83,146,170,40,19,150,241,241,241,129,129,1,39,211,91,105,83,98,2,23,38,207,212,154,113,95,185,114,69,141,209,177,177,177,246,246,246,112,56,44,23,103,70,106,252,
196,90,181,184,184,8,43,247,134,134,6,202,107,144,57,144,205,102,107,106,106,2,129,0,251,113,84,157,86,98,247,128,107,112,95,70,71,71,115,185,28,107,89,184,113,165,82,233,234,213,171,240,82,146,117,255,
129,129,1,208,75,77,197,125,196,232,88,44,86,93,93,93,95,95,111,242,160,255,47,20,3,93,14,170,147,187,72,211,57,165,20,0,223,160,184,198,97,111,149,181,227,236,64,13,131,69,48,188,73,93,93,29,212,89,193,
228,5,239,211,69,214,78,129,6,114,28,50,76,115,124,98,73,88,89,89,217,180,105,147,233,197,183,70,246,130,117,139,227,121,183,43,96,42,149,202,102,179,36,125,122,60,158,87,95,125,245,236,217,179,208,141,
136,197,98,101,101,101,175,189,246,26,52,38,233,51,73,16,67,134,99,102,205,40,149,169,72,45,243,104,211,125,88,146,23,110,186,233,38,83,173,201,69,248,201,170,145,132,175,143,133,92,198,104,143,199,227,
45,149,74,47,188,240,194,248,248,248,175,255,250,175,23,10,133,112,56,12,41,203,229,229,101,164,63,220,252,194,61,104,108,108,76,209,81,185,21,229,230,20,83,43,147,201,12,14,14,146,21,160,150,32,233,121,
174,84,232,100,226,0,130,26,9,43,196,194,152,125,51,11,70,4,71,18,1,70,23,254,19,105,23,42,84,74,39,207,93,47,28,228,92,156,228,236,236,108,67,67,67,62,159,103,211,1,155,181,16,137,182,108,217,226,100,
54,152,76,38,255,241,31,255,241,154,115,146,75,5,147,77,86,92,205,142,33,245,32,22,139,41,186,33,190,212,192,192,192,193,131,7,149,251,129,100,113,240,178,151,74,165,217,217,89,232,172,34,101,150,164,
37,80,223,80,4,39,16,137,166,228,242,242,114,16,93,234,235,235,193,90,1,91,96,114,114,146,81,24,111,85,93,93,93,93,93,61,56,56,136,13,166,172,183,96,10,157,60,121,114,223,190,125,106,80,201,24,13,41,37,
176,77,110,32,113,254,95,45,6,186,103,208,107,204,157,21,194,80,91,91,139,241,236,100,133,197,93,26,178,87,38,161,126,191,31,36,75,25,190,3,129,0,50,83,180,242,58,153,185,88,25,23,76,238,36,79,131,117,
17,36,118,209,104,20,70,227,55,16,157,229,201,72,243,45,110,85,173,44,0,156,201,238,221,187,203,202,202,246,238,221,139,48,178,127,255,126,236,177,138,197,34,146,197,138,138,138,153,153,153,138,138,10,
212,225,1,146,48,137,102,224,150,185,179,181,161,215,26,163,101,190,168,170,5,238,176,134,41,49,196,2,213,187,220,208,241,241,151,46,93,58,125,250,244,47,255,242,47,87,84,84,64,204,129,179,66,98,130,139,
139,139,146,184,46,243,68,213,70,89,42,149,64,249,178,118,85,170,18,1,107,119,234,236,171,170,170,32,87,134,188,0,156,107,58,238,160,28,129,16,0,173,69,92,53,159,207,135,75,153,207,231,37,78,34,169,99,
38,220,166,78,12,94,30,220,125,140,143,143,131,166,205,107,55,50,50,2,92,172,162,162,98,114,114,82,114,30,121,89,6,6,6,94,126,249,229,211,167,79,223,192,118,15,23,95,194,71,46,233,243,240,240,176,218,
232,112,7,16,143,199,131,193,32,135,56,6,37,66,167,220,67,80,222,1,20,236,170,170,42,240,91,208,8,71,62,34,226,175,207,231,171,171,171,99,23,214,212,212,20,91,224,176,91,202,231,243,8,4,193,96,16,217,
55,106,203,83,83,83,133,66,129,65,135,6,210,120,159,100,50,57,53,53,21,10,133,156,84,70,129,111,44,44,44,64,185,237,186,18,231,255,237,98,160,203,49,48,48,208,213,213,229,18,157,85,245,219,227,241,212,
214,214,66,224,197,100,118,170,206,11,230,92,200,63,8,71,212,213,213,97,0,115,108,251,253,126,172,109,243,243,243,92,23,93,172,255,84,196,148,96,180,137,123,4,2,1,165,72,190,246,213,75,114,1,60,194,222,
129,142,201,42,175,82,200,128,252,19,12,21,209,179,138,171,209,220,220,92,94,94,222,210,210,66,124,3,226,124,119,222,121,231,212,212,20,134,119,60,30,71,150,3,184,102,105,105,201,26,169,213,10,65,143,
121,201,226,120,207,123,222,227,30,88,204,200,195,190,80,149,59,255,52,64,247,244,244,108,221,186,181,189,189,29,243,124,211,166,77,184,226,166,127,10,235,12,146,41,44,87,84,41,190,209,223,223,15,171,
8,101,76,160,120,36,204,176,60,194,152,138,231,7,150,30,184,213,128,210,8,12,97,150,66,65,130,153,32,229,44,16,154,185,50,91,53,182,221,247,164,201,100,82,113,107,226,241,56,76,151,241,89,139,139,139,
80,52,174,173,173,13,4,2,35,35,35,27,55,110,196,215,95,92,92,60,125,250,244,247,190,247,189,68,34,113,195,120,156,220,251,112,122,40,214,29,137,31,116,93,49,197,106,251,250,250,110,190,249,102,153,56,
211,184,132,47,65,248,198,96,165,74,28,194,34,210,94,149,106,161,193,164,186,186,218,239,247,179,116,147,78,167,227,241,56,156,106,89,131,149,169,7,253,15,65,209,65,122,40,141,2,60,30,207,133,11,23,246,
239,223,79,22,176,18,110,38,232,49,51,51,83,95,95,239,84,70,254,133,20,3,221,99,16,83,96,167,10,54,195,13,186,42,128,35,73,113,65,249,18,89,147,199,192,192,133,69,100,65,221,175,162,162,194,231,243,33,
9,69,151,47,88,58,112,129,168,172,172,28,27,27,115,105,29,80,180,48,57,247,37,103,131,162,119,64,180,175,247,144,140,41,245,233,112,216,112,234,242,160,53,135,41,195,148,72,36,176,123,64,24,225,246,29,
255,12,54,116,69,69,197,79,126,242,147,64,32,128,242,99,103,103,167,242,6,67,133,134,91,13,204,119,20,165,84,6,189,99,199,14,171,32,181,59,166,97,22,27,148,102,239,207,2,244,251,223,255,126,166,48,241,
120,188,172,172,172,187,187,91,82,26,77,227,87,89,4,35,45,151,145,186,84,42,93,184,112,33,159,207,155,28,76,19,206,71,98,197,136,76,129,46,137,78,114,123,158,203,229,160,169,86,81,81,129,43,203,125,61,
70,42,146,56,120,32,169,246,22,171,48,174,117,103,7,131,65,133,108,210,41,131,23,142,147,7,117,194,163,71,143,110,216,176,33,149,74,29,61,122,244,245,215,95,231,215,255,159,58,16,152,48,31,176,47,99,171,
231,196,196,132,139,1,79,161,80,152,156,156,140,70,163,72,63,25,49,177,124,122,222,237,168,141,92,88,30,216,21,162,99,88,73,247,66,62,20,165,54,89,122,117,113,38,195,170,41,221,108,75,165,82,36,18,89,
183,110,29,104,85,208,77,237,236,236,84,1,26,255,41,125,203,82,169,212,210,210,82,48,24,252,191,83,12,116,185,119,74,18,218,170,32,138,38,64,244,245,56,165,219,114,84,99,7,131,97,128,0,141,207,162,219,
72,109,109,45,104,66,109,109,109,210,227,24,25,122,79,79,207,240,240,48,21,150,229,116,48,115,38,201,78,147,53,18,140,156,222,222,94,23,69,36,151,52,72,229,206,106,89,149,100,12,39,80,72,189,54,147,201,
36,147,73,244,52,32,152,176,90,214,212,212,196,94,74,4,171,108,54,59,63,63,143,191,130,210,23,8,4,208,233,83,93,93,13,159,79,76,121,115,92,73,255,188,123,238,185,39,157,78,131,54,234,100,113,235,82,30,
148,61,132,102,69,205,171,94,28,143,199,231,231,231,183,110,221,106,74,57,171,59,164,188,80,25,40,71,70,70,208,93,42,151,92,112,164,152,204,51,171,69,86,37,71,158,244,239,192,14,2,150,54,120,50,159,207,
131,95,193,6,19,132,66,66,49,86,9,105,23,137,69,5,1,23,139,69,56,128,152,163,161,88,44,38,147,73,112,162,77,209,153,255,252,207,255,236,235,235,123,253,245,215,43,43,43,131,193,224,186,117,235,40,180,
244,243,244,56,168,155,42,141,212,200,118,226,206,93,237,170,248,242,161,161,33,52,161,40,151,41,118,114,186,96,5,248,19,202,92,204,88,249,255,185,92,110,124,124,28,236,111,104,244,32,200,214,212,212,
160,44,44,75,160,114,255,100,141,227,136,98,147,147,147,64,75,157,88,116,60,225,92,46,87,40,20,34,145,136,149,97,242,255,191,24,232,178,78,168,102,66,207,187,125,149,200,91,192,69,176,234,130,154,37,65,
134,72,100,127,108,217,111,108,108,196,166,7,14,238,236,131,85,195,201,231,243,109,223,190,61,145,72,160,188,236,100,81,164,186,87,112,31,101,2,215,218,218,218,210,210,114,189,215,4,69,69,115,73,224,95,
177,180,252,52,72,121,189,200,181,229,222,223,243,110,185,40,252,117,124,124,28,211,65,246,61,202,210,159,84,205,68,248,198,175,232,228,202,229,114,44,123,6,2,1,116,3,97,83,34,79,79,9,168,126,247,187,
223,117,129,152,93,244,84,229,77,145,82,145,50,76,91,4,251,115,185,220,133,11,23,32,98,107,54,173,201,142,76,51,185,190,124,249,50,26,123,20,103,219,99,8,18,225,73,8,93,154,161,83,225,113,104,175,240,
188,35,31,188,178,178,2,174,37,54,200,0,158,172,123,37,126,180,154,219,214,246,229,66,161,144,205,102,77,131,106,57,231,81,27,148,188,189,116,58,29,139,197,184,131,94,94,94,158,157,157,157,157,157,173,
172,172,140,70,163,32,135,253,111,180,63,96,80,194,59,213,99,115,5,229,127,22,10,133,241,241,241,150,150,22,73,164,33,103,203,189,96,245,179,149,252,157,178,30,225,230,88,44,6,32,136,236,84,116,85,212,
213,213,33,19,148,229,101,107,74,136,199,170,178,180,186,186,58,56,56,216,219,219,43,5,113,152,16,169,213,113,121,121,121,122,122,58,18,137,72,242,192,47,170,24,232,116,12,15,15,51,132,201,69,148,37,19,
218,13,155,9,148,231,221,250,147,220,173,202,250,42,74,35,228,35,39,147,73,64,174,117,117,117,136,221,18,96,97,201,11,193,110,239,222,189,109,109,109,63,254,241,143,177,121,151,227,71,233,253,43,147,123,
50,175,169,118,125,93,209,217,20,95,149,0,93,58,157,102,197,76,17,240,9,136,227,238,227,187,147,140,43,89,61,8,86,28,183,248,103,102,135,138,78,39,201,11,0,244,33,28,200,124,20,125,49,228,185,153,72,133,
83,165,119,45,72,38,23,102,51,52,121,61,54,135,24,196,232,205,155,55,115,59,227,17,166,39,44,230,42,175,166,209,209,81,192,237,178,7,196,201,211,129,44,14,92,65,92,86,169,206,195,255,4,61,64,150,71,73,
228,192,57,212,214,214,22,139,69,196,41,235,133,147,102,178,86,221,69,174,22,166,15,161,242,176,160,21,8,58,0,231,230,230,72,162,50,243,193,137,137,137,137,137,137,154,154,26,68,106,23,217,114,151,91,
232,66,64,6,240,226,226,212,192,10,76,44,22,3,242,200,12,90,70,52,235,240,82,98,137,210,240,48,22,139,145,73,41,89,156,120,144,78,167,83,169,20,16,234,234,234,106,136,138,152,144,171,44,5,43,50,70,177,
88,156,158,158,14,133,66,172,34,112,78,154,119,103,101,101,37,22,139,133,195,97,100,160,191,192,98,224,90,32,14,9,107,84,85,85,97,84,72,243,108,53,219,37,7,84,138,190,75,250,60,69,175,48,119,210,233,116,
75,75,11,168,53,4,172,25,125,168,181,0,36,164,88,44,182,183,183,223,115,207,61,71,143,30,5,22,100,117,251,54,227,35,178,200,61,123,246,72,197,206,181,168,2,161,236,239,94,224,133,99,47,139,97,184,50,148,
254,128,239,12,253,60,185,92,149,149,149,77,79,79,51,21,101,116,198,251,144,83,196,104,198,2,160,26,153,116,11,51,55,175,82,181,131,233,41,83,251,53,30,138,175,205,244,217,42,118,239,53,29,36,241,183,
124,62,127,241,226,69,72,181,153,36,13,9,95,224,215,217,217,89,16,162,149,88,132,213,79,87,206,124,138,245,201,130,161,124,208,208,208,48,51,51,227,17,202,156,172,13,114,205,169,173,173,197,141,119,103,
176,41,123,83,25,172,193,82,112,129,186,200,189,91,89,89,65,251,178,146,89,112,25,145,163,163,163,163,163,163,245,245,245,193,96,208,138,106,173,29,232,80,80,126,34,145,48,57,61,210,129,155,207,76,79,
79,55,55,55,203,57,38,197,146,220,99,52,209,234,217,217,89,34,200,242,179,164,93,22,193,40,92,34,148,25,93,178,137,112,56,204,222,22,30,201,100,18,173,137,30,97,11,224,177,25,78,123,222,233,142,73,167,
211,176,154,245,252,31,59,164,235,21,163,91,67,67,3,86,122,146,240,204,222,122,229,80,35,113,69,94,118,90,119,115,62,174,91,183,14,101,88,143,80,188,180,98,44,220,89,214,213,213,125,248,195,31,62,125,
250,244,233,211,167,157,182,143,146,11,139,19,216,187,119,175,172,1,172,49,58,91,5,248,229,120,67,173,2,192,2,23,54,148,136,177,42,200,78,116,211,53,137,239,207,2,166,188,62,10,244,151,223,136,80,59,232,
31,238,120,183,84,119,74,38,147,185,92,174,166,166,134,98,129,170,87,192,169,250,37,241,13,43,68,185,186,186,250,255,0,95,219,94,100,72,156,181,227,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* MrAlias2Editor::mralias2_png = (const char*) resource_MrAlias2Editor_mralias2_png;
const int MrAlias2Editor::mralias2_pngSize = 127623;

// JUCER_RESOURCE: alias_svg2, 85270, "../../../../My Documents/alias.svg"
static const unsigned char resource_MrAlias2Editor_alias_svg2[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,32,115,
116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,67,114,101,97,116,101,100,32,119,105,116,104,32,73,110,107,115,99,97,112,101,32,40,104,116,116,112,58,47,47,119,119,119,46,105,
110,107,115,99,97,112,101,46,111,114,103,47,41,32,45,45,62,10,60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,108,
101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,119,101,98,46,114,101,115,111,117,114,99,101,46,111,114,103,47,99,99,47,34,10,32,32,32,
120,109,108,110,115,58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,10,32,
32,32,120,109,108,110,115,58,115,118,103,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,116,116,112,58,47,
47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,105,112,111,100,105,
46,115,111,117,114,99,101,102,111,114,103,101,46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,99,97,112,101,61,
34,104,116,116,112,58,47,47,119,119,119,46,105,110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,119,105,100,116,104,61,34,
52,56,48,34,10,32,32,32,104,101,105,103,104,116,61,34,51,50,48,34,10,32,32,32,105,100,61,34,115,118,103,50,34,10,32,32,32,115,111,100,105,112,111,100,105,58,118,101,114,115,105,111,110,61,34,48,46,51,
50,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,52,53,46,49,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,98,97,115,101,61,34,67,58,92,68,111,
99,117,109,101,110,116,115,32,97,110,100,32,83,101,116,116,105,110,103,115,92,118,105,110,97,114,101,92,77,121,32,68,111,99,117,109,101,110,116,115,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,
111,99,110,97,109,101,61,34,97,108,105,97,115,46,115,118,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,111,117,116,112,117,116,95,101,120,116,101,110,115,105,111,110,61,34,111,114,103,46,105,110,
107,115,99,97,112,101,46,111,117,116,112,117,116,46,115,118,103,46,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,114,115,105,111,110,61,34,49,46,48,34,62,10,32,32,60,100,101,102,115,10,32,32,32,
32,32,105,100,61,34,100,101,102,115,52,34,32,47,62,10,32,32,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,105,100,61,34,98,97,115,101,34,10,32,32,32,32,32,
112,97,103,101,99,111,108,111,114,61,34,35,102,102,102,102,102,102,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,98,111,114,100,101,114,
111,112,97,99,105,116,121,61,34,49,46,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,48,48,48,34,10,32,32,32,32,32,103,117,105,100,101,116,111,108,101,114,97,110,
99,101,61,34,49,48,34,10,32,32,32,32,32,111,98,106,101,99,116,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,105,116,121,
61,34,48,46,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,115,104,97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,34,48,46,49,
55,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,120,61,34,49,48,49,48,46,51,54,49,52,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,45,49,55,56,46,55,56,50,53,50,34,
10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,100,111,99,117,109,101,110,116,45,117,110,105,116,115,61,34,112,120,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,117,114,114,101,110,116,
45,108,97,121,101,114,61,34,108,97,121,101,114,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,55,52,56,34,10,32,32,32,32,32,105,110,107,115,
99,97,112,101,58,119,105,110,100,111,119,45,104,101,105,103,104,116,61,34,53,55,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,120,61,34,50,52,49,34,10,32,32,32,32,
32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,45,49,49,34,10,32,32,32,32,32,119,105,100,116,104,61,34,52,56,48,112,120,34,10,32,32,32,32,32,104,101,105,103,104,116,61,34,51,
50,48,112,120,34,32,47,62,10,32,32,60,109,101,116,97,100,97,116,97,10,32,32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,55,34,62,10,32,32,32,32,60,114,100,102,58,82,68,70,62,10,32,32,32,32,32,
32,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,10,32,32,32,32,32,32,32,32,60,100,99,58,102,111,114,109,97,116,62,105,109,97,103,101,47,115,118,
103,43,120,109,108,60,47,100,99,58,102,111,114,109,97,116,62,10,32,32,32,32,32,32,32,32,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,102,58,114,101,115,111,117,114,99,101,61,
34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,10,32,32,32,32,32,32,60,47,99,99,58,87,111,114,
107,62,10,32,32,32,32,60,47,114,100,102,58,82,68,70,62,10,32,32,60,47,109,101,116,97,100,97,116,97,62,10,32,32,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,
101,114,32,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,49,34,62,10,32,32,
32,32,60,114,101,99,116,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,111,112,97,99,105,116,121,58,49,59,102,105,108,108,58,35,52,102,52,99,52,55,59,102,105,108,108,45,111,112,97,99,105,116,121,58,
49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,46,49,51,49,57,57,57,57,55,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,
58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,110,111,110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,
97,99,105,116,121,58,49,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,50,52,49,51,34,10,32,32,32,32,32,32,32,119,105,100,116,104,61,34,52,56,48,34,10,32,32,32,32,32,32,32,104,101,105,103,104,
116,61,34,51,50,48,34,10,32,32,32,32,32,32,32,120,61,34,48,34,10,32,32,32,32,32,32,32,121,61,34,48,34,32,47,62,10,32,32,32,32,60,103,10,32,32,32,32,32,32,32,105,100,61,34,103,50,51,57,55,34,10,32,32,32,
32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,45,49,49,49,46,52,50,56,53,55,44,45,51,46,55,57,48,55,52,48,54,41,34,10,32,32,32,32,32,32,32,115,116,121,108,101,
61,34,115,116,114,111,107,101,58,110,111,110,101,34,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,52,57,52,53,52,53,59,115,116,
114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,49,49,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,
52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,
49,32,76,32,49,50,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,
32,76,32,49,49,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,49,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,50,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,
76,32,49,51,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,51,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,51,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,
32,49,51,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,
49,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,55,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,52,49,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,52,
49,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,52,49,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,52,48,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,52,48,
49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,57,54,
46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,51,57,49,46,
52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,
50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,49,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,
56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,49,54,46,52,50,56,
53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,
55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,49,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,
44,54,56,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,50,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,53,55,44,
55,51,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,51,54,46,52,50,56,53,55,44,54,
51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,53,51,
46,55,57,48,55,52,49,32,76,32,52,52,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,52,56,46,
55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,52,51,46,55,
57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,56,54,46,52,50,56,53,55,44,53,51,46,55,57,
48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,
55,52,49,32,76,32,52,57,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,
52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,
50,32,76,32,53,57,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,
32,76,32,53,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,
76,32,53,56,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,
32,53,57,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,
53,56,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,
57,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,55,
54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,53,54,49,
46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,
52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,
50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,
56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,
53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,
55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,
44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,
51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,122,32,77,32,50,52,49,46,52,50,56,53,55,
44,50,55,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,
50,55,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,50,
56,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,52,53,49,46,52,50,56,53,55,44,
50,55,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,
55,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,50,54,
51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,53,51,
46,55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,52,56,46,
55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,52,51,46,55,
57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,50,55,51,46,55,57,
48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,
55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,
52,32,122,32,77,32,50,51,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,
55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,
52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,
32,76,32,50,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,48,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,
76,32,50,48,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,57,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,
32,49,57,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,
49,57,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,50,
48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,48,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,49,
49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,51,49,
46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,122,32,77,32,53,54,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,53,54,
49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,49,
46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,54,49,46,
52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,122,32,77,32,51,56,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,51,56,49,
46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,56,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,57,49,46,
52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,
50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,54,54,46,52,50,
56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,122,32,77,32,52,57,49,46,52,
50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,
56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,
53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,
55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,
44,49,53,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,
49,53,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,49,
51,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,50,
51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,50,56,
46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,51,51,46,
55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,49,53,51,46,55,
57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,54,51,46,55,57,
48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,
55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,
52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,
32,76,32,52,53,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,
76,32,52,54,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,
32,52,56,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,
52,57,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,122,32,77,32,51,51,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,
32,51,50,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,
51,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,
51,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,122,32,77,32,49,53,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,
49,52,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,
52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,
49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,53,49,
46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,122,32,77,32,50,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,53,
49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,49,
46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,53,49,46,
52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,122,32,77,32,50,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,57,49,
46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,
52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,55,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,
50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,56,54,46,52,50,
56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,122,32,77,32,49,55,49,46,52,
50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,
56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,
53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,122,32,77,32,53,51,49,46,52,50,
56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,50,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,
53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,50,54,46,52,50,56,53,
55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,122,32,77,32,52,54,49,46,52,50,56,
53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,54,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,
55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,54,54,46,52,50,56,53,55,
44,51,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,122,32,34,10,32,32,32,32,32,32,32,32,
32,105,100,61,34,112,97,116,104,50,52,49,49,34,32,47,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,52,50,51,99,51,100,59,115,116,
114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,49,49,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,
55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,
52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,
32,76,32,49,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,
76,32,49,51,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,
32,49,51,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,
49,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,57,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,
53,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,55,
49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,50,55,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,51,54,
46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,52,48,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,52,48,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,52,48,49,46,
52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,
50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,57,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,
56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,50,54,46,52,50,56,
53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,
55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,52,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,
44,52,56,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,
52,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,55,54,46,52,50,56,53,55,44,53,
51,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,54,51,
46,55,57,48,55,52,49,32,76,32,52,56,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,53,56,46,
55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,48,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,53,51,46,55,
57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,54,51,46,55,57,
48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,53,51,46,55,57,48,
55,52,49,32,76,32,53,51,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,
52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,49,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,
49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,57,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,
32,76,32,52,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,
76,32,53,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,
32,53,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,
53,56,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,
55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,55,
54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,56,49,
46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,57,49,46,
52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,
50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,
56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,
53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,
55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,
44,51,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,
50,57,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,51,
48,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,51,49,
51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,50,51,
46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,49,53,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,57,
51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,57,56,
46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,51,46,
55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,122,32,77,32,52,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,52,51,
46,55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,52,56,46,
55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,53,51,46,55,
57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,55,51,46,55,57,
48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,
55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,
52,32,76,32,52,52,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,
32,76,32,52,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,122,32,77,32,50,52,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,
52,32,76,32,50,51,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,
32,76,32,50,51,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,
76,32,50,50,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,
32,50,49,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,
50,49,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,50,
50,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,48,
49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,57,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,57,49,
46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,48,49,46,
52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,50,49,49,46,52,
50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,
56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,
53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,
55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,50,55,49,46,52,50,56,
53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,
55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,
44,50,57,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,122,32,77,32,51,48,49,46,52,50,56,53,
55,44,50,55,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,
44,50,55,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,
50,56,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,51,48,49,46,52,50,56,53,55,
44,50,52,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,
50,52,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,
51,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,52,
51,46,55,57,48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,52,56,
46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,53,51,46,
55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,122,32,77,32,51,56,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,48,51,
46,55,57,48,55,52,32,76,32,51,56,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,49,51,46,
55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,57,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,50,51,46,55,
57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,57,51,46,55,57,
48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,
55,52,32,76,32,51,53,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,
52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,52,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,
32,76,32,51,52,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,52,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,
76,32,51,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,
32,51,53,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,
51,54,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,54,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,
55,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,55,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,56,
49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,122,32,77,32,53,54,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,53,
54,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,
49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,54,49,
46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,122,32,77,32,52,57,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,57,
49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,57,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,48,49,
46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,50,49,46,
52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,
50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,
56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,
53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,
55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,
44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,
49,49,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,
49,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,50,
51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,51,51,
46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,52,51,46,
55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,53,56,46,55,
57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,
48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,
55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,
52,32,76,32,52,55,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,
32,76,32,52,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,
76,32,52,57,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,122,32,77,32,51,50,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,
32,76,32,51,50,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,
76,32,51,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,
32,51,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,49,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,
51,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,122,32,77,32,49,53,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,
32,49,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,53,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,
49,54,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,
56,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,54,
49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,49,52,49,
46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,
52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,50,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,
50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,
56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,
53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,
55,44,49,48,51,46,55,57,48,55,52,32,122,32,77,32,50,53,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,
53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,
55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,52,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,
44,57,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,
49,48,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,49,
49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,122,32,77,32,50,57,49,46,52,50,56,53,55,44,
56,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,55,
51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,57,51,
46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,122,32,77,32,51,57,49,46,52,50,56,53,55,44,56,
51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,55,51,
46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,54,51,46,
55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,52,51,46,55,
57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,51,56,46,55,57,
48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,
55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,54,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,
52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,
49,32,76,32,51,54,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,
32,76,32,51,55,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,
76,32,51,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,122,32,77,32,49,49,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,49,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,
32,76,32,49,49,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,50,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,50,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,
76,32,49,50,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,
32,49,49,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,122,32,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,50,52,48,57,34,32,47,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,
32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,51,97,51,52,51,53,59,115,116,114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,49,49,49,46,52,
50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,
56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,
53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,
55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,
44,50,56,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,50,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,
50,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,51,54,46,52,50,56,53,55,44,49,
51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,52,49,46,52,50,56,53,55,44,51,46,
55,57,48,55,52,49,50,32,76,32,49,57,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,56,46,55,
57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,49,51,46,55,
57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,50,55,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,51,49,46,52,50,56,53,55,44,51,46,55,57,48,
55,52,49,50,32,76,32,51,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,57,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,51,57,49,46,52,50,56,53,55,44,49,51,46,55,57,48,
55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,
52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,
49,32,76,32,51,55,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,54,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,
32,76,32,51,54,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,
76,32,51,53,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,
32,51,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,53,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,
51,54,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,54,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,
55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,54,
54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,54,49,
46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,56,49,46,
52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,
50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,
56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,
53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,
55,44,51,56,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,48,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,
44,51,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,50,54,46,52,50,56,53,55,44,
55,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,54,
51,46,55,57,48,55,52,49,32,76,32,52,52,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,53,56,
46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,54,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,53,51,46,
55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,54,51,46,55,
57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,53,51,46,55,57,
48,55,52,49,32,76,32,53,48,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,53,56,46,55,57,48,
55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,50,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,
52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,51,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,
49,32,76,32,53,51,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,
32,76,32,53,50,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,
76,32,53,49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,
32,52,57,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,
53,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,
56,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,53,56,
49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,55,49,
46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,56,49,46,
52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,
50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,
56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,
53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,
55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,
44,50,52,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,
50,51,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,
50,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,50,
51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,50,54,51,
46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,53,51,46,
55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,54,51,46,55,
57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,
48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,
55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,
52,32,76,32,53,54,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,
32,76,32,53,54,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,
76,32,53,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,
32,53,48,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,
52,57,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,52,
57,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,56,
49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,54,49,
46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,53,54,46,
52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,
50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,
56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,
53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,
55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,
44,51,48,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,
51,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,
50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,122,32,77,32,49,53,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,
50,56,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,
57,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,
51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,122,32,77,32,50,55,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,
56,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,55,
56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,55,51,
46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,50,54,51,46,
55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,52,51,46,55,
57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,50,56,46,55,57,
48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,
55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,
52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,
32,76,32,50,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,
76,32,50,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,
32,50,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,
50,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,
53,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,122,32,77,32,
51,48,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,
56,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,57,
49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,51,
49,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,48,
49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,57,54,
46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,50,57,49,46,
52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,
50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,122,32,77,32,51,53,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,52,54,46,
52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,
50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,52,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,
56,53,55,44,50,51,56,46,55,57,48,55,52,32,122,32,77,32,51,56,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,
50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,
56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,
53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,
55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,
44,50,49,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,
50,50,51,46,55,57,48,55,52,32,76,32,51,54,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,
50,56,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,55,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,51,
51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,122,32,77,32,52,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,
48,51,46,55,57,48,55,52,32,76,32,52,57,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,57,
51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,56,51,
46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,55,51,46,
55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,53,51,46,55,
57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,52,51,46,55,57,
48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,
55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,
52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,
32,76,32,53,48,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,
76,32,53,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,
32,52,55,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,
52,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,
52,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,52,53,
49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,55,49,
46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,55,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,56,49,46,
52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,
50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,122,32,77,32,51,48,49,46,
52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,
50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,
56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,122,32,77,32,51,50,49,46,52,
50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,
56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,
53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,
55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,49,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,
44,49,50,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,49,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,
49,52,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,122,32,77,32,50,54,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,
44,55,51,46,55,57,48,55,52,49,32,76,32,50,54,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,
56,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,57,
51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,57,54,46,52,50,56,53,55,44,55,51,
46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,53,51,46,
55,57,48,55,52,49,32,76,32,50,57,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,53,56,46,55,
57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,56,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,54,51,46,55,57,
48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,54,46,52,50,56,53,55,44,55,51,46,55,57,48,
55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,
52,49,32,76,32,50,54,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,
49,32,76,32,50,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,53,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,
32,76,32,50,53,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,
76,32,50,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,
32,50,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,
50,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,
54,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,122,32,77,32,49,53,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,
49,53,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,
54,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,56,
49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,54,49,
46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,52,54,46,
52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,
50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,50,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,
56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,
53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,
55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,122,32,34,10,32,32,32,32,32,32,32,
32,32,105,100,61,34,112,97,116,104,50,52,48,55,34,32,47,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,50,56,50,52,50,53,59,115,
116,114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,49,49,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,
48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,
55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,50,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,
52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,51,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,
32,76,32,49,52,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,
76,32,49,50,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,
32,49,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,
49,50,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,50,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,
51,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,52,
49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,53,49,
46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,53,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,54,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,49,54,49,46,
52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,54,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,54,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,
50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,55,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,49,49,46,52,50,
56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,53,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,
53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,53,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,
55,44,49,56,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,54,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,
44,49,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,50,55,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,51,49,46,52,50,56,53,55,44,
51,46,55,57,48,55,52,49,50,32,76,32,51,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,57,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,51,57,49,46,52,50,56,53,55,44,49,
51,46,55,57,48,55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,49,56,
46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,50,51,46,
55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,51,51,46,55,
57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,54,51,46,55,57,
48,55,52,49,32,76,32,50,55,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,54,56,46,55,57,48,
55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,
52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,
49,32,76,32,50,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,
32,76,32,50,50,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,
76,32,50,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,
32,50,51,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,
50,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,
54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,50,55,
49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,54,49,
46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,
52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,57,54,46,52,
50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,
56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,48,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,
53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,
55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,
44,52,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,
55,51,46,55,57,48,55,52,49,32,76,32,51,53,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,55,
56,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,53,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,56,51,
46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,53,54,46,52,50,56,53,55,44,57,51,46,
55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,51,54,49,46,52,50,56,53,55,44,49,48,51,46,
55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,57,56,46,55,57,
48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,
55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,
52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,
49,32,76,32,52,49,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,
32,76,32,52,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,51,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,
76,32,52,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,54,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,
32,52,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,
53,48,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,53,
50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,50,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,51,
49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,51,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,52,49,
46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,52,54,46,
52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,
50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,52,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,
56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,50,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,
53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,48,54,46,52,50,56,53,
55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,
44,50,51,46,55,57,48,55,52,49,32,76,32,52,57,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,
49,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,51,
46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,49,48,
51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,50,51,
46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,50,56,46,
55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,51,51,46,55,
57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,49,52,51,46,55,57,
48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,
55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,
52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,
32,76,32,53,55,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,
76,32,53,56,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,
32,53,56,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,
53,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,
54,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,
49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,52,54,
46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,53,52,49,46,
52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,
50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,
56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,
53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,
55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,
44,51,49,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,
51,49,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,
56,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,57,
51,46,55,57,48,55,52,32,76,32,52,55,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,56,51,
46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,55,51,46,
55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,54,51,46,55,
57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,53,51,46,55,57,
48,55,52,32,76,32,52,54,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,
55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,
52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,
32,76,32,52,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,
76,32,52,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,
32,52,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,
52,51,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,
52,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,55,
54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,122,32,77,32,49,
52,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,53,
49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,52,49,
46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,51,49,46,
52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,51,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,
50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,122,32,77,32,50,55,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,56,54,46,
52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,
50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,
56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,
53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,
55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,
44,50,56,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,
50,55,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,
55,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,53,
51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,52,51,
46,55,57,48,55,52,32,76,32,51,55,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,51,56,46,
55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,51,51,46,55,
57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,49,57,51,46,55,57,
48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,
55,52,32,76,32,51,55,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,
52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,
32,76,32,51,51,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,
76,32,51,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,
32,51,52,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,
51,51,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,
50,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,57,
49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,56,54,
46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,50,56,49,46,
52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,
50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,
56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,
53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,
55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,
44,50,52,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,
50,51,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,
50,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,48,
51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,57,56,
46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,57,51,46,
55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,50,49,51,46,55,
57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,
48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,
55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,
52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,
32,76,32,50,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,
76,32,50,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,
32,50,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,
50,51,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,
54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,54,
54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,122,32,77,32,50,
57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,50,
49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,48,54,
46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,122,32,77,32,52,57,
49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,57,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,48,49,
46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,49,54,46,
52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,
50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,
56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,
53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,
55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,
44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,
49,49,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,
49,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,49,50,
51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,51,51,
46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,52,51,46,
55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,53,51,46,55,
57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,49,55,51,46,55,57,
48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,
55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,
52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,
32,76,32,52,55,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,
76,32,52,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,122,32,77,32,50,53,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,
32,76,32,50,53,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,
76,32,50,52,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,
32,50,53,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,122,32,77,32,50,57,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,
76,32,50,57,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,
32,51,49,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,49,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,
51,50,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,
50,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,51,51,
49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,52,49,
46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,51,49,46,
52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,
50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,
56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,
53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,
55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,
44,49,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,
49,51,51,46,55,57,48,55,52,32,76,32,50,56,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,
50,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,50,
51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,49,51,51,
46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,54,51,46,
55,57,48,55,52,32,76,32,50,56,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,53,56,46,55,
57,48,55,52,32,122,32,77,32,49,54,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,54,54,46,52,50,56,53,55,44,57,51,46,55,
57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,56,51,46,55,57,
48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,55,56,46,55,57,48,
55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,56,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,
52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,54,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,
49,32,76,32,49,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,
32,76,32,49,51,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,
76,32,49,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,50,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,
32,49,51,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,
49,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,
53,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,122,32,77,32,
52,53,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,
55,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,52,54,
49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,122,32,77,32,53,
55,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,54,
49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,54,54,
46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,53,55,49,46,
52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,
50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,
56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,122,32,77,32,51,56,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,
50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,56,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,
56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,51,57,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,
53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,
55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,56,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,122,32,34,10,32,32,32,32,32,32,32,
32,32,105,100,61,34,112,97,116,104,50,52,48,53,34,32,47,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,50,50,49,102,50,48,59,115,
116,114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,49,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,
48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,
55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,51,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,
52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,53,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,
32,76,32,49,54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,
76,32,49,53,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,
32,49,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,
49,51,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,51,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,
52,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,52,
54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,53,49,
46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,51,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,50,49,46,
52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,
50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,
56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,
53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,
55,44,49,49,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,
44,49,50,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,
49,49,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,57,
51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,56,56,
46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,56,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,56,51,46,
55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,54,51,46,55,
57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,52,51,46,55,57,
48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,52,56,46,55,57,48,
55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,56,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,
52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,53,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,
49,32,76,32,49,51,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,51,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,
32,76,32,49,51,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,
76,32,49,52,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,
32,49,54,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,54,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,
49,55,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,
55,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,56,
49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,55,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,55,49,
46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,49,55,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,48,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,52,49,46,
52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,52,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,52,54,46,52,
50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,
56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,53,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,
53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,54,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,
55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,55,54,46,52,50,56,53,55,
44,49,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,50,56,49,46,52,50,56,53,55,44,
51,46,55,57,48,55,52,49,50,32,76,32,51,51,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,56,
46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,49,51,
46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,53,54,46,52,50,56,53,55,44,50,51,46,
55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,51,51,46,55,
57,48,55,52,49,32,76,32,51,49,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,51,56,46,55,57,
48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,56,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,52,51,46,55,57,48,
55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,
52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,
49,32,76,32,50,53,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,
32,76,32,50,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,
76,32,50,51,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,50,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,
32,50,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,
50,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,50,
52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,53,
49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,54,49,
46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,54,54,46,
52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,
50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,
56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,49,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,
53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,
55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,
44,49,51,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,
49,49,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,
48,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,49,51,
51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,50,51,
46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,49,51,46,
55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,48,51,46,55,
57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,50,57,54,46,52,50,56,53,55,44,57,51,46,55,57,48,
55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,
52,49,32,76,32,51,48,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,
49,32,76,32,51,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,49,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,
32,76,32,51,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,51,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,
76,32,51,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,
32,51,53,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,
51,54,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,
56,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,56,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,57,
49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,51,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,57,54,
46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,48,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,52,48,49,46,
52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,
50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,52,49,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,49,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,
56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,
53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,
55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,52,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,
44,54,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,
53,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,56,54,46,52,50,56,53,55,44,54,
51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,55,51,
46,55,57,48,55,52,49,32,76,32,53,48,54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,55,56,46,
55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,49,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,56,51,46,55,
57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,48,51,46,55,
57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,57,51,46,55,57,48,
55,52,49,32,76,32,53,51,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,
52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,52,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,
49,32,76,32,53,53,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,54,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,
32,76,32,53,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,
76,32,53,53,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,
32,53,52,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,
53,50,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,49,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,
49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,48,
49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,52,57,49,
46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,57,49,46,
52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,
50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,
56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,
53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,
55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,
44,49,56,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,
49,57,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,
48,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,48,
56,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,49,51,
46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,52,54,46,52,50,56,53,55,44,50,53,51,46,
55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,56,51,46,55,
57,48,55,52,32,76,32,53,52,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,56,56,46,55,57,
48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,
55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,52,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,
52,32,76,32,53,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,
32,76,32,53,50,54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,
76,32,53,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,
32,53,49,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,
52,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,
56,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,52,56,
49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,55,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,55,49,
46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,55,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,56,49,46,
52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,
50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,
56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,57,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,
53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,
55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,
44,49,55,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,
49,53,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,
52,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,51,
51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,50,51,
46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,48,51,46,
55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,48,56,46,55,
57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,49,51,46,55,57,
48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,
55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,
52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,
32,76,32,52,51,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,49,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,
76,32,52,48,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,
32,51,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,
51,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,
52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,51,51,
49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,52,49,
46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,51,49,46,
52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,
50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,
56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,
53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,
55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,
44,50,51,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,
50,49,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,
48,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,57,
51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,51,51,
46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,51,56,46,
55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,54,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,52,51,46,55,
57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,50,53,51,46,55,57,
48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,
55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,
52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,
32,76,32,50,50,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,
76,32,50,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,
32,50,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,
50,57,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,
49,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,52,
49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,53,49,
46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,54,49,46,
52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,52,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,
50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,
56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,54,54,46,52,50,56,
53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,
55,44,50,52,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,
44,50,52,56,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,
50,53,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,49,54,46,52,50,56,53,55,44,50,
54,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,56,
51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,56,56,
46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,57,51,46,
55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,51,49,51,46,55,
57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,51,50,51,46,55,57,
48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,
55,52,32,122,32,77,32,50,53,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,49,57,51,46,55,57,
48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,
55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,
52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,
32,76,32,50,51,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,
76,32,50,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,
32,50,52,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,122,32,
77,32,51,48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,
32,51,50,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,
51,49,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,51,
49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,48,
49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,122,32,77,32,53,56,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,
55,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,53,55,
49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,57,49,
46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,56,49,46,
52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,122,32,77,32,52,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,49,49,
46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,48,49,46,
52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,
50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,49,54,46,52,50,
56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,
53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,
55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,
44,50,48,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,
50,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,50,
50,51,46,55,57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,50,
56,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,51,51,
46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,122,32,77,32,49,49,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,56,51,
46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,56,56,46,
55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,57,51,46,55,
57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,122,32,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,50,52,48,51,34,32,47,62,10,32,32,32,32,32,32,60,
112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,50,48,49,100,49,100,59,115,116,114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,61,34,
77,32,49,49,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,
32,49,50,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,
49,49,54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,122,32,77,
32,49,51,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,
49,53,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,
53,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,54,
49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,53,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,53,49,
46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,52,49,46,
52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,
50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,
56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,
53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,
55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,
44,49,49,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,
49,50,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,49,
50,56,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,51,
51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,49,49,51,
46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,57,51,46,55,
57,48,55,52,49,32,76,32,49,55,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,56,51,46,55,57,
48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,55,51,46,55,57,48,
55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,49,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,
52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,
49,32,76,32,50,49,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,
32,76,32,50,49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,48,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,
76,32,50,48,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,
32,49,56,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,
49,55,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,49,
55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,49,53,
49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,52,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,52,49,
46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,52,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,
52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,
50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,54,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,
56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,55,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,
53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,49,49,46,52,50,56,53,
55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,52,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,52,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,
44,51,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,
50,56,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,50,
51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,49,51,
46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,51,50,49,46,52,50,56,53,55,44,51,46,55,
57,48,55,52,49,50,32,76,32,51,53,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,56,46,55,57,
48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,55,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,49,51,46,55,57,
48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,51,55,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,53,54,46,52,50,56,53,55,44,50,51,46,55,57,48,
55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,
52,49,32,76,32,51,50,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,
49,32,76,32,51,49,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,
32,76,32,50,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,57,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,56,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,
76,32,50,56,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,50,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,
32,50,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,
50,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,53,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,
53,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,51,
49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,50,54,
46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,50,50,49,46,
52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,
50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,
56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,
53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,
55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,
44,49,53,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,
49,54,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,56,54,46,52,50,56,53,55,44,49,
55,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,54,
51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,53,51,
46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,52,51,46,
55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,51,51,46,55,
57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,
48,55,52,32,76,32,51,52,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,
55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,
52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,
32,76,32,52,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,
76,32,52,51,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,
32,52,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,
52,55,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,55,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,
56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,57,
49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,53,48,49,
46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,48,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,
52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,48,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,
50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,
56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,
53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,53,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,
55,44,49,50,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,
44,49,51,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,
49,54,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,
55,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,55,
56,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,56,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,56,51,
46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,53,54,46,52,50,56,53,55,44,49,55,51,46,
55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,56,51,46,55,
57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,48,56,46,55,57,
48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,
55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,
52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,
32,76,32,50,55,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,
76,32,50,55,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,
32,50,54,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,
50,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,
52,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,52,
49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,54,49,
46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,55,49,46,
52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,
50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,
56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,
53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,
55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,51,54,46,52,50,56,53,55,
44,49,54,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,
49,55,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,
56,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,57,
51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,50,50,51,
46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,51,51,46,
55,57,48,55,52,32,76,32,49,54,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,52,51,46,55,
57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,
48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,
55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,
52,32,76,32,50,49,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,
32,76,32,50,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,
76,32,50,48,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,48,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,
32,50,49,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,
50,50,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,50,
51,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,56,
49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,51,49,
46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,52,49,46,
52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,51,53,49,46,52,
50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,53,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,
56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,53,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,
53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,53,54,46,52,50,56,53,
55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,
44,50,53,51,46,55,57,48,55,52,32,76,32,51,56,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,
50,54,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,49,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,
55,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,57,
51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,51,49,51,
46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,51,49,56,46,
55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,51,50,51,46,55,
57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,122,32,77,32,50,48,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,55,51,46,
55,57,48,55,52,32,76,32,49,57,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,55,56,46,55,
57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,49,57,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,56,51,46,55,57,
48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,50,56,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,48,51,46,55,
57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,48,56,46,55,57,
48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,55,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,
55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,122,32,77,32,53,50,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,56,51,46,55,57,
48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,
55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,
52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,56,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,
32,76,32,52,56,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,
76,32,52,56,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,
32,52,57,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,
53,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,
50,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,51,
49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,53,52,49,
46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,51,49,46,
52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,
50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,
56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,
53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,
55,44,57,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,51,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,
44,57,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,
56,51,46,55,57,48,55,52,49,32,76,32,53,54,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,54,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,53,54,49,46,52,50,56,53,55,44,55,
51,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,54,56,
46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,54,51,46,
55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,57,51,46,55,
57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,50,51,46,55,
57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,50,56,46,55,57,
48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,
55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,53,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,
52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,
32,76,32,53,54,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,
76,32,53,55,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,55,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,
32,53,56,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,
53,54,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,
53,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,53,53,
49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,52,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,52,49,
46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,52,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,53,49,46,
52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,52,54,46,52,
50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,
56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,
53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,52,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,
55,44,50,57,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,
44,51,48,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,
51,49,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,
57,56,46,55,57,48,55,52,32,122,32,77,32,49,49,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,
50,57,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,51,
48,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,50,57,
56,46,55,57,48,55,52,32,122,32,77,32,51,48,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,
53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,54,
51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,53,56,
46,55,57,48,55,52,32,122,32,77,32,53,56,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,50,51,
51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,53,57,49,46,52,50,56,53,55,44,50,52,51,
46,55,57,48,55,52,32,76,32,53,56,54,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,51,56,46,
55,57,48,55,52,32,122,32,77,32,52,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,49,57,51,
46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,49,51,46,
55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,49,56,46,55,
57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,52,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,50,51,46,55,57,
48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,
55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,122,32,77,32,50,57,49,46,52,50,56,53,55,44,49,50,56,46,55,57,
48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,56,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,
55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,
52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,
32,76,32,50,57,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,
122,32,77,32,51,51,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,49,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,
32,76,32,51,48,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,51,48,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,
76,32,51,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,
32,51,50,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,50,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,
51,51,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,51,54,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,
52,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,52,
54,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,51,53,49,
46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,51,51,49,46,
52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,122,32,77,32,49,49,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,49,54,
46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,50,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,50,49,46,
52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,49,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,49,49,46,52,
50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,122,32,77,32,53,53,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,52,49,46,
52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,
50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,
56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,48,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,
53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,52,49,46,52,50,56,53,
55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,56,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,53,56,49,46,52,50,56,53,55,
44,49,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,
51,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,53,
51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,122,32,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,50,52,48,49,34,32,47,62,10,32,32,32,32,
32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,49,56,49,50,49,51,59,115,116,114,111,107,101,58,110,111,110,101,34,10,32,32,32,32,32,32,32,32,32,100,
61,34,77,32,49,52,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,
32,76,32,49,53,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,
76,32,49,53,54,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,
32,49,54,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,54,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,
49,55,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,
48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,57,
54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,50,56,56,46,55,57,48,55,52,32,76,32,49,57,49,
46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,50,49,49,46,
52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,
50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,
56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,122,32,77,32,50,51,49,46,52,
50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,
56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,
53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,52,32,122,32,77,32,51,49,49,46,52,50,
56,53,55,44,51,49,56,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,
53,55,44,51,49,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,51,48,56,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,53,54,46,52,50,56,53,
55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,57,56,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,
44,50,57,51,46,55,57,48,55,52,32,76,32,51,54,54,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,57,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,
50,56,56,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,54,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,
56,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,50,54,
51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,50,53,51,
46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,54,51,46,
55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,55,51,46,55,
57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,50,56,51,46,55,57,
48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,51,48,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,
55,52,32,76,32,51,53,54,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,51,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,51,49,56,46,55,57,48,55,
52,32,122,32,77,32,53,50,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,49,54,46,52,50,56,53,55,44,50,55,51,46,55,57,48,
55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,54,56,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,
52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,
32,76,32,52,57,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,48,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,
76,32,53,49,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,49,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,
32,53,51,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,
53,51,54,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,53,
52,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,51,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,53,51,
49,46,52,50,56,53,55,44,50,55,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,50,49,
46,52,50,56,53,55,44,50,56,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,55,56,46,55,57,48,55,52,32,122,32,77,32,50,54,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,76,32,50,54,
49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,53,49,
46,52,50,56,53,55,44,50,51,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,52,49,46,
52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,52,54,46,52,
50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,50,53,49,46,52,50,
56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,53,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,
53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,
55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,
44,50,52,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,52,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,52,56,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,
50,53,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,53,51,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,
53,56,46,55,57,48,55,52,32,76,32,50,55,49,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,54,54,46,52,50,56,53,55,44,50,54,51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,54,
51,46,55,57,48,55,52,32,76,32,50,54,49,46,52,50,56,53,55,44,50,53,56,46,55,57,48,55,52,32,122,32,77,32,49,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,
49,51,46,55,57,48,55,52,32,76,32,49,51,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,50,48,
51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,57,51,
46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,49,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,49,54,46,52,50,56,53,55,44,49,50,51,46,
55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,51,51,46,55,
57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,51,56,46,55,57,
48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,
55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,49,57,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,
52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,
32,76,32,50,49,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,
76,32,50,50,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,49,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,
32,50,49,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,
49,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,
56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,49,55,
49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,49,57,49,
46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,49,57,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,48,49,46,
52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,50,48,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,
50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,
56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,50,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,
53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,50,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,
55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,48,54,46,52,50,56,53,55,
44,51,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,57,49,46,52,50,56,53,55,44,
49,51,46,55,57,48,55,52,49,32,76,32,49,56,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,49,56,49,46,52,50,56,53,55,44,56,
46,55,57,48,55,52,49,50,32,76,32,49,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,49,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,50,52,49,46,52,50,56,53,55,44,51,46,
55,57,48,55,52,49,50,32,76,32,50,52,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,51,54,46,52,50,56,53,55,44,51,51,46,
55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,50,51,49,46,52,50,56,53,55,44,52,51,46,55,
57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,52,56,46,55,57,
48,55,52,49,32,76,32,50,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,
55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,53,56,46,55,57,48,55,52,49,32,76,32,50,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,52,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,
52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,50,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,
49,32,76,32,50,51,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,50,50,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,
32,76,32,50,50,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,49,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,50,49,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,
76,32,50,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,
32,50,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,50,52,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,
50,51,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,50,51,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,50,
51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,50,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,50,50,
49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,50,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,49,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,48,49,
46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,50,48,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,57,49,46,
52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,49,56,49,46,52,
50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,55,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,
56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,49,55,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,54,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,
53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,50,56,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,53,54,46,52,50,56,53,
55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,51,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,122,32,77,32,49,51,49,46,52,50,56,
53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,52,54,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,
55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,49,54,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,53,54,46,52,50,56,53,55,
44,49,55,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,49,53,49,46,52,50,56,53,55,44,
49,54,51,46,55,57,48,55,52,32,76,32,49,52,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,
54,56,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,50,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,55,
51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,49,50,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,50,54,46,52,50,56,53,55,44,49,57,51,
46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,49,51,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,122,32,77,32,49,57,49,46,52,50,56,53,55,44,49,54,
56,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,54,51,
46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,49,56,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,56,54,46,52,50,56,53,55,44,49,55,51,46,
55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,49,57,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,122,32,77,32,51,49,49,46,52,50,56,53,55,44,50,49,56,
46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,48,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,49,51,46,
55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,48,56,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,50,48,51,46,55,
57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,55,51,46,55,57,
48,55,52,32,76,32,50,57,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,
55,52,32,76,32,51,48,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,
52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,
32,76,32,51,51,49,46,52,50,56,53,55,44,49,52,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,
76,32,51,52,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,53,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,
32,51,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,
51,55,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,
57,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,51,57,
54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,52,48,49,
46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,48,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,49,49,46,
52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,49,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,
50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,52,50,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,50,54,46,52,50,
56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,52,51,49,46,52,50,56,
53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,
55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,53,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,54,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,
44,54,51,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,54,56,46,55,57,48,55,52,49,32,76,32,52,55,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,56,49,46,52,50,56,53,55,44,
55,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,55,56,46,55,57,48,55,52,49,32,76,32,52,57,49,46,52,50,56,53,55,44,56,
51,46,55,57,48,55,52,49,32,76,32,52,57,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,57,56,
46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,57,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,49,51,
46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,52,57,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,56,49,46,52,50,56,53,55,44,49,48,51,46,
55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,52,55,49,46,52,50,56,53,55,44,49,49,51,46,55,
57,48,55,52,32,76,32,52,54,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,49,56,46,55,57,
48,55,52,32,76,32,52,53,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,
55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,50,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,
52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,51,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,52,56,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,
32,76,32,52,49,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,52,48,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,
76,32,52,48,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,57,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,
32,51,57,49,46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,51,57,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,56,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,
51,56,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,51,56,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,
55,54,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,53,51,46,55,57,48,55,52,32,76,32,51,55,49,46,52,50,56,53,55,44,49,53,56,46,55,57,48,55,52,32,76,32,51,55,
49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,53,54,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,54,51,46,55,57,48,55,52,32,76,32,51,52,49,
46,52,50,56,53,55,44,49,54,56,46,55,57,48,55,52,32,76,32,51,52,49,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,51,54,46,52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,51,49,46,
52,50,56,53,55,44,49,55,51,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,55,56,46,55,57,48,55,52,32,76,32,51,51,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,50,54,46,52,
50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,51,50,49,46,52,50,
56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,49,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,51,49,49,46,52,50,56,
53,55,44,50,49,56,46,55,57,48,55,52,32,122,32,77,32,52,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,50,49,46,52,50,
56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,53,55,44,49,57,56,46,55,57,48,55,52,32,76,32,52,51,49,46,52,50,56,
53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,51,54,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,
55,44,50,48,56,46,55,57,48,55,52,32,76,32,52,52,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,50,54,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,
44,50,50,51,46,55,57,48,55,52,32,76,32,52,49,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,122,32,77,32,53,51,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,
55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,
44,50,48,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,
50,48,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,49,
56,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,56,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,56,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,57,
51,46,55,57,48,55,52,32,76,32,53,55,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,57,51,46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,49,57,56,
46,55,57,48,55,52,32,76,32,53,56,49,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,50,48,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,48,51,46,
55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,49,51,46,55,57,48,55,52,32,76,32,53,53,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,50,50,51,46,55,
57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,50,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,50,49,56,46,55,57,48,55,52,32,122,32,77,32,50,56,49,46,52,50,56,53,55,44,49,49,51,46,
55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,56,54,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,48,51,46,55,
57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,50,57,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,56,54,46,52,50,56,53,55,44,49,50,51,46,55,57,
48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,50,56,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,122,32,77,32,53,51,49,46,52,50,56,53,55,44,49,49,56,46,55,
57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,50,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,49,51,46,55,57,
48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,48,56,46,55,57,48,55,52,32,76,32,53,50,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,
55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,49,48,51,46,55,57,48,55,52,32,76,32,53,52,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,53,52,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,
49,32,76,32,53,53,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,54,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,54,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,
32,76,32,53,54,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,54,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,
76,32,53,55,49,46,52,50,56,53,55,44,57,56,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,54,54,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,
32,53,54,49,46,52,50,56,53,55,44,49,49,51,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,76,32,53,54,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,
53,52,54,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,50,51,46,55,57,48,55,52,32,76,32,53,51,49,46,52,50,56,53,55,44,49,49,56,46,55,57,48,55,52,32,122,32,77,
32,53,56,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,
53,57,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,
56,54,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,57,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,56,56,46,55,57,48,55,52,49,32,122,32,77,32,
51,51,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,51,54,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,
52,49,46,52,50,56,53,55,44,54,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,51,
54,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,56,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,55,51,46,55,57,48,55,52,49,32,122,32,77,32,49,
53,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,53,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,54,
49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,54,54,
46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,49,55,49,46,
52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,54,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,49,53,49,46,52,
50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,122,32,77,32,53,55,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,53,49,46,
52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,50,56,53,55,44,51,56,46,55,57,48,55,52,49,32,76,32,53,51,49,46,52,
50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,50,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,
56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,53,50,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,49,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,
53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,53,48,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,52,49,46,52,50,56,53,
55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,53,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,
44,50,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,
51,51,46,55,57,48,55,52,49,32,76,32,53,57,49,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,56,54,46,52,50,56,53,55,44,52,51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,52,
51,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,76,32,53,56,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,55,54,46,52,50,56,53,55,44,53,51,
46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,53,51,46,55,57,48,55,52,49,32,76,32,53,55,49,46,52,50,56,53,55,44,52,56,46,55,57,48,55,52,49,32,122,32,77,32,51,51,49,46,52,50,56,53,55,44,50,
56,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,50,51,
46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,51,49,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,50,49,46,52,50,56,53,55,44,49,51,46,
55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,56,46,55,57,48,55,52,49,50,32,76,32,51,51,49,46,52,50,56,53,55,44,51,46,55,57,
48,55,52,49,50,32,76,32,51,53,54,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,51,46,55,57,48,55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,56,46,55,57,48,
55,52,49,50,32,76,32,51,56,49,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,54,54,46,52,50,56,53,55,44,49,51,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,49,51,46,55,57,48,
55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,49,56,46,55,57,48,55,52,49,32,76,32,51,53,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,52,54,46,52,50,56,53,55,44,50,51,46,55,57,48,55,
52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,50,51,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,32,76,32,51,52,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,
49,32,76,32,51,51,54,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,51,51,46,55,57,48,55,52,49,32,76,32,51,51,49,46,52,50,56,53,55,44,50,56,46,55,57,48,55,52,49,
32,122,32,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,50,51,57,57,34,32,47,62,10,32,32,32,32,60,47,103,62,10,32,32,60,47,103,62,10,60,47,115,118,103,62,10,0,0};

const char* MrAlias2Editor::alias_svg2 = (const char*) resource_MrAlias2Editor_alias_svg2;
const int MrAlias2Editor::alias_svg2Size = 85270;

// JUCER_RESOURCE: title_svg2, 4392, "../../../../My Documents/title.svg"
static const unsigned char resource_MrAlias2Editor_title_svg2[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,32,115,
116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,67,114,101,97,116,101,100,32,119,105,116,104,32,73,110,107,115,99,97,112,101,32,40,104,116,116,112,58,47,47,119,119,119,46,105,
110,107,115,99,97,112,101,46,111,114,103,47,41,32,45,45,62,10,60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,108,
101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,119,101,98,46,114,101,115,111,117,114,99,101,46,111,114,103,47,99,99,47,34,10,32,32,32,
120,109,108,110,115,58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,10,32,
32,32,120,109,108,110,115,58,115,118,103,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,116,116,112,58,47,
47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,105,112,111,100,105,
46,115,111,117,114,99,101,102,111,114,103,101,46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,99,97,112,101,61,
34,104,116,116,112,58,47,47,119,119,119,46,105,110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,119,105,100,116,104,61,34,
51,54,51,34,10,32,32,32,104,101,105,103,104,116,61,34,50,52,34,10,32,32,32,105,100,61,34,115,118,103,52,51,56,49,34,10,32,32,32,115,111,100,105,112,111,100,105,58,118,101,114,115,105,111,110,61,34,48,
46,51,50,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,52,53,46,49,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,98,97,115,101,61,34,67,58,92,68,
111,99,117,109,101,110,116,115,32,97,110,100,32,83,101,116,116,105,110,103,115,92,118,105,110,97,114,101,92,77,121,32,68,111,99,117,109,101,110,116,115,34,10,32,32,32,115,111,100,105,112,111,100,105,58,
100,111,99,110,97,109,101,61,34,116,105,116,108,101,46,115,118,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,111,117,116,112,117,116,95,101,120,116,101,110,115,105,111,110,61,34,111,114,103,46,105,
110,107,115,99,97,112,101,46,111,117,116,112,117,116,46,115,118,103,46,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,114,115,105,111,110,61,34,49,46,48,34,62,10,32,32,60,100,101,102,115,10,32,32,
32,32,32,105,100,61,34,100,101,102,115,52,51,56,51,34,32,47,62,10,32,32,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,105,100,61,34,98,97,115,101,34,10,32,
32,32,32,32,112,97,103,101,99,111,108,111,114,61,34,35,102,102,102,102,102,102,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,98,111,114,
100,101,114,111,112,97,99,105,116,121,61,34,49,46,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,48,48,48,34,10,32,32,32,32,32,103,117,105,100,101,116,111,108,101,
114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,111,98,106,101,99,116,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,
105,116,121,61,34,48,46,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,115,104,97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,
34,48,46,57,56,57,57,52,57,52,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,120,61,34,51,50,50,46,55,54,56,53,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,54,53,
46,53,55,53,57,55,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,100,111,99,117,109,101,110,116,45,117,110,105,116,115,61,34,112,120,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,
117,114,114,101,110,116,45,108,97,121,101,114,61,34,108,97,121,101,114,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,55,52,56,34,10,32,32,
32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,104,101,105,103,104,116,61,34,53,55,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,120,61,34,54,
56,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,48,34,10,32,32,32,32,32,104,101,105,103,104,116,61,34,50,52,112,120,34,10,32,32,32,32,32,119,105,100,116,104,
61,34,51,54,51,112,120,34,32,47,62,10,32,32,60,109,101,116,97,100,97,116,97,10,32,32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,52,51,56,54,34,62,10,32,32,32,32,60,114,100,102,58,82,68,70,62,
10,32,32,32,32,32,32,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,10,32,32,32,32,32,32,32,32,60,100,99,58,102,111,114,109,97,116,62,105,109,97,
103,101,47,115,118,103,43,120,109,108,60,47,100,99,58,102,111,114,109,97,116,62,10,32,32,32,32,32,32,32,32,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,102,58,114,101,115,111,
117,114,99,101,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,10,32,32,32,32,32,32,60,47,
99,99,58,87,111,114,107,62,10,32,32,32,32,60,47,114,100,102,58,82,68,70,62,10,32,32,60,47,109,101,116,97,100,97,116,97,62,10,32,32,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,
108,61,34,76,97,121,101,114,32,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,
49,34,62,10,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,48,48,48,48,48,48,34,10,32,32,32,32,32,32,32,100,61,34,77,32,45,49,46,51,101,45,48,48,
54,44,49,50,32,76,32,45,49,46,51,101,45,48,48,54,44,45,50,101,45,48,48,55,32,76,32,49,48,46,57,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,32,50,49,46,57,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,
32,50,49,46,57,57,57,57,57,56,44,52,46,48,48,48,48,48,48,50,32,76,32,50,49,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,50,55,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,
51,51,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,51,51,46,57,57,57,57,57,56,44,49,50,32,76,32,51,51,46,57,57,57,57,57,56,44,49,54,32,76,32,51,56,46,57,57,57,57,57,56,44,49,54,32,76,32,
52,51,46,57,57,57,57,57,56,44,49,54,32,76,32,52,51,46,57,57,57,57,57,56,44,49,50,32,76,32,52,51,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,52,57,46,57,57,57,57,57,56,44,56,46,48,48,48,
48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,52,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,45,50,101,45,48,48,
55,32,76,32,54,55,46,52,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,32,55,56,46,57,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,32,55,56,46,57,57,57,57,57,56,44,49,50,32,76,32,55,56,46,57,57,57,57,
57,56,44,50,52,32,76,32,55,51,46,52,57,57,57,57,56,44,50,52,32,76,32,54,55,46,57,57,57,57,57,56,44,50,52,32,76,32,54,55,46,57,57,57,57,57,56,44,49,54,32,76,32,54,55,46,57,57,57,57,57,56,44,56,46,48,48,
48,48,48,48,50,32,76,32,54,49,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,49,50,32,76,32,
53,53,46,57,57,57,57,57,56,44,49,54,32,76,32,52,57,46,57,57,57,57,57,56,44,49,54,32,76,32,52,51,46,57,57,57,57,57,56,44,49,54,32,76,32,52,51,46,57,57,57,57,57,56,44,50,48,32,76,32,52,51,46,57,57,57,57,
57,56,44,50,52,32,76,32,51,56,46,57,57,57,57,57,56,44,50,52,32,76,32,51,51,46,57,57,57,57,57,56,44,50,52,32,76,32,51,51,46,57,57,57,57,57,56,44,50,48,32,76,32,51,51,46,57,57,57,57,57,56,44,49,54,32,76,
32,50,55,46,57,57,57,57,57,56,44,49,54,32,76,32,50,49,46,57,57,57,57,57,56,44,49,54,32,76,32,50,49,46,57,57,57,57,57,56,44,49,50,32,76,32,50,49,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,
32,49,54,46,52,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,49,48,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,49,48,46,57,57,57,57,57,56,44,49,54,32,76,32,49,48,46,57,57,57,57,
57,56,44,50,52,32,76,32,53,46,52,57,57,57,57,56,51,44,50,52,32,76,32,45,49,46,51,101,45,48,48,54,44,50,52,32,76,32,45,49,46,51,101,45,48,48,54,44,49,50,32,122,32,77,32,56,57,46,57,57,57,57,57,56,44,49,
54,32,76,32,56,57,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,49,48,49,46,53,44,56,46,48,48,48,48,48,48,50,32,76,32,49,49,51,44,56,46,48,48,48,48,48,48,50,32,76,32,49,49,51,44,49,48,32,
76,32,49,49,51,44,49,50,32,76,32,49,48,55,44,49,50,32,76,32,49,48,49,44,49,50,32,76,32,49,48,49,44,49,56,32,76,32,49,48,49,44,50,52,32,76,32,57,53,46,53,48,48,48,48,49,44,50,52,32,76,32,56,57,46,57,57,
57,57,57,56,44,50,52,32,76,32,56,57,46,57,57,57,57,57,56,44,49,54,32,122,32,77,32,49,50,53,44,50,50,32,76,32,49,50,53,44,50,48,32,76,32,49,51,48,44,50,48,32,76,32,49,51,53,44,50,48,32,76,32,49,51,53,44,
50,50,32,76,32,49,51,53,44,50,52,32,76,32,49,51,48,44,50,52,32,76,32,49,50,53,44,50,52,32,76,32,49,50,53,44,50,50,32,122,32,77,32,49,54,57,44,50,48,32,76,32,49,54,57,44,49,54,32,76,32,49,55,52,46,53,44,
49,54,32,76,32,49,56,48,44,49,54,32,76,32,49,56,48,44,49,50,32,76,32,49,56,48,44,56,46,48,48,48,48,48,48,50,32,76,32,49,56,54,46,53,44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,51,44,56,46,48,48,48,48,
48,48,50,32,76,32,49,57,51,44,52,46,48,48,48,48,48,48,50,32,76,32,49,57,51,44,45,50,101,45,48,48,55,32,76,32,49,57,57,44,45,50,101,45,48,48,55,32,76,32,50,48,53,44,45,50,101,45,48,48,55,32,76,32,50,48,
53,44,52,46,48,48,48,48,48,48,50,32,76,32,50,48,53,44,56,46,48,48,48,48,48,48,50,32,76,32,50,49,48,44,56,46,48,48,48,48,48,48,50,32,76,32,50,49,53,44,56,46,48,48,48,48,48,48,50,32,76,32,50,49,53,44,49,
50,32,76,32,50,49,53,44,49,54,32,76,32,50,50,49,44,49,54,32,76,32,50,50,55,44,49,54,32,76,32,50,50,55,44,50,48,32,76,32,50,50,55,44,50,52,32,76,32,50,50,49,44,50,52,32,76,32,50,49,53,44,50,52,32,76,32,
50,49,53,44,50,48,32,76,32,50,49,53,44,49,54,32,76,32,49,57,55,46,53,44,49,54,32,76,32,49,56,48,44,49,54,32,76,32,49,56,48,44,50,48,32,76,32,49,56,48,44,50,52,32,76,32,49,55,52,46,53,44,50,52,32,76,32,
49,54,57,44,50,52,32,76,32,49,54,57,44,50,48,32,122,32,77,32,50,48,53,44,49,48,32,76,32,50,48,53,44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,57,44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,51,44,56,46,
48,48,48,48,48,48,50,32,76,32,49,57,51,44,49,48,32,76,32,49,57,51,44,49,50,32,76,32,49,57,57,44,49,50,32,76,32,50,48,53,44,49,50,32,76,32,50,48,53,44,49,48,32,122,32,77,32,50,51,56,44,49,50,32,76,32,50,
51,56,44,45,50,101,45,48,48,55,32,76,32,50,52,51,46,53,44,45,50,101,45,48,48,55,32,76,32,50,52,57,44,45,50,101,45,48,48,55,32,76,32,50,52,57,44,49,50,32,76,32,50,52,57,44,50,52,32,76,32,50,52,51,46,53,
44,50,52,32,76,32,50,51,56,44,50,52,32,76,32,50,51,56,44,49,50,32,122,32,77,32,50,54,49,44,49,54,32,76,32,50,54,49,44,56,46,48,48,48,48,48,48,50,32,76,32,50,54,54,46,53,44,56,46,48,48,48,48,48,48,50,32,
76,32,50,55,50,44,56,46,48,48,48,48,48,48,50,32,76,32,50,55,50,44,49,54,32,76,32,50,55,50,44,50,52,32,76,32,50,54,54,46,53,44,50,52,32,76,32,50,54,49,44,50,52,32,76,32,50,54,49,44,49,54,32,122,32,77,32,
50,57,52,44,50,50,32,76,32,50,57,52,44,50,48,32,76,32,50,56,57,44,50,48,32,76,32,50,56,52,44,50,48,32,76,32,50,56,52,44,49,56,32,76,32,50,56,52,44,49,54,32,76,32,50,56,57,44,49,54,32,76,32,50,57,52,44,
49,54,32,76,32,50,57,52,44,49,56,32,76,32,50,57,52,44,50,48,32,76,32,51,48,48,44,50,48,32,76,32,51,48,54,44,50,48,32,76,32,51,48,54,44,49,54,32,76,32,51,48,54,44,49,50,32,76,32,50,57,53,44,49,50,32,76,
32,50,56,52,44,49,50,32,76,32,50,56,52,44,49,48,32,76,32,50,56,52,44,56,46,48,48,48,48,48,48,50,32,76,32,50,57,53,44,56,46,48,48,48,48,48,48,50,32,76,32,51,48,54,44,56,46,48,48,48,48,48,48,50,32,76,32,
51,48,54,44,49,48,32,76,32,51,48,54,44,49,50,32,76,32,51,49,49,46,53,44,49,50,32,76,32,51,49,55,44,49,50,32,76,32,51,49,55,44,49,56,32,76,32,51,49,55,44,50,52,32,76,32,51,48,53,46,53,44,50,52,32,76,32,
50,57,52,44,50,52,32,76,32,50,57,52,44,50,50,32,122,32,77,32,51,50,56,44,50,50,32,76,32,51,50,56,44,50,48,32,76,32,51,51,57,46,53,44,50,48,32,76,32,51,53,49,44,50,48,32,76,32,51,53,49,44,49,56,32,76,32,
51,53,49,44,49,54,32,76,32,51,53,55,44,49,54,32,76,32,51,54,51,44,49,54,32,76,32,51,54,51,44,49,56,32,76,32,51,54,51,44,50,48,32,76,32,51,53,55,44,50,48,32,76,32,51,53,49,44,50,48,32,76,32,51,53,49,44,
50,50,32,76,32,51,53,49,44,50,52,32,76,32,51,51,57,46,53,44,50,52,32,76,32,51,50,56,44,50,52,32,76,32,51,50,56,44,50,50,32,122,32,77,32,51,50,56,44,49,52,32,76,32,51,50,56,44,49,50,32,76,32,51,51,52,44,
49,50,32,76,32,51,52,48,44,49,50,32,76,32,51,52,48,44,49,48,32,76,32,51,52,48,44,56,46,48,48,48,48,48,48,50,32,76,32,51,53,49,46,53,44,56,46,48,48,48,48,48,48,50,32,76,32,51,54,51,44,56,46,48,48,48,48,
48,48,50,32,76,32,51,54,51,44,49,48,32,76,32,51,54,51,44,49,50,32,76,32,51,53,49,46,53,44,49,50,32,76,32,51,52,48,44,49,50,32,76,32,51,52,48,44,49,52,32,76,32,51,52,48,44,49,54,32,76,32,51,51,52,44,49,
54,32,76,32,51,50,56,44,49,54,32,76,32,51,50,56,44,49,52,32,122,32,77,32,50,54,49,44,50,46,48,48,48,48,48,48,50,32,76,32,50,54,49,44,45,50,101,45,48,48,55,32,76,32,50,54,54,46,53,44,45,50,101,45,48,48,
55,32,76,32,50,55,50,44,45,50,101,45,48,48,55,32,76,32,50,55,50,44,50,46,48,48,48,48,48,48,50,32,76,32,50,55,50,44,52,46,48,48,48,48,48,48,50,32,76,32,50,54,54,46,53,44,52,46,48,48,48,48,48,48,50,32,76,
32,50,54,49,44,52,46,48,48,48,48,48,48,50,32,76,32,50,54,49,44,50,46,48,48,48,48,48,48,50,32,122,32,34,10,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,52,53,48,34,32,47,62,10,32,32,60,47,103,62,
10,60,47,115,118,103,62,10,0,0};

const char* MrAlias2Editor::title_svg2 = (const char*) resource_MrAlias2Editor_title_svg2;
const int MrAlias2Editor::title_svg2Size = 4392;

// JUCER_RESOURCE: whitetitle_svg, 4390, "../../../../My Documents/whitetitle.svg"
static const unsigned char resource_MrAlias2Editor_whitetitle_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,32,
115,116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,67,114,101,97,116,101,100,32,119,105,116,104,32,73,110,107,115,99,97,112,101,32,40,104,116,116,112,58,47,47,119,119,119,46,
105,110,107,115,99,97,112,101,46,111,114,103,47,41,32,45,45,62,10,60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,
108,101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,119,101,98,46,114,101,115,111,117,114,99,101,46,111,114,103,47,99,99,47,34,10,32,32,
32,120,109,108,110,115,58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,10,
32,32,32,120,109,108,110,115,58,115,118,103,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,116,116,112,58,
47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,105,112,111,100,
105,46,115,111,117,114,99,101,102,111,114,103,101,46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,99,97,112,101,
61,34,104,116,116,112,58,47,47,119,119,119,46,105,110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,119,105,100,116,104,61,
34,51,54,51,34,10,32,32,32,104,101,105,103,104,116,61,34,50,52,34,10,32,32,32,105,100,61,34,115,118,103,52,51,56,49,34,10,32,32,32,115,111,100,105,112,111,100,105,58,118,101,114,115,105,111,110,61,34,
48,46,51,50,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,52,53,46,49,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,98,97,115,101,61,34,67,58,92,
68,111,99,117,109,101,110,116,115,32,97,110,100,32,83,101,116,116,105,110,103,115,92,118,105,110,97,114,101,92,77,121,32,68,111,99,117,109,101,110,116,115,34,10,32,32,32,115,111,100,105,112,111,100,105,
58,100,111,99,110,97,109,101,61,34,119,104,105,116,101,116,105,116,108,101,46,115,118,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,111,117,116,112,117,116,95,101,120,116,101,110,115,105,111,110,
61,34,111,114,103,46,105,110,107,115,99,97,112,101,46,111,117,116,112,117,116,46,115,118,103,46,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,114,115,105,111,110,61,34,49,46,48,34,62,10,32,32,60,
100,101,102,115,10,32,32,32,32,32,105,100,61,34,100,101,102,115,52,51,56,51,34,32,47,62,10,32,32,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,105,100,61,34,
98,97,115,101,34,10,32,32,32,32,32,112,97,103,101,99,111,108,111,114,61,34,35,102,102,102,102,102,102,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,
32,32,32,32,98,111,114,100,101,114,111,112,97,99,105,116,121,61,34,49,46,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,48,48,48,34,10,32,32,32,32,32,103,117,105,
100,101,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,111,98,106,101,99,116,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,
97,103,101,111,112,97,99,105,116,121,61,34,48,46,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,115,104,97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,
101,58,122,111,111,109,61,34,49,46,52,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,120,61,34,50,49,56,46,50,56,50,54,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,50,
52,46,56,49,56,48,57,51,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,100,111,99,117,109,101,110,116,45,117,110,105,116,115,61,34,112,120,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,
99,117,114,114,101,110,116,45,108,97,121,101,114,61,34,108,97,121,101,114,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,55,52,56,34,10,32,
32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,104,101,105,103,104,116,61,34,53,55,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,120,61,34,
54,56,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,48,34,10,32,32,32,32,32,104,101,105,103,104,116,61,34,50,52,112,120,34,10,32,32,32,32,32,119,105,100,116,
104,61,34,51,54,51,112,120,34,32,47,62,10,32,32,60,109,101,116,97,100,97,116,97,10,32,32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,52,51,56,54,34,62,10,32,32,32,32,60,114,100,102,58,82,68,70,
62,10,32,32,32,32,32,32,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,10,32,32,32,32,32,32,32,32,60,100,99,58,102,111,114,109,97,116,62,105,109,
97,103,101,47,115,118,103,43,120,109,108,60,47,100,99,58,102,111,114,109,97,116,62,10,32,32,32,32,32,32,32,32,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,102,58,114,101,115,
111,117,114,99,101,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,10,32,32,32,32,32,32,60,
47,99,99,58,87,111,114,107,62,10,32,32,32,32,60,47,114,100,102,58,82,68,70,62,10,32,32,60,47,109,101,116,97,100,97,116,97,62,10,32,32,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,
101,108,61,34,76,97,121,101,114,32,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,
114,49,34,62,10,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,34,10,32,32,32,32,32,32,32,100,61,34,77,32,45,49,46,51,101,
45,48,48,54,44,49,50,32,76,32,45,49,46,51,101,45,48,48,54,44,45,50,101,45,48,48,55,32,76,32,49,48,46,57,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,32,50,49,46,57,57,57,57,57,56,44,45,50,101,45,48,48,
55,32,76,32,50,49,46,57,57,57,57,57,56,44,52,46,48,48,48,48,48,48,50,32,76,32,50,49,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,50,55,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,
32,76,32,51,51,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,51,51,46,57,57,57,57,57,56,44,49,50,32,76,32,51,51,46,57,57,57,57,57,56,44,49,54,32,76,32,51,56,46,57,57,57,57,57,56,44,49,54,
32,76,32,52,51,46,57,57,57,57,57,56,44,49,54,32,76,32,52,51,46,57,57,57,57,57,56,44,49,50,32,76,32,52,51,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,52,57,46,57,57,57,57,57,56,44,56,46,
48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,52,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,45,50,101,
45,48,48,55,32,76,32,54,55,46,52,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,32,55,56,46,57,57,57,57,57,56,44,45,50,101,45,48,48,55,32,76,32,55,56,46,57,57,57,57,57,56,44,49,50,32,76,32,55,56,46,57,
57,57,57,57,56,44,50,52,32,76,32,55,51,46,52,57,57,57,57,56,44,50,52,32,76,32,54,55,46,57,57,57,57,57,56,44,50,52,32,76,32,54,55,46,57,57,57,57,57,56,44,49,54,32,76,32,54,55,46,57,57,57,57,57,56,44,56,
46,48,48,48,48,48,48,50,32,76,32,54,49,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,53,53,46,57,57,57,57,57,56,44,49,50,
32,76,32,53,53,46,57,57,57,57,57,56,44,49,54,32,76,32,52,57,46,57,57,57,57,57,56,44,49,54,32,76,32,52,51,46,57,57,57,57,57,56,44,49,54,32,76,32,52,51,46,57,57,57,57,57,56,44,50,48,32,76,32,52,51,46,57,
57,57,57,57,56,44,50,52,32,76,32,51,56,46,57,57,57,57,57,56,44,50,52,32,76,32,51,51,46,57,57,57,57,57,56,44,50,52,32,76,32,51,51,46,57,57,57,57,57,56,44,50,48,32,76,32,51,51,46,57,57,57,57,57,56,44,49,
54,32,76,32,50,55,46,57,57,57,57,57,56,44,49,54,32,76,32,50,49,46,57,57,57,57,57,56,44,49,54,32,76,32,50,49,46,57,57,57,57,57,56,44,49,50,32,76,32,50,49,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,
50,32,76,32,49,54,46,52,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,49,48,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,49,48,46,57,57,57,57,57,56,44,49,54,32,76,32,49,48,46,57,
57,57,57,57,56,44,50,52,32,76,32,53,46,52,57,57,57,57,56,51,44,50,52,32,76,32,45,49,46,51,101,45,48,48,54,44,50,52,32,76,32,45,49,46,51,101,45,48,48,54,44,49,50,32,122,32,77,32,56,57,46,57,57,57,57,57,
56,44,49,54,32,76,32,56,57,46,57,57,57,57,57,56,44,56,46,48,48,48,48,48,48,50,32,76,32,49,48,49,46,53,44,56,46,48,48,48,48,48,48,50,32,76,32,49,49,51,44,56,46,48,48,48,48,48,48,50,32,76,32,49,49,51,44,
49,48,32,76,32,49,49,51,44,49,50,32,76,32,49,48,55,44,49,50,32,76,32,49,48,49,44,49,50,32,76,32,49,48,49,44,49,56,32,76,32,49,48,49,44,50,52,32,76,32,57,53,46,53,48,48,48,48,49,44,50,52,32,76,32,56,57,
46,57,57,57,57,57,56,44,50,52,32,76,32,56,57,46,57,57,57,57,57,56,44,49,54,32,122,32,77,32,49,50,53,44,50,50,32,76,32,49,50,53,44,50,48,32,76,32,49,51,48,44,50,48,32,76,32,49,51,53,44,50,48,32,76,32,49,
51,53,44,50,50,32,76,32,49,51,53,44,50,52,32,76,32,49,51,48,44,50,52,32,76,32,49,50,53,44,50,52,32,76,32,49,50,53,44,50,50,32,122,32,77,32,49,54,57,44,50,48,32,76,32,49,54,57,44,49,54,32,76,32,49,55,52,
46,53,44,49,54,32,76,32,49,56,48,44,49,54,32,76,32,49,56,48,44,49,50,32,76,32,49,56,48,44,56,46,48,48,48,48,48,48,50,32,76,32,49,56,54,46,53,44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,51,44,56,46,48,
48,48,48,48,48,50,32,76,32,49,57,51,44,52,46,48,48,48,48,48,48,50,32,76,32,49,57,51,44,45,50,101,45,48,48,55,32,76,32,49,57,57,44,45,50,101,45,48,48,55,32,76,32,50,48,53,44,45,50,101,45,48,48,55,32,76,
32,50,48,53,44,52,46,48,48,48,48,48,48,50,32,76,32,50,48,53,44,56,46,48,48,48,48,48,48,50,32,76,32,50,49,48,44,56,46,48,48,48,48,48,48,50,32,76,32,50,49,53,44,56,46,48,48,48,48,48,48,50,32,76,32,50,49,
53,44,49,50,32,76,32,50,49,53,44,49,54,32,76,32,50,50,49,44,49,54,32,76,32,50,50,55,44,49,54,32,76,32,50,50,55,44,50,48,32,76,32,50,50,55,44,50,52,32,76,32,50,50,49,44,50,52,32,76,32,50,49,53,44,50,52,
32,76,32,50,49,53,44,50,48,32,76,32,50,49,53,44,49,54,32,76,32,49,57,55,46,53,44,49,54,32,76,32,49,56,48,44,49,54,32,76,32,49,56,48,44,50,48,32,76,32,49,56,48,44,50,52,32,76,32,49,55,52,46,53,44,50,52,
32,76,32,49,54,57,44,50,52,32,76,32,49,54,57,44,50,48,32,122,32,77,32,50,48,53,44,49,48,32,76,32,50,48,53,44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,57,44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,51,
44,56,46,48,48,48,48,48,48,50,32,76,32,49,57,51,44,49,48,32,76,32,49,57,51,44,49,50,32,76,32,49,57,57,44,49,50,32,76,32,50,48,53,44,49,50,32,76,32,50,48,53,44,49,48,32,122,32,77,32,50,51,56,44,49,50,32,
76,32,50,51,56,44,45,50,101,45,48,48,55,32,76,32,50,52,51,46,53,44,45,50,101,45,48,48,55,32,76,32,50,52,57,44,45,50,101,45,48,48,55,32,76,32,50,52,57,44,49,50,32,76,32,50,52,57,44,50,52,32,76,32,50,52,
51,46,53,44,50,52,32,76,32,50,51,56,44,50,52,32,76,32,50,51,56,44,49,50,32,122,32,77,32,50,54,49,44,49,54,32,76,32,50,54,49,44,56,46,48,48,48,48,48,48,50,32,76,32,50,54,54,46,53,44,56,46,48,48,48,48,48,
48,50,32,76,32,50,55,50,44,56,46,48,48,48,48,48,48,50,32,76,32,50,55,50,44,49,54,32,76,32,50,55,50,44,50,52,32,76,32,50,54,54,46,53,44,50,52,32,76,32,50,54,49,44,50,52,32,76,32,50,54,49,44,49,54,32,122,
32,77,32,50,57,52,44,50,50,32,76,32,50,57,52,44,50,48,32,76,32,50,56,57,44,50,48,32,76,32,50,56,52,44,50,48,32,76,32,50,56,52,44,49,56,32,76,32,50,56,52,44,49,54,32,76,32,50,56,57,44,49,54,32,76,32,50,
57,52,44,49,54,32,76,32,50,57,52,44,49,56,32,76,32,50,57,52,44,50,48,32,76,32,51,48,48,44,50,48,32,76,32,51,48,54,44,50,48,32,76,32,51,48,54,44,49,54,32,76,32,51,48,54,44,49,50,32,76,32,50,57,53,44,49,
50,32,76,32,50,56,52,44,49,50,32,76,32,50,56,52,44,49,48,32,76,32,50,56,52,44,56,46,48,48,48,48,48,48,50,32,76,32,50,57,53,44,56,46,48,48,48,48,48,48,50,32,76,32,51,48,54,44,56,46,48,48,48,48,48,48,50,
32,76,32,51,48,54,44,49,48,32,76,32,51,48,54,44,49,50,32,76,32,51,49,49,46,53,44,49,50,32,76,32,51,49,55,44,49,50,32,76,32,51,49,55,44,49,56,32,76,32,51,49,55,44,50,52,32,76,32,51,48,53,46,53,44,50,52,
32,76,32,50,57,52,44,50,52,32,76,32,50,57,52,44,50,50,32,122,32,77,32,51,50,56,44,50,50,32,76,32,51,50,56,44,50,48,32,76,32,51,51,57,46,53,44,50,48,32,76,32,51,53,49,44,50,48,32,76,32,51,53,49,44,49,56,
32,76,32,51,53,49,44,49,54,32,76,32,51,53,55,44,49,54,32,76,32,51,54,51,44,49,54,32,76,32,51,54,51,44,49,56,32,76,32,51,54,51,44,50,48,32,76,32,51,53,55,44,50,48,32,76,32,51,53,49,44,50,48,32,76,32,51,
53,49,44,50,50,32,76,32,51,53,49,44,50,52,32,76,32,51,51,57,46,53,44,50,52,32,76,32,51,50,56,44,50,52,32,76,32,51,50,56,44,50,50,32,122,32,77,32,51,50,56,44,49,52,32,76,32,51,50,56,44,49,50,32,76,32,51,
51,52,44,49,50,32,76,32,51,52,48,44,49,50,32,76,32,51,52,48,44,49,48,32,76,32,51,52,48,44,56,46,48,48,48,48,48,48,50,32,76,32,51,53,49,46,53,44,56,46,48,48,48,48,48,48,50,32,76,32,51,54,51,44,56,46,48,
48,48,48,48,48,50,32,76,32,51,54,51,44,49,48,32,76,32,51,54,51,44,49,50,32,76,32,51,53,49,46,53,44,49,50,32,76,32,51,52,48,44,49,50,32,76,32,51,52,48,44,49,52,32,76,32,51,52,48,44,49,54,32,76,32,51,51,
52,44,49,54,32,76,32,51,50,56,44,49,54,32,76,32,51,50,56,44,49,52,32,122,32,77,32,50,54,49,44,50,46,48,48,48,48,48,48,50,32,76,32,50,54,49,44,45,50,101,45,48,48,55,32,76,32,50,54,54,46,53,44,45,50,101,
45,48,48,55,32,76,32,50,55,50,44,45,50,101,45,48,48,55,32,76,32,50,55,50,44,50,46,48,48,48,48,48,48,50,32,76,32,50,55,50,44,52,46,48,48,48,48,48,48,50,32,76,32,50,54,54,46,53,44,52,46,48,48,48,48,48,48,
50,32,76,32,50,54,49,44,52,46,48,48,48,48,48,48,50,32,76,32,50,54,49,44,50,46,48,48,48,48,48,48,50,32,122,32,34,10,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,52,53,48,34,32,47,62,10,32,32,60,
47,103,62,10,60,47,115,118,103,62,10,0,0};

const char* MrAlias2Editor::whitetitle_svg = (const char*) resource_MrAlias2Editor_whitetitle_svg;
const int MrAlias2Editor::whitetitle_svgSize = 4390;
