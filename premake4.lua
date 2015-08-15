solution "sani"
	
	configurations { "Debug", "Release" }
		flags { "ExtraWarnings" }


	configuration { "Debug" }
		targetdir "bin/debug" 
	configuration { "Release" }
		targetdir "bin/release" 

	project "sani"
	        kind "StaticLib"
		language "C++"
		files { "src/core/**.cpp", "include/**.hpp" }
		includedirs { "include" }
		buildoptions { "-std=c++11" }


	project "tests"
		kind "ConsoleApp"
		language "C++"
		buildoptions { "-std=c++11" }
		files { "tests/**.cpp", "include/**.hpp", "thirdparty/catch/include/**.hpp" }
		includedirs { "include", "thirdparty/catch/include" }
		links { "sani" }
