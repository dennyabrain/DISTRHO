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

#ifndef __JUCETICE_VEXPEGGYSETTINGS_HEADER__
#define __JUCETICE_VEXPEGGYSETTINGS_HEADER__

#include "StandardHeader.h"

struct PeggySettings
{
    int length;
    int timeMode;
    int syncMode;
    int failMode;
    int velMode;
    float velocities[16];
    bool grid[80];
    bool on;

    PeggySettings()
        : length(0),
          timeMode(0),
          syncMode(0),
          failMode(0),
          velMode(0),
          on(false)
    {
        zeromem(velocities, sizeof(float)*16);
        zeromem(grid, sizeof(bool)*80);
    }

    void reset()
    {
        length   = 8;
        timeMode = 2;
        syncMode = 1;
        failMode = 1;
        velMode  = 1;
        on       = true;

        for (int i = 0; i < 16; ++i)
            velocities[i] = 0.5f;

        for (int i = 0; i < 80; ++i)
            grid[i] = false;
    }
};

#endif
