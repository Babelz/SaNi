#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);

namespace sani {

	namespace engine {
		
		namespace services {

			namespace cvarservice {

				enum class CVarServiceCommands : uint32 {
					GetCVar			= 0,

					ListCVars		= 1
				};

				void getCVar(messages::QueryMessage* const message, const String& name);
				
				void listCVars(messages::DocumentMessage* const message);
			}
		}
	}
}