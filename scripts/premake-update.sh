#!/bin/bash

set -e

LINUX=0
MAC=0
WINDOWS=0

if [ "$1" = "" ]; then
  echo "usage: $0 linux|mac|windows"
  exit
fi

if [ "$1" = "linux" ]; then
  LINUX=1
elif [ "$1" = "mac" ]; then
  MAC=1
elif [ "$1" = "windows" ]; then
  WINDOWS=1
else
  echo "parameter must be linux, mac or windows"
  exit
fi

if [ -d ../libs ]; then
  echo cd ..
  cd ..
fi

# ------------------------------------------------------------------------------------------------------------

FILES=`find . -name premake.lua`

for i in $FILES; do
  FOLDER=`echo $i | awk sub'("/premake.lua","")'`

  echo cd $FOLDER
  cd $FOLDER

  if [ $LINUX = 1 ]; then

    echo premake --os linux --target gnu --cc gcc
    premake --os linux --target gnu --cc gcc

    echo sed \""s/\\\$(LDFLAGS)/\\\$(LDFLAGS) \\\$(LDFLAGS)/\"" -i `find . -name \*.make`
    sed "s/\$(LDFLAGS)/\$(LDFLAGS) \$(LDFLAGS)/" -i `find . -name \*.make`

  elif [ $MAC = 1 ]; then

    echo premake --os macosx --target gnu --cc gcc
    premake --os macosx --target gnu --cc gcc

  elif [ $WINDOWS = 1 ]; then

    echo premake --os windows --target vs2005
    premake --os windows --target vs2005

    echo sed \""s/SubSystem=\\\"1\\\"/SubSystem=\\\"2\\\"/\"" -i `find . -name \*.vcproj`
    sed "s/SubSystem=\"1\"/SubSystem=\"2\"/" -i `find . -name \*.vcproj`

    echo sed \""s/\t\t\t\tEntryPointSymbol=\\\"mainCRTStartup\\\"//\"" -i `find . -name \*.vcproj`
    sed "s/\t\t\t\tEntryPointSymbol=\"mainCRTStartup\"//" -i `find . -name \*.vcproj`

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

  echo sed \""s/ = lib/ = /\"" -i Makefile
  sed "s/ = lib/ = /" -i Makefile

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
