#include "sani/core/logging/out_flags.hpp"

namespace sani {

	namespace log {

		OutFlags operator &(const OutFlags lhs, const OutFlags rhs) {
			const uint32 a = static_cast<uint32>(lhs); 
			const uint32 b = static_cast<uint32>(rhs);

			return static_cast<OutFlags>(a & b);
		}
	}
}