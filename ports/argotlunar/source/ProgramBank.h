#ifndef PROGRAMBANK_H
#define PROGRAMBANK_H

#include "juce.h"
#include "Debug.h"
#include "Program.h"
#include "Parameters.h"

class Parameters;
class Program;

class ProgramBank
{
public:
  ProgramBank(const int num_programs, Parameters* parameters);
  ~ProgramBank();
  void initProgram(int index);
  void loadParametersFromProgram(int index);
  void saveParametersToProgram(int index);
  XmlElement* getBank();
  void setBank(XmlElement* bank_src);
  XmlElement* getProgram(int index);
  void setProgram(int index, XmlElement* program_src);
  const String getProgramName(int index);
  void setProgramName(int index, const String new_name);

private:
  int num_programs;
  Program* programs; //[NUMPROGRAMS];
  Parameters* parameters;
  XmlElement* bank;
};

#endif //PROGRAMBANK_H
