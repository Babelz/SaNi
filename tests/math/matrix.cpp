#include "catch/catch.hpp"
#include "sani/core/math/matrix2.hpp"
#include "sani/core/math/matrix3.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/core/math/vector.hpp"
#include "sani/core/math/func/transform.hpp"

using namespace sani::math;
TEST_CASE("Mat2x2 test cases", "[matrix]") {

	SECTION("Operators") {
		REQUIRE(Mat2() == Mat2(1, 0, 0, 1));
		REQUIRE(Mat2(Vec2(1, 0), Vec2(0, 1)) == Mat2());
		Mat2 identity;
		REQUIRE(Mat2(identity) == Mat2(1, 0, 0, 1));
		REQUIRE(Mat2(Mat2i()) == Mat2());
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

TEST_CASE("Mat3x3 tests cases", "[matrix]") {
	SECTION("Operators") {
		REQUIRE(Mat3() == Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1));
		REQUIRE(Mat3(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1)) == Mat3());
		Mat3 identity;
		REQUIRE(Mat3(identity) == Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1));
		REQUIRE(Mat3(Mat3i()) == Mat3());
	}

	SECTION("Arithmetic") {
		REQUIRE((Mat3() * 2) == Mat3(2, 0, 0, 0, 2, 0, 0, 0, 2));
		REQUIRE((Mat3() + Mat3(1, 1, 1, 1, 1, 1, 1, 1, 1)) == Mat3(2, 1, 1, 1, 2, 1, 1, 1, 2));
		REQUIRE((Mat3() - Mat3(1, 1, 1, 1, 1, 1, 1, 1, 1)) == Mat3(0, -1, -1, -1, 0, -1, -1, -1, 0));
		REQUIRE((Mat3(2, 4, 6, 2, 4, 6, 2, 4, 6) / 2) == Mat3(1, 2, 3, 1, 2, 3, 1, 2, 3));
		Mat3 mat(1, 2, 3, 1, 2, 3, 1, 2, 3);
		mat += Mat3(5, 5, 5, 5, 5, 5, 5, 5, 5);
		REQUIRE(mat == Mat3(6, 7, 8, 6, 7, 8, 6,7,8));
		mat -= Mat3(3, 3, 3, 3, 3, 3, 3, 3, 3);
		REQUIRE(mat == Mat3(3, 4, 5, 3, 4, 5, 3, 4, 5));
		mat *= 2;
		REQUIRE(mat == Mat3(6, 8, 10, 6, 8, 10, 6, 8, 10));
		mat /= 2;
		REQUIRE(mat == Mat3(3, 4, 5, 3, 4, 5, 3, 4, 5));
		REQUIRE((Mat3() * Mat3()) == Mat3());

		Mat3 a(0, -1, 2, 1, 0, 3, 2, 5, 1);
		Mat3 b(1, 2, 3, 1, 2, 3, 1, 2, 3);
		Mat3 result(1, 2, 3, 4, 8, 12, 8, 16, 24);
		Mat3 value(a * b);
		REQUIRE(value == result);

	}
}

TEST_CASE("Mat4x4 tests cases", "[matrix]") {
	SECTION("Operators") {
		REQUIRE(Mat4() == Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
		REQUIRE(Mat4(Vec4(1, 0, 0, 0), Vec4(0, 1, 0, 0), Vec4(0, 0, 1, 0), Vec4(0, 0, 0, 1)) == Mat4());
		Mat4 identity;
		REQUIRE(Mat4(identity) == Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
		REQUIRE(Mat4(Mat4i()) == Mat4());
	}

	SECTION("Arithmetic") {
		REQUIRE((Mat4() * 2) == Mat4(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2));
		REQUIRE((Mat4() + Mat4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)) == Mat4(2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2));
		REQUIRE((Mat4() - Mat4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)) == Mat4(0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0));
		REQUIRE((Mat4(2, 4, 6, 8, 2, 4, 6, 8, 2, 4, 6, 8, 2, 4, 6, 8) / 2) == Mat4(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4));
		Mat4 mat(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4);
		mat += Mat4(5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5);
		REQUIRE(mat == Mat4(6, 7, 8, 9, 6, 7, 8, 9, 6, 7, 8, 9, 6, 7, 8, 9));
		mat -= Mat4(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);
		REQUIRE(mat == Mat4(3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6));
		mat *= 2;
		REQUIRE(mat == Mat4(6, 8, 10, 12, 6, 8, 10, 12, 6, 8, 10, 12, 6, 8, 10, 12));
		mat /= 2;
		REQUIRE(mat == Mat4(3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6));
		REQUIRE((Mat4() * Mat4()) == Mat4());

		Mat4 a(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
		Mat4 b(16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1);
		Mat4 result(80, 70, 60, 50, 240, 214, 188, 162, 400, 358, 316, 274, 560, 502, 444, 386);
		Mat4 value(a * b);
		REQUIRE(value == result);
	}
}

TEST_CASE("Arithmetic funcs", "[matrix]") {
	
	SECTION("Translation") {
		Mat4 mat;
		Vec3 translation(5, 5, 5);
		Mat4 translationMat(translate(mat, translation));
		REQUIRE(translationMat[3] == Vec4(translation.x, translation.y, translation.z, 1));
	}
}