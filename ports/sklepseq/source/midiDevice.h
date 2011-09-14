// midiDevice.h: interface for the midiDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIDEVICE_H__FB529C4A_C29B_4DF3_9006_E29AE9591D05__INCLUDED_)
#define AFX_MIDIDEVICE_H__FB529C4A_C29B_4DF3_9006_E29AE9591D05__INCLUDED_

#include <juce.h>

class midiDevice
{
	public:
		midiDevice (int _deviceIndex);
		~midiDevice();
		bool openDevice ();
		void sendMessage (const MidiMessage *m);
		void sendMessageBuffer (const MidiBuffer *mb);
		void process();
		bool isOpen();

	private:
		int deviceIndex;
		MidiOutput *d;
		bool open;
};


#endif