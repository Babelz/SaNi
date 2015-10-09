#include "sani/core/memory/heap_allocator.hpp"
#include "catch/catch.hpp"
#include <iostream>

struct Foo {
	int a;
	int b;
};

struct Rek {
	double a;
	double b;
};

struct Kek {
	int a;
	int b;
};

TEST_CASE("Memory", "[memory]") {

	SECTION("Heap allocator") {

	}
}