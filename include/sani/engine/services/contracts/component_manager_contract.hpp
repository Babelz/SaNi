#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace componentmanager {

				/*
					TODO: gen contracts with macros?
				*/

				enum class ComponentManagerCommands : uint32 {
					CreateComponent  = 0,

					DestroyComponent = 1,

					ListComponents	 = 2
				};

				void createComponent(const String& recipient, messages::DocumentMessage* const message);

				void destroyComponent(const String& recipient, messages::QueryMessage* const message, const uint32 id);

				void listComponents(const String& recipient, messages::DocumentMessage* const message);
			}
		}
	}
}