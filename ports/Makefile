# Compile all the VST Plugins

all: build


build:
	# Libs
	$(MAKE) -C ../libs/juce-153

	# Plugins
	$(MAKE) -C vex/LinuxVST
	$(MAKE) -C tal-dub-3-juce/LinuxVST
	$(MAKE) -C tal-filter-juce/LinuxVST
	$(MAKE) -C tal-filter-2-juce/LinuxVST
	$(MAKE) -C tal-noisemaker-juce/LinuxVST
	$(MAKE) -C tal-reverb-juce/LinuxVST
	$(MAKE) -C tal-reverb-2-juce/LinuxVST
	$(MAKE) -C tal-reverb-3-juce/LinuxVST
	$(MAKE) -C tal-vocoder-2-juce/LinuxVST

clean:
	# Plugins
	$(MAKE) clean -C vex/LinuxVST
	$(MAKE) clean -C tal-dub-3-juce/LinuxVST
	$(MAKE) clean -C tal-filter-juce/LinuxVST
	$(MAKE) clean -C tal-filter-2-juce/LinuxVST
	$(MAKE) clean -C tal-noisemaker-juce/LinuxVST
	$(MAKE) clean -C tal-reverb-juce/LinuxVST
	$(MAKE) clean -C tal-reverb-2-juce/LinuxVST
	$(MAKE) clean -C tal-reverb-3-juce/LinuxVST
	$(MAKE) clean -C tal-vocoder-2-juce/LinuxVST
