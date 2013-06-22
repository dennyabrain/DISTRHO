#!/bin/bash

set -e

if [ -d bin ]; then
  echo cd bin
  cd bin
else
  echo "Please run this script from the distrho root folder"
  exit
fi

mkdir -p vst

if [ -f ../libs/lv2_ttl_generator.exe ]; then
  EXT=dll
else
  EXT=so
fi

FILES=`find ./cabbage -name \*.csd`

for i in $FILES; do
  basename=`echo $i | awk 'sub("./cabbage/","cabbage_")' | awk 'sub("/","-")' | awk 'sub(".csd","")'`

  if ( echo $i | grep "./cabbage/Synths/" > /dev/null ); then
    echo cp `pwd`/standalone/CabbagePluginSynth.so vst/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginSynth.so vst/$basename.$EXT
  else
    echo cp `pwd`/standalone/CabbagePluginEffect.so vst/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginEffect.so vst/$basename.$EXT
  fi

  echo cp $i vst/$basename.csd
  cp $i vst/$basename.csd

done

# Special files
cp cabbage/Synths/bassline.snaps vst/
cp cabbage/Synths/Clavinet.snaps vst/
cp cabbage/Synths/TR-808_pattern.0.txt vst/

cd ..