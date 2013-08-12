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

#ifndef __JUCETICE_VEXPRESETMAN_HEADER__
#define __JUCETICE_VEXPRESETMAN_HEADER__

#include "StandardHeader.h"
#include "synth/cArpSettings.h"

struct Program
{
    String name;
    float parameters[92];
    VexArpSettings pegSet1;
    VexArpSettings pegSet2;
    VexArpSettings pegSet3;
    String waveFile1;
    String waveFile2;
    String waveFile3;

    Program()
    {
        name      = "Not Set";
        waveFile1 = "Not Set";
        waveFile2 = "Not Set";
        waveFile3 = "Not Set";
    }

    void reset()
    {
        name      = "Default";
        waveFile1 = "sine";
        waveFile2 = "sine";
        waveFile3 = "sine";

        pegSet1.reset();
        pegSet2.reset();
        pegSet3.reset();

        // 0, 24, 48 + 1<->24
        for (int i = 0; i < 3; ++i)
        {
            const int offset = i * 24;

            parameters[offset +  1] = 0.5f;
            parameters[offset +  2] = 0.5f;
            parameters[offset +  3] = 0.5f;
            parameters[offset +  4] = 0.5f;
            parameters[offset +  5] = 0.9f;
            parameters[offset +  6] = 0.0f;
            parameters[offset +  7] = 1.0f;
            parameters[offset +  8] = 0.5f;
            parameters[offset +  9] = 0.0f;
            parameters[offset + 10] = 0.2f;
            parameters[offset + 11] = 0.0f;
            parameters[offset + 12] = 0.5f;
            parameters[offset + 13] = 0.5f;
            parameters[offset + 14] = 0.0f;
            parameters[offset + 15] = 0.3f;
            parameters[offset + 16] = 0.7f;
            parameters[offset + 17] = 0.1f;
            parameters[offset + 18] = 0.5f;
            parameters[offset + 19] = 0.5f;
            parameters[offset + 20] = 0.0f;
            parameters[offset + 21] = 0.0f;
            parameters[offset + 22] = 0.5f;
            parameters[offset + 23] = 0.5f;
            parameters[offset + 24] = 0.5f;
        }

        parameters[ 0] = 0.5f;
        parameters[73] = 0.5f;
        parameters[74] = 0.4f;
        parameters[75] = 0.5f;
        parameters[76] = 0.3f;
        parameters[77] = 0.6f;
        parameters[78] = 0.0f;
        parameters[79] = 0.6f;
        parameters[80] = 0.7f;
        parameters[81] = 0.6f;
        parameters[82] = 0.0f;
        parameters[83] = 0.5f;
        parameters[84] = 0.5f;
        parameters[85] = 0.5f;
        parameters[86] = 0.5f;
        parameters[87] = 0.5f;
        parameters[88] = 0.5f;
        parameters[89] = 0.0f;
        parameters[90] = 0.0f;
        parameters[91] = 0.0f;
    }
};

class PresetMan
{
public:
    static const int kNumPrograms = 8;

    PresetMan()
        : curProgram(0)
    {
        for (int i = 0; i < kNumPrograms; ++i)
            programs[i].reset();
    }

    int getNumPrograms() const
    {
        return kNumPrograms;
    }

    int getCurrentProgram() const
    {
        return curProgram;
    }

    const String& getProgramName(const int i) const
    {
        if (i >= 0 && i < kNumPrograms)
            return programs[i].name;
        return String::empty;
    }

    Program* getProgramStruct(const int i)
    {
        if (i >= 0 && i < kNumPrograms)
            return &programs[i];
        return nullptr;
    }

//     const Program& getCurrentProgramStructRef()
//     {
//         return programs[curProgram];
//     }

    void setProgramName(const int i, const String& newName)
    {
        if (i >= 0 && i < kNumPrograms)
            programs[i].name = newName;
    }

    void setCurrentProgram(const int i)
    {
        if (i >= 0 && i < kNumPrograms)
            curProgram = i;
    }

    void setPointersToCurrent(float** pars, VexArpSettings** p1, VexArpSettings** p2, VexArpSettings** p3)
    {
        *pars =  programs[curProgram].parameters;
        *p1   = &programs[curProgram].pegSet1;
        *p2   = &programs[curProgram].pegSet2;
        *p3   = &programs[curProgram].pegSet3;
    }

    String getWaveName(const int part) const
    {
        switch (part)
        {
        case 1:
            return programs[curProgram].waveFile1;
        case 2:
            return programs[curProgram].waveFile2;
        case 3:
            return programs[curProgram].waveFile3;
        default:
            return "1k_Sine";
        }
    }

    void setWaveName(const int part, const String& newName)
    {
        switch (part)
        {
        case 1:
            programs[curProgram].waveFile1 = newName;
            break;
        case 2:
            programs[curProgram].waveFile2 = newName;
            break;
        case 3:
            programs[curProgram].waveFile3 = newName;
            break;
        }
    }

private:
    int  curProgram;
    Program programs[kNumPrograms];
};

#endif
