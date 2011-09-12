# Compile all the Plugins

all: build


build: libs plugins

plugins: standalone lv2 vst

libs:
	# Libs
	$(MAKE) -C ../libs/juce-153/standalone
	$(MAKE) -C ../libs/juce-153/plugin

standalone:
# 	$(MAKE) -C vex/Standalone
	$(MAKE) -C tal-dub-3-juce/Standalone
	$(MAKE) -C tal-filter-juce/Standalone
	$(MAKE) -C tal-filter-2-juce/Standalone
	$(MAKE) -C tal-noisemaker-juce/Standalone
	$(MAKE) -C tal-reverb-juce/Standalone
	$(MAKE) -C tal-reverb-2-juce/Standalone
	$(MAKE) -C tal-reverb-3-juce/Standalone
	$(MAKE) -C tal-vocoder-2-juce/Standalone

lv2:
# 	$(MAKE) -C vex/LV2
# 	$(MAKE) -C tal-dub-3-juce/LV2
# 	$(MAKE) -C tal-filter-juce/LV2
# 	$(MAKE) -C tal-filter-2-juce/LV2
# 	$(MAKE) -C tal-noisemaker-juce/LV2
# 	$(MAKE) -C tal-reverb-juce/LV2
# 	$(MAKE) -C tal-reverb-2-juce/LV2
# 	$(MAKE) -C tal-reverb-3-juce/LV2
# 	$(MAKE) -C tal-vocoder-2-juce/LV2

vst:
# 	$(MAKE) -C vex/VST
	$(MAKE) -C tal-dub-3-juce/VST
	$(MAKE) -C tal-filter-juce/VST
	$(MAKE) -C tal-filter-2-juce/VST
	$(MAKE) -C tal-noisemaker-juce/VST
	$(MAKE) -C tal-reverb-juce/VST
	$(MAKE) -C tal-reverb-2-juce/VST
	$(MAKE) -C tal-reverb-3-juce/VST
	$(MAKE) -C tal-vocoder-2-juce/VST

clean:
	# Standalones
# 	$(MAKE) clean -C vex/Standalone
	$(MAKE) clean -C tal-dub-3-juce/Standalone
	$(MAKE) clean -C tal-filter-juce/Standalone
	$(MAKE) clean -C tal-filter-2-juce/Standalone
	$(MAKE) clean -C tal-noisemaker-juce/Standalone
	$(MAKE) clean -C tal-reverb-juce/Standalone
	$(MAKE) clean -C tal-reverb-2-juce/Standalone
	$(MAKE) clean -C tal-reverb-3-juce/Standalone
	$(MAKE) clean -C tal-vocoder-2-juce/Standalone

	# LV2
# 	$(MAKE) clean -C vex/LV2
# 	$(MAKE) clean -C tal-dub-3-juce/LV2
# 	$(MAKE) clean -C tal-filter-juce/LV2
# 	$(MAKE) clean -C tal-filter-2-juce/LV2
# 	$(MAKE) clean -C tal-noisemaker-juce/LV2
# 	$(MAKE) clean -C tal-reverb-juce/LV2
# 	$(MAKE) clean -C tal-reverb-2-juce/LV2
# 	$(MAKE) clean -C tal-reverb-3-juce/LV2
# 	$(MAKE) clean -C tal-vocoder-2-juce/LV2

	# VST
# 	$(MAKE) clean -C vex/VST
	$(MAKE) clean -C tal-dub-3-juce/VST
	$(MAKE) clean -C tal-filter-juce/VST
	$(MAKE) clean -C tal-filter-2-juce/VST
	$(MAKE) clean -C tal-noisemaker-juce/VST
	$(MAKE) clean -C tal-reverb-juce/VST
	$(MAKE) clean -C tal-reverb-2-juce/VST
	$(MAKE) clean -C tal-reverb-3-juce/VST
	$(MAKE) clean -C tal-vocoder-2-juce/VST
