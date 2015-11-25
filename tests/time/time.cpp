#include "catch/catch.hpp"
#include "sani/platform/time/stopwatch.hpp"
#include <Windows.h>

TEST_CASE("Tim", "[time]") {

	SECTION("Stopwatch") {
		sani::Stopwatch<float> sw;

		sw.start();

		Sleep(2500);

		sw.stop();

		float ms = sw.getElapsedMilliseconds();
		float s = sw.getElapsedSeconds();

		REQUIRE(ms >= 250.0f);
		REQUIRE(s >= 1.0f);
	}
}