/*
 * JUCE LV2 *.ttl generator
 */

#include <stdio.h>

#if defined(_WIN32) || defined (_WIN64)
#include <windows.h>
#define TTL_GENERATOR_WINDOWS
#else
#include <dlfcn.h>
#endif

#ifndef nullptr
#define nullptr 0
#endif

typedef void (*TTL_Generator_Function)(void);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: %s /path/to/binary.so\n", argv[0]);
        return 1;
    }

#ifdef TTL_GENERATOR_WINDOWS
    void* handle = LoadLibrary(argv[1]);
#else
    void* handle = dlopen(argv[1], RTLD_LAZY);
#endif

    if (! handle)
    {
#ifdef TTL_GENERATOR_WINDOWS
        printf("Failed to open library\n");
#else
        printf("Failed to open library, error was:\n%s\n", dlerror());
#endif
        return 2;
    }

#ifdef TTL_GENERATOR_WINDOWS
    TTL_Generator_Function ttl_fcn = (TTL_Generator_Function)GetProcAddress((HMODULE)handle, "juce_lv2_ttl_generator");
#else
    TTL_Generator_Function ttl_fcn = (TTL_Generator_Function)dlsym(handle, "juce_lv2_ttl_generator");
#endif

    if (ttl_fcn)
        ttl_fcn();
    else
        printf("Failed to find 'juce_lv2_ttl_generator' function\n");

#ifdef TTL_GENERATOR_WINDOWS
    FreeLibrary((HMODULE)handle);
#else
    dlclose(handle);
#endif

    return 0;
}
