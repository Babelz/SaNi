#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <vector>

SANI_FORWARD_DECLARE_1(sani, Component);

namespace sani {

	/// @class Entity entity.hpp "sani/ecs/entity.hpp"
	/// @author voidbab
	///
	/// Entities group together components to form the
	/// game objects games use.
	class Entity {
	public:
		std::vector<Component*> component;

		uint32 ID { 0 };

		Entity()	= default;
		~Entity()	= default;
	};
}