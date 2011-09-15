
project.name = "juce-extended"
project.bindir = ".."
project.libdir = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "lib"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].buildoptions = { "-O2 -march=native -msse -ffast-math -fPIC" }
-- package.config["Release"].links        = { "freetype", "pthread", "asound", "rt", "X11", "Xext" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
-- package.config["Debug"].links          = { "freetype", "pthread", "asound", "rt", "X11", "Xext" }

-- TODO: check for OS
package.config["Release"].defines      = { "LINUX=1", "NDEBUG=1" }
package.config["Debug"].defines        = { "LINUX=1", "DEBUG=1", "_DEBUG=1" }

package.includepaths = {
    ".",
    "source",
    "../juce-153/source",
    "/usr/include",
    "/usr/include/freetype2"
}

package.libpaths = {
    "/usr/X11R6/lib/",
    "/usr/lib/",
    ".."
}

package.files = {
  matchfiles (
    "source/*.cpp",
    "source/audio/midi/*.cpp",
    "source/controls/*.cpp",
    "source/lookandfeel/*.cpp"
    )
}
