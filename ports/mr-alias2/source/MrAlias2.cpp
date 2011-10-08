#include "JucePluginCharacteristics.h"
#include "MrAlias2.h"
#ifdef MRALIASPRO
#include "MrAliasProGUI.h"
#include "key.h"
#define MOD(i) (*mod[i])
#define VMOD(i,v) (*vmod[i][v])
#else
#include "MrAliasGUI.h"
#define MOD(i) (1.f)
#define VMOD(i,v) (1.f)
#endif
#include "waveforms.h"
#include "stuff.h"

//#define dontusepervoicefx
//#define noinputs

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new MrAlias2();
}

struct wavetable
{
	float waves[2][waveSize];
	wavetable()
	{
		for (int i = 0; i < waveSize; i++) {
			waves[0][i] = (float)(sin(i*PI/((double)waveSize*0.5)));
			waves[1][i] = -(float)(-1. + (2. * ((double)i / (double)waveSize)));
		}
	}
};

static wavetable waves;


//==============================================================================
MrAliasProgram::MrAliasProgram () {
    //default values
    //first set all to 0, just in case
    for (int i=numParams;i--;) {
        param[i] = 0.f;
    }
    //oscillators
    param[kWaveform1] = 0.f;
    param[kWaveform2] = 0.f;
    param[kFreq1]     = 0.5f;
    param[kOctave2]   = 0.666666667f;
    param[kOctave1]   = 0.666666667f;
    param[kOctave]    = 0.0f;
    param[kAlias]     = 0.0f;
    param[kAInertia]  = 0.333f;
    param[kStereo]    = 0.5f;

    //MIDI
    param[kPBRange]   = 0.0834f;
    param[kUseProgCh] = 1.f;
    param[kChannel]   = 0.f;

    //filter
    param[kCut]       = 1.0f;
    param[kRes]       = 0.0f;
    param[kFAtt]      = 0.0f;
    param[kFDec]      = 0.0f;
    param[kFSus]      = 1.0f;
    param[kFRel]      = 1.0f;
    param[kFiltEnv]   = 0.0f;
    param[kOPLP]      = 0.9f;
    param[kFilterPower] = 1.f;
    param[kFMode]     = (float)lpf24/(float)(numFilterModes-1);

    //divider
    param[kDivide]    = 0.0f;
    param[kThresh]    = 0.5f;
    param[kDivMix]    = 1.0f;
    param[kPostDivMix]= 1.0f;
    param[kDivEnv]    = 0.0f;

    //amp envelope
    param[kAtt]       = 0.01f;
    param[kDec]       = 0.01f;
    param[kSus]       = 1.0f;
    param[kRel]       = 0.01f;

    //m effect
    param[kM1Mix]     = 1.f;

    //downsampler
    param[kRate]      = 1.f;

    //sine effect
    param[kSineRes]   = 0.25f;
    param[kSineFreq]  = 0.5f;

    //mixer
    param[kInputGain] = 0.5f;
    param[kWet]       = 0.5f;
    param[kOscGain]   = 0.5f;
    param[kStereo2]   = 1.0f;
    param[kVolume]    = 0.5f;

	//assignable envelope
    param[kAtt3]       = 0.01f;
    param[kDec3]       = 0.01f;
    param[kSus3]       = 1.0f;
    param[kRel3]       = 0.01f;
    param[kEnv3Amount] = 0.5f;

	//lfo
	param[kLFO1Amount] = 0.5f;
	param[kLFO1Rate]   = lfoFreqToParam(1.f);
    param[kLFO1Waveform] = (float)sine/(float)(plusUserWaveforms-1);
	param[kLFO2Amount] = 0.5f;
	param[kLFO2Rate]   = lfoFreqToParam(1.f);
    param[kLFO2Waveform] = (float)sine/(float)(plusUserWaveforms-1);
	param[kOsc1ModAmount] = 1.f;
	param[kOsc2ModAmount] = 1.f;

	param[kAudioEnvAmount] = 1.f;

	param[kRandomSpeed] = 0.97f;
	param[kRandomStrength] = 0.01f;
	param[kAuto] = 0.f;

	memcpy(wave,waves.waves,sizeof(waves));

    //default program name
    name = T("Default");
}

//==============================================================================
MrAlias2::MrAlias2()
    : 
    lastUIHeight(320),
#ifdef MRALIASPRO
    lastUIWidth(548),
	currentPage(0),
#else
    lastUIWidth(480),
#endif
    wait(false),
	curProgram(0),
	init(true),    
    waitcount(0),
    waitcount2(0)
{

    //stuff to initialize before loading a bank
    logDebugString("Plugin constructor");
	leds = new ChangeBroadcaster();
	
	zeromem(actualParameter,sizeof(actualParameter));
	modulating=false;
    programs = new MrAliasProgram[getNumPrograms()];

    //this should be the location of the actual plugin file
    currentPath = ((File::getSpecialLocation(File::currentApplicationFile)).getParentDirectory()).getFullPathName();
    logDebugString("PluginFile=" + currentPath + File::separatorString + File::getSpecialLocation(File::currentApplicationFile).getFileName());

#ifdef MRALIASPRO
	currentPath	<< File::separatorString << T("MrAliasPro");
	if (!File(currentPath).isDirectory()) {
		logDebugString("no " + currentPath);
		currentPath = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() + File::separatorString + T("MrAliasPro");
		if (!File(currentPath).isDirectory()) {
			logDebugString("no " + currentPath);
			currentPath = File::getSpecialLocation(File::commonApplicationDataDirectory).getFullPathName() + File::separatorString + T("MrAliasPro");
		}
	}
  #ifdef MAKE_LOG
	if (File(currentPath).isDirectory()) {
		logDebugString("MrAliasProPath=" + currentPath);
	}
	else {
		logDebugString("no " + currentPath);
		logDebugString("MrAliasPro folder not found");
	}
  #endif
#endif


    //initialize values
    for (int v=maxPoly;v--;) {
        freq1[v] = 440.f;
        freq2[v] = 440.f;
    }
    voices=0;
    memset(notes,0,sizeof(notes));
    notes[0] = EVENTS_DONE;

    gvelocity=0;
    genv=0;
    genvd=0;
    genvl=0;
    gfenv=0;
    gfenvd=0;
    gfenvl=0;
    gksf=0;

    att=0; dec=0; sus=0; rel=0;
    fatt=0; fdec=0; fsus=0; frel=0;
    dcoeff=0; acoeff=0; rcoeff=0;
    fdcoeff=0; facoeff=0; frcoeff=0;
#ifdef MRALIASPRO
    att3=0; dec3=0; sus3=0; rel3=0;
	dcoeff3=0; acoeff3=0; rcoeff3=0;
	lfo1freq=1.f; lfo2freq=1.f;
	freelfo1=freelfo2=0.f;
	bpm = 120.f;
	ppqPerBar = 4.f;
#endif

    sustain=0;
    pbrange=0;
    bend=1.0;

    SR = 44100.f;	// we don't know the sample rate yet
    ifs = 1.0 / (double)SR;
    fScaler = (float)((double)waveSize * ifs);

    ledon=false;
    aledon=false;
    clipped=false;
	clipcount=0;
    filtercount=0;
    fcounttarget=1;

    // make waveforms
	//waveNames.add("RampUp");
	//waveNames.add("RampDown");
	//waveNames.add("Square");
	//waveNames.add("Triangle");
	//waveNames.add("Sine");
	//waveNames.add("Minkowski");
	//waveNames.add("Weierstrass");
	//waveNames.add("AutoAlias");
	//waveNames.add("Eight");
	//waveNames.add("OddEight");
	//waveNames.add("Computer");
	//waveNames.add("Funnel");
	//waveNames.add("Grate");
	//waveNames.add("Noise");
	//waveNames.add("Sine+");
	//waveNames.add("Narrow");
	//waveNames.add("Octaves");
	//waveNames.add("Ughhh");
	//waveNames.add("Drawable");
    wsf = (float)waveSize;
    createWaves();

    mono=false;
    polymode=polyphonic;
    target=0;
    posttarget=0;
    threshold=0.5f;
    divenv=0.f;
	w1 = w2 = rampup;
    wave1 = table[rampup];
    dtable1 = dtable[rampup];
    wave2 = table[rampup];
    dtable2 = dtable[rampup];
    ff = 12500.f;
    rr = 0.2f;
    filtenv = 0.f;
    usefilter = true;
    useringmod = false;
    usedecimator = false;
    useclipper = false;
    usesine = false;
    //usestereo = false;
    //useosc2 = false;
    usem1 = false;
	useinput = false;
	uselimiter = false;
    m1=100;
    ingain = 0.f;
    oscgain = 1.f;
    wet = 0.0000000001f;
    octave = 0.f;
    octave1 = 1.f;
    octave2 = 1.f;
    detune = 0.f;
    phmodfactor = 0.f;
    sinefreq = 0.5f;
    sineres = 512;
    filtermode = lpf24;
    useprogch = true;
    listenchannel = -1;
    newbank = false;
    glide = 1.f;
	zero = 0.f;

    midilearnlisten = false;
    useccmap = false;
	CCMappingToBankByDefault = false;
    followPresetA = true;
    followPresetB = false;
    snapshotA.param[kMorph]=0.f;
    snapshotB.param[kMorph]=1.f;
#ifdef MRALIASPRO
	for (int i=numModSources;i--;) {
		modSource[i]=1.f;
		for (int v=maxPoly;v--;) vmodSource[i][v]=1.f;
	}
#endif
    clearModMatrix();

#if MAKE_LOG
    _iter=0;
#endif

	settingProgram=false;

    //look for a default bank
#ifdef MRALIASPRO
	patchPath = currentPath + File::separatorString + "sounds";
	wavePath = currentPath + File::separatorString + "drawablewaves";
    String defaultBank = patchPath + File::separatorString + T("DefaultPro.MrAliasBank");
#else
	patchPath = currentPath;
	String defaultBank = patchPath + File::separatorString + T("Default.MrAliasBank");
#endif
	File initPatch = File(patchPath + File::separatorString + T("Init.MrAliasPatch"));
	if (initPatch.exists()) setBlankPatch(initPatch);

    if (File(defaultBank).existsAsFile()) {
        logDebugString("Loading " + defaultBank);
		loadBank(File(defaultBank));
    }
	else {
#ifdef MRALIASPRO
		defaultBank = ((File::getSpecialLocation(File::currentApplicationFile)).getParentDirectory()).getFullPathName() 
			+ File::separatorString
			+ T("DefaultPro.MrAliasBank");
		if (File(defaultBank).existsAsFile()) {
			logDebugString("Loading " + defaultBank);
			loadBank(File(defaultBank));
		}
#else
        defaultBank = currentPath
            + File::separatorString
            + T("MrAlias2.fxb");
        if (File(defaultBank).existsAsFile()) {
            logDebugString("Loading " + defaultBank);
            MemoryBlock bank = MemoryBlock(0,true);
            File(defaultBank).loadFileAsData(bank);
            bank.removeSection(0,0xA0);
            setStateInformation(bank.getData(), bank.getSize());
        }
#endif
        else {
            logDebugString("Default bank not found");
            // no bank found, blank programs
			if (initPatch.exists())
			{
				initializeBank();
			}
			else {
				for(int i=0;i<getNumPrograms();i++){
					programs[i].name = String(T("Program ")) + String(i+1);
				}
				setCurrentProgram (0);
			}
        }
    }

    fzip=param[kCut]*param[kCut]*12500.f;
    rzip=param[kRes]*2.05f+0.2f;
    bzip=0;
    azip=102.0f*param[kAlias]+1.0f;
    srzip=param[kRate];
    vzip=param[kVolume]*2.f;
    vol = vzip;

    init=true;
    processing=false;
    editorIsShowing=false;

#ifdef MRALIASPRO
	demo = !readKeyFile();
	skin = String("skins") + File::separatorString + String("Default");
	readSettings();
    keyFocus=false;
	lfo1w = lfo2w = sine;
    lfowave1 = table[sine];
    lfodtable1 = dtable[sine];
    lfowave2 = table[sine];
    lfodtable2 = dtable[sine];
	zeromem(beats,sizeof(beats));
	recBuffer = new AudioSampleBuffer(1,waveSize);
	if (demo) infoString = String("Demo Version");
	recording=false;
	numSamplesRecorded=0;
	recordingIndex=draw1;
#else
    infoString = String("Ready to rok");
#endif
}

MrAlias2::~MrAlias2() {
    logDebugString(String(_iter)+" Bye!");
	//this->dispatchPendingMessages();
#if MRALIASPRO
	stopTimer();
	writeSettings();
	delete recBuffer;
#endif
    if (programs) delete [] programs;
}

//==============================================================================
float MrAlias2::getParameter (int index) {
    //logDebugString(String(_iter)+" "+"getParameter(" + String(index) + ")");
    //return index<getNumParameters() ? param[index] : 0.f;
    return index<getNumParameters() ? actualParameter[index] : 0.f;
}

//#if MAKE_LOG
void MrAlias2::setParameterNotifyingHost (int index, float newValue) {
    logDebugString(String(_iter)+" setParameterNotifyingHost(" + String(index) + ", " + String(newValue) + ")");
	actualParameter[index]=newValue;
	modulating=false;
    AudioProcessor::setParameterNotifyingHost (index, newValue);
}
//#endif

void MrAlias2::setParameter (int index, float newValue) {
    //logDebugString(String(_iter)+" "+"setParameter(" + String(index) + ", " + String(newValue) + ")");
    if (index<getNumParameters()-2) {
        MrAliasProgram* ap = &programs[curProgram];
        switch(index)
        {
        //int temp, temp2;
        //global parameters
        case kChannel:
            if (listenchannel!=roundFloatToInt(newValue*16.f)-1) {
                for (int i=0;i<numPrograms;i++) programs[i].param[index]=newValue;
            }
            listenchannel = roundFloatToInt(newValue*16.f)-1;
            break;
        case kUseProgCh:
            if (useprogch!=newValue>=0.5f) {
                for (int i=0;i<numPrograms;i++) programs[i].param[index]=newValue;
            }
            useprogch = newValue>=0.5f;
            break;
        case kInputGain:
            for (int i=0;i<numPrograms;i++) programs[i].param[index]=newValue;
            ingain = newValue*2.f;
            break;
        case kWet:
            for (int i=0;i<numPrograms;i++) programs[i].param[index]=newValue;
            wet = newValue+0.0000000001f;
            break;

        //per-patch parameters
        case kLimiter:
            uselimiter = newValue>=0.5f;
            break;
        case kFMode:
            filtermode = roundFloatToInt(newValue*(float)(numFilterModes-1));
			filtercount = fcounttarget;
            break;
        case kDivide:
            //getCallbackLock().enter();
            target=roundFloatToInt(newValue*100.f);
            if (target==0) divenv=0.f;
            //getCallbackLock().exit();
            break;
        case kPostDivide:
            posttarget=roundFloatToInt(newValue*100.f);
            break;
        case kThresh:
            //getCallbackLock().enter();
            threshold=jmax(0.f,newValue-0.01f);
            divenv = target==0 ? 0.f : param[kDivEnv]*2.f*threshold;
            //getCallbackLock().exit();
            break;
        case kDivEnv:
            //getCallbackLock().enter();
            divenv = target==0 ? 0.f : newValue*2.f*threshold;
            //getCallbackLock().exit();
            break;
        case kMode:
            if(newValue<0.5f) polymode=polyphonic;
            else if(newValue<1.0f) polymode=monophonic;
            else polymode=monomicro;
            mono=newValue>=0.5f;
            if (voices>0 && newValue!=param[kMode]) {
                for (int v=1;v<maxPoly;v++) {
                    voice[v].note=NO_NOTE;
                    voice[v].oldnote=NO_NOTE;
                    voice[v].velocity=0;
                    voice[v].env=SILENCE;
                    voice[v].envd=0;
                    voice[v].envl=0;
                    voice[v].fenv=SILENCE;
                    voice[v].fenvd=0;
                    voice[v].fenvl=0;
#ifdef MRALIASPRO
					voice[v].env3=SILENCE;
					vmodSource[modEnv3][v] = 1.f-param[kEnv3Amount];
                    voice[v].envd3=0;
                    voice[v].envl3=0;
					voice[v].lfo1=0;
					voice[v].lfo2=0;
					logDebugString(String(_iter)+" "+"mode changed");
#endif
					voice[v].fPhase1=0;
                    voice[v].fPhase2=0;
                }
                voices=1;
                //notes[0] = EVENTS_DONE;
            }
            break;
        case kWaveform1:
            w1 = roundFloatToInt(newValue*(float)(plusUserWaveforms-1));
            wave1 = table[w1];
            dtable1 = dtable[w1];
            break;
        case kWaveform2:
            w2 = roundFloatToInt(newValue*(float)(plusUserWaveforms-1));
            wave2 = table[w2];
            dtable2 = dtable[w2];
            break;
#ifdef MRALIASPRO
        case kLFO1Waveform:
            lfo1w = roundFloatToInt(newValue*(float)(plusUserWaveforms-1));
            lfowave1 = table[lfo1w];
            lfodtable1 = dtable[lfo1w];
            break;
        case kLFO2Waveform:
            lfo2w = roundFloatToInt(newValue*(float)(plusUserWaveforms-1));
            lfowave2 = table[lfo2w];
            lfodtable2 = dtable[lfo2w];
            break;
#endif
        case kCut:
            ff = newValue*newValue*12500.f;
            break;
        case kRes:
            rr = newValue*2.05f+0.2f;
            break;
        case kFiltEnv:
            filtenv = newValue;
            break;
        case kFilterPower:
            usefilter = newValue>=0.5f;
            break;
        case kFAtt:
            if(newValue<0.01f) fatt = 0.1f; //extra fast attack
            else fatt = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue)); //0.0055 .. 0.0
            facoeff = 1.0f - (float)(log(SILENCE) - log(2.f)) / ((0.0001f/fatt) * SR);
            break;
        case kFDec:
            if(newValue<0.01f) fdec = 0.01f; //extra fast decay
            else fdec = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue));
            fdcoeff = 1.0f + (float)(log(jmax(SILENCE,fsus)) - log(2.f)) / ((0.0001f/fdec) * SR);
            break;
        case kFSus:
            fsus = newValue;
            frcoeff = 1.0f + (float)(log(SILENCE*0.5f)) / ((0.0001f/frel) * SR);
            fdcoeff = 1.0f + (float)(log(jmax(SILENCE,fsus)) - log(2.f)) / ((0.0001f/fdec) * SR);
            break;
        case kFRel:
            if(newValue<0.01f) frel = 0.1f; //extra fast release
            else frel = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue));
            frcoeff = 1.0f + (float)(log(SILENCE*0.5f)) / ((0.0001f/frel) * SR);
            break;
        case kAtt:
            if(newValue<0.01f) att = 0.1f; //extra fast attack
            else  att = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue)); //0.0055 .. 0.0
            acoeff = 1.0f - (float)(log(SILENCE) - log(2.f)) / ((0.0001f/att) * SR);
            break;
        case kDec:
            if(newValue<0.01f) dec = 0.01f; //extra fast decay
            else dec = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue));
            dcoeff = 1.0f + (float)(log(jmax(SILENCE,sus)) - log(2.f)) / ((0.0001f/dec) * SR);
            break;
        case kSus:
            sus = newValue;
            rcoeff = 1.0f + (float)(log(SILENCE*0.5f)) / ((0.0001f/rel) * SR);
            dcoeff = 1.0f + (float)(log(jmax(SILENCE,sus)) - log(2.f)) / ((0.0001f/dec) * SR);
            break;
        case kRel:
            if (newValue<0.01f) rel = 0.1f; //extra fast release
            else rel = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue));
            rcoeff = 1.0f + (float)(log(SILENCE*0.5f)) / ((0.0001f/rel) * SR);
            break;
