# -----------------------------------------
# Compile all the Ports

all: libs lv2 vst

plugins: lv2 vst

# -----------------------------------------
# libs

libs:
	$(MAKE) -C ../libs/drowaudio
	$(MAKE) -C ../libs/juce-2.0
	$(MAKE) -C ../libs/juced
	$(MAKE) -C ../libs/lv2-ttl-generator

# -----------------------------------------
# lv2

lv2: libs
	install -d ../bin/lv2
	$(MAKE) -C arctican-function/LV2
	$(MAKE) -C arctican-pilgrim/LV2
	$(MAKE) -C cabbage/LV2-fx
	$(MAKE) -C cabbage/LV2-ins
	$(MAKE) -C cabbage/LV2-midi
	$(MAKE) -C drowaudio-distortion/LV2
	$(MAKE) -C drowaudio-distortionshaper/LV2
	$(MAKE) -C drowaudio-flanger/LV2
	$(MAKE) -C drowaudio-reverb/LV2
	$(MAKE) -C drowaudio-tremolo/LV2
	$(MAKE) -C drumsynth/LV2
	$(MAKE) -C eqinox/LV2
	$(MAKE) -C juce-demo-plugin/LV2
	$(MAKE) -C klangfalter/LV2
	$(MAKE) -C midiChords/LV2
	$(MAKE) -C midiLooper/LV2
	$(MAKE) -C pitchedDelay/LV2
	$(MAKE) -C tal-dub-3/LV2
	$(MAKE) -C tal-filter/LV2
	$(MAKE) -C tal-filter-2/LV2
	$(MAKE) -C tal-noisemaker/LV2
	$(MAKE) -C tal-reverb/LV2
	$(MAKE) -C tal-reverb-2/LV2
	$(MAKE) -C tal-reverb-3/LV2
	$(MAKE) -C tal-vocoder-2/LV2
	$(MAKE) -C vex/LV2
	$(MAKE) -C wolpertinger/LV2

# -----------------------------------------
# vst

vst: libs
	install -d ../bin/vst
	$(MAKE) -C arctican-function/VST
	$(MAKE) -C arctican-pilgrim/VST
	$(MAKE) -C cabbage/VST-fx
	$(MAKE) -C cabbage/VST-ins
	$(MAKE) -C cabbage/VST-midi
	$(MAKE) -C drowaudio-distortion/VST
	$(MAKE) -C drowaudio-distortionshaper/VST
	$(MAKE) -C drowaudio-flanger/VST
	$(MAKE) -C drowaudio-reverb/VST
	$(MAKE) -C drowaudio-tremolo/VST
	$(MAKE) -C drumsynth/VST
	$(MAKE) -C eqinox/VST
	$(MAKE) -C juce-demo-plugin/VST
	$(MAKE) -C klangfalter/VST
	$(MAKE) -C midiChords/VST
	$(MAKE) -C midiLooper/VST
	$(MAKE) -C pitchedDelay/VST
	$(MAKE) -C tal-dub-3/VST
	$(MAKE) -C tal-filter/VST
	$(MAKE) -C tal-filter-2/VST
	$(MAKE) -C tal-noisemaker/VST
	$(MAKE) -C tal-reverb/VST
	$(MAKE) -C tal-reverb-2/VST
	$(MAKE) -C tal-reverb-3/VST
	$(MAKE) -C tal-vocoder-2/VST
	$(MAKE) -C vex/VST
	$(MAKE) -C wolpertinger/VST

# -----------------------------------------
# clean

clean:
	# LV2
	$(MAKE) clean -C arctican-function/LV2
	$(MAKE) clean -C arctican-pilgrim/LV2
	$(MAKE) clean -C cabbage/LV2-fx
	$(MAKE) clean -C cabbage/LV2-ins
	$(MAKE) clean -C cabbage/LV2-midi
	$(MAKE) clean -C drowaudio-distortion/LV2
	$(MAKE) clean -C drowaudio-distortionshaper/LV2
	$(MAKE) clean -C drowaudio-flanger/LV2
	$(MAKE) clean -C drowaudio-reverb/LV2
	$(MAKE) clean -C drowaudio-tremolo/LV2
	$(MAKE) clean -C drumsynth/LV2
	$(MAKE) clean -C eqinox/LV2
	$(MAKE) clean -C juce-demo-plugin/LV2
	$(MAKE) clean -C klangfalter/LV2
	$(MAKE) clean -C midiChords/LV2
	$(MAKE) clean -C midiLooper/LV2
	$(MAKE) clean -C pitchedDelay/LV2
	$(MAKE) clean -C tal-dub-3/LV2
	$(MAKE) clean -C tal-filter/LV2
	$(MAKE) clean -C tal-filter-2/LV2
	$(MAKE) clean -C tal-noisemaker/LV2
	$(MAKE) clean -C tal-reverb/LV2
	$(MAKE) clean -C tal-reverb-2/LV2
	$(MAKE) clean -C tal-reverb-3/LV2
	$(MAKE) clean -C tal-vocoder-2/LV2
	$(MAKE) clean -C vex/LV2
	$(MAKE) clean -C wolpertinger/LV2

	# VST
	$(MAKE) clean -C arctican-function/VST
	$(MAKE) clean -C arctican-pilgrim/VST
	$(MAKE) clean -C cabbage/VST-fx
	$(MAKE) clean -C cabbage/VST-ins
	$(MAKE) clean -C cabbage/VST-midi
	$(MAKE) clean -C drowaudio-distortion/VST
	$(MAKE) clean -C drowaudio-distortionshaper/VST
	$(MAKE) clean -C drowaudio-flanger/VST
	$(MAKE) clean -C drowaudio-reverb/VST
	$(MAKE) clean -C drowaudio-tremolo/VST
	$(MAKE) clean -C drumsynth/VST
	$(MAKE) clean -C eqinox/VST
	$(MAKE) clean -C juce-demo-plugin/VST
	$(MAKE) clean -C klangfalter/VST
	$(MAKE) clean -C midiChords/VST
	$(MAKE) clean -C midiLooper/VST
	$(MAKE) clean -C pitchedDelay/VST
	$(MAKE) clean -C tal-dub-3/VST
	$(MAKE) clean -C tal-filter/VST
	$(MAKE) clean -C tal-filter-2/VST
	$(MAKE) clean -C tal-noisemaker/VST
	$(MAKE) clean -C tal-reverb/VST
	$(MAKE) clean -C tal-reverb-2/VST
	$(MAKE) clean -C tal-reverb-3/VST
	$(MAKE) clean -C tal-vocoder-2/VST
	$(MAKE) clean -C vex/VST
	$(MAKE) clean -C wolpertinger/VST

	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate

distclean: clean
	rm -rf */LV2/*.lv2
	rm -f */*/Makefile
	rm -f */*/*.make
