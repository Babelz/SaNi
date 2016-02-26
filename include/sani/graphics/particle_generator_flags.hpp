#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		enum class GeneratorFlags : int16 {
			None						= 0,
			VaryingSpawnLocation		= 1,	// Bits from 1 to 13. First bit (0) reserved 
			VaryingVelocity				= 2,	// to be a "null"
			VaryingAcceleration			= 4,
			VaryingScale				= 8,
			VaryingScaleAcceleration	= 16,
			UseScaleAcceleration		= 32,
			VaryingScaleVelocity		= 64,
			UseScaleVelocity			= 128,
			VaryingAngularVelocity		= 256,
			VaryingAngularAcceleration	= 512,
			VaryingDecayTime			= 1024,
			VaryingColor				= 2048,
			VaryingAttributes			= 4096	
		};

		bool isGeneratorFlagOn(const GeneratorFlags flags, const GeneratorFlags& what);

		GeneratorFlags operator &(GeneratorFlags lhs, const GeneratorFlags rhs);
		GeneratorFlags& operator &=(GeneratorFlags& lhs, const GeneratorFlags rhs);

		GeneratorFlags operator|(GeneratorFlags lhs, const GeneratorFlags rhs);
		GeneratorFlags& operator |=(GeneratorFlags& lhs, const GeneratorFlags rhs);
	}
}