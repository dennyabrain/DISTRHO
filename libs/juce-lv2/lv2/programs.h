/*****************************************************************************
 *
 *  This work is in public domain.
 *
 *  This file is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  If you have questions, contact Filipe Coelho <falktx@gmail.com> or
 *  ask for falktx in #lad channel, FreeNode IRC network.
 *
 *****************************************************************************/

#ifndef LV2_PROGRAMS_H
#define LV2_PROGRAMS_H

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

/** LV2 extension ... */
#define LV2_PROGRAMS_URI                        "http://kxstudio.sourceforge.net/ns/lv2_programs"
#define LV2_PROGRAMS_EXTENSION_DATA_URI         "http://kxstudio.sourceforge.net/ns/lv2_programs#extensionData"

#ifdef __cplusplus
extern "C" {
#endif

/**
   Programs Extension Data.

   When the plugin's extension_data is called with argument LV2_PROGRAMS_EXTENSION_DATA_URI,
   the plugin MUST return an LV2_Programs_Feature structure, which remains valid for the
   lifetime of the plugin.
*/
typedef struct {
  /**
   * TODO
   */
  unsigned int (*get_program_count)(LV2_Handle instance);

  /**
   * TODO
   */
  const char* (*get_program_name)(LV2_Handle instance, unsigned int program);

  /**
   * TODO
   */
  int (*set_program)(LV2_Handle instance, unsigned int program);
} LV2_Programs_Feature;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* #ifndef LV2_PROGRAMS_H */
