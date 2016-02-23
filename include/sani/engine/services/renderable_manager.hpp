#pragma once

#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/engine/services/engine_service.hpp"

#include <vector>

namespace sani {

	namespace engine {
		
		namespace services {

			/// @class RenderableManager renderable_manager.hpp "sani/engine/services.hpp"
			/// @author voidbab
			/// 
			/// Simple, generic engine service that is responsible of 
			/// managing renderable elements of given type.
			template<class T>
			class RenderableManager : public EngineService {
			private:
				// Type of the elements.
				const renderablemanager::ElementType type;

				// Allocator to contain the elements.
				PagePoolAllocator<T> allocator;
				
				// Elements that require geo/render data updates.
				std::list<T*> elementsToUpdate;
				// All elements allocated by the allocator.
				std::list<T*> elements;

				/// Method that handles all incoming document messages.
				void handleDocumentMessage(messages::DocumentMessage* const message);
				
				/// Message response that creates new element.
				void createElement(messages::DocumentMessage* const message);
				/// Message response that deletes the given element.
				void deleteElement(messages::DocumentMessage* const message);
				/// Message response that queues the given element for updates.
				void queueForUpdates(messages::DocumentMessage* const message);

				/// Message response that returns all the elements this manager contains.
				void getElements(messages::DocumentMessage* const message);
			protected:
				/*
					Keeping constructor as private since we don't
					want to allow anyone to make instance of this class.

					This class is intended to work as a base class for
					other managers.
				*/

				RenderableManager(const String& name, const renderablemanager::ElementType type, engine::SaNiEngine* const engine);
			public:
				void receive(messages::Message* const message) final override;

				void update(const EngineTime& time) override;

				virtual ~RenderableManager() = default;
			};
		}
	}
}

#include "sani/engine/services/impl/renderable_manager.hpp"