/*
  ==============================================================================

    AudioSample.h
    Created: 8 Sep 2011 2:16:36pm
    Author:  Hemmer

  ==============================================================================
*/

#ifndef __AUDIOSAMPLE_H_DED61AB8__
#define __AUDIOSAMPLE_H_DED61AB8__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../JuceLibraryCode/JucePluginCharacteristics.h"


class AudioSample 
{
public:
    AudioSample(const File &sampleSource);

    AudioSampleBuffer* getAudioData() const { return data; }

    int getSampleLength() const { return sampleLength; }
    float getSampleLengthSeconds() const { return (float) (sampleLength / sampleSampleRate); }
    int getNumChannels() const { return numChannels; }
    String getSampleName() const { return sampleName; }
    File getSampleFile() const { return sampleFile; }
    double getSampleRate() const { return sampleSampleRate; }

    // override comparison operator == 
    bool operator== (const AudioSample &s1) const;
private:
    
    // this stores the File object so
    // we can retrieve metadata (path,
    // comments etc)
    File sampleFile;        // TODO: should this be const?

    String sampleName, fileType;
    
    // information about the current sample
    int sampleLength, numChannels;
    double sampleSampleRate;
    ScopedPointer <AudioSampleBuffer> data;

    // DEBUG:
    JUCE_LEAK_DETECTOR(AudioSample);
};


#endif  // __AUDIOSAMPLE_H_DED61AB8__


