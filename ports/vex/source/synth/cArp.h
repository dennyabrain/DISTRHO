/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_VEXCARP_HEADER__
#define __JUCETICE_VEXCARP_HEADER__

#include "cArpSettings.h"

#ifdef CARLA_EXPORT
 #include "JuceHeader.h"
#else
 #include "../StandardHeader.h"
#endif

class VexArp
{
public:
    static const int kMaxNotes = 10;

    VexArp(const VexArpSettings* p)
        : peggySet(p),
          dead(true),
          notesPlaying(false),
          doSync(true),
          nextStep(0),
          sampleCount(0),
          sampleRate(44100)
    {
        meter[0] = 4;
        meter[1] = 8;
        meter[2] = 16;
        meter[3] = 32;

        for (int i = 0; i < kMaxNotes; ++i)
        {
            cKeysDown[i] = 0;
            cNotesToKill[i] = 0;
            cKeysVelocity[i] = 0;
        }

        outMidiBuffer.ensureSize(kMaxNotes+128);
    }

    void addNote(const char note, const char vel)
    {
        char tmp, tmpNote = note, tmpVel = vel;

        for (int i = 0; i < kMaxNotes; ++i)
        {
            if (note < cKeysDown[i] || cKeysDown[i] == 0)
            {
                tmp = cKeysDown[i];     cKeysDown[i]     = tmpNote; tmpNote = tmp;
                tmp = cKeysVelocity[i]; cKeysVelocity[i] = tmpVel;  tmpVel  = tmp;
            }
        }

        doSync = true;
    }

    void dropNote(const char note)
    {
        int i = 0;

        for (; i < kMaxNotes; ++i)
        {
            if (cKeysDown[i] == note)
                break;
        }

        if (i == kMaxNotes)
            return;

        for (; i < kMaxNotes-1; ++i)
        {
            cKeysDown[i] = cKeysDown[i+1];
            cKeysVelocity[i] = cKeysVelocity[i+1];
        }

        cKeysDown[kMaxNotes-1] = 0;
        cKeysVelocity[kMaxNotes-1] = 0;
    }

    void killThisNoteLater(const char note)
    {
        for (int i = 0; i < kMaxNotes; ++i)
        {
            if (cNotesToKill[i] == note)
                break;

            if (cNotesToKill[i] == 0)
            {
                cNotesToKill[i] = note;
                break;
            }
        }
    }

    void setSampleRate(const int srate)
    {
        sampleRate = srate;
    }

