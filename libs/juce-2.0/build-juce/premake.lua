
project.name    = "juce"
project.bindir  = "../.."
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language  = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -mtune=generic -msse -msse2 -mfpmath=sse" }
if (not macosx) then
package.config["Release"].linkoptions  = { "-Wl,--strip-all" }
end

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }

if (windows) then
  package.defines = { "WINDOWS=1" }
  package.buildoptions = { "-fpermissive -std=c++0x" }
  package.links        = { "comdlg32", "gdi32", "imm32", "ole32", "oleaut32", "shlwapi", "uuid", "version", "winmm", "wininet", "ws2_32" }
elseif (macosx) then
  package.defines = { "MAC=1" }
  package.targetextension = "dylib"
  package.buildoptions = { "-ObjC++" }
  package.linkoptions  = { "-framework Accelerate -framework AudioToolbox -framework AudioUnit -framework Carbon -framework Cocoa",
                           "-framework CoreAudio -framework CoreMIDI -framework IOKit -framework QuartzCore -framework WebKit",
                           "-dynamiclib" }
else
  package.defines = { "LINUX=1" }
  package.buildoptions = { "`pkg-config --cflags freetype2` -std=c++0x" }
  package.links        = { "pthread", "asound", "dl", "rt", "X11", "Xext" }
  package.linkoptions  = { "`pkg-config --libs freetype2`" }
end

package.includepaths = {
  ".",
  "../source",
  "../../../sdks/ASIOSDK2/common/",
  "../../../sdks/vstsdk2.4/"
}

package.files = {
  matchfiles (
    "../source/modules/juce_audio_basics/juce_audio_basics.cpp",
    "../source/modules/juce_audio_devices/juce_audio_devices.cpp",
    "../source/modules/juce_audio_formats/juce_audio_formats.cpp",
    "../source/modules/juce_audio_processors/juce_audio_processors.cpp",
    "../source/modules/juce_audio_utils/juce_audio_utils.cpp",
    "../source/modules/juce_core/juce_core.cpp",
    "../source/modules/juce_data_structures/juce_data_structures.cpp",
    "../source/modules/juce_events/juce_events.cpp",
    "../source/modules/juce_graphics/juce_graphics.cpp",
    "../source/modules/juce_gui_basics/juce_gui_basics.cpp",
    "../source/modules/juce_gui_extra/juce_gui_extra.cpp"
  )
}