#ifdef MRALIASPRO
        case kAtt3:
            if(newValue<0.01f) att3 = 0.1f; //extra fast attack
            else  att3 = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue)); //0.0055 .. 0.0
            acoeff3 = 1.0f - (float)(log(SILENCE) - log(2.f)) / ((0.0001f/att3) * SR);
            break;
        case kDec3:
            if(newValue<0.01f) dec3 = 0.01f; //extra fast decay
            else dec3 = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue));
            dcoeff3 = 1.0f + (float)(log(jmax(SILENCE,sus3)) - log(2.f)) / ((0.0001f/dec3) * SR);
            break;
        case kSus3:
            sus3 = newValue;
            rcoeff3 = 1.0f + (float)(log(SILENCE*0.5f)) / ((0.0001f/rel3) * SR);
            dcoeff3 = 1.0f + (float)(log(jmax(SILENCE,sus3)) - log(2.f)) / ((0.0001f/dec3) * SR);
            break;
        case kRel3:
            if (newValue<0.01f) rel3 = 0.1f; //extra fast release
            else rel3 = 1.0f - (float)exp(-ifs * exp(5.5 - 7.5 * newValue));
            rcoeff3 = 1.0f + (float)(log(SILENCE*0.5f)) / ((0.0001f/rel3) * SR);
            break;
		case kRandomSpeed:
			if (param[kRandomStrength]>=0.01f) startTimer(1 + roundFloatToInt(1999.f*(1.f-newValue)));
			break;
		case kRandomStrength:
			if (newValue<0.01f && isTimerRunning()) stopTimer();
			else startTimer(1 + roundFloatToInt(1999.f*(1.f-param[kRandomSpeed])));
			break;
#endif
        case kRingMod:
            useringmod = newValue>0.f;
            break;
        case kRate:
            //usedecimator = newValue<1.f && param[kBRMix]>0.f;
            break;
        case kBRMix:
            usedecimator = /*param[kRate]<1.f &&*/ newValue>0.f;
            break;
        case kClip:
            useclipper = newValue>0.f;
            break;
        case kSineMix:
            usesine = newValue>0.f;
            break;
        case kSineFreq:
            sinefreq = 1.2f*newValue-0.2f;
            break;
        case kSineRes:
            sineres = roundFloatToInt(newValue*1023.f)+1;
            break;
        //case kStereo:
        //    usestereo = newValue!=0.5f;
        //    break;
        //case kOscMix:
        //    useosc2 = newValue>denorm;
        //    break;
        case kM1:
            usem1 = newValue>0.f;
            m1=roundFloatToInt((float)getSampleRate()*0.005f*newValue);
            break;
        case kOscGain: oscgain = newValue;
            break;
        case kVolume: vol = newValue*2.f;
            break;
        case kAlias:
            aliasboost = 102.0f*newValue+1.0f;
            break;
        case kAInertia:
            ainertia = newValue==0.f ? 1.0f : 0.00495f-0.0049f*newValue;
            break;
        case kPBRange:
            pbrange = roundFloatToInt(24.0f*newValue);
            break;
        case kOctave:
            octave = 12.f*newValue;
            break;
        case kOctave2:
            octave2 = (float)pow(2.0,18.0*(double)newValue-12.0);
            break;
        case kOctave1:
            octave1 = (float)pow(2.0,18.0*(double)newValue-12.0);
            break;
        case kFreq1:
            detune = (newValue-0.5f)*0.5f;
            break;
        case kPhMod:
            phmodfactor = 0.25f*newValue;
            break;
        case kGlide:
            glide = newValue<0.02f ? 1.f : 1.f - (float)exp(-ifs*exp(6.f-7.f*newValue));
            break;
#ifdef MRALIASPRO
		case kLFO1Rate:
			updateLFOFreq(0,newValue);
			break;
		case kLFO2Rate:
			updateLFOFreq(1,newValue);
			break;
		case kLFO1Sync:
			updateLFOFreq(0,param[kLFO1Rate],newValue>=0.5f);
			break;
		case kLFO2Sync:
			updateLFOFreq(1,param[kLFO2Rate],newValue>=0.5f);
			break;
#endif

		default:
            break;
        }
        if (param[index]!=newValue) {
            param[index] = ap->param[index] = newValue;
            if (!settingProgram) {
				if (!modulating) 
				{
					actualParameter[index] = newValue;
					infoString = getParameterName(index) + ": " + getParameterText(index);
					if (processing) {
						wait=true;
					}
					else {
						sendChangeMessage();
					}
				}
            }
        }
    }
    else if (index==kMorph) {
        if (newValue!=param[kMorph] && !settingProgram) {
            morph(newValue);
            param[kMorph] = newValue;
            infoString = "Morph: " + getParameterText(index);
            //sendChangeMessage ();
            //wait=true;
        }
    }
    else if (index==kRandomize) {
		if (param[kRandomize]==0.f && newValue>0.f && !settingProgram) {
			randomize(newValue);
			param[kRandomize] = 0.f;
		}
    }
}

const String MrAlias2::getParameterName (int index) {
    //logDebugString(String(_iter)+" "+"getParameterName(" + String(index) + ")");
    switch (index)
    {
    case kWaveform1:	return String("Waveform");
    case kWaveform2:	return String("Waveform2");
    case kFreq1:		return String("Detune");
    case kVolume:		return String("Volume");
    case kAlias:		return String("Alias");
    case kPBRange:		return String("PBRange");
    case kCut:		    return String("Cutoff");
    case kRes:		    return String("Resonance");
    case kDivide:		return String("Divide");
    case kRingMod:		return String("RingMod");
    case kPostDivide:   return String("PostDivide");
    case kThresh:       return String("Threshold");
    case kDivEnv:       return String("EnvDivide");
    case kAtt:		    return String("Attack");
    case kDec:		    return String("Decay");
    case kSus:		    return String("Sustain");
    case kRel:		    return String("Release");
    case kClip:         return String("Clipper");
    case kRate:         return String("RateReduce");
    case kBRMix:        return String("SRMix");
    case kSineMix:      return String("SineMix");
    case kSineRes:      return String("SineRes");
    case kSineFreq:     return String("SineFreq");
    case kVelSens:      return String("VelSens");
    case kAInertia:     return String("AliasInertia");
    case kInputGain:    return String("InputGain");
    case kOscGain:      return String("OscGain");
    case kFAtt:		    return String("FiltAttack");
    case kFDec:		    return String("FiltDecay");
    case kFSus:		    return String("FiltSustain");
    case kFRel:		    return String("FiltRelease");
    case kFiltEnv:      return String("FiltEnvAmt");
    case kWet:          return String("InputWetDry");
    case kOctave2:      return String("Osc2Octave");
    case kOctave1:      return String("Osc1Octave");
    case kOctave:       return String("Osc2Harmonic");
    case kStereo:       return String("OscSeparation");
    case kStereo2:      return String("Stereoness");
    case kOscMix:       return String("OscMix");
    case kMode:         return String("Mode");
    case kM1:           return String("M1");
    case kM1Mix:        return String("M1Mix");
    case kPhMod:        return String("PhaseMod");
    case kDivMix:       return String("DivMix");
    case kOPLP:         return String("OPLP");
    case kPostDivMix:   return String("PostDivMix");
    case kFilterPower:  return String("FilterPower");
    case kFKeyFollow:   return String("FilterKeyFollow");
    case kFVSens:       return String("FilterVelSens");
    case kUseProgCh:    return String("UseProgCh");
    case kChannel:      return String("Channel");
    case kFMode:        return String("FilterMode");
    case kLimiter:      return String("Limiter");
    case kExp:          return String("EnvSlope");
    case kFExp:         return String("FilterEnvSlope");
    case kExp3:         return String("Env3Slope");
    case kPitchShift:   return String("PitchShift");
    case kDecoupled1:   return String("Osc1Pitch");
    case kDecoupled2:   return String("Osc2Pitch");
    case kGlide:        return String("Glide");
    case kRetrig:       return String("Retrigger");
    case kEnhanceStereo:return String("EnhanceStereo");
    case kAtt3:		    return String("Env3Attack");
    case kDec3:		    return String("Env3Decay");
    case kSus3:		    return String("Env3Sustain");
    case kRel3:		    return String("Env3Release");
	case kEnv3Amount:   return String("Env3Amount");
	case kLFO1Rate:		return String("LFO1Rate");
	case kLFO1Amount:	return String("LFO1Amount");
	case kLFO1Waveform:	return String("LFO1Waveform");
	case kLFO2Rate:		return String("LFO2Rate");
	case kLFO2Amount:	return String("LFO2Amount");
	case kLFO2Waveform:	return String("LFO2Waveform");
	case kLFO1Free:		return String("LFO1FreeRunning");
	case kLFO2Free:		return String("LFO2FreeRunning");
	case kLFO1Sync:		return String("LFO1TempoSync");
	case kLFO2Sync:		return String("LFO2TempoSync");
	case kRandomSpeed:  return String("RandomSpeed");
	case kRandomStrength:	return String("RandomStrength");
	case kAuto:			return String("AutoRandomizer");
	case kAudioEnvAmount:	return String("AudioEnvAmount");
	case kOsc1ModAmount:	return String("Osc1ModAmount");
	case kOsc2ModAmount:	return String("Osc2ModAmount");
	case kInterpolate1:		return String("Osc1Interpolate");
	case kInterpolate2:		return String("Osc2Interpolate");

    case kRandomize:        return String("Randomize");
    case kMorph:        return String("Morph");
    default:            return String("param[" + String(index) + "]");
    }
}

const String MrAlias2::getParameterText (int index) {
    //logDebugString(String(_iter)+" "+"getParameterName(" + String(index) + ")");
	const float v = (index<numParams) ? actualParameter[index] : 0.f;
    switch (index) {
        //0..99
        case kDivEnv:
        case kInputGain:
        case kRes:
        case kFiltEnv:
        case kRingMod:
        case kBRMix:
        case kSineMix:
        case kDivMix:
        case kPostDivMix:
        case kM1Mix:
        case kOscGain:
        case kVolume:
        case kAInertia:
        case kPhMod:
        case kCut:
        case kFVSens:
        case kVelSens:
        case kFKeyFollow:
        case kOPLP:
        case kGlide:
		case kLFO1Amount:
		case kLFO2Amount:
		case kAudioEnvAmount:
		case kOsc1ModAmount:
		case kOsc2ModAmount:
            return String(v*99.f,3);

        //-99..+99
        case kOscMix:
        case kWet:
        case kFreq1:
        case kStereo:
            return String(v*198.f - 99.f,3);

        //0..100 int
        case kDivide:
        case kPostDivide:
            return String(roundFloatToInt(v*100.f));

        //0..100 float
        case kStereo2:
        case kThresh:
        case kFAtt:
        case kFDec:
        case kFSus:
        case kFRel:
        case kAtt:
        case kDec:
        case kSus:
        case kRel:
        case kAtt3:
        case kDec3:
        case kSus3:
        case kRel3:
        case kRate:
        case kClip:
        case kSineFreq:
        case kSineRes:
        case kM1:
		case kRandomStrength:
            return String(v*100.f,3);

        //named values
        case kFMode:
            switch(filtermode) {
                case svlow: return "Lowpass";
                case svband: return "Bandpass";
                case svnotch: return "Notch";
                case svhigh: return "Highpass";
                case lpf24: return "Lowpass24";
                case formant: return "Formant";
            }
        case kWaveform1:
        case kWaveform2:
        case kLFO1Waveform:
        case kLFO2Waveform:
			return getWaveformName(roundFloatToInt(v*((float)plusUserWaveforms-1.f)));
        case kAlias:
            return String(aliasboost-1.f);
        case kPBRange:
            return String(pbrange);
        case kOctave:
            return String(octave);
        case kOctave1:
        case kOctave2:
            return String(v*18.f-12.f);
        //case kMicrocomputer:
        //    if(param[index]<0.5f) return "Normal";
        //    return "Microcomputer";
        case kFilterPower:
        case kPitchShift:
        case kLimiter:
        case kRetrig:
        case kEnhanceStereo:
		case kLFO1Free:
		case kLFO2Free:
		case kLFO1Sync:
		case kLFO2Sync:
		case kAuto:
		case kInterpolate1:
		case kInterpolate2:
            return v<0.5f ? "Off" : "On";
        case kExp:
        case kFExp:
        case kExp3:
            if(v<0.5f) return "Normal";
            else if (v<1.0f) return "P";
            return "P!";
        case kMode:
            switch (polymode)
            {
            case polyphonic: return "Poly";
            case monophonic: return "Mono";
            case monomicro:  return "microcomputer";
            default: return "?";
            }
        case kChannel:
            return listenchannel==-1 ? "Any" : String(listenchannel+1);
        case kDecoupled1:
        case kDecoupled2:
            return roundFloatToInt(v*128.f)==0 ? "MIDI Notes" : String(roundFloatToInt(v*128.f)-1);
		case kRandomSpeed:
			return String(1 + roundFloatToInt(1999.f*(1.f-v))) + " ms";
#ifdef MRALIASPRO
		case kLFO1Rate:
			if (param[kLFO1Sync]<0.5f) return String(lfo1freq,5) + " Hz";
			else return getTempoSyncText(v);
		case kLFO2Rate:
			if (param[kLFO2Sync]<0.5f) return String(lfo2freq,5) + " Hz";
			else return getTempoSyncText(v);
#endif
        default: return String(v);
    }
}

bool MrAlias2::isMetaParameter(int parameterIndex) {
	//needed for AU validation
	switch(parameterIndex)
	{
	case kMorph: 
	case kRandomize: 
		return true;
	default: return false;
	}
}

const String MrAlias2::getInputChannelName (const int channelIndex) const {
    return String(T("MrAlias2In")) + String(channelIndex + 1);
}

const String MrAlias2::getOutputChannelName (const int channelIndex) const {
    return String(T("MrAlias2Out")) + String(channelIndex + 1);
}

bool MrAlias2::isInputChannelStereoPair (int index) const {
    if (index==0 && getNumInputChannels()>1) return true;
    return false;
}

bool MrAlias2::isOutputChannelStereoPair (int index) const {
    if (index==0 && getNumOutputChannels()>1) return true;
    return false;
}

//======================Programs================================================
void MrAlias2::setCurrentProgram (int index) {
	logDebugString(String(_iter)+" setCurrentProgram(" + String(index) + "): " + programs[index].name);
    settingProgram=true;
	clearModMatrix();
	if (!init) 
	{
		memcpy(programs[curProgram].wave[0],table[draw1],sizeof(programs[curProgram].wave[0]));
		memcpy(programs[curProgram].wave[1],table[draw2],sizeof(programs[curProgram].wave[1]));
		memcpy(programs[curProgram].param,actualParameter,sizeof(float)*numParams);
		infoString = "Program " + String(index+1) + ": " + programs[index].name;
	}
    MrAliasProgram* ap = &programs[index];
    curProgram = index;

    for (int i=0;i<getNumParameters();i++) {
        setParameter(i,ap->param[i]);
        setCCMapping(i,ap->ccmap[i].cc);
        setCCLo(i,ap->ccmap[i].lo);
        setCCHi(i,ap->ccmap[i].hi);
        if (init || followPresetA) snapshotA.param[i] = param[i];
        if (followPresetB) snapshotB.param[i] = param[i];
        if (i!=kMorph) setModMatrix(ap->mods[i].source,i,ap->mods[i].amount);
    }
    if (followPresetA) param[kMorph]=0.f;
    else if (followPresetB) param[kMorph]=1.f;

	memcpy(table[draw1],ap->wave[0],sizeof(programs[curProgram].wave[0]));
	memcpy(table[draw2],ap->wave[1],sizeof(programs[curProgram].wave[1]));
	memcpy(actualParameter,ap->param,sizeof(float)*numParams);
	updateDrawableWave(0);
	updateDrawableWave(1);
    if (!wait) sendChangeMessage();
    if (wait && !processing) {
        wait=false;
        waitcount=0;
        sendChangeMessage();
        updateHostDisplay();
    }
    init = false;
    settingProgram=false;
}

void MrAlias2::changeProgramName(int index, const String &newName) {
    logDebugString(String(_iter)+" changeProgramName(" + String(index) + ", " + newName + ")");
    programs[index].name = newName;
    sendChangeMessage();
}

const String MrAlias2::getProgramName(int index) {
    return programs[index].name;
}

int MrAlias2::getCurrentProgram() {
    return curProgram;
}

//==============================================================================
void MrAlias2::prepareToPlay (double sampleRate, int samplesPerBlock) {
    (void)samplesPerBlock;
    // do your pre-playback setup stuff here..
    SR=(float)sampleRate;
    ifs = 1.0 / sampleRate;
    fScaler = (float)((double)waveSize * ifs);
    fcounttarget = filtercount = roundFloatToInt(SR*0.005f);
    oplpL.updateSR(SR);
    oplpR.updateSR(SR);

    //DC blockers
    dcL.init(SR);
    dcR.init(SR);
    dc2a.init(SR);
    dc2b.init(SR);
    inpostdcL.init(SR);
    inpostdcR.init(SR);
    postdcL.init(SR);
    postdcR.init(SR);
    postdc2L.init(SR);
    postdc2R.init(SR);

    for (int v=maxPoly;v--;) {
        dcsynL[v].init(SR);
        dcsynR[v].init(SR);
        dc3L[v].init(SR);
        dc3R[v].init(SR);
        voice[v].init();
        sfilter[v].update(ff,rr,(float)ifs);
        M1[v].reset();
    }
    filter2.update(ff,rr,(float)ifs);
    infilter.update(ff*2.f,rr*0.64f,(float)ifs);
    voices=0;
    notes[0] = EVENTS_DONE;
    globalM1.reset();
    inM1.reset();
#ifdef MRALIASPRO
    keyboardState.reset();
	envelopeFollower.setup( 10, 500, sampleRate );
#endif
	logDebugString(String(_iter) + " " + String(this->getNumInputChannels())+ " in / " + String(this->getNumOutputChannels()) + " out"); 
	logDebugString(String(_iter) + " sampleRate=" + String(sampleRate)); 
	logDebugString(String(_iter) + " samplesPerBlock=" + String(sampleRate)); 
}