    const MidiBuffer& processMidi(MidiBuffer& inMidiBuffer, const bool isPlaying,
                                                            const double ppqPosition,
                                                            const double ppqPositionOfLastBarStart,
                                                            const double bpm,
                                                            const int numSamples)
    {
        const int timeSig = meter[peggySet->timeMode];

        // Loop though the midibuffer, take away note on/off, let the rest pass
        {
            outMidiBuffer.clear();

            MidiBuffer::Iterator inBufferIterator(inMidiBuffer);
            MidiMessage midiMessage(0xf4);
            int sampleNumber;

            while (inBufferIterator.getNextEvent(midiMessage, sampleNumber))
            {
                if (midiMessage.isNoteOn())
                    addNote(midiMessage.getNoteNumber(), midiMessage.getVelocity());
                else if(midiMessage.isNoteOff())
                    dropNote(midiMessage.getNoteNumber());
                else
                    outMidiBuffer.addEvent(midiMessage, sampleNumber);
            }
        }

        // BarSync
        const int samplesPerStep = int((60.0 / bpm) * sampleRate * 4) / timeSig;

        if (isPlaying && peggySet->syncMode == 2)
        {
            if (doSync)
            {
                //offset sample count
                sampleCount = int((ppqPosition - ppqPositionOfLastBarStart) * ((60 / bpm) * sampleRate));

                //offset step count
                nextStep = sampleCount / samplesPerStep;

                //Cycle the counts
                sampleCount = (sampleCount % samplesPerStep) + samplesPerStep - 10;
                nextStep = nextStep % peggySet->length;
            }
            doSync = false;
        }
        else
        {
            doSync = true;
        }

        //***************************
        if (cKeysDown[0])
        {   //Keys are down
            dead = false;
            sampleCount += numSamples;
            bool repeat = false;

            do
            {
                repeat = false;

                //***
                if (sampleCount >= samplesPerStep)
                {   //Play step
                    int offset = numSamples - (sampleCount - samplesPerStep);
                    bool doFail = true;

                    for (int i = 0; i < 5; ++i)
                    {
                        if((cKeysDown[i]!= 0) && (peggySet->grid[nextStep*5 + i]))
                        {   //we have a note to play
                            int vel;

                            switch (peggySet->velMode)
                            {
                            case 1:
                                vel = roundFloatToInt (peggySet->velocities[nextStep] * 127.0f);
                                break;
                            case 2:
                                vel = (int) cKeysVelocity[i];
                                break;
                            case 3:
                                vel = (int) cKeysVelocity[i] + roundFloatToInt (peggySet->velocities[nextStep] * 127.0f);
                                break;
                            default:
                                vel = 127;
                                break;
                            }

                            doFail = false;
                            notesPlaying = true;
                            killThisNoteLater(cKeysDown[i]);
                            outMidiBuffer.addEvent(MidiMessage::noteOn(1, cKeysDown[i], uint8(vel)), offset);
                        }
                    }

                    if (doFail)
                    {
                        switch (peggySet->failMode)
                        {
                        case 1: //normal
                            sampleCount -= samplesPerStep;
                            nextStep++;
                            nextStep = nextStep % peggySet->length;
                            break;
                        case 2: //skip one
                            //SampleCount -= SamplesPerStep;
                            nextStep++;
                            nextStep = nextStep % peggySet->length;
                            repeat = true;
                            break;
                        case 3: //skip two
                            //SampleCount -= SamplesPerStep;
                            nextStep += 2;
                            nextStep = nextStep % peggySet->length;
                            repeat = true;
                            break;
                        }
                    }
                    else
                    {
                        sampleCount -= samplesPerStep;
                        nextStep++;
                        nextStep = nextStep % peggySet->length; //Cycle the steps over pattern length
                    }
                }
            } while (repeat);

            //***
            unsigned int NoteLength = (samplesPerStep / 4) * 3;
            if ((sampleCount >= NoteLength) && notesPlaying)
            {   //Mute step
                int offset = numSamples - (sampleCount - NoteLength);
                //***
                for(int i = 0; i < kMaxNotes; ++i)
                {
                    if (cNotesToKill[i] != 0)
                    {   //do we have a note to kill?
                        outMidiBuffer.addEvent(MidiMessage::noteOff(1, cNotesToKill[i]), offset);
                        cNotesToKill[i] = 0;
                    }
                }
                notesPlaying = false;
            }
        //***
        }
        else if (! dead)
        {   //No keys pressed - kill 'em all
            for (int i = 0; i < kMaxNotes; ++i)
            {
                if (cNotesToKill[i] != 0)
                {   //do we have a note to kill?
                    outMidiBuffer.addEvent(MidiMessage::noteOff(1, cNotesToKill[i]), 0);
                    cNotesToKill[i] = 0;
                }
            }

            nextStep = 0;
            sampleCount = samplesPerStep;
            dead = true;
        }

        return outMidiBuffer;
    }

private:
    const VexArpSettings* peggySet;
    MidiBuffer outMidiBuffer;
    bool dead, notesPlaying, doSync;
    char nextStep;
    unsigned int sampleCount, sampleRate;
    int meter[4];
    char cKeysDown[kMaxNotes];
    char cKeysVelocity[kMaxNotes];
    char cNotesToKill[kMaxNotes];
};

#endif
