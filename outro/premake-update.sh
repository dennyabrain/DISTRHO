#!/bin/bash

set -e

if [ -d ../libs ]; then
  echo cd ..
  cd ..
fi

FILES=`find . -name premake.lua`

for i in $FILES; do
  FOLDER=`echo $i | awk sub'("/premake.lua","")'`
  echo cd $FOLDER
  cd $FOLDER
  echo premake --os linux --target gnu --cc gcc
  premake --os linux --target gnu --cc gcc
  echo cd ../../..
  cd ../../..
done
