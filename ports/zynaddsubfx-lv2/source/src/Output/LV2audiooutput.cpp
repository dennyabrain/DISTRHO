/*
  ZynAddSubFX - a software synthesizer

  DSSIaudiooutput.cpp - Audio functions for DSSI
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

/*
 * Inital working LV2 output code based on DSSI plugin
 */

#include "LV2audiooutput.h"
#include "../Misc/Config.h"
#include "../Misc/Bank.h"
#include "../Misc/Util.h"
#include <string.h>
#include <limits.h>

#if defined(__WIN32__) || defined(__WIN64__)
#define PLUGIN_EXPORT extern "C" __declspec (dllexport)
#else
#define PLUGIN_EXPORT extern "C" __attribute__ ((visibility("default")))
#endif

using std::string;
using std::vector;

//
// Static stubs for LV2 member functions
//

void LV2audiooutput::stub_connectPort(LV2_Handle instance, uint32_t port, void* dataLocation)
{
    getInstance(instance)->connectPort(port, dataLocation);
}

void LV2audiooutput::stub_activate(LV2_Handle instance)
{
    getInstance(instance)->activate();
}

void LV2audiooutput::stub_run(LV2_Handle instance, uint32_t sampleCount)
{
    getInstance(instance)->run(sampleCount);
}

void LV2audiooutput::stub_deactivate(LV2_Handle instance)
{
    getInstance(instance)->deactivate();
}

void LV2audiooutput::stub_cleanup(LV2_Handle instance)
{
    LV2audiooutput *plugin_instance = getInstance(instance);
    plugin_instance->cleanup();
    delete plugin_instance;
}

const void* LV2audiooutput::stub_extension_data(const char* uri)
{
    static LV2_Programs_Interface lv2ProgramsDescriptor = { stub_getProgram, stub_selectProgram };
    if (strcmp(uri, LV2_PROGRAMS__Interface) == 0)
      return &lv2ProgramsDescriptor;
    return NULL;
}

const LV2_Program_Descriptor *LV2audiooutput::stub_getProgram(LV2_Handle instance, uint32_t index)
{
    return getInstance(instance)->getProgram(index);
}

void LV2audiooutput::stub_selectProgram(LV2_Handle instance, uint32_t bank, uint32_t program)
{
    getInstance(instance)->selectProgram(bank, program);
}

//
// LV2 member functions
//

/**
 * Instantiates a plug-in.
 +
 * Zyn Implementation
 * ------------------
 * This implementation creates a C++ class object and hides its pointer
 * in the handle by type casting.
 */
LV2_Handle LV2audiooutput::instantiate(const LV2_Descriptor*, double sample_rate, const char*, const LV2_Feature* const* features)
{
    return (LV2_Handle)(new LV2audiooutput(sample_rate, features));
}

/**
 * Connects a port on an instantiated plug-in.
 *
 * Zyn Implementation
 * ------------------
 * The buffer pointers are stored as member variables
 *
 */
void LV2audiooutput::connectPort(uint32_t port, void* dataLocation)
{
    switch(port) {
        case 0:
            lv2_event = (LV2_Event_Buffer*)dataLocation;
            break;
        case 1:
            outl = (float*)dataLocation;
            break;
        case 2:
            outr = (float*)dataLocation;
            break;
    }
}

/**
 * Initialises a plug-in instance and activates it for use.
 *
 * Zyn Implementation
 * ------------------
 * Currently this does nothing; Care must be taken as to code placed here as
 * too much code here seems to cause time-out problems in jack-dssi-host.
*/
void LV2audiooutput::activate()
{}

/**
 * Runs an instance of a plug-in for a block.
 *
 * Zyn Implementation
 * ------------------
 * This is a LV2 function that does not process any MIDI events; it is hence
 * implemented by simply calling runSynth() with an empty event list.
 */
void LV2audiooutput::run(uint32_t sampleCount)
{
    LV2_Event_Iterator iter;
    lv2_event_begin(&iter, lv2_event);
    uint32_t sampleFrame = 0;
    uint8_t* data = 0;
    uint8_t channel, type;
    pthread_mutex_lock(&master->mutex);

    while (sampleFrame < sampleCount && lv2_event_is_valid(&iter))
    {
        LV2_Event* const event = lv2_event_get(&iter, &data);

        if (event && event->type == uridIdMidi)
        {
            type    = data[0] & 0xF0;
            channel = data[0] & 0x0F;
            sampleFrame = event->frames;

            if (type == 0x90)
                master->noteOn(channel, data[1], data[2]);
            else if (type == 0x80)
                master->noteOff(channel, data[1]);
            else if (type == 0xC0)
                master->setController(channel, data[1], data[2]);
        }

        lv2_event_increment(&iter);
    }

    master->GetAudioOutSamples(sampleCount, (int)sampleRate, outl, outr);
    pthread_mutex_unlock(&master->mutex);
}

