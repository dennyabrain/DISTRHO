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
  echo sed "s/\\\$(LDFLAGS)/\\\$(LDFLAGS) \\\$(LDFLAGS)/" -i `find . -name \*.make`
  sed "s/\$(LDFLAGS)/\$(LDFLAGS) \$(LDFLAGS)/" -i `find . -name \*.make`
  if [ -d ../libs ]; then
    echo cd ..
    cd ..
  elif [ -d ../../libs ]; then
    echo cd ../..
    cd ../..
  else
    echo cd ../../..
    cd ../../..
  fi
done
