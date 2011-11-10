# Compile all the Plugins

all: build


build: libs standalone lv2 vst


libs: libs_standalone libs_plugin libs_lv2

libs_standalone:
	$(MAKE) -C ../libs/juce-153/standalone

libs_plugin:
	$(MAKE) -C ../libs/juce-153/plugin

libs_lv2:
	$(MAKE) -C ../libs/juce-lv2


standalone: libs_standalone
	$(MAKE) -C 3BandEQ/Standalone


lv2: libs_plugin libs_lv2
	$(MAKE) -C 3BandEQ/LV2


vst: libs_plugin
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
