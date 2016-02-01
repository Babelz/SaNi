#pragma once

#include "sani/core/memory/memory.hpp"

namespace sani {
	
	uint32 align(const uint32 bytes) {
		const uint32 memmod = bytes % WORD_SIZE;

		if (memmod == 0) return bytes;

		const uint32 pad = WORD_SIZE - memmod;
		const uint32 adjusted = bytes + pad;

		return adjusted;
	}
}