
#include "DistrhoPluginProcessor.h"
#include "DistrhoPluginEditor.h"

#define AMP_DB 8.656170245f
#define DC_ADD 1e-30f
#define PI 3.141592654f

#ifndef WINDOWS
inline float abs (float x)
{
    return ( x<0 ? -x:x);
}
#endif

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
    // Default values
    fLow = 0.5;
    fMid = 0.5;
    fHigh = 0.5;
    fMaster = 0.5;
    fLowMidFreq = 0.208706402;
    fMidHighFreq = 0.436790232;

    // Internal stuff
    lowVol = midVol = highVol = outVol = 1.0;
    freqLP = 200;
    freqHP = 2000;

    xLP = a0LP = b1LP = 0;
    xHP = a0HP = b1HP = 0;

    out1LP = out2LP = out1HP = out2HP = 0;
    tmp1LP = tmp2LP = tmp1HP = tmp2HP = 0;

    initialized = false;
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
      case pLow:
        return fLow;
      case pMid:
        return fMid;
      case pHigh:
        return fHigh;
      case pMaster:
        return fMaster;
      case pLowMidFreq:
        return fLowMidFreq;
      case pMidHighFreq:
        return fMidHighFreq;
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
      case pLow:
        fLow = newValue;
        lowVol = exp( (fLow - 0.5f) * 48 / AMP_DB);
        break;
      case pMid:
        fMid = newValue;
        midVol = exp( (fMid - 0.5f) * 48 / AMP_DB);
        break;
      case pHigh:
        fHigh = newValue;
        highVol = exp( (fHigh - 0.5f) * 48 / AMP_DB);
        break;
      case pMaster:
        fMaster = newValue;
        outVol = exp( (fMaster - 0.5f) * 48 / AMP_DB);
        break;
      case pLowMidFreq:
        fLowMidFreq = min(newValue, fMidHighFreq);
        freqLP = fLowMidFreq * fLowMidFreq * fLowMidFreq * 24000.0f;
        xLP  = exp(-2.0 * PI * freqLP / sampleRate);
        a0LP = 1.0 - xLP;
        b1LP = -xLP;
        break;
      case pMidHighFreq:
        fMidHighFreq = max(newValue, fLowMidFreq);
        freqHP = fMidHighFreq * fMidHighFreq * fMidHighFreq * 24000.0f;
        xHP  = exp(-2.0 * PI * freqHP / sampleRate);
        a0HP = 1.0 - xHP;
        b1HP = -xHP;
        break;
    }
}

const String DistrhoPluginAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
      case pLow:
        return "Low";
      case pMid:
        return "Mid";
      case pHigh:
        return "High";
      case pMaster:
        return "Master";
      case pLowMidFreq:
        return "Low-Mid Freq";
      case pMidHighFreq:
        return "Mid-High Freq";
    }
    return String::empty;
}

const String DistrhoPluginAudioProcessor::getParameterText (int index)
{
    switch (index)
    {
      case pLow:
        return String (log(lowVol)*AMP_DB, 1);
      case pMid:
        return String (log(midVol)*AMP_DB, 1);
      case pHigh:
        return String (log(highVol)*AMP_DB, 1);
      case pMaster:
        return String (log(outVol)*AMP_DB, 1);
      case pLowMidFreq:
        return String (freqLP, 0);
      case pMidHighFreq:
        return String (freqHP, 0);
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
    if (initialized == false)
    {
        xLP  = exp(-2.0 * PI * freqLP / sampleRate);
        a0LP = 1.0f - xLP;
        b1LP = -xLP;

        xHP  = exp(-2.0 * PI * freqHP / sampleRate);
        a0HP = 1.0 - xHP;
        b1HP = -xHP;
    }
    initialized = true;
}

void DistrhoPluginAudioProcessor::releaseResources()
{
    out1LP = out2LP = out1HP = out2HP = 0.0f;
    tmp1LP = tmp2LP = tmp1HP = tmp2HP = 0.0f;
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
        out1LP = (tmp1LP = a0LP * (*buf1) - b1LP * tmp1LP + DC_ADD) - DC_ADD;
        out2LP = (tmp2LP = a0LP * (*buf2) - b1LP * tmp2LP + DC_ADD) - DC_ADD;

        out1HP = (*buf1) - (tmp1HP = a0HP * (*buf1) - b1HP * tmp1HP + DC_ADD) - DC_ADD;
        out2HP = (*buf2) - (tmp2HP = a0HP * (*buf2) - b1HP * tmp2HP + DC_ADD) - DC_ADD;

        (*buf1++) = (out1LP*lowVol + ((*buf1) - out1LP - out1HP) * midVol + out1HP * highVol)*outVol;
        (*buf2++) = (out2LP*lowVol + ((*buf2) - out2LP - out2HP) * midVol + out2HP * highVol)*outVol;
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
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
    XmlElement xml ("3BandEQ-Settings");

    xml.setAttribute ("Low", fLow);
    xml.setAttribute ("Mid", fMid);
    xml.setAttribute ("High", fHigh);
    xml.setAttribute ("Master", fMaster);
    xml.setAttribute ("LowMidFreq", fLowMidFreq);
    xml.setAttribute ("MidHighFreq", fMidHighFreq);

    copyXmlToBinary (xml, destData);
}

void DistrhoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr && xmlState->hasTagName ("3BandEQ-Settings"))
    {
        fLow  = (float) xmlState->getDoubleAttribute ("Low", fLow);
        fMid  = (float) xmlState->getDoubleAttribute ("Mid", fMid);
        fHigh  = (float) xmlState->getDoubleAttribute ("High", fHigh);
        fMaster  = (float) xmlState->getDoubleAttribute ("Master", fMaster);
        fLowMidFreq  = (float) xmlState->getDoubleAttribute ("LowMidFreq", fLowMidFreq);
        fMidHighFreq  = (float) xmlState->getDoubleAttribute ("MidHighFreq", fMidHighFreq);
    }
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistrhoPluginAudioProcessor();
}
