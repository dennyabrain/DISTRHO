#ifndef MrAlias2PLUGINFILTER_H
#define MrAlias2PLUGINFILTER_H


#include "common/log.h"
#include "juce.h"
#include "stuff.h"
#include "effects.h"
#include "JucePluginCharacteristics.h"


//==============================================================================
enum parameters {
	// Global
	numPrograms = 128,
	maxPoly = 6,                // max polyphony
	numLFOs = 2,
	waveSize = 256,		        // samples (must be power of 2 here)
	TableSize = 4096,		    // samples (must be power of 2 here)
	midiLearn = -99,
	pbBufferSize = 1024,

	// Parameters Tags
	kWaveform1 = 0,
	kWaveform2,
	kFreq1,
	kStereo,
	kOscMix,
	kOctave,
	kOctave1,
	kOctave2,
	kPhMod,
	kAlias,
	kAInertia,

	kMode,
	kPBRange,

	kDivide,
	kDivMix,
	kThresh,
	kPostDivide,
	kPostDivMix,
	kDivEnv,

	kRate,
	kBRMix,

	kM1,
	kM1Mix,

	kSineRes,
	kSineFreq,
	kSineMix,

	kFilterPower,
	kFMode,
	kCut,
	kRes,
	kFKeyFollow,
	kRingMod,

	kAtt,
	kDec,
	kSus,
	kRel,
	kVelSens,

	kFAtt,
	kFDec,
	kFSus,
	kFRel,
	kFiltEnv,
	kFVSens,

	kInputGain,
	kWet,
	kOscGain,

	kOPLP,
	kClip,
	kStereo2,
	kVolume,
	kLimiter,

	kUseProgCh,
	kChannel,

	kExp,
	kFExp,

	kPitchShift,
	kDecoupled1,
	kDecoupled2,
	kGlide,
	kRetrig,
	kEnhanceStereo,

	kAtt3,
	kDec3,
	kSus3,
	kRel3,
	kEnv3Amount,
	kExp3,
	kLFO1Rate,
	kLFO1Amount,
	kLFO1Waveform,
	kLFO1Free,
	kLFO2Rate,
	kLFO2Amount,
	kLFO2Waveform,
	kLFO2Free,
	kAudioEnvAmount,
	kLFO1Sync,
	kLFO2Sync,
	kOsc1ModAmount,
	kOsc2ModAmount,

	kInterpolate1,
	kInterpolate2,
	//kInterpolateLFO1,
	//kInterpolateLFO2,

	kRandomSpeed,
	kRandomStrength,
	kAuto,

	//this should always be the last parameter
	//kRecallA,
	//kRecallB,
	kRandomize,
	kMorph,
	numParams
};

enum modsources {modNone,
modVelocity, modAftertouch, modChPressure, modNote,
modAmpEnv, modFiltEnv, modEnv3,
modOsc1, modOsc2, modLFO1, modLFO2,
modAudio, modAudioEnv,
modModWheel, modPitchBend,
numModSources, numVoiceModSources = numModSources};
enum polymodes {polyphonic, monophonic, monomicro};
enum filtermodes {svlow, svband, svnotch, svhigh, lpf24, formant, numFilterModes};
enum waveforms {rampup, rampdn, pulse, triangle, sine, minko, weier, comb, harm, odd, computer,
wave11, wave12, noise, wave14, wave15, octaves, wave17, draw1, draw2, numWaveforms, plusUserWaveforms=24};

//==============================================================================
class CCMap {
public:
	CCMap() {cc=-1; lo=0.f; hi=1.f;}
	~CCMap(){};
	int cc;
	float lo;
	float hi;
};

class Mod {
public:
	Mod() {source=modNone; destination=0; amount=1.f;}
	~Mod() {};
	int source;
	int destination;
	float amount;
};

class MrAliasProgram {
	friend class MrAlias2;
public:
	MrAliasProgram ();
	~MrAliasProgram () {}
private:
	float param[numParams];
	String name;
	CCMap ccmap[numParams];
	Mod mods[numParams];
	float wave[2][waveSize];
};

