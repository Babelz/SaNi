#include "sani/core/utils/convert.hpp"
#include "catch/catch.hpp"
#include <vector>
#include <list>

using namespace sani::utils;

String intStrs[] = {
	"10",
	"123",
	"5235",
	"89942",
	"2",
	"920913",
	"124912",
	"5232515",
};

TEST_CASE("Convert utils", "[convert utils]") {
	
	SECTION("uint8 converting") {
		for (uint32 i = 0; i < 128; i++) {
			auto s = std::to_string(i);

			auto j = toUInt8(s);

			REQUIRE(j == i);
		}
	}
	SECTION("int8 converting") {
		for (uint32 i = 0; i < 128; i++) {
			auto s = std::to_string(i);

			auto j = toInt8(s);

			REQUIRE(j == i);
		}
	}
}