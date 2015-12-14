#include "sani/core/memory/heap_block.hpp"

namespace sani {
	
	HeapBlock::HeapBlock(char* handle, const uint32 size) : handle(handle),
		size(size),
		released(false) {
	}

	void HeapBlock::shrink(const uint32 bytes) {
		size -= bytes;
	}
	void HeapBlock::grow(const uint32 bytes) {
		size += bytes;
	}

	uint32 HeapBlock::getSize() const {
		return size;
	}
	char* HeapBlock::getHandle() const {
		return handle;
	}

	bool HeapBlock::isReleased() const {
		return released;
	}
	void HeapBlock::release() {
		released = true;
	}
	void HeapBlock::reserve() {
		released = false;
	}

	HeapBlock::~HeapBlock() {
	}

	bool HeapBlock::operator == (const HeapBlock& other) const {
		return handle == other.handle;
	}

	bool HeapBlock::operator < (const HeapBlock& other) const {
		return size < other.size;
	}
}