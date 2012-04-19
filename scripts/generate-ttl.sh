#!/bin/bash

set -e

if [ -d ../bin ]; then
  echo cd ..
  cd ..
fi

if [ -d bin ]; then
  echo cd bin
  cd bin
fi

FOLDERS=`find . -name \*.lv2`

for i in $FOLDERS; do
  echo cd $i
  cd $i
  echo "if [ ! -f ./manifest.ttl ]; then ../../libs/lv2_ttl_generator ./*.so; fi"
  if [ ! -f ./manifest.ttl ]; then ../../libs/lv2_ttl_generator ./*.so; fi
  echo cd ..
  cd ..
done
