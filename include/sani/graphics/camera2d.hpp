#pragma once

#include "sani/platform/graphics/viewport.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace graphics {

		/// @class Camera2D camera2d.hpp "sani/graphics/camera2d.hpp"
		/// @author
		///
		/// Two dimensional camera that supports zooming, rota
		class Camera2D {
		private:
			math::Mat4f transform;
			Viewport viewport;

			math::Vec3f position;
			math::Vec3f origin;
			math::Vec3f zoom;

			float32 rotation;

			String name;
		public:
			Camera2D(Viewport& viewport);

			inline float32 getX() const;
			inline float32 getY() const;

			inline float32 getOriginX() const;
			inline float32 getOriginY() const;

			inline float32 getZoom() const;
			inline float32 getRotation() const;

			inline void setX(const float32 x);
			inline void setY(const float32 y);
			inline void setPosition(const math::Vec2f& position);
			inline void setPosition(const float32 x, const float32 y);

			inline void setOriginX(const float32 x);
			inline void setOriginY(const float32 y);
			inline void setOrigin(const math::Vec2f& origin);

			inline void setZoom(const float32 value);
			inline void setRotation(const float32 value);

			inline void moveBy(const float32 x, const float32 y);
			inline void moveBy(const math::Vec2f& amount);

			inline void zoomBy(const float32 amount);
			inline void rotateBy(const float32 amount);

			inline const Viewport& getViewport() const;
			inline void setViewport(const Viewport& viewport);

			inline const math::Mat4f& transformation() const;
			inline void computeTransformation();

			inline const String& getName() const;
			inline void setName(const String& name);

			~Camera2D();

			bool operator ==(const Camera2D& lhs) const;
			bool operator !=(const Camera2D& lhs) const;
		};
	}
}

#include "sani/graphics/inl/camera2d.inl"