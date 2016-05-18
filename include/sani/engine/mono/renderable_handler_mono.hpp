#pragma once

/*
	Contains common renderable internal call hookings for all classes
	that implement the interface IRenderable.
*/

#include "sani/engine/mono/mono_define.hpp"
#include "sani/types.hpp"

#include <mono/metadata/object.h>

#include <vector>

namespace sani {

	namespace engine {
		
		namespace mono {
		
			template<class T>
			void registerRenderableMembers(std::vector<T*>* handles, MonoClassDefinition* classDef);
		}
	}
}

#include "sani/engine/mono/impl/renderable_handler_mono.hpp"