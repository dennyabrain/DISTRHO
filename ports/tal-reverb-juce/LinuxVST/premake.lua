
project.name = "TAL-Reverb"
project.bindir = "../../../bin/"
project.libdir = "../../../bin/"

project.configs = { "Release", "Debug" }

package = newpackage()
package.name = "TAL-Reverb"
package.kind = "dll"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].objdir = "intermediate/Release"
package.config["Debug"].objdir   = "intermediate/Debug"

package.config["Release"].target = "TAL-Reverb"
package.config["Debug"].target   = "TAL-Reverb_debug"

package.config["Release"].defines      = { "LINUX=1", "NDEBUG=1", "JUCE_ALSA=0", "JUCE_USE_VSTSDK_2_4=1" };
package.config["Release"].buildoptions = { "-O2 -s -fvisibility=hidden -msse -ffast-math -static" }
package.config["Release"].links        = { "freetype", "pthread", "rt", "X11", "GL", "juce-152" }

package.config["Debug"].defines        = { "LINUX=1", "DEBUG=1", "_DEBUG=1", "JUCE_ALSA=0", "JUCE_USE_VSTSDK_2_4=1" };
package.config["Debug"].buildoptions   = { "-O0 -ggdb -static" }
package.config["Debug"].links          = { "freetype", "pthread", "rt", "X11", "GL", "juce-152_debug" }

package.includepaths = {
    "../src",
    "../src/engine",
    "/usr/include",
    "/usr/include/freetype2",
    "../../../libs/juce-152/source",
    "../../../sdks/vstsdk2.4",
    "." --fake
}

package.libpaths = {
    "/usr/X11R6/lib/",
    "/usr/lib/",
    "../../../libs/"
}

package.files = {
    matchfiles (
        "../src/*.cpp",
        "../../../libs/juce-152/source/extras/audio plugins/wrapper/VST/juce_VST_Wrapper.cpp"
        -- "../../../libs/juce-152/source/src/audio/plugin_client/VST/juce_VST_Wrapper.cpp"
    )
}