void MrAlias2::updateDrawableWave(int index) {
    for (int i = 0; i < waveSize; i++) {
        dtable[draw1+index][i] = table[draw1+index][(i+1)] - table[draw1+index][i];
    }
    dtable[draw1+index][waveSize-1] = table[draw1+index][0]-table[draw1+index][waveSize-1];
}

void MrAlias2::updateBigWave(int index) {
    for (int i = 0; i < TableSize; i++) {
        dtable[numWaveforms+index][i] = table[numWaveforms+index][(i+1)] - table[numWaveforms+index][i];
    }
    dtable[numWaveforms+index][TableSize-1] = table[numWaveforms+index][0]-table[numWaveforms+index][TableSize-1];
}

void MrAlias2::resetDrawableWave(int waveform, int index) {
    for (int i = 0; i < waveSize; i++) {
		table[draw1+index][i] = table[waveform][i];
		dtable[draw1+index][i] = dtable[waveform][i];
	}
}

void MrAlias2::invertWave(int index) {
    for (int i = 0; i < waveSize; i++) {
		table[draw1+index][i] = -table[draw1+index][i];
		dtable[draw1+index][i] = -dtable[draw1+index][i];
	}
}

void MrAlias2::reverseWave(int index) {
	AudioSampleBuffer temp(1,waveSize);
	temp.copyFrom(0,0,table[draw1+index],waveSize);
    for (int i = 0; i < waveSize; i++) {
		table[draw1+index][i] = temp.getSampleData(0)[waveSize-1-i];
	}
	updateDrawableWave(index);
}

void MrAlias2::normalizeWave(int index) {
	AudioSampleBuffer temp(1,waveSize);
	temp.copyFrom(0,0,table[draw1+index],waveSize);
	float m = temp.getMagnitude(0,waveSize);
	if (m<1.f) temp.applyGain(0,waveSize,1.f/m);
    for (int i = 0; i < waveSize; i++) {
		table[draw1+index][i] = temp.getSampleData(0)[i];
	}
	updateDrawableWave(index);
}

void MrAlias2::createWaves() {
    memset(table,0,sizeof(table));
    memset(dtable,0,sizeof(dtable));
    int32 i;
    //old waves, 256-point wavetable
    //    int32 wh = waveSize / 4;	// 1:3 pulse
    int32 wh = waveSize / 2;	// square
    for (i = 0; i < waveSize; i++) {
        table[rampup][i]   = (float)(-1. + (2. * ((double)i / (double)waveSize))); //ramp up
        table[rampdn][i]   = -table[rampup][i]; //ramp down
        table[pulse][i]    = (i < wh) ? 1.f : -1.f;
		table[sine][i]     = (float)(sin(i*PI/((double)waveSize*0.5)));
        table[triangle][i] = (float)((double)i / ((double)waveSize*0.25));
        if (table[triangle][i]>3.f) table[triangle][i] = table[triangle][i]-4.f;
        else if (table[triangle][i]>1.f) table[triangle][i] = 2.f-table[triangle][i];
		table[draw1][i] = table[sine][i];
		table[draw2][i] = table[rampdn][i];
    }
    //new waves

	Array<File> waveFiles;
	if (File(currentPath+File::separatorString+"waveforms").findChildFiles(waveFiles,File::findFiles,true,"*.wav")) 
	{
		for (int w=0;w<waveFiles.size();w++) 
		{
			if (w<plusUserWaveforms) {
				readWavFile(waveFiles.getReference(w),(int)TableSize,numWaveforms+w);
			}
		}
	}

	float increment = float_2PI / (float)TableSize;
	float x = 0.0f;
    for (i = 0; i < TableSize; i++) {
        float z = (float)i/(float)TableSize;

        table[minko][i] = (float)((Minkowski(z)-z)*9.);
        table[weier][i] = (float)Weierstrass(z,2.)*5.f - 1.f;

		if (i%2==0) table[comb][i] = 0.9f; //"autoalias"
		else        table[comb][i] = -0.9f;

		table[harm][i]=(float) ( //"eight"
			((float)sin(x     + float_2PI)) +
			((float)sin(x*2.f + float_2PI)) +
			((float)sin(x*3.f + float_2PI)) +
			((float)sin(x*4.f + float_2PI))*0.9f +
			((float)sin(x*5.f + float_2PI))*0.8f +
			((float)sin(x*6.f + float_2PI))*0.7f +
			((float)sin(x*7.f + float_2PI))*0.6f +
			((float)sin(x*8.f + float_2PI))*0.5f
			) / 4.0f;

		table[odd][i]=(float) ( //"oddeight"
			((float)sin(x      + float_2PI)) +
			((float)sin(x*3.f  + float_2PI)) +
			((float)sin(x*5.f  + float_2PI)) +
			((float)sin(x*7.f  + float_2PI))*0.9f +
			((float)sin(x*9.f  + float_2PI))*0.8f +
			((float)sin(x*11.f + float_2PI))*0.7f +
			((float)sin(x*13.f + float_2PI))*0.6f +
			((float)sin(x*15.f + float_2PI))*0.5f
			) / 4.0f;

		table[computer][i]=(float)( 
			sin( (double)i / (double)TableSize + ( sin((double)i*4))/2 ) )
			*2.f;
		table[11][i]=(float)(sin((double)i/(double)TableSize*(sin((double)i*6)/4)))*4.f; //"funnel"
		table[12][i]=(float)cos((double)i*4*((double)table[comb][i]/5)); //"grate"
		table[noise][i]=(float)(sin((double)i*(sin((double)i*1.3)/5)));
		table[14][i]=(float) ( //"sine+"
			((float)sin(x + float_2PI)) +
			((float)sin(x*1024.f + float_2PI))
			) / 4.0f;
        table[15][i]=(i < (TableSize/64)) ? -1.f : 1.f; //"narrow"
		table[octaves][i]=(float)(
			((float)sin(x       + float_2PI)) +
			((float)sin(x*2.f   + float_2PI)) +
			((float)sin(x*4.f   + float_2PI)) +
			((float)sin(x*8.f   + float_2PI))*0.9 +
			((float)sin(x*16.f  + float_2PI))*0.9 +
			((float)sin(x*32.f  + float_2PI))*0.8 +
			((float)sin(x*64.f  + float_2PI))*0.8 +
			((float)sin(x*128.f + float_2PI))*0.7 +
			((float)sin(x*256.f + float_2PI))*0.7 +
			((float)sin(x*512.f + float_2PI))*0.6 +
			((float)sin(x*1024.f+ float_2PI))*0.6
			) / 4.0f;
		table[17][i]=(float)cos((double)i*4*((double)table[comb][i]/150)); //"ughhh"

		x += increment;
    }

	//fill extra waveform slots with random waveforms
	for (int w=waveFiles.size()+numWaveforms;w<plusUserWaveforms;w++) {
		//int randomwave = (Random::getSystemRandom().nextInt())%(numWaveforms-1);
		//memcpy(table[w],table[randomwave],sizeof(float)*TableSize);
		memset(table[w],0,sizeof(float)*TableSize);
	}

	// difference table for linear interpolation
    for (int w=0;w<plusUserWaveforms;w++) { 
        if (w<=sine || w==draw1 || w==draw2) {
            for (i = 0; i < waveSize-1; i++) {
                dtable[w][i] = table[w][(i+1)] - table[w][i];
            }
            dtable[w][waveSize-1] = table[w][0]-table[w][waveSize-1];
#ifdef _DEBUG
			saveWavFile(File(currentPath+File::separator+getWaveformName(w)+".wav"),waveSize,w);
#endif
        }
        else {
            for (i = 0; i < TableSize-1; i++) {
				dtable[w][i] = table[w][(i+1)] - table[w][i];
            }
			dtable[w][TableSize-1] = table[w][0]-table[w][TableSize-1];
#ifdef _DEBUG
			saveWavFile(File(currentPath+File::separator+getWaveformName(w)+".wav"),TableSize,w);
			//File wavFile = File(currentPath+File::separator+getWaveformName(w)+"_dtable.wav");
			//AudioFormatWriter* audioWriter = 0;
			//AudioSampleBuffer buffer(1,TableSize);
			//buffer.copyFrom(0,0,dtable[w],TableSize);
			//WavAudioFormat wavFormat;
			//audioWriter = wavFormat.createWriterFor(wavFile.createOutputStream(),44100,1,32,0,0);
			//buffer.writeToAudioWriter(audioWriter,0,TableSize);
			//delete audioWriter;
#endif
		}
    }

    // make frequency (Hz) table
    double k = 1.0594630943592952645618252949461;	// 12th root of 2
    double a = 27.5; // A below note 0
    a *= k;	// B
    a *= k;	// Bb
    a *= k;	// C, frequency of midi note 0
    for (i = 0; i < numFrequencies; i++) {
        freqtab[i] = a;
        a *= k;
    }
}

void MrAlias2::releaseResources() {
    // when playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for (int v=0;v<maxPoly;v++) {
		sfilter[v].reset();
	}
    processing=false;
}

void MrAlias2::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
	processing=true;
    #if MAKE_LOG
    _iter++;
    #endif
    int sampleFrames = buffer.getNumSamples();
    waitcount+=sampleFrames;
    if (wait) {
        if (waitcount>=roundDoubleToInt(getSampleRate()*0.041667)) { //24fps
            logDebugString(String(_iter)+" waitcounter in processBlock");
            waitcount=0;
            sendChangeMessage();
            updateHostDisplay();
            if (!editorIsShowing) wait=false;
        }
    }
#ifdef MRALIASPRO
	//timeinfo
	AudioPlayHead::CurrentPositionInfo pos;
    if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition (pos))
    {
        if (memcmp (&pos, &lastPosInfo, sizeof (pos)) != 0)
        {
			ppqPerBar = ((float)pos.timeSigNumerator * 4.f / (float)pos.timeSigDenominator);
			bpm = (float)pos.bpm;
			if (param[kLFO1Sync]>=0.5f) updateLFOFreq(0,param[kLFO1Rate]);
			if (param[kLFO2Sync]>=0.5f) updateLFOFreq(1,param[kLFO2Rate]);
			lastPosInfo = pos;
		}
    }
    else
    {
        zeromem (&lastPosInfo, sizeof (lastPosInfo));
        lastPosInfo.timeSigNumerator = 4;
        lastPosInfo.timeSigDenominator = 4;
        lastPosInfo.bpm = 120;
    }
	if (lastPosInfo.isPlaying)
	{
		float scale=1.f;
		if (lfo1w>sine && lfo1w!=draw1 && lfo1w!=draw2) 
			scale = 16.f; //adjustment for larger wavetable size
		if (param[kLFO1Free]>=0.5f && param[kLFO1Sync]>=0.5f)
		{
			float p = fmod((float)lastPosInfo.ppqPosition,beats[0])/beats[0];
			freelfo1 = waveSize*scale*p; 
		}
		if (lfo2w>sine && lfo2w!=draw1 && lfo2w!=draw2) 
			scale = 16.f; //adjustment for larger wavetable size
		if (param[kLFO2Free]>=0.5f && param[kLFO2Sync]>=0.5f)
		{
			float p = fmod((float)lastPosInfo.ppqPosition,beats[1])/beats[1];
			freelfo2 = waveSize*scale*(p - floor(p)); 
		}
	}
    //midi input
    keyboardState.processNextMidiBuffer (midiMessages,0,buffer.getNumSamples(),true);
