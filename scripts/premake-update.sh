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

  echo premake --os windows --target vs2005
  premake --os windows --target vs2005

  echo sed "s/SubSystem=\\\"1\\\"/SubSystem=\\\"2\\\"/" -i `find . -name \*.vcproj`
  sed "s/SubSystem=\"1\"/SubSystem=\"2\"/" -i `find . -name \*.vcproj`

  echo sed "s/\t\t\t\tEntryPointSymbol=\\\"mainCRTStartup\\\"//" -i `find . -name \*.vcproj`
  sed "s/\t\t\t\tEntryPointSymbol=\"mainCRTStartup\"//" -i `find . -name \*.vcproj`

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
  elif [ -d ../../../libs ]; then
    echo cd ../../..
    cd ../../..
  else
    echo cd ../../../..
    cd ../../../..
  fi
done
