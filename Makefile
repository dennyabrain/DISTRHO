# Compile all the Plugins and Ports

all: build


build: build_libs build_plugins build_ports build_outro


build_libs:
	$(MAKE) -C libs/juce-153/standalone
	$(MAKE) -C libs/juce-153/standalone-vst
	$(MAKE) -C libs/juce-153/plugin
	$(MAKE) -C libs/juce-153/plugin-vst
	$(MAKE) -C libs/juce-lv2

build_plugins:
	$(MAKE) -C plugins

build_ports:
	$(MAKE) -C ports

build_outro:
	$(MAKE) -C outro


clean:
	$(MAKE) clean -C libs/juce-153/standalone
	$(MAKE) clean -C libs/juce-153/standalone-vst
	$(MAKE) clean -C libs/juce-153/plugin
	$(MAKE) clean -C libs/juce-153/plugin-vst
	$(MAKE) clean -C libs/juce-lv2
	$(MAKE) clean -C plugins
	$(MAKE) clean -C ports
	$(MAKE) clean -C outro


# Custom build types
standalone:
	$(MAKE) -C libs/juce-153/standalone
	$(MAKE) standalone -C plugins
	$(MAKE) standalone -C ports
	$(MAKE) standalone -C outro

standalone_vst:
	$(MAKE) -C libs/juce-153/standalone-vst
	$(MAKE) standalone_vst -C plugins
	$(MAKE) standalone_vst -C ports
	$(MAKE) standalone_vst -C outro

lv2:
	$(MAKE) -C libs/juce-153/plugin
	$(MAKE) -C libs/juce-lv2
	$(MAKE) lv2 -C plugins
	$(MAKE) lv2 -C ports
	$(MAKE) lv2 -C outro

lv2_vst:
	$(MAKE) -C libs/juce-153/plugin-vst
	$(MAKE) -C libs/juce-lv2
	$(MAKE) lv2_vst -C plugins
	$(MAKE) lv2_vst -C ports
	$(MAKE) lv2_vst -C outro

vst:
	$(MAKE) -C libs/juce-153/plugin
	$(MAKE) vst -C plugins
	$(MAKE) vst -C ports
	$(MAKE) vst -C outro
