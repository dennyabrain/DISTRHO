#include "midiDevice.h"

midiDevice::midiDevice (int _deviceIndex)
{
	deviceIndex = _deviceIndex;
	d			= 0;
	open		= false;	
}

midiDevice::~midiDevice()
{
	if (d)
	{
		Logger::writeToLog (String::formatted ("close device: %d", deviceIndex));
		d->stopBackgroundThread();

		deleteAndZero (d);
	}
}

bool midiDevice::openDevice ()
{
	Logger::writeToLog (String::formatted ("opening device: %d", deviceIndex));
	if (d || deviceIndex == 0)
	{
		open = true;
		return (true);
	}

	d = MidiOutput::openDevice (deviceIndex);
			
	if (d)
	{
		Logger::writeToLog ("success!!!");
		d->startBackgroundThread();

		open = true;
		return (true);
	}
	else
	{
		Logger::writeToLog ("FAILED!!!");
		open = false;
		d = 0;
		return (false);
	}
}
		
void midiDevice::sendMessage (const MidiMessage *m)
{
	if (isOpen())
	{
		Logger::writeToLog (String::formatted ("send message"));
		d->sendMessageNow (*m);
	}
	else
	{
		return;
	}
}

void midiDevice::sendMessageBuffer (const MidiBuffer *mb)
{
	if (isOpen())
	{
		MidiBuffer::Iterator i (*mb);
		int len;
		MidiMessage message (0xf4, 0.0);

		while (i.getNextEvent (message, len))
		{
			sendMessage (&message);
		}
	}
	else
	{
		return;
	}
}

void midiDevice::process()
{
	if (d)
	{
		d->clearAllPendingMessages();
	}
}
bool midiDevice::isOpen()
{
	return (open);
}

