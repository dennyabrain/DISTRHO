# Compile all the Plugins and Ports

all: build


build:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0 all
	$(MAKE) -C libs/juced
	$(MAKE) -C libs/lv2-ttl-generator
	$(MAKE) plugins -C plugins
	$(MAKE) plugins -C ports

gen:
	@./scripts/generate-cabbage-lv2.sh
	@./scripts/generate-ttl.sh

mingw:
	$(MAKE) -C libs/lv2-ttl-generator mingw

clean:
	$(MAKE) clean -C libs/distrho/dgl
	$(MAKE) clean -C libs/drowaudio
	$(MAKE) clean -C libs/juce-2.0
	$(MAKE) clean -C libs/juced
	$(MAKE) clean -C libs/lv2-ttl-generator
	$(MAKE) clean -C plugins
	$(MAKE) clean -C ports
	rm -rf bin/lv2/*.lv2

distclean: clean
	$(MAKE) distclean -C libs/distrho/dgl
	$(MAKE) distclean -C libs/drowaudio
	$(MAKE) distclean -C libs/juce-2.0
	$(MAKE) distclean -C libs/juced
	$(MAKE) distclean -C plugins
	$(MAKE) distclean -C ports


# Custom build types
standalone:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juced
	$(MAKE) standalone -C plugins
	$(MAKE) standalone -C ports

standalone-host: standalone
	$(MAKE) -C libs/juce-2.0 all
	$(MAKE) standalone-host -C ports

dssi:
	$(MAKE) -C libs/distrho/dgl

lv2:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juced
	$(MAKE) -C libs/lv2-ttl-generator
	$(MAKE) lv2 -C plugins
	$(MAKE) lv2 -C ports
	$(MAKE) gen

vst:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juced
	$(MAKE) vst -C plugins
	$(MAKE) vst -C ports
