#!/bin/bash

set -e

if [ -d bin ]; then
  cd bin
else
  echo "Please run this script from the distrho root folder"
  exit
fi

PWD=`pwd`

if [ -f $PWD/../libs/lv2_ttl_generator.exe ]; then
  GEN=$PWD/../libs/lv2_ttl_generator.exe
  EXT=dll
else
  GEN=$PWD/../libs/lv2_ttl_generator
  EXT=so
fi

FOLDERS=`find ./lv2/ -name \*.lv2`

for i in $FOLDERS; do
  cd $i
  $GEN ./*.$EXT
  cd ../..
done

# Remove cabbage logs
rm -f $PWD/lv2/cabbage*.lv2/CabbageLog.txt
