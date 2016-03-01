#pragma once

#include "sani/core/memory/register_allocator.hpp"
#include "sani/engine/services/engine_service.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_1(sani, Component);
SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);

namespace sani {

	namespace engine {

		namespace services {
			
			template<class T>
			class ComponentManager : public EngineService {
			private:
				RegisterAllocator<Component> allocator;

				void handleDocumentMessage(messages::DocumentMessage* const message);

				void createComponent(messages::DocumentMessage* const message);
				void destroyComponent(messages::DocumentMessage* const message);

				void listComponents(messages::DocumentMessage* const message);
			public:
				ComponentManager(SaNiEngine* const engine);

				virtual void receive(messages::Message* const message) final override;

				virtual ~ComponentManager() = default;
			};
		}
	}
}
