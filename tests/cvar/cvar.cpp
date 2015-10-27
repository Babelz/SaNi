#include "sani/platform/platform_config.hpp"

// TODO: does it matter if we just with the win32 builds?
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/core/cvar/link_record.hpp"
#include "sani/core/cvar/cvar_linker.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/cvar/cvar_statement.hpp"
#include "sani/core/cvar/cvar_condition.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "catch/catch.hpp"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <list>

using namespace sani;
using namespace sani::io;

TEST_CASE("CVar loading and file tests", "[cvar]") {

	SECTION("Loading") {
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

		/*
			TODO: not supported by the system yet, implement.
		*/

		auto aEqualsBOrCEqualsD = CVarCondition(cvarlang::Or, [a, b](){
			return a == b; 
		});

		auto cEqualsD = CVarCondition(cvarlang::Or, [c, d](){
			return c == d;
		});

		std::vector<CVarCondition> conditions;
		conditions.push_back(aEqualsBOrCEqualsD);
		conditions.push_back(cEqualsD);
		
		CVarRequireStatement statement(conditions, String(""));
		
		REQUIRE(statement());
	}
}

TEST_CASE("CVar parsing", "[cvar]") {

	SECTION("Record syncing") {
		String line = String("			my_int_var 10 // uncle ebons reiseronis comments          ");
		String syncReq = String("			my_int_var 128 // uncle ebons reiseronis comments          ");
		CVar cvar(cvarlang::ValueType::IntVal, "my_int_var", true, "10");
		CVarToken token(cvarlang::TokenType::Declaration, 123, "perkele", line);

		CVarRecord record(token, cvar);
	
		cvar.write(128);
		
		String synced = record.generateSyncedStringRepresentation();

		REQUIRE(synced == syncReq);
	}

	SECTION("Compiling") {
		const String prog(
			"a 10\n"
			"b 20\n"
			"require (a == b)\n"
			"message(can't access my_secret_str while a does not equal b)\n"
			""
			"	my_secret_str \"hello, world!\"\n"
			"require\n");

		CVarFile file("perkele", prog);

		std::list<CVar> cvars;
		std::list<CVarFile> files;
		std::list<CVarRecord> records;

		files.push_back(file);

		CVarCompiler compiler;
		compiler.compile("perkele", files, cvars, records);

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
		
		std::vector<String> messages;
		my_secret_str.getRequireStatementMessages(messages);

		REQUIRE(messages.size() == 1);

		for (String& message : messages) std::cout << message << std::endl;
		messages.clear();

		a.write(10);
		b.write(10);

		REQUIRE(my_secret_str.canWrite());
		
		my_secret_str.getRequireStatementMessages(messages);

		REQUIRE(messages.size() == 0);
	}

	SECTION("Compiling error catching") {
		const String prog(
			"a10\n"																// First error.
			"gg 10 // this should be just fine\n"					
			"b_ \"20dfasd\n"													// Second.
			"b 10 20 30 40 50\n"												// Third error.
			"require (jiijii)\n"												// Undefined cvar jiijii.
			"require (a == b && gg != 9)\n"										// Fourth error. System supports statements like this but does not have
			"\n"																// required regex to parse them.
			"message(can't access my_secret_str while a does not equal b)\n"	
			"\n"
			"	my_secret_str \"hello, world!\"\n"
			"// scope not closed, should throw and error\n");					// Fifth error.

		CVarFile file("perkele", prog);

		std::list<CVar> cvars;
		std::list<CVarFile> files;
		std::list<CVarRecord> records;

		files.push_back(file);

		CVarCompiler compiler;
		compiler.compile("perkele", files, cvars, records);

		REQUIRE(compiler.hasErrors());
		
		size_t i = 0;
		while (compiler.hasErrors()) {
			i++;
			std::cout << compiler.getNextError() << std::endl;
		}

		REQUIRE(i == 8);
	}

	SECTION("Operators") {
		CVar a(cvarlang::ValueType::StringVal, String("__TEMP__"), false, "\"short_str\"");
		CVar b(cvarlang::ValueType::StringVal, String("__TEMP__"), false, "\"loooong_str\"");	
		
		REQUIRE(!(a == b));
		REQUIRE(a != b);
		REQUIRE(a < b);
		REQUIRE(!(a > b));
		REQUIRE(a <= b);
		REQUIRE(!(a >= b));
	}

	SECTION("Linking") {
		const String mainContents(
			"a 10\n"
			"b 20\n"
			"include other.cfg\n");

		const String someOtherContents(
			"string_var \"hello world\"\n"
			"require(string_var == \"foo\"\n"
			"	e 20\n"
			"	include other.cfg\n"
			"require\n");

		const String otherContents(
			"include someother.cfg\n"
			"c 20\n"
			"d 30\n");

		CVarFile main("main.cfg", mainContents);
		CVarFile someOther("someother.cfg", someOtherContents);
		CVarFile other("other.cfg", otherContents);
		
		std::list<CVarFile> files;
		files.push_back(main);
		files.push_back(someOther);
		files.push_back(other);
		
		CVarLinker linker;
		LinkRecord record;

		linker.link("main.cfg", files, &record);

		REQUIRE(linker.hasErrors());

		while (linker.hasErrors()) std::cout << linker.getNextError() << std::endl;
	}
}

#endif