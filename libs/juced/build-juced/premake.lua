
dofile("../../../scripts/make-project.lua")

package = make_library_project("juced")

package.includepaths = {
  ".",
  "../../juce-2.0/source"
}

package.files = {
  matchfiles (
    "../source/juced.cpp"
  )
}