/**
 * Counterpart to activate().
 *
 * Zyn Implementation
 * ------------------
 * Currently this function does nothing.
 */
void LV2audiooutput::deactivate()
{}

/**
 * Deletes a plug-in instance that is no longer required.
 *
 * Zyn Implementation
 * ------------------
 * Currently cleanup is deferred to the destructor that is invoked after cleanup()
 */
void LV2audiooutput::cleanup()
{}

/**
 * Provides a description of a program available on this synth.
 *
 * Zyn Implementation
 * ------------------
 * The instruments in all Zyn's bank directories, as shown by the `instrument
 * -> show instrument bank` command, are enumerated to the host by this
 * function, allowing access to all those instruments.
 * The first time an instrument is requested, the bank it is in and any
 * unmapped ones preceding that are mapped; all the instruments names and
 * filenames from those banks are stored in the programMap member variable for
 * later use. This is done on demand in this way, rather than up front in one
 * go because loading all the instrument names in one go can lead to timeouts
 * and zombies.
 */
const LV2_Program_Descriptor *LV2audiooutput::getProgram(uint32_t index)
{
    static LV2_Program_Descriptor retVal;

    /* Make sure we have the list of banks loaded */
    initBanks();

    /* Make sure that the bank containing the instrument has been mapped */
    while(index >= programMap.size() && mapNextBank())
        /* DO NOTHING MORE */;

    if(index >= programMap.size())
        /* No more instruments */
        return NULL;
    else {
        /* OK, return the instrument */
        retVal.name    = programMap[index].name.c_str();
        retVal.program = programMap[index].program;
        retVal.bank    = programMap[index].bank;
        return &retVal;
    }
}

/**
 * Selects a new program for this synth.
 *
 * Zyn Implementation
 * ------------------
 * the banks and instruments are as shown in the `instrument -> show instrument
 * bank` command in Zyn. The bank no is a 1-based index into the list of banks
 * Zyn loads and shows in the drop down and the program number is the
 * instrument within that bank.
 */
void LV2audiooutput::selectProgram(uint32_t bank, uint32_t program)
{
    initBanks();
//    cerr << "selectProgram(" << (bank & 0x7F) << ':' << ((bank >> 7) & 0x7F) << "," << program  << ")" << '\n';
    if((bank < master->bank.banks.size()) && (program < BANK_SIZE)) {
        const std::string bankdir = master->bank.banks[bank].dir;
        if(!bankdir.empty()) {
            pthread_mutex_lock(&master->mutex);

            /* We have to turn off the CheckPADsynth functionality, else
             * the program change takes way too long and we get timeouts
             * and hence zombies (!) */
            int save = config.cfg.CheckPADsynth;
            config.cfg.CheckPADsynth = 0;

            /* Load the bank... */
            master->bank.loadbank(bankdir);

            /* restore the CheckPADsynth flag */
            config.cfg.CheckPADsynth = save;

            /* Now load the instrument... */
            master->bank.loadfromslot((unsigned int)program, master->part[0]);

            pthread_mutex_unlock(&master->mutex);
        }
    }
}

/**
 * Initial entry point for the LV2 plug-in library.
 *
 * Zyn Implementation
 * ------------------
 * The descriptor is created statically by LV2audiooutput::initLv2Descriptor()
 * when the plug-in library is loaded. This function merely returns a pointer to
 * that descriptor.
 */
const LV2_Descriptor *LV2audiooutput::getLv2Descriptor(uint32_t index)
{
    if((index > 0) || (lv2Descriptor == NULL))
        return NULL;
    else
        return lv2Descriptor;
}

//
// Internal member functions
//

// Initialise the LV2 descriptor, statically:
LV2_Descriptor *LV2audiooutput:: lv2Descriptor = LV2audiooutput::initLv2Descriptor();

/**
 * Initializes the LV2 descriptor, returning it is an object.
 */
