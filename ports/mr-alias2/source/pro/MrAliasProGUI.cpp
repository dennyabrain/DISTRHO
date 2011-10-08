/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 Dec 2009 4:33:40 pm

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

#include "MrAliasProGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#ifdef MRALIASPRO

MrAliasKeyboard::MrAliasKeyboard(MidiKeyboardState &state, const Orientation orientation)
    : MidiKeyboardComponent(state,orientation)
{
    s = &state;
    const char* const keymap = "zsxdcvgbhnjmq2w3er5t6y7ui9o0p[";

    for (int i = String (keymap).length(); --i >= 0;)
        setKeyPressForNote (KeyPress (keymap[i], 0, 0), i);
    setKeyPressBaseOctave(2);
}

bool MrAliasKeyboard::mouseDownOnKey(int midiNoteNumber, const MouseEvent &e) {
    if (e.mods.isPopupMenu()) {
        if (s->isNoteOn(this->getMidiChannel(),midiNoteNumber)) {
            s->noteOff(this->getMidiChannel(),midiNoteNumber);
        }
        else {
            s->noteOn(this->getMidiChannel(),midiNoteNumber,1.f);
        }
        return false;
    }
    else if (e.mods.isShiftDown()) {
        setKeyPressBaseOctave(midiNoteNumber/12);
        return false;
    }
    else if (e.mods.isCtrlDown() || e.mods.isMiddleButtonDown()) {
        s->allNotesOff(this->getMidiChannel());
        return false;
    }
    return true;
}

#endif
//[/MiscUserDefs]

//==============================================================================
MrAlias2Editor::MrAlias2Editor (MrAlias2* const ownerFilter)
    : AudioProcessorEditor (ownerFilter),
      aspectRatio(1.7125),
      bg(0),
      wood1(0),
      wood2(0),
      smallKnob(0),
      largeKnob(0),
      hSliderThumb(0),
      hSliderBG(0),
      vSliderThumb(0),
      vSliderBG(0),
      sChannel (0),
      keyboard (0),
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
      sPitchShift (0),
      resizer (0),
      patchBox (0),
      sVolume (0),
      toggleButton (0),
      decoupled1Button (0),
      decoupled2Button (0),
      sDecoupled2 (0),
      sDecoupled1 (0),
      sGlide (0),
      sRetrig (0),
      page2 (0),
      sLFO1Rate (0),
      sLFO1Amount (0),
      sEnv3Amount (0),
      sRel3 (0),
      sSus3 (0),
      sDec3 (0),
      sAtt3 (0),
      sPage (0),
      Env3DestBox (0),
      sLFO2Rate (0),
      sLFO2Amount (0),
      LFO1WaveBox (0),
      LFO2WaveBox (0),
      menuButton (0),
      lfo1indicator (0),
      bLFO1Free (0),
      bLFO2Free (0),
      LFO1DestBox (0),
      LFO2DestBox (0),
      lfo2indicator (0),
      aboutbox (0),
      env3indicator (0),
      demoButton (0),
      bAuto (0),
      bDraw (0),
      bDraw2 (0),
      waveDrawer (0),
      sync1 (0),
      sync2 (0),
      sExp3 (0),
      interpolate1 (0),
      interpolate2 (0),
      cachedImage_wood2_png (0),
      cachedImage_wood1_png (0)
{
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

    addAndMakeVisible (keyboard = new MrAliasKeyboard (ownerFilter->keyboardState,MidiKeyboardComponent::horizontalKeyboard));
    keyboard->setName (T("keyboard"));

    addAndMakeVisible (sAlias = new ProSliderH (T("Alias")));
    sAlias->setTooltip (T("Alias"));
    sAlias->setRange (0, 102, 0.01);
    sAlias->setSliderStyle (Slider::LinearHorizontal);
    sAlias->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAlias->addListener (this);

    addAndMakeVisible (sCutoff = new ProKnob (T("Filter Cutoff")));
    sCutoff->setTooltip (T("Filter Cutoff"));
    sCutoff->setRange (0, 99, 0);
    sCutoff->setSliderStyle (Slider::RotaryVerticalDrag);
    sCutoff->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sCutoff->setColour (Slider::backgroundColourId, Colour (0x0));
    sCutoff->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sCutoff->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sCutoff->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sCutoff->addListener (this);

    addAndMakeVisible (sDivide = new ProSliderH (T("Divide")));
    sDivide->setTooltip (T("Divide"));
    sDivide->setRange (0, 100, 1);
    sDivide->setSliderStyle (Slider::LinearHorizontal);
    sDivide->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDivide->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    sDivide->addListener (this);
    sDivide->setSkewFactor (0.5);

    addAndMakeVisible (sAtt = new ProSliderV (T("Amp Env Attack")));
    sAtt->setTooltip (T("Amp Env Attack"));
    sAtt->setRange (0, 100, 0);
    sAtt->setSliderStyle (Slider::LinearVertical);
    sAtt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAtt->addListener (this);

    addAndMakeVisible (sRate = new ProSliderH (T("Downsample Rate")));
    sRate->setTooltip (T("Downsample Rate"));
    sRate->setRange (0, 100, 0.1);
    sRate->setSliderStyle (Slider::LinearHorizontal);
    sRate->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRate->addListener (this);

    addAndMakeVisible (sSineMix = new ProKnob (T("Sine Mix")));
    sSineMix->setTooltip (T("Sine Mix"));
    sSineMix->setRange (0, 99, 0);
    sSineMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sSineMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSineMix->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sSineMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sSineMix->addListener (this);

    addAndMakeVisible (sSineRes = new ProSliderH (T("Sine Resolution")));
    sSineRes->setTooltip (T("Sine Resolution"));
    sSineRes->setRange (0, 100, 0.1);
    sSineRes->setSliderStyle (Slider::LinearHorizontal);
    sSineRes->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSineRes->addListener (this);

    addAndMakeVisible (sPostDivide = new ProSliderH (T("Post Divide")));
    sPostDivide->setTooltip (T("Post Divide"));
    sPostDivide->setRange (0, 100, 1);
    sPostDivide->setSliderStyle (Slider::LinearHorizontal);
    sPostDivide->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPostDivide->addListener (this);
    sPostDivide->setSkewFactor (0.5);

    addAndMakeVisible (sClip = new ProSliderH (T("Clipper")));
    sClip->setTooltip (T("Clipper"));
    sClip->setRange (0, 100, 0.1);
    sClip->setSliderStyle (Slider::LinearHorizontal);
    sClip->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sClip->addListener (this);

    addAndMakeVisible (sAInertia = new ProKnob (T("Inertia")));
    sAInertia->setTooltip (T("Inertia"));
    sAInertia->setRange (0, 99, 0);
    sAInertia->setSliderStyle (Slider::RotaryVerticalDrag);
    sAInertia->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAInertia->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sAInertia->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sAInertia->addListener (this);

    addAndMakeVisible (sDec = new ProSliderV (T("Amp Env Decay")));
    sDec->setTooltip (T("Amp Env Decay"));
    sDec->setRange (0, 100, 0);
    sDec->setSliderStyle (Slider::LinearVertical);
    sDec->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDec->addListener (this);

    addAndMakeVisible (sSus = new ProSliderV (T("Amp Env Sustain")));
    sSus->setTooltip (T("Amp Env Sustain"));
    sSus->setRange (0, 100, 0);
    sSus->setSliderStyle (Slider::LinearVertical);
    sSus->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSus->addListener (this);

    addAndMakeVisible (sRel = new ProSliderV (T("Amp Env Release")));
    sRel->setTooltip (T("Amp Env Release"));
    sRel->setRange (0, 100, 0);
    sRel->setSliderStyle (Slider::LinearVertical);
    sRel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRel->addListener (this);

    addAndMakeVisible (sDivEnv = new ProKnob (T("AmpEnv -> Divider")));
    sDivEnv->setTooltip (T("AmpEnv -> Divider"));
    sDivEnv->setRange (0, 99, 0);
    sDivEnv->setSliderStyle (Slider::RotaryVerticalDrag);
    sDivEnv->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDivEnv->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sDivEnv->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sDivEnv->addListener (this);

    addAndMakeVisible (sRes = new ProKnob (T("Filter Resonance")));
    sRes->setTooltip (T("Filter Resonance"));
    sRes->setRange (0, 99, 0);
    sRes->setSliderStyle (Slider::RotaryVerticalDrag);
    sRes->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRes->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sRes->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sRes->addListener (this);

    addAndMakeVisible (sBRMix = new ProKnob (T("Downsampler Mix")));
    sBRMix->setTooltip (T("Downsampler Mix"));
    sBRMix->setRange (0, 99, 0.1);
    sBRMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sBRMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sBRMix->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sBRMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sBRMix->addListener (this);

    addAndMakeVisible (sSineFreq = new ProSliderH (T("Sine Frequency")));
    sSineFreq->setTooltip (T("Sine Frequency"));
    sSineFreq->setRange (0, 100, 0.1);
    sSineFreq->setSliderStyle (Slider::LinearHorizontal);
    sSineFreq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSineFreq->addListener (this);

    addAndMakeVisible (sVelSens = new ProKnob (T("Velocity Sensitivity")));
    sVelSens->setTooltip (T("Amp Velocity Sensitivity"));
    sVelSens->setRange (0, 99, 0);
    sVelSens->setSliderStyle (Slider::RotaryVerticalDrag);
    sVelSens->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sVelSens->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sVelSens->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sVelSens->addListener (this);

    addAndMakeVisible (sFiltEnv = new ProKnob (T("Filter Env Amount")));
    sFiltEnv->setTooltip (T("Filter Env Amount"));
    sFiltEnv->setRange (0, 99, 0);
    sFiltEnv->setSliderStyle (Slider::RotaryVerticalDrag);
    sFiltEnv->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFiltEnv->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sFiltEnv->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sFiltEnv->addListener (this);

    addAndMakeVisible (sFVSens = new ProKnob (T("Filter Velocity Sens")));
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

    addAndMakeVisible (sInputGain = new ProKnob (T("Input Gain")));
    sInputGain->setTooltip (T("Input Gain"));
    sInputGain->setRange (0, 99, 0);
    sInputGain->setSliderStyle (Slider::RotaryVerticalDrag);
    sInputGain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sInputGain->setColour (Slider::backgroundColourId, Colour (0x0));
    sInputGain->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sInputGain->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sInputGain->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sInputGain->addListener (this);

    addAndMakeVisible (sWet = new ProKnob (T("Wet/Dry")));
    sWet->setTooltip (T("Wet/Dry"));
    sWet->setRange (-99, 99, 0);
    sWet->setSliderStyle (Slider::RotaryVerticalDrag);
    sWet->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sWet->setColour (Slider::backgroundColourId, Colour (0x0));
    sWet->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sWet->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sWet->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sWet->addListener (this);

    addAndMakeVisible (sOscGain = new ProKnob (T("Synth Gain")));
    sOscGain->setTooltip (T("Synth Gain"));
    sOscGain->setRange (0, 99, 0);
    sOscGain->setSliderStyle (Slider::RotaryVerticalDrag);
    sOscGain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOscGain->setColour (Slider::backgroundColourId, Colour (0x0));
    sOscGain->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sOscGain->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sOscGain->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sOscGain->addListener (this);

    addAndMakeVisible (sThresh = new ProSliderH (T("Div Threshold")));
    sThresh->setTooltip (T("Div Threshold"));
    sThresh->setRange (0, 100, 0.1);
    sThresh->setSliderStyle (Slider::LinearHorizontal);
    sThresh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sThresh->setColour (Slider::backgroundColourId, Colour (0xff));
    sThresh->addListener (this);

    addAndMakeVisible (sFreq1 = new ProKnob (T("Detune")));
    sFreq1->setTooltip (T("Detune"));
    sFreq1->setRange (-99, 99, 0);
    sFreq1->setSliderStyle (Slider::RotaryVerticalDrag);
    sFreq1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFreq1->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sFreq1->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sFreq1->addListener (this);

    addAndMakeVisible (sRingMod = new ProKnob (T("Ring Modulation")));
    sRingMod->setTooltip (T("Ring Modulation"));
    sRingMod->setRange (0, 99, 0);
    sRingMod->setSliderStyle (Slider::RotaryVerticalDrag);
    sRingMod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRingMod->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sRingMod->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sRingMod->addListener (this);

    addAndMakeVisible (sFAtt = new ProSliderV (T("Filter Env Attack")));
    sFAtt->setTooltip (T("Filter Env Attack"));
    sFAtt->setRange (0, 100, 0);
    sFAtt->setSliderStyle (Slider::LinearVertical);
    sFAtt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFAtt->addListener (this);

    addAndMakeVisible (sFDec = new ProSliderV (T("Filter Env Decay")));
    sFDec->setTooltip (T("Filter Env Decay"));
    sFDec->setRange (0, 100, 0);
    sFDec->setSliderStyle (Slider::LinearVertical);
    sFDec->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFDec->addListener (this);

    addAndMakeVisible (sFSus = new ProSliderV (T("Filter Env Sustain")));
    sFSus->setTooltip (T("Filter Env Sustain"));
    sFSus->setRange (0, 100, 0);
    sFSus->setSliderStyle (Slider::LinearVertical);
    sFSus->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFSus->addListener (this);

    addAndMakeVisible (sFRel = new ProSliderV (T("Filter Env Release")));
    sFRel->setTooltip (T("Filter Env Release"));
    sFRel->setRange (0, 100, 0);
    sFRel->setSliderStyle (Slider::LinearVertical);
    sFRel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sFRel->addListener (this);

    addAndMakeVisible (audioled = new LED());
    addAndMakeVisible (sStereo = new ProKnob (T("Osc Separation")));
    sStereo->setTooltip (T("Osc Separation"));
    sStereo->setRange (-99, 99, 0);
    sStereo->setSliderStyle (Slider::RotaryVerticalDrag);
    sStereo->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sStereo->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sStereo->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sStereo->addListener (this);

    addAndMakeVisible (sOscMix = new ProKnob (T("Osc Mix")));
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

    addAndMakeVisible (sStereo2 = new ProSliderH (T("Stereo")));
    sStereo2->setTooltip (T("Stereo"));
    sStereo2->setRange (0, 100, 0.1);
    sStereo2->setSliderStyle (Slider::LinearHorizontal);
    sStereo2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sStereo2->addListener (this);

    addAndMakeVisible (sM1 = new ProSliderH (T("M Factor")));
    sM1->setTooltip (T("M Factor"));
    sM1->setRange (0, 100, 0.001);
    sM1->setSliderStyle (Slider::LinearHorizontal);
    sM1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sM1->addListener (this);
    sM1->setSkewFactor (0.5);

    addAndMakeVisible (sPhMod = new ProKnob (T("Phase Mod")));
    sPhMod->setTooltip (T("Phase Mod"));
    sPhMod->setRange (0, 99, 0);
    sPhMod->setSliderStyle (Slider::RotaryVerticalDrag);
    sPhMod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPhMod->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sPhMod->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sPhMod->addListener (this);
    sPhMod->setSkewFactor (0.5);

    addAndMakeVisible (sDivMix = new ProKnob (T("Divider Mix")));
    sDivMix->setTooltip (T("Divider Mix"));
    sDivMix->setRange (0, 99, 0.1);
    sDivMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sDivMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDivMix->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sDivMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sDivMix->addListener (this);

    addAndMakeVisible (info = new Label (T("new label"),
                                         String::empty));
    info->setFont (Font (11.0000f, Font::plain));
    info->setJustificationType (Justification::centredLeft);
    info->setEditable (false, false, false);
    info->setColour (Label::textColourId, Colour (0xa6ffffff));
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
    nextButton->setColour (TextButton::textColourId, Colours::white);

    addAndMakeVisible (prevButton = new TextButton (T("previous")));
    prevButton->setTooltip (T("Previous Preset"));
    prevButton->setButtonText (T("<"));
    prevButton->addButtonListener (this);
    prevButton->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    prevButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    prevButton->setColour (TextButton::textColourId, Colours::white);

    addAndMakeVisible (sReset = new TextButton (T("Reset")));
    sReset->setTooltip (T("Reset all parameters"));
    sReset->addButtonListener (this);
    sReset->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    sReset->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sReset->setColour (TextButton::textColourId, Colour (0xc5ffffff));

    addAndMakeVisible (sOPLP = new Slider (T("Harshness")));
    sOPLP->setTooltip (T("Harshness"));
    sOPLP->setRange (0, 99, 0);
    sOPLP->setSliderStyle (Slider::RotaryVerticalDrag);
    sOPLP->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sOPLP->setColour (Slider::rotarySliderFillColourId, Colour (0x0));
    sOPLP->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff));
    sOPLP->setColour (Slider::textBoxTextColourId, Colours::white);
    sOPLP->addListener (this);

    addAndMakeVisible (sPostDivMix = new ProKnob (T("Post Divider Mix")));
    sPostDivMix->setTooltip (T("Post Divider Mix"));
    sPostDivMix->setRange (0, 99, 0.1);
    sPostDivMix->setSliderStyle (Slider::RotaryVerticalDrag);
    sPostDivMix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sPostDivMix->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sPostDivMix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sPostDivMix->addListener (this);

    addAndMakeVisible (sSavePatch = new TextButton (T("Save Patch")));
    sSavePatch->setTooltip (T("Save patch"));
    sSavePatch->setButtonText (T("Save patch"));
    sSavePatch->addButtonListener (this);
    sSavePatch->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    sSavePatch->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sSavePatch->setColour (TextButton::textColourId, Colour (0xc5ffffff));

    addAndMakeVisible (sSavePatch2 = new TextButton (T("Save Bank")));
    sSavePatch2->setTooltip (T("Save bank"));
    sSavePatch2->setButtonText (T("Save bank"));
    sSavePatch2->addButtonListener (this);
    sSavePatch2->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    sSavePatch2->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    sSavePatch2->setColour (TextButton::textColourId, Colour (0xc5ffffff));

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
    loadButton->setColour (TextButton::textColourId, Colour (0xc5ffffff));

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
    comboBox->addItem (T("Drawable1"), 19);
    comboBox->addItem (T("Drawable2"), 20);
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
    comboBox2->addItem (T("Drawable1"), 19);
    comboBox2->addItem (T("Drawable2"), 20);
    comboBox2->addListener (this);

    addAndMakeVisible (sOctave = new ProKnob (T("Osc 2 Harmonic")));
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
    sUseProgCh->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (sM1Mix = new ProKnob (T("M Effect Mix")));
    sM1Mix->setTooltip (T("M Effect Mix"));
    sM1Mix->setRange (0, 99, 0.1);
    sM1Mix->setSliderStyle (Slider::RotaryVerticalDrag);
    sM1Mix->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sM1Mix->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sM1Mix->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sM1Mix->addListener (this);

    addAndMakeVisible (randomButton = new TextButton (T("Randomize")));
    randomButton->setTooltip (T("Randomize all parameters"));
    randomButton->addButtonListener (this);
    randomButton->setColour (TextButton::buttonColourId, Colour (0x478f8f9e));
    randomButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    randomButton->setColour (TextButton::textColourId, Colour (0xc5ffffff));

    addAndMakeVisible (limiterButton = new TextButton (T("Limiter")));
    limiterButton->setTooltip (T("Limiter"));
    limiterButton->addButtonListener (this);
    limiterButton->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    limiterButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    limiterButton->setColour (TextButton::textColourId, Colours::black);

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
    saveSnapshotButtonB->setConnectedEdges (Button::ConnectedOnRight);
    saveSnapshotButtonB->addButtonListener (this);
    saveSnapshotButtonB->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    saveSnapshotButtonB->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    saveSnapshotButtonB->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (recallSnapshotButtonB = new TextButton (T("Recall Snapshot")));
    recallSnapshotButtonB->setTooltip (T("Recall Snapshot B"));
    recallSnapshotButtonB->setButtonText (T("R"));
    recallSnapshotButtonB->setConnectedEdges (Button::ConnectedOnRight);
    recallSnapshotButtonB->addButtonListener (this);
    recallSnapshotButtonB->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    recallSnapshotButtonB->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    recallSnapshotButtonB->setColour (TextButton::textColourId, Colours::black);

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
    saveSnapshotButtonA->setConnectedEdges (Button::ConnectedOnLeft);
    saveSnapshotButtonA->addButtonListener (this);
    saveSnapshotButtonA->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    saveSnapshotButtonA->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    saveSnapshotButtonA->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (recallSnapshotButtonA = new TextButton (T("Recall Snapshot")));
    recallSnapshotButtonA->setTooltip (T("Recall Snapshot A"));
    recallSnapshotButtonA->setButtonText (T("R"));
    recallSnapshotButtonA->setConnectedEdges (Button::ConnectedOnLeft);
    recallSnapshotButtonA->addButtonListener (this);
    recallSnapshotButtonA->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    recallSnapshotButtonA->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    recallSnapshotButtonA->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (sPitchShift = new TextButton (T("Pitch Shift Input")));
    sPitchShift->setTooltip (T("Pitch Shift Input"));
    sPitchShift->setButtonText (T("PitchShift"));
    sPitchShift->addButtonListener (this);
    sPitchShift->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sPitchShift->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));

    addAndMakeVisible (patchBox = new PizComboBox (T("Program Select")));
    patchBox->setTooltip (T("Select Patch"));
    patchBox->setEditableText (false);
    patchBox->setJustificationType (Justification::centredLeft);
    patchBox->setTextWhenNothingSelected (String::empty);
    patchBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    patchBox->addItem (T("dummy1"), 1);
    patchBox->addItem (T("dummy2"), 2);
    patchBox->addListener (this);

    addAndMakeVisible (sVolume = new ProKnob (T("Main Volume")));
    sVolume->setTooltip (T("Main Volume"));
    sVolume->setRange (0, 99, 0);
    sVolume->setSliderStyle (Slider::RotaryVerticalDrag);
    sVolume->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sVolume->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sVolume->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sVolume->addListener (this);

    addAndMakeVisible (toggleButton = new TextButton (T("new button")));
    toggleButton->setTooltip (T("Grab QWERTY"));
    toggleButton->setButtonText (T(">"));
    toggleButton->addButtonListener (this);
    toggleButton->setColour (TextButton::buttonColourId, Colour (0x30bbbbff));

    addAndMakeVisible (decoupled1Button = new TextButton (T("Decoupled 1")));
    decoupled1Button->setTooltip (T("Decouple Osc 1"));
    decoupled1Button->setButtonText (String::empty);
    decoupled1Button->addButtonListener (this);
    decoupled1Button->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    decoupled1Button->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    decoupled1Button->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (decoupled2Button = new TextButton (T("Decoupled 2")));
    decoupled2Button->setTooltip (T("Decouple Osc 2"));
    decoupled2Button->setButtonText (String::empty);
    decoupled2Button->addButtonListener (this);
    decoupled2Button->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    decoupled2Button->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    decoupled2Button->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (sDecoupled2 = new ProSliderH (T("Decoupled2")));
    sDecoupled2->setTooltip (T("Decouple Osc 2"));
    sDecoupled2->setRange (-1, 127, 1);
    sDecoupled2->setSliderStyle (Slider::LinearHorizontal);
    sDecoupled2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDecoupled2->setColour (Slider::thumbColourId, Colours::black);
    sDecoupled2->setColour (Slider::trackColourId, Colour (0x5b4a3333));
    sDecoupled2->setColour (Slider::textBoxTextColourId, Colour (0xf6000000));
    sDecoupled2->addListener (this);

    addAndMakeVisible (sDecoupled1 = new ProSliderH (T("Decoupled1")));
    sDecoupled1->setTooltip (T("Decouple Osc 1"));
    sDecoupled1->setRange (-1, 127, 1);
    sDecoupled1->setSliderStyle (Slider::LinearHorizontal);
    sDecoupled1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDecoupled1->setColour (Slider::thumbColourId, Colours::black);
    sDecoupled1->setColour (Slider::trackColourId, Colour (0x5b4a3333));
    sDecoupled1->setColour (Slider::textBoxTextColourId, Colour (0xf4000000));
    sDecoupled1->addListener (this);

    addAndMakeVisible (sGlide = new ProKnob (T("Glide")));
    sGlide->setTooltip (T("Glide"));
    sGlide->setRange (0, 99, 0);
    sGlide->setSliderStyle (Slider::RotaryVerticalDrag);
    sGlide->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sGlide->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sGlide->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sGlide->addListener (this);

    addAndMakeVisible (sRetrig = new TextButton (T("Retrigger")));
    sRetrig->setTooltip (T("Mono Retrigger"));
    sRetrig->setButtonText (T("R"));
    sRetrig->addButtonListener (this);
    sRetrig->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sRetrig->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (page2 = new BlankPage());
    page2->setName (T("Page 2"));

    addAndMakeVisible (sLFO1Rate = new ProKnob (T("LFO 1 Rate")));
    sLFO1Rate->setTooltip (T("LFO 1 Rate"));
    sLFO1Rate->setRange (0, 1, 0);
    sLFO1Rate->setSliderStyle (Slider::RotaryVerticalDrag);
    sLFO1Rate->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sLFO1Rate->setColour (Slider::backgroundColourId, Colour (0x0));
    sLFO1Rate->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sLFO1Rate->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sLFO1Rate->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sLFO1Rate->addListener (this);

    addAndMakeVisible (sLFO1Amount = new ProKnob (T("LFO 1 Amount")));
    sLFO1Amount->setTooltip (T("LFO 1 Amount"));
    sLFO1Amount->setRange (0, 99, 0);
    sLFO1Amount->setSliderStyle (Slider::RotaryVerticalDrag);
    sLFO1Amount->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sLFO1Amount->setColour (Slider::backgroundColourId, Colour (0x0));
    sLFO1Amount->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sLFO1Amount->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sLFO1Amount->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sLFO1Amount->addListener (this);

    addAndMakeVisible (sEnv3Amount = new ProKnob (T("Env 3 Amount")));
    sEnv3Amount->setTooltip (T("Env 3 Amount"));
    sEnv3Amount->setRange (0, 99, 0);
    sEnv3Amount->setSliderStyle (Slider::RotaryVerticalDrag);
    sEnv3Amount->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sEnv3Amount->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sEnv3Amount->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sEnv3Amount->addListener (this);

    addAndMakeVisible (sRel3 = new ProSliderV (T("Env 3 Release")));
    sRel3->setTooltip (T("Env 3 Release"));
    sRel3->setRange (0, 100, 0);
    sRel3->setSliderStyle (Slider::LinearVertical);
    sRel3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRel3->addListener (this);

    addAndMakeVisible (sSus3 = new ProSliderV (T("Env 3 Systain")));
    sSus3->setTooltip (T("Env 3 Sustain"));
    sSus3->setRange (0, 100, 0);
    sSus3->setSliderStyle (Slider::LinearVertical);
    sSus3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sSus3->addListener (this);

    addAndMakeVisible (sDec3 = new ProSliderV (T("Env 3 Decay")));
    sDec3->setTooltip (T("Env 3 Decay"));
    sDec3->setRange (0, 100, 0);
    sDec3->setSliderStyle (Slider::LinearVertical);
    sDec3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sDec3->addListener (this);

    addAndMakeVisible (sAtt3 = new ProSliderV (T("Env 3 Attack")));
    sAtt3->setTooltip (T("Env 3 Attack"));
    sAtt3->setRange (0, 100, 0);
    sAtt3->setSliderStyle (Slider::LinearVertical);
    sAtt3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sAtt3->addListener (this);

    addAndMakeVisible (sPage = new TextButton (T("Page Switch")));
    sPage->setTooltip (T("Switch Page"));
    sPage->setButtonText (T("page"));
    sPage->addButtonListener (this);
    sPage->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sPage->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (Env3DestBox = new TextButton (T("Env 3 Destination")));
    Env3DestBox->setTooltip (T("Env 3 Destination"));
    Env3DestBox->setButtonText (T("dest"));
    Env3DestBox->addButtonListener (this);
    Env3DestBox->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    Env3DestBox->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (sLFO2Rate = new ProKnob (T("LFO 2 Rate")));
    sLFO2Rate->setTooltip (T("LFO 2 Rate"));
    sLFO2Rate->setRange (0, 1, 0);
    sLFO2Rate->setSliderStyle (Slider::RotaryVerticalDrag);
    sLFO2Rate->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sLFO2Rate->setColour (Slider::backgroundColourId, Colour (0x0));
    sLFO2Rate->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sLFO2Rate->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sLFO2Rate->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sLFO2Rate->addListener (this);

    addAndMakeVisible (sLFO2Amount = new ProKnob (T("LFO 2 Amount")));
    sLFO2Amount->setTooltip (T("LFO 2 Amount"));
    sLFO2Amount->setRange (0, 99, 0);
    sLFO2Amount->setSliderStyle (Slider::RotaryVerticalDrag);
    sLFO2Amount->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sLFO2Amount->setColour (Slider::backgroundColourId, Colour (0x0));
    sLFO2Amount->setColour (Slider::rotarySliderFillColourId, Colour (0xe3000000));
    sLFO2Amount->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    sLFO2Amount->setColour (Slider::textBoxOutlineColourId, Colour (0xb2888888));
    sLFO2Amount->addListener (this);

    addAndMakeVisible (LFO1WaveBox = new ComboBox (T("LFOWaveform1")));
    LFO1WaveBox->setTooltip (T("LFO 1 Waveform"));
    LFO1WaveBox->setEditableText (false);
    LFO1WaveBox->setJustificationType (Justification::centredLeft);
    LFO1WaveBox->setTextWhenNothingSelected (T("???????"));
    LFO1WaveBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    LFO1WaveBox->addItem (T("RampUp"), 1);
    LFO1WaveBox->addItem (T("RampDown"), 2);
    LFO1WaveBox->addItem (T("Square"), 3);
    LFO1WaveBox->addItem (T("Triangle"), 4);
    LFO1WaveBox->addItem (T("Sine"), 5);
    LFO1WaveBox->addItem (T("Minkowski"), 6);
    LFO1WaveBox->addItem (T("Weierstrass"), 7);
    LFO1WaveBox->addItem (T("AutoAlias"), 8);
    LFO1WaveBox->addItem (T("Eight"), 9);
    LFO1WaveBox->addItem (T("OddEight"), 10);
    LFO1WaveBox->addItem (T("Computer"), 11);
    LFO1WaveBox->addItem (T("Funnel"), 12);
    LFO1WaveBox->addItem (T("Grate"), 13);
    LFO1WaveBox->addItem (T("Noise"), 14);
    LFO1WaveBox->addItem (T("Sine+"), 15);
    LFO1WaveBox->addItem (T("Narrow"), 16);
    LFO1WaveBox->addItem (T("Octaves"), 17);
    LFO1WaveBox->addItem (T("Ughhh"), 18);
    LFO1WaveBox->addItem (T("Drawable1"), 19);
    LFO1WaveBox->addItem (T("Drawable2"), 20);
    LFO1WaveBox->addListener (this);

    addAndMakeVisible (LFO2WaveBox = new ComboBox (T("LFO2Waveform")));
    LFO2WaveBox->setTooltip (T("LFO 2 Waveform"));
    LFO2WaveBox->setEditableText (false);
    LFO2WaveBox->setJustificationType (Justification::centredLeft);
    LFO2WaveBox->setTextWhenNothingSelected (T("???????"));
    LFO2WaveBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    LFO2WaveBox->addItem (T("RampUp"), 1);
    LFO2WaveBox->addItem (T("RampDown"), 2);
    LFO2WaveBox->addItem (T("Square"), 3);
    LFO2WaveBox->addItem (T("Triangle"), 4);
    LFO2WaveBox->addItem (T("Sine"), 5);
    LFO2WaveBox->addItem (T("Minkowski"), 6);
    LFO2WaveBox->addItem (T("Weierstrass"), 7);
    LFO2WaveBox->addItem (T("AutoAlias"), 8);
    LFO2WaveBox->addItem (T("Eight"), 9);
    LFO2WaveBox->addItem (T("OddEight"), 10);
    LFO2WaveBox->addItem (T("Computer"), 11);
    LFO2WaveBox->addItem (T("Funnel"), 12);
    LFO2WaveBox->addItem (T("Grate"), 13);
    LFO2WaveBox->addItem (T("Noise"), 14);
    LFO2WaveBox->addItem (T("Sine+"), 15);
    LFO2WaveBox->addItem (T("Narrow"), 16);
    LFO2WaveBox->addItem (T("Octaves"), 17);
    LFO2WaveBox->addItem (T("Ughhh"), 18);
    LFO2WaveBox->addItem (T("Drawable1"), 19);
    LFO2WaveBox->addItem (T("Drawable2"), 20);
    LFO2WaveBox->addListener (this);

    addAndMakeVisible (menuButton = new TextButton (T("menu")));
    menuButton->setTooltip (T("Main Menu"));
    menuButton->setButtonText (T("m"));
    menuButton->addButtonListener (this);
    menuButton->setColour (TextButton::buttonColourId, Colour (0x30bbbbff));
    menuButton->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (lfo1indicator = new Indicator (T("lfo 1 indicator")));
    lfo1indicator->setRange (0, 2, 0);
    lfo1indicator->setSliderStyle (Slider::LinearVertical);
    lfo1indicator->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfo1indicator->setColour (Slider::trackColourId, Colour (0xffffff));
    lfo1indicator->setColour (Slider::textBoxTextColourId, Colour (0x0));
    lfo1indicator->addListener (this);

    addAndMakeVisible (bLFO1Free = new TextButton (T("LFO 1 Free Running")));
    bLFO1Free->setTooltip (T("LFO 1 Free Running"));
    bLFO1Free->setButtonText (T("free"));
    bLFO1Free->addButtonListener (this);
    bLFO1Free->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    bLFO1Free->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (bLFO2Free = new TextButton (T("LFO 2 Free Running")));
    bLFO2Free->setTooltip (T("LFO 2 free running"));
    bLFO2Free->setButtonText (T("free"));
    bLFO2Free->addButtonListener (this);
    bLFO2Free->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    bLFO2Free->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (LFO1DestBox = new TextButton (T("LFO 1 Destination")));
    LFO1DestBox->setTooltip (T("LFO 1 Destination"));
    LFO1DestBox->setButtonText (T("dest"));
    LFO1DestBox->addButtonListener (this);
    LFO1DestBox->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    LFO1DestBox->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (LFO2DestBox = new TextButton (T("LFO 2 Destination")));
    LFO2DestBox->setTooltip (T("LFO 2 Destination"));
    LFO2DestBox->setButtonText (T("dest"));
    LFO2DestBox->addButtonListener (this);
    LFO2DestBox->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    LFO2DestBox->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (lfo2indicator = new Indicator (T("lfo 2 indicator")));
    lfo2indicator->setRange (0, 2, 0);
    lfo2indicator->setSliderStyle (Slider::LinearVertical);
    lfo2indicator->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfo2indicator->setColour (Slider::trackColourId, Colour (0xffffff));
    lfo2indicator->setColour (Slider::textBoxTextColourId, Colour (0x0));
    lfo2indicator->addListener (this);

    addAndMakeVisible (aboutbox = new AboutBox());
    addAndMakeVisible (env3indicator = new Indicator (T("env 3 indicator")));
    env3indicator->setRange (0, 2, 0);
    env3indicator->setSliderStyle (Slider::LinearVertical);
    env3indicator->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    env3indicator->setColour (Slider::trackColourId, Colour (0xffffff));
    env3indicator->setColour (Slider::textBoxTextColourId, Colour (0x0));
    env3indicator->addListener (this);

    addAndMakeVisible (demoButton = new TextButton (T("demo")));
    demoButton->setTooltip (T("buy me!!!!!!!!!"));
    demoButton->setButtonText (T("DEMO VERSION"));
    demoButton->addButtonListener (this);
    demoButton->setColour (TextButton::buttonColourId, Colour (0x95bbbbff));

    addAndMakeVisible (bAuto = new TextButton (T("Auto Randomizer")));
    bAuto->setTooltip (T("Auto Randomizer"));
    bAuto->setButtonText (T("auto"));
    bAuto->addButtonListener (this);
    bAuto->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    bAuto->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (bDraw = new TextButton (T("Draw Waveform")));
    bDraw->setTooltip (T("Draw Waveform"));
    bDraw->setButtonText (T("draw1"));
    bDraw->addButtonListener (this);
    bDraw->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    bDraw->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (bDraw2 = new TextButton (T("Draw Waveform")));
    bDraw2->setTooltip (T("Draw Waveform"));
    bDraw2->setButtonText (T("draw2"));
    bDraw2->addButtonListener (this);
    bDraw2->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    bDraw2->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (waveDrawer = new WaveDrawWindow (this,ownerFilter));
    addAndMakeVisible (sync1 = new TextButton (T("LFO 1 Tempo Sync")));
    sync1->setTooltip (T("LFO 1 Tempo Sync"));
    sync1->setButtonText (T("sync"));
    sync1->addButtonListener (this);
    sync1->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sync1->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (sync2 = new TextButton (T("LFO 2 Tempo Sync")));
    sync2->setTooltip (T("LFO 2 Tempo Sync"));
    sync2->setButtonText (T("sync"));
    sync2->addButtonListener (this);
    sync2->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sync2->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (sExp3 = new TextButton (T("Envelope 3 Curve")));
    sExp3->setTooltip (T("Percussive Envelope"));
    sExp3->setButtonText (T("P"));
    sExp3->addButtonListener (this);
    sExp3->setColour (TextButton::buttonColourId, Colour (0xaf8f8f9e));
    sExp3->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));

    addAndMakeVisible (interpolate1 = new TextButton (T("Interpolate 1")));
    interpolate1->setTooltip (T("Interpolate Osc 1"));
    interpolate1->setButtonText (T("i"));
    interpolate1->addButtonListener (this);
    interpolate1->setColour (TextButton::buttonColourId, Colour (0x808f8f9e));
    interpolate1->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    interpolate1->setColour (TextButton::textColourId, Colours::black);

    addAndMakeVisible (interpolate2 = new TextButton (T("Interpolate 2")));
    interpolate2->setTooltip (T("Interpolate Osc 2"));
    interpolate2->setButtonText (T("i"));
    interpolate2->addButtonListener (this);
    interpolate2->setColour (TextButton::buttonColourId, Colour (0x808f8f9e));
    interpolate2->setColour (TextButton::buttonOnColourId, Colour (0xc9faff44));
    interpolate2->setColour (TextButton::textColourId, Colours::black);

    cachedImage_wood2_png = ImageCache::getFromMemory (wood2_png, wood2_pngSize);
    cachedImage_wood1_png = ImageCache::getFromMemory (wood1_png, wood1_pngSize);
    drawable17 = Drawable::createFromImageData (whitetitle_svg, whitetitle_svgSize);

    //[UserPreSize]
    resizer->setMouseClickGrabsKeyboardFocus(false);
    resizeLimits.setFixedAspectRatio (aspectRatio);
    resizeLimits.setSizeLimits (200, 150, 1024, 768);

#ifdef MRALIASPRO
	waveDrawer->setVisible(false);
    addAndMakeVisible (sRandomSpeed = new ProSliderH (T("RandomSpeed")));
    sRandomSpeed->setTooltip (T("Random Speed"));
    sRandomSpeed->setRange (0, 100, 0);
    sRandomSpeed->setSliderStyle (Slider::LinearHorizontal);
    sRandomSpeed->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRandomSpeed->setColour (Slider::thumbColourId, Colours::black);
    sRandomSpeed->setColour (Slider::trackColourId, Colour (0x5b4a3333));
    sRandomSpeed->setColour (Slider::textBoxTextColourId, Colour (0xf4000000));
    sRandomSpeed->addListener (this);
	sRandomSpeed->setSkewFactor(2.0);
	sRandomSpeed->addMouseListener(this,false);
	sRandomSpeed->setDoubleClickReturnValue(true,97);

    addAndMakeVisible (sRandomStrength = new ProSliderH (T("RandomStrength")));
    sRandomStrength->setTooltip (T("Random Strength"));
    sRandomStrength->setRange (0, 100, 1);
    sRandomStrength->setSliderStyle (Slider::LinearHorizontal);
    sRandomStrength->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sRandomStrength->setColour (Slider::thumbColourId, Colours::black);
    sRandomStrength->setColour (Slider::trackColourId, Colour (0x5b4a3333));
    sRandomStrength->setColour (Slider::textBoxTextColourId, Colour (0xf4000000));
    sRandomStrength->addListener (this);
	sRandomStrength->addMouseListener(this,false);
	sRandomStrength->setDoubleClickReturnValue(true,0);

	reloadSkin();

    keyboard->setMouseClickGrabsKeyboardFocus(false);
    keyboard->setKeyWidth(14);
    keyboard->setScrollButtonsVisible(false);
    //keyboard->setKeyPressBaseOctave(2);
    toggleButton->setMouseClickGrabsKeyboardFocus(false);
	sAtt3->addMouseListener(this,false);
	sAtt3->setDoubleClickReturnValue(true,1.0);
	sDec3->addMouseListener(this,false);
	sDec3->setDoubleClickReturnValue(true,1.0);
	sSus3->addMouseListener(this,false);
	sSus3->setDoubleClickReturnValue(true,100.0);
	sRel3->addMouseListener(this,false);
	sRel3->setDoubleClickReturnValue(true,1.0);
	sEnv3Amount->addMouseListener(this,false);
	sEnv3Amount->setDoubleClickReturnValue(true,50.0);
	sLFO1Rate->addMouseListener(this,false);
	sLFO1Rate->setDoubleClickReturnValue(true,lfoFreqToParam(1.f));
	sLFO1Amount->addMouseListener(this,false);
	sLFO1Amount->setDoubleClickReturnValue(true,50.0);
	sLFO2Rate->addMouseListener(this,false);
	sLFO2Rate->setDoubleClickReturnValue(true,lfoFreqToParam(1.f));
	sLFO2Amount->addMouseListener(this,false);
	sLFO2Amount->setDoubleClickReturnValue(true,50.0);
	sPage->setMouseClickGrabsKeyboardFocus(false);
	LFO1DestBox->setMouseClickGrabsKeyboardFocus(false);
	LFO2DestBox->setMouseClickGrabsKeyboardFocus(false);
	Env3DestBox->setMouseClickGrabsKeyboardFocus(false);
	bLFO1Free->setMouseClickGrabsKeyboardFocus(false);
	bLFO2Free->setMouseClickGrabsKeyboardFocus(false);
	menuButton->setMouseClickGrabsKeyboardFocus(false);
#endif

    sDecoupled1->setMouseClickGrabsKeyboardFocus(false);
    sDecoupled1->addMouseListener(this,false);
    sDecoupled1->setSliderSnapsToMousePosition(false);
    sDecoupled1->setDoubleClickReturnValue(true,-1);

    sDecoupled2->setMouseClickGrabsKeyboardFocus(false);
    sDecoupled2->addMouseListener(this,false);
    sDecoupled2->setSliderSnapsToMousePosition(false);
    sDecoupled2->setDoubleClickReturnValue(true,-1);

    decoupled1Button->setMouseClickGrabsKeyboardFocus(false);
    decoupled2Button->setMouseClickGrabsKeyboardFocus(false);

    sAlias->setMouseClickGrabsKeyboardFocus(false);
    sAlias->setSliderSnapsToMousePosition(false);
    sAlias->addMouseListener(this,false);
    sAlias->setDoubleClickReturnValue(true,0.0);
    sAlias->setMouseDragSensitivity(204);

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

    pizButton->setTooltip(String(T("Insert Piz Here-> Mr. Alias Pro ")) + String(T(JucePlugin_VersionString)));
    pizButton->addButtonListener(this);
    pizButton->setMouseClickGrabsKeyboardFocus(false);
    pizButton->addMouseListener(this,false);

    aboutbox->setVisible(false);
    aboutbox->addButtonListener(this);
    aboutbox->setMouseClickGrabsKeyboardFocus(false);

	bDraw->setMouseClickGrabsKeyboardFocus(false);
	bDraw2->setMouseClickGrabsKeyboardFocus(false);
	bAuto->setMouseClickGrabsKeyboardFocus(false);

    //parameter buttons
    sExp->setMouseClickGrabsKeyboardFocus(false);
    sExp->addMouseListener(this,false);
    sFExp->setMouseClickGrabsKeyboardFocus(false);
    sFExp->addMouseListener(this,false);
    sMode->setMouseClickGrabsKeyboardFocus(false);
    sMode->addMouseListener(this,false);
    limiterButton->setMouseClickGrabsKeyboardFocus(false);
    limiterButton->addMouseListener(this,false);
    sRetrig->setMouseClickGrabsKeyboardFocus(false);
    sRetrig->addMouseListener(this,false);
#ifdef MRALIASPRO
	interpolate1->setMouseClickGrabsKeyboardFocus(false);
    interpolate1->addMouseListener(this,false);
	interpolate2->setMouseClickGrabsKeyboardFocus(false);
    interpolate2->addMouseListener(this,false);
	//hidden controls
    sExp3->setMouseClickGrabsKeyboardFocus(false);
    sExp3->addMouseListener(this,false);
	sAtt3->setVisible(false);
	sDec3->setVisible(false);
	sSus3->setVisible(false);
	sRel3->setVisible(false);
	sEnv3Amount->setVisible(false);
	sLFO1Amount->setVisible(false);
	sLFO1Rate->setVisible(false);
	sLFO2Amount->setVisible(false);
	sLFO2Rate->setVisible(false);
	page2->setVisible(false);
	LFO1DestBox->setVisible(false);
	LFO2DestBox->setVisible(false);
	Env3DestBox->setVisible(false);
	LFO1WaveBox->setVisible(false);
	LFO2WaveBox->setVisible(false);
	bLFO1Free->setVisible(false);
	bLFO2Free->setVisible(false);
	sync1->setVisible(false);
	sync2->setVisible(false);
	sExp3->setVisible(false);

    startTimer (1000/24);
	if(ownerFilter->demo) {
		demoButton->setVisible(true);
	}
	else demoButton->setVisible(false);
	demoRight=demoDown=true;

#endif

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

    setSize (548, 320);

    //[Constructor] You can add your own custom stuff here..
    #endif
     static PizLookAndFeel Look;
     LookAndFeel::setDefaultLookAndFeel (&Look);
     setMouseClickGrabsKeyboardFocus(false);

     setSize ((int)(ownerFilter->lastUIHeight*aspectRatio),
             ownerFilter->lastUIHeight);

    ownerFilter->editorIsShowing=true;
    ownerFilter->addChangeListener (this);
    ownerFilter->leds->addChangeListener (this);

	for (int i=0;i<ownerFilter->waveNames.size();i++) {
		comboBox->addItem(ownerFilter->waveNames[i],numWaveforms+i+1);
		comboBox2->addItem(ownerFilter->waveNames[i],numWaveforms+i+1);
		LFO1WaveBox->addItem(ownerFilter->waveNames[i],numWaveforms+i+1);
		LFO2WaveBox->addItem(ownerFilter->waveNames[i],numWaveforms+i+1);
	}

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
	stopTimer();
    //[/Destructor_pre]

    deleteAndZero (sChannel);
    deleteAndZero (keyboard);
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
    deleteAndZero (sPitchShift);
    deleteAndZero (resizer);
    deleteAndZero (patchBox);
    deleteAndZero (sVolume);
    deleteAndZero (toggleButton);
    deleteAndZero (decoupled1Button);
    deleteAndZero (decoupled2Button);
    deleteAndZero (sDecoupled2);
    deleteAndZero (sDecoupled1);
    deleteAndZero (sGlide);
    deleteAndZero (sRetrig);
    deleteAndZero (page2);
    deleteAndZero (sLFO1Rate);
    deleteAndZero (sLFO1Amount);
    deleteAndZero (sEnv3Amount);
    deleteAndZero (sRel3);
    deleteAndZero (sSus3);
    deleteAndZero (sDec3);
    deleteAndZero (sAtt3);
    deleteAndZero (sPage);
    deleteAndZero (Env3DestBox);
    deleteAndZero (sLFO2Rate);
    deleteAndZero (sLFO2Amount);
    deleteAndZero (LFO1WaveBox);
    deleteAndZero (LFO2WaveBox);
    deleteAndZero (menuButton);
    deleteAndZero (lfo1indicator);
    deleteAndZero (bLFO1Free);
    deleteAndZero (bLFO2Free);
    deleteAndZero (LFO1DestBox);
    deleteAndZero (LFO2DestBox);
    deleteAndZero (lfo2indicator);
    deleteAndZero (aboutbox);
    deleteAndZero (env3indicator);
    deleteAndZero (demoButton);
    deleteAndZero (bAuto);
    deleteAndZero (bDraw);
    deleteAndZero (bDraw2);
    deleteAndZero (waveDrawer);
    deleteAndZero (sync1);
    deleteAndZero (sync2);
    deleteAndZero (sExp3);
    deleteAndZero (interpolate1);
    deleteAndZero (interpolate2);
    //ImageCache::release (cachedImage_wood2_png);
    //ImageCache::release (cachedImage_wood1_png);
    deleteAndZero (drawable17);

    //[Destructor]. You can add your own custom destruction code here..
    for (int i=0;i<numParams;i++) deleteAndZero (ccmapbox[i]);
	deleteAndZero(sRandomSpeed);
	deleteAndZero(sRandomStrength);
	if (bg) deleteAndZero(bg);
	//ImageCache::release(wood1);
	//ImageCache::release(wood2);
	//ImageCache::release(smallKnob);
	//ImageCache::release(largeKnob);
	//ImageCache::release(hSliderThumb);
	//ImageCache::release(vSliderThumb);
	if (hSliderBG) deleteAndZero(hSliderBG);
	if (vSliderBG) deleteAndZero(vSliderBG);
	logDebugString("GUI destroyed");
    //[/Destructor]
}

//==============================================================================
void MrAlias2Editor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	if (bg==0) {
    //[/UserPrePaint]

    g.fillAll (Colour (0xff434343));

    GradientBrush gradient_1 (Colours::black,
                              (float) (proportionOfWidth (0.5000f)), 0.0f,
                              Colour (0xff2c2a31),
                              (float) (proportionOfWidth (0.5000f)), 100.0f,
                              false);
    g.setBrush (&gradient_1);
    g.fillRect (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));

    GradientBrush gradient_2 (Colour (0xff424242),
                              (float) (proportionOfWidth (0.0000f)), (float) (proportionOfHeight (0.0000f)),
                              Colour (0xff4e3f3f),
                              (float) (proportionOfWidth (0.0000f)), (float) (proportionOfHeight (0.4400f)),
                              false);
    g.setBrush (&gradient_2);
    g.fillRect (proportionOfWidth (0.6715f), proportionOfHeight (0.2529f), proportionOfWidth (0.2847f), proportionOfHeight (0.4676f));

    GradientBrush gradient_3 (Colours::white,
                              (float) (proportionOfWidth (0.0000f)), (float) (proportionOfHeight (0.0000f)),
                              Colours::black,
                              (float) (proportionOfWidth (1.0000f)), (float) (proportionOfHeight (1.0000f)),
                              false);
    g.setBrush (&gradient_3);
    g.drawRect (proportionOfWidth (0.6715f), proportionOfHeight (0.2529f), proportionOfWidth (0.2847f), proportionOfHeight (0.4676f), 1);

    g.setColour (Colours::black);
    g.drawImage (cachedImage_wood2_png,
                 proportionOfWidth (0.9636f), 0, proportionOfWidth (0.0350f), proportionOfHeight (1.0000f),
                 0, 0, cachedImage_wood2_png->getWidth(), cachedImage_wood2_png->getHeight());

    GradientBrush gradient_5 (Colour (0xff4c4c4c),
                              0.0f, (float) (proportionOfHeight (-0.2000f)),
                              Colour (0xff4e3f3f),
                              0.0f, (float) (proportionOfHeight (0.3000f)),
                              false);
    g.setBrush (&gradient_5);
    g.fillPath (internalPath4);
    GradientBrush gradient_6 (Colour (0x8fffffff),
                              0.0f, 0.0f,
                              Colours::black,
                              (float) (proportionOfWidth (1.0000f)), (float) (proportionOfHeight (1.0000f)),
                              false);
    g.setBrush (&gradient_6);
    g.strokePath (internalPath4, PathStrokeType (0.9000f));

    GradientBrush gradient_7 (Colour (0xff4d4d4d),
                              0.0f, (float) (proportionOfHeight (-0.1000f)),
                              Colour (0xff4e3f3f),
                              (float) (proportionOfWidth (0.0000f)), (float) (proportionOfHeight (0.4000f)),
                              false);
    g.setBrush (&gradient_7);
    g.fillRect (proportionOfWidth (0.0420f), proportionOfHeight (0.1588f), proportionOfWidth (0.2847f), proportionOfHeight (0.2941f));

    GradientBrush gradient_8 (Colour (0x75ffffff),
                              0.0f, 0.0f,
                              Colours::black,
                              (float) (proportionOfWidth (1.0000f)), (float) (proportionOfHeight (1.0000f)),
                              false);
    g.setBrush (&gradient_8);
    g.drawRect (proportionOfWidth (0.0420f), proportionOfHeight (0.1588f), proportionOfWidth (0.2847f), proportionOfHeight (0.2941f), 1);

    GradientBrush gradient_10 (Colour (0xff737373),
                               0.0f, (float) (proportionOfHeight (0.1000f)),
                               Colour (0xff4e3f3f),
                               0.0f, (float) (proportionOfHeight (0.7000f)),
                               false);
    g.setBrush (&gradient_10);
    g.fillPath (internalPath9);
    GradientBrush gradient_11 (Colours::white,
                               0.0f, 0.0f,
                               Colours::black,
                               (float) (proportionOfWidth (1.0000f)), (float) (proportionOfHeight (1.0000f)),
                               false);
    g.setBrush (&gradient_11);
    g.strokePath (internalPath9, PathStrokeType (1.0000f));

    GradientBrush gradient_12 (Colour (0xff434343),
                               0.0f, (float) (proportionOfHeight (0.1000f)),
                               Colour (0xff4e3f3f),
                               0.0f, (float) (proportionOfHeight (0.5000f)),
                               false);
    g.setBrush (&gradient_12);
    g.fillRect (proportionOfWidth (0.3449f), proportionOfHeight (0.3794f), proportionOfWidth (0.3084f), proportionOfHeight (0.2176f));

    GradientBrush gradient_13 (Colour (0xc2ffffff),
                               0.0f, 0.0f,
                               Colours::black,
                               (float) (proportionOfWidth (1.0000f)), (float) (proportionOfHeight (1.0000f)),
                               false);
    g.setBrush (&gradient_13);
    g.drawRect (proportionOfWidth (0.3449f), proportionOfHeight (0.3794f), proportionOfWidth (0.3084f), proportionOfHeight (0.2176f), 1);

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.3540f), proportionOfHeight (0.7677f), proportionOfWidth (0.2920f), proportionOfHeight (0.1294f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.3540f), proportionOfHeight (0.1706f), proportionOfWidth (0.1679f), proportionOfHeight (0.0500f));

    g.setColour (Colour (0x50ffffff));
    g.fillPath (internalPath14);

    GradientBrush gradient_15 (Colours::darkgrey,
                               0.0f, (float) (proportionOfHeight (0.2400f)),
                               Colour (0xff4e3f3f),
                               0.0f, (float) (proportionOfHeight (0.6800f)),
                               false);
    g.setBrush (&gradient_15);
    g.fillRect (proportionOfWidth (0.0420f), proportionOfHeight (0.4765f), proportionOfWidth (0.2847f), proportionOfHeight (0.2441f));

    GradientBrush gradient_16 (Colour (0x84ffffff),
                               0.0f, 0.0f,
                               Colours::black,
                               (float) (proportionOfWidth (1.0000f)), (float) (proportionOfHeight (1.0000f)),
                               false);
    g.setBrush (&gradient_16);
    g.drawRect (proportionOfWidth (0.0420f), proportionOfHeight (0.4765f), proportionOfWidth (0.2847f), proportionOfHeight (0.2441f), 1);

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.6825f), proportionOfHeight (0.4794f), proportionOfWidth (0.2628f), proportionOfHeight (0.2235f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.5313f), proportionOfHeight (0.1312f), proportionOfWidth (0.4199f), proportionOfHeight (0.0906f));

    g.setColour (Colour (0x36000000));
    g.fillRect (proportionOfWidth (0.6533f), proportionOfHeight (0.1375f), proportionOfWidth (0.2190f), proportionOfHeight (0.0406f));

    g.setColour (Colours::black);
    g.drawImage (cachedImage_wood1_png,
                 0, 0, proportionOfWidth (0.0350f), proportionOfHeight (1.0000f),
                 0, 0, cachedImage_wood1_png->getWidth(), cachedImage_wood1_png->getHeight());

    g.setColour (Colours::black.withAlpha (0.3770f));
    jassert (drawable17 != 0);
    if (drawable17 != 0)
        drawable17->drawWithin (g, Rectangle<float>(proportionOfWidth (0.0712f), proportionOfHeight (0.0323f), proportionOfWidth (0.6825f), proportionOfHeight (0.0765f)),
                                RectanglePlacement::centred, 0);

    //[UserPaint] Add your own custom painting code here..
	}
	else {
		bg->drawWithin (g, Rectangle<float>(0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f)),
			RectanglePlacement::stretchToFit, 0);
		if (wood1!=0) {
			g.drawImage (wood1,
						 0, 0, proportionOfWidth (0.0350f), proportionOfHeight (1.0000f),
						 0, 0, wood1->getWidth(), wood1->getHeight());
		}
		if (wood2!=0) {
			g.drawImage (wood2,
						 proportionOfWidth (0.9636f), 0, proportionOfWidth (0.0350f), proportionOfHeight (1.0000f),
						 0, 0, wood2->getWidth(), wood2->getHeight());
		}
	}
    //[/UserPaint]
}

void MrAlias2Editor::resized()
{
    sChannel->setBounds (proportionOfWidth (0.4580f), proportionOfHeight (0.1063f), proportionOfWidth (0.0566f), proportionOfHeight (0.0781f));
    keyboard->setBounds (proportionOfWidth (0.0383f), proportionOfHeight (0.9312f), proportionOfWidth (0.9252f), proportionOfHeight (0.0688f));
    sAlias->setBounds (proportionOfWidth (0.0456f), proportionOfHeight (0.3750f), proportionOfWidth (0.2208f), proportionOfHeight (0.0531f));
    sCutoff->setBounds (proportionOfWidth (0.0529f), proportionOfHeight (0.5063f), proportionOfWidth (0.1077f), proportionOfHeight (0.1844f));
    sDivide->setBounds (proportionOfWidth (0.3558f), proportionOfHeight (0.3844f), proportionOfWidth (0.2317f), proportionOfHeight (0.0531f));
    sAtt->setBounds (proportionOfWidth (0.6807f), proportionOfHeight (0.2562f), proportionOfWidth (0.0456f), proportionOfHeight (0.2125f));
    sRate->setBounds (proportionOfWidth (0.0511f), proportionOfHeight (0.7656f), proportionOfWidth (0.2172f), proportionOfHeight (0.0531f));
    sSineMix->setBounds (proportionOfWidth (0.5766f), proportionOfHeight (0.6375f), proportionOfWidth (0.0620f), proportionOfHeight (0.1063f));
    sSineRes->setBounds (proportionOfWidth (0.3558f), proportionOfHeight (0.6219f), proportionOfWidth (0.2153f), proportionOfHeight (0.0531f));
    sPostDivide->setBounds ((proportionOfWidth (0.3558f)) + roundFloatToInt ((proportionOfWidth (0.2317f)) * 0.0000f), ((proportionOfHeight (0.3844f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f), roundFloatToInt ((proportionOfWidth (0.2317f)) * 1.0000f), proportionOfHeight (0.0531f));
    sClip->setBounds (proportionOfWidth (0.6679f), proportionOfHeight (0.7625f), proportionOfWidth (0.1697f), proportionOfHeight (0.0531f));
    sAInertia->setBounds (proportionOfWidth (0.2646f), proportionOfHeight (0.3594f), proportionOfWidth (0.0547f), proportionOfHeight (0.0875f));
    sDec->setBounds (proportionOfWidth (0.7318f), (proportionOfHeight (0.2562f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f));
    sSus->setBounds (proportionOfWidth (0.7847f), ((proportionOfHeight (0.2562f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f));
    sRel->setBounds (proportionOfWidth (0.8394f), (((proportionOfHeight (0.2562f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    sDivEnv->setBounds (proportionOfWidth (0.8905f), proportionOfHeight (0.3094f), proportionOfWidth (0.0566f), proportionOfHeight (0.0938f));
    sRes->setBounds (proportionOfWidth (0.2044f), (proportionOfHeight (0.5063f)) + roundFloatToInt ((proportionOfHeight (0.1844f)) * 0.0000f), proportionOfWidth (0.1077f), proportionOfHeight (0.1844f));
    sBRMix->setBounds ((proportionOfWidth (0.0511f)) + roundFloatToInt ((proportionOfWidth (0.2172f)) * 1.0420f), (proportionOfHeight (0.7656f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * -0.5294f), proportionOfWidth (0.0493f), proportionOfHeight (0.1031f));
    sSineFreq->setBounds ((proportionOfWidth (0.3558f)) + roundFloatToInt ((proportionOfWidth (0.2153f)) * 0.0000f), (proportionOfHeight (0.6219f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f), roundFloatToInt ((proportionOfWidth (0.2153f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.0000f));
    sVelSens->setBounds (proportionOfWidth (0.8905f), proportionOfHeight (0.3875f), proportionOfWidth (0.0566f), proportionOfHeight (0.0938f));
    sFiltEnv->setBounds (proportionOfWidth (0.8905f), proportionOfHeight (0.5437f), proportionOfWidth (0.0566f), proportionOfHeight (0.0938f));
    sFVSens->setBounds (proportionOfWidth (0.8905f), proportionOfHeight (0.6250f), proportionOfWidth (0.0566f), proportionOfHeight (0.0938f));
    sPBRange->setBounds (proportionOfWidth (0.3412f), proportionOfHeight (0.1594f), proportionOfWidth (0.0566f), proportionOfHeight (0.0781f));
    sInputGain->setBounds (proportionOfWidth (0.3613f), proportionOfHeight (0.7688f), proportionOfWidth (0.0821f), proportionOfHeight (0.1125f));
    sWet->setBounds (proportionOfWidth (0.4599f), proportionOfHeight (0.7688f), proportionOfWidth (0.0821f), proportionOfHeight (0.1125f));
    sOscGain->setBounds (proportionOfWidth (0.5566f), proportionOfHeight (0.7688f), proportionOfWidth (0.0821f), proportionOfHeight (0.1125f));
    sThresh->setBounds ((proportionOfWidth (0.3558f)) + roundFloatToInt ((proportionOfWidth (0.2317f)) * 0.0000f), (proportionOfHeight (0.3844f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.2353f), roundFloatToInt ((proportionOfWidth (0.2317f)) * 1.0000f), proportionOfHeight (0.0531f));
    sFreq1->setBounds (proportionOfWidth (0.0402f), proportionOfHeight (0.2531f), proportionOfWidth (0.0566f), proportionOfHeight (0.1031f));
    sRingMod->setBounds (proportionOfWidth (0.1551f), proportionOfHeight (0.6156f), proportionOfWidth (0.0566f), proportionOfHeight (0.0969f));
    sFAtt->setBounds (proportionOfWidth (0.6807f), proportionOfHeight (0.4875f), proportionOfWidth (0.0456f), roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f));
    sFDec->setBounds (proportionOfWidth (0.7318f), (proportionOfHeight (0.4875f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f));
    sFSus->setBounds (proportionOfWidth (0.7847f), ((proportionOfHeight (0.4875f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    sFRel->setBounds (proportionOfWidth (0.8394f), (((proportionOfHeight (0.4875f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    audioled->setBounds (proportionOfWidth (0.3759f), proportionOfHeight (0.2844f), proportionOfWidth (0.0219f), proportionOfHeight (0.0281f));
    sStereo->setBounds (proportionOfWidth (0.0967f), (proportionOfHeight (0.2531f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), proportionOfWidth (0.0566f), proportionOfHeight (0.1031f));
    sOscMix->setBounds (proportionOfWidth (0.1569f), (proportionOfHeight (0.2531f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), proportionOfWidth (0.0566f), proportionOfHeight (0.1031f));
    clipled->setBounds (proportionOfWidth (0.8869f), proportionOfHeight (0.8656f), proportionOfWidth (0.0219f), proportionOfHeight (0.0281f));
    sMode->setBounds (proportionOfWidth (0.3869f), proportionOfHeight (0.1750f), proportionOfWidth (0.0639f), proportionOfHeight (0.0469f));
    sStereo2->setBounds (proportionOfWidth (0.6679f), (proportionOfHeight (0.7625f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.4118f), proportionOfWidth (0.1697f), proportionOfHeight (0.0531f));
    sM1->setBounds ((proportionOfWidth (0.0511f)) + roundFloatToInt ((proportionOfWidth (0.2172f)) * 0.0000f), (proportionOfHeight (0.7656f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.3529f), roundFloatToInt ((proportionOfWidth (0.2172f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.0000f));
    sPhMod->setBounds (proportionOfWidth (0.2701f), ((proportionOfHeight (0.2531f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0566f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.1031f)) * 1.0000f));
    sDivMix->setBounds (proportionOfWidth (0.5876f), proportionOfHeight (0.3781f), proportionOfWidth (0.0566f), proportionOfHeight (0.1031f));
    info->setBounds (proportionOfWidth (0.0438f), proportionOfHeight (0.1063f), proportionOfWidth (0.2226f), proportionOfHeight (0.0313f));
    pizButton->setBounds (proportionOfWidth (0.4142f), proportionOfHeight (0.2375f), proportionOfWidth (0.1679f), proportionOfHeight (0.1344f));
    sFKeyFollow->setBounds (proportionOfWidth (0.2792f), proportionOfHeight (0.6563f), proportionOfWidth (0.0566f), proportionOfHeight (0.0688f));
    nextButton->setBounds (proportionOfWidth (0.5766f), proportionOfHeight (0.1344f), proportionOfWidth (0.0310f), proportionOfHeight (0.0406f));
    prevButton->setBounds (proportionOfWidth (0.5365f), proportionOfHeight (0.1344f), proportionOfWidth (0.0310f), proportionOfHeight (0.0406f));
    sReset->setBounds (proportionOfWidth (0.8832f), proportionOfHeight (0.1813f), proportionOfWidth (0.0675f), proportionOfHeight (0.0406f));
    sOPLP->setBounds (proportionOfWidth (0.0310f), proportionOfHeight (0.6563f), proportionOfWidth (0.0566f), proportionOfHeight (0.0688f));
    sPostDivMix->setBounds (proportionOfWidth (0.5876f), proportionOfHeight (0.4844f), proportionOfWidth (0.0566f), proportionOfHeight (0.1031f));
    sSavePatch->setBounds (proportionOfWidth (0.5365f), proportionOfHeight (0.1813f), proportionOfWidth (0.0967f), proportionOfHeight (0.0406f));
    sSavePatch2->setBounds (proportionOfWidth (0.6423f), proportionOfHeight (0.1813f), proportionOfWidth (0.0967f), proportionOfHeight (0.0406f));
    info3->setBounds (proportionOfWidth (0.6113f), proportionOfHeight (0.1375f), proportionOfWidth (0.0511f), proportionOfHeight (0.0406f));
    info2->setBounds (proportionOfWidth (0.6515f), proportionOfHeight (0.1375f), proportionOfWidth (0.2025f), proportionOfHeight (0.0406f));
    loadButton->setBounds (proportionOfWidth (0.8832f), proportionOfHeight (0.1344f), proportionOfWidth (0.0675f), proportionOfHeight (0.0406f));
    filterModeBox->setBounds (proportionOfWidth (0.1405f), proportionOfHeight (0.4875f), proportionOfWidth (0.0858f), roundFloatToInt ((proportionOfHeight (0.0375f)) * 1.0000f));
    sOctave1->setBounds (proportionOfWidth (0.0329f), proportionOfHeight (0.1750f), proportionOfWidth (0.0566f), proportionOfHeight (0.0688f));
    comboBox->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.1875f), proportionOfWidth (0.0985f), proportionOfHeight (0.0375f));
    sOctave2->setBounds (proportionOfWidth (0.2792f), proportionOfHeight (0.1750f), proportionOfWidth (0.0566f), proportionOfHeight (0.0688f));
    comboBox2->setBounds (proportionOfWidth (0.1880f), (proportionOfHeight (0.1875f)) + roundFloatToInt ((proportionOfHeight (0.0375f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0985f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.0375f)) * 1.0000f));
    sOctave->setBounds (proportionOfWidth (0.2135f), (proportionOfHeight (0.2531f)) + roundFloatToInt ((proportionOfHeight (0.1031f)) * 0.0000f), proportionOfWidth (0.0566f), proportionOfHeight (0.1031f));
    sUseProgCh->setBounds (proportionOfWidth (0.3686f), proportionOfHeight (0.1250f), proportionOfWidth (0.0949f), proportionOfHeight (0.0406f));
    sM1Mix->setBounds ((proportionOfWidth (0.0511f)) + roundFloatToInt ((proportionOfWidth (0.2172f)) * 1.0420f), ((proportionOfHeight (0.7656f)) + roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.3529f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.0531f)) * 1.0000f)) * -0.4706f), proportionOfWidth (0.0493f), proportionOfHeight (0.1031f));
    randomButton->setBounds (proportionOfWidth (0.7518f), proportionOfHeight (0.1813f), proportionOfWidth (0.1223f), proportionOfHeight (0.0406f));
    limiterButton->setBounds (proportionOfWidth (0.8595f), proportionOfHeight (0.7312f), proportionOfWidth (0.0766f), proportionOfHeight (0.0375f));
    sExp->setBounds (proportionOfWidth (0.8996f), proportionOfHeight (0.2656f), proportionOfWidth (0.0383f), proportionOfHeight (0.0469f));
    sFExp->setBounds (proportionOfWidth (0.8996f), proportionOfHeight (0.4969f), proportionOfWidth (0.0383f), proportionOfHeight (0.0469f));
    midiled->setBounds (proportionOfWidth (0.6040f), proportionOfHeight (0.2844f), proportionOfWidth (0.0219f), proportionOfHeight (0.0281f));
    saveSnapshotButtonB->setBounds (proportionOfWidth (0.9343f), proportionOfHeight (0.0000f), proportionOfWidth (0.0310f), proportionOfHeight (0.0406f));
    recallSnapshotButtonB->setBounds (proportionOfWidth (0.9343f), proportionOfHeight (0.0469f), proportionOfWidth (0.0310f), proportionOfHeight (0.0406f));
    sMorph->setBounds (proportionOfWidth (0.0675f), proportionOfHeight (-0.0188f), proportionOfWidth (0.8650f), proportionOfHeight (0.0531f));
    saveSnapshotButtonA->setBounds (proportionOfWidth (0.0365f), proportionOfHeight (0.0000f), proportionOfWidth (0.0310f), proportionOfHeight (0.0406f));
    recallSnapshotButtonA->setBounds (proportionOfWidth (0.0365f), proportionOfHeight (0.0469f), proportionOfWidth (0.0310f), proportionOfHeight (0.0406f));
    sPitchShift->setBounds (proportionOfWidth (0.3558f), proportionOfHeight (1.0187f), proportionOfWidth (0.0839f), proportionOfHeight (0.0406f));
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    patchBox->setBounds (proportionOfWidth (0.8540f), proportionOfHeight (0.1375f), proportionOfWidth (0.0219f), proportionOfHeight (0.0375f));
    sVolume->setBounds (proportionOfWidth (0.8467f), proportionOfHeight (0.7594f), proportionOfWidth (0.1022f), proportionOfHeight (0.1469f));
    toggleButton->setBounds (proportionOfWidth (0.0055f), proportionOfHeight (0.9469f), proportionOfWidth (0.0256f), proportionOfHeight (0.0375f));
    decoupled1Button->setBounds (proportionOfWidth (0.0420f), proportionOfHeight (0.1594f), proportionOfWidth (0.0402f), proportionOfHeight (0.0250f));
    decoupled2Button->setBounds (proportionOfWidth (0.2865f), proportionOfHeight (0.1594f), proportionOfWidth (0.0402f), proportionOfHeight (0.0250f));
    sDecoupled2->setBounds (proportionOfWidth (0.1843f), proportionOfHeight (-0.0969f), proportionOfWidth (0.2208f), proportionOfHeight (0.0531f));
    sDecoupled1->setBounds (proportionOfWidth (-0.0529f), proportionOfHeight (-0.1063f), proportionOfWidth (0.2208f), proportionOfHeight (0.0531f));
    sGlide->setBounds (proportionOfWidth (0.4818f), proportionOfHeight (0.1656f), proportionOfWidth (0.0474f), proportionOfHeight (0.0625f));
    sRetrig->setBounds (proportionOfWidth (0.4525f), proportionOfHeight (0.1750f), proportionOfWidth (0.0310f), proportionOfHeight (0.0469f));
    page2->setBounds (proportionOfWidth (0.6715f), proportionOfHeight (0.2531f), proportionOfWidth (0.2847f), proportionOfHeight (0.4750f));
    sLFO1Rate->setBounds (proportionOfWidth (0.6953f), proportionOfHeight (0.4906f), proportionOfWidth (0.0821f), proportionOfHeight (0.1125f));
    sLFO1Amount->setBounds (proportionOfWidth (0.7847f), proportionOfHeight (0.4906f), proportionOfWidth (0.0657f), proportionOfHeight (0.1125f));
    sEnv3Amount->setBounds (proportionOfWidth (0.8905f), proportionOfHeight (0.3094f), proportionOfWidth (0.0566f), proportionOfHeight (0.0938f));
    sRel3->setBounds (proportionOfWidth (0.8394f), (((proportionOfHeight (0.2562f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f)) * 1.0000f));
    sSus3->setBounds (proportionOfWidth (0.7847f), ((proportionOfHeight (0.2562f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f)) + roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 0.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f)) * 1.0000f), roundFloatToInt ((roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f)) * 1.0000f));
    sDec3->setBounds (proportionOfWidth (0.7318f), (proportionOfHeight (0.2562f)) + roundFloatToInt ((proportionOfHeight (0.2125f)) * 0.0000f), roundFloatToInt ((proportionOfWidth (0.0456f)) * 1.0000f), roundFloatToInt ((proportionOfHeight (0.2125f)) * 1.0000f));
    sAtt3->setBounds (proportionOfWidth (0.6807f), proportionOfHeight (0.2562f), proportionOfWidth (0.0456f), proportionOfHeight (0.2125f));
    sPage->setBounds (proportionOfWidth (0.6953f), proportionOfHeight (0.2313f), proportionOfWidth (0.0657f), proportionOfHeight (0.0344f));
    Env3DestBox->setBounds (proportionOfWidth (0.8887f), proportionOfHeight (0.4156f), proportionOfWidth (0.0657f), proportionOfHeight (0.0344f));
    sLFO2Rate->setBounds (proportionOfWidth (0.6953f), proportionOfHeight (0.6062f), proportionOfWidth (0.0821f), proportionOfHeight (0.1125f));
    sLFO2Amount->setBounds (proportionOfWidth (0.7847f), proportionOfHeight (0.6062f), proportionOfWidth (0.0657f), proportionOfHeight (0.1125f));
    LFO1WaveBox->setBounds (proportionOfWidth (0.8522f), proportionOfHeight (0.5031f), proportionOfWidth (0.0985f), proportionOfHeight (0.0375f));
    LFO2WaveBox->setBounds (proportionOfWidth (0.8522f), proportionOfHeight (0.6187f), proportionOfWidth (0.0985f), proportionOfHeight (0.0375f));
    menuButton->setBounds (proportionOfWidth (0.0055f), proportionOfHeight (0.0125f), proportionOfWidth (0.0256f), proportionOfHeight (0.0375f));
    lfo1indicator->setBounds (proportionOfWidth (0.6916f), proportionOfHeight (0.4938f), proportionOfWidth (0.0128f), proportionOfHeight (0.1094f));
    bLFO1Free->setBounds (proportionOfWidth (0.8522f), proportionOfHeight (0.5469f), proportionOfWidth (0.0493f), proportionOfHeight (0.0344f));
    bLFO2Free->setBounds (proportionOfWidth (0.8522f), proportionOfHeight (0.6625f), proportionOfWidth (0.0493f), proportionOfHeight (0.0344f));
    LFO1DestBox->setBounds (proportionOfWidth (0.9033f), proportionOfHeight (0.5469f), proportionOfWidth (0.0493f), proportionOfHeight (0.0344f));
    LFO2DestBox->setBounds (proportionOfWidth (0.9033f), proportionOfHeight (0.6625f), proportionOfWidth (0.0493f), proportionOfHeight (0.0344f));
    lfo2indicator->setBounds (proportionOfWidth (0.6916f), proportionOfHeight (0.6094f), proportionOfWidth (0.0128f), proportionOfHeight (0.1094f));
    aboutbox->setBounds (proportionOfWidth (0.4991f) - ((proportionOfWidth (0.4726f)) / 2), proportionOfHeight (0.1344f), proportionOfWidth (0.4726f), proportionOfHeight (0.4906f));
    env3indicator->setBounds (proportionOfWidth (0.8814f), proportionOfHeight (0.3000f), proportionOfWidth (0.0128f), proportionOfHeight (0.1094f));
    demoButton->setBounds (proportionOfWidth (0.3613f), proportionOfHeight (0.8875f), proportionOfWidth (0.2737f), proportionOfHeight (0.1000f));
    bAuto->setBounds (proportionOfWidth (0.8102f), proportionOfHeight (0.2188f), proportionOfWidth (0.0657f), proportionOfHeight (0.0344f));
    bDraw->setBounds (proportionOfWidth (0.2682f), proportionOfHeight (0.1000f), proportionOfWidth (0.0474f), proportionOfHeight (0.0344f));
    bDraw2->setBounds (proportionOfWidth (0.3175f), proportionOfHeight (0.1000f), proportionOfWidth (0.0474f), proportionOfHeight (0.0344f));
    waveDrawer->setBounds (proportionOfWidth (0.5000f) - ((proportionOfWidth (0.4672f)) / 2), proportionOfHeight (0.4031f) - ((proportionOfHeight (0.5375f)) / 2), proportionOfWidth (0.4672f), proportionOfHeight (0.5375f));
    sync1->setBounds (proportionOfWidth (0.8522f), proportionOfHeight (0.5781f), proportionOfWidth (0.0493f), proportionOfHeight (0.0344f));
    sync2->setBounds (proportionOfWidth (0.8522f), proportionOfHeight (0.6938f), proportionOfWidth (0.0493f), proportionOfHeight (0.0344f));
    sExp3->setBounds (proportionOfWidth (0.8996f), proportionOfHeight (0.2656f), proportionOfWidth (0.0383f), proportionOfHeight (0.0469f));
    interpolate1->setBounds (proportionOfWidth (0.1606f), proportionOfHeight (0.1594f), proportionOfWidth (0.0201f), proportionOfHeight (0.0281f));
    interpolate2->setBounds (proportionOfWidth (0.1861f), proportionOfHeight (0.1594f), proportionOfWidth (0.0201f), proportionOfHeight (0.0281f));
    internalPath4.clear();
    internalPath4.startNewSubPath ((float) (proportionOfWidth (0.3449f)), (float) (proportionOfHeight (0.2313f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.3449f)), (float) (proportionOfHeight (0.1375f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.0420f)), (float) (proportionOfHeight (0.1375f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.0420f)), (float) (proportionOfHeight (0.1016f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.9570f)), (float) (proportionOfHeight (0.1016f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.9570f)), (float) (proportionOfHeight (0.2300f)));
    internalPath4.closeSubPath();

    internalPath9.clear();
    internalPath9.startNewSubPath ((float) (proportionOfWidth (0.0430f)), (float) (proportionOfHeight (0.9100f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.0430f)), (float) (proportionOfHeight (0.7510f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.3457f)), (float) (proportionOfHeight (0.7510f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.3457f)), (float) (proportionOfHeight (0.6200f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.6525f)), (float) (proportionOfHeight (0.6200f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.6525f)), (float) (proportionOfHeight (0.7510f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.9562f)), (float) (proportionOfHeight (0.7510f)));
    internalPath9.lineTo ((float) (proportionOfWidth (0.9570f)), (float) (proportionOfHeight (0.9100f)));
    internalPath9.closeSubPath();

    internalPath14.clear();
    internalPath14.startNewSubPath ((float) (proportionOfWidth (0.8976f)), (float) (proportionOfHeight (0.0442f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.7988f)), (float) (proportionOfHeight (0.0442f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.7888f)), (float) (proportionOfHeight (0.0251f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.9164f)), (float) (proportionOfHeight (0.0151f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.9364f)), (float) (proportionOfHeight (0.0773f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.8175f)), (float) (proportionOfHeight (0.0773f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.8275f)), (float) (proportionOfHeight (0.0914f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.9264f)), (float) (proportionOfHeight (0.0914f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.9364f)), (float) (proportionOfHeight (0.1104f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.7988f)), (float) (proportionOfHeight (0.1204f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.7888f)), (float) (proportionOfHeight (0.0583f)));
    internalPath14.lineTo ((float) (proportionOfWidth (0.9076f)), (float) (proportionOfHeight (0.0583f)));
    internalPath14.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    logDebugString("resized()");

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

void MrAlias2Editor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sChannel)
    {
        //[UserSliderCode_sChannel] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kChannel,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sChannel]
    }
    else if (sliderThatWasMoved == sAlias)
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
    else if (sliderThatWasMoved == sVolume)
    {
        //[UserSliderCode_sVolume] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kVolume,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sVolume]
    }
    else if (sliderThatWasMoved == sDecoupled2)
    {
        //[UserSliderCode_sDecoupled2] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kDecoupled2,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDecoupled2]
    }
    else if (sliderThatWasMoved == sDecoupled1)
    {
        //[UserSliderCode_sDecoupled1] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kDecoupled1,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDecoupled1]
    }
    else if (sliderThatWasMoved == sGlide)
    {
        //[UserSliderCode_sGlide] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kGlide,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sGlide]
    }
    else if (sliderThatWasMoved == sLFO1Rate)
    {
        //[UserSliderCode_sLFO1Rate] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kLFO1Rate,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sLFO1Rate]
    }
    else if (sliderThatWasMoved == sLFO1Amount)
    {
        //[UserSliderCode_sLFO1Amount] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kLFO1Amount,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sLFO1Amount]
    }
    else if (sliderThatWasMoved == sEnv3Amount)
    {
        //[UserSliderCode_sEnv3Amount] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kEnv3Amount,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sEnv3Amount]
    }
    else if (sliderThatWasMoved == sRel3)
    {
        //[UserSliderCode_sRel3] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            getFilter()->setParameterNotifyingHost(kSus3,0.f);
            getFilter()->setParameterNotifyingHost(kAtt3,0.f);
            getFilter()->setParameterNotifyingHost(kRel3,mapToVSTRange(sliderThatWasMoved));
            sExp3->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kExp3,1.f);
        }
        getFilter()->setParameterNotifyingHost(kRel3,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sRel3]
    }
    else if (sliderThatWasMoved == sSus3)
    {
        //[UserSliderCode_sSus3] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kSus3,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sSus3]
    }
    else if (sliderThatWasMoved == sDec3)
    {
        //[UserSliderCode_sDec3] -- add your slider handling code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
            getFilter()->setParameterNotifyingHost(kSus3,0.f);
            getFilter()->setParameterNotifyingHost(kAtt3,0.f);
            getFilter()->setParameterNotifyingHost(kRel3,mapToVSTRange(sliderThatWasMoved));
            sExp3->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kExp3,1.f);
        }
        getFilter()->setParameterNotifyingHost(kDec3,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sDec3]
    }
    else if (sliderThatWasMoved == sAtt3)
    {
        //[UserSliderCode_sAtt3] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kAtt3,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sAtt3]
    }
    else if (sliderThatWasMoved == sLFO2Rate)
    {
        //[UserSliderCode_sLFO2Rate] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kLFO2Rate,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sLFO2Rate]
    }
    else if (sliderThatWasMoved == sLFO2Amount)
    {
        //[UserSliderCode_sLFO2Amount] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kLFO2Amount,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sLFO2Amount]
    }
    else if (sliderThatWasMoved == lfo1indicator)
    {
        //[UserSliderCode_lfo1indicator] -- add your slider handling code here..
        //[/UserSliderCode_lfo1indicator]
    }
    else if (sliderThatWasMoved == lfo2indicator)
    {
        //[UserSliderCode_lfo2indicator] -- add your slider handling code here..
        //[/UserSliderCode_lfo2indicator]
    }
    else if (sliderThatWasMoved == env3indicator)
    {
        //[UserSliderCode_env3indicator] -- add your slider handling code here..
        //[/UserSliderCode_env3indicator]
    }

    //[UsersliderValueChanged_Post]
    else if (sliderThatWasMoved == sRandomSpeed)
    {
        //[UserSliderCode_sOctave] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kRandomSpeed,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOctave]
    }
    else if (sliderThatWasMoved == sRandomStrength)
    {
        //[UserSliderCode_sOctave] -- add your slider handling code here..
        getFilter()->setParameterNotifyingHost(kRandomStrength,mapToVSTRange(sliderThatWasMoved));
        //[/UserSliderCode_sOctave]
    }
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
            sMode->setButtonText("micro");
        }
        else {
            sMode->setButtonText("Mono");
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
		if (ModifierKeys::getCurrentModifiers().isShiftDown())
		{
			getFilter()->initializeBank();
		}
		else {
	        getFilter()->progReset();
		}
        //[/UserButtonCode_sReset]
    }
    else if (buttonThatWasClicked == sSavePatch)
    {
        //[UserButtonCode_sSavePatch] -- add your button handler code here..
        FileChooser myChooser ("Save current patch...",
			File(getFilter()->patchPath + File::separatorString
					 + info2->getText() + ".MrAliasPatch"),
                 "*.MrAliasPatch;*.MrAliasCCMap");

        if (myChooser.browseForFileToSave(true))
        {
            bool saveccmap=false;
            File file (myChooser.getResult());
			getFilter()->patchPath = file.getParentDirectory().getFullPathName();
            if (file.hasFileExtension("MrAliasCCMap")) saveccmap=true;
            else if (!file.hasFileExtension("MrAliasPatch")) file = file.withFileExtension("MrAliasPatch");

            getFilter()->savePatch (file,saveccmap);
        }
        //[/UserButtonCode_sSavePatch]
    }
    else if (buttonThatWasClicked == sSavePatch2)
    {
        //[UserButtonCode_sSavePatch2] -- add your button handler code here..
        FileChooser myChooser ("Save current bank...",
            File(getFilter()->patchPath ),
                               "*.MrAliasBank");

        if (myChooser.browseForFileToSave(true))
        {
            File file (myChooser.getResult());
			getFilter()->patchPath = file.getParentDirectory().getFullPathName();
            if (!file.hasFileExtension("MrAliasBank")) file = file.withFileExtension("MrAliasBank");

            getFilter()->saveBank (file);
        }
        //[/UserButtonCode_sSavePatch2]
    }
    else if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        FileChooser myChooser ("Load bank/patch...",
                               File(getFilter()->patchPath),
                               "*.MrAliasBank;*.MrAliasPatch;*.fxb;*.fxp;*.MrAliasCCMap");

        if (myChooser.browseForFileToOpen())
        {
            File file (myChooser.getResult());
			getFilter()->patchPath = file.getParentDirectory().getFullPathName();
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
        const String alphabet = "abbccddeeffgghhijjkkllmmnnoppqqrrssttuvwxyz ";
        const String vowels = "aeiou";
        float strength = 0.005f;
        String newName;
        if (ModifierKeys::getCurrentModifiers().isCommandDown()) {
            getFilter()->randomize(strength);
            newName = getFilter()->getProgramName(getFilter()->getCurrentProgram());
            int i=JUCE_NAMESPACE::Random::getSystemRandom().nextInt(newName.length());
            tchar o=newName[i];
            tchar n=o;
            while (o==n) n=alphabet[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(alphabet.length())];
            newName[i] = n;
        }
		else if (ModifierKeys::getCurrentModifiers().isShiftDown()) {
			getFilter()->randomizeMods(ModifierKeys::getCurrentModifiers().isAltDown());
            newName = getFilter()->getProgramName(getFilter()->getCurrentProgram());
            int i=JUCE_NAMESPACE::Random::getSystemRandom().nextInt(newName.length());
            tchar o=newName[i];
            tchar n=o;
            while (o==n) n=alphabet[JUCE_NAMESPACE::Random::getSystemRandom().nextInt(alphabet.length())];
            newName[i] = n;
		}
        else {
            int x,y;
            randomButton->getMouseXYRelative(x,y);
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
    else if (buttonThatWasClicked == toggleButton)
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        keyboard->grabKeyboardFocus();
        //[/UserButtonCode_toggleButton]
    }
    else if (buttonThatWasClicked == decoupled1Button)
    {
        //[UserButtonCode_decoupled1Button] -- add your button handler code here..
        PopupMenu m;
        m.addCustomItem(-1,sDecoupled1,120,18,false);
        m.showAt(decoupled1Button);
        //[/UserButtonCode_decoupled1Button]
    }
    else if (buttonThatWasClicked == decoupled2Button)
    {
        //[UserButtonCode_decoupled2Button] -- add your button handler code here..
        PopupMenu m;
        m.addCustomItem(-1,sDecoupled2,120,18,false);
        m.showAt(decoupled2Button);
        //[/UserButtonCode_decoupled2Button]
    }
    else if (buttonThatWasClicked == sRetrig)
    {
        //[UserButtonCode_sRetrig] -- add your button handler code here..
        sRetrig->setToggleState(!sRetrig->getToggleState(),false);
        if (sRetrig->getToggleState()) getFilter()->setParameterNotifyingHost(kRetrig,1.f);
        else getFilter()->setParameterNotifyingHost(kRetrig,0.f);
        //[/UserButtonCode_sRetrig]
    }
    else if (buttonThatWasClicked == sPage)
    {
        //[UserButtonCode_sPage] -- add your button handler code here..
		sAtt3->setVisible(!sPage->getToggleState());
		sDec3->setVisible(!sPage->getToggleState());
		sSus3->setVisible(!sPage->getToggleState());
		sRel3->setVisible(!sPage->getToggleState());
		sEnv3Amount->setVisible(!sPage->getToggleState());
		sLFO1Amount->setVisible(!sPage->getToggleState());
		sLFO1Rate->setVisible(!sPage->getToggleState());
		sLFO2Amount->setVisible(!sPage->getToggleState());
		sLFO2Rate->setVisible(!sPage->getToggleState());
		page2->setVisible(!sPage->getToggleState());
		LFO1DestBox->setVisible(!sPage->getToggleState());
		LFO2DestBox->setVisible(!sPage->getToggleState());
		Env3DestBox->setVisible(!sPage->getToggleState());
		LFO1WaveBox->setVisible(!sPage->getToggleState());
		LFO2WaveBox->setVisible(!sPage->getToggleState());
		bLFO1Free->setVisible(!sPage->getToggleState());
		bLFO2Free->setVisible(!sPage->getToggleState());
		lfo1indicator->setVisible(!sPage->getToggleState());
		lfo2indicator->setVisible(!sPage->getToggleState());
		env3indicator->setVisible(!sPage->getToggleState());
		sync1->setVisible(!sPage->getToggleState());
		sync2->setVisible(!sPage->getToggleState());
		sExp3->setVisible(!sPage->getToggleState());

		sAtt->setVisible(sPage->getToggleState());
		sDec->setVisible(sPage->getToggleState());
		sSus->setVisible(sPage->getToggleState());
		sRel->setVisible(sPage->getToggleState());
		sFAtt->setVisible(sPage->getToggleState());
		sFDec->setVisible(sPage->getToggleState());
		sFSus->setVisible(sPage->getToggleState());
		sFRel->setVisible(sPage->getToggleState());
		sExp->setVisible(sPage->getToggleState());
		sFExp->setVisible(sPage->getToggleState());
		sFiltEnv->setVisible(sPage->getToggleState());
		sFVSens->setVisible(sPage->getToggleState());
		sVelSens->setVisible(sPage->getToggleState());
		sDivEnv->setVisible(sPage->getToggleState());

		sPage->setToggleState(!sPage->getToggleState(),false);
		getFilter()->currentPage = sPage->getToggleState() ? 1 : 0;
        //[/UserButtonCode_sPage]
    }
    else if (buttonThatWasClicked == Env3DestBox)
    {
        //[UserButtonCode_Env3DestBox] -- add your button handler code here..
		PopupMenu Env3DestMenu;
		for (int i=0;i<numParams-2;i++) {
			Env3DestMenu.addColouredItem(i+1,getFilter()->getParameterName(i),getFilter()->isModulatable(i) ? Colours::black : Colours::red, true, getFilter()->matchModMatrix(modEnv3,i));
		}
		int result = Env3DestMenu.show()-1;
		if (result != -1)
		{
			getFilter()->getCallbackLock().enter();
			getFilter()->setModMatrix(getFilter()->matchModMatrix(modEnv3,result) ? modNone : modEnv3,
												   result);
			Env3DestBox->setToggleState(false,false);
			LFO1DestBox->setToggleState(false,false);
			LFO2DestBox->setToggleState(false,false);
			for (int i=numParams-2; i--;) {
				if (getFilter()->matchModMatrix(modEnv3,i)) Env3DestBox->setToggleState(true,false);
				if (getFilter()->matchModMatrix(modLFO1,i)) LFO1DestBox->setToggleState(true,false);
				if (getFilter()->matchModMatrix(modLFO2,i)) LFO2DestBox->setToggleState(true,false);
			}
			getFilter()->getCallbackLock().exit();
		}
        //[/UserButtonCode_Env3DestBox]
    }
    else if (buttonThatWasClicked == menuButton)
    {
        //[UserButtonCode_menuButton] -- add your button handler code here..
		showMainMenu();
        //[/UserButtonCode_menuButton]
    }
    else if (buttonThatWasClicked == bLFO1Free)
    {
        //[UserButtonCode_bLFO1Free] -- add your button handler code here..
        bLFO1Free->setToggleState(!bLFO1Free->getToggleState(),false);
        if (bLFO1Free->getToggleState()) getFilter()->setParameterNotifyingHost(kLFO1Free,1.f);
        else getFilter()->setParameterNotifyingHost(kLFO1Free,0.f);
        //[/UserButtonCode_bLFO1Free]
    }
    else if (buttonThatWasClicked == bLFO2Free)
    {
        //[UserButtonCode_bLFO2Free] -- add your button handler code here..
        bLFO2Free->setToggleState(!bLFO2Free->getToggleState(),false);
        if (bLFO2Free->getToggleState()) getFilter()->setParameterNotifyingHost(kLFO2Free,1.f);
        else getFilter()->setParameterNotifyingHost(kLFO2Free,0.f);
        //[/UserButtonCode_bLFO2Free]
    }
    else if (buttonThatWasClicked == LFO1DestBox)
    {
        //[UserButtonCode_LFO1DestBox] -- add your button handler code here..
		PopupMenu LFO1DestMenu;
		for (int i=0;i<numParams-2;i++) {
			LFO1DestMenu.addColouredItem(i+1,getFilter()->getParameterName(i),getFilter()->isModulatable(i) ? Colours::black : Colours::red, true, getFilter()->matchModMatrix(modLFO1,i));
		}
		int result = LFO1DestMenu.show()-1;
		if (result > -1)
		{
			getFilter()->getCallbackLock().enter();
			getFilter()->setModMatrix(getFilter()->matchModMatrix(modLFO1,result) ? modNone : modLFO1,
												   result);
			Env3DestBox->setToggleState(false,false);
			LFO1DestBox->setToggleState(false,false);
			LFO2DestBox->setToggleState(false,false);
			for (int i=numParams-2; i--;) {
				if (getFilter()->matchModMatrix(modEnv3,i)) Env3DestBox->setToggleState(true,false);
				if (getFilter()->matchModMatrix(modLFO1,i)) LFO1DestBox->setToggleState(true,false);
				if (getFilter()->matchModMatrix(modLFO2,i)) LFO2DestBox->setToggleState(true,false);
			}
			getFilter()->getCallbackLock().exit();
		}
        //[/UserButtonCode_LFO1DestBox]
    }
    else if (buttonThatWasClicked == LFO2DestBox)
    {
        //[UserButtonCode_LFO2DestBox] -- add your button handler code here..
		PopupMenu LFO2DestMenu;
		for (int i=0;i<numParams-2;i++) {
			LFO2DestMenu.addColouredItem(i+1,getFilter()->getParameterName(i),getFilter()->isModulatable(i) ? Colours::black : Colours::red, true, getFilter()->matchModMatrix(modLFO2,i));
		}
		int result = LFO2DestMenu.show()-1;
		if (result > -1)
		{
			getFilter()->getCallbackLock().enter();
			getFilter()->setModMatrix(getFilter()->matchModMatrix(modLFO2,result) ? modNone : modLFO2,
												   result);
			Env3DestBox->setToggleState(false,false);
			LFO1DestBox->setToggleState(false,false);
			LFO2DestBox->setToggleState(false,false);
			for (int i=numParams-2; i--;) {
				if (getFilter()->matchModMatrix(modEnv3,i)) Env3DestBox->setToggleState(true,false);
				if (getFilter()->matchModMatrix(modLFO1,i)) LFO1DestBox->setToggleState(true,false);
				if (getFilter()->matchModMatrix(modLFO2,i)) LFO2DestBox->setToggleState(true,false);
			}
			getFilter()->getCallbackLock().exit();
		}
        //[/UserButtonCode_LFO2DestBox]
    }
    else if (buttonThatWasClicked == demoButton)
    {
        //[UserButtonCode_demoButton] -- add your button handler code here..
		URL(T("http://thepiz.org/mralias2/pro.php")).launchInDefaultBrowser();
        //[/UserButtonCode_demoButton]
    }
    else if (buttonThatWasClicked == bAuto)
    {
        //[UserButtonCode_bAuto] -- add your button handler code here..
        bAuto->setToggleState(!bAuto->getToggleState(),false);
        if (bAuto->getToggleState()) getFilter()->setParameterNotifyingHost(kAuto,1.f);
        else getFilter()->setParameterNotifyingHost(kAuto,0.f);
        //[/UserButtonCode_bAuto]
    }
    else if (buttonThatWasClicked == bDraw)
    {
        //[UserButtonCode_bDraw] -- add your button handler code here..
		if (bDraw->getToggleState()) {
			bDraw->setToggleState(false,false);
			waveDrawer->setVisible(false);
		}
		else {
			bDraw2->setToggleState(false,false);
			waveDrawer->setWave(0);
			waveDrawer->setVisible(true);
			bDraw->setToggleState(true,false);
		}
        //[/UserButtonCode_bDraw]
    }
    else if (buttonThatWasClicked == bDraw2)
    {
        //[UserButtonCode_bDraw2] -- add your button handler code here..
		if (bDraw2->getToggleState()) {
			bDraw2->setToggleState(false,false);
			waveDrawer->setVisible(false);
		}
		else {
			bDraw->setToggleState(false,false);
			waveDrawer->setWave(1);
			waveDrawer->setVisible(true);
			bDraw2->setToggleState(true,false);
		}
        //[/UserButtonCode_bDraw2]
    }
    else if (buttonThatWasClicked == sync1)
    {
        //[UserButtonCode_sync1] -- add your button handler code here..
        sync1->setToggleState(!sync1->getToggleState(),false);
		getFilter()->setParameterNotifyingHost(kLFO1Sync,sync1->getToggleState()?1.f:0.f);
        //[/UserButtonCode_sync1]
    }
    else if (buttonThatWasClicked == sync2)
    {
        //[UserButtonCode_sync2] -- add your button handler code here..
        sync2->setToggleState(!sync2->getToggleState(),false);
		getFilter()->setParameterNotifyingHost(kLFO2Sync,sync2->getToggleState()?1.f:0.f);
        //[/UserButtonCode_sync2]
    }
    else if (buttonThatWasClicked == sExp3)
    {
        //[UserButtonCode_sExp3] -- add your button handler code here..
        if (ModifierKeys::getCurrentModifiers().isShiftDown()
            || ModifierKeys::getCurrentModifiers().isCommandDown()) {
            sExp3->setToggleState(true,false);
            getFilter()->setParameterNotifyingHost(kExp3,1.f);
            sExp3->setButtonText("P!");
        }
        else {
            sExp3->setButtonText("P");
            sExp3->setToggleState(!sExp3->getToggleState(),false);
            if (sExp3->getToggleState()) getFilter()->setParameterNotifyingHost(kExp3,0.75f);
            else getFilter()->setParameterNotifyingHost(kExp3,0.f);
        }
        //[/UserButtonCode_sExp3]
    }
    else if (buttonThatWasClicked == interpolate1)
    {
        //[UserButtonCode_interpolate1] -- add your button handler code here..
        interpolate1->setToggleState(!interpolate1->getToggleState(),false);
		getFilter()->setParameterNotifyingHost(kInterpolate1,interpolate1->getToggleState()?1.f:0.f);
        //[/UserButtonCode_interpolate1]
    }
    else if (buttonThatWasClicked == interpolate2)
    {
        //[UserButtonCode_interpolate2] -- add your button handler code here..
        interpolate2->setToggleState(!interpolate2->getToggleState(),false);
		getFilter()->setParameterNotifyingHost(kInterpolate2,interpolate2->getToggleState()?1.f:0.f);
        //[/UserButtonCode_interpolate2]
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
		else if (!ModifierKeys::getCurrentModifiers().isPopupMenu()) {
			aboutbox->setVisible(true);
		}
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

void MrAlias2Editor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == filterModeBox)
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
        getFilter()->setParameterNotifyingHost(kWaveform1,(float)comboBox->getSelectedItemIndex()/(float)(plusUserWaveforms-1));
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2)
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        getFilter()->setParameterNotifyingHost(kWaveform2,(float)comboBox2->getSelectedItemIndex()/(float)(plusUserWaveforms-1));
#if 0
        //[/UserComboBoxCode_comboBox2]
    }
    else if (comboBoxThatHasChanged == patchBox)
    {
        //[UserComboBoxCode_patchBox] -- add your combo box handling code here..
#endif
    }
    else if (comboBoxThatHasChanged == (ComboBox*)patchBox)
    {
        getFilter()->wait=true;
        getFilter()->setCurrentProgram(patchBox->getSelectedId()-1);
        //[/UserComboBoxCode_patchBox]
    }
    else if (comboBoxThatHasChanged == LFO1WaveBox)
    {
        //[UserComboBoxCode_LFO1WaveBox] -- add your combo box handling code here..
        getFilter()->setParameterNotifyingHost(kLFO1Waveform,(float)LFO1WaveBox->getSelectedItemIndex()/(float)(plusUserWaveforms-1));
        //[/UserComboBoxCode_LFO1WaveBox]
    }
    else if (comboBoxThatHasChanged == LFO2WaveBox)
    {
        //[UserComboBoxCode_LFO2WaveBox] -- add your combo box handling code here..
        getFilter()->setParameterNotifyingHost(kLFO2Waveform,(float)LFO2WaveBox->getSelectedItemIndex()/(float)(plusUserWaveforms-1));
        //[/UserComboBoxCode_LFO2WaveBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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
        if (e.eventComponent==this || e.eventComponent==pizButton) {
            showMainMenu();
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
        else if (slider==sRel3) {
           getFilter()->setParameterNotifyingHost(kDec3,mapToVSTRange(slider));
           getFilter()->setParameterNotifyingHost(kSus3,0.f);
        }
        else if (slider==sDec3) {
           getFilter()->setParameterNotifyingHost(kRel3,mapToVSTRange(slider));
           getFilter()->setParameterNotifyingHost(kSus3,0.f);
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
		if (file.hasFileExtension("MrAliasBank")) {
			getFilter()->loadBank(file);
		}
		else if (file.hasFileExtension("MrAliasPatch")) {
			if (getFilter()->getCurrentProgram() < numPrograms-1)
			{
				getFilter()->loadPatch(file);
				if (i!=filenames.size()-1) getFilter()->next();
			}
		}
		else if (file.hasFileExtension("MrAliasCCMap")) {
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
        || file.hasFileExtension("fxp")
		)
    {
        return true;
    }
    return false;
}

void MrAlias2Editor::timerCallback ()
{
	lfo1indicator->setValue(getFilter()->getMod(modLFO1),true,false);
	lfo2indicator->setValue(getFilter()->getMod(modLFO2),true,false);
	env3indicator->setValue(getFilter()->getMod(modEnv3),true,false);
	if (getFilter()->demo) {
		if (demoRight) {
			if (demoButton->getX()>=(getWidth()-demoButton->getWidth())) demoRight=false;
		}
		else {
			if (demoButton->getX()<=0) demoRight=true;
		}
		if (demoDown) {
			if (demoButton->getY()>=(getHeight()-demoButton->getHeight())) demoDown=false;
		}
		else {
			if (demoButton->getY()<=0) demoDown=true;
		}

		demoButton->setTopLeftPosition(
			demoRight ? (demoButton->getX()+1) : (demoButton->getX()-1),
			demoDown ? (demoButton->getY()+1) : (demoButton->getY()-1));

		if (Time::getCurrentTime().getDayOfWeek()==2) {
			//Tuesday
			getFilter()->randomize(0.1f,true);
		}
	}
}

void MrAlias2Editor::changeListenerCallback (ChangeBroadcaster* source)
{
    //logDebugString("changeListenerCallback " + String((int)&source));
    if (source==getFilter()) {
        //logDebugString("source==getFilter()");
        updateParametersFromFilter();
    }
    else if (source==getFilter()->leds) {
        //logDebugString("source==leds");
        clipled->setToggleState(getFilter()->clipped,false);
        midiled->setToggleState(getFilter()->ledon,false);
        audioled->setToggleState(getFilter()->aledon,false);
        if (info->getText().compare(getFilter()->infoString)) info->setText(getFilter()->infoString,true);
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
    for (int i=numParams;i--;) {
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
	const bool page = filter->currentPage > 0;

    // ..release the lock ASAP
    filter->getCallbackLock().exit();

    // ..and after releasing the lock, we're free to do the time-consuming UI stuff..

	if (!filter->demo) demoButton->setVisible(false);

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
    setVSTSlider(sDecoupled1,params[kDecoupled1]);
    setVSTSlider(sDecoupled2,params[kDecoupled2]);
    setVSTSlider(sGlide,params[kGlide]);
	setVSTSlider(sAtt3,params[kAtt3]);
	setVSTSlider(sDec3,params[kDec3]);
	setVSTSlider(sSus3,params[kSus3]);
	setVSTSlider(sRel3,params[kRel3]);
	setVSTSlider(sEnv3Amount,params[kEnv3Amount]);
	setVSTSlider(sLFO1Rate,params[kLFO1Rate]);
	setVSTSlider(sLFO1Amount,params[kLFO1Amount]);
	setVSTSlider(sLFO2Rate,params[kLFO2Rate]);
	setVSTSlider(sLFO2Amount,params[kLFO2Amount]);
	setVSTSlider(sRandomSpeed,params[kRandomSpeed]);
	setVSTSlider(sRandomStrength,params[kRandomStrength]);


    setVSTSlider(sMorph,params[kMorph]);
//    sWaveform1->setVSTSlider(params[kWaveform1]);

    sMode->setToggleState(params[kMode]>=0.5f,false);
    if (params[kMode]==1.f) sMode->setButtonText("micro");
    else sMode->setButtonText("Mono");
    sRetrig->setToggleState(params[kRetrig]>=0.5f,false);
    sRetrig->setVisible(params[kMode]>=0.5f && params[kMode]<1.f);
    sGlide->setVisible(params[kMode]>=0.5f/* && params[kMode]<1.f*/);

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
    sExp3->setToggleState(params[kExp3]>=0.5f,false);
    if (params[kExp3]==1.f) sExp3->setButtonText("P!");
    else sExp3->setButtonText("P");

	int wave = roundFloatToInt(params[kWaveform1]*((float)plusUserWaveforms-1.f));
	comboBox->setText(getFilter()->getWaveformName(wave),true);
	wave = roundFloatToInt(params[kWaveform2]*((float)plusUserWaveforms-1.f));
	comboBox2->setText(getFilter()->getWaveformName(wave),true);
	wave=roundFloatToInt(params[kLFO1Waveform]*((float)plusUserWaveforms-1.f));
	LFO1WaveBox->setText(getFilter()->getWaveformName(wave),true);
	wave=roundFloatToInt(params[kLFO2Waveform]*((float)plusUserWaveforms-1.f));
	LFO2WaveBox->setText(getFilter()->getWaveformName(wave),true);
    //switch(wave) {
    //    case rampup: comboBox->setText("RampUp",true); break;
    //    case rampdn: comboBox->setText("RampDown",true); break;
    //    case pulse: comboBox->setText("Square",true); break;
    //    case triangle: comboBox->setText("Triangle",true); break;
    //    case sine: comboBox->setText("Sine",true); break;
    //    case minko: comboBox->setText("Minkowski",true); break;
    //    case weier: comboBox->setText("Weierstrass",true); break;
    //    case comb: comboBox->setText("AutoAlias",true); break;
    //    case 8: comboBox->setText("Eight",true); break;
    //    case 9: comboBox->setText("OddEight",true); break;
    //    case computer: comboBox->setText("Computer",true); break;
    //    case 11: comboBox->setText("Funnel",true); break;
    //    case 12: comboBox->setText("Grate",true); break;
    //    case 13: comboBox->setText("Noise",true); break;
    //    case 14: comboBox->setText("Sine+",true); break;
    //    case 15: comboBox->setText("Narrow",true); break;
    //    case 16: comboBox->setText("Octaves",true); break;
    //    case 17: comboBox->setText("Ughhh",true); break;
    //    case draw1: comboBox->setText("Drawable1",true); break;
    //    case draw2: comboBox->setText("Drawable2",true); break;
    //    default: comboBox->setText(getFilter()->waveNames[wave-numWaveforms],true); break;
    //}

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
    patchBox->changeItemText(patchnum+1,String(patchnum+1)+". " + patchname);
    if (filter->newbank) {
        patchBox->clear(true);
        for (int i=0;i<numPrograms;i++) {
            patchBox->addItem (String(i+1)+". "+ filter->getProgramName(i), i+1);
        }
        filter->newbank=false;
    }

    clipled->setToggleState(clipped,false);
    midiled->setToggleState(ledon,false);
    audioled->setToggleState(aledon,false);
	sync1->setToggleState(params[kLFO1Sync]>=0.5f,false);
	sync2->setToggleState(params[kLFO2Sync]>=0.5f,false);

    if (h!=getHeight()) {
        setSize ((int)(h*aspectRatio), h);
    }

#ifdef MRALIASPRO
    int ch = roundFloatToInt(params[kChannel]*16.f)-1;
    keyboard->setMidiChannelsToDisplay(ch==-1?0xffff:1<<ch);
    keyboard->setMidiChannel(ch==-1?1:ch+1);

    decoupled1Button->setToggleState(roundFloatToInt(params[kDecoupled1]*128.f)>0,false);
    decoupled2Button->setToggleState(roundFloatToInt(params[kDecoupled2]*128.f)>0,false);
    interpolate1->setToggleState(params[kInterpolate1]>=0.5f,false);
    interpolate2->setToggleState(params[kInterpolate2]>=0.5f,false);
    bAuto->setToggleState(params[kAuto]>=0.5f,false);

	Env3DestBox->setToggleState(false,false);
	LFO1DestBox->setToggleState(false,false);
	LFO2DestBox->setToggleState(false,false);
#endif
    for (int i=numParams; i--;) {
        if (ccmap[i]!=oldccmap[i]) {
           oldccmap[i] = ccmap[i];
           getSliderByIndex(i)->setColour(Slider::backgroundColourId, Colours::transparentBlack);
           ccmapbox[i]->setValue(ccmap[i],false);
        }
#ifdef MRALIASPRO
		if (filter->matchModMatrix(modEnv3,i)) Env3DestBox->setToggleState(true,false);
		if (filter->matchModMatrix(modLFO1,i)) LFO1DestBox->setToggleState(true,false);
		if (filter->matchModMatrix(modLFO2,i)) LFO2DestBox->setToggleState(true,false);
#endif
    }
#ifdef MRALIASPRO
		sAtt3->setVisible(page);
		sDec3->setVisible(page);
		sSus3->setVisible(page);
		sRel3->setVisible(page);
		sEnv3Amount->setVisible(page);
		sLFO1Amount->setVisible(page);
		sLFO1Rate->setVisible(page);
		sLFO2Amount->setVisible(page);
		sLFO2Rate->setVisible(page);
		page2->setVisible(page);
		LFO1DestBox->setVisible(page);
		LFO2DestBox->setVisible(page);
		LFO1WaveBox->setVisible(page);
		LFO2WaveBox->setVisible(page);
		bLFO1Free->setVisible(page);
		bLFO2Free->setVisible(page);
		Env3DestBox->setVisible(page);
		lfo1indicator->setVisible(page);
		lfo2indicator->setVisible(page);
		env3indicator->setVisible(page);
		sPage->setToggleState(page,false);
		bLFO1Free->setToggleState(params[kLFO1Free]>=0.5f,false);
		bLFO2Free->setToggleState(params[kLFO2Free]>=0.5f,false);
		sync1->setVisible(page);
		sync2->setVisible(page);
		sExp3->setVisible(page);

		sAtt->setVisible(!page);
		sDec->setVisible(!page);
		sSus->setVisible(!page);
		sRel->setVisible(!page);
		sFAtt->setVisible(!page);
		sFDec->setVisible(!page);
		sFSus->setVisible(!page);
		sFRel->setVisible(!page);
		sExp->setVisible(!page);
		sFExp->setVisible(!page);
		sFiltEnv->setVisible(!page);
		sFVSens->setVisible(!page);
		sVelSens->setVisible(!page);
		sDivEnv->setVisible(!page);
		waveDrawer->repaint();
#endif

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
    if (slider==sDecoupled1) return kDecoupled1;
    if (slider==sDecoupled2) return kDecoupled2;
    if (slider==sGlide)      return kGlide;
    if (slider==sMorph)      return kMorph;
	if (slider==sAtt3)		 return kAtt3;
	if (slider==sDec3)		 return kDec3;
	if (slider==sSus3)		 return kSus3;
	if (slider==sRel3)		 return kRel3;
	if (slider==sEnv3Amount) return kEnv3Amount;
	if (slider==sLFO1Rate)	 return kLFO1Rate;
	if (slider==sLFO1Amount) return kLFO1Amount;
	if (slider==sLFO2Rate)	 return kLFO2Rate;
	if (slider==sLFO2Amount) return kLFO2Amount;
	if (slider==sRandomSpeed)	 return kRandomSpeed;
	if (slider==sRandomStrength) return kRandomStrength;

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
    case kDecoupled1: return sDecoupled1;
    case kDecoupled2: return sDecoupled2;
    case kGlide:      return sGlide;
    case kAtt3:       return sAtt3;
    case kDec3:       return sDec3;
    case kSus3:       return sSus3;
    case kRel3:       return sRel3;
    case kEnv3Amount: return sEnv3Amount;
    case kLFO1Rate:   return sLFO1Rate;
    case kLFO1Amount: return sLFO1Amount;
    case kLFO2Rate:   return sLFO2Rate;
    case kLFO2Amount: return sLFO2Amount;
	case kRandomSpeed:return sRandomSpeed;
	case kRandomStrength:return sRandomStrength;

    case kMorph:      return sMorph;
    default:          return sMorph;
    }
}

inline void MrAlias2Editor::getComponentIndexAndType(Component* c, int &index, int &type) {
    //buttons
    if      (c==sExp) {type=buttonType; index=kExp;}
    else if (c==sFExp) {type=buttonType; index=kFExp;}
    else if (c==sExp3) {type=buttonType; index=kExp3;}
    else if (c==sMode) {type=buttonType; index=kMode;}
    else if (c==sPitchShift) {type=buttonType; index=kPitchShift;}
    else if (c==limiterButton) {type=buttonType; index=kLimiter;}
    else if (c==randomButton) {type=buttonType; index=kRandomize;}
    else if (c==sRetrig) {type=buttonType; index=kRetrig;}
    else if (c==bLFO1Free) {type=buttonType; index=kLFO1Free;}
    else if (c==bLFO2Free) {type=buttonType; index=kLFO2Free;}
    else if (c==interpolate1) {type=buttonType; index=kInterpolate1;}
    else if (c==interpolate2) {type=buttonType; index=kInterpolate2;}
    else if (c==bAuto) {type=buttonType; index=kAuto;}
    //combo boxes
    else if (c==comboBox) {type=comboBoxType; index=kWaveform1;}
    else if (c==comboBox2) {type=comboBoxType; index=kWaveform2;}
    else if (c==filterModeBox) {type=comboBoxType; index=kFMode;}
    else if (c==LFO1WaveBox) {type=comboBoxType; index=kLFO1Waveform;}
    else if (c==LFO2WaveBox) {type=comboBoxType; index=kLFO2Waveform;}
    //sliders
    else {
        type=sliderType;
        index = getSliderIndex((Slider*)c);
    }
}

void MrAlias2Editor::showMainMenu() {
    PopupMenu m, vDest, aDest, cpDest, paDest, nDest, envfollowerDest, ampenvDest, filtenvDest,
		envDest, osc1Dest, osc2Dest, lfo1Dest, lfo2Dest, pbDest, modWheelDest,
		skinMenu;

	bool vDestTicked=false;
	bool aDestTicked=false;
	bool cpDestTicked=false;
	bool paDestTicked=false;
	bool nDestTicked=false;
	bool envfollowerDestTicked=false;
	bool ampenvDestTicked=false;
	bool filtenvDestTicked=false;
	bool envDestTicked=false;
	bool osc1DestTicked=false;
	bool osc2DestTicked=false;
	bool lfo1DestTicked=false;
	bool lfo2DestTicked=false;
	bool pbDestTicked=false;
	bool modWheelDestTicked=false;
    for (int i=0;i<numParams-2;i++) {
		Colour textColor = getFilter()->isModulatable(i) ? Colours::black : Colours::red;
		vDest.addColouredItem(100+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modVelocity,i));
		if(getFilter()->matchModMatrix(modVelocity,i)) vDestTicked = true;
		cpDest.addColouredItem(200+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modChPressure,i));
		if(getFilter()->matchModMatrix(modChPressure,i)) cpDestTicked = true;
		paDest.addColouredItem(300+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modAftertouch,i));
		if(getFilter()->matchModMatrix(modAftertouch,i)) paDestTicked = true;
		nDest.addColouredItem(1100+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modNote,i));
		if(getFilter()->matchModMatrix(modNote,i)) nDestTicked = true;
		modWheelDest.addColouredItem(1400+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modModWheel,i));
		if(getFilter()->matchModMatrix(modModWheel,i)) modWheelDestTicked = true;
		pbDest.addColouredItem(1500+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modPitchBend,i));
		if(getFilter()->matchModMatrix(modPitchBend,i)) pbDestTicked = true;
		aDest.addColouredItem(400+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modAudio,i));
		if(getFilter()->matchModMatrix(modAudio,i)) aDestTicked = true;
		envfollowerDest.addColouredItem(500+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modAudioEnv,i));
		if(getFilter()->matchModMatrix(modAudioEnv,i)) envfollowerDestTicked = true;
		ampenvDest.addColouredItem(600+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modAmpEnv,i));
		if(getFilter()->matchModMatrix(modAmpEnv,i)) ampenvDestTicked = true;
		filtenvDest.addColouredItem(700+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modFiltEnv,i));
		if(getFilter()->matchModMatrix(modFiltEnv,i)) filtenvDestTicked = true;
		envDest.addColouredItem(800+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modEnv3,i));
		if(getFilter()->matchModMatrix(modEnv3,i)) envDestTicked = true;
		osc1Dest.addColouredItem(900+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modOsc1,i));
		if(getFilter()->matchModMatrix(modOsc1,i)) osc1DestTicked = true;
		osc2Dest.addColouredItem(1000+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modOsc2,i));
		if(getFilter()->matchModMatrix(modOsc2,i)) osc2DestTicked = true;
		lfo1Dest.addColouredItem(1200+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modLFO1,i));
		if(getFilter()->matchModMatrix(modLFO1,i)) lfo1DestTicked = true;
		lfo2Dest.addColouredItem(1300+i,getFilter()->getParameterName(i),textColor, true, getFilter()->matchModMatrix(modLFO2,i));
		if(getFilter()->matchModMatrix(modLFO2,i)) lfo2DestTicked = true;
    }

	OwnedArray<File> skins;
	if (File(getFilter()->currentPath+File::separatorString+"skins").findChildFiles(skins,File::findDirectories,false,"*"))
	{
		for (int i=0;i<skins.size();i++)
		{
			skinMenu.addItem(90000+i,skins[i]->getFileName(),true,
				getFilter()->skin == String("skins") + File::separatorString + skins[i]->getFileName());
		}
	}
    m.addSectionHeader("Modulation");
	m.addSubMenu("Velocity",vDest,true,vDestTicked?menuDot:0);
	m.addSubMenu("Mod Wheel",modWheelDest,true,modWheelDestTicked?menuDot:0);
	m.addSubMenu("Pitch Wheel",pbDest,true,pbDestTicked?menuDot:0);
    m.addSubMenu("Channel Pressure",cpDest,true,cpDestTicked?menuDot:0);
    m.addSubMenu("Poly Aftertouch",paDest,true,paDestTicked?menuDot:0);
    m.addSubMenu("Note Number",nDest,true,nDestTicked?menuDot:0);
    m.addSubMenu("Audio Input",aDest,true,aDestTicked?menuDot:0);
    m.addSubMenu("Audio Env Follower",envfollowerDest,true,envfollowerDestTicked?menuDot:0);
    m.addSubMenu("Amp Env",ampenvDest,true,ampenvDestTicked?menuDot:0);
    m.addSubMenu("Filter Env",filtenvDest,true,filtenvDestTicked?menuDot:0);
    m.addSubMenu("Extra Env",envDest,true,envDestTicked?menuDot:0);
    m.addSubMenu("Osc 1",osc1Dest,true,osc1DestTicked?menuDot:0);
    m.addSubMenu("Osc 2",osc2Dest,true,osc2DestTicked?menuDot:0);
    m.addSubMenu("LFO 1",lfo1Dest,true,lfo1DestTicked?menuDot:0);
    m.addSubMenu("LFO 2",lfo2Dest,true,lfo2DestTicked?menuDot:0);
    m.addItem(2000,"Clear");
    m.addSeparator();
    m.addSectionHeader("CC Mapping");
    m.addItem (3, String(T("Use CC Mapping")), true, getFilter()->isCCMappingEnabled());
    m.addItem (4, String(T("Clear All CC Mapping")));
    m.addItem (43, String(T("Apply All to Bank Now")));
    m.addItem (44, String(T("Apply All to Bank by Default")), true, getFilter()->CCMappingToBankByDefault);
    m.addItem (88, String(T("Save CC Map to File")));
	m.addSeparator();
	m.addSubMenu("Choose skin",skinMenu);
	m.addItem (77, String(T("User's Manual")));
	if (getFilter()->demo)
	{
		m.addItem (99, String(T("Load MrAliasKey")));
	}
    m.addSeparator();
    m.addSectionHeader("Auto Randomizer");
	m.addCustomItem(-1,sRandomSpeed,100,20,false);
	m.addCustomItem(-1,sRandomStrength,100,20,false);
    int result = m.show();
    if (result > 0)
    {
        if (result==2000) {
            getFilter()->getCallbackLock().enter();
            getFilter()->clearModMatrix();
            getFilter()->getCallbackLock().exit();
        }
		else if (result>=90000) {
			// choose skin
			getFilter()->skin=String("skins") + File::separatorString + skins[result-90000]->getFileName();
			reloadSkin();
			getFilter()->writeSettings();
		}
        else if (result>=1500) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modPitchBend,result-1500)
                                                   ? modNone : modPitchBend,
                                                   result-1500);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=1400) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modModWheel,result-1400)
                                                   ? modNone : modModWheel,
                                                   result-1400);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=1300) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modLFO2,result-1300)
                                                   ? modNone : modLFO2,
                                                   result-1300);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=1200) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modLFO1,result-1200)
                                                   ? modNone : modLFO1,
                                                   result-1200);
            getFilter()->getCallbackLock().exit();
        }
		else if (result>=1100) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modNote,result-1100)
                                                   ? modNone : modNote,
                                                   result-1100);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=1000) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modOsc2,result-1000)
                                                   ? modNone : modOsc2,
                                                   result-1000);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=900) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modOsc1,result-900)?modNone:modOsc1,result-900);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=800) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modEnv3,result-800)?modNone:modEnv3,result-800);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=700) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modFiltEnv,result-700)?modNone:modFiltEnv,result-700);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=600) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modAmpEnv,result-600)?modNone:modAmpEnv,result-600);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=500) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modAudioEnv,result-500)?modNone:modAudioEnv,result-500);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=400) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modAudio,result-400)?modNone:modAudio,result-400);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=300) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modAftertouch,result-300)?modNone:modAftertouch,result-300);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=200) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modChPressure,result-200)?modNone:modChPressure,result-200);
            getFilter()->getCallbackLock().exit();
        }
        else if (result>=100) {
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(modVelocity,result-100)?modNone:modVelocity,result-100);
            getFilter()->getCallbackLock().exit();
        }

        else if (result==3) {
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
		else if (result==99) {
			if (!getFilter()->readKeyFile())
			{
				FileChooser myChooser ("Load MrAliasKey...",
									   File(getFilter()->currentPath),
									   "*.txt;MrAliasKey");

				if (myChooser.browseForFileToOpen())
				{
					File file (myChooser.getResult());
					if (!getFilter()->readKeyFile(file))
						info->setText("MrAliasKey not found",true);
				}

			}
		}
		else if (result==77) {
			String manualPath = getFilter()->currentPath + File::separatorString
								+ String("doc") + File::separatorString
								+ String("Mr. Alias Pro User's Manual.pdf");
			info->setText(manualPath,true);
			File(manualPath).startAsProcess();
		}
		Env3DestBox->setToggleState(false,false);
		LFO1DestBox->setToggleState(false,false);
		LFO2DestBox->setToggleState(false,false);
		for (int i=numParams-2; i--;) {
			if (getFilter()->matchModMatrix(modEnv3,i)) Env3DestBox->setToggleState(true,false);
			if (getFilter()->matchModMatrix(modLFO1,i)) LFO1DestBox->setToggleState(true,false);
			if (getFilter()->matchModMatrix(modLFO2,i)) LFO2DestBox->setToggleState(true,false);
		}
	}
}

void MrAlias2Editor::showControlMenu(Component* c) {
    int componentType;
    int index;
    getComponentIndexAndType(c,index,componentType);

    const float value = getFilter()->getParameter(index);
    PopupMenu m, modMenu;

	bool modActive=false;
	for (int i=0;i<numModSources;i++)
	{
		modMenu.addItem(i+1000,getFilter()->getModSourceName(i),true,getFilter()->matchModMatrix(i,index));
		if (i!=modNone && getFilter()->matchModMatrix(i,index)) modActive=true;
	}

    m.addSectionHeader("- " + c->getName() + " -");
	m.addItem(-1,"Current value: " + getFilter()->getParameterText(index),false);
    m.addSeparator();
    m.addSectionHeader("Modulation");
	m.addSubMenu("Mod Source",modMenu,index!=kMorph && index!=kRandomize,modActive?menuDot:0);

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
        if (result>=1000) {
			result-=1000;
            getFilter()->getCallbackLock().enter();
            getFilter()->setModMatrix(getFilter()->matchModMatrix(result,index)
                                                   ? modNone : result, index);
            getFilter()->getCallbackLock().exit();
        }
        else if (result==1) {
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

void MrAlias2Editor::reloadSkin()
{
	String bgFile = getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("bg.svg");
	if (!File(bgFile).exists()) bgFile = getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("bg.png");
	bg = Drawable::createFromImageFile(File(bgFile));

	String page2File = getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("page2.svg");
	if (!File(page2File).exists()) page2File = getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("page2.png");
	page2->setBackgroundImage(File(page2File));

	wood1 = ImageCache::getFromFile(File(getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("wood1.png")));
	wood2 = ImageCache::getFromFile(File(getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("wood2.png")));
	menuDot = ImageCache::getFromFile(File(getFilter()->currentPath+File::separatorString + getFilter()->skin + File::separatorString + T("dot.png")));

	smallKnob = ImageCache::getFromFile(File(getFilter()->currentPath + File::separator + getFilter()->skin + File::separatorString + String("knob.png")));
	sEnv3Amount->setImage(smallKnob);
	sLFO1Amount->setImage(smallKnob);
	sLFO2Amount->setImage(smallKnob);
	sLFO1Rate->setImage(smallKnob);
	sLFO2Rate->setImage(smallKnob);
	sLFO1Amount->setImage(smallKnob);
	sSineMix->setImage(smallKnob);
    sAInertia->setImage(smallKnob);
    sDivEnv->setImage(smallKnob);
    sFreq1->setImage(smallKnob);
    sRingMod->setImage(smallKnob);
    sBRMix->setImage(smallKnob);
    sVelSens->setImage(smallKnob);
    sInputGain->setImage(smallKnob);
    sOscGain->setImage(smallKnob);
    sFiltEnv->setImage(smallKnob);
    sWet->setImage(smallKnob);
    sOctave->setImage(smallKnob);
    sStereo->setImage(smallKnob);
    sOscMix->setImage(smallKnob);
    sFVSens->setImage(smallKnob);
    sPhMod->setImage(smallKnob);
    sDivMix->setImage(smallKnob);
    sPostDivMix->setImage(smallKnob);
    sM1Mix->setImage(smallKnob);
    sGlide->setImage(smallKnob);

	largeKnob = ImageCache::getFromFile(File(getFilter()->currentPath + File::separatorString + getFilter()->skin + File::separatorString + String("knob_large.png")));
	sCutoff->setImage(largeKnob);
	sRes->setImage(largeKnob);
	sVolume->setImage(largeKnob);

	hSliderThumb = ImageCache::getFromFile(File(getFilter()->currentPath + File::separatorString + getFilter()->skin + File::separatorString + String("slider_h.png")));
	hSliderBG = Drawable::createFromImageFile(File(getFilter()->currentPath + File::separatorString + getFilter()->skin + File::separatorString + String("slider_h_bg.svg")));
	sAlias->setImages(hSliderThumb,hSliderBG);
	sDivide->setImages(hSliderThumb,hSliderBG);
	sThresh->setImages(hSliderThumb,hSliderBG);
	sPostDivide->setImages(hSliderThumb,hSliderBG);
	sRate->setImages(hSliderThumb,hSliderBG);
	sSineFreq->setImages(hSliderThumb,hSliderBG);
	sSineRes->setImages(hSliderThumb,hSliderBG);
	sClip->setImages(hSliderThumb,hSliderBG);;
	sStereo2->setImages(hSliderThumb,hSliderBG);
	sM1->setImages(hSliderThumb,hSliderBG);
	sDecoupled1->setImages(hSliderThumb,hSliderBG);
	sDecoupled2->setImages(hSliderThumb,hSliderBG);
	sRandomSpeed->setImages(hSliderThumb,hSliderBG);
	sRandomStrength->setImages(hSliderThumb,hSliderBG);

	vSliderThumb = ImageCache::getFromFile(File(getFilter()->currentPath + File::separatorString + getFilter()->skin + File::separatorString + String("slider_v.png")));
	vSliderBG = Drawable::createFromImageFile(File(getFilter()->currentPath + File::separatorString + getFilter()->skin + File::separatorString + String("slider_v_bg.svg")));
	sAtt->setImages(vSliderThumb,vSliderBG);
	sDec->setImages(vSliderThumb,vSliderBG);
	sSus->setImages(vSliderThumb,vSliderBG);
	sRel->setImages(vSliderThumb,vSliderBG);
	sFAtt->setImages(vSliderThumb,vSliderBG);
	sFDec->setImages(vSliderThumb,vSliderBG);
	sFSus->setImages(vSliderThumb,vSliderBG);
	sFRel->setImages(vSliderThumb,vSliderBG);
	sAtt3->setImages(vSliderThumb,vSliderBG);
	sDec3->setImages(vSliderThumb,vSliderBG);
	sSus3->setImages(vSliderThumb,vSliderBG);
	sRel3->setImages(vSliderThumb,vSliderBG);

	repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MrAlias2Editor" componentName=""
                 parentClasses="public AudioProcessorEditor, public ChangeListener, public FileDragAndDropTarget, public PizComboBoxListener, public Timer"
                 constructorParams="MrAlias2* const ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter),&#10;aspectRatio(1.7125),&#10;bg(0),&#9;&#10;wood1(0),&#9;&#10;wood2(0),&#10;&#9;smallKnob(0),&#10;&#9;largeKnob(0),&#10;&#9;hSliderThumb(0),&#10;&#9;hSliderBG(0),&#10;&#9;vSliderThumb(0),&#10;&#9;vSliderBG(0)"
                 snapPixels="3" snapActive="0" snapShown="1" overlayOpacity="0"
                 fixedSize="1" initialWidth="548" initialHeight="320">
  <BACKGROUND backgroundColour="ff434343">
    <RECT pos="0% 0% 100% 100%" fill="linear: 50% 0, 50% 100, 0=ff000000, 1=ff2c2a31"
          hasStroke="0"/>
    <RECT pos="67.153% 25.294% 28.467% 46.765%" fill="linear: 0% 0%, 0% 44%, 0=ff424242, 1=ff4e3f3f"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 0% 0%, 100% 100%, 0=ffffffff, 1=ff000000"/>
    <IMAGE pos="96.36% 0 3.5% 100%" resource="wood2_png" opacity="1" mode="0"/>
    <PATH pos="0 0 100 100" fill="linear: 0 -20%, 0 30%, 0=ff4c4c4c, 1=ff4e3f3f"
          hasStroke="1" stroke="0.899999976, mitered, butt" strokeColour="linear: 0 0, 100% 100%, 0=8fffffff, 1=ff000000"
          nonZeroWinding="1">s 34.489% 23.125% l 34.489% 13.75% l 4.2% 13.75% l 4.2% 10.156% l 95.7% 10.156% l 95.7% 23% x</PATH>
    <RECT pos="4.197% 15.882% 28.467% 29.412%" fill="linear: 0 -10%, 0% 40%, 0=ff4d4d4d, 1=ff4e3f3f"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 0 0, 100% 100%, 0=75ffffff, 1=ff000000"/>
    <PATH pos="0 0 100 100" fill="linear: 0 10%, 0 70%, 0=ff737373, 1=ff4e3f3f"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 0 0, 100% 100%, 0=ffffffff, 1=ff000000"
          nonZeroWinding="1">s 4.3% 91% l 4.3% 75.1% l 34.568% 75.1% l 34.568% 62% l 65.25% 62% l 65.25% 75.1% l 95.62% 75.1% l 95.7% 91% x</PATH>
    <RECT pos="34.489% 37.941% 30.839% 21.765%" fill="linear: 0 10%, 0 50%, 0=ff434343, 1=ff4e3f3f"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 0 0, 100% 100%, 0=c2ffffff, 1=ff000000"/>
    <RECT pos="35.401% 76.765% 29.197% 12.941%" fill="solid: 36000000"
          hasStroke="0"/>
    <RECT pos="35.401% 17.059% 16.788% 5%" fill="solid: 36000000" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: 50ffffff" hasStroke="0" nonZeroWinding="1">s 89.757% 4.423% l 79.884% 4.423% l 78.884% 2.509% l 91.637% 1.509% l 93.637% 7.732% l 81.746% 7.732% l 82.746% 9.137% l 92.637% 9.137% l 93.637% 11.038% l 79.884% 12.038% l 78.884% 5.828% l 90.757% 5.828% x</PATH>
    <RECT pos="4.197% 47.647% 28.467% 24.412%" fill="linear: 0 24%, 0 68%, 0=ff555555, 1=ff4e3f3f"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 0 0, 100% 100%, 0=84ffffff, 1=ff000000"/>
    <RECT pos="68.248% 47.941% 26.277% 22.353%" fill="solid: 36000000"
          hasStroke="0"/>
    <RECT pos="53.125% 13.125% 41.992% 9.062%" fill="solid: 36000000" hasStroke="0"/>
    <RECT pos="65.328% 13.75% 21.898% 4.062%" fill="solid: 36000000" hasStroke="0"/>
    <IMAGE pos="0 0 3.5% 100%" resource="wood1_png" opacity="1" mode="0"/>
    <IMAGE pos="7.117% 3.235% 68.248% 7.647%" resource="whitetitle_svg"
           opacity="0.377" mode="1"/>
  </BACKGROUND>
  <SLIDER name="MIDI Channel" id="b7a8ffcec56914e5" memberName="sChannel"
          virtualName="" explicitFocusOrder="0" pos="45.803% 10.625% 5.657% 7.812%"
          posRelativeW="b4cfea27308348d9" tooltip="MIDI Channel" thumbcol="bbbbff"
          trackcol="ffffff" rotarysliderfill="ff" rotaryslideroutline="0"
          textboxtext="ffffffff" min="0" max="16" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="keyboard" id="ef6daecb91aa015c" memberName="keyboard" virtualName="MrAliasKeyboard"
                    explicitFocusOrder="0" pos="3.832% 93.125% 92.518% 6.875%" class="MidiKeyboardComponent"
                    params="ownerFilter-&gt;keyboardState,MidiKeyboardComponent::horizontalKeyboard"/>
  <SLIDER name="Alias" id="643c9f76ae9fecfc" memberName="sAlias" virtualName="ProSliderH"
          explicitFocusOrder="0" pos="4.562% 37.5% 22.08% 5.312%" tooltip="Alias"
          min="0" max="102" int="0.01" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Cutoff" id="95d9e283adc46234" memberName="sCutoff"
          virtualName="ProKnob" explicitFocusOrder="0" pos="5.292% 50.625% 10.766% 18.438%"
          tooltip="Filter Cutoff" bkgcol="0" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" textboxoutline="b2888888" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Divide" id="e15284b871cb9580" memberName="sDivide" virtualName="ProSliderH"
          explicitFocusOrder="0" pos="35.584% 38.438% 23.175% 5.312%" tooltip="Divide"
          rotaryslideroutline="66000000" min="0" max="100" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Amp Env Attack" id="98f08232c4ccc1db" memberName="sAtt"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="68.066% 25.625% 4.562% 21.25%"
          tooltip="Amp Env Attack" min="0" max="100" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Downsample Rate" id="67291950d5f1ae5c" memberName="sRate"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="5.109% 76.562% 21.715% 5.312%"
          tooltip="Downsample Rate" min="0" max="100" int="0.1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sine Mix" id="9c7fc02f68f62bb7" memberName="sSineMix" virtualName="ProKnob"
          explicitFocusOrder="0" pos="57.664% 63.75% 6.204% 10.625%" tooltip="Sine Mix"
          rotarysliderfill="e3000000" rotaryslideroutline="66ffffff" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sine Resolution" id="2c5c4d3bc0769a2b" memberName="sSineRes"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="35.584% 62.187% 21.533% 5.312%"
          tooltip="Sine Resolution" min="0" max="100" int="0.1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Post Divide" id="f6f5cffc22cfc5df" memberName="sPostDivide"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="0% 123.529% 100% 5.312%"
          posRelativeX="e15284b871cb9580" posRelativeY="835be6a95912d3cf"
          posRelativeW="e15284b871cb9580" tooltip="Post Divide" min="0"
          max="100" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Clipper" id="20c26f0e7b36dd30" memberName="sClip" virtualName="ProSliderH"
          explicitFocusOrder="0" pos="66.788% 76.25% 16.971% 5.312%" tooltip="Clipper"
          min="0" max="100" int="0.1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Inertia" id="439a364155b8a9a1" memberName="sAInertia" virtualName="ProKnob"
          explicitFocusOrder="0" pos="26.46% 35.938% 5.474% 8.75%" tooltip="Inertia"
          rotarysliderfill="e3000000" rotaryslideroutline="66ffffff" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Decay" id="45d621746fcf224f" memberName="sDec"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="73.175% 0% 100% 100%"
          posRelativeY="98f08232c4ccc1db" posRelativeW="98f08232c4ccc1db"
          posRelativeH="98f08232c4ccc1db" tooltip="Amp Env Decay" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Sustain" id="7e37ae1d9e9c0614" memberName="sSus"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="78.467% 0% 100% 100%"
          posRelativeY="45d621746fcf224f" posRelativeW="45d621746fcf224f"
          posRelativeH="45d621746fcf224f" tooltip="Amp Env Sustain" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Release" id="93deecf83421a9aa" memberName="sRel"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="83.942% 0% 100% 100%"
          posRelativeY="7e37ae1d9e9c0614" posRelativeW="7e37ae1d9e9c0614"
          posRelativeH="7e37ae1d9e9c0614" tooltip="Amp Env Release" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="AmpEnv -&gt; Divider" id="f57d520d0d29459" memberName="sDivEnv"
          virtualName="ProKnob" explicitFocusOrder="0" pos="89.051% 30.938% 5.657% 9.375%"
          tooltip="AmpEnv -&gt; Divider" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Resonance" id="a1fe1c4479e68a76" memberName="sRes"
          virtualName="ProKnob" explicitFocusOrder="0" pos="20.438% 0% 10.766% 18.438%"
          posRelativeY="95d9e283adc46234" tooltip="Filter Resonance" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Downsampler Mix" id="b44fe15f624d0449" memberName="sBRMix"
          virtualName="ProKnob" explicitFocusOrder="0" pos="104.202% -52.941% 4.927% 10.312%"
          posRelativeX="67291950d5f1ae5c" posRelativeY="67291950d5f1ae5c"
          tooltip="Downsampler Mix" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sine Frequency" id="a0fd508eebf3b240" memberName="sSineFreq"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="0% 123.529% 100% 100%"
          posRelativeX="2c5c4d3bc0769a2b" posRelativeY="2c5c4d3bc0769a2b"
          posRelativeW="2c5c4d3bc0769a2b" posRelativeH="2c5c4d3bc0769a2b"
          tooltip="Sine Frequency" min="0" max="100" int="0.1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Velocity Sensitivity" id="7ddc354c5ee1fba6" memberName="sVelSens"
          virtualName="ProKnob" explicitFocusOrder="0" pos="89.051% 38.75% 5.657% 9.375%"
          tooltip="Amp Velocity Sensitivity" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Amount" id="892c3c51db89d048" memberName="sFiltEnv"
          virtualName="ProKnob" explicitFocusOrder="0" pos="89.051% 54.375% 5.657% 9.375%"
          tooltip="Filter Env Amount" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Velocity Sens" id="f12eb2f0344129ea" memberName="sFVSens"
          virtualName="ProKnob" explicitFocusOrder="0" pos="89.051% 62.5% 5.657% 9.375%"
          tooltip="Filter Velocity Sensitivity" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pitchbend Range" id="f8d35e4737e52ab5" memberName="sPBRange"
          virtualName="" explicitFocusOrder="0" pos="34.124% 15.937% 5.657% 7.812%"
          posRelativeW="b4cfea27308348d9" tooltip="Pitchbend Range" thumbcol="bbbbff"
          trackcol="ffffff" rotarysliderfill="ff" rotaryslideroutline="0"
          textboxtext="ffffffff" min="0" max="24" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Input Gain" id="f41463c86a598835" memberName="sInputGain"
          virtualName="ProKnob" explicitFocusOrder="0" pos="36.131% 76.875% 8.212% 11.25%"
          tooltip="Input Gain" bkgcol="0" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Wet/Dry" id="d8fa16ddd92f185b" memberName="sWet" virtualName="ProKnob"
          explicitFocusOrder="0" pos="45.985% 76.875% 8.212% 11.25%" tooltip="Wet/Dry"
          bkgcol="0" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="-99" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Synth Gain" id="c3be568e2a93f6a3" memberName="sOscGain"
          virtualName="ProKnob" explicitFocusOrder="0" pos="55.657% 76.875% 8.212% 11.25%"
          tooltip="Synth Gain" bkgcol="0" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Div Threshold" id="835be6a95912d3cf" memberName="sThresh"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="0% 123.529% 100% 5.312%"
          posRelativeX="e15284b871cb9580" posRelativeY="e15284b871cb9580"
          posRelativeW="e15284b871cb9580" tooltip="Div Threshold" bkgcol="ff"
          min="0" max="100" int="0.1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Detune" id="cc4dac9a4a740ea3" memberName="sFreq1" virtualName="ProKnob"
          explicitFocusOrder="0" pos="4.015% 25.312% 5.657% 10.312%" tooltip="Detune"
          rotarysliderfill="e3000000" rotaryslideroutline="66ffffff" min="-99"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Ring Modulation" id="d43d8133b340635a" memberName="sRingMod"
          virtualName="ProKnob" explicitFocusOrder="0" pos="15.511% 61.562% 5.657% 9.688%"
          tooltip="Ring Modulation" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Attack" id="6a2e40edea06a000" memberName="sFAtt"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="68.066% 48.75% 4.562% 100%"
          posRelativeH="98f08232c4ccc1db" tooltip="Filter Env Attack" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Decay" id="2375d21ea14c41f8" memberName="sFDec"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="73.175% 0% 100% 100%"
          posRelativeY="6a2e40edea06a000" posRelativeW="6a2e40edea06a000"
          posRelativeH="6a2e40edea06a000" tooltip="Filter Env Decay" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Sustain" id="cc2b4987ae45a26e" memberName="sFSus"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="78.467% 0% 100% 100%"
          posRelativeY="2375d21ea14c41f8" posRelativeW="2375d21ea14c41f8"
          posRelativeH="2375d21ea14c41f8" tooltip="Filter Env Sustain"
          min="0" max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Release" id="e91c901bfee60a50" memberName="sFRel"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="83.942% 0% 100% 100%"
          posRelativeY="cc2b4987ae45a26e" posRelativeW="cc2b4987ae45a26e"
          posRelativeH="cc2b4987ae45a26e" tooltip="Filter Env Release"
          min="0" max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <JUCERCOMP name="" id="7c27853901fd2a9d" memberName="audioled" virtualName=""
             explicitFocusOrder="0" pos="37.591% 28.438% 2.19% 2.812%" sourceFile="led.cpp"
             constructorParams=""/>
  <SLIDER name="Osc Separation" id="75c6111f14c56688" memberName="sStereo"
          virtualName="ProKnob" explicitFocusOrder="0" pos="9.672% 0% 5.657% 10.312%"
          posRelativeY="cc4dac9a4a740ea3" tooltip="Osc Separation" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="-99" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc Mix" id="8adc900b8b11e514" memberName="sOscMix" virtualName="ProKnob"
          explicitFocusOrder="0" pos="15.693% 0% 5.657% 10.312%" posRelativeY="cc4dac9a4a740ea3"
          tooltip="Osc Mix" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="-99" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <JUCERCOMP name="" id="1645d1f6e255ba56" memberName="clipled" virtualName=""
             explicitFocusOrder="0" pos="88.686% 86.562% 2.19% 2.812%" sourceFile="led.cpp"
             constructorParams=""/>
  <TEXTBUTTON name="Polyphony" id="252f162c02937bbc" memberName="sMode" virtualName=""
              explicitFocusOrder="0" pos="38.686% 17.5% 6.387% 4.688%" tooltip="Mono Mode"
              bgColOff="af8f8f9e" bgColOn="c9faff44" buttonText="Mono" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Stereo" id="cbcc3c037ba6f0a6" memberName="sStereo2" virtualName="ProSliderH"
          explicitFocusOrder="0" pos="66.788% 141.176% 16.971% 5.312%"
          posRelativeY="20c26f0e7b36dd30" tooltip="Stereo" min="0" max="100"
          int="0.1" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="M Factor" id="46d8858795d0c45" memberName="sM1" virtualName="ProSliderH"
          explicitFocusOrder="0" pos="0% 135.294% 100% 100%" posRelativeX="67291950d5f1ae5c"
          posRelativeY="67291950d5f1ae5c" posRelativeW="67291950d5f1ae5c"
          posRelativeH="67291950d5f1ae5c" tooltip="M Factor" min="0" max="100"
          int="0.001" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Phase Mod" id="1d749f6879590691" memberName="sPhMod" virtualName="ProKnob"
          explicitFocusOrder="0" pos="27.007% 0% 100% 100%" posRelativeY="8adc900b8b11e514"
          posRelativeW="8adc900b8b11e514" posRelativeH="8adc900b8b11e514"
          tooltip="Phase Mod" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Divider Mix" id="2e215e4f2ed1f863" memberName="sDivMix"
          virtualName="ProKnob" explicitFocusOrder="0" pos="58.759% 37.812% 5.657% 10.312%"
          tooltip="Divider Mix" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="587aa06a37f3589c" memberName="info" virtualName=""
         explicitFocusOrder="0" pos="4.38% 10.625% 22.263% 3.125%" textCol="a6ffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="33"/>
  <JUCERCOMP name="" id="f4ad4dc211f498e4" memberName="pizButton" virtualName=""
             explicitFocusOrder="0" pos="41.423% 23.75% 16.788% 13.438%" sourceFile="PizButton.cpp"
             constructorParams=""/>
  <SLIDER name="Filter Key Follow" id="dbd7d6b2284ee89b" memberName="sFKeyFollow"
          virtualName="" explicitFocusOrder="0" pos="27.92% 65.625% 5.657% 6.875%"
          tooltip="Filter Key Follow" rotarysliderfill="0" rotaryslideroutline="ffffff"
          textboxtext="ffffffff" min="0" max="99" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="next" id="2401d40242c71fcc" memberName="nextButton" virtualName=""
              explicitFocusOrder="0" pos="57.664% 13.438% 3.102% 4.062%" tooltip="Next Preset"
              bgColOff="478f8f9e" bgColOn="c9faff44" textCol="ffffffff" buttonText="&gt;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="previous" id="b18b281b256254b0" memberName="prevButton"
              virtualName="" explicitFocusOrder="0" pos="53.65% 13.438% 3.102% 4.062%"
              tooltip="Previous Preset" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="ffffffff" buttonText="&lt;" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Reset" id="d0d8a64702e81217" memberName="sReset" virtualName=""
              explicitFocusOrder="0" pos="88.321% 18.125% 6.752% 4.062%" tooltip="Reset all parameters"
              bgColOff="478f8f9e" bgColOn="c9faff44" textCol="c5ffffff" buttonText="Reset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Harshness" id="7b535f3a8eb8d3ed" memberName="sOPLP" virtualName=""
          explicitFocusOrder="0" pos="3.102% 65.625% 5.657% 6.875%" tooltip="Harshness"
          rotarysliderfill="0" rotaryslideroutline="ffffff" textboxtext="ffffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Post Divider Mix" id="1af37757abf958e" memberName="sPostDivMix"
          virtualName="ProKnob" explicitFocusOrder="0" pos="58.759% 48.438% 5.657% 10.312%"
          tooltip="Post Divider Mix" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Save Patch" id="c423ebfec56b25d4" memberName="sSavePatch"
              virtualName="" explicitFocusOrder="0" pos="53.65% 18.125% 9.672% 4.062%"
              tooltip="Save patch" bgColOff="478f8f9e" bgColOn="c9faff44" textCol="c5ffffff"
              buttonText="Save patch" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Save Bank" id="acdc62fb20065374" memberName="sSavePatch2"
              virtualName="" explicitFocusOrder="0" pos="64.234% 18.125% 9.672% 4.062%"
              tooltip="Save bank" bgColOff="478f8f9e" bgColOn="c9faff44" textCol="c5ffffff"
              buttonText="Save bank" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="512bea4aaf67435" memberName="info3" virtualName=""
         explicitFocusOrder="0" pos="61.131% 13.75% 5.109% 4.062%" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="128:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="94e887826c3824bb" memberName="info2" virtualName=""
         explicitFocusOrder="0" pos="65.146% 13.75% 20.255% 4.062%" tooltip="Rename Patch"
         textCol="ffffffff" edTextCol="ffffff9f" edBkgCol="0" hiliteCol="7bffff00"
         labelText="patch name" editableSingleClick="0" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Load Patch" id="eaec04d5a8153bf0" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="88.321% 13.438% 6.752% 4.062%"
              tooltip="Load bank/patch" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="c5ffffff" buttonText="Load" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="Filter Mode" id="7435cbde124ae4de" memberName="filterModeBox"
            virtualName="" explicitFocusOrder="0" pos="14.051% 48.75% 8.577% 100%"
            posRelativeH="bc6289c05f44be1a" tooltip="Filter Mode" editable="0"
            layout="33" items="Off&#10;Low24&#10;Low&#10;Band&#10;Notch&#10;High&#10;Formant" textWhenNonSelected="Formant"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc 1 Octave" id="a31407cc9477bc24" memberName="sOctave1"
          virtualName="" explicitFocusOrder="0" pos="3.285% 17.5% 5.657% 6.875%"
          tooltip="Osc 1 Octave" rotarysliderfill="0" rotaryslideroutline="ffffff"
          textboxtext="ffffffff" min="-12" max="6" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Waveform1" id="bc6289c05f44be1a" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="8.029% 18.75% 9.854% 3.75%"
            tooltip="Waveform1" editable="0" layout="33" items="RampUp&#10;RampDown&#10;Square&#10;Triangle&#10;Sine&#10;Minkowski&#10;Weierstrass&#10;AutoAlias&#10;Eight&#10;OddEight&#10;Computer&#10;Funnel&#10;Grate&#10;Noise&#10;Sine+&#10;Narrow&#10;Octaves&#10;Ughhh&#10;Drawable1&#10;Drawable2"
            textWhenNonSelected="???????" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc 2 Octave" id="16bb23adebfca409" memberName="sOctave2"
          virtualName="" explicitFocusOrder="0" pos="27.92% 17.5% 5.657% 6.875%"
          tooltip="Osc 2 Octave" rotarysliderfill="0" rotaryslideroutline="ffffff"
          textboxtext="ffffffff" min="-12" max="6" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Waveform2" id="52decd564aac4c47" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="18.796% 0% 100% 100%"
            posRelativeY="bc6289c05f44be1a" posRelativeW="bc6289c05f44be1a"
            posRelativeH="bc6289c05f44be1a" tooltip="Waveform2" editable="0"
            layout="33" items="RampUp&#10;RampDown&#10;Square&#10;Triangle&#10;Sine&#10;Minkowski&#10;Weierstrass&#10;AutoAlias&#10;Eight&#10;OddEight&#10;Computer&#10;Funnel&#10;Grate&#10;Noise&#10;Sine+&#10;Narrow&#10;Octaves&#10;Ughhh&#10;Drawable1&#10;Drawable2"
            textWhenNonSelected="???????" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc 2 Harmonic" id="1967b716efd6939b" memberName="sOctave"
          virtualName="ProKnob" explicitFocusOrder="0" pos="21.35% 0% 5.657% 10.312%"
          posRelativeY="cc4dac9a4a740ea3" tooltip="Osc 2 Harmonic" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" min="0" max="12" int="1" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="UseProgCh" id="32af558b7d0377d0" memberName="sUseProgCh"
              virtualName="" explicitFocusOrder="0" pos="36.861% 12.5% 9.489% 4.062%"
              tooltip="Use Program Change" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="Use ProgCh" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="M Effect Mix" id="34b1a1b115a46f1a" memberName="sM1Mix"
          virtualName="ProKnob" explicitFocusOrder="0" pos="104.202% -47.059% 4.927% 10.312%"
          posRelativeX="67291950d5f1ae5c" posRelativeY="46d8858795d0c45"
          tooltip="M Effect Mix" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Randomize" id="b33dbbb86b9227ef" memberName="randomButton"
              virtualName="" explicitFocusOrder="0" pos="75.182% 18.125% 12.226% 4.062%"
              tooltip="Randomize all parameters" bgColOff="478f8f9e" bgColOn="c9faff44"
              textCol="c5ffffff" buttonText="Randomize" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Limiter" id="5968edc0e0163352" memberName="limiterButton"
              virtualName="" explicitFocusOrder="0" pos="85.949% 73.125% 7.664% 3.75%"
              tooltip="Limiter" bgColOff="af8f8f9e" bgColOn="c9faff44" textCol="ff000000"
              buttonText="Limiter" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Envelope Curve" id="1f96516861dcce44" memberName="sExp"
              virtualName="" explicitFocusOrder="0" pos="89.964% 26.562% 3.832% 4.688%"
              tooltip="Percussive Envelope" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="P" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Filter Envelope Curve" id="2c92bb97805a786b" memberName="sFExp"
              virtualName="" explicitFocusOrder="0" pos="89.964% 49.688% 3.832% 4.688%"
              tooltip="Percussive Envelope" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="P" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="1f5c15f3cb510b21" memberName="midiled" virtualName=""
             explicitFocusOrder="0" pos="60.401% 28.438% 2.19% 2.812%" sourceFile="led.cpp"
             constructorParams=""/>
  <TEXTBUTTON name="Save Snapshot" id="95c28f5c22f1a6ea" memberName="saveSnapshotButtonB"
              virtualName="" explicitFocusOrder="0" pos="93.431% 0% 3.102% 4.062%"
              tooltip="Save Snapshot B" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="S" connectedEdges="2" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Recall Snapshot" id="cce0eb45b4f9a834" memberName="recallSnapshotButtonB"
              virtualName="" explicitFocusOrder="0" pos="93.431% 4.688% 3.102% 4.062%"
              tooltip="Recall Snapshot B" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="R" connectedEdges="2" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="Morph" id="b61f633600f68112" memberName="sMorph" virtualName=""
          explicitFocusOrder="0" pos="6.752% -1.875% 86.496% 5.312%" tooltip="Morph"
          thumbcol="20ababab" trackcol="ffffff" rotarysliderfill="360000ff"
          min="-100" max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Save Snapshot" id="6228cbbb6bb2b857" memberName="saveSnapshotButtonA"
              virtualName="" explicitFocusOrder="0" pos="3.65% 0% 3.102% 4.062%"
              tooltip="Save Snapshot A" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="S" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Recall Snapshot" id="7208f7c435615e0f" memberName="recallSnapshotButtonA"
              virtualName="" explicitFocusOrder="0" pos="3.65% 4.688% 3.102% 4.062%"
              tooltip="Recall Snapshot A" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="R" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Pitch Shift Input" id="b8dbd9871b5f3e25" memberName="sPitchShift"
              virtualName="" explicitFocusOrder="0" pos="35.584% 101.875% 8.394% 4.062%"
              tooltip="Pitch Shift Input" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="PitchShift" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="872770bb2d2498d9" memberName="resizer" virtualName=""
                    explicitFocusOrder="0" pos="16R 16R 16 16" class="ResizableCornerComponent"
                    params="this, &amp;resizeLimits"/>
  <COMBOBOX name="Program Select" id="42cfeb77ae238add" memberName="patchBox"
            virtualName="PizComboBox" explicitFocusOrder="0" pos="85.401% 13.75% 2.19% 3.75%"
            tooltip="Select Patch" editable="0" layout="33" items="dummy1&#10;dummy2"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="Main Volume" id="7cfebe5576414d20" memberName="sVolume"
          virtualName="ProKnob" explicitFocusOrder="0" pos="84.672% 75.938% 10.219% 14.688%"
          tooltip="Main Volume" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="new button" id="fff416079d82e417" memberName="toggleButton"
              virtualName="" explicitFocusOrder="0" pos="0.547% 94.688% 2.555% 3.75%"
              tooltip="Grab QWERTY" bgColOff="30bbbbff" buttonText="&gt;" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Decoupled 1" id="ddb0b6c84b952153" memberName="decoupled1Button"
              virtualName="" explicitFocusOrder="0" pos="4.197% 15.937% 4.015% 2.5%"
              tooltip="Decouple Osc 1" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Decoupled 2" id="ccd13949dac93852" memberName="decoupled2Button"
              virtualName="" explicitFocusOrder="0" pos="28.65% 15.937% 4.015% 2.5%"
              tooltip="Decouple Osc 2" bgColOff="af8f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="Decoupled2" id="64c10a9d93fdd086" memberName="sDecoupled2"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="18.431% -9.688% 22.08% 5.312%"
          tooltip="Decouple Osc 2" thumbcol="ff000000" trackcol="5b4a3333"
          textboxtext="f6000000" min="-1" max="127" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Decoupled1" id="ce1a83afc44e73ff" memberName="sDecoupled1"
          virtualName="ProSliderH" explicitFocusOrder="0" pos="-5.292% -10.625% 22.08% 5.312%"
          tooltip="Decouple Osc 1" thumbcol="ff000000" trackcol="5b4a3333"
          textboxtext="f4000000" min="-1" max="127" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Glide" id="55cb77335c4065c3" memberName="sGlide" virtualName="ProKnob"
          explicitFocusOrder="0" pos="48.175% 16.562% 4.745% 6.25%" tooltip="Glide"
          rotarysliderfill="e3000000" rotaryslideroutline="66ffffff" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Retrigger" id="83132ba207c7d0fd" memberName="sRetrig" virtualName=""
              explicitFocusOrder="0" pos="45.255% 17.5% 3.102% 4.688%" tooltip="Mono Retrigger"
              bgColOff="af8f8f9e" bgColOn="c9faff44" buttonText="R" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Page 2" id="b8407028ae51a80c" memberName="page2" virtualName="BlankPage"
                    explicitFocusOrder="0" pos="67.153% 25.312% 28.467% 47.5%" class="Component"
                    params=""/>
  <SLIDER name="LFO 1 Rate" id="cbe88f88768da97e" memberName="sLFO1Rate"
          virtualName="ProKnob" explicitFocusOrder="0" pos="69.526% 49.062% 8.212% 11.25%"
          tooltip="LFO 1 Rate" bkgcol="0" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO 1 Amount" id="d66d5acb8aff0f06" memberName="sLFO1Amount"
          virtualName="ProKnob" explicitFocusOrder="0" pos="78.467% 49.062% 6.569% 11.25%"
          tooltip="LFO 1 Amount" bkgcol="0" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" textboxoutline="b2888888" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env 3 Amount" id="9449622b4e812dcd" memberName="sEnv3Amount"
          virtualName="ProKnob" explicitFocusOrder="0" pos="89.051% 30.938% 5.657% 9.375%"
          tooltip="Env 3 Amount" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          min="0" max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env 3 Release" id="a529b513e79ea5bd" memberName="sRel3"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="83.942% 0% 100% 100%"
          posRelativeY="7e37ae1d9e9c0614" posRelativeW="7e37ae1d9e9c0614"
          posRelativeH="7e37ae1d9e9c0614" tooltip="Env 3 Release" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env 3 Systain" id="df296f0b2162c3c0" memberName="sSus3"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="78.467% 0% 100% 100%"
          posRelativeY="45d621746fcf224f" posRelativeW="45d621746fcf224f"
          posRelativeH="45d621746fcf224f" tooltip="Env 3 Sustain" min="0"
          max="100" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env 3 Decay" id="4bb0572b00618e" memberName="sDec3" virtualName="ProSliderV"
          explicitFocusOrder="0" pos="73.175% 0% 100% 100%" posRelativeY="98f08232c4ccc1db"
          posRelativeW="98f08232c4ccc1db" posRelativeH="98f08232c4ccc1db"
          tooltip="Env 3 Decay" min="0" max="100" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env 3 Attack" id="7286d248536b6035" memberName="sAtt3"
          virtualName="ProSliderV" explicitFocusOrder="0" pos="68.066% 25.625% 4.562% 21.25%"
          tooltip="Env 3 Attack" min="0" max="100" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Page Switch" id="e8aec97bea8deeea" memberName="sPage" virtualName=""
              explicitFocusOrder="0" pos="69.526% 23.125% 6.569% 3.438%" tooltip="Switch Page"
              bgColOff="af8f8f9e" bgColOn="c9faff44" buttonText="page" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Env 3 Destination" id="d7aafd23f8e06c7e" memberName="Env3DestBox"
              virtualName="" explicitFocusOrder="0" pos="88.869% 41.562% 6.569% 3.438%"
              tooltip="Env 3 Destination" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="dest" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="LFO 2 Rate" id="f44cac660783f700" memberName="sLFO2Rate"
          virtualName="ProKnob" explicitFocusOrder="0" pos="69.526% 60.625% 8.212% 11.25%"
          tooltip="LFO 2 Rate" bkgcol="0" rotarysliderfill="e3000000" rotaryslideroutline="66ffffff"
          textboxoutline="b2888888" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO 2 Amount" id="5840c50cadb1ee14" memberName="sLFO2Amount"
          virtualName="ProKnob" explicitFocusOrder="0" pos="78.467% 60.625% 6.569% 11.25%"
          tooltip="LFO 2 Amount" bkgcol="0" rotarysliderfill="e3000000"
          rotaryslideroutline="66ffffff" textboxoutline="b2888888" min="0"
          max="99" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="LFOWaveform1" id="fe0223ccd0b45e95" memberName="LFO1WaveBox"
            virtualName="" explicitFocusOrder="0" pos="85.219% 50.313% 9.854% 3.75%"
            tooltip="LFO 1 Waveform" editable="0" layout="33" items="RampUp&#10;RampDown&#10;Square&#10;Triangle&#10;Sine&#10;Minkowski&#10;Weierstrass&#10;AutoAlias&#10;Eight&#10;OddEight&#10;Computer&#10;Funnel&#10;Grate&#10;Noise&#10;Sine+&#10;Narrow&#10;Octaves&#10;Ughhh&#10;Drawable1&#10;Drawable2"
            textWhenNonSelected="???????" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="LFO2Waveform" id="c0065cd4066d8df9" memberName="LFO2WaveBox"
            virtualName="" explicitFocusOrder="0" pos="85.219% 61.875% 9.854% 3.75%"
            tooltip="LFO 2 Waveform" editable="0" layout="33" items="RampUp&#10;RampDown&#10;Square&#10;Triangle&#10;Sine&#10;Minkowski&#10;Weierstrass&#10;AutoAlias&#10;Eight&#10;OddEight&#10;Computer&#10;Funnel&#10;Grate&#10;Noise&#10;Sine+&#10;Narrow&#10;Octaves&#10;Ughhh&#10;Drawable1&#10;Drawable2"
            textWhenNonSelected="???????" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="menu" id="6e16f6400d126156" memberName="menuButton" virtualName=""
              explicitFocusOrder="0" pos="0.547% 1.25% 2.555% 3.75%" tooltip="Main Menu"
              bgColOff="30bbbbff" bgColOn="c9faff44" buttonText="m" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="lfo 1 indicator" id="d175af0580778717" memberName="lfo1indicator"
          virtualName="Indicator" explicitFocusOrder="0" pos="69.161% 49.375% 1.277% 10.938%"
          trackcol="ffffff" textboxtext="0" min="0" max="2" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="LFO 1 Free Running" id="85c17ce3a92015fe" memberName="bLFO1Free"
              virtualName="" explicitFocusOrder="0" pos="85.219% 54.688% 4.927% 3.438%"
              tooltip="LFO 1 Free Running" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="free" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="LFO 2 Free Running" id="bffdc7208952fbc8" memberName="bLFO2Free"
              virtualName="" explicitFocusOrder="0" pos="85.219% 66.25% 4.927% 3.438%"
              tooltip="LFO 2 free running" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="free" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="LFO 1 Destination" id="31552c2401108b48" memberName="LFO1DestBox"
              virtualName="" explicitFocusOrder="0" pos="90.328% 54.688% 4.927% 3.438%"
              tooltip="LFO 1 Destination" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="dest" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="LFO 2 Destination" id="f4c118887a73c5d0" memberName="LFO2DestBox"
              virtualName="" explicitFocusOrder="0" pos="90.328% 66.25% 4.927% 3.438%"
              tooltip="LFO 2 Destination" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="dest" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="lfo 2 indicator" id="a0c783cd289b7a91" memberName="lfo2indicator"
          virtualName="Indicator" explicitFocusOrder="0" pos="69.161% 60.938% 1.277% 10.938%"
          trackcol="ffffff" textboxtext="0" min="0" max="2" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <JUCERCOMP name="" id="44c6a61eea081d43" memberName="aboutbox" virtualName=""
             explicitFocusOrder="0" pos="49.909%c 13.438% 47.263% 49.062%"
             sourceFile="AboutBoxPro.cpp" constructorParams=""/>
  <SLIDER name="env 3 indicator" id="7c873389befadb24" memberName="env3indicator"
          virtualName="Indicator" explicitFocusOrder="0" pos="88.139% 30% 1.277% 10.938%"
          trackcol="ffffff" textboxtext="0" min="0" max="2" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="demo" id="edd64e98066a5be2" memberName="demoButton" virtualName=""
              explicitFocusOrder="0" pos="36.131% 88.75% 27.372% 10%" tooltip="buy me!!!!!!!!!"
              bgColOff="95bbbbff" buttonText="DEMO VERSION" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Auto Randomizer" id="9dfacd0ea5bb20b5" memberName="bAuto"
              virtualName="" explicitFocusOrder="0" pos="81.022% 21.875% 6.569% 3.438%"
              tooltip="Auto Randomizer" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="auto" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Draw Waveform" id="e01382612266d397" memberName="bDraw"
              virtualName="" explicitFocusOrder="0" pos="26.825% 10% 4.745% 3.438%"
              tooltip="Draw Waveform" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="draw1" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Draw Waveform" id="3c6da92b14a411aa" memberName="bDraw2"
              virtualName="" explicitFocusOrder="0" pos="31.752% 10% 4.745% 3.438%"
              tooltip="Draw Waveform" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="draw2" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="9befc0bfbc8aa204" memberName="waveDrawer" virtualName=""
             explicitFocusOrder="0" pos="50%c 40.312%c 46.715% 53.75%" sourceFile="WaveDrawWindow.cpp"
             constructorParams="this,ownerFilter"/>
  <TEXTBUTTON name="LFO 1 Tempo Sync" id="71477f0a1c25990a" memberName="sync1"
              virtualName="" explicitFocusOrder="0" pos="85.219% 57.812% 4.927% 3.438%"
              tooltip="LFO 1 Tempo Sync" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="sync" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="LFO 2 Tempo Sync" id="635921cbcd92b317" memberName="sync2"
              virtualName="" explicitFocusOrder="0" pos="85.219% 69.375% 4.927% 3.438%"
              tooltip="LFO 2 Tempo Sync" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="sync" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Envelope 3 Curve" id="18865019ea1d66ab" memberName="sExp3"
              virtualName="" explicitFocusOrder="0" pos="89.964% 26.562% 3.832% 4.688%"
              tooltip="Percussive Envelope" bgColOff="af8f8f9e" bgColOn="c9faff44"
              buttonText="P" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Interpolate 1" id="6e7a2d6fbb871a1a" memberName="interpolate1"
              virtualName="" explicitFocusOrder="0" pos="16.058% 15.937% 2.007% 2.812%"
              tooltip="Interpolate Osc 1" bgColOff="808f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="i" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Interpolate 2" id="5ff5a7f0ab0661" memberName="interpolate2"
              virtualName="" explicitFocusOrder="0" pos="18.613% 15.937% 2.007% 2.812%"
              tooltip="Interpolate Osc 2" bgColOff="808f8f9e" bgColOn="c9faff44"
              textCol="ff000000" buttonText="i" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

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

// JUCER_RESOURCE: wood1_png, 42724, "../../../../My Documents/My Pictures/wood1.png"
static const unsigned char resource_MrAlias2Editor_wood1_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,44,0,0,1,244,8,6,0,0,0,70,158,207,247,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,
6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,10,30,17,4,50,121,144,81,44,0,0,0,25,116,69,88,116,67,111,109,109,101,
110,116,0,67,114,101,97,116,101,100,32,119,105,116,104,32,71,73,77,80,87,129,14,23,0,0,32,0,73,68,65,84,120,218,84,188,91,143,36,73,146,165,247,169,138,170,154,154,187,135,123,70,94,42,235,178,53,219,
51,187,51,88,114,23,92,144,15,252,197,252,25,4,193,7,114,65,240,130,217,203,144,211,91,51,213,93,221,93,85,157,89,121,117,15,119,55,51,85,21,85,62,168,133,71,87,2,137,66,33,35,220,205,244,34,114,228,156,
35,98,254,191,255,227,127,106,74,98,27,54,56,235,161,42,74,5,44,180,254,223,166,138,86,67,109,5,76,5,109,224,5,84,241,10,57,37,26,25,196,66,205,84,10,210,4,48,164,57,49,95,19,24,203,54,58,60,150,121,158,
169,173,224,49,140,65,176,166,97,154,210,76,197,141,130,181,5,169,32,205,160,53,81,85,241,34,140,49,226,162,29,65,2,2,80,45,154,180,63,172,181,216,32,128,7,169,160,133,154,193,82,168,40,154,21,95,42,90,
27,214,8,88,3,1,168,6,138,165,229,76,77,150,57,41,90,10,52,184,228,68,240,129,229,178,80,117,97,177,112,185,40,37,37,178,46,180,57,33,222,128,81,212,42,146,251,162,64,67,188,97,12,1,247,108,127,15,128,
53,25,104,176,217,80,171,50,169,66,21,192,98,45,12,177,63,76,81,75,205,153,70,89,119,0,196,1,173,65,173,204,37,161,173,146,52,97,67,98,75,128,80,17,223,240,84,230,57,209,154,97,158,45,181,42,173,41,9,
165,86,64,148,52,37,106,86,166,50,163,21,114,202,52,85,68,64,68,112,135,103,27,16,104,218,152,255,248,191,162,105,33,77,115,255,155,10,214,24,156,23,146,177,24,107,104,179,7,192,121,33,14,1,231,251,255,
151,156,73,41,83,166,5,0,84,89,210,132,170,34,98,80,99,81,91,209,42,212,82,16,173,120,39,136,8,12,32,163,96,229,142,16,2,41,23,114,81,106,173,180,214,48,21,176,21,111,192,29,31,206,136,107,128,225,151,
55,31,209,154,49,214,98,141,16,239,34,67,8,88,107,1,168,181,18,55,91,140,53,120,39,24,107,81,85,82,202,92,146,178,44,133,16,7,198,49,18,156,199,216,138,72,35,142,174,63,152,105,208,28,154,10,89,149,86,
43,185,40,75,74,228,148,209,218,104,173,18,0,113,2,64,8,142,65,4,239,44,198,130,251,229,231,247,228,58,225,125,224,63,254,253,63,82,178,18,6,71,28,2,227,216,31,216,251,254,203,0,41,89,140,49,0,180,214,
168,181,254,234,133,182,219,145,113,94,216,142,174,47,244,122,81,107,107,0,120,227,200,170,104,209,245,40,90,140,24,172,181,136,49,12,34,56,17,180,182,219,3,7,75,63,174,84,28,14,124,11,4,25,240,126,192,
143,141,166,149,185,20,174,199,83,255,80,107,9,193,33,226,136,195,136,170,50,47,137,148,242,250,161,190,175,32,80,88,184,204,194,251,79,80,214,159,91,230,133,57,37,52,23,134,56,208,90,35,231,254,192,222,
11,222,57,156,23,68,28,65,193,174,11,242,248,146,37,207,104,82,230,41,225,238,238,239,81,20,1,94,127,245,146,218,10,154,149,178,110,245,237,188,134,192,48,244,227,145,114,198,121,195,50,27,68,44,206,59,
196,88,180,85,160,161,173,111,247,227,10,121,39,12,101,160,213,138,177,22,239,4,231,29,126,125,201,148,11,41,101,114,201,148,76,255,60,17,194,250,224,100,65,209,190,194,135,237,14,173,13,77,149,141,236,
40,45,49,238,34,98,43,151,235,149,105,153,104,181,34,162,208,18,206,141,56,23,216,109,99,191,132,181,245,45,94,87,44,181,132,23,193,136,161,228,190,74,94,28,46,120,196,26,162,243,168,86,84,149,186,110,
187,182,138,102,165,181,6,38,227,130,199,187,167,99,88,107,236,191,147,10,206,154,128,149,134,31,149,175,191,125,13,232,122,145,10,113,19,17,15,97,253,229,218,42,86,26,115,74,156,78,23,82,46,4,239,120,
113,216,32,34,212,214,40,233,49,72,40,57,87,188,23,134,33,16,195,6,241,130,152,190,242,185,40,173,54,106,171,20,237,17,161,20,197,17,251,101,92,159,161,214,138,45,14,15,32,13,151,166,5,19,12,226,45,96,
153,166,133,243,245,74,206,133,24,132,93,136,132,48,96,108,163,213,74,90,46,28,54,91,238,119,59,230,57,173,97,75,176,214,244,179,237,250,153,55,166,135,59,47,66,8,14,154,160,218,144,193,161,170,235,2,
40,90,45,78,4,9,210,35,207,36,183,123,243,120,145,203,116,165,182,66,171,13,55,233,12,19,48,89,254,223,127,252,30,177,134,101,78,104,83,156,19,236,27,139,230,190,108,46,56,202,50,49,12,1,17,65,181,159,
117,99,109,63,6,198,16,227,72,8,158,24,20,241,66,115,144,83,165,105,35,149,204,156,103,114,46,92,167,153,105,90,110,47,188,219,142,125,39,60,248,224,216,140,177,127,7,202,57,125,164,105,5,107,113,163,
248,219,118,111,199,129,33,6,56,244,172,50,4,33,23,101,186,246,100,48,196,192,160,134,211,233,202,233,124,1,4,103,61,90,43,179,42,77,27,147,60,220,34,198,227,74,90,233,151,173,213,10,1,170,246,120,155,
215,127,151,193,128,86,40,149,99,89,48,201,240,176,44,104,173,44,115,226,252,240,9,67,35,6,143,187,219,222,65,232,241,240,127,252,183,127,119,187,68,94,4,9,14,90,91,211,105,69,68,16,19,184,76,11,173,85,
134,33,16,188,39,229,140,22,197,138,229,124,58,246,204,166,173,95,172,150,177,198,222,22,197,59,139,136,185,189,64,63,203,117,77,86,150,139,4,172,237,209,65,179,146,98,97,231,247,136,8,49,10,238,248,233,
35,86,132,138,242,253,223,255,3,170,202,178,36,106,181,196,24,122,166,19,131,49,22,107,13,126,61,155,0,102,61,183,143,47,24,135,128,113,32,206,17,188,35,4,195,16,118,136,135,148,10,203,156,144,2,70,161,
31,81,139,51,130,143,61,69,135,224,217,17,250,165,204,74,147,138,49,22,191,219,244,23,206,138,67,26,73,215,171,141,246,21,75,133,148,102,150,101,66,92,192,173,151,202,24,139,234,116,91,1,179,174,220,227,
246,167,148,161,72,207,94,214,16,7,97,179,237,73,229,122,153,56,157,79,180,201,244,48,186,102,186,97,8,236,247,91,14,251,29,219,205,200,184,15,204,115,98,154,102,90,107,4,231,24,72,104,41,76,41,99,244,
151,255,179,61,126,169,253,211,255,5,198,160,75,34,107,191,225,253,224,23,82,158,201,37,225,137,212,53,41,220,210,117,233,171,55,47,11,83,78,196,16,48,13,74,73,136,181,104,173,232,146,88,210,194,162,220,
110,127,74,5,85,197,90,131,56,33,120,207,33,127,226,211,231,19,203,156,158,226,244,245,4,70,160,41,238,195,207,159,112,209,34,206,113,254,233,109,223,54,17,66,136,183,72,144,218,130,49,141,16,12,77,214,
24,91,158,178,153,177,22,17,203,225,176,97,75,196,137,80,84,145,26,25,162,32,78,250,106,97,96,141,233,186,226,16,45,186,198,225,126,17,47,245,191,197,167,178,62,67,199,29,229,225,72,174,13,157,23,220,
167,143,159,104,166,191,201,127,252,15,127,143,53,141,224,7,98,220,96,140,233,171,151,231,126,30,163,227,124,185,210,244,215,160,231,6,82,66,207,98,181,245,11,71,173,191,2,78,33,248,142,226,196,224,69,
24,98,96,51,70,130,119,24,99,105,173,114,26,250,239,75,19,108,178,212,86,81,78,72,180,12,91,193,237,15,119,125,149,164,242,55,191,249,106,205,80,143,33,73,8,193,18,154,208,106,166,85,197,123,75,182,138,
173,16,124,95,189,170,253,193,250,42,111,111,233,182,214,6,90,89,150,105,197,37,150,172,149,50,21,46,83,143,199,183,136,176,102,182,243,37,33,214,116,176,190,238,198,241,227,59,164,65,51,224,238,158,239,
208,148,81,237,171,52,142,59,82,202,212,106,217,140,3,155,77,68,141,82,210,76,86,229,56,95,59,82,203,185,159,113,47,200,122,249,30,177,197,40,174,135,41,49,104,78,76,103,200,67,232,103,59,244,227,177,
75,25,85,197,24,75,240,142,86,123,98,25,166,227,175,238,135,53,134,203,238,74,41,153,154,27,46,134,128,134,1,74,225,219,111,95,114,58,206,4,239,136,195,134,187,221,134,24,3,153,30,53,26,202,151,195,23,
148,146,127,5,15,85,27,115,90,88,230,68,8,254,22,85,200,74,213,198,117,123,161,182,70,116,14,164,167,98,109,29,0,149,245,115,114,46,204,75,34,190,240,88,107,110,73,37,120,207,254,149,103,46,189,116,114,
223,255,241,123,188,56,6,231,249,211,247,127,98,28,182,12,222,1,66,109,149,15,31,149,75,186,144,210,66,69,41,43,18,147,53,46,63,102,181,57,37,174,231,137,193,121,130,239,224,61,186,53,150,199,177,191,
156,19,170,54,124,232,96,102,94,18,173,22,140,53,132,16,25,55,149,73,238,25,198,200,70,58,182,24,199,129,250,240,145,41,77,156,83,194,181,73,185,48,241,64,229,31,127,251,251,158,42,109,32,14,1,145,128,
170,50,165,137,172,9,17,208,224,8,222,227,253,35,118,8,236,118,91,188,8,41,23,230,75,79,227,75,90,72,169,48,88,161,161,204,115,98,78,137,253,110,115,139,62,167,243,149,148,50,219,49,178,93,177,68,217,
126,102,24,2,173,85,170,54,196,9,215,143,111,169,173,95,98,247,229,95,127,67,90,18,121,46,252,171,191,253,107,0,198,113,203,214,133,167,56,171,48,149,76,170,202,249,122,38,231,130,106,237,171,55,4,4,75,
85,112,214,227,247,125,117,71,109,88,49,56,7,130,101,154,102,30,206,87,220,24,56,95,39,114,203,216,237,142,184,83,66,8,24,239,57,231,204,203,31,255,105,141,237,11,101,158,40,64,250,243,159,58,31,50,45,
184,65,132,97,28,177,35,220,255,251,191,229,116,185,18,164,35,126,81,131,174,229,145,117,130,218,94,211,165,148,201,185,80,138,174,81,165,220,128,78,170,202,184,137,140,99,36,58,131,216,94,179,53,109,
24,205,28,231,194,146,22,68,132,77,116,88,99,58,142,206,133,57,37,166,227,107,82,202,136,38,70,109,136,49,164,251,47,192,38,114,86,220,199,159,223,96,189,65,156,227,227,239,126,224,243,117,194,214,126,
33,210,212,57,32,25,3,33,6,172,88,238,247,175,16,99,48,98,105,90,209,214,240,198,16,66,63,211,209,8,198,130,166,153,203,69,73,105,126,66,109,10,18,61,193,24,118,97,96,227,6,150,50,49,207,137,17,195,179,
237,134,63,106,192,229,66,0,198,184,37,120,71,218,31,32,247,11,238,150,229,140,153,42,5,248,238,159,127,71,8,189,54,211,185,61,213,116,131,199,14,3,213,192,119,255,244,7,198,77,36,56,215,75,154,181,36,
119,235,229,139,49,144,82,97,158,151,78,105,1,214,214,117,39,148,184,38,146,96,58,77,80,114,231,63,204,99,242,25,159,97,173,99,51,68,66,188,144,36,48,189,253,128,120,80,99,112,195,224,40,69,33,245,220,
125,153,230,254,16,128,113,13,111,251,234,154,40,52,211,241,133,243,149,86,151,30,143,151,252,171,10,225,227,39,69,91,197,97,123,201,191,233,52,65,157,149,148,26,182,21,230,57,113,202,51,65,132,253,126,
203,110,23,56,30,143,188,125,119,196,215,31,9,49,16,135,145,218,250,81,250,240,195,31,16,11,173,90,220,184,221,246,173,53,150,127,255,223,253,29,167,249,194,128,167,182,78,250,89,39,72,28,145,176,98,0,
38,170,214,30,17,150,116,195,178,178,86,184,231,235,76,171,13,99,33,172,171,222,106,69,183,224,183,30,153,149,97,16,150,69,192,40,227,46,48,136,163,182,13,115,154,152,116,166,13,149,217,78,76,211,204,
164,149,247,124,196,214,70,74,21,215,170,101,158,21,200,76,201,240,197,235,47,49,218,73,18,1,170,113,29,15,136,37,81,33,15,164,84,240,162,236,54,102,5,245,253,24,181,218,216,236,51,185,40,100,37,175,24,
56,233,140,208,49,195,120,232,229,212,82,50,203,220,97,237,82,20,239,182,188,126,61,226,66,192,26,139,90,58,202,67,121,30,60,103,205,228,84,112,89,13,73,21,154,114,186,44,92,114,47,211,5,139,247,66,240,
14,9,129,42,150,84,21,93,50,243,156,176,98,25,199,129,113,136,20,173,204,57,145,146,18,194,136,160,168,52,108,80,70,20,167,61,113,4,231,136,177,103,194,208,42,119,123,24,28,61,218,20,197,121,207,78,239,
73,84,172,173,12,195,64,179,202,91,43,28,63,158,153,230,9,247,112,156,208,150,169,170,188,251,229,51,182,54,196,123,196,9,74,47,139,220,216,9,148,90,43,136,189,225,215,57,87,142,231,165,87,182,43,253,
100,234,229,233,103,87,132,134,17,74,81,10,202,116,156,16,39,136,181,88,99,136,222,118,138,0,184,92,38,22,127,232,119,168,58,102,99,58,27,101,190,96,188,219,99,204,132,19,15,100,11,70,9,206,119,26,73,
251,45,47,172,152,245,8,102,125,208,84,59,40,55,198,244,149,10,158,16,60,198,154,190,149,250,4,130,140,53,164,214,249,135,91,156,62,62,172,63,111,41,181,215,130,130,185,85,60,90,143,183,207,114,94,8,206,
177,188,251,9,130,193,208,112,207,15,135,21,94,90,94,253,15,255,13,167,135,78,144,52,211,195,85,173,149,73,203,90,18,25,154,213,27,211,83,84,169,173,115,113,181,54,180,85,132,94,30,41,29,216,244,135,237,
97,205,88,139,140,27,176,149,6,144,13,57,87,174,57,209,90,67,107,197,249,207,184,149,124,105,70,72,205,240,126,254,3,110,130,86,11,110,220,239,161,42,149,74,11,145,215,95,245,56,154,74,15,87,98,250,101,
123,228,30,196,117,80,84,178,146,75,190,21,151,203,90,57,75,244,183,200,80,107,187,225,221,199,202,68,231,186,150,254,150,104,4,113,79,229,82,206,153,143,215,239,215,197,152,153,83,161,168,114,185,126,
128,10,226,13,238,114,90,241,103,85,62,124,120,143,27,101,61,99,125,91,196,11,7,55,220,232,37,172,193,86,139,216,6,206,35,226,24,199,120,99,28,223,126,252,68,8,29,34,186,181,78,131,126,227,189,56,234,
181,220,94,64,156,195,218,74,205,157,35,214,18,216,222,253,91,180,244,18,236,241,24,189,146,3,21,133,86,113,63,189,249,17,140,165,170,242,207,223,253,19,138,18,130,239,171,105,44,67,12,236,134,1,177,29,
67,140,99,188,85,200,41,151,91,118,27,66,32,198,192,243,113,67,28,134,206,78,174,12,123,46,157,157,164,1,97,232,117,254,250,167,45,74,213,204,96,13,118,8,168,126,137,9,125,55,93,232,172,40,195,55,92,151,
137,121,206,56,113,118,125,147,138,15,22,193,50,207,137,79,211,76,154,19,214,90,118,161,83,83,178,202,4,117,61,147,218,58,223,230,68,136,49,32,226,24,92,232,161,240,150,52,86,138,106,141,185,129,126,121,
123,125,39,107,57,100,137,33,224,130,193,243,153,6,204,127,81,153,235,187,63,18,69,216,139,193,125,253,47,190,36,229,68,213,202,70,127,131,182,218,209,87,81,130,233,149,65,190,44,43,223,86,169,185,167,
103,179,166,226,162,74,78,185,95,192,92,152,114,37,165,94,6,233,186,3,89,59,149,250,200,79,60,86,19,157,70,0,214,75,11,16,239,244,87,12,63,192,135,31,126,75,116,194,24,3,206,185,151,93,102,210,4,225,27,
134,116,37,4,67,222,70,144,192,104,42,246,48,97,230,51,44,51,111,174,5,231,31,185,179,74,144,167,202,185,67,198,126,7,240,149,57,43,169,21,170,51,168,85,148,70,184,12,136,118,18,123,154,102,180,40,209,
61,49,248,211,202,215,206,154,152,114,47,94,127,25,95,115,39,158,115,112,56,172,3,113,56,59,240,234,245,107,130,84,170,90,22,85,178,130,230,68,89,60,11,22,109,145,145,30,71,173,233,88,215,5,143,24,115,
163,154,58,205,85,81,43,28,156,5,239,176,18,200,170,157,68,49,239,58,199,150,97,187,223,245,140,233,29,78,220,42,15,4,82,171,204,121,70,91,34,171,242,124,172,120,117,4,107,112,199,15,191,64,171,88,3,167,
223,255,150,184,223,66,109,80,250,214,120,47,140,33,48,132,129,54,238,24,229,176,74,7,230,118,139,243,202,158,27,99,8,163,144,102,69,21,172,29,25,101,67,144,113,21,243,132,188,251,242,22,195,3,79,5,233,
35,185,253,144,126,162,214,134,23,11,26,186,2,181,191,3,53,120,181,184,235,155,223,161,90,96,201,124,255,191,253,47,212,221,51,188,46,208,50,14,144,16,176,113,71,29,55,88,55,242,250,95,254,134,113,28,
110,74,143,88,115,147,171,58,247,246,40,214,8,133,196,60,93,64,45,84,33,88,195,146,251,101,21,99,24,199,216,105,130,90,59,217,45,134,23,135,136,182,76,51,157,42,8,193,17,118,207,177,38,0,14,119,119,216,
19,172,128,49,60,251,239,255,29,111,166,76,205,9,155,18,185,117,248,56,21,97,153,148,153,153,252,243,47,157,225,201,74,42,249,150,130,91,237,151,106,210,25,163,218,119,198,9,6,69,167,169,199,89,148,157,
223,17,214,248,30,92,63,6,57,21,154,86,140,88,246,135,17,168,253,204,75,79,92,243,155,223,113,135,39,120,193,217,253,55,52,111,161,42,159,119,223,16,95,198,126,20,208,27,7,54,42,204,185,82,154,197,229,
135,94,33,167,130,36,233,148,211,16,214,176,38,28,167,51,53,37,90,205,56,15,94,26,28,32,21,75,77,153,144,59,213,106,164,210,116,33,173,76,101,213,30,198,166,41,162,52,18,133,82,186,36,241,231,239,190,
39,26,75,192,224,24,239,81,58,159,117,29,95,17,131,5,49,104,19,84,44,190,130,111,153,64,23,169,67,238,144,243,81,170,242,34,140,99,87,148,0,94,62,63,144,139,146,242,42,7,88,16,211,107,191,146,50,243,252,
14,241,114,203,140,251,53,116,61,134,50,210,11,18,133,89,251,239,171,86,2,138,102,112,185,225,6,111,0,79,147,202,203,215,123,158,7,88,212,112,209,134,38,40,53,177,105,150,81,26,129,204,131,17,134,232,
241,193,18,195,35,85,101,86,250,170,240,121,129,193,141,196,184,35,136,235,10,231,26,178,178,83,134,241,239,158,42,101,85,130,49,191,146,24,194,253,196,37,23,124,75,104,205,136,181,4,167,44,215,68,61,
21,92,203,75,207,76,21,116,186,240,112,14,132,96,217,83,81,77,24,41,132,141,3,111,88,84,24,205,221,10,198,193,141,66,201,74,42,157,30,29,5,154,156,17,15,115,86,172,56,14,187,123,140,27,81,21,130,117,44,
199,7,230,180,208,146,226,194,72,136,253,8,146,20,80,102,18,69,21,24,216,196,187,46,55,196,19,119,177,226,94,121,220,241,237,31,186,236,4,188,249,238,63,33,33,222,232,249,214,42,193,121,226,118,64,189,
37,103,69,198,39,96,30,188,199,7,135,56,75,24,251,37,218,183,29,89,97,201,10,20,146,126,64,19,164,106,9,62,48,220,85,66,235,144,179,214,43,169,125,66,176,108,238,7,238,183,27,62,93,3,50,218,27,17,8,224,
182,178,46,136,199,5,187,32,8,130,178,119,137,164,103,150,185,49,157,19,203,82,48,198,225,195,128,90,152,114,195,28,118,93,209,28,194,77,221,44,218,73,63,128,56,42,70,12,119,219,145,113,140,156,166,153,
79,159,30,122,86,171,141,38,153,113,19,185,187,219,224,69,200,75,33,229,190,245,113,8,248,248,37,33,120,134,33,224,86,86,19,115,226,58,39,142,69,113,227,120,191,82,248,224,246,175,112,210,8,75,194,198,
76,156,19,169,245,234,66,236,234,88,177,14,35,22,154,64,115,164,89,89,22,101,78,169,127,248,167,51,0,15,187,129,205,93,164,148,4,100,14,187,190,106,15,231,132,92,149,84,18,186,190,108,154,19,243,210,35,
66,202,239,217,109,71,118,119,219,30,121,172,225,221,239,190,227,124,93,184,92,46,56,29,159,163,169,130,81,150,240,53,120,139,4,216,30,234,90,178,20,148,76,182,202,8,72,61,118,92,204,227,95,8,218,216,
212,94,167,149,211,151,29,187,2,203,101,101,117,198,128,93,171,151,175,183,95,63,138,28,55,26,171,136,162,54,49,207,137,247,20,172,22,150,135,51,203,3,136,24,230,135,51,121,41,157,91,219,236,94,162,173,
160,85,121,222,190,37,37,197,8,120,211,48,182,178,164,11,231,116,37,231,11,106,97,87,15,120,233,15,228,86,200,217,244,166,235,48,15,134,81,30,143,74,66,107,193,89,233,140,198,52,35,215,181,254,91,235,
66,17,203,86,186,95,168,238,26,175,246,186,98,10,189,85,61,59,61,82,201,44,151,130,163,156,160,102,90,105,164,243,27,140,49,232,212,85,77,35,43,212,76,19,180,218,201,20,179,7,213,126,142,125,55,128,116,
11,65,238,194,203,97,102,240,158,166,134,148,61,166,212,206,35,105,195,111,238,24,95,244,75,173,69,185,204,51,105,41,20,99,24,98,32,56,207,217,78,221,174,96,13,161,118,186,108,158,119,160,141,48,84,220,
143,223,255,67,175,231,106,227,237,63,254,239,84,173,92,167,25,180,87,27,113,24,9,97,100,216,111,217,236,70,202,152,186,17,73,149,75,146,155,77,224,177,164,217,238,182,228,97,37,176,9,132,16,41,9,36,56,
54,33,242,192,137,97,8,12,54,96,178,99,154,22,210,146,120,208,133,154,38,236,46,66,236,242,2,128,203,25,73,123,162,152,158,154,255,252,233,119,120,17,84,225,63,127,255,15,132,214,43,218,188,178,231,0,
35,194,151,187,59,246,143,31,178,202,90,33,244,4,62,47,43,131,51,39,144,192,39,85,84,2,102,28,33,142,20,241,168,4,16,97,16,189,213,140,143,2,99,171,21,23,58,115,239,19,92,82,143,28,166,117,201,32,189,
253,39,162,91,205,81,223,254,230,111,32,43,105,73,252,155,191,253,27,28,218,131,245,170,16,205,75,98,57,79,148,10,31,167,133,193,10,62,116,29,120,74,61,105,204,115,34,4,71,211,198,187,203,71,170,5,235,
2,245,124,1,177,168,8,138,1,177,228,41,117,44,237,59,227,233,68,122,212,129,174,216,107,195,181,126,134,139,42,206,24,222,255,254,191,50,90,3,52,220,94,14,168,40,209,102,190,124,254,18,53,66,93,122,233,
110,22,240,42,176,25,217,110,251,54,111,164,187,69,116,165,244,31,45,8,29,110,86,220,178,32,166,95,170,92,187,168,254,36,243,42,49,188,238,85,241,163,146,111,12,218,90,39,254,74,102,76,157,2,16,12,78,
87,249,237,156,152,157,193,38,197,205,179,96,17,106,131,121,242,132,221,14,111,20,235,51,163,120,18,149,108,32,62,27,73,6,30,142,19,20,110,156,131,4,139,106,229,148,18,211,180,176,123,241,170,107,106,
218,89,116,65,25,131,103,37,63,73,169,194,42,218,244,178,170,99,141,86,239,122,184,60,253,133,220,171,138,181,150,131,59,35,52,150,41,225,14,251,151,136,128,181,202,238,175,254,154,5,143,107,253,205,119,
62,208,106,227,216,50,89,224,170,133,176,237,124,155,93,183,241,145,102,189,76,11,211,212,57,223,172,74,91,102,106,73,140,214,18,131,193,107,71,112,47,159,143,200,90,19,46,43,180,92,153,21,198,232,209,
56,118,123,164,42,30,8,222,225,204,115,64,185,78,5,87,166,35,69,12,152,198,52,93,153,150,165,87,18,192,117,140,212,86,89,82,134,224,72,181,112,42,133,113,140,220,109,70,82,201,228,21,184,7,32,110,133,
157,241,84,181,36,1,33,118,133,180,194,156,38,52,195,241,227,153,237,110,100,8,1,211,12,193,118,226,113,28,7,130,247,184,195,110,21,218,59,155,4,144,79,145,135,60,51,197,134,251,238,247,127,143,49,189,
196,249,238,63,252,207,157,119,16,3,190,115,5,181,85,210,53,17,176,148,37,19,198,110,192,155,246,91,166,105,38,165,124,43,74,135,56,144,31,149,84,4,31,122,120,170,226,209,12,169,100,198,177,195,240,166,
6,77,160,197,32,70,64,29,213,90,126,249,249,125,167,191,154,226,157,96,87,137,108,55,110,120,181,113,56,204,17,31,3,66,96,127,128,207,159,126,102,177,21,165,97,130,131,172,72,105,60,147,0,90,145,234,33,
123,74,25,88,78,87,46,211,140,136,161,228,78,246,253,40,145,121,94,200,10,72,196,202,72,69,40,244,12,39,106,59,194,91,73,240,24,2,47,158,63,227,254,254,142,16,60,199,116,97,158,19,169,20,138,233,46,150,
239,127,251,15,120,17,54,99,196,29,94,62,71,115,34,107,133,160,124,117,191,39,9,212,32,240,40,180,52,67,192,98,102,110,228,158,24,203,179,87,35,155,212,249,133,199,154,174,94,129,102,8,22,172,140,60,20,
101,201,5,9,13,111,7,48,51,154,97,42,221,208,119,17,195,117,250,204,155,183,253,187,78,45,19,92,135,173,143,25,241,248,211,59,172,86,78,131,224,118,227,215,224,122,165,123,8,95,97,164,225,180,34,222,227,
135,17,89,89,158,32,6,157,11,15,235,7,138,239,42,190,85,101,92,89,155,214,42,195,8,237,211,17,90,101,28,35,255,194,64,74,153,37,37,230,233,202,146,234,138,65,134,14,81,215,69,89,150,14,126,238,21,32,99,
86,254,205,122,67,29,149,243,249,194,116,84,156,205,247,208,50,66,98,176,47,40,8,169,36,184,128,215,128,26,71,182,112,53,144,90,99,222,117,35,105,109,141,37,39,140,24,246,207,182,157,177,47,202,3,23,212,
237,9,77,9,2,77,39,172,191,246,18,75,6,62,165,134,248,126,201,118,155,17,17,135,106,193,23,101,83,27,135,178,178,166,235,78,90,99,185,75,95,241,249,120,229,116,186,224,6,9,96,29,67,176,124,241,226,25,
31,22,37,204,14,135,231,46,142,84,129,100,64,99,160,122,193,6,158,156,42,41,99,140,101,59,70,172,24,150,84,72,246,30,169,96,219,140,73,137,52,95,24,67,65,134,138,88,120,190,86,52,143,116,238,117,154,185,
94,175,100,85,130,115,232,33,96,31,83,254,156,40,37,243,214,221,163,135,103,176,155,113,147,126,130,146,65,11,31,30,126,226,115,106,140,33,240,250,197,115,190,249,98,139,132,192,41,39,174,40,169,101,194,
180,242,187,2,140,157,140,190,158,143,60,156,47,92,167,133,32,7,74,79,109,56,47,220,141,145,113,23,87,133,223,254,138,8,28,134,64,217,41,151,113,162,181,142,39,202,70,110,4,226,108,47,228,235,140,198,
3,113,244,157,170,122,251,238,247,144,22,10,133,31,254,244,29,159,210,66,153,51,191,181,161,11,42,143,118,196,253,142,48,4,238,83,175,120,131,115,108,119,35,49,12,228,146,97,78,12,173,162,243,159,145,
24,240,67,164,22,97,78,35,167,147,80,87,154,53,165,5,205,189,140,26,99,36,4,183,150,243,13,239,132,120,17,150,212,37,49,85,37,88,203,97,254,200,158,192,48,10,78,182,224,189,71,141,227,254,249,129,122,
62,82,86,179,178,51,93,158,21,173,180,211,137,37,43,63,79,122,43,103,188,115,136,216,155,207,199,59,97,183,243,196,24,168,226,104,8,169,90,230,162,32,174,59,82,208,27,91,116,245,114,179,146,61,50,246,
187,49,178,44,9,205,202,16,123,204,167,45,132,148,176,13,220,235,87,95,160,115,66,75,99,126,245,154,113,140,92,82,162,80,169,214,179,115,142,123,31,57,24,15,169,48,137,95,77,204,105,229,125,43,57,63,209,
251,69,225,52,39,46,215,9,53,172,95,40,52,85,102,151,176,210,58,206,246,129,90,43,231,243,196,52,45,136,24,188,243,252,164,239,110,112,245,49,138,252,215,255,231,183,104,77,120,107,113,145,47,72,190,34,
109,102,43,95,243,226,235,191,102,190,44,204,139,118,0,210,224,136,229,13,134,20,26,7,235,48,209,210,118,21,113,61,152,119,80,211,211,104,43,138,81,40,117,162,150,137,52,159,65,103,64,241,182,33,102,69,
125,171,25,52,149,76,73,5,173,149,156,50,203,244,112,59,195,143,204,207,40,150,37,211,207,48,38,32,100,96,32,134,13,243,84,136,97,195,24,45,41,85,90,181,16,35,50,6,36,58,230,212,110,153,202,172,22,154,
37,37,30,78,215,14,186,131,197,82,9,197,83,213,99,131,199,233,140,80,16,83,89,180,131,163,107,163,115,101,227,72,188,235,218,246,52,45,108,15,219,110,88,253,139,63,59,185,114,62,246,23,113,167,207,39,
166,52,211,114,225,151,63,191,35,28,122,58,29,8,140,163,239,94,156,113,67,3,46,41,33,99,184,85,28,29,11,3,181,225,125,247,213,75,24,240,98,241,110,203,32,138,183,138,33,225,171,130,173,252,248,203,147,
175,94,254,194,17,152,114,38,153,43,190,41,62,184,213,248,212,143,70,115,3,45,40,53,87,156,12,137,49,52,124,21,204,183,177,11,224,110,6,155,215,246,158,137,235,249,195,106,193,157,153,82,187,249,125,172,
237,122,243,126,183,229,46,6,236,198,50,108,123,249,223,106,235,88,90,149,162,149,107,169,100,42,119,247,207,110,133,235,117,234,230,143,230,60,33,4,246,62,128,182,85,248,105,248,213,185,18,242,55,92,
207,11,151,41,225,126,126,247,3,141,140,193,242,231,223,253,103,46,105,66,68,216,134,145,33,134,206,185,45,189,55,200,123,199,110,182,72,145,155,200,104,213,194,236,72,107,79,199,199,233,66,174,134,169,
53,166,42,76,10,41,4,140,4,240,129,96,26,247,247,119,12,33,116,206,56,235,205,243,158,139,178,117,142,185,246,142,154,101,73,140,99,196,123,199,151,207,61,86,4,231,67,160,210,211,106,6,130,21,46,169,59,
160,194,226,113,21,230,203,76,93,10,22,216,77,189,255,232,102,21,127,244,81,174,30,138,151,247,3,136,39,155,129,5,97,110,66,170,66,246,190,135,54,171,180,229,114,75,229,226,132,33,4,166,71,211,233,170,
59,79,211,114,131,174,151,31,191,35,122,193,137,193,189,190,255,150,92,187,75,79,95,253,45,109,74,156,174,19,11,153,113,51,114,216,239,8,78,168,215,212,113,234,229,129,105,90,86,175,89,119,103,155,213,
240,233,179,242,94,19,113,229,24,6,49,72,106,4,85,154,102,178,102,114,90,56,45,103,46,215,137,135,243,181,59,193,135,167,75,182,151,241,182,16,214,90,210,44,252,233,251,159,57,158,207,148,148,112,226,
238,123,107,152,175,60,219,255,21,227,157,229,121,206,156,114,162,180,4,72,247,177,237,44,119,192,252,77,229,114,233,30,226,33,6,52,43,231,203,196,178,242,195,193,59,156,88,130,169,144,38,66,154,176,101,
34,24,195,24,44,42,207,186,219,80,59,19,164,89,185,76,51,215,203,68,42,5,51,207,232,196,205,241,29,156,195,107,226,222,131,120,135,187,164,83,111,225,241,134,205,189,64,181,248,84,121,41,91,162,63,220,
148,251,110,75,80,246,140,120,107,153,53,99,179,35,37,101,183,221,179,127,214,179,214,98,115,247,79,44,133,105,246,16,34,187,241,21,206,10,151,84,8,187,129,236,187,84,22,86,73,247,96,44,187,245,5,236,
249,120,115,131,223,250,56,252,68,164,97,156,193,29,158,141,216,218,168,20,202,124,102,55,238,184,180,68,154,50,211,131,246,85,195,16,67,232,34,162,86,76,205,132,213,70,142,135,170,137,135,115,247,232,
132,93,184,241,199,119,65,16,23,184,219,244,134,42,99,44,37,101,140,152,238,164,74,202,104,164,91,116,188,99,43,14,63,68,114,233,108,232,35,158,32,11,110,140,236,247,1,247,203,31,126,0,11,134,198,187,
223,255,158,156,234,234,14,140,108,55,35,91,219,125,190,49,52,196,86,36,192,232,149,57,21,130,157,9,174,115,18,119,65,200,219,136,58,115,107,115,136,50,144,114,134,164,8,66,64,122,86,53,150,36,141,24,
220,45,166,79,215,5,105,149,113,123,96,4,182,89,73,155,194,146,50,245,197,75,226,234,149,115,215,243,103,180,21,4,248,244,254,45,154,149,24,3,219,112,135,168,162,205,112,189,192,244,208,207,213,156,20,
173,93,96,17,17,146,42,135,253,142,221,110,228,126,191,37,211,105,90,59,95,185,148,43,203,41,173,9,192,80,181,177,25,195,205,23,28,188,99,59,116,185,7,107,0,33,205,109,5,239,194,24,7,238,182,194,221,245,
21,74,3,20,183,164,5,77,133,90,19,239,223,125,66,130,229,116,133,79,199,35,104,143,135,218,122,24,171,181,178,93,33,97,74,133,16,28,37,43,231,235,150,113,28,216,124,26,65,44,210,44,69,11,243,212,213,159,
237,110,195,16,122,151,216,195,124,89,5,152,158,128,174,155,17,39,114,19,38,179,13,124,186,76,156,206,87,90,171,220,237,182,216,243,137,215,119,123,14,227,14,247,252,229,87,104,77,168,86,190,253,87,127,
197,148,167,27,6,214,164,132,53,61,62,178,49,233,52,145,86,123,128,174,170,102,57,77,188,125,127,188,17,43,143,117,90,41,189,88,221,93,54,120,47,204,179,114,60,30,111,238,20,239,4,239,187,65,196,173,82,
88,13,219,91,6,221,109,70,198,81,56,77,19,191,123,243,145,243,241,1,23,15,135,174,23,52,229,242,226,11,34,185,155,131,30,207,214,26,192,107,238,253,29,113,191,103,179,174,240,99,240,183,198,112,124,56,
83,230,194,134,128,49,245,102,132,206,85,81,10,203,188,112,185,78,60,182,129,120,129,172,137,211,241,132,61,217,53,89,204,12,251,253,138,47,220,173,43,242,247,255,233,255,230,60,39,114,74,56,23,118,80,
51,90,10,54,56,54,155,17,173,149,162,141,89,27,201,8,46,8,118,48,72,84,74,154,24,15,123,118,174,155,58,40,221,235,48,158,47,84,109,216,83,70,91,35,12,6,231,87,86,82,42,102,165,211,218,244,228,188,158,
211,194,135,143,199,27,242,123,120,184,242,176,204,196,193,49,110,226,77,207,139,65,80,211,191,207,165,10,105,82,82,81,82,25,169,9,210,156,8,33,224,179,33,108,119,220,223,239,123,99,41,141,107,82,10,80,
180,162,5,164,52,164,41,155,48,160,181,113,221,41,199,135,19,243,113,98,60,192,254,126,36,196,134,56,67,181,74,187,116,169,96,106,13,85,199,243,231,119,253,242,166,76,200,133,195,231,207,79,222,248,208,
157,45,241,223,125,221,91,61,109,195,29,238,246,76,214,179,164,153,60,110,73,109,70,171,237,172,185,15,136,245,164,12,213,123,168,141,224,215,46,25,15,162,13,117,21,48,120,44,27,17,182,17,82,73,204,243,
132,38,144,234,113,110,232,145,35,23,146,233,165,144,115,130,163,119,251,214,86,113,113,192,69,120,118,183,97,89,101,225,178,18,219,185,90,118,193,51,132,128,59,127,58,119,137,180,41,145,202,235,47,191,
232,146,65,214,91,53,113,78,9,140,161,217,198,18,12,3,125,149,122,111,231,66,109,246,102,72,218,136,240,13,47,120,182,219,129,84,66,240,180,194,218,247,209,59,206,231,148,208,107,111,95,139,33,32,206,
244,6,148,162,124,78,5,241,35,132,145,172,51,41,39,22,29,57,167,129,9,193,137,94,33,21,144,138,158,143,44,40,85,181,139,40,88,114,201,76,159,142,152,193,129,181,196,56,246,230,148,96,8,222,99,220,182,
123,115,164,219,7,108,171,132,195,134,151,135,61,85,122,51,73,90,153,33,39,66,105,245,22,69,30,206,157,28,65,96,63,110,241,163,167,242,236,246,242,143,237,23,119,82,16,12,75,154,112,199,119,63,65,45,104,
129,247,63,252,51,231,241,101,255,112,107,186,176,152,50,211,126,13,250,188,0,0,32,0,73,68,65,84,241,129,221,97,71,220,14,108,214,232,81,47,149,236,186,156,181,212,167,34,116,88,27,169,53,129,223,140,
236,198,93,15,91,34,88,28,154,174,12,107,15,95,202,21,151,50,222,121,198,0,104,198,142,91,106,169,104,106,180,100,136,126,100,23,15,136,192,149,136,203,181,209,230,4,13,206,231,137,227,167,159,123,111,
166,24,62,188,125,203,101,90,56,95,38,198,195,134,237,126,75,8,110,237,175,107,183,126,33,211,158,200,145,236,250,185,52,56,154,183,4,23,144,16,25,226,72,12,129,72,190,245,29,45,169,224,197,240,124,235,
241,33,115,62,95,249,238,79,111,86,107,101,199,47,119,251,45,27,77,236,7,7,163,193,125,241,229,87,228,210,213,245,244,155,191,98,186,156,73,41,51,136,239,250,196,96,241,135,64,53,80,3,76,182,112,181,19,
41,23,124,53,72,162,59,88,90,167,176,112,221,120,183,25,71,74,182,156,167,19,115,238,96,200,199,129,121,173,138,227,138,129,83,202,252,252,49,176,223,245,150,160,195,24,110,173,201,144,88,78,71,254,252,
195,127,225,251,6,170,9,151,240,204,40,205,8,23,137,176,237,202,207,120,191,69,140,225,96,45,50,56,166,212,237,95,87,201,60,155,247,232,146,177,64,77,153,101,154,48,185,17,68,240,210,113,129,115,130,181,
30,100,232,103,121,53,3,142,135,13,159,142,15,156,115,215,164,47,243,68,157,42,239,46,253,152,200,121,194,7,119,59,70,169,100,222,254,248,61,219,33,48,110,5,119,120,182,101,152,61,170,133,235,171,23,196,
203,200,188,201,168,216,222,98,9,84,96,31,44,166,129,37,147,108,129,17,28,14,29,26,113,204,56,58,99,159,37,80,114,247,193,205,41,67,73,88,85,134,149,145,28,130,231,217,151,95,209,106,230,124,157,184,196,
243,218,230,182,170,74,219,47,215,148,95,73,218,192,0,242,140,57,9,73,27,206,224,24,163,160,85,121,54,110,25,14,123,14,64,161,61,245,39,151,222,221,229,68,176,161,50,46,153,86,237,173,175,115,94,18,181,
64,117,2,165,59,101,181,117,57,75,177,248,218,152,108,197,87,203,32,14,156,16,220,192,203,253,142,231,250,146,148,123,7,238,188,36,174,167,25,23,2,193,90,156,235,97,47,206,95,227,6,33,58,139,123,243,227,
207,55,219,224,47,127,124,67,216,12,132,109,68,98,215,45,188,23,150,94,240,115,8,1,44,44,198,146,81,196,132,206,98,110,2,180,70,51,6,189,206,88,43,12,42,108,54,91,162,23,124,48,4,113,93,185,95,25,34,145,
238,89,214,162,88,2,180,9,177,25,49,189,97,171,214,70,41,138,113,66,245,145,107,206,156,231,138,139,190,161,57,35,65,248,226,89,224,218,44,27,49,44,243,194,164,74,22,193,182,70,173,160,210,65,81,16,65,
198,129,184,141,224,132,212,42,57,21,82,173,140,247,135,27,27,25,168,93,30,51,149,154,122,232,155,214,195,172,106,169,165,50,93,51,243,146,1,67,8,91,126,243,229,129,109,140,164,156,187,250,47,142,23,124,
226,186,164,222,155,95,211,9,35,150,154,43,15,159,223,224,205,8,140,12,98,136,214,50,198,161,187,172,151,76,76,93,197,23,99,17,28,134,165,95,48,1,39,150,173,184,238,216,54,128,51,221,239,165,149,180,20,
206,151,137,235,52,179,31,199,155,237,49,120,71,217,237,200,143,182,222,48,144,74,194,224,250,247,216,214,147,140,29,113,67,232,61,161,231,203,17,172,69,115,225,167,159,127,100,23,70,194,209,211,108,191,
108,222,57,170,42,203,181,155,243,163,13,228,181,1,5,177,24,235,176,206,117,251,64,112,76,102,123,163,79,67,240,183,20,254,72,140,180,195,238,86,109,248,224,9,18,215,136,98,200,90,24,157,133,90,168,57,
161,243,149,41,23,30,222,190,165,104,35,165,132,235,101,78,3,28,49,68,188,8,215,101,230,116,186,114,60,95,58,116,140,129,224,28,14,203,131,237,77,126,67,12,68,233,49,179,150,194,249,83,111,75,219,29,122,
82,80,3,243,36,183,38,108,90,197,228,194,116,236,50,195,212,204,138,200,6,226,106,55,16,25,80,153,59,63,188,74,183,243,156,56,47,87,162,51,212,156,112,95,127,253,45,41,85,42,141,125,254,215,204,215,43,
73,149,221,139,196,225,122,189,117,225,110,188,135,92,73,171,43,112,73,153,105,78,88,147,9,254,201,79,252,241,195,251,222,25,163,173,23,2,195,136,127,44,235,197,210,170,18,162,32,226,187,79,190,20,200,
22,227,3,206,86,150,243,133,203,180,16,67,96,19,3,1,56,60,187,227,249,97,139,150,132,155,101,164,5,5,85,146,143,108,159,143,196,162,196,92,184,219,118,66,176,173,166,250,57,37,172,0,75,34,49,51,167,153,
40,130,140,22,71,239,27,210,230,152,115,66,211,12,73,9,215,11,86,26,166,213,222,54,225,65,172,163,174,173,58,32,176,250,133,226,202,229,221,237,182,196,231,7,196,85,196,8,239,143,19,239,223,126,134,6,
46,133,45,146,161,56,229,26,239,185,214,19,133,198,92,96,161,81,107,238,109,98,119,142,104,44,7,42,246,49,62,107,130,220,250,132,152,202,77,112,209,146,104,89,73,58,147,206,87,82,201,136,244,46,113,187,
218,131,230,185,192,202,128,118,203,86,119,24,158,166,207,156,166,35,63,189,251,153,224,122,229,113,252,227,15,180,170,84,26,78,148,238,189,84,101,153,23,16,112,126,32,74,192,250,222,141,235,131,71,214,
177,34,131,118,237,225,81,250,106,249,73,58,136,64,78,19,33,236,215,246,181,194,252,48,113,158,206,189,139,70,42,146,186,63,45,120,135,21,15,42,93,250,186,44,100,85,94,239,122,127,105,73,189,87,212,15,
6,113,48,151,254,124,238,250,246,123,170,237,21,240,249,135,255,130,97,188,169,71,143,45,251,178,29,217,110,70,124,112,212,187,59,64,104,213,98,77,35,209,167,40,153,85,4,124,126,120,113,27,48,160,117,
65,182,129,93,28,159,26,180,139,34,113,196,174,158,137,170,22,27,55,108,14,157,74,136,237,114,155,64,243,216,30,84,175,31,137,151,43,231,41,225,174,31,63,116,222,186,20,46,63,255,140,218,241,166,206,119,
57,206,83,206,194,229,17,116,199,221,173,222,10,222,175,195,137,220,173,119,99,190,234,237,139,172,181,196,97,100,220,30,16,99,41,40,171,59,130,235,58,157,70,53,147,230,94,38,137,24,94,135,241,246,187,
143,141,233,219,241,57,113,216,179,75,21,71,220,96,157,224,155,225,254,235,111,144,208,131,245,118,59,178,27,183,171,142,214,86,43,140,144,106,159,78,144,215,182,8,161,146,242,194,195,116,165,214,202,
24,247,196,33,176,221,244,46,90,9,79,29,186,173,53,78,159,142,29,4,25,225,238,176,239,12,168,54,174,151,137,165,100,82,234,47,108,177,107,235,132,99,255,226,37,75,41,164,57,225,112,59,42,149,108,44,83,
18,242,242,208,249,176,119,167,167,46,23,237,184,97,28,7,94,237,238,72,37,163,89,9,113,100,51,10,119,171,197,92,188,80,82,194,152,68,75,137,247,159,215,152,42,220,24,201,58,183,206,31,7,135,122,139,14,
189,21,185,78,51,86,27,254,240,156,218,86,157,217,25,36,10,195,232,201,147,226,131,193,217,166,93,22,32,225,90,225,16,14,36,242,74,102,68,106,237,6,34,107,13,27,217,240,240,225,23,46,151,137,115,90,171,
140,208,169,43,23,250,81,218,109,21,140,116,227,145,230,30,107,237,234,15,174,141,109,49,4,127,199,214,140,56,132,50,157,89,166,153,156,10,222,9,243,18,250,100,133,149,186,242,87,225,244,238,71,148,134,
87,112,113,179,3,91,177,185,208,198,200,241,60,147,168,212,170,136,38,172,111,4,81,76,75,28,143,191,112,92,155,159,118,135,145,253,184,189,153,149,141,56,154,42,15,159,46,191,210,147,67,240,104,235,6,
166,233,58,243,113,73,252,244,99,63,156,187,237,200,243,231,7,66,240,79,238,150,36,79,131,8,232,243,102,126,250,254,39,242,50,163,85,113,175,14,207,123,11,123,73,228,87,175,224,144,184,164,196,195,180,
246,100,94,102,166,249,218,127,65,19,97,189,20,41,41,179,237,30,52,35,246,230,199,12,193,99,180,247,45,165,82,168,173,97,141,33,56,71,216,239,216,168,118,83,233,58,219,231,116,190,220,38,31,0,236,195,
231,30,77,214,217,19,173,54,46,31,62,246,1,116,128,211,213,154,149,138,50,105,197,1,86,28,119,155,29,187,113,211,39,120,105,198,180,174,229,177,138,38,178,234,196,203,181,131,239,107,214,155,12,240,216,
53,35,242,151,35,73,250,206,236,247,219,94,2,201,240,52,133,169,244,106,101,136,129,207,159,142,79,61,211,107,219,69,76,9,66,31,43,229,78,211,140,5,156,27,184,191,191,167,206,51,214,218,110,184,107,125,
164,152,104,70,233,65,89,207,215,167,129,65,170,84,132,106,64,5,172,8,135,113,127,107,129,143,33,32,94,208,220,25,245,180,142,104,168,6,22,237,144,243,225,116,97,89,181,229,97,8,188,126,22,16,129,176,
245,55,151,182,121,230,104,52,180,37,220,54,110,168,40,77,11,215,185,3,239,109,112,108,194,22,17,203,178,36,46,243,133,105,157,103,98,232,1,191,209,87,167,185,129,241,16,241,30,92,240,236,195,112,235,
122,185,105,20,40,1,193,74,119,178,244,86,249,213,121,21,71,226,184,197,15,61,147,158,231,19,214,54,100,53,61,181,90,249,195,251,7,74,202,228,86,112,226,4,26,212,117,12,136,143,155,62,2,170,20,244,156,
57,207,115,119,83,59,193,136,99,220,13,183,110,175,150,83,55,220,219,167,14,241,150,27,139,102,166,169,220,206,169,181,118,5,226,150,162,144,42,52,43,196,109,100,220,217,219,48,174,166,141,113,116,79,
195,94,214,11,45,155,17,137,3,131,109,184,119,239,222,99,188,16,130,225,146,19,154,13,251,24,185,223,221,177,121,190,165,25,152,210,196,167,116,230,180,92,105,115,67,198,208,191,164,101,188,235,86,220,
57,79,168,54,206,243,185,223,114,121,114,101,185,117,126,138,247,142,90,32,172,71,224,209,43,33,214,96,165,95,84,204,72,62,95,32,101,76,240,29,197,189,120,142,0,97,244,184,187,231,123,196,10,182,86,210,
221,182,187,80,51,124,250,124,229,104,166,30,150,130,244,86,181,141,97,24,186,152,157,107,234,3,19,109,163,185,222,105,99,4,54,119,220,122,66,31,33,105,210,70,75,218,63,27,233,188,115,202,148,149,165,
12,193,51,198,161,71,155,224,88,154,101,86,216,34,40,150,99,177,8,149,177,24,156,159,174,136,52,82,83,166,95,126,38,53,101,103,28,187,232,9,166,146,46,189,26,201,62,144,18,48,90,8,14,99,61,126,197,20,
67,8,132,221,243,126,44,110,103,180,176,44,169,15,110,89,163,197,117,234,238,237,59,15,15,151,137,43,103,70,63,82,233,19,31,227,232,161,6,14,187,200,48,174,177,220,193,55,223,124,133,40,232,156,112,211,
116,197,172,77,3,0,47,247,119,152,90,160,42,41,41,173,25,68,32,138,197,14,189,62,23,107,215,113,61,21,74,159,196,148,166,206,183,205,15,215,219,153,21,177,24,44,40,20,233,137,164,206,235,48,67,186,10,
85,107,237,219,29,3,67,136,196,56,50,231,174,3,86,250,148,154,20,35,166,86,84,44,206,137,233,12,100,90,120,255,241,3,63,253,248,35,131,88,14,195,64,92,89,70,98,68,36,145,177,196,221,72,190,40,151,219,
96,151,158,205,6,223,219,37,82,202,136,177,132,237,72,8,66,109,93,204,9,214,162,226,57,107,66,181,48,24,97,184,11,79,168,110,197,216,89,187,127,216,180,6,181,219,126,147,42,46,43,69,19,110,153,22,144,
74,214,110,186,63,220,141,189,151,3,219,71,60,94,102,244,58,227,134,1,196,144,242,140,172,253,69,209,27,188,244,214,5,145,118,107,163,120,196,210,115,235,157,185,73,245,54,184,104,28,35,48,247,68,177,
223,220,90,136,197,246,158,59,99,20,187,38,153,89,123,145,64,74,76,151,196,92,19,238,146,206,92,78,15,180,166,188,255,240,158,151,119,35,181,54,206,56,124,235,111,232,45,68,1,241,150,203,116,165,217,62,
120,19,228,134,111,251,67,247,10,188,105,229,114,238,93,99,147,246,94,185,176,38,147,103,251,67,159,213,42,22,146,114,190,92,57,77,229,22,218,144,222,201,155,105,168,237,161,50,56,193,141,14,20,220,215,
47,95,145,14,7,114,203,236,234,223,240,195,31,255,196,52,101,200,253,66,121,43,108,104,28,31,30,200,57,225,199,241,54,222,177,103,133,206,150,239,118,35,131,247,144,50,75,235,12,62,214,16,173,161,122,
79,8,2,182,145,83,1,211,7,111,77,211,204,241,120,230,52,149,117,40,210,200,146,174,228,90,105,182,143,181,138,67,32,21,237,163,86,19,56,76,237,101,119,133,37,10,223,254,230,91,206,231,132,78,107,229,160,
21,219,20,65,49,198,243,197,253,221,19,145,109,236,173,173,7,26,166,102,238,70,143,95,169,85,181,182,207,2,28,123,135,65,167,176,18,212,110,166,107,205,178,25,119,140,67,3,239,136,49,48,110,158,49,175,
19,111,250,56,53,199,160,175,40,41,161,215,11,238,231,55,111,58,162,114,134,227,219,15,84,239,177,120,238,158,223,33,226,89,206,19,243,52,145,211,5,1,126,249,248,161,79,29,141,27,130,115,164,82,200,41,
35,46,244,94,102,186,45,50,169,146,5,164,10,214,65,197,116,82,228,220,143,76,46,16,55,91,94,191,124,197,110,59,146,214,169,75,211,52,115,77,137,148,231,206,72,197,64,154,102,154,246,42,199,157,47,23,230,
178,224,141,225,120,124,224,213,171,47,251,120,223,199,44,53,58,190,184,59,96,116,195,229,58,113,252,248,126,117,164,88,130,219,117,131,103,46,104,73,84,17,178,88,38,205,204,41,225,125,31,56,180,137,253,
114,141,49,112,183,14,225,82,227,122,239,126,16,234,106,60,189,78,11,86,38,124,23,201,122,135,99,86,74,82,238,14,247,12,7,139,235,70,164,62,225,193,121,71,106,13,215,90,87,207,87,6,231,154,103,210,52,
113,60,158,176,22,14,187,13,251,67,71,101,85,27,54,122,114,234,158,159,90,50,70,44,113,220,162,69,121,255,241,51,239,63,126,166,225,48,198,176,223,109,17,239,80,3,125,216,227,25,239,133,148,123,121,31,
124,31,174,44,94,216,56,71,42,141,63,190,253,12,111,222,49,74,192,217,224,217,217,136,108,60,145,175,33,121,170,21,172,24,230,169,48,229,94,159,213,105,166,104,35,248,110,98,154,62,124,188,93,58,99,205,
218,133,91,40,115,159,242,241,56,204,66,188,128,241,183,145,23,121,13,113,136,37,219,140,96,25,71,207,254,48,244,127,171,11,226,132,101,78,124,56,247,89,23,177,205,160,141,227,167,43,174,150,62,92,211,
39,225,252,112,37,103,33,248,1,130,80,110,213,50,196,93,100,187,219,48,167,43,199,227,153,148,26,135,253,142,195,97,92,253,236,230,54,60,224,201,45,53,178,25,7,88,71,144,180,214,135,31,56,23,105,206,16,
83,47,8,134,232,250,64,100,133,209,252,255,116,189,205,146,28,73,150,165,247,233,175,153,185,123,68,32,144,64,101,78,117,13,101,164,103,102,193,5,133,111,192,247,223,114,65,46,154,210,67,118,119,117,86,
101,2,137,128,123,184,187,153,169,234,85,229,226,170,89,4,154,194,18,105,41,169,170,70,34,194,221,76,245,254,156,243,157,73,157,13,75,194,213,198,41,68,226,167,103,221,136,230,51,254,126,95,240,253,200,
89,210,74,224,160,234,211,36,248,106,169,93,92,159,215,140,24,75,116,35,143,39,203,16,35,63,255,252,145,231,167,103,106,171,92,111,10,71,94,23,217,229,5,24,67,150,70,234,93,72,140,1,41,142,156,22,228,
173,25,81,145,127,83,183,249,216,183,250,198,88,62,124,250,192,97,26,249,245,159,254,202,122,43,140,211,132,127,120,124,192,58,135,179,112,206,141,56,121,82,145,46,236,128,232,140,14,10,83,33,24,131,27,
13,135,227,68,244,35,215,107,226,122,253,173,219,221,91,183,90,86,82,41,88,28,113,138,187,217,26,20,31,114,121,185,40,117,198,192,48,134,55,181,119,237,166,65,28,24,133,211,57,231,184,55,56,55,144,193,
227,141,197,255,229,151,63,145,37,49,207,51,78,42,243,245,70,90,59,156,51,56,226,160,54,199,211,195,145,159,142,7,140,31,119,93,217,125,94,185,207,25,107,45,15,147,206,203,230,164,152,211,66,235,2,141,
1,112,172,69,65,134,199,231,143,58,202,50,218,140,58,175,22,55,233,226,144,239,185,48,142,234,253,255,126,95,73,115,161,96,113,167,73,137,118,127,253,251,239,88,169,140,99,224,52,142,28,14,79,24,27,72,
34,212,78,63,72,243,204,104,29,147,143,84,107,144,46,159,249,120,124,224,224,18,247,121,197,149,202,48,58,204,99,100,58,77,170,124,53,150,53,9,127,92,174,187,175,168,102,253,5,83,173,29,22,7,135,206,90,
171,214,96,125,100,73,29,160,56,14,216,34,220,170,83,147,34,22,255,124,124,162,44,9,36,19,24,49,54,96,171,33,38,8,120,134,211,4,31,63,114,47,137,23,47,48,119,204,238,93,159,203,187,40,49,201,26,195,84,
11,134,161,63,175,218,250,100,42,227,113,196,57,61,34,99,60,236,115,184,13,228,146,179,168,125,8,152,35,76,7,245,58,187,36,4,31,248,249,56,224,205,160,147,213,211,225,129,228,86,214,124,163,26,131,36,
5,199,206,215,68,154,87,154,81,97,70,242,21,23,245,91,208,31,40,18,98,228,99,231,180,198,56,96,199,64,93,58,81,166,91,89,213,215,84,201,2,41,235,40,33,74,219,159,221,42,106,156,218,199,1,173,64,74,74,
204,86,214,58,158,180,247,121,254,247,239,103,144,134,65,88,147,22,242,227,52,113,152,30,119,144,230,101,185,82,214,59,107,74,180,110,218,83,62,132,78,41,66,244,36,7,129,74,182,142,165,143,4,130,119,28,
198,137,216,253,254,185,200,14,95,94,215,68,190,235,203,102,187,251,214,25,203,105,131,51,23,221,134,90,54,218,71,162,204,130,31,134,19,46,40,1,60,61,63,169,140,107,156,56,68,101,6,130,112,170,207,148,
180,32,173,144,253,198,60,82,129,82,173,202,5,150,16,168,198,168,20,97,59,24,130,197,56,48,173,210,146,142,5,118,82,46,96,189,99,244,10,138,217,94,228,180,206,228,44,212,146,245,202,7,230,215,133,182,
36,93,142,63,126,58,97,208,78,33,62,157,120,126,58,34,2,185,53,82,110,42,173,73,133,101,153,41,101,225,154,83,71,159,26,44,58,14,117,135,200,96,42,67,84,141,175,35,34,77,11,122,39,122,190,110,148,143,
108,243,62,24,172,181,246,127,95,120,189,233,133,179,222,84,193,77,145,254,24,20,126,251,219,239,184,82,89,106,198,47,181,97,209,88,128,230,44,127,253,242,85,159,187,113,96,140,17,59,5,101,68,56,207,50,
59,30,252,248,206,198,16,116,129,136,32,235,204,178,110,0,23,139,201,21,105,137,222,60,224,208,250,250,229,251,247,157,94,179,17,114,223,155,90,93,19,93,92,122,199,224,44,41,27,158,143,30,7,228,217,226,
11,64,105,84,73,44,77,248,240,73,217,216,169,193,85,86,228,158,160,100,76,42,74,247,92,20,150,92,157,78,215,77,127,219,165,86,172,117,224,213,207,41,165,104,202,3,70,187,22,42,62,4,20,22,98,116,137,222,
55,160,174,215,35,94,215,121,72,19,48,6,211,26,86,26,142,173,233,117,248,33,68,132,132,56,79,28,226,62,150,90,68,88,115,37,173,51,36,97,0,90,90,25,170,161,22,193,13,150,193,170,167,115,28,6,178,213,171,
55,137,16,140,33,23,7,57,41,206,164,75,122,45,112,157,19,67,140,76,253,255,182,177,86,234,10,170,128,32,41,179,136,80,122,132,192,237,229,130,183,250,139,251,249,114,238,134,255,202,245,219,11,146,86,
69,142,216,198,227,52,48,142,39,234,53,225,164,96,177,188,122,5,182,168,85,61,67,205,208,26,46,87,36,195,67,25,245,141,239,4,143,150,116,162,185,116,109,253,247,243,89,103,25,99,252,1,132,177,45,98,206,
146,176,206,236,142,94,128,215,249,12,8,53,85,124,90,23,218,198,130,184,174,12,190,34,22,242,92,144,180,240,146,10,229,118,195,39,93,165,58,105,148,44,212,142,186,217,164,229,219,164,242,183,170,76,65,
181,14,235,55,176,150,196,114,237,124,193,96,184,205,43,151,235,189,219,50,117,236,37,181,145,83,134,49,40,127,187,86,114,159,242,95,103,125,199,36,11,254,242,242,77,27,198,90,57,127,249,138,151,132,245,
142,185,27,249,115,85,39,192,104,29,53,247,91,174,255,176,210,84,11,108,102,179,27,170,147,115,228,69,199,170,83,8,140,222,80,250,159,153,92,64,176,196,105,220,183,80,174,47,198,183,137,123,232,235,176,
13,92,223,106,133,215,143,180,142,24,246,223,127,253,85,225,219,14,46,191,254,198,113,136,152,209,170,128,212,90,98,116,196,131,58,191,82,202,76,31,30,246,83,66,231,196,111,53,179,212,202,81,60,210,42,
17,203,20,53,143,160,38,97,138,145,135,83,36,9,251,94,186,213,250,54,161,239,63,252,112,28,222,30,147,94,143,223,78,109,207,73,240,191,252,252,51,209,66,136,142,159,249,175,44,235,76,136,65,47,132,224,
8,113,196,122,167,138,190,37,193,113,218,49,254,155,25,219,56,101,8,219,142,65,107,181,50,249,160,250,226,165,32,203,12,82,17,28,15,143,39,238,243,218,59,109,21,229,171,203,188,114,187,39,66,111,4,234,
59,4,196,53,105,29,98,156,193,63,158,38,144,166,152,254,214,112,221,7,26,123,193,109,195,0,222,98,188,195,24,207,40,138,228,45,98,187,168,211,16,9,59,239,117,142,141,117,73,180,92,213,170,9,84,235,201,
77,104,235,202,223,206,215,93,111,233,188,26,88,164,233,243,155,114,198,133,31,83,37,0,190,254,118,166,53,129,10,126,78,186,201,175,77,56,223,238,156,215,89,49,165,205,113,242,3,45,40,101,201,79,145,102,
213,51,180,185,97,247,142,193,40,114,210,26,195,106,97,206,137,82,244,2,48,163,250,63,113,150,236,61,205,102,149,143,87,203,90,10,115,218,160,248,30,23,3,199,113,216,119,36,42,252,176,228,15,39,202,154,
48,88,124,70,15,230,76,97,41,141,108,28,88,135,151,198,181,100,100,94,72,2,167,167,35,46,54,22,39,58,87,168,111,64,173,224,28,209,40,141,113,170,150,209,58,24,2,153,202,42,194,156,148,147,121,75,137,209,
7,114,15,181,153,122,156,139,117,58,179,40,169,32,253,249,54,222,34,206,34,192,10,228,166,131,21,127,122,124,160,228,130,45,134,227,135,19,127,158,142,170,200,238,227,40,233,186,74,107,13,222,25,92,223,
254,108,172,169,45,253,100,83,251,101,171,207,177,53,134,64,67,214,2,82,160,26,66,77,72,115,4,99,240,33,48,14,129,232,85,130,16,198,160,51,141,119,39,6,65,71,180,167,143,35,121,214,250,195,199,105,100,
154,128,58,49,201,47,204,247,149,233,56,236,25,47,210,26,185,232,6,72,247,203,86,165,95,206,145,172,85,79,65,12,26,235,2,220,123,51,170,53,179,195,15,3,199,41,48,133,216,35,92,254,67,120,8,141,36,89,47,
138,38,212,234,246,83,200,25,131,177,6,131,242,134,146,8,62,25,93,68,227,28,23,10,225,160,74,235,57,45,111,1,30,214,170,112,205,58,230,57,97,156,101,173,21,183,1,184,76,165,186,70,43,9,51,58,106,247,225,
215,6,39,60,203,42,44,247,27,32,138,93,237,24,73,239,220,46,27,79,27,198,175,207,164,245,182,115,176,170,145,170,44,10,67,244,151,57,97,3,184,172,100,91,138,188,17,53,168,152,208,165,221,193,81,107,35,
78,113,255,223,223,62,9,187,31,246,27,137,35,205,9,3,28,125,80,216,86,111,119,172,107,157,254,177,188,49,42,122,83,160,42,44,175,179,226,173,3,169,21,230,140,226,245,26,62,189,190,246,99,4,46,127,124,
103,140,67,215,246,166,253,86,11,222,129,85,224,113,235,164,187,45,121,103,139,96,177,93,74,230,130,142,164,244,26,135,217,117,39,66,85,235,123,117,61,246,34,231,206,164,98,111,88,173,51,32,170,32,220,
49,147,210,56,255,113,166,38,181,158,248,0,250,146,72,99,204,130,203,119,114,201,200,146,200,75,66,90,38,189,75,132,232,245,10,173,75,13,155,87,31,209,246,13,208,63,177,105,136,68,55,82,36,235,47,223,
253,219,215,243,107,143,20,114,248,46,34,41,34,220,123,207,70,103,7,234,254,186,35,219,187,179,17,1,127,204,85,189,156,198,225,48,220,238,51,30,56,58,207,240,105,32,4,143,212,186,179,46,183,111,75,147,
163,222,164,226,74,245,48,156,191,125,195,209,152,236,196,116,12,72,174,92,105,212,9,44,158,225,249,97,255,133,183,8,129,16,20,17,233,140,5,27,118,254,154,117,106,151,240,243,7,29,182,44,130,63,56,139,
237,137,56,46,58,254,252,248,137,235,77,55,249,121,78,228,251,170,137,38,89,155,69,31,244,185,218,2,24,0,82,95,172,248,224,120,114,142,219,146,200,230,142,169,133,57,85,154,3,63,77,184,0,163,27,119,6,
155,123,23,76,178,35,220,141,251,97,194,111,141,33,156,78,92,231,5,231,18,158,231,127,32,137,102,192,189,140,127,240,47,34,216,227,9,255,248,70,157,163,171,91,141,181,88,111,24,67,248,193,119,44,210,223,
126,31,88,169,220,230,21,215,244,47,75,165,96,42,28,199,129,48,141,208,111,189,218,103,111,190,75,34,165,168,143,186,54,249,33,210,69,106,37,207,119,124,17,78,128,87,105,183,206,211,30,78,39,156,237,213,
83,12,63,156,197,210,247,198,33,4,188,119,76,239,224,156,242,46,165,42,56,215,169,30,118,255,223,180,108,212,63,23,187,201,100,179,25,215,214,176,210,25,154,206,209,36,67,167,241,106,175,23,96,116,172,
82,105,34,248,107,73,24,84,129,71,244,140,147,163,137,210,148,122,60,29,181,106,91,158,81,0,70,206,121,15,16,217,37,99,189,219,76,45,237,143,74,8,129,230,172,138,143,106,198,20,97,120,237,140,237,255,
159,127,73,83,44,171,243,142,135,227,68,115,158,53,101,94,111,87,150,34,248,203,252,66,192,18,189,225,150,190,51,90,71,206,178,75,100,157,127,123,52,44,240,122,43,59,173,163,214,70,154,205,15,75,238,114,
93,251,219,110,184,70,135,152,30,89,52,70,220,20,249,254,250,189,95,243,111,73,40,202,145,232,183,35,10,80,244,206,169,41,59,4,214,203,149,219,249,66,146,130,119,70,103,179,185,84,46,183,47,164,179,116,
177,241,186,127,205,251,134,171,53,66,214,58,224,116,80,94,207,70,112,86,147,148,197,151,74,28,148,75,140,192,34,69,119,30,175,149,224,3,181,229,157,204,177,49,96,155,40,166,199,71,15,114,196,245,127,
158,72,193,57,72,109,217,249,110,62,165,89,243,19,17,214,249,6,179,158,135,53,101,106,239,100,229,29,188,24,105,196,24,145,60,189,1,181,122,200,147,115,14,215,42,46,107,94,82,233,17,133,223,175,87,93,
184,24,195,248,225,184,31,91,219,57,155,187,14,104,28,34,63,61,142,80,69,19,38,102,144,236,88,110,51,41,175,180,181,226,243,156,105,128,105,13,153,117,190,230,67,100,156,6,198,137,93,48,180,81,197,55,
79,243,230,165,171,89,175,231,241,164,142,152,132,234,116,230,37,145,74,133,16,121,120,254,200,211,71,251,3,36,96,75,4,90,82,82,196,111,17,76,243,172,73,223,129,38,58,218,90,173,229,62,207,228,110,107,
243,129,137,42,66,169,66,154,157,182,236,237,45,207,69,159,45,253,207,206,57,220,113,216,33,180,174,54,90,92,21,75,253,116,234,182,158,164,37,145,137,196,214,118,252,141,203,90,146,202,178,209,240,212,
224,71,45,180,24,57,76,182,3,64,211,94,108,213,90,169,181,170,202,194,169,100,220,63,255,252,9,168,84,129,147,191,41,136,27,139,239,183,80,171,141,100,209,33,96,159,242,196,216,251,183,222,124,6,31,186,
69,210,18,238,26,28,66,209,29,241,104,148,102,103,250,115,105,15,118,119,200,44,107,194,139,229,169,119,25,181,54,8,239,46,141,190,110,120,245,14,73,133,210,4,111,48,224,2,209,85,236,97,226,118,159,181,
240,54,6,106,35,163,110,173,156,42,197,234,63,180,119,73,58,40,169,21,105,247,119,236,213,21,58,51,211,25,53,171,144,132,109,200,246,233,227,211,59,241,82,131,208,1,49,128,197,48,186,105,95,13,111,83,
33,249,240,76,126,172,144,26,190,136,40,193,22,97,78,43,68,71,174,141,165,7,138,170,141,4,21,87,56,163,5,207,150,15,234,28,205,26,76,109,176,5,223,40,2,143,80,213,248,186,227,166,251,80,132,119,165,105,
136,122,61,191,103,24,103,35,224,32,209,244,28,197,34,206,104,242,212,4,126,73,119,108,133,21,225,245,229,5,63,134,93,228,182,125,229,214,88,106,255,97,98,23,113,108,197,203,198,132,223,86,93,10,45,170,
100,117,155,225,81,79,157,65,103,12,215,238,231,216,242,104,60,58,245,17,217,244,150,129,82,50,116,197,138,94,76,61,11,111,21,252,245,114,85,67,135,131,249,126,199,39,45,21,195,38,129,169,125,52,58,103,
74,41,16,227,126,196,57,231,8,206,236,5,119,240,14,211,35,8,37,139,98,212,93,7,255,247,235,221,25,135,136,202,104,82,19,106,159,230,111,57,53,27,248,126,191,246,171,227,122,187,118,17,117,195,123,212,
181,5,48,144,105,105,69,10,52,163,5,138,173,221,229,146,50,181,8,137,55,48,92,115,61,73,170,215,4,51,80,54,191,156,188,49,94,125,212,249,174,72,99,45,153,188,150,31,138,119,233,191,96,22,33,76,234,74,
216,46,149,146,133,191,254,223,255,140,235,46,73,159,46,23,26,130,161,113,254,237,11,1,67,170,162,191,125,109,56,12,174,233,177,20,26,156,37,247,120,66,251,3,15,112,167,132,69,240,239,254,179,145,70,44,
234,48,208,45,125,193,15,208,106,7,201,134,160,158,166,94,200,223,174,137,80,21,142,92,171,242,176,142,41,129,105,120,49,120,210,10,77,176,209,16,171,38,55,24,154,158,123,93,207,51,136,85,204,159,84,78,
221,108,34,34,92,239,26,249,186,83,28,141,65,28,68,175,153,27,234,156,21,214,153,221,187,124,189,205,251,35,36,181,18,67,216,79,132,92,52,23,23,41,164,59,123,234,10,69,217,19,137,138,183,159,126,209,253,
151,117,28,17,30,14,39,94,95,239,157,197,51,236,191,185,119,78,221,6,242,198,47,249,169,127,146,219,124,183,182,74,120,23,178,55,2,238,7,42,35,60,179,244,40,45,251,67,206,221,86,194,110,130,82,231,220,
59,29,190,250,73,150,156,241,159,62,126,222,218,61,194,242,141,101,121,43,15,183,231,44,165,130,56,101,77,76,211,1,113,1,51,216,31,252,70,251,81,53,190,149,155,34,73,159,255,119,19,206,167,167,159,246,
31,118,11,89,104,77,83,214,36,23,78,147,254,217,205,230,14,224,203,157,201,235,70,203,19,244,248,169,173,178,72,166,52,37,226,75,171,164,121,222,15,239,109,90,254,186,190,125,42,198,88,98,229,135,34,230,
219,31,223,223,149,119,121,15,135,236,171,33,30,103,253,115,27,153,113,131,195,24,111,193,195,250,186,244,79,220,210,82,101,73,137,63,126,203,16,43,198,52,252,45,105,123,212,114,227,190,104,97,35,118,
171,126,251,121,29,135,253,135,186,101,187,199,188,109,167,133,233,73,18,107,209,57,240,22,34,233,172,14,101,66,99,231,2,105,224,142,208,122,233,154,128,188,188,213,211,27,242,212,58,250,130,199,98,166,
62,109,66,240,71,23,17,211,84,1,125,156,200,34,140,238,125,206,108,251,33,244,238,232,20,46,240,62,139,118,255,11,12,140,93,109,165,80,11,193,118,171,166,115,26,22,194,240,70,37,221,38,60,219,39,109,172,
229,92,146,86,129,78,1,114,49,84,30,159,141,14,7,11,248,116,187,106,95,69,37,93,175,120,231,118,210,215,246,2,232,78,206,83,74,161,250,222,241,246,114,243,63,22,248,158,65,79,13,43,251,99,18,48,224,116,
243,153,91,250,97,225,146,106,165,181,202,98,172,246,117,31,15,72,77,186,254,234,47,99,146,239,68,156,74,25,95,207,223,180,185,115,112,249,250,59,37,245,150,69,116,241,82,165,225,189,123,87,203,234,47,
16,253,219,225,46,253,37,117,214,114,125,247,118,235,237,150,119,103,205,232,2,151,121,222,187,237,247,145,157,27,64,249,250,237,107,79,71,113,251,112,230,252,235,87,124,48,180,44,248,243,87,253,129,141,
131,111,127,255,131,113,24,118,227,210,20,3,130,144,214,133,235,253,70,206,66,28,117,112,82,59,93,191,182,182,127,35,206,24,82,8,184,10,173,229,158,249,92,52,143,113,212,95,50,173,111,97,168,91,123,180,
13,201,141,181,20,167,125,228,233,216,189,79,210,120,249,118,237,151,78,197,159,158,127,233,38,19,71,68,88,75,98,168,85,233,113,78,21,131,146,50,193,105,186,234,188,188,236,63,228,229,188,236,103,166,
115,17,41,149,39,59,208,156,69,234,192,66,193,186,132,29,148,200,97,156,197,150,133,113,24,247,151,86,247,25,117,183,70,88,239,152,14,234,188,73,185,176,230,196,253,239,55,110,105,214,229,209,159,126,
249,220,151,221,142,7,46,92,250,217,185,165,234,212,162,164,164,116,95,88,106,195,77,15,56,32,28,208,193,70,120,203,239,202,69,56,13,170,75,219,7,136,123,181,167,49,243,36,53,99,111,3,197,237,7,222,214,
92,225,114,251,193,82,225,156,227,191,187,68,147,170,233,219,140,81,83,246,82,225,101,94,105,222,64,237,110,141,104,48,99,196,84,197,46,57,192,152,183,142,160,181,74,218,240,123,14,108,176,48,28,192,57,
114,116,12,193,50,58,101,71,244,36,36,238,105,102,149,61,88,245,237,146,170,32,24,30,98,164,2,115,209,248,229,67,136,216,195,9,201,137,138,193,111,181,154,0,215,44,156,198,3,93,23,72,178,142,136,197,141,
3,14,157,202,95,111,243,126,246,138,8,243,50,179,174,10,120,57,132,129,100,163,166,60,244,184,0,205,60,90,119,111,81,11,6,143,70,21,253,88,111,171,138,251,254,249,164,141,111,150,174,206,142,252,177,120,
150,57,35,107,193,183,148,58,147,93,201,3,13,193,4,213,67,4,182,153,87,159,154,91,125,25,246,20,170,30,4,114,237,245,132,94,221,106,218,174,165,71,117,103,197,55,233,93,84,153,166,227,254,11,191,143,158,
221,3,117,236,214,153,168,177,176,197,64,182,14,113,129,52,89,252,229,242,21,131,118,172,148,5,185,43,80,69,128,123,209,177,212,6,38,218,36,184,41,229,157,47,49,12,145,159,78,113,175,23,188,23,162,183,
184,189,81,115,251,112,27,80,124,106,143,22,122,127,180,181,218,112,34,80,216,59,118,107,13,126,105,60,207,141,180,24,76,244,120,46,87,154,133,230,35,114,254,14,213,80,164,33,82,184,118,0,236,22,96,186,
181,44,242,14,42,175,22,158,97,111,151,86,201,120,31,136,65,191,106,39,181,255,96,42,90,142,125,113,196,106,125,81,0,0,32,0,73,68,65,84,105,173,142,121,183,103,88,90,131,156,57,217,19,78,222,8,188,46,
84,184,117,34,217,2,222,52,65,114,102,158,103,190,252,245,87,98,136,239,186,218,138,235,80,239,101,238,14,172,214,118,156,77,171,141,188,24,214,126,149,215,218,8,131,199,15,145,38,78,83,216,58,121,188,
181,10,57,241,45,127,219,143,184,247,123,146,173,227,176,220,246,218,217,58,136,46,240,229,223,254,206,125,93,144,37,227,221,16,137,118,160,85,56,60,63,16,4,76,84,179,245,128,87,154,82,199,63,101,1,226,
219,212,102,91,108,111,71,144,72,101,232,215,54,24,130,11,56,91,145,166,35,47,36,242,225,168,5,251,24,227,238,234,122,63,192,94,37,246,218,121,187,61,29,79,167,129,33,122,102,55,227,127,254,203,63,96,
129,44,5,87,254,211,110,95,95,150,68,222,182,244,242,182,247,205,100,181,72,134,240,67,29,177,165,165,237,133,77,191,12,232,65,99,54,101,106,18,230,82,152,215,198,171,250,236,9,61,27,119,43,5,130,211,
114,73,122,123,134,183,196,227,136,159,50,88,193,127,59,175,187,221,236,251,85,168,203,69,167,146,61,146,48,198,177,175,20,76,151,185,24,154,4,196,189,233,26,52,124,65,139,242,121,86,179,136,169,96,109,
192,199,17,55,158,120,234,108,32,141,33,210,38,212,89,163,132,253,62,225,105,173,177,204,115,239,186,149,106,42,8,51,66,166,177,58,240,46,198,254,181,58,236,47,159,25,131,218,208,151,85,221,136,21,183,
223,72,198,91,60,78,33,21,152,254,15,214,182,203,25,163,228,37,97,255,203,171,49,148,62,197,79,61,104,175,72,192,140,145,216,159,211,86,155,202,33,251,132,212,154,10,30,53,95,213,134,113,14,153,6,44,194,
112,112,248,220,115,151,13,141,101,94,200,87,161,208,148,193,179,197,87,0,222,105,96,238,158,93,103,45,155,158,206,244,16,221,24,148,144,32,82,251,213,195,126,214,10,58,198,119,163,223,245,16,69,74,23,
66,183,94,160,111,75,70,45,93,107,47,144,188,213,110,164,149,134,167,36,16,152,91,227,219,175,127,103,28,223,90,120,231,71,90,113,106,106,221,112,102,183,244,150,6,216,111,178,205,158,211,162,167,46,125,
66,31,254,67,242,187,235,25,28,168,90,106,233,105,108,27,240,83,187,155,70,78,171,22,239,14,36,169,243,224,229,242,2,168,214,200,203,237,69,175,225,156,88,95,190,208,6,205,36,152,103,45,180,233,149,255,
233,120,218,247,106,206,88,164,207,136,183,150,189,25,131,196,128,195,234,167,153,122,35,218,239,143,106,245,92,54,132,29,16,61,58,77,166,106,61,34,49,165,204,105,24,48,232,162,6,84,71,36,49,106,102,157,
91,241,44,51,85,219,39,30,6,131,212,132,239,182,200,212,247,194,89,132,107,151,36,108,153,181,239,117,63,219,198,40,70,79,232,183,228,246,169,186,224,52,44,39,40,132,190,213,165,27,87,133,239,75,218,83,
4,135,81,5,211,183,156,104,69,73,165,173,87,107,231,111,175,100,89,185,190,204,248,84,142,88,175,227,147,148,79,196,81,165,225,193,8,182,85,14,143,234,197,144,69,117,238,211,193,50,223,23,132,134,15,74,
120,182,214,80,157,186,186,74,42,248,119,187,98,155,27,178,104,70,104,121,199,41,86,31,136,35,18,85,128,52,87,218,146,112,65,223,129,113,187,85,43,156,47,119,92,131,143,211,136,255,233,151,79,56,171,93,
110,88,254,164,95,81,83,79,134,20,193,155,200,195,113,194,253,228,120,74,153,203,245,149,105,24,250,196,38,80,127,108,235,72,77,222,233,218,106,151,33,190,133,53,76,227,64,238,78,197,237,191,171,210,95,
60,10,160,203,28,169,149,165,136,62,94,167,35,14,29,221,250,195,243,9,107,156,202,113,239,39,164,116,252,105,122,91,196,44,24,72,234,126,89,155,193,184,1,14,19,241,56,237,45,61,253,241,56,70,221,125,164,
92,58,216,94,119,21,165,135,72,26,28,247,148,88,146,46,218,143,211,200,116,26,186,12,76,39,160,82,42,247,251,202,235,109,86,10,211,243,9,107,26,203,61,227,175,41,97,49,84,26,223,110,111,57,2,41,101,130,
177,28,166,3,143,143,71,226,195,196,84,225,229,229,174,167,70,12,164,109,128,178,181,184,192,24,70,170,115,24,179,241,129,42,146,10,58,241,133,107,109,172,93,144,23,99,32,5,143,113,142,236,12,193,130,
157,6,109,82,75,219,94,3,194,252,68,110,43,132,136,95,150,89,241,251,52,150,52,99,99,196,162,109,191,193,34,8,151,121,198,46,61,142,123,28,104,75,151,19,164,186,15,2,183,128,189,37,111,197,78,135,61,86,
116,105,115,136,76,7,56,30,134,183,151,118,171,65,122,206,146,49,134,151,151,171,234,52,250,204,98,136,142,101,114,200,236,137,206,225,95,239,183,93,110,117,95,22,98,84,61,229,211,195,196,16,3,173,232,
170,43,215,74,181,150,211,52,144,66,163,73,166,108,78,195,108,168,178,21,228,14,143,197,111,235,3,187,205,144,116,127,124,187,223,213,84,221,79,138,210,87,19,49,170,232,233,233,121,34,205,122,11,14,209,
129,129,251,139,218,233,168,6,239,209,79,46,56,109,113,74,203,26,137,85,84,52,4,14,231,42,211,16,152,14,3,95,191,126,87,65,156,115,122,166,58,163,102,167,174,232,187,126,155,117,117,16,61,177,171,3,1,
76,81,39,162,208,246,200,89,17,233,235,134,66,21,15,62,114,145,210,161,167,112,110,153,38,141,191,253,251,239,172,139,106,235,124,201,69,225,237,222,145,110,11,197,37,114,209,31,104,140,19,209,40,206,
127,1,230,171,35,216,136,115,150,24,28,206,27,245,190,149,162,122,245,214,136,168,210,250,118,131,101,67,60,217,119,157,117,103,97,30,7,215,53,246,48,207,55,150,57,49,47,43,57,6,66,8,202,183,210,143,149,
49,58,30,38,15,173,224,15,198,96,189,210,113,157,100,88,43,135,56,18,140,199,227,153,83,166,244,122,152,224,49,81,215,88,243,93,246,56,43,87,245,128,55,173,225,205,68,106,26,164,16,198,128,75,134,215,
178,236,110,220,252,94,170,16,52,216,212,27,53,119,59,23,25,17,110,151,139,242,181,251,41,117,253,245,171,190,220,243,130,255,240,240,184,251,128,78,199,7,70,231,149,102,208,99,97,71,103,176,253,166,138,
222,243,116,156,104,181,117,158,73,161,101,217,119,116,214,89,166,216,21,171,81,23,59,107,21,204,44,148,161,81,93,165,173,130,57,41,37,116,154,70,156,105,44,235,202,245,114,35,45,5,113,3,69,170,58,192,
140,118,234,114,57,82,155,144,108,197,159,62,126,66,186,208,205,125,254,19,145,160,49,88,243,194,109,209,228,201,33,234,39,96,163,35,158,212,167,121,168,90,189,197,238,80,152,239,90,87,155,125,7,167,177,
153,78,132,102,221,190,238,61,30,39,150,37,245,226,167,232,89,228,7,166,147,103,108,149,148,3,86,68,77,175,13,82,90,73,205,83,197,145,20,136,225,169,78,11,229,108,149,145,106,162,199,5,79,140,73,93,221,
49,48,244,31,224,146,102,14,97,160,210,8,198,192,52,130,207,84,52,154,219,166,168,10,111,99,177,206,234,124,162,167,151,184,16,88,178,198,194,10,130,139,134,177,39,106,211,160,229,10,46,97,236,182,242,
18,230,219,130,161,116,96,50,248,89,82,151,199,8,215,156,0,97,154,70,226,20,113,131,238,120,245,191,213,249,196,195,225,191,170,150,248,50,115,78,137,33,233,39,93,151,7,198,49,210,98,218,31,17,172,195,
13,22,167,77,53,222,57,230,121,33,196,137,97,210,23,215,71,167,142,249,53,179,200,170,169,176,222,18,93,0,91,17,107,104,230,145,153,74,164,225,151,101,37,245,16,211,111,47,223,56,140,35,134,4,182,183,
70,253,23,154,183,31,98,250,127,104,247,202,124,95,73,37,51,44,110,239,48,238,226,246,136,77,221,154,246,89,70,215,2,75,66,117,150,181,145,110,137,34,153,232,148,201,26,188,1,11,185,70,108,177,42,216,
41,141,121,158,201,114,231,24,131,2,227,150,239,170,224,119,21,204,117,225,245,143,175,204,206,97,135,176,183,48,155,36,198,57,7,211,191,239,99,167,83,112,120,244,229,82,5,84,35,216,199,189,71,180,169,
193,172,210,198,220,11,249,233,56,208,170,16,68,200,61,215,163,39,160,98,13,180,226,89,170,32,65,53,247,181,20,220,245,119,252,113,192,25,240,127,126,58,244,184,55,225,240,237,129,117,233,235,167,38,180,
92,123,72,105,161,117,157,14,243,35,185,71,198,174,189,249,241,162,18,174,82,10,226,47,106,236,171,93,199,158,4,215,127,65,77,133,215,91,205,111,19,33,163,35,176,77,190,104,71,85,98,139,179,208,42,243,
178,242,229,95,255,7,95,170,176,204,5,111,15,159,201,86,231,0,238,151,255,194,243,84,181,178,74,237,141,225,96,100,215,234,4,127,220,213,217,181,234,152,116,151,28,118,222,246,70,251,106,173,105,220,85,
146,55,240,97,244,88,163,191,76,154,187,160,201,26,12,150,82,133,151,249,70,176,250,194,229,53,81,16,126,51,55,68,10,107,93,240,217,66,162,98,29,212,201,115,45,133,220,84,190,21,131,70,10,233,252,120,
155,207,153,31,172,17,161,211,110,157,115,132,148,112,198,238,121,227,185,8,83,46,59,59,83,93,5,149,224,125,127,182,117,246,32,181,33,73,47,161,143,252,244,38,85,207,9,145,198,231,95,70,106,91,185,47,
5,207,41,64,214,177,148,56,203,241,241,51,105,217,236,10,138,240,45,53,163,195,72,161,214,181,75,104,3,57,43,102,221,34,184,218,250,18,69,7,127,177,15,7,43,236,253,159,136,33,132,8,78,163,237,251,64,14,
111,29,238,24,153,234,192,53,173,123,151,29,6,199,104,45,206,126,208,17,238,154,240,37,117,6,171,179,228,150,185,189,156,117,36,133,99,136,126,39,118,24,83,177,52,230,86,113,46,236,146,219,117,93,251,
80,112,96,8,30,87,27,182,95,31,209,88,76,248,177,37,89,211,218,59,237,6,173,34,73,200,53,247,46,18,13,150,238,188,76,231,2,67,112,140,67,224,134,134,94,251,219,183,63,112,78,237,53,246,124,35,215,182,
151,137,121,13,224,93,95,160,8,182,107,224,153,19,243,146,118,47,179,15,158,241,209,50,89,199,154,85,166,32,89,246,102,212,97,8,93,87,252,116,140,250,195,234,162,148,66,163,182,66,233,142,48,89,19,247,
69,105,10,193,59,24,35,249,114,163,150,130,220,110,248,229,229,66,169,130,193,242,253,175,255,178,91,32,141,115,68,167,222,98,221,185,181,110,250,123,155,189,165,164,150,222,72,36,189,36,228,251,91,113,
179,166,244,22,39,27,52,115,99,136,142,245,188,25,163,180,208,175,187,250,167,225,58,71,133,190,118,195,58,194,224,201,223,191,32,85,112,107,194,139,44,212,92,104,34,220,190,191,192,113,130,46,3,75,125,
238,212,90,7,12,185,170,120,111,107,201,89,231,8,146,2,183,222,13,23,17,92,84,229,235,59,113,20,247,29,104,15,227,56,234,4,200,233,230,202,56,75,202,137,57,173,10,90,182,144,22,117,144,141,83,164,44,142,
219,203,87,210,109,38,173,5,255,112,58,168,46,34,120,124,251,153,178,108,179,134,31,85,33,42,147,53,12,147,150,133,215,235,76,185,36,238,233,182,171,84,93,112,56,215,8,142,31,78,138,114,91,153,251,78,
251,42,145,180,100,230,82,186,116,71,213,168,173,53,37,48,116,107,154,243,14,166,3,16,57,207,103,46,247,43,105,94,240,79,159,255,147,62,238,173,33,79,159,185,72,255,1,176,148,174,136,114,193,49,186,72,
69,152,5,214,102,88,106,196,140,143,156,142,61,9,173,131,16,105,7,150,101,221,183,155,26,107,97,184,223,103,94,111,87,142,79,142,188,188,15,128,82,183,204,125,158,89,238,11,79,241,200,233,48,236,82,222,
63,254,120,225,229,18,8,238,19,206,36,188,139,35,174,169,104,227,245,38,196,211,216,83,209,26,33,196,93,11,33,173,176,46,194,50,155,142,208,59,50,142,70,83,85,67,232,139,194,192,220,195,21,172,3,23,64,
234,138,180,134,241,149,135,83,196,5,67,112,94,101,236,221,216,146,75,65,234,9,169,149,81,17,42,164,92,88,146,240,244,112,32,254,252,129,15,79,35,88,240,243,185,235,19,74,65,238,130,12,221,71,228,76,191,
133,234,190,52,73,41,227,186,16,110,27,142,4,175,117,196,122,207,220,89,24,66,235,226,79,3,217,178,136,144,83,70,106,209,14,67,204,15,78,46,107,170,26,78,186,233,207,136,214,193,214,88,62,60,30,145,41,
242,210,46,180,90,185,92,102,252,229,250,109,119,197,150,58,115,253,126,235,179,96,186,96,179,96,173,101,24,180,200,193,174,36,73,44,233,109,35,191,141,168,52,17,45,48,47,11,77,42,195,168,41,127,218,204,
86,74,177,24,52,199,174,214,170,92,181,24,148,250,43,66,90,86,8,199,61,18,166,54,149,156,93,46,87,28,149,121,73,248,101,190,244,117,66,227,122,254,170,49,175,239,106,133,34,137,24,2,141,129,234,27,214,
105,124,230,134,216,219,43,51,107,137,120,238,23,184,222,103,242,90,152,14,3,229,48,97,92,219,207,99,41,250,73,98,33,122,75,106,106,189,164,191,116,231,203,69,107,240,34,196,193,209,138,240,245,203,11,
99,103,169,248,15,207,15,56,163,254,92,57,31,41,197,117,206,187,154,85,141,137,4,231,113,81,215,90,247,245,186,47,21,183,32,233,70,85,162,171,131,33,40,192,37,15,250,210,137,40,165,6,1,187,5,234,89,131,
243,150,117,209,241,215,114,93,181,59,30,34,172,22,23,13,96,177,213,51,47,43,215,243,11,215,170,12,21,31,77,68,151,54,149,99,156,8,147,99,137,142,44,177,103,214,182,125,224,156,83,38,78,31,137,62,188,
83,67,213,31,68,207,199,233,248,3,206,73,97,133,73,245,151,77,239,160,156,85,208,92,91,97,94,18,107,88,145,42,12,163,135,172,193,58,178,8,173,137,202,32,134,145,227,49,106,84,150,36,144,166,77,232,237,
154,137,46,189,169,169,36,247,73,188,223,243,7,26,26,190,183,149,148,82,85,178,168,106,192,192,249,124,221,73,249,214,88,76,127,105,203,82,200,69,173,198,203,178,32,77,193,2,211,24,153,98,232,38,64,171,
130,16,44,197,89,164,90,252,96,25,221,137,211,52,242,33,37,252,82,174,234,159,40,194,117,190,176,174,189,68,140,94,189,242,253,211,219,220,4,137,204,225,168,32,151,109,27,250,120,58,50,140,129,146,22,
150,69,125,201,198,90,164,19,188,36,233,47,37,61,123,17,26,62,244,173,212,172,117,131,11,142,113,240,56,28,107,18,114,82,159,211,49,70,92,152,152,175,137,235,53,225,47,223,191,43,241,176,84,238,231,87,
76,116,250,14,38,233,158,101,219,107,135,153,203,245,198,135,199,19,107,155,117,39,215,51,149,175,61,201,93,68,27,216,205,246,43,89,213,44,123,33,100,45,181,10,193,25,98,140,196,96,105,162,233,20,2,220,
157,193,197,105,215,209,149,98,184,214,198,235,183,51,243,101,225,62,175,120,23,29,221,187,219,133,21,42,65,92,250,250,127,24,35,143,15,71,254,244,57,238,143,202,15,112,45,160,244,34,125,219,140,110,131,
190,85,20,169,234,156,83,159,145,115,60,127,56,144,171,26,161,74,89,73,219,124,205,178,27,167,252,59,129,135,17,21,87,184,232,56,184,9,255,231,159,127,102,157,87,114,201,12,243,39,82,147,125,95,177,105,
114,54,254,131,116,185,193,230,146,125,111,150,206,69,67,169,101,235,64,188,227,233,233,164,234,86,171,203,195,33,6,160,178,150,194,154,87,46,103,65,156,16,199,168,108,249,224,48,131,102,212,185,78,6,
161,239,95,252,56,232,46,102,189,207,220,150,133,101,78,156,191,95,58,239,119,216,169,5,235,186,106,198,76,240,250,201,209,118,151,97,201,101,95,200,4,239,145,88,57,197,184,83,204,7,223,141,129,171,202,
24,46,87,117,59,58,91,241,206,243,244,56,209,166,81,103,193,93,212,87,138,33,217,178,75,208,182,213,153,243,250,255,227,111,203,140,228,172,122,156,154,57,223,238,220,239,189,169,236,230,212,231,231,7,
30,30,142,125,89,29,247,213,150,174,37,250,95,183,147,23,11,75,17,210,188,112,183,96,170,238,252,54,21,182,9,6,107,84,156,138,40,71,219,245,14,185,165,134,139,145,136,131,136,130,60,141,99,114,15,29,150,
95,241,215,45,88,9,195,186,36,158,30,79,251,215,177,205,37,140,177,148,46,246,64,242,62,248,219,38,60,69,230,157,40,115,187,205,253,145,89,104,169,187,189,125,23,61,43,171,147,154,27,82,20,35,137,69,141,
128,182,43,82,54,9,101,15,85,247,206,177,156,191,170,2,183,86,188,247,145,96,13,198,57,30,30,143,124,59,95,84,118,187,201,98,186,134,173,181,218,81,168,202,111,119,206,233,244,209,154,125,215,182,77,121,
68,132,18,53,109,88,191,111,11,61,41,32,39,221,188,150,222,73,59,111,20,30,87,155,214,193,147,199,25,199,216,213,2,181,86,238,181,210,178,168,112,105,124,126,36,246,193,242,249,219,132,77,25,63,70,101,
99,23,225,122,189,235,150,211,7,240,1,215,155,202,224,157,110,248,231,196,82,210,206,114,101,49,196,33,112,58,77,24,231,122,175,105,118,193,242,150,22,81,77,192,68,13,102,40,86,59,156,113,178,12,97,162,
73,101,78,43,41,137,134,146,136,199,185,192,207,143,19,94,230,204,77,180,196,156,207,55,150,235,76,186,173,164,206,125,112,85,59,217,97,99,241,24,181,0,75,183,88,230,57,237,195,234,77,19,219,128,92,208,
111,14,219,247,111,154,163,20,93,0,87,209,21,181,218,34,98,151,231,208,90,71,171,54,92,133,201,169,234,123,137,134,49,128,31,44,158,90,41,249,205,213,245,249,211,51,247,121,97,190,175,92,251,209,21,182,
175,63,56,174,203,13,105,29,12,30,35,77,222,116,146,206,88,210,146,72,107,34,147,184,95,44,217,244,113,87,74,52,129,105,8,125,81,99,40,146,104,125,34,228,189,6,235,29,135,131,110,73,131,223,91,52,190,
193,125,209,73,134,159,142,7,166,195,8,198,194,245,145,218,50,227,112,196,124,60,169,197,172,219,196,180,207,243,92,151,9,105,122,124,237,226,164,94,232,180,62,186,18,201,172,243,74,154,43,46,23,156,85,
249,110,107,130,119,65,13,39,214,112,187,53,174,151,68,74,122,220,29,91,68,178,82,70,131,211,170,113,77,133,47,223,94,244,10,175,173,239,73,141,129,38,204,243,109,215,242,232,95,62,107,62,129,8,62,122,
142,211,200,105,28,17,41,111,190,205,90,119,91,133,177,150,216,186,135,41,120,156,21,38,28,212,128,88,29,158,44,243,77,31,131,232,24,220,196,105,242,106,121,235,181,196,225,249,153,161,119,222,231,243,
43,183,121,37,198,79,74,173,169,130,191,93,95,247,206,248,235,215,239,250,245,247,76,196,33,6,74,103,175,149,53,113,45,194,112,136,164,82,112,198,48,175,150,188,232,12,34,39,61,236,31,167,46,196,171,10,
3,176,86,201,185,221,180,169,117,11,133,180,168,22,238,233,113,192,121,219,55,77,149,57,205,164,170,8,135,57,175,164,188,80,91,193,57,125,116,61,198,82,146,108,147,174,157,141,61,207,139,46,200,243,155,
116,54,6,79,170,157,119,50,141,140,198,17,39,125,246,82,40,132,232,181,202,234,117,128,21,131,72,37,201,157,44,186,18,56,61,110,3,112,200,82,201,87,37,224,180,222,245,212,160,22,9,215,59,140,38,141,235,
101,193,89,225,118,75,120,203,219,236,75,51,62,13,33,24,106,181,164,172,22,248,128,233,143,137,176,44,101,119,182,72,252,209,130,233,177,16,21,233,111,106,165,101,221,238,231,110,124,165,53,254,246,235,
204,52,69,14,163,66,13,115,210,23,47,68,13,3,94,114,102,190,170,215,195,69,195,178,20,254,248,242,77,9,190,5,252,211,79,127,218,31,137,249,247,127,213,56,227,37,49,140,145,207,79,159,241,61,201,79,121,
128,137,90,150,93,94,96,187,253,172,100,93,129,41,232,66,213,215,209,89,48,26,26,89,81,190,118,94,19,227,113,192,187,160,96,206,214,56,156,142,68,231,201,146,88,68,184,206,133,232,66,111,147,32,6,199,
135,167,7,16,75,105,25,63,109,72,102,224,231,95,126,129,44,36,218,142,215,253,97,93,0,220,175,215,221,42,97,187,123,124,219,233,1,68,219,20,122,223,47,13,21,145,102,146,211,231,215,164,202,233,56,226,
64,219,163,121,97,73,137,41,158,248,52,5,36,14,111,214,227,146,201,73,184,63,234,180,212,209,240,255,250,111,191,235,215,238,60,95,126,59,19,157,62,199,185,212,174,5,42,123,141,218,90,69,137,36,150,42,
244,231,78,239,251,97,242,221,111,164,147,206,188,118,200,133,49,36,42,173,40,32,99,56,245,108,165,156,112,227,200,199,199,83,159,83,116,202,130,83,218,93,149,198,109,73,80,51,206,13,196,104,25,140,193,
79,143,167,190,87,30,24,249,207,92,190,189,144,114,225,251,69,253,249,213,41,204,216,71,221,21,27,125,249,49,218,153,235,100,200,25,173,214,36,115,147,68,90,10,243,245,78,106,154,247,117,205,11,121,209,
208,94,103,103,162,119,58,147,238,83,252,219,146,136,193,112,58,78,172,27,100,163,54,106,81,51,235,114,159,117,177,233,192,159,142,7,165,12,24,21,89,252,183,255,249,191,144,82,97,158,23,214,37,105,51,
25,244,209,88,147,158,4,161,119,16,219,34,197,117,157,113,202,153,116,190,18,163,16,195,64,244,129,15,79,39,196,235,248,63,232,60,129,53,9,107,39,132,136,84,124,46,208,96,60,68,142,125,89,147,187,58,208,
57,203,221,117,41,141,20,124,145,2,93,218,253,242,242,157,95,127,253,187,102,113,60,29,153,78,3,99,28,116,20,149,51,198,57,198,97,80,253,111,23,40,167,148,185,46,51,121,78,172,41,225,68,103,205,54,6,220,
16,49,163,103,112,22,162,65,114,225,195,227,129,215,219,204,250,77,77,84,159,62,60,40,245,188,251,75,63,124,122,212,226,189,8,165,234,163,146,47,176,148,21,201,13,127,187,93,112,157,75,178,174,179,134,
232,24,225,54,111,202,126,118,65,198,56,68,94,46,141,104,222,196,113,82,4,138,142,248,79,167,72,112,58,142,178,93,253,183,150,25,68,197,168,183,121,230,251,245,130,115,150,106,132,181,22,126,251,190,244,
69,142,22,64,175,255,126,87,207,191,115,184,104,9,222,171,98,0,52,143,195,69,45,98,0,110,147,199,197,216,227,84,42,146,212,10,121,187,207,204,57,107,86,81,8,148,62,209,172,173,41,99,187,8,195,16,57,30,
35,215,36,157,206,97,185,151,204,156,238,12,211,192,232,3,107,21,234,172,90,12,41,133,82,203,174,146,125,189,220,152,211,162,185,141,104,137,186,251,159,94,245,48,24,7,143,143,46,118,177,167,99,140,35,
102,82,118,84,200,170,251,93,114,82,152,219,164,199,77,20,179,107,117,114,22,136,149,149,132,52,45,246,29,166,7,140,36,176,112,154,130,214,219,214,50,48,145,130,33,122,71,177,142,251,37,115,62,95,240,
78,229,8,67,60,226,156,110,78,75,82,173,219,60,207,252,250,111,127,199,88,225,241,225,160,122,207,90,133,44,153,151,151,11,83,86,72,64,64,161,220,182,27,170,99,119,198,228,37,239,90,203,24,116,223,182,
137,140,92,175,200,134,33,112,42,35,43,125,91,132,80,115,163,80,137,222,18,131,238,253,158,78,35,167,99,100,136,97,63,231,99,116,123,70,232,245,182,144,91,85,181,182,55,72,19,252,216,179,64,43,149,211,
243,9,89,10,49,58,30,199,17,59,233,148,242,190,36,13,12,41,11,107,122,203,33,80,19,149,217,143,33,73,133,96,13,33,58,66,48,180,84,88,36,147,18,52,73,212,10,110,116,148,254,146,75,251,209,143,212,222,137,
248,157,119,76,83,196,71,135,147,89,35,90,28,248,203,253,170,218,95,11,146,11,209,106,20,214,101,77,88,233,211,155,174,136,42,14,166,195,208,53,152,149,86,133,36,58,146,205,169,32,185,18,131,170,174,13,
144,22,97,109,25,99,250,252,185,9,183,89,24,163,74,110,135,78,96,218,124,212,89,132,145,198,146,87,202,134,173,233,107,198,224,28,147,183,248,188,36,196,57,92,80,1,179,43,176,102,53,121,108,134,105,13,
20,209,63,186,5,164,255,8,99,17,245,224,59,163,190,229,142,113,72,105,37,137,194,54,107,170,20,41,234,249,159,6,142,227,168,222,230,180,246,0,83,173,204,78,143,145,219,188,16,186,66,220,24,203,124,239,
239,136,119,232,168,67,4,105,116,57,64,247,49,47,121,31,146,108,210,241,210,10,174,249,174,115,171,228,220,222,44,15,253,235,12,209,146,175,80,82,226,134,244,217,89,85,124,31,186,60,76,146,185,222,239,
90,241,137,128,129,56,68,78,71,253,97,243,90,144,119,100,154,111,223,239,212,170,41,109,126,234,125,89,213,195,146,220,225,41,66,163,149,142,224,245,134,163,27,192,77,239,106,230,205,252,212,231,109,73,
15,254,36,9,231,42,227,227,196,135,41,118,74,130,128,232,16,123,51,67,174,243,162,41,150,183,133,210,164,223,130,240,244,112,164,76,153,235,109,229,143,151,43,41,37,110,183,59,211,20,112,222,226,67,112,
184,232,169,8,167,211,208,199,173,1,111,157,210,157,129,36,141,82,5,105,185,187,108,235,62,97,172,162,196,196,148,51,235,156,240,193,235,11,130,16,209,243,124,158,23,74,21,162,11,186,76,236,229,230,79,
99,228,225,116,228,122,83,144,109,74,25,169,137,195,52,112,58,61,241,112,82,121,78,250,228,245,157,88,11,222,212,30,2,82,27,235,93,9,225,198,26,232,72,211,173,223,113,205,97,196,64,126,43,39,141,133,34,
133,60,175,170,226,158,38,134,48,234,189,79,195,10,152,44,132,172,196,254,218,22,82,71,231,172,178,32,189,115,249,116,60,146,167,131,46,200,123,2,90,89,50,147,117,221,89,163,154,230,228,51,190,53,233,
78,216,186,175,0,106,110,180,119,199,215,222,198,123,7,165,105,58,74,107,200,146,245,252,237,195,64,128,235,178,236,203,239,214,165,92,123,220,80,83,137,130,177,22,111,45,174,231,150,207,89,200,37,97,
141,99,78,183,221,88,181,173,194,228,122,99,77,69,213,227,183,101,161,74,163,137,176,44,43,205,242,163,216,30,209,232,172,212,149,168,169,48,142,131,238,142,71,85,243,5,20,181,115,189,207,8,90,228,148,
38,172,201,171,99,192,26,114,23,243,223,211,194,48,69,98,120,139,207,42,125,82,25,199,160,94,125,204,206,29,108,77,229,188,84,24,92,196,63,30,143,212,10,69,18,243,52,98,250,39,185,101,110,108,108,202,
29,193,208,53,93,89,20,142,24,241,140,147,246,99,143,167,71,110,243,204,53,205,164,53,239,93,72,238,3,239,53,37,134,211,176,127,226,69,132,180,20,110,183,155,62,159,131,231,231,79,207,88,231,153,70,187,
195,228,242,171,6,242,45,69,121,253,196,41,224,154,99,56,142,255,31,182,143,177,22,215,33,87,120,207,24,70,238,243,66,190,221,145,82,152,215,66,153,165,19,201,71,30,142,19,33,58,150,168,182,72,31,116,
136,82,139,242,172,162,123,243,25,181,10,60,52,230,211,129,44,133,232,34,143,207,71,85,139,167,194,210,39,82,238,54,33,34,132,209,226,47,247,59,92,117,50,249,239,191,254,174,221,133,247,132,240,110,115,
180,69,90,137,80,214,51,146,5,23,96,24,130,222,241,171,112,190,222,185,166,85,251,176,170,106,42,11,12,163,239,26,75,165,200,220,151,123,63,121,58,124,206,185,30,16,41,16,18,223,94,228,135,233,251,134,
36,209,140,59,240,167,195,212,129,243,194,211,211,195,142,101,138,239,10,18,17,193,164,76,177,134,41,132,254,120,44,180,82,145,173,46,160,178,92,87,26,186,49,202,89,72,105,133,171,246,139,244,233,230,
113,140,56,167,211,125,219,185,217,214,26,142,163,222,106,95,206,47,140,83,228,52,77,76,227,160,171,139,249,149,219,101,70,22,209,106,205,245,201,228,212,241,12,239,205,213,155,79,233,120,210,40,171,229,
158,113,226,40,70,161,220,209,4,78,61,14,118,41,169,107,247,149,108,187,166,85,119,115,70,47,12,41,194,195,105,98,240,129,220,68,227,145,129,150,213,183,97,29,60,63,61,82,155,112,91,87,174,179,138,167,
231,111,23,237,184,141,195,207,115,218,39,59,215,235,186,111,145,66,120,51,245,109,128,162,24,125,207,11,175,29,243,228,168,185,242,245,251,133,53,39,205,17,181,202,165,176,64,90,82,119,41,122,114,105,
164,37,179,228,68,43,85,53,151,64,90,212,236,122,154,38,253,133,158,244,54,157,123,160,106,73,153,226,3,167,227,128,168,105,66,117,54,22,205,248,86,117,158,217,61,110,42,166,215,56,182,195,113,162,245,
51,179,228,68,154,179,126,253,85,99,59,99,127,132,202,162,107,217,86,5,131,33,167,162,250,227,49,64,85,218,104,93,116,28,229,250,50,254,252,170,112,153,219,118,113,164,172,14,27,99,200,77,189,213,215,
121,197,127,252,168,60,190,82,26,249,241,128,244,137,140,115,238,7,183,150,198,35,69,132,140,177,130,115,145,193,69,44,125,235,89,133,36,73,147,44,151,132,20,144,106,180,46,106,66,75,224,189,225,231,79,
207,92,231,21,201,5,31,3,193,90,46,215,27,175,23,149,61,156,239,74,130,110,173,17,23,253,69,55,62,183,1,188,72,211,93,91,119,26,186,224,200,75,250,1,93,99,157,126,74,243,125,33,175,26,149,73,5,135,195,
133,160,3,144,86,137,54,242,225,97,218,173,197,85,116,127,183,137,243,171,232,120,107,138,81,179,159,163,103,154,34,198,168,111,197,59,207,71,167,117,70,107,250,8,101,201,136,27,57,198,1,169,71,252,245,
58,35,125,103,188,206,26,175,178,46,101,239,36,156,171,170,176,74,210,249,106,138,201,201,179,254,208,182,39,93,43,219,59,179,46,243,219,233,146,84,64,231,130,167,74,101,45,137,239,87,152,162,74,115,212,
207,177,238,81,3,198,89,138,148,29,98,203,59,181,183,186,45,13,190,245,161,69,90,18,191,254,253,11,159,126,122,214,56,139,211,113,247,129,214,214,5,28,209,67,52,100,9,36,151,187,165,65,143,171,101,205,
72,206,44,109,237,17,243,149,101,94,105,77,79,159,216,111,183,63,190,157,25,166,136,67,49,82,210,129,68,181,54,29,219,138,144,107,101,28,130,18,112,122,92,253,173,227,80,253,47,191,252,169,79,122,102,
218,249,51,243,178,226,172,74,184,134,81,107,101,157,74,54,61,178,156,37,84,71,152,28,18,245,49,74,146,32,163,93,73,111,26,91,85,122,152,100,221,111,184,65,215,179,219,15,59,134,136,137,48,167,85,167,
157,193,17,125,36,53,141,40,58,14,3,46,120,149,83,102,248,94,103,125,15,110,247,123,143,141,127,195,57,165,92,248,250,237,188,187,192,92,80,240,97,29,20,16,160,98,143,205,146,14,15,113,224,225,48,168,
101,189,107,208,106,213,115,58,247,222,236,48,68,134,209,243,229,219,43,203,188,224,188,103,136,142,34,101,231,5,130,118,30,54,9,211,56,236,118,206,101,81,237,194,48,121,252,249,54,171,164,92,42,127,127,
121,101,73,149,56,90,70,231,25,6,199,228,44,37,39,205,14,199,210,102,33,205,137,219,188,112,79,11,222,117,24,173,83,41,1,2,181,41,112,206,52,79,112,182,203,30,181,248,183,24,134,49,48,29,12,99,240,12,
167,19,121,210,171,124,41,137,243,107,34,173,153,219,235,204,211,131,186,36,255,248,122,38,207,186,35,245,34,138,131,30,71,135,124,254,248,3,229,51,162,15,191,148,196,42,26,73,24,122,32,233,227,227,129,
37,173,44,203,194,156,50,105,205,136,20,202,42,155,2,136,24,28,213,232,75,186,46,250,85,159,134,145,215,215,153,249,222,211,50,101,3,116,54,214,69,57,240,203,156,112,87,67,90,51,227,65,147,89,211,170,
90,98,255,56,141,136,100,178,52,202,60,67,112,208,31,145,212,231,190,209,57,14,199,73,87,81,151,43,75,223,55,11,141,105,28,121,60,30,73,146,73,75,226,230,181,195,117,40,110,103,26,70,126,254,164,173,255,
97,138,124,249,237,204,156,150,174,138,117,250,97,245,177,84,22,225,60,39,61,202,164,105,36,220,20,121,152,26,237,227,129,180,54,189,233,140,117,140,206,242,244,120,226,229,114,238,34,80,205,126,161,141,
204,93,104,68,133,201,193,154,18,203,170,242,45,31,3,167,41,118,189,186,234,41,157,81,107,89,171,77,37,138,223,243,174,160,61,29,7,61,81,170,48,246,139,233,214,247,128,37,11,196,200,24,34,226,148,156,
126,189,222,88,123,90,43,85,240,151,107,215,72,140,35,193,193,159,78,19,181,13,228,206,196,158,14,71,74,39,123,74,210,221,243,116,60,113,120,116,218,93,87,173,115,91,133,210,23,60,198,233,53,239,195,168,
163,130,252,246,82,13,209,171,131,193,89,237,237,250,104,85,47,8,112,77,136,126,196,72,165,53,67,244,150,112,90,145,162,68,105,127,156,34,183,121,230,182,220,56,127,251,198,231,211,164,107,168,158,24,
33,107,226,150,86,230,91,238,187,96,149,49,142,67,236,74,65,118,240,197,109,77,124,127,121,65,146,112,35,17,202,27,65,55,56,135,179,142,223,95,95,251,181,236,251,48,229,109,193,99,123,132,133,102,43,109,
32,241,17,103,61,185,222,169,106,74,19,198,77,85,242,48,113,185,94,212,32,82,114,87,159,120,82,43,80,93,47,110,28,247,57,113,157,87,162,55,184,16,24,163,211,114,114,89,58,71,88,57,106,209,71,230,57,105,
248,66,42,72,89,123,28,103,86,196,84,149,119,80,35,253,161,183,166,33,117,80,162,212,202,253,114,101,158,239,152,98,240,41,21,150,121,1,103,57,127,251,206,195,24,176,147,101,66,213,81,46,198,62,114,162,
175,167,132,67,212,79,54,73,65,36,51,207,10,96,121,56,30,73,185,95,181,155,47,195,89,38,55,242,225,193,211,154,112,189,45,44,201,49,198,192,195,233,216,117,241,111,143,69,42,137,113,24,119,128,189,31,
2,14,225,225,56,242,116,154,240,183,116,215,73,183,115,196,99,224,53,55,101,66,84,209,165,200,114,213,165,94,18,46,34,72,30,58,56,78,35,140,211,154,116,119,236,131,218,138,163,163,44,9,99,29,143,15,19,
206,121,150,53,113,158,175,93,206,42,16,44,55,201,48,175,64,227,54,207,251,39,125,156,38,206,243,43,167,105,34,151,130,193,242,244,52,49,207,51,98,5,255,252,248,19,62,170,108,209,92,62,114,233,112,56,
103,58,31,194,169,40,46,244,130,59,14,71,82,17,76,215,77,204,105,133,46,22,149,164,159,146,115,93,252,81,50,78,132,36,185,131,189,209,105,103,18,150,84,104,99,195,121,85,187,108,181,239,156,22,230,235,
202,50,235,38,63,58,71,116,194,229,114,81,88,210,223,126,127,81,93,58,240,247,127,253,194,173,39,157,109,203,110,235,212,67,175,172,42,139,117,87,150,172,251,97,29,209,234,226,196,161,159,184,14,188,27,
38,56,188,51,187,6,109,156,52,248,41,245,2,189,73,85,173,59,141,37,103,166,81,23,44,55,110,0,0,32,0,73,68,65,84,149,128,167,97,164,110,33,141,70,45,22,70,32,226,16,4,111,9,228,162,232,60,99,3,79,143,227,
15,212,80,16,134,16,116,178,35,144,157,80,87,131,100,109,97,194,164,245,131,166,174,106,167,64,135,122,90,107,59,81,198,210,209,171,28,199,135,46,150,54,12,157,63,156,68,56,29,6,53,165,220,202,142,147,
218,94,196,72,102,89,11,193,11,254,127,250,199,191,236,207,207,99,84,125,194,158,217,217,141,32,219,196,177,150,74,201,9,201,133,165,100,197,227,120,71,67,185,19,209,186,77,90,185,15,11,165,10,243,178,
112,121,157,153,151,244,70,14,171,6,188,42,254,134,108,222,132,36,178,73,40,245,217,95,214,196,45,221,148,80,110,5,191,246,183,90,146,240,251,215,63,148,8,243,174,197,87,214,109,69,22,33,173,133,91,90,
176,70,211,27,156,177,189,227,86,182,137,247,93,96,154,84,101,242,30,98,216,154,32,185,241,235,151,47,122,1,45,11,177,251,157,54,64,226,188,36,108,210,26,196,24,203,154,50,203,146,184,189,94,149,132,80,
51,254,255,250,231,255,129,179,150,148,51,255,244,191,255,31,140,147,123,71,77,204,125,167,210,52,83,188,100,78,241,196,113,82,183,75,78,58,176,222,150,130,198,90,142,83,212,153,111,74,138,106,232,146,
153,113,210,88,161,63,255,242,19,203,90,56,220,110,26,104,29,195,187,36,192,68,45,111,148,187,77,43,47,146,24,157,199,248,130,255,249,63,253,180,75,97,152,255,194,186,222,223,129,46,122,162,137,115,170,
53,107,141,90,35,79,167,9,23,2,37,43,169,166,37,33,139,198,191,166,156,249,40,106,3,138,33,80,105,170,109,7,98,28,152,198,110,79,43,31,127,96,253,76,83,164,229,202,52,158,180,136,154,215,93,156,234,154,
104,239,7,248,159,127,250,172,146,111,96,252,203,63,96,157,239,163,163,68,12,116,6,107,213,240,71,231,224,250,129,113,138,72,82,228,191,115,142,138,218,203,160,82,230,19,75,94,105,109,101,56,36,104,133,
121,122,33,215,149,224,80,63,104,8,196,209,19,189,35,21,121,131,224,79,224,236,72,56,78,44,139,178,129,156,119,68,179,121,253,51,254,229,219,69,115,189,154,102,183,108,98,26,83,27,214,194,124,91,152,239,
55,14,29,251,113,171,255,162,114,196,170,89,205,211,65,205,126,138,194,73,56,151,89,102,65,170,211,128,62,6,90,115,144,163,174,136,237,215,183,233,82,22,150,141,209,93,117,250,179,174,133,105,120,155,
112,26,107,58,83,101,214,243,250,203,215,239,138,83,104,194,191,253,243,95,9,83,36,90,61,59,157,129,203,249,198,235,203,121,23,43,199,41,245,96,105,24,135,128,173,17,59,13,58,172,94,22,230,180,57,20,44,
169,168,248,222,25,45,124,12,58,167,72,189,233,189,245,80,133,246,78,143,60,196,65,159,247,206,40,116,86,181,112,143,167,136,49,21,255,223,254,241,31,247,77,206,95,78,109,47,15,149,208,97,89,151,59,249,
182,66,233,122,9,249,207,52,218,238,77,154,198,200,48,141,180,34,61,122,240,66,52,14,108,97,145,59,141,85,141,220,17,172,171,76,83,100,89,85,107,188,205,127,227,110,100,49,92,231,43,67,232,251,238,237,
136,51,96,93,35,58,240,146,52,170,53,56,207,20,60,47,183,187,194,12,163,227,224,223,176,56,56,84,86,48,254,147,30,180,85,184,175,137,175,47,119,220,217,178,141,17,74,201,12,49,16,221,200,154,43,52,75,
92,28,46,68,205,180,237,131,241,82,244,69,149,170,211,255,13,188,44,61,255,110,205,153,210,169,118,6,205,1,1,139,127,189,92,137,49,178,2,191,254,245,119,196,66,202,25,239,44,119,107,20,30,175,96,92,6,
235,104,211,63,83,81,244,222,235,249,202,31,223,206,74,117,244,142,96,1,57,118,120,214,73,243,19,37,98,93,192,73,84,28,79,185,247,176,179,183,196,136,156,133,181,20,74,126,139,207,144,141,26,237,45,180,
70,73,170,116,241,159,63,61,227,186,159,104,121,62,32,206,146,83,230,195,20,123,93,90,160,101,76,238,54,156,246,191,41,220,226,0,229,88,72,159,179,166,4,31,213,112,242,229,143,223,9,206,169,228,166,117,
39,13,253,185,167,15,174,223,3,185,250,26,88,68,200,181,17,172,33,215,70,233,109,212,48,141,28,93,229,42,61,61,237,215,223,190,40,202,201,88,254,253,215,47,188,188,92,176,86,75,58,154,176,204,73,39,150,
181,114,58,68,156,63,168,175,83,90,79,93,171,202,232,113,158,181,100,110,247,188,171,89,165,104,46,162,166,85,110,63,116,103,102,111,25,186,49,246,1,246,136,143,158,24,28,41,11,223,207,87,238,215,153,
224,3,33,24,93,238,0,126,28,5,135,67,106,198,219,196,159,255,28,185,221,103,68,18,206,58,172,201,100,86,78,143,145,49,10,166,173,56,167,117,112,179,90,244,196,232,169,157,79,241,244,0,215,219,157,41,14,
196,201,34,165,246,252,174,168,50,6,247,164,211,253,160,115,232,247,84,253,214,42,212,64,12,150,211,167,103,236,231,79,122,105,53,53,186,54,105,120,111,38,166,233,192,52,141,124,254,95,254,87,110,243,
133,34,186,225,44,25,238,243,157,150,164,11,157,133,136,211,83,66,182,105,145,33,14,174,3,106,27,191,253,241,66,185,95,72,179,80,114,195,135,136,245,3,222,88,21,122,184,25,33,233,92,203,52,176,149,101,
77,93,195,150,64,142,12,99,228,116,58,240,112,24,59,157,127,37,207,250,45,249,235,124,99,158,117,67,255,183,127,250,63,145,42,29,160,210,119,222,69,25,72,82,133,156,23,162,213,175,200,96,245,57,43,69,
81,125,61,180,102,73,153,151,151,87,157,9,87,181,72,140,46,128,213,201,168,143,203,62,213,119,65,251,196,86,43,105,75,99,19,157,7,43,47,75,135,55,101,205,212,38,52,10,254,241,228,136,113,194,88,75,254,
60,225,156,97,153,117,242,62,198,9,231,33,205,137,218,10,144,9,18,53,248,220,217,55,185,150,110,102,180,254,168,149,229,31,158,25,99,36,165,153,44,181,207,102,26,227,168,154,206,255,151,172,119,233,146,
35,57,211,244,30,187,186,123,68,100,100,37,10,32,138,108,146,67,106,122,90,210,57,218,104,169,159,175,133,86,154,163,238,214,105,77,75,51,205,102,145,236,170,46,84,161,50,17,145,238,97,238,118,213,226,
179,112,128,18,119,117,0,2,200,8,119,179,239,242,190,207,123,187,173,44,33,238,156,171,82,42,111,6,161,32,200,233,210,216,98,34,70,225,80,120,39,64,142,193,27,236,203,243,134,241,242,230,254,240,195,149,
175,223,60,201,21,90,97,158,35,97,94,89,215,133,220,10,149,140,183,195,254,233,24,117,239,242,133,138,111,80,123,240,136,208,146,170,136,156,239,233,171,69,83,203,200,109,174,44,81,76,45,57,201,55,234,
39,197,249,232,177,230,89,216,43,49,73,167,157,146,108,66,69,202,137,157,198,55,251,90,96,48,111,120,125,105,124,243,254,107,198,163,227,37,207,68,21,120,122,124,194,27,33,104,140,222,83,242,125,233,215,
200,69,142,43,213,111,172,91,9,187,40,164,154,117,7,33,191,206,11,177,70,166,201,48,76,71,78,231,51,222,58,148,81,180,210,24,70,203,249,112,36,182,103,90,173,108,49,75,87,30,51,57,174,125,146,95,177,227,
0,21,121,33,204,47,31,185,133,27,167,179,70,171,198,116,234,33,175,85,12,169,206,2,250,6,90,150,226,185,100,249,218,250,172,45,27,67,82,61,103,70,3,117,165,104,169,37,98,125,38,197,196,37,124,148,220,
101,167,24,172,251,43,4,218,143,206,124,246,134,164,194,218,1,95,37,198,46,121,208,216,31,63,253,171,68,89,105,205,135,63,254,61,222,59,254,244,239,145,152,146,104,200,170,98,94,102,214,184,113,60,91,
160,67,12,1,167,132,109,25,195,138,50,226,166,109,125,251,233,172,230,122,189,201,218,203,27,81,87,123,195,211,233,204,122,19,44,251,198,190,197,21,192,109,209,196,235,1,227,220,231,232,205,36,139,243,
113,178,12,214,99,127,243,238,127,233,191,8,167,229,13,165,197,142,61,21,144,139,118,34,74,222,214,133,148,50,235,214,209,208,198,50,122,89,200,120,47,4,175,105,28,246,127,65,173,159,147,82,238,222,13,
63,58,82,202,188,188,92,104,165,113,60,77,120,99,191,152,254,20,178,250,249,175,148,86,41,23,76,151,152,157,142,30,91,234,66,169,18,77,97,92,230,52,62,10,191,186,20,230,37,211,90,162,70,25,91,201,138,
118,165,146,41,88,230,117,198,26,45,198,16,52,198,110,187,102,120,9,129,53,38,92,207,59,240,86,115,168,19,63,63,95,120,125,93,168,181,50,133,161,95,227,118,151,35,132,52,247,34,74,68,126,91,136,125,138,
47,9,175,246,187,159,255,243,94,105,253,248,195,63,240,250,169,238,98,140,254,81,129,110,160,42,218,21,180,217,246,117,85,205,34,31,40,37,201,26,182,74,56,158,235,199,155,234,96,240,210,1,90,110,148,190,
46,164,72,173,133,215,34,9,152,199,201,163,54,17,117,148,240,219,189,159,19,13,81,161,70,57,102,163,3,251,254,171,255,1,101,228,19,122,8,158,215,199,139,96,245,68,176,213,27,193,210,237,99,21,148,99,48,
10,227,141,12,91,114,194,40,35,66,36,96,180,174,255,0,242,194,228,36,211,160,47,73,231,143,158,125,22,176,63,122,125,26,239,223,249,255,31,118,221,245,252,16,135,198,14,238,61,218,42,177,139,77,11,191,
255,221,223,81,147,166,148,187,220,54,82,91,20,128,102,3,170,212,181,206,25,162,141,40,37,71,93,253,98,169,179,197,216,127,0,221,29,4,226,28,115,104,25,115,233,14,218,138,5,227,52,163,179,164,59,237,198,
127,16,184,237,42,69,83,105,149,212,163,102,146,2,251,199,127,255,95,133,208,97,12,63,255,241,239,185,254,189,156,24,220,115,35,250,39,44,148,13,64,199,94,35,223,191,106,73,107,21,236,111,197,123,49,79,
27,107,152,14,163,208,150,122,52,75,202,137,113,24,123,242,245,74,248,98,227,154,239,86,75,247,78,164,11,155,16,27,91,171,84,37,90,79,83,193,174,219,173,39,151,120,174,215,27,218,13,34,135,117,94,2,16,
80,180,146,73,217,179,165,136,31,61,235,45,80,239,48,139,110,130,58,158,79,156,188,76,54,47,47,175,125,106,35,132,15,103,100,194,83,74,97,54,146,247,217,238,33,101,94,186,116,89,237,106,198,73,224,179,
211,23,25,74,26,209,86,216,10,246,63,252,234,127,2,44,41,101,210,155,153,167,55,83,215,166,211,225,23,70,88,83,173,107,32,213,27,81,64,245,253,115,186,7,157,182,198,249,52,81,74,226,108,102,81,162,26,
131,86,166,179,217,76,31,5,136,130,85,107,205,52,120,134,195,64,76,145,249,26,68,6,113,148,148,97,231,13,234,206,105,67,244,69,202,128,253,197,47,222,237,103,222,169,252,2,221,157,138,90,105,201,228,90,
55,188,51,156,207,82,130,174,49,49,250,19,49,70,94,94,2,49,197,253,171,143,81,54,242,143,111,39,38,99,132,20,125,139,40,155,113,85,228,181,33,103,140,149,225,140,114,154,176,20,65,249,185,134,113,224,
171,151,252,163,210,200,77,30,153,211,228,121,60,29,133,166,251,227,143,63,129,18,75,227,229,227,39,84,151,135,123,107,105,78,230,91,215,215,153,151,143,87,74,43,132,146,241,86,44,18,226,198,90,165,142,
232,243,184,251,232,202,33,138,217,180,100,114,91,133,7,27,63,199,110,214,90,136,249,238,148,169,123,192,244,232,15,34,127,176,6,167,149,156,54,113,197,121,33,243,218,63,252,225,91,1,184,88,195,15,255,
242,167,157,229,39,103,237,40,253,86,140,189,35,107,44,115,160,213,94,184,123,233,6,106,145,244,169,113,242,188,190,206,196,36,66,163,211,52,98,27,84,4,202,169,80,253,34,17,12,246,125,128,98,180,234,201,
85,178,37,141,73,74,74,173,20,58,21,214,90,80,177,81,21,216,191,251,239,255,150,123,171,250,232,102,110,75,96,141,17,167,13,167,67,119,110,233,202,96,28,222,202,179,24,150,192,45,70,156,85,95,144,158,
37,32,213,24,196,206,160,217,3,27,74,10,148,40,174,129,161,227,124,219,189,43,118,82,248,15,222,163,181,98,89,34,37,53,145,7,199,66,88,35,138,198,105,178,104,52,246,221,251,55,187,158,221,46,143,188,246,
183,214,57,203,97,26,229,83,72,177,183,238,142,18,18,202,123,106,76,196,45,11,60,171,27,172,83,140,12,199,177,219,49,91,247,129,176,7,133,196,92,184,93,59,31,165,126,70,156,9,153,41,254,85,52,75,91,43,
175,97,35,111,137,193,43,40,85,248,195,255,215,63,255,75,255,20,18,127,254,47,255,200,120,150,0,233,209,15,12,198,16,195,74,140,145,9,81,144,156,143,71,42,50,223,189,188,204,108,97,219,11,151,18,19,79,
111,206,93,232,20,89,150,181,199,191,117,77,70,44,24,101,5,148,124,55,95,245,80,211,59,67,123,183,197,3,183,208,225,136,186,225,149,34,108,155,8,60,248,194,75,119,91,197,124,151,115,97,173,146,113,64,
74,104,227,200,177,240,122,189,237,95,171,211,160,71,191,211,112,91,149,77,191,178,50,228,246,206,49,14,6,165,37,122,211,104,131,197,145,123,201,168,122,206,179,233,117,240,61,114,235,254,107,90,127,37,
53,113,8,104,196,91,106,223,191,127,191,23,57,83,254,13,161,47,251,70,111,119,128,161,106,133,161,66,205,13,215,23,45,61,196,68,186,142,174,139,136,49,226,187,25,21,165,164,64,178,134,152,2,91,42,76,7,
71,188,137,14,232,142,67,29,58,83,254,75,72,65,8,171,72,195,78,114,43,134,121,134,30,75,107,253,228,49,125,29,235,219,215,92,151,173,71,37,139,192,238,189,31,4,106,81,101,218,174,186,81,80,247,163,233,
30,18,146,162,88,123,74,170,12,135,81,48,103,41,178,222,34,211,225,200,227,36,14,68,53,22,14,90,126,152,227,116,215,168,109,66,148,110,21,227,29,231,199,7,30,207,39,188,49,124,188,188,226,149,161,228,
196,188,204,216,15,63,125,236,192,110,199,245,251,159,40,21,182,173,131,179,98,162,22,217,186,27,52,24,37,133,75,95,182,148,34,195,110,163,12,165,137,126,71,209,251,185,36,103,171,152,198,21,75,201,132,
117,229,232,92,87,1,74,233,185,107,133,191,200,230,184,43,88,238,67,193,229,50,3,133,112,219,176,151,235,181,107,133,21,63,252,249,251,61,94,232,78,56,40,37,114,185,6,230,37,18,114,234,116,59,225,94,27,
43,136,179,169,155,5,161,113,91,226,125,129,36,66,15,37,30,254,45,102,82,220,24,191,144,75,222,125,122,222,89,180,145,111,224,238,223,187,199,42,43,173,216,194,141,210,18,41,37,236,227,89,160,132,169,
10,125,67,170,47,65,247,251,126,92,81,51,105,43,59,46,189,213,59,74,161,162,140,233,128,0,25,76,151,82,247,191,232,158,122,121,95,216,24,35,236,180,20,51,91,220,136,155,12,87,166,105,234,139,30,88,186,
140,44,103,161,55,122,239,41,49,176,109,145,84,34,246,252,120,150,133,97,45,108,95,61,98,233,76,108,37,104,200,82,51,53,86,97,180,91,215,43,92,67,39,145,72,160,100,111,249,161,226,173,151,89,178,182,34,
88,66,44,154,74,201,39,89,11,140,227,192,52,13,61,253,71,36,142,37,201,4,243,244,56,10,232,126,203,164,90,113,90,220,145,183,96,73,201,98,79,211,225,179,84,241,253,59,74,143,232,214,90,81,84,163,180,36,
60,246,250,197,178,176,175,109,161,145,170,136,147,239,147,31,17,55,203,114,93,55,249,61,30,69,138,242,117,207,69,178,16,78,39,47,3,195,209,9,166,164,67,229,76,231,186,21,39,17,69,185,54,76,44,28,78,134,
219,2,86,120,123,26,235,13,147,115,164,222,154,228,82,160,68,145,81,87,121,233,180,86,84,138,224,171,238,201,235,81,198,174,177,191,229,227,97,20,103,83,148,231,28,32,106,133,74,141,45,172,20,3,151,16,
248,233,123,137,84,78,95,66,61,71,203,235,117,222,255,59,22,25,247,214,94,49,206,243,21,251,237,183,127,166,244,56,149,239,255,235,63,224,238,27,2,39,68,103,45,187,2,208,138,164,26,215,235,44,58,75,235,
56,30,39,198,209,124,126,169,74,161,60,191,48,25,153,241,198,57,80,82,97,114,142,209,90,76,3,38,71,74,105,223,49,175,33,50,47,139,40,166,156,65,87,121,105,39,47,89,141,183,176,98,82,68,31,61,121,13,88,
133,190,195,95,4,60,111,12,202,200,215,98,154,116,191,227,52,50,141,242,201,165,55,79,56,47,154,246,45,202,179,107,187,32,142,46,71,172,165,178,213,72,9,167,61,142,219,24,9,148,28,71,191,31,99,247,12,
186,91,216,8,97,69,27,195,211,227,9,235,62,91,138,182,53,145,194,85,0,226,165,96,255,227,127,250,15,123,114,206,239,158,106,87,75,197,187,35,130,122,15,106,66,147,75,234,127,185,104,212,183,20,185,221,
2,49,137,189,125,156,60,167,211,68,204,137,53,109,232,73,186,139,221,94,209,237,15,74,240,95,2,145,179,150,243,121,218,195,251,110,97,67,111,138,211,105,236,200,6,205,237,146,187,199,46,98,127,252,225,
71,25,61,104,197,199,111,255,204,229,242,66,89,229,70,195,104,180,17,108,41,20,137,169,119,154,56,175,196,20,59,187,189,131,176,116,87,76,153,207,87,172,174,80,83,101,203,129,53,136,130,123,91,35,214,
153,221,125,62,118,252,164,240,126,4,15,5,112,58,28,120,56,203,129,240,242,195,71,74,137,164,148,177,175,75,232,199,79,229,249,249,153,97,48,248,158,59,59,12,3,222,88,14,253,140,124,221,54,158,175,87,
102,10,38,202,167,55,77,163,20,219,200,65,47,178,4,131,51,142,18,19,107,220,240,25,30,207,199,125,236,42,93,179,240,95,15,199,129,113,24,41,89,252,167,143,231,147,212,192,70,241,208,205,137,235,223,60,
9,85,194,20,236,127,252,221,111,247,113,235,251,241,85,10,24,99,25,70,143,83,221,154,227,69,157,241,102,139,188,125,251,176,59,110,111,243,141,45,165,46,91,148,173,125,42,229,243,45,25,86,98,116,164,90,
57,142,3,211,228,249,120,121,33,175,9,122,176,200,249,52,246,246,106,100,58,120,206,135,7,46,215,89,248,40,94,116,203,222,89,204,8,163,181,216,159,95,62,82,139,92,7,207,223,127,32,133,130,247,142,209,
121,33,192,196,184,19,233,98,159,35,88,47,128,129,45,172,50,84,233,200,40,238,177,223,247,88,184,158,32,21,99,34,214,72,206,121,159,74,230,222,70,253,224,158,247,177,212,113,18,132,229,117,190,237,213,
92,105,149,219,203,21,76,198,20,133,253,211,159,191,131,42,222,184,111,255,241,143,146,183,209,83,254,10,98,187,164,213,46,25,200,24,107,137,33,238,114,3,63,90,166,193,75,240,93,76,40,15,94,25,156,115,
187,71,46,23,169,198,114,17,91,132,181,118,255,135,199,53,179,246,96,168,117,203,156,31,30,177,214,98,250,0,102,141,25,239,52,5,69,204,13,251,254,253,219,142,20,51,248,249,215,40,154,212,178,227,32,167,
1,61,117,202,42,214,156,5,205,208,151,126,166,207,35,82,18,3,170,50,154,102,232,130,231,66,221,250,52,199,24,158,158,30,122,92,69,221,99,236,231,107,160,13,149,183,131,227,112,144,165,120,237,38,45,221,
65,158,169,86,76,124,149,213,92,137,216,223,254,250,215,253,163,47,60,150,95,226,156,148,120,186,118,200,102,202,29,248,58,145,90,69,215,192,193,123,140,51,108,33,112,189,74,210,165,114,210,144,182,36,
18,177,166,101,177,29,147,244,125,250,104,56,29,6,210,77,174,232,109,77,240,245,227,174,10,108,29,206,153,70,17,68,13,163,195,123,47,153,141,183,215,62,163,139,216,29,74,223,83,36,47,31,111,123,94,92,
136,129,176,238,92,6,182,53,242,213,209,117,25,215,231,225,159,28,103,22,216,48,42,239,147,160,149,194,22,34,75,16,198,251,221,83,84,186,87,78,27,181,7,83,219,158,228,234,244,180,59,112,75,207,233,8,215,
23,137,153,203,21,251,159,255,225,159,246,175,224,219,127,250,63,56,121,67,170,26,173,187,1,175,7,125,212,34,161,34,31,70,17,115,236,47,96,31,67,181,82,59,72,185,236,60,75,156,238,190,38,139,177,93,191,
147,213,222,100,254,127,255,23,115,225,233,225,180,135,160,214,174,84,153,127,126,230,86,18,164,140,125,255,238,23,224,4,128,60,44,191,129,38,226,124,235,68,158,232,156,221,255,130,146,11,225,14,49,234,
219,199,90,27,57,215,110,172,238,159,162,177,50,165,175,2,97,30,71,191,211,203,141,18,208,150,255,34,218,83,59,81,21,174,49,209,214,32,12,250,110,183,0,8,215,51,49,70,97,183,254,254,111,127,47,207,71,
107,188,169,191,234,206,151,206,54,243,66,14,167,8,31,176,118,173,131,238,106,88,107,32,230,218,39,65,236,156,192,113,180,50,112,185,163,168,41,196,36,250,8,163,213,95,229,122,1,127,21,200,110,123,235,
213,218,103,41,239,200,1,167,38,224,1,251,233,211,115,167,122,70,254,244,79,255,13,237,122,22,120,189,15,132,58,146,111,141,34,73,52,190,163,77,187,132,177,15,77,116,15,154,150,182,73,166,56,107,138,132,
18,137,189,214,173,95,100,222,166,34,63,68,201,89,122,187,78,146,158,58,76,32,165,76,105,149,82,26,243,203,71,180,174,194,151,248,215,111,255,208,51,14,43,255,207,119,127,166,198,72,79,142,147,178,178,
201,152,52,245,53,152,243,158,184,230,47,16,169,130,50,189,167,250,229,30,51,95,1,253,69,94,89,81,50,242,210,229,175,159,223,47,5,209,205,24,94,41,189,157,146,103,221,88,169,115,98,183,210,219,113,176,
88,231,192,91,126,255,251,247,184,123,22,98,44,40,103,187,133,172,171,165,71,135,103,218,103,194,159,85,127,109,255,106,133,191,86,228,219,112,30,172,98,141,97,247,59,221,175,245,193,57,124,119,193,220,
215,98,187,146,170,143,175,238,70,218,240,252,64,137,82,21,218,111,222,255,74,86,4,6,142,239,222,131,183,196,156,241,59,255,90,190,34,211,59,140,181,21,140,26,247,63,176,181,238,164,81,26,55,90,210,154,
63,99,36,91,165,150,202,105,60,139,22,174,100,252,232,250,26,226,51,229,192,28,167,157,125,165,156,162,165,182,147,29,83,173,56,167,241,227,196,169,106,236,157,107,41,173,117,229,186,205,168,238,200,154,
14,30,143,124,29,225,182,210,182,40,244,185,38,217,87,211,100,208,218,98,74,33,173,185,167,150,44,242,220,111,121,55,22,58,229,119,51,150,140,184,238,29,180,231,112,240,24,235,118,137,238,116,30,123,36,
226,23,192,219,169,66,147,241,149,253,210,86,243,154,34,215,109,197,149,198,141,5,126,170,123,58,154,51,6,235,12,71,235,187,62,190,18,95,197,111,44,75,108,41,144,150,24,104,69,239,42,41,235,12,88,195,
125,176,149,110,129,75,31,9,40,37,112,56,247,197,17,55,167,184,211,121,77,159,100,126,250,247,15,228,44,82,30,251,225,167,159,37,181,178,20,254,248,47,223,115,189,204,226,180,114,150,146,50,243,109,37,
149,196,104,36,59,49,7,153,184,235,14,146,77,177,244,103,83,239,179,98,165,62,71,211,27,44,126,8,251,118,243,62,245,185,103,61,151,214,88,99,34,132,149,16,34,110,18,165,246,29,69,57,122,207,117,190,18,
230,141,121,14,216,184,138,147,171,148,74,92,27,231,211,89,48,165,222,136,11,75,203,128,59,247,60,102,59,78,210,225,246,23,166,101,25,91,25,45,91,77,221,165,7,170,23,84,247,71,32,118,227,182,83,162,66,
185,79,45,239,20,133,146,68,168,183,228,184,219,230,197,22,225,56,122,77,60,5,94,47,55,236,239,127,247,223,129,146,120,215,67,252,153,209,202,122,42,244,232,137,248,182,50,120,215,55,161,138,126,112,236,
227,0,167,63,135,156,166,42,136,167,47,85,171,78,41,148,118,187,76,102,240,110,23,219,9,47,94,82,217,204,160,176,90,243,205,193,224,180,38,85,25,172,140,206,225,235,161,195,229,34,118,244,147,168,166,
91,4,20,177,84,20,6,235,61,42,85,49,92,27,135,30,20,53,55,198,147,80,19,77,17,194,184,82,29,2,238,100,107,68,71,163,75,29,220,165,229,74,158,233,152,128,156,249,202,219,253,27,18,132,234,231,99,210,150,
89,28,230,177,96,188,97,116,242,226,171,110,230,178,32,66,206,106,224,224,39,106,202,104,39,87,235,154,179,236,137,141,116,32,195,209,18,76,102,112,158,73,41,214,40,180,253,200,103,158,118,74,72,142,109,
169,221,60,210,122,157,32,88,145,55,211,68,28,43,62,182,207,140,193,248,25,121,58,186,194,245,42,11,73,179,26,46,237,198,79,127,249,11,107,167,42,216,63,252,215,255,77,190,106,55,242,225,219,255,29,221,
60,167,195,36,226,161,110,70,181,198,112,41,137,101,222,48,157,56,167,122,98,213,125,154,46,191,207,49,29,250,101,147,90,39,48,229,94,201,137,202,228,226,26,99,7,217,222,149,128,190,219,147,69,44,34,33,
104,201,72,130,224,218,10,63,127,248,129,53,38,162,42,216,24,35,37,86,140,143,108,243,70,140,55,46,47,159,228,102,214,236,153,91,208,136,57,177,124,204,251,56,85,108,56,226,151,211,221,178,222,138,163,
180,42,201,173,169,48,122,203,48,121,14,253,17,240,238,175,19,88,107,237,82,198,218,176,214,51,62,122,170,129,161,231,52,158,129,163,143,200,194,185,96,223,253,205,255,72,204,5,131,194,132,128,181,178,
141,47,57,97,148,237,88,95,249,90,83,203,188,251,173,237,127,25,123,137,152,118,91,101,101,190,5,44,48,84,133,55,178,187,27,156,163,85,69,8,81,224,225,247,80,6,111,73,173,177,133,77,98,49,180,32,159,252,
23,108,0,239,45,109,187,72,193,85,50,54,158,126,141,55,142,70,227,250,114,65,163,8,110,131,82,121,120,124,192,122,219,201,140,137,70,67,123,89,21,64,165,88,33,205,221,207,85,13,156,74,191,174,239,55,149,
115,48,14,162,95,79,101,231,247,40,173,72,189,174,176,185,236,211,167,119,205,96,172,21,218,65,17,91,70,228,194,84,19,33,45,216,199,211,131,216,122,21,168,111,222,131,150,221,132,65,11,145,192,136,79,
254,254,82,161,99,151,127,151,61,189,231,175,93,1,102,255,111,57,246,252,14,219,202,173,98,149,22,139,187,86,251,186,246,203,107,91,95,251,26,109,43,220,86,81,112,215,235,2,173,80,90,198,154,79,127,98,
63,84,190,255,39,17,117,118,190,94,49,226,165,215,173,220,23,9,20,34,206,171,93,69,125,31,205,74,114,160,40,81,188,17,8,70,105,138,237,11,41,76,220,26,97,93,24,250,75,38,143,94,217,137,230,37,23,202,100,
246,157,201,178,8,127,123,153,63,201,63,56,22,236,246,242,253,254,211,45,223,253,43,185,201,0,112,219,196,182,214,186,94,167,180,202,26,51,161,86,70,39,136,17,239,191,8,103,232,234,149,199,243,145,75,
18,221,100,8,177,15,255,220,174,23,126,122,58,179,25,185,225,106,145,148,138,252,5,163,42,108,154,233,224,123,34,74,36,181,68,201,159,200,181,144,106,198,82,26,67,7,201,166,211,72,43,6,213,83,80,231,209,
67,131,97,16,153,215,188,4,198,39,89,245,198,24,59,146,73,162,131,142,71,145,216,14,86,137,145,250,120,220,67,80,173,31,100,30,220,173,194,0,131,245,12,163,147,76,242,45,162,148,97,24,37,160,79,121,185,
25,63,5,193,160,149,199,177,223,242,21,107,30,79,104,35,201,104,250,116,196,106,17,121,141,106,226,196,27,104,26,65,169,120,222,54,131,27,164,248,14,113,229,245,122,67,233,207,152,135,88,50,195,225,81,
62,217,124,207,160,49,187,154,85,107,69,141,23,166,193,51,223,100,217,56,248,145,167,55,231,14,8,183,124,68,90,177,156,11,38,157,249,26,48,249,177,115,9,87,236,139,155,58,186,169,241,47,183,196,217,143,
24,219,89,236,198,99,141,84,76,146,214,39,138,41,213,52,17,8,253,76,213,61,44,212,218,137,237,214,219,255,97,144,14,197,251,126,235,9,2,173,153,119,60,140,71,154,151,205,210,166,53,63,222,54,184,202,15,
252,27,243,30,237,52,222,216,189,137,80,241,6,53,99,27,216,105,122,43,24,72,224,205,215,191,199,143,199,189,167,19,3,160,199,76,94,82,42,91,99,74,150,212,10,163,47,248,169,201,205,87,138,32,173,167,145,
215,122,237,5,186,237,108,42,211,235,140,142,180,94,69,73,24,194,231,1,206,244,120,146,201,191,82,188,191,137,168,95,120,219,146,93,179,93,94,89,163,28,181,246,155,225,36,221,174,179,188,127,251,75,201,
232,238,207,104,202,137,66,102,236,81,199,177,86,90,158,37,217,199,54,82,171,56,85,58,7,36,99,107,225,93,17,70,246,58,39,230,91,144,126,207,89,188,146,18,51,149,133,77,233,206,169,55,221,170,246,249,165,
251,169,55,169,254,11,22,253,53,252,64,184,6,82,44,216,219,79,223,97,250,200,104,254,238,191,225,162,40,66,194,182,114,93,111,148,156,80,70,2,194,36,59,81,92,5,173,138,77,114,151,113,101,73,246,137,169,
48,14,242,50,221,66,39,27,220,115,16,98,194,152,210,125,34,18,3,94,122,25,25,99,68,107,77,24,132,251,102,141,225,116,20,28,224,229,227,15,188,94,22,153,222,255,219,199,191,244,172,45,199,247,223,127,11,
89,83,146,32,207,215,156,104,53,119,215,85,167,210,28,11,231,118,148,154,121,21,45,143,119,98,168,78,49,115,52,19,69,203,190,162,152,74,85,133,218,227,92,172,49,100,38,150,20,216,154,97,168,189,39,116,
154,241,225,204,52,120,14,122,21,237,68,109,157,120,106,89,39,121,15,140,209,216,241,233,13,222,136,55,254,248,254,23,152,84,123,146,73,229,107,101,104,78,247,88,54,137,50,70,233,207,53,68,43,28,39,143,
49,150,82,114,119,35,234,189,99,88,111,146,85,32,14,68,67,75,141,53,87,252,53,112,58,142,28,78,3,90,153,61,183,195,59,199,201,188,163,148,207,3,23,165,52,191,125,186,210,138,228,227,218,247,143,223,96,
239,21,212,249,27,38,43,122,180,173,79,117,82,42,44,215,141,72,65,97,120,152,190,34,117,71,248,113,208,76,190,167,67,208,48,163,248,241,125,87,171,166,135,246,87,224,66,73,133,127,230,101,186,114,152,
36,233,181,244,245,217,18,68,254,168,253,21,107,36,226,232,62,253,49,245,134,166,82,109,193,62,156,37,116,166,180,202,227,195,145,98,20,134,196,168,155,216,24,170,161,190,117,24,245,128,55,71,26,97,31,
61,221,121,63,74,107,138,237,9,37,230,4,77,72,160,143,167,134,210,137,45,222,88,211,43,177,100,92,177,188,61,63,73,152,211,188,118,54,203,70,139,133,86,11,101,253,129,154,53,235,178,178,5,1,119,166,117,
150,188,69,97,6,74,92,160,1,198,227,35,203,178,176,109,137,249,150,72,49,116,94,154,103,242,17,239,103,244,36,221,132,119,162,178,26,239,128,161,168,72,69,145,227,139,64,234,47,43,207,151,32,35,129,38,
177,146,90,21,192,73,187,180,70,82,107,56,245,217,18,1,150,218,26,147,7,141,227,208,83,36,234,65,106,238,85,131,253,248,225,231,110,3,211,132,127,251,158,233,96,201,107,235,81,176,138,209,26,14,147,66,
243,74,43,175,148,77,212,215,151,57,9,11,51,110,98,90,93,133,239,186,133,107,47,252,29,163,21,11,133,55,159,131,76,135,190,9,141,70,56,221,169,54,106,18,118,124,14,6,147,87,22,235,196,173,85,228,2,9,243,
133,176,110,228,88,4,38,208,87,158,184,22,121,254,249,133,154,33,39,177,163,49,74,145,18,243,43,203,122,229,242,186,202,98,92,139,31,120,87,245,245,129,160,25,53,131,181,120,211,208,166,82,163,102,69,
134,224,219,26,9,221,232,29,115,220,203,203,82,132,0,169,123,166,129,42,34,205,169,27,100,91,88,98,148,249,91,1,251,195,79,223,246,1,156,229,211,199,63,81,75,38,231,74,188,137,122,117,26,193,249,74,229,
198,45,92,88,139,112,79,188,150,155,172,170,178,51,218,83,169,156,166,71,74,203,132,88,200,177,81,155,66,51,50,13,147,112,39,198,94,185,133,70,169,17,163,165,250,179,131,231,97,26,217,98,235,163,218,76,
118,89,148,87,109,197,140,142,188,21,172,50,173,59,100,13,143,39,39,85,86,145,174,66,227,240,163,97,154,140,228,118,150,194,243,188,118,228,216,103,112,125,105,159,245,148,26,73,144,72,171,164,254,148,
8,198,91,70,39,216,178,121,9,76,163,236,164,167,226,187,167,174,237,212,177,243,227,36,26,164,10,177,22,97,13,45,14,211,73,161,246,151,223,252,234,174,71,38,174,239,8,69,94,144,251,52,76,25,71,136,22,
234,132,193,50,14,69,60,164,119,218,156,150,231,76,247,116,147,187,47,217,121,24,83,3,18,218,137,104,169,181,200,116,156,56,159,142,210,192,154,186,47,217,215,16,217,114,97,219,68,247,214,52,68,26,39,
61,226,205,132,50,224,171,194,218,113,16,191,92,41,204,177,81,146,97,43,153,66,119,194,108,153,178,90,140,153,240,218,161,188,223,77,124,222,106,156,183,180,10,107,144,55,253,48,25,177,58,168,12,190,224,
221,137,97,82,64,238,148,3,205,177,103,32,172,73,234,233,156,34,235,216,205,43,229,8,78,241,41,70,74,138,146,111,94,192,85,9,187,182,147,63,83,140,236,22,252,227,123,200,87,96,18,218,162,114,36,68,180,
153,114,207,185,55,103,230,101,21,174,90,23,131,206,203,70,43,149,195,105,100,60,158,72,41,145,227,70,117,145,109,93,185,92,103,182,109,65,41,67,243,154,20,95,36,164,196,202,35,229,251,213,189,198,196,
227,40,176,152,39,10,103,34,186,26,84,93,68,10,28,86,108,192,211,84,1,3,229,248,200,227,195,175,73,33,203,217,105,36,16,161,54,17,140,230,146,249,121,254,72,49,149,193,27,226,152,209,40,218,97,37,108,
145,185,94,56,241,74,44,114,51,214,4,218,41,112,3,106,180,226,57,138,64,177,16,228,57,244,78,49,26,207,224,60,39,23,137,229,70,205,133,150,239,44,172,130,185,163,116,98,193,254,249,219,63,238,25,46,175,
127,249,175,148,226,9,219,74,140,27,85,37,140,107,160,146,4,50,213,2,188,98,140,197,123,57,91,101,84,155,152,95,3,203,45,112,116,13,131,197,104,199,56,157,24,166,51,206,76,44,75,33,220,86,70,10,235,186,
236,194,103,121,180,232,44,128,42,55,105,17,109,220,216,167,159,183,203,139,152,3,105,216,250,241,91,116,135,210,95,254,240,143,212,102,209,70,212,77,170,20,238,177,52,71,47,172,136,86,128,182,162,172,
225,56,8,56,40,167,194,152,50,167,92,104,183,32,249,140,198,99,214,138,91,10,164,43,229,182,18,174,27,203,113,150,145,172,251,60,229,140,25,156,170,114,243,217,3,42,75,78,180,218,167,174,17,133,52,195,
246,253,211,180,215,179,233,168,200,245,134,29,68,251,147,170,101,91,1,45,34,143,227,116,68,99,185,133,136,6,206,167,145,97,28,161,210,213,214,47,0,0,32,0,73,68,65,84,86,98,236,169,15,70,248,240,37,23,
66,108,123,89,58,29,71,206,39,205,226,60,199,73,20,0,230,139,117,133,209,162,139,11,81,170,64,128,163,18,67,202,235,229,68,171,25,91,20,182,156,222,74,206,172,137,148,199,247,28,142,157,33,104,28,42,138,
234,213,224,208,198,82,180,231,26,111,228,22,101,0,234,39,17,65,151,34,241,112,6,22,52,205,41,170,142,52,223,61,247,100,56,104,74,179,140,225,1,51,216,30,8,172,122,153,42,44,122,143,97,58,43,38,196,1,
119,175,34,85,173,232,24,65,107,108,25,31,137,90,38,144,249,233,29,155,130,114,15,78,152,196,176,138,49,40,171,88,91,227,60,61,238,179,181,125,103,92,42,170,111,47,207,222,118,184,161,38,106,161,222,201,
54,72,174,225,175,244,195,231,41,144,149,206,163,52,177,161,201,176,176,79,131,10,59,112,214,31,21,197,139,85,200,30,15,7,166,73,228,223,229,124,226,164,38,105,105,188,188,76,173,36,148,110,96,123,26,
132,249,10,239,140,136,155,115,34,165,194,224,197,14,156,75,196,172,133,235,26,73,69,146,130,105,6,101,70,70,165,240,163,167,218,89,228,229,49,99,178,66,251,70,37,113,93,101,151,71,152,24,239,114,180,
222,61,63,249,71,212,36,233,84,86,36,94,192,4,167,199,7,34,25,44,228,34,113,130,166,8,123,216,171,177,187,10,82,23,54,91,14,147,163,121,153,59,100,3,225,86,88,117,194,121,112,90,56,198,37,23,226,182,81,
189,161,153,72,205,2,183,152,38,143,51,50,169,92,179,229,171,179,140,4,166,2,63,61,95,168,41,114,50,158,82,35,151,215,23,225,109,231,136,5,241,90,198,24,9,203,34,203,146,174,190,182,94,209,178,102,125,
13,252,116,123,38,196,136,233,81,42,195,104,121,152,70,106,199,88,235,174,197,92,215,136,239,41,61,90,247,149,45,149,1,197,100,0,103,8,33,240,242,242,202,178,138,135,35,102,225,169,56,227,56,105,199,60,
47,196,45,65,145,13,211,243,15,63,49,175,129,154,19,246,251,63,255,69,92,173,192,203,159,255,2,246,110,221,45,232,44,231,115,41,133,215,110,151,24,149,145,53,152,115,92,70,79,94,35,215,57,64,45,221,196,
39,214,181,187,130,123,137,159,245,192,218,104,82,143,132,187,187,115,157,19,91,209,61,77,48,86,49,111,89,99,152,140,229,112,154,248,234,237,200,27,53,50,78,22,187,188,188,200,17,114,60,114,154,28,57,
173,148,24,217,66,143,54,198,96,80,28,116,227,48,74,180,182,162,244,201,124,1,87,153,134,74,203,226,220,94,99,194,84,211,39,237,149,175,188,195,140,118,239,211,236,121,146,176,201,126,6,11,249,235,94,
155,24,162,215,187,80,180,197,34,98,234,2,107,95,207,217,207,14,3,209,145,53,99,132,228,229,29,181,101,252,253,244,238,121,7,178,12,151,228,147,193,232,158,17,250,4,21,182,44,150,202,61,51,137,207,248,
201,82,11,75,76,152,30,202,119,47,79,83,145,90,90,119,163,84,29,196,88,181,132,27,161,109,162,165,168,26,141,72,106,236,241,171,175,36,120,97,244,68,63,98,245,216,153,216,6,167,205,174,157,84,90,49,14,
158,229,53,200,208,68,174,60,116,169,12,163,108,47,77,200,12,99,255,161,84,217,105,32,206,24,18,96,91,129,152,137,169,124,38,239,210,24,92,159,23,39,121,153,107,45,24,6,70,98,143,31,48,36,45,143,140,125,
243,205,47,63,11,240,143,7,14,61,148,49,245,179,115,205,242,135,106,165,40,198,16,253,68,172,25,163,197,11,103,84,163,245,139,211,152,194,75,16,84,106,233,225,56,185,207,52,172,49,184,163,103,93,34,113,
45,123,209,63,122,203,211,163,231,225,124,96,168,5,191,181,158,199,209,40,131,12,177,27,142,227,36,12,77,235,134,17,114,162,81,56,158,206,24,63,245,200,160,85,188,181,25,66,79,131,240,37,131,55,36,100,
34,51,29,70,114,204,220,226,70,235,157,111,49,158,134,161,82,216,106,33,164,64,41,153,211,209,115,112,35,211,227,200,241,73,248,150,98,117,216,248,148,42,159,126,158,137,91,198,191,172,253,157,146,21,
113,88,86,216,18,199,131,199,224,176,204,43,186,53,60,16,175,171,100,5,196,8,73,46,12,63,40,204,120,79,55,17,186,103,42,5,125,171,232,100,56,57,199,112,79,243,3,62,174,129,193,201,218,10,18,184,32,37,
226,250,137,225,3,220,24,184,206,11,1,56,29,6,78,192,229,117,230,242,233,38,0,230,147,227,225,52,177,172,240,210,7,224,222,174,172,218,137,77,248,174,132,82,74,97,45,92,150,151,187,175,81,226,219,0,93,
239,115,3,17,209,151,53,17,242,198,170,4,105,106,141,233,234,192,194,144,43,37,54,170,46,104,83,241,140,160,19,37,174,92,214,141,15,243,207,220,230,133,152,178,56,204,123,167,44,215,178,231,228,13,6,73,
39,142,91,36,110,27,249,245,194,114,187,73,154,240,245,250,188,219,113,63,189,252,40,123,177,158,205,188,70,169,242,115,46,61,165,7,114,44,148,178,18,67,38,39,161,144,43,211,33,25,53,113,54,174,35,80,
55,114,250,60,140,81,166,83,16,116,17,106,115,41,164,59,91,190,117,216,172,49,124,188,184,110,143,144,136,11,235,45,45,222,136,33,177,164,136,253,254,167,127,219,127,194,239,254,240,127,239,128,121,225,
17,107,129,27,122,139,115,114,53,155,146,24,173,99,234,252,192,117,205,104,157,247,160,36,243,56,65,41,84,235,153,83,33,52,41,202,78,211,145,58,121,142,78,84,173,119,241,198,95,1,94,74,227,181,207,185,
79,253,36,121,56,79,28,76,234,105,146,21,251,244,244,216,157,85,26,191,253,13,49,197,221,235,106,180,164,73,209,12,181,66,41,13,83,50,227,232,176,202,177,109,82,252,220,179,11,140,6,109,13,107,73,56,10,
79,237,192,91,251,142,226,164,119,139,89,244,242,119,87,204,151,131,194,123,49,255,224,166,47,126,8,249,32,95,195,66,74,145,18,19,246,252,248,245,206,158,244,211,145,243,87,79,226,169,40,210,165,238,151,
64,83,228,178,241,246,240,6,90,37,173,133,113,26,168,13,156,228,39,19,115,102,181,48,221,65,70,90,117,103,77,37,118,78,113,217,20,245,254,142,120,209,92,186,158,165,8,176,246,236,59,221,5,209,165,53,234,
104,105,104,106,90,177,214,79,125,100,223,56,30,31,113,202,137,97,175,139,233,156,151,175,207,168,214,7,121,16,111,165,119,5,26,103,36,187,171,214,2,86,206,236,209,88,156,215,212,92,88,74,165,85,205,87,
206,50,28,60,117,210,59,10,216,249,174,219,252,66,134,240,246,236,72,253,91,46,169,176,150,44,126,146,42,2,85,235,135,169,63,175,66,92,116,88,76,107,140,99,233,34,184,210,137,159,98,92,77,177,96,70,135,
42,146,146,90,154,104,37,156,151,5,76,122,89,168,108,108,161,50,184,145,175,237,136,157,186,8,41,27,142,15,150,37,196,125,142,60,117,125,253,125,97,30,111,47,20,37,250,54,129,34,74,202,96,222,18,175,33,
96,71,51,236,130,58,183,60,146,242,34,218,134,98,104,89,38,238,104,161,33,133,219,140,202,78,140,85,199,161,255,212,98,255,89,111,145,203,101,97,94,34,211,232,120,115,152,152,220,128,175,80,111,242,252,
181,218,152,111,118,39,135,190,204,129,151,203,76,76,105,175,208,140,11,108,91,234,26,182,123,247,177,48,58,71,172,17,251,252,124,233,43,57,195,122,185,82,130,84,254,181,42,4,136,155,241,190,226,198,130,
74,141,209,43,28,21,98,102,187,5,94,131,52,159,227,232,121,115,26,249,221,175,222,16,227,198,114,13,124,120,185,82,238,25,49,181,98,138,140,159,140,81,2,110,201,185,39,78,69,241,49,25,195,249,100,9,157,
102,215,106,234,249,32,55,14,78,52,159,54,133,121,143,213,156,63,252,72,204,17,163,12,214,136,100,128,146,201,49,82,34,148,24,249,241,245,131,112,125,172,124,242,45,85,66,216,88,211,74,137,133,143,207,
151,46,84,254,44,139,185,135,243,214,82,153,58,143,208,15,22,107,108,23,132,22,137,230,52,158,215,57,238,162,255,253,180,40,240,26,130,60,18,31,126,248,115,7,179,20,190,255,231,255,147,152,36,30,224,116,
60,225,188,234,116,162,130,41,154,181,20,46,97,97,43,2,191,24,156,235,147,33,185,104,168,149,183,103,79,76,137,84,160,104,81,112,223,245,15,120,3,93,144,100,157,225,224,61,169,54,98,79,45,118,222,224,
213,132,31,156,156,211,93,49,203,186,176,197,200,121,14,216,243,163,149,70,81,25,206,188,227,114,153,187,107,176,72,45,80,58,194,31,48,197,50,158,158,246,241,172,81,253,60,165,73,208,227,113,160,173,27,
165,72,33,127,203,153,176,69,24,44,195,224,112,222,50,116,110,133,210,157,63,156,18,215,235,103,167,173,121,58,73,70,174,209,130,142,244,30,125,242,140,10,166,92,176,231,243,131,220,32,222,243,100,222,
243,187,223,254,138,121,9,172,113,161,54,193,137,16,13,84,67,41,154,121,43,29,185,110,255,202,182,126,255,234,10,22,51,14,188,57,123,78,72,242,229,254,229,58,195,65,153,158,224,110,241,67,127,1,183,220,
123,58,131,249,234,233,139,155,79,172,203,109,189,145,214,42,81,201,70,9,98,33,7,184,254,180,97,166,73,164,92,102,196,15,26,7,20,107,168,65,14,246,227,65,242,193,27,141,53,22,180,49,24,63,238,42,239,61,
247,168,136,7,36,25,187,135,151,153,164,97,234,239,134,211,180,222,89,123,11,186,119,51,183,37,209,82,219,103,111,10,75,152,23,226,86,100,4,22,54,69,173,18,229,248,241,90,241,75,161,1,211,100,48,56,104,
6,170,66,227,105,26,236,16,56,140,163,72,107,194,202,229,122,163,150,141,113,116,24,99,169,245,30,70,45,127,129,211,226,162,241,123,148,82,207,97,142,18,10,160,149,124,138,247,46,228,23,135,35,107,42,
132,188,98,236,200,56,90,200,6,117,132,199,211,17,171,38,39,185,92,192,249,221,153,107,49,140,122,2,15,197,192,100,60,227,221,213,178,172,92,55,65,235,210,36,237,250,97,244,56,59,116,135,87,101,176,10,
51,13,172,221,206,62,116,169,237,218,10,126,176,232,237,51,7,40,229,194,186,67,109,69,67,63,223,2,159,174,51,173,8,123,240,82,86,84,220,56,159,44,45,24,236,219,175,223,81,138,56,191,135,195,137,199,123,
214,28,73,242,194,59,213,221,32,11,149,214,54,36,188,24,90,199,66,213,86,168,125,107,201,48,81,91,235,217,181,226,2,43,72,254,50,155,56,20,63,163,79,133,232,28,250,205,87,74,37,59,179,147,70,199,163,101,
168,71,182,75,16,202,116,84,216,57,220,37,74,10,109,61,95,31,32,197,149,146,65,231,66,141,145,112,223,85,104,24,186,205,71,91,221,187,232,207,177,89,119,159,114,204,73,176,80,173,176,221,34,161,20,92,
143,19,152,188,40,96,197,70,169,137,81,51,89,189,43,180,230,231,139,128,15,151,192,28,164,240,154,95,62,177,172,43,163,51,216,65,55,193,230,24,199,244,56,177,222,22,113,135,91,133,66,145,51,164,190,164,
209,10,98,8,228,251,246,40,39,150,126,140,221,157,51,49,23,226,150,246,112,232,91,119,226,120,47,142,241,123,201,120,111,241,67,88,119,129,179,50,210,206,75,58,196,186,251,150,130,156,123,12,222,97,183,
139,208,185,90,43,252,252,237,63,131,105,228,181,235,41,35,92,195,202,18,110,228,148,48,26,76,149,91,201,24,41,168,75,107,61,119,67,214,103,107,216,36,158,194,137,8,47,23,201,241,240,147,255,98,226,46,
234,1,103,12,174,131,191,149,238,106,129,187,74,229,38,250,181,211,195,132,169,111,196,207,100,192,94,127,254,40,79,99,131,79,31,62,48,60,78,2,29,220,18,45,105,40,137,209,42,180,157,58,83,77,212,43,163,
51,88,43,209,201,119,148,63,64,62,172,253,38,147,60,141,76,235,51,13,183,139,235,140,150,104,250,187,125,45,149,207,234,88,122,96,187,159,250,32,252,112,96,212,181,83,157,42,214,31,14,125,160,161,41,239,
223,244,73,58,24,171,72,170,112,194,81,244,125,219,32,143,172,209,102,79,251,181,163,197,36,41,180,169,80,157,140,161,214,34,157,200,52,72,147,170,39,203,224,60,219,42,167,139,55,146,181,49,116,35,246,
189,93,122,94,18,74,59,38,232,103,177,236,243,142,222,179,174,25,59,14,83,31,56,23,110,107,225,97,212,56,229,209,19,164,206,190,30,135,1,180,200,103,201,230,11,192,166,176,2,25,216,99,137,134,201,144,
107,227,211,229,42,123,101,227,192,24,188,246,28,134,9,215,167,242,247,109,166,118,6,239,61,195,32,235,129,227,155,7,172,115,140,131,35,132,194,203,229,74,91,67,191,17,11,214,159,190,2,12,67,43,172,239,
126,13,30,18,6,242,157,117,221,40,174,114,80,133,3,26,14,131,128,184,139,40,5,219,29,9,149,27,107,140,132,144,88,66,102,171,6,55,157,49,199,9,172,140,11,214,98,248,122,140,28,141,71,149,70,75,21,149,10,
138,132,78,221,217,59,94,240,205,113,91,251,17,24,19,38,110,132,185,192,150,176,106,20,179,180,43,240,240,213,91,94,215,155,132,53,29,228,24,90,110,43,174,20,134,113,226,116,112,228,158,112,189,222,247,
85,69,65,42,84,10,198,122,150,75,192,41,133,63,77,28,198,19,126,114,44,61,250,34,181,194,75,124,98,24,44,131,119,84,87,73,183,204,22,18,181,172,180,218,152,90,16,195,119,109,184,146,100,193,89,86,106,
108,176,21,44,230,32,186,27,15,211,195,27,236,227,3,37,137,232,205,153,138,177,71,82,188,241,49,5,62,124,136,176,205,228,210,225,1,198,160,74,163,100,185,173,140,49,44,107,102,26,29,103,45,78,5,171,43,
39,52,230,65,220,48,255,118,45,196,144,33,20,208,133,88,50,113,13,82,124,0,166,188,178,44,27,97,13,148,86,57,90,135,218,34,49,85,138,196,189,25,172,147,231,199,140,19,131,57,48,155,13,31,171,136,51,188,
166,197,64,184,205,68,191,80,231,72,42,146,59,211,138,40,69,98,234,214,181,38,244,26,105,1,35,49,52,84,20,19,212,232,192,24,203,255,252,0,215,215,27,91,88,168,69,116,113,97,11,172,203,44,84,114,28,97,
14,220,214,165,43,179,12,237,50,179,230,174,226,110,57,178,229,155,228,113,94,159,25,141,193,245,189,89,140,141,203,101,38,196,27,163,129,195,104,8,75,195,121,195,193,139,92,76,57,13,71,191,119,190,167,
81,142,51,231,13,254,14,132,143,133,24,10,41,205,44,151,31,153,231,141,53,46,180,146,161,102,230,219,38,54,204,180,177,105,47,55,109,109,120,175,48,206,211,226,13,186,19,216,14,165,103,23,88,141,215,43,
151,143,162,210,70,107,26,138,53,188,178,134,153,90,65,29,13,20,33,108,164,178,145,174,91,215,182,73,199,17,66,36,206,225,174,140,236,235,44,72,93,227,179,198,190,52,239,99,133,214,170,200,196,17,250,
179,53,3,78,71,217,218,143,160,7,39,156,120,32,43,208,222,96,89,126,102,203,145,154,10,243,159,255,11,231,97,96,13,153,173,131,3,134,150,9,203,204,243,229,153,31,215,204,75,79,72,49,154,157,98,215,82,
133,94,82,122,73,2,160,85,205,146,161,85,133,50,110,119,205,148,163,228,208,25,100,195,68,42,224,12,211,52,96,141,225,105,160,91,141,165,213,111,70,75,44,81,211,178,13,253,233,135,191,16,194,149,180,102,
126,252,167,127,194,54,120,93,110,220,98,227,112,246,12,147,162,172,145,112,187,17,227,202,245,150,105,200,54,127,28,189,96,158,122,165,229,157,161,197,40,48,122,103,56,105,75,198,96,172,199,56,79,81,
112,122,50,120,59,245,106,174,143,196,140,130,40,23,133,247,19,29,21,45,114,94,111,176,195,38,166,152,45,99,67,120,17,46,32,141,212,86,94,203,74,246,13,76,101,137,51,183,8,222,90,220,100,112,135,19,79,
111,36,6,168,80,132,155,230,156,12,84,122,61,16,151,91,103,92,122,166,225,132,63,29,97,24,40,104,18,21,135,195,79,158,105,240,180,238,213,168,61,145,219,3,91,52,221,211,108,33,245,185,196,240,10,25,252,
148,177,17,40,202,128,110,100,99,208,102,148,209,85,107,88,35,54,29,171,164,216,113,218,96,253,136,90,110,204,65,34,137,87,148,132,223,56,143,183,150,223,188,255,122,175,7,138,50,164,166,136,5,97,166,
0,118,178,20,5,243,38,121,118,122,26,25,189,3,37,57,8,231,211,184,155,0,87,4,146,236,180,70,13,138,86,192,70,140,100,33,1,117,152,164,38,80,138,211,40,58,119,221,55,243,105,203,68,192,28,38,180,247,76,
199,51,78,105,172,179,224,187,24,84,203,11,114,207,114,182,8,254,113,52,66,176,51,206,81,204,145,244,133,252,214,25,183,255,3,35,154,132,161,172,98,222,138,107,18,36,132,245,28,143,82,207,88,252,177,103,
23,24,198,175,223,64,209,12,131,103,116,22,63,56,84,167,150,199,77,6,42,43,133,168,45,197,155,78,202,54,212,32,133,142,113,133,243,112,20,198,79,23,124,170,32,196,3,101,50,222,100,66,43,248,65,192,244,
163,29,185,67,45,205,168,57,105,43,182,226,214,48,102,128,67,231,11,110,55,106,146,82,192,62,190,121,35,88,39,224,241,171,71,140,25,240,206,202,218,180,71,95,140,167,35,227,81,242,230,204,224,8,57,146,
146,164,14,215,44,1,188,208,5,32,217,117,56,65,145,23,83,131,29,140,132,156,59,195,37,202,42,205,24,135,209,18,109,81,74,65,210,17,133,167,41,255,104,89,83,196,80,104,91,162,246,145,129,149,27,74,6,211,
215,249,198,228,5,203,64,149,98,70,118,176,50,206,143,165,136,134,162,128,147,36,28,106,215,170,27,99,241,206,33,250,207,130,209,14,103,68,133,237,12,224,20,81,9,224,62,198,66,173,153,113,156,240,202,
224,221,23,150,89,21,73,77,20,40,26,81,32,122,213,48,190,227,207,156,54,148,170,49,222,114,158,38,214,109,163,101,181,23,235,40,104,49,146,140,124,205,14,25,140,244,89,16,165,102,74,110,130,82,191,179,
37,140,69,121,209,193,187,61,31,198,128,214,60,28,101,218,35,214,8,197,96,253,23,105,131,154,184,10,245,198,63,218,221,44,24,127,250,200,109,89,216,74,233,1,211,189,62,173,199,35,28,143,66,169,171,141,
161,131,143,75,74,104,99,56,78,35,198,201,88,169,164,66,138,149,181,104,232,214,136,211,105,228,99,20,17,180,187,91,208,114,15,80,215,128,53,164,46,29,247,59,22,39,176,109,21,93,10,206,56,24,18,36,136,
1,174,169,177,110,145,231,143,63,146,203,134,42,10,187,41,125,191,132,120,69,225,173,167,30,228,167,118,147,71,107,205,45,69,66,140,172,40,65,172,27,57,89,170,174,59,67,123,85,5,76,228,120,84,196,116,
37,173,154,45,244,54,103,26,49,21,106,82,140,198,136,154,187,128,73,34,162,113,85,194,31,148,106,60,106,191,39,102,127,90,174,108,91,228,201,68,188,151,135,196,222,201,137,173,192,97,26,137,247,113,231,
240,217,72,90,98,233,144,121,129,105,150,218,125,248,74,113,62,142,59,7,27,224,117,17,195,83,79,46,218,17,58,70,43,12,18,171,21,179,150,73,144,249,108,119,215,125,144,242,252,124,221,35,180,156,177,28,
78,131,124,77,173,98,82,147,125,245,157,156,85,74,229,120,18,195,168,233,243,176,187,157,119,242,66,249,26,198,46,3,15,145,216,50,47,151,185,79,212,19,181,85,166,97,148,255,191,49,76,163,96,24,234,86,
8,49,81,74,224,195,60,247,63,179,47,99,190,48,188,42,163,120,59,77,108,157,83,49,57,139,86,141,101,174,130,197,14,17,171,238,153,182,90,139,227,54,150,251,76,231,139,33,137,204,21,188,17,188,147,70,129,
177,228,2,53,23,114,17,9,249,97,56,240,246,23,15,204,75,144,99,113,21,24,231,209,40,38,35,167,138,61,76,2,84,238,219,87,16,84,239,189,207,187,60,139,137,181,148,200,165,15,182,231,231,11,165,108,164,53,
97,231,112,195,32,157,238,252,122,131,106,80,90,182,236,35,50,91,40,94,239,209,45,206,91,92,87,63,181,38,73,83,243,82,89,99,164,214,27,223,125,191,113,185,206,2,210,194,48,40,131,153,100,23,82,179,226,
233,205,132,46,221,199,220,35,234,161,103,66,27,5,198,112,242,142,82,60,37,71,82,45,60,158,39,188,58,137,235,214,59,11,221,185,98,189,101,84,35,34,139,87,168,10,26,77,211,117,135,31,191,94,3,185,123,219,
140,213,12,198,96,189,99,210,98,4,28,14,14,107,45,199,209,115,50,3,163,241,248,166,185,190,46,204,33,243,252,225,153,82,36,143,230,158,90,57,158,143,156,167,129,97,240,108,161,225,71,49,169,92,174,51,
106,22,234,1,14,214,84,176,40,141,211,66,156,115,198,200,108,33,22,86,85,161,136,187,22,45,147,76,106,235,60,159,200,186,10,205,156,174,191,244,222,8,32,203,64,8,113,247,210,93,202,44,185,92,171,156,222,
111,58,242,239,110,196,86,72,244,192,37,21,224,198,26,250,41,164,139,188,108,192,209,77,156,30,28,71,239,145,97,104,109,52,50,235,178,17,110,51,70,188,7,216,81,34,41,156,50,232,34,129,8,115,92,101,130,
174,149,112,128,82,33,230,85,126,159,183,172,107,38,108,43,14,35,80,163,220,80,214,227,140,102,114,158,172,68,204,100,123,68,178,60,203,253,168,219,18,15,199,7,110,235,70,186,45,196,156,153,151,192,50,
95,153,174,112,178,14,107,140,2,39,158,205,167,183,39,124,233,241,41,57,17,47,25,178,18,39,12,226,23,114,89,242,185,234,214,192,8,155,231,160,29,30,135,91,129,169,48,54,225,254,57,60,182,104,182,88,120,
125,189,241,221,15,47,132,24,80,70,241,238,237,19,79,167,163,104,48,201,188,206,161,95,206,55,214,45,82,149,228,223,62,90,203,175,30,79,28,78,30,215,26,118,141,17,87,100,2,255,252,60,51,199,130,167,162,
106,101,212,35,222,10,192,194,24,152,252,40,104,105,26,171,137,180,150,169,73,147,99,228,214,86,124,215,157,73,207,38,199,223,154,54,90,1,53,140,188,123,55,240,244,205,111,9,97,99,64,17,119,200,28,108,
89,56,239,91,150,214,127,52,22,148,194,25,135,209,149,169,147,21,236,121,60,177,22,249,232,47,47,87,148,241,132,150,24,170,198,78,116,13,111,21,96,161,86,232,254,78,155,201,139,156,176,21,214,40,176,45,
103,12,117,237,32,240,209,195,73,65,48,29,66,100,89,105,252,229,187,159,246,99,18,224,228,44,206,59,220,36,149,27,69,24,108,190,111,103,203,154,185,46,178,49,157,211,138,189,94,95,145,181,55,156,252,128,
159,142,88,50,148,138,105,146,126,157,98,101,67,220,95,134,138,179,90,126,221,12,40,45,203,151,214,10,205,14,248,82,121,137,129,242,252,138,247,163,92,14,71,223,177,190,138,199,167,83,15,244,45,228,53,
49,147,241,157,238,88,98,65,123,195,96,20,177,147,253,111,121,99,157,3,183,20,169,45,97,165,20,52,24,101,121,152,14,180,150,241,94,62,201,45,36,82,139,96,29,18,113,157,216,82,97,163,151,160,204,157,127,
232,176,222,48,162,185,134,149,219,107,96,165,113,58,52,244,233,128,170,141,177,22,34,18,178,171,141,194,85,5,163,232,120,140,51,98,16,52,50,42,8,166,237,0,13,128,227,227,196,147,57,225,71,35,154,36,83,
43,137,141,203,252,73,34,56,149,233,143,66,99,83,48,142,112,52,150,136,166,98,216,214,149,37,52,114,172,88,167,209,40,188,81,28,14,142,80,10,15,15,240,56,56,134,105,148,216,160,34,149,157,2,252,40,202,
150,108,13,214,105,178,18,184,22,119,62,108,51,251,146,8,111,49,206,224,82,238,151,153,193,166,176,144,122,76,149,211,133,154,95,33,159,72,170,75,185,114,34,92,165,162,107,14,172,247,84,18,180,132,117,
247,118,48,147,170,40,178,143,143,39,244,106,80,165,64,92,153,99,36,229,200,209,123,6,107,105,26,182,40,89,116,169,23,77,133,210,169,143,48,41,219,121,196,109,167,224,164,82,41,33,17,147,198,202,42,119,
33,148,194,119,223,127,199,64,225,149,153,97,232,76,235,24,120,45,77,154,129,201,18,67,233,65,101,138,243,121,226,120,58,66,17,82,77,43,137,176,70,214,109,149,46,193,24,76,41,212,84,137,37,80,173,225,
245,22,36,229,218,104,30,198,137,58,105,230,144,192,100,82,105,108,183,188,123,60,90,46,76,195,136,167,98,181,198,104,141,77,217,80,155,195,26,71,90,96,45,154,114,180,196,236,49,169,16,139,134,219,21,
210,10,174,113,242,111,112,86,160,154,238,101,35,188,220,118,140,105,107,149,199,169,160,75,165,217,129,226,78,130,217,41,128,246,52,55,96,137,52,50,170,41,214,69,108,238,131,209,184,212,217,66,93,2,105,
116,162,216,198,96,34,166,136,46,174,84,131,61,29,79,232,163,166,80,248,249,241,137,37,174,24,55,66,81,40,109,24,218,128,57,156,40,155,161,214,149,211,208,144,35,49,177,188,190,242,186,204,164,152,81,
90,73,152,250,210,132,232,120,208,192,66,142,142,53,85,208,9,119,91,25,156,216,41,91,107,40,47,10,67,235,12,177,163,221,93,231,108,22,5,202,73,63,152,114,102,155,87,82,45,216,167,167,55,84,32,167,204,
155,183,95,243,166,73,193,190,172,25,83,10,102,28,96,243,108,206,83,210,145,91,248,4,65,180,15,133,204,52,25,30,31,199,29,111,102,80,76,167,35,167,105,36,106,203,122,203,20,26,41,4,102,26,169,195,179,
176,6,95,28,203,218,35,102,157,19,54,247,45,236,154,205,90,58,42,42,203,227,86,75,197,134,181,75,1,166,129,223,252,230,87,226,161,171,176,109,161,51,170,42,53,6,174,175,129,188,174,92,62,6,89,79,245,110,
126,28,21,131,247,228,148,185,190,222,40,181,17,10,162,211,233,232,245,218,33,138,181,102,230,14,223,114,206,161,90,35,36,209,210,91,99,120,56,77,60,120,65,149,172,33,238,205,106,141,17,221,36,25,200,
222,201,250,165,14,108,33,83,214,200,97,26,176,70,17,29,148,216,120,205,144,171,34,226,248,229,175,126,207,225,56,224,173,229,58,47,92,174,11,225,46,177,53,150,79,241,130,190,38,180,22,145,211,212,41,
30,214,25,14,165,201,60,173,47,194,141,51,184,9,82,146,23,124,24,70,110,179,72,41,157,21,73,112,140,137,232,53,53,72,228,133,245,163,39,149,68,166,240,241,249,133,167,195,81,184,215,253,60,198,43,126,
49,61,226,127,249,142,193,141,196,80,208,86,81,98,196,153,129,147,63,245,40,22,57,75,191,97,233,29,67,161,229,200,164,76,15,71,151,205,211,18,229,134,43,78,243,112,154,56,28,68,254,240,233,38,90,163,163,
59,97,156,147,162,168,67,18,215,109,145,44,243,92,176,211,97,96,40,70,124,21,131,227,231,215,43,107,30,41,172,130,11,115,138,131,61,176,210,112,177,49,140,3,175,33,178,174,27,5,205,248,116,100,176,119,
250,65,226,50,75,72,250,228,45,163,87,76,94,35,129,153,178,111,254,169,47,199,7,231,56,63,30,152,142,19,113,141,76,215,27,215,121,161,68,47,26,138,73,198,15,49,5,50,21,51,130,41,13,91,74,238,133,180,22,
109,66,116,34,142,183,39,114,137,224,52,37,25,94,158,23,94,231,159,169,93,105,168,149,145,168,33,173,32,46,59,27,45,27,135,165,16,141,194,53,205,101,222,88,230,87,226,188,82,106,198,61,28,132,203,102,
12,215,229,38,0,69,35,211,160,82,4,104,59,14,14,6,183,71,10,36,101,168,70,163,77,194,38,173,80,163,239,220,73,135,126,235,169,211,40,222,121,18,57,68,10,145,95,254,242,204,111,236,19,78,21,46,215,69,162,
53,99,129,85,124,70,222,90,193,69,69,41,114,74,44,68,10,211,105,228,221,223,60,225,189,99,219,34,63,94,103,158,63,93,185,221,130,76,224,189,225,183,191,121,207,175,127,243,134,152,34,203,45,50,47,27,91,
145,8,217,225,116,226,208,165,99,173,21,236,54,191,238,158,160,56,95,24,79,7,202,188,49,179,79,97,137,41,177,93,86,194,186,73,54,151,243,18,131,233,220,78,65,202,53,130,202,248,163,199,91,199,52,13,2,
29,40,141,203,117,230,242,252,74,43,149,97,52,252,250,215,111,24,70,199,109,77,98,169,160,240,241,249,153,53,37,182,32,194,38,165,20,199,113,20,221,132,183,40,35,58,108,187,92,94,208,86,49,249,17,199,
74,189,220,88,182,72,94,35,248,59,105,89,152,150,203,178,114,153,11,111,222,60,98,252,35,30,139,246,16,194,194,186,8,208,229,120,28,136,197,17,162,194,92,250,92,168,137,3,108,24,229,74,214,74,201,22,84,
107,30,207,71,90,173,92,231,192,229,117,230,55,191,124,199,186,197,61,147,195,251,30,153,81,51,97,189,97,13,73,48,145,113,225,229,167,143,12,104,142,222,224,78,3,222,25,214,90,184,108,27,107,88,200,45,
115,112,22,74,230,182,124,226,182,192,224,44,41,33,67,196,90,9,43,120,159,89,183,194,182,138,95,249,224,15,104,224,249,231,128,153,60,143,143,15,61,63,87,232,252,145,134,247,240,205,55,143,84,178,228,
47,213,68,172,9,213,169,7,149,36,36,165,112,155,37,69,167,21,62,254,244,145,177,202,85,89,148,180,45,33,221,132,9,56,122,142,167,145,219,53,144,111,130,129,90,215,212,41,249,150,90,122,68,253,24,101,5,
128,33,133,68,53,154,80,68,64,125,125,13,152,155,161,150,200,104,93,119,38,86,114,109,146,20,232,45,120,25,57,168,146,200,81,150,142,197,119,49,78,45,216,212,196,138,238,237,196,249,171,175,73,91,2,35,
154,96,211,42,38,249,221,217,173,138,98,94,18,248,68,109,154,22,53,219,86,81,42,139,111,25,75,184,70,194,22,160,123,149,75,46,164,20,25,157,227,225,97,98,203,153,203,135,192,207,253,242,168,70,34,46,148,
82,252,156,37,180,111,71,253,166,34,243,17,36,19,193,91,131,253,79,127,251,119,98,34,41,240,184,253,158,215,107,228,182,173,220,150,141,148,86,14,134,47,68,207,9,205,81,36,134,74,115,58,136,126,221,27,
191,139,239,135,92,216,202,218,213,169,133,18,55,73,181,222,2,166,174,88,127,196,0,126,180,228,84,184,206,11,17,56,63,29,57,120,67,140,18,245,34,75,156,74,205,149,121,121,149,178,86,131,93,35,29,102,156,
121,249,105,230,252,112,98,116,142,195,233,65,130,21,172,103,116,2,215,138,171,208,231,226,154,48,222,239,233,126,163,23,228,255,229,114,35,204,175,36,127,160,213,12,58,98,78,71,126,163,31,208,182,161,
76,229,229,89,224,201,166,192,52,90,6,61,74,198,146,170,220,230,155,208,246,251,241,100,173,197,56,71,92,3,69,87,172,2,123,185,9,63,216,24,131,154,38,120,156,72,91,166,133,72,93,50,215,40,177,195,50,213,
212,212,144,240,214,227,156,240,87,75,42,124,120,158,247,252,174,227,215,95,113,154,134,158,227,28,36,197,189,21,182,117,97,185,109,255,111,95,231,182,219,56,114,69,209,197,186,145,37,201,86,219,221,147,
153,76,144,0,249,255,111,10,16,4,147,185,186,109,75,34,89,55,86,85,30,14,173,78,94,162,39,195,6,12,153,150,196,170,58,123,175,197,231,191,61,241,112,60,48,141,86,184,20,10,110,183,133,183,247,153,227,
14,178,119,163,72,69,62,88,131,214,153,253,118,191,97,190,255,225,153,1,89,139,254,253,120,227,37,174,228,91,36,48,48,121,69,203,142,212,170,80,193,122,199,141,134,188,85,66,205,104,52,202,42,56,201,205,
215,25,205,120,244,12,40,98,43,164,160,24,148,195,57,9,38,49,21,150,88,57,61,253,137,227,201,115,121,187,242,251,235,133,219,82,153,252,153,239,15,158,31,254,252,44,101,191,84,8,49,137,170,254,225,153,
65,1,102,192,12,85,9,189,118,232,212,156,228,201,46,178,16,57,157,14,84,239,24,107,65,91,33,134,77,222,177,173,137,90,50,125,24,238,65,80,109,44,218,25,222,215,128,87,86,106,12,71,177,104,215,222,184,
197,149,247,107,65,57,199,107,30,72,161,241,91,238,44,122,226,248,253,35,71,239,49,86,243,175,151,229,126,136,158,114,21,149,194,182,27,51,155,194,188,94,223,118,6,90,227,237,31,255,196,107,77,76,130,
193,171,163,163,34,81,176,20,3,185,87,78,101,186,119,243,7,187,223,130,243,38,188,42,38,220,193,177,148,70,94,18,113,147,208,199,113,60,162,252,9,175,70,24,20,107,211,92,174,153,88,12,238,48,98,15,19,
75,46,204,151,5,106,103,52,14,229,156,152,90,123,131,156,8,187,34,198,244,36,229,166,1,104,57,240,248,252,196,163,183,12,74,188,157,161,102,46,85,108,171,165,102,194,71,175,205,72,53,144,86,161,21,1,99,
20,200,173,236,156,214,182,251,62,149,172,71,118,240,161,114,144,170,116,65,45,16,66,98,93,231,187,155,169,214,74,214,17,179,233,59,242,122,26,27,147,50,146,117,53,67,199,24,153,39,76,79,158,235,215,223,
239,236,212,87,163,201,90,246,86,159,158,31,121,26,61,189,119,82,172,244,30,25,170,252,210,201,74,118,141,144,113,7,47,20,243,144,136,115,148,115,90,187,23,86,27,140,110,98,164,49,90,77,200,133,48,47,
98,186,210,22,53,105,158,252,116,71,163,166,173,64,173,80,164,211,92,74,193,188,254,250,179,188,54,173,225,246,239,95,249,244,112,160,182,74,184,222,120,249,160,122,141,134,30,86,234,240,95,248,155,173,
222,45,149,31,143,75,41,123,97,79,50,238,223,89,207,120,178,104,58,235,122,37,132,76,170,150,172,6,210,254,164,12,157,63,159,70,252,36,131,203,183,203,111,180,233,163,161,35,78,26,219,43,212,134,170,27,
38,135,133,70,165,105,203,229,235,43,225,122,185,191,232,93,189,251,47,137,111,23,254,152,23,122,107,248,201,125,195,57,181,126,151,236,78,195,64,204,73,208,81,192,102,13,221,123,96,35,196,204,188,70,
106,145,173,81,51,130,164,214,86,227,190,123,162,173,134,57,36,46,107,144,165,65,109,108,69,118,227,211,32,159,78,37,109,24,119,152,118,31,29,184,163,67,97,8,49,147,171,96,254,21,27,15,118,196,105,205,
143,227,145,152,11,53,55,122,41,50,201,55,3,235,101,101,29,224,240,120,160,82,216,54,57,80,121,157,19,117,171,60,61,28,120,56,122,124,145,228,160,53,138,178,109,172,33,17,75,229,151,203,140,217,233,75,
227,241,64,186,197,251,190,47,215,202,31,239,23,140,129,7,55,98,158,254,244,3,3,66,48,179,243,95,120,249,58,51,186,9,239,4,223,75,105,104,42,14,133,61,131,9,2,172,168,117,35,118,201,173,159,39,79,220,
103,107,29,141,54,150,79,207,143,156,190,159,132,179,22,178,68,23,172,196,220,172,115,184,105,32,15,9,114,145,27,8,176,213,141,52,39,14,135,137,211,193,222,95,118,78,11,216,62,174,25,131,243,116,58,185,
52,174,213,49,126,254,140,213,157,233,113,98,180,134,249,26,8,151,43,161,86,82,147,222,169,25,68,0,0,6,3,73,68,65,84,171,238,79,142,68,99,218,42,7,63,49,121,71,31,32,229,242,63,4,48,175,13,83,149,172,
133,51,154,209,26,14,7,169,210,215,173,242,122,145,215,181,51,66,202,253,184,170,206,137,3,183,236,144,45,242,35,32,135,223,166,185,73,244,239,58,19,173,37,23,225,233,60,22,205,201,57,162,217,88,140,19,
14,144,86,232,99,35,27,43,217,225,154,41,177,161,188,227,209,123,62,125,118,119,162,93,72,153,247,235,76,72,27,71,127,96,218,215,192,21,168,163,32,31,102,52,11,154,147,155,240,123,152,127,77,153,183,93,
39,224,172,4,71,74,15,232,193,112,122,62,96,66,22,136,107,169,149,76,35,237,2,165,186,106,50,82,199,65,59,170,222,208,189,242,112,120,184,7,67,15,229,27,145,252,154,50,167,222,121,244,35,165,117,150,144,
152,215,72,88,19,107,44,44,101,19,99,229,86,153,198,137,86,43,75,169,116,173,216,128,144,5,147,22,253,32,193,17,171,232,59,217,102,153,197,93,247,126,75,59,121,183,75,58,245,236,39,170,179,220,98,100,
64,162,93,177,100,168,5,183,67,141,111,243,114,255,24,27,253,200,81,27,150,16,9,33,242,6,156,181,229,22,50,243,28,200,77,46,66,9,145,80,55,206,231,3,103,127,148,74,188,149,34,160,116,65,245,158,137,207,
28,253,132,121,50,216,65,17,119,43,202,168,196,110,28,214,132,161,167,221,103,43,126,101,61,104,188,130,214,54,200,89,166,158,78,49,88,217,171,118,215,104,65,80,213,97,238,164,61,102,96,59,24,103,81,33,
227,106,229,224,6,78,147,199,121,71,147,240,5,199,199,35,49,68,98,201,82,157,184,199,208,245,55,200,209,251,194,241,48,9,240,107,111,52,142,45,130,134,100,26,134,40,78,101,6,141,205,81,166,63,8,167,149,
253,157,63,162,25,181,166,208,8,73,78,23,31,15,19,49,101,74,216,164,94,182,85,140,177,108,185,237,82,210,189,99,52,202,72,32,204,145,203,237,42,206,187,88,238,203,81,109,165,198,243,49,156,127,28,29,92,
34,218,57,142,126,162,214,194,219,111,55,114,136,104,235,48,249,245,182,99,69,58,241,247,139,180,186,91,103,219,10,181,109,12,21,226,100,176,218,98,52,168,38,169,211,109,15,121,212,218,118,103,81,35,3,
190,105,180,154,24,154,148,174,232,142,62,40,82,138,164,37,130,221,109,215,251,252,226,35,232,225,156,225,233,252,0,250,89,6,226,243,59,47,165,80,251,198,229,215,95,112,181,115,62,140,152,203,219,11,206,
238,196,129,120,35,228,118,239,84,200,150,8,182,240,77,71,60,42,45,63,223,171,189,31,21,156,143,66,106,66,225,246,239,85,5,35,10,38,77,107,10,109,29,91,206,232,193,114,114,78,90,93,74,113,155,87,110,215,
76,142,87,190,252,120,98,137,11,151,219,149,90,101,212,64,204,84,171,184,165,13,99,168,132,101,225,146,51,63,253,243,39,30,207,103,250,126,62,187,247,157,238,240,88,80,244,110,217,221,44,48,52,172,218,
101,10,251,228,167,232,129,178,179,92,105,16,82,129,53,253,23,93,84,223,123,118,71,45,157,80,244,1,55,57,148,54,92,174,23,150,144,88,66,184,119,234,150,144,208,75,195,218,130,249,252,252,195,110,19,134,
191,122,205,181,110,248,157,57,41,226,144,2,219,30,213,106,141,102,39,254,223,99,29,36,150,75,222,137,186,59,95,208,238,205,173,211,97,98,94,227,110,31,230,190,89,149,140,177,225,90,2,39,119,224,120,126,
184,47,178,22,253,78,50,26,117,24,49,88,47,161,56,41,74,202,228,94,65,173,134,90,33,111,3,177,36,116,215,216,193,112,77,34,230,149,192,135,240,224,245,222,66,52,122,96,122,116,178,194,235,157,161,128,
170,98,82,243,206,226,38,179,131,232,195,93,125,220,123,35,237,95,43,173,248,98,127,20,13,134,218,40,101,239,227,205,81,230,206,206,99,10,150,181,86,122,169,92,147,116,128,10,146,211,220,74,166,166,142,
54,142,233,225,200,233,56,114,214,219,93,135,209,186,16,237,114,173,212,24,41,181,211,181,223,149,219,210,233,207,171,128,97,140,177,76,179,166,162,153,67,64,171,1,63,10,149,87,77,211,29,193,243,252,244,
196,117,94,72,89,110,30,131,158,56,63,159,153,188,103,80,19,198,127,57,113,106,50,161,244,250,139,244,136,140,98,176,3,170,124,152,213,243,222,145,203,82,175,220,175,198,199,32,173,54,40,86,209,117,163,
198,204,160,52,147,179,82,111,99,7,14,121,25,40,94,47,25,189,243,80,176,154,182,63,81,235,12,131,82,188,188,189,200,57,49,27,202,27,156,158,88,117,96,233,176,222,2,38,181,101,111,110,85,174,125,145,16,
115,133,30,26,67,151,22,86,201,50,96,108,121,31,227,238,144,150,111,18,144,46,84,143,221,83,96,140,38,59,135,117,178,63,204,70,75,50,176,75,217,36,101,75,171,162,174,216,82,188,223,64,228,143,91,9,165,
112,244,19,167,227,136,114,154,249,210,153,175,51,95,83,198,220,126,251,105,127,55,26,174,127,252,202,113,208,84,45,7,112,153,130,197,226,245,128,239,138,205,88,226,38,159,189,90,203,1,74,109,157,249,
26,68,178,167,53,61,9,230,191,110,153,116,201,212,82,217,172,166,205,1,165,21,39,63,114,62,122,194,82,152,231,121,191,253,126,3,188,220,138,152,94,115,143,252,251,245,74,107,154,159,255,245,11,202,107,
26,26,19,110,239,82,124,26,12,199,211,51,113,137,168,170,8,53,211,250,64,214,138,163,241,140,163,195,58,69,13,87,188,30,112,163,70,209,201,161,48,90,195,150,43,67,19,126,90,77,27,41,45,44,57,209,75,162,
213,141,92,51,45,85,62,29,78,28,142,154,116,141,80,59,110,18,26,249,86,2,239,215,192,123,184,82,102,8,73,86,11,161,65,179,48,157,224,252,52,97,46,47,95,81,74,51,26,131,182,142,53,4,104,16,107,162,212,
138,25,224,130,195,162,25,106,163,110,9,93,119,213,113,107,242,191,81,187,1,98,4,157,51,121,201,148,28,209,53,17,215,192,237,186,144,151,68,219,10,171,191,112,62,121,150,189,199,247,197,203,153,92,206,
141,235,188,50,95,36,22,175,165,62,74,3,82,128,28,225,229,18,49,222,137,197,90,8,74,27,159,79,39,112,160,56,81,135,138,238,144,155,162,229,74,93,35,170,121,134,188,23,77,20,152,65,67,237,204,57,178,190,
7,226,117,6,5,147,27,152,180,112,205,183,150,113,170,10,63,77,27,142,206,225,217,233,77,89,108,149,84,152,148,132,187,157,18,25,95,72,240,48,66,61,202,172,35,20,248,15,12,200,216,167,53,76,79,29,0,0,0,
0,73,69,78,68,174,66,96,130,0,0};

const char* MrAlias2Editor::wood1_png = (const char*) resource_MrAlias2Editor_wood1_png;
const int MrAlias2Editor::wood1_pngSize = 42724;

// JUCER_RESOURCE: wood2_png, 41625, "../../../../My Documents/My Pictures/wood2.png"
static const unsigned char resource_MrAlias2Editor_wood2_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,44,0,0,1,244,8,6,0,0,0,70,158,207,247,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,
6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,10,30,17,4,46,109,145,13,99,0,0,0,25,116,69,88,116,67,111,109,109,101,
110,116,0,67,114,101,97,116,101,100,32,119,105,116,104,32,71,73,77,80,87,129,14,23,0,0,32,0,73,68,65,84,120,218,100,189,221,146,36,71,146,165,247,153,169,153,185,123,68,100,70,101,161,208,64,79,79,15,
123,151,220,165,240,177,249,12,188,226,13,239,40,188,91,225,82,102,135,100,115,102,187,27,64,163,129,174,66,101,101,84,68,184,187,153,169,25,47,212,35,178,64,166,8,4,168,159,204,112,183,31,213,163,231,
28,85,184,191,252,239,255,75,79,78,104,189,161,78,137,17,240,158,70,67,91,71,115,1,58,189,53,28,219,151,7,65,16,192,187,74,214,194,50,207,204,185,224,122,103,72,1,231,160,87,101,41,87,28,142,142,82,174,
51,235,229,74,203,43,209,121,0,156,111,116,42,67,10,196,113,176,207,61,205,156,231,11,93,59,95,167,137,152,2,42,157,211,114,193,189,252,233,127,235,226,133,90,148,172,153,214,149,78,163,149,142,54,236,
191,233,8,32,222,225,5,156,7,10,208,58,12,25,154,210,75,163,104,65,196,35,128,118,165,106,193,137,135,214,232,221,94,190,228,149,220,10,173,43,0,187,210,209,58,67,107,72,18,132,78,57,175,228,82,209,92,
104,59,193,59,15,226,0,37,140,147,32,56,24,2,75,118,120,60,77,28,208,241,112,255,240,214,26,218,59,208,0,144,201,227,157,163,105,196,3,164,109,245,187,82,80,122,41,52,5,143,128,235,168,7,77,216,10,82,
209,214,232,128,198,74,153,51,90,10,13,101,1,228,208,16,58,210,1,109,160,138,111,157,212,29,225,252,249,153,16,34,16,248,219,63,255,207,0,20,4,85,123,176,199,105,192,121,71,10,17,137,66,220,14,70,5,84,
59,65,30,236,5,68,136,34,246,208,170,56,96,20,161,20,143,120,71,16,143,202,118,168,4,186,120,156,56,86,50,83,80,154,244,237,143,236,239,164,20,25,83,194,117,184,234,200,242,233,130,94,103,194,15,63,252,
200,144,4,124,228,191,252,223,255,74,148,68,115,1,237,246,237,251,4,206,121,188,119,4,91,75,170,42,57,23,84,21,135,109,109,20,97,24,18,34,130,247,158,97,72,140,99,66,61,72,176,23,45,85,209,82,113,165,
48,142,137,41,37,52,122,170,218,14,38,236,115,156,243,168,119,172,206,115,58,95,240,251,223,208,52,227,67,32,60,238,247,72,138,244,230,120,123,124,131,151,72,177,235,128,56,207,97,74,104,85,122,177,135,
44,219,15,151,102,183,111,41,47,244,222,200,206,179,20,135,247,158,214,26,222,123,82,136,92,116,33,122,135,224,105,101,33,207,153,168,48,196,200,52,36,114,94,88,151,108,47,239,61,163,19,156,119,212,82,
41,85,121,153,103,190,249,195,191,35,76,19,211,97,36,76,195,1,31,61,170,141,253,97,194,185,136,2,189,131,115,14,170,50,134,128,140,3,49,216,150,59,133,222,187,61,216,56,208,90,71,181,209,186,69,147,162,
74,205,118,78,195,42,244,214,0,197,5,97,154,166,237,8,117,20,229,120,77,168,8,85,149,208,193,59,143,243,142,158,34,173,55,142,191,123,67,58,62,145,41,204,186,16,166,253,8,56,180,119,158,142,79,136,120,
150,170,20,173,0,188,25,70,154,118,170,42,186,253,158,23,79,216,182,30,253,134,70,167,211,192,129,75,219,177,137,138,86,229,248,120,96,41,51,185,42,42,32,41,208,165,115,173,133,235,146,249,105,90,72,49,
34,226,233,218,200,165,32,222,179,27,70,166,221,192,227,41,51,30,159,40,89,81,10,33,202,4,170,8,112,72,7,134,49,33,1,196,123,180,41,227,152,40,217,14,137,111,80,84,45,68,21,101,201,153,117,81,156,120,
66,138,68,17,36,89,248,43,170,104,177,243,253,244,246,13,33,10,89,149,46,176,168,50,169,242,141,8,95,231,43,211,52,32,206,243,114,157,89,150,140,247,142,148,34,0,151,131,144,82,32,170,16,85,8,207,207,
31,183,139,226,56,95,103,206,243,249,22,159,108,235,182,15,31,37,146,82,192,109,1,63,118,32,43,218,59,162,141,238,29,146,132,221,52,32,34,244,222,41,154,73,97,32,70,225,50,175,156,151,11,90,245,150,126,
208,32,140,99,98,76,137,148,34,49,6,230,93,165,245,70,215,142,182,198,191,247,145,226,18,170,25,85,71,88,243,140,120,64,132,15,191,188,71,123,67,182,115,4,10,8,117,169,168,170,101,195,214,73,216,229,210,
162,156,251,7,0,66,16,198,148,24,70,11,244,170,74,169,202,154,21,231,28,53,23,180,119,142,211,196,110,26,201,185,48,47,43,239,188,144,83,34,29,6,134,148,56,68,187,39,183,215,42,173,227,211,3,189,103,42,
74,248,205,187,55,64,71,59,164,255,230,27,156,115,196,40,168,118,84,149,228,18,151,121,97,205,25,173,202,90,10,81,45,84,245,222,57,234,98,23,81,60,67,180,148,156,75,165,228,134,208,120,57,159,56,236,38,
30,143,201,162,64,18,70,215,88,80,122,94,105,115,231,114,249,204,114,18,226,182,59,173,55,122,235,52,15,101,16,188,156,89,106,102,94,174,132,243,249,133,40,17,137,129,36,130,4,11,43,90,50,121,201,228,
45,203,13,41,49,78,178,29,19,143,115,142,222,59,142,127,64,196,206,89,10,145,78,97,89,51,185,84,188,119,28,31,94,248,230,237,145,135,195,158,154,11,243,188,18,26,76,41,225,163,112,74,66,45,133,165,42,
94,236,184,229,92,200,205,238,213,132,199,251,192,209,65,164,19,242,146,97,4,39,240,114,250,204,50,43,203,146,57,95,103,214,37,179,228,108,153,39,70,246,41,17,182,135,139,33,34,192,249,106,225,111,28,
237,28,118,237,44,229,74,235,29,17,97,93,50,151,211,153,81,130,129,169,170,164,20,56,78,59,68,132,151,228,152,179,69,31,137,130,56,71,217,238,15,192,203,124,37,165,129,189,4,222,61,238,113,47,255,242,
63,117,17,193,139,231,252,221,255,65,41,21,182,51,90,138,162,90,200,185,64,177,48,181,228,76,45,150,122,85,21,25,235,61,26,164,20,192,119,114,46,244,214,145,40,36,39,156,206,23,214,53,219,133,21,135,124,
177,146,111,211,158,190,197,112,194,29,15,90,2,18,199,139,102,192,227,113,36,58,97,205,25,113,30,20,62,124,120,198,123,97,24,6,60,129,156,149,128,50,74,96,58,236,25,82,34,70,177,163,35,66,107,29,80,230,
121,161,170,146,98,196,137,221,240,214,218,134,61,148,203,188,82,55,208,180,228,66,117,48,140,3,136,227,41,60,210,122,35,231,74,109,74,81,197,123,203,178,68,225,160,14,17,187,124,107,85,194,159,191,251,
14,23,4,58,252,245,207,63,16,99,32,57,1,188,253,160,146,239,88,33,108,128,36,165,0,96,219,142,210,181,17,130,80,171,26,4,220,254,59,165,72,118,153,132,179,213,142,145,195,180,227,33,13,150,36,230,194,
79,151,3,203,146,201,181,146,66,224,248,230,13,187,221,100,43,92,26,77,4,109,74,206,149,249,243,66,56,28,38,98,26,8,18,233,223,126,205,178,230,45,149,130,235,176,63,78,148,92,185,206,11,203,60,243,114,
190,108,169,213,182,149,218,44,173,6,3,69,173,219,247,230,117,69,188,195,73,199,123,135,119,158,193,11,49,8,206,123,187,88,165,161,229,227,61,4,222,50,104,16,193,109,200,110,76,201,48,114,132,249,178,
16,14,187,35,18,65,66,226,221,55,143,92,230,133,232,27,211,52,218,42,110,15,207,29,238,118,203,98,219,135,196,54,88,108,142,129,222,59,56,197,137,35,111,23,169,121,37,151,66,157,179,173,100,174,172,57,
67,179,7,58,62,190,181,20,191,125,86,173,186,29,53,240,222,209,128,185,174,212,89,249,252,178,18,30,191,122,36,151,66,240,158,248,120,96,26,3,105,240,132,20,88,175,51,18,236,193,181,55,123,200,162,27,
248,113,140,4,2,143,104,169,140,99,194,57,187,172,41,185,215,15,149,198,178,102,174,151,153,229,186,144,75,165,105,195,139,39,197,64,108,122,255,185,165,110,88,197,57,195,23,65,192,59,242,101,6,58,115,
93,8,223,127,255,3,186,84,210,24,56,255,252,3,77,43,34,13,45,149,151,207,103,114,86,98,16,66,12,68,17,82,138,119,172,43,34,124,62,63,147,115,101,28,146,109,119,104,140,105,192,137,163,107,39,107,165,245,
142,71,137,41,178,223,77,12,99,224,113,24,72,49,114,57,57,174,215,153,243,101,38,98,33,111,183,223,49,142,22,66,95,46,23,174,237,196,16,19,143,189,18,108,11,21,84,185,156,62,115,157,47,204,243,66,211,
202,60,47,44,249,245,108,89,248,115,247,115,22,162,112,220,61,113,190,206,244,102,225,236,58,47,120,103,89,50,231,194,97,63,145,198,68,12,129,193,111,171,55,90,2,106,57,163,122,160,230,106,40,77,132,221,
52,18,111,151,90,59,79,79,15,204,231,23,130,192,231,203,74,248,221,219,35,181,43,52,101,95,126,67,222,182,101,112,150,32,50,22,236,115,41,228,108,152,194,57,71,12,150,21,19,145,211,233,98,216,98,123,200,
148,94,227,236,146,149,20,34,160,228,188,160,53,211,178,178,150,153,124,94,88,248,238,190,8,146,34,25,33,103,232,189,81,138,242,233,165,146,79,39,30,222,140,84,32,124,250,248,130,85,62,149,124,186,26,
188,20,203,90,211,56,144,84,145,209,142,66,74,1,127,171,219,182,175,249,229,202,62,141,132,244,250,33,41,69,188,135,92,10,67,26,137,81,200,57,115,58,95,160,100,198,81,104,173,176,174,153,75,201,86,21,
131,129,43,237,196,32,12,27,138,115,85,121,249,240,51,224,209,82,8,31,126,254,51,33,88,201,251,247,127,253,35,206,7,246,187,157,65,73,239,185,94,174,136,31,238,176,113,205,25,231,44,166,122,113,104,206,
136,88,209,24,55,44,146,125,35,138,224,196,163,181,49,151,149,156,23,196,123,198,97,98,8,143,160,59,166,33,50,36,232,173,209,182,226,160,110,17,168,206,133,121,177,23,25,229,200,33,57,74,240,4,205,30,
186,130,118,10,66,94,50,115,233,91,241,219,152,231,43,170,175,24,54,103,75,18,55,204,59,56,195,210,55,224,2,208,182,170,16,64,139,82,52,211,123,69,130,99,26,39,162,59,64,31,173,124,30,243,134,69,34,135,
221,196,48,166,237,115,86,170,42,31,63,52,150,211,71,166,49,48,74,39,236,222,236,241,8,173,41,211,225,64,170,29,239,28,206,123,196,57,124,124,220,42,100,171,158,251,150,24,180,192,146,51,145,72,74,14,
183,149,56,95,130,127,11,133,153,101,157,81,205,56,1,245,157,92,206,148,124,198,251,196,148,172,50,89,179,39,151,129,157,222,30,184,146,115,193,201,158,92,63,146,47,202,89,148,240,230,235,183,52,53,226,
67,223,189,197,75,36,197,192,52,141,140,67,226,188,149,45,182,202,114,135,146,183,36,178,150,194,16,237,82,221,42,106,128,222,183,15,116,145,121,190,160,125,197,59,3,57,235,178,162,221,19,66,226,105,60,
176,228,124,7,80,113,3,240,222,43,34,202,90,207,144,26,165,20,196,67,104,56,186,115,168,23,8,145,6,148,230,241,165,81,91,225,225,225,29,15,15,208,213,25,162,2,163,181,170,37,146,199,199,106,151,113,43,
239,241,250,171,75,68,75,172,107,70,91,65,196,202,166,203,101,166,86,197,73,96,212,200,225,224,238,223,83,106,126,141,54,162,196,166,200,219,35,142,72,173,141,144,231,138,151,134,224,137,49,108,15,165,
44,75,163,84,229,211,243,235,3,69,17,36,38,196,89,92,30,134,4,254,138,246,78,94,50,85,43,69,87,35,76,110,181,91,31,128,78,140,129,253,52,50,166,137,232,39,202,118,47,82,203,140,83,96,72,131,29,133,154,
208,146,209,110,191,190,150,137,225,155,39,60,194,124,110,132,159,126,248,17,241,198,68,254,252,253,119,119,32,125,75,4,195,180,167,247,182,225,128,102,225,110,26,57,236,39,14,135,29,180,74,173,229,78,
1,168,90,1,0,106,240,82,210,6,150,18,243,197,138,88,85,165,214,76,107,141,60,159,217,79,227,253,178,105,107,136,55,240,31,131,32,187,137,156,87,14,163,112,124,55,16,254,225,183,95,27,131,179,44,156,62,
68,122,111,12,131,193,187,162,202,156,47,164,32,56,129,113,242,88,24,94,184,46,11,181,157,105,25,114,45,104,177,140,88,106,37,47,179,173,222,152,136,169,111,160,6,104,70,47,182,94,104,173,83,139,162,87,
97,154,10,105,244,212,162,148,114,139,48,182,3,42,157,247,63,253,149,16,29,79,199,61,225,237,219,119,160,10,199,35,95,167,203,22,95,45,232,47,235,204,243,47,59,98,148,59,103,86,74,33,151,108,248,192,57,
28,246,251,113,171,5,123,235,134,226,130,144,98,128,110,191,94,214,204,154,27,153,78,107,238,70,34,64,175,219,69,85,100,75,74,185,86,122,43,4,17,170,207,76,187,5,93,50,75,249,76,16,231,208,214,200,181,
146,215,108,68,94,138,236,194,72,138,145,175,223,254,22,239,28,170,86,231,205,243,194,193,237,25,167,64,144,128,71,80,85,116,11,119,173,53,180,42,18,132,49,13,164,40,204,75,102,89,87,188,139,184,49,18,
37,81,54,206,120,153,23,67,101,64,205,11,57,215,59,166,246,174,67,132,207,67,164,103,91,241,240,211,47,47,172,139,101,162,243,207,239,137,183,16,85,10,85,149,135,195,35,79,79,15,60,30,246,52,60,110,176,
170,35,108,225,231,116,177,242,223,59,99,107,92,140,224,149,238,28,25,199,233,249,132,122,171,247,118,135,3,251,105,68,29,148,213,128,191,56,135,120,79,46,5,245,158,148,2,195,56,24,247,220,59,185,173,
148,113,160,117,193,19,9,34,137,33,121,134,36,232,249,64,85,229,114,41,156,207,153,82,11,31,62,206,252,244,254,197,34,72,235,244,222,140,202,218,50,219,52,218,109,30,134,196,227,227,30,17,49,150,179,84,
180,55,174,231,249,254,103,200,204,117,89,89,102,37,87,59,171,135,105,228,101,94,248,124,186,80,85,25,134,87,172,82,84,241,209,18,209,184,243,28,198,9,247,151,255,245,127,236,116,147,5,242,243,247,176,
109,241,141,164,254,248,241,227,157,39,211,222,208,86,173,20,218,64,120,216,104,174,32,194,56,24,89,146,139,1,27,67,118,254,94,61,88,132,200,86,85,247,142,4,225,97,60,112,189,156,201,181,144,66,228,240,
184,35,37,127,199,211,195,40,204,207,63,35,205,147,34,132,135,199,119,116,44,9,244,249,196,178,100,150,170,104,235,136,119,188,251,246,247,104,85,156,179,178,41,70,97,158,23,114,89,55,198,103,75,213,27,
4,5,152,252,43,174,232,205,179,44,43,235,154,41,154,153,98,98,26,49,145,166,216,247,56,9,236,210,64,138,246,125,243,165,88,129,155,224,114,201,252,242,211,207,56,148,174,153,144,14,7,11,33,10,146,223,
50,237,236,86,215,108,80,49,196,78,163,88,26,174,142,57,43,93,133,214,39,124,104,140,99,196,137,51,144,115,54,160,52,6,171,72,108,91,97,156,26,165,102,208,78,12,48,108,199,102,158,47,156,94,62,147,246,
19,211,52,50,36,195,48,183,50,41,72,160,179,240,52,22,80,165,104,39,172,243,130,83,161,75,167,20,67,252,227,56,89,72,81,229,227,243,123,166,105,119,79,10,170,21,145,215,84,138,47,76,211,184,133,38,33,
215,122,167,2,138,42,97,195,214,113,91,81,180,16,69,208,186,50,142,201,98,235,45,156,229,74,239,229,126,140,170,214,45,212,9,40,140,33,18,78,63,127,143,71,9,94,200,167,191,193,184,163,74,66,155,241,18,
199,7,207,48,38,122,107,92,230,21,73,142,27,83,36,206,113,234,25,205,171,29,135,58,227,139,146,210,196,224,18,9,69,23,229,33,117,198,228,96,106,232,226,89,102,133,178,227,33,189,69,135,249,181,66,222,
10,87,137,66,215,102,44,211,82,153,142,130,195,147,98,34,116,76,24,60,205,149,15,223,255,5,250,150,36,82,220,120,52,185,223,252,121,94,183,74,216,221,107,46,63,217,106,166,20,41,75,166,230,194,231,243,
133,55,199,7,6,9,124,252,248,194,15,63,45,172,231,25,39,158,199,195,142,113,28,145,38,56,34,241,176,219,4,70,147,209,0,66,109,120,231,233,234,9,146,40,213,67,19,214,218,8,97,156,144,150,72,163,162,79,
143,100,205,27,223,11,18,96,189,234,253,7,197,240,10,47,111,200,109,165,209,90,167,105,99,191,27,208,49,209,180,241,249,124,229,83,174,140,73,76,106,19,143,46,133,247,203,11,69,127,1,175,140,73,104,239,
109,247,140,8,244,119,126,58,196,13,194,22,229,249,253,247,182,242,234,9,81,246,56,103,176,112,127,56,50,106,97,169,43,173,21,180,53,14,111,14,196,16,105,189,163,90,95,97,224,22,250,180,234,253,3,111,
228,75,206,149,101,89,169,69,121,201,103,196,89,201,222,196,49,95,207,156,231,207,72,88,233,12,44,229,66,174,5,113,30,145,215,172,153,194,173,4,171,252,242,211,127,221,142,177,39,236,30,191,2,20,93,51,
195,248,68,45,11,45,102,180,89,138,148,33,222,223,54,23,59,91,107,45,119,225,17,28,206,11,222,5,106,238,44,203,74,41,21,9,194,241,205,35,75,134,94,3,165,118,14,251,129,167,175,246,208,158,128,76,26,33,
183,76,201,5,191,113,206,185,84,122,111,70,44,58,199,32,194,243,163,99,209,10,10,225,113,119,48,192,28,50,28,143,228,178,35,228,149,85,23,84,149,119,95,239,9,49,32,98,104,234,22,45,140,11,115,232,178,
85,22,222,147,112,236,166,193,184,54,177,45,126,244,59,28,66,87,133,38,72,220,234,62,181,251,176,46,66,246,229,46,83,212,168,247,213,54,10,119,96,200,123,75,60,193,19,126,252,248,19,130,39,37,161,183,
66,154,132,113,63,17,228,240,138,79,241,228,165,208,187,152,118,215,5,154,2,142,97,124,173,46,146,68,82,154,172,64,109,221,212,39,63,114,56,164,59,184,81,85,90,241,84,221,211,186,35,185,189,97,10,239,
182,207,235,246,178,81,182,178,73,72,147,32,2,83,140,132,247,239,127,178,165,31,35,159,127,254,238,14,37,199,33,33,99,68,213,81,74,101,89,51,218,218,198,57,184,123,13,54,98,71,199,59,207,89,45,99,142,
41,49,77,35,41,138,81,175,5,43,70,231,121,147,28,14,180,234,233,26,24,6,71,34,188,86,217,189,27,69,224,28,121,163,121,231,151,202,188,22,158,203,71,130,115,23,60,202,233,165,242,227,143,127,102,201,149,
156,27,62,37,142,143,7,188,250,59,168,222,239,39,134,148,182,154,203,42,140,164,133,253,110,194,69,161,107,39,165,128,106,227,239,167,19,57,87,124,253,51,41,37,150,166,204,243,76,239,141,105,23,121,24,
7,196,119,30,210,239,239,44,81,217,202,170,146,13,56,221,248,58,185,62,163,10,207,231,51,225,15,255,240,31,237,210,229,206,83,152,88,214,204,188,20,130,36,118,211,136,139,95,86,205,198,85,172,57,227,157,
253,218,85,33,164,209,2,191,235,180,6,153,14,8,49,154,231,96,46,155,101,33,78,116,10,173,122,62,95,26,2,204,227,31,239,73,226,182,8,117,251,172,33,39,198,169,113,254,248,157,9,154,218,8,138,229,120,28,
28,82,102,16,120,156,4,68,8,210,200,69,24,247,187,123,250,212,246,74,244,245,222,105,165,48,166,116,15,117,170,122,87,132,82,10,236,191,21,230,121,165,160,200,24,16,57,152,220,85,42,94,60,78,234,70,113,
165,123,108,87,213,173,182,243,68,57,34,165,82,234,213,236,14,73,60,120,5,231,72,143,142,154,55,215,130,235,244,174,196,182,1,233,101,54,193,187,55,130,8,83,16,192,177,63,60,221,43,6,197,76,32,37,23,188,
243,76,211,192,169,126,196,85,133,82,177,72,168,112,99,248,189,39,103,183,213,121,254,94,4,220,52,14,231,29,189,236,105,211,27,114,222,65,84,66,157,49,54,188,123,244,131,220,83,100,191,189,169,183,139,
210,107,133,174,36,17,14,59,51,123,0,44,243,130,110,38,14,151,132,93,136,84,183,69,13,15,111,211,239,209,208,168,189,83,54,97,134,212,137,152,92,230,25,209,106,36,76,111,109,203,164,241,46,190,183,233,
202,52,43,103,206,118,137,63,126,252,25,69,97,46,252,248,199,255,100,101,78,107,119,106,213,79,70,92,223,66,205,152,18,121,222,142,64,41,228,217,228,44,31,77,55,222,77,38,33,172,221,202,159,195,254,43,
43,123,82,68,54,68,23,130,199,119,59,66,245,100,231,118,140,175,156,49,181,154,227,165,40,151,126,102,253,248,98,200,47,8,225,211,249,123,20,101,189,156,249,254,135,127,182,50,7,199,178,100,68,58,146,
191,54,3,199,90,41,181,160,218,127,69,183,38,49,244,38,206,35,81,240,49,216,25,95,235,22,155,103,100,74,196,52,226,188,195,187,155,205,166,67,134,97,42,27,215,49,48,142,166,46,185,173,252,90,150,149,222,
35,237,229,71,60,158,143,13,194,87,199,223,129,116,178,156,152,223,253,158,175,142,150,85,230,203,108,217,38,189,62,220,237,178,221,110,179,219,232,214,155,85,64,181,161,172,52,10,77,87,90,111,44,75,135,
75,133,56,211,221,134,109,179,82,86,51,131,228,106,11,144,66,184,95,220,184,237,102,201,149,170,51,207,63,252,128,199,67,21,194,241,248,239,161,21,78,114,226,248,237,79,84,81,92,44,132,183,71,246,83,36,
246,233,87,212,105,147,237,193,182,88,236,26,236,119,3,203,146,185,110,58,114,174,133,113,151,113,222,179,223,142,200,151,47,125,147,214,68,4,198,145,101,201,204,179,101,193,4,219,78,120,18,144,103,37,
111,104,49,95,47,4,48,251,213,94,2,199,199,3,189,43,215,50,163,90,40,171,16,119,130,200,86,186,236,32,109,32,197,56,251,206,242,114,33,166,4,73,236,31,64,84,241,75,70,188,103,201,5,159,190,100,237,133,
199,227,14,137,130,115,158,199,221,38,44,230,66,220,252,19,41,198,123,225,155,187,178,252,50,210,251,194,121,201,4,229,10,189,34,1,158,14,19,115,173,247,7,242,226,185,244,197,60,128,77,105,219,249,237,
95,2,248,232,104,163,224,155,99,12,114,39,182,199,186,113,14,215,249,78,221,2,91,81,96,71,168,86,229,244,225,19,89,51,218,20,186,144,240,70,82,185,142,143,13,87,26,189,23,150,178,160,93,9,63,252,248,255,
152,200,141,240,233,187,127,166,21,136,105,100,24,39,122,113,204,113,221,46,149,99,233,175,213,244,45,137,236,37,192,174,222,237,8,227,230,90,73,230,136,228,221,195,1,213,78,185,46,92,174,43,53,151,95,
225,134,208,184,151,72,17,79,89,10,101,41,119,129,156,86,144,86,24,197,227,181,19,94,78,239,233,121,161,41,252,203,127,249,207,208,61,135,233,72,74,3,203,82,137,49,48,14,137,180,233,114,33,6,226,144,32,
10,30,200,101,70,182,210,169,109,118,176,244,234,210,100,233,74,46,213,120,138,82,239,41,248,166,70,249,104,25,241,112,216,243,246,233,145,221,52,224,54,174,78,68,8,218,240,143,35,3,118,172,194,225,97,
66,117,162,151,204,215,71,131,124,99,16,188,7,41,138,22,104,173,147,215,124,47,18,95,182,21,110,173,211,85,239,46,146,186,212,187,155,164,168,34,181,65,226,46,237,238,166,17,231,28,173,214,87,227,211,
20,153,85,57,125,248,200,167,159,141,118,125,149,30,96,106,157,151,239,254,141,182,237,66,24,195,91,124,2,55,116,254,233,31,255,128,96,12,100,211,70,250,70,56,95,230,187,221,162,220,206,229,24,55,146,
164,81,214,106,90,200,198,58,230,213,72,16,178,225,10,63,4,74,85,122,235,56,223,204,76,26,133,221,206,84,42,99,130,172,46,116,117,65,103,187,128,173,153,168,126,109,157,191,125,248,104,178,130,54,130,
200,209,210,100,84,246,211,27,80,229,252,114,54,59,214,126,226,248,238,112,175,211,238,190,181,20,239,34,204,78,251,157,208,83,85,234,246,119,40,6,146,10,237,46,58,26,209,253,90,210,231,92,56,142,3,241,
120,224,112,152,152,198,145,222,26,159,175,179,221,43,17,206,170,68,206,148,92,200,90,8,95,63,62,225,3,4,95,72,207,143,168,22,222,62,237,145,96,224,121,193,148,121,99,23,205,237,103,180,84,69,81,94,150,
77,57,149,176,241,21,193,128,139,128,3,166,105,219,177,222,216,225,239,134,210,91,216,146,110,159,227,26,92,138,82,181,227,210,116,207,87,79,34,236,127,243,53,115,41,148,178,18,86,140,163,165,42,179,6,
158,222,189,227,120,60,208,180,113,157,51,122,153,169,146,153,231,153,185,100,68,132,105,23,120,58,38,36,5,190,85,185,115,21,78,95,89,205,27,249,23,69,88,114,230,58,47,119,2,81,106,35,151,202,226,50,75,
84,20,238,4,34,30,6,137,140,131,81,186,139,194,167,121,102,209,5,217,65,120,126,249,145,146,149,94,50,63,253,245,59,222,63,191,48,140,35,235,166,19,247,86,13,230,109,20,254,52,141,208,2,13,133,172,120,
237,136,242,43,60,140,182,123,248,147,100,219,220,122,39,58,33,17,8,131,97,135,225,48,33,62,51,110,248,226,118,97,133,237,136,181,198,53,43,121,56,64,107,228,121,37,44,31,62,220,93,213,249,239,63,114,
174,223,83,49,139,108,105,141,247,235,231,141,70,117,175,86,154,205,14,86,75,101,23,3,177,25,182,189,201,174,109,171,247,188,119,208,140,234,138,41,220,33,169,223,128,82,16,225,235,105,143,12,137,105,
50,59,194,237,200,232,106,149,57,107,198,207,127,101,186,46,156,175,51,225,183,223,254,71,28,5,188,34,255,225,63,0,153,130,233,24,231,124,225,247,250,100,229,120,206,124,62,93,200,61,51,110,133,42,163,
16,75,5,129,86,50,89,203,134,47,26,17,143,32,70,92,207,11,37,123,46,165,48,207,11,235,23,224,233,199,77,35,185,101,215,232,253,157,187,107,106,158,226,151,239,255,2,173,83,18,132,101,60,154,212,218,50,
231,244,150,70,166,234,76,97,33,247,196,148,45,188,140,17,118,143,79,168,56,246,147,85,197,34,194,33,58,106,49,64,83,54,139,204,205,236,57,109,8,76,85,185,108,201,34,247,106,113,26,115,95,101,49,246,104,
217,60,114,165,52,212,123,66,16,122,111,84,231,105,79,203,118,60,86,130,236,38,210,224,137,173,81,207,223,80,242,130,239,21,113,13,232,200,165,34,33,224,156,67,209,215,109,215,70,150,202,57,111,200,77,
61,16,65,26,136,167,57,97,65,216,141,130,230,66,138,22,205,167,32,155,1,31,214,174,204,206,126,255,88,55,58,246,214,28,176,221,137,235,233,138,172,103,246,67,98,92,27,225,237,46,111,32,170,243,245,222,
225,210,200,136,67,186,101,168,143,227,98,162,184,87,164,9,126,171,104,67,242,196,20,40,87,11,117,117,195,201,107,41,232,156,169,85,89,181,176,46,51,110,115,252,17,5,159,28,108,254,247,128,48,45,6,67,
35,225,158,44,110,0,63,231,194,63,30,247,124,240,39,146,8,67,72,132,191,255,249,95,40,69,241,56,126,254,211,63,163,25,36,237,73,187,9,71,224,58,127,166,245,198,126,55,113,124,154,238,162,248,237,2,145,
149,224,18,116,15,37,48,224,144,253,72,99,97,158,175,28,247,191,161,183,138,122,5,215,104,209,211,177,58,212,123,192,27,157,240,176,159,24,135,116,47,98,243,156,55,111,188,227,225,237,59,162,8,163,8,225,
199,191,125,15,21,196,37,126,248,243,119,84,2,12,123,210,56,1,30,241,74,111,133,95,158,161,252,201,60,240,251,125,226,237,155,71,198,49,145,47,22,246,162,155,238,5,100,26,29,222,117,198,33,145,219,70,
88,187,45,70,59,43,223,213,57,164,119,82,18,34,13,45,230,78,233,107,177,243,188,153,239,34,129,211,143,191,208,5,118,83,36,252,195,187,111,41,29,124,0,153,191,101,238,194,220,58,69,131,209,255,193,145,
210,30,231,225,122,185,178,172,153,56,8,231,124,230,151,115,166,101,208,220,182,142,15,59,119,57,111,74,102,186,117,13,116,98,55,158,174,109,222,54,191,1,148,49,76,132,45,234,36,239,190,16,115,58,219,
241,230,243,143,223,153,193,127,31,9,242,238,119,184,214,65,11,225,237,59,30,128,9,251,193,181,24,13,107,254,49,37,166,29,95,135,71,118,251,137,222,43,231,203,140,46,142,92,205,48,234,182,135,238,189,
129,235,56,113,204,217,86,88,179,162,243,38,133,193,134,131,149,129,6,165,209,115,230,188,177,59,108,169,188,181,206,186,102,222,255,229,39,166,201,236,190,65,31,127,107,93,42,249,74,222,191,99,242,141,
7,167,8,214,166,115,153,179,153,98,54,222,107,28,18,49,25,114,115,46,48,60,141,148,205,15,175,229,166,224,7,64,40,170,60,236,227,70,9,52,150,75,69,231,217,178,166,22,74,183,44,215,122,135,210,94,95,22,
190,64,212,240,187,157,25,115,214,170,132,210,130,253,113,232,72,218,225,107,102,201,51,101,89,209,156,209,30,54,127,186,25,158,135,97,216,86,80,137,211,158,221,222,200,193,117,201,228,106,10,80,74,3,
53,7,74,46,124,190,156,24,227,68,12,35,113,47,200,99,39,136,3,159,169,154,73,27,233,210,179,254,170,88,149,13,19,151,162,76,172,208,32,175,133,240,40,43,34,142,64,226,120,56,144,124,103,93,246,156,253,
68,27,59,200,107,51,137,106,69,53,25,149,20,173,62,139,201,131,42,147,36,38,160,53,79,85,16,113,200,180,99,127,216,147,100,135,99,36,111,171,39,78,169,253,76,201,43,101,89,208,238,208,202,230,32,124,45,
86,1,246,187,61,249,122,36,37,207,94,132,48,45,39,107,71,107,149,245,211,47,244,48,209,188,48,76,143,68,73,44,139,81,164,215,121,102,93,26,33,45,120,111,234,166,185,89,87,58,202,144,132,253,97,34,74,98,
93,33,186,137,113,76,28,198,61,34,19,170,98,29,97,30,252,208,9,68,70,57,227,166,201,112,203,214,133,227,183,163,113,35,6,159,175,11,239,63,158,41,106,214,178,240,243,79,255,74,207,102,232,124,254,227,
127,34,134,129,68,4,60,41,14,180,100,150,216,135,33,241,0,144,49,203,247,188,48,207,43,231,249,194,52,141,212,14,31,127,50,208,29,130,176,2,139,8,151,73,136,227,68,138,129,92,148,207,167,76,237,134,250,
246,211,129,165,53,98,16,166,97,224,105,26,97,178,99,32,226,204,89,112,92,248,54,126,67,39,160,34,132,151,143,207,230,227,157,87,190,255,243,247,230,101,216,28,84,41,68,194,230,90,5,203,13,245,11,50,219,
139,35,61,36,150,26,77,255,40,122,23,203,111,2,225,238,97,132,23,208,238,232,186,109,184,68,150,37,112,58,63,51,61,60,81,170,195,172,31,233,94,77,83,33,84,97,10,141,21,69,80,84,133,112,216,191,69,81,218,
46,83,254,233,91,196,127,209,125,21,35,159,175,51,173,191,94,136,222,10,93,204,77,189,223,79,92,169,84,250,134,33,0,49,207,47,89,105,5,190,251,235,123,90,179,7,149,148,72,49,16,98,186,23,177,249,231,159,
239,41,249,230,193,184,125,25,135,225,249,249,135,63,225,186,128,58,2,97,111,241,112,216,179,127,251,141,241,108,181,80,90,198,139,224,130,69,215,27,4,76,189,51,181,134,143,230,170,122,232,118,12,188,
243,136,247,22,179,171,245,20,169,42,239,210,55,119,122,106,93,116,251,217,29,145,132,143,142,41,117,74,45,228,181,178,46,22,123,111,226,162,247,142,79,151,202,143,239,63,160,181,80,46,157,64,154,0,71,
241,202,18,15,104,171,156,91,163,86,33,32,48,61,26,145,226,95,59,4,110,146,148,121,36,51,185,180,215,23,42,102,68,218,88,83,118,50,146,68,152,142,130,30,221,157,253,20,177,18,170,250,217,176,67,49,70,
255,203,47,231,28,235,58,19,243,55,72,114,128,39,28,158,222,34,218,201,229,202,229,225,64,238,149,253,146,88,122,38,133,112,111,202,179,251,102,162,203,77,177,156,231,21,231,2,93,43,75,86,162,119,172,
91,150,234,205,211,52,178,147,29,68,193,133,200,97,76,68,17,204,146,100,59,32,201,154,179,44,157,155,247,232,198,181,245,174,164,100,21,201,77,105,10,199,36,244,166,140,195,14,255,180,223,0,152,82,40,
196,20,73,196,47,76,67,214,170,208,110,63,120,90,25,222,90,250,236,173,25,207,80,21,205,175,2,164,247,198,23,175,235,204,170,214,138,118,115,206,58,239,105,53,65,19,82,176,118,161,29,160,59,189,31,11,
80,134,102,222,79,237,16,250,124,134,205,25,56,145,193,11,161,22,50,29,81,229,16,19,85,185,91,100,138,135,117,201,72,107,140,34,44,100,124,2,113,194,40,209,206,104,220,116,145,210,144,205,199,51,142,19,
49,153,25,164,214,106,236,189,42,83,124,36,99,196,9,95,120,77,163,179,151,138,222,113,149,145,113,28,237,210,125,60,61,163,170,236,82,228,229,199,143,168,15,164,52,162,5,36,66,60,212,215,254,79,239,152,
66,196,123,143,100,179,191,244,212,145,238,208,214,57,233,124,47,125,110,166,209,175,190,249,13,98,182,78,208,74,213,78,112,123,134,253,64,116,137,52,98,178,90,239,27,169,237,89,115,166,105,179,94,62,
173,80,207,104,48,41,38,156,62,157,41,53,243,203,170,252,235,127,254,191,208,106,14,169,16,133,52,237,73,209,202,237,219,3,123,231,9,155,150,214,180,49,125,243,192,152,76,219,48,139,57,104,0,239,13,50,
158,94,62,209,90,69,187,33,49,211,140,18,18,18,209,39,202,156,153,231,149,222,26,195,56,222,239,135,136,144,135,196,241,113,207,216,61,90,29,165,43,65,210,136,115,17,66,225,233,233,145,66,35,198,120,239,
38,200,213,218,32,90,86,242,178,222,101,131,155,37,140,249,197,30,52,70,90,52,150,135,141,69,15,34,124,62,205,224,204,75,153,6,199,78,70,11,125,106,40,238,171,233,129,92,43,222,57,68,34,163,136,49,32,
106,37,254,159,255,248,129,151,143,63,89,219,15,141,176,63,190,5,10,165,41,95,253,211,63,208,123,161,160,214,33,72,99,148,129,146,43,126,54,144,15,240,232,119,4,103,109,18,196,118,63,50,75,211,59,81,93,
55,46,109,156,34,165,40,125,93,56,95,149,217,93,137,105,32,109,59,240,247,203,103,242,70,162,95,230,103,198,113,188,55,197,138,120,14,211,68,106,103,214,117,33,151,76,152,222,60,210,180,32,181,48,189,
123,3,210,233,189,208,154,146,117,101,170,137,249,186,176,34,16,130,93,190,49,177,11,137,33,69,150,47,236,227,206,91,8,212,214,183,18,199,76,164,244,78,45,141,166,182,43,193,113,23,225,7,86,174,151,171,
29,11,174,44,57,111,76,167,29,158,191,254,252,204,243,95,255,204,181,43,218,148,48,141,9,237,66,41,240,112,120,196,249,78,109,153,69,43,117,245,120,117,164,52,210,187,71,134,193,30,56,90,255,166,11,194,
99,58,220,251,134,186,118,150,90,104,69,153,246,3,251,141,12,241,226,17,31,40,69,89,115,38,47,51,203,58,179,104,69,83,99,78,144,187,97,150,155,130,20,196,154,4,254,240,237,192,211,94,41,169,209,123,37,
204,47,23,67,247,2,83,23,146,68,50,129,99,18,138,60,240,97,249,196,184,155,120,120,140,12,27,149,116,67,100,222,59,230,108,68,119,85,101,206,11,231,229,213,47,159,8,200,227,184,77,81,104,52,25,112,83,
100,152,38,118,100,84,43,15,135,137,189,208,222,171,0,0,32,0,73,68,65,84,53,223,178,156,188,26,78,111,122,96,79,180,195,51,234,59,180,66,40,151,133,232,61,69,11,250,97,38,251,149,230,176,214,93,26,15,
211,35,211,52,50,109,84,126,157,51,151,101,97,93,23,180,40,87,50,94,28,34,129,148,18,95,239,247,200,96,231,219,121,191,153,152,60,181,130,184,173,193,196,87,148,76,111,133,203,185,67,50,2,209,137,177,
157,222,155,78,18,163,64,134,86,179,185,103,117,37,172,250,29,115,87,124,241,252,242,252,47,208,19,184,201,172,227,4,124,152,185,196,215,65,1,55,112,210,180,227,197,49,46,246,235,136,105,212,21,32,142,
200,100,136,236,144,54,47,68,177,142,196,56,76,230,94,13,201,6,85,188,92,204,91,20,2,176,218,89,214,102,154,74,16,14,113,199,219,174,76,143,19,97,216,19,126,249,233,3,181,65,235,202,143,127,252,139,77,
146,232,9,145,184,133,43,185,251,212,238,197,203,70,216,57,231,56,30,2,82,27,13,79,111,110,107,101,240,236,15,19,50,78,124,94,234,93,204,201,116,158,231,207,198,14,109,152,59,140,137,55,15,7,142,95,189,
97,28,38,202,180,51,59,111,179,232,243,233,151,191,243,203,79,127,166,226,204,164,148,198,55,164,90,169,185,18,124,178,20,233,42,30,181,9,19,109,183,177,52,30,217,30,92,139,82,86,59,119,122,154,33,91,
151,86,244,214,118,233,99,34,162,140,93,153,100,143,195,161,165,211,115,166,175,25,26,4,239,136,2,56,79,240,158,174,43,243,117,189,203,10,218,76,121,186,44,51,231,243,11,94,28,69,35,225,31,127,251,223,
163,121,97,169,43,97,125,193,7,35,1,17,227,38,70,49,233,181,84,67,84,243,188,112,157,23,242,146,205,157,154,149,114,93,136,179,249,214,196,7,202,186,240,60,103,244,253,11,85,221,175,0,185,4,51,46,183,
222,204,226,235,141,17,242,206,164,137,170,217,218,60,83,196,59,199,225,73,248,120,121,97,156,6,134,216,9,109,60,208,72,224,23,252,241,43,198,201,147,146,71,213,182,109,213,197,218,206,85,240,173,177,
127,179,227,24,12,176,59,113,12,75,231,58,47,8,145,221,102,138,126,185,206,44,106,22,6,25,220,102,197,181,254,142,195,86,117,220,132,201,150,183,80,151,11,195,174,225,138,217,125,79,23,211,254,126,188,
206,252,248,111,223,51,166,129,73,34,65,169,16,59,93,4,55,13,184,205,62,83,186,185,83,31,194,129,255,239,151,243,222,52,13,231,73,62,49,45,153,180,205,144,40,69,241,107,230,182,176,50,202,198,253,174,
212,92,113,91,147,223,152,18,49,69,218,121,49,72,218,172,95,164,107,231,249,229,196,203,203,139,237,202,20,121,72,206,154,105,171,18,224,2,98,230,137,113,84,204,115,236,144,102,221,196,96,225,73,130,32,
222,25,63,92,148,165,88,135,237,28,27,189,86,102,192,53,208,218,32,88,19,139,2,215,6,126,156,120,216,31,140,237,81,179,211,148,222,40,171,178,59,140,196,77,207,144,205,59,60,69,208,41,26,69,11,232,183,
223,32,162,136,54,194,95,127,254,19,9,115,177,158,254,246,227,38,201,6,3,68,64,10,211,93,70,189,19,117,189,223,251,63,63,231,51,117,206,208,173,11,204,168,211,61,146,2,107,83,220,42,95,116,130,185,123,
127,70,41,138,244,206,231,172,140,163,128,23,174,106,133,192,130,163,197,4,206,177,139,35,211,241,145,99,20,6,91,216,198,232,3,226,27,121,61,211,63,27,19,217,90,167,230,198,48,166,173,227,208,116,142,
91,143,70,211,173,149,98,112,28,247,123,166,20,216,37,225,97,170,196,165,48,95,42,90,225,24,172,51,220,112,5,16,61,108,253,123,75,171,68,223,209,205,128,167,165,144,23,147,121,31,167,29,218,26,49,101,
116,20,50,144,17,194,238,220,145,190,26,102,253,241,132,106,35,18,205,252,148,11,87,50,57,217,246,120,239,77,144,217,110,52,57,67,1,221,207,212,228,184,10,172,155,5,49,215,74,69,120,46,202,184,181,58,
140,97,224,241,113,207,116,60,50,28,198,109,172,200,235,113,208,144,80,121,157,64,99,123,50,241,16,29,215,146,41,5,194,155,183,95,163,53,147,151,194,126,63,209,138,7,156,169,63,77,209,174,148,141,56,137,
65,24,36,209,68,104,162,32,13,63,87,234,57,115,105,138,138,0,141,101,173,172,170,136,11,172,177,163,34,100,39,204,192,201,219,44,137,91,185,148,137,116,189,245,111,164,205,70,57,161,211,72,12,194,124,
121,230,211,95,191,227,165,216,221,9,28,15,214,177,152,23,194,229,27,35,160,189,39,85,136,107,102,89,46,91,171,77,35,196,136,23,49,77,67,13,54,62,228,133,249,60,147,151,153,213,217,116,153,181,216,144,
24,21,207,193,59,134,40,248,6,100,227,161,243,156,153,79,202,172,133,56,78,247,5,17,73,175,93,235,91,36,74,14,62,252,245,59,150,172,16,133,176,110,21,113,77,35,186,27,168,173,147,181,81,168,100,215,216,
191,251,154,8,86,50,109,103,249,58,47,104,206,120,237,36,102,214,228,224,210,16,15,107,235,20,15,185,129,247,129,229,50,147,90,100,138,194,254,144,76,100,12,194,82,149,169,20,122,94,89,22,54,169,12,90,
151,187,138,234,157,39,207,51,78,102,36,57,86,157,9,250,113,5,177,73,71,105,49,0,62,56,232,33,210,252,64,100,178,76,132,71,186,213,91,94,27,3,130,4,207,14,97,220,9,110,122,196,187,206,114,93,184,202,98,
23,215,123,120,243,21,185,46,212,165,240,156,43,190,46,200,224,239,116,66,242,141,50,216,195,169,55,195,243,102,163,166,107,101,183,63,178,127,250,150,125,74,102,101,220,133,157,1,52,241,200,120,64,197,
128,71,217,88,152,72,48,109,162,84,35,185,155,13,218,186,141,108,72,227,145,97,156,16,223,72,192,186,55,65,69,183,152,250,241,116,198,107,96,145,76,22,19,215,101,31,73,83,98,114,142,227,195,72,107,175,
28,244,186,100,28,241,238,31,206,115,97,109,13,145,136,239,16,152,34,68,163,228,251,96,241,16,231,137,222,84,118,93,150,155,74,130,111,221,254,237,188,141,52,163,114,34,177,214,66,104,186,9,218,149,186,
37,130,162,16,87,97,72,3,199,201,206,37,9,24,2,4,232,14,228,112,216,38,141,109,237,18,100,147,156,130,64,84,166,199,153,62,78,144,109,114,83,152,63,254,124,183,116,61,127,247,29,195,155,29,187,253,1,197,
243,249,50,243,102,191,191,247,52,223,47,159,8,218,59,235,146,25,90,97,183,219,223,180,201,141,19,243,84,173,104,174,156,226,153,152,2,163,108,29,53,155,47,224,198,188,206,55,255,143,55,111,209,52,132,
13,107,71,68,27,94,30,224,188,178,208,144,32,132,181,174,56,26,29,207,82,102,150,95,10,215,107,38,164,132,164,180,205,253,10,91,214,115,27,101,116,27,51,98,30,159,146,21,106,187,135,62,231,61,189,216,
196,154,92,138,245,65,111,253,248,121,211,224,186,7,23,132,121,163,181,134,209,86,176,181,6,42,72,106,36,239,137,62,208,36,144,134,78,240,129,224,92,217,38,32,5,126,251,238,128,34,20,21,90,128,65,60,65,
43,249,124,222,198,50,85,214,92,238,230,103,239,61,11,230,189,28,71,195,210,159,79,87,51,106,108,179,127,196,123,214,235,130,94,51,178,141,219,25,189,49,145,84,120,124,124,184,79,15,19,239,57,95,174,228,
210,137,93,173,235,235,148,137,179,245,74,249,212,9,73,58,181,87,150,243,204,135,191,254,13,197,186,82,242,109,184,202,182,114,206,121,68,44,190,246,222,8,33,16,99,96,217,178,224,245,236,145,6,37,91,227,
160,165,244,9,159,132,182,52,180,22,124,131,161,67,114,1,217,220,130,206,234,46,98,46,150,245,78,43,101,205,180,32,52,17,70,172,12,27,167,132,58,8,207,47,39,107,144,206,202,188,92,153,198,29,143,143,7,
156,243,228,218,152,231,139,25,148,170,162,149,123,96,79,97,36,5,177,150,226,57,83,123,227,97,24,57,62,154,30,61,207,11,215,79,159,88,150,149,113,28,216,13,137,146,149,249,151,23,46,91,3,149,75,97,235,
90,55,182,223,187,112,223,189,97,76,32,130,72,164,175,103,164,79,166,206,157,207,153,113,8,56,245,228,57,211,47,153,124,58,211,91,55,153,118,67,106,211,152,56,236,39,155,160,180,141,185,241,186,146,226,
72,18,227,222,168,87,230,211,66,190,46,60,63,127,230,124,190,240,246,237,17,173,137,60,199,173,183,180,34,77,201,128,203,114,111,56,204,53,177,159,70,156,152,215,98,140,183,234,164,241,233,114,226,252,
203,47,92,87,8,49,237,112,29,132,78,34,224,189,18,197,38,29,189,217,7,180,26,189,122,253,248,194,203,251,143,247,65,43,183,41,30,249,124,254,149,115,21,96,146,200,239,191,126,64,190,125,3,219,228,48,180,
224,146,216,72,191,253,0,65,232,30,150,108,250,180,108,195,141,96,171,102,60,120,177,158,14,4,174,221,76,82,225,15,191,255,111,237,182,183,204,155,254,7,150,249,51,151,151,207,204,203,21,205,11,159,207,
122,159,69,229,191,104,56,189,92,102,235,136,137,16,83,184,215,107,201,11,42,202,121,177,58,80,114,191,155,148,170,51,209,134,49,18,14,3,50,37,14,199,39,155,213,22,4,21,235,119,106,218,12,54,23,227,233,
230,190,112,60,78,124,253,238,72,56,109,196,91,169,141,79,37,49,28,126,67,58,254,150,195,70,169,202,50,223,189,194,85,21,188,35,56,143,108,24,36,56,181,212,237,29,130,173,230,69,235,189,39,52,77,70,10,
214,170,4,177,207,210,151,5,94,22,82,138,188,164,151,59,155,228,196,147,226,235,172,181,90,148,166,153,151,31,255,171,245,79,227,9,81,28,94,34,62,193,195,214,53,251,165,250,116,124,122,180,20,89,202,189,
249,250,62,71,162,119,106,57,191,74,10,218,209,160,72,47,196,49,90,201,159,87,194,148,16,53,123,47,218,88,242,140,223,102,88,60,127,58,49,139,89,39,111,253,27,211,20,57,30,15,236,167,129,243,121,225,211,
139,145,43,69,60,33,28,15,24,35,171,200,124,184,207,243,187,141,116,84,60,136,17,204,78,219,125,86,224,173,159,195,32,135,165,98,156,131,232,128,196,102,30,103,94,11,78,4,217,26,84,189,40,163,120,72,118,
76,190,125,156,238,93,187,183,139,94,181,128,243,20,132,221,211,145,199,243,1,45,13,157,33,104,174,212,174,168,46,60,191,156,182,109,182,54,7,239,59,227,238,64,105,141,230,183,44,183,141,187,208,222,80,
96,119,124,216,64,146,255,245,244,142,106,103,55,220,86,182,88,73,213,242,178,69,95,27,22,243,241,227,203,221,168,111,3,230,18,195,46,108,210,238,200,178,46,244,183,111,173,231,99,41,95,116,45,225,17,
137,4,113,247,22,5,109,157,162,157,109,234,11,49,5,226,23,229,126,235,141,53,219,40,168,220,54,148,87,51,20,155,43,216,212,132,27,68,104,174,131,118,122,24,13,10,104,7,81,14,143,230,6,188,53,180,212,214,
185,190,204,124,124,190,226,189,99,119,72,92,79,43,195,148,72,78,8,226,109,204,99,19,97,146,141,113,17,40,181,152,76,224,245,255,199,75,200,23,231,120,218,61,152,46,87,204,201,119,67,100,91,187,51,189,
23,147,186,130,160,143,205,180,43,148,216,236,133,253,86,220,206,243,202,249,50,115,189,94,41,8,113,176,130,161,162,92,20,220,220,232,81,8,130,208,189,130,218,140,80,205,133,220,109,160,69,169,122,79,
161,186,105,26,77,251,125,158,159,23,71,222,86,211,58,24,237,236,135,47,124,242,196,68,11,130,17,241,158,178,49,73,243,102,224,208,217,218,47,198,105,34,13,3,199,183,15,247,169,143,38,210,43,75,156,88,
75,225,172,43,161,230,108,67,224,218,202,233,124,53,129,176,27,36,117,222,195,205,15,188,121,113,238,12,195,198,244,212,13,168,223,218,48,99,3,252,23,23,179,66,110,6,75,117,53,103,182,170,205,120,19,28,
163,24,104,58,157,47,247,25,21,206,59,180,217,4,178,20,35,231,98,195,140,240,133,224,212,218,196,146,15,188,217,79,164,41,65,176,241,98,107,46,248,206,125,162,232,154,235,235,216,210,190,21,50,209,124,
64,178,153,62,50,138,179,212,105,78,194,179,205,137,112,40,210,236,189,189,75,72,50,114,176,109,54,133,131,26,233,216,215,98,101,146,122,30,82,34,166,198,50,29,80,201,120,6,194,170,121,155,67,21,113,41,
154,143,119,249,98,54,37,221,44,141,222,17,199,0,226,238,204,79,140,130,186,112,111,195,57,95,94,157,213,155,195,128,162,25,197,111,28,177,48,141,129,32,252,218,32,186,37,158,150,149,146,2,67,214,215,
33,27,20,220,122,100,190,44,219,132,189,173,218,104,90,120,57,93,44,65,96,19,69,67,74,214,81,176,17,76,173,55,250,38,180,220,188,101,41,110,103,53,69,30,191,16,97,216,46,235,110,63,253,106,132,200,171,
127,200,178,159,94,245,94,210,163,157,86,212,70,66,136,161,184,49,109,35,82,85,201,57,19,14,111,110,131,135,178,97,216,209,152,245,33,69,134,49,113,154,151,251,24,145,27,180,12,242,202,151,157,79,167,
187,124,96,77,130,74,41,253,222,239,92,182,7,183,214,248,118,31,22,208,183,1,204,226,27,89,51,126,11,223,45,219,37,118,106,45,22,113,154,140,48,223,192,127,40,61,211,212,210,129,15,32,62,160,173,82,52,
211,230,178,41,147,205,154,181,229,22,29,250,125,197,222,61,238,237,24,229,74,111,186,173,108,71,194,54,108,123,181,198,149,224,76,206,133,77,131,243,134,202,74,41,240,69,147,108,236,246,208,183,52,253,
254,124,225,244,193,240,6,162,132,40,1,153,172,116,115,211,214,99,84,109,56,114,74,145,117,89,241,116,190,28,2,214,85,95,219,41,231,133,82,204,39,121,235,130,185,117,160,221,18,130,19,65,131,152,195,197,
123,188,180,13,240,88,17,173,85,97,94,136,183,113,127,219,89,53,165,171,210,47,51,185,67,11,74,88,46,47,212,220,81,205,156,126,122,111,152,54,43,97,16,246,211,136,100,126,53,180,229,158,229,180,67,107,
92,180,218,164,59,239,136,98,246,197,40,198,222,148,92,108,98,116,235,232,92,41,221,6,201,25,129,221,104,189,208,169,204,167,249,62,16,84,212,22,228,118,169,93,241,92,95,78,172,61,147,151,74,240,222,131,
47,56,26,105,16,164,11,69,170,145,207,235,130,102,40,91,107,206,178,172,232,54,20,249,21,180,103,155,135,153,34,173,91,47,104,74,145,182,117,231,238,100,164,110,158,180,126,159,84,83,239,125,121,89,231,
141,77,178,162,149,14,173,168,197,123,13,212,10,161,43,187,97,196,29,29,97,249,248,17,93,10,165,123,158,255,246,241,158,213,106,174,156,231,149,235,229,196,24,197,116,226,205,65,125,47,233,83,164,37,135,
95,214,95,173,126,253,98,2,222,33,29,108,156,79,111,56,233,236,135,0,189,18,27,60,30,2,15,233,107,114,45,156,87,155,200,132,243,60,238,6,100,155,4,141,243,132,169,51,78,129,221,152,8,167,207,159,89,231,
149,101,158,249,183,255,243,79,228,92,240,67,100,55,13,86,126,187,72,146,100,137,64,140,242,188,205,112,7,177,121,240,222,49,12,137,105,55,114,216,77,247,57,174,222,89,115,172,147,45,105,59,69,176,68,
53,120,152,198,100,161,109,27,177,250,114,186,144,107,167,137,219,132,70,88,181,82,105,156,230,202,233,146,9,41,68,210,20,56,238,247,196,255,238,119,230,151,240,195,125,226,56,189,217,89,222,134,98,180,
178,249,131,55,137,64,182,182,222,113,72,60,60,238,239,68,244,173,253,125,153,109,144,198,90,108,96,98,206,51,173,174,36,60,130,103,46,43,117,51,237,207,90,161,9,113,12,132,184,105,28,135,1,13,17,68,72,
209,17,222,61,60,90,55,237,32,252,187,167,255,193,82,242,98,173,59,185,42,151,211,140,184,128,199,147,130,131,0,94,234,221,161,18,189,217,110,203,170,204,231,204,76,230,124,153,191,152,170,27,120,57,157,
89,107,217,186,25,26,131,68,36,25,199,241,120,124,186,39,20,25,6,43,239,189,167,150,194,165,84,210,227,142,75,170,104,135,222,148,240,249,243,5,90,197,165,128,126,124,127,111,70,53,251,183,187,55,156,
108,173,207,136,8,251,49,222,71,172,47,27,190,0,184,148,76,20,123,1,196,221,231,10,142,251,145,201,77,16,5,209,206,40,129,49,69,164,193,41,111,243,213,170,162,151,207,100,26,116,185,13,30,229,152,18,47,
217,142,77,157,59,97,154,38,178,174,52,231,208,98,221,223,183,81,146,32,124,253,213,27,36,24,176,214,102,34,77,20,65,186,34,185,114,12,129,154,235,38,28,154,155,42,109,67,140,162,8,107,169,12,187,136,
191,53,110,95,22,78,75,230,178,84,146,23,211,46,54,163,115,1,122,19,220,24,57,62,28,120,124,220,217,255,82,224,241,145,117,134,18,102,2,33,110,51,73,28,241,241,96,179,42,47,51,85,45,214,126,247,183,247,
72,176,85,91,115,198,109,227,36,181,119,123,185,57,223,61,109,105,43,247,255,95,178,222,109,201,145,36,187,178,92,122,53,51,0,238,30,151,140,202,234,34,217,228,76,63,244,255,127,202,140,140,72,75,183,
12,135,69,86,87,50,178,226,226,1,119,0,102,166,170,71,117,30,142,154,193,131,124,34,171,68,42,19,14,152,169,158,203,222,107,219,55,96,162,136,65,156,206,209,246,164,137,16,113,213,50,76,3,67,120,192,196,
174,22,136,142,180,170,72,68,169,96,128,215,93,161,3,170,29,241,62,12,224,4,99,161,184,8,206,48,77,93,183,16,34,195,164,207,225,186,36,94,146,78,235,99,12,123,17,127,140,241,39,174,235,222,149,244,57,
92,116,142,165,20,94,95,175,157,77,117,98,12,129,9,221,77,231,214,143,64,49,132,230,25,14,142,201,77,42,18,233,158,189,56,157,144,40,228,92,240,105,136,189,79,40,188,212,76,28,29,15,79,19,174,233,1,255,
34,70,211,26,92,128,163,150,132,185,251,247,157,179,228,21,90,53,84,177,184,55,29,159,244,179,250,42,122,87,15,15,17,87,43,21,88,26,212,104,72,34,44,146,123,108,134,229,154,10,100,245,161,26,99,176,205,
114,171,150,219,210,52,177,130,140,143,211,8,182,82,196,226,198,145,180,100,174,203,69,21,173,206,98,58,203,175,74,221,201,51,155,164,211,56,195,24,130,22,69,27,251,164,223,130,74,93,82,106,227,166,175,
144,168,74,217,188,255,26,43,143,241,180,151,156,174,155,188,115,86,253,70,171,25,231,6,124,169,157,86,29,240,216,128,160,127,25,98,168,86,129,88,165,47,70,198,6,120,197,128,140,118,208,10,11,101,186,
215,90,201,53,253,220,160,246,42,201,57,139,237,245,179,177,166,219,143,218,254,248,208,139,155,47,223,191,224,186,108,113,235,19,125,95,27,75,171,152,185,32,231,51,37,23,144,130,159,162,103,94,148,54,
16,71,207,209,15,200,169,79,39,171,62,42,90,149,93,247,111,216,25,75,8,134,224,44,20,5,124,239,96,101,175,112,194,237,91,139,210,200,73,197,121,243,27,139,240,6,3,101,185,203,200,66,112,56,19,144,238,
118,108,173,242,16,143,204,215,103,242,101,102,77,9,159,230,132,228,21,41,11,233,122,69,172,33,83,238,11,190,69,177,124,83,244,28,163,142,70,95,175,87,206,95,110,92,46,55,66,82,161,199,166,253,117,238,
174,140,106,173,49,184,78,68,122,83,158,186,126,210,56,231,25,92,214,51,86,4,153,133,220,96,238,10,241,38,141,47,57,243,183,127,249,103,230,57,177,230,130,255,237,159,255,39,164,76,66,248,235,255,250,
31,187,176,67,140,110,118,162,211,151,78,141,168,121,119,212,214,86,41,53,241,152,198,189,139,214,253,134,220,33,45,185,48,28,167,29,9,89,123,235,159,210,162,246,33,32,173,202,208,222,0,116,42,145,52,
251,212,255,188,94,249,246,229,111,24,227,152,162,195,159,127,255,29,107,245,47,186,124,249,76,238,116,80,103,44,217,26,94,182,58,21,75,244,142,49,56,108,247,49,219,36,187,161,186,255,166,157,138,107,
176,85,183,74,175,207,23,76,236,132,198,232,116,139,84,171,222,108,181,193,168,147,33,231,13,113,115,66,226,118,154,244,31,34,252,233,221,72,176,158,225,16,240,191,60,30,244,237,172,2,159,158,176,81,71,
249,119,74,93,223,3,163,240,160,209,41,97,191,86,21,41,13,124,32,173,119,57,184,143,126,23,106,148,44,152,232,104,174,195,104,45,212,14,175,183,78,255,239,11,155,233,47,236,143,147,70,26,57,66,112,28,
162,229,135,21,106,214,95,218,199,95,30,180,168,113,142,208,254,142,104,220,46,235,174,205,80,200,138,139,236,47,201,224,226,79,240,138,88,28,47,181,240,133,196,45,232,42,43,90,93,166,56,105,58,81,50,
192,24,32,168,68,125,50,29,138,241,146,57,202,170,106,236,106,49,91,192,142,232,29,144,83,33,201,64,100,224,92,110,120,227,241,211,211,7,156,81,25,184,139,71,29,141,138,48,26,229,79,165,221,43,164,206,
196,155,24,94,23,237,223,150,148,112,83,100,181,141,197,245,7,199,122,108,12,212,46,195,97,12,10,99,153,34,130,193,46,130,193,242,48,57,204,164,207,115,74,170,216,150,214,118,183,151,237,47,105,244,35,
130,130,182,196,89,124,152,38,114,170,20,155,200,120,176,65,189,73,147,98,207,19,186,241,92,179,22,222,27,176,34,246,155,226,213,47,255,161,215,171,136,99,103,81,220,92,38,137,194,104,83,17,184,101,38,
171,41,65,99,245,42,53,119,130,140,109,63,93,54,16,146,180,70,106,194,37,37,214,171,144,90,194,35,81,105,29,57,112,201,170,190,118,6,197,35,132,192,22,221,36,189,203,152,23,184,166,220,225,90,32,246,66,
16,149,79,218,164,26,202,74,67,188,126,35,151,203,139,250,138,156,161,25,135,183,22,188,71,16,94,154,229,122,77,111,222,217,14,41,104,246,222,36,196,160,163,245,67,100,0,252,191,254,219,103,74,77,228,
36,124,249,183,223,137,78,123,181,24,189,162,63,114,247,206,247,242,112,149,204,50,107,13,92,68,56,166,27,177,90,38,209,246,156,34,172,34,36,42,18,45,83,21,189,144,158,30,240,167,64,145,202,92,46,124,
75,153,235,34,16,194,142,69,139,81,95,188,13,113,226,156,163,188,156,249,250,251,23,29,149,167,130,255,245,221,19,165,233,44,216,157,39,221,213,181,4,107,98,190,20,134,120,96,152,6,44,85,85,222,57,97,
107,81,243,118,107,112,157,117,40,226,3,167,209,99,76,212,15,75,211,208,155,219,204,131,139,188,63,157,24,199,137,115,94,160,53,134,135,200,211,83,96,201,242,211,24,65,178,232,169,243,22,4,179,44,12,83,
192,71,131,127,60,14,10,112,171,149,240,116,228,26,81,125,186,17,150,4,199,56,16,166,62,157,204,153,195,52,114,152,134,254,83,129,157,255,139,174,117,173,249,137,108,176,46,137,107,73,186,229,26,99,215,
19,1,103,193,219,134,155,34,15,211,9,111,235,79,60,194,186,237,245,250,84,51,122,207,250,245,145,105,212,45,191,191,190,156,187,184,78,88,94,94,88,230,43,65,207,114,88,19,151,203,74,156,6,140,243,172,
69,136,83,196,79,142,145,64,162,242,18,132,90,11,13,48,221,233,85,93,99,173,133,132,112,25,193,212,153,227,82,96,17,174,47,23,90,202,76,121,100,77,21,147,211,126,134,27,99,246,194,40,6,37,32,228,148,56,
127,254,11,167,56,145,100,198,207,105,230,60,39,130,13,252,126,89,73,18,24,79,71,165,139,186,202,146,19,174,56,90,106,196,16,57,185,35,203,21,202,249,130,115,134,37,223,241,12,211,164,80,128,49,6,198,
35,180,67,227,67,151,232,102,17,4,225,241,253,211,206,168,120,17,81,202,63,111,242,195,66,79,95,201,90,91,168,194,21,242,188,144,178,224,79,159,126,209,233,33,240,84,254,136,180,202,49,30,177,78,75,77,
151,221,79,107,217,208,31,133,77,54,123,178,113,175,212,172,181,4,28,129,176,55,175,107,157,25,163,101,196,98,142,111,48,189,41,119,78,241,116,231,173,116,123,144,181,74,209,187,205,11,143,211,19,239,
98,198,118,243,182,151,199,129,150,33,181,74,57,234,104,51,133,190,114,107,14,130,237,208,204,93,237,172,138,234,13,189,192,246,252,176,175,120,243,182,31,235,139,176,237,76,182,84,112,158,224,12,97,138,
221,163,87,118,150,68,237,248,61,231,29,82,132,16,60,167,135,136,155,53,167,227,122,77,248,91,22,76,51,253,95,108,48,206,80,107,37,20,29,249,99,2,194,27,130,179,180,123,85,85,43,227,168,223,138,174,188,
20,125,90,223,216,204,92,232,232,255,218,176,98,118,60,218,70,250,200,69,118,104,81,202,25,169,119,159,126,165,112,62,39,242,229,59,37,137,250,56,150,111,175,186,181,172,21,206,115,223,232,66,48,154,12,
120,179,63,119,20,244,159,218,90,168,52,110,243,143,159,216,85,107,74,123,220,219,6,172,221,162,49,182,93,73,46,178,83,235,36,53,166,62,22,147,62,198,141,222,255,148,130,242,250,229,43,34,133,52,39,60,
151,5,73,133,121,89,248,242,231,191,238,63,79,28,251,191,208,251,157,233,190,145,235,182,118,70,178,208,228,199,238,201,7,48,85,47,143,170,250,40,74,214,27,211,70,223,99,139,164,199,176,212,157,15,184,
54,149,3,235,68,51,51,111,19,123,107,240,62,144,175,51,37,37,117,157,61,97,85,22,32,224,37,43,98,61,45,26,91,232,44,199,224,21,196,221,191,181,183,25,51,74,167,89,52,205,111,106,93,121,109,104,98,118,
15,105,78,139,102,211,153,168,220,182,92,126,34,137,182,102,89,164,238,183,220,227,99,188,67,9,188,103,89,19,238,241,145,36,139,238,56,38,31,105,62,170,32,255,211,71,152,28,83,73,106,158,183,150,81,216,
35,216,182,221,134,119,90,196,167,82,144,228,247,35,105,123,219,173,53,221,152,98,121,126,249,206,241,56,241,216,41,184,138,42,91,247,254,112,59,17,118,166,10,58,143,206,185,176,56,135,181,21,235,132,
41,170,85,211,175,69,77,82,226,2,25,195,124,153,17,169,216,81,75,186,69,10,193,197,29,194,18,162,154,74,148,115,210,24,226,105,239,229,54,58,191,119,142,208,153,167,255,248,233,255,212,14,91,4,107,42,
143,227,145,209,46,24,223,152,14,3,107,78,250,1,59,90,245,237,109,153,83,161,212,153,25,8,14,198,83,196,243,244,128,113,66,244,150,71,126,225,184,102,164,22,92,55,65,57,107,254,211,174,89,61,157,66,53,
142,91,89,239,82,5,209,129,135,201,134,128,54,167,179,168,8,111,89,23,146,172,93,126,227,20,223,144,18,130,232,244,71,50,182,90,50,170,201,208,139,166,146,10,204,64,109,70,167,244,215,73,79,5,227,96,113,
208,162,197,100,175,154,137,36,36,238,207,173,123,179,238,10,39,85,238,181,30,230,184,179,171,68,186,151,19,76,130,235,186,40,44,220,69,90,105,248,24,137,147,199,58,219,89,199,22,194,189,163,177,189,39,
116,61,241,114,154,70,154,92,53,217,85,4,47,115,38,147,176,181,241,253,251,25,164,18,76,83,83,116,174,196,113,234,238,196,134,117,119,76,250,62,236,243,96,77,175,180,186,80,100,79,15,12,176,190,206,140,
131,198,108,185,158,95,215,90,99,73,243,79,73,42,27,62,160,54,61,234,74,210,21,110,106,149,151,151,11,33,68,168,21,47,95,207,84,41,172,178,112,254,151,223,72,40,115,56,244,150,252,112,124,124,35,59,232,
218,158,174,248,51,198,104,65,212,143,180,205,8,88,54,97,94,112,124,252,116,36,56,187,143,8,156,55,138,246,165,18,131,163,188,25,164,52,169,148,205,239,36,122,60,122,103,136,214,109,156,59,252,99,46,164,
166,250,242,83,151,204,88,17,42,134,66,195,109,130,250,170,161,76,255,49,54,75,156,48,196,251,145,117,247,207,153,238,87,82,83,234,178,166,61,252,116,163,29,88,107,137,198,237,59,191,146,255,179,54,35,
30,34,215,175,191,51,197,136,139,1,255,237,246,210,97,198,194,237,199,247,93,136,228,250,230,232,181,62,255,244,13,110,117,234,118,68,229,96,153,123,90,218,118,171,89,103,246,250,193,187,74,217,52,21,
206,81,163,215,15,188,168,79,212,116,2,186,20,161,202,207,185,94,214,88,106,91,144,203,153,197,57,130,137,248,135,79,143,61,155,182,194,235,47,80,51,17,75,236,109,107,152,2,67,95,180,220,174,55,125,169,
182,172,142,121,33,126,120,212,1,161,168,220,113,28,52,27,55,229,220,19,92,103,124,8,4,175,48,240,109,207,231,173,198,102,189,188,94,126,254,213,234,189,88,218,206,164,121,62,169,248,14,240,121,58,224,
68,16,26,243,147,98,160,230,94,57,73,63,29,198,206,80,203,71,247,179,135,126,58,50,245,217,153,115,19,18,42,47,155,161,218,5,108,48,12,239,126,33,160,224,217,201,7,74,206,188,118,201,204,247,121,225,241,
225,151,78,21,189,19,17,182,64,168,92,212,218,214,130,238,168,115,174,248,113,122,210,209,84,109,12,125,163,211,106,222,243,63,183,99,44,75,165,185,198,120,58,237,197,12,64,120,195,247,171,181,233,222,
77,228,14,3,16,129,49,18,125,228,188,20,206,47,55,93,173,77,3,143,167,19,222,69,230,44,60,159,87,141,129,131,253,130,114,38,34,82,57,103,77,90,145,102,240,130,165,86,133,80,172,40,26,207,150,187,59,209,
246,41,79,136,118,55,98,111,67,109,227,12,185,181,187,104,201,1,86,48,253,122,54,214,238,179,238,84,42,47,243,202,235,90,247,56,194,165,193,247,231,207,251,51,59,12,58,243,40,206,80,16,106,209,84,54,25,
85,217,93,1,79,89,52,217,186,85,234,60,247,32,134,173,224,134,101,214,153,90,237,181,65,238,231,227,38,114,30,162,239,17,217,58,128,174,89,58,196,91,143,189,121,94,21,66,43,96,179,240,16,245,205,119,163,
163,164,194,248,233,180,171,88,182,13,213,219,197,100,109,21,46,80,49,48,88,124,190,190,66,203,42,70,234,123,186,106,100,215,179,199,254,34,36,145,238,171,235,173,210,52,48,180,131,222,155,70,195,125,
229,77,142,115,238,137,15,37,21,194,52,112,136,195,62,222,106,201,195,52,96,68,240,147,135,172,69,255,58,27,214,222,142,153,30,107,148,69,152,251,231,242,206,226,235,203,143,158,237,85,144,151,239,59,
78,79,182,187,171,42,173,224,45,218,209,24,139,156,13,139,119,36,219,9,117,111,106,14,227,238,65,209,67,244,48,223,184,93,148,244,184,174,73,55,76,6,230,148,123,104,46,123,5,184,21,62,155,174,104,28,35,
47,191,253,134,113,10,143,243,235,109,198,72,129,42,172,207,215,77,29,167,128,105,169,4,175,132,46,21,158,233,22,200,26,203,210,15,255,114,140,187,222,125,227,178,186,234,246,64,200,243,247,46,239,106,
244,169,142,197,123,143,219,93,6,42,66,157,37,237,107,179,183,165,234,245,188,242,253,183,115,255,88,130,127,255,244,174,11,43,50,225,79,191,222,7,122,253,86,219,154,79,117,112,101,114,22,21,94,244,29,
196,217,183,61,180,87,67,32,141,114,135,115,163,37,29,47,77,49,242,238,116,210,128,190,62,51,195,59,226,163,37,46,247,29,223,174,200,10,78,93,230,93,252,47,239,158,72,85,253,167,62,199,136,180,140,136,
229,43,70,83,159,66,0,66,23,221,41,123,202,121,199,83,240,251,7,93,250,108,237,93,116,76,227,120,15,40,219,62,120,15,199,27,123,62,82,202,133,203,229,138,141,77,125,33,193,145,82,225,211,135,184,143,12,
222,154,12,183,80,178,156,33,125,120,220,60,229,248,241,116,66,36,83,167,198,227,252,235,79,103,106,107,134,44,43,110,136,123,136,72,234,231,172,61,140,28,130,99,125,153,105,206,33,155,102,176,47,208,
29,96,107,229,243,223,126,236,3,240,218,172,194,185,166,131,226,32,166,202,235,243,43,243,124,191,140,114,46,93,64,173,101,109,177,150,235,215,239,160,224,74,188,153,38,92,243,170,118,122,122,194,217,
240,198,14,9,38,95,144,214,56,151,174,21,222,212,170,210,144,92,121,122,122,234,234,219,251,149,186,99,214,139,112,250,240,241,167,146,212,245,122,34,245,46,153,211,137,56,221,41,210,177,213,189,229,18,
209,216,89,142,147,106,149,169,248,243,229,76,109,153,146,27,159,63,127,166,138,237,194,121,141,190,26,79,97,111,201,99,80,192,102,236,1,230,37,11,180,176,207,29,232,96,22,215,143,57,141,145,229,14,46,
220,186,237,90,73,181,209,48,212,102,112,65,255,153,173,42,130,106,235,106,178,52,66,244,216,110,159,48,128,255,116,58,144,68,7,114,241,195,99,239,46,182,121,153,39,137,224,227,61,150,59,165,68,186,220,
238,109,186,155,250,135,99,167,241,151,110,178,206,34,156,186,50,112,251,137,183,217,197,86,249,13,206,50,14,93,202,248,134,5,182,169,3,74,205,24,43,180,42,250,89,254,242,111,255,134,69,48,82,249,246,
151,63,239,51,177,93,119,38,3,62,120,29,110,188,153,214,148,172,97,9,210,69,106,174,27,4,53,42,238,254,120,164,219,143,93,115,44,125,148,186,131,50,0,113,142,213,57,150,49,238,77,236,6,11,55,198,34,243,
133,246,242,138,193,112,244,22,31,107,84,175,69,90,201,23,176,125,124,154,122,118,134,53,227,254,237,169,30,179,175,196,86,77,204,150,238,8,183,193,211,98,80,67,183,51,106,124,242,129,60,47,251,94,110,
83,251,81,155,234,148,151,68,194,254,212,42,109,221,243,246,199,199,104,120,254,252,59,198,27,66,176,248,95,63,254,137,117,153,201,45,81,62,188,215,167,199,73,223,136,38,16,171,241,221,91,186,100,46,44,
235,74,24,2,167,33,16,29,63,137,240,114,74,148,85,250,128,48,99,59,114,132,90,137,78,203,204,113,24,84,142,190,36,242,186,236,18,156,45,84,207,26,187,131,182,46,215,153,147,119,56,11,193,121,60,167,1,
127,138,184,37,113,122,255,142,216,67,23,170,164,61,36,87,222,76,123,98,41,24,235,223,164,96,171,170,106,59,151,79,79,26,105,168,126,252,66,28,123,168,88,199,82,91,239,169,40,167,248,112,26,105,167,105,
239,114,182,233,207,61,21,219,240,152,11,199,176,244,205,82,195,223,230,27,146,51,57,37,126,123,254,161,34,251,110,73,143,88,196,214,187,60,166,111,121,196,5,202,126,238,246,28,165,201,49,244,103,207,
58,139,235,69,208,161,83,104,222,86,95,59,129,180,9,209,71,164,39,97,147,50,244,88,174,93,18,217,26,87,113,196,120,194,181,134,39,122,109,143,196,18,199,137,56,104,36,208,219,4,181,109,168,210,218,253,
248,218,236,9,175,151,23,124,247,116,42,47,222,18,189,167,69,7,82,21,219,32,116,174,74,0,3,226,5,156,114,199,151,156,186,131,209,238,102,111,141,170,85,3,129,49,158,193,41,149,180,137,224,157,105,186,
185,143,6,27,29,153,74,22,3,101,155,186,203,78,55,74,249,254,215,111,199,156,10,68,140,162,164,107,69,106,214,132,168,237,167,53,10,160,205,162,162,38,173,75,234,142,78,15,147,174,40,55,193,136,20,33,
215,70,78,42,67,0,225,252,31,117,48,205,0,0,32,0,73,68,65,84,124,197,96,8,209,226,41,25,135,96,130,101,138,218,179,73,186,203,109,173,181,88,163,49,67,27,137,121,179,245,108,145,197,111,57,105,181,87,
118,63,137,160,133,159,176,37,91,202,148,115,142,14,187,83,103,194,214,185,148,59,112,96,28,163,102,213,149,70,90,5,255,227,124,198,214,134,33,115,254,242,101,239,118,107,119,135,15,46,144,122,2,201,38,
127,217,72,71,173,54,124,240,72,15,191,121,171,182,178,214,34,185,236,255,249,237,89,94,69,53,106,86,95,253,157,210,191,129,192,239,148,133,202,249,98,185,124,249,129,233,40,97,111,175,43,57,47,184,150,
89,190,125,99,45,115,31,104,40,138,111,121,155,170,218,135,39,155,64,73,85,211,58,202,34,6,108,140,187,18,101,203,15,247,67,216,217,105,41,184,187,248,99,3,194,53,123,223,126,246,192,212,56,248,159,146,
3,101,126,233,101,175,224,39,103,112,98,168,2,99,55,255,185,168,86,177,146,239,203,151,173,101,217,118,17,181,35,125,71,127,212,173,190,53,56,167,126,165,146,43,213,52,10,141,215,203,139,198,19,58,183,
215,33,49,90,74,207,230,144,45,206,162,223,162,206,86,140,41,251,116,40,213,198,245,252,149,146,133,232,44,126,57,62,210,198,9,227,44,254,250,223,240,125,73,189,141,240,173,189,255,220,219,183,227,222,
200,5,164,222,177,165,4,71,120,227,181,179,198,226,207,215,61,16,125,234,209,0,111,107,222,23,35,251,165,180,61,14,169,20,94,94,174,164,121,81,36,251,240,17,227,212,153,224,31,223,61,209,90,6,3,233,245,
72,73,117,111,227,91,176,122,236,168,67,82,183,69,6,136,142,113,240,251,55,191,237,215,182,76,220,92,100,183,1,61,157,134,78,32,109,84,239,123,88,94,99,73,137,75,94,9,209,171,247,75,26,180,134,239,249,
51,83,140,250,62,181,198,145,153,249,229,130,204,43,126,37,65,183,43,172,182,82,163,70,104,59,163,44,214,229,252,66,51,150,220,212,222,227,76,247,92,248,141,212,88,181,130,75,137,122,93,246,23,110,211,
176,63,61,30,85,207,185,36,102,17,108,86,151,65,243,142,66,101,180,246,63,13,24,109,52,122,81,121,199,56,58,220,242,200,101,10,44,151,25,79,169,228,90,168,34,92,207,175,128,163,13,177,59,185,225,216,51,
231,182,94,239,205,43,172,22,74,49,76,68,166,24,127,18,244,183,90,33,195,252,99,209,71,167,227,113,140,177,26,185,53,68,158,14,39,234,114,85,253,155,99,135,10,168,177,177,97,168,44,151,140,72,86,49,235,
232,240,135,232,84,114,88,132,152,43,206,25,162,8,118,214,182,126,248,15,161,232,123,120,72,119,180,212,165,116,230,176,251,233,249,220,157,141,173,169,104,164,215,19,85,180,14,110,41,147,186,232,159,
65,118,4,170,51,134,252,38,148,44,145,49,52,78,67,228,56,4,252,229,235,89,59,138,180,82,126,92,8,211,132,45,141,90,151,78,26,191,95,209,222,59,92,216,180,237,58,44,28,157,78,234,107,82,227,200,54,79,216,
148,85,199,65,213,175,213,89,14,157,208,145,69,152,95,94,153,231,133,98,85,154,190,173,209,222,22,62,49,6,170,129,249,203,119,198,73,131,251,252,203,245,69,209,11,169,114,190,205,204,146,123,98,170,182,
64,62,252,220,143,109,186,180,237,121,51,114,167,138,106,188,133,236,143,68,109,109,199,242,189,61,95,183,225,117,17,225,225,225,176,59,19,84,96,90,119,162,157,54,194,153,151,151,11,151,139,174,123,253,
227,227,35,182,89,42,137,203,199,199,253,214,73,57,51,78,35,66,218,253,246,41,37,214,55,1,56,247,124,241,182,139,58,106,207,71,220,188,206,247,187,174,238,25,7,58,169,29,120,55,157,104,115,34,58,168,86,
207,230,218,76,15,237,181,12,163,227,117,206,208,231,33,115,73,248,211,24,149,54,35,158,63,124,120,80,14,96,174,204,179,234,201,174,47,202,62,219,58,0,255,70,12,167,19,161,244,147,71,84,242,27,13,125,
63,211,157,49,248,168,225,235,193,187,189,85,202,34,112,124,228,214,109,109,113,26,247,127,199,38,83,152,166,128,249,49,34,107,38,248,9,95,72,164,150,88,211,194,223,46,207,251,7,171,86,139,151,199,79,
135,125,153,157,107,214,136,138,168,65,145,131,179,164,51,251,226,219,88,191,247,101,155,140,43,122,141,232,20,224,150,149,11,180,51,134,129,218,151,50,199,14,221,216,30,171,232,149,17,235,226,129,233,
241,164,67,247,10,126,168,35,222,140,76,113,98,56,253,97,191,62,205,155,211,224,45,36,217,57,211,87,0,90,184,95,143,203,190,180,218,108,108,177,196,221,153,89,185,115,92,55,180,164,188,89,219,26,235,48,
22,140,11,248,232,145,85,221,103,210,148,125,133,11,56,55,129,90,244,241,76,239,116,131,143,96,46,103,22,96,145,78,218,88,19,183,235,188,23,62,251,210,58,27,66,212,194,126,140,182,167,184,107,154,251,
54,139,219,10,154,232,6,85,198,58,93,3,152,81,97,45,49,122,213,169,197,55,163,170,232,153,198,145,161,7,144,180,86,57,30,79,148,249,189,174,151,179,224,127,91,111,253,222,21,190,93,190,232,145,212,57,
47,217,8,241,15,35,146,179,54,140,105,133,172,154,127,37,37,88,62,206,2,213,236,103,168,181,138,85,223,50,202,183,111,244,174,2,208,110,226,48,141,28,142,19,183,148,200,246,190,253,223,208,126,182,53,
150,69,157,191,57,23,146,116,225,221,113,254,78,150,140,205,153,195,247,223,52,36,108,67,93,215,130,88,104,57,67,42,216,238,142,137,62,236,117,195,191,47,7,234,238,0,115,56,231,119,212,191,51,166,187,
192,180,159,243,78,51,54,102,209,201,228,109,94,180,233,20,13,234,11,13,242,114,159,179,197,157,30,38,68,167,205,183,159,178,103,156,5,140,39,212,145,154,10,169,172,56,42,181,194,107,78,12,173,50,232,
160,72,135,215,217,32,87,125,72,63,252,233,87,45,188,147,182,251,173,111,145,36,235,211,27,156,163,21,81,231,120,220,178,98,244,91,211,7,85,118,215,248,106,44,243,188,236,145,111,198,89,214,239,153,243,
95,63,119,91,16,120,251,244,43,233,168,248,255,106,51,164,140,201,43,209,109,153,48,119,243,169,235,189,92,120,115,93,191,235,89,206,91,221,220,106,101,153,117,135,183,246,172,141,157,69,129,142,110,79,
113,234,89,162,3,11,115,199,247,222,215,108,67,55,177,6,239,168,77,56,241,65,73,79,2,94,158,222,227,168,24,7,87,10,151,174,27,126,53,58,20,140,162,83,249,33,70,157,190,199,128,25,253,46,190,127,117,250,
179,121,4,107,154,62,78,33,225,38,152,86,152,107,196,77,14,75,38,70,139,181,158,156,32,249,17,23,31,113,225,136,91,146,122,69,128,240,120,47,89,215,148,245,100,88,132,143,143,19,208,148,221,154,178,126,
195,163,51,42,241,230,222,103,45,254,68,42,133,107,22,214,52,107,204,96,138,123,219,243,116,189,128,228,254,159,193,69,56,184,62,185,153,70,28,17,156,130,95,150,148,24,71,71,60,12,24,23,89,200,74,119,
24,3,131,27,59,235,82,85,134,195,56,49,245,235,254,181,158,89,66,224,232,12,190,46,47,200,154,53,103,241,242,5,106,195,112,87,53,37,211,35,137,201,200,198,164,36,83,210,66,1,94,151,31,63,183,56,205,177,
122,71,108,58,181,207,107,98,28,34,227,241,137,148,179,134,229,164,164,233,130,97,195,243,24,229,199,27,203,234,116,171,159,55,82,141,179,220,250,146,254,234,192,175,223,62,179,204,179,170,175,127,251,
151,55,231,173,154,65,126,169,110,207,79,222,242,192,71,171,103,103,107,149,31,100,61,230,156,5,235,72,5,100,73,188,244,43,45,70,75,90,230,159,84,127,244,168,218,237,121,223,110,196,233,48,246,27,83,245,
238,107,159,191,189,124,249,78,41,10,203,247,131,203,56,95,169,173,224,208,55,180,165,202,40,58,231,58,180,251,0,229,58,171,66,138,24,246,202,42,62,253,129,16,60,65,148,40,222,106,213,97,160,232,184,54,
217,218,107,5,221,109,76,147,198,204,58,167,245,174,111,80,82,198,137,99,180,173,55,178,77,161,224,169,224,166,9,183,174,164,235,170,218,203,47,127,59,67,203,24,224,199,249,74,109,133,177,107,24,28,240,
219,252,99,159,23,172,107,2,167,247,252,166,138,58,201,216,119,114,93,93,189,161,39,157,233,128,129,27,164,130,119,138,255,154,111,169,39,249,192,56,56,94,46,250,80,140,99,36,245,116,248,109,128,163,121,
183,11,183,223,254,166,145,137,22,252,211,63,254,55,108,237,25,169,70,57,172,250,245,52,61,19,167,163,78,231,157,195,213,188,203,100,83,209,86,63,46,247,218,216,177,77,32,163,182,253,88,166,255,250,145,
219,101,101,77,149,224,34,214,53,150,101,230,124,121,102,158,175,156,38,221,3,198,88,241,38,107,57,106,43,227,48,48,196,200,235,124,37,215,133,232,44,33,26,124,27,78,58,27,64,104,143,191,18,105,132,224,
168,203,194,122,190,240,75,28,122,146,175,254,1,82,27,243,90,153,151,85,203,200,54,239,180,142,104,213,94,107,100,129,164,134,235,171,120,66,140,132,33,116,143,102,101,58,77,28,223,71,156,201,186,36,79,
119,19,225,6,79,158,166,129,105,138,140,105,226,16,110,188,59,13,186,186,77,243,5,19,84,44,154,202,202,37,229,222,178,56,102,231,73,117,237,115,137,200,240,126,100,93,86,150,148,56,156,34,214,88,14,140,
140,99,220,67,242,182,236,153,86,213,74,97,107,37,116,82,152,248,170,77,65,213,133,99,13,83,95,215,150,253,17,75,214,179,166,196,203,185,16,103,21,146,126,121,17,206,105,229,56,120,188,107,9,174,154,11,
87,127,252,77,203,59,180,86,152,128,82,103,210,12,75,47,186,215,30,29,56,140,145,211,97,226,117,221,246,199,238,39,4,212,246,220,47,22,178,237,114,133,102,193,36,114,206,92,214,181,15,204,39,98,8,96,157,
86,123,206,48,28,198,62,226,45,224,29,211,227,3,227,228,53,121,138,151,239,72,211,206,180,157,191,144,103,101,152,180,168,117,177,164,235,62,33,87,243,170,250,58,218,12,235,213,51,55,199,101,171,180,118,
41,162,236,5,252,227,199,15,10,138,75,5,231,12,167,211,145,218,227,5,0,230,226,240,73,186,12,71,186,45,190,40,18,176,53,162,241,252,237,235,43,135,208,215,94,185,100,210,178,80,83,226,235,151,175,251,
190,215,187,74,78,122,200,223,174,243,79,25,180,85,244,57,207,84,14,143,143,154,216,147,50,185,179,125,182,103,222,56,195,242,253,76,74,153,203,60,235,69,242,120,210,17,213,6,193,207,170,2,140,33,112,
60,233,138,44,173,51,198,24,142,227,196,37,21,190,127,254,204,183,37,35,205,226,197,68,220,49,50,29,133,95,255,238,31,136,49,112,124,136,154,11,179,36,254,246,237,25,198,73,105,29,221,3,183,149,139,49,
120,158,166,137,101,74,189,1,109,187,240,121,203,178,173,115,131,41,242,105,58,18,70,93,76,2,60,185,149,148,51,103,119,37,165,134,113,153,88,116,78,33,47,51,84,152,199,27,47,215,153,31,255,250,191,53,
213,253,16,213,98,73,21,176,14,105,142,165,84,184,101,150,245,202,183,231,51,175,235,194,241,48,241,254,253,211,30,144,62,207,43,115,206,92,37,33,139,62,211,155,42,251,237,55,12,5,174,157,12,18,61,41,
47,44,179,98,77,182,209,192,135,99,100,248,112,234,225,79,96,108,101,252,199,168,191,224,162,85,223,223,135,5,104,156,78,19,62,120,195,186,86,174,243,202,249,242,162,219,42,55,18,135,192,199,95,78,28,
102,207,24,7,20,94,167,85,213,216,121,108,214,88,134,102,254,147,192,99,167,55,183,138,21,126,154,124,158,175,87,172,248,222,200,6,85,173,118,73,249,109,190,106,96,83,105,92,47,51,151,121,161,117,47,18,
162,16,70,255,252,251,239,100,209,60,21,153,53,40,225,117,185,97,186,118,221,132,200,249,122,227,218,185,217,198,90,14,211,176,239,212,210,181,237,136,233,183,8,167,109,99,52,139,34,71,108,124,187,131,
86,150,149,147,204,105,60,50,207,210,183,203,58,252,174,87,97,93,51,115,106,234,90,55,145,240,224,16,28,254,251,249,181,175,150,51,223,126,92,246,111,163,117,103,109,78,231,159,130,28,17,120,126,190,145,
202,89,103,11,115,226,116,156,238,47,76,82,37,212,166,145,120,93,151,61,43,119,195,72,74,107,187,212,235,122,190,232,35,54,207,212,164,231,174,217,24,219,82,24,7,207,203,247,51,118,132,186,24,252,127,
253,199,127,32,80,49,166,241,209,221,116,212,68,222,127,230,212,119,202,155,112,99,203,30,223,246,201,233,182,232,163,209,33,178,185,200,221,164,93,132,143,70,117,238,154,218,115,31,186,20,17,218,82,59,
204,69,139,165,24,189,26,17,189,235,66,45,203,58,47,188,206,51,117,174,68,59,106,77,98,68,15,246,109,33,83,186,87,121,51,166,182,174,54,213,186,183,99,255,59,41,119,99,172,110,65,55,219,47,100,173,193,
212,198,229,118,219,189,70,225,52,225,195,3,227,48,16,131,87,130,157,247,234,32,232,169,127,182,83,19,134,41,48,70,207,117,89,41,255,240,136,247,134,146,192,31,199,137,52,207,72,213,115,118,58,6,96,220,
7,40,186,187,184,31,101,219,203,165,225,144,229,167,108,207,246,70,156,177,77,36,79,28,250,154,235,205,243,251,246,229,236,184,190,235,117,225,114,185,170,143,52,232,92,122,216,52,66,151,23,78,143,35,
158,136,255,246,252,66,74,51,109,89,248,242,253,43,135,227,68,140,161,131,49,102,14,211,113,223,177,9,149,101,21,74,215,172,183,90,113,99,216,37,50,91,17,51,198,216,167,71,218,155,57,234,110,183,216,162,
5,84,238,149,105,89,168,221,199,127,156,70,234,84,105,52,144,202,58,39,12,150,31,231,27,63,206,23,253,192,231,151,51,210,18,164,204,203,229,70,74,133,254,107,247,44,153,183,124,64,33,111,58,9,233,233,
216,65,183,67,27,62,207,58,179,79,216,223,154,71,214,53,245,241,173,106,136,117,207,177,48,118,201,142,113,134,216,199,95,27,14,45,23,33,184,166,74,109,73,200,109,193,63,61,30,17,25,0,97,125,126,216,153,
129,206,117,9,205,112,64,68,73,71,197,203,46,86,218,46,135,236,116,105,88,107,99,12,110,199,250,99,12,88,203,33,250,30,48,29,246,33,223,48,14,180,90,24,86,207,122,89,169,85,7,125,235,109,85,31,191,219,
30,151,70,67,85,89,49,120,46,146,241,135,113,32,139,65,82,235,76,136,188,127,171,166,25,150,117,221,31,129,24,117,117,181,161,169,139,8,115,43,123,246,242,182,143,219,164,50,206,25,206,179,222,148,199,
195,180,103,127,233,185,221,152,114,230,44,231,110,87,107,136,85,183,121,145,123,100,97,173,234,173,30,99,224,253,233,136,127,93,4,201,106,79,51,214,32,9,174,207,122,246,158,142,221,17,43,26,213,189,94,
19,233,135,74,204,215,85,219,246,58,141,234,242,30,163,114,215,232,127,124,85,62,196,20,143,248,230,200,55,33,35,88,35,164,177,82,73,72,206,44,57,211,218,166,196,178,52,116,20,54,140,94,17,83,73,56,60,
141,212,212,152,203,130,95,211,66,196,48,4,29,67,153,109,53,219,111,174,220,39,63,219,42,118,24,34,113,208,48,39,227,44,217,40,203,53,93,23,100,201,187,92,119,155,120,70,113,136,145,157,131,162,50,19,
13,75,95,114,222,97,21,58,38,168,80,161,184,66,74,134,101,41,120,107,152,207,87,92,8,58,189,252,211,211,59,76,48,96,44,237,249,145,197,69,30,167,73,229,140,168,75,38,6,175,182,6,99,25,199,72,232,30,161,
107,135,94,189,253,144,27,53,97,123,73,141,51,52,233,140,19,231,187,75,204,18,157,227,216,255,61,236,33,103,61,73,184,159,32,171,235,179,228,56,18,92,32,28,192,103,145,158,39,151,184,188,44,12,163,227,
221,244,168,178,110,209,84,119,173,19,148,34,190,44,66,118,138,34,59,30,79,60,58,75,216,172,239,93,5,187,89,38,91,171,76,211,200,34,249,205,96,124,230,218,183,173,14,125,49,189,239,136,29,111,244,134,
83,43,142,106,237,251,126,111,37,51,172,22,159,82,34,167,133,52,39,190,126,125,230,216,207,225,13,77,186,57,189,198,49,238,5,207,150,7,122,58,28,184,94,243,62,245,217,40,95,247,235,187,241,114,249,214,
215,208,94,3,163,36,65,18,28,150,97,84,103,76,140,219,94,163,66,131,84,147,230,224,14,158,211,224,112,215,17,145,140,195,226,115,206,148,156,117,184,223,26,47,243,140,91,86,77,140,176,154,19,195,70,152,
50,129,117,77,170,99,79,153,16,95,217,126,2,223,207,208,56,108,156,225,158,226,94,26,97,48,248,33,96,77,237,226,17,149,205,44,201,33,85,255,120,107,233,91,166,70,154,51,34,26,159,53,77,145,203,237,170,
115,59,235,213,121,62,28,14,180,90,112,222,113,89,147,134,211,120,176,205,236,101,226,50,207,156,187,9,165,26,112,83,196,56,71,186,46,90,197,57,139,29,116,127,156,23,149,15,148,34,28,188,161,54,75,89,
211,254,24,196,168,14,114,233,40,118,75,163,174,149,38,26,244,75,149,14,121,113,188,190,94,184,92,102,229,181,12,14,239,92,96,28,61,149,200,244,120,32,148,3,135,135,3,199,81,231,190,29,186,136,20,217,
93,0,209,7,221,203,173,137,211,167,199,221,231,153,82,225,122,187,33,86,120,56,28,56,30,14,68,170,42,169,242,74,43,21,23,109,191,233,42,115,73,187,151,174,144,17,26,113,240,4,103,89,230,68,136,134,163,
57,225,243,181,139,244,26,254,244,225,35,22,125,86,143,199,7,29,184,133,30,242,216,121,129,169,232,183,63,244,88,204,113,136,120,17,213,64,56,120,56,76,24,107,57,159,47,59,182,186,182,202,195,97,218,215,
120,54,116,20,123,211,89,179,53,149,101,93,177,147,127,35,120,214,190,208,189,73,186,189,189,232,251,181,204,51,89,50,126,78,137,41,6,124,28,24,166,73,211,164,150,210,165,139,14,55,141,208,39,62,169,222,
113,55,21,75,161,33,198,147,208,151,52,161,37,99,69,183,153,109,109,29,160,88,145,85,237,102,52,56,30,28,167,227,68,156,2,170,181,82,148,25,42,197,192,25,215,137,52,16,204,136,147,196,211,188,146,83,198,
187,16,177,81,181,106,199,199,7,29,163,166,4,198,98,134,129,69,68,65,155,193,17,172,70,91,224,2,165,102,114,133,191,254,120,37,222,148,5,168,211,77,118,74,185,119,142,227,120,84,89,142,209,117,111,18,
225,219,34,184,31,207,72,173,156,226,64,45,149,146,19,82,178,154,8,107,165,246,189,222,16,35,243,243,15,232,191,180,127,60,169,157,39,87,16,28,46,142,248,190,36,76,5,156,215,244,234,173,190,253,137,238,
44,194,211,187,143,58,54,141,129,119,69,246,176,156,117,73,248,120,159,41,7,239,80,254,81,234,101,102,99,45,137,52,39,76,52,196,225,136,177,250,223,235,36,94,201,121,214,88,66,176,76,135,216,7,41,85,104,
82,148,249,158,85,128,161,56,233,126,14,23,29,104,182,84,145,6,206,120,134,105,98,58,157,168,82,185,37,233,255,155,248,19,155,120,112,142,113,28,64,52,77,170,22,61,99,131,143,68,15,135,193,83,105,180,
164,183,161,94,111,186,139,83,98,72,186,167,97,186,129,232,2,38,56,124,107,130,148,74,173,58,111,200,89,118,233,226,154,18,121,213,233,252,113,26,123,233,231,112,182,237,18,4,197,52,9,148,180,255,145,
202,236,105,72,190,49,207,25,89,19,33,42,135,48,149,66,90,103,206,175,170,2,84,38,214,222,126,244,242,22,12,22,23,53,101,97,185,205,204,233,6,55,240,215,249,210,237,233,138,119,178,198,50,142,147,110,
68,17,136,39,5,12,116,41,205,214,53,232,102,180,32,253,27,217,78,150,186,237,234,168,228,24,88,111,26,1,126,156,2,99,176,92,229,202,50,95,184,93,110,228,36,196,232,84,79,44,21,105,5,117,76,56,198,168,
23,145,52,225,242,124,86,235,123,19,252,47,239,62,104,13,144,103,230,135,19,46,56,222,61,170,245,247,199,203,133,214,17,121,222,232,84,210,181,138,169,22,79,83,255,41,86,145,11,185,135,81,239,74,43,193,
225,24,188,209,107,86,178,166,22,103,93,90,190,123,56,50,78,177,159,34,80,214,162,236,121,185,11,61,164,101,30,14,71,252,211,180,231,150,251,92,26,69,50,37,233,180,48,96,201,115,234,96,128,194,186,150,
125,132,170,215,175,74,23,91,211,230,20,132,167,167,147,42,87,65,217,149,52,188,159,104,82,241,163,83,230,74,240,72,73,92,74,197,25,157,177,141,193,33,65,37,55,109,20,226,224,126,82,32,46,57,147,82,229,
118,94,73,157,54,234,215,249,170,207,160,133,97,112,125,207,44,72,73,148,146,118,156,100,248,15,209,196,155,32,105,93,231,221,180,87,107,235,246,156,166,71,191,128,248,198,229,252,66,146,66,232,114,69,
139,97,189,37,206,203,74,28,53,234,162,85,33,173,203,253,159,237,244,67,63,29,31,113,114,32,205,133,210,42,254,245,122,193,58,112,214,177,222,22,138,115,187,145,47,231,76,206,154,27,42,162,139,109,121,
35,157,209,28,13,69,248,110,31,218,118,227,137,53,250,194,172,111,58,105,239,204,27,237,38,28,205,192,82,86,32,35,85,183,85,187,91,161,243,122,94,46,55,100,46,221,109,38,248,91,90,49,82,65,132,47,95,159,
137,161,39,255,117,108,67,182,5,178,176,164,182,75,191,204,38,182,3,150,100,223,184,10,234,158,85,75,213,156,143,57,173,248,94,117,89,103,153,47,11,73,10,209,121,134,41,116,35,183,46,19,55,9,111,163,225,
140,163,82,185,205,23,242,114,69,154,62,219,254,52,29,84,194,37,69,211,128,107,211,28,91,164,119,13,101,215,10,55,81,131,246,56,104,86,134,136,110,124,118,173,131,189,123,225,151,117,161,212,198,187,211,
73,125,27,183,85,115,161,115,162,44,133,165,93,169,95,27,135,119,7,64,127,181,109,238,102,148,107,175,32,207,33,210,110,5,145,204,146,5,127,58,142,148,168,91,243,79,159,158,112,21,74,210,158,171,20,129,
172,227,210,105,26,247,174,121,140,81,247,20,183,153,219,124,213,29,5,224,189,33,184,128,179,112,200,10,79,188,92,102,150,180,128,181,68,167,185,116,199,24,21,215,222,212,30,161,6,38,16,123,199,247,237,
154,226,156,73,209,224,146,211,24,250,146,51,181,233,215,115,140,234,16,200,65,246,238,226,118,77,58,23,136,97,55,228,109,174,151,208,117,237,161,187,98,141,81,102,154,247,142,169,191,172,15,199,105,151,
48,210,224,50,171,191,46,186,192,116,28,247,198,83,74,225,58,223,40,93,91,164,31,182,187,36,251,61,97,157,195,235,228,220,232,66,58,21,150,174,238,243,206,49,58,207,225,195,164,5,252,146,184,205,43,175,
151,219,46,5,147,218,56,29,39,172,179,72,119,13,252,236,181,55,196,41,116,17,71,163,229,76,240,125,238,236,116,129,89,115,143,98,50,134,209,7,220,48,118,201,152,195,26,168,45,243,250,108,88,102,165,44,
248,182,244,177,105,75,252,237,247,103,78,199,17,239,52,220,46,60,156,88,110,58,160,75,165,220,237,56,111,116,106,52,253,176,89,244,25,159,247,160,43,253,165,91,133,101,213,173,208,56,168,169,123,176,
14,89,51,231,215,23,173,39,169,253,23,168,90,41,246,206,6,42,67,81,32,193,130,168,99,113,152,162,134,46,173,74,47,184,94,111,52,233,201,238,189,3,46,111,180,233,27,242,73,71,164,133,81,28,41,37,150,219,
178,47,21,189,22,3,24,11,191,124,248,72,149,198,154,50,243,69,88,156,14,109,164,231,61,115,109,29,3,161,88,117,183,139,251,245,69,158,115,101,189,105,246,46,84,188,179,210,103,5,142,135,41,98,173,86,106,
147,76,28,142,19,206,109,44,148,188,195,93,54,95,192,56,90,205,230,106,35,237,221,73,11,22,235,186,91,54,211,170,176,72,211,23,117,236,75,23,69,12,145,122,10,138,171,250,248,89,61,141,251,120,87,245,153,
105,205,111,80,17,61,213,253,118,61,3,86,163,183,201,212,46,110,139,193,247,208,59,56,78,145,71,163,113,1,27,223,100,236,173,60,57,99,141,7,11,222,232,53,92,123,246,193,34,133,180,102,142,67,192,133,113,
63,242,148,26,218,16,105,76,147,206,218,106,109,152,85,149,49,193,155,221,128,232,59,132,54,76,3,222,128,127,121,185,96,188,131,90,121,254,241,74,233,109,189,239,208,65,169,89,195,60,142,19,190,251,140,
215,53,49,239,190,125,253,67,210,170,130,78,65,193,198,203,58,35,89,56,157,142,220,130,198,190,166,148,40,185,97,173,158,177,82,11,159,215,153,97,19,150,246,122,101,218,230,31,34,228,108,105,75,162,166,
68,173,130,255,244,241,19,214,247,216,236,243,159,16,52,134,219,196,190,240,78,105,39,207,104,156,96,37,141,177,115,45,87,222,61,62,168,250,186,35,246,178,168,215,206,88,205,151,249,240,254,65,171,181,
218,168,109,234,205,173,78,122,140,129,203,143,51,161,71,104,44,243,178,39,70,212,46,95,127,56,78,148,80,185,166,196,178,8,222,42,63,17,71,34,198,129,214,99,45,198,199,73,131,203,237,137,146,21,202,189,
59,188,122,50,182,12,26,179,201,4,199,238,235,108,189,110,189,46,11,34,133,243,143,215,110,55,235,18,50,111,251,115,172,23,196,244,48,96,173,62,122,222,187,125,77,161,215,191,227,211,233,145,116,25,152,
165,112,73,11,126,62,207,212,232,72,245,202,151,47,63,168,70,145,57,15,162,84,185,205,242,254,54,85,103,51,92,199,16,184,94,103,242,218,9,28,181,246,103,185,107,83,172,225,195,135,119,106,64,173,186,212,
105,85,88,211,122,79,37,142,170,251,212,103,94,151,232,165,232,163,17,163,167,126,19,210,203,133,132,190,196,254,197,100,197,53,89,199,92,11,183,121,101,188,37,228,154,123,113,179,16,98,80,83,211,166,
216,51,42,52,178,206,50,224,117,110,182,65,48,164,116,239,144,232,13,214,90,63,167,91,39,228,154,55,140,53,136,214,146,250,151,67,83,192,178,49,150,180,10,235,37,147,198,70,201,75,223,145,52,252,227,211,
99,223,16,53,202,47,202,151,56,248,72,232,170,213,121,94,246,111,118,195,41,172,41,33,89,119,200,86,160,230,202,218,185,219,53,108,249,137,173,127,48,77,228,57,69,207,116,140,76,195,136,52,149,148,47,
37,51,207,115,63,6,27,129,158,55,254,166,67,143,33,50,13,39,162,179,221,80,59,70,114,94,52,241,216,57,38,23,136,163,46,14,219,214,84,202,207,184,156,218,5,28,44,9,223,52,253,119,205,26,44,29,163,170,90,
157,183,72,202,88,204,110,69,59,244,229,163,180,70,246,130,47,218,235,169,53,83,107,226,183,33,214,0,183,75,194,215,66,60,117,6,192,245,250,130,36,13,203,189,62,95,144,49,226,146,221,179,8,156,115,28,
14,170,26,105,93,241,52,14,17,235,32,45,153,188,102,214,94,120,43,77,215,65,71,64,134,227,192,243,247,11,136,122,76,151,117,217,71,96,62,56,69,171,199,168,55,161,115,164,37,179,148,117,255,162,140,181,
248,193,227,214,204,124,75,92,110,51,62,134,72,2,92,105,204,253,5,200,75,161,37,181,69,86,175,55,81,226,94,118,218,78,82,76,115,198,99,149,212,97,44,214,192,220,215,91,134,202,24,3,167,211,81,33,244,235,
66,153,117,77,187,229,120,189,58,163,179,135,182,173,217,100,255,195,253,224,137,38,32,86,31,159,36,133,84,50,254,52,77,200,20,85,26,251,254,65,1,175,115,162,4,136,198,224,167,73,183,67,214,226,198,168,
81,178,89,255,165,15,15,71,90,218,62,128,182,74,69,4,137,13,143,70,101,142,209,179,0,71,105,240,48,112,152,34,33,122,82,41,204,75,98,250,52,237,133,78,126,131,144,180,86,137,186,235,146,40,249,218,83,
44,3,254,114,157,177,182,225,140,86,109,174,103,38,90,83,137,113,212,15,217,255,33,166,103,33,14,131,191,175,108,83,125,83,172,104,72,136,243,10,182,23,96,153,147,66,151,59,230,215,90,211,97,90,194,146,
86,46,223,87,188,11,132,168,10,23,23,28,225,141,227,134,49,194,26,25,98,227,129,136,159,47,55,106,15,27,123,189,92,241,88,82,94,246,102,145,198,221,219,145,50,181,22,30,79,7,134,232,185,93,86,202,146,
89,82,97,78,90,229,105,54,135,35,167,196,58,47,136,180,187,17,86,148,176,91,123,3,171,213,152,48,140,158,88,28,139,11,119,135,121,63,234,140,53,188,62,255,32,118,86,128,55,123,52,160,161,26,101,234,140,
211,19,41,21,206,139,166,79,238,238,65,167,29,197,92,132,249,60,107,237,208,26,110,244,60,61,126,196,58,93,21,164,37,65,12,28,166,145,219,122,35,47,133,220,26,118,112,120,27,177,181,50,184,200,56,13,125,
126,86,119,112,162,18,194,232,97,167,14,103,28,152,184,187,200,253,120,26,250,79,219,88,250,56,106,235,221,78,167,190,254,170,109,95,36,166,156,187,46,211,80,146,16,135,8,253,133,139,49,16,221,136,76,
218,250,4,103,121,153,35,53,229,253,23,19,169,144,101,159,7,187,168,208,251,45,148,100,236,129,74,206,216,157,180,207,49,50,70,221,158,122,149,98,21,228,150,248,246,237,249,39,40,156,116,37,149,233,158,
227,214,223,226,150,43,169,23,229,215,37,245,246,190,117,177,157,46,94,230,69,165,99,113,116,88,177,61,145,214,232,251,208,169,51,22,173,125,99,31,212,152,62,183,144,62,54,216,50,119,229,122,214,173,84,
174,248,16,3,118,17,156,143,28,14,211,174,117,223,138,246,173,216,217,44,237,219,208,36,205,89,255,179,97,111,205,227,27,126,118,90,34,165,36,94,174,42,133,156,70,45,87,27,149,58,151,253,76,247,193,49,
13,35,211,113,36,24,195,146,238,187,62,107,13,195,52,32,151,216,147,97,4,191,44,73,111,185,238,179,223,56,81,117,179,77,122,79,8,58,245,217,221,50,152,61,61,213,58,135,180,123,100,177,46,129,164,191,164,
194,175,127,252,133,201,186,55,22,180,12,190,119,195,173,240,112,58,236,244,176,185,11,246,146,100,162,211,205,235,229,114,229,246,124,233,240,252,132,31,67,196,85,131,139,14,251,120,98,73,9,99,18,16,
118,115,233,78,166,169,58,123,115,125,154,190,209,16,26,142,202,157,190,4,142,214,39,53,187,130,165,116,218,254,178,224,155,238,49,246,190,109,209,225,181,180,138,181,134,163,27,119,50,147,51,119,195,
150,53,6,127,75,51,100,195,224,28,175,215,153,214,116,9,238,118,27,90,253,79,122,52,146,244,100,30,245,219,109,146,181,86,20,76,40,162,153,72,57,9,95,191,158,153,130,251,9,50,27,177,56,175,239,195,231,
47,223,116,52,230,66,207,220,213,176,167,183,103,241,104,15,218,217,159,38,188,100,161,220,50,43,150,235,229,186,199,28,75,22,94,94,110,59,14,71,155,193,110,167,236,113,175,169,8,214,91,188,51,111,186,
138,190,145,239,92,149,66,131,160,104,157,74,35,250,200,136,221,231,112,18,42,113,8,68,231,72,34,154,83,215,177,126,211,48,210,164,114,121,209,182,223,91,135,31,195,4,15,170,72,145,23,157,214,76,102,220,
51,50,170,185,3,47,198,232,246,231,252,246,178,114,75,137,65,32,70,183,51,6,213,119,4,171,11,204,238,198,5,157,170,207,57,49,132,192,56,6,76,174,186,99,118,142,220,218,254,109,110,59,141,237,195,78,99,
100,205,121,207,135,78,107,193,59,99,104,58,34,239,98,249,164,178,112,235,119,159,144,219,32,2,210,72,115,82,46,96,133,131,243,156,151,91,199,66,41,32,248,110,183,44,20,26,31,159,30,239,44,64,169,72,173,
56,209,21,65,138,250,33,55,39,168,180,74,116,97,71,63,165,222,226,111,140,149,120,140,248,235,122,67,114,165,73,226,249,252,242,19,144,101,51,151,108,182,29,201,137,229,154,104,64,24,124,239,193,122,8,
153,146,83,251,107,167,75,30,128,63,255,239,223,21,35,149,20,4,238,172,193,73,23,236,245,17,151,179,42,174,115,253,214,221,99,9,82,225,251,247,51,203,245,7,143,199,35,79,15,19,222,118,127,252,22,162,43,
77,135,28,151,235,204,60,175,76,211,208,165,138,35,214,25,172,53,204,185,144,23,189,201,196,233,165,225,195,38,57,128,210,3,240,130,115,156,198,136,72,64,130,94,189,206,26,66,221,17,109,252,242,199,15,
42,238,251,15,68,70,177,22,235,44,239,158,30,152,201,96,12,151,148,240,143,211,1,166,134,212,72,253,227,47,63,57,96,55,93,250,150,69,43,146,152,66,230,177,182,110,78,113,44,105,233,80,129,168,27,161,6,
75,42,72,207,72,146,121,193,217,159,219,158,22,236,189,187,88,11,113,8,12,61,67,105,211,99,228,174,69,158,66,96,185,124,211,241,89,206,120,55,4,162,117,184,56,49,200,39,74,202,63,129,134,34,254,30,19,
43,185,91,24,124,47,94,2,231,235,181,95,221,96,49,90,104,119,200,166,51,6,185,204,186,39,121,179,35,145,112,231,8,165,34,196,238,142,153,151,196,249,124,225,124,89,152,111,51,185,54,158,38,79,155,231,
29,131,226,159,191,63,99,58,177,249,251,95,254,250,70,135,222,235,134,165,238,90,223,24,13,161,39,139,109,12,191,209,187,157,100,167,136,73,189,20,68,10,69,50,215,231,43,99,208,68,247,53,235,31,147,169,
186,38,168,141,165,201,94,20,149,78,85,136,49,242,244,120,228,225,81,243,65,95,231,11,243,92,72,75,194,231,181,80,170,144,229,198,151,175,207,61,43,60,16,189,106,118,220,20,21,143,183,44,92,94,18,203,
156,244,27,236,89,225,182,109,153,49,9,107,96,152,6,142,163,106,55,151,117,225,253,195,17,233,229,98,110,170,157,48,78,119,36,54,118,2,169,215,4,227,44,234,253,176,78,51,30,189,143,184,193,35,229,136,
245,137,113,114,248,119,31,63,226,45,88,231,248,67,212,24,150,205,72,18,176,136,237,249,48,181,233,98,187,147,237,232,240,171,135,33,98,130,58,16,140,181,164,156,238,220,247,44,140,199,238,225,120,83,
139,128,170,77,162,115,36,222,44,115,128,208,223,198,188,109,84,93,229,20,146,26,6,93,192,31,166,73,73,51,214,97,78,19,206,142,132,62,57,116,21,50,173,103,140,87,164,42,163,85,45,108,234,53,90,107,222,
143,178,6,132,56,96,163,39,246,151,166,74,193,57,148,15,239,28,181,246,192,156,218,97,114,253,40,220,210,59,77,255,127,66,182,26,146,218,27,159,101,73,92,214,27,62,149,68,73,42,101,249,250,231,223,176,
246,78,60,112,2,210,253,109,218,222,40,95,85,127,99,173,93,23,39,172,41,147,182,156,229,10,37,235,124,77,82,198,197,0,168,148,87,68,246,111,115,99,22,135,173,245,9,118,95,184,231,69,75,219,84,132,249,
58,115,254,246,133,84,180,206,246,159,63,127,33,103,253,169,255,250,151,207,56,171,227,34,103,45,182,66,181,61,74,187,170,5,210,116,202,168,226,116,160,140,102,15,211,173,85,246,136,44,213,42,232,180,
157,168,133,204,0,0,32,0,73,68,65,84,198,153,13,226,105,238,183,166,181,119,96,92,135,11,216,170,144,219,119,79,167,251,158,3,207,243,239,239,247,26,217,255,242,241,131,6,220,132,192,223,191,19,188,83,
123,174,53,22,211,160,25,118,230,79,19,21,115,46,115,34,173,89,91,39,87,137,209,49,77,145,232,157,182,75,189,205,26,162,227,252,58,19,162,99,24,222,230,126,105,165,215,164,114,232,250,182,218,47,155,77,
186,190,57,215,167,227,145,95,159,156,70,49,139,108,114,92,29,70,171,105,58,117,139,218,22,225,221,246,35,46,246,205,188,188,209,196,79,99,84,87,214,24,129,198,237,182,48,175,73,115,97,172,97,136,142,
156,27,175,47,149,148,133,82,186,81,170,246,163,108,95,192,188,217,99,219,59,3,115,89,87,218,237,194,116,140,152,84,241,127,254,151,223,72,101,38,167,204,239,255,242,207,120,167,185,247,49,122,162,117,
100,90,23,226,53,134,232,176,205,144,150,162,75,18,11,114,110,61,37,66,95,214,220,182,5,142,126,96,233,231,244,54,185,79,111,132,251,202,130,189,127,227,165,179,219,166,67,100,154,38,142,83,100,190,93,
200,45,225,18,28,172,195,127,250,227,123,154,40,63,245,151,113,101,28,29,131,209,150,168,38,205,223,184,243,208,116,119,182,101,22,216,126,140,57,231,24,250,250,234,182,20,114,210,121,4,192,130,112,112,
145,96,213,203,81,165,99,252,210,70,107,42,187,244,113,195,82,215,218,122,61,221,248,239,255,253,159,120,254,237,47,188,206,43,146,42,254,252,249,43,206,107,161,114,253,250,204,117,99,186,183,198,245,
154,8,83,236,64,140,162,201,169,169,145,69,171,151,224,12,195,150,215,236,44,203,154,153,175,87,214,165,116,55,121,38,149,237,154,87,219,123,235,202,193,237,229,204,8,227,208,17,17,162,248,145,211,97,
196,121,79,74,137,235,151,149,239,191,253,141,203,45,225,89,241,79,239,166,253,175,252,248,139,126,211,235,162,6,211,167,167,83,23,36,111,189,157,218,42,203,34,93,110,30,201,105,6,53,220,170,64,250,143,
143,28,162,78,55,107,169,80,85,95,217,74,163,82,73,82,52,131,201,235,139,186,246,171,185,230,74,107,130,49,90,84,149,214,200,75,226,175,159,191,114,122,28,248,227,159,30,248,240,52,225,231,185,11,63,131,
229,242,124,38,245,204,78,215,229,137,155,195,197,199,192,24,13,198,128,216,206,16,70,55,164,13,209,76,48,81,155,207,107,116,189,77,234,31,46,40,21,76,208,227,175,116,83,235,188,58,230,229,94,183,236,
81,1,82,184,93,23,230,37,241,238,253,137,230,19,223,231,149,215,229,140,191,92,94,241,206,130,115,204,243,170,140,147,232,118,15,232,191,127,253,170,210,154,232,152,38,15,5,150,155,66,134,156,213,67,62,
216,109,128,168,117,181,233,75,64,189,7,42,227,160,107,128,34,194,178,129,181,242,126,255,239,195,155,56,68,98,39,45,229,170,246,123,177,129,193,77,184,38,204,105,198,255,211,127,253,123,188,53,184,24,
184,184,133,91,95,66,215,90,89,214,194,127,225,151,253,165,155,38,157,208,212,220,84,117,211,125,160,214,25,92,208,233,144,250,59,164,15,17,245,88,218,232,29,41,173,60,245,76,74,63,4,162,179,124,63,191,
232,198,115,219,99,247,243,118,240,129,241,16,49,213,209,236,200,224,12,222,76,248,223,62,127,133,214,212,164,244,219,23,230,57,145,69,56,118,96,197,166,114,90,214,196,60,171,44,33,154,176,183,53,95,126,
156,169,189,43,27,125,184,7,72,247,209,231,113,138,136,64,74,43,215,235,186,199,115,15,82,88,13,76,113,96,138,195,190,155,43,82,246,229,207,48,141,180,20,185,242,66,218,118,221,79,79,79,180,110,171,52,
79,143,76,83,166,138,90,208,78,199,9,227,180,120,95,215,68,46,125,181,106,157,22,75,198,114,122,56,252,20,7,176,230,204,178,172,44,171,158,221,193,121,194,224,123,232,66,151,243,58,199,16,61,198,178,239,
240,52,30,174,145,139,174,190,114,173,4,107,201,237,134,48,51,13,78,29,139,151,219,13,170,90,111,190,126,62,99,157,225,48,142,92,111,51,223,190,95,176,174,236,3,193,86,245,67,136,243,56,171,47,86,107,
66,140,90,184,164,84,248,242,245,153,239,223,207,92,47,51,80,121,255,254,9,231,84,16,242,122,157,247,29,220,20,2,113,84,28,101,74,133,37,229,157,67,177,147,202,67,224,113,74,252,248,250,149,96,193,68,
143,119,68,245,24,45,43,175,23,85,164,86,209,202,234,54,47,93,58,30,250,184,72,229,180,174,231,205,8,16,198,94,24,57,203,50,175,164,148,192,57,166,195,132,11,234,89,214,236,50,45,170,162,115,24,2,14,67,
205,22,67,96,26,43,135,163,229,253,251,83,159,69,171,200,36,45,25,63,157,248,232,39,134,48,16,237,17,255,199,79,159,246,162,250,239,79,236,164,240,203,117,230,252,242,186,167,64,41,17,183,80,114,82,186,
232,171,206,139,255,240,233,128,72,194,56,109,249,107,86,13,92,219,225,68,122,85,111,90,138,113,208,71,45,186,240,19,39,54,101,65,90,82,250,76,205,204,115,226,117,94,137,83,166,205,154,176,233,168,248,
127,254,215,191,208,138,162,119,191,255,219,255,250,105,46,176,44,43,199,211,161,231,215,26,106,45,72,83,58,66,149,198,154,11,159,191,255,59,41,151,125,242,227,172,101,24,60,173,8,166,239,234,160,237,
166,19,99,182,44,220,174,132,89,180,74,155,231,155,162,252,140,217,241,101,169,100,92,92,184,157,127,104,74,33,13,95,86,245,12,197,232,25,134,251,180,114,154,6,62,124,120,218,255,59,213,192,107,16,77,
87,150,227,134,200,101,94,123,10,165,190,119,214,84,36,135,94,191,182,158,45,211,89,85,21,117,150,85,246,139,233,240,52,49,1,199,217,237,45,212,54,7,76,34,164,242,29,242,64,180,35,129,136,255,167,127,
250,163,194,100,167,72,254,69,41,48,231,151,139,146,15,178,240,112,84,34,110,12,161,47,5,239,193,77,42,227,253,59,214,117,193,116,43,165,65,33,137,243,188,130,84,230,235,141,37,101,214,180,168,149,184,
86,198,56,106,253,220,21,172,202,224,214,180,169,82,50,41,181,93,37,155,203,223,177,92,158,181,28,77,13,63,47,87,46,203,21,247,2,175,159,255,178,15,157,231,101,85,207,198,229,220,137,250,90,224,216,142,
235,107,169,238,231,101,234,11,113,253,230,232,91,210,130,1,190,127,255,193,188,204,170,138,106,224,163,99,240,151,222,148,8,165,54,166,49,226,173,39,173,69,107,105,122,39,109,45,89,60,215,243,119,96,
101,93,22,252,95,254,237,55,106,77,172,41,241,151,255,249,127,49,12,81,53,16,176,159,137,27,198,105,67,173,187,170,39,68,237,241,130,160,67,188,237,146,129,186,227,156,126,253,244,1,23,2,239,15,234,98,
116,70,87,5,37,9,139,204,216,30,118,86,114,98,45,194,50,47,74,191,25,2,45,56,158,252,129,113,82,105,88,26,12,254,225,253,132,229,136,49,224,214,63,169,94,109,136,123,193,109,140,217,93,221,89,10,173,21,
213,237,148,170,41,217,77,255,152,195,52,64,189,7,239,150,254,191,189,204,51,199,56,242,244,56,105,250,201,122,101,157,149,4,50,198,200,44,43,49,12,12,199,192,3,6,249,240,200,219,168,153,245,229,6,8,83,
28,56,198,136,255,229,255,248,199,173,6,225,253,147,101,116,94,185,37,2,178,20,166,83,220,225,197,146,250,55,152,215,93,185,55,47,185,63,50,1,23,238,131,234,224,52,247,83,106,32,205,87,46,243,133,182,
204,204,199,1,62,8,213,21,82,173,24,9,12,206,99,130,101,12,158,135,135,9,74,99,158,85,220,255,52,142,148,31,138,85,167,53,188,188,56,13,24,115,32,179,67,70,167,59,180,90,49,177,113,62,167,221,25,158,115,
97,93,86,72,73,79,141,165,208,156,225,235,143,185,175,189,212,86,28,186,134,210,24,139,13,134,83,12,156,166,39,112,7,234,172,112,22,103,12,199,67,160,230,239,125,235,148,153,47,51,207,207,175,44,215,149,
243,235,133,146,133,191,251,240,158,203,249,251,78,196,243,255,239,255,248,127,52,67,195,193,231,255,239,255,198,185,134,177,149,226,54,128,219,27,242,231,146,145,86,120,244,131,146,159,165,50,211,184,
94,47,92,94,175,218,234,68,221,87,196,168,19,203,210,178,138,241,5,70,23,41,140,170,114,77,141,107,21,226,155,48,95,149,217,88,90,214,89,93,109,141,111,191,127,231,246,253,251,190,237,247,211,152,186,
186,191,50,141,236,240,226,216,151,220,177,103,142,3,172,65,75,207,167,30,77,104,170,210,109,111,203,137,84,146,238,243,130,195,160,66,143,49,70,172,119,188,156,95,120,254,118,209,13,232,113,192,85,199,
101,93,145,165,50,185,73,47,29,81,17,116,140,161,47,232,187,135,58,9,233,131,250,73,83,90,240,159,30,63,161,59,73,195,144,28,197,88,76,24,24,135,7,221,33,199,192,24,53,172,76,49,191,141,201,105,50,149,
72,229,124,153,113,239,45,227,224,25,198,64,73,194,245,170,102,167,24,148,232,252,244,81,248,227,227,74,91,18,9,1,215,131,162,34,32,23,74,173,212,182,109,89,213,211,92,187,85,88,68,48,7,122,249,249,128,
183,177,237,176,250,194,138,224,160,26,82,185,98,150,8,203,11,231,190,108,89,110,171,22,243,162,65,168,146,132,241,52,117,6,188,3,11,215,151,153,215,235,43,85,132,224,2,47,183,68,52,142,227,49,48,4,16,
183,130,111,140,147,135,232,153,207,186,53,146,110,181,172,85,17,15,186,40,87,69,120,121,57,171,207,78,4,255,124,123,165,182,68,203,133,223,207,127,86,31,220,91,84,68,146,29,173,75,159,66,58,41,244,72,
19,236,220,71,135,78,119,208,181,41,37,204,25,173,153,231,37,97,169,60,23,199,201,57,236,20,168,53,147,190,23,214,84,88,46,3,37,233,75,232,66,231,15,27,245,71,47,73,1,4,243,203,153,211,24,117,6,23,195,
175,208,18,213,21,158,30,206,96,87,138,17,253,35,106,99,176,195,222,190,12,27,85,52,41,235,149,6,118,208,83,166,118,179,9,125,95,39,37,147,230,194,227,199,8,69,111,65,143,163,217,64,173,142,134,101,161,
114,12,78,21,129,85,246,136,184,184,113,142,83,194,89,71,190,60,19,7,45,154,252,248,203,17,234,132,105,130,229,35,134,198,64,101,136,150,209,58,170,143,29,77,173,56,233,255,159,172,183,235,145,35,201,
210,244,30,251,116,247,136,200,8,146,197,154,234,238,217,158,105,205,172,4,45,176,208,165,0,65,191,92,23,186,20,4,65,87,11,236,106,23,154,153,238,158,174,234,110,178,138,149,201,140,140,8,119,55,179,99,
166,139,99,225,153,53,202,59,22,88,100,50,210,221,236,124,188,239,243,170,194,181,226,104,221,70,217,5,120,162,11,235,218,5,73,89,26,28,42,184,72,24,45,182,10,166,35,218,151,50,83,211,141,73,26,41,143,
140,126,208,99,235,206,9,119,142,24,28,211,97,36,142,158,152,2,46,58,157,94,78,241,117,241,96,199,35,222,140,88,49,80,44,115,17,150,245,70,22,243,198,10,108,24,77,100,28,21,142,209,80,29,251,146,82,247,
64,59,154,56,170,128,11,134,209,235,159,87,107,83,3,107,3,114,4,78,196,8,38,158,105,237,62,163,215,179,155,62,32,191,255,157,151,229,6,221,249,230,255,242,199,39,76,42,52,50,207,159,255,136,15,218,10,
41,6,167,112,254,250,180,49,123,36,75,207,108,118,28,166,73,133,33,209,48,47,43,75,73,212,238,68,200,77,54,215,225,195,97,236,48,24,173,220,40,58,156,46,189,62,78,215,190,19,180,186,74,184,243,52,77,112,
27,25,236,241,243,95,85,86,233,29,254,250,244,72,35,81,91,226,199,167,63,16,156,65,134,162,186,8,3,227,81,15,113,43,66,115,42,64,206,21,230,20,73,206,115,190,232,243,71,211,109,144,11,142,216,29,92,206,
24,110,245,51,85,38,21,120,140,13,170,97,63,53,170,244,198,211,189,223,26,88,58,36,217,118,15,127,179,80,157,161,213,133,218,58,127,232,120,204,84,231,176,38,82,230,7,150,218,192,122,198,65,197,117,7,
166,45,250,39,165,66,19,209,128,116,209,64,212,169,150,215,93,244,16,94,85,0,77,65,102,211,84,113,4,149,223,44,149,49,4,156,241,208,250,117,255,237,109,27,28,42,68,241,117,117,171,111,186,231,253,228,
48,221,234,227,79,239,255,1,76,37,56,141,24,44,77,183,240,244,96,82,36,18,141,99,232,99,36,231,29,174,52,178,44,119,11,83,207,216,16,77,105,174,157,231,46,90,172,136,241,10,172,52,194,56,25,166,113,207,
208,85,90,250,208,62,109,11,114,23,28,120,183,233,137,53,10,185,242,16,74,191,56,4,63,157,126,213,19,249,50,199,119,47,88,83,16,187,178,44,11,89,146,142,239,239,98,231,16,122,33,111,40,57,233,143,242,
38,164,37,111,167,7,125,154,46,52,156,131,18,163,234,128,68,119,39,46,194,124,211,185,153,181,150,154,199,123,199,133,13,190,227,28,116,44,91,106,197,57,65,154,158,34,206,88,252,45,253,153,101,185,146,
165,49,63,125,207,56,40,154,233,250,146,120,185,220,248,211,95,190,110,15,255,24,92,207,170,211,254,206,37,56,13,39,114,146,30,78,214,116,137,213,175,84,90,227,49,9,82,11,89,10,251,224,113,17,210,50,119,
247,109,232,122,120,245,128,26,103,251,186,82,215,199,202,126,119,60,255,244,19,75,214,23,213,187,207,159,113,115,34,122,71,123,122,162,6,195,140,240,50,23,181,202,22,161,36,213,95,86,28,115,190,34,146,
161,105,236,102,122,86,97,134,233,158,164,210,61,244,166,171,175,150,238,200,133,202,108,157,166,169,20,253,61,18,189,70,209,139,74,31,130,211,8,130,37,101,181,21,1,236,2,73,18,193,130,173,224,63,255,
221,191,71,210,10,77,120,22,97,23,34,31,227,192,71,44,129,192,48,70,230,219,162,192,250,224,123,33,68,255,166,65,204,163,242,77,92,0,11,235,178,40,126,204,106,87,242,119,97,68,90,37,223,29,217,210,16,
178,254,68,60,124,55,78,72,42,170,238,166,253,34,57,45,122,207,181,36,210,227,187,215,177,214,63,238,79,44,46,209,214,196,224,6,34,142,227,244,128,239,69,184,204,9,91,154,130,50,90,233,165,109,161,86,
81,41,249,208,49,167,65,1,193,235,178,104,0,100,207,170,181,86,253,204,136,168,178,21,8,214,144,107,163,220,18,159,191,94,144,165,31,151,82,148,244,24,28,99,87,164,252,229,211,23,30,63,127,130,14,144,
241,207,255,215,255,182,197,107,255,252,167,255,140,68,199,159,15,19,43,141,106,225,232,98,71,252,246,102,49,173,74,34,45,154,80,253,254,241,157,74,116,93,195,24,71,89,117,53,22,156,97,24,35,231,44,58,
60,244,90,223,54,167,222,209,218,101,93,127,148,231,205,223,33,253,121,30,66,96,183,27,57,76,19,210,42,151,243,153,180,170,139,193,231,223,252,3,181,25,38,111,249,219,195,65,113,121,2,169,106,34,101,20,
69,60,222,113,209,203,178,82,74,210,102,213,71,236,239,132,91,74,140,222,17,70,253,61,47,75,66,214,212,25,63,129,105,84,219,186,52,65,114,5,155,201,85,152,138,240,31,174,199,77,81,216,254,77,162,251,224,
189,26,8,198,134,205,42,126,242,135,247,255,129,150,87,69,137,201,9,58,95,135,162,120,145,67,39,232,223,83,43,93,40,216,17,134,168,187,227,231,211,191,34,151,149,171,173,157,85,85,88,39,143,20,79,94,244,
47,63,59,112,166,81,82,37,153,172,233,128,14,172,11,252,46,186,174,151,184,91,42,244,249,53,61,3,228,203,229,140,5,134,49,16,140,195,255,249,63,253,239,26,180,91,225,243,31,254,11,184,64,139,78,19,89,
187,244,91,231,6,202,12,46,101,193,84,245,28,9,240,157,196,142,227,85,51,84,73,133,74,197,246,140,92,73,169,231,221,85,172,87,212,164,241,150,16,61,163,11,252,215,99,220,230,24,41,149,174,185,120,213,
126,174,235,141,159,126,248,17,31,13,227,20,241,213,116,252,169,88,46,233,66,243,22,143,231,37,37,150,62,235,218,239,38,134,49,234,152,10,173,27,214,156,200,173,242,156,186,103,40,122,238,194,8,75,167,
57,75,102,255,126,175,89,73,146,241,198,245,237,189,116,252,191,112,125,58,247,103,87,47,156,105,84,13,232,52,170,25,241,42,39,245,80,83,117,46,49,253,238,127,229,168,178,62,226,254,27,82,46,32,249,53,
48,196,153,126,251,168,170,196,153,94,168,171,91,140,199,248,172,150,226,218,240,161,19,63,122,148,150,202,207,51,94,26,33,9,136,16,250,74,216,91,135,195,241,237,210,84,188,239,220,54,79,51,189,4,0,248,
181,187,208,190,137,218,105,215,134,255,199,143,7,168,141,214,18,239,243,3,203,178,210,80,0,134,239,223,168,53,170,71,215,21,171,170,183,141,215,63,244,253,225,131,234,44,107,83,27,112,239,20,214,164,
228,209,241,206,163,232,53,6,169,18,234,171,66,59,119,206,246,125,86,60,198,192,48,69,162,243,180,38,184,60,82,111,207,74,210,149,27,254,143,159,127,15,93,175,62,63,255,64,170,13,108,165,173,111,83,234,
186,160,40,45,186,231,168,16,156,206,224,246,143,142,165,59,100,68,132,181,167,148,208,32,24,131,73,130,117,108,29,244,93,207,153,150,66,107,194,237,42,219,85,124,135,195,132,238,189,147,44,32,123,158,
127,254,212,117,112,9,159,190,255,172,21,90,22,158,62,127,175,139,197,170,35,169,212,132,95,31,142,175,177,21,173,32,75,214,41,163,119,204,206,240,39,212,146,211,145,179,29,76,100,153,38,79,28,71,36,21,
196,191,241,198,89,171,105,42,131,3,12,223,152,87,202,249,29,205,174,143,71,163,32,204,242,140,225,12,178,208,90,193,255,253,255,244,63,144,151,140,164,194,233,59,183,81,102,176,125,120,114,185,244,127,
121,224,158,17,50,191,44,61,115,188,242,55,94,197,26,99,212,30,99,77,137,188,172,8,186,254,125,8,81,223,246,187,193,213,168,250,196,57,71,24,28,105,53,170,119,3,114,110,155,209,187,245,72,35,63,125,224,
87,231,131,238,18,189,197,255,213,100,36,52,8,112,105,17,250,173,214,156,197,24,79,59,133,62,54,18,77,43,52,22,217,123,45,113,141,227,219,235,172,246,246,174,80,137,217,179,70,191,169,0,147,136,190,184,
226,54,220,67,201,90,137,205,115,37,189,155,136,119,210,205,221,90,214,109,178,69,26,213,4,82,156,24,109,212,24,162,31,255,207,255,4,174,129,119,92,255,242,131,250,51,194,107,46,81,220,143,154,158,179,
204,180,44,148,114,23,35,233,203,241,79,50,83,150,220,181,195,175,124,147,187,119,159,193,233,217,235,12,1,75,16,72,210,55,159,171,240,147,204,27,245,81,3,159,28,49,198,142,52,43,188,204,194,249,231,31,
153,66,96,63,69,252,135,65,203,55,214,76,126,126,81,233,184,188,26,165,90,212,172,239,189,18,84,84,180,44,170,45,219,77,129,217,232,82,220,180,74,236,215,239,178,148,62,93,175,36,167,98,39,20,61,204,96,
29,161,75,204,140,49,252,71,9,42,157,204,218,165,248,80,177,78,127,125,93,86,62,6,56,127,189,224,12,236,143,224,15,255,227,127,71,74,43,105,94,25,39,61,26,162,185,19,235,42,38,6,92,19,140,169,58,134,109,
224,114,213,11,34,56,190,19,207,114,213,101,77,107,16,157,193,120,187,41,182,221,157,108,228,218,134,58,237,84,229,109,241,98,173,217,148,92,119,75,178,113,150,163,53,12,217,113,186,188,167,57,85,21,122,
23,35,251,24,152,134,9,110,7,230,249,74,109,86,119,205,99,212,60,90,116,45,70,213,221,162,157,204,54,105,148,5,38,31,145,162,252,169,232,85,156,180,113,5,138,126,83,141,123,60,119,15,193,233,168,246,185,
232,204,34,85,149,226,28,166,35,251,233,213,78,159,91,34,157,27,77,12,75,178,120,169,130,180,130,164,202,66,194,68,199,216,163,136,109,180,76,93,29,21,239,121,205,216,142,23,211,137,99,113,141,225,189,
39,118,132,148,49,176,166,194,124,187,178,44,133,48,121,114,123,149,27,152,208,205,226,253,235,92,87,214,53,235,88,202,57,226,20,176,247,137,63,176,90,75,29,29,214,120,108,179,248,207,255,249,95,84,128,
63,223,248,241,95,255,155,218,29,140,46,18,173,179,152,232,25,7,181,64,132,59,129,159,70,18,13,103,146,113,210,134,19,211,13,221,58,91,187,127,79,199,227,78,169,138,107,126,157,191,189,9,109,138,105,38,
231,204,186,118,202,93,202,234,142,233,169,196,37,195,124,126,196,5,29,24,250,64,100,138,141,82,3,53,28,212,53,211,145,234,206,9,204,58,249,158,89,184,245,249,153,115,10,171,104,210,248,105,159,168,221,
239,38,29,116,120,79,141,114,193,241,231,191,252,68,110,186,53,82,105,184,34,35,233,47,246,183,115,126,141,128,75,73,255,140,77,159,236,57,250,192,243,139,2,236,230,178,224,235,63,124,71,233,116,2,251,
109,98,31,182,247,129,86,43,151,219,13,211,193,109,14,171,235,174,141,18,90,249,221,53,43,3,205,104,184,216,61,220,70,186,255,104,152,94,183,171,210,29,8,111,191,126,10,154,235,99,140,209,141,104,87,190,
170,53,194,65,202,212,151,15,20,129,83,110,120,14,71,164,102,42,9,234,1,63,70,198,24,117,186,211,26,230,146,182,216,194,96,94,51,145,116,222,38,124,252,114,83,9,227,157,30,19,27,83,111,40,223,218,52,99,
212,121,3,217,246,66,199,97,29,124,153,94,131,209,99,119,50,222,149,46,77,42,46,128,191,89,108,243,184,12,254,31,147,87,139,2,35,203,229,153,244,152,105,245,194,110,84,184,225,124,235,225,76,37,19,125,
221,162,87,28,22,231,3,233,219,145,92,50,47,215,27,183,37,105,184,185,52,172,211,49,255,16,192,197,72,244,22,154,33,53,13,27,105,89,175,246,255,37,239,137,81,213,133,222,190,58,112,238,0,164,203,85,72,
183,153,121,185,34,82,240,98,10,214,193,146,51,207,203,83,71,160,55,190,156,207,42,43,184,199,184,161,90,204,112,207,111,238,169,169,207,63,189,80,171,222,128,202,18,4,63,106,86,227,146,10,31,15,145,236,
22,94,138,74,112,124,106,188,247,145,73,128,155,240,116,251,76,202,186,61,26,7,143,43,141,235,77,131,29,162,115,44,215,153,116,123,198,70,168,190,226,63,127,249,2,182,50,95,95,248,244,207,127,36,70,45,
76,230,121,233,235,87,121,67,192,53,29,48,32,204,235,202,50,47,220,184,117,107,142,211,2,101,112,4,44,75,73,172,115,226,207,206,83,99,71,52,116,124,250,41,76,76,198,67,17,158,127,122,98,126,89,117,238,
209,167,150,83,119,141,239,119,35,243,101,225,246,211,35,201,235,40,204,63,167,68,12,14,177,32,209,146,68,151,59,227,24,57,78,234,9,165,106,41,235,172,217,208,12,41,175,44,107,226,121,125,86,203,77,79,
140,10,81,15,252,152,132,28,19,80,180,62,192,99,246,22,124,199,83,59,143,68,203,233,195,137,169,95,205,119,186,99,20,237,154,119,187,129,161,53,204,207,71,198,36,32,22,255,219,191,255,29,54,170,195,246,
215,167,29,181,136,198,95,229,134,109,149,91,213,103,205,54,157,142,7,171,131,102,37,29,9,217,201,107,30,76,63,57,156,177,119,121,48,151,52,43,179,170,207,131,147,131,217,192,236,128,209,50,127,80,247,
216,62,70,34,134,148,18,243,45,97,130,133,160,104,41,249,16,117,11,42,30,31,135,147,162,114,17,98,60,170,232,83,132,151,167,103,158,206,103,252,56,245,37,161,223,28,6,119,146,190,174,107,123,58,107,147,
187,166,249,213,199,36,149,143,167,15,32,21,150,222,20,208,176,168,90,16,231,24,163,218,45,29,154,42,232,93,224,193,143,111,242,68,85,137,162,84,216,65,51,101,236,82,59,125,0,140,213,137,225,195,251,19,
110,28,169,22,198,193,51,77,81,73,159,139,182,65,175,46,197,74,105,21,67,35,14,81,151,72,210,144,82,40,185,144,168,84,107,33,66,77,176,143,240,110,60,17,247,138,161,60,184,214,163,3,212,212,109,189,161,
26,85,192,206,47,9,82,35,221,170,22,92,36,252,203,151,207,220,230,149,148,102,126,252,211,63,145,115,97,138,142,227,113,215,163,50,35,178,54,230,213,116,132,158,176,100,13,107,8,206,146,206,170,127,191,
243,87,13,234,47,90,251,140,65,100,197,141,234,62,68,148,163,118,72,43,254,236,112,205,241,146,68,123,194,84,94,11,166,86,185,46,9,185,38,125,233,190,254,76,37,145,114,194,255,245,211,247,204,215,153,
84,18,143,63,254,89,79,129,227,64,122,190,246,28,152,214,177,186,90,184,47,57,105,49,95,180,75,222,79,145,235,101,102,77,165,51,146,205,235,206,2,240,17,198,105,216,24,41,14,56,226,48,87,161,60,205,156,
113,219,138,192,220,229,152,214,18,7,53,101,123,28,222,43,162,207,70,240,31,93,128,189,99,113,133,99,254,22,156,165,58,15,78,163,98,155,185,64,115,236,68,15,115,159,96,218,91,53,64,161,228,219,248,62,
82,250,60,97,63,69,188,15,56,107,41,181,128,179,24,65,33,48,233,149,81,225,222,57,150,95,9,191,42,117,131,109,153,202,43,120,171,227,121,106,113,228,92,176,22,150,154,240,251,211,158,218,32,144,24,249,
0,193,129,87,119,128,186,15,223,119,52,147,214,1,13,125,193,94,115,20,47,4,71,207,30,200,44,185,108,120,29,231,35,165,84,178,21,106,22,114,81,83,202,58,4,221,226,135,192,153,138,84,207,98,181,133,202,
226,153,187,64,68,106,197,239,27,151,39,29,20,18,28,254,240,241,93,15,203,75,148,184,128,233,225,97,181,131,131,208,36,64,151,181,11,118,214,16,189,206,195,154,52,188,156,58,32,35,51,142,19,31,78,177,
171,4,19,115,90,8,211,72,237,150,134,86,117,196,154,104,212,177,27,83,247,19,41,105,241,191,246,56,251,104,53,49,187,54,33,153,130,152,17,107,71,168,30,63,157,190,81,98,103,206,164,166,94,208,85,106,39,
47,234,154,74,68,16,175,250,76,239,29,177,183,224,183,148,240,109,228,48,30,48,147,125,165,43,2,199,3,156,172,225,231,231,39,172,117,236,38,45,170,174,41,49,231,140,4,75,54,192,168,157,246,102,92,125,
227,229,207,34,12,14,242,232,137,126,68,196,224,159,159,86,205,68,50,134,182,24,132,168,32,67,99,181,131,200,65,7,216,171,66,143,197,89,37,219,118,231,128,11,69,115,150,123,12,103,238,113,133,46,6,172,
129,195,238,29,53,101,236,98,184,46,112,203,176,36,72,17,170,55,148,63,255,188,217,235,205,16,33,233,90,102,145,172,100,176,113,224,165,43,82,14,198,225,191,252,248,19,142,6,131,129,14,251,94,74,198,121,
71,26,45,109,17,214,57,49,223,179,8,238,220,19,133,240,114,185,220,200,171,254,183,49,4,14,135,137,97,26,136,139,122,155,255,235,255,243,51,72,209,91,50,56,146,52,204,232,136,83,164,121,131,121,252,178,
241,225,109,183,194,251,59,128,57,11,23,38,150,159,31,137,17,150,152,240,53,189,144,243,138,156,133,231,207,127,64,18,92,210,66,203,133,24,28,206,93,180,232,145,87,127,80,205,165,211,9,12,11,71,13,212,
117,142,107,18,190,126,82,246,240,56,68,166,49,146,208,14,123,192,130,24,116,14,25,104,121,37,207,133,150,179,110,161,154,162,115,238,209,46,209,185,190,125,154,89,76,130,232,136,84,252,175,255,246,192,
124,117,164,117,97,47,247,53,173,235,56,83,75,190,170,1,100,26,149,104,160,179,94,233,220,8,88,252,171,26,219,90,131,139,246,237,8,145,159,175,9,74,197,74,133,220,48,34,132,81,197,210,107,106,200,175,
63,226,176,28,246,3,161,243,82,144,170,60,160,181,64,244,60,127,214,124,177,128,197,59,217,113,218,239,96,47,92,107,226,50,103,146,172,186,52,113,234,138,153,139,33,38,135,171,176,204,106,119,87,210,104,
127,49,130,67,221,233,69,225,92,84,162,83,91,229,111,79,74,204,159,111,74,93,172,185,49,140,158,33,142,125,188,122,143,119,233,115,9,116,8,9,142,247,39,207,126,31,248,237,113,234,150,248,130,79,226,186,
45,161,81,240,76,239,39,142,46,80,141,90,210,218,135,188,249,230,107,181,132,189,14,187,167,65,143,182,193,141,58,115,115,186,193,175,45,3,94,71,173,56,158,111,103,156,15,76,15,40,199,216,53,133,24,73,
231,194,7,135,243,129,195,56,18,7,175,137,218,107,217,192,156,9,97,89,100,3,101,248,233,97,79,158,103,230,185,112,126,158,137,115,210,229,116,81,37,234,254,208,129,112,25,150,214,225,89,146,32,39,150,
44,28,172,128,47,180,146,209,61,120,219,116,194,10,21,200,12,65,241,12,170,246,107,28,246,59,166,253,128,51,154,36,175,81,181,21,186,57,112,201,185,123,255,251,40,225,118,35,223,67,217,207,143,143,148,
148,104,37,81,46,143,20,4,111,70,220,232,117,25,29,15,84,42,177,211,66,99,112,100,28,98,212,76,197,229,214,45,153,66,90,19,6,245,129,4,70,156,87,243,182,45,234,27,53,203,140,239,205,193,148,85,207,243,
114,185,144,101,217,76,85,174,235,126,150,146,40,41,115,190,92,96,62,179,63,232,35,228,255,240,207,255,5,99,84,123,249,252,253,159,64,32,231,186,89,133,191,126,248,150,74,165,52,184,174,106,96,93,80,182,
85,116,14,123,126,198,57,203,56,233,238,34,55,165,156,7,167,105,162,243,245,242,58,255,45,66,240,145,75,135,28,165,162,150,162,86,235,27,7,216,107,182,210,154,52,97,254,242,248,101,139,155,245,127,247,
155,191,129,156,105,45,115,152,15,212,162,193,29,215,219,202,101,78,252,245,251,63,19,246,131,206,223,188,231,48,6,4,75,203,85,119,206,163,101,152,12,163,211,241,100,46,142,117,45,84,41,212,186,194,124,
37,175,175,121,5,166,174,72,242,164,53,49,167,132,53,247,197,163,154,86,214,188,130,173,12,49,240,16,61,118,10,236,37,244,231,94,240,211,225,129,150,103,210,26,8,97,196,57,195,232,118,28,166,194,41,173,
200,110,207,113,63,113,152,6,194,24,217,13,129,180,10,243,109,233,58,224,247,128,96,172,96,251,132,82,167,71,80,165,176,255,251,95,109,105,172,210,250,224,175,247,112,77,12,206,169,50,54,68,200,146,186,
49,27,118,135,200,110,28,120,124,122,161,238,117,71,39,181,225,49,81,229,87,62,129,137,136,117,84,95,73,24,240,48,163,197,245,79,215,51,67,48,236,227,0,213,145,231,123,64,164,233,231,114,194,5,116,183,
17,7,92,52,152,98,241,131,99,28,100,195,244,166,12,225,205,192,251,97,58,49,14,58,233,81,19,150,118,234,146,132,210,18,213,13,204,53,176,206,234,153,246,225,120,208,88,88,87,169,239,191,81,69,159,183,
125,209,209,120,231,22,6,167,185,228,37,45,12,192,20,2,165,86,100,78,60,247,76,47,24,117,123,26,29,118,138,120,227,40,77,120,54,130,181,17,39,70,199,216,78,157,177,177,117,103,175,137,44,179,144,202,178,
165,5,121,11,214,59,96,162,149,27,115,170,155,213,199,75,60,170,94,104,106,88,249,13,96,145,134,238,133,115,194,36,207,146,27,121,206,164,57,16,157,225,221,20,57,237,71,56,192,242,222,224,188,199,57,195,
165,104,129,116,19,197,150,58,107,177,147,97,48,22,103,99,111,147,12,210,92,39,32,232,254,68,242,202,154,50,149,12,40,221,84,146,190,224,241,219,29,211,169,47,208,77,192,63,61,158,85,77,109,224,252,124,
102,140,30,75,84,220,88,74,44,151,27,209,121,28,77,111,179,44,156,215,153,243,237,70,150,196,195,175,62,144,250,91,213,90,37,221,18,115,147,174,35,214,164,147,197,186,14,172,221,171,87,186,64,115,6,239,
19,13,161,32,24,167,248,135,24,212,24,190,44,22,147,23,134,16,136,157,97,124,157,19,254,196,51,237,190,211,184,254,149,118,173,120,171,180,209,154,50,113,232,11,152,224,8,78,205,34,210,4,87,20,179,30,
174,159,52,85,42,103,170,8,78,42,147,188,194,184,198,59,166,193,57,102,32,207,194,237,166,150,11,235,44,195,97,232,88,52,157,252,196,193,116,240,189,46,203,83,93,152,159,159,180,27,79,5,255,233,175,127,
214,149,67,206,252,248,135,127,82,58,232,253,69,202,69,19,165,156,10,144,91,211,203,97,94,23,202,172,176,216,157,88,150,156,21,67,210,203,194,42,119,30,183,129,8,198,4,198,16,54,198,196,221,53,227,188,
195,219,131,42,5,165,128,243,64,100,28,2,227,100,73,1,206,11,172,77,161,206,123,235,240,241,248,27,32,99,9,60,172,170,211,109,185,178,136,42,247,15,245,110,77,239,170,255,33,227,230,27,121,208,140,57,
156,225,125,84,121,216,120,231,186,150,130,17,141,57,36,250,109,68,27,172,37,195,6,113,49,214,98,7,143,93,213,223,148,83,161,68,207,242,38,175,241,104,13,107,56,80,111,9,111,193,143,199,119,219,78,234,
152,126,211,149,39,150,211,93,236,89,81,238,84,74,44,77,136,41,147,226,140,67,24,198,128,29,162,42,80,157,98,172,179,8,116,232,97,74,137,195,52,105,0,78,173,204,69,16,111,105,163,87,147,128,8,147,11,152,
88,241,169,109,157,142,235,162,15,245,164,78,152,120,128,180,210,200,120,15,172,203,76,109,153,235,243,133,86,213,23,231,172,82,24,255,130,126,146,211,62,114,60,30,169,53,195,37,106,119,12,28,173,35,215,
74,94,18,25,24,131,211,154,88,12,41,11,179,89,48,214,105,3,218,10,163,243,68,167,137,128,89,18,161,85,205,23,245,61,132,175,86,212,180,102,48,88,210,203,133,40,137,84,43,203,45,225,157,115,12,251,1,170,
167,237,135,62,122,113,228,30,165,242,161,3,131,220,117,161,246,157,218,116,19,88,181,19,206,15,134,178,22,114,143,106,153,139,214,191,193,123,226,199,3,50,47,122,33,56,24,221,132,139,250,15,76,41,81,
107,227,121,21,164,159,191,206,90,66,116,248,0,213,107,93,189,138,112,206,43,109,86,169,164,159,118,187,14,45,172,132,199,168,44,225,218,136,30,246,120,150,78,61,8,193,50,221,49,14,99,224,253,126,100,
152,6,230,116,99,181,176,46,186,146,5,8,209,19,7,93,1,15,251,83,23,224,213,14,45,106,224,217,36,139,23,187,42,83,200,43,165,209,223,243,153,250,52,40,152,61,203,94,35,139,40,25,255,233,135,239,113,53,
19,26,252,248,47,191,215,209,103,80,209,133,247,145,67,212,225,182,77,26,197,169,52,70,237,177,130,19,154,36,70,7,117,103,128,216,211,45,213,82,97,156,126,250,216,206,204,8,150,92,117,228,21,131,30,10,
191,249,238,129,220,251,197,117,157,73,183,76,42,101,123,233,174,207,11,203,203,163,138,76,104,248,229,229,89,181,104,101,229,135,127,249,61,99,12,140,131,223,44,104,151,219,202,109,158,177,198,112,58,
30,8,222,113,157,147,174,183,188,195,216,218,3,121,117,110,28,130,227,48,169,85,189,74,227,229,249,162,29,113,116,12,62,190,137,142,83,133,104,42,212,23,0,0,32,0,73,68,65,84,202,154,102,114,81,193,233,
154,146,70,97,52,245,225,25,107,72,179,112,254,242,101,75,146,240,46,196,158,63,160,148,152,34,133,101,233,80,67,209,248,119,5,6,24,230,249,70,242,158,121,158,89,146,118,213,243,121,249,69,132,225,191,
13,76,151,34,10,183,240,14,235,20,204,124,87,159,24,99,217,143,110,67,82,27,163,203,158,209,27,69,54,56,75,24,2,230,48,109,173,191,63,190,223,209,142,3,84,193,253,199,191,239,19,70,205,12,119,198,110,
11,236,251,118,114,89,23,94,206,154,95,16,130,99,247,91,54,108,211,6,21,42,122,155,165,84,152,166,129,97,80,232,208,34,202,41,174,181,105,215,49,197,95,72,190,170,40,97,236,206,174,0,48,123,131,179,139,
110,161,0,191,18,48,206,209,140,144,194,208,195,19,128,220,136,1,162,209,107,181,221,67,69,140,197,29,70,144,138,9,174,159,225,158,97,55,190,122,150,68,116,190,155,132,253,94,107,108,107,44,185,213,95,
40,255,130,115,44,85,169,73,164,172,6,216,34,188,181,145,140,24,214,101,230,156,82,119,25,28,30,58,25,38,241,240,241,195,47,118,100,65,94,183,239,57,55,166,96,120,248,240,110,139,215,20,17,142,163,30,
129,173,86,230,250,42,41,32,56,198,41,246,20,226,178,209,62,198,93,36,211,184,188,204,92,206,23,14,251,189,126,146,49,50,77,142,227,191,193,230,76,147,99,56,232,255,31,113,248,95,13,239,213,170,110,13,
191,254,240,21,113,14,241,112,153,51,55,41,248,117,229,249,235,5,41,5,154,110,52,173,49,236,71,29,135,230,86,72,200,6,173,183,198,96,162,250,162,231,82,49,15,129,210,233,163,107,28,89,109,231,96,69,207,
16,39,37,142,26,75,244,122,62,47,34,236,93,96,138,158,38,141,221,251,129,211,206,232,164,105,17,252,229,242,164,36,164,86,184,253,235,247,212,110,117,176,94,167,51,151,156,201,173,232,139,16,160,229,172,
251,230,206,25,86,236,191,97,218,121,245,210,197,128,119,230,77,220,208,12,62,234,185,107,35,110,232,0,245,146,122,212,139,82,242,118,125,39,157,146,202,107,170,40,6,234,79,255,244,153,207,127,254,158,
60,175,236,156,199,255,229,241,19,146,10,166,193,143,159,126,224,48,169,35,246,116,58,113,124,152,88,14,142,219,44,125,72,45,84,119,135,181,116,218,232,105,82,61,143,115,111,114,233,10,181,85,138,52,92,
223,180,194,29,81,166,180,4,139,50,131,214,116,163,93,132,219,87,195,208,211,130,2,150,209,123,70,15,31,190,121,207,183,204,93,79,97,240,159,126,250,68,77,137,86,133,63,254,203,31,116,9,232,28,251,65,
245,187,165,163,123,31,142,19,31,63,188,227,112,216,17,125,64,146,50,217,158,150,180,1,98,115,15,159,94,250,181,13,48,26,229,190,175,139,108,172,158,56,57,13,251,181,2,85,253,204,49,122,246,251,9,83,65,
146,198,13,105,212,70,226,122,254,178,157,66,222,123,131,24,143,162,43,139,42,0,37,145,210,204,249,242,12,82,185,93,212,147,28,251,149,187,31,245,98,200,41,241,243,243,172,71,224,189,214,237,103,241,16,
61,49,68,102,215,37,93,169,109,224,207,97,12,140,131,193,5,253,189,151,203,210,177,213,81,229,97,171,70,22,185,6,45,9,143,63,124,34,83,113,199,136,63,189,127,135,164,149,134,240,241,187,15,26,81,209,23,
80,173,233,152,149,143,234,122,49,111,232,71,122,124,141,252,187,223,254,237,54,36,73,171,166,170,166,30,85,24,172,213,247,193,216,109,216,167,221,114,37,142,234,219,31,134,136,139,87,117,51,58,135,245,
130,31,39,130,209,159,116,104,142,211,52,65,108,216,201,225,247,227,14,187,223,65,109,156,191,213,99,237,126,158,106,230,134,103,233,83,117,233,134,188,184,155,52,85,10,64,134,109,52,251,246,43,24,189,
173,214,218,149,90,118,216,20,127,169,174,125,150,97,8,198,114,122,175,97,146,209,57,93,112,110,153,28,21,153,51,187,147,103,138,1,1,188,53,81,127,99,132,227,113,79,205,224,70,79,184,31,244,147,35,136,
232,82,38,58,124,240,236,39,117,14,92,175,51,101,25,113,193,108,25,183,155,111,16,85,180,238,123,152,131,181,170,8,168,173,98,138,210,160,135,16,88,115,198,182,14,213,194,130,53,140,83,216,96,50,178,100,
158,31,11,23,209,211,201,31,222,239,85,70,46,194,116,220,17,253,68,11,129,101,201,234,239,124,126,102,63,104,190,98,176,170,91,75,55,197,222,28,199,3,196,216,135,219,230,85,98,155,101,251,117,93,4,215,
55,70,89,68,249,64,15,251,142,118,18,118,135,137,161,200,70,48,13,188,174,11,106,171,140,251,129,195,104,57,95,102,94,206,55,252,224,20,210,233,164,112,43,129,249,154,200,117,38,140,35,239,227,200,233,
187,72,74,133,203,117,230,107,31,57,25,107,152,122,104,244,20,130,222,255,169,246,109,191,10,147,131,104,4,172,123,51,8,92,59,109,63,230,87,32,204,16,228,77,78,168,242,126,238,235,219,92,52,122,227,118,
89,72,89,105,163,254,143,255,237,247,61,30,107,199,46,101,118,195,200,218,135,119,7,103,56,167,134,203,149,40,10,145,39,64,116,253,180,216,13,152,97,100,93,83,87,243,233,167,234,157,193,154,87,253,188,
22,228,42,112,146,90,145,182,48,207,137,185,155,186,67,119,67,82,148,208,20,131,195,78,6,178,101,94,10,45,39,198,96,137,99,192,167,249,76,121,17,190,126,17,254,245,255,254,63,176,174,135,235,237,39,198,
195,72,205,250,124,233,55,56,109,66,34,130,35,221,60,226,45,107,201,164,44,4,251,10,121,219,18,181,151,87,163,125,110,13,113,175,227,0,253,217,175,136,179,164,172,220,214,53,21,38,167,25,29,198,88,126,
252,233,204,245,249,145,253,33,226,177,248,184,55,140,120,82,170,132,144,201,178,48,23,120,249,242,133,244,151,130,92,242,47,52,240,119,254,228,29,69,178,72,101,237,89,162,119,216,242,61,9,248,238,145,
187,255,90,232,176,206,96,212,57,54,69,44,233,21,42,190,100,156,52,134,49,178,223,13,140,33,112,190,38,158,31,191,240,236,213,224,237,247,239,31,8,128,228,204,241,155,61,75,41,170,230,239,178,238,118,
214,161,115,112,94,51,236,86,213,242,44,253,155,62,225,54,226,193,93,113,85,68,182,33,181,123,51,99,72,29,64,32,100,198,30,80,182,63,28,250,240,165,15,178,165,50,98,213,57,30,28,223,126,123,226,113,234,
185,185,214,226,19,174,179,170,65,194,158,44,11,95,115,35,116,187,238,248,113,175,237,78,159,128,187,90,153,90,195,165,204,124,91,249,102,119,66,58,192,37,244,219,174,202,235,4,63,224,153,111,137,185,
204,56,17,166,123,98,246,33,48,141,81,71,85,249,149,28,13,144,86,213,90,140,24,196,131,71,147,82,170,53,248,154,227,6,203,140,135,15,12,135,215,79,107,28,35,207,117,38,1,203,154,245,71,22,28,251,221,68,
29,6,106,140,148,60,81,93,165,25,69,119,56,227,72,189,134,142,46,224,99,192,199,133,33,77,68,175,138,45,122,125,178,24,203,156,61,203,172,82,242,97,24,113,193,81,234,66,174,194,205,90,174,47,23,100,233,
199,101,169,248,119,227,78,97,24,177,145,142,39,158,175,51,169,101,24,71,114,12,156,146,194,145,31,6,184,201,172,90,120,60,183,117,38,154,61,102,156,152,188,50,172,238,105,83,247,174,35,21,33,186,61,54,
102,166,110,179,124,219,74,149,238,174,153,166,93,55,13,54,198,224,241,239,143,219,239,249,112,122,207,151,79,190,155,194,13,126,152,14,4,3,38,90,190,59,189,39,250,200,82,192,70,167,171,43,95,40,69,69,
115,98,26,62,70,198,253,68,156,30,152,166,129,148,244,27,8,65,21,215,181,199,92,165,38,136,203,204,100,76,188,163,114,114,199,20,55,138,213,141,245,109,93,24,194,160,100,244,57,243,248,116,86,119,206,
56,176,219,141,252,116,190,240,244,245,89,21,48,209,224,111,215,11,222,58,194,234,120,122,186,114,238,161,55,174,90,160,112,149,220,179,149,247,28,118,239,56,30,39,166,105,68,74,159,244,192,47,78,133,
218,55,64,213,24,36,25,78,239,38,130,103,131,208,231,34,224,100,227,26,127,244,191,237,237,144,108,245,244,214,185,88,199,175,243,141,175,223,30,152,215,5,155,11,254,124,121,193,89,85,86,95,46,207,88,
224,112,152,216,31,13,222,68,62,125,93,240,193,50,26,69,64,69,73,200,69,107,225,165,20,240,195,107,193,211,187,144,120,247,125,68,8,185,96,170,193,90,61,250,92,111,241,173,47,80,12,151,154,184,206,179,
70,117,239,39,14,187,161,39,248,36,230,180,178,159,38,222,1,199,24,16,239,241,46,232,117,123,189,172,252,240,167,127,38,165,76,112,81,231,1,2,255,254,119,191,38,93,133,231,53,177,44,10,49,26,99,192,71,
205,168,45,125,17,88,91,237,210,23,135,31,34,251,113,32,120,143,111,241,77,13,215,40,89,71,86,235,86,164,67,78,61,90,104,201,156,127,238,121,72,93,111,252,149,39,118,44,156,142,15,140,222,227,199,157,
71,230,76,30,225,97,231,152,141,16,157,234,45,93,128,127,254,127,127,191,229,120,221,109,11,15,187,137,211,241,160,115,178,224,58,207,50,245,120,182,74,28,3,207,62,50,14,158,211,225,35,34,122,19,86,202,
47,74,208,214,50,151,91,63,210,222,204,39,238,22,181,224,28,215,107,129,219,153,232,28,107,45,248,156,26,82,42,146,27,222,13,60,76,202,187,28,205,235,112,228,126,19,13,62,246,31,189,195,71,207,124,93,
73,203,178,201,187,0,82,17,174,231,2,204,60,3,79,246,89,57,195,37,83,121,237,172,95,43,187,229,151,17,113,221,67,125,207,168,43,75,229,229,249,177,95,44,130,7,71,205,190,75,17,149,64,35,75,87,124,151,
198,112,60,32,162,225,165,183,166,99,82,83,44,49,71,94,46,87,190,57,30,25,71,191,29,105,181,169,210,111,153,181,243,16,73,88,235,120,232,79,134,50,47,139,142,189,114,193,239,61,187,105,32,122,143,180,
246,122,197,223,81,235,5,124,92,181,216,215,4,172,29,50,57,104,19,178,87,184,113,140,158,28,53,119,227,93,29,181,192,127,232,109,123,90,40,69,56,76,19,239,223,21,204,206,19,172,229,114,157,185,190,44,
26,31,212,165,96,99,244,76,236,25,220,61,216,204,16,166,134,45,194,248,94,87,129,71,116,202,57,134,160,81,25,176,61,191,33,58,174,84,218,199,175,175,194,189,212,44,89,84,85,250,151,47,87,156,181,188,123,
63,241,237,225,129,211,113,128,170,130,187,37,21,221,77,56,139,147,10,83,164,38,21,192,101,189,121,104,174,167,175,85,205,213,152,14,3,127,115,152,182,14,36,88,139,49,150,135,55,252,136,151,160,152,222,
139,232,81,231,123,183,99,172,65,172,37,92,133,236,214,173,206,246,199,211,59,102,191,66,138,252,205,119,191,98,8,150,227,97,226,216,11,239,31,251,142,204,58,71,56,12,76,70,219,242,212,42,115,107,132,
42,196,224,136,251,137,95,157,14,91,163,122,127,86,151,166,90,9,90,35,27,213,242,236,186,231,217,24,75,14,21,137,133,57,37,150,37,35,115,209,125,201,224,149,178,107,116,17,217,188,122,75,188,113,123,134,
73,61,247,242,237,119,60,140,129,33,86,34,22,105,153,223,126,252,192,229,186,246,48,39,125,89,246,59,157,228,28,246,194,249,252,252,106,28,112,129,113,63,109,113,21,173,85,230,162,87,203,208,255,33,86,
165,63,91,214,184,251,105,97,140,129,147,241,204,171,70,107,132,96,216,163,143,72,222,25,30,215,43,203,165,144,90,195,31,99,164,70,40,121,225,75,17,190,124,250,74,150,149,209,120,166,189,195,184,27,73,
244,121,28,167,17,68,168,139,98,75,169,141,227,238,184,237,220,162,87,41,151,178,133,21,169,186,116,173,229,28,192,38,117,130,165,84,144,69,101,57,167,5,30,38,125,20,236,98,105,169,112,189,36,210,185,
39,188,15,112,254,233,66,162,49,190,8,62,93,191,168,197,114,41,4,121,97,60,56,106,29,21,127,94,43,225,122,101,189,205,20,103,152,123,0,239,16,2,195,224,217,143,145,212,189,81,222,84,230,121,225,241,233,
133,235,109,217,174,218,225,48,105,92,102,113,106,101,202,186,22,115,206,48,6,45,51,137,30,134,200,206,59,166,190,73,74,73,16,41,184,82,217,253,202,178,155,84,45,232,175,63,255,85,117,148,181,145,47,79,
156,62,124,192,69,199,109,209,46,215,77,48,96,120,216,107,180,80,17,165,207,188,92,207,188,204,32,215,85,93,97,91,173,144,57,250,200,233,180,103,154,6,142,15,7,229,4,190,105,139,234,214,251,169,48,245,
23,220,214,36,204,41,17,179,66,242,221,146,144,116,65,114,226,182,94,241,235,211,143,234,168,149,202,167,223,127,207,167,63,254,5,59,77,60,28,143,124,252,155,247,72,91,88,229,6,75,33,163,78,196,117,205,
156,111,250,108,202,69,77,254,223,126,56,241,241,187,19,99,119,208,182,218,184,204,11,151,207,47,250,201,74,69,92,87,53,128,218,47,234,47,243,11,238,160,91,165,218,193,52,68,86,10,50,159,53,113,97,77,
248,37,223,212,86,85,133,117,62,179,20,71,125,190,240,242,244,194,143,63,124,98,232,155,163,181,100,166,56,176,59,12,140,62,242,221,113,162,74,227,241,154,248,120,60,113,116,144,158,190,242,60,167,46,
25,211,125,115,196,32,29,212,217,44,56,239,153,83,102,105,153,232,35,83,135,207,133,224,24,141,97,114,194,241,110,193,115,106,82,73,82,153,162,99,124,136,248,37,169,125,166,97,32,58,198,224,40,88,210,
188,48,215,202,215,178,110,145,221,222,191,170,169,135,168,243,136,21,199,240,67,196,25,67,41,106,220,59,76,35,161,27,61,191,123,56,110,117,66,118,170,66,201,89,57,44,97,23,121,17,221,24,165,62,53,93,
115,230,122,89,89,55,74,180,231,250,252,5,151,133,86,18,158,253,158,57,45,200,124,227,203,227,141,97,140,60,76,3,15,167,177,243,210,84,94,56,39,157,40,106,218,142,74,189,70,92,207,149,209,166,243,50,175,
148,69,248,122,125,222,38,61,159,122,248,199,182,12,183,6,211,169,207,99,240,248,224,126,177,132,17,169,44,61,221,253,190,105,154,191,62,233,174,197,130,119,113,34,136,161,249,134,25,85,89,82,106,226,
218,243,231,167,56,169,90,187,214,95,152,165,167,24,21,68,184,190,176,59,68,172,49,92,247,150,151,235,204,210,83,81,196,54,82,127,161,141,84,156,88,34,174,231,128,130,147,204,20,98,71,142,72,23,59,27,
70,111,183,160,95,235,26,75,179,16,6,130,105,248,232,12,227,62,80,167,7,126,247,119,223,97,165,176,92,22,174,203,149,185,11,145,238,159,236,221,77,139,71,185,37,2,82,11,235,178,244,83,34,99,108,101,156,
28,67,24,54,39,173,136,50,133,163,53,138,224,177,238,77,100,70,237,221,246,47,35,194,165,233,223,23,99,100,49,6,41,137,185,52,124,112,22,219,235,180,211,56,169,92,208,40,251,111,63,38,174,75,166,137,78,
116,108,51,10,54,156,133,203,165,112,118,11,78,214,205,43,247,26,52,109,184,117,83,94,8,110,139,190,202,24,110,174,97,239,216,189,91,194,143,97,115,71,190,141,52,170,85,165,202,159,175,23,110,95,18,67,
208,242,192,203,229,138,84,197,172,204,215,249,142,88,211,35,38,87,118,49,146,91,211,96,188,84,136,81,31,143,203,101,213,173,61,59,157,73,244,221,155,125,147,103,84,155,46,11,189,85,64,167,74,20,101,11,
144,174,99,225,130,186,121,37,215,45,171,217,57,199,48,122,108,180,28,79,3,206,61,50,70,8,83,192,59,172,242,44,211,194,237,249,138,139,1,19,29,195,52,17,135,17,35,16,91,213,249,130,145,237,57,182,220,
17,77,97,139,202,220,118,116,247,23,202,59,108,209,83,96,191,159,72,84,174,203,186,113,169,74,41,8,21,231,181,142,158,251,179,239,189,83,241,136,49,60,236,142,124,13,129,92,133,128,224,101,52,72,52,20,
7,47,78,40,41,225,178,18,58,212,118,54,18,194,64,115,1,55,152,254,164,57,118,247,208,178,156,54,69,107,173,21,82,98,93,11,226,45,110,116,36,211,88,90,229,86,53,91,134,56,112,45,9,153,5,48,138,252,203,
104,110,130,168,147,81,63,115,69,54,172,121,33,147,53,154,25,193,75,105,106,108,105,14,235,6,70,15,195,232,153,226,200,126,26,200,233,149,5,225,250,2,187,245,103,89,164,169,181,237,30,75,100,12,177,19,
7,154,232,28,109,220,143,40,250,202,116,180,78,96,103,38,172,83,8,115,234,76,20,143,108,65,104,10,250,84,183,193,245,182,48,14,158,138,231,20,29,126,127,220,147,211,202,21,129,46,216,44,179,230,144,20,
17,140,137,189,187,189,7,50,196,141,157,226,130,219,34,55,141,211,249,109,240,35,176,223,178,10,238,248,62,221,52,141,4,103,84,71,95,173,238,175,115,3,151,53,243,177,39,10,138,100,164,233,123,177,223,
69,100,209,32,158,210,42,254,154,50,121,73,186,30,72,89,63,173,92,73,2,193,11,142,204,126,63,177,123,216,51,198,62,51,72,10,16,42,85,168,253,33,177,88,214,172,215,232,125,48,232,120,229,3,57,175,105,108,
206,24,114,40,144,5,67,99,242,142,82,52,65,109,153,19,105,94,144,156,222,52,165,112,126,254,66,90,11,45,131,71,12,46,140,4,31,248,237,63,252,59,156,49,155,148,101,140,145,121,153,149,204,85,96,185,143,
85,7,79,32,224,172,225,186,168,227,49,56,61,91,151,148,41,173,33,98,136,214,113,251,122,83,159,127,171,228,174,126,109,61,251,46,68,135,17,182,209,108,110,137,48,56,246,195,94,141,83,193,169,207,47,168,
9,177,229,138,119,211,14,39,186,150,197,121,146,8,151,231,89,53,18,89,237,190,69,212,50,236,156,103,26,35,150,192,178,206,228,82,216,251,72,219,197,141,250,220,250,81,6,176,182,198,238,221,78,11,250,214,
216,25,131,184,242,11,103,248,219,4,120,136,219,98,210,55,181,127,141,193,35,206,145,164,146,165,161,218,37,11,214,56,205,127,201,142,113,31,186,100,86,47,3,41,113,3,199,227,35,62,6,78,15,147,98,205,214,
194,232,61,206,105,152,175,137,14,91,95,207,226,175,79,243,118,182,250,201,162,175,87,210,90,247,62,107,3,90,45,144,171,230,121,136,108,17,157,83,176,156,31,159,40,73,131,31,188,238,195,42,150,166,33,
209,83,143,28,236,102,234,44,66,12,170,250,203,93,120,191,174,185,23,39,142,253,176,235,179,219,194,188,200,214,176,222,35,218,62,124,24,53,241,199,128,179,93,16,237,84,79,239,156,99,104,185,95,211,22,
27,97,104,21,76,123,213,6,93,110,180,201,195,52,244,151,183,86,210,154,184,213,133,231,167,103,45,106,162,35,53,168,85,152,66,236,46,173,220,49,33,55,214,89,227,55,141,117,140,226,126,145,3,22,189,174,
2,164,227,81,47,164,77,150,35,206,192,170,18,153,41,40,152,89,154,14,111,98,84,207,126,234,167,84,158,245,214,179,199,1,201,129,72,192,91,131,167,7,63,239,172,231,1,67,41,25,145,140,239,45,207,229,54,
255,226,104,154,130,195,217,200,238,254,208,206,149,86,45,19,225,245,248,218,174,231,215,92,163,74,197,206,61,205,85,10,53,43,90,50,173,90,74,186,78,244,208,98,41,97,91,211,156,187,36,212,91,69,124,69,
138,197,231,121,166,81,160,20,214,219,170,85,199,155,173,212,237,124,217,148,123,49,6,134,113,216,152,193,82,27,41,251,55,61,153,85,43,164,119,219,246,104,190,200,47,226,87,92,39,209,220,181,198,173,9,
38,183,14,155,237,164,143,82,59,96,192,82,74,34,93,87,174,101,101,78,9,47,37,147,115,134,156,72,183,89,35,50,239,236,212,156,217,121,161,20,29,223,155,164,218,225,187,121,83,90,163,153,168,147,161,165,
32,165,116,134,196,235,151,183,113,227,97,190,158,173,150,188,40,8,99,226,77,26,85,31,60,134,59,133,166,85,30,134,61,49,14,152,209,178,74,196,95,94,174,200,170,241,66,95,254,250,51,209,56,98,80,61,143,
72,67,218,172,122,224,218,182,55,218,154,59,246,31,190,244,154,249,94,165,121,239,54,153,98,240,78,87,3,217,192,12,206,121,198,232,117,87,84,180,110,153,251,230,168,214,134,21,165,58,95,165,110,51,186,
121,183,114,251,250,164,216,15,111,241,181,129,31,28,164,208,157,222,9,46,69,83,205,140,101,201,149,16,20,2,37,85,165,96,209,91,188,213,117,235,199,24,183,178,242,109,92,230,22,133,85,213,235,52,247,163,
170,18,81,115,91,195,59,148,18,141,50,132,192,42,109,28,161,54,165,155,26,103,88,215,149,229,34,52,91,241,211,97,66,16,66,104,28,223,29,89,214,2,85,136,77,63,181,72,83,71,204,157,249,112,71,146,222,165,
226,37,109,170,190,123,132,64,145,162,12,152,142,24,105,73,176,125,160,53,167,212,195,162,181,32,10,157,38,170,252,86,181,236,236,245,122,160,214,198,188,38,134,131,99,114,145,104,13,254,227,199,239,40,
146,48,85,112,191,251,237,6,205,108,69,11,245,243,188,254,98,85,213,36,111,67,19,169,13,215,193,66,210,43,45,41,108,138,66,231,192,148,138,11,142,9,69,161,213,218,152,187,172,55,58,199,195,7,157,227,150,
37,179,172,153,150,117,245,16,251,171,48,238,60,54,15,44,101,230,233,186,226,167,221,81,165,155,107,102,157,62,144,203,170,64,128,208,5,247,241,70,24,3,222,88,173,150,140,101,77,26,120,110,140,37,68,112,
93,66,171,121,180,203,86,196,27,107,57,30,226,86,59,220,255,209,215,190,253,215,1,247,235,233,112,216,31,249,216,11,166,232,251,18,94,132,159,194,39,74,90,121,255,65,240,151,151,133,86,21,161,247,50,191,
242,220,197,106,154,137,196,1,107,20,183,231,98,196,121,207,110,2,87,246,253,124,77,154,65,107,149,29,31,93,192,221,69,249,198,50,29,39,45,168,66,84,0,114,23,80,223,95,96,153,21,167,158,68,168,89,19,0,
27,89,133,163,214,96,165,64,89,88,215,196,52,142,248,176,27,161,5,16,97,127,58,110,152,133,251,228,230,122,77,10,70,150,138,73,48,141,119,229,170,233,144,216,110,241,189,231,120,132,218,145,35,6,235,28,
79,151,181,127,226,43,225,203,229,85,134,208,63,225,227,184,187,7,127,210,170,102,64,167,62,147,190,155,0,158,179,178,127,78,167,35,126,190,93,185,67,216,207,77,231,194,214,56,194,20,169,173,114,220,29,
180,35,78,119,252,152,221,192,113,17,120,185,93,113,213,98,58,41,188,245,137,189,171,218,139,15,195,129,214,163,14,183,196,85,42,249,46,9,93,138,70,131,59,133,112,41,83,194,17,156,37,140,154,166,125,60,
61,104,16,117,28,241,254,48,118,74,166,198,4,229,166,174,44,135,186,183,191,94,214,55,32,161,218,143,154,206,75,51,134,211,233,240,58,75,232,153,70,230,109,122,2,234,64,48,222,48,238,226,246,172,175,139,
150,172,244,196,160,67,244,61,128,90,237,149,131,81,145,199,124,189,33,50,51,47,137,249,114,195,187,90,21,160,41,109,131,199,187,193,97,123,11,228,150,180,237,145,245,37,17,66,208,200,120,107,44,83,120,
61,130,74,84,105,194,219,149,65,12,110,187,253,220,157,216,191,84,134,81,255,123,158,235,150,238,238,222,52,180,55,132,219,154,24,238,63,136,57,33,100,188,52,213,229,82,27,107,90,48,62,106,93,1,180,148,
120,183,143,93,125,210,231,10,190,252,226,27,169,111,218,25,58,213,217,119,200,156,115,202,148,40,61,236,244,78,83,170,85,145,125,147,247,136,75,122,210,180,70,205,130,139,175,250,181,148,132,233,24,137,
118,34,78,186,50,243,159,254,242,51,85,50,56,248,250,244,200,225,116,98,103,45,169,234,50,209,25,165,217,101,121,147,25,142,37,85,33,167,130,91,58,144,168,201,22,175,233,186,134,205,24,167,112,218,166,
32,251,109,153,216,221,8,98,28,243,124,65,122,100,103,171,153,177,69,252,126,234,224,152,194,227,227,13,155,111,172,37,177,166,130,63,126,60,49,116,202,253,180,124,208,78,128,132,107,221,224,55,43,140,
232,158,63,107,205,43,73,201,88,29,132,143,62,16,129,212,4,155,149,112,176,80,85,194,0,140,33,128,119,100,169,56,19,8,206,144,13,228,86,152,92,0,43,196,104,136,113,34,93,18,127,250,252,61,151,203,170,
30,168,208,144,155,162,215,141,11,248,29,6,215,64,150,132,220,102,74,206,36,113,164,146,122,39,80,85,159,19,213,186,62,14,81,91,152,85,71,1,139,17,106,94,185,137,234,46,239,22,203,235,154,105,14,188,192,
220,5,32,134,128,115,158,48,233,79,203,210,217,41,173,34,178,50,207,112,205,43,11,5,19,50,206,169,127,218,197,169,95,58,5,255,244,248,19,84,33,56,195,237,203,147,102,40,183,170,37,97,119,88,151,148,56,
63,95,120,238,55,214,61,219,22,32,12,10,51,148,148,148,147,61,12,58,38,21,97,185,37,6,212,128,186,56,219,227,140,70,66,245,200,61,174,126,168,125,254,172,127,230,154,10,41,47,250,33,26,135,44,103,66,213,
24,186,146,4,111,139,16,80,58,71,190,222,116,47,49,235,110,55,186,200,117,185,82,138,178,124,118,187,145,135,190,217,180,61,163,139,75,2,103,48,107,193,229,66,156,50,227,97,66,74,34,204,137,194,204,250,
166,55,158,205,11,95,221,235,240,218,141,189,240,33,227,114,239,152,173,193,121,85,81,201,117,225,242,252,200,245,101,161,214,134,151,94,228,180,166,56,156,92,4,211,153,151,73,132,111,222,31,55,50,151,
31,35,251,24,55,137,0,234,204,212,156,175,21,46,82,144,91,98,153,11,171,100,46,107,34,78,30,156,146,147,226,208,213,130,238,213,114,97,59,56,78,128,82,250,214,177,27,239,231,214,216,27,168,207,11,245,
178,18,162,199,127,247,171,239,244,25,202,5,247,143,191,37,132,145,33,122,82,127,121,238,76,246,180,190,73,17,206,162,196,37,96,170,153,193,58,86,147,104,46,98,140,114,37,124,46,28,194,200,143,151,43,
214,9,126,242,236,164,233,64,176,83,116,157,49,188,155,116,38,61,177,211,162,63,188,38,9,2,24,17,78,211,196,210,223,15,111,246,15,4,84,135,198,120,0,31,112,123,141,175,98,92,136,209,50,77,211,86,235,106,
39,82,52,120,47,235,8,212,96,24,165,49,136,26,168,173,53,202,65,113,240,63,127,56,109,181,47,85,243,57,206,235,218,43,56,7,73,125,72,14,209,33,141,177,250,188,230,132,239,36,178,241,223,189,211,250,67,
42,126,149,66,244,158,234,29,215,106,41,115,226,64,15,131,140,145,75,78,16,107,207,180,191,209,250,55,21,166,200,120,240,8,130,6,12,55,38,227,25,199,72,13,22,35,85,151,134,205,108,192,194,76,99,193,145,
196,176,96,137,88,230,10,115,79,225,222,91,193,152,6,162,82,96,231,42,38,103,246,78,148,28,189,36,188,247,7,76,116,184,150,120,255,205,7,141,90,129,13,143,32,56,126,122,94,123,128,186,161,86,75,146,138,
79,134,86,87,36,233,122,118,28,61,140,99,79,161,48,184,33,48,207,11,79,231,27,118,212,217,219,74,37,89,8,211,72,52,138,201,217,157,190,217,114,29,143,251,29,209,59,110,243,140,119,150,105,63,177,94,159,
89,230,103,130,8,251,111,29,30,107,250,92,182,146,114,222,138,237,214,199,77,49,132,215,155,235,190,145,55,6,239,172,234,134,51,175,157,196,162,89,51,68,195,110,215,212,56,178,223,225,71,135,141,177,199,
56,240,186,45,50,158,107,42,138,250,237,187,63,168,28,220,180,157,43,49,122,68,28,41,87,130,51,120,169,170,58,21,105,10,132,27,35,225,222,197,246,96,231,181,164,215,33,199,27,115,83,22,193,118,60,201,
146,50,130,14,74,98,12,156,142,59,172,115,26,145,145,2,184,149,220,107,237,80,33,90,195,197,59,172,176,213,37,95,175,87,53,101,249,215,212,97,124,229,118,190,146,250,204,218,235,168,212,104,132,235,24,
9,198,82,69,235,87,1,214,181,15,231,238,223,100,18,213,194,59,71,176,134,93,79,53,118,34,92,36,179,206,23,174,23,33,173,163,62,239,187,7,46,147,87,20,148,209,91,109,50,122,26,56,44,147,143,228,160,131,
237,165,204,132,92,145,112,79,207,110,154,163,148,109,159,89,11,254,235,227,79,56,231,241,181,49,63,61,119,165,159,58,174,130,181,72,79,74,181,189,237,119,221,59,63,6,253,117,104,32,6,194,49,114,34,242,
110,10,136,52,246,221,95,42,89,48,99,208,220,231,62,64,140,209,49,186,72,236,241,112,34,10,71,28,189,161,58,11,169,208,100,214,232,140,199,89,151,227,85,216,1,254,203,15,127,101,24,35,13,225,243,159,254,
140,189,51,168,186,176,243,30,219,22,131,39,246,91,41,36,71,235,63,55,211,35,224,164,214,13,110,223,164,81,221,132,181,142,83,156,176,166,178,116,9,175,136,96,147,3,183,146,114,69,36,105,132,17,104,204,
92,75,156,47,179,38,172,1,7,239,113,233,5,177,112,91,5,255,48,105,24,105,74,137,117,190,18,77,211,88,148,62,88,78,69,135,25,113,55,189,134,35,56,131,20,93,198,248,172,68,253,140,26,2,115,238,12,204,94,
237,93,23,193,142,58,144,158,151,164,137,151,214,97,170,208,146,240,124,155,187,244,171,113,218,77,248,224,72,75,33,149,5,43,149,167,44,180,117,102,240,14,156,197,143,99,160,73,70,82,99,16,33,14,150,120,
119,128,183,202,131,243,72,21,162,107,80,245,5,92,123,3,153,139,16,114,214,158,79,4,156,227,214,1,244,33,56,50,149,125,215,207,55,103,182,155,50,58,215,43,196,162,97,234,89,72,82,41,151,171,66,53,68,35,
235,115,17,190,9,30,210,76,233,6,88,255,241,253,129,44,153,135,105,162,252,238,55,212,236,32,232,90,64,178,176,27,95,253,157,185,53,98,46,148,162,194,79,145,70,168,23,226,224,123,166,184,116,247,64,210,
206,215,170,64,223,24,195,24,220,38,73,119,62,178,15,147,222,207,181,112,93,23,189,158,199,97,251,176,238,93,206,228,61,97,125,225,235,121,1,73,248,107,174,4,27,113,163,227,248,112,162,54,112,46,18,221,
216,173,185,162,221,68,143,76,249,255,125,181,147,30,129,61,13,254,227,183,218,89,36,81,239,197,215,151,139,70,197,246,230,108,93,11,214,120,28,177,39,174,69,166,146,200,181,49,6,221,50,109,114,116,239,
56,238,71,242,147,131,252,149,245,42,248,53,1,209,50,78,145,211,55,31,213,65,144,132,37,45,26,96,218,231,182,111,207,223,59,167,245,222,159,221,23,139,227,104,122,74,176,83,172,83,169,248,221,145,4,36,
138,190,23,62,48,196,17,23,60,38,237,33,66,100,207,212,163,18,1,174,183,89,149,87,192,249,233,70,157,19,45,236,224,221,132,119,251,3,107,46,220,158,103,254,250,195,79,56,201,202,183,110,153,146,51,57,
68,130,243,93,35,225,137,49,16,70,245,47,25,107,184,220,192,6,61,85,106,171,164,37,49,167,110,187,52,30,39,186,6,144,126,213,71,31,193,122,172,223,107,32,232,72,55,111,123,252,168,33,125,206,70,220,210,
125,164,59,184,62,175,164,85,67,127,61,181,105,156,74,63,158,130,115,76,163,101,52,158,218,70,46,219,99,160,254,207,188,22,66,90,184,89,197,238,10,123,92,115,184,88,201,73,88,146,210,192,172,179,132,96,
248,240,225,164,19,157,117,238,62,105,71,136,3,189,15,37,37,5,185,156,111,13,249,34,219,80,49,116,82,105,17,225,241,211,149,219,117,165,185,140,63,191,60,17,189,35,196,198,126,111,20,52,216,52,46,165,
75,169,187,192,163,34,169,207,221,156,78,117,162,115,204,233,172,5,253,147,86,87,86,21,168,219,196,243,241,233,231,126,117,223,40,69,24,134,64,76,147,238,218,112,188,92,206,155,96,250,117,158,97,113,68,
26,202,33,204,233,194,24,52,41,197,159,38,213,186,107,174,235,194,154,103,53,125,56,167,245,106,93,212,211,169,145,49,24,171,232,17,69,70,54,222,239,180,184,94,186,21,194,218,138,161,34,233,133,146,187,
54,194,26,40,51,178,36,230,108,89,237,85,27,82,99,168,183,212,81,168,218,232,42,227,205,245,16,85,195,57,39,24,44,46,104,254,150,47,233,170,11,196,188,178,44,47,219,18,112,105,66,186,194,216,148,93,109,
58,121,153,38,122,67,37,93,100,103,121,234,144,121,157,156,91,163,169,18,215,101,33,165,149,156,133,253,97,34,6,45,226,135,208,229,189,53,99,109,96,156,180,20,16,41,44,151,43,215,94,168,223,243,57,98,
112,60,126,253,194,113,208,52,88,255,244,253,159,168,70,177,221,47,159,31,17,231,137,195,136,27,6,205,66,58,12,90,237,47,154,65,55,142,134,37,53,37,129,90,195,187,116,31,77,89,205,162,89,11,243,186,16,
103,229,97,71,111,137,47,137,24,61,206,131,91,102,48,11,33,168,32,239,114,85,22,75,147,215,240,133,59,229,217,2,229,218,224,233,204,179,8,79,231,21,63,28,14,42,65,76,5,105,112,123,89,249,249,235,141,123,
186,93,225,117,24,61,14,158,49,116,163,105,47,186,151,201,252,114,237,213,11,158,165,10,98,32,149,204,44,11,46,189,254,62,169,101,123,102,119,211,158,232,29,195,62,178,139,3,225,62,18,235,222,189,116,
41,92,46,51,102,108,24,50,94,247,108,2,206,18,253,1,179,19,118,73,148,111,214,132,151,107,210,192,93,99,240,85,129,224,182,128,235,239,100,179,188,46,186,141,81,37,75,244,184,201,83,91,219,114,156,149,
191,198,102,64,185,23,242,79,95,95,200,89,248,122,153,183,222,207,59,135,247,10,131,201,6,126,74,43,114,206,212,4,254,227,119,191,214,115,114,185,50,191,59,65,202,4,211,195,25,29,140,211,97,43,132,204,
27,27,101,221,192,243,137,240,198,11,154,251,229,18,172,46,106,230,121,237,19,201,140,243,65,115,68,141,5,171,150,228,223,252,131,219,214,106,111,191,242,61,14,195,57,118,118,1,105,236,48,248,132,114,
128,25,71,166,195,17,106,86,123,152,160,231,108,127,185,106,39,111,228,86,53,62,165,127,143,227,254,195,54,125,207,69,207,212,96,141,38,71,77,145,119,39,72,45,81,179,78,244,77,247,130,138,104,113,179,
32,4,111,54,253,132,62,82,149,92,20,26,58,250,1,23,143,212,101,166,57,135,15,163,238,209,92,245,196,41,98,69,147,214,23,17,100,21,108,214,201,206,208,213,86,163,213,136,160,123,72,227,247,143,23,93,38,
246,132,181,82,84,201,125,112,142,220,28,181,119,10,82,242,22,112,195,155,28,59,150,202,165,203,35,183,0,28,115,55,18,26,158,47,55,126,252,124,37,149,149,17,193,171,253,6,82,73,204,85,221,178,227,116,
208,152,120,60,243,139,30,252,182,63,147,41,11,75,104,180,156,184,74,97,216,25,149,47,88,101,5,185,168,226,58,235,148,26,61,119,67,202,86,208,184,87,45,102,232,91,254,77,226,241,230,209,186,135,58,77,
251,200,244,223,127,67,52,6,235,192,134,54,73,245,0,0,1,184,73,68,65,84,47,203,5,193,170,67,118,239,8,98,152,83,226,233,172,76,225,135,125,143,35,76,104,0,36,85,1,26,49,64,134,209,182,109,212,229,250,
174,216,218,134,200,202,37,87,240,186,210,186,135,83,75,207,166,185,127,237,179,127,61,206,172,221,202,81,213,134,106,222,221,255,215,211,25,237,198,17,194,80,244,128,135,73,182,170,212,254,255,175,245,
53,170,84,41,109,180,219,201,194,24,108,242,96,118,255,0,241,96,140,175,239,61,211,14,42,198,253,104,108,250,126,139,164,163,156,185,253,57,158,235,94,133,201,15,73,120,139,253,72,45,13,238,64,31,212,
107,204,199,84,97,176,56,95,36,132,252,116,43,246,165,12,69,110,183,179,175,217,178,72,14,100,253,162,5,55,143,138,209,22,8,231,209,63,60,34,129,19,198,239,95,111,207,64,241,237,250,239,47,158,133,145,
132,253,245,39,34,153,45,193,94,2,94,170,189,33,119,37,123,6,78,110,106,24,202,144,200,168,12,118,243,42,105,140,167,74,52,84,169,102,180,227,127,140,102,221,33,199,94,231,54,39,163,42,163,119,174,181,
34,133,112,231,174,15,67,72,197,193,3,51,139,115,144,183,64,42,99,29,153,70,217,86,122,126,83,142,250,201,249,113,208,206,26,128,154,233,188,18,142,129,211,43,99,10,89,4,179,232,43,182,181,187,89,214,
8,213,53,124,120,15,2,15,26,116,86,215,74,215,184,169,107,211,16,120,242,36,237,112,126,40,170,78,21,184,92,4,207,75,167,14,2,12,86,161,37,216,46,133,133,170,24,36,51,246,169,209,236,124,75,236,229,5,
218,65,74,1,209,43,162,88,111,48,4,151,18,162,162,43,140,21,153,254,25,162,96,159,17,241,155,128,50,119,124,156,248,48,148,30,201,10,234,148,126,50,239,61,158,107,95,116,170,1,47,2,114,26,201,97,40,200,
119,232,7,44,219,7,95,95,112,177,128,226,110,207,85,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* MrAlias2Editor::wood2_png = (const char*) resource_MrAlias2Editor_wood2_png;
const int MrAlias2Editor::wood2_pngSize = 41625;
