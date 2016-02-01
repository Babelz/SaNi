#include "catch/catch.hpp"
#include "eventmath.h"

TEST_CASE("Event tests", "[events]") {
	SECTION("Usage") {
		EventMath math;

		int a = 0, aa = 0, b = 0, c = -1;

		auto onAddHandler = SANI_EVENT_HANDLER(void(int), [&a](int result) {
			a = result;
		});
		auto onAddHandlerSecond = SANI_EVENT_HANDLER(void(int), [&aa](int result) {
			aa = result;
		});
		auto onSubHandler = SANI_EVENT_HANDLER(void(int), [&b](int result) {
			b = result;
		});
		auto onOperHandler = SANI_EVENT_HANDLER(void(void), [&c]() {
			c = 1;
		});

		math.onAdd += onAddHandler;
		math.onAdd += onAddHandlerSecond;
		math.onSub += onSubHandler;
		math.onOper += onOperHandler;

		math.add(10, 10);
		math.sub(20, 10);

		REQUIRE(a == 20);
		REQUIRE(b == 10);
		REQUIRE(c == 1);
		
		math.onAdd -= onAddHandler;
		math.onSub -= onSubHandler;
		math.onOper -= onOperHandler;

		REQUIRE(math.onAdd.hasSubscribers());
		REQUIRE(!math.onSub.hasSubscribers());
		REQUIRE(!math.onOper.hasSubscribers());

		math.add(20, 20);

		REQUIRE(aa == 40);

		math.onAdd -= onAddHandlerSecond;

		REQUIRE(!math.onAdd.hasSubscribers());
	}
}
