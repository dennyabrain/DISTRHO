# Compile all the Plugins and Ports

all: build


build:
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/lv2-ttl-generator
	$(MAKE) plugins -C plugins
	$(MAKE) plugins -C ports

gen:
	@./scripts/generate-ttl.sh

clean:
	$(MAKE) clean -C libs/juce-2.0
	$(MAKE) clean -C libs/lv2-ttl-generator
	$(MAKE) clean -C plugins
	$(MAKE) clean -C ports
	rm -rf bin/*.lv2

distclean: clean
	$(MAKE) distclean -C libs/juce-2.0
	$(MAKE) distclean -C plugins
	$(MAKE) distclean -C ports


# Custom build types
standalone:
	$(MAKE) -C libs/juce-2.0
	$(MAKE) standalone -C plugins
	$(MAKE) standalone -C ports

lv2:
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/lv2-ttl-generator
	$(MAKE) lv2 -C plugins
	$(MAKE) lv2 -C ports

vst:
	$(MAKE) -C libs/juce-2.0
	$(MAKE) vst -C plugins
	$(MAKE) vst -C ports
