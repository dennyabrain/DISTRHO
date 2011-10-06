#include "ProgramBank.h"


ProgramBank::ProgramBank(const int num_programs, Parameters* parameters)
{
  this->parameters = parameters;
  this->num_programs = num_programs;
  programs = new Program[num_programs];
  loadParametersFromProgram(0);
}

ProgramBank::~ProgramBank()
{
  delete[] programs;
}

void ProgramBank::saveParametersToProgram(int index)
{
  // internal parameters
  for (int i = 0; i < (NUMPARAMS - 1); i++)
    programs[index].parameters[i] = parameters->param[i];

  // external parameters
  programs[index].scale = parameters->scale;
  for (int i = 0; i < 3; i++) {
    programs[index].matrix_source[i] = parameters->matrix_source[i];
    programs[index].matrix_dest[i] = parameters->matrix_dest[i];
    programs[index].matrix_mode[i] = parameters->matrix_mode[i];
  }
}

void ProgramBank::loadParametersFromProgram(int index)
{
  // internal parameters
  for (int i = 0; i < (NUMPARAMS - 1); i++)
    parameters->param[i] = programs[index].parameters[i];

  // external parameters
  parameters->scale = programs[index].scale;
  for (int i = 0; i < 3; i++) {
    parameters->matrix_source[i] = programs[index].matrix_source[i];
    parameters->matrix_dest[i] = programs[index].matrix_dest[i];
    parameters->matrix_mode[i] = programs[index].matrix_mode[i];
  }
  parameters->initializeInternalParameters();
}

XmlElement* ProgramBank::getBank()
{
  XmlElement* program_bank = new XmlElement(T("ARGOTLUNAR2_BANK"));
  for (int i = 0; i < num_programs; i++)
    program_bank->addChildElement(getProgram(i));
  return program_bank;
}

void ProgramBank::setBank(XmlElement* bank_src)
{
  if (bank_src->hasTagName("ARGOTLUNAR2_BANK") == false)
    return;
  int i = 0;
  forEachXmlChildElement(*bank_src, program) {
    setProgram(i, program);
    i++;
  }
}

