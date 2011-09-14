// myMidiMessage.cpp: implementation of the myMidiMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "myMidiMessage.h"
#include "sklepSeqPattern.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

myMidiMessage::myMidiMessage(int ch, int nIndex, sklepSeqPattern *owner)
{
	multi			= false;
	m				= 0;
	mB				= 0;
	index			= nIndex;
	messageLength	= 0;
	enabled			= false;
	midiChannel		= ch;
	deviceId		= 0;
	ownerPattern	= owner;
	noteOff			= 0;
}

myMidiMessage::~myMidiMessage()
{
}

void myMidiMessage::setOwner (sklepSeqPattern *owner)
{
	ownerPattern = owner;
}

Array <myMidiMessage *>*myMidiMessage::getExtraEvents()
{
	return (&extraMessages);
}

/* append a midi message as the first one on stack
	if the message is a single message, make it a multi
*/
void myMidiMessage::insertMidiMessage (MidiMessage midiMessage)
{
	if (isMulti())
	{
		MidiBuffer copy;
		MidiBuffer::Iterator i (*mB);
		MidiMessage msg(0xf0, 0.0);
		int pos;

		copy.addEvent (midiMessage, 0);

		while (i.getNextEvent (msg, pos))
		{
			copy.addEvent (msg, pos+1);
		}

		if (mB)
			deleteAndZero (mB);

		mB = new MidiBuffer (copy);
	}
	else
	{
		multi = true;
		MidiBuffer copy;

		copy.addEvent (midiMessage, 0);
		copy.addEvent (*m, 1);

		mB = new MidiBuffer (copy);

		deleteAndZero (m);
	}
}

void myMidiMessage::setMidiChannel (int ch)
{
	if (m)
	{
		m->setChannel (ch);
		midiChannel = ch;
	}
}

void myMidiMessage::setMidiMessage (MidiMessage midiMessage, int len)
{
	multi	= false;
	
	if (m)
		deleteAndZero (m);

	if (mB)
		deleteAndZero (mB);

	m		= new MidiMessage (midiMessage);
	m->setTimeStamp ((double)index);

	if (!m->isSysEx())
	{
		m->setChannel (midiChannel);
	}

	setEnabled(true);

	if (m->isNoteOn())
	{
		setLength (len);
	}
}

void myMidiMessage::setMidiMessageRaw (uint8 *data, int dataLen)
{
	multi	= false;

	if (m)
		deleteAndZero (m);

	if (mB)
		deleteAndZero (mB);

	m		= new MidiMessage (data, dataLen, 0);
	m->setTimeStamp ((double)index);

	setEnabled(true);
	setLength (1);
}

void myMidiMessage::setMidiMessageMulti (MidiBuffer midiBuffer)
{
	multi	= true;

	if (m)
		deleteAndZero (m);

	if (mB)
		deleteAndZero (mB);

	mB		= new MidiBuffer(midiBuffer);
	setEnabled(true);
}

bool myMidiMessage::isMulti()
{
	return (multi);
}

MidiMessage *myMidiMessage::getMidiMessage()
{
	if (m)
	{
		return (m);
	}
	else
	{
		return (0);
	}
}

MidiBuffer *myMidiMessage::getMidiBuffer()
{
	if (mB)
	{
		return (mB);
	}
	else
	{
		return (0);
	}
}

int myMidiMessage::getIndex()
{
	return (index);
}

void myMidiMessage::setMidiDevice (int dId)
{
	if (deviceId < 0)
	{
		deviceId = 0;
		return;
	}

	deviceId = dId;
}

int myMidiMessage::getDeviceId ()
{
	return (deviceId);
}

void myMidiMessage::setLength (short l)
{
	if (l != messageLength)
	{
		Logger::writeToLog ("setLength()");
		/* midi len changed */
		myMidiMessage *noteOffMessage = ownerPattern->getStep (getMyNoteOff());

		/* remove my note off */
		noteOffMessage->removeExtra (noteOff);

		/* set new length */
		messageLength = l;

		/* add my new note off based on my new length */
		const int myNoteOffIndex = getMyNoteOff();
		ownerPattern->setEnabled (myNoteOffIndex, false);
		noteOffMessage = ownerPattern->getStep (myNoteOffIndex);

		if (noteOff)
		{
			/* we can do this, the array in the note off event is not a ownedArray */
			deleteAndZero (noteOff);
		}

		noteOff = new myMidiMessage (midiChannel, 1, ownerPattern);
		noteOff->setMidiMessage (MidiMessage::noteOff (midiChannel, m->getNoteNumber()));
		noteOffMessage->addExtra (noteOff);
	}
}

short myMidiMessage::getLength ()
{
	return (messageLength);
}

short myMidiMessage::getMyNoteOff()
{
	if (messageLength+index < 32)
	{
		return (messageLength+(index+1));
	}
	else
	{
		/* d0h */
		return ((32 - (index+1))+messageLength);
	}
}

void myMidiMessage::removeExtra (myMidiMessage *_m)
{
	if (_m)
	{
		extraMessages.removeValue (_m);
	}
}

void myMidiMessage::addExtra(myMidiMessage *_m)
{
	if (_m)
	{
		Logger::writeToLog ("addExtra()");
		extraMessages.add (_m);
	}
}

bool myMidiMessage::isEnabled ()
{
	return (enabled);
}

void myMidiMessage::setEnabled (bool t, bool initialCheck)
{
	if (t != enabled && initialCheck)
		enablementChanged();

	enabled = t;
}

void myMidiMessage::enablementChanged()
{
	if (isEnabled())
	{
		/* we are beeing deactivated*/
	}
	else
	{
		/* we are beeing turned on */
		if (!isMulti())
		{
			if (!m)
			{
				/* this is a initial midi message */
				m = new MidiMessage (MidiMessage::noteOn (midiChannel, 64, 1.0f));
				m->setTimeStamp ((double)index);
				setLength(1);
			}
		}
	}
}