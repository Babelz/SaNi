#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace resourcemanagerhandler {

				enum class ResourceManagerHandlerCommands : uint32 {
					GetDefaultResourceManager = 0
				};

				void getDefaultResourceManager(messages::DocumentMessage* const message);
			}
		}
	}
}