# Compile all the Ports

all: build


build: libs standalone lv2 vst

plugins: standalone lv2 vst


libs:
	$(MAKE) -C ../libs/drowaudio
	$(MAKE) -C ../libs/juce-2.0
	$(MAKE) -C ../libs/juced
	$(MAKE) -C ../libs/lv2-ttl-generator

standalone:
	$(MAKE) -C arctican-function/Standalone
	$(MAKE) -C arctican-pilgrim/Standalone
	$(MAKE) -C drowaudio-distortion/Standalone
	$(MAKE) -C drowaudio-distortionshaper/Standalone
	$(MAKE) -C drowaudio-flanger/Standalone
	$(MAKE) -C drowaudio-reverb/Standalone
	$(MAKE) -C drowaudio-tremolo/Standalone
# 	$(MAKE) -C drumsynth/Standalone
# 	$(MAKE) -C eqinox/Standalone
# 	$(MAKE) -C highlife/Standalone
# 	$(MAKE) -C juce-demo-plugin/Standalone
	$(MAKE) -C tal-dub-3/Standalone
	$(MAKE) -C tal-filter/Standalone
	$(MAKE) -C tal-filter-2/Standalone
	$(MAKE) -C tal-noisemaker/Standalone
	$(MAKE) -C tal-reverb/Standalone
	$(MAKE) -C tal-reverb-2/Standalone
	$(MAKE) -C tal-reverb-3/Standalone
	$(MAKE) -C tal-vocoder-2/Standalone
# 	$(MAKE) -C vex/Standalone
# 	$(MAKE) -C wolpertinger/Standalone

lv2:
# 	$(MAKE) -C arctican-function/LV2
# 	$(MAKE) -C arctican-pilgrim/LV2
# 	$(MAKE) -C drowaudio-distortion/LV2
# 	$(MAKE) -C drowaudio-distortionshaper/LV2
# 	$(MAKE) -C drowaudio-flanger/LV2
# 	$(MAKE) -C drowaudio-reverb/LV2
# 	$(MAKE) -C drowaudio-tremolo/LV2
# 	$(MAKE) -C drumsynth/LV2
# 	$(MAKE) -C eqinox/LV2
# 	$(MAKE) -C highlife/LV2
# 	$(MAKE) -C juce-demo-plugin/LV2
# 	$(MAKE) -C tal-dub-3/LV2
# 	$(MAKE) -C tal-filter/LV2
# 	$(MAKE) -C tal-filter-2/LV2
# 	$(MAKE) -C tal-noisemaker/LV2
# 	$(MAKE) -C tal-reverb/LV2
# 	$(MAKE) -C tal-reverb-2/LV2
# 	$(MAKE) -C tal-reverb-3/LV2
# 	$(MAKE) -C tal-vocoder-2/LV2
# 	$(MAKE) -C vex/LV2
# 	$(MAKE) -C wolpertinger/LV2

vst:
	$(MAKE) -C arctican-function/VST
	$(MAKE) -C arctican-pilgrim/VST
	$(MAKE) -C drowaudio-distortion/VST
	$(MAKE) -C drowaudio-distortionshaper/VST
	$(MAKE) -C drowaudio-flanger/VST
	$(MAKE) -C drowaudio-reverb/VST
	$(MAKE) -C drowaudio-tremolo/VST
# 	$(MAKE) -C drumsynth/VST
# 	$(MAKE) -C eqinox/VST
# 	$(MAKE) -C highlife/VST
# 	$(MAKE) -C juce-demo-plugin/VST
	$(MAKE) -C tal-dub-3/VST
	$(MAKE) -C tal-filter/VST
	$(MAKE) -C tal-filter-2/VST
	$(MAKE) -C tal-noisemaker/VST
	$(MAKE) -C tal-reverb/VST
	$(MAKE) -C tal-reverb-2/VST
	$(MAKE) -C tal-reverb-3/VST
	$(MAKE) -C tal-vocoder-2/VST
# 	$(MAKE) -C vex/VST
# 	$(MAKE) -C wolpertinger/VST

