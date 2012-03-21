// Copyright (C) 2007, Michael Gruhn.
// License: LGPL - http://www.gnu.org/licenses/lgpl.html

// This uses the VST SDK 2.3. copyright as follows:
//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Example AGain (VST 1.0)
// Stereo plugin which applies a Gain [-oo, 0dB]
// (C) 2003, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#include <math.h>
#include <algorithm>

#define cAmpDB_ 8.656170245
#define cDcAdd_ 1e-30
#define cPi_ 3.141592654

inline float abs(float x){
    return ( x<0 ? -x:x);
}

inline float min (float x, float y){
    return ( x<y ? x:y);
}

inline float max (float x, float y){
    return ( x>y ? x:y);
}

#ifndef __AVST_H
#include "AVst.hpp"
#endif

//-------------------------------------------------------------------------------------------------------
AVst::AVst (audioMasterCallback audioMaster)
	: AudioEffectX (audioMaster, 1, 6)	// 1 program, 1 parameter only
{

    lowVolFader = 0.5;
    midVolFader = 0.5;
    highVolFader = 0.5;

    lowVol = midVol = highVol = 1;
    freqLPFader = 0.208706402f;
    freqHPFader = 0.436790232f;

    freqLP = 200;
    freqHP = 2000;

    outVolFader = .5;
    outVol = 1;

    xLP = exp(-2.0*cPi_*freqLP/getSampleRate());
    a0LP = 1.0-xLP;
    b1LP = -xLP;

    xHP = exp(-2.0*cPi_*freqHP/getSampleRate());
    a0HP = 1.0-xHP;
    b1HP = -xHP;

///

	setNumInputs (2);		// stereo in
	setNumOutputs (2);		// stereo out
	setUniqueID ((long)"3Beq");	// identify
	canMono ();				// makes sense to feed both inputs with the same signal
	canProcessReplacing ();	// supports both accumulating and replacing output
	strcpy (programName, "Default");	// default program name

    suspend();
}

//-------------------------------------------------------------------------------------------------------
AVst::~AVst ()
{

}


void AVst::suspend()
{
    out1LP = out2LP = out1HP = out2HP = 0;
    tmp1LP = tmp2LP = tmp1HP = tmp2HP = 0;
}

//-------------------------------------------------------------------------------------------------------
void AVst::setProgramName (char *name)
{
	strcpy (programName, name);
}

//-----------------------------------------------------------------------------------------
void AVst::getProgramName (char *name)
{
	strcpy (name, programName);
}

//-----------------------------------------------------------------------------------------
void AVst::setParameter (long index, float value)
{

    switch (index)
	{
		case 0 : 
        lowVolFader = value;
        lowVol = exp( (lowVolFader -.5)*48 / cAmpDB_);
        break;
		
        case 1 : 
        freqLPFader = min(value,freqHPFader);
        freqLP = freqLPFader*freqLPFader*freqLPFader*24000;
        xLP = exp(-2.0*cPi_*freqLP/getSampleRate());
        a0LP = 1.0-xLP;
        b1LP = -xLP;
        break;

		case 2 :
        midVolFader = value;
        midVol = exp( (midVolFader -.5)*48 / cAmpDB_);
        break;

		case 3 : 
        freqHPFader = max(value,freqLPFader);
        freqHP = freqHPFader*freqHPFader*freqHPFader*24000;
        xHP = exp(-2.0*cPi_*freqHP/getSampleRate());
        a0HP = 1.0-xHP;
        b1HP = -xHP;
        break;

		case 4 :
        highVolFader = value;
        highVol = exp( (highVolFader -.5)*48 / cAmpDB_);
        break;

		case 5 :
        outVolFader = value;
        outVol = exp( (outVolFader -.5)*48 / cAmpDB_);
        break;
	}

}

//-----------------------------------------------------------------------------------------
float AVst::getParameter (long index)
{
    float v = 0;
	switch (index)
	{
		case 0 : v = lowVolFader;   break;
		case 1 : v = freqLPFader;   break;
		case 2 : v = midVolFader;   break;
		case 3 : v = freqHPFader;   break;
		case 4 : v = highVolFader;  break;
		case 5 : v = outVolFader;   break;
	}
    return v;
}

