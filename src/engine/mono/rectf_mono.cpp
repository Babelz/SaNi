#include "sani/engine/mono/rectangle_mono.hpp"
#include "sani/engine/mono/mono_include.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/core/math/rectangle.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			namespace rectf {

				const MonoClassDefinition ClassDef("SaNi.Mono.Math", "Rectf");
				const MonoFieldDefinition XDef("x");
				const MonoFieldDefinition YDef("y");
				const MonoFieldDefinition WidthDef("width");
				const MonoFieldDefinition HeightDef("height");

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

				static math::Vec2f getVector(MonoObject* rectf, const MonoFieldDefinition* const xField, const MonoFieldDefinition* const yField) {
					void* x = nullptr;
					void* y = nullptr;

					//MONO_PROVIDER->readField(rectf, &ClassDef, xField, x);
					//MONO_PROVIDER->readField(rectf, &ClassDef, yField, y);

					const float32 xVal = *static_cast<float32*>(x);
					const float32 yVal = *static_cast<float32*>(y);

					return math::Vec2f(xVal, yVal);
				}
				static void writeVector(MonoObject* rectf, const MonoFieldDefinition* const xField, const MonoFieldDefinition* const yField, math::Vec2f& value) {
					MONO_PROVIDER->writeField(rectf, &ClassDef, xField, &value.x);
					MONO_PROVIDER->writeField(rectf, &ClassDef, yField, &value.y);
				}

				math::Vec2f getPosition(MonoObject* rectf) {
					return getVector(rectf, &XDef, &YDef);
				}
				void setPosition(MonoObject* rectf, math::Vec2f& value) {
					writeVector(rectf, &XDef, &YDef, value);
				}

				math::Vec2f getSize(MonoObject* rectf) {
					return getVector(rectf, &WidthDef, &HeightDef);
				}
				void setSize(MonoObject* rectf, math::Vec2f& value) {
					writeVector(rectf, &WidthDef, &HeightDef, value);
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
					writeVector(to, &XDef, &YDef, from->position());
					writeVector(to, &WidthDef, &HeightDef, from->position());
				}
			}
		}
	}
}