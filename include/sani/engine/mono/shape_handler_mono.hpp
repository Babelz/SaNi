#pragma once

#include "sani/engine/mono/mono_define.hpp"
#include <vector>

namespace sani {

	namespace engine {

		namespace mono {

			template<class T>
			void registerShapeMembers(std::vector<T*>* handles, MonoClassDefinition classDef);
		}
	}
}

#include "sani/engine/mono/impl/shape_handler_mono.hpp"