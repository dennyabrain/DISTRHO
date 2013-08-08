#!/bin/bash

set -e

LINUX=0
MAC=0
MINGW=0

if [ "$1" = "" ]; then
  echo "usage: $0 linux|mac|mingw"
  exit
fi

if [ "$1" = "linux" ]; then
  LINUX=1
elif [ "$1" = "mac" ]; then
  MAC=1
elif [ "$1" = "mingw" ]; then
  MINGW=1
else
  echo "parameter must be linux, mac or mingw"
  exit
fi

if [ -d ../libs ]; then
  cd ..
fi

run_premake()
{
  premake --os $1 --target gnu --cc gcc
  sed "s/\$(LDFLAGS)/\$(LDFLAGS) \$(LDFLAGS)/" -i `find . -name \*.make`
}

# ------------------------------------------------------------------------------------------------------------

FILES=`find libs -name premake.lua`

for i in $FILES; do
  FOLDER=`echo $i | awk sub'("/premake.lua","")'`

  cd $FOLDER

  if [ $LINUX = 1 ]; then
      run_premake "linux"
  elif [ $MAC = 1 ]; then
      run_premake "macosx"
  elif [ $MINGW = 1 ]; then
      run_premake "windows"
  fi

  if [ -d ../libs ]; then
    cd ..
  elif [ -d ../../libs ]; then
    cd ../..
  elif [ -d ../../../libs ]; then
    cd ../../..
  else
    cd ../../../..
  fi
done
