#include "sani/platform/platform_config.hpp"

// TODO: does it matter if we just with the win32 builds?
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/core/cvar/cvar_statement.hpp"
#include "sani/core/cvar/cvar_condition.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/platform/file_system.hpp"
#include "catch/catch.hpp"
#include <vector>
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

TEST_CASE("CVar conditionals", "[cvar]") {

	/*
		TODO: test more or test in production ":D"
	*/
	SECTION("Statements") {
		const int a = 5;
		const int b = 5;
		const int c = 10;
		const int d = 10;

		auto aEqualsBOrCEqualsD = CVarCondition(cvarlang::Or, [a, b](){
			return a == b; 
		});

		auto cEqualsD = CVarCondition(cvarlang::Or, [c, d](){
			return c == d;
		});

		std::vector<CVarCondition> conditions;
		conditions.push_back(aEqualsBOrCEqualsD);
		conditions.push_back(cEqualsD);
		
		CVarRequireStatement statement(conditions);
		
		REQUIRE(statement());
	}
}

#endif