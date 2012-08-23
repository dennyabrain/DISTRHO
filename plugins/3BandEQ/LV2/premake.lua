
project.name    = "3BandEQ.lv2/3BandEQ"
project.bindir  = "../../../bin/lv2"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""

package.defines      = { "DISTRHO_PLUGIN_TARGET_LV2=1" }
package.buildoptions = { "-std=c++0x" }
package.linkflags    = { "no-symbols", "static-runtime" }
package.links        = { "GLU" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC" }

package.config["Debug"].target       = project.name
package.config["Debug"].objdir       = "intermediate/Debug"
package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions = { "-O0 -ggdb -fPIC" }

if (macosx) then
  package.targetextension = "dylib"
end

package.includepaths = {
  "../source",
  "../../distrho-plugin-toolkit/distrho"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../distrho-plugin-toolkit/src/DistrhoPlugin.cpp",
    "../../distrho-plugin-toolkit/src/DistrhoUI.cpp"
  )
}
