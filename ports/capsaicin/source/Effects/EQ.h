/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

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

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHEQ_HEADER__
#define __JUCETICE_XSYNTHEQ_HEADER__

#include "../globals.h"
#include "../DSP/AnalogFilter.h"
#include "Effect.h"


class EQ : public Effect
{
public:

    EQ (int insertion, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~EQ();

    void setPreset (uint8 npreset);
    void setParameter (int npar, uint8 value);
    uint8 getParameter (int npar);
    void out (REALTYPE *smpsl, REALTYPE *smpr, const int numSamples);
    void clean();

    REALTYPE getFrequencyResponse (REALTYPE freq);

private:
    uint8 Pvolume; // Volumul
    uint8 Pdrywet; // DryWet for signal

    void setvolume (uint8 Pvolume);
    void setdrywet (uint8 Pdrywet);

    REALTYPE drywet;

    struct {
        uint8 Ptype, Pfreq, Pgain, Pq, Pstages;
        AnalogFilter *l, *r;
    }filter [MAX_EQ_BANDS];
};


#endif
