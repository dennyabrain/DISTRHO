
project.name    = "midiSwing"
project.bindir  = "../../../../bin"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""

package.linkflags = { "no-symbols", "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildoptions = { "-Wall -Wno-multichar -O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fmessage-length=0 -finline-functions -fvisibility=hidden -fPIC" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
-- package.config["Release"].linkoptions  = { "-Wl,-O1 -Wl,--as-needed" }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC" }

if (windows) then
  package.defines = { "WINDOWS=1" }
elseif (macosx) then
  package.defines = { "MAC=1" }
else
  package.defines = { "LINUX=1", "__cdecl=\"\"" }
end

package.includepaths = {
  "../../source/midiSwing",
  "../../../../sdks/vstsdk2.4"
}

package.files = {
  matchfiles (
    "../../source/midiSwing/*.cpp",
    "../../source/common/PizMidi.cpp",
    "../../source/common/vstplugmain.cpp",
    "../../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/audioeffect.cpp",
    "../../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/audioeffectx.cpp"
  )
}
