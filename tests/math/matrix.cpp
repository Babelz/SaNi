#include "catch/catch.hpp"
#include "sani/core/math/matrix2.hpp"
#include "sani/core/math/vector.hpp"
using namespace sani::math;
TEST_CASE("Mat2x2 test cases", "[matrix]") {

	SECTION("Operators") {
		REQUIRE(Mat2() == Mat2(1, 0, 0, 1));
		REQUIRE(Mat2(Vec2(1, 0), Vec2(0, 1)) == Mat2());
		Mat2 identity;
		REQUIRE(Mat2(identity) == Mat2(1, 0, 0, 1));
	}

	SECTION("Arithmetic") {
		REQUIRE((Mat2() * 2) == Mat2(2, 0, 0, 2));
		REQUIRE((Mat2() + Mat2(1,1,1,1)) == Mat2(2, 1, 1, 2));
		REQUIRE((Mat2() - Mat2(1, 1, 1, 1)) == Mat2(0, -1, -1, 0));
		REQUIRE((Mat2(5,5,5,5) / 5) == Mat2(1, 1, 1, 1));
		REQUIRE((Mat2(2, 4, 6, 8) / 2) == Mat2(1, 2, 3, 4));
		Mat2 mat(1, 2, 3, 4);
		mat += Mat2(5,5,5,5);
		REQUIRE(mat == Mat2(6, 7, 8, 9));
		mat -= Mat2(3, 3, 3, 3);
		REQUIRE(mat == Mat2(3, 4, 5, 6));
		mat *= 2;
		REQUIRE(mat == Mat2(6, 8, 10, 12));
		mat /= 2;
		REQUIRE(mat == Mat2(3, 4, 5, 6));
		REQUIRE((2.f * mat) == Mat2(6, 8, 10, 12));
	}
}


