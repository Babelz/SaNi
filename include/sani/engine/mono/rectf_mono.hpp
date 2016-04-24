#pragma once

#include <mono/metadata/object.h>

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, math, Rect32f);
SANI_FORWARD_DECLARE_2(sani, math, Vec2f);

namespace sani {

	namespace engine {

		namespace mono {

			MonoObject* createRectf(float32 x, float32 y, float32 width, float32 height);

			math::Vec2f getPosition(MonoObject* rectf);
			math::Vec2f setPosition(MonoObject* rectf, math::Vec2f& value);

			math::Vec2f getSize(MonoObject* rectf);
			math::Vec2f setSize(MonoObject* rectf, math::Vec2f& value);
		}
	}
}