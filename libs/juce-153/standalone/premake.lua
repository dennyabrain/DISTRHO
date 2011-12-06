
project.name = "juce-standalone-153"
project.bindir = "../.."
project.libdir = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "lib"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" };
package.config["Release"].buildflags   = { "optimize-speed" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" };

if (windows) then
  package.defines = { "WINDOWS=1" };
else
  package.config["Release"].buildoptions = { "-O2 -mtune=generic -ffast-math -fomit-frame-pointer -fPIC" }
  package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
  if (macosx) then
    package.defines = { "MAC=1" };
  else
    package.defines = { "LINUX=1" };
    package.buildoptions = { "`pkg-config --cflags freetype2`" }
  end
end

if (windows) then
  package.includepaths = { ".", "../../../sdks/ASIOSDK2/common" }
else
  package.includepaths = { "." }
end

package.files = {
  matchfiles (
    "../source/src/application/*.cpp",
    "../source/src/audio/*.cpp",
    "../source/src/audio/audio_file_formats/*.cpp",
    "../source/src/audio/audio_sources/*.cpp",
    "../source/src/audio/devices/*.cpp",
    "../source/src/audio/dsp/*.cpp",
    "../source/src/audio/midi/*.cpp",
    -- "../source/src/audio/plugin_client/RTAS/*.cpp",
    -- "../source/src/audio/plugin_client/Standalone/*.cpp",
    -- "../source/src/audio/plugin_client/VST/*.cpp",
    "../source/src/audio/plugin_host/*.cpp",
    "../source/src/audio/plugin_host/formats/*.cpp",
    "../source/src/audio/processors/*.cpp",
    "../source/src/audio/synthesisers/*.cpp",
    "../source/src/containers/*.cpp",
    "../source/src/core/*.cpp",
    "../source/src/cryptography/*.cpp",
    "../source/src/events/*.cpp",
    "../source/src/gui/components/*.cpp",
    "../source/src/gui/components/buttons/*.cpp",
    "../source/src/gui/components/code_editor/*.cpp",
    "../source/src/gui/components/controls/*.cpp",
    "../source/src/gui/components/filebrowser/*.cpp",
    "../source/src/gui/components/keyboard/*.cpp",
    "../source/src/gui/components/layout/*.cpp",
    "../source/src/gui/components/lookandfeel/*.cpp",
    "../source/src/gui/components/menus/*.cpp",
    "../source/src/gui/components/mouse/*.cpp",
    "../source/src/gui/components/positioning/*.cpp",
    "../source/src/gui/components/properties/*.cpp",
    "../source/src/gui/components/special/*.cpp",
    "../source/src/gui/components/windows/*.cpp",
    "../source/src/gui/graphics/colour/*.cpp",
    "../source/src/gui/graphics/contexts/*.cpp",
    "../source/src/gui/graphics/drawables/*.cpp",
    "../source/src/gui/graphics/effects/*.cpp",
    "../source/src/gui/graphics/fonts/*.cpp",
    "../source/src/gui/graphics/geometry/*.cpp",
    "../source/src/gui/graphics/imaging/*.cpp",
    "../source/src/gui/graphics/imaging/image_file_formats/*.cpp",
    "../source/src/io/files/*.cpp",
    "../source/src/io/network/*.cpp",
    "../source/src/io/streams/*.cpp",
    "../source/src/maths/*.cpp",
    "../source/src/memory/*.cpp",
    "../source/src/native/common/*.cpp",
    "../source/src/text/*.cpp",
    "../source/src/threads/*.cpp",
    "../source/src/utilities/*.cpp"
    )
}

if (windows) then
  package.files = { package.files, matchfiles ("../source/src/native/windows/*.cpp") }
elseif (macosx) then
  package.files = { package.files, matchfiles ("../source/src/native/mac/*.cpp") }
else
  package.files = { package.files, matchfiles ("../source/src/native/linux/*.cpp") }
end

-- Missing android -> "../source/src/native/android/*.cpp"
