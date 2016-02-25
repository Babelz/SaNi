#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		enum class GeneratorFlags : int16 {
			None = 0,
			VaryingSpawnLocation,	    // Bits from 1 to 13. First bit (0) reserved 
			VaryingVelocity,			// to be a "null"
			VaryingAcceleration,
			VaryingScale,
			VaryingScaleAcceleration,
			UseScaleAcceleration,
			VaryingScaleVelocity,
			UseScaleVelocity,
			VaryingAngularVelocity,
			VaryingAngularAcceleration,
			VaryingDecayTime,
			VaryingColor,
			VaryingAttributes	
		};

		void toggleGeneratorFlag(GeneratorFlags& flags, const GeneratorFlags what);
		void clearGeneratorFlag(GeneratorFlags& flag, const GeneratorFlags what);
		
		bool isGeneratorFlagOn(const GeneratorFlags flags, const GeneratorFlags what);

		void operator |=(GeneratorFlags& lhs, const GeneratorFlags rhs);
	}
}