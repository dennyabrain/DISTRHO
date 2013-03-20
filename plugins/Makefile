# Compile all the Plugins

all: build


build: plugins

plugins: standalone ladspa dssi lv2 vst


standalone:
# 	mkdir -p ../bin/standalone
# 	$(MAKE) -C 3BandEQ/Standalone
# 	$(MAKE) -C 3BandSplitter/Standalone
# 	$(MAKE) -C PingPongPan/Standalone

ladspa:
# 	mkdir -p ../bin/ladspa
# 	$(MAKE) -C 3BandEQ/LADSPA
# 	$(MAKE) -C 3BandSplitter/LADSPA
# 	$(MAKE) -C PingPongPan/LADSPA

dssi:
# 	mkdir -p ../bin/dssi
# 	$(MAKE) -C 3BandEQ/DSSI
# 	$(MAKE) -C 3BandSplitter/DSSI
# 	$(MAKE) -C PingPongPan/DSSI

lv2:
# 	mkdir -p ../bin/lv2
# 	$(MAKE) -C 3BandEQ/LV2
# 	$(MAKE) -C 3BandSplitter/LV2
# 	$(MAKE) -C PingPongPan/LV2

vst:
	mkdir -p ../bin/vst
# 	$(MAKE) -C 3BandEQ/VST
# 	$(MAKE) -C 3BandSplitter/VST
# 	$(MAKE) -C PingPongPan/VST
	$(MAKE) -C JackAss/VST


clean:
	# Standalone
# 	$(MAKE) clean -C 3BandEQ/Standalone
# 	$(MAKE) clean -C 3BandSplitter/Standalone
# 	$(MAKE) clean -C PingPongPan/Standalone

	# LADSPA
# 	$(MAKE) clean -C 3BandEQ/LADSPA
# 	$(MAKE) clean -C 3BandSplitter/LADSPA
# 	$(MAKE) clean -C PingPongPan/LADSPA

	# DSSI
# 	$(MAKE) clean -C 3BandEQ/DSSI
# 	$(MAKE) clean -C 3BandSplitter/DSSI
# 	$(MAKE) clean -C PingPongPan/DSSI

	# LV2
# 	$(MAKE) clean -C 3BandEQ/LV2
# 	$(MAKE) clean -C 3BandSplitter/LV2
# 	$(MAKE) clean -C PingPongPan/LV2

	# VST
# 	$(MAKE) clean -C 3BandEQ/VST
# 	$(MAKE) clean -C 3BandSplitter/VST
# 	$(MAKE) clean -C PingPongPan/VST
	$(MAKE) clean -C JackAss/VST


distclean: clean
	# Standalone
# 	$(MAKE) distclean -C 3BandEQ/Standalone
# 	$(MAKE) distclean -C 3BandSplitter/Standalone
# 	$(MAKE) distclean -C PingPongPan/Standalone

	# LADSPA
# 	$(MAKE) distclean -C 3BandEQ/LADSPA
# 	$(MAKE) distclean -C 3BandSplitter/LADSPA
# 	$(MAKE) distclean -C PingPongPan/LADSPA

	# DSSI
# 	$(MAKE) distclean -C 3BandEQ/DSSI
# 	$(MAKE) distclean -C 3BandSplitter/DSSI
# 	$(MAKE) distclean -C PingPongPan/DSSI

	# LV2
# 	$(MAKE) distclean -C 3BandEQ/LV2
# 	$(MAKE) distclean -C 3BandSplitter/LV2
# 	$(MAKE) distclean -C PingPongPan/LV2

	# VST
# 	$(MAKE) distclean -C 3BandEQ/VST
# 	$(MAKE) distclean -C 3BandSplitter/VST
# 	$(MAKE) distclean -C PingPongPan/VST

	rm -f */*/Makefile
	rm -f */*/*.make
