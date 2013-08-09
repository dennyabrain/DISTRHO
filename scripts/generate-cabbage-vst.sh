#!/bin/bash

set -e

if [ -d bin ]; then
  echo cd bin
  cd bin
else
  echo "Please run this script from the distrho root folder"
  exit
fi

if [ ! -f standalone/CabbagePluginSynth.so  ]; then exit 0; fi
if [ ! -f standalone/CabbagePluginMidi.so   ]; then exit 0; fi
if [ ! -f standalone/CabbagePluginEffect.so ]; then exit 0; fi

mkdir -p vst

if [ -f ../libs/lv2_ttl_generator.exe ]; then
  EXT=dll
else
  EXT=so
fi

FILES=`find ./cabbage -name \*.csd`

for i in $FILES; do
  basename=`echo $i | awk 'sub("./cabbage/","")' | awk 'sub("/","\n")' | tail -n 1 | awk 'sub(".csd","")'`
  basename=`echo "cabbage-$basename"`

  if ( echo $i | grep "./cabbage/Synths/" > /dev/null ); then
    echo cp `pwd`/standalone/CabbagePluginSynth.so vst/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginSynth.so vst/$basename.$EXT
  elif ( echo $i | grep "./cabbage/MIDI/" > /dev/null ); then
    echo cp `pwd`/standalone/CabbagePluginMidi.so vst/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginMidi.so vst/$basename.$EXT
  else
    echo cp `pwd`/standalone/CabbagePluginEffect.so vst/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginEffect.so vst/$basename.$EXT
  fi

  echo cp $i vst/$basename.csd
  cp $i vst/$basename.csd

done

# Special files
cp cabbage/Synths/bassline.snaps vst/
# cp cabbage/Synths/Clavinet.snaps vst/
# cp cabbage/Synths/TR-808_pattern.0.txt vst/

cd ..
