#pragma once

#include "sani/core/memory/memory.hpp"

namespace sani {
	
	uint32 pad(const uint32 bytes) {
		const uint32 memmod = bytes % WORD_SIZE;

		if (memmod == 0) return 0;

		const uint32 pad = WORD_SIZE - memmod;
		
		return pad;
	}
}