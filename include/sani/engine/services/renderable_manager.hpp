#pragma once

#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/engine/services/engine_service.hpp"

#include <vector>

namespace sani {

	namespace engine {
		
		namespace services {

			template<class T>
			class RenderableManager : public EngineService {
			private:
				PagePoolAllocator<T> allocator;
				std::vector<T*> elements;

				
			protected:
				RenderableManager(const String& name, engine::SaNiEngine* const engine);
			public:
			};
		}
	}
}