//==============================================================================
class MrAlias2  : public AudioProcessor,
#ifdef MRALIASPRO
	public Timer,
#endif
	public ChangeBroadcaster
{
public:
	//==============================================================================
	MrAlias2();
	~MrAlias2();
	
	bool hasEditor() const { return true; }

	//==============================================================================
	void prepareToPlay (double sampleRate, int samplesPerBlock);
	void releaseResources();

	void processBlock (AudioSampleBuffer& buffer,
		MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();

	//==============================================================================
	const String getName() const {return JucePlugin_Name;}

	int getNumParameters() { return numParams; }
	float getParameter (int index);
	void setParameter (int index, float newValue);
//#if MAKE_LOG
	void setParameterNotifyingHost (int index, float newValue);
//#endif
	const String getParameterName (int index);
	const String getParameterText (int index);
	bool isMetaParameter (int parameterIndex);

	const String getInputChannelName (const int channelIndex) const;
	const String getOutputChannelName (const int channelIndex) const;
	bool isInputChannelStereoPair (int index) const;
	bool isOutputChannelStereoPair (int index) const;

	bool acceptsMidi() const {return JucePlugin_WantsMidiInput?true:false;}
	bool producesMidi() const {return JucePlugin_ProducesMidiOutput?true:false;}

	//==============================================================================
	int getNumPrograms()      { return numPrograms; }
	int getCurrentProgram();
	void setCurrentProgram (int index);
	const String getProgramName (int index);
	void changeProgramName (int index, const String& newName);

	//==============================================================================
	void getCurrentProgramStateInformation (MemoryBlock& destData);
	void setCurrentProgramStateInformation (const void* data, int sizeInBytes);
	void getStateInformation (MemoryBlock& destData);
	void setStateInformation (const void* data, int sizeInBytes);

	//==============================================================================
	AudioPlayHead::CurrentPositionInfo lastPosInfo;

	int lastUIHeight, lastUIWidth;

	//==============================================================================
	juce_UseDebuggingNewOperator

	bool ledon;
	bool aledon;
	bool clipped;
	String infoString;
	bool settingProgram;
	void progReset();
	void randomize(float strength=0.01f,bool oneParameter=false);
	void next();
	void prev();
	void saveBank(File bankFile);
	void savePatch(File patchFile, bool CCMapOnly=false);
	void loadBank(File bankFile);
	void loadPatch(File patchFile);
	void initializeBank();
	void setBlankPatch(File patchFile);

	int filtermode;
	bool newbank;

	String currentPath;
	String patchPath;
	String wavePath;
	void setCCMapping(int index, int cc);
	int getCCMapping(int index);
	void setCCLo(int index, float lo);
	void setCCHi(int index, float hi);
	void flipCCRange(int index);
	bool isCCRangeReversed(int index);
	void enableCCMapping(bool enabled, bool clear=false);
	bool isCCMappingEnabled();
	void applyCCToBank(int index);
	void clearCCFromBank(int index);
	void applyAllCCsToBank();
	bool CCMappingToBankByDefault;

	void saveSnapshot(bool B=false);
	void recallSnapshot(bool B=false);
	void applyValueToSnapshots(int index,float value,bool A,bool B);
	void setSnapshotFollowsPreset(bool enabled, int snapshot);
	bool getSnapshotFollowsPreset(int snapshot);

	void setModMatrix(int source, int destination, float amount=1.f);
	bool matchModMatrix(int source, int destination);
	bool matchProgramModMatrix(int source, int destination, int program);
	void clearModMatrix();
	void clearModMatrix(int index);

	ChangeBroadcaster* leds;

#ifdef MRALIASPRO
	MidiKeyboardState keyboardState;
	bool keyFocus;
	int currentPage;
	bool demo;
	void timerCallback ();
	float getMod(int modSource);
	bool isModulatable(int);
	void randomizeMods(bool);
	bool readKeyFile(File file=File::nonexistent);
	void readSettings();
	void writeSettings();
	String skin;
	String getModSourceName(int index);
#endif

	bool wait;
	bool editorIsShowing;
	StringArray waveNames;
	float* getDrawableWave(int index) {return table[draw1+index];}
	void updateDrawableWave(int index);
	void updateBigWave(int index);
	void resetDrawableWave(int waveform, int index);
	void invertWave(int index);
	void reverseWave(int index);
	void normalizeWave(int index);
	void readWavFile(File &wavFile, int size,int index);
	void saveWavFile(File &wavFile, int size, int index);
	String getWaveformName(int index);
	void startRecording(int index);
	bool isRecording(int index) {return (index==recordingIndex && recording);}

private:
	float param[numParams];

	void setProgramStateFromXml(XmlElement* xmlState);
	void setBankStateFromXml(XmlElement* xmlState);
	XmlElement getProgramStateAsXml(bool CCMapOnly=false);
	XmlElement getBankStateAsXml(bool saveSize=true, bool initBank=false);

	MrAliasProgram* programs;
	MrAliasProgram blankProgram;
	MrAliasProgram snapshotA;
	MrAliasProgram snapshotB;
	int curProgram;
	bool init;

	int clipcount;

	void initProcess ();
	void createWaves ();
	void noteOn (int32 note, int32 velocity);

#define SILENCE    0.001f  //voice choking
#define SUSTAIN -2
#define NO_NOTE -1
#define EVENTBUFFER 120
#define EVENTS_DONE 99999999

	struct Voice {
		int32 note;
		int32 notey;
		int32 velocity;
		float env;
		float envd;
		float envl;
		float coeff;
		float fenv;
		float fenvd;
		float fenvl;
		float fcoeff;
#ifdef MRALIASPRO
		//assignable envelope
		float env3;
		float envd3;
		float envl3;
		float coeff3;
		//lfos
		float lfo1;
		float lfo2;
#endif
		float fPhase1;
		float fPhase2;
		float pressure;
		int oldnote;
		float oldBaseFreq1;
		float oldBaseFreq2;
		Voice() {init();}
		void init() {note=notey=oldnote=NO_NOTE; env=fenv=SILENCE;
		envd=envl=fenvd=fenvl=coeff=fcoeff=fPhase1=fPhase2=0.f;
#ifdef MRALIASPRO
		env3=envl3=envd3=coeff3=0.f;
		lfo1=lfo2=0.f;
#endif
		pressure=0.f;
		oldBaseFreq1=oldBaseFreq2=0.f;
		velocity=0; }
	};
	Voice voice[maxPoly];
	char voices;

	long notes[EVENTBUFFER + 8];  //list of delta|note|velocity for current block
	float SR; //sample rate
	double ifs; //for envelope calculations

	int sustain;

	//pitch bend stuff
	float bend;
	int pbrange;

	//filters
	TLP24DB sfilter[maxPoly];
	TLP24DB filter2;
	TLP24DB infilter;
	OnePoleLPF oplpL;
	OnePoleLPF oplpR;
	SVF svf[maxPoly];
	SVF postsvf;
	SVF insvf;
	formant_filter formantL[maxPoly];
	formant_filter formantR[maxPoly];
	formant_filter informantL;
	formant_filter informantR;
	formant_filter postformantL;
	formant_filter postformantR;
	int filtercount;
	int fcounttarget;

	mdaLimiter limiter;

	//for parameter smoothing
	float fzip;
	float rzip;
	float bzip;
	float azip;
	float srzip;
	float vzip;

	//dc removers
	RemoveDC dcsynL[maxPoly], dcsynR[maxPoly], dcL, dcR, dc2a, dc2b, dc3L[maxPoly], dc3R[maxPoly], postdcL, postdcR, inpostdcL, inpostdcR, postdc2L, postdc2R;

	//dividers
	divider divL[maxPoly];
	divider divR[maxPoly];
	divider indivL;
	divider indivR;
	divider globaldivL;
	divider globaldivR;

	//m effects
	M_Effect M1[maxPoly];
	M_Effect inM1;
	M_Effect globalM1;
	//    int globalm1counterL;
	//    int globalm1counterR;
	//    int inm1counterL;
	//    int inm1counterR;

	//decimators
	decimate decimatorL[maxPoly];
	decimate decimatorR[maxPoly];
	decimate sinedecimatorL[maxPoly];
	decimate sinedecimatorR[maxPoly];
	decimate indecimator;

	//sine effect
	Sine sineeffectL[maxPoly];
	Sine sineeffectR[maxPoly];
	Sine insineL, insineR;
	Sine postsineL, postsineR;

	//waveforms
	float table[plusUserWaveforms][TableSize];
	float dtable[plusUserWaveforms][TableSize];

	//osc frequency determination
	double freqtab[numFrequencies];
	float fScaler;
	float freq1[maxPoly];
	float freq2[maxPoly];
#ifdef MRALIASPRO
	float lfo1freq;
	float lfo2freq;
	float freelfo1;
	float freelfo2;
#endif

	int waitcount, waitcount2;
	float wsf;

	//global envelope
	float genv;
	float genvd;
	float genvl;
	float gfenv;
	float gfenvd;
	float gfenvl;
	float gvelocity;
	float gksf;

	//calculated values
	//midi stuff
	bool useprogch;
	int listenchannel;
	bool mono;
	int polymode;
	//divider stuff
	int target;
	int posttarget;
	float threshold;
	float divenv;
	//m effect parameter
	int m1;
	//sine effect stuff
	float sinefreq;
	int sineres;
	//oscillator stuff
	float* wave1;
	float* wave2;
	int w1;
	int w2;
	float* dtable1;
	float* dtable2;
#ifdef MRALIASPRO
	float* lfowave1;
	float* lfowave2;
	int lfo1w;
	int lfo2w;
	float* lfodtable1;
	float* lfodtable2;
	inline float beatsToHz(float b) {return bpm / (60.f * b);}
	void updateLFOFreq(int index, float v, bool sync=false);
	float bpm;
	float ppqPerBar;
	String getTempoSyncText(float v);
	float beats[numLFOs];
#endif
	float aliasboost;
	float ainertia;
	float octave, octave1, octave2;
	float detune;
	float phmodfactor;
	//filter stuff
	float ff;
	float rr;
	float filtenv;
	bool usefilter;
	//envelope stuff
	float att, dec, sus, rel;
	float dcoeff,acoeff,rcoeff;
	float fatt, fdec, fsus, frel;
	float fdcoeff,facoeff,frcoeff;
#ifdef MRALIASPRO
	float att3, dec3, sus3, rel3;
	float dcoeff3,acoeff3,rcoeff3;
	EnvelopeFollower envelopeFollower;
#endif
	//effect disablers
	bool useringmod;
	bool usedecimator;
	bool useclipper;
	bool usesine;
	//bool usestereo;
	//bool useosc2;
	bool usem1;
	//volume
	bool useinput;
	float ingain;
	float oscgain;
	float wet;
	float vol;

	bool uselimiter;
	float glide;

	//cc mapping stuff
	bool midilearnlisten;
	CCMap ccmap[numParams];
	bool useccmap;

	//snapshot stuff
	void morph(float amount);
	bool followPresetA;
	bool followPresetB;

	//mod matrix
	float* mod[numParams];
	float* vmod[numParams][maxPoly];
	float modSource[numModSources];
	float vmodSource[numVoiceModSources][maxPoly];
	float actualParameter[numParams];
	bool modulating;

	bool processing;
	bool paramchanged;
	float zero;

	AudioSampleBuffer* recBuffer;
	int numSamplesRecorded;
	bool recording;
	int recordingIndex;
	//    AudioSampleBuffer* pbBuffer;
	//    AudioSampleBuffer* pbRemainder;
	//    int pbSample;
	//    bool pbBufferIsFull;

#if MAKE_LOG
	int _iter;
#endif
};


#endif
