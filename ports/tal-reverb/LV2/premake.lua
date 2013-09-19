
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("TAL-Reverb")

package.includepaths = {
  package.includepath,
  "." --fake
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
