
project.name = "mr-alias2"
project.bindir = "../../../bin"
project.libdir = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "exe"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" };
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].links        = { "juce-standalone-153" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" };
package.config["Debug"].links          = { "juce-standalone-153_debug" }

if (windows) then
  package.defines = { package.defines, "WINDOWS=1" };
else
  package.config["Release"].buildoptions = { "-O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
--   package.config["Release"].linkoptions  = { "-Wl,-O1 -Wl,--as-needed" }
  package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
  if (macosx) then
    package.defines = { package.defines, "MAC=1" };
  else
    package.defines = { package.defines, "LINUX=1" };
    package.buildoptions = { "`pkg-config --cflags freetype2`" }
    package.linkoptions  = { "`pkg-config --libs freetype2`" }
  end
end

package.includepaths = {
    "../source",
    "/usr/include",
    "/usr/include/freetype2",
    "../../../libs/juce-153/standalone",
    "../../../libs/juce-153/source"
}

package.libpaths = {
    "/usr/X11R6/lib",
    "/usr/lib",
    "../../../libs"
}

package.files = {
    matchfiles (
        "../source/*.cpp",
        "../../../libs/juce-custom/Standalone/*.cpp"
    )
}
