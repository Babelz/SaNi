#pragma once

#include "sani/core/math/vector.hpp"
#include "sani/types.hpp"

namespace sani {
	
	namespace graphics {
			
		/// @class Transform Transform.hpp "sani/graphics/transform.hpp"
		/// @author voidbab
		///
		/// Transform defined by position, scale, origin and rotation.
		class Transform {
		public:
			sani::math::Vec3f position;
			sani::math::Vec3f scale;
			sani::math::Vec3f origin;

			float32 rotation;

			Transform();
			
			~Transform();
		};
	}
}