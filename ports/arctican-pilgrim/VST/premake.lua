
dofile("../../../scripts/make-project.lua")

package = make_vst_project("ThePilgrim")

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
