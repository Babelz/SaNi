#include "sani/core/memory/preallocated_array.hpp"
#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/core/memory/heap_allocator.hpp"
#include "catch/catch.hpp"

using namespace sani;

struct Foo64 {
	int nums[16];
};

TEST_CASE("PreallocatedArra", "[preallocated_array]") {

	SECTION("With pool allocator") {
		HeapAllocator alloc(sizeof(Foo64)* 8, 1, DefragmentationPolicy::ManualUserCall);

		PreallocatedStaticArray<Foo64, HeapAllocator> arr(4, alloc);

		for (uint32 i = 0; i < arr.size(); i++) {
			Foo64* f = &arr[i];
			
			for (int32 j = 0; j < sizeof(f->nums) / sizeof(int); j++) f->nums[j] = i;
		}

		for (uint32 i = 0; i < arr.size(); i++) {
			Foo64* f = &arr[i];

			for (int32 j = 0; j < sizeof(f->nums) / sizeof(int); j++) REQUIRE(f->nums[j] == i);
		}

		arr.~PreallocatedStaticArray();

		REQUIRE(alloc.getBytesUsed() == 0);
	}

	SECTION("With heap allocator") {
		PagePoolAllocator<Foo64> alloc(16, 1);

		PreallocatedStaticArray<Foo64, PagePoolAllocator<Foo64>> arr(8, alloc);

		for (uint32 i = 0; i < arr.size(); i++) {
			Foo64* f = &arr[i];

			for (int32 j = 0; j < sizeof(f->nums) / sizeof(int); j++) f->nums[j] = i;
		}

		for (uint32 i = 0; i < arr.size(); i++) {
			Foo64* f = &arr[i];

			for (int32 j = 0; j < sizeof(f->nums) / sizeof(int); j++) REQUIRE(f->nums[j] == i);
		}

		arr.~PreallocatedStaticArray();

		REQUIRE(alloc.getBytesUsed() == 0);
	}
}