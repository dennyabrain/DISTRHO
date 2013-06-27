
project.name    = "3BandSplitter"
project.bindir  = "../../../bin/ladspa"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""

package.defines   = { "DISTRHO_PLUGIN_TARGET_LADSPA=1" }
package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -mtune=generic -msse -msse2 -mfpmath=sse" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }

if (windows) then
  package.defines      = { package.defines, "WINDOWS=1" }
  package.buildoptions = { "-std=c++0x" }
elseif (macosx) then
  package.defines      = { package.defines, "MAC=1" }
  package.targetextension = "dylib"
  package.buildoptions = { "-std=c++0x" }
else
  package.defines      = { package.defines, "LINUX=1" }
  package.buildoptions = { "-std=c++0x" }
end

package.includepaths = {
  "../source",
  "../../../libs/distrho"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/DistrhoPlugin3BandSplitter.cpp",
    "../../../libs/distrho/DistrhoPluginMain.cpp"
  )
}
