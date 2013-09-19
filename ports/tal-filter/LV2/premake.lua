
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("TAL-Filter")

package.includepaths = {
  package.includepath,
  "../source/Engine",
  "." --fake
}

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/Engine/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
