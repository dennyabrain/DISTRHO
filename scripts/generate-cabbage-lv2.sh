#!/bin/bash

set -e

if [ -d bin ]; then
  echo cd bin
  cd bin
else
  echo "Please run this script from the distrho root folder"
  exit
fi

if [ ! -f standalone/CabbagePluginSynthLv2.so ]; then exit 0; fi
if [ ! -f standalone/CabbagePluginEffectLv2.so ]; then exit 0; fi

mkdir -p lv2

GEN=../../../libs/lv2_ttl_generator
EXT=so

if [ -f ../libs/lv2_ttl_generator.exe ]; then
  GEN=../../../libs/lv2_ttl_generator.exe
  EXT=dll
fi

FILES=`find ./cabbage -name \*.csd`

for i in $FILES; do
  #shortname=`echo $i | awk 'sub("./cabbage/","")' | awk 'sub("/","\n")' | tail -n 1 | awk 'sub(".csd","")'`
  basename=`echo $i | awk 'sub("./cabbage/","cabbage_")' | awk 'sub("/","-")' | awk 'sub(".csd","")'`
  lv2dir=`echo "./lv2/"$basename".lv2/"`

  echo mkdir -p $lv2dir
  mkdir -p $lv2dir

  if ( echo $i | grep "./cabbage/Synths/" > /dev/null ); then
    echo cp `pwd`/standalone/CabbagePluginSynthLv2.so $lv2dir/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginSynthLv2.so $lv2dir/$basename.$EXT
  else
    echo cp `pwd`/standalone/CabbagePluginEffectLv2.so $lv2dir/$basename.$EXT
    cp `pwd`/standalone/CabbagePluginEffectLv2.so $lv2dir/$basename.$EXT
  fi

  echo cp $i $lv2dir/$basename.csd
  cp $i $lv2dir/$basename.csd

done

# Special files
cp cabbage/Synths/bassline.snaps lv2/cabbage_Synths-bassline.lv2/
# cp cabbage/Synths/Clavinet.snaps lv2/cabbage_Synths-Clavinet.lv2/
# cp cabbage/Synths/TR-808_pattern.0.txt lv2/cabbage_Synths-TR-808.lv2/

cd ..
