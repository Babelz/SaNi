#include "catch/catch.hpp"
#include "sani/core/math/rectangle.hpp"

using namespace sani::math;

TEST_CASE("Rectangle test cases", "[rectangle]") {

	SECTION("Operators") {
		REQUIRE(Rect() == Rect(0, 0, 0, 0));

		REQUIRE(Rect(1, 1, 0, 0) == Rect(1, 1, 0, 0));
		REQUIRE(Rect(1, 1, 0, 0) != Rect(0, 0, 1, 1));

		REQUIRE(Rect(1, 1, 1, 1).x == 1);
		REQUIRE(Rect(1, 1, 1, 1).y == 1);
		REQUIRE(Rect(1, 1, 1, 1).h == 1);
		REQUIRE(Rect(1, 1, 1, 1).w == 1);

		REQUIRE(Rect(0, 0, 1) == Rect(0, 0, 1, 1));

		Rect r1(1, 1, 1, 1);
		Rect r2 = r1;

		REQUIRE(r1 == r2);
	}

	SECTION("Functions") {
		Rectf r(10.0f, 10.0f, 32.0f, 32.0f);
		REQUIRE(r.center().x == 26.0f);
		REQUIRE(r.center().y == 26.0f);
		REQUIRE(r.size().x == 32.0f);
		REQUIRE(r.size().y == 32.0f);
		REQUIRE(r.position().x == 10.0f);
		REQUIRE(r.position().y == 10.0f);
		REQUIRE(!r.isEmpty());
		
		REQUIRE(Rectf(0.0f, 0.0f, 0.0f).isEmpty());

		REQUIRE(r.intersects(Rectf(5.0f, 5.0f, 32.0f, 32.0f)));
		REQUIRE(r.contains(Vec2(16.0f, 16.0f)));
		REQUIRE(r.contains(16.0f, 16.0f));
	}
}


