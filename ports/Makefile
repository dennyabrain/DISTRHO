# Compile all the Ports

all: build


build: libs standalone standalone_vst lv2 lv2_vst vst


libs: libs_standalone libs_standalone_vst libs_plugin libs_plugin_vst libs_lv2

libs_standalone:
	$(MAKE) -C ../libs/juce-153/standalone

libs_standalone_vst:
	$(MAKE) -C ../libs/juce-153/standalone-vst

libs_plugin:
	$(MAKE) -C ../libs/juce-153/plugin

libs_plugin_vst:
	$(MAKE) -C ../libs/juce-153/plugin-vst

libs_lv2:
	$(MAKE) -C ../libs/juce-lv2


standalone: libs_standalone
	$(MAKE) -C arctican-function/Standalone
	$(MAKE) -C arctican-pilgrim/Standalone
	$(MAKE) -C argotlunar/Standalone
	$(MAKE) -C bitmangler/Standalone
	$(MAKE) -C hybridreverb2/Standalone
	$(MAKE) -C juce-demo-plugin/Standalone
	$(MAKE) -C juce_pitcher/Standalone
# 	$(MAKE) -C mr-alias2/Standalone
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

standalone_vst: libs_standalone_vst
	# None

lv2: libs_plugin libs_lv2
	$(MAKE) -C arctican-function/LV2
	$(MAKE) -C arctican-pilgrim/LV2
	$(MAKE) -C argotlunar/LV2
	$(MAKE) -C bitmangler/LV2
	$(MAKE) -C hybridreverb2/LV2
	$(MAKE) -C juce-demo-plugin/LV2
	$(MAKE) -C juce_pitcher/LV2
# 	$(MAKE) -C mr-alias2/LV2
	$(MAKE) -C sDelay/LV2
	$(MAKE) -C tal-dub-3-juce/LV2
	$(MAKE) -C tal-filter-juce/LV2
	$(MAKE) -C tal-filter-2-juce/LV2
	$(MAKE) -C tal-noisemaker-juce/LV2
	$(MAKE) -C tal-reverb-juce/LV2
	$(MAKE) -C tal-reverb-2-juce/LV2
	$(MAKE) -C tal-reverb-3-juce/LV2
	$(MAKE) -C tal-vocoder-2-juce/LV2
	$(MAKE) -C wolpertinger/LV2

lv2_vst: libs_plugin_vst libs_lv2
	# None

vst: libs_plugin libs_plugin_vst
	$(MAKE) -C arctican-function/VST
	$(MAKE) -C arctican-pilgrim/VST
	$(MAKE) -C argotlunar/VST
	$(MAKE) -C bitmangler/VST
	$(MAKE) -C hybridreverb2/VST
	$(MAKE) -C juce-demo-plugin/VST
	$(MAKE) -C juce_pitcher/VST
# 	$(MAKE) -C mr-alias2/VST
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
	$(MAKE) clean -C argotlunar/Standalone
	$(MAKE) clean -C bitmangler/Standalone
	$(MAKE) clean -C hybridreverb2/Standalone
	$(MAKE) clean -C juce-demo-plugin/Standalone
	$(MAKE) clean -C juce_pitcher/Standalone
# 	$(MAKE) clean -C mr-alias2/Standalone
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
	$(MAKE) clean -C arctican-function/LV2
	$(MAKE) clean -C arctican-pilgrim/LV2
	$(MAKE) clean -C argotlunar/LV2
	$(MAKE) clean -C bitmangler/LV2
	$(MAKE) clean -C hybridreverb2/LV2
	$(MAKE) clean -C juce-demo-plugin/LV2
	$(MAKE) clean -C juce_pitcher/LV2
# 	$(MAKE) clean -C mr-alias2/LV2
	$(MAKE) clean -C sDelay/LV2
	$(MAKE) clean -C tal-dub-3-juce/LV2
	$(MAKE) clean -C tal-filter-juce/LV2
	$(MAKE) clean -C tal-filter-2-juce/LV2
	$(MAKE) clean -C tal-noisemaker-juce/LV2
	$(MAKE) clean -C tal-reverb-juce/LV2
	$(MAKE) clean -C tal-reverb-2-juce/LV2
	$(MAKE) clean -C tal-reverb-3-juce/LV2
	$(MAKE) clean -C tal-vocoder-2-juce/LV2
	$(MAKE) clean -C wolpertinger/LV2

	# VST
	$(MAKE) clean -C arctican-function/VST
	$(MAKE) clean -C arctican-pilgrim/VST
	$(MAKE) clean -C argotlunar/VST
	$(MAKE) clean -C bitmangler/VST
	$(MAKE) clean -C hybridreverb2/VST
	$(MAKE) clean -C juce-demo-plugin/VST
	$(MAKE) clean -C juce_pitcher/VST
# 	$(MAKE) clean -C mr-alias2/VST
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
