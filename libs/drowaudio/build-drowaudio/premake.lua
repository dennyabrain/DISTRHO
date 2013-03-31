
project.name    = "drowaudio"
project.bindir  = "../.."
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "lib"
package.language  = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC -mtune=generic -msse -msse2 -mfpmath=sse" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }

if (windows) then
  package.defines = { "WINDOWS=1" }
  package.buildoptions = { "-fpermissive -std=c++0x" }
elseif (macosx) then
  package.defines = { "MAC=1" }
  package.buildoptions =  { "-ObjC++" }
else
  package.defines = { "LINUX=1" }
  package.buildoptions = { "-std=c++0x" }
end

package.includepaths = {
  ".",
  "../../juce-2.0/source"
}

package.files = {
  matchfiles (
    "../source/dRowAudio/dRowAudio.cpp"
  )
}
