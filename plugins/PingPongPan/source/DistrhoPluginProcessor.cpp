
#include "DistrhoPluginProcessor.h"
#include "DistrhoPluginEditor.h"

#define c_2PI 6.283185307f

#ifndef WINDOWS
inline float abs (float x)
{
    return ( x<0 ? -x:x);
}
#endif

inline float absmax (float x, float y)
{
    float absx = abs(x);
    float absy = abs(y);
    return (absx>absy ? absx : absy);
}

inline float min (float x, float y)
{
    return ( x<y ? x:y);
}

inline float max (float x, float y)
{
    return ( x>y ? x:y);
}

//==============================================================================
DistrhoPluginAudioProcessor::DistrhoPluginAudioProcessor()
{
    freqFader = 0.5f;
    waveSpeed = (c_2PI/2) / getSampleRate();

    width = 0.75f;
}

DistrhoPluginAudioProcessor::~DistrhoPluginAudioProcessor()
{
}

//==============================================================================
const String DistrhoPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int DistrhoPluginAudioProcessor::getNumParameters()
{
    return pMAX;
}

float DistrhoPluginAudioProcessor::getParameter (int index)
{
    switch (index)
    {
      case pFreq:
        return freqFader;
      case pWidth:
        return width;
    }
    return 0.0f;
}

void DistrhoPluginAudioProcessor::setParameter (int index, float newValue)
{
    double sampleRate = getSampleRate();

    if (sampleRate <= 0)
      sampleRate = 44100;

    switch (index)
    {
      case pFreq:
        freqFader = newValue;
        waveSpeed = (c_2PI * freqFader)/getSampleRate();
        break;
      case pWidth:
        width = newValue;
        break;
    }
}

const String DistrhoPluginAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
      case pFreq:
        return "Frequency";
      case pWidth:
        return "Width";
    }
    return String::empty;
}

const String DistrhoPluginAudioProcessor::getParameterText (int index)
{
    switch (index)
    {
      case pFreq:
        return String (freqFader, 3);
      case pWidth:
        return String (width*100, 0);
    }
    return String::empty;
}

const String DistrhoPluginAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String DistrhoPluginAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool DistrhoPluginAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool DistrhoPluginAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool DistrhoPluginAudioProcessor::acceptsMidi() const
{
    return false;
}

bool DistrhoPluginAudioProcessor::producesMidi() const
{
    return false;
}

int DistrhoPluginAudioProcessor::getNumPrograms()
{
    return 0;
}

int DistrhoPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistrhoPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String DistrhoPluginAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void DistrhoPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistrhoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    waveSpeed = (c_2PI * freqFader)/sampleRate;
}

void DistrhoPluginAudioProcessor::releaseResources()
{
}

void DistrhoPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    if (getNumInputChannels() != 2 && getNumOutputChannels() != 2)
        return;

    float *buf1 = buffer.getSampleData(0);
    float *buf2 = buffer.getSampleData(1);

    int sampleFrames = buffer.getNumSamples();

    while (--sampleFrames >= 0)
    {
        pan = min( max( (sin(wavePos)) * width, -1 ) , 1 );

        if ((wavePos+=waveSpeed) >= c_2PI)
          wavePos -= c_2PI;

        (*buf1) = (*buf1++) * (pan > 0 ? 1-pan:1);
        (*buf2) = (*buf2++) * (pan < 0 ? 1+pan:1);
    }
}

//==============================================================================
bool DistrhoPluginAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* DistrhoPluginAudioProcessor::createEditor()
{
    return new DistrhoPluginAudioProcessorEditor (this);
}

//==============================================================================
void DistrhoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml ("PingPongPan-Settings");

    xml.setAttribute ("Freq", freqFader);
    xml.setAttribute ("Width", width);

    copyXmlToBinary (xml, destData);
}

void DistrhoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr && xmlState->hasTagName ("PingPongPan-Settings"))
    {
        freqFader = (float) xmlState->getDoubleAttribute ("Freq", freqFader);
        width     = (float) xmlState->getDoubleAttribute ("Width", width);
    }
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistrhoPluginAudioProcessor();
}
