
project.name    = "juce-standalone"
project.bindir  = "../.."
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language  = "c++"
package.linkflags = { "static-runtime" }
package.defines   = { "JucePlugin_Build_Standalone=1" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -mtune=generic -msse -msse2 -mfpmath=sse" }
package.config["Release"].linkoptions  = { "-Wl,--strip-all" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }

if (windows) then
  package.defines = { package.defines, "WINDOWS=1" }
  package.buildoptions = { "-fpermissive -std=c++0x" }
  package.links        = { "gdi32", "imm32", "ole32", "shlwapi", "uuid", "version", "winmm", "wininet", "ws2_32" }
elseif (macosx) then
  package.defines = { package.defines, "MAC=1" }
  package.targetextension = "dylib"
  package.buildoptions = { "-ObjC++" }
  package.linkoptions  = { "-framework Accelerate -framework AudioToolbox -framework Cocoa -framework CoreAudio -framework CoreMIDI -framework QuartzCore" }
else
  package.defines = { package.defines, "LINUX=1" }
  package.buildoptions = { "`pkg-config --cflags freetype2` -std=c++0x" }
  package.links        = { "pthread", "asound", "dl", "rt", "X11", "Xext" }
  package.linkoptions  = { "`pkg-config --libs freetype2`" }
end

package.includepaths = {
  "..",
  "../../juce-2.0/source"
}

package.files = {
  matchfiles (
    "../../juce-2.0/source/modules/juce_core/juce_core.cpp",
    "../../juce-2.0/source/modules/juce_audio_basics/juce_audio_basics.cpp",
    "../../juce-2.0/source/modules/juce_audio_devices/juce_audio_devices.cpp",
    "../../juce-2.0/source/modules/juce_audio_formats/juce_audio_formats.cpp",
    "../../juce-2.0/source/modules/juce_audio_processors/juce_audio_processors.cpp",
    "../../juce-2.0/source/modules/juce_audio_utils/juce_audio_utils.cpp",
    "../../juce-2.0/source/modules/juce_data_structures/juce_data_structures.cpp",
    "../../juce-2.0/source/modules/juce_events/juce_events.cpp",
    "../../juce-2.0/source/modules/juce_graphics/juce_graphics.cpp",
    "../../juce-2.0/source/modules/juce_gui_basics/juce_gui_basics.cpp"
  )
}
