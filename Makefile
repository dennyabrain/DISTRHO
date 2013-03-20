# Compile all the Plugins and Ports

all: build


build:
# 	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
# 	$(MAKE) -C libs/juced
# 	$(MAKE) -C libs/lv2-ttl-generator
# 	$(MAKE) plugins -C plugins
# 	$(MAKE) plugins -C ports

gen:
	@./scripts/generate-ttl.sh

	# Copy manually modified ttls with extra data
# 	if [ -d bin/3BandEQ.lv2/ ]; then cp static-lv2-ttl/3BandEQ.ttl bin/3BandEQ.lv2/; fi
# 	if [ -d bin/3BandSplitter.lv2/ ]; then cp static-lv2-ttl/3BandSplitter.ttl bin/3BandSplitter.lv2/; fi
# 	if [ -d bin/Bitcrusher.lv2/ ]; then cp static-lv2-ttl/Bitcrusher.ttl bin/Bitcrusher.lv2/; fi

mingw:
	$(MAKE) -C libs/lv2-ttl-generator mingw

clean:
# 	$(MAKE) clean -C libs/drowaudio
	$(MAKE) clean -C libs/juce-2.0
# 	$(MAKE) clean -C libs/juced
# 	$(MAKE) clean -C libs/lv2-ttl-generator
# 	$(MAKE) clean -C plugins
# 	$(MAKE) clean -C ports
# 	rm -rf bin/lv2/*.lv2

distclean: clean
# 	$(MAKE) distclean -C libs/drowaudio
	$(MAKE) distclean -C libs/juce-2.0
# 	$(MAKE) distclean -C libs/juced
# 	$(MAKE) distclean -C plugins
# 	$(MAKE) distclean -C ports


# Custom build types
standalone:
# 	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
# 	$(MAKE) -C libs/juced
# 	$(MAKE) standalone -C plugins
# 	$(MAKE) standalone -C ports

lv2:
# 	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
# 	$(MAKE) -C libs/juced
# 	$(MAKE) -C libs/lv2-ttl-generator
# 	$(MAKE) lv2 -C plugins
# 	$(MAKE) lv2 -C ports

vst:
# 	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
# 	$(MAKE) -C libs/juced
# 	$(MAKE) vst -C plugins
# 	$(MAKE) vst -C ports
