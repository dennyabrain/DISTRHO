// sklepSeqPattern.h: interface for the sklepSeqPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKLEPSEQPATTERN_H__F277BDA6_FA04_4DC5_8E91_89AF43BE3A54__INCLUDED_)
#define AFX_SKLEPSEQPATTERN_H__F277BDA6_FA04_4DC5_8E91_89AF43BE3A54__INCLUDED_

#include <juce.h>
#include "midiMessageManager.h"
#include "myMidiMessage.h"

class sklepSeqPattern  : public Component
{
	public:
		sklepSeqPattern(int _id);
		~sklepSeqPattern();
		bool fromXml (XmlElement *e);
		void setMidiData (MidiBuffer b);
		void setMidiEvent (int n, MidiMessage note);
		int getPatternId();
		int getPatternLength();
		void setPatternLength(int len);
		void forward(int pos);
		void setActive (bool t);
		bool getActive();
		int getCurrentPosition();
		void setMidiChannel (int c);
		int getMidiChannel ();
		int getMidiDevice();
		void setMidiDevice(int d);
		enum patternMode
		{
			patternForward,
			patternReverse,
			patternRandom
		};
		void reset();
		void addMidiManager (midiMessageManager *m);
		void triggerEvents ();
		void setStep (int nId, int nNumber, float nVelo);
		myMidiMessage* getStep (int nId);
		myMidiMessage* getStepNoVeirfy (int nId);
		void toggleStep(int nId);
		MidiMessageSequence serialize();
		void unserialize (const MidiMessageSequence *seq);
		void setSyncMode (bool m);
		bool getSyncMode();
		bool isWaitingForSync();
		void setEnabled(int nIndex, bool initialCheck=true);
	private:
		bool waitingForSync;
		int patternLength;
		int patternId;
		int currentPosition;
		int previousPosition;
		bool isActive;
		short mode;
		bool syncMode;
		bool patternHasBeenActivated;
		midiMessageManager *midiManager;
		int midiChannel;
		int midiDevice;
		OwnedArray <myMidiMessage> notes;
};

#endif // !defined(AFX_SKLEPSEQPATTERN_H__F277BDA6_FA04_4DC5_8E91_89AF43BE3A54__INCLUDED_)
