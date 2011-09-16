
project.name = "huit"
project.bindir = "../../../bin"
project.libdir = project.bindir
project.configs = { "Release", "Debug" }

package = newpackage()
package.name = project.name
package.kind = "dll"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.config["Release"].target       = project.name
package.config["Release"].objdir       = "intermediate/Release"
package.config["Release"].buildoptions = { "-O2 -march=native -msse -ffast-math -fvisibility=hidden" }
package.config["Release"].links        = { }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].buildoptions   = { "-O0 -ggdb -static" }
package.config["Debug"].links          = { }

-- TODO: Check for OS
package.config["Release"].defines      = { "LINUX=1", "NDEBUG=1" };
package.config["Debug"].defines        = { "LINUX=1", "DEBUG=1", "_DEBUG=1" };

package.includepaths = {
    "../source",
    "/usr/include",
    "../../../sdks/vstsdk2.4",
}

package.libpaths = {
    "/usr/X11R6/lib",
    "/usr/lib",
    "../../../libs"
}

package.files = {
    matchfiles (
        "../source/*.cpp",
        "../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/audioeffect.cpp",
        "../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/audioeffectx.cpp",
        "../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/vstplugmain.cpp"
    )
}
