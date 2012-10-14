# Compile all the Plugins

all: build


build: plugins

plugins: standalone ladspa dssi lv2 vst


standalone:
	$(MAKE) -C 3BandEQ/Standalone
	$(MAKE) -C 3BandSplitter/Standalone

ladspa:
	$(MAKE) -C 3BandEQ/LADSPA
	$(MAKE) -C 3BandSplitter/LADSPA

dssi:
	$(MAKE) -C 3BandEQ/DSSI
	$(MAKE) -C 3BandSplitter/DSSI

lv2:
	$(MAKE) -C 3BandEQ/LV2
	$(MAKE) -C 3BandSplitter/LV2

vst:
	$(MAKE) -C 3BandEQ/VST
	$(MAKE) -C 3BandSplitter/VST
	$(MAKE) -C JackAss/VST


clean:
	# Standalone
	$(MAKE) clean -C 3BandEQ/Standalone
	$(MAKE) clean -C 3BandSplitter/Standalone

	# LADSPA
	$(MAKE) clean -C 3BandEQ/LADSPA
	$(MAKE) clean -C 3BandSplitter/LADSPA

	# DSSI
	$(MAKE) clean -C 3BandEQ/DSSI
	$(MAKE) clean -C 3BandSplitter/DSSI

	# LV2
	$(MAKE) clean -C 3BandEQ/LV2
	$(MAKE) clean -C 3BandSplitter/LV2

	# VST
	$(MAKE) clean -C 3BandEQ/VST
	$(MAKE) clean -C 3BandSplitter/VST
	$(MAKE) clean -C JackAss/VST


distclean: clean
	# Standalone
	$(MAKE) distclean -C 3BandEQ/Standalone
	$(MAKE) distclean -C 3BandSplitter/Standalone

	# LADSPA
	$(MAKE) distclean -C 3BandEQ/LADSPA
	$(MAKE) distclean -C 3BandSplitter/LADSPA

	# DSSI
	$(MAKE) distclean -C 3BandEQ/DSSI
	$(MAKE) distclean -C 3BandSplitter/DSSI

	# LV2
	$(MAKE) distclean -C 3BandEQ/LV2
	$(MAKE) distclean -C 3BandSplitter/LV2

	# VST
	$(MAKE) distclean -C 3BandEQ/VST
	$(MAKE) distclean -C 3BandSplitter/VST

	rm -f */*/Makefile
	rm -f */*/*.make
