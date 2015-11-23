#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace math {

		namespace random {

			inline int8 nextInt8(const int8 min, const int8 max);
			inline uint8 nextUInt8(const int8 min, const int8 max);

			inline int16 nextInt16(const int16 min, const int16 max);
			inline uint16 nextUInt16(const uint16 min, const uint16 max);

			inline int32 nextInt32(const int32 min, const int32 max);
			inline uint32 nextUint32(const uint32 min, const uint32 max);

			inline int64 nextInt64(const int64 min, const int64 max);
			inline uint64 nextUint64(const uint64 min, const uint64 max);

			inline float32 nextFloat32(const float32 min, const float32 max);
			inline float64 nextFloat64(const float64 min, const float64 max);
		}
	}
}

#include "sani/core/math/impl/random.hpp"