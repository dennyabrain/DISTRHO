// distrho vst redirect handler

#include "d_vst.h"

extern AudioEffect* createEffectInstance(audioMasterCallback audioMaster);

DistrhoPluginBase* createDistrhoPlugin()
{
   return createEffectInstance(nullptr);
}
