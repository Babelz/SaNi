#pragma once

#include "sani/core/memory/memory.hpp"

namespace sani {
	
	uint32 pad(const uint32 bytes) {
		const uint32 memmod = bytes % WordSize;

		if (memmod == 0) return 0;

		const uint32 pad = WordSize - memmod;
		
		return pad;
	}
}