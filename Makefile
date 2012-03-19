# Compile all the Plugins and Ports

all: build


build:
	$(MAKE) -C libs/juce-2.0
	$(MAKE) -C libs/juce-lv2
# 	$(MAKE) plugins -C plugins
	$(MAKE) plugins -C ports
	@./scripts/generate-ttl.sh


clean:
	$(MAKE) clean -C libs/juce-2.0
	$(MAKE) clean -C libs/juce-lv2
# 	$(MAKE) clean -C plugins
	$(MAKE) clean -C ports


# Custom build types
# standalone:
# 	$(MAKE) -C libs/juce-153/standalone
# 	$(MAKE) standalone -C plugins
# 	$(MAKE) standalone -C ports
# 
# standalone_vst:
# 	$(MAKE) -C libs/juce-153/standalone-vst
# 	$(MAKE) standalone_vst -C plugins
# 	$(MAKE) standalone_vst -C ports
# 
# lv2:
# 	$(MAKE) -C libs/juce-153/plugin
# 	$(MAKE) -C libs/juce-lv2
# 	$(MAKE) lv2 -C plugins
# 	$(MAKE) lv2 -C ports
# 
# lv2_vst:
# 	$(MAKE) -C libs/juce-153/plugin-vst
# 	$(MAKE) -C libs/juce-lv2
# 	$(MAKE) lv2_vst -C plugins
# 	$(MAKE) lv2_vst -C ports
# 
# vst:
# 	$(MAKE) -C libs/juce-153/plugin
# 	$(MAKE) vst -C plugins
# 	$(MAKE) vst -C ports
