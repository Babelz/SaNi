#include "sani/core/memory/heap_allocator.hpp"
#include "catch/catch.hpp"
#include "sani/types.hpp"
#include <iostream>

struct Foo {
	int a;
	int b;

	Foo() {
		a = 128;
		b = 128;
	}
};

struct BigFoo {
	int a;
	int b;
	int c;
	int d;
};

struct Rek {
	double a;
	double b;

	Rek() {
		a = 128;
		b = 128;
	}
};

struct Kek {
	int a;
	int b;
	
	Kek(const int a, const int b) : a(a), b(b) {
	}

	Kek() {
		a = 128;
		b = 128;
	}

	~Kek() {
		a = -1;
		b = -1;
	}
};

TEST_CASE("Memory", "[memory]") {

	SECTION("Heap allocator pages") {
		sani::HeapAllocator allocator(8, 1, sani::DefragmentationPolicy::Manual);

		int32* a = allocator.allocate<int32>();
		int32* b = allocator.allocate<int32>();
		int32* c = allocator.allocate<int32>();

		REQUIRE(allocator.pagesCount() == 2);
	}

	SECTION("Realloc at first released") {
		sani::HeapAllocator allocator(8, 1, sani::DefragmentationPolicy::Manual);

		int32* a = allocator.allocate<int32>();
		int32* b = allocator.allocate<int32>();
		*b = 10;

		allocator.deallocate(b);

		int32 *c = allocator.allocate<int32>();

		*c = 20;

		REQUIRE(*b == *c);
	}

	SECTION("Alloc diff types") {
		sani::HeapAllocator allocator(16, 1, sani::DefragmentationPolicy::Manual);

		Foo* foo = allocator.allocate<Foo>();
		Kek* kek = allocator.allocate<Kek>();
		Rek* rek = allocator.allocate<Rek>(); 
		
		NEW_DYNAMIC_DEFAULT(Foo, foo);
		NEW_DYNAMIC_DEFAULT(Kek, kek);
		NEW_DYNAMIC_DEFAULT(Rek, rek);

		REQUIRE(foo->a == 128);
		REQUIRE(foo->b == 128);

		REQUIRE(kek->a == 128);
		REQUIRE(kek->a == 128);
		
		REQUIRE(rek->a == 128);
		REQUIRE(rek->a == 128);

		allocator.deallocate(foo);
		allocator.deallocate(kek);
		allocator.deallocate(rek);

		REQUIRE(kek->a == -1);
		REQUIRE(kek->b == -1);

		kek = allocator.allocate<Kek>();
		NEW_DYNAMIC(Kek, kek, 30, 40);

		REQUIRE(kek->a == 30);
		REQUIRE(kek->b == 40);
	}

	SECTION("Alloc diff types") {
		sani::HeapAllocator allocator(16, 1, sani::DefragmentationPolicy::Manual);

		// Heap: | 4 | 4 | 4 | 4 |
		int* a = allocator.allocate<int>();
		int* b = allocator.allocate<int>();
		int* c = allocator.allocate<int>();
		int* d = allocator.allocate<int>();

		// Heap: | 4 | f4 | f4 | 4 |
		allocator.deallocate(b);
		allocator.deallocate(c);

		allocator.defragment();

		*b = 255;
		*c = 255;

		Kek* kek = allocator.allocate<Kek>();
		NEW_DYNAMIC(Kek, kek, 255, 10);
		
		allocator.deallocate(kek);

		BigFoo* foo = allocator.allocate<BigFoo>();
		REQUIRE(allocator.fragmented());
	}

	SECTION("Fragmentation") {
		sani::HeapAllocator allocator(64, 1, sani::DefragmentationPolicy::Manual);
		REQUIRE(!allocator.fragmented());

		// Fill.
		// First 32-bytes.
		Foo* a = allocator.allocate<Foo>();
		Foo* b = allocator.allocate<Foo>();
		Foo* c = allocator.allocate<Foo>();
		Foo* d = allocator.allocate<Foo>();

		// Second 32-bytes. Page is now full.
		Foo* e = allocator.allocate<Foo>();
		Foo* f = allocator.allocate<Foo>();
		Foo* g = allocator.allocate<Foo>();
		Foo* h = allocator.allocate<Foo>();

		REQUIRE(allocator.pagesCount() == 1);
		REQUIRE(!allocator.fragmented());

		// Release c, d, e and f to make some fragmentation.
		allocator.deallocate(c);
		allocator.deallocate(d);
		allocator.deallocate(e);
		allocator.deallocate(f);

		REQUIRE(allocator.fragmented());
		REQUIRE(!allocator.shouldDefragment());

		// Do some failed allocations.
		BigFoo* fA = allocator.allocate<BigFoo>();
		BigFoo* fB = allocator.allocate<BigFoo>();
		BigFoo* fC = allocator.allocate<BigFoo>();
		BigFoo* fD = allocator.allocate<BigFoo>();

		REQUIRE(allocator.shouldDefragment());
		REQUIRE(allocator.pagesCount() > 1);
		REQUIRE(allocator.getFragmentation() == 1.0f);

		std::cout << "Fragmentation with " << allocator.pagesCount() << " pages: " << allocator.getFragmentation() << std::endl;

		allocator.defragment();

		std::cout << "Fragmentation after defrag: " << allocator.getFragmentation() << std::endl;
	}
}