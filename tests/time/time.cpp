#include "catch/catch.hpp"
#include "sani/platform/time/stopwatch.hpp"
#include <Windows.h>

TEST_CASE("Tim", "[time]") {

	SECTION("Stopwatch") {
		sani::Stopwatch<float> sw;

		sw.start();

		Sleep(250);

		sw.stop();

		REQUIRE(sw.getElapsedMilliseconds() >= 250.0f);
	}
}