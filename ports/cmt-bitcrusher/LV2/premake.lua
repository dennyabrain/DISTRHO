
project.name    = "Bitcrusher.lv2/Bitcrusher"
project.bindir  = "../../../bin"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""

package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target     = project.name
package.config["Release"].objdir     = "intermediate/Release"
package.config["Release"].defines    = { "NDEBUG=1" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }

package.config["Debug"].target       = project.name
package.config["Debug"].objdir       = "intermediate/Debug"
package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1" }

if (windows) then
  package.defines = { package.defines, "WINDOWS=1" }
else
  package.config["Release"].buildoptions = { "-Wall -O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }
  package.config["Debug"].buildoptions   = { "-Wall -O0 -ggdb -fPIC" }
  if (macosx) then
    package.defines = { package.defines, "MAC=1" }
    package.targetextension = "dylib"
  else
    package.defines = { package.defines, "LINUX=1" }
  end
end

package.includepaths = {
  "../source",
  "../../../libs/distrho-ports"
}

package.files = {
  matchfiles (
    "../source/BitcrusherEditMain.cpp",
    "../../../libs/distrho-ports/PluginLv2.cpp"
  )
}
