
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("TAL-NoiseMaker")

package.includepaths = {
  package.includepath,
  "../source/Engine",
  ".", --fake
  "./intermediate", --fake
  "./intermediate/Release", --fake
  "./intermediate/Debug" --fake
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/Engine/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
