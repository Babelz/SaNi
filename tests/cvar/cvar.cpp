#include "sani/platform/platform_config.hpp"

// TODO: does it matter if we just with the win32 builds?
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/core/cvar/cvar_parser.hpp"
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
		
		CVarRequireStatement statement(conditions);
		
		REQUIRE(statement());
	}
}

TEST_CASE("CVar parsing", "[cvar]") {

	SECTION("CVar declarations") {
		CVarParser parser;

		String var1 = "string_var \"jeesus\"";
		String var2 = "invalid bool var 1";
		String var3 = "bool_var 0";
		String var4 = "int_var 128";
		String var5 = "float_var 0.2f";
		String var6 = "double_var 55.0 // comment...";
		String var7 = "other_int_var_with_very_long_name_and_value and with_some_syntax_errors 23242424";

		cvarlang::IntermediateCVar var1Intr;
		parser.parseCvar(var1, var1Intr);
		REQUIRE((var1Intr.name == "string_var" && var1Intr.type == cvarlang::ValueType::StringVal && var1Intr.value == "\"jeesus\""));

		cvarlang::IntermediateCVar var2Intr;
		parser.parseCvar(var2, var2Intr);
		REQUIRE(parser.hasErrors());
		parser.getNextError();

		cvarlang::IntermediateCVar var3Intr;
		parser.parseCvar(var3, var3Intr);
		REQUIRE((var3Intr.name == "bool_var" && var3Intr.value == "0" && var3Intr.type == cvarlang::ValueType::IntVal));

		cvarlang::IntermediateCVar var4Intr;
		parser.parseCvar(var4, var4Intr);
		REQUIRE((var4Intr.name == "int_var" && var4Intr.value == "128" && var4Intr.type == cvarlang::ValueType::IntVal));

		cvarlang::IntermediateCVar var5Intr;
		parser.parseCvar(var5, var5Intr);
		REQUIRE((var5Intr.name == "float_var" && var5Intr.value == "0.2f" && var5Intr.type == cvarlang::ValueType::FloatVal));

		cvarlang::IntermediateCVar var6Intr;
		parser.parseCvar(var6, var6Intr);
		REQUIRE((var6Intr.name == "double_var" && var6Intr.value == "55.0" && var6Intr.type == cvarlang::ValueType::DoubleVal));

		cvarlang::IntermediateCVar var7Intr;
		parser.parseCvar(var7, var7Intr);
		REQUIRE(parser.hasErrors());
	}

	SECTION("Requirements") {
		CVarParser parser;

		String req1 = "require (a == 10 && b)";
		String req1msg = "message(go to home)";
		cvarlang::IntermediateRequireStatement stat1Intr;
	
		parser.parseRequireStatement(req1, req1msg, stat1Intr);
		
		REQUIRE(stat1Intr.conditions.size() == 2);
		REQUIRE((stat1Intr.conditions[0].lhs == "a"));
		REQUIRE((stat1Intr.conditions[0].rhs == "10"));
		REQUIRE((stat1Intr.conditions[0].conditionalOperator == cvarlang::ConditionalOperators::Equal));
		REQUIRE((stat1Intr.conditions[0].logicalOperator == cvarlang::LogicalOperators::And));
		REQUIRE((!stat1Intr.conditions[0].lhsIsConst));
		REQUIRE((stat1Intr.conditions[0].rhsIsConst));
		REQUIRE((stat1Intr.conditions[0].logicalOperator == cvarlang::LogicalOperators::And));

		REQUIRE((stat1Intr.conditions[1].lhs == "b"));
	}
}

#endif