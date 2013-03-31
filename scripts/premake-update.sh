#!/bin/bash

set -e

LINUX=0
MAC=0
MINGW=0

if [ "$1" = "" ]; then
  echo "usage: $0 linux|mac|windows|mingw"
  exit
fi

if [ "$1" = "linux" ]; then
  LINUX=1
elif [ "$1" = "mac" ]; then
  MAC=1
elif [ "$1" = "mingw" ]; then
  MINGW=1
else
  echo "parameter must be linux, mac or windows"
  exit
fi

if [ -d ../libs ]; then
  echo cd ..
  cd ..
fi

run_premake()
{
  echo premake --os $1 --target gnu --cc gcc
  premake --os $1 --target gnu --cc gcc

  echo sed \""s/\\\$(LDFLAGS)/\\\$(LDFLAGS) \\\$(LDFLAGS)/\"" -i `find . -name \*.make`
  sed "s/\$(LDFLAGS)/\$(LDFLAGS) \$(LDFLAGS)/" -i `find . -name \*.make`
}

# ------------------------------------------------------------------------------------------------------------

FILES=`find . -name premake.lua`

for i in $FILES; do
  FOLDER=`echo $i | awk sub'("/premake.lua","")'`

  echo cd $FOLDER
  cd $FOLDER

  if [ $LINUX = 1 ]; then
      run_premake "linux"
  elif [ $MAC = 1 ]; then
      run_premake "macosx"
  elif [ $MINGW = 1 ]; then
      run_premake "windows"
  fi

  if [ -d ../libs ]; then
    echo cd ..
    cd ..
  elif [ -d ../../libs ]; then
    echo cd ../..
    cd ../..
  elif [ -d ../../../libs ]; then
    echo cd ../../..
    cd ../../..
  else
    echo cd ../../../..
    cd ../../../..
  fi
done

# ------------------------------------------------------------------------------------------------------------

FILES=`find . -name qmake.pro`

for i in $FILES; do
  FOLDER=`echo $i | awk sub'("/qmake.pro","")'`

  echo cd $FOLDER
  cd $FOLDER

  echo qmake qmake.pro
  qmake qmake.pro

  if [ -d ../libs ]; then
    echo cd ..
    cd ..
  elif [ -d ../../libs ]; then
    echo cd ../..
    cd ../..
  elif [ -d ../../../libs ]; then
    echo cd ../../..
    cd ../../..
  else
    echo cd ../../../..
    cd ../../../..
  fi
done
