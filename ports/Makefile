# Compile all the Ports

all: build


build: libs plugins

plugins: standalone lv2 vst

libs:
	# Libs
	$(MAKE) -C ../libs/juce-153/standalone
	$(MAKE) -C ../libs/juce-153/plugin
	$(MAKE) -C ../libs/juce-lv2

standalone:
	$(MAKE) -C arctican-function/Standalone
	$(MAKE) -C arctican-pilgrim/Standalone
	$(MAKE) -C eqinox/Standalone
	$(MAKE) -C hybridreverb2/Standalone
	$(MAKE) -C nekobee/Standalone
	$(MAKE) -C sDelay/Standalone
	$(MAKE) -C tal-dub-3-juce/Standalone
	$(MAKE) -C tal-filter-juce/Standalone
	$(MAKE) -C tal-filter-2-juce/Standalone
	$(MAKE) -C tal-noisemaker-juce/Standalone
	$(MAKE) -C tal-reverb-juce/Standalone
	$(MAKE) -C tal-reverb-2-juce/Standalone
	$(MAKE) -C tal-reverb-3-juce/Standalone
	$(MAKE) -C tal-vocoder-2-juce/Standalone
	$(MAKE) -C wolpertinger/Standalone

lv2:
# 	$(MAKE) -C arctican-function/LV2
# 	$(MAKE) -C arctican-pilgrim/LV2
	$(MAKE) -C eqinox/LV2
#	$(MAKE) -C hybridreverb2/LV2
# 	$(MAKE) -C nekobee/LV2
# 	$(MAKE) -C sDelay/LV2
# 	$(MAKE) -C tal-dub-3-juce/LV2
# 	$(MAKE) -C tal-filter-juce/LV2
# 	$(MAKE) -C tal-filter-2-juce/LV2
# 	$(MAKE) -C tal-noisemaker-juce/LV2
# 	$(MAKE) -C tal-reverb-juce/LV2
# 	$(MAKE) -C tal-reverb-2-juce/LV2
# 	$(MAKE) -C tal-reverb-3-juce/LV2
# 	$(MAKE) -C tal-vocoder-2-juce/LV2
#	$(MAKE) -C wolpertinger/LV2

# 	../libs/juce_lv2_ttl_generator ../bin/*.lv2/*.so

vst:
	$(MAKE) -C arctican-function/VST
	$(MAKE) -C arctican-pilgrim/VST
	$(MAKE) -C eqinox/VST
	$(MAKE) -C huit/VST
	$(MAKE) -C hybridreverb2/VST
	$(MAKE) -C nekobee/VST
	$(MAKE) -C sDelay/VST
	$(MAKE) -C tal-dub-3-juce/VST
	$(MAKE) -C tal-filter-juce/VST
	$(MAKE) -C tal-filter-2-juce/VST
	$(MAKE) -C tal-noisemaker-juce/VST
	$(MAKE) -C tal-reverb-juce/VST
	$(MAKE) -C tal-reverb-2-juce/VST
	$(MAKE) -C tal-reverb-3-juce/VST
	$(MAKE) -C tal-vocoder-2-juce/VST
	$(MAKE) -C wolpertinger/VST

clean:
	# Standalone
	$(MAKE) clean -C arctican-function/Standalone
	$(MAKE) clean -C arctican-pilgrim/Standalone
	$(MAKE) clean -C eqinox/Standalone
	$(MAKE) clean -C hybridreverb2/Standalone
	$(MAKE) clean -C nekobee/Standalone
	$(MAKE) clean -C sDelay/Standalone
	$(MAKE) clean -C tal-dub-3-juce/Standalone
	$(MAKE) clean -C tal-filter-juce/Standalone
	$(MAKE) clean -C tal-filter-2-juce/Standalone
	$(MAKE) clean -C tal-noisemaker-juce/Standalone
	$(MAKE) clean -C tal-reverb-juce/Standalone
	$(MAKE) clean -C tal-reverb-2-juce/Standalone
	$(MAKE) clean -C tal-reverb-3-juce/Standalone
	$(MAKE) clean -C tal-vocoder-2-juce/Standalone
	$(MAKE) clean -C wolpertinger/Standalone

	# LV2
# 	$(MAKE) clean -C arctican-function/LV2
# 	$(MAKE) clean -C arctican-pilgrim/LV2
	$(MAKE) clean -C eqinox/LV2
#	$(MAKE) clean -C hybridreverb2/LV2
# 	$(MAKE) clean -C nekobee/LV2
# 	$(MAKE) clean -C sDelay/LV2
# 	$(MAKE) clean -C tal-dub-3-juce/LV2
# 	$(MAKE) clean -C tal-filter-juce/LV2
# 	$(MAKE) clean -C tal-filter-2-juce/LV2
# 	$(MAKE) clean -C tal-noisemaker-juce/LV2
# 	$(MAKE) clean -C tal-reverb-juce/LV2
# 	$(MAKE) clean -C tal-reverb-2-juce/LV2
# 	$(MAKE) clean -C tal-reverb-3-juce/LV2
# 	$(MAKE) clean -C tal-vocoder-2-juce/LV2
# 	$(MAKE) clean -C wolpertinger/LV2

	# VST
	$(MAKE) clean -C arctican-function/VST
	$(MAKE) clean -C arctican-pilgrim/VST
	$(MAKE) clean -C eqinox/VST
	$(MAKE) clean -C huit/VST
	$(MAKE) clean -C hybridreverb2/VST
	$(MAKE) clean -C nekobee/VST
	$(MAKE) clean -C sDelay/VST
	$(MAKE) clean -C tal-dub-3-juce/VST
	$(MAKE) clean -C tal-filter-juce/VST
	$(MAKE) clean -C tal-filter-2-juce/VST
	$(MAKE) clean -C tal-noisemaker-juce/VST
	$(MAKE) clean -C tal-reverb-juce/VST
	$(MAKE) clean -C tal-reverb-2-juce/VST
	$(MAKE) clean -C tal-reverb-3-juce/VST
	$(MAKE) clean -C tal-vocoder-2-juce/VST
	$(MAKE) clean -C wolpertinger/VST

	rm -rf */Standalone/intermediate
	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate
