#include "sani/engine/mono/rectangle_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/mono/mono_include.hpp"
#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			static const MonoClassDefinition transformDef("SaNi.Mono.Graphics", "Transform");
			static const MonoFieldDefinition positionDef("position");
			static const MonoFieldDefinition scaleDef("scale");
			static const MonoFieldDefinition originDef("origin");
			static const MonoFieldDefinition rotationDef("rotation");

			static const MonoClassDefinition vec3Def("SaNi.Mono.Math", "Vector3");
			static const MonoFieldDefinition xDef("x");
			static const MonoFieldDefinition yDef("y");
			static const MonoFieldDefinition zDef("z");

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

				MonoObject* transform = MONO_PROVIDER->createObject(&transformDef, args, argc);

				return transform;
			}

			static math::Vec3f readVector(MonoObject* transform, const MonoFieldDefinition* const field) {
				void* vector = nullptr;
				MONO_PROVIDER->readField(transform, &transformDef, &positionDef, vector);

				void* x = nullptr;
				void* y = nullptr;
				void* z = nullptr;

				MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), &vec3Def, &xDef, x);
				MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), &vec3Def, &yDef, y);
				MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), &vec3Def, &zDef, z);

				const float32 xVal = *static_cast<float32*>(x);
				const float32 yVal = *static_cast<float32*>(y);
				const float32 zVal = *static_cast<float32*>(z);
				
				return sani::math::Vec3f(xVal, yVal, zVal);
			}
			static void writeVector(MonoObject* transform, const MonoFieldDefinition* const field, math::Vec3f& value) {
				void* vector = nullptr;
				MONO_PROVIDER->readField(transform, &transformDef, &positionDef, vector);

				MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), &vec3Def, &xDef, &value.x);
				MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), &vec3Def, &yDef, &value.y);
				MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), &vec3Def, &zDef, &value.z);
			}

			math::Vec3f getPosition(MonoObject* transform) {
				return readVector(transform, &positionDef);
			}
			void setPosition(MonoObject* transform, math::Vec3f& value) {
				writeVector(transform, &positionDef, value);
			}

			math::Vec3f getScale(MonoObject* transform) {
				return readVector(transform, &scaleDef);
			}
			void setScale(MonoObject* transform, math::Vec3f& value) {
				writeVector(transform, &scaleDef, value);
			}

			math::Vec3f getOrigin(MonoObject* transform) {
				return readVector(transform, &originDef);
			}
			void setOrigin(MonoObject* transform, math::Vec3f& value) {
				writeVector(transform, &originDef, value);
			}

			float32 getRotation(MonoObject* transform) {
				void* rotation = nullptr;

				MONO_PROVIDER->readField(transform, &transformDef, &rotationDef, rotation);

				return *static_cast<float32*>(rotation);
			}
			void setRotation(MonoObject* transform, float32 value) {
				MONO_PROVIDER->writeField(transform, &transformDef, &rotationDef, &value);
			}
		}
	}
}