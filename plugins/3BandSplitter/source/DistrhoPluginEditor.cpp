
#include "DistrhoArtwork.h"
#include "DistrhoPluginEditor.h"

//==============================================================================
DistrhoPluginAudioProcessorEditor::DistrhoPluginAudioProcessorEditor (DistrhoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();

    knobImage       = ImageCache::getFromMemory (DistrhoArtwork::knob_png, DistrhoArtwork::knob_pngSize);
    sliderImage     = ImageCache::getFromMemory (DistrhoArtwork::slider_png, DistrhoArtwork::slider_pngSize);
    backgroundImage = ImageCache::getFromMemory (DistrhoArtwork::background_png, DistrhoArtwork::background_pngSize);

    setSize (backgroundImage.getWidth(), backgroundImage.getHeight());

    const int sliderTop    = 39;
    const int sliderSpace  = 157;
    const int knobFrames   = 70;

    sLow = new ImageSlider (sliderImage, sliderSpace, DistrhoPluginAudioProcessor::pLow);
    sLow->setBounds (49, sliderTop, sliderImage.getWidth(), sliderSpace + sliderImage.getHeight());
    sLow->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pLow), false);
    sLow->addListener (this);
    addAndMakeVisible (sLow);

    sMid = new ImageSlider (sliderImage, sliderSpace, DistrhoPluginAudioProcessor::pMid);
    sMid->setBounds (115, sliderTop, sliderImage.getWidth(), sliderSpace + sliderImage.getHeight());
    sMid->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pMid), false);
    sMid->addListener (this);
    addAndMakeVisible (sMid);

    sHigh = new ImageSlider (sliderImage, sliderSpace, DistrhoPluginAudioProcessor::pHigh);
    sHigh->setBounds (178, sliderTop, sliderImage.getWidth(), sliderSpace + sliderImage.getHeight());
    sHigh->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pHigh), false);
    sHigh->addListener (this);
    addAndMakeVisible (sHigh);

    sMaster = new ImageSlider (sliderImage, sliderSpace, DistrhoPluginAudioProcessor::pMaster);
    sMaster->setBounds (282, sliderTop, sliderImage.getWidth(), sliderSpace + sliderImage.getHeight());
    sMaster->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pMaster), false);
    sMaster->addListener (this);
    addAndMakeVisible (sMaster);

    sLowMidFreq = new FilmStripKnob (knobImage, knobFrames, false, DistrhoPluginAudioProcessor::pLowMidFreq);
    sLowMidFreq->setBounds (66, 270, knobImage.getWidth(), knobImage.getHeight() / knobFrames);
    sLowMidFreq->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pLowMidFreq), false);
    sLowMidFreq->addListener (this);
    addAndMakeVisible (sLowMidFreq);

    sMidHighFreq = new FilmStripKnob (knobImage, knobFrames, false, DistrhoPluginAudioProcessor::pMidHighFreq);
    sMidHighFreq->setBounds (160, 270, knobImage.getWidth(), knobImage.getHeight() / knobFrames);
    sMidHighFreq->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pMidHighFreq), false);
    sMidHighFreq->addListener (this);
    addAndMakeVisible (sMidHighFreq);

    aboutLogo = new DistrhoIcon(DistrhoIcon::ICON_LIGHT);
    aboutLogo->setTopLeftPosition(250, 300);
    addAndMakeVisible (aboutLogo);

    startTimer (50);
}

DistrhoPluginAudioProcessorEditor::~DistrhoPluginAudioProcessorEditor()
{
    stopTimer ();
    slidersDraggedList.clear();

    delete sLow;
    delete sMid;
    delete sHigh;
    delete sMaster;
    delete sLowMidFreq;
    delete sMidHighFreq;
    delete aboutLogo;
}

//==============================================================================
void DistrhoPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.drawImage(backgroundImage,
                0, 0, backgroundImage.getWidth(), backgroundImage.getHeight(),
                0, 0, backgroundImage.getWidth(), backgroundImage.getHeight(),
                false);
}

void DistrhoPluginAudioProcessorEditor::sliderValueChanged (Slider* caller)
{
    DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();

    // Do not allow knobs wrong values
    if (caller == sLowMidFreq)
    {
        if (caller->getValue() > sMidHighFreq->getValue())
            caller->setValue(sMidHighFreq->getValue(), false);
    }
    else if (caller == sMidHighFreq)
    {
        if (caller->getValue() < sLowMidFreq->getValue())
            caller->setValue(sLowMidFreq->getValue(), false);
    }

    NamedValueSet values = caller->getProperties();
    if (values.contains(Identifier("index")))
    {
       ourProcessor->setParameterNotifyingHost(values["index"], (float)caller->getValue());
    }
}

void DistrhoPluginAudioProcessorEditor::sliderDragStarted (Slider* caller)
{
    NamedValueSet values = caller->getProperties();
    if (values.contains(Identifier("index")) && ! slidersDraggedList.contains(values["index"]))
    {
        slidersDraggedList.add(values["index"]);
        DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();
        ourProcessor->beginParameterChangeGesture(values["index"]);
    }
}

void DistrhoPluginAudioProcessorEditor::sliderDragEnded (Slider* caller)
{
    NamedValueSet values = caller->getProperties();
    if (values.contains(Identifier("index")) && slidersDraggedList.contains(values["index"]))
    {
        slidersDraggedList.removeValue(values["index"]);
        DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();
        ourProcessor->endParameterChangeGesture(values["index"]);
    }
}

//==============================================================================
void DistrhoPluginAudioProcessorEditor::timerCallback()
{
    DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();

    sLow->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pLow), false);
    sMid->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pMid), false);
    sHigh->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pHigh), false);
    sMaster->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pMaster), false);
    sLowMidFreq->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pLowMidFreq), false);
    sMidHighFreq->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pMidHighFreq), false);
}
