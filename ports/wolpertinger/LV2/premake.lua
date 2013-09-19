
dofile("../../../scripts/make-project.lua")

package = make_lv2_project("Wolpertinger")

package.defines = { package.defines, "BUILDDATE=\"`date +%F`\"", "WOLPVERSION=\"0041\"", "WOLPVERSIONSTRING=\"0.4.1\"" }

package.files = {
  matchfiles (
    "../source/*.cpp",
    "../../../libs/juce-plugin/JucePluginMain.cpp"
  )
}
