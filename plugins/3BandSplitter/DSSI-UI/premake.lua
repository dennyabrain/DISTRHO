
project.name    = "3BandSplitter/3BandSplitter_gl"
project.bindir  = "../../../bin/dssi"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "exe"
package.language = "c++"

package.defines   = { "DISTRHO_PLUGIN_TARGET_DSSI=1" }
package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -mtune=generic -msse -msse2 -mfpmath=sse" }
package.config["Release"].links        = { "dgl" }

package.config["Debug"].target         = project.name .. "Debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }
package.config["Debug"].links          = { "dgl_debug" }

if (windows) then
  package.defines      = { package.defines, "WINDOWS=1" }
  package.buildoptions = { "-std=c++0x" }
  package.links        = { "opengl32", "gdi32" }
  package.linkoptions  = { "-static -mwindows" }
elseif (macosx) then
  package.defines      = { package.defines, "MAC=1" }
  package.linkoptions  = { "-framework OpenGL -framework Cocoa" }
else
  package.defines      = { package.defines, "LINUX=1" }
  package.buildoptions = { "-std=c++0x `pkg-config --cflags liblo gl`" }
  package.links        = { "X11" }
  package.linkoptions  = { "`pkg-config --libs liblo gl`" }
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
    "../source/DistrhoArtwork3BandSplitter.cpp",
    "../source/DistrhoUI3BandSplitter.cpp",
    "../../../libs/distrho/DistrhoUIMain.cpp"
  )
}
