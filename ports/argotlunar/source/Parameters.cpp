#include "Parameters.h"

Parameters::Parameters(Plugin* plugin, const int internal_block_size)
{
  this->plugin = plugin;
  time_quantizer = new TimeQuantizer(this, internal_block_size);
  delay_coeff = sqrt(plugin->granulator->kBufferSeconds * 1000.0f);
  iot_coeff = log10(kMaxIot * 1.0f);
  dur_coeff = log10(kMaxDuration * 1.0f);
  param = new float[NUMPARAMS];
  for (int i = 0; i < NUMPARAMS; i++) {
    param[i]= 0.0f;
  }
  setParametersSavedState(true);
  quantization_disabled = false;
}

Parameters::~Parameters()
{
  delete[] param;
}

void Parameters::initializeInternalParameters()
{
  for (int i = 0; i < (NUMPARAMS - 2); i++) {
    setParameter(i, param[i], true);
  }
  setParametersSavedState(true);
}

void Parameters::setParameter(int index, float new_value, bool initializing)
{
  if (param[index] != new_value || initializing == true) {

    param[index] = new_value;

    switch(index) {
    case kMix:
      dry_mix = 1.0f - new_value;
      break;
    case kAmp:
    case kAmpv:
      amp_max = param[kAmp] + param[kAmpv];
      if (amp_max > 1.0f)
        amp_max = 1.0f;
      break;
    case kPan:
    case kPanv:
      pan_min = param[kPan] - (0.5f * param[kPanv]);
      pan_max = param[kPan] + (0.5f * param[kPanv]);
      if (pan_min < 0.0f)
        pan_min = 0.0f;
      if (pan_max > 1.0f)
        pan_max = 1.0f;
      break;
    case kDelay:
    case kDelayv:
      delay_max = param[kDelay] + param[kDelayv];
      if (delay_max > 1.0f)
        delay_max = 1.0f;
      break;
    case kIot:
    case kIotv:
      iot_max = param[kIot] + param[kIotv];
      if (iot_max > 1.0f)
        iot_max = 1.0f;
      break;
    case kDur:
    case kDurv:
      dur_max = param[kDur] + param[kDurv];
      if (dur_max > 1.0f)
        dur_max = 1.0f;
      break;
    case kTrans:
    case kTransv:
      trans_min = param[kTrans] - (0.5f * param[kTransv]);
      trans_max = param[kTrans] + (0.5f * param[kTransv]);
      if (trans_min < 0.0f)
        trans_min = 0.0f;
      if (trans_max > 1.0f)
        trans_max = 1.0f;
      break;
    case kGliss:
    case kGlissv:
      gliss_min = param[kGliss] - (0.5f * param[kGlissv]);
      gliss_max = param[kGliss] + (0.5f * param[kGlissv]);
      if (gliss_min < 0.0f)
        gliss_min = 0.0f;
      if (gliss_max > 1.0f)
        gliss_max = 1.0f;
      break;
    case kFfreq:
    case kFfreqv:
      ffreq_max = param[kFfreq] + param[kFfreqv];
      if (ffreq_max > 1.0f)
        ffreq_max = 1.0f;
      break;
    case kFq:
    case kFqv:
      fq_max = param[kFq] + param[kFqv];
      if (fq_max > 1.0f)
        fq_max = 1.0f;
      break;
    case kFtype:
      filter_type = MathFunc::roundFtoI(new_value * 6.0f);
      break;
    case kEnvType:
      env_type = MathFunc::roundFtoI(new_value * 2.0f);
      break;
    case kEnvSustain:
      if (param[kEnvSustain] < 0.05f) {
        param[kEnvSustain] = 0.05f;
      } else if (param[kEnvSustain] > 0.95f) {
        param[kEnvSustain] = 0.95f;
      }
      break;
    case kEnvSkew:
      if (param[kEnvSkew] < 0.05f) {
        param[kEnvSkew] = 0.05f;
      } else if (param[kEnvSkew] > 0.95f) {
        param[kEnvSkew] = 0.95f;
      }
      break;
    case kGrains:
      selected_grains = MathFunc::roundFtoI(new_value
        * plugin->granulator->kMaxGrains);
      break;
    case kDelayQuant:
      if (quantization_disabled)
        param[kDelayQuant] = 1.0f/NumQuantModes::delay;
      time_quantizer->setQuantizeMode(kDelayQuant, param[kDelayQuant]);
      break;
    case kIotQuant:
      if (quantization_disabled)
        param[kIotQuant] = 1.0f/NumQuantModes::iot;
      time_quantizer->setQuantizeMode(kIotQuant, param[kIotQuant]);
      break;
    case kDurQuant:
      if (quantization_disabled)
        param[kDurQuant] = 1.0f/NumQuantModes::dur;
      time_quantizer->setQuantizeMode(kDurQuant, param[kDurQuant]);
      break;
    case kScaleKey:
      scale_key = MathFunc::roundFtoI(new_value * 12); // Should be '11'. Keeping '12' to maintain compatibility
      if(scale_key == 12) scale_key--;
      break;
    case kFreezeToggle:
      freeze = (new_value == 0.0f) ? false : true;
      break;
    }

    if (initializing == false) {
      setParametersSavedState(false);
    }
  }
}

