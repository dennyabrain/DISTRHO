# Compile all the Plugins

all: build


build: libs standalone lv2 vst

plugins: standalone lv2 vst


libs:
	$(MAKE) -C ../libs/lv2-ttl-generator

standalone:

lv2:

vst:
	$(MAKE) -C JackAss/VST

clean:
	# Standalone

	# LV2

	# VST
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
