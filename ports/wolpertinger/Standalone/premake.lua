
project.name    = "Wolpertinger"
project.bindir  = "../../../bin/standalone"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "exe"
package.language  = "c++"
package.linkflags = { "static-runtime" }
package.defines   = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=0", "JucePlugin_Build_Standalone=1",
                      "BUILDDATE=\"`date +%F`\"", "WOLPVERSION=\"0041\"", "WOLPVERSIONSTRING=\"0.4.1\"" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1", "CONFIGURATION=\"Release\"" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -mtune=generic -msse -msse2 -mfpmath=sse" }
package.config["Release"].links        = { "juce" }
if (not macosx) then
package.config["Release"].linkoptions  = { "-Wl,--strip-all" }
end

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1", "CONFIGURATION=\"Debug\"" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }
package.config["Debug"].links          = { "juce_debug" }

if (windows) then
  package.defines      = { package.defines, "WINDOWS=1", "BINTYPE=\"Windows-Standalone\"" }
  package.buildoptions = { "-fpermissive -std=c++0x" }
elseif (macosx) then
  package.defines      = { package.defines, "MAC=1", "BINTYPE=\"Mac-Standalone\"" }
  package.buildoptions = { "-ObjC++" }
else
  package.defines      = { package.defines, "LINUX=1", "BINTYPE=\"Linux-Standalone\"" }
  package.buildoptions = { "-std=c++0x" }
end

package.includepaths = {
  "../source",
  "../../../libs/juce-2.0/source",
  "../../../libs/juce-plugin"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
