#include "sani/engine/mono/rectangle_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/mono/mono_include.hpp"

#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			namespace transform {

				const MonoClassDefinition TransformDef("SaNi.Mono.Graphics", "Transform");
				const char* const FieldPosition = "position";
				const char* const FieldScale = "scale";
				const char* const FieldOrigin = "origin";
				const char* const FieldRotation = "rotation";

				const MonoClassDefinition Vec3Def("SaNi.Mono.Math", "Vector3");
				const char* const FieldX = "x";
				const char* const FieldY = "y";
				const char* const FieldZ = "z";

				MonoObject* create(math::Vec3f& position, math::Vec3f& scale, math::Vec3f& origin, float32 rotation) {
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

					return MONO_PROVIDER->createObject(&TransformDef, args, argc);
				}

				static math::Vec3f readVector(MonoObject* transform, const char* const field) {
					void* vector = MONO_PROVIDER->readField(transform, field);

					const float32 x = *MONO_UNBOX(MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), FieldX), float32);
					const float32 y = *MONO_UNBOX(MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), FieldY), float32);
					const float32 z = *MONO_UNBOX(MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), FieldZ), float32);

					return math::Vec3f(z, y, z);
				}
				static void writeVector(MonoObject* transform, const char* const field, math::Vec3f& value) {
					void* vector = MONO_PROVIDER->readField(transform, field);

					MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), FieldX, &value.x);
					MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), FieldY, &value.y);
					MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), FieldZ, &value.z);
				}

				math::Vec3f getPosition(MonoObject* transform) {
					return readVector(transform, FieldPosition);
				}
				void setPosition(MonoObject* transform, math::Vec3f& value) {
					writeVector(transform, FieldPosition, value);
				}

				math::Vec3f getScale(MonoObject* transform) {
					return readVector(transform, FieldScale);
				}
				void setScale(MonoObject* transform, math::Vec3f& value) {
					writeVector(transform, FieldScale, value);
				}

				math::Vec3f getOrigin(MonoObject* transform) {
					return readVector(transform, FieldOrigin);
				}
				void setOrigin(MonoObject* transform, math::Vec3f& value) {
					writeVector(transform, FieldOrigin, value);
				}

				float32 getRotation(MonoObject* transform) {
					return *MONO_UNBOX(MONO_PROVIDER->readField(transform, FieldRotation), float32);
				}
				void setRotation(MonoObject* transform, float32 value) {
					MONO_PROVIDER->writeField(transform, FieldRotation, &value);
				}
			}
		}
	}
}