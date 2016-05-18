#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);

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
					/// Creates new element of a given type.
					CreateElement = 0,

					/// Deletes given element of a given type.
					DeleteElement = 1,

					/// Returns all elements of a given type to the user.
					GetElements = 2
				};

				enum class ElementType : uint32 {
					Rectangle = 0,

					Triangle,

					Sprite,

					Circle,

					SpriteAnimation,

					ParticleEmitter,
					
					Text
				};

				void createElement(messages::DocumentMessage* const message, const ElementType type);

				void deleteElement(messages::DocumentMessage* const message, const ElementType type);

				void getElements(messages::DocumentMessage* const message, const ElementType type);
			}
		}
	}
}