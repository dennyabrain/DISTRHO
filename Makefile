# Compile all the Plugins and Ports

all: build


build: libs plugins ports


libs: libs_standalone libs_plugin libs_lv2

libs_standalone:
	$(MAKE) -C libs/juce-153/standalone

libs_plugin:
	$(MAKE) -C libs/juce-153/plugin

libs_lv2:
	$(MAKE) -C libs/juce-lv2


plugins:
	$(MAKE) -C plugins


ports:
	$(MAKE) -C ports


clean:
	$(MAKE) clean -C libs/juce-153/standalone
	$(MAKE) clean -C libs/juce-153/plugin
	$(MAKE) clean -C libs/juce-lv2
	$(MAKE) clean -C plugins
	$(MAKE) clean -C ports
