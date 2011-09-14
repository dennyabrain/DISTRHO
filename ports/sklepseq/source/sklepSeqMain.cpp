#include <juce.h>
#include "sklepSeqMain.h"
#include "sklepSeqEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DemoJuceFilter();
}

DemoJuceFilter::DemoJuceFilter()
{
	for (int x=0; x<64; x++)
	{
		patterns.add (new sklepSeqPattern(x));
		patterns[x]->setActive (false);
		patterns[x]->addMidiManager (&midiManager);
		activePatterns.add (false);
	}

	activePatterns.set (0, true);
	patterns[0]->setActive (true);
	_p = 0;

	currentPattern = 0;
	currentPatternPtr = patterns[0];
	
	intBpm = currentBpm = 120;
	syncThread = new xsync();
	syncThread->setBPM (120);
	syncThread->addChangeListener (this);
	isSyncedToHost = false;

    zeromem (&lastPosInfo, sizeof (lastPosInfo));
    lastPosInfo.timeSigNumerator = 4;
    lastPosInfo.timeSigDenominator = 4;
    lastPosInfo.bpm = 120;
}

DemoJuceFilter::~DemoJuceFilter()
{
	syncThread->signalThreadShouldExit();

	deleteAndZero (syncThread);
}

const String DemoJuceFilter::getName() const
{
    return "sklepSeq";
}

int DemoJuceFilter::getNumParameters()
{
    return 1;
}

float DemoJuceFilter::getParameter (int index)
{
	return (0.0);
}

void DemoJuceFilter::setParameter (int index, float newValue)
{
}

const String DemoJuceFilter::getParameterName (int index)
{
    return String::empty;
}

const String DemoJuceFilter::getParameterText (int index)
{
    return String::empty;
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
    return true;
}

bool DemoJuceFilter::producesMidi() const
{
    return true;
}

void DemoJuceFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    keyboardState.reset();
}

void DemoJuceFilter::releaseResources()
{
}

void DemoJuceFilter::changeListenerCallback(ChangeBroadcaster *ptr)
{
	/* this is called by our internal sync thread */
	if (!isSyncedToHost)
	{
		MidiBuffer b;
		const int beat = ((xsync *)ptr)->getMidiSixteenthNote();
		currentBpm = ((xsync *)ptr)->getBpm();

		Logger::writeToLog (String::formatted ("_p=%d beat=%d", _p, beat));

		if (_p != beat)
		{
			for (int x=0; x<64; x++)
			{
				if (activePatterns[x])
				{
					patterns[x]->forward(beat+1);
				}
			}

			currentBeat = currentPatternPtr->getCurrentPosition();

			if (currentBeat > 16)
				currentBeat = currentBeat - 16;
			
			midiManager.clear();

			sendChangeMessage ();
		}

		_p = beat;
	}
}

void DemoJuceFilter::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
	if (isSyncedToHost)
	{
		AudioPlayHead::CurrentPositionInfo pos;

		if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition (pos))
		{
	        if (memcmp (&pos, &lastPosInfo, sizeof (pos)) != 0)
			{
	            lastPosInfo = pos;

				const int ppqPerBar		= (pos.timeSigNumerator * 4 / pos.timeSigDenominator);
				const double beats		= (fmod (pos.ppqPosition, ppqPerBar) / ppqPerBar) * pos.timeSigNumerator;
				const double position	= beats*4;
				const int beat			= (int)position;
				
				currentBpm	= (int)pos.bpm;

				if (_p != beat)
				{
					for (int x=0; x<64; x++)
					{
						if (activePatterns[x])
						{
							patterns[x]->forward(beat+1);
						}
					}

					currentBeat = currentPatternPtr->getCurrentPosition();

					if (currentBeat > 16)
						currentBeat = currentBeat - 16;

					/* process midi events to their devices */
					midiMessages.addEvents (midiManager.getVstMidiEvents(),0,-1,0);

					/* clean the buffers */
					midiManager.clear();

					sendChangeMessage ();
				}
				
				_p = beat;
			}
		}
		else
		{
	        zeromem (&lastPosInfo, sizeof (lastPosInfo));
			lastPosInfo.timeSigNumerator = 4;
	        lastPosInfo.timeSigDenominator = 4;
			lastPosInfo.bpm = 120;
	   }	
	}
}

AudioProcessorEditor* DemoJuceFilter::createEditor()
{
    return new DemoEditorComponent (this);
}

void DemoJuceFilter::getStateInformation (MemoryBlock& destData)
{
    XmlElement xmlState ("MYPLUGINSETTINGS");
    xmlState.setAttribute ("pluginVersion", 1);
    copyXmlToBinary (xmlState, destData);
}

void DemoJuceFilter::setStateInformation (const void* data, int sizeInBytes)
{
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
    if (xmlState != 0)
    {
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            sendChangeMessage ();
        }
        delete xmlState;
    }
}

sklepSeqPattern *DemoJuceFilter::getCurrentPattern()
{
	return (currentPatternPtr);
}

void DemoJuceFilter::setCurrentPattern (int p)
{
	if (patterns[p])
	{
		currentPatternPtr = patterns[p];
		currentPattern = p;
	}
	else
	{
		currentPatternPtr = patterns[0];
		currentPattern = 0;
	}
}

void DemoJuceFilter::setSyncToHost (bool t)
{
	if (t != isSyncedToHost)
	{
		zeromem (&lastPosInfo, sizeof (lastPosInfo));
		lastPosInfo.timeSigNumerator = 4;
		lastPosInfo.timeSigDenominator = 4;
		lastPosInfo.bpm = 120;
		sendChangeMessage ();
	}
	
	if (!t)
	{
		syncThread->setBPM (intBpm);
		syncThread->startThread();
	}
	else
	{
		syncThread->signalThreadShouldExit();
	}
	isSyncedToHost = t;
}

bool DemoJuceFilter::getSyncToHost ()
{
	return (isSyncedToHost);
}

void DemoJuceFilter::activatePattern (bool t, int pId)
{
	if (patterns[pId])
	{
		addPatternToActiveList (t, pId);
		patterns[pId]->setActive (t);
	}
}

void DemoJuceFilter::addPatternToActiveList (bool t, int pId)
{
	activePatterns.set (pId, t);
}

void DemoJuceFilter::setBpm (int b)
{
	intBpm = b;
	syncThread->setBPM (intBpm);
}

int DemoJuceFilter::getBpm ()
{
	return (currentBpm);
}

void DemoJuceFilter::transportStop()
{
	if (!getSyncToHost())
	{
		if (syncThread->isThreadRunning())
		{
			syncThread->signalThreadShouldExit();
			restartSequencer();
		}
	}
}

void DemoJuceFilter::transportPlay()
{
	if (!getSyncToHost())
	{
		if (!syncThread->isThreadRunning())
		{
			syncThread->startThread();
		}
	}
}

void DemoJuceFilter::transportPause()
{
	if (!getSyncToHost())
	{
		if (syncThread->isThreadRunning())
		{
			syncThread->signalThreadShouldExit();
		}
	}
}

void DemoJuceFilter::restartSequencer()
{
	for (int x=0; x<64; x++)
	{
		if (activePatterns[x])
		{
			patterns[x]->reset();
		}
	}

	_p = -1;
}

sklepSeqPattern *DemoJuceFilter::getPattern(int pId)
{
	return (patterns[pId]);
}