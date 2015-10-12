#pragma once
#include <vector>
#include "sani/types.hpp"
namespace sani {
	namespace resource {
		struct Texture2DContent {
			const uint32 width;
			const uint32 height;
			std::vector<unsigned char> pixels;
		};
	}
}