
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("TAL-Dub-III")

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
