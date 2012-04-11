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
  echo ../../libs/lv2_ttl_generator ./*.so
  ../../libs/lv2_ttl_generator ./*.so
  echo cd ..
  cd ..
done
