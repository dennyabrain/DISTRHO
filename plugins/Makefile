# Compile all the Plugins

all: build


build: plugins

plugins: standalone ladspa dssi lv2 vst


standalone:
# 	$(MAKE) -C 3BandEQ/Standalone

ladspa:
	$(MAKE) -C 3BandEQ/LADSPA

dssi:
	$(MAKE) -C 3BandEQ/DSSI

lv2:
# 	$(MAKE) -C 3BandEQ/LV2

vst:
	$(MAKE) -C 3BandEQ/VST
	$(MAKE) -C JackAss/VST


clean:
	# Standalone
	$(MAKE) clean -C 3BandEQ/Standalone

	# LADSPA
	$(MAKE) clean -C 3BandEQ/LADSPA

	# DSSI
	$(MAKE) clean -C 3BandEQ/DSSI

	# LV2
	$(MAKE) clean -C 3BandEQ/LV2

	# VST
	$(MAKE) clean -C 3BandEQ/VST
	$(MAKE) clean -C JackAss/VST


distclean: clean
	# Standalone
	$(MAKE) distclean -C 3BandEQ/Standalone

	# LADSPA
	$(MAKE) distclean -C 3BandEQ/LADSPA

	# DSSI
	$(MAKE) distclean -C 3BandEQ/DSSI

	# LV2
	$(MAKE) distclean -C 3BandEQ/LV2

	# VST
	$(MAKE) distclean -C 3BandEQ/VST

	rm -f */*/Makefile
	rm -f */*/*.make
