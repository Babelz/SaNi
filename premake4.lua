solution "sani"
	--configurations { "" }
	--flags { "" }

	configuration { "gmake" }
		--buildoptions { "" }
	configuration { "linux" }

	project "core"
		language "C++"
		files { "src/core/**.cpp", "include/sani/core/**.hpp" }
		includedirs { "include" }
-- TODOODODODODODOO