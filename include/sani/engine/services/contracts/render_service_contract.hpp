#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
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

				/// List of all known commands for the render service.
				enum class RenderServiceCommands : uint32 {
					CreateLayer		= 0,

					DeleteLayer		= 1,

					GetLayers		= 2
				};

				/// Generates a message that will causes the service to create a new layer with given name.
				void createLayer(messages::CommandMessage* const message, const String& layerInformation);

				/// Generates a message that will causes the service to delete the layer with given name.
				void deleteLayer(messages::CommandMessage* const message, const String& layerInformation);

				/// Generates a message that will return all layers.
				void getLayers(messages::DocumentMessage* const message);
				
				bool isValidCommand(const uint32 command);
			}
		}
	}
}