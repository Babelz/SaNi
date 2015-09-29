#include "sani/platform/platform_config.hpp"

// TODO: does it matter if we just with the win32 builds?
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/cvar/cvar_statement.hpp"
#include "sani/core/cvar/cvar_condition.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/platform/file_system.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "catch/catch.hpp"
#include <iostream>
#include <vector>
#include <list>

using namespace sani;
using namespace sani::io;

TEST_CASE("CVar loading and file tests", "[cvar]") {

	SECTION("Loading") {
		/*
		FileSystem fileSystem;
		CVarLoader cvarLoader("../../tests/configuration",
							  fileSystem);

		std::list<CVarFile> files;

		cvarLoader.load(files);

		REQUIRE(files.size() != 0);
		CHECK(files.begin()->getLinesCount() != 0);*/
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
		
		CVarRequireStatement statement(conditions, "vittu");
		
		REQUIRE(statement());
	}
}

TEST_CASE("CVar parsing", "[cvar]") {

	SECTION("CVar declarations") {
	}

	SECTION("Requirements") {
	}

	SECTION("Record syncing") {
	}

	SECTION("Compiling") {
		const String prog(
			"a 10\n"
			"b 20\n"
			"require (a == b)\n"
			"message(can't access my_secret_str until while a does not equal b)\n"
			""
			"	my_secret_str \"hello, world!\"\n"
			"require\n");

		CVarFile file("perkele", prog);

		std::list<CVar> cvars;
		std::list<CVarFile> files;
		std::list<CVarRecord> records;

		files.push_back(file);

		CVarCompiler compiler;
		compiler.compile(files, cvars, records, true);

		REQUIRE(!compiler.hasErrors());
		REQUIRE(cvars.size() == 3);

		std::list<CVar>::iterator i = cvars.begin();

		CVar& a = *i;
		std::advance(i, 1);

		CVar& b = *i;
		std::advance(i, 1);

		CVar& my_secret_str = *i;

		REQUIRE(a != b);
		REQUIRE(!my_secret_str.canWrite());
		
		a.write(10);
		b.write(10);

		REQUIRE(my_secret_str.canWrite());
	}
}

#endif