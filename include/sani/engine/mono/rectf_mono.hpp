#pragma once

#include <mono/metadata/object.h>

#include "sani/core/math/vector2.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			namespace rectf {

				MonoObject* create(float32 x, float32 y, float32 width, float32 height);

				math::Vec2f getPosition(MonoObject* rectf);
				void setPosition(MonoObject* rectf, math::Vec2f& value);

				math::Vec2f getSize(MonoObject* rectf);
				void setSize(MonoObject* rectf, math::Vec2f& value);

				void copyData(MonoObject* from, math::Rect32f* const to);
				void copyData(math::Rect32f* const from, MonoObject* to);
			}
		}
	}
}