#!/usr/bin/makefile -f

all: build

build: ../juce_lv2_ttl_generator

../juce_lv2_ttl_generator: juce_lv2_ttl_generator.c
	$(CXX) juce_lv2_ttl_generator.c -o ../juce_lv2_ttl_generator -ldl

clean:
	rm -f ../juce_lv2_ttl_generator
