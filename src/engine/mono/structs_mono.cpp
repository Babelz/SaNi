#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/mono/mono_include.hpp"

#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			MonoObject* createTransform(math::Vec3f& position, math::Vec3f& scale, math::Vec3f& origin, float32 rotation) {
				const uint32 argc = 10;

				void* args[argc] = {
					&position.x,
					&position.y,
					&position.z,

					&scale.x,
					&scale.y,
					&scale.z,

					&origin.x,
					&origin.y,
					&origin.z,

					&rotation
				};

				const MonoClassDefinition classDef("SaNi.Mono.Graphics", "Transform");

				return MONO_PROVIDER->createObject(&classDef, args, argc);
			}
			MonoObject* createRectf(float32 x, float32 y, float32 width, float32 height) {
				const uint32 argc = 4;

				void* args[argc] = {
					&x,
					&y,
					&width,
					&height
				};

				const MonoClassDefinition classDef("SaNi.Mono.Math", "Rectf");

				return MONO_PROVIDER->createObject(&classDef, args, argc);
			}
			MonoObject* createRecti(int32 x, int32 y, int32 width, int32 height) {
				const uint32 argc = 4;

				void* args[argc] = {
					&x,
					&y,
					&width,
					&height
				};

				const MonoClassDefinition classDef("SaNi.Mono.Math", "Recti");

				return MONO_PROVIDER->createObject(&classDef, args, argc);
			}
			MonoObject* createColor(float32 r, float32 g, float32 b, float32 a) {
				const uint32 argc = 4;

				void* args[argc] = {
					&r,
					&g,
					&b,
					&a
				};

				const MonoClassDefinition classDef("SaNi.Mono.Graphics", "Color");

				return MONO_PROVIDER->createObject(&classDef, args, argc);
			}
		}
	}
}