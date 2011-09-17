
project.name = "sDelay"
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
package.config["Release"].buildoptions = { "-O2 -march=native -msse -ffast-math -fvisibility=hidden -static" }
package.config["Release"].links        = { "freetype", "pthread", "rt", "X11", "Xext", "juce-plugin-153" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].buildoptions   = { "-O0 -ggdb -static" }
package.config["Debug"].links          = { "freetype", "pthread", "rt", "X11", "Xext", "juce-plugin-153_debug" }

-- TODO: Check for OS
package.config["Release"].defines      = { "LINUX=1", "NDEBUG=1", "JUCE_USE_VSTSDK_2_4=1" };
package.config["Debug"].defines        = { "LINUX=1", "DEBUG=1", "_DEBUG=1", "JUCE_USE_VSTSDK_2_4=1" };

package.includepaths = {
    "../source",
    "/usr/include",
    "/usr/include/freetype2",
    "../../../libs/juce-153/plugin",
    "../../../libs/juce-153/source",
    "../../../sdks/vstsdk2.4"
}

package.libpaths = {
    "/usr/X11R6/lib",
    "/usr/lib",
    "../../../libs"
}

package.files = {
    matchfiles (
        "../source/*.cpp",
        "../../../libs/juce-153/source/src/audio/plugin_client/VST/juce_VST_Wrapper.cpp"
    )
}
