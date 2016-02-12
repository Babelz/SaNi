#include "sani/core/math/random.hpp"
#include <random>

#define ASSERT_MIN_MAX() SANI_ASSERT(min < max)

namespace sani {

	namespace math {
		
		namespace random {

			static std::default_random_engine generator;

			inline int8 nextInt8(const int8 min, const int8 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<int8> dist(min, max);

				return dist(generator);
			}
			inline uint8 nextUInt8(const int8 min, const int8 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<uint8> dist(min, max);

				return dist(generator);
			}

			inline int16 nextInt16(const int16 min, const int16 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<int16> dist(min, max);

				return dist(generator);
			}
			inline uint16 nextUInt16(const uint16 min, const uint16 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<uint16> dist(min, max);

				return dist(generator);
			}

			inline int32 nextInt32(const int32 min, const int32 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<int32> dist(min, max);

				return dist(generator);
			}
			inline uint32 nextUint32(const uint32 min, const uint32 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<uint32> dist(min, max);

				return dist(generator);
			}

			inline int64 nextInt64(const int64 min, const int64 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<int64> dist(min, max);

				return dist(generator);
			}
			inline uint64 nextUint64(const uint64 min, const uint64 max) {
				ASSERT_MIN_MAX();

				std::uniform_int_distribution<uint64> dist(min, max);

				return dist(generator);
			}

			inline float32 nextFloat32(const float32 min, const float32 max) {
				ASSERT_MIN_MAX();

				std::uniform_real_distribution<float32> dist(min, max);

				return dist(generator);
			}
			inline float64 nextFloat64(const float64 min, const float64 max) {
				ASSERT_MIN_MAX();

				std::uniform_real_distribution<float64> dist(min, max);

				return dist(generator);
			}
		}
	}
}