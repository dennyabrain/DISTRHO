
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("TheFunction")

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/Headers/UI/Knob.cpp",
    "../source/Headers/UI/FancyButton.cpp",
    "../source/Headers/Binary Data/Backgrounds/thefunctionbackground.cpp",
    "../source/Headers/Binary Data/UI/button.cpp",
    "../source/Headers/Binary Data/UI/knobs.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
