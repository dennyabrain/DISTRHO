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

#ifndef __JUCER_HEADER_MRALIASEDITOR_MRALIASPROGUI_3F2521F2__
#define __JUCER_HEADER_MRALIASEDITOR_MRALIASPROGUI_3F2521F2__

//[Headers]     -- You can add your own extra header files here --
#include "MrAlias2.h"
#include "juce.h"
#include "common/piz_LookAndFeel.h"
#include "CCMapSlider.h"
#include "piz_ComboBox.h"
#ifdef MRALIASPRO
#include "ProKnob.h"
#include "common/ImageSlider.h"


class MrAliasKeyboard : public MidiKeyboardComponent
{
public:
    MrAliasKeyboard(MidiKeyboardState &state, const Orientation orientation);
private:
    bool mouseDownOnKey(int midiNoteNumber, const MouseEvent &e);
    MidiKeyboardState* s;
};

class Indicator : public Slider
{
public:
	Indicator(String name) : Slider(name) {
		this->setMouseClickGrabsKeyboardFocus(false);
		this->setEnabled(false);
	}

	void paint(Graphics &g) {
		g.fillAll(Colours::black.withAlpha(0.1f));
        if (getSliderStyle() == Slider::LinearVertical)
        {
			g.setColour(Colours::white.withAlpha(0.1f));
			g.drawHorizontalLine(getHeight()/2,0.f,(float)getWidth());
			double sliderpos = 1.0 - getValue()/(this->getMaximum()-this->getMinimum());
			g.setColour(Colours::white.withAlpha(0.5f));
			g.drawHorizontalLine((int)(sliderpos*(double)getHeight()*0.98),0.f,(float)getWidth());
        }
        else if (getSliderStyle() == Slider::LinearHorizontal)
        {
			g.setColour(Colours::white.withAlpha(0.1f));
			g.drawVerticalLine(getWidth()/2,0.f,(float)getHeight());
			double sliderpos = getValue()/(this->getMaximum()-this->getMinimum());
			g.setColour(Colours::white.withAlpha(0.5f));
			g.drawVerticalLine((int)(sliderpos*(double)getWidth()*0.98),0.f,(float)getHeight());
        }
	}

};

class ProSliderV : public ImageSlider
{
public:
	ProSliderV(const String& name)
		: ImageSlider(name)
	{
		setOrientation (ImageSlider::LinearVertical);
		this->setMouseClickGrabsKeyboardFocus(false);
		this->setSliderSnapsToMousePosition(false);
	}
};

class ProSliderH : public ImageSlider
{
public:
	ProSliderH(const String& name)
		: ImageSlider(name)
	{
		setOrientation (ImageSlider::LinearHorizontal);
		this->setMouseClickGrabsKeyboardFocus(false);
		this->setSliderSnapsToMousePosition(false);
	}
};

class BlankPage : public Component
{
public:
	friend class MrAlias2Editor;
	BlankPage()	: bg(0) {
		this->setMouseClickGrabsKeyboardFocus(false);
	}
	void setBackgroundImage(File image) {
		bg = Drawable::createFromImageFile(image);
	}
	void paint(Graphics &g) {
		g.fillAll(Colours::transparentBlack);
		if (bg!=0) bg->drawWithin(g,Rectangle<float>(0,0,getWidth(),getHeight()),RectanglePlacement::stretchToFit, 0);
	}
	~BlankPage() { if (bg) delete bg; }
private:
	Drawable* bg;
};

#endif
//[/Headers]

