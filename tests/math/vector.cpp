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

TEST_CASE("Vector3 test cases", "[vector]") {
	SECTION("Operators") {
		REQUIRE(Vec3() == Vec3(0, 0, 0));
		REQUIRE(Vec3(0, 0, 0) == Vec3(Vec3i(0, 0, 0)));
		REQUIRE(Vec3() == Vec3(0));
		REQUIRE(Vec3() == Vec3u(0));
		REQUIRE(Vec3(Vec2(2, 3), 4) == Vec3(2, 3, 4));
		REQUIRE(Vec3(5, 6, 7).z == Vec3(5, 6, 7)[2]);
	}

	SECTION("Arithmetics") {
		REQUIRE(Vec3(1, 0, 0).length() == 1);
		REQUIRE(Vec3(1, 0, 0).lengthSquared() == 1);
		REQUIRE(Vec3(0, 3, 0).length() == 3);
		REQUIRE(Vec3(0, 3, 0).lengthSquared() == 9);

		REQUIRE(Vec3(1, 0, 0).isNormalized());
		REQUIRE(Vec3(0, 1, 0).isNormalized());
		REQUIRE_FALSE(Vec3(13, 37, 37).isNormalized());

		REQUIRE((Vec3(5, 5, 5) + Vec3(5, 5, 5)) == Vec3(10, 10, 10));
		REQUIRE((Vec3(5, 5, 3) - Vec3(5, 5, 5)) == Vec3(0, 0, -2));
		REQUIRE((Vec3(5, 5, 3) * Vec3(5, 5, 5)) == Vec3(25, 25, 15));
		REQUIRE((Vec3(5, 5, 2) / Vec3(5, 5, 1)) == Vec3(1, 1, 2));
		REQUIRE((Vec3(5, 5, 4) * 5) == Vec3(25, 25, 20));
		REQUIRE((Vec3(5, 5, 5) / 5) == Vec3(1, 1, 1));
		REQUIRE(-Vec3(5, 5, 5) == Vec3(-5, -5, -5));
	}
}

TEST_CASE("Vector4 test cases", "[vector]") {
	SECTION("Operators") {
		REQUIRE(Vec4() == Vec4(0, 0, 0, 0));
		REQUIRE(Vec4(0, 0, 0, 0) == Vec4(Vec4i(0, 0, 0, 0)));
		REQUIRE(Vec4() == Vec4(0));
		REQUIRE(Vec4() == Vec4u(0));
		REQUIRE(Vec4(Vec2(2, 3), 4, 5) == Vec4(2, 3, 4, 5));
		REQUIRE(Vec4(Vec3(2, 3, 4), 5) == Vec4(2, 3, 4, 5));
		REQUIRE(Vec4(Vec2(2, 3), Vec2( 4, 5)) == Vec4(2, 3, 4, 5));
		REQUIRE(Vec4(5, 6, 7, 8).w == Vec4(5, 6, 7, 8)[3]);
	}

	SECTION("Arithmetics") {
		REQUIRE(Vec4(1, 0, 0, 0).length() == 1);
		REQUIRE(Vec4(1, 0, 0, 0).lengthSquared() == 1);
		REQUIRE(Vec4(0, 3, 0, 0).length() == 3);
		REQUIRE(Vec4(0, 3, 0, 0).lengthSquared() == 9);

		REQUIRE(Vec4(1, 0, 0, 0).isNormalized());
		REQUIRE(Vec4(0, 0, 1, 0).isNormalized());
		REQUIRE_FALSE(Vec4(0, 13, 37, 37).isNormalized());

		REQUIRE((Vec4(5, 5, 5, 5) + Vec4(5, 5, 5, 7)) == Vec4(10, 10, 10, 12));
		REQUIRE((Vec4(5, 5, 3, 2) - Vec4(5, 5, 5, 2)) == Vec4(0, 0, -2, 0));
		REQUIRE((Vec4(5, 5, 3, 4) * Vec4(5, 5, 5, 2)) == Vec4(25, 25, 15, 8));
		REQUIRE((Vec4(5, 5, 2, 10) / Vec4(5, 5, 1, 2)) == Vec4(1, 1, 2, 5));
		REQUIRE((Vec4(5, 5, 4, 2) * 5) == Vec4(25, 25, 20, 10));
		REQUIRE((Vec4(5, 5, 5, 10) / 5) == Vec4(1, 1, 1, 2));
		REQUIRE(-Vec4(5, 5, 5, 10) == Vec4(-5, -5, -5, -10));
	}
}