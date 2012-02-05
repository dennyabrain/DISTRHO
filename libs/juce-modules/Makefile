# Compile the juce modules

all: build


build: audio-basics audio-devices audio-formats audio-processors audio-utils \
	core cryptography data-structures events graphics gui-basics gui-extra opengl video


audio-basics:
	$(MAKE) -C build-audio-basics

audio-devices:
	$(MAKE) -C build-audio-devices

audio-formats:
	$(MAKE) -C build-audio-formats

audio-processors:
# 	$(MAKE) -C build-audio-processors

audio-utils:
	$(MAKE) -C build-audio-utils

browser-plugin:
	$(MAKE) -C build-browser-plugin

core:
	$(MAKE) -C build-core

cryptography:
	$(MAKE) -C build-cryptography

data-structures:
	$(MAKE) -C build-data-structures

events:
	$(MAKE) -C build-events

graphics:
	$(MAKE) -C build-graphics

gui-basics:
	$(MAKE) -C build-gui-basics

gui-extra:
	$(MAKE) -C build-gui-extra

opengl:
	$(MAKE) -C build-opengl

video:
	$(MAKE) -C build-video


clean:
	$(MAKE) clean -C build-audio-basics
	$(MAKE) clean -C build-audio-devices
	$(MAKE) clean -C build-audio-formats
# 	$(MAKE) clean -C build-audio-processors
	$(MAKE) clean -C build-audio-utils
	$(MAKE) clean -C build-core
	$(MAKE) clean -C build-cryptography
	$(MAKE) clean -C build-data-structures
	$(MAKE) clean -C build-events
	$(MAKE) clean -C build-graphics
	$(MAKE) clean -C build-gui-basics
	$(MAKE) clean -C build-gui-extra
	$(MAKE) clean -C build-opengl
	$(MAKE) clean -C build-video