#include "led.h"
#include "PizButton.h"
#include "AboutBoxPro.h"
#include "WaveDrawWindow.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MrAlias2Editor  : public AudioProcessorEditor,
                        public ChangeListener,
                        public FileDragAndDropTarget,
                        public PizComboBoxListener,
                        public Timer,
                        public SliderListener,
                        public ButtonListener,
                        public LabelListener,
                        public ComboBoxListener
{
public:
    //==============================================================================
    MrAlias2Editor (MrAlias2* const ownerFilter);
    ~MrAlias2Editor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback (ChangeBroadcaster* source);
    bool isInterestedInFileDrag (const StringArray& files);
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
    void sliderDragStarted (Slider* slider); //slider mousedown
    void sliderDragEnded (Slider* slider); //slider mouseup
    void mouseDown (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
	void buttonStateChanged (Button *);
    void timerCallback ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    // Binary resources:
    static const char* whitetitle_svg;
    static const int whitetitle_svgSize;
    static const char* wood1_png;
    static const int wood1_pngSize;
    static const char* wood2_png;
    static const int wood2_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    enum componenttypes {sliderType,buttonType,comboBoxType};
    ComponentBoundsConstrainer resizeLimits;
    TooltipWindow tooltipWindow;

    void updateParametersFromFilter();

    inline float mapToVSTRange(Slider* source);
    inline void setVSTSlider(Slider* slider, float x);
    inline int getSliderIndex(Slider* slider);
    inline void getComponentIndexAndType(Component* c, int &index, int &type);
    Slider* getSliderByIndex(int index);
    int oldccmap[numParams];
    CCMapSlider* ccmapbox[numParams];
	ProSliderH* sRandomSpeed;
	ProSliderH* sRandomStrength;
    void showMainMenu();
	void showControlMenu(Component* c);
	void reloadSkin();

    MrAlias2* getFilter() const throw() { return (MrAlias2*) getAudioProcessor(); }

    bool init;

    double aspectRatio;

	Drawable* bg;
	Image wood1;
	Image wood2;
	Image smallKnob;
	Image largeKnob;
	Image hSliderThumb;
	Drawable* hSliderBG;
	Image vSliderThumb;
	Drawable* vSliderBG;
	Image menuDot;

	bool demoRight, demoDown;
    //[/UserVariables]

    //==============================================================================
    Slider* sChannel;
    MrAliasKeyboard* keyboard;
    ProSliderH* sAlias;
    ProKnob* sCutoff;
    ProSliderH* sDivide;
    ProSliderV* sAtt;
    ProSliderH* sRate;
    ProKnob* sSineMix;
    ProSliderH* sSineRes;
    ProSliderH* sPostDivide;
    ProSliderH* sClip;
    ProKnob* sAInertia;
    ProSliderV* sDec;
    ProSliderV* sSus;
    ProSliderV* sRel;
    ProKnob* sDivEnv;
    ProKnob* sRes;
    ProKnob* sBRMix;
    ProSliderH* sSineFreq;
    ProKnob* sVelSens;
    ProKnob* sFiltEnv;
    ProKnob* sFVSens;
    Slider* sPBRange;
    ProKnob* sInputGain;
    ProKnob* sWet;
    ProKnob* sOscGain;
    ProSliderH* sThresh;
    ProKnob* sFreq1;
    ProKnob* sRingMod;
    ProSliderV* sFAtt;
    ProSliderV* sFDec;
    ProSliderV* sFSus;
    ProSliderV* sFRel;
    LED* audioled;
    ProKnob* sStereo;
    ProKnob* sOscMix;
    LED* clipled;
    TextButton* sMode;
    ProSliderH* sStereo2;
    ProSliderH* sM1;
    ProKnob* sPhMod;
    ProKnob* sDivMix;
    Label* info;
    PizButton* pizButton;
    Slider* sFKeyFollow;
    TextButton* nextButton;
    TextButton* prevButton;
    TextButton* sReset;
    Slider* sOPLP;
    ProKnob* sPostDivMix;
    TextButton* sSavePatch;
    TextButton* sSavePatch2;
    Label* info3;
    Label* info2;
    TextButton* loadButton;
    ComboBox* filterModeBox;
    Slider* sOctave1;
    ComboBox* comboBox;
    Slider* sOctave2;
    ComboBox* comboBox2;
    ProKnob* sOctave;
    TextButton* sUseProgCh;
    ProKnob* sM1Mix;
    TextButton* randomButton;
    TextButton* limiterButton;
    TextButton* sExp;
    TextButton* sFExp;
    LED* midiled;
    TextButton* saveSnapshotButtonB;
    TextButton* recallSnapshotButtonB;
    Slider* sMorph;
    TextButton* saveSnapshotButtonA;
    TextButton* recallSnapshotButtonA;
    TextButton* sPitchShift;
    ResizableCornerComponent* resizer;
    PizComboBox* patchBox;
    ProKnob* sVolume;
    TextButton* toggleButton;
    TextButton* decoupled1Button;
    TextButton* decoupled2Button;
    ProSliderH* sDecoupled2;
    ProSliderH* sDecoupled1;
    ProKnob* sGlide;
    TextButton* sRetrig;
    BlankPage* page2;
    ProKnob* sLFO1Rate;
    ProKnob* sLFO1Amount;
    ProKnob* sEnv3Amount;
    ProSliderV* sRel3;
    ProSliderV* sSus3;
    ProSliderV* sDec3;
    ProSliderV* sAtt3;
    TextButton* sPage;
    TextButton* Env3DestBox;
    ProKnob* sLFO2Rate;
    ProKnob* sLFO2Amount;
    ComboBox* LFO1WaveBox;
    ComboBox* LFO2WaveBox;
    TextButton* menuButton;
    Indicator* lfo1indicator;
    TextButton* bLFO1Free;
    TextButton* bLFO2Free;
    TextButton* LFO1DestBox;
    TextButton* LFO2DestBox;
    Indicator* lfo2indicator;
    AboutBox* aboutbox;
    Indicator* env3indicator;
    TextButton* demoButton;
    TextButton* bAuto;
    TextButton* bDraw;
    TextButton* bDraw2;
    WaveDrawWindow* waveDrawer;
    TextButton* sync1;
    TextButton* sync2;
    TextButton* sExp3;
    TextButton* interpolate1;
    TextButton* interpolate2;
    Image* cachedImage_wood2_png;
    Path internalPath4;
    Path internalPath9;
    Path internalPath14;
    Image* cachedImage_wood1_png;
    Drawable* drawable17;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MrAlias2Editor (const MrAlias2Editor&);
    const MrAlias2Editor& operator= (const MrAlias2Editor&);
};


#endif   // __JUCER_HEADER_MRALIASEDITOR_MRALIASPROGUI_3F2521F2__
