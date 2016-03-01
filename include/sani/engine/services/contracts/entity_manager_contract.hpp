#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace entitymanager {

				enum class EntityManagerCommands : uint32 {
					CreateEntity	= 0,

					DestroyEntity	= 1,

					ListEntities	= 2
				};

				void createEntity(messages::DocumentMessage* const message);

				void destroyEntity(messages::QueryMessage* const message, const uint32 id);

				void listEntities(messages::DocumentMessage* const message);
			}
		}
	}
}