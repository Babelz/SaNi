#include "catch/catch.hpp"
#include "eventmath.h"

TEST_CASE("Event tests", "[events]") {
	SECTION("Usage") {
		EventMath math;

		int a = 0, b = 0, c = -1;

		math.onAdd += SANI_CALLBACK(void(int), [&a](int result) {
			a = result;
		});
		math.onSub += SANI_CALLBACK(void(int), [&b](int result) {
			b = result;
		});
		math.onOper += SANI_CALLBACK(void(void), [&c]() {
			c = 1;
		});

		math.add(10, 10);
		math.sub(20, 10);

		REQUIRE(a == 20);
		REQUIRE(b == 10);
		REQUIRE(c == 1);
	}
}