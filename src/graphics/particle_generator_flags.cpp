#include "sani/graphics/particle_generator_flags.hpp"

namespace sani {

	namespace graphics {

#define __CAST_GENERATOR_FLAGS_ARGS__ const int16 iflags = static_cast<int16>(flags); \
									  const int16 iwhat = static_cast<int16>(what) \

		void toggleGeneratorFlag(GeneratorFlags& flags, const GeneratorFlags what) {
			__CAST_GENERATOR_FLAGS_ARGS__;

			flags = static_cast<GeneratorFlags>(iflags | (1 << iwhat));
		}
		void clearGeneratorFlag(GeneratorFlags& flags, const GeneratorFlags what) {
			__CAST_GENERATOR_FLAGS_ARGS__;

			flags = static_cast<GeneratorFlags>(iflags & ~(1 << iwhat));
		}

		bool isGeneratorFlagOn(const GeneratorFlags flags, const GeneratorFlags what) {
			__CAST_GENERATOR_FLAGS_ARGS__;

			return static_cast<bool>((iflags >> iwhat) & 1);
		}

		void operator |=(GeneratorFlags& lhs, const GeneratorFlags rhs) {
			const int16 ilhs = static_cast<int16>(lhs);
			const int16 irhs = static_cast<int16>(rhs);

			lhs = static_cast<GeneratorFlags>(ilhs | (irhs == 0 ? 0 : (1 << irhs)));
		}
	}
}