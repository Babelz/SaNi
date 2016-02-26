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
			const int16 ilhs = static_cast<int16>(lhs);
			const int16 irhs = static_cast<int16>(rhs);

			lhs = static_cast<GeneratorFlags>(ilhs & irhs);

			return lhs;
		}

		GeneratorFlags operator|(GeneratorFlags lhs, const GeneratorFlags rhs) {
			lhs |= rhs;

			return lhs;
		}

		GeneratorFlags& operator |=(GeneratorFlags& lhs, const GeneratorFlags rhs) {
			const int16 ilhs = static_cast<int16>(lhs);
			const int16 irhs = static_cast<int16>(rhs);

			lhs = static_cast<GeneratorFlags>(ilhs | irhs);
			
			return lhs;
		}
	}
}