const String Parameters::getParameterName(int index)
{
  switch (index) {
  case kMix:
    return T("mix");
  case kIngain:
    return T("input_gain");
  case kAmp:
    return T("amp");
  case kAmpv:
    return T("ampv");
  case kPan:
    return T("pan");
  case kPanv:
    return T("panv");
  case kDelay:
    return T("delay");
  case kDelayv:
    return T("delayv");
  case kFeedback:
    return T("feedback");
  case kTrans:
    return T("trans");
  case kTransv:
    return T("transv");
  case kGliss:
    return T("gliss");
  case kGlissv:
    return T("glissv");
  case kIot:
    return T("IOT");
  case kIotv:
    return T("IOTv");
  case kDur:
    return T("dur");
  case kDurv:
    return T("durv");
  case kFfreq:
    return T("ffreq");
  case kFfreqv:
    return T("ffreqv");
  case kFq:
    return T("fq");
  case kFqv:
    return T("fqv");
  case kFtype:
    return T("filter_type");
  case kGrains:
    return T("grains");
  case kEnvSustain:
    return T("env_sustain");
  case kEnvSkew:
    return T("env_skew");
  case kEnvType:
    return T("env_type");
  case kDelayQuant:
    return T("delay_quantize");
  case kDurQuant:
    return T("dur_quantize");
  case kIotQuant:
    return T("IOT_quantize");
  case kTransToggle:
    return T("trans_toggle");
  case kGlissToggle:
    return T("gliss_toggle");
  case kFreezeToggle:
    return T("freeze_toggle");
  case kScaleKey:
    return T("scale_key");
  case kMatrixMod1:
    return T("matrix_mod_1");
  case kMatrixMod2:
    return T("matrix_mod_2");
  case kMatrixMod3:
    return T("matrix_mod_3");
  case kProgram:
    return T("program");
  }
  return String::empty;
}

