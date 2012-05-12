#!/bin/bash

set -e

if [ -d bin ]; then
  echo cd bin
  cd bin
else
  echo "Please run this script from the distrho root folder"
  exit
fi

FOLDERS=`find . -name \*.lv2`

for i in $FOLDERS; do
  echo cd $i
  cd $i
  echo "if [ ! -f ./manifest.ttl ]; then ../../../libs/lv2_ttl_generator ./*.so; fi"
  if [ ! -f ./manifest.ttl ]; then ../../../libs/lv2_ttl_generator ./*.so; fi
  echo cd ../..
  cd ../..
done
