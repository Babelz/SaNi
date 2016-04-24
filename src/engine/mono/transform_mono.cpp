#include "sani/engine/mono/rectangle_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/mono/mono_include.hpp"

#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			namespace transform {

				const MonoClassDefinition TransformDef("SaNi.Mono.Graphics", "Transform");
				const MonoFieldDefinition PositionDef("position");
				const MonoFieldDefinition ScaleDef("scale");
				const MonoFieldDefinition OriginDef("origin");
				const MonoFieldDefinition RotationDef("rotation");

				const MonoClassDefinition Vec3Def("SaNi.Mono.Math", "Vector3");
				const MonoFieldDefinition XDef("x");
				const MonoFieldDefinition YDef("y");
				const MonoFieldDefinition ZDef("z");

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

				static math::Vec3f readVector(MonoObject* transform, const MonoFieldDefinition* const field) {
					void* vector = nullptr;
					//MONO_PROVIDER->readField(transform, &TransformDef, &PositionDef, vector);

					void* x = nullptr;
					void* y = nullptr;
					void* z = nullptr;

					//MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), &Vec3Def, &XDef, x);
					//MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), &Vec3Def, &YDef, y);
					//MONO_PROVIDER->readField(static_cast<MonoObject*>(vector), &Vec3Def, &ZDef, z);

					const float32 xVal = *static_cast<float32*>(x);
					const float32 yVal = *static_cast<float32*>(y);
					const float32 zVal = *static_cast<float32*>(z);

					return math::Vec3f(xVal, yVal, zVal);
				}
				static void writeVector(MonoObject* transform, const MonoFieldDefinition* const field, math::Vec3f& value) {
					void* vector = nullptr;
					//MONO_PROVIDER->readField(transform, &TransformDef, &PositionDef, vector);

					//MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), &Vec3Def, &XDef, &value.x);
					//MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), &Vec3Def, &YDef, &value.y);
					//MONO_PROVIDER->writeField(static_cast<MonoObject*>(vector), &Vec3Def, &ZDef, &value.z);
				}

				math::Vec3f getPosition(MonoObject* transform) {
					return readVector(transform, &PositionDef);
				}
				void setPosition(MonoObject* transform, math::Vec3f& value) {
					writeVector(transform, &PositionDef, value);
				}

				math::Vec3f getScale(MonoObject* transform) {
					return readVector(transform, &ScaleDef);
				}
				void setScale(MonoObject* transform, math::Vec3f& value) {
					writeVector(transform, &ScaleDef, value);
				}

				math::Vec3f getOrigin(MonoObject* transform) {
					return readVector(transform, &OriginDef);
				}
				void setOrigin(MonoObject* transform, math::Vec3f& value) {
					writeVector(transform, &OriginDef, value);
				}

				float32 getRotation(MonoObject* transform) {
					void* rotation = nullptr;

					//MONO_PROVIDER->readField(transform, &TransformDef, &RotationDef, rotation);

					return *static_cast<float32*>(rotation);
				}
				void setRotation(MonoObject* transform, float32 value) {
					MONO_PROVIDER->writeField(transform, &TransformDef, &RotationDef, &value);
				}
			}
		}
	}
}