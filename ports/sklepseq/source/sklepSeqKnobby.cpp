/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 Jul 2008 9:28:32 pm

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
//[/Headers]

#include "sklepSeqKnobby.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sklepSeqKnobby::sklepSeqKnobby ()
    : slider (0),
      slider2 (0),
      slider3 (0),
      slider4 (0),
      slider5 (0),
      slider6 (0),
      slider7 (0),
      slider8 (0),
      slider25 (0),
      slider26 (0),
      slider27 (0),
      slider28 (0),
      slider9 (0),
      slider10 (0),
      slider11 (0),
      slider12 (0),
      slider13 (0),
      slider14 (0),
      slider15 (0),
      slider16 (0),
      slider17 (0),
      slider18 (0),
      slider19 (0),
      slider20 (0),
      slider21 (0),
      slider22 (0),
      slider23 (0),
      slider24 (0),
      slider29 (0),
      slider30 (0),
      slider31 (0),
      slider32 (0),
      slider33 (0),
      slider34 (0),
      slider35 (0),
      slider36 (0),
      slider37 (0),
      slider38 (0),
      slider39 (0),
      slider40 (0),
      slider41 (0),
      slider42 (0),
      groupComponent (0),
      groupComponent2 (0),
      groupComponent3 (0)
{
    addAndMakeVisible (slider = new Slider ("new slider 1"));
    slider->setRange (1, 256, 1);
    slider->setSliderStyle (Slider::RotaryVerticalDrag);
    slider->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7ffc9fff));
    slider->setColour (Slider::rotarySliderOutlineColourId, Colours::red);
    slider->setColour (Slider::textBoxTextColourId, Colours::black);
    slider->addListener (this);

    addAndMakeVisible (slider2 = new Slider ("new slider 2"));
    slider2->setRange (1, 256, 1);
    slider2->setSliderStyle (Slider::RotaryVerticalDrag);
    slider2->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider2->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ffeb));
    slider2->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc2d83b));
    slider2->setColour (Slider::textBoxTextColourId, Colours::black);
    slider2->addListener (this);

    addAndMakeVisible (slider3 = new Slider ("new slider 3"));
    slider3->setRange (1, 256, 1);
    slider3->setSliderStyle (Slider::RotaryVerticalDrag);
    slider3->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider3->setColour (Slider::rotarySliderFillColourId, Colour (0x7f788c8d));
    slider3->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff9194ae));
    slider3->setColour (Slider::textBoxTextColourId, Colours::black);
    slider3->addListener (this);

    addAndMakeVisible (slider4 = new Slider ("new slider 4"));
    slider4->setRange (1, 256, 1);
    slider4->setSliderStyle (Slider::RotaryVerticalDrag);
    slider4->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider4->setColour (Slider::rotarySliderFillColourId, Colour (0x7f23232f));
    slider4->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffda9d5e));
    slider4->setColour (Slider::textBoxTextColourId, Colours::black);
    slider4->addListener (this);

    addAndMakeVisible (slider5 = new Slider ("new slider 5"));
    slider5->setRange (1, 256, 1);
    slider5->setSliderStyle (Slider::RotaryVerticalDrag);
    slider5->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider5->setColour (Slider::rotarySliderFillColourId, Colour (0x7f33ff66));
    slider5->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffee1ceb));
    slider5->setColour (Slider::textBoxTextColourId, Colours::black);
    slider5->addListener (this);

    addAndMakeVisible (slider6 = new Slider ("new slider 6"));
    slider6->setRange (1, 256, 1);
    slider6->setSliderStyle (Slider::RotaryVerticalDrag);
    slider6->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider6->setColour (Slider::rotarySliderFillColourId, Colour (0x7f61ff00));
    slider6->setColour (Slider::rotarySliderOutlineColourId, Colours::black);
    slider6->setColour (Slider::textBoxTextColourId, Colours::black);
    slider6->addListener (this);

    addAndMakeVisible (slider7 = new Slider ("new slider 7"));
    slider7->setRange (1, 256, 1);
    slider7->setSliderStyle (Slider::RotaryVerticalDrag);
    slider7->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider7->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ff86));
    slider7->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff002097));
    slider7->setColour (Slider::textBoxTextColourId, Colours::black);
    slider7->addListener (this);

    addAndMakeVisible (slider8 = new Slider ("new slider 8"));
    slider8->setRange (1, 256, 1);
    slider8->setSliderStyle (Slider::RotaryVerticalDrag);
    slider8->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider8->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    slider8->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff119f62));
    slider8->setColour (Slider::textBoxTextColourId, Colours::black);
    slider8->addListener (this);

    addAndMakeVisible (slider25 = new Slider ("new slider 9"));
    slider25->setRange (1, 256, 1);
    slider25->setSliderStyle (Slider::RotaryVerticalDrag);
    slider25->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider25->setColour (Slider::rotarySliderFillColourId, Colour (0x7f97ce9f));
    slider25->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff78e286));
    slider25->setColour (Slider::textBoxTextColourId, Colours::black);
    slider25->addListener (this);

    addAndMakeVisible (slider26 = new Slider ("new slider 10"));
    slider26->setRange (1, 256, 1);
    slider26->setSliderStyle (Slider::RotaryVerticalDrag);
    slider26->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider26->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffbf00));
    slider26->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff2cd2b8));
    slider26->setColour (Slider::textBoxTextColourId, Colours::black);
    slider26->addListener (this);

    addAndMakeVisible (slider27 = new Slider ("new slider 11"));
    slider27->setRange (1, 256, 1);
    slider27->setSliderStyle (Slider::RotaryVerticalDrag);
    slider27->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider27->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff4600));
    slider27->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc6647b));
    slider27->setColour (Slider::textBoxTextColourId, Colours::black);
    slider27->addListener (this);

    addAndMakeVisible (slider28 = new Slider ("new slider 12"));
    slider28->setRange (1, 256, 1);
    slider28->setSliderStyle (Slider::RotaryVerticalDrag);
    slider28->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider28->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ff40));
    slider28->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff090768));
    slider28->setColour (Slider::textBoxTextColourId, Colours::black);
    slider28->addListener (this);

    addAndMakeVisible (slider9 = new Slider ("new slider 13"));
    slider9->setRange (1, 256, 1);
    slider9->setSliderStyle (Slider::LinearVertical);
    slider9->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider9->setColour (Slider::thumbColourId, Colour (0xffd06868));
    slider9->addListener (this);

    addAndMakeVisible (slider10 = new Slider ("new slider 14"));
    slider10->setRange (1, 256, 1);
    slider10->setSliderStyle (Slider::LinearVertical);
    slider10->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider10->setColour (Slider::thumbColourId, Colour (0xff28284b));
    slider10->setColour (Slider::rotarySliderFillColourId, Colour (0x7f6f6fff));
    slider10->addListener (this);

    addAndMakeVisible (slider11 = new Slider ("new slider 15"));
    slider11->setRange (1, 256, 1);
    slider11->setSliderStyle (Slider::RotaryVerticalDrag);
    slider11->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider11->setColour (Slider::rotarySliderFillColourId, Colour (0x7ffc9fff));
    slider11->setColour (Slider::rotarySliderOutlineColourId, Colours::red);
    slider11->setColour (Slider::textBoxTextColourId, Colours::black);
    slider11->addListener (this);

    addAndMakeVisible (slider12 = new Slider ("new slider 16"));
    slider12->setRange (1, 256, 1);
    slider12->setSliderStyle (Slider::RotaryVerticalDrag);
    slider12->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider12->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ffeb));
    slider12->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc2d83b));
    slider12->setColour (Slider::textBoxTextColourId, Colours::black);
    slider12->addListener (this);

    addAndMakeVisible (slider13 = new Slider ("new slider 17"));
    slider13->setRange (1, 256, 1);
    slider13->setSliderStyle (Slider::RotaryVerticalDrag);
    slider13->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider13->setColour (Slider::rotarySliderFillColourId, Colour (0x7f788c8d));
    slider13->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff9194ae));
    slider13->setColour (Slider::textBoxTextColourId, Colours::black);
    slider13->addListener (this);

    addAndMakeVisible (slider14 = new Slider ("new slider 18"));
    slider14->setRange (1, 256, 1);
    slider14->setSliderStyle (Slider::RotaryVerticalDrag);
    slider14->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider14->setColour (Slider::rotarySliderFillColourId, Colour (0x7f23232f));
    slider14->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffda9d5e));
    slider14->setColour (Slider::textBoxTextColourId, Colours::black);
    slider14->addListener (this);

    addAndMakeVisible (slider15 = new Slider ("new slider 19"));
    slider15->setRange (1, 256, 1);
    slider15->setSliderStyle (Slider::RotaryVerticalDrag);
    slider15->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider15->setColour (Slider::rotarySliderFillColourId, Colour (0x7f33ff66));
    slider15->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffee1ceb));
    slider15->setColour (Slider::textBoxTextColourId, Colours::black);
    slider15->addListener (this);

    addAndMakeVisible (slider16 = new Slider ("new slider 20"));
    slider16->setRange (1, 256, 1);
    slider16->setSliderStyle (Slider::RotaryVerticalDrag);
    slider16->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider16->setColour (Slider::rotarySliderFillColourId, Colour (0x7f61ff00));
    slider16->setColour (Slider::rotarySliderOutlineColourId, Colours::black);
    slider16->setColour (Slider::textBoxTextColourId, Colours::black);
    slider16->addListener (this);

    addAndMakeVisible (slider17 = new Slider ("new slider 21"));
    slider17->setRange (1, 256, 1);
    slider17->setSliderStyle (Slider::RotaryVerticalDrag);
    slider17->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider17->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ff86));
    slider17->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff002097));
    slider17->setColour (Slider::textBoxTextColourId, Colours::black);
    slider17->addListener (this);

    addAndMakeVisible (slider18 = new Slider ("new slider 22"));
    slider18->setRange (1, 256, 1);
    slider18->setSliderStyle (Slider::RotaryVerticalDrag);
    slider18->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider18->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    slider18->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff119f62));
    slider18->setColour (Slider::textBoxTextColourId, Colours::black);
    slider18->addListener (this);

    addAndMakeVisible (slider19 = new Slider ("new slider 23"));
    slider19->setRange (1, 256, 1);
    slider19->setSliderStyle (Slider::RotaryVerticalDrag);
    slider19->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider19->setColour (Slider::rotarySliderFillColourId, Colour (0x7f97ce9f));
    slider19->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff78e286));
    slider19->setColour (Slider::textBoxTextColourId, Colours::black);
    slider19->addListener (this);

    addAndMakeVisible (slider20 = new Slider ("new slider 24"));
    slider20->setRange (1, 256, 1);
    slider20->setSliderStyle (Slider::RotaryVerticalDrag);
    slider20->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider20->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffbf00));
    slider20->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff2cd2b8));
    slider20->setColour (Slider::textBoxTextColourId, Colours::black);
    slider20->addListener (this);

    addAndMakeVisible (slider21 = new Slider ("new slider 25"));
    slider21->setRange (1, 256, 1);
    slider21->setSliderStyle (Slider::RotaryVerticalDrag);
    slider21->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider21->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff4600));
    slider21->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc6647b));
    slider21->setColour (Slider::textBoxTextColourId, Colours::black);
    slider21->addListener (this);

    addAndMakeVisible (slider22 = new Slider ("new slider 26"));
    slider22->setRange (1, 256, 1);
    slider22->setSliderStyle (Slider::RotaryVerticalDrag);
    slider22->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider22->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ff40));
    slider22->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff090768));
    slider22->setColour (Slider::textBoxTextColourId, Colours::black);
    slider22->addListener (this);

    addAndMakeVisible (slider23 = new Slider ("new slider 27"));
    slider23->setRange (1, 256, 1);
    slider23->setSliderStyle (Slider::LinearVertical);
    slider23->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider23->setColour (Slider::thumbColourId, Colour (0xffd06868));
    slider23->addListener (this);

    addAndMakeVisible (slider24 = new Slider ("new slider 28"));
    slider24->setRange (1, 256, 1);
    slider24->setSliderStyle (Slider::LinearVertical);
    slider24->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider24->setColour (Slider::thumbColourId, Colour (0xff28284b));
    slider24->setColour (Slider::rotarySliderFillColourId, Colour (0x7f6f6fff));
    slider24->addListener (this);

    addAndMakeVisible (slider29 = new Slider ("new slider 29"));
    slider29->setRange (1, 256, 1);
    slider29->setSliderStyle (Slider::RotaryVerticalDrag);
    slider29->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider29->setColour (Slider::rotarySliderFillColourId, Colour (0x7ffc9fff));
    slider29->setColour (Slider::rotarySliderOutlineColourId, Colours::red);
    slider29->setColour (Slider::textBoxTextColourId, Colours::black);
    slider29->addListener (this);

    addAndMakeVisible (slider30 = new Slider ("new slider 30"));
    slider30->setRange (1, 256, 1);
    slider30->setSliderStyle (Slider::RotaryVerticalDrag);
    slider30->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider30->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ffeb));
    slider30->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc2d83b));
    slider30->setColour (Slider::textBoxTextColourId, Colours::black);
    slider30->addListener (this);

    addAndMakeVisible (slider31 = new Slider ("new slider 31"));
    slider31->setRange (1, 256, 1);
    slider31->setSliderStyle (Slider::RotaryVerticalDrag);
    slider31->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider31->setColour (Slider::rotarySliderFillColourId, Colour (0x7f788c8d));
    slider31->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff9194ae));
    slider31->setColour (Slider::textBoxTextColourId, Colours::black);
    slider31->addListener (this);

    addAndMakeVisible (slider32 = new Slider ("new slider 32"));
    slider32->setRange (1, 256, 1);
    slider32->setSliderStyle (Slider::RotaryVerticalDrag);
    slider32->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider32->setColour (Slider::rotarySliderFillColourId, Colour (0x7f23232f));
    slider32->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffda9d5e));
    slider32->setColour (Slider::textBoxTextColourId, Colours::black);
    slider32->addListener (this);

    addAndMakeVisible (slider33 = new Slider ("new slider 33"));
    slider33->setRange (1, 256, 1);
    slider33->setSliderStyle (Slider::RotaryVerticalDrag);
    slider33->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider33->setColour (Slider::rotarySliderFillColourId, Colour (0x7f33ff66));
    slider33->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffee1ceb));
    slider33->setColour (Slider::textBoxTextColourId, Colours::black);
    slider33->addListener (this);

    addAndMakeVisible (slider34 = new Slider ("new slider 34"));
    slider34->setRange (1, 256, 1);
    slider34->setSliderStyle (Slider::RotaryVerticalDrag);
    slider34->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider34->setColour (Slider::rotarySliderFillColourId, Colour (0x7f61ff00));
    slider34->setColour (Slider::rotarySliderOutlineColourId, Colours::black);
    slider34->setColour (Slider::textBoxTextColourId, Colours::black);
    slider34->addListener (this);

    addAndMakeVisible (slider35 = new Slider ("new slider 35"));
    slider35->setRange (1, 256, 1);
    slider35->setSliderStyle (Slider::RotaryVerticalDrag);
    slider35->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider35->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ff86));
    slider35->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff002097));
    slider35->setColour (Slider::textBoxTextColourId, Colours::black);
    slider35->addListener (this);

    addAndMakeVisible (slider36 = new Slider ("new slider 36"));
    slider36->setRange (1, 256, 1);
    slider36->setSliderStyle (Slider::RotaryVerticalDrag);
    slider36->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider36->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    slider36->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff119f62));
    slider36->setColour (Slider::textBoxTextColourId, Colours::black);
    slider36->addListener (this);

    addAndMakeVisible (slider37 = new Slider ("new slider 37"));
    slider37->setRange (1, 256, 1);
    slider37->setSliderStyle (Slider::RotaryVerticalDrag);
    slider37->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider37->setColour (Slider::rotarySliderFillColourId, Colour (0x7f97ce9f));
    slider37->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff78e286));
    slider37->setColour (Slider::textBoxTextColourId, Colours::black);
    slider37->addListener (this);

    addAndMakeVisible (slider38 = new Slider ("new slider 38"));
    slider38->setRange (1, 256, 1);
    slider38->setSliderStyle (Slider::RotaryVerticalDrag);
    slider38->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider38->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffbf00));
    slider38->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff2cd2b8));
    slider38->setColour (Slider::textBoxTextColourId, Colours::black);
    slider38->addListener (this);

    addAndMakeVisible (slider39 = new Slider ("new slider 39"));
    slider39->setRange (1, 256, 1);
    slider39->setSliderStyle (Slider::RotaryVerticalDrag);
    slider39->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider39->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff4600));
    slider39->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc6647b));
    slider39->setColour (Slider::textBoxTextColourId, Colours::black);
    slider39->addListener (this);

    addAndMakeVisible (slider40 = new Slider ("new slider 40"));
    slider40->setRange (1, 256, 1);
    slider40->setSliderStyle (Slider::RotaryVerticalDrag);
    slider40->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider40->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00ff40));
    slider40->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff090768));
    slider40->setColour (Slider::textBoxTextColourId, Colours::black);
    slider40->addListener (this);

    addAndMakeVisible (slider41 = new Slider ("new slider 41"));
    slider41->setRange (1, 256, 1);
    slider41->setSliderStyle (Slider::LinearVertical);
    slider41->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider41->setColour (Slider::thumbColourId, Colour (0xffd06868));
    slider41->addListener (this);

    addAndMakeVisible (slider42 = new Slider ("new slider 42"));
    slider42->setRange (1, 256, 1);
    slider42->setSliderStyle (Slider::LinearVertical);
    slider42->setTextBoxStyle (Slider::TextBoxBelow, false, 24, 14);
    slider42->setColour (Slider::thumbColourId, Colour (0xff28284b));
    slider42->setColour (Slider::rotarySliderFillColourId, Colour (0x7f6f6fff));
    slider42->addListener (this);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group 1",
                                                            String::empty));
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0xff3a5e92));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group 2",
                                                             String::empty));
    groupComponent2->setColour (GroupComponent::outlineColourId, Colour (0xffd33838));

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group 3",
                                                             String::empty));
    groupComponent3->setColour (GroupComponent::outlineColourId, Colour (0xff86fd95));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (492, 492);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

