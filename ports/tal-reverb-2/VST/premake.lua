
dofile("../../../scripts/make-project.lua")

package = make_vst_project("TAL-Reverb-2")

package.includepaths = {
  package.includepaths,
  "." --fake
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
