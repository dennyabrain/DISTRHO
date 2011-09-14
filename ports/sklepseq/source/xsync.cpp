// xSync.cpp: implementation of the xSync class.
//
//////////////////////////////////////////////////////////////////////

#include "xsync.h"
#include "sklepSeqEditor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

xsync::xsync() : Thread ("Sync thread")
{
	setPriority (7);
	updateAsync = 0;
	timeBPM = 120;
	timeElapsed = 0;
	timeNow = 0;
	setBPM (120);
	midiQuarterNote = midiTicks = midiEighthNote = midiSixteenthNote = 0;

	Logger::writeToLog ("xsync created");
}

xsync::~xsync()
{
}

void xsync::run()
{
	timeElapsed = 0;
	timeNow = 0;
	midiQuarterNote = midiEighthNote = midiSixteenthNote = 0;
	midiTicks = 0;

	/* async updates, like GUI */
	if (updateAsync)
	{
		((AsyncUpdater *)updateAsync)->triggerAsyncUpdate();
	}

	/* sync updates, like midi manager */
	sendChangeMessage ();

	while (1)
	{
		timeNow =  Time::getMillisecondCounter();
		Time::waitForMillisecondCounter (timeNow + 3);

		timeElapsed = timeElapsed + (Time::getMillisecondCounter() - timeNow);

		if (timeElapsed >= timeMidiTick)
		{
			if (threadShouldExit())
			{
				stopSync();
				return;
			}

			if (midiTicks == 6 || midiTicks == 12 || midiTicks == 18 || midiTicks == 0)
			{
				midiSixteenthNote++;

				if (midiSixteenthNote == 2 || midiSixteenthNote == 4)
				{
					midiEighthNote++;

					if (midiEighthNote == 2 || midiEighthNote == 4)
					{
						midiQuarterNote++;

						if (midiQuarterNote == 4)
						{
							midiQuarterNote = 0;
						}
						
						if (midiEighthNote == 4)
							midiEighthNote = 0;
					}
				}

				if (midiSixteenthNote == 4)
					midiSixteenthNote = 0;

				/* async updates, like GUI */
				if (updateAsync)
				{
					((AsyncUpdater *)updateAsync)->triggerAsyncUpdate();
				}

				/* sync updates, like midi manager */
				sendChangeMessage ();
			}

			timeElapsed = 0;
			
			midiTicks++;

			if (midiTicks == 23)
				midiTicks = 0;
		}

		if (threadShouldExit())
		{
			stopSync();
			return;
		}
	}
}

void xsync::setBPM (unsigned int bpm)
{
	timeBPM = bpm;
	timeMidiTick = 60000 / (24 * timeBPM);
}

void xsync::setGui (void *ptr)
{
	updateAsync = ptr;
}

unsigned int xsync::getMidiQuarterNote()
{
	return (midiQuarterNote);
}

unsigned int xsync::getMidiEighthNote()
{
	return (midiEighthNote);
}

unsigned int xsync::getMidiSixteenthNote()
{
	return (midiSixteenthNote);
}

void xsync::stopSync()
{
	timeElapsed = 0;
	timeNow = 0;
	midiQuarterNote = midiEighthNote = midiSixteenthNote = 0;
	midiTicks = 0;
	timeBPM = 120;

	Logger::writeToLog ("xsync stopped");
}

int xsync::getBpm()
{
	return (timeBPM);
}