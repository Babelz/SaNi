#pragma once

#include "sani/core/math/vector.hpp"
#include "sani/types.hpp"

namespace sani {
	
	namespace graphics {
			
		class Transformable {
		private:
			math::Vec3f position;
			math::Vec2f scale;
			math::Vec2f origin;

			float32 rotation;
		public:
			Transformable();

			~Transformable();
		};
	}
}