const String Parameters::getParameterText(int index)
{
  String text;
  switch (index)
  {
  case kMix:
    return String(dry_mix, 2) + " dry | " + String(param[kMix], 2) + " wet";
  case kIngain:
    return getDecibelString(param[kIngain]);
  case kFeedback:
    return getDecibelString(param[kFeedback]);
  case kAmp:
  case kAmpv:
    if (param[kAmp] == amp_max) {
      return getDecibelString(param[kAmp]);
    } else {
      return getDecibelString(param[kAmp]) + ", " + getDecibelString(amp_max);
    }
  case kPan:
  case kPanv:
    if (pan_min == pan_max) {
      return getPanString(pan_min);
    } else {
      return getPanString(pan_min) + ", " + getPanString(pan_max);
    }
  case kDelay:
  case kDelayv:
    if (param[kDelay] == delay_max) {
      return getDelayString(param[kDelay]);
    } else {
      return getDelayString(param[kDelay]) + ", " + getDelayString(delay_max);
    }
  case kIot:
  case kIotv:
    if (param[kIot] == iot_max) {
      return getIOTString(param[kIot]);
    } else {
      return getIOTString(param[kIot]) + ", " + getIOTString(iot_max);
    }
  case kDur:
  case kDurv:
    if (param[kDur] == dur_max) {
      return getDurString(param[kDur]);
    } else {
      return getDurString(param[kDur]) + ", " + getDurString(dur_max);
    }
  case kTrans:
  case kTransv: {
    if (trans_min == trans_max) {
      return getTransString(trans_min);
    } else {
      text = getTransString(trans_min) + ", " + getTransString(trans_max);
      if (index == kTransv)
        text += " [+- " + String(static_cast<int>(param[kTransv] * 2400.0f)) + " c.]";
      return text;
    }
  }
  case kGliss:
  case kGlissv: {
    if (gliss_min == gliss_max) {
      return getGlissString(gliss_min);
    } else {
      text = getGlissString(gliss_min) + ", " + getGlissString(gliss_max);
      if (index == kGlissv)
        text += " [+- " + String(static_cast<int>(param[kGlissv] * 2400.0f)) + " c.]";
      return text;
    }
  }
  case kFfreq:
  case kFfreqv:
    if (param[kFfreq] == ffreq_max) {
      return getFFreqString(param[kFfreq]);
    } else {
      return getFFreqString(param[kFfreq]) + ", " + getFFreqString(ffreq_max);
    }
  case kFq:
  case kFqv:
    if (param[kFq] == fq_max) {
      return String(param[kFq], 2) + " Q";
    } else {
      return String(param[kFq], 2) + " Q, " + String(fq_max, 2) + " Q";
    }
  case kFtype:
    return getFilterTypeString();
  case kEnvSustain:
    return String(param[kEnvSustain] * 100.0f, 1);
  case kEnvSkew: {
    float skew = (param[kEnvSkew] - 0.5f) * 200.0f;
    if (skew <= 0.0f) {
      return String(skew, 1);
    } else {
      return "+" + String(skew,1);
    }
  }
  case kEnvType:
    return getEnvTypeString();
  case kTransToggle:
    return getToggleString(kTransToggle);
  case kGlissToggle:
    return getToggleString(kGlissToggle);
  case kFreezeToggle:
    return getToggleString(kFreezeToggle);
  case kGrains:
    return String(MathFunc::roundFtoI(param[kGrains]
                  * plugin->granulator->kMaxGrains)) + " grains";
  case kScaleKey:
    return getScaleKeyString();
  case kMatrixMod1:
    return getMatrixmodString(kMatrixMod1);
  case kMatrixMod2:
    return getMatrixmodString(kMatrixMod2);
  case kMatrixMod3:
    return getMatrixmodString(kMatrixMod3);
  case kDelayQuant:
  return time_quantizer->getQuantModeString(kDelayQuant);
  case kDurQuant:
  return time_quantizer->getQuantModeString(kDurQuant);
  case kIotQuant:
  return time_quantizer->getQuantModeString(kIotQuant);
  }
  return "";
}

void Parameters::setQuantizationDisabled()
{
  quantization_disabled = true;
}

String Parameters::getPercentString(float value)
{
  return String(value * 100, 1) + "% ";
}

String Parameters::getEnvTypeString()
{
  String types[] = {"raised cosine bell", "parabola", "triangle"};
  int index = MathFunc::roundFtoI(param[kEnvType] * 2.0f);
  return types[index];
}

String Parameters::getFilterTypeString()
{
  String types[] = {"off", "band", "low", "high", "notch", "comb", "random"};
  int index = MathFunc::roundFtoI(param[kFtype] * 6.0f);
  return types[index];
}

String Parameters::getScaleKeyString()
{
  String keys[] = {"C", "C#", "D", "D#", "E", "F",
                   "F#", "G", "G#", "A", "A#", "B"};
  return keys[scale_key];
}

String Parameters::getMatrixmodString(int parameter)
{
  if (param[parameter] > 0.5f) {
    return "+" + String((int)((param[parameter] - 0.5f) * 200.0f)) + "%";
  } else if (param[parameter] < 0.5f) {
    return String((int)((param[parameter] - 0.5f) * 200.0f)) + "%";
  } else {
    return "0%";
  }
}

String Parameters::getDecibelString(float value)
{
  if (value < 0.006f) {
    return "-inf";
  } else {
    return String(log10(pow(value, 20)), 1) + " dB";
  }
}

