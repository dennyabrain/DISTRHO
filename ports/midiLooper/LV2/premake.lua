
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("midiLooper")

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/common/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
