# Compile all the Plugins

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
	$(MAKE) -C 3BandEQ/Standalone

standalone_vst: libs_standalone_vst
	# None

lv2: libs_plugin libs_lv2
	$(MAKE) -C 3BandEQ/LV2

lv2_vst: libs_plugin_vst libs_lv2
	# None

vst: libs_plugin libs_plugin_vst
	$(MAKE) -C 3BandEQ/VST


clean:
	# Standalone
	$(MAKE) clean -C 3BandEQ/Standalone

	# LV2
	$(MAKE) clean -C 3BandEQ/LV2

	# VST
	$(MAKE) clean -C 3BandEQ/VST

	rm -rf */Standalone/intermediate
	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate
