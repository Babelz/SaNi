#include "sani/engine/mono/rectangle_mono.hpp"
#include "sani/engine/mono/mono_include.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/core/math/rectangle.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			namespace rectf {

				const MonoClassDefinition ClassDef("SaNi.Mono.Math", "Rectf");
				const char* const FieldX = "x";
				const char* const FieldY = "y";
				const char* const FieldWidth = "width";
				const char* const FieldHeight = "height";

				MonoObject* create(float32 x, float32 y, float32 width, float32 height) {
					const uint32 argc = 4;

					void* args[argc] = {
						&x,
						&y,
						&width,
						&height
					};

					return MONO_PROVIDER->createObject(&ClassDef, args, argc);
				}

				static math::Vec2f getVector(MonoObject* rectf, const char* const xField, const char* const yField) {
					const float32 x = *MONO_UNBOX(MONO_PROVIDER->readField(rectf, xField), float32);
					const float32 y = *MONO_UNBOX(MONO_PROVIDER->readField(rectf, yField), float32);

					return math::Vec2f(x, y);
				}
				static void writeVector(MonoObject* rectf, const char* const xField, const char* const yField, math::Vec2f& value) {
					MONO_PROVIDER->writeField(rectf, xField, &value.x);
					MONO_PROVIDER->writeField(rectf, yField, &value.y);
				}

				math::Vec2f getPosition(MonoObject* rectf) {
					return getVector(rectf, FieldX, FieldY);
				}
				void setPosition(MonoObject* rectf, math::Vec2f& value) {
					writeVector(rectf, FieldX, FieldY, value);
				}

				math::Vec2f getSize(MonoObject* rectf) {
					return getVector(rectf, FieldWidth, FieldHeight);
				}
				void setSize(MonoObject* rectf, math::Vec2f& value) {
					writeVector(rectf, FieldWidth, FieldHeight, value);
				}

				void copyData(MonoObject* from, math::Rect32f* const to) {
					auto position = getPosition(from);
					auto size = getPosition(from);

					to->x = position.x;
					to->y = position.y;
					to->w = size.x;
					to->h = size.y;
				}
				void copyData(math::Rect32f* const from, MonoObject* to) {
					writeVector(to, FieldX, FieldY, from->position());
					writeVector(to, FieldWidth, FieldHeight, from->position());
				}
			}
		}
	}
}