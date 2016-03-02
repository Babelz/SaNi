#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_1(sani, Entity);

namespace sani {

	/// @class Component component.hpp "sani/ecs/component.hpp"
	/// @author voidbab
	/// 
	/// Base class for all components.
	class Component {
	public:
		// The entity this component is being attached to.
		// If owner is null, the component has not yet 
		// been inserted to any entity or it is being
		// destroyed.
		Entity* owner			{ nullptr };
		uint32 id				{ 0 };

		Component()	= default;

		virtual ~Component() = default;
	};
}