#endif
    MidiBuffer::Iterator mid_buffer_iter(midiMessages);
    MidiMessage midi_message(0xfe);
    int sample_number;
    long npos=0;
    while(mid_buffer_iter.getNextEvent(midi_message,sample_number))
    {
        uint8 *midiData = midi_message.getRawData();
        const unsigned char status = midiData[0] & 0xf0; //ignoring channel
        const unsigned char data1  = midiData[1] & 0x7f;
        const unsigned char data2  = midiData[2] & 0x7f;

        if (midi_message.isForChannel(listenchannel+1) || listenchannel==-1) {
            if (status == 0x90 && data2>0) { //noteon
                logDebugString(String(_iter)+" noteOn " + String(data1) + " " + String(data2) + " " + String(sample_number));
                if (!ledon) {
                    ledon=true;
                    sendChangeMessage();
                }
                notes[npos++] = sample_number; //delta
                notes[npos++] = data1; //note
                notes[npos++] = data2; //vel
                if (useccmap) {
                    for (int i=0;i<numParams-1;i++) {
                        if (ccmap[i].cc==128) {
                           float value = linearMap(velScaler*(data2-1),ccmap[i].lo,ccmap[i].hi,0.f,1.f);
                           setParameterNotifyingHost(i,value);
                        }
                    }
                }
            }
            else if (status == 0x80 || (status==0x90 && data2==0)) { //noteoff
                logDebugString(String(_iter)+" noteOff " + String(data1) + " " + String(data2) + " " + String(sample_number));
                if (ledon) {
                    ledon=false;
                    sendChangeMessage();
                }
                notes[npos++] = sample_number; //delta
                notes[npos++] = data1; //note
                notes[npos++] = 0;     //vel
            }
            else if (status == 0xb0) //CC
            {
                //logDebugString(String(_iter)+" CC " + String(data1) + " " + String(data2) + " " + String(sample_number));
				if (data1 == 0x01) // mod wheel
				{
					modSource[modModWheel] = midiScaler*(float)data2;
				}
                if (data1 == 0x7b) // all notes off
                {
                    logDebugString(String(_iter)+" all notes off");
                    if (ledon) {
                        ledon=false;
                        sendChangeMessage();
                    }
                    for (int v=0;v<maxPoly;v++) {
                        voice[v].envl=0;
                        voice[v].envd=0.2f;
                        voice[v].fenvl=0;
                        voice[v].fenvd=rel;
#ifdef MRALIASPRO
                        voice[v].envl3=0;
                        voice[v].envd3=rel;
#endif
                    }
                    sustain = 0;
				}
                else {
                    if (midilearnlisten || useccmap) {
                        if (ccmap[kMorph].cc==data1) {
                           float value = linearMap(midiScaler*data2,ccmap[kMorph].lo,ccmap[kMorph].hi,0.f,1.f);
                           setParameterNotifyingHost(kMorph,value);
                        }
                        else if (ccmap[kMorph].cc==midiLearn) {
                           setCCMapping(kMorph,data1);
                        }
                        else {
                            for (int i=0;i<numParams-1;i++) {
                                if (ccmap[i].cc==midiLearn) {
                                   setCCMapping(i,data1);
                                }
                                if (ccmap[i].cc==data1) {
                                   float value = linearMap(midiScaler*data2,ccmap[i].lo,ccmap[i].hi,0.f,1.f);
                                   setParameterNotifyingHost(i,value);
                                }
                            }
                        }
                        midilearnlisten=false;
                    }
                    if (data1 == 0x40)  //sustain
                    {
                        sustain = data2 & 0x40;
                        if(sustain==0)
                        {
                            notes[npos++] = sample_number;
                            notes[npos++] = SUSTAIN; //end all sustained notes
                            notes[npos++] = 0;
//                            infoString = "Sustain Off";
//                            sendChangeMessage();
                        }
//                        else {
//                            infoString = "Sustain On";
//                            sendChangeMessage();
//                        }
                    }
                }
            }
            else if (status == 0xe0) //PitchBend
            {
                //logDebugString(String(_iter)+" PitchBend " + String(data1) + " " + String(data2) + " " + String(sample_number));                
				unsigned short pb14 = CombineBytes(data1,data2);
				double signedpb=0.0;
                if (pb14==8192) bend=1.f; //centered
                else {
                    //convert pitch bend to a frequency multiplication factor:
                    signedpb = ((double)pb14-8192.0);
                    double factor;
                    bool pos = signedpb>0.f;
                    if (pos) factor = 1.0/(12.0*8191.0); //1.017376795670044357628291213934e-5
                    else     factor = 1.0/(12.0*8192.0); //1.0172526041666666666666666666667e-5

                    if (pbrange==0) {
                        // +/- 10 cents bend
                        factor*=0.1;
                    }
                    bend = (float)pow(2.0,(double)pbrange*signedpb*factor);
                }
				modSource[modPitchBend] = 1.f + (float)(signedpb/8192.0);
            }
            else if (status == 0xd0) //Channel Pressure
            {
                if (useccmap) {
                    if (ccmap[kMorph].cc==129) {
                       float value = linearMap(midiScaler*data1,ccmap[kMorph].lo,ccmap[kMorph].hi,0.f,1.f);
                       setParameterNotifyingHost(kMorph,value);
                    }
                    else {
                        for (int i=0;i<numParams-1;i++) {
                            if (ccmap[i].cc==129) {
                               float value = linearMap(midiScaler*data1,ccmap[i].lo,ccmap[i].hi,0.f,1.f);
                               setParameterNotifyingHost(i,value);
                            }
                        }
                    }
                }
#ifdef MRALIASPRO
                modSource[modChPressure]=midiScaler*(float)data1;
#endif
            }
            else if (status == 0xa0) //Poly Aftertouch
            {
                if (useccmap) {
                    for (int i=0;i<numParams-1;i++) {
                        if (ccmap[i].cc==130) {
                           float value = linearMap(midiScaler*data2,ccmap[i].lo,ccmap[i].hi,0.f,1.f);
                           setParameterNotifyingHost(i,value);
                        }
                    }
                }
                for (int v=0;v<maxPoly;v++) {
                    if (voice[v].notey==data1) voice[v].pressure = midiScaler*(float)data2;
                }
            }
            else if (status == 0xc0) //Program Change
            {
                if (useprogch) this->setCurrentProgram(data1);
            }
        }
    }
    notes[npos] = EVENTS_DONE;

    //audio output------------------------------------------------------------------
	//useinput = ingain==0 ? false : getNumInputChannels()>0;
	useinput = getNumInputChannels()>0;

	if (!useinput) {
		buffer.clear();
	}
	else if (buffer.getMagnitude(0,sampleFrames) < 0.00000001f) {
		useinput=false;
	}

	float* bufferL = getNumOutputChannels()>0 ? buffer.getSampleData(0) : &zero;
	float* bufferR = getNumOutputChannels()>1 ? buffer.getSampleData(1) : &zero;
	if (getNumInputChannels()==1 && getNumOutputChannels()==2) buffer.clear(1,0,sampleFrames);

    float rms = 0.f;
    bool aledwason = aledon;
    aledon=false;
    if (wet>0.f && useinput) {
		rms = buffer.getRMSLevel(0,0,sampleFrames)+ (getNumInputChannels()==1 ? 0.f : buffer.getRMSLevel(1,0,sampleFrames));
        aledon=true;

        //if (param[kPitchShift]>=0.5f && pbBufferIsFull) {
        //// low-quality pitch shift for audio input
        //    smbPitchShift(azip, sampleFrames, 4096, 2, SR, bufferL, bufferL);
        //    smbPitchShift(azip, sampleFrames, 4096, 2, SR, bufferR, bufferR);
        //}
    }
    if (aledon!=aledwason) sendChangeMessage();
	
	if(voices>0 || useinput || notes[0]<sampleFrames 
#ifdef MRALIASPRO
		|| param[kLFO1Free]>=0.5f || param[kLFO2Free]>=0.5f
#endif
		)
    {
        long event=0, frame=0;
        while(frame<sampleFrames)
        {
            long frames = notes[event++];
            if(frames>sampleFrames) frames = sampleFrames;
            frames -= frame;
            frame += frames;

            while(--frames>=0)
            {
#ifdef MRALIASPRO
				//free running lfos
				int iphase = 0;
				int index = 0;
				float scale = 1.f;
				int mask = TableSize-1;
				if (param[kLFO1Free]>=0.5f) {
					if (lfo1w>sine && lfo1w!=draw1 && lfo1w!=draw2) {
						scale = 16.f; //adjustment for larger wavetable size
						wsf = (float)TableSize;
						mask = TableSize-1;
					}
					else {
						wsf = (float)waveSize;
						mask = waveSize-1;
					}
					iphase = ((int) freelfo1);
					freelfo1 = fmod(freelfo1,wsf);
					index = iphase & mask;
					modSource[modLFO1]=jmax(0.f,1.f + /*0.5f * */param[kLFO1Amount]*MOD(kLFO1Amount) * (lfowave1[index] + lfodtable1[index]*(freelfo1 - (float) iphase)));
					freelfo1 += fScaler*lfo1freq*scale*MOD(kLFO1Rate);
					for (int v=0;v<maxPoly;v++) vmodSource[modLFO1][v] = modSource[modLFO1];
				}
				if (param[kLFO2Free]>=0.5f) {
					if (lfo2w>sine && lfo2w!=draw1 && lfo2w!=draw2) {
						scale = 16.f; //adjustment for larger wavetable size
						wsf = (float)TableSize;
						mask = TableSize-1;
					}
					else {
						wsf = (float)waveSize;
						mask = waveSize-1;
					}
					iphase = ((int) freelfo2);
					freelfo2 = fmod(freelfo2,wsf);
					index = iphase & mask;
					modSource[modLFO2]=jmax(0.f,1.f + /*0.5f * */param[kLFO2Amount]*MOD(kLFO2Amount) * (lfowave2[index] + lfodtable2[index]*(freelfo2 - (float) iphase)));
					freelfo2 += fScaler*lfo2freq*scale*MOD(kLFO2Rate);
					for (int v=0;v<maxPoly;v++) vmodSource[modLFO2][v] = modSource[modLFO2];
				}
#endif

                ++filtercount;
                if (filtercount>=fcounttarget) filtercount=0;
                fzip += 0.0005f * (ff - fzip); //filter zipper noise filter
                rzip += 0.0005f * (rr - rzip); //filter zipper noise filter
                bzip += ainertia * (bend - bzip); //de-zippered pitchbend
                azip += ainertia * (aliasboost - azip);
                srzip += ainertia * (param[kRate] - srzip);

                float o1=0.f;
                float o2=0.f;
                float i1=0.f;
                float i2=0.f;
#ifndef noinputs
                //audio input
	#ifdef MRALIASPRO
				modSource[modAudio]=fabs((*bufferL+*bufferR)*0.5f);
				modSource[modAudioEnv]=(1.f-param[kAudioEnvAmount])+param[kAudioEnvAmount]*jlimit(0.f,1.f,envelopeFollower.process(modSource[modAudio]));
	#endif
                if (useinput) {
                    i1=(*bufferL)*ingain*MOD(kInputGain);
					i2= getNumInputChannels()==1 ? i1 : (*bufferR)*ingain*MOD(kInputGain);
                    float Lin=i1;
                    float Rin=i2;
                    if (wet>0.f) {
                        if (usedecimator) {
                            smix(Lin,Rin,
                                indecimator.process(Lin+denorm,param[kRate]),
                                indecimator.process(Rin+denorm,param[kRate]),
                                param[kBRMix]*MOD(kBRMix));
                        }
                        if (target>0) { //divide effect
                            smix(Lin,Rin,
								indivL.process(Lin+denorm,threshold*MOD(kThresh),target),
								indivR.process(Rin+denorm,threshold*MOD(kThresh),roundFloatToInt((float)target*MOD(kDivide))),
								param[kDivMix]*MOD(kDivMix));
                            Lin = inpostdcL.process(Lin);
                            Rin = inpostdcR.process(Rin);
                        }
                        if (usem1) {
                            inM1.stprocess(Lin,Rin,roundFloatToInt((float)m1*MOD(kM1)),param[kM1Mix]*MOD(kM1Mix));
                        }
                        if (usesine) {
                            smix(Lin,Rin,
                                rms*insineL.process(Lin+denorm+sinefreq*MOD(kSineFreq),(float)ifs,roundFloatToInt((float)sineres*MOD(kSineRes))),
                                rms*insineR.process(Rin+denorm+sinefreq*MOD(kSineFreq),(float)ifs,roundFloatToInt((float)sineres*MOD(kSineRes))),
                                param[kSineMix]*MOD(kSineMix));
                        }
                        if (usefilter) {
                            const float prmtempL=Lin+denorm;
                            const float prmtempR=Rin+denorm;
                            if (filtermode==lpf24) {
                                if (filtercount==0) {
                                    infilter.update(fzip*2.f*MOD(kCut),rzip*0.64f*MOD(kRes),(float)ifs);
                                }
                                infilter.stprocess(Lin,Rin);
                                Rin += denorm;
                                Lin += denorm;
                            }
                            else if (filtermode==formant) {
                                Lin = informantL.process(Lin,rzip*MOD(kRes),fzip*(4.f/12500.f)*MOD(kCut));
                                Rin = informantR.process(Rin,rzip*MOD(kRes),fzip*(4.f/12500.f)*MOD(kCut));
                            }
                            else {
                                insvf.stprocess(Lin,Rin,fzip*MOD(kCut),rzip*MOD(kRes),(float)ifs,filtermode);
                            }

                            //ringmod
                            if (useringmod) {
                                smix(Lin,Rin,2.f*postdc2L.process(Lin*prmtempL),2.f*postdc2R.process(Rin*prmtempR),param[kRingMod]*MOD(kRingMod));
                            }
                        }
                        smix(i1,i2,Lin,Rin,wet*MOD(kWet));
                    }
                }
#endif

                bool onlyL = (param[kStereo]==0.f && param[kOscMix]==0.f)
                    || (param[kStereo]==1.f && param[kOscMix]==1.f);
                bool onlyR = (param[kStereo]==0.f && param[kOscMix]==1.f)
                    || (param[kStereo]==1.f && param[kOscMix]==0.f);
                Voice* V = voice;
                for (int v=0;v<maxPoly;v++)
                {
                    if (V->env>SILENCE) {
#ifdef MRALIASPRO
                        vmodSource[modVelocity][v]=((float)V->velocity)*midiScaler;
                        vmodSource[modModWheel][v]=modSource[modModWheel];
                        vmodSource[modPitchBend][v]=modSource[modPitchBend];
                        vmodSource[modAftertouch][v]=V->pressure;
						vmodSource[modChPressure][v]=modSource[modChPressure];
                        vmodSource[modNote][v]=((float)V->notey)*midiScaler;
						vmodSource[modAudio][v]=modSource[modAudio];
						vmodSource[modAudioEnv][v]=modSource[modAudioEnv];
#endif
						//amp envelope
                        if (param[kExp]>0.5f) {
                            if (V->envd==att && param[kAtt]==0.f) {
                                V->env=1.f;
                                V->envd=dec;
                            }
                            else {
                                V->env *= V->coeff;
                                if (param[kExp]==1.f && V->env>0.6f) V->env *= V->coeff*V->coeff;
                                if (V->envl==sus) V->env = jmax(V->env,sus);
                            }
                        }
                        else {
                            V->env += V->envd * (V->envl - V->env);
                            V->env = jmax(V->env,SILENCE);
                        }
                        if((V->env+V->envl)>3.0f) {
                            V->coeff=dcoeff;
                            V->envd=dec;
                            V->envl=sus;
                        }
                        if (genv<V->env) {
                            genv = V->env*( ((float)V->velocity*midiScaler * param[kVelSens]) + (1.f-param[kVelSens]))*oscgain;
                            genvd = V->envd;
                            genvl = V->envl;
                        }
#ifdef MRALIASPRO
                        vmodSource[modAmpEnv][v]=jlimit(0.f,1.f,V->env);
#endif
                        //filter envelope
                        if (usefilter) {
                            if (param[kFExp]>0.5f) {
                                if (V->fenvd==fatt && param[kFAtt]==0.f) {
                                    V->fenv=1.f;
                                    V->fenvd=fdec;
                                }
                                else {
                                    V->fenv *= V->fcoeff;
                                    if (param[kFExp]==1.f && V->fenv>0.6f) V->fenv *= V->fcoeff*V->fcoeff;
                                    if (V->fenvl==fsus) V->fenv = jmax(V->fenv,fsus);
                                }
                            }
                            else {
                                V->fenv += V->fenvd * (V->fenvl - V->fenv);
                            }
                            V->fenv=jlimit(SILENCE,1.01f,V->fenv);
                            if((V->fenv+V->fenvl)>3.0f) {
                                V->fcoeff=fdcoeff;
                                V->fenvd=fdec;
                                V->fenvl=fsus;
                            }
                            if (gfenv<V->fenv) {
                                gfenv = V->fenv;
                                gfenvd = V->fenvd;
                                gfenvl = V->fenvl;
                                gvelocity = (float)V->velocity*midiScaler;
                            }
                        }
#ifdef MRALIASPRO
                        vmodSource[modFiltEnv][v]=jlimit(0.f,1.f,V->fenv);
                        //assignable envelope 1
                        //V->env3 += V->envd3 * (V->envl3 - V->env3);
                        //V->env3=jlimit(SILENCE,1.01f,V->env3);
                        if (param[kExp3]>0.5f) {
                            if (V->envd3==att3 && param[kAtt3]==0.f) {
                                V->env3=1.f;
                                V->envd3=dec3;
                            }
                            else {
                                V->env3 *= V->coeff3;
                                if (param[kExp3]==1.f && V->env3>0.6f) V->env3 *= V->coeff3*V->coeff3;
                                if (V->envl3==sus3) V->env3 = jmax(V->env3,sus3);
                            }
                        }
                        else {
                            V->env3 += V->envd3 * (V->envl3 - V->env3);
                            //V->env3 = jmax(V->env3,SILENCE);
	                        V->env3=jlimit(SILENCE,1.01f,V->env3);
                        }
                        if((V->env3+V->envl3)>3.0f) {
                            V->coeff3=dcoeff3;
                            V->envd3=dec3;
                            V->envl3=sus3;
                        }
                        //vmodSource[modEnv3][v]=jlimit(1.f-param[kEnv3Amount],1.f,V->env3);
						vmodSource[modEnv3][v] = (1.f-param[kEnv3Amount])+param[kEnv3Amount]*jlimit(0.f,1.f,V->env3);
#endif
                        const bool enhanceStereo = param[kEnhanceStereo]>=0.5f;

                        //determine oscillator frequencies
                        const int32 n=V->notey & 0x7f;
                        const float ksf = (1.f-param[kFKeyFollow])+param[kFKeyFollow]*(float)(n)*midiScaler;
                        gksf = ksf;
                        const float baseFreq1 =
                            V->oldnote==NO_NOTE ? (float)freqtab[( roundFloatToInt(param[kDecoupled1]*128.f)>0 ? (roundFloatToInt(param[kDecoupled1]*128.f)-1) : n )] * fScaler
                            : V->oldBaseFreq1
                                + ( (float)freqtab[( roundFloatToInt(param[kDecoupled1]*128.f)>0 ? (roundFloatToInt(param[kDecoupled1]*128.f)-1) : n )] * fScaler
                                  - V->oldBaseFreq1 )
                                 * glide;
                        V->oldBaseFreq1 = baseFreq1;
                        const float baseFreq2 =
                            V->oldnote==NO_NOTE ? (float)freqtab[( roundFloatToInt(param[kDecoupled2]*128.f)>0 ? (roundFloatToInt(param[kDecoupled2]*128.f)-1) : n )] * fScaler
                            : V->oldBaseFreq2
                                + ( (float)freqtab[( roundFloatToInt(param[kDecoupled2]*128.f)>0 ? (roundFloatToInt(param[kDecoupled2]*128.f)-1) : n )] * fScaler
                                  - V->oldBaseFreq2 )
                                 * glide;
                        V->oldBaseFreq2 = baseFreq2;
                        freq1[v] = bzip * azip*VMOD(kAlias,v)
                                  * baseFreq1
                                  * octave1*VMOD(kOctave1,v)
                                  + detune*VMOD(kFreq1,v);
                        freq2[v] = bzip * ( azip*VMOD(kAlias,v) + octave*VMOD(kOctave,v) )
                                  * baseFreq2
                                  * octave2*VMOD(kOctave2,v)
                                  - detune*VMOD(kFreq1,v);
                        if (w1>sine && w1!=draw1 && w1!=draw2) freq1[v]*=16.f; //adjustment for larger wavetable size
                        if (w2>sine && w2!=draw1 && w2!=draw2) freq2[v]*=16.f; //adjustment for larger wavetable size

                        //oscillators
                        //osc 1
                        int iphase = ((int) V->fPhase1); //integer phase
                        float alpha = V->fPhase1 - (float) iphase; //phase error

                        unsigned int mask, index;
                        //adjust for different wavetable sizes
                        if (w1<=sine || w1==draw1 || w1==draw2) {
                            wsf = (float)waveSize;
                            mask = waveSize-1;
                        }
                        else {
                            wsf = (float)TableSize;
                            mask = TableSize-1;
                        }
                        //wrap phase to the wavetable size
                        V->fPhase1 = fmod(V->fPhase1,wsf);
                        index = iphase & mask;
                        //increment for next time
                        V->fPhase1 += freq1[v];

						float synthL = wave1[index] + ((param[kInterpolate1]>0.5f) ? dtable1[index]*alpha : 0.f);

                        //osc 2
                        //if (useosc2) {
                        V->fPhase2 *= 1.f + synthL*phmodfactor*VMOD(kPhMod,v);
                        iphase = ((int) V->fPhase2);
                        alpha = V->fPhase2 - (float) iphase;
                        if (w2<=sine || w2==draw1 || w2==draw2) {
                            wsf = (float)waveSize;
                            mask = waveSize-1;
                        }
                        else {
                            wsf = (float)TableSize;
                            mask = TableSize-1;
                        }
                        V->fPhase2 = fmod(V->fPhase2,wsf);
                        V->fPhase2 += freq2[v];
                        index = iphase & mask;
						float synthR = wave2[index] + ((param[kInterpolate2]>0.5f) ? dtable2[index]*alpha : 0.f);

#ifdef MRALIASPRO
                        vmodSource[modOsc1][v]=jmax(0.f,1.f + param[kOsc1ModAmount]*MOD(kOsc1ModAmount) * synthL);
                        vmodSource[modOsc2][v]=jmax(0.f,1.f + param[kOsc2ModAmount]*MOD(kOsc2ModAmount) * synthR);
#endif
						const float divscaler = 1.f-0.5f*V->env*divenv; //to apply envelope before divide effect
                        synthL = mixB(synthL*divscaler,0.f,param[kOscMix]*VMOD(kOscMix,v));
                        synthR = mixB(0.f,synthR*divscaler,param[kOscMix]*VMOD(kOscMix,v));
                        //xmix(synthL,synthR,param[kOscMix]);
                        //}
#ifdef MRALIASPRO
                        //vmodSource[modOsc1][v]=synthL;
                        //vmodSource[modOsc2][v]=synthR;

						float scale = 1.f;
						//lfo 1
						if (param[kLFO1Free]<0.5f) {
							if (lfo1w>sine && lfo1w!=draw1 && lfo1w!=draw2) {
								scale = 16.f; //adjustment for larger wavetable size
								wsf = (float)TableSize;
								mask = TableSize-1;
							}
							else {
								wsf = (float)waveSize;
								mask = waveSize-1;
							}
							iphase = ((int) V->lfo1);
							V->lfo1 = fmod(V->lfo1,wsf);
							index = iphase & mask;
							vmodSource[modLFO1][v]=jmax(0.f,1.f + /*0.5f * */param[kLFO1Amount]*VMOD(kLFO1Amount,v) * (lfowave1[index] + lfodtable1[index]*(V->lfo1 - (float) iphase)));
							V->lfo1 += fScaler*lfo1freq*scale*VMOD(kLFO1Rate,v);
						}
						//lfo 2
						if (param[kLFO2Free]<0.5f) {
							if (lfo2w>sine && lfo2w!=draw1 && lfo2w!=draw2) {
								scale = 16.f; //adjustment for larger wavetable size
								wsf = (float)TableSize;
								mask = TableSize-1;
							}
							else {
								scale = 1.f;
								wsf = (float)waveSize;
								mask = waveSize-1;
							}                        
							iphase = ((int) V->lfo2);
							V->lfo2 = fmod(V->lfo2,wsf);
							index = iphase & mask;
							vmodSource[modLFO2][v]=jmax(0.f,1.f + /*0.5f * */param[kLFO2Amount]*VMOD(kLFO2Amount,v) * (lfowave2[index] + lfodtable2[index]*(V->lfo2 - (float) iphase)));
							V->lfo2 += fScaler*lfo2freq*scale*VMOD(kLFO2Rate,v);
						}
#endif

                        xpanEP(synthL,synthR,param[kStereo]*VMOD(kStereo,v));
#ifndef dontusepervoicefx
                        if (usedecimator) {
                            smix(synthL,synthR,
                                decimatorL[v].process(synthL,srzip*VMOD(kRate,v)),
                                decimatorR[v].process(synthR,srzip*VMOD(kRate,v)),
                                param[kBRMix]*VMOD(kBRMix,v));
                        }
                        if (target>0) {
                            smix(synthL,synthR,
                                divL[v].process(synthL,threshold*VMOD(kThresh,v),roundFloatToInt((float)target*VMOD(kDivide,v))),
                                divR[v].process(synthR,threshold*VMOD(kThresh,v),roundFloatToInt((float)target*VMOD(kDivide,v))),
                                param[kDivMix]*VMOD(kDivMix,v));
                        }
                        if (usem1) {
                            M1[v].stprocess(synthL,synthR,roundFloatToInt((float)m1*VMOD(kM1,v)),param[kM1Mix]*VMOD(kM1Mix,v));
                        }
                        if (usesine) {
                            smix(synthL,synthR,
                                sineeffectL[v].process(synthL+sinefreq*VMOD(kSineFreq,v),(float)ifs,roundFloatToInt((float)sineres*VMOD(kSineRes,v))),
                                sineeffectR[v].process(synthR+sinefreq*VMOD(kSineFreq,v),(float)ifs,roundFloatToInt((float)sineres*VMOD(kSineRes,v))),
                                param[kSineMix]*VMOD(kSineMix,v));
                        }
                        if (usefilter) {
                            //ringmod source
                            float rmtempL=synthL;
                            float rmtempR=synthR;
                            if (filtermode==lpf24) {
                                if (filtercount==0) {
                                    const float fcutoff = (fzip*ksf*V->fenv*filtenv + fzip*ksf*(1.f-filtenv))
                                        * ( ((float)V->velocity*midiScaler * param[kFVSens]) + (1.f-param[kFVSens]) );
                                    sfilter[v].update(fcutoff*VMOD(kCut,v),rzip*VMOD(kRes,v),(float)ifs);
                                }
                                sfilter[v].stprocess(synthL,synthR);
                                rmtempL=synthL;
                                rmtempR=synthR;
                                sfilter[v].stprocess(synthL,synthR);
                            }
                            else if (filtermode==formant) {
                                const float fcutoff = 0.00032f * (fzip*ksf*V->fenv*filtenv + fzip*ksf*(1.f-filtenv))
                                    * ( ((float)V->velocity*midiScaler * param[kFVSens]) + (1.f-param[kFVSens]) )
                                    *VMOD(kCut,v);
                                synthL = formantL[v].process(synthL,rzip*VMOD(kRes,v),fcutoff,true);
                                synthR = formantR[v].process(synthR,rzip*VMOD(kRes,v),fcutoff,true);
                            }
                            else {
                                rmtempL=synthL;
                                rmtempR=synthR;
                                const float fcutoff = (fzip*ksf*V->fenv*filtenv + fzip*ksf*(1.f-filtenv))
                                        * ( ((float)V->velocity*midiScaler * param[kFVSens]) + (1.f-param[kFVSens]) )
                                        *VMOD(kCut,v);
                                svf[v].stprocess(synthL,synthR,fcutoff,rzip*VMOD(kRes,v),(float)ifs,filtermode);
                                synthL*=0.5f;
                                synthR*=0.5f;
                            }

                            //ringmod
                            if (useringmod) {
                                smix(synthL,synthR,
                                    2.f*dc3L[v].process(synthL*rmtempL),
                                    2.f*dc3R[v].process(synthR*rmtempR),
                                    param[kRingMod]*VMOD(kRingMod,v));
                            }
                        }
                        else {
                            //to match volume
                            synthL*=0.7f;
                            synthR*=0.7f;
                        }

                        //scale using velocity & envelope
                        float r=denormRand;
                        if (!onlyR) o1 += r + synthL * V->env  * ( ((float)V->velocity*midiScaler * param[kVelSens]) + (1.f-param[kVelSens]) );
                        if (enhanceStereo) r=denormRand;
                        if (!onlyL) o2 += r + synthR * V->env  * ( ((float)V->velocity*midiScaler * param[kVelSens]) + (1.f-param[kVelSens]) );
#else
                        o1+=synthL;
                        o2+=synthR;
#endif
                    }//if e<silence
                    V++;
                } //end voice loop
#ifdef MRALIASPRO
				//copy voice modulators for loudest voice to global modulators
				int v=0;
				float temp=SILENCE;
				for (int i=0;i<maxPoly;i++) {
					if (voice[i].env>temp) {
						temp=voice[i].env;
						v=i;
					}
				}
				for (int s=numModSources;s--;) {
					if (s==modLFO1) {
						if (param[kLFO1Free]<0.5f) modSource[s] = vmodSource[s][v];
					}
					else if (s==modLFO2) {
						if (param[kLFO2Free]<0.5f) modSource[s] = vmodSource[s][v];
					}
					else modSource[s] = vmodSource[s][v];
				}
#endif
                if (posttarget>0) { //global divide effect
                    //remove DC & amplify
                    const float dryL = o1;
                    const float dryR = o2;
                    o1 = globaldivL.process(dc2a.process(o1)*3.f,threshold*MOD(kThresh),roundFloatToInt((float)posttarget*MOD(kPostDivide)));
                    o1 = postdcL.process(o1);
                    o2 = globaldivR.process(dc2b.process(o2)*3.f,threshold*MOD(kThresh),roundFloatToInt((float)posttarget*MOD(kPostDivide)));
                    o2 = postdcR.process(o2);
                    if (usem1) {
                        globalM1.stprocess(o1,o2,roundFloatToInt((float)m1*MOD(kM1)),param[kM1Mix]*MOD(kM1Mix));
                    }
                    if (usesine) {
                        smix(o1,o2,
                            (postsineL.process(o1+sinefreq*MOD(kSineFreq),(float)ifs,roundFloatToInt((float)sineres*MOD(kSineRes))))*genv,
                            (postsineR.process(o2+sinefreq*MOD(kSineFreq),(float)ifs,roundFloatToInt((float)sineres*MOD(kSineRes))))*genv,
                            param[kSineMix]*MOD(kSineMix));
                    }
                    if (usefilter) {
                        const float grmtempL=o1+denorm;
                        const float grmtempR=o2+denorm;
                        if (filtermode==lpf24) {
                            if (filtercount==0) {
                                filter2.update(fzip*MOD(kCut),rzip*MOD(kRes)*0.5f,(float)ifs);
                            }
                            filter2.stprocess(o1,o2);
                        }
                        else if (filtermode==formant) {
                            o1 = postformantL.process(o1,rzip*MOD(kRes),fzip*(4.f/12500.f)*MOD(kCut));
                            o2 = postformantR.process(o2,rzip*MOD(kRes),fzip*(4.f/12500.f)*MOD(kCut));
                        }
                        else {
                            postsvf.stprocess(o1,o2,fzip*MOD(kCut),rzip*MOD(kRes),(float)ifs,filtermode);
                        }
                        //ringmod
                        if (useringmod) {
                            smix(o1,o2,
                                2.f*dc3L[0].process(o1*grmtempL),
                                2.f*dc3R[0].process(o2*grmtempR),
                                param[kRingMod]*MOD(kRingMod));
                        }
                    }
                    o1=mixEP(dryL,o1*genv,param[kPostDivMix]*MOD(kPostDivMix));
                    o2=mixEP(dryR,o2*genv,param[kPostDivMix]*MOD(kPostDivMix));
                    o1+=denormRand;
                    o2+=denormRand;
                }

                if (oscgain>0.f) {
                    o1 = dcL.process(o1*oscgain*MOD(kOscGain))+i2+denorm;
                    o2 = dcR.process(o2*oscgain*MOD(kOscGain))+i2+denorm;
                }
                else {
                    o1 = i1;
                    o2 = i2;
                }

                //post-panning
                xpanEI(o1,o2,0.5f-param[kStereo2]*MOD(kStereo2)*0.5f);

                if (useclipper) {
                    smix2(o1,o2,clip(o1,-0.5f,0.5f),clip(o2,-0.5f,0.5f),param[kClip]*MOD(kClip));
                }
                if (param[kOPLP]<1.f) {
                    o1 = oplpL.process(o1+denorm,param[kOPLP]*MOD(kOPLP));
                    o2 = oplpR.process(o2+denorm,param[kOPLP]*MOD(kOPLP));
                }
                //main volume
                vzip += 0.005f * (vol*MOD(kVolume)-vzip);
                o1 *= vzip;
                o2 *= vzip;

                if (uselimiter) limiter.stprocess(o1,o2);

                *bufferL++ = o1;
                if (getNumOutputChannels()>1) *bufferR++ = o2;

            }//while frames
            if(frame<sampleFrames) {
                long note = notes[event++];
                long vel  = notes[event++];
                noteOn(note, vel);
            }
        }//while frame<sampleframes
        //clip indicator
        if (buffer.getMagnitude(0,sampleFrames)>1.0) {
            logDebugString(String(_iter)+" clipped");
            clipcount=(int)(getSampleRate()*0.05f);
			if (!clipped)
			{
				clipped=true;
				sendChangeMessage();
			}
        }
        else {
            if (clipped) {
                clipcount-=sampleFrames;
                if (clipcount<=0) {
                    logDebugString(String(_iter)+" not clipped");
                    clipped=false;
					clipcount=0;
                    sendChangeMessage();
                }
            }
        }
        voices = maxPoly;
        for(int v=maxPoly; v--;) {
            if(voice[v].env<=SILENCE) {
                //choke voices
                voice[v].env = SILENCE;
                voice[v].envl = 0.0f;
                voice[v].fenv = SILENCE;
                voice[v].fenvl = 0.0f;
                voice[v].fenvd = rel;
#ifdef MRALIASPRO
                voice[v].env3 = SILENCE;
                voice[v].envl3 = 0.0f;
				vmodSource[modEnv3][v] = 1.f-param[kEnv3Amount];
#endif
				voice[v].notey = NO_NOTE;
                voices--;
            }
        }
    }//if voices
    else //empty block
    {
        fzip=ff;
        rzip=rr;
        bzip=bend;
        azip=aliasboost;
        srzip=param[kRate];
        vzip=vol*MOD(kVolume);
        filtercount+=buffer.getNumSamples();
#ifdef MRALIASPRO
		modSource[modEnv3] = 1.f-param[kEnv3Amount];
		modSource[modAudio] = 0.f;
#endif
        if (ledon || aledon || clipped) {
            logDebugString(String(_iter)+" empty block, turning off leds");
            ledon=false;
            aledon=false;
            clipped=false;
            sendChangeMessage();
        }
        while(--sampleFrames >= 0)
        {
            *bufferL++ = 0.0f;
            if (getNumOutputChannels()>1) *bufferR++ = 0.0f;
#ifdef MRALIASPRO
			modSource[modAudioEnv] = envelopeFollower.process(0.f);
			float scale = 1.f;
			int iphase = 0;
			int index = 0;
			int mask = 0;
			if (param[kLFO1Free]>=0.5f) {
				if (lfo1w>sine && lfo1w!=draw1 && lfo1w!=draw2) {
					scale = 16.f; //adjustment for larger wavetable size
					wsf = (float)TableSize;
					mask = TableSize-1;
				}
				else {
					wsf = (float)waveSize;
					mask = waveSize-1;
				}
				iphase = ((int) freelfo1);
				freelfo1 = fmod(freelfo1,wsf);
				index = iphase & mask;
				modSource[modLFO1]=jmax(0.f,1.f + /*0.5f * */param[kLFO1Amount]*MOD(kLFO1Amount) * (lfowave1[index] + lfodtable1[index]*(freelfo1 - (float) iphase)));
				freelfo1 += fScaler*lfo1freq*scale*MOD(kLFO1Rate);
			}
			if (param[kLFO2Free]>=0.5f) {
				if (lfo2w>sine && lfo2w!=draw1 && lfo2w!=draw2) {
					scale = 16.f; //adjustment for larger wavetable size
					wsf = (float)TableSize;
					mask = TableSize-1;
				}
				else {
					wsf = (float)waveSize;
					mask = waveSize-1;
				}
				iphase = ((int) freelfo2);
				freelfo2 = fmod(freelfo2,wsf);
				index = iphase & mask;
				modSource[modLFO2]=jmax(0.f,1.f + /*0.5f * */param[kLFO2Amount]*MOD(kLFO2Amount) * (lfowave2[index] + lfodtable2[index]*(freelfo2 - (float) iphase)));
				freelfo2 += fScaler*lfo2freq*scale*MOD(kLFO2Rate);
			}
#endif
        }
    }
