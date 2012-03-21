#ifndef OscNoise_H
#define OscNoise_H

#include "Math.h"

/*
	==============================================================================
	This file is part of Tal-NoiseMaker by Patrick Kunz.

	Copyright(c) 2005-2010 Patrick Kunz, TAL
	Togu Audio Line, Inc.
	http://kunz.corrupt.ch

	This file may be licensed under the terms of of the
	GNU General Public License Version 2 (the ``GPL'').

	Software distributed under the License is distributed
	on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
	express or implied. See the GPL for the specific language
	governing rights and limitations.

	You should have received a copy of the GPL along with this
	program. If not, go to http://www.gnu.org/licenses/gpl.html
	or write to the Free Software Foundation, Inc.,  
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
	==============================================================================
 */

#include <cstdlib>

class OscNoise
{
public:
    int randSeed;

    OscNoise(float sampleRate) 
    {
        resetOsc();
    }

    void resetOsc() 
    {
        randSeed = 1;
    }

    inline float getNextSample() 
    {
        randSeed *= 16807;
        //return (float)(randSeed &  0x7FFFFFFF) * 4.6566129e-010f; // 0..1
        return (float)randSeed * 4.6566129e-010f;
    }

	inline float getNextSamplePositive() 
	{
        randSeed *= 16807;
        return (float)(randSeed &  0x7FFFFFFF) * 4.6566129e-010f;
	}
};
#endif