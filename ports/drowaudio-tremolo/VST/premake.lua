
project.name    = "drowaudio-tremolo"
project.bindir  = "../../../bin/vst"
project.libdir  = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.targetprefix = ""
package.linkflags = { "static-runtime" }
package.defines   = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=1", "JucePlugin_Build_Standalone=0", "USE_DROWAUDIO=1" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].defines      = { "NDEBUG=1" }
package.config["Release"].buildflags   = { "no-symbols", "optimize-speed" }
package.config["Release"].buildoptions = { "-O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -mtune=generic -msse -msse2 -mfpmath=sse" }
package.config["Release"].links        = { "juce", "drowaudio" }
if (not macosx) then
package.config["Release"].linkoptions  = { "-Wl,--strip-all" }
end

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions   = { "-O0 -ggdb" }
package.config["Debug"].links          = { "juce_debug", "drowaudio_debug" }

if (windows) then
  package.defines      = { package.defines, "WINDOWS=1" }
  package.buildoptions = { "-fpermissive -std=c++0x" }
elseif (macosx) then
  package.defines      = { package.defines, "MAC=1" }
  package.targetextension = "dylib"
  package.buildoptions = { "-ObjC++" }
  package.linkoptions  = { "-framework Carbon -framework Cocoa -dynamiclib" }
else
  package.defines      = { package.defines, "LINUX=1" }
  package.buildoptions = { "-std=c++0x" }
end

package.includepaths = {
  "../source",
  "../../../libs/drowaudio/source",
  "../../../libs/juce-2.0/source",
  "../../../libs/juce-plugin",
  "../../../sdks/vstsdk2.4"
}

package.libpaths = {
  "../../../libs"
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/Common/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
