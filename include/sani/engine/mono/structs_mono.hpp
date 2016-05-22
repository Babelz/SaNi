#pragma once

#include <mono/metadata/object.h>

#include "sani/core/math/vector3.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			struct MonoTransform final {
				float32 px;
				float32 py;
				float32 pz;

				float32 sx;
				float32 sy;
				float32 sz;

				float32 ox;
				float32 oy;
				float32 oz;

				float32 r;
			};

			struct MonoRectf final {
				float32 x;
				float32 y;
				float32 w;
				float32 h;
			};

			struct MonoRecti final {
				int32 x;
				int32 y;
				int32 w;
				int32 h;
			};

			struct MonoColor final {
				float32 r;
				float32 g;
				float32 b;
				float32 a;
			};

			struct MonoVec2 final {
				float32 x;
				float32 y;
			};

			struct MonoVec3 final {
				float32 x;
				float32 y;
				float32 z;
			};

			struct MonoVec4 final {
				float32 x;
				float32 y;
				float32 z;
				float32 w;
			};

			struct MonoParticleGenerator final {
				MonoVec2 spawnLocationMinOffset;
				MonoVec2 spawnLocationMaxOffset;

				MonoVec2 startVelocity;
				MonoVec2 velocityVariance;

				MonoVec2 baseAcceleration;
				MonoVec2 accelerationVariance;

				MonoVec2 startSize;

				MonoVec2 baseScale;
				MonoVec2 scaleVariance;

				MonoVec2 baseScaleAcceleration;
				MonoVec2 scaleAccelerationVariance;

				MonoVec2 baseScaleVelocity;
				MonoVec2 scaleVelocityVariance;

				MonoColor color;
				MonoColor colorVariance;

				int16 flags;

				float32 baseAngularVelocity;
				float32 angularVelocityVariance;

				float32 baseAngularAcceleration;
				float32 angularAccelerationVariance;

				float32 baseDecayTime;
				float32 decayTimeVariance;

				uint32 firstAttributeListIndex;
				uint32 lastAttributeListIndex;

				uint32 framesToFade;
				uint32 framesToFadeVariance;
			};

			MonoObject* ceatetTransform(math::Vec3f& position, math::Vec3f& scale, math::Vec3f& origin, float32 rotation);
			MonoObject* createRectf(float32 x, float32 y, float32 width, float32 height);
			MonoObject* createRecti(int32 x, int32 y, int32  width, int32  height);
			MonoObject* createColor(float32 r, float32 g, float32 b, float32 a);

			MonoObject* createParticleGenerator(const MonoParticleGenerator* const generator);
		}
	}
}