#pragma once

#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/engine/services/engine_service.hpp"
#include "sani/forward_declare.hpp"

#include <vector>
#include <stack>

SANI_FORWARD_DECLARE_1(sani, Entity);
SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);

namespace sani {

	namespace engine {

		namespace services {
			
			template<class T>
			class ComponentManager final : public EngineService {
			private:
				PagePoolAllocator<T> allocator;
				std::stack<uint32> released;

			public:
			};
		}
	}
}
