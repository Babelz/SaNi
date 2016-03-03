#pragma once

#include "sani/core/math/vector2.hpp"
#include "sani/core/math/vector3.hpp"
#include "sani/ecs/component.hpp"
#include "sani/types.hpp"
#include "sani/preprocessor/rtti.hpp"
#include "sani/preprocessor/rtti_runtime.hpp"

namespace sani {

	class Transform final : public Component {
		DECLARE_REFLECTABLE;
	public:
		math::Vec3f position	{ 0.0f, 0.0f, 0.0f };
		math::Vec2f scale		{ 1.0f, 1.0f };
		
		float32 rotation		{ 0.0f };

		Transform() = default;

		~Transform() = default;
	};
	// TODO move this to cpp
	void Transform::RTTI_Init() {
		auto& db = sani::rtti::TypeDatabase::getInstance();
		RTTI_REGISTER_TYPE(sani::Transform);
		RTTI_DEFAULT_CTOR(sani::Transform);
		RTTI_PUBLIC_FIELD(sani::Transform, position, sani::math::Vec3f);
		RTTI_PUBLIC_FIELD(sani::Transform, scale, sani::math::Vec2f);
		RTTI_PUBLIC_FIELD(sani::Transform, rotation, float32);
	}
}