clean:
	# Standalone
	$(MAKE) clean -C arctican-function/Standalone
	$(MAKE) clean -C arctican-pilgrim/Standalone
	$(MAKE) clean -C drowaudio-distortion/Standalone
	$(MAKE) clean -C drowaudio-distortionshaper/Standalone
	$(MAKE) clean -C drowaudio-flanger/Standalone
	$(MAKE) clean -C drowaudio-reverb/Standalone
	$(MAKE) clean -C drowaudio-tremolo/Standalone
# 	$(MAKE) clean -C drumsynth/Standalone
# 	$(MAKE) clean -C eqinox/Standalone
# 	$(MAKE) clean -C highlife/Standalone
# 	$(MAKE) clean -C juce-demo-plugin/Standalone
	$(MAKE) clean -C tal-dub-3/Standalone
	$(MAKE) clean -C tal-filter/Standalone
	$(MAKE) clean -C tal-filter-2/Standalone
	$(MAKE) clean -C tal-noisemaker/Standalone
	$(MAKE) clean -C tal-reverb/Standalone
	$(MAKE) clean -C tal-reverb-2/Standalone
	$(MAKE) clean -C tal-reverb-3/Standalone
	$(MAKE) clean -C tal-vocoder-2/Standalone
# 	$(MAKE) clean -C vex/Standalone
# 	$(MAKE) clean -C wolpertinger/Standalone

	# LV2
	$(MAKE) clean -C arctican-function/LV2
	$(MAKE) clean -C arctican-pilgrim/LV2
	$(MAKE) clean -C drowaudio-distortion/LV2
	$(MAKE) clean -C drowaudio-distortionshaper/LV2
	$(MAKE) clean -C drowaudio-flanger/LV2
	$(MAKE) clean -C drowaudio-reverb/LV2
	$(MAKE) clean -C drowaudio-tremolo/LV2
# 	$(MAKE) clean -C drumsynth/LV2
# 	$(MAKE) clean -C eqinox/LV2
# 	$(MAKE) clean -C highlife/LV2
# 	$(MAKE) clean -C juce-demo-plugin/LV2
	$(MAKE) clean -C tal-dub-3/LV2
	$(MAKE) clean -C tal-filter/LV2
	$(MAKE) clean -C tal-filter-2/LV2
	$(MAKE) clean -C tal-noisemaker/LV2
	$(MAKE) clean -C tal-reverb/LV2
	$(MAKE) clean -C tal-reverb-2/LV2
	$(MAKE) clean -C tal-reverb-3/LV2
	$(MAKE) clean -C tal-vocoder-2/LV2
# 	$(MAKE) clean -C vex/LV2
# 	$(MAKE) clean -C wolpertinger/LV2

	# VST
	$(MAKE) clean -C arctican-function/VST
	$(MAKE) clean -C arctican-pilgrim/VST
	$(MAKE) clean -C drowaudio-distortion/VST
	$(MAKE) clean -C drowaudio-distortionshaper/VST
	$(MAKE) clean -C drowaudio-flanger/VST
	$(MAKE) clean -C drowaudio-reverb/VST
	$(MAKE) clean -C drowaudio-tremolo/VST
# 	$(MAKE) clean -C drumsynth/VST
# 	$(MAKE) clean -C eqinox/VST
# 	$(MAKE) clean -C highlife/VST
# 	$(MAKE) clean -C juce-demo-plugin/VST
	$(MAKE) clean -C tal-dub-3/VST
	$(MAKE) clean -C tal-filter/VST
	$(MAKE) clean -C tal-filter-2/VST
	$(MAKE) clean -C tal-noisemaker/VST
	$(MAKE) clean -C tal-reverb/VST
	$(MAKE) clean -C tal-reverb-2/VST
	$(MAKE) clean -C tal-reverb-3/VST
	$(MAKE) clean -C tal-vocoder-2/VST
# 	$(MAKE) clean -C vex/VST
# 	$(MAKE) clean -C wolpertinger/VST

	rm -rf */Standalone/intermediate
	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate

distclean: clean
	rm -rf */LV2/*.lv2
	rm -f */*/Makefile
	rm -f */*/*.make
	rm -f */*/*.sln
	rm -f */*/*.vcproj
