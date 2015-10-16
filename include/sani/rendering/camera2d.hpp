#pragma once

#include "sani/platform/graphics/viewport.hpp"
#include "sani/core/math/matrix3.hpp"
#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace graphics {

		class Camera2D {
		private:
			math::Mat3f transform;
			Viewport viewport;
			
			math::Vec2f zoom;

			float rotation;
		public:
			math::Vec2f position;
			math::Vec2f origin;

			inline void setZoom(const float zoom) {

			}

			Camera2D(Viewport& viewport);

			const Viewport& getViewport() const;
			void setViewport(const Viewport& viewport);

			const math::Mat3f& transformation() const;
			void computeTransformation();

			~Camera2D();
		};
	}
}