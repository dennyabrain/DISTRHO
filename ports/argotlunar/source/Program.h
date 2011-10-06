#ifndef PROGRAM_H
#define PROGRAM_H

#include "juce.h"
#include "Debug.h"
#include "ParametersEnum.h"

class Program
{
public:
  Program();
  void init();

  String name;
  float parameters[NUMPARAMS - 1];
  int scale;
  ModSource matrix_source[3];
  ModDest matrix_dest[3];
  ModMode matrix_mode[3];
};

#endif //PROGRAMBANK_H
