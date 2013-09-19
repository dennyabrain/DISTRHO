
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("TAL-Vocoder-II")

package.includepaths = {
  package.includepath,
  "../source/engine",
  "../source/engine/synth",
  "." --fake
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/engine/vocoder/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