#ifdef MRALIASPRO
	if (recording && buffer.getMagnitude(0,buffer.getNumSamples())>0.01f) {
		int target=waveSize;
		recBuffer->copyFrom(0,numSamplesRecorded,buffer,0,0,jmin(buffer.getNumSamples(),target-numSamplesRecorded));
		numSamplesRecorded+=jmin(buffer.getNumSamples(),target);
		if (numSamplesRecorded>=target) {
			numSamplesRecorded=0;
			recording=false;
			for (int i=0;i<target;i++) {
				table[recordingIndex][i]=recBuffer->getSampleData(0)[i];
			}
			updateDrawableWave(recordingIndex-draw1);
			recBuffer->clear();
			infoString="Waveform Recorded";
			sendChangeMessage();
		}
	}
#endif

    notes[0] = EVENTS_DONE;
	midiMessages.clear();

#ifdef MRALIASPRO
	//experimental
	for (int i=0;i<numParams-1;i++)
	{
		if (!isModulatable(i) && mod[i]!=&(modSource[modNone]))
		{
			getCallbackLock().enter();
			modulating=true;
			const float temp = jlimit(0.f,1.f,actualParameter[i]*MOD(i));
			if (param[i]!=temp)
				setParameter(i,temp);
			modulating=false;
			getCallbackLock().exit();
		}
	}
#endif

    processing=false;
}

//==============================================================================
void MrAlias2::noteOn (int note, int velocity) {
    int v=0, tmp=0, held=0;
    bool ignore = false;
    bool done=false;
    if (velocity>0) { //note on
        if(mono) //monophonic
        {
            if(voice[v].note > NO_NOTE) //legato pitch change
            {
                voice[v].oldnote = voice[v].note;
                //infoString="legato";
                //sendChangeMessage();
                if (polymode==monomicro) {
                    voice[v].velocity=velocity;
                    voice[v].envl=2.f;
                    voice[v].envd=att;
                    voice[v].coeff = acoeff;
                    voice[v].fenvl=2.f;
                    voice[v].fenvd=fatt;
                    voice[v].fcoeff = facoeff;
#ifdef MRALIASPRO
                    voice[v].envl3=2.f;
                    voice[v].envd3=att3;
                    voice[v].coeff3=acoeff3;
#endif
                }
                else for(tmp=(maxPoly-1); tmp>0; tmp--)  //queue any held notes
                {
                    voice[tmp].note = voice[tmp - 1].note;
                    voice[tmp].notey = voice[tmp].note;
                }
                voice[v].env += SILENCE + SILENCE; ///was missed out below if returned?
                voice[v].note = note;
                voice[v].notey = note;
                if (polymode!=monomicro && param[kRetrig]>=0.5f) {
                    voice[v].velocity=velocity;
                    voice[v].envl=2.f;
                    voice[v].envd=att;
                    voice[v].coeff = acoeff;
                    voice[v].fenvl=2.f;
                    voice[v].fenvd=fatt;
                    voice[v].fcoeff = facoeff;
#ifdef MRALIASPRO
                    voice[v].envl3=2.f;
                    voice[v].envd3=att3;
                    voice[v].coeff3=acoeff3;
#endif
				}
                return;
            }
        }
        else {
            float l=100.f;
            int tmp2=0;
            for(tmp=0; tmp<maxPoly; tmp++)  //replace quietest voice not in attack
            {
                if (!done) {
                    if(voice[tmp].notey==note) {
                        //reuse voice if it's the same note
                        ignore=true;
                        voice[tmp].note=note;
                        voice[tmp].velocity=velocity;
                        //voice[tmp].env+=SILENCE+SILENCE;
                        //voice[tmp].fenv=SILENCE;
                        voice[tmp].envl=2.f;
                        voice[tmp].envd=att;
                        voice[tmp].fenvl=2.f;
                        voice[tmp].coeff = acoeff;
                        voice[tmp].fenvd=fatt;
                        voice[tmp].fcoeff = facoeff;
#ifdef MRALIASPRO
						voice[tmp].envl3=2.f;
                        voice[tmp].envd3=att3;
                        voice[tmp].coeff3 = acoeff3;
#endif
                        //infoString = "retrigger voice " + String(tmp);
                        //sendChangeMessage();
                        done=true;
                    }
                    else {
                        if(voice[tmp].notey>NO_NOTE) {
                            held++;
                        }
                        else {
                            v=tmp;
                            //infoString = "use voice " + String(v);
                            //sendChangeMessage();
                            done=true;
                        }
                        if(voice[tmp].env<l && voice[tmp].envl<2.0f && !done) {
                            l=voice[tmp].env;
                            tmp2=tmp;
                        }
                    }
                }
            }
            if (held>=maxPoly && !done) {
                v=tmp2;
                //infoString = "steal voice " + String(v);
                //sendChangeMessage();
            }
        }
        if (!ignore) {
            voice[v].fPhase1=0.f;
            voice[v].fPhase2=0.f;
            voice[v].oldnote = NO_NOTE;//voice[v].note;
            voice[v].note=note;
            voice[v].notey=note;
            voice[v].velocity=velocity;
            voice[v].env+=SILENCE+SILENCE;
            voice[v].envl=2.f;
            voice[v].envd=att;
            voice[v].coeff = acoeff;
            voice[v].fenvl=2.f;
            voice[v].fenvd=fatt;
            voice[v].fcoeff = facoeff;
#ifdef MRALIASPRO
            voice[v].envl3=2.f;
            voice[v].envd3=att3;
            voice[v].coeff3 = acoeff3;       
			voice[v].lfo1 = 0.f;
			voice[v].lfo2 = 0.f;
#endif
			//if (mono) {
                //infoString="not legato v=" + String(v);
                //sendChangeMessage();
            //}
        }
    }
    else { //note off
        if (mono) {
            for(v=1; v<maxPoly; v++) 
			{
				if(voice[v].note==note) //any voices playing that note?
				{
					if(sustain==0)
					{
						voice[v].envl  = 0.0f;
						voice[v].envd  = rel;
						voice[v].coeff = rcoeff;
						voice[v].fenvl  = 0.0f;
						voice[v].fenvd  = frel;
						voice[v].fcoeff = frcoeff;
#ifdef MRALIASPRO
						voice[v].envl3  = 0.0f;
						voice[v].envd3  = rel3;
						voice[v].coeff3 = rcoeff3;
#endif
						voice[v].note  = NO_NOTE;
						voice[v].oldnote = NO_NOTE;
					}
					else voice[v].note = SUSTAIN;
				}
			}
			if (voice[0].note==note) { //monophonic (and current note)
				for(v=(maxPoly-1); v>0; v--)
				{
					if(voice[v].note>NO_NOTE) held = v; //any other notes queued?
				}
				if(held>0 && polymode!=monomicro)
				{
					voice[0].oldnote = voice[0].note;
					voice[0].note = voice[held].note;
					voice[0].notey = voice[held].note;
					voice[held].note = NO_NOTE;
					voice[held].oldnote = NO_NOTE;
					//infoString="held="+String(held);
					//sendChangeMessage();
					if (param[kRetrig]>=0.5f) {
						voice[0].velocity=velocity;
						voice[0].envl=2.f;
						voice[0].envd=att;
						voice[0].coeff = acoeff;
						voice[0].fenvl=2.f;
						voice[0].fenvd=fatt;
						voice[0].fcoeff = facoeff;
#ifdef MRALIASPRO
						voice[0].envl3=2.f;
						voice[0].envd3=att3;
						voice[0].coeff3 = acoeff3;
						logDebugString(String(_iter)+" "+"noteoff");
#endif
					}
				}
				else
				{
					voice[0].envl  = 0.0f;
					voice[0].envd  = rel;
					voice[0].coeff = rcoeff;
					voice[0].fenvl = 0.0f;
					voice[0].fenvd = frel;
					voice[0].fcoeff = frcoeff;
#ifdef MRALIASPRO
					voice[0].envl3  = 0.0f;
					voice[0].envd3  = rel3;
					voice[0].coeff3 = rcoeff3;
					logDebugString(String(_iter)+" "+"noteofffff");
#endif
					voice[0].note  = NO_NOTE;
					voice[0].oldnote = NO_NOTE;
					//infoString="none held";
					//sendChangeMessage();
				}
			}
			else if (polymode==monomicro) {
				//wrong noteoff, kill all notes
				for(v=0; v<maxPoly; v++) {
					voice[v].envl  = 0.0f;
					voice[v].envd  = rel;
					voice[v].coeff = rcoeff;
					voice[v].fenvl = 0.0f;
					voice[v].fenvd = frel;
					voice[v].fcoeff = frcoeff;
#ifdef MRALIASPRO
					voice[v].envl3  = 0.0f;
					voice[v].envd3  = rel3;
					voice[v].coeff3 = rcoeff3;
					logDebugString(String(_iter)+" "+"wrongnoteoff");
#endif
					voice[v].note  = NO_NOTE;
					voice[v].oldnote = NO_NOTE;
					voice[v].env   = SILENCE;
				}
			}
        }
        else //polyphonic
        {
            for(v=maxPoly; v--;) if(voice[v].note==note) //any voices playing that note?
            {
                if(sustain==0)
                {
                    voice[v].envl  = 0.0f;
                    voice[v].envd  = rel;
                    voice[v].coeff = rcoeff;
                    voice[v].fenvl  = 0.0f;
                    voice[v].fenvd  = frel;
                    voice[v].fcoeff = frcoeff;
#ifdef MRALIASPRO
                    voice[v].envl3  = 0.0f;
                    voice[v].envd3  = rel3;
                    voice[v].coeff3 = rcoeff3;
#endif
					voice[v].note  = NO_NOTE;
                    voice[v].oldnote = NO_NOTE;
                }
                else voice[v].note = SUSTAIN;
            }
        }
    }
}

