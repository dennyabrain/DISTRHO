
project.name = "HybridReverb2"
project.bindir = "../../../bin"
project.libdir = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "exe"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].buildoptions = { "-O2 -march=native -msse -ffast-math -fomit-frame-pointer -funroll-loops -fopenmp -fvisibility=hidden -static `pkg-config fftw3f --cflags`" }
package.config["Release"].links        = { "freetype", "pthread", "asound", "rt", "X11", "Xext", "gomp", "juce-standalone-153" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].buildoptions   = { "-O0 -ggdb -static `pkg-config fftw3f --cflags`" }
package.config["Debug"].links          = { "freetype", "pthread", "asound", "rt", "X11", "Xext", "gomp", "juce-standalone-153_debug" }

package.linkoptions = {
    "`pkg-config fftw3f --libs`"
}

-- TODO: Check for OS
package.config["Release"].defines      = { "LINUX=1", "NDEBUG=1", "JucePlugin_Build_VST=0", "JucePlugin_Build_AU=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_Standalone=1" };
package.config["Debug"].defines        = { "LINUX=1", "DEBUG=1", "_DEBUG=1", "JucePlugin_Build_VST=0", "JucePlugin_Build_AU=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_Standalone=1" };

package.includepaths = {
    "../source",
    "/usr/include",
    "/usr/include/freetype2",
    "../../../libs/juce-153/standalone",
    "../../../libs/juce-153/source"
}

package.libpaths = {
    "/usr/X11R6/lib",
    "/usr/lib",
    "../../../libs"
}

package.files = {
    matchfiles (
        "../source/*.cpp",
        "../source/gui/*.cpp",
        "../source/libHybridConv/*.c",
        "../../../libs/juce-custom/Standalone/*.cpp"
    )
}