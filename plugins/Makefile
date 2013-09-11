# Compile all the Plugins

all: build


build: libs standalone ladspa dssi lv2 vst

plugins: standalone ladspa dssi lv2 vst


libs:
	$(MAKE) -C ../libs/distrho/dgl

standalone:
	mkdir -p ../bin/standalone
# 	$(MAKE) -C 3BandEQ/Standalone
# 	$(MAKE) -C 3BandSplitter/Standalone
# 	$(MAKE) -C PingPongPan/Standalone

ladspa:
	mkdir -p ../bin/ladspa
	$(MAKE) -C 3BandEQ/LADSPA
	$(MAKE) -C 3BandSplitter/LADSPA
	$(MAKE) -C PingPongPan/LADSPA

dssi: libs
	mkdir -p ../bin/dssi
	$(MAKE) -C 3BandEQ/DSSI
	$(MAKE) -C 3BandEQ/DSSI-UI
	$(MAKE) -C 3BandSplitter/DSSI
	$(MAKE) -C 3BandSplitter/DSSI-UI
	$(MAKE) -C Nekobi/DSSI
	$(MAKE) -C Nekobi/DSSI-UI
	$(MAKE) -C PingPongPan/DSSI
	$(MAKE) -C PingPongPan/DSSI-UI

lv2:
	mkdir -p ../bin/lv2
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
	$(MAKE) clean -C 3BandEQ/LADSPA
	$(MAKE) clean -C 3BandSplitter/LADSPA
	$(MAKE) clean -C PingPongPan/LADSPA

	# DSSI
	$(MAKE) clean -C 3BandEQ/DSSI
	$(MAKE) clean -C 3BandEQ/DSSI-UI
	$(MAKE) clean -C 3BandSplitter/DSSI
	$(MAKE) clean -C 3BandSplitter/DSSI-UI
	$(MAKE) clean -C Nekobi/DSSI
	$(MAKE) clean -C Nekobi/DSSI-UI
	$(MAKE) clean -C PingPongPan/DSSI
	$(MAKE) clean -C PingPongPan/DSSI-UI

	# LV2
# 	$(MAKE) clean -C 3BandEQ/LV2
# 	$(MAKE) clean -C 3BandSplitter/LV2
# 	$(MAKE) clean -C PingPongPan/LV2

	# VST
# 	$(MAKE) clean -C 3BandEQ/VST
# 	$(MAKE) clean -C 3BandSplitter/VST
# 	$(MAKE) clean -C PingPongPan/VST
	$(MAKE) clean -C JackAss/VST

# 	rm -rf */Standalone/intermediate
	rm -rf */LADSPA/intermediate
	rm -rf */DSSI/intermediate
	rm -rf */DSSI-UI/intermediate
# 	rm -rf */LV2/intermediate
# 	rm -rf */VST/intermediate

distclean: clean
# 	rm -rf */LV2/*.lv2
	rm -f */*/Makefile
	rm -f */*/*.make
	rm -f */*/*.sln
	rm -f */*/*.vcproj