XmlElement* ProgramBank::getProgram(int index)
{
  XmlElement* program = new XmlElement("ARGOTLUNAR2_PROGRAM");
  // external parameters
  program->setAttribute(T("program_name"), programs[index].name);
  program->setAttribute(T("grains"), programs[index].parameters[kGrains]);
  program->setAttribute(T("mix"), programs[index].parameters[kMix]);
  program->setAttribute(T("input_gain"), programs[index].parameters[kIngain]);
  program->setAttribute(T("feedback"), programs[index].parameters[kFeedback]);
  program->setAttribute(T("amp"), programs[index].parameters[kAmp]);
  program->setAttribute(T("ampv"), programs[index].parameters[kAmpv]);
  program->setAttribute(T("pan"), programs[index].parameters[kPan]);
  program->setAttribute(T("panv"), programs[index].parameters[kPanv]);
  program->setAttribute(T("delay"), programs[index].parameters[kDelay]);
  program->setAttribute(T("delayv"), programs[index].parameters[kDelayv]);
  program->setAttribute(T("iot"), programs[index].parameters[kIot]);
  program->setAttribute(T("iotv"), programs[index].parameters[kIotv]);
  program->setAttribute(T("dur"), programs[index].parameters[kDur]);
  program->setAttribute(T("durv"), programs[index].parameters[kDurv]);
  program->setAttribute(T("trans"), programs[index].parameters[kTrans]);
  program->setAttribute(T("transv"), programs[index].parameters[kTransv]);
  program->setAttribute(T("gliss"), programs[index].parameters[kGliss]);
  program->setAttribute(T("glissv"), programs[index].parameters[kGlissv]);
  program->setAttribute(T("filter_type"), programs[index].parameters[kFtype]);
  program->setAttribute(T("ffreq"), programs[index].parameters[kFfreq]);
  program->setAttribute(T("ffreqv"), programs[index].parameters[kFfreqv]);
  program->setAttribute(T("fq"), programs[index].parameters[kFq]);
  program->setAttribute(T("fqv"), programs[index].parameters[kFqv]);
  program->setAttribute(T("env_type"), programs[index].parameters[kEnvType]);
  program->setAttribute(T("env_shape"), programs[index].parameters[kEnvSustain]);
  program->setAttribute(T("env_skew"), programs[index].parameters[kEnvSkew]);
  program->setAttribute(T("delay_quant"), programs[index].parameters[kDelayQuant]);
  program->setAttribute(T("dur_quant"), programs[index].parameters[kDurQuant]);
  program->setAttribute(T("iot_quant"), programs[index].parameters[kIotQuant]);
  program->setAttribute(T("trans_toggle"), programs[index].parameters[kTransToggle]);
  program->setAttribute(T("gliss_toggle"), programs[index].parameters[kGlissToggle]);
  program->setAttribute(T("freeze_toggle"), programs[index].parameters[kFreezeToggle]);
  program->setAttribute(T("scale_key"), programs[index].parameters[kScaleKey]);
  program->setAttribute(T("matrix_mod_1"), programs[index].parameters[kMatrixMod1]);
  program->setAttribute(T("matrix_mod_2"), programs[index].parameters[kMatrixMod1]);
  program->setAttribute(T("matrix_mod_3"), programs[index].parameters[kMatrixMod3]);
  // internal parameters
  program->setAttribute(T("scale"), programs[index].scale);
  program->setAttribute(T("matrix_src_1"), programs[index].matrix_source[0]);
  program->setAttribute(T("matrix_src_2"), programs[index].matrix_source[1]);
  program->setAttribute(T("matrix_src_3"), programs[index].matrix_source[2]);
  program->setAttribute(T("matrix_dest_1"), programs[index].matrix_dest[0]);
  program->setAttribute(T("matrix_dest_2"), programs[index].matrix_dest[1]);
  program->setAttribute(T("matrix_dest_3"), programs[index].matrix_dest[2]);
  program->setAttribute(T("matrix_mode_1"), programs[index].matrix_mode[0]);
  program->setAttribute(T("matrix_mode_2"), programs[index].matrix_mode[1]);
  program->setAttribute(T("matrix_mode_3"), programs[index].matrix_mode[2]);
  return program;
}

