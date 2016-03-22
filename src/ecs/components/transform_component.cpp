#include "sani/ecs/components/transform_component.hpp"

namespace sani {

    void Transform::RTTI_Init() {
        
		auto& db = sani::rtti::TypeDatabase::getInstance();
        RTTI_REGISTER_TYPE(sani::Transform);
        RTTI_DEFAULT_CTOR(sani::Transform);
        RTTI_PUBLIC_FIELD(sani::Transform, position, sani::math::Vec3f);
        RTTI_PUBLIC_FIELD(sani::Transform, scale, sani::math::Vec2f);
        RTTI_PUBLIC_FIELD(sani::Transform, rotation, float32);
    }
}

