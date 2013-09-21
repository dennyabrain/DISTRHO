
--=======================================================================================--

function make_library_project(name)
  project.name    = name
  project.bindir  = "../.."
  project.libdir  = project.bindir
  project.configs = { "Release", "Debug" }

  package = newpackage()
  package.name = project.name
  package.kind = "lib"
  package.language = "c++"

  package.target       = project.name
  package.objdir       = "intermediate"
  package.defines      = {}
  package.buildoptions = { "-fPIC", "-DPIC", os.getenv("CXXFLAGS") }

  package.config["Release"].target       = project.name
  package.config["Release"].objdir       = "intermediate/Release"
  package.config["Release"].defines      = { "NDEBUG=1" }
  package.config["Release"].buildoptions = { "-O3", "-ffast-math", "-fomit-frame-pointer", "-mtune=generic", "-msse", "-msse2", "-mfpmath=sse", "-fvisibility=hidden", "-fvisibility-inlines-hidden" }

  if (not macosx) then
    package.config["Release"].buildoptions = { package.config["Release"].buildoptions, "-fdata-sections", "-ffunction-sections" }
  end

  package.config["Debug"].target         = project.name .. "_debug"
  package.config["Debug"].objdir         = "intermediate/Debug"
  package.config["Debug"].defines        = { "DEBUG=1", "_DEBUG=1" }
  package.config["Debug"].buildoptions   = { "-O0", "-ggdb" }

  if (windows) then
    package.defines      = { "WINDOWS=1" }
    package.buildoptions = { package.buildoptions, "-fpermissive", "-std=c++0x" }
  elseif (macosx) then
    package.defines      = { "MAC=1" }
    package.buildoptions = { package.buildoptions, "-ObjC++" }
  else
    package.defines      = { "LINUX=1" }
    package.buildoptions = { package.buildoptions, "`pkg-config --cflags freetype2`", "-std=c++0x" }
  end

  return package
end

--=======================================================================================--

function make_lv2_project(name)
  project.name    = name .. ".lv2/" .. name
  project.bindir  = "../../../bin/lv2"
  project.libdir  = project.bindir
  project.configs = { "Release", "Debug" }

  package = newpackage()
  package.name = project.name
  package.kind = "dll"
  package.language = "c++"
  package.defines  = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=1", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=0", "JucePlugin_Build_Standalone=0" }

  package.target       = project.name
  package.targetprefix = ""
  package.objdir       = "intermediate"
  package.buildoptions = { os.getenv("CXXFLAGS") }
  package.links        = {}
  package.linkoptions  = { os.getenv("LDFLAGS") }

  package.config["Release"].target       = project.name
  package.config["Release"].objdir       = "intermediate/Release"
  package.config["Release"].defines      = { "NDEBUG=1", "CONFIGURATION=\"Release\"" }
  package.config["Release"].buildoptions = { "-O3", "-ffast-math", "-fomit-frame-pointer", "-mtune=generic", "-msse", "-msse2", "-mfpmath=sse", "-fvisibility=hidden", "-fvisibility-inlines-hidden" }
  package.config["Release"].links        = { "juce" }

  if (not macosx) then
    package.config["Release"].buildoptions = { package.config["Release"].buildoptions, "-fdata-sections", "-ffunction-sections" }
    package.config["Release"].linkoptions  = { "-Wl,--gc-sections", "-Wl,--strip-all" }
  end

  package.config["Debug"].target       = project.name
  package.config["Debug"].objdir       = "intermediate/Debug"
  package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1", "CONFIGURATION=\"Debug\"" }
  package.config["Debug"].buildoptions = { "-O0", "-ggdb" }
  package.config["Debug"].links        = { "juce_debug" }

  package.includepaths = {
    "../source",
    "../../../libs/juce-2.0/source",
    "../../../libs/drowaudio/source",
    "../../../libs/juced/source",
    "../../../libs/juce-plugin",
    "../../../sdks/vstsdk2.4"
  }

  package.libpaths = {
    "../../../libs"
  }

  if (windows) then
    package.defines      = { package.defines, "WINDOWS=1", "BINTYPE=\"Windows-LV2\"" }
    package.buildoptions = { package.buildoptions, "-fpermissive", "-std=c++0x" }
    package.links        = { "comdlg32", "gdi32", "imm32", "ole32", "oleaut32", "shlwapi", "uuid", "version", "winmm", "wininet", "ws2_32" }
  elseif (macosx) then
    package.defines      = { package.defines, "MAC=1", "BINTYPE=\"Mac-LV2\"" }
    package.buildoptions = { package.buildoptions, "-ObjC++" }
    package.linkoptions  = { package.linkoptions, "-dynamiclib",
                             "-framework Accelerate", "-framework AudioToolbox", "-framework AudioUnit", "-framework Carbon", "-framework Cocoa",
                             "-framework CoreAudio", "-framework CoreMIDI", "-framework IOKit", "-framework QuartzCore", "-framework WebKit" }
    package.targetextension = "dylib"
  else
    package.defines      = { package.defines, "LINUX=1", "BINTYPE=\"Linux-LV2\"" }
    package.buildoptions = { package.buildoptions, "-std=c++0x" }
    package.links        = { "dl", "pthread", "rt", "X11", "Xext" }
    package.linkoptions  = { package.linkoptions, "`pkg-config --libs freetype2`" }
  end

  return package
