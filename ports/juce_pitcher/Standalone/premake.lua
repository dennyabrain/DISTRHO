
project.name = "juce_pitcher"
project.bindir = "../../../bin"
project.libdir = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "exe"
package.language = "c++"

package.defines    = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=0", "JucePlugin_Build_Standalone=1" };
package.linkflags  = { "no-symbols", "static-runtime" }
package.links      = { "freetype", "pthread", "asound", "dl", "rt", "m", "X11", "Xext" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" };
package.config["Release"].buildoptions = { "-O2 -mtune=generic -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].linkoptions  = { "-Wl,-O1 -Wl,--as-needed" }
package.config["Release"].links        = { "juce-standalone-153" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" };
package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
package.config["Debug"].links          = { "juce-standalone-153_debug" }

if (windows) then
  package.defines = { package.defines, "WINDOWS=1" };
elseif (macosx) then
  package.defines = { package.defines, "MAC=1" };
else
  package.defines = { package.defines, "LINUX=1" };
  package.buildoptions = { package.buildoptions, "`pkg-config --cflags freetype2`" }
  package.linkoptions  = { package.linkoptions, "`pkg-config --libs freetype2`" }
end

package.includepaths = {
    "../source",
    "../source/soundtouch",
    "../../../libs/juce-153/standalone",
    "../../../libs/juce-153/source"
}

package.libpaths = {
    "../../../libs"
}

package.files = {
    matchfiles (
        "../source/*.cpp",
	"../source/soundtouch/*.cpp",
        "../../../libs/juce-custom/Standalone/*.cpp"
    )
}

if (windows) then
  package.excludes = { matchfiles ( "../source/soundtouch/cpu_detect_x86_gcc.cpp" ) }
else
  package.excludes = { matchfiles ( "../source/soundtouch/3dnow_win.cpp", "../source/soundtouch/cpu_detect_x86_win.cpp" ) }
end
