# Compile all the Plugins and Ports

PREFIX=/usr/local


all: build


build:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juced
	$(MAKE) -C libs/lv2-ttl-generator
# 	$(MAKE) plugins -C plugins
	$(MAKE) plugins -C ports
	$(MAKE) gen


install:
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -d $(DESTDIR)$(PREFIX)/lib/
# 	install -d $(DESTDIR)$(PREFIX)/lib/ladspa/
# 	install -d $(DESTDIR)$(PREFIX)/lib/dssi/
	install -d $(DESTDIR)$(PREFIX)/lib/lv2/
	install -d $(DESTDIR)$(PREFIX)/lib/vst/
	install -m 644 bin/standalone/* $(DESTDIR)$(PREFIX)/bin/
# 	install -m 644 bin/ladspa/*     $(DESTDIR)$(PREFIX)/lib/ladspa/
# 	install -m 644 bin/dssi/*       $(DESTDIR)$(PREFIX)/lib/dssi/
	install -m 644 bin/vst/*        $(DESTDIR)$(PREFIX)/lib/vst/
	install -m 644 libs/*.so        $(DESTDIR)$(PREFIX)/lib/
	install -m 755 libs/lv2_ttl_generator $(DESTDIR)$(PREFIX)/bin/

	cp -r bin/lv2/*.lv2/ static-lv2-ttl/*.lv2/ $(DESTDIR)$(PREFIX)/lib/lv2/


gen: gen_lv2 gen_vst

gen_lv2:
	$(MAKE) -C libs/lv2-ttl-generator
	@./scripts/generate-cabbage-lv2.sh
	@./scripts/generate-ttl.sh

gen_vst:
	@./scripts/generate-cabbage-vst.sh


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
	rm -rf bin/lv2/*.lv2/

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
# 	$(MAKE) standalone -C plugins
	$(MAKE) standalone -C ports

ladspa:
# 	$(MAKE) ladspa -C plugins

dssi:
	$(MAKE) -C libs/distrho/dgl
# 	$(MAKE) dssi -C plugins

lv2:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juced
	$(MAKE) -C libs/lv2-ttl-generator
# 	$(MAKE) lv2 -C plugins
	$(MAKE) lv2 -C ports
	$(MAKE) gen_lv2

vst:
	$(MAKE) -C libs/distrho/dgl
	$(MAKE) -C libs/drowaudio
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juced
# 	$(MAKE) vst -C plugins
	$(MAKE) vst -C ports
	$(MAKE) gen_vst
