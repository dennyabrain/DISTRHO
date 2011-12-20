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
	$(MAKE) -C midilfo/Standalone

standalone_vst: libs_standalone_vst
	$(MAKE) -C juce-demo-host/Standalone

lv2: libs_plugin libs_lv2
	# None

lv2_vst: libs_plugin_vst libs_lv2
	# None

vst: libs_plugin libs_plugin_vst
	$(MAKE) -C pizmidi/VST
	$(MAKE) -C sorollet/VST


clean:
	# Standalone
	$(MAKE) clean -C juce-demo-host/Standalone
	$(MAKE) clean -C midilfo/Standalone

	# VST
	$(MAKE) clean -C pizmidi/VST
	$(MAKE) clean -C sorollet/VST

	rm -rf */Standalone/intermediate
	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate
	rm -rf */VST/*/intermediate
