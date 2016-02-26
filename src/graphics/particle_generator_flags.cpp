#include "sani/graphics/particle_generator_flags.hpp"

namespace sani {

	namespace graphics {

		bool isGeneratorFlagOn(const GeneratorFlags flags, const GeneratorFlags& what) {
			return (flags & what) == what;
		}

		GeneratorFlags operator &(GeneratorFlags lhs, const GeneratorFlags rhs) {
			lhs &= rhs;

			return lhs;
		}
		GeneratorFlags& operator &=(GeneratorFlags& lhs, const GeneratorFlags rhs) {
			const auto ilhs = static_cast<std::underlying_type<GeneratorFlags>::type>(rhs);
			const auto irhs = static_cast<std::underlying_type<GeneratorFlags>::type>(lhs);

			lhs = static_cast<GeneratorFlags>(ilhs & irhs);

			return lhs;
		}

		GeneratorFlags operator|(GeneratorFlags lhs, const GeneratorFlags rhs) {
			lhs |= rhs;

			return lhs;
		}

		GeneratorFlags& operator |=(GeneratorFlags& lhs, const GeneratorFlags rhs) {
			const auto ilhs = static_cast<std::underlying_type<GeneratorFlags>::type>(rhs);
			const auto irhs = static_cast<std::underlying_type<GeneratorFlags>::type>(lhs);

			lhs = static_cast<GeneratorFlags>(ilhs | irhs);
			
			return lhs;
		}
	}
}