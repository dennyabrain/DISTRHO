#ifndef PIZ_LOG_H
#define PIZ_LOG_H

#if MAKE_LOG || defined (_DEBUG)
	#ifndef MAKE_LOG
	#define MAKE_LOG 1
	#endif
	#ifdef _WIN32
    #include <windows.h>
    #endif
#include "juce_amalgamated.h"
inline void logDebugString(const String& text, bool toFile=false, bool toDbgview=true)
{
    if (toFile) {
        File logfile = File("~/Desktop/MrAlias2.log");
        if (logfile.create()) {
            logfile.appendText(text + "\n");
        }
    }
    #ifdef _WIN32
	if (toDbgview) OutputDebugString("MrAP: " + text + "\n");
	#else 
	printf("MrAP: %s\n",(const char*)text);
    #endif
}
#else 
#define logDebugString(i)
#endif

#endif