sklepSeqKnobby::~sklepSeqKnobby()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (slider);
    deleteAndZero (slider2);
    deleteAndZero (slider3);
    deleteAndZero (slider4);
    deleteAndZero (slider5);
    deleteAndZero (slider6);
    deleteAndZero (slider7);
    deleteAndZero (slider8);
    deleteAndZero (slider25);
    deleteAndZero (slider26);
    deleteAndZero (slider27);
    deleteAndZero (slider28);
    deleteAndZero (slider9);
    deleteAndZero (slider10);
    deleteAndZero (slider11);
    deleteAndZero (slider12);
    deleteAndZero (slider13);
    deleteAndZero (slider14);
    deleteAndZero (slider15);
    deleteAndZero (slider16);
    deleteAndZero (slider17);
    deleteAndZero (slider18);
    deleteAndZero (slider19);
    deleteAndZero (slider20);
    deleteAndZero (slider21);
    deleteAndZero (slider22);
    deleteAndZero (slider23);
    deleteAndZero (slider24);
    deleteAndZero (slider29);
    deleteAndZero (slider30);
    deleteAndZero (slider31);
    deleteAndZero (slider32);
    deleteAndZero (slider33);
    deleteAndZero (slider34);
    deleteAndZero (slider35);
    deleteAndZero (slider36);
    deleteAndZero (slider37);
    deleteAndZero (slider38);
    deleteAndZero (slider39);
    deleteAndZero (slider40);
    deleteAndZero (slider41);
    deleteAndZero (slider42);
    deleteAndZero (groupComponent);
    deleteAndZero (groupComponent2);
    deleteAndZero (groupComponent3);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sklepSeqKnobby::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x3dc35fc2));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void sklepSeqKnobby::resized()
{
    slider->setBounds (16, 8, 48, 56);
    slider2->setBounds (80, 8, 48, 56);
    slider3->setBounds (168, 8, 48, 56);
    slider4->setBounds (232, 8, 48, 56);
    slider5->setBounds (17, 80, 48, 56);
    slider6->setBounds (81, 80, 48, 56);
    slider7->setBounds (169, 80, 48, 56);
    slider8->setBounds (233, 80, 48, 56);
    slider25->setBounds (322, 8, 48, 56);
    slider26->setBounds (386, 8, 48, 56);
    slider27->setBounds (323, 80, 48, 56);
    slider28->setBounds (387, 80, 48, 56);
    slider9->setBounds (136, 8, 31, 128);
    slider10->setBounds (288, 8, 31, 128);
    slider11->setBounds (55, 168, 48, 56);
    slider12->setBounds (119, 168, 48, 56);
    slider13->setBounds (207, 168, 48, 56);
    slider14->setBounds (271, 168, 48, 56);
    slider15->setBounds (56, 240, 48, 56);
    slider16->setBounds (120, 240, 48, 56);
    slider17->setBounds (208, 240, 48, 56);
    slider18->setBounds (272, 240, 48, 56);
    slider19->setBounds (361, 168, 48, 56);
    slider20->setBounds (425, 168, 48, 56);
    slider21->setBounds (362, 240, 48, 56);
    slider22->setBounds (426, 240, 48, 56);
    slider23->setBounds (175, 168, 31, 128);
    slider24->setBounds (327, 168, 31, 128);
    slider29->setBounds (16, 322, 48, 56);
    slider30->setBounds (80, 322, 48, 56);
    slider31->setBounds (168, 322, 48, 56);
    slider32->setBounds (232, 322, 48, 56);
    slider33->setBounds (17, 394, 48, 56);
    slider34->setBounds (81, 394, 48, 56);
    slider35->setBounds (169, 394, 48, 56);
    slider36->setBounds (233, 394, 48, 56);
    slider37->setBounds (322, 322, 48, 56);
    slider38->setBounds (386, 322, 48, 56);
    slider39->setBounds (323, 394, 48, 56);
    slider40->setBounds (387, 394, 48, 56);
    slider41->setBounds (136, 322, 31, 128);
    slider42->setBounds (288, 322, 31, 128);
    groupComponent->setBounds (40, 144, 448, 160);
    groupComponent2->setBounds (8, 304, 448, 160);
    groupComponent3->setBounds (0, -8, 456, 152);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void sklepSeqKnobby::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3)
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4)
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        //[/UserSliderCode_slider4]
    }
    else if (sliderThatWasMoved == slider5)
    {
        //[UserSliderCode_slider5] -- add your slider handling code here..
        //[/UserSliderCode_slider5]
    }
    else if (sliderThatWasMoved == slider6)
    {
        //[UserSliderCode_slider6] -- add your slider handling code here..
        //[/UserSliderCode_slider6]
    }
    else if (sliderThatWasMoved == slider7)
    {
        //[UserSliderCode_slider7] -- add your slider handling code here..
        //[/UserSliderCode_slider7]
    }
    else if (sliderThatWasMoved == slider8)
    {
        //[UserSliderCode_slider8] -- add your slider handling code here..
        //[/UserSliderCode_slider8]
    }
    else if (sliderThatWasMoved == slider25)
    {
        //[UserSliderCode_slider25] -- add your slider handling code here..
        //[/UserSliderCode_slider25]
    }
    else if (sliderThatWasMoved == slider26)
    {
        //[UserSliderCode_slider26] -- add your slider handling code here..
        //[/UserSliderCode_slider26]
    }
    else if (sliderThatWasMoved == slider27)
    {
        //[UserSliderCode_slider27] -- add your slider handling code here..
        //[/UserSliderCode_slider27]
    }
    else if (sliderThatWasMoved == slider28)
    {
        //[UserSliderCode_slider28] -- add your slider handling code here..
        //[/UserSliderCode_slider28]
    }
    else if (sliderThatWasMoved == slider9)
    {
        //[UserSliderCode_slider9] -- add your slider handling code here..
        //[/UserSliderCode_slider9]
    }
    else if (sliderThatWasMoved == slider10)
    {
        //[UserSliderCode_slider10] -- add your slider handling code here..
        //[/UserSliderCode_slider10]
    }
    else if (sliderThatWasMoved == slider11)
    {
        //[UserSliderCode_slider11] -- add your slider handling code here..
        //[/UserSliderCode_slider11]
    }
    else if (sliderThatWasMoved == slider12)
    {
        //[UserSliderCode_slider12] -- add your slider handling code here..
        //[/UserSliderCode_slider12]
    }
    else if (sliderThatWasMoved == slider13)
    {
        //[UserSliderCode_slider13] -- add your slider handling code here..
        //[/UserSliderCode_slider13]
    }
    else if (sliderThatWasMoved == slider14)
    {
        //[UserSliderCode_slider14] -- add your slider handling code here..
        //[/UserSliderCode_slider14]
    }
    else if (sliderThatWasMoved == slider15)
    {
        //[UserSliderCode_slider15] -- add your slider handling code here..
        //[/UserSliderCode_slider15]
    }
    else if (sliderThatWasMoved == slider16)
    {
        //[UserSliderCode_slider16] -- add your slider handling code here..
        //[/UserSliderCode_slider16]
    }
    else if (sliderThatWasMoved == slider17)
    {
        //[UserSliderCode_slider17] -- add your slider handling code here..
        //[/UserSliderCode_slider17]
    }
    else if (sliderThatWasMoved == slider18)
    {
        //[UserSliderCode_slider18] -- add your slider handling code here..
        //[/UserSliderCode_slider18]
    }
    else if (sliderThatWasMoved == slider19)
    {
        //[UserSliderCode_slider19] -- add your slider handling code here..
        //[/UserSliderCode_slider19]
    }
    else if (sliderThatWasMoved == slider20)
    {
        //[UserSliderCode_slider20] -- add your slider handling code here..
        //[/UserSliderCode_slider20]
    }
    else if (sliderThatWasMoved == slider21)
    {
        //[UserSliderCode_slider21] -- add your slider handling code here..
        //[/UserSliderCode_slider21]
    }
    else if (sliderThatWasMoved == slider22)
    {
        //[UserSliderCode_slider22] -- add your slider handling code here..
        //[/UserSliderCode_slider22]
    }
    else if (sliderThatWasMoved == slider23)
    {
        //[UserSliderCode_slider23] -- add your slider handling code here..
        //[/UserSliderCode_slider23]
    }
    else if (sliderThatWasMoved == slider24)
    {
        //[UserSliderCode_slider24] -- add your slider handling code here..
        //[/UserSliderCode_slider24]
    }
    else if (sliderThatWasMoved == slider29)
    {
        //[UserSliderCode_slider29] -- add your slider handling code here..
        //[/UserSliderCode_slider29]
    }
    else if (sliderThatWasMoved == slider30)
    {
        //[UserSliderCode_slider30] -- add your slider handling code here..
        //[/UserSliderCode_slider30]
    }
    else if (sliderThatWasMoved == slider31)
    {
        //[UserSliderCode_slider31] -- add your slider handling code here..
        //[/UserSliderCode_slider31]
    }
    else if (sliderThatWasMoved == slider32)
    {
        //[UserSliderCode_slider32] -- add your slider handling code here..
        //[/UserSliderCode_slider32]
    }
    else if (sliderThatWasMoved == slider33)
    {
        //[UserSliderCode_slider33] -- add your slider handling code here..
        //[/UserSliderCode_slider33]
    }
    else if (sliderThatWasMoved == slider34)
    {
        //[UserSliderCode_slider34] -- add your slider handling code here..
        //[/UserSliderCode_slider34]
    }
    else if (sliderThatWasMoved == slider35)
    {
        //[UserSliderCode_slider35] -- add your slider handling code here..
        //[/UserSliderCode_slider35]
    }
    else if (sliderThatWasMoved == slider36)
    {
        //[UserSliderCode_slider36] -- add your slider handling code here..
        //[/UserSliderCode_slider36]
    }
    else if (sliderThatWasMoved == slider37)
    {
        //[UserSliderCode_slider37] -- add your slider handling code here..
        //[/UserSliderCode_slider37]
    }
    else if (sliderThatWasMoved == slider38)
    {
        //[UserSliderCode_slider38] -- add your slider handling code here..
        //[/UserSliderCode_slider38]
    }
    else if (sliderThatWasMoved == slider39)
    {
        //[UserSliderCode_slider39] -- add your slider handling code here..
        //[/UserSliderCode_slider39]
    }
    else if (sliderThatWasMoved == slider40)
    {
        //[UserSliderCode_slider40] -- add your slider handling code here..
        //[/UserSliderCode_slider40]
    }
    else if (sliderThatWasMoved == slider41)
    {
        //[UserSliderCode_slider41] -- add your slider handling code here..
        //[/UserSliderCode_slider41]
    }
    else if (sliderThatWasMoved == slider42)
    {
        //[UserSliderCode_slider42] -- add your slider handling code here..
        //[/UserSliderCode_slider42]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sklepSeqKnobby" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="492" initialHeight="492">
  <BACKGROUND backgroundColour="3dc35fc2"/>
  <SLIDER name="new slider" id="95cc8fd1b4f9fae3" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="16 8 48 56" rotarysliderfill="7ffc9fff"
          rotaryslideroutline="ffff0000" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="deaa4edfb24c979" memberName="slider2" virtualName=""
          explicitFocusOrder="0" pos="80 8 48 56" rotarysliderfill="7f00ffeb"
          rotaryslideroutline="ffc2d83b" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="f7c7191355dc7065" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="168 8 48 56" rotarysliderfill="7f788c8d"
          rotaryslideroutline="ff9194ae" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="213a7c819213961b" memberName="slider4"
          virtualName="" explicitFocusOrder="0" pos="232 8 48 56" rotarysliderfill="7f23232f"
          rotaryslideroutline="ffda9d5e" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="c27b1dbf7864bfb5" memberName="slider5"
          virtualName="" explicitFocusOrder="0" pos="17 80 48 56" rotarysliderfill="7f33ff66"
          rotaryslideroutline="ffee1ceb" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="ae6e9781f69e59a3" memberName="slider6"
          virtualName="" explicitFocusOrder="0" pos="81 80 48 56" rotarysliderfill="7f61ff00"
          rotaryslideroutline="ff000000" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="6c1297615f12ee99" memberName="slider7"
          virtualName="" explicitFocusOrder="0" pos="169 80 48 56" rotarysliderfill="7f00ff86"
          rotaryslideroutline="ff002097" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="71b36ee1e03613be" memberName="slider8"
          virtualName="" explicitFocusOrder="0" pos="233 80 48 56" rotarysliderfill="7fffffff"
          rotaryslideroutline="ff119f62" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="8abeb974519bfb09" memberName="slider25"
          virtualName="" explicitFocusOrder="0" pos="322 8 48 56" rotarysliderfill="7f97ce9f"
          rotaryslideroutline="ff78e286" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="366e0569cbad9c2" memberName="slider26"
          virtualName="" explicitFocusOrder="0" pos="386 8 48 56" rotarysliderfill="7fffbf00"
          rotaryslideroutline="ff2cd2b8" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="d1c748f1c96fa587" memberName="slider27"
          virtualName="" explicitFocusOrder="0" pos="323 80 48 56" rotarysliderfill="7fff4600"
          rotaryslideroutline="ffc6647b" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="dc74cfd995bfa155" memberName="slider28"
          virtualName="" explicitFocusOrder="0" pos="387 80 48 56" rotarysliderfill="7f00ff40"
          rotaryslideroutline="ff090768" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="2c61c90f8ff5249a" memberName="slider9"
          virtualName="" explicitFocusOrder="0" pos="136 8 31 128" thumbcol="ffd06868"
          min="1" max="256" int="1" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="9c5790880dbedcfa" memberName="slider10"
          virtualName="" explicitFocusOrder="0" pos="288 8 31 128" thumbcol="ff28284b"
          rotarysliderfill="7f6f6fff" min="1" max="256" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="24"
          textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="89e79988ceffb93e" memberName="slider11"
          virtualName="" explicitFocusOrder="0" pos="55 168 48 56" rotarysliderfill="7ffc9fff"
          rotaryslideroutline="ffff0000" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="23d59362f18741f8" memberName="slider12"
          virtualName="" explicitFocusOrder="0" pos="119 168 48 56" rotarysliderfill="7f00ffeb"
          rotaryslideroutline="ffc2d83b" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="55373ba738e8021" memberName="slider13"
          virtualName="" explicitFocusOrder="0" pos="207 168 48 56" rotarysliderfill="7f788c8d"
          rotaryslideroutline="ff9194ae" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="abbc39499124548e" memberName="slider14"
          virtualName="" explicitFocusOrder="0" pos="271 168 48 56" rotarysliderfill="7f23232f"
          rotaryslideroutline="ffda9d5e" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="106e4d0266ce38b6" memberName="slider15"
          virtualName="" explicitFocusOrder="0" pos="56 240 48 56" rotarysliderfill="7f33ff66"
          rotaryslideroutline="ffee1ceb" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="953c54676b3e14ac" memberName="slider16"
          virtualName="" explicitFocusOrder="0" pos="120 240 48 56" rotarysliderfill="7f61ff00"
          rotaryslideroutline="ff000000" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="ff7129c375ec2c0" memberName="slider17"
          virtualName="" explicitFocusOrder="0" pos="208 240 48 56" rotarysliderfill="7f00ff86"
          rotaryslideroutline="ff002097" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="b6b1105cc6166776" memberName="slider18"
          virtualName="" explicitFocusOrder="0" pos="272 240 48 56" rotarysliderfill="7fffffff"
          rotaryslideroutline="ff119f62" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="59da707b7a4808ae" memberName="slider19"
          virtualName="" explicitFocusOrder="0" pos="361 168 48 56" rotarysliderfill="7f97ce9f"
          rotaryslideroutline="ff78e286" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="90a3e5a1b69e4d37" memberName="slider20"
          virtualName="" explicitFocusOrder="0" pos="425 168 48 56" rotarysliderfill="7fffbf00"
          rotaryslideroutline="ff2cd2b8" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="9baff5974cb9620" memberName="slider21"
          virtualName="" explicitFocusOrder="0" pos="362 240 48 56" rotarysliderfill="7fff4600"
          rotaryslideroutline="ffc6647b" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="22f447b738cdc585" memberName="slider22"
          virtualName="" explicitFocusOrder="0" pos="426 240 48 56" rotarysliderfill="7f00ff40"
          rotaryslideroutline="ff090768" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="de85c01064da92aa" memberName="slider23"
          virtualName="" explicitFocusOrder="0" pos="175 168 31 128" thumbcol="ffd06868"
          min="1" max="256" int="1" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="eb0f82a35d5351a2" memberName="slider24"
          virtualName="" explicitFocusOrder="0" pos="327 168 31 128" thumbcol="ff28284b"
          rotarysliderfill="7f6f6fff" min="1" max="256" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="24"
          textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="7cc47b9958ceb924" memberName="slider29"
          virtualName="" explicitFocusOrder="0" pos="16 322 48 56" rotarysliderfill="7ffc9fff"
          rotaryslideroutline="ffff0000" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="3634c3b094fc816f" memberName="slider30"
          virtualName="" explicitFocusOrder="0" pos="80 322 48 56" rotarysliderfill="7f00ffeb"
          rotaryslideroutline="ffc2d83b" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="7c648f65de0f4d8" memberName="slider31"
          virtualName="" explicitFocusOrder="0" pos="168 322 48 56" rotarysliderfill="7f788c8d"
          rotaryslideroutline="ff9194ae" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="725bf0516e552afc" memberName="slider32"
          virtualName="" explicitFocusOrder="0" pos="232 322 48 56" rotarysliderfill="7f23232f"
          rotaryslideroutline="ffda9d5e" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="35abd5735b9563e4" memberName="slider33"
          virtualName="" explicitFocusOrder="0" pos="17 394 48 56" rotarysliderfill="7f33ff66"
          rotaryslideroutline="ffee1ceb" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="7bacf59f57b3258b" memberName="slider34"
          virtualName="" explicitFocusOrder="0" pos="81 394 48 56" rotarysliderfill="7f61ff00"
          rotaryslideroutline="ff000000" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="fe6a02978b46af2b" memberName="slider35"
          virtualName="" explicitFocusOrder="0" pos="169 394 48 56" rotarysliderfill="7f00ff86"
          rotaryslideroutline="ff002097" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="e6c31eb2cdd422af" memberName="slider36"
          virtualName="" explicitFocusOrder="0" pos="233 394 48 56" rotarysliderfill="7fffffff"
          rotaryslideroutline="ff119f62" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="ef28fe6d5e63fef4" memberName="slider37"
          virtualName="" explicitFocusOrder="0" pos="322 322 48 56" rotarysliderfill="7f97ce9f"
          rotaryslideroutline="ff78e286" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="757938f5f4afe9ca" memberName="slider38"
          virtualName="" explicitFocusOrder="0" pos="386 322 48 56" rotarysliderfill="7fffbf00"
          rotaryslideroutline="ff2cd2b8" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="702cc077eba166cd" memberName="slider39"
          virtualName="" explicitFocusOrder="0" pos="323 394 48 56" rotarysliderfill="7fff4600"
          rotaryslideroutline="ffc6647b" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="43a65c3d0a0b808f" memberName="slider40"
          virtualName="" explicitFocusOrder="0" pos="387 394 48 56" rotarysliderfill="7f00ff40"
          rotaryslideroutline="ff090768" textboxtext="ff000000" min="1"
          max="256" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="9593e1e2ae68abad" memberName="slider41"
          virtualName="" explicitFocusOrder="0" pos="136 322 31 128" thumbcol="ffd06868"
          min="1" max="256" int="1" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="14" skewFactor="1"/>
  <SLIDER name="new slider" id="7d56a01deff7d7c2" memberName="slider42"
          virtualName="" explicitFocusOrder="0" pos="288 322 31 128" thumbcol="ff28284b"
          rotarysliderfill="7f6f6fff" min="1" max="256" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="24"
          textBoxHeight="14" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="1503835632472c49" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="40 144 448 160" outlinecol="ff3a5e92"
                  title=""/>
  <GROUPCOMPONENT name="new group" id="92523e794e4d2f47" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="8 304 448 160" outlinecol="ffd33838"
                  title=""/>
  <GROUPCOMPONENT name="new group" id="5c600fa88d001b21" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 456 152" outlinecol="ff86fd95"
                  title=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
