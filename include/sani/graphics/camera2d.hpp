#pragma once

#include "sani/platform/graphics/viewport.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace graphics {

		class Camera2D {
		private:
			math::Mat4f transform;
			Viewport viewport;
		public:
			math::Vec3f zoom;

			float rotation;

			math::Vec3f position;
			math::Vec3f origin;

			Camera2D(Viewport& viewport);

			const Viewport& getViewport() const;
			void setViewport(const Viewport& viewport);

			const math::Mat4f& transformation() const;
			void computeTransformation();

			~Camera2D();
		};
	}
}