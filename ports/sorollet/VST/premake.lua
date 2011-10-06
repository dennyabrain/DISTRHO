
project.name = "sorollet"
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
package.config["Release"].buildoptions = { "-O2 -march=native -msse -ffast-math -fvisibility=hidden -fPIC -static" }
package.config["Release"].links        = { }

package.config["Debug"].target         = project.name .. "_debug"
package.config["Debug"].objdir         = "intermediate/Debug"
package.config["Debug"].buildoptions   = { "-O0 -ggdb -fPIC -static" }
package.config["Debug"].links          = { }

-- TODO: Check for OS
package.config["Release"].defines      = { "LINUX=1", "NDEBUG=1" };
package.config["Debug"].defines        = { "LINUX=1", "DEBUG=1" };

package.includepaths = {
    "../source",
    "../source/core",
    "../source/sys",
    "../source/vsti",
    "/usr/include",
    "../../../sdks/vstsdk2.4"
}

package.libpaths = {
    "/usr/lib",
    "../../../libs"
}

package.files = {
    matchfiles (
        "../source/core/*.cpp",
	"../source/sys/*.cpp",
	"../source/vsti/*.cpp",
	"../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/*.cpp"
    )
}
