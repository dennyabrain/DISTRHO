
#ifndef __DISTRHOPLUGINPROCESSOR_H__
#define __DISTRHOPLUGINPROCESSOR_H__

#include "DistrhoPlugin.h"
#include "DistrhoPluginUtils.h"

//==================================================================================
class DistrhoPluginAudioProcessor : public DISTRHO::Plugin
{
public:
    //==============================================================================
    enum Parameters
    {
      pLow = 0,
      pMid,
      pHigh,
      pMaster,
      pLowMidFreq,
      pMidHighFreq,
      pMAX
    };

    //==============================================================================
    DistrhoPluginAudioProcessor();
    ~DistrhoPluginAudioProcessor();

protected:
    // Information
    const char* d_name()
    {
        return "3 Band EQ";
    }

    const char* d_label()
    {
        return "3BandEQ";
    }

    const char* d_maker()
    {
        return "DISTRHO";
    }

    const char* d_license()
    {
        return "";
    }

    uint32_t d_version()
    {
        return 0x1000;
    }

    long d_uniqueId()
    {
        return CCONST('D', '3', 'E', 'Q');
    }

    // Init
    void d_initParameter(uint32_t index, DISTRHO::Parameter& parameter);

    // Internal data
    float d_parameterValue(uint32_t index);
    //void  d_parameterText(uint32_t index, char* strBuf);
    void  d_setParameterValue(uint32_t index, float value);

    // Process
    void d_activate();
    void d_deactivate();
    void d_run(const float* const* inputs, float* const* outputs, uint32_t frames, uint32_t midiEventCount, const DISTRHO::MidiEvent* midiEvents);

#if 0
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
    void  setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool  isInputChannelStereoPair (int index) const;
    bool  isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;

    //==============================================================================
    int  getNumPrograms();
    int  getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void  changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
#endif

private:
    //==============================================================================
    float fLow, fMid, fHigh, fMaster, fLowMidFreq, fMidHighFreq;

    //==============================================================================
    float lowVol, midVol, highVol, outVol;
    float freqLP, freqHP;

    float xLP, a0LP, b1LP;
    float xHP, a0HP, b1HP;

    float out1LP, out2LP, out1HP, out2HP;
    float tmp1LP, tmp2LP, tmp1HP, tmp2HP;
};

#endif  // __DISTRHOPLUGINPROCESSOR_H__
