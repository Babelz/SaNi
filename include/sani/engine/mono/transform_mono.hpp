#pragma once

#include <mono/metadata/object.h>

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, math, Vec3f);

namespace sani { 

	namespace engine {
		
		namespace mono {

			MonoObject* createTransform(math::Vec3f& position, math::Vec3f& scale, math::Vec3f& origin, float32 rotation);

			math::Vec3f getPosition(MonoObject* transform);
			void setPosition(MonoObject* transform, math::Vec3f& value);
			
			math::Vec3f getScale(MonoObject* transform);
			void setScale(MonoObject* transform, math::Vec3f& value);

			math::Vec3f getOrigin(MonoObject* transform);
			void setOrigin(MonoObject* transform, math::Vec3f& value);

			float32 getRotation(MonoObject* transform);
			void setRotation(MonoObject* transform, float32 value);
		}
	}
}