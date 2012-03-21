# Compile all the Ports

all: build


build: libs standalone lv2 vst

plugins: standalone lv2 vst


libs:
	$(MAKE) -C ../libs/juce-2.0
	$(MAKE) -C ../libs/juce-lv2

standalone:
	$(MAKE) -C arctican-function/Standalone
	$(MAKE) -C arctican-pilgrim/Standalone
	$(MAKE) -C argotlunar/Standalone
	$(MAKE) -C bitmangler/Standalone
	$(MAKE) -C hybridreverb2/Standalone
	$(MAKE) -C juce-demo-plugin/Standalone
	$(MAKE) -C juce_pitcher/Standalone
	$(MAKE) -C sDelay/Standalone
	$(MAKE) -C tal-dub-3/Standalone
	$(MAKE) -C tal-filter/Standalone
	$(MAKE) -C tal-filter-2/Standalone
	$(MAKE) -C tal-noisemaker/Standalone
	$(MAKE) -C tal-reverb/Standalone
	$(MAKE) -C tal-reverb-2/Standalone
	$(MAKE) -C tal-reverb-3/Standalone
	$(MAKE) -C tal-vocoder-2/Standalone
	$(MAKE) -C wolpertinger/Standalone

lv2:
	$(MAKE) -C arctican-function/LV2
	$(MAKE) -C arctican-pilgrim/LV2
	$(MAKE) -C argotlunar/LV2
	$(MAKE) -C bitmangler/LV2
	$(MAKE) -C cmt-bitcrusher/LV2
	$(MAKE) -C hybridreverb2/LV2
	$(MAKE) -C juce-demo-plugin/LV2
	$(MAKE) -C juce_pitcher/LV2
	$(MAKE) -C sDelay/LV2
	$(MAKE) -C tal-dub-3/LV2
	$(MAKE) -C tal-filter/LV2
	$(MAKE) -C tal-filter-2/LV2
	$(MAKE) -C tal-noisemaker/LV2
	$(MAKE) -C tal-reverb/LV2
	$(MAKE) -C tal-reverb-2/LV2
	$(MAKE) -C tal-reverb-3/LV2
	$(MAKE) -C tal-vocoder-2/LV2
	$(MAKE) -C wolpertinger/LV2

vst:
	$(MAKE) -C arctican-function/VST
	$(MAKE) -C arctican-pilgrim/VST
	$(MAKE) -C argotlunar/VST
	$(MAKE) -C bitmangler/VST
	$(MAKE) -C hybridreverb2/VST
	$(MAKE) -C juce-demo-plugin/VST
	$(MAKE) -C juce_pitcher/VST
	$(MAKE) -C sDelay/VST
	$(MAKE) -C tal-dub-3/VST
	$(MAKE) -C tal-filter/VST
	$(MAKE) -C tal-filter-2/VST
	$(MAKE) -C tal-noisemaker/VST
	$(MAKE) -C tal-reverb/VST
	$(MAKE) -C tal-reverb-2/VST
	$(MAKE) -C tal-reverb-3/VST
	$(MAKE) -C tal-vocoder-2/VST
	$(MAKE) -C wolpertinger/VST

clean:
	# Standalone
	$(MAKE) clean -C arctican-function/Standalone
	$(MAKE) clean -C arctican-pilgrim/Standalone
	$(MAKE) clean -C argotlunar/Standalone
	$(MAKE) clean -C bitmangler/Standalone
	$(MAKE) clean -C hybridreverb2/Standalone
	$(MAKE) clean -C juce-demo-plugin/Standalone
	$(MAKE) clean -C juce_pitcher/Standalone
	$(MAKE) clean -C sDelay/Standalone
	$(MAKE) clean -C tal-dub-3/Standalone
	$(MAKE) clean -C tal-filter/Standalone
	$(MAKE) clean -C tal-filter-2/Standalone
	$(MAKE) clean -C tal-noisemaker/Standalone
	$(MAKE) clean -C tal-reverb/Standalone
	$(MAKE) clean -C tal-reverb-2/Standalone
	$(MAKE) clean -C tal-reverb-3/Standalone
	$(MAKE) clean -C tal-vocoder-2/Standalone
	$(MAKE) clean -C wolpertinger/Standalone

	# LV2
	$(MAKE) clean -C arctican-function/LV2
	$(MAKE) clean -C arctican-pilgrim/LV2
	$(MAKE) clean -C argotlunar/LV2
	$(MAKE) clean -C bitmangler/LV2
	$(MAKE) clean -C cmt-bitcrusher/LV2
	$(MAKE) clean -C hybridreverb2/LV2
	$(MAKE) clean -C juce-demo-plugin/LV2
	$(MAKE) clean -C juce_pitcher/LV2
	$(MAKE) clean -C sDelay/LV2
	$(MAKE) clean -C tal-dub-3/LV2
	$(MAKE) clean -C tal-filter/LV2
	$(MAKE) clean -C tal-filter-2/LV2
	$(MAKE) clean -C tal-noisemaker/LV2
	$(MAKE) clean -C tal-reverb/LV2
	$(MAKE) clean -C tal-reverb-2/LV2
	$(MAKE) clean -C tal-reverb-3/LV2
	$(MAKE) clean -C tal-vocoder-2/LV2
	$(MAKE) clean -C wolpertinger/LV2

	# VST
	$(MAKE) clean -C arctican-function/VST
	$(MAKE) clean -C arctican-pilgrim/VST
	$(MAKE) clean -C argotlunar/VST
	$(MAKE) clean -C bitmangler/VST
	$(MAKE) clean -C hybridreverb2/VST
	$(MAKE) clean -C juce-demo-plugin/VST
	$(MAKE) clean -C juce_pitcher/VST
	$(MAKE) clean -C sDelay/VST
	$(MAKE) clean -C tal-dub-3/VST
	$(MAKE) clean -C tal-filter/VST
	$(MAKE) clean -C tal-filter-2/VST
	$(MAKE) clean -C tal-noisemaker/VST
	$(MAKE) clean -C tal-reverb/VST
	$(MAKE) clean -C tal-reverb-2/VST
	$(MAKE) clean -C tal-reverb-3/VST
	$(MAKE) clean -C tal-vocoder-2/VST
	$(MAKE) clean -C wolpertinger/VST

	rm -rf */Standalone/intermediate
	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate

distclean: clean
	rm -rf */LV2/*.lv2
	rm -f */*/Makefile
	rm -f */*/*.make
	rm -f */*/*.sln
	rm -f */*/*.vcproj
