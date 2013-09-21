
dofile("../../../scripts/make-project.lua")

package = make_vst_project("CabbagePluginEffect")

project.bindir  = "../../../bin/cabbage"
package.links   = { package.links, "csound64" }
package.defines = { package.defines, "USE_DOUBLE=1" } -- , "CSOUND5=1", "CSOUND_5=1"

package.includepaths = {
  package.includepaths,
  "/opt/kxstudio/include/csound",
  "/usr/include/csound"
}

package.libpaths = {
  package.libpaths,
  "/opt/kxstudio/lib"
}

package.links = {
  package.links,
  "sndfile"
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/Plugin/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
