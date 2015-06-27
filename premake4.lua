solution "sani"
	
	configurations { "Debug", "Release" }
		flags { "ExtraWarnings" }


	configuration { "Debug" }
		targetdir "bin/debug" 
	configuration { "Release" }
		targetdir "bin/release" 

	configuration { "gmake" }
		buildoptions { "-std=c++11" }

	project "core"
        kind "StaticLib"
		language "C++"
		files { "src/core/**.cpp", "include/sani/core/**.hpp" }
		includedirs { "include" }

		configuration "linux"
			links { "platform" }

	project "platform"
    	kind "StaticLib"
		language "C++"
		files { "src/platform/**.cpp", "include/sani/platform/**.hpp" }
		includedirs { "include" }

	project "tests"
		kind "ConsoleApp"
		language "C++"
		files { "tests/**.cpp", "include/sani/**.hpp", "thirdparty/include/**.hpp" }
		includedirs { "include", "thirdparty/include" }
	configuration "linux"
		links { "platform", "core" }
-- TODOODODODODODOO