//==============================================================================
AudioProcessorEditor* MrAlias2::createEditor() {
    logDebugString(String(_iter)+" createEditor()");
	return new MrAlias2Editor (this);
}

//patch/bank saving
//==============================================================================
void MrAlias2::getCurrentProgramStateInformation (MemoryBlock& destData) {
    logDebugString(String(_iter)+" getCurrentProgramStateInformation()");
    XmlElement xmlState = getProgramStateAsXml();
    copyXmlToBinary (xmlState, destData);
}

void MrAlias2::saveBank(File bankFile) {
	bool isInitBank = bankFile.getFileNameWithoutExtension().equalsIgnoreCase(T("Init"));
	bool isDefaultBank = (bankFile.getFileNameWithoutExtension().startsWith(T("Default")));
	getBankStateAsXml(isDefaultBank,isInitBank).writeToFile(bankFile," ");
}

void MrAlias2::savePatch(File patchFile, bool CCMapOnly) {
    getProgramStateAsXml(CCMapOnly).writeToFile(patchFile," ");
}

XmlElement MrAlias2::getProgramStateAsXml(bool CCMapOnly) {
    XmlElement xmlState ("MrAlias2Settings");
    xmlState.setAttribute (T("pluginversion"), 251);

    if (!CCMapOnly) {
		XmlElement* wavenames = new XmlElement ("WaveNames");
		for (int i=0;i<plusUserWaveforms-numWaveforms;i++) {
			wavenames->setAttribute (T("wave")+String(i),waveNames[i]);
		}
		xmlState.addChildElement(wavenames);

        XmlElement *prog = new XmlElement("MrAliasProgram");
        prog->setAttribute(T("name"), getProgramName(getCurrentProgram()));
        for (int i=0;i<getNumParameters()-1;i++) {
            prog->setAttribute (getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), actualParameter[i]);
        }
        xmlState.addChildElement(prog);
    }
    if (CCMapOnly || useccmap) {
        XmlElement *ccmapping = new XmlElement("CCMapping");
        for (int i=0;i<getNumParameters();i++) {
            ccmapping->setAttribute (T("ccforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), ccmap[i].cc);
            ccmapping->setAttribute (T("loforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), ccmap[i].lo);
            ccmapping->setAttribute (T("hiforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), ccmap[i].hi);
        }
        xmlState.addChildElement(ccmapping);
    }

    XmlElement *modmatrix = new XmlElement("ModMatrix");
    for (int i=0;i<getNumParameters()-1;i++) {
        for (int j=1;j<numModSources;j++) {
            if (matchModMatrix(j,i)) {
                modmatrix->setAttribute (T("mod") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), j);
            }
        }
    }
    xmlState.addChildElement(modmatrix);

	if (memcmp(table[draw1],blankProgram.wave[0],sizeof(float)*256))
	{
		XmlElement* drawablewave = new XmlElement ("Wave1");
		for (int i=0;i<waveSize;i++) {
			drawablewave->setAttribute ("w"+String(i), table[draw1][i]);
		}
		xmlState.addChildElement(drawablewave);
	}

	if (memcmp(table[draw2],blankProgram.wave[1],sizeof(float)*256))
	{
		XmlElement* drawablewave2 = new XmlElement ("Wave2");
		for (int i=0;i<waveSize;i++) {
			drawablewave2->setAttribute ("w"+String(i), table[draw2][i]);
		}
		xmlState.addChildElement(drawablewave2);
	}
	return xmlState;
}

XmlElement MrAlias2::getBankStateAsXml(bool saveSize, bool initBank) {
	memcpy(programs[curProgram].wave[0],table[draw1],sizeof(programs[curProgram].wave[0]));
	memcpy(programs[curProgram].wave[1],table[draw2],sizeof(programs[curProgram].wave[1]));
	memcpy(programs[curProgram].param,actualParameter,sizeof(float)*numParams);

    XmlElement xmlState ("MrAlias2Settings");
    xmlState.setAttribute (T("pluginversion"), 251);

    XmlElement *uisize = new XmlElement("Options");
	if (saveSize)
	{
		uisize->setAttribute(T("uiwidth"), lastUIWidth);
		uisize->setAttribute(T("uiheight"), lastUIHeight);
	}
	uisize->setAttribute(T("applytobank"), CCMappingToBankByDefault);
    #ifdef MRALIASPRO
    uisize->setAttribute(T("keyfocus"), keyFocus);
	uisize->setAttribute(T("page"), currentPage);
    #endif
    xmlState.addChildElement(uisize);

	XmlElement* wavenames = new XmlElement ("WaveNames");
    for (int i=0;i<plusUserWaveforms-numWaveforms;i++) {
		wavenames->setAttribute (T("wave")+String(i),waveNames[i]);
	}
	xmlState.addChildElement(wavenames);

    for (int p=0;p<getNumPrograms();p++) {
		XmlElement *prog = new XmlElement("MrAliasProgram");
        prog->setAttribute(T("index"), p);
		MrAliasProgram* program = &programs[p];
		if (initBank) program = &blankProgram;
        prog->setAttribute(T("name"), program->name);
        for (int i=0;i<getNumParameters();i++) {
            prog->setAttribute (getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), program->param[i]);
        }
        xmlState.addChildElement(prog);
        if (useccmap) {
			XmlElement *ccmapping = new XmlElement("CCMapping");
            ccmapping->setAttribute(T("index"), p);
            for (int i=0;i<getNumParameters();i++) {
                ccmapping->setAttribute (T("ccforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), program->ccmap[i].cc);
                ccmapping->setAttribute (T("loforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), program->ccmap[i].lo);
                ccmapping->setAttribute (T("hiforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), program->ccmap[i].hi);
            }
			xmlState.addChildElement(ccmapping);
        }
		XmlElement *modmatrix = new XmlElement("ModMatrix");
        modmatrix->setAttribute(T("index"), p);
        for (int i=0;i<getNumParameters()-1;i++) {
            for (int j=1;j<numModSources;j++) {
				if (!initBank)
				{
					if (matchProgramModMatrix(j,i,p)) {
						modmatrix->setAttribute (T("mod") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), j);
					}
				}
				else 
				{
					if ((program->mods[i].source==j)) {
						modmatrix->setAttribute (T("mod") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), j);
					}
				}
            }
        }
        xmlState.addChildElement(modmatrix);

		if (memcmp(programs[p].wave[0],blankProgram.wave[0],sizeof(float)*256))
		{
			XmlElement* drawablewave = new XmlElement ("Wave1");
			drawablewave->setAttribute(T("index"), p);
			for (int i=0;i<waveSize;i++) {
				drawablewave->setAttribute ("w"+String(i), programs[p].wave[0][i]);
			}
			xmlState.addChildElement(drawablewave);
		}

		if (memcmp(programs[p].wave[1],blankProgram.wave[1],sizeof(float)*256))
		{
			XmlElement* drawablewave2 = new XmlElement ("Wave2");
			drawablewave2->setAttribute(T("index"), p);
			for (int i=0;i<waveSize;i++) {
				drawablewave2->setAttribute ("w"+String(i), programs[p].wave[1][i]);
			}
			xmlState.addChildElement(drawablewave2);
		}
    }

    XmlElement *snapa = new XmlElement("SnapshotA");
    snapa->setAttribute (T("followa"),followPresetA);
    for (int i=0;i<getNumParameters()-1;i++) {
        snapa->setAttribute (getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), snapshotA.param[i]);
    }
    xmlState.addChildElement(snapa);

    XmlElement *snapb = new XmlElement("SnapshotB");
    snapb->setAttribute (T("followb"),followPresetB);
    for (int i=0;i<getNumParameters()-1;i++) {
        snapb->setAttribute (getParameterName(i).toLowerCase().retainCharacters(goodXmlChars), snapshotB.param[i]);
    }
    xmlState.addChildElement(snapb);

	XmlElement *curprog = new XmlElement("ActiveProgram");
    curprog->setAttribute(T("index"),getCurrentProgram());
    xmlState.addChildElement(curprog);
    return xmlState;
}

//patch/bank loading
//==============================================================================
void MrAlias2::getStateInformation(MemoryBlock &destData) {
    logDebugString(String(_iter)+" "+"getStateInformation()");
    XmlElement xmlState = getBankStateAsXml();
    copyXmlToBinary (xmlState, destData);
}

void MrAlias2::setCurrentProgramStateInformation (const void* data, int sizeInBytes) {
    logDebugString(String(_iter)+" "+"setCurrentProgramStateInformation()");
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
    wait=true;
    waitcount=0;
    setProgramStateFromXml(xmlState);
    this->dispatchPendingMessages();
}

void MrAlias2::loadPatch (File patchFile) {
    String xml = patchFile.loadFileAsString();
    XmlDocument xmldoc(xml);
    XmlElement* const xmlState = xmldoc.getDocumentElement();
    //wait=true;
    //waitcount=0;
    setProgramStateFromXml(xmlState);
    this->dispatchPendingMessages();
	init=true;
	sendChangeMessage();//////???????
}

void MrAlias2::setStateInformation (const void* data, int sizeInBytes) {
    logDebugString(String(_iter)+" "+"setStateInformation()");
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
    setBankStateFromXml(xmlState);
    setCurrentProgram(curProgram);
    wait=true;
    this->dispatchPendingMessages();
}

void MrAlias2::loadBank (File bankFile) {
    XmlElement* const xmlState = XmlDocument(bankFile.loadFileAsString()).getDocumentElement();
    setBankStateFromXml(xmlState);
    setCurrentProgram(0);
    wait=true;
    this->dispatchPendingMessages();
	infoString="Bank loaded";
}

void MrAlias2::setBlankPatch(File patchFile)
{
    String xml = patchFile.loadFileAsString();
    XmlDocument xmldoc(xml);
    XmlElement* const xmlState = xmldoc.getDocumentElement();
    wait=true;
    waitcount=0;
   if (xmlState != 0) 
   {
        if (xmlState->hasTagName (T("MrAlias2Settings"))) 
		{
			StringArray savedWaveNames;
            forEachXmlChildElement (*xmlState, e) 
			{
				if (e->hasTagName(T("WaveNames"))) {
					for (int i=0;i<plusUserWaveforms-numWaveforms;i++) {
						savedWaveNames.add(e->getStringAttribute(T("wave")+String(i)));
					}
				}
                else if (e->hasTagName(T("MrAliasProgram"))) {
					blankProgram.name=e->getStringAttribute(T("name"));
                    for (int i=0;i<getNumParameters();i++) {
                        blankProgram.param[i] = (float) e->getDoubleAttribute(getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),blankProgram.param[i]);
                    }
					int w = roundFloatToInt(blankProgram.param[kWaveform1]*plusUserWaveforms-1);
					if (w>=numWaveforms) {
						w = waveNames.indexOf(savedWaveNames[w-numWaveforms],true);
						if (w!=-1) blankProgram.param[kWaveform1] = (float)(w+numWaveforms)/((float)(plusUserWaveforms-1));
					}
                }
                else if (e->hasTagName(T("CCMapping"))) {
                    for (int i=0;i<getNumParameters();i++) {
						blankProgram.ccmap[i].cc = e->getIntAttribute(T("ccforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),-1);
						blankProgram.ccmap[i].lo = (float)e->getDoubleAttribute(T("loforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),0);
						blankProgram.ccmap[i].hi = (float)e->getDoubleAttribute(T("hiforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),127);
                    }
                }
                else if (e->hasTagName(T("ModMatrix"))) {
                    for (int i=0;i<getNumParameters()-1;i++) {
						blankProgram.mods[i].source=e->getIntAttribute(T("mod")+getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),modNone);
                    }
                }
				else if (e->hasTagName(T("Wave1"))) {
					for (int i=0;i<waveSize;i++) {
						blankProgram.wave[0][i] = (float)e->getDoubleAttribute(T("w")+String(i));
					}
				}
				else if (e->hasTagName(T("Wave2"))) {
					for (int i=0;i<waveSize;i++) {
						blankProgram.wave[1][i] = (float)e->getDoubleAttribute(T("w")+String(i));
					}
				}
            }
        }
        delete xmlState;
    }
}

void MrAlias2::setProgramStateFromXml(XmlElement* xmlState) {
   if (xmlState != 0) {
        if (xmlState->hasTagName (T("MrAlias2Settings"))) {
            int version = xmlState->getIntAttribute(T("pluginversion"));
			StringArray savedWaveNames;
            forEachXmlChildElement (*xmlState, e) {
				if (e->hasTagName(T("WaveNames"))) {
					for (int i=0;i<plusUserWaveforms-numWaveforms;i++) {
						savedWaveNames.add(e->getStringAttribute(T("wave")+String(i)));
					}
				}
                else if (e->hasTagName(T("MrAliasProgram"))) {
                    changeProgramName(getCurrentProgram(),e->getStringAttribute(T("name")));
                    infoString = e->getStringAttribute(T("name"));
                    for (int i=0;i<getNumParameters();i++) {
                        switch(i) {
                            //ignore these global parameters
                            case kInputGain:
                            case kWet:
                            case kUseProgCh:
                            case kChannel:
                                programs[curProgram].param[i] = param[i];
                                break;
							case kRandomize:
								programs[curProgram].param[i] = 0.f;

                            default:
                                programs[curProgram].param[i] = (float) e->getDoubleAttribute(getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),blankProgram.param[i]);
                                break;
                        }
                    }
					int w = roundFloatToInt(programs[curProgram].param[kWaveform1]*plusUserWaveforms-1);
					if (w>=numWaveforms) {
						w = waveNames.indexOf(savedWaveNames[w-numWaveforms],true);
						if (w!=-1) programs[curProgram].param[kWaveform1] = (float)(w+numWaveforms)/((float)(plusUserWaveforms-1));
					}
                    //convert old patches
                    if (version<2) {
                        programs[curProgram].param[kOctave2] = blankProgram.param[kOctave2];
                        programs[curProgram].param[kOctave] = (float) e->getDoubleAttribute(T("osc2octave"),blankProgram.param[kOctave]);
                    }
                    if (version<3) {
                        programs[curProgram].param[kFMode] = (float) e->getDoubleAttribute(T("filtermode"),blankProgram.param[kMode])*0.8f;
                    }
                    if (version<5) {
                        float old=programs[curProgram].param[kWaveform1];
                        if (old==0.0f) programs[curProgram].param[kWaveform1] = (float)rampup/(float)(plusUserWaveforms-1);
                        else if (old<0.75f) programs[curProgram].param[kWaveform1] = (float)pulse/(float)(plusUserWaveforms-1);
                        else if (old<1.0f) programs[curProgram].param[kWaveform1] = (float)triangle/(float)(plusUserWaveforms-1);
                        else if (old==1.0f) programs[curProgram].param[kWaveform1] = (float)sine/(float)(plusUserWaveforms-1);
                        old=programs[curProgram].param[kWaveform2];
                        if (old==0.0f) programs[curProgram].param[kWaveform2] = (float)rampup/(float)(plusUserWaveforms-1);
                        else if (old<0.75f) programs[curProgram].param[kWaveform2] = (float)pulse/(float)(plusUserWaveforms-1);
                        else if (old<1.0f) programs[curProgram].param[kWaveform2] = (float)triangle/(float)(plusUserWaveforms-1);
                        else if (old==1.0f) programs[curProgram].param[kWaveform2] = (float)sine/(float)(plusUserWaveforms-1);
                    }
					if (version>=5 && version<240) {
						int oldwave = roundFloatToInt(programs[curProgram].param[kWaveform1]*17.f);
						programs[curProgram].param[kWaveform1] = (float)oldwave/(float)(plusUserWaveforms-1);
						oldwave = roundFloatToInt(programs[curProgram].param[kWaveform2]*17.f);
						programs[curProgram].param[kWaveform2] = (float)oldwave/(float)(plusUserWaveforms-1);
						if (version==230) {
							oldwave = roundFloatToInt(programs[curProgram].param[kLFO1Waveform]*17.f);
							programs[curProgram].param[kLFO1Waveform] = (float)oldwave/(float)(plusUserWaveforms-1);
							oldwave = roundFloatToInt(programs[curProgram].param[kLFO2Waveform]*17.f);
							programs[curProgram].param[kLFO2Waveform] = (float)oldwave/(float)(plusUserWaveforms-1);
						}
					}
                    if (version<6) {
                        programs[curProgram].param[kAlias] *= 101.f/102.f;
                    }
                    if (version<7) {
                        if (e->getDoubleAttribute(T("noteoffmode"))>=0.5f) programs[curProgram].param[kMode]=1.f;
                        else if (e->getDoubleAttribute(T("mode"))>=0.5f) programs[curProgram].param[kMode]=0.7f;
                    }
					if (version<230) {
						programs[curProgram].param[kLFO1Amount]*=0.5f;
						programs[curProgram].param[kLFO2Amount]*=0.5f;
					}
					if (version==241) {
						if (!(programs[curProgram].param[kLFO1Free]<0.5f)) programs[curProgram].param[kLFO1Amount]*=0.5f;
						programs[curProgram].param[kLFO2Amount]*=0.5f;
					}
					if (version<251) {
						if (w==draw1 || w==draw2) 
						{
						 //   float p = (float)pow(2.0,18.0*(double)programs[curProgram].param[kOctave1]-8.0);
							//programs[curProgram].param[kOctave1] = (log(p)/log(2.f) + 12.f)/18.f;
							programs[curProgram].param[kOctave1] += 0.2222222222222f;
						}
						w = roundFloatToInt(programs[curProgram].param[kWaveform2]*(float)(plusUserWaveforms-1));
						if (w==draw1 || w==draw2)
						{
						 //   float p = (float)pow(2.0,18.0*(double)programs[curProgram].param[kOctave2]-8.0);
							//programs[curProgram].param[kOctave2] = (log(p)/log(2.f) + 12.f)/18.f;
							programs[curProgram].param[kOctave2] += 0.2222222222222f;
						}
					}
					memcpy(actualParameter,programs[curProgram].param,sizeof(param));
                    setCurrentProgram(curProgram);
                }
                else if (e->hasTagName(T("CCMapping"))) {
                    for (int i=0;i<getNumParameters();i++) {
                        setCCMapping(i, e->getIntAttribute(T("ccforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),ccmap[i].cc));
                        setCCLo(i, (float)e->getDoubleAttribute(T("loforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),ccmap[i].lo));
                        setCCHi(i, (float)e->getDoubleAttribute(T("hiforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),ccmap[i].hi));
                    }
                }
                else if (e->hasTagName(T("ModMatrix"))) {
                    for (int i=0;i<getNumParameters()-1;i++) {
                        setModMatrix(e->getIntAttribute(T("mod")+getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),modNone),i);
                    }
                }
				else if (e->hasTagName(T("Wave1"))) {
					for (int i=0;i<waveSize;i++) {
						table[draw1][i] = programs[curProgram].wave[0][i] = (float)e->getDoubleAttribute(T("w")+String(i));
					}
					updateDrawableWave(0);
				}
				else if (e->hasTagName(T("Wave2"))) {
					for (int i=0;i<waveSize;i++) {
						table[draw2][i] = programs[curProgram].wave[1][i] = (float)e->getDoubleAttribute(T("w")+String(i));
					}
					updateDrawableWave(1);
				}
            }
        }
        deleteAndZero(xmlState);
    }
}

void MrAlias2::initializeBank() {
	File initPatch = File(currentPath + File::separatorString + "sounds" + File::separatorString + T("Init.MrAliasPatch"));
	if (initPatch.exists()) setBlankPatch(initPatch);

	for (int p=0;p<getNumPrograms();p++) {
		memcpy(&programs[p].ccmap,&blankProgram.ccmap,sizeof(blankProgram.ccmap));
		memcpy(&programs[p].param,&blankProgram.param,sizeof(blankProgram.param));
		memcpy(&programs[p].mods,&blankProgram.mods,sizeof(blankProgram.mods));
		memcpy(&programs[p].wave,&blankProgram.wave,sizeof(blankProgram.wave));
		programs[p].name = blankProgram.name;
    }
    init=true;
    wait=true;
    waitcount=0;
    newbank=true;
    setCurrentProgram(0);
    wait=true;
    this->dispatchPendingMessages();
	infoString="Bank initialized";
}

void MrAlias2::setBankStateFromXml(XmlElement* xmlState) {
    if (xmlState != 0) {
        if (xmlState->hasTagName (T("MrAlias2Settings"))) {
			for (int i=0;i<getNumPrograms();i++)
			{
				memcpy(programs[i].mods,blankProgram.mods,sizeof(blankProgram.mods));
				memcpy(programs[i].wave,blankProgram.wave,sizeof(waves));
			}
			StringArray savedWaveNames;
            int version = xmlState->getIntAttribute(T("pluginversion"));
            forEachXmlChildElement (*xmlState, e) {
                if (e->hasTagName(T("Size")) || e->hasTagName(T("Options"))) {
                    lastUIWidth = e->getIntAttribute (T("uiwidth"), lastUIWidth);
                    lastUIHeight = e->getIntAttribute (T("uiheight"), lastUIHeight);
					CCMappingToBankByDefault = e->getBoolAttribute(T("applytobank"), CCMappingToBankByDefault);
                    #ifdef MRALIASPRO
                    keyFocus = e->getBoolAttribute (T("keyfocus"), false);
					currentPage = e->getIntAttribute (T("page"), currentPage);
                    #endif
                }
				else if (e->hasTagName(T("WaveNames"))) {
					for (int i=0;i<plusUserWaveforms-numWaveforms;i++) {
						savedWaveNames.add(e->getStringAttribute(T("wave")+String(i)));
					}
				}
                else if (e->hasTagName(T("MrAliasProgram"))) {
                    int p = e->getIntAttribute(T("index"),curProgram);
                    if (p<getNumPrograms()) {
                        for (int i=0;i<getNumParameters();i++) {
                            programs[p].param[i] = (float) e->getDoubleAttribute(getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),blankProgram.param[i]);
                        }
                        if (version<2) {
                            programs[p].param[kOctave2] = blankProgram.param[kOctave2];
                            programs[p].param[kOctave] = (float) e->getDoubleAttribute(T("osc2octave"),blankProgram.param[kOctave]);
                        }
                        if (version<3) {
                            programs[p].param[kFMode] = (float) e->getDoubleAttribute(T("filtermode"),blankProgram.param[kMode])*0.8f;
                        }
                        if (version<5) {
                            float old=programs[p].param[kWaveform1];
                            if (old==0.0f) programs[p].param[kWaveform1] = (float)rampup/(float)(plusUserWaveforms-1);
                            else if (old<0.75f) programs[p].param[kWaveform1] = (float)pulse/(float)(plusUserWaveforms-1);
                            else if (old<1.0f) programs[p].param[kWaveform1] = (float)triangle/(float)(plusUserWaveforms-1);
                            else if (old==1.0f) programs[p].param[kWaveform1] = (float)sine/(float)(plusUserWaveforms-1);
                            old=programs[p].param[kWaveform2];
                            if (old==0.0f) programs[p].param[kWaveform2] = (float)rampup/(float)(plusUserWaveforms-1);
                            else if (old<0.75f) programs[p].param[kWaveform2] = (float)pulse/(float)(plusUserWaveforms-1);
                            else if (old<1.0f) programs[p].param[kWaveform2] = (float)triangle/(float)(plusUserWaveforms-1);
                            else if (old==1.0f) programs[p].param[kWaveform2] = (float)sine/(float)(plusUserWaveforms-1);
                        }
						if (version>=5 && version<240) {
							int oldwave = roundFloatToInt(programs[p].param[kWaveform1]*17.f);
							programs[p].param[kWaveform1] = (float)oldwave/(float)(plusUserWaveforms-1);
							oldwave = roundFloatToInt(programs[p].param[kWaveform2]*17.f);
							programs[p].param[kWaveform2] = (float)oldwave/(float)(plusUserWaveforms-1);
							if (version==230) {
								oldwave = roundFloatToInt(programs[p].param[kLFO1Waveform]*17.f);
								programs[p].param[kLFO1Waveform] = (float)oldwave/(float)(plusUserWaveforms-1);
								oldwave = roundFloatToInt(programs[p].param[kLFO2Waveform]*17.f);
								programs[p].param[kLFO2Waveform] = (float)oldwave/(float)(plusUserWaveforms-1);
							}
						}
                        if (version<6) {
                            programs[p].param[kAlias] *= 101.f/102.f;
                        }
                        if (version<7) {
                            if (e->getDoubleAttribute(T("noteoffmode"))>=0.5) programs[p].param[kMode]=1.f;
                            else if (e->getDoubleAttribute(T("mode"))>=0.5) programs[p].param[kMode]=0.7f;
                        }
						if (version<230) {
							programs[p].param[kLFO1Amount]*=0.5f;
							programs[p].param[kLFO2Amount]*=0.5f;
						}
						if (version==241) {
							if (!(programs[p].param[kLFO1Free]<0.5f)) programs[p].param[kLFO1Amount]*=0.5f;
							programs[p].param[kLFO2Amount]*=0.5f;
						}
						if (version<251) {
							int w = roundFloatToInt(programs[p].param[kWaveform1]*(float)(plusUserWaveforms-1));
							if (w==draw1 || w==draw2) programs[p].param[kOctave1] += 0.2222222222222f;
							w = roundFloatToInt(programs[p].param[kWaveform2]*(float)(plusUserWaveforms-1));
							if (w==draw1 || w==draw2) programs[p].param[kOctave2] += 0.2222222222222f;
						}
                        programs[p].name = e->getStringAttribute(T("name"), "Program "+String(p));

						int w = roundFloatToInt(programs[p].param[kWaveform1]*plusUserWaveforms-1);
						if (w>=numWaveforms) {
							w = waveNames.indexOf(savedWaveNames[w-numWaveforms],true);
							if (w!=-1) programs[p].param[kWaveform1] = (float)(w+numWaveforms)/((float)(plusUserWaveforms-1));
						}
                    }
                }
                else if (e->hasTagName(T("CCMapping"))) {
                    int p = e->getIntAttribute(T("index"),curProgram);
                    for (int i=0;i<getNumParameters();i++) {
                        programs[p].ccmap[i].cc = e->getIntAttribute(T("ccforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),programs[p].ccmap[i].cc);
                        programs[p].ccmap[i].lo = (float)e->getDoubleAttribute(T("loforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),programs[p].ccmap[i].lo);
                        programs[p].ccmap[i].hi = (float)e->getDoubleAttribute(T("hiforparam") + getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),programs[p].ccmap[i].hi);
                    }
                }
                else if (e->hasTagName(T("SnapshotA"))) {
                    followPresetA = e->getBoolAttribute(T("followa"), followPresetA);
                    for (int i=0;i<getNumParameters()-1;i++) {
                        snapshotA.param[i] = (float) e->getDoubleAttribute(getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),blankProgram.param[i]);
                    }
                }
                else if (e->hasTagName(T("SnapshotB"))) {
                    followPresetB = e->getBoolAttribute(T("followb"), followPresetB);
                    for (int i=0;i<getNumParameters()-1;i++) {
                        snapshotB.param[i] = (float) e->getDoubleAttribute(getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),blankProgram.param[i]);
                    }
                }
                else if (e->hasTagName(T("ModMatrix"))) {
                    int p = e->getIntAttribute(T("index"),curProgram);
                    for (int i=0;i<getNumParameters()-1;i++) {
                        //programs[p].mods[i].destination=i;
                        programs[p].mods[i].source=e->getIntAttribute(T("mod")+getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),modNone);
                        //setModMatrix(e->getIntAttribute(T("mod")+getParameterName(i).toLowerCase().retainCharacters(goodXmlChars),modNone),i);
                    }
                }
				else if (e->hasTagName(T("Wave1"))) {
                    int p = e->getIntAttribute(T("index"),curProgram);
					for (int i=0;i<waveSize;i++) {
						programs[p].wave[0][i] = (float)e->getDoubleAttribute(T("w")+String(i));
					}
				}
				else if (e->hasTagName(T("Wave2"))) {
                    int p = e->getIntAttribute(T("index"),curProgram);
					for (int i=0;i<waveSize;i++) {
						programs[p].wave[1][i] = (float)e->getDoubleAttribute(T("w")+String(i));
					}
				}
            }
            init=true;
            wait=true;
            waitcount=0;
            newbank=true;
        }
        deleteAndZero(xmlState);
    }
}

//patch/bank manipulation
//==============================================================================
void MrAlias2::progReset() {
	File initPatch = File(currentPath + File::separatorString + "sounds" + File::separatorString + T("Init.MrAliasPatch"));
	if (initPatch.exists())
		loadPatch(initPatch);
	else 
	{
		for (int i=0;i<numParams;i++) {
			programs[curProgram].param[i] = actualParameter[i] = blankProgram.param[i];
			if (i<kMorph) programs[curProgram].mods[i].source=modNone;
		}
		changeProgramName(curProgram,"Default");
		clearModMatrix();
		wait=true;
		waitcount=0;
		setCurrentProgram(curProgram);
		infoString = "Reset";
	}
}

#ifdef MRALIASPRO
void MrAlias2::randomizeMods(bool extra)
{
	for (int i=0;i<numParams-2;i++)
	{
		if (isModulatable(i) || extra) 
		{
			bool doIt = JUCE_NAMESPACE::Random::getSystemRandom().nextFloat() > 0.7f;
			if (doIt)
			{
				int n = JUCE_NAMESPACE::Random::getSystemRandom().nextInt() % numModSources;
				if (n>0 && n!=modAudio && n!=modAudioEnv)
					setModMatrix(matchModMatrix(n,i)?modNone:n,i);
			}
		}
	}
}
#endif

void MrAlias2::randomize(float strength, bool oneParameter) {
	if (oneParameter) {
		logDebugString(String(_iter)+" randomize one parameter");
		int p = JUCE_NAMESPACE::Random::getSystemRandom().nextInt(getNumParameters());
		//don't change these parameters
		if (p==kRandomSpeed) p = kCut;
		else if (p==kRandomStrength) p = kRes;
		else if (p==kRandomize) p = kRate;
		else if (p==kAuto) p = kClip;
		else if (p==kChannel) p = kM1;
		else if (p==kUseProgCh) p = kCut;
		else if (p==kMorph) p = kRes;
		else if (p==kMode) p = kCut;
		float f = JUCE_NAMESPACE::Random::getSystemRandom().nextFloat();
		float a = jlimit(0.f,1.f,getParameter(p)+(JUCE_NAMESPACE::Random::getSystemRandom().nextBool()?(-1.f * strength * f):(strength * f)));

		//and don't let these parameters be too low
		if (p==kOPLP && a<0.1f) a+=0.1f;
		else if (p==kCut && a<0.1f) a+=0.1f;

		//and disable inaudible effects
		else if (p==kM1Mix && a<0.1f) a=0.f;
		else if (p==kBRMix && a<0.1f) a=0.f;
		else if (p==kSineMix && a<0.1f) a=0.f;
		else if (p==kClip && a<0.1f) a=0.f;
		else if (p==kOscMix && a<0.1f) a=0.f;

		setParameterNotifyingHost(p,a);
	}
	else {
		//randomize all parameters
		for (int i=0;i<numParams-2;i++) {
			programs[curProgram].param[i] = jlimit(0.0f,1.0f,param[i]+(JUCE_NAMESPACE::Random::getSystemRandom().nextFloat()-0.5f)*strength);
		}
		//but keep these parameters the same
		programs[curProgram].param[kInputGain] = param[kInputGain];
		programs[curProgram].param[kWet] = param[kWet];
		programs[curProgram].param[kOscGain] = param[kOscGain];
		programs[curProgram].param[kVolume] = param[kVolume];
		programs[curProgram].param[kChannel] = param[kChannel];
		programs[curProgram].param[kUseProgCh] = param[kUseProgCh];
		//secret parameters
		programs[curProgram].param[kPitchShift] = param[kPitchShift];
		programs[curProgram].param[kDecoupled1] = param[kDecoupled1];
		programs[curProgram].param[kDecoupled2] = param[kDecoupled2];
		programs[curProgram].param[kGlide] = param[kGlide];
		programs[curProgram].param[kRetrig] = param[kRetrig];
		programs[curProgram].param[kRandomSpeed] = param[kRandomSpeed];
		programs[curProgram].param[kRandomStrength] = param[kRandomStrength];
		programs[curProgram].param[kAuto] = param[kAuto];

		//and don't let these parameters be too low
		if (programs[curProgram].param[kOPLP]<0.1f) programs[curProgram].param[kOPLP]+=0.1f;
		if (programs[curProgram].param[kCut]<0.1f) programs[curProgram].param[kCut]+=0.1f;

		//and disable inaudible effects
		if (programs[curProgram].param[kM1Mix]<0.1f) programs[curProgram].param[kM1]=0.f;
		if (programs[curProgram].param[kRate]>0.9f
		 || programs[curProgram].param[kBRMix]<0.1f) programs[curProgram].param[kBRMix]=0.f;
		if (programs[curProgram].param[kDivMix]<0.1f) programs[curProgram].param[kDivide]=0.f;
		if (programs[curProgram].param[kPostDivMix]<0.1f) programs[curProgram].param[kPostDivide]=0.f;
		if (programs[curProgram].param[kSineMix]<0.1f) programs[curProgram].param[kSineMix]=0.f;
		if (programs[curProgram].param[kClip]<0.1f) programs[curProgram].param[kClip]=0.f;
		if (programs[curProgram].param[kOscMix]<0.1f) programs[curProgram].param[kOscMix]=0.f;

		wait=true;
		memcpy(actualParameter,programs[curProgram].param,sizeof(param));
		setCurrentProgram(curProgram);
		infoString = "Randomized";
	}
}

void MrAlias2::next() {
    wait=true;
    if (curProgram==getNumPrograms()-1) setCurrentProgram(0);
    else setCurrentProgram(curProgram+1);
}

void MrAlias2::prev() {
    wait=true;
    if (curProgram==0) setCurrentProgram(getNumPrograms()-1);
    else setCurrentProgram(curProgram-1);
}

//snapshots
//==============================================================================
void MrAlias2::saveSnapshot(bool B) {
    if(B) for (int i=0;i<numParams-1;i++) snapshotB.param[i] = param[i];
    else for (int i=0;i<numParams-1;i++) snapshotA.param[i] = param[i];
}

void MrAlias2::recallSnapshot(bool B) {
    if(B) {
        for (int i=0;i<numParams-1;i++) setParameter(i,snapshotB.param[i]);
        setParameter(kMorph,1.f);
    }
    else {
        for (int i=0;i<numParams-1;i++) setParameter(i,snapshotA.param[i]);
        setParameter(kMorph,0.f);
    }
}

void MrAlias2::applyValueToSnapshots(int index,float value,bool A,bool B) {
    if (A) snapshotA.param[index] = value;
    if (B) snapshotB.param[index] = value;
}

void MrAlias2::setSnapshotFollowsPreset(bool enabled, int snapshot) {
    switch (snapshot) {
        case 0: followPresetA = enabled; break;
        case 1: followPresetB = enabled; break;
        default: break;
    }
}

bool MrAlias2::getSnapshotFollowsPreset(int snapshot) {
    switch (snapshot) {
        case 0: return followPresetA;
        case 1: return followPresetB;
        default: return false;
    }
}

void MrAlias2::morph(float amount) {
    //logDebugString(String(_iter)+" morph(" + String(amount) + ")");
    getCallbackLock().enter();
    settingProgram=true;
    for (int i=0;i<numParams-1;i++) {
        if (snapshotA.param[i]!=snapshotB.param[i]) 
		{
            setParameter(i,mixEI(snapshotA.param[i],snapshotB.param[i],amount));
			actualParameter[i]=param[i];
		}
    }
    settingProgram=false;
    getCallbackLock().exit();
    if (processing) wait=true;
    else
        sendChangeMessage();
}

//cc mapping
//==============================================================================
bool MrAlias2::isCCRangeReversed(int index){
     if (ccmap[index].lo > ccmap[index].hi) return true;
     return false;
}

void MrAlias2::applyCCToBank(int index) {
    for (int p=0;p<numPrograms;p++) {
        programs[p].ccmap[index].cc = ccmap[index].cc;
        programs[p].ccmap[index].lo = ccmap[index].lo;
        programs[p].ccmap[index].hi = ccmap[index].hi;
    }
}

void MrAlias2::clearCCFromBank(int index) {
    for (int p=0;p<numPrograms;p++) {
        programs[p].ccmap[index].cc = -1;
        programs[p].ccmap[index].lo = 0.f;
        programs[p].ccmap[index].hi = 1.f;
    }
}

void MrAlias2::applyAllCCsToBank() {
    for (int p=0;p<numPrograms;p++) {
        for (int i=0;i<numParams;i++) {
            programs[p].ccmap[i].cc = ccmap[i].cc;
            programs[p].ccmap[i].lo = ccmap[i].lo;
            programs[p].ccmap[i].hi = ccmap[i].hi;
        }
    }
}

int MrAlias2::getCCMapping (int index) {
    if (index<getNumParameters()) return ccmap[index].cc;
    return -1;
}

bool MrAlias2::isCCMappingEnabled () {
    return useccmap;
}

void MrAlias2::setCCMapping (int index, int cc) {
    //logDebugString(String(_iter)+" setCCMapping " + String(index));
    if (index<getNumParameters()) {
        if (cc==midiLearn) {
            ccmap[index].cc = midiLearn;
            midilearnlisten = true;
        }
        else {
            MrAliasProgram* ap = &programs[curProgram];
            ccmap[index].cc = ap->ccmap[index].cc = cc;
            sendChangeMessage();
            if (cc>-1) useccmap = true;
			if (CCMappingToBankByDefault) applyCCToBank(index);
        }
    }
}

void MrAlias2::setCCLo(int index, float lo) {
    MrAliasProgram* ap = &programs[curProgram];
     ccmap[index].lo = ap->ccmap[index].lo = lo;
}

void MrAlias2::setCCHi(int index, float hi) {
    MrAliasProgram* ap = &programs[curProgram];
     ccmap[index].hi = ap->ccmap[index].hi = hi;
}

void MrAlias2::flipCCRange(int index) {
     swapVariables(ccmap[index].lo,ccmap[index].hi);
     programs[curProgram].ccmap[index].lo = ccmap[index].lo;
     programs[curProgram].ccmap[index].hi = ccmap[index].hi;
}

void MrAlias2::enableCCMapping(bool enabled, bool clear) {
     logDebugString(String(_iter)+" enableCCMapping");
     if (enabled) useccmap=true;
     else {
         if (clear) {
            for (int i=0;i<numParams;i++) {
                setCCMapping(i,-1);
                setCCLo(i,0.f);
                setCCHi(i,1.f);
            }
            sendChangeMessage();
         }
         else useccmap=false;
     }
}
void MrAlias2::setModMatrix(int source, int destination, float amount) {
    if (destination<numParams-1 && source<numModSources) {
        mod[destination] = &(modSource[source]);
		for (int v=0;v<maxPoly;v++) 
			vmod[destination][v] = &(vmodSource[source][v]);
		programs[curProgram].mods[destination].source=source;

        //modAmount[source][destination] = amount;
    }
}

bool MrAlias2::matchModMatrix(int source, int destination) {
    if (destination<numParams-1 && source<numModSources) {
        return (mod[destination]==&(modSource[source]));
    }
    else return false;
}

bool MrAlias2::matchProgramModMatrix(int source, int destination, int program) {
    if (destination<numParams-1 && source<numModSources) {
        return (programs[program].mods[destination].source==source);
    }
    else return false;
}

void MrAlias2::clearModMatrix() {
    for (int i=0;i<numParams-1;i++) {
        mod[i]=&(modSource[modNone]);
        for (int v=maxPoly;v--;) vmod[i][v]=&(vmodSource[modNone][v]);
        //for (int j=0;j<numModSources;j++) modAmount[j][i]=0.f;
    }
}

void MrAlias2::clearModMatrix(int index) {
    for (int i=0;i<numParams-1;i++) {
		programs[index].mods[i].source=modNone;
    }
}

#ifdef MRALIASPRO
void MrAlias2::timerCallback() {
	if (getParameter(kAuto)>=0.5f && getParameter(kRandomStrength)>0.0001f)
		randomize(getParameter(kRandomStrength)*MOD(kRandomStrength),true);
}

float MrAlias2::getMod(int n) {
	int v=0;
	float temp=SILENCE;
	if (n==modLFO1) {
		if (param[kLFO1Free]<0.5f) {
			for (int i=0;i<maxPoly;i++) {
				if (voice[i].env>temp) {
					temp=voice[i].env;
					v=i;
				}
			}
			return vmodSource[modLFO1][v];
		}
		return modSource[modLFO1];
	}
	if (n==modLFO2) {
		if (param[kLFO2Free]<0.5f) {
			for (int i=0;i<maxPoly;i++) {
				if (voice[i].env>temp) {
					temp=voice[i].env;
					v=i;
				}
			}
			return vmodSource[modLFO2][v];
		}
		return modSource[modLFO2];
	}
	if (n==modEnv3) {
		return 2*modSource[modEnv3];
	}
	if (n<numModSources) {
		return modSource[n];
	}
	return 0.f;
}

bool MrAlias2::isModulatable(int i) {
	switch(i) 
	{
	//these won't show up in the mod destination menu
	case kPitchShift:
	case kWaveform1:
	case kWaveform2:
	case kAInertia:
	case kMode:
	case kPBRange:
	case kDivEnv:
	case kFilterPower:
	case kFMode:
	case kFKeyFollow:
	case kVelSens:
	case kFiltEnv:
	case kFVSens:
	case kLimiter:
	case kUseProgCh:
	case kChannel:
	case kExp:
	case kFExp:
	case kAtt:
	case kRel:
	case kDec:
	case kSus:
	case kFAtt:
	case kFRel:
	case kFDec:
	case kFSus:
	case kDecoupled1:
	case kDecoupled2:
	case kRetrig:
	case kGlide:
	case kEnhanceStereo:
	case kAtt3:
	case kRel3:
	case kDec3:
	case kSus3:
	case kEnv3Amount:
	case kExp3:
	case kAuto:
	case kAudioEnvAmount:
	case kRandomSpeed:
	case kRandomize:
	case kLFO1Waveform:
	case kLFO2Waveform:
	case kLFO1Free:
	case kLFO2Free:
		return false;
	default:
		return true;
	}
}


void MrAlias2::startRecording(int index) {
	recording=true;
	recordingIndex=index;
	numSamplesRecorded=0;
}

bool MrAlias2::readKeyFile(File file)
{
	bool copy = false;
	if (file.exists())
	{
		copy=true;
	}
	else {
		String path = currentPath+File::separatorString+T("MrAliasKey");
		if (!File(path).exists()) {
			path = currentPath+File::separatorString+T("MrAliasKey.txt");
			if (!File(path).exists()) {
				path = ((File::getSpecialLocation(File::currentApplicationFile)).getParentDirectory()).getFullPathName()+File::separatorString+T("MrAliasKey");
				if (!File(path).exists()) {
					path = ((File::getSpecialLocation(File::currentApplicationFile)).getParentDirectory()).getFullPathName()+File::separatorString+T("MrAliasKey.txt");
				}
			}
		}
		file = File(path);
	}

	if (file.exists()) {
		XmlElement* xmlKey = decodeEncryptedXml(file.loadFileAsString(),T("5,8bf1f433a0100a66080d064e36c0cb37de577a16ad0ef45de0480eb80ed0832cae9a10d7910bfc80c5e2e82e8c0b84850c912cd363b6c8aaf8a69ada39df5019"));
		if ( !xmlKey->getStringAttribute(T("product")).compare(T("Mr. Alias Pro 2.x"))
			&& xmlKey->getStringAttribute(T("username")).isNotEmpty()
			&& xmlKey->getStringAttribute(T("time")).isNotEmpty() )
		{
			demo=false;
			infoString = "Registered to " + xmlKey->getStringAttribute(T("username"));
			if (copy) file.copyFileTo(File(currentPath+File::separatorString+T("MrAliasKey.txt")));
			sendChangeMessage();
		}
		else
		{
			infoString = "Bad MrAliasKey";
			sendChangeMessage();
		}
		if (xmlKey) deleteAndZero(xmlKey);
		return true;
	}
	return false;
}

void MrAlias2::readSettings()
{
	File settingsFile=File(currentPath+File::separator+T("settings.ini"));
	if (settingsFile.existsAsFile()) {
		StringArray lines;
		lines.addLines(settingsFile.loadFileAsString());
		for (int i=0;i<lines.size();i++) {
            if (!lines[i].startsWithChar(';')) {
				if (lines[i].startsWith(T("skin="))) {
					skin = lines[i].fromFirstOccurrenceOf(T("="),false,true);
					if (!File(currentPath+File::separatorString+skin).isDirectory()) 
						skin = String("skins") + File::separatorString + String("Default");
				}
				else if (lines[i].startsWith(T("lastPatchPath="))) {
					patchPath = lines[i].fromFirstOccurrenceOf(T("="),false,true);
					if (!File(patchPath).isDirectory()) 
						patchPath = currentPath + File::separatorString + "sounds";

				}
				else if (lines[i].startsWith(T("lastWavePath="))) {
					wavePath = lines[i].fromFirstOccurrenceOf(T("="),false,true);
					if (!File(wavePath).isDirectory()) 
						wavePath = currentPath + File::separatorString + "sounds";

				}
			}
		}
	}
}

void MrAlias2::writeSettings()
{
	String settings = String("; Mr. Alias Pro settings\n")
		+ String("skin=") + skin + String("\n")
		//+ String("height=") + String(this->lastUIHeight) + String("\n")
		+ String("lastPatchPath=") + patchPath + String("\n")
		+ String("lastWavePath=") + wavePath;
	File settingsFile = File(currentPath+File::separatorString+"settings.ini");
	settingsFile.replaceWithText(settings);
}

String MrAlias2::getModSourceName(int index)
{
	switch (index)
	{
	case modNone : return "None";
	case modVelocity: return "Velocity";
	case modAftertouch: return "Poly Aftertouch";
	case modChPressure: return "Channel Pressure";
	case modNote: return "Note Number";
	case modAmpEnv: return "Amp Env";
	case modFiltEnv: return "Filter Env";
	case modEnv3: return "Extra Env";
	case modOsc1: return "Osc 1";
	case modOsc2: return "Osc 2";
	case modLFO1: return "LFO 1";
	case modLFO2: return "LFO 2";
	case modAudio: return "Audio Input";
	case modAudioEnv: return "Audio Env Follower";
	case modModWheel: return "Mod Wheel";
	case modPitchBend: return "Pitch Wheel";
	default: return " ";
	}
}

void MrAlias2::updateLFOFreq(int index, float v, bool sync)
{
	if (param[kLFO1Sync+index]<0.5f && !sync) 
	{
		if		(index==0) lfo1freq = paramToLfoFreq(v); 
		else if (index==1) lfo2freq = paramToLfoFreq(v); 
	}
	else
	{
		const float inc = 0.04545454545f; // 1/22
		if      (v<1*inc)  beats[index]=ppqPerBar*32; //32 bars
		else if (v<2*inc)  beats[index]=ppqPerBar*24; //24 bars
		else if (v<3*inc)  beats[index]=ppqPerBar*16; //16 bars
		else if (v<4*inc)  beats[index]=ppqPerBar*12; //12 bars
		else if (v<5*inc)  beats[index]=ppqPerBar*8; //8 bars
		else if (v<6*inc)  beats[index]=ppqPerBar*6; //6 bars
		else if (v<7*inc)  beats[index]=ppqPerBar*4; //4 bars
		else if (v<8*inc)  beats[index]=ppqPerBar*3; //3 bars
		else if (v<9*inc)  beats[index]=ppqPerBar*2; //2 bars
		else if (v<10*inc) beats[index]=ppqPerBar*1.5f; //1.5 bars
		else if (v<11*inc) beats[index]=ppqPerBar; //1 bar
		else if (v<12*inc) beats[index]=3; //3 beats
		else if (v<13*inc) beats[index]=2; //2 beats
		else if (v<14*inc) beats[index]=1.5f;
		else if (v<15*inc) beats[index]=1;
		else if (v<16*inc) beats[index]=0.75f;
		else if (v<17*inc) beats[index]=0.6666666666666666666666667f;
		else if (v<18*inc) beats[index]=0.5f;
		else if (v<19*inc) beats[index]=0.3333333333333333333333333f;
		else if (v<20*inc) beats[index]=0.25f;
		else if (v<21*inc) beats[index]=0.1666666666666666666666667f;
		else               beats[index]=0.125f;

		if		(index==0) lfo1freq = beatsToHz(beats[index]);
		else if (index==1) lfo2freq = beatsToHz(beats[index]);
	}
}

String MrAlias2::getTempoSyncText(float v)
{
	const float inc = 0.04545454545f; // 1/22
	if      (v<1*inc)  return "32 Bars";
	else if (v<2*inc)  return "24 Bars";
	else if (v<3*inc)  return "16 Bars";
	else if (v<4*inc)  return "12 Bars";
	else if (v<5*inc)  return "8 Bars";
	else if (v<6*inc)  return "6 Bars";
	else if (v<7*inc)  return "4 Bars";
	else if (v<8*inc)  return "3 Bars";
	else if (v<9*inc)  return "2 Bars";
	else if (v<10*inc) return "1.5 Bars";
	else if (v<11*inc) return "1 Bar";
	else if (v<12*inc) return "Dotted Half";
	else if (v<13*inc) return "Half";
	else if (v<14*inc) return "Dotted Quarter";
	else if (v<15*inc) return "Quarter";
	else if (v<16*inc) return "Dotted 8th";
	else if (v<17*inc) return "4th Triplet";
	else if (v<18*inc) return "8th";
	else if (v<19*inc) return "8th Triplet";
	else if (v<20*inc) return "16th";
	else if (v<21*inc) return "16th Triplet";
	else               return "32nd";
}

#endif
void MrAlias2::readWavFile(File &wavFile, int size, int index) {
	if (wavFile.existsAsFile()) 
	{
		AudioFormatReader* audioReader = 0;
		WavAudioFormat wavFormat;
		audioReader = wavFormat.createReaderFor (wavFile.createInputStream(),true);
		const int numSourceSamples = (int)audioReader->lengthInSamples;
#if (JUCE_VERSION < ((1<<16) | (50<<8)) )
		float* buffer = new float[numSourceSamples];
		audioReader->read((int**)(&buffer),0,numSourceSamples);
#else
		AudioSampleBuffer buffer(1,numSourceSamples);
		audioReader->read((int**)buffer.getArrayOfChannels(),1,0,numSourceSamples,false);
#endif

		for (int s=0;s<size;s++) {
			if (audioReader) {
#if (JUCE_VERSION < ((1<<16) | (50<<8)) )
				table[index][s] = //buffer[s];
					jlimit(-1.f,1.f,buffer[(int)((float)(s*(numSourceSamples-1))/(float)(size-1))]);
#else
				table[index][s] = //buffer.getSampleData(0)[s];
					jlimit(-1.f,1.f,buffer.getSampleData(0)[(int)((float)(s*(numSourceSamples-1))/(float)(size-1))]);
#endif
			}
			else table[index][s]=0;
		}
		if(index==draw1 || index==draw2) updateDrawableWave(index-draw1);
		else if (index>=numWaveforms) waveNames.add(wavFile.getFileNameWithoutExtension());
		delete audioReader;
#if (JUCE_VERSION < ((1<<16) | (50<<8)) )
		delete buffer;
#endif
	}
}

void MrAlias2::saveWavFile(File &wavFile, int size, int index) {
	AudioFormatWriter* audioWriter = 0;
	AudioSampleBuffer buffer(1,size);
	buffer.copyFrom(0,0,table[index],size);
	WavAudioFormat wavFormat;
	if (wavFile.exists()) wavFile.deleteFile();
	audioWriter = wavFormat.createWriterFor(wavFile.createOutputStream(),44100,1,32,0,0);
	buffer.writeToAudioWriter(audioWriter,0,size);
	delete audioWriter;
}

String MrAlias2::getWaveformName(int index)
{
	switch(index)
	{
	case rampup: return "RampUp";
	case rampdn: return "RampDown";
	case pulse: return "Square";
	case triangle: return "Triangle";
	case sine: return "Sine";
	case minko: return "Minkowski";
	case weier: return "Weierstrass";
	case comb: return "AutoAlias";
	case harm: return "Eight";
	case odd: return "OddEight";
	case computer: return "Computer";
	case wave11: return "Funnel";
	case wave12: return "Grate";
	case noise: return "Noise";
	case wave14: return "Sine+";
	case wave15: return "Narrow";
	case octaves: return "Octaves";
	case wave17: return "Ughhh";
	case draw1: return "Drawable1";
	case draw2: return "Drawable2";
	default: 
		if (index-numWaveforms<waveNames.size()) 
		{
			if (waveNames[index-numWaveforms].isEmpty()) return "wave"+String(index);
			return waveNames[index-numWaveforms];
		}
		return String::empty;
	}
}