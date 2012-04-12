
#include "DistrhoArtwork.h"
#include "DistrhoPluginEditor.h"

//==============================================================================
DistrhoPluginAudioProcessorEditor::DistrhoPluginAudioProcessorEditor (DistrhoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();

    knobImage       = ImageCache::getFromMemory (DistrhoArtwork::knob_png, DistrhoArtwork::knob_pngSize);
    backgroundImage = ImageCache::getFromMemory (DistrhoArtwork::background_png, DistrhoArtwork::background_pngSize);

    setSize (backgroundImage.getWidth(), backgroundImage.getHeight());

    const int knobFrames = 70;

    sFreq = new FilmStripKnob (knobImage, knobFrames, false, DistrhoPluginAudioProcessor::pFreq);
    sFreq->setBounds (115, 0, knobImage.getWidth(), knobImage.getHeight() / knobFrames);
    sFreq->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pFreq), false);
    sFreq->addListener (this);
    addAndMakeVisible (sFreq);

    sWidth = new FilmStripKnob (knobImage, knobFrames, false, DistrhoPluginAudioProcessor::pWidth);
    sWidth->setBounds (235, 0, knobImage.getWidth(), knobImage.getHeight() / knobFrames);
    sWidth->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pWidth), false);
    sWidth->addListener (this);
    addAndMakeVisible (sWidth);

    aboutLogo = new DistrhoIcon(DistrhoIcon::ICON_DARK);
    aboutLogo->setTopLeftPosition(25, 35);
    addAndMakeVisible (aboutLogo);

    startTimer (50);
}

DistrhoPluginAudioProcessorEditor::~DistrhoPluginAudioProcessorEditor()
{
    stopTimer ();

    delete sFreq;
    delete sWidth;
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

    NamedValueSet values = caller->getProperties();
    if (values.contains(Identifier("index")))
    {
       ourProcessor->setParameterNotifyingHost(values["index"], (float)caller->getValue());
    }
}

void DistrhoPluginAudioProcessorEditor::sliderDragStarted (Slider* caller)
{
    NamedValueSet values = caller->getProperties();
    if (values.contains(Identifier("index")))
    {
        DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();
        ourProcessor->beginParameterChangeGesture(values["index"]);
    }
}

void DistrhoPluginAudioProcessorEditor::sliderDragEnded (Slider* caller)
{
    NamedValueSet values = caller->getProperties();
    if (values.contains(Identifier("index")))
    {
        DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();
        ourProcessor->endParameterChangeGesture(values["index"]);
    }
}

//==============================================================================
void DistrhoPluginAudioProcessorEditor::timerCallback()
{
    DistrhoPluginAudioProcessor* const ourProcessor = getProcessor();

    sFreq->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pFreq), false);
    sWidth->setValue (ourProcessor->getParameter(DistrhoPluginAudioProcessor::pWidth), false);
}
