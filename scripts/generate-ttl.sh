#!/bin/bash

set -e

if [ -d bin ]; then
  echo cd bin
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

export LD_LIBRARY_PATH=$PWD/../libs/

FOLDERS=`find . -name \*.lv2`

for i in $FOLDERS; do
  cd $i
  $GEN ./*.$EXT
  cd ../..
done

# Remove cabbage logs
rm -f lv2/cabbage_*.lv2/CabbageLog.txt
