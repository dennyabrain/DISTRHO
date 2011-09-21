/*
  ==============================================================================

    SampleStrip.h
    Created: 13 Sep 2011 1:07:11pm
    Author:  Hemmer

    This class is the logic version equivalent of WaveformControl.

  ==============================================================================
*/

#ifndef __SAMPLESTRIP_H_ACB589A6__
#define __SAMPLESTRIP_H_ACB589A6__

#include "AudioSample.h"

class SampleStrip
{
public:
    SampleStrip();
    ~SampleStrip()
    {
    }

    enum SampleStripParameter
    {
        FirstParam,                     // This is so we can loop over GUI params
        ParamIsPlaying = FirstParam,
        ParamCurrentChannel,        
        ParamNumChunks,
        ParamPlayMode,
        ParamIsLatched,
        ParamIsReversed,
        ParamStripVolume,
        ParamPlaySpeed,
        ParamIsPlaySpeedLocked,
        ParamPlaybackPercentage,
        ParamFractionalStart,
        ParamFractionalEnd,
        ParamAudioSample,
        NumGUIParams,
        // The above are the only params needed by the GUI
         
        ParamChunkSize = NumGUIParams,
        ParamSampleStart,       // these return the key sample points
        ParamSampleEnd,         // (taking selection into account)

        TotalNumParams
    };

    enum PlayMode
    { 
        LOOP = 1,               // starts the sample looping
        LOOP_CHUNK,             // loops the chunk associated with a button
        PLAY_TO_END             // plays from current point until the end then stops
    };


    String getParameterName(const int &parameterID) const
    {
        switch(parameterID)
        {
        case ParamCurrentChannel : return "current channel";
        case ParamNumChunks : return "num chunks";
        case ParamPlayMode : return "playmode";
        case ParamIsLatched : return "is latched";
        case ParamIsReversed : return "is reversed";
        case ParamStripVolume : return "strip volume";
        case ParamPlaySpeed : return "play speed";
        case ParamIsPlaySpeedLocked : return "is play speed locked";
        case ParamIsPlaying : return "is playing";
        case ParamChunkSize : return "chunk size";
        case ParamFractionalStart : return "fractional start";
        case ParamFractionalEnd : return "fractional end";
        case ParamAudioSample : return "audio sample";
        case ParamPlaybackPercentage : return "playback percentage";
        default : jassert(false); return "parameter not found";
        }
    }


    // these are for getting / setting the int parameters
    void setSampleStripParam(const int &parameterID, const void *newValue);
    const void* getSampleStripParam(const int &parameterID) const;

    void updatePlaySpeedForBPMChange(const double &newBPM);
    void updatePlaySpeedForSelectionChange();
    void findInitialPlaySpeed(const double &BPM, const float &hostSampleRate);

    void modPlaySpeed(const double &factor) { playSpeed *= factor; }
private:

    // These are just so the GUI can show where in the sample we are
    bool isPlaying;
    float playbackPercentage;

    // Pointer to currently selected sample
    const AudioSample *currentSample;
    int totalSampleLength;
    double sampleSampleRate;

    // start / end points (fractional, i.e. 0.5 is half way through)
    float fractionalSampleStart, fractionalSampleEnd;
    // start / end / length of the selection (in samples)
    int selectionStart, selectionEnd, selectionLength;

    // How many blocks the sample is split up into...
    int numChunks;
    // ...and what size are they (in samples).
    int chunkSize;

    int currentChannel;

    // Playback options
    int currentPlayMode;
    bool isReversed, isLatched;
    float stripVolume;
    double playSpeed;
    bool isPlaySpeedLocked;

    double previousBPM;
    int previousSelectionLength;
};



#endif  // __SAMPLESTRIP_H_ACB589A6__
