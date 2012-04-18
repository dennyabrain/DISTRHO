# Compile all the Plugins

all: build


build: libs standalone lv2 vst

plugins: standalone lv2 vst


libs:
	$(MAKE) -C ../libs/juce-2.0
	$(MAKE) -C ../libs/lv2-ttl-generator

standalone:
	$(MAKE) -C 3BandEQ/Standalone
	$(MAKE) -C PingPongPan/Standalone

lv2:
	$(MAKE) -C 3BandEQ/LV2
	$(MAKE) -C 3BandSplitter/LV2
	$(MAKE) -C PingPongPan/LV2
	$(MAKE) -C StereoAudioGain/LV2

vst:
	$(MAKE) -C 3BandEQ/VST
	$(MAKE) -C 3BandSplitter/VST
	$(MAKE) -C PingPongPan/VST
	$(MAKE) -C JackAss/VST

clean:
	# Standalone
	$(MAKE) clean -C 3BandEQ/Standalone
	$(MAKE) clean -C PingPongPan/Standalone

	# LV2
	$(MAKE) clean -C 3BandEQ/LV2
	$(MAKE) clean -C 3BandSplitter/LV2
	$(MAKE) clean -C PingPongPan/LV2
	$(MAKE) clean -C StereoAudioGain/LV2

	# VST
	$(MAKE) clean -C 3BandEQ/VST
	$(MAKE) clean -C 3BandSplitter/VST
	$(MAKE) clean -C PingPongPan/VST
	$(MAKE) clean -C JackAss/VST

	rm -rf */Standalone/intermediate
	rm -rf */LV2/intermediate
	rm -rf */VST/intermediate

distclean: clean
	rm -rf */LV2/*.lv2
	rm -f */*/Makefile
	rm -f */*/*.make
	rm -f */*/*.sln
	rm -f */*/*.vcproj
