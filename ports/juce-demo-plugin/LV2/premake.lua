
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("JuceDemoPlugin")

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
