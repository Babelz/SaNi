#include "catch/catch.hpp"
#include "sani/core/math/vector.hpp"

using namespace sani::math;
TEST_CASE("Vector2 test cases", "[vector]") {
	
	SECTION("Operators") {
		REQUIRE(Vec2f() == Vec2f(0, 0));
		REQUIRE(Vec2f(0, 0) == Vec2f(Vec2i(0, 0)));
		REQUIRE(Vec2f() == Vec2f(0));
		REQUIRE(Vec2f() == Vec2u(0));
		REQUIRE(Vec2f(5, 6).x == Vec2f(5, 6)[0]);
	}

	SECTION("Arithmetics") {
		REQUIRE(Vec2f(1, 0).length() == 1);
		REQUIRE(Vec2f(1, 0).lengthSquared() == 1);
		REQUIRE(Vec2f(0, 3).length() == 3);
		REQUIRE(Vec2f(0, 3).lengthSquared() == 9);

		REQUIRE(Vec2f(1, 0).isNormalized());
		REQUIRE(Vec2f(0, 1).isNormalized());
		REQUIRE_FALSE(Vec2f(13, 37).isNormalized());

		REQUIRE((Vec2f(5, 5) + Vec2f(5, 5)) == Vec2f(10, 10));
		REQUIRE((Vec2f(5, 5) - Vec2f(5, 5)) == Vec2f(0, 0));
		REQUIRE((Vec2f(5, 5) * Vec2f(5, 5)) == Vec2f(25, 25));
		REQUIRE((Vec2f(5, 5) / Vec2f(5, 5)) == Vec2f(1, 1));
		REQUIRE((Vec2f(5, 5) * 5) == Vec2f(25, 25));
		REQUIRE((Vec2f(5, 5) / 5) == Vec2f(1, 1));
		REQUIRE(-Vec2f(5, 5) == Vec2f(-5, -5));
	}
	
}

TEST_CASE("Vector3 test cases", "[vector]") {
	SECTION("Operators") {
		REQUIRE(Vec3f() == Vec3f(0, 0, 0));
		REQUIRE(Vec3f(0, 0, 0) == Vec3f(Vec3i(0, 0, 0)));
		REQUIRE(Vec3f() == Vec3f(0));
		REQUIRE(Vec3f() == Vec3u(0));
		REQUIRE(Vec3f(Vec2f(2, 3), 4) == Vec3f(2, 3, 4));
		REQUIRE(Vec3f(5, 6, 7).z == Vec3f(5, 6, 7)[2]);
	}

	SECTION("Arithmetics") {
		REQUIRE(Vec3f(1, 0, 0).length() == 1);
		REQUIRE(Vec3f(1, 0, 0).lengthSquared() == 1);
		REQUIRE(Vec3f(0, 3, 0).length() == 3);
		REQUIRE(Vec3f(0, 3, 0).lengthSquared() == 9);

		REQUIRE(Vec3f(1, 0, 0).isNormalized());
		REQUIRE(Vec3f(0, 1, 0).isNormalized());
		REQUIRE_FALSE(Vec3f(13, 37, 37).isNormalized());

		REQUIRE((Vec3f(5, 5, 5) + Vec3f(5, 5, 5)) == Vec3f(10, 10, 10));
		REQUIRE((Vec3f(5, 5, 3) - Vec3f(5, 5, 5)) == Vec3f(0, 0, -2));
		REQUIRE((Vec3f(5, 5, 3) * Vec3f(5, 5, 5)) == Vec3f(25, 25, 15));
		REQUIRE((Vec3f(5, 5, 2) / Vec3f(5, 5, 1)) == Vec3f(1, 1, 2));
		REQUIRE((Vec3f(5, 5, 4) * 5) == Vec3f(25, 25, 20));
		REQUIRE((Vec3f(5, 5, 5) / 5) == Vec3f(1, 1, 1));
		REQUIRE(-Vec3f(5, 5, 5) == Vec3f(-5, -5, -5));
	}
}

TEST_CASE("Vector4 test cases", "[vector]") {
	SECTION("Operators") {
		REQUIRE(Vec4f() == Vec4f(0, 0, 0, 0));
		REQUIRE(Vec4f(0, 0, 0, 0) == Vec4f(Vec4i(0, 0, 0, 0)));
		REQUIRE(Vec4f() == Vec4f(0));
		REQUIRE(Vec4f() == Vec4u(0));
		REQUIRE(Vec4f(Vec2f(2, 3), 4, 5) == Vec4f(2, 3, 4, 5));
		REQUIRE(Vec4f(Vec3f(2, 3, 4), 5) == Vec4f(2, 3, 4, 5));
		REQUIRE(Vec4f(Vec2f(2, 3), Vec2f( 4, 5)) == Vec4f(2, 3, 4, 5));
		REQUIRE(Vec4f(5, 6, 7, 8).w == Vec4f(5, 6, 7, 8)[3]);
	}

	SECTION("Arithmetics") {
		REQUIRE(Vec4f(1, 0, 0, 0).length() == 1);
		REQUIRE(Vec4f(1, 0, 0, 0).lengthSquared() == 1);
		REQUIRE(Vec4f(0, 3, 0, 0).length() == 3);
		REQUIRE(Vec4f(0, 3, 0, 0).lengthSquared() == 9);

		REQUIRE(Vec4f(1, 0, 0, 0).isNormalized());
		REQUIRE(Vec4f(0, 0, 1, 0).isNormalized());
		REQUIRE_FALSE(Vec4f(0, 13, 37, 37).isNormalized());

		REQUIRE((Vec4f(5, 5, 5, 5) + Vec4f(5, 5, 5, 7)) == Vec4f(10, 10, 10, 12));
		REQUIRE((Vec4f(5, 5, 3, 2) - Vec4f(5, 5, 5, 2)) == Vec4f(0, 0, -2, 0));
		REQUIRE((Vec4f(5, 5, 3, 4) * Vec4f(5, 5, 5, 2)) == Vec4f(25, 25, 15, 8));
		REQUIRE((Vec4f(5, 5, 2, 10) / Vec4f(5, 5, 1, 2)) == Vec4f(1, 1, 2, 5));
		REQUIRE((Vec4f(5, 5, 4, 2) * 5) == Vec4f(25, 25, 20, 10));
		REQUIRE((Vec4f(5, 5, 5, 10) / 5) == Vec4f(1, 1, 1, 2));
		REQUIRE(-Vec4f(5, 5, 5, 10) == Vec4f(-5, -5, -5, -10));
	}
}