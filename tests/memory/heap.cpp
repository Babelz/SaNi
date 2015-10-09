#include "sani/core/memory/heap_allocator.hpp"
#include "catch/catch.hpp"
#include "sani/types.hpp"
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

	SECTION("Heap allocator pages") {
		sani::HeapAllocator allocator(8, 1);

		int32* a = allocator.allocate<int32>();
		int32* b = allocator.allocate<int32>();
		int32* c = allocator.allocate<int32>();

		REQUIRE(allocator.pagesCount() == 2);
	}

	SECTION("Realloc at first released") {
		sani::HeapAllocator allocator(8, 1);

		int32* a = allocator.allocate<int32>();
		int32* b = allocator.allocate<int32>();
		*b = 10;

		allocator.deallocate(b);

		int32 *c = allocator.allocate<int32>();

		*c = 20;

		REQUIRE(*b == *c);
	}
}