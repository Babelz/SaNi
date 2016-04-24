#pragma once

#include <mono/metadata/object.h>

#include "sani/graphics/color.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			namespace color {

				MonoObject* create(float32 r, float32 g, float32 b, float32 a);

				void copyData(MonoObject* from, graphics::Color* const to);
				void copyData(graphics::Color* const from, MonoObject* to);
			}
		}
	}
}