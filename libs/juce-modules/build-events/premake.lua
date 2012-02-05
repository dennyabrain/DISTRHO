
project.name    = "juce-events"
project.bindir  = "../.."
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "lib"
package.language  = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target     = project.name
package.config["Release"].objdir     = "intermediate/Release"
package.config["Release"].defines    = { "NDEBUG=1" }
package.config["Release"].buildflags = { "optimize-speed" }

package.config["Debug"].target       = project.name .. "_debug"
package.config["Debug"].objdir       = "intermediate/Debug"
package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1" }

if (windows) then
  package.defines = { "WINDOWS=1" }
else
  package.config["Release"].buildoptions = { "-O2 -mtune=generic -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
  package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }
  if (macosx) then
    package.defines = { "MAC=1" }
  else
    package.defines = { "LINUX=1" }
    package.buildoptions = { "`pkg-config --cflags freetype2`" }
  end
end

package.includepaths = {
    "."
}

package.files = {
  matchfiles (
    "../source/modules/juce_events/juce_events.cpp"
  )
}
