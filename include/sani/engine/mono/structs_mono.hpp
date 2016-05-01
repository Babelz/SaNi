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

			MonoObject* ceatetTransform(math::Vec3f& position, math::Vec3f& scale, math::Vec3f& origin, float32 rotation);
			MonoObject* createRectf(float32 x, float32 y, float32 width, float32 height);
			MonoObject* createRecti(int32 x, int32 y, int32  width, int32  height);
			MonoObject* createColor(float32 r, float32 g, float32 b, float32 a);
		}
	}
}