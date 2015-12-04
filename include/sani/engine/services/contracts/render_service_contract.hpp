#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, CommandMessage);

namespace sani {
	
	namespace engine {
		
		namespace services {

			/// ! Contains the contract definition and helper functions to interact with 
			///   the rendering service.
			namespace renderservice {

				/*
					
					Render service contract definition
					
					Purpose of the service: Render the scene to the user. Uses 
											some other classes to optimize the 
											rendering steps. 

											User can add and remove elements from
											the renderer at any time.

											User can define layers that will be used 
											for the rendering. Layers can be dynamic
											or static. Static layers are rendered once
											and dynamic layers are rendered again 
											each frame.

					Functionalities:		Modify layers.
				*/

				enum class RenderServiceCommands : uint32 {
					CreateLayer,
					DeleteLayer,

					AddElement,
					RemoveElement,

					GetLayer
				};

				void createLayer(messages::CommandMessage* const message, const String& layerName);
				void deleteLayer(messages::CommandMessage* const message, const String& layerName);

				void addElement(messages::CommandMessage* const message, const String& layerName);
				void removeElement(messages::CommandMessage* const message, const String& layerName);

				void getLayer(messages::CommandMessage* const message, const String& layerName);
			}
		}
	}
}