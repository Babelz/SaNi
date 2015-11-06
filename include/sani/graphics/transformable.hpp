#pragma once

#include "sani/core/math/vector.hpp"
#include "sani/types.hpp"

namespace sani {
	
	namespace graphics {
			
		/// @class Transformable transformable.hpp "sani/graphics/transformable.hpp"
		/// @author voidbab
		///
		/// Transform defined by position, scale, origin and rotation.
		class Transformable {
		private:
			sani::math::Vec3f position;
			sani::math::Vec3f scale;
			sani::math::Vec3f origin;

			float32 rotation;

			bool changed;
		protected:
			/// Returns true if the transformation has changed.
			inline bool hasChanged() const;
			/// Clears the changes flag (sets it to false)
			inline void clearChanges();
		public:
			Transformable();

			inline void setPosition(const sani::math::Vec3f& position);
			inline void setPosition(const float32 x, const float32 y);
			inline void setX(const float32 x);
			inline void setY(const float32 y);

			inline void setScale(const sani::math::Vec3f& scale);
			inline void setScale(const float32 horizontalScale, const float32 verticalScale);
			inline void setHorizontalScale(const float32 scale);
			inline void setVerticalScale(const float32 scale);
			
			inline void setOrigin(const sani::math::Vec3f& origin);
			inline void setOrigin(const float32 x, const float32 y);
			inline void setOriginX(const float32 x);
			inline void setOriginY(const float32 y);

			inline void setRotation(const float32 angle);
			inline void rotate(const float32 angle);

			inline void move(const sani::math::Vec3f& offset);
			inline void move(const float32 offsetX, const float32 offsetY);

			inline const sani::math::Vec3f& getPosition() const;
			inline float32 getX() const;
			inline float32 getY() const;

			inline const sani::math::Vec3f& getScale() const;
			inline float32 getHorizontalScale() const;
			inline float32 getVerticalScale() const;

			inline const sani::math::Vec3f& getOrigin() const;
			inline float32 getOriginX() const;
			inline float32 getOriginY() const;

			inline float32 getRotation() const;

			~Transformable();
		};
	}
}

#include "sani/graphics/inl/transformable.inl"