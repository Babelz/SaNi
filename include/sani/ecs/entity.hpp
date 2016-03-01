#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <vector>

SANI_FORWARD_DECLARE_1(sani, Component);

namespace sani {

	using ComponentList = std::vector<Component*>;

	/// @class Entity entity.hpp "sani/ecs/entity.hpp"
	/// @author voidbab
	///
	/// Entities group together components to form the
	/// game objects games use.
	class Entity {
	public:
		ComponentList components;

		uint32 ID { 0 };

		Entity()	= default;

		~Entity()	= default;
	};
}