/*
  ZynAddSubFX - a software synthesizer

  VSTaudiooutput.h - Audio output for VST
  Copyright (C) 2002 Nasca Octavian Paul
  Author: Nasca Octavian Paul

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License (version 2 or later) for more details.

  You should have received a copy of the GNU General Public License (version 2)
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/
#ifndef LV2_AUDIO_OUTPUT_H
#define LV2_AUDIO_OUTPUT_H

#include <pthread.h>
#include <vector>

#include "../globals.h"
#include "../Misc/Master.h"

#include "lv2/lv2.h"
#include "lv2/event.h"
#include "lv2/event-helpers.h"
#include "lv2/midi.h"
#include "lv2/state.h"
#include "lv2/urid.h"
#include "lv2/lv2_programs.h"

class LV2audiooutput
{
    public:
        //
        // Static stubs for LV2 member functions
        //
        static void stub_connectPort(LV2_Handle instance, uint32_t port, void* dataLocation);
        static void stub_activate(LV2_Handle instance);
        static void stub_run(LV2_Handle instance, uint32_t sampleCount);
        static void stub_deactivate(LV2_Handle Instance);
        static void stub_cleanup(LV2_Handle instance);
        static const void* stub_extension_data(const char* uri);

        static const LV2_Program_Descriptor *stub_getProgram(LV2_Handle instance, uint32_t index);
        static void stub_selectProgram(LV2_Handle instance, uint32_t bank, uint32_t program);

        /*
         * LV2 member functions
         */
        static LV2_Handle instantiate(const LV2_Descriptor* descriptor, double sample_rate, const char*, const LV2_Feature* const* features);
        void connectPort(uint32_t port, void* dataLocation);
        void activate();
        void run(uint32_t sampleCount);
        void deactivate();
        void cleanup();

        const LV2_Program_Descriptor *getProgram(uint32_t index);
        void selectProgram(uint32_t bank, uint32_t program);
//         void runSynth(unsigned long sample_count,
//                       snd_seq_event_t *events,
//                       unsigned long event_count);
        static const LV2_Descriptor *getLv2Descriptor(uint32_t index);

        struct ProgramDescriptor {
            uint32_t bank;
            uint32_t program;
            std::string name;
            ProgramDescriptor(uint32_t _bank, uint32_t _program, char* _name);
        };

    private:

        LV2audiooutput(double sampleRate, const LV2_Feature* const* features);
        ~LV2audiooutput();
        static LV2_Descriptor *initLv2Descriptor();
        static LV2audiooutput *getInstance(LV2_Handle instance);
        void initBanks();
        bool mapNextBank();

        float *outl;
        float *outr;
        LV2_Event_Buffer* lv2_event;
        LV2_URID uridIdMidi;
        double sampleRate;
        Master *master;
        static LV2_Descriptor *lv2Descriptor;
        static std::string bankDirNames[];
        static std::vector<ProgramDescriptor> programMap;

        /**
         * Flag controlling the list of bank directories
         */
        bool banksInited;
        static long bankNoToMap;
};

#endif
