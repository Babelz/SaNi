#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, CommandMessage);

namespace sani {

	namespace engine {
		
		namespace services {
			
			/// ! Contains the contract definition and helper functions to interact with 
			///   the renderable services.
			namespace renderablemanager {

				/*
					Renderable manager contract definition

					Purpose of the service: Handle memory of the given types of 
											renderables and handle their 
											render and geometry updates.

											User can create, delete and 
											queue elements for updates.

											Updating an element causes it's 
											geo/render data to be updated
											and it might get relocated in 
											the layer it is contained in.

				*/

				/// List of all known commands for the renderable services.
				enum class RenderableManagerCommands : uint32 {
					CreateElement		= 0,
					
					DeleteElement		= 1,

					QueueForUpdates		= 3
				};

				enum class ElementType : uint32 {
					Rectangle	= 0,

					Triangle	= 1,
					
					Sprite		= 2,
					
					Circle		= 3
				};

				void createElement(messages::DocumentMessage* const message, const ElementType type);

				void deleteElement(messages::CommandMessage* const message, const ElementType type);
				
				void queueForUpdates(messages::CommandMessage* const message, const ElementType type);
			}
		}
	}
}