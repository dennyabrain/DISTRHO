// sklepSeqPattern.cpp: implementation of the sklepSeqPattern class.
//
//////////////////////////////////////////////////////////////////////

#include "sklepSeqPattern.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sklepSeqPattern::sklepSeqPattern(int _id)
{
	patternId		=	_id;
	patternLength	=	16;
	isActive		=	false;
	currentPosition	=	1;
	mode			=	patternForward;
	midiChannel		=	1;
	midiDevice		=	1;
	syncMode		=	true;
	waitingForSync	=	false;

	for (int x=0; x<32; x++)
	{
		notes.add (new myMidiMessage(midiChannel, x, this));
	}
}

sklepSeqPattern::~sklepSeqPattern()
{
	notes.clear();
}

int sklepSeqPattern::getPatternId()
{
	return (patternId);
}

void sklepSeqPattern::setPatternLength(int len)
{
	if (len > 32 || len < 1)
		patternLength = 16;
	else
		patternLength = len;
}

int sklepSeqPattern::getPatternLength()
{
	return (patternLength);
}

void sklepSeqPattern::forward(int pos)
{
	/* pattern is not active, or nothing changed */
	if (pos == currentPosition || !isActive)
		return;

	if (patternHasBeenActivated && syncMode && isActive)
	{
		/* full sync mode, start at beat start */
		if (pos!=patternLength)
		{
			waitingForSync = true;
			return;
		}

		waitingForSync = false;

		currentPosition = pos;
		patternHasBeenActivated = false;
	}
	else if (patternHasBeenActivated && !syncMode && isActive)
	{
		/* half sync mode, start at next step */
		currentPosition = pos;
		patternHasBeenActivated = false;
	}

	if (mode == patternForward)
		currentPosition++;

	if (mode == patternReverse)
		currentPosition--;

	if (currentPosition > patternLength)
	{
		currentPosition = (currentPosition - patternLength);
	}

	triggerEvents();
}

void sklepSeqPattern::triggerEvents ()
{
	if (notes[currentPosition-1]->enabled)
	{
		midiManager->sendMessageToDevice (notes[currentPosition-1]);
	}
}

void sklepSeqPattern::setActive (bool t)
{
	if (!isActive)
	{
		patternHasBeenActivated = true;
	}

	isActive = t;
}

bool sklepSeqPattern::getActive ()
{
	return (isActive);
}

int sklepSeqPattern::getCurrentPosition ()
{
	return (currentPosition);
}

void sklepSeqPattern::addMidiManager (midiMessageManager *m)
{
	midiManager = m;
}

void sklepSeqPattern::setStep (int nId, int nNumber, float nVelo)
{
	if (nNumber == 0 && nVelo == 0.0)
	{
		if (notes[nId]->enabled)
		{
			notes[nId]->enabled = false;
			deleteAndZero (notes[nId]->m);
		}
	}
	else
	{
		if (notes[nId]->enabled)
			deleteAndZero (notes[nId]->m);
		
		notes[nId]->m = new MidiMessage (MidiMessage::noteOn (midiChannel, nNumber, nVelo));
	}
}

myMidiMessage* sklepSeqPattern::getStep (int nId)
{
	if (notes[nId])
	{
		if (notes[nId]->enabled)
			return (notes[nId]);
		else
			return (0);
	}
	else
	{
		return (0);
	}
}

myMidiMessage* sklepSeqPattern::getStepNoVeirfy (int nId)
{
	if (notes[nId])
	{
		return (notes[nId]);
	}
	else
	{
		return (0);
	}
}

void sklepSeqPattern::toggleStep(int nId)
{
	if (notes[nId])
	{
		if (notes[nId]->isEnabled())
		{
			notes[nId]->setEnabled (false, true);
		}
		else
		{
			notes[nId]->setEnabled (true, true);
		}
	}
}

void sklepSeqPattern::setMidiChannel (int c)
{
	if (c>1 && c<16)
		midiChannel = c;
	else
		midiChannel = 1;

	for (int x=0; x<notes.size(); x++)
	{
		if (notes[x])
		{
			notes[x]->setMidiChannel (midiChannel);
		}
	}
}

int sklepSeqPattern::getMidiChannel ()
{
	return (midiChannel);
}

void sklepSeqPattern::setMidiDevice (int d)
{
	Logger::writeToLog (T("pattern, set midi device"));
	
	for (int x=0; x<32; x++)
	{
		if (notes[x])
		{
			notes[x]->setMidiDevice (d-1);
		}
	}

	midiManager->prepareDevice (d);
	midiDevice = d;
}

int sklepSeqPattern::getMidiDevice ()
{
	return (midiDevice);
}

MidiMessageSequence sklepSeqPattern::serialize()
{
	MidiMessageSequence sequence;

	for (int x=0; x<32; x++)
	{
		if (!notes[x]->isMulti())
		{
			if (notes[x]->getMidiMessage())
			{
				Logger::writeToLog (String::formatted (T("add message with len %.2f to seq"), notes[x]->getMidiMessage()->getTimeStamp()));
				sequence.addEvent (*notes[x]->getMidiMessage());
			}
		}
		else
		{
			MidiBuffer *mB = notes[x]->getMidiBuffer();
			MidiBuffer::Iterator i (*mB);
			MidiMessage msg(0xf0, 0.0);
			int pos;

			while (i.getNextEvent (msg, pos))
			{
				msg.setTimeStamp ((double)x+1);
				sequence.addEvent (msg);
			}
		}
	}

	return (sequence);
}

void sklepSeqPattern::reset()
{
	currentPosition = 1;
}

void sklepSeqPattern::unserialize (const MidiMessageSequence *seq)
{
	int realEvents = 0;
	for (int x=0; x<seq->getNumEvents(); x++)
	{
		if (realEvents>31)
			break;

		MidiMessageSequence::MidiEventHolder *e = seq->getEventPointer (x);

		if (e->message.isNoteOn())
		{
			const int position = (int)e->message.getTimeStamp();
			notes[position]->setMidiMessage (e->message);

			realEvents++;

			Logger::writeToLog (T("midiFile load noteon"));
		}
		if (e->message.isController())
		{
			/* can be a sequence of 4 messages, check */
			const int ctrlrNumber = e->message.getControllerNumber();

			if ((ctrlrNumber >= 98 && ctrlrNumber < 101) || (ctrlrNumber == 38 || ctrlrNumber == 6))
			{
				Logger::writeToLog (T("midiFile load controller MULTI"));
				continue;
			}

			const int position = (int)e->message.getTimeStamp();
			notes[position]->setMidiMessage (e->message);

			realEvents++;

			Logger::writeToLog (T("midiFile load controller"));
		}
		if (e->message.isSysEx())
		{
			/* this can also be a sequence of messages */
			const int position = (int)e->message.getTimeStamp();
			notes[position]->setMidiMessage (e->message);

			realEvents++;

			Logger::writeToLog (T("midiFile load sysex"));
		}
	}
}

void sklepSeqPattern::setSyncMode (bool m)
{
	syncMode = m;
}

bool sklepSeqPattern::getSyncMode()
{
	return (syncMode);
}

bool sklepSeqPattern::isWaitingForSync()
{
	return (waitingForSync);
}

void sklepSeqPattern::setEnabled (int nIndex, bool noInitialCheck)
{
	if (notes[nIndex])
	{
		notes[nIndex]->setEnabled (true, noInitialCheck);
	}
}