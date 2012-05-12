
project.name    = "zynaddsubfx.lv2/zynaddsubfx"
project.bindir  = "../../../bin/lv2"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""

package.defines   = { "DISABLE_GUI=1", "ASM_F2I_YES=1", "VERSION=\\\"2.4.2-lv2\\\"" }
package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target     = project.name
package.config["Release"].objdir     = "intermediate/Release"
package.config["Release"].defines    = { "NDEBUG=1" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
-- package.config["Release"].links      = { "" }

package.config["Debug"].target       = project.name
package.config["Debug"].objdir       = "intermediate/Debug"
package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1" }
-- package.config["Debug"].links        = { "" }

if (windows) then
  package.defines = { package.defines, "WINDOWS=1" }
else
  package.config["Release"].buildoptions = { "-O2 -g -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
  package.config["Debug"].buildoptions   = { "-O0 -g -ggdb -fPIC" }
  if (macosx) then
    package.defines = { package.defines, "MAC=1" }
    package.targetextension = "dylib"
    package.linkoptions     = { "-bundle " }
  else
    package.defines = { package.defines, "LINUX=1" }
    package.links   = { "z" }
    package.buildoptions = { "`pkg-config --cflags mxml fftw3`" }
    package.linkoptions  = { "`pkg-config --libs mxml fftw3`" }
  end
end

package.includepaths = {
  "../source/src"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/src/DSP/*.cpp",
    "../source/src/Effects/*.cpp",
    "../source/src/Misc/*.cpp",
    "../source/src/Nio/*.cpp",
    "../source/src/Output/LV2audiooutput.cpp",
    "../source/src/Params/*.cpp",
    "../source/src/Synth/*.cpp"
  )
}

package.excludes = {
  matchfiles (
    "../source/src/Misc/LASHClient.cpp",
    "../source/src/Misc/Stereo.cpp",
    "../source/src/Nio/AlsaEngine.cpp",
    "../source/src/Nio/JackEngine.cpp",
    "../source/src/Nio/OssEngine.cpp",
    "../source/src/Nio/PaEngine.cpp",
    "../source/src/Nio/SafeQueue.cpp"
  )
}