LV2_Descriptor *LV2audiooutput::initLv2Descriptor()
{
    LV2_Descriptor *newLv2Descriptor = new LV2_Descriptor;

    if(newLv2Descriptor) {
        newLv2Descriptor->URI = "http://zynaddsubfx.sourceforge.net/";
        newLv2Descriptor->instantiate = instantiate;
        newLv2Descriptor->connect_port = stub_connectPort;
        newLv2Descriptor->activate = stub_activate;
        newLv2Descriptor->run = stub_run;
        newLv2Descriptor->deactivate = stub_deactivate;
        newLv2Descriptor->cleanup = stub_cleanup;
        newLv2Descriptor->extension_data = stub_extension_data;
    }

    lv2Descriptor = newLv2Descriptor;

    return lv2Descriptor;
}

/**
 * Converts a LV2 handle into a LV2audiooutput instance.
 *
 * @param instance [in]
 * @return the instance
 */
LV2audiooutput *LV2audiooutput::getInstance(LV2_Handle instance)
{
    return (LV2audiooutput *)(instance);
}

SYNTH_T *synth;

/**
 * The private sole constructor for the LV2audiooutput class.
 *
 * Only ever called via instantiate().
 * @param sampleRate [in] the sample rate to be used by the synth.
 * @return
 */
LV2audiooutput::LV2audiooutput(double sampleRate, const LV2_Feature* const* features)
{
    synth = new SYNTH_T;
    synth->samplerate = sampleRate;

    this->sampleRate  = sampleRate;
    this->banksInited = false;
    this->uridIdMidi  = 0;

    config.init();

    sprng(time(NULL));
    denormalkillbuf = new float [synth->buffersize];
    for(int i = 0; i < synth->buffersize; i++)
        denormalkillbuf[i] = (RND - 0.5f) * 1e-16;

    this->master = new Master();

    for (uint32_t i = 0; features[i]; i++)
    {
        if (strcmp(features[i]->URI, LV2_URID_MAP_URI) == 0)
        {
            LV2_URID_Map* uridMap = (LV2_URID_Map*)features[i]->data;
            uridIdMidi = uridMap->map(uridMap->handle, LV2_MIDI__MidiEvent);
            break;
        }
    }
}

/**
 * The destructor for the LV2audiooutput class
 * @return
 */
LV2audiooutput::~LV2audiooutput()
{}

/**
 * Ensures the list of bank (directories) has been initialised.
 */
void LV2audiooutput::initBanks(void)
{
    if(!banksInited) {
        pthread_mutex_lock(&master->mutex);
        master->bank.rescanforbanks();
        banksInited = true;
        pthread_mutex_unlock(&master->mutex);
    }
}

/**
 * constructor for the internally used ProgramDescriptor class
 *
 * @param _bank [in] bank number
 * @param _program [in] program number
 * @param _name [in] instrument / sample name
 * @return
 */
LV2audiooutput::ProgramDescriptor::ProgramDescriptor(uint32_t _bank,
                                                     uint32_t _program,
                                                     char* _name)
    : bank(_bank), program(_program), name(_name)
{}

/**
 * The map of programs available; held as a single shared statically allocated object.
 */
vector<LV2audiooutput::ProgramDescriptor> LV2audiooutput:: programMap =
    vector<LV2audiooutput::ProgramDescriptor>();

/**
 * Index controlling the map of banks
 */
long LV2audiooutput:: bankNoToMap = 1;

/**
 * Queries and maps the next available bank of instruments.
 *
 * If the program index requested to getProgram() lies beyond the banks mapped to date,
 * this member function is called to map the next one.
 * @return true if a new bank has been found and mapped, else false.
 */
bool LV2audiooutput::mapNextBank()
{
    pthread_mutex_lock(&master->mutex);
    Bank &bank = master->bank;
    bool  retval;
    if((bankNoToMap >= (int)bank.banks.size())
       || bank.banks[bankNoToMap].dir.empty())
        retval = false;
    else {
        bank.loadbank(bank.banks[bankNoToMap].dir);
        for(uint32_t instrument = 0; instrument < BANK_SIZE;
            ++instrument) {
            string insName = bank.getname(instrument);
            if(!insName.empty() && (insName[0] != '\0') && (insName[0] != ' '))
                programMap.push_back(ProgramDescriptor(bankNoToMap, instrument,
                                                       const_cast<char *>(
                                                           insName.c_str())));
        }
        bankNoToMap++;
        retval = true;
    }
    pthread_mutex_unlock(&master->mutex);
    return retval;
}

PLUGIN_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    return LV2audiooutput::getLv2Descriptor(index);
}

int main()
{
   const LV2_Descriptor* desc = lv2_descriptor(0);
   return 0;
}
