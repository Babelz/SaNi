#include "sani/platform/platform_config.hpp"

// TODO: does it matter if we just with the win32 builds?
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/platform/file_system.hpp"
#include "catch/catch.hpp"
#include <list>

using namespace sani;
using namespace sani::io;

TEST_CASE("CVar loading and file tests", "[cvar]") {

	SECTION("Loading") {
		FileSystem fileSystem;
		CVarLoader cvarLoader("../../tests/configuration",
							  fileSystem);

		std::list<CVarFile> files;

		cvarLoader.load(files);

		REQUIRE(files.size() != 0);
		CHECK(files.begin()->getLinesCount() != 0);
	}
}
#endif