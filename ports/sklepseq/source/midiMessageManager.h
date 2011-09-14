// midiMessageManager.h: interface for the midiMessageManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIMESSAGEMANAGER_H__198293E7_B17B_4844_A44A_42B7E392EEDD__INCLUDED_)
#define AFX_MIDIMESSAGEMANAGER_H__198293E7_B17B_4844_A44A_42B7E392EEDD__INCLUDED_

#include <juce.h>
#include "myMidiMessage.h"
#include "midiDevice.h"

class midiMessageManager  
{
	public:
		midiMessageManager();
		~midiMessageManager();
		void clear();
		void sendMessageToDevice (myMidiMessage *m);
		bool isDeviceOpen(int id);
		void initDevices();
		void prepareDevice(int i);
		int getCurrentEventsCount ();
		MidiBuffer getVstMidiEvents();

	private:
		StringArray midiOutputList;
		OwnedArray <myMidiMessage> m;
		OwnedArray <midiDevice> device;
		MidiBuffer vstMidiBuffer;
};

#endif // !defined(AFX_MIDIMESSAGEMANAGER_H__198293E7_B17B_4844_A44A_42B7E392EEDD__INCLUDED_)
