#pragma once
#include <vector>
#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, rtti, Argument);

namespace sani {
	namespace rtti {
		using Arguments = std::vector<Argument>;
	}
}