void ProgramBank::setProgram(int index, XmlElement* program_src)
{
  if (program_src->hasTagName("ARGOTLUNAR2_PROGRAM") == false)
    return;
  // external parameters
  programs[index].name = program_src->getStringAttribute(T("program_name"));
  programs[index].parameters[kGrains] = (float)program_src->getDoubleAttribute(T("grains"));
  programs[index].parameters[kMix] = (float)program_src->getDoubleAttribute(T("mix"));
  programs[index].parameters[kIngain] = (float)program_src->getDoubleAttribute(T("input_gain"));
  programs[index].parameters[kFeedback] = (float)program_src->getDoubleAttribute(T("feedback"));
  programs[index].parameters[kAmp] = (float)program_src->getDoubleAttribute(T("amp"));
  programs[index].parameters[kAmpv] = (float)program_src->getDoubleAttribute(T("ampv"));
  programs[index].parameters[kPan] = (float)program_src->getDoubleAttribute(T("pan"));
  programs[index].parameters[kPanv] = (float)program_src->getDoubleAttribute(T("panv"));
  programs[index].parameters[kDelay] = (float)program_src->getDoubleAttribute(T("delay"));
  programs[index].parameters[kDelayv] = (float)program_src->getDoubleAttribute(T("delayv"));
  programs[index].parameters[kIot] = (float)program_src->getDoubleAttribute(T("iot"));
  programs[index].parameters[kIotv] = (float)program_src->getDoubleAttribute(T("iotv"));
  programs[index].parameters[kDur] = (float)program_src->getDoubleAttribute(T("dur"));
  programs[index].parameters[kDurv] = (float)program_src->getDoubleAttribute(T("durv"));
  programs[index].parameters[kTrans] = (float)program_src->getDoubleAttribute(T("trans"));
  programs[index].parameters[kTransv] = (float)program_src->getDoubleAttribute(T("transv"));
  programs[index].parameters[kGliss] = (float)program_src->getDoubleAttribute(T("gliss"));
  programs[index].parameters[kGlissv] = (float)program_src->getDoubleAttribute(T("glissv"));
  programs[index].parameters[kFfreq] = (float)program_src->getDoubleAttribute(T("ffreq"));
  programs[index].parameters[kFfreqv] = (float)program_src->getDoubleAttribute(T("ffreqv"));
  programs[index].parameters[kFtype] = (float)program_src->getDoubleAttribute(T("filter_type"));
  programs[index].parameters[kFq] = (float)program_src->getDoubleAttribute(T("fq"));
  programs[index].parameters[kFqv] = (float)program_src->getDoubleAttribute(T("fqv"));
  programs[index].parameters[kEnvType] = (float)program_src->getDoubleAttribute(T("env_type"));
  programs[index].parameters[kEnvSustain] = (float)program_src->getDoubleAttribute(T("env_shape"));
  programs[index].parameters[kEnvSkew] = (float)program_src->getDoubleAttribute(T("env_skew"));
  programs[index].parameters[kDelayQuant] = (float)program_src->getDoubleAttribute(T("delay_quant"));
  programs[index].parameters[kDurQuant] = (float)program_src->getDoubleAttribute(T("dur_quant"));
  programs[index].parameters[kIotQuant] = (float)program_src->getDoubleAttribute(T("iot_quant"));
  programs[index].parameters[kTransToggle] = (float)program_src->getDoubleAttribute(T("trans_toggle"));
  programs[index].parameters[kGlissToggle] = (float)program_src->getDoubleAttribute(T("gliss_toggle"));
  programs[index].parameters[kFreezeToggle] = (float)program_src->getDoubleAttribute(T("freeze_toggle"));
  programs[index].parameters[kScaleKey] = (float)program_src->getDoubleAttribute(T("scale_key"));
  programs[index].parameters[kMatrixMod1] = (float)program_src->getDoubleAttribute(T("matrix_mod_1"));
  programs[index].parameters[kMatrixMod2] = (float)program_src->getDoubleAttribute(T("matrix_mod_2"));
  programs[index].parameters[kMatrixMod3] = (float)program_src->getDoubleAttribute(T("matrix_mod_3"));
  // internal parameters
  programs[index].scale = program_src->getIntAttribute(T("scale"));
  programs[index].matrix_source[0] = static_cast<ModSource>(program_src->getIntAttribute(T("matrix_src_1")));
  programs[index].matrix_source[1] = static_cast<ModSource>(program_src->getIntAttribute(T("matrix_src_2")));
  programs[index].matrix_source[2] = static_cast<ModSource>(program_src->getIntAttribute(T("matrix_src_3")));
  programs[index].matrix_dest[0] = static_cast<ModDest>(program_src->getIntAttribute(T("matrix_dest_1")));
  programs[index].matrix_dest[1] = static_cast<ModDest>(program_src->getIntAttribute(T("matrix_dest_2")));
  programs[index].matrix_dest[2] = static_cast<ModDest>(program_src->getIntAttribute(T("matrix_dest_3")));
  programs[index].matrix_mode[0] = static_cast<ModMode>(program_src->getIntAttribute(T("matrix_mode_1")));
  programs[index].matrix_mode[1] = static_cast<ModMode>(program_src->getIntAttribute(T("matrix_mode_2")));
  programs[index].matrix_mode[2] = static_cast<ModMode>(program_src->getIntAttribute(T("matrix_mode_3")));
}

void ProgramBank::initProgram(int index)
{
  programs[index].init();
}

const String ProgramBank::getProgramName(int index)
{
  return programs[index].name;
}

void ProgramBank::setProgramName(int index, const String new_name)
{
  programs[index].name = new_name;
}

