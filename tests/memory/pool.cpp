#include "catch/catch.hpp"
#include "sani/core/memory/page_pool_allocator.hpp"

namespace pool {

	struct Foo {
		int a;
		int b;

		Foo() {
			a = 0;
			b = 0;
		}
	};
}

TEST_CASE("Pool", "[pool]") {

	SECTION("Pool allocator addressing") {
		sani::PagePoolAllocator<pool::Foo> allocator(4, 1);
		pool::Foo* a = allocator.allocate();
		pool::Foo* b = allocator.allocate();
		pool::Foo* c = allocator.allocate();
		pool::Foo* d = allocator.allocate();

		NEW_DYNAMIC_DEFAULT(pool::Foo, a);
		NEW_DYNAMIC_DEFAULT(pool::Foo, b);
		NEW_DYNAMIC_DEFAULT(pool::Foo, c);
		NEW_DYNAMIC_DEFAULT(pool::Foo, d);

		REQUIRE(allocator.pagesCount() == 1);

		allocator.deallocate(c);
		allocator.deallocate(b);

		pool::Foo* e = allocator.allocate();
		NEW_DYNAMIC_DEFAULT(pool::Foo, e);
		REQUIRE(e->a == 0);
		REQUIRE(e->b == 0);

		e->a = 10;
		e->b = 10;

		REQUIRE(e->a == b->a);
		REQUIRE(e->b == b->b);

		pool::Foo* g = allocator.allocate();
		NEW_DYNAMIC_DEFAULT(pool::Foo, g);
		REQUIRE(g->a == 0);
		REQUIRE(g->b == 0);

		g->a = 10;
		g->b = 10;
		
		REQUIRE(g->a == c->a);
		REQUIRE(g->b == c->b);
	}
}