end

--=======================================================================================--

function make_vst_project(name)
  project.name    = name
  project.bindir  = "../../../bin/vst"
  project.libdir  = project.bindir
  project.configs = { "Release", "Debug" }

  package = newpackage()
  package.name = project.name
  package.kind = "dll"
  package.language = "c++"
  package.defines  = { "JucePlugin_Build_AU=0", "JucePlugin_Build_LV2=0", "JucePlugin_Build_RTAS=0", "JucePlugin_Build_VST=1", "JucePlugin_Build_Standalone=0" }

  package.target       = project.name
  package.targetprefix = ""
  package.objdir       = "intermediate"
  package.buildoptions = { os.getenv("CXXFLAGS") }
  package.links        = {}
  package.linkoptions  = { os.getenv("LDFLAGS") }

  package.config["Release"].target       = project.name
  package.config["Release"].objdir       = "intermediate/Release"
  package.config["Release"].defines      = { "NDEBUG=1", "CONFIGURATION=\"Release\"" }
  package.config["Release"].buildoptions = { "-O3", "-ffast-math", "-fomit-frame-pointer", "-mtune=generic", "-msse", "-msse2", "-mfpmath=sse", "-fvisibility=hidden", "-fvisibility-inlines-hidden" }
  package.config["Release"].links        = { "juce" }

  if (not macosx) then
    package.config["Release"].buildoptions = { package.config["Release"].buildoptions, "-fdata-sections", "-ffunction-sections" }
    package.config["Release"].linkoptions  = { "-Wl,--gc-sections", "-Wl,--strip-all" }
  end

  package.config["Debug"].target       = project.name .. "_debug"
  package.config["Debug"].objdir       = "intermediate/Debug"
  package.config["Debug"].defines      = { "DEBUG=1", "_DEBUG=1", "CONFIGURATION=\"Debug\"" }
  package.config["Debug"].buildoptions = { "-O0", "-ggdb" }
  package.config["Debug"].links        = { "juce_debug" }

  package.includepaths = {
    "../source",
    "../../../libs/juce-2.0/source",
    "../../../libs/drowaudio/source",
    "../../../libs/juced/source",
    "../../../libs/juce-plugin",
    "../../../sdks/vstsdk2.4"
  }

  package.libpaths = {
    "../../../libs"
  }

  if (windows) then
    package.defines      = { package.defines, "WINDOWS=1", "BINTYPE=\"Windows-VST\"" }
    package.buildoptions = { package.buildoptions, "-fpermissive", "-std=c++0x" }
    package.links        = { "comdlg32", "gdi32", "imm32", "ole32", "oleaut32", "shlwapi", "uuid", "version", "winmm", "wininet", "ws2_32" }
  elseif (macosx) then
    package.defines      = { package.defines, "MAC=1", "BINTYPE=\"Mac-VST\"" }
    package.buildoptions = { package.buildoptions, "-ObjC++" }
    package.linkoptions  = { package.linkoptions, "-dynamiclib",
                             "-framework Accelerate", "-framework AudioToolbox", "-framework AudioUnit", "-framework Carbon", "-framework Cocoa",
                             "-framework CoreAudio", "-framework CoreMIDI", "-framework IOKit", "-framework QuartzCore", "-framework WebKit" }
    package.targetextension = "dylib"
  else
    package.defines      = { package.defines, "LINUX=1", "BINTYPE=\"Linux-VST\"" }
    package.buildoptions = { package.buildoptions, "-std=c++0x" }
    package.links        = { "dl", "pthread", "rt", "X11", "Xext" }
    package.linkoptions  = { package.linkoptions, "`pkg-config --libs freetype2`" }
  end

  return package
end

--=======================================================================================--
