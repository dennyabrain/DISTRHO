# Compile all the Plugins and Ports

all: build


build: build_libs build_plugins build_ports


build_libs:
	$(MAKE) -C libs/juce-153/standalone
	$(MAKE) -C libs/juce-153/plugin
	$(MAKE) -C libs/juce-lv2


build_plugins:
	$(MAKE) -C plugins


build_ports:
	$(MAKE) -C ports


clean:
	$(MAKE) clean -C libs/juce-153/standalone
	$(MAKE) clean -C libs/juce-153/plugin
	$(MAKE) clean -C libs/juce-lv2
	$(MAKE) clean -C plugins
	$(MAKE) clean -C ports
