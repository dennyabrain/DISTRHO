
project.name = "juce-152"
project.bindir = "."
project.libdir = project.bindir .. "/.."
project.configs = { "Release", "Debug" }

target = "linux";

package = newpackage()
package.name = project.name
package.target = project.name
package.language = "c++"

package.objdir = project.bindir .. "/intermediate"
package.includepaths = { "/usr/include", "/usr/include/freetype2", "../../vstsdk2.4" }
package.libpaths = { "/usr/X11R6/lib/" }
package.links = { "freetype", "pthread", "rt", "X11" }
package.linkflags = { "static-runtime" }

package.config["Release"].target        = project.name
package.config["Release"].objdir        = package.objdir .. "/" .. project.name .. "_Release"
package.config["Release"].buildoptions  = { "-march=native -O2 -fPIC -msse -ffast-math -static" }
package.config["Release"].kind = "lib"

package.config["Debug"].target          = project.name .. "_debug"
package.config["Debug"].objdir          = package.objdir .. "/" .. project.name .. "_Debug"
package.config["Debug"].buildoptions    = { "-march=native -ggdb -O0 -fPIC" }
package.config["Debug"].kind = "lib"

-- TODO - check for linux build
package.config["Release"].defines       = { "LINUX=1", "NDEBUG=1", "JUCE_USE_VSTSDK_2_4=1" }
package.config["Debug"].defines         = { "LINUX=1", "DEBUG=1", "_DEBUG=1", "JUCE_USE_VSTSDK_2_4=1" }

package.files = { matchfiles (
    "source/src/application/*.cpp",
    "source/src/audio/*.cpp",
    "source/src/audio/audio_file_formats/*.cpp",
    "source/src/audio/audio_sources/*.cpp",
    "source/src/audio/devices/*.cpp",
    "source/src/audio/dsp/*.cpp",
    "source/src/audio/midi/*.cpp",
    "source/src/audio/plugins/*.cpp",
    "source/src/audio/plugins/formats/*.cpp",
    "source/src/audio/processors/*.cpp",
    "source/src/audio/synthesisers/*.cpp",
    "source/src/containers/*.cpp",
    "source/src/core/*.cpp",
    "source/src/cryptography/*.cpp",
    "source/src/events/*.cpp",
    "source/src/gui/components/*.cpp",
    "source/src/gui/components/buttons/*.cpp",
    "source/src/gui/components/code_editor/*.cpp",
    "source/src/gui/components/controls/*.cpp",
    "source/src/gui/components/filebrowser/*.cpp",
    "source/src/gui/components/keyboard/*.cpp",
    "source/src/gui/components/layout/*.cpp",
    "source/src/gui/components/lookandfeel/*.cpp",
    "source/src/gui/components/menus/*.cpp",
    "source/src/gui/components/mouse/*.cpp",
    "source/src/gui/components/properties/*.cpp",
    "source/src/gui/components/special/*.cpp",
    "source/src/gui/components/windows/*.cpp",
    "source/src/gui/graphics/colour/*.cpp",
    "source/src/gui/graphics/contexts/*.cpp",
    "source/src/gui/graphics/drawables/*.cpp",
    "source/src/gui/graphics/effects/*.cpp",
    "source/src/gui/graphics/fonts/*.cpp",
    "source/src/gui/graphics/geometry/*.cpp",
    "source/src/gui/graphics/imaging/*.cpp",
    "source/src/gui/graphics/imaging/image_file_formats/*.cpp",
    "source/src/io/files/*.cpp",
    "source/src/io/network/*.cpp",
    "source/src/io/streams/*.cpp",
    "source/src/maths/*.cpp",
    "source/src/memory/*.cpp",
    "source/src/native/juce_linux_NativeCode.cpp",
    -- "source/src/native/juce_win32_NativeCode.cpp",
    "source/src/native/linux/*.cpp",
    -- "source/src/native/mac/*.cpp",
    -- "source/src/native/windows/*.cpp",
    "source/src/text/*.cpp",
    "source/src/threads/*.cpp",
    "source/src/utilities/*.cpp"
    )
}
