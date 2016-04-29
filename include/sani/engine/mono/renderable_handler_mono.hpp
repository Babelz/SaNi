#pragma once

/*
	Contains common renderable internal call hookings for all classes
	that implement the interface IRenderable.
*/

#include "sani/engine/mono/mono_define.hpp"
#include "sani/types.hpp"

#include "sani/engine/mono/glib_types.hpp"
#include <mono/metadata/object.h>

#include <vector>

namespace sani {

	namespace engine {
		
		namespace mono {
		
			template<class T>
			using HandleList = std::vector<T*>;

			template<class T>
			class RenderableHandlerMono final {
			private:
				HandleList<T*> const handles;
			public:
				RenderableHandlerMono(HandleList* const handles);
				
				~RenderableHandlerMono() = default;
			};
		}
	}
}

#include "sani/engine/mono/impl/renderable_handler_mono.hpp"