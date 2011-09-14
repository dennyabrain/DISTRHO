// midiMessageManager.cpp: implementation of the midiMessageManager class.
//
//////////////////////////////////////////////////////////////////////

#include "midiMessageManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

midiMessageManager::midiMessageManager()
{
	m.clear();
	initDevices();
	midiOutputList.clear();
}

midiMessageManager::~midiMessageManager()
{
	m.clear();
	device.clear();
	midiOutputList.clear();
}

MidiBuffer midiMessageManager::getVstMidiEvents()
{
	return (vstMidiBuffer);
}

void midiMessageManager::clear()
{
	m.clear();
	vstMidiBuffer.clear();
}

void midiMessageManager::sendMessageToDevice (myMidiMessage *m)
{
	if (!m)
		return;

	if (!m->isEnabled())
		return;

	const MidiMessage *msg = m->m;
	const MidiBuffer *msgB = m->mB;

	const int deviceId = m->getDeviceId();

	if (msg && deviceId == 0)
	{
		vstMidiBuffer.addEvent (*msg, 0);
	}

	if (msg && deviceId > 0)
	{
		if (device[deviceId])
		{
			device[deviceId]->sendMessage (msg);
		}
	}
	else if (msgB && deviceId > 0)
	{
		if (device[deviceId])
		{
			device[deviceId]->sendMessageBuffer (msgB);
		}
	}

	const int e = m->getExtraEvents()->size();
	
	if (e>0)
	{
		Logger::writeToLog ("extra events");
		/* extra events from other messages go here */
	}

	if (device[deviceId])
	{
		device[deviceId]->process();
	}
}

bool midiMessageManager::isDeviceOpen(int id)
{
	if (device[id])
	{
		return (device[id]->isOpen());
	}
	else
	{
		return (false);
	}
}

void midiMessageManager::initDevices()
{
	device.clear();
	
	device.add (new midiDevice (0));

	int len = MidiOutput::getDevices().size();

	for (int x=0; x<len; x++)
	{
		device.add (new midiDevice (x+1));
	}
}

void midiMessageManager::prepareDevice (int i)
{
	/* devices are indexed on a +1 basis, due to ComboBox internals
		subtract one but only in this method, don't do it anywhere else */

	int deviceId = i-1;
	Logger::writeToLog (String::formatted ("prepareDevice: %d", deviceId));

	if (deviceId == 0)
	{
		Logger::writeToLog ("internal midi device, no need to open");
		return;
	}

	if (device[deviceId])
	{
		if (device[deviceId]->isOpen())
		{
			Logger::writeToLog ("device already opened");
			return;
		}
		else
		{
			Logger::writeToLog ("device not opened, trying");
			device[deviceId]->openDevice();
		}
	}
}

int midiMessageManager::getCurrentEventsCount()
{
	return (m.size());
}