#include "catch/catch.hpp"
#include "sani/core/math/vector.hpp"

using namespace sani::math;
TEST_CASE("Vector2 test cases", "[vector]") {
	
	SECTION("Operators") {
		REQUIRE(Vec2() == Vec2(0, 0));
		REQUIRE(Vec2(0, 0) == Vec2(Vec2i(0, 0)));
		REQUIRE(Vec2() == Vec2(0));
		REQUIRE(Vec2() == Vec2u(0));
		REQUIRE(Vec2(5, 6).x == Vec2(5, 6)[0]);
	}

	SECTION("Arithmetics") {
		REQUIRE(Vec2(1, 0).length() == 1);
		REQUIRE(Vec2(1, 0).lengthSquared() == 1);
		REQUIRE(Vec2(0, 3).length() == 3);
		REQUIRE(Vec2(0, 3).lengthSquared() == 9);

		REQUIRE(Vec2(1, 0).isNormalized());
		REQUIRE(Vec2(0, 1).isNormalized());
		REQUIRE_FALSE(Vec2(13, 37).isNormalized());

		REQUIRE((Vec2(5, 5) + Vec2(5, 5)) == Vec2(10, 10));
		REQUIRE((Vec2(5, 5) - Vec2(5, 5)) == Vec2(0, 0));
		REQUIRE((Vec2(5, 5) * Vec2(5, 5)) == Vec2(25, 25));
		REQUIRE((Vec2(5, 5) / Vec2(5, 5)) == Vec2(1, 1));
		REQUIRE((Vec2(5, 5) * 5) == Vec2(25, 25));
		REQUIRE((Vec2(5, 5) / 5) == Vec2(1, 1));
		REQUIRE(-Vec2(5, 5) == Vec2(-5, -5));
	}
	
}