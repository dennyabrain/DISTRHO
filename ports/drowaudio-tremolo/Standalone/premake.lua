
project.name    = "drowaudio-tremolo"
project.bindir  = "../../../bin/standalone"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "exe"
package.language = "c++"

package.defines   = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=0", "JucePlugin_Build_Standalone=1" }
package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -mtune=generic -msse -mfpmath=sse" }
package.config["Release"].links        = { "juce-core", "juce-audio-basics", "juce-audio-devices_full", "juce-audio-formats", "juce-audio-processors", "juce-audio-utils", "juce-data-structures", "juce-events", "juce-graphics", "juce-gui-basics" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].links          = { "juce-core_debug", "juce-audio-basics_debug", "juce-audio-devices_full_debug", "juce-audio-formats_debug", "juce-audio-processors_debug", "juce-audio-utils_debug", "juce-data-structures_debug", "juce-events_debug", "juce-graphics_debug", "juce-gui-basics_debug" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }

if (windows) then
  package.defines      = { package.defines, "WINDOWS=1" }
  package.buildoptions = { "-fpermissive -std=c++0x" }
  package.links        = { "gdi32", "imm32", "ole32", "shlwapi", "uuid", "version", "winmm", "wininet", "ws2_32" }
  package.linkoptions  = { "-static -mwindows" }
elseif (macosx) then
  package.defines      = { package.defines, "MAC=1" }
  package.buildoptions = { "-ObjC++" }
  package.linkoptions  = { "-framework AudioToolbox -framework Cocoa -framework CoreAudio -framework CoreMidi -framework QuartzCore" }
else
  package.defines      = { package.defines, "LINUX=1" }
  package.links        = { "pthread", "asound", "dl", "rt", "X11", "Xext" }
  package.buildoptions = { "-std=c++0x" }
  package.linkoptions  = { "`pkg-config --libs freetype2`" }
end

package.includepaths = {
  "../source",
  "../../../libs/juce-2.0/source",
  "../../../libs/drowaudio/source",
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
