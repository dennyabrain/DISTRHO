#!/bin/bash

set -e

if [ -d bin ]; then
  echo cd bin
  cd bin
else
  echo "Please run this script from the distrho root folder"
  exit
fi

GEN=../../../libs/lv2_ttl_generator
EXT=so

if [ -f ../libs/lv2_ttl_generator.exe ]; then
  GEN=../../../libs/lv2_ttl_generator.exe
  EXT=dll
fi

FOLDERS=`find . -name \*.lv2`

for i in $FOLDERS; do
  echo cd $i
  cd $i
  echo "if [ ! -f ./manifest.ttl ]; then $GEN ./*.$EXT; fi"
  if [ ! -f ./manifest.ttl ]; then $GEN ./*.$EXT; fi
  echo cd ../..
  cd ../..
done
