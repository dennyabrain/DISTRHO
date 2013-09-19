
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("Vex")

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/lookandfeel/*.cpp",
    "../source/resources/*.cpp",
    "../source/synth/*.cpp",
    "../source/synth/freeverb/*.cpp",
    "../source/waverom/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