//-----------------------------------------------------------------------------------------
void AVst::getParameterName (long index, char *label)
{
     	switch (index)
	{
		case 0 : strcpy (label, "Low");                   break;
		case 1 : strcpy (label, "Low-Mid Frequency");     break;
		case 2 : strcpy (label, "Mid");                   break;
		case 3 : strcpy (label, "Mid-High Frequency");    break;
		case 4 : strcpy (label, "High");                  break;
		case 5 : strcpy (label, "Output");                break;
	}
}

//-----------------------------------------------------------------------------------------
void AVst::getParameterDisplay (long index, char *text)
{
	switch (index)
	{
		case 0 : float2string (log(lowVol)*cAmpDB_, text);      break;
		case 1 : float2string (freqLP, text);   break;
		case 2 : float2string (log(midVol)*cAmpDB_, text);      break;
		case 3 : float2string (freqHP, text);   break;
		case 4 : float2string (log(highVol)*cAmpDB_, text);     break;
		case 5 : float2string (log(outVol)*cAmpDB_, text);      break;
        break;
	}

}

//-----------------------------------------------------------------------------------------
void AVst::getParameterLabel(long index, char *label)
{
	switch (index)
	{
		case 0 : strcpy (label, "dB");	break;
		case 1 : strcpy (label, "Hz");	break;
		case 2 : strcpy (label, "dB");	break;
		case 3 : strcpy (label, "Hz");	break;
		case 4 : strcpy (label, "dB");	break;
		case 5 : strcpy (label, "dB");  break;
	}
}

//------------------------------------------------------------------------
bool AVst::getEffectName (char* name)
{
	strcpy (name, "3-Band EQ");
	return true;
}

//------------------------------------------------------------------------
bool AVst::getProductString (char* text)
{
	strcpy (text, "3-Band EQ");
	return true;
}

//------------------------------------------------------------------------
bool AVst::getVendorString (char* text)
{
	strcpy (text, "LOSER-Development");
	return true;
}

//-----------------------------------------------------------------------------------------
void AVst::process (float **inputs, float **outputs, long sampleFrames)
{
    float *in1  =  inputs[0];
    float *in2  =  inputs[1];
    float *out1 = outputs[0];
    float *out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
    out1LP = (tmp1LP = a0LP * (*in1) - b1LP * tmp1LP + cDcAdd_) - cDcAdd_;
    out2LP = (tmp2LP = a0LP * (*in2) - b1LP * tmp2LP + cDcAdd_) - cDcAdd_;
    
    out1HP = (*in1) - (tmp1HP = a0HP * (*in1) - b1HP * tmp1HP + cDcAdd_) - cDcAdd_;
    out2HP = (*in2) - (tmp2HP = a0HP * (*in2) - b1HP * tmp2HP + cDcAdd_) - cDcAdd_;

    (*out1++) += (out1LP*lowVol + ((*in1++) - out1LP - out1HP) * midVol + out1HP * highVol)*outVol;
    (*out2++) += (out2LP*lowVol + ((*in2++) - out2LP - out2HP) * midVol + out2HP * highVol)*outVol;

    }
}

//-----------------------------------------------------------------------------------------
void AVst::processReplacing (float **inputs, float **outputs, long sampleFrames)
{
    float *in1  =  inputs[0];
    float *in2  =  inputs[1];
    float *out1 = outputs[0];
    float *out2 = outputs[1];

    while (--sampleFrames >= 0)
    {

    out1LP = (tmp1LP = a0LP * (*in1) - b1LP * tmp1LP + cDcAdd_) - cDcAdd_;
    out2LP = (tmp2LP = a0LP * (*in2) - b1LP * tmp2LP + cDcAdd_) - cDcAdd_;
    
    out1HP = (*in1) - (tmp1HP = a0HP * (*in1) - b1HP * tmp1HP + cDcAdd_) - cDcAdd_;
    out2HP = (*in2) - (tmp2HP = a0HP * (*in2) - b1HP * tmp2HP + cDcAdd_) - cDcAdd_;

    (*out1++) = (out1LP*lowVol + ((*in1++) - out1LP - out1HP) * midVol + out1HP * highVol)*outVol;
    (*out2++) = (out2LP*lowVol + ((*in2++) - out2LP - out2HP) * midVol + out2HP * highVol)*outVol;

    }
}
