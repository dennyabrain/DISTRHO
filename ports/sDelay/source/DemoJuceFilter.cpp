/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "includes.h"
#include "DemoJuceFilter.h"
#include "sDelayEditorComponent.h"


//==============================================================================
/**
    This function must be implemented to create a new instance of your
    plugin object.
*/
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DemoJuceFilter();
}

//==============================================================================
DemoJuceFilter::DemoJuceFilter()
{
    samplingRate = 44100;
	maxDelayTime = 3000;			// (ms) Max delay time, must equal max value of slider on GUI
	delayTime = 0.5;				// Starting delay time, % of maxDelayTime, must be between 0 and 1 for host
	feedback = 0.5;					// Feedback level, 0-100%, must be between 0 and 1 for host
	gain = 0.5;						// Gain level, 0-100%, must be between 0 and 1 for host
	
	delayLineLength = (int)((maxDelayTime/1000) * samplingRate);	//over 1000 because maxDelayTime in milliseconds
	delayLine = new float[delayLineLength];
	
	endPtr = delayLine + delayLineLength;
	rwPtr = delayLine;
	
	setDelay(delayTime);		//Resets endPtr to specified delayTime
	
}

DemoJuceFilter::~DemoJuceFilter()
{
}

//==============================================================================
void DemoJuceFilter::setDelay(float delay)
{
	delayTime = delay;
	delayLineLength = (int)(((delayTime*maxDelayTime)/1000) * samplingRate);	//over 1000 because maxDelayTime in milliseconds
	endPtr = delayLine + delayLineLength;
}

const String DemoJuceFilter::getName() const
{
    return "Juce sDelay Filter";
}

int DemoJuceFilter::getNumParameters()
{
    return kNumParams;
}

float DemoJuceFilter::getParameter (int index)
{
    float v = 0; 

	switch (index) 
	{ 
		case kDelay :		v = delayTime;	break; 
		case kFeedback :	v = feedback;	break; 
		case kGain :		v = gain;		break;
	} 
	
	return v; 
}

void DemoJuceFilter::setParameter (int index, float newValue)
{
    switch (index) 
	{ 
		case kDelay:{	
						setDelay(newValue); 
						sendChangeMessage (); 
						break; 
					}
		case kFeedback:{	
							feedback = newValue; 
							sendChangeMessage (); 
							break; 
						}
		case kGain:{
						gain = newValue; 
						sendChangeMessage (); 
						break; 
					}	
	} 
}

const String DemoJuceFilter::getParameterName (int index)
{
    switch (index) 
	{ 
		case kDelay :		return "Delay (0-3sec)"; 
							break; 
		case kFeedback :	return "Feedback";
							break; 
		case kGain :		return "Gain";
							break; 
		default:			return String::empty; break;
	} 
}

const String DemoJuceFilter::getParameterText (int index)
{
    switch (index) 
	{ 
		case kDelay :		return String (delayTime, 2);	break; 
		case kFeedback :	return String (feedback, 2);	break; 
		case kGain :		return String (gain, 2);		break; 
		default:			return String::empty;
	} 
}

const String DemoJuceFilter::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String DemoJuceFilter::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool DemoJuceFilter::isInputChannelStereoPair (int index) const
{
    return false;
}

bool DemoJuceFilter::isOutputChannelStereoPair (int index) const
{
    return false;
}

bool DemoJuceFilter::acceptsMidi() const
{
    return false;
}

bool DemoJuceFilter::producesMidi() const
{
    return false;
}

void DemoJuceFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// do your pre-playback setup stuff here..
}
   
void DemoJuceFilter::releaseResources()
{
	// when playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

void DemoJuceFilter::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
		int numSamples = buffer.getNumSamples();
		float* in1 = buffer.getSampleData(0, 0);
		float* in2;

		//capture pointer for second input's data
		if(getNumInputChannels() > 1 || getNumOutputChannels() > 1){
			in2 = buffer.getSampleData(1, 0);
		}
		while (--numSamples >= 0)
		{
			//setup signal pointers
			input = in1++;
			output = input;
			
			//get delayed samples from delayLine
			delayLineOutput = *rwPtr;
			
			//write the input sample and any feedback to delayline
			*rwPtr = *input + (feedback * delayLineOutput);
			
			//add the delayed sample and the current input to create the output, scale by gain
			*output = gain * (*input + delayLineOutput);
				
			//write to output if stereo
			if(getNumOutputChannels() > 1){
				*in2++ = *output;
			}

			//increment delayLine index and wrap if necesary
			if (++rwPtr >= endPtr)
			  rwPtr = delayLine;
				
		}
		

    // in case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
AudioProcessorEditor* DemoJuceFilter::createEditor()
{
    return new sDelayEditorComponent (this);
}

//==============================================================================
void DemoJuceFilter::getStateInformation (MemoryBlock& destData)
{
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

    // create an outer XML element..
    XmlElement xmlState ("MYPLUGINSETTINGS");

    // add some attributes to it..
    xmlState.setAttribute ("pluginVersion", 1);
    xmlState.setAttribute ("delayTime", delayTime);
	xmlState.setAttribute ("feedback", feedback);
	xmlState.setAttribute ("gain", gain);
    // you could also add as many child elements as you need to here..


    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void DemoJuceFilter::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our parameters..
            delayTime = (float) xmlState->getDoubleAttribute ("delayTime", delayTime);
			feedback = (float) xmlState->getDoubleAttribute ("feedback", feedback);
			gain = (float) xmlState->getDoubleAttribute ("gain", gain);

            sendChangeMessage ();
        }

        delete xmlState;
    }
}
