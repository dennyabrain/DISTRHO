
project.name    = "3BandEQ.lv2/3BandEQ"
project.bindir  = "../../../bin/lv2"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""

package.defines   = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=1", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=0", "JucePlugin_Build_Standalone=0" }
package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target     = project.name
package.config["Release"].objdir     = "intermediate/Release"
package.config["Release"].defines    = { "NDEBUG=1" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
package.config["Release"].links      = { "juce-core", "juce-audio-basics", "juce-audio-devices", "juce-audio-formats", "juce-audio-processors", "juce-audio-utils", "juce-data-structures", "juce-events", "juce-graphics", "juce-gui-basics" }

package.config["Debug"].target       = project.name
package.config["Debug"].objdir       = "intermediate/Debug"
package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].links        = { "juce-core_debug", "juce-audio-basics_debug", "juce-audio-devices_debug", "juce-audio-formats_debug", "juce-audio-processors_debug", "juce-audio-utils_debug", "juce-data-structures_debug", "juce-events_debug", "juce-graphics_debug", "juce-gui-basics_debug" }

if (windows) then
  package.defines     = { package.defines, "WINDOWS=1" }
  package.links       = { "imm32", "ole32", "shlwapi", "uuid", "version", "wininet", "winmm", "ws2_32" }
  package.linkoptions = { "-mwindows" }
  package.config["Release"].buildoptions = { "-O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fpermissive -fvisibility=hidden -fPIC" }
  package.config["Debug"].buildoptions   = { "-O0 -ggdb -fpermissive -fPIC" }
else
  package.config["Release"].buildoptions = { "-O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
  package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
  if (macosx) then
    package.defines = { package.defines, "MAC=1" }
    package.targetextension = "dylib"
    package.buildoptions    = { "-ObjC++" }
    package.linkoptions     = { "-bundle -framework Carbon -framework QuartzCore" }
  else
    package.defines = { package.defines, "LINUX=1" }
    package.links   = { "freetype", "pthread", "rt", "X11", "Xext" }
    package.buildoptions = { "`pkg-config --cflags freetype2`" }
    package.linkoptions  = { "`pkg-config --libs freetype2`" }
  end
end

package.includepaths = {
  "../source",
  "../../../libs/juce-2.0/source",
  "../../../libs/juce-lv2",
  "../../../libs/juce-plugin"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../common/Juce-Widgets/DistrhoIconArtwork.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
