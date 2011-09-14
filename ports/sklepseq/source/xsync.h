// xSync.h: interface for the xSync class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XSYNC_H__FB529C4A_C29B_4DF3_9006_E29AE9591D05__INCLUDED_)
#define AFX_XSYNC_H__FB529C4A_C29B_4DF3_9006_E29AE9591D05__INCLUDED_

#include <juce.h>

class xsync : public Thread, public ChangeBroadcaster
{
	public:
		xsync();
		~xsync();
		void run();
		void setBPM (unsigned int bpm);
		void setGui (void *ptr);
		void stopSync();
		int getBpm();
		unsigned int getMidiQuarterNote();
		unsigned int getMidiEighthNote();
		unsigned int getMidiSixteenthNote();
		
	private:
		unsigned int timeElapsed;
		unsigned int timeNow;
		unsigned int timeBPM;
		unsigned int timeMidiTick;
		unsigned int midiTicks;
		unsigned int midiQuarterNote;
		unsigned int midiEighthNote;
		unsigned int midiSixteenthNote;
		void *updateAsync;
};

#endif // !defined(AFX_XSYNC_H__FB529C4A_C29B_4DF3_9006_E29AE9591D05__INCLUDED_)
