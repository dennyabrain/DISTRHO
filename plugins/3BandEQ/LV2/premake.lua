
project.name    = "3BandEQ.lv2/3BandEQ"
project.bindir  = "../../../bin"
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
package.config["Release"].links      = { "juce-plugin-153" }

package.config["Debug"].target       = project.name .. "_debug"
package.config["Debug"].objdir       = "intermediate/Debug"
package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].links        = { "juce-plugin-153_debug" }

if (windows) then
  package.defines = { package.defines, "WINDOWS=1" }
else
  package.config["Release"].buildoptions = { "-O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
--   package.config["Release"].linkoptions  = { "-Wl,-O1 -Wl,--as-needed" }
  package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
  if (macosx) then
    package.defines = { package.defines, "MAC=1" }
  else
    package.defines = { package.defines, "LINUX=1" }
    package.links   = { "freetype", "pthread", "rt", "X11", "Xext" }
    package.buildoptions = { "`pkg-config --cflags freetype2`" }
    package.linkoptions  = { "`pkg-config --libs freetype2`" }
  end
end

package.includepaths = {
  "../source",
  "../../../libs/juce-153/plugin",
  "../../../libs/juce-153/source"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-lv2/juce_LV2_Wrapper.cpp"
  )
}
