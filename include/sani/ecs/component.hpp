#pragma once

#include "sani/types.hpp"

namespace sani {

	/// @class Component component.hpp "sani/ecs/component.hpp"
	/// @author voidbab
	/// 
	/// Base class for all components.
	class Component {
	public:
		uint32 id { 0 };

		Component()				= default;

		virtual ~Component()	= default;
	};
}