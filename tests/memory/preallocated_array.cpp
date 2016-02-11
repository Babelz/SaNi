#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/core/memory/heap_allocator.hpp"
#include "catch/catch.hpp"

TEST_CASE("PreallocatedArra", "[preallocated_array]") {

	using namespace sani;

	struct Foo {
		int a;
		int b;
		int c;
		int d;
	};

	SECTION("With pool allocator") {
		volatile HeapAllocator alloc(sizeof(Foo)* 8, 4, DefragmentationPolicy::ManualUserCall);

		REQUIRE(false);
	}

	SECTION("With heap allocator") {
		REQUIRE(false);
	}
}