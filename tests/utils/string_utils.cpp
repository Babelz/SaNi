#include "sani/core/utils/string_utils.hpp"
#include "catch/catch.hpp"
#include <vector>
#include <list>

using namespace sani::utils;

TEST_CASE("String utils", "[string utils]") {

	SECTION("Trimming") {
		String orig = "   jeesus    ";

		String trimmed;
		trim(orig, trimmed);
		
		String beg;
		trimStart(orig, beg);
		
		String end;
		trimEnd(orig, end);

		REQUIRE(trimmed == "jeesus");
		REQUIRE(beg == "jeesus    ");
		REQUIRE(end == "   jeesus");
	}

	SECTION("Splitting") {
		String str = "perkele||assd||jeesus";

		std::list<String> listRes;
		std::vector<String> vectorRes;
		
		split(str, String("||"), listRes);
		split(str, String("||"), vectorRes);

		std::list<String>::iterator iter = listRes.begin();

		REQUIRE(*iter == String("perkele"));
		REQUIRE(vectorRes[0] == String("perkele"));
		std::advance(iter, 1);

		REQUIRE(*iter == String("assd"));
		REQUIRE(vectorRes[1] == String("assd"));
		std::advance(iter, 1);

		REQUIRE(*iter == String("jeesus"));
		REQUIRE(vectorRes[2] == String("jeesus"));
	}
}