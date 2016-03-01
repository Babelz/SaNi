#pragma once

#include "sani/core/memory/register_allocator.hpp"
#include "sani/engine/services/engine_service.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_1(sani, Component);
SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);

namespace sani {

	namespace engine {

		namespace services {
			
			template<class T>
			class ComponentManager : public EngineService {
			private:
				RegisterAllocator<T> allocator;

				void handleDocumentMessage(messages::DocumentMessage* const message);
				void handleQueryMessage(messages::QueryMessage* const message);

				void createComponent(messages::DocumentMessage* const message);
				void destroyComponent(messages::DocumentMessage* const message);

				void listComponents(messages::DocumentMessage* const message);
			protected:
				ComponentManager(const String& name, engine::SaNiEngine* const engine);

				const RegisterAllocator<T>& getAllocator() const;
			public:
				virtual void receive(messages::Message* const message) final override;

				virtual ~ComponentManager() = default;
			};
		}
	}
}

#include "sani/engine/services/impl/component_manager.hpp"