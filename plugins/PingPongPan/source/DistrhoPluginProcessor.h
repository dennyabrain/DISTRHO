
#ifndef __DISTRHOPLUGINPROCESSOR_H__
#define __DISTRHOPLUGINPROCESSOR_H__

#include "JuceHeader.h"
#include "JucePluginCharacteristics.h"

//==================================================================================
class DistrhoPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DistrhoPluginAudioProcessor();
    ~DistrhoPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    enum Parameters
    {
      pFreq = 0,
      pWidth,
      pMAX
    };

private:
    //==============================================================================
    float freqFader;
    float waveSpeed;
    float width;

    float pan, wavePos;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistrhoPluginAudioProcessor);
};

#endif  // __DISTRHOPLUGINPROCESSOR_H__
