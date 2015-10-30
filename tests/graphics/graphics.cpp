#include "sani/graphics/buffer.hpp"
#include "catch/catch.hpp"
#include "sani/types.hpp"

TEST_CASE("Buffer", "[buffer]") {

	SECTION("Buffer pointer testing") {
		sani::graphics::Buffer<uint32> buffer(10, sani::graphics::BufferSizing::Static);

		for (uint32 i = 0; i < buffer.getSize(); i++) buffer.push(i);

		uint32* headPtr = buffer.pointer();

		for (uint32 i = 0; i < buffer.getSize(); i++) REQUIRE(headPtr[i] == i);
	}
}