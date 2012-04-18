/*-----------------------------------------------------------------------------

(C) 1999, Steinberg Soft und Hardware GmbH, All Rights Reserved

-----------------------------------------------------------------------------*/
#ifndef __BITCRUSHER_H
#define __BITCRUSHER_H

#include "d_vst.h"

enum
{
    kDistortionType = 0,
    kGain,
    kBitDepth,
    kSampleRate,
    kNumParams
};

class Bitcrusher : public AudioEffectX
{
public:
    Bitcrusher(audioMasterCallback audioMaster);
    ~Bitcrusher();

    virtual void process(float **inputs, float **outputs, long sampleFrames);
    virtual void processReplacing(float **inputs, float **outputs, long sampleFrames);
    virtual void setProgramName(char *name);
    virtual void getProgramName(char *name);
    virtual void setParameter(long index, float value);
    virtual float getParameter(long index);
    virtual void getParameterLabel(long index, char *label);
    virtual void getParameterDisplay(long index, char *text);
    virtual void getParameterName(long index, char *text);

    // originally not implemented
    virtual bool getEffectName (char* name);
    virtual bool getVendorString (char* text);
    virtual bool getProductString (char* text);
    virtual long getVendorVersion () { return 1000; }

protected:
    float fDistortionType, fGain, fBitDepth, fSampleRate;
    float bitcrush_left, bitcrush_right, hold_left, hold_right;
    int	  downsampling_pointer;
    char  programName[32];
};

#endif
