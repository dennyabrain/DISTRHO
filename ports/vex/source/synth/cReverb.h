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

#ifndef __JUCETICE_VEXCREVERB_HEADER__
#define __JUCETICE_VEXCREVERB_HEADER__

#ifdef CARLA_EXPORT
 #include "JuceHeader.h"
#else
 #include "../StandardHeader.h"
#endif

#include "freeverb/revmodel.hpp"

class VexReverb
{
public:
    VexReverb(const float* const p)
        : parameters(p)
    {
        model.setwet(1.0f);
        model.setdry(0.0f);
    }

    void updateParameterPtr(const float* const p)
    {
        parameters = p;
    }

    void processBlock(AudioSampleBuffer* const outBuffer)
    {
        processBlock(outBuffer->getSampleData(0, 0), outBuffer->getSampleData(1, 0), outBuffer->getNumSamples());
    }

    void processBlock(float* const outBufferL, float* const outBufferR, const int numSamples)
    {
#ifdef CARLA_EXPORT
        model.setroomsize(parameters[0]);
        model.setdamp(parameters[1]);
        model.setwidth(parameters[2]);
#else
        model.setroomsize(parameters[79]);
        model.setdamp(parameters[81]);
        model.setwidth(parameters[80]);
#endif
        model.processreplace(outBufferL, outBufferR, outBufferL, outBufferR, numSamples, 1);
    }

private:
    revmodel model;
    const float* parameters;
};

#endif