String Parameters::getToggleString(int parameter)
{
  return (param[parameter] == 0.0f) ? "off" : "on";
}

String Parameters::getPanString(float value)
{
  if (value == 0.5f) {
    return "C";
  } else if (value < 0.5f) {
    return String((value - 0.5f) * -2.0f, 2) + "L";
  } else if (value > 0.5f) {
    return String((value - 0.5f) * 2.0f, 2) + "R";
  }
  return "";
}

float Parameters::getDelayMilliseconds(float value)
{
  return (value * delay_coeff) * (value * delay_coeff);
}

String Parameters::getDelayString(float value)
{
  QuantizeMode del_quant_mode = time_quantizer->getQuantizeMode(kDelayQuant);
  if (del_quant_mode == QUANT_MS) {
    return String(getDelayMilliseconds(value), 1) + " ms";
  }
  else return time_quantizer->getQuantValueString(kDelayQuant, value);
}

float Parameters::getIOTMilliseconds(float value)
{
  return static_cast<float>(pow(10.0f, value * iot_coeff));
}

String Parameters::getIOTString(float value)
{
  if (time_quantizer->getQuantizeMode(kIotQuant) == QUANT_MS) {
    return String(getIOTMilliseconds(value), 1) + " ms";
  }
  else return time_quantizer->getQuantValueString(kIotQuant, value);
}

float Parameters::getDurMilliseconds(float value)
{
  return static_cast<float>(pow(10.0f, dur_coeff + (value * 2.0f)));
}

String Parameters::getDurString(float value)
{
  QuantizeMode dur_quant_mode = time_quantizer->getQuantizeMode(kDurQuant);
  if (dur_quant_mode == QUANT_MS || dur_quant_mode == QUANT_MS_LONG) {
    float length = getDurMilliseconds(value);
    if (dur_quant_mode == QUANT_MS_LONG)
      length *= 10.0f;
    return String(length, 1) + " ms";
  }
  else return time_quantizer->getQuantValueString(kDurQuant, value);
}

String Parameters::getTransString(float value)
{
  if (value == 0.5f) {
    return "0";
  } else {
    if (scale == 0) {
      return String(static_cast<int>((value - 0.5f) * 4800.0f)) + " c.";
    } else {
      int semitones = MathFunc::roundFtoI((value - 0.5f) * 48.0f);
      return String(semitones);
    }
  }
}

String Parameters::getGlissString(float value)
{
  if (value == 0.5f) {
    return "0";
  } else {
    return String(static_cast<int>((value - 0.5f) * 4800.0f)) + " c.";
  }
}

String Parameters::getFFreqString(float value)
{
  return String(pow(10.0, value * 3.0) * 22.05f, 1) + " hz";
}

int Parameters::getScale()
{
  return scale;
}

int Parameters::getMatrixDest(int index)
{
  return matrix_dest[index] + 1;
}

int Parameters::getMatrixSource(int index)
{
  return static_cast<int>(matrix_source[index] + 1);
}

int Parameters::getMatrixMode(int index)
{
  return static_cast<int>(matrix_mode[index]);
}

void Parameters::setMatrixSource(int index, int param)
{
  param--;
  if (matrix_source[index] != param) {
    matrix_source[index] = static_cast<ModSource>(param);
    setParametersSavedState(false);
  }
}

void Parameters::setMatrixDest(int index, int param)
{
  param--;
  if (matrix_dest[index] != param) {
    matrix_dest[index] = static_cast<ModDest>(param);
    setParametersSavedState(false);
  }
}

void Parameters::setMatrixMode(int index, int param)
{
  if (matrix_mode[index] != param) {
    matrix_mode[index] = static_cast<ModMode>(param);
    setParametersSavedState(false);
  }
}

void Parameters::setScale(int index)
{
  if (scale != index) {
    scale = index;
    setParametersSavedState(false);
  }
}

void Parameters::setParametersSavedState(bool state)
{
  plugin->setSavedState(state);
}

float Parameters::getSampleRate()
{
  return samplerate;
}

void Parameters::setSampleRate(float samplerate)
{
  this->samplerate = samplerate;
  time_quantizer->setSampleRate(samplerate);
}

