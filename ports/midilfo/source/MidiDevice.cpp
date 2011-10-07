/*
 *  MidiDevice.cpp
 *  MidiLFO
 *
 *  Midi-Lfo: This is a small project using the JUCE library.
 *	It provides a user tweakable Midi LFO. This sends a
 *	(selectable) CC with LFO modulated values to a
 *	(selectable) Midi output.
 *
 *	Copyright (C) 2009, Christian Stoecklmeier and Volker Duemke
 * 
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MidiDevice.h"

#include "MyMidiInputCallback.h"

MidiDevice::MidiDevice() 
: myMidiCallback(0)
, midiInputSync(0)
, midiOutput(0)
,midiInputSyncStarted(false)
,midiOutputReady(false)
{
	myMidiCallback = new MyMidiInputCallback();
}

MidiDevice::~MidiDevice()
{
	if (midiInputSync)
		midiInputSync->stop();
	
	if (myMidiCallback != 0)
		deleteAndZero (myMidiCallback);
	
	if(midiOutput)
		midiOutput->stopBackgroundThread();
}

void MidiDevice::setMidiInputSync (int ndx)
{

	if(midiInputSyncStarted == true)
		midiInputSync->stop();
	midiInputSync = MidiInput::openDevice (ndx, myMidiCallback);
	midiInputSync->start();
	midiInputSyncStarted = true;
}

void MidiDevice::setMidiOutput (int ndx)
{
	midiOutput = MidiOutput::openDevice(ndx);
	midiOutput->startBackgroundThread();
}

void MidiDevice::sendMidiMessage(MidiMessage msg)
{
	const MidiMessage& constmsg = msg;
	if (midiOutput)
		midiOutput->sendMessageNow (constmsg);
}

void MidiDevice::setProcessingCore(ProcessingCore* core) 
{
	myMidiCallback->setProcessingCore(core);
};


