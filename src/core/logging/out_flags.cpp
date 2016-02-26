#include "sani/core/logging/out_flags.hpp"

namespace sani {

	namespace log {

		OutFlags operator &(const OutFlags lhs, const OutFlags rhs) {
			const auto ilhs = static_cast<std::underlying_type<OutFlags>::type>(rhs);
			const auto irhs = static_cast<std::underlying_type<OutFlags>::type>(lhs);

			return static_cast<OutFlags>(ilhs & irhs);
		}
	}
}