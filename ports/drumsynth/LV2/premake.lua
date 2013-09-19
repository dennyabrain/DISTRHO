
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("DrumSynth")

package.config["Release"].links = { package.config["Release"].links, "juced" }
package.config["Debug"].links   = { package.config["Debug"].links, "juced_debug" }

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../source/Components/*.cpp",
    "../source/DrumSynth/*.cpp",
    "../source/IniParser/*.cpp",
    "../source/Resources/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
