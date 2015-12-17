#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/forward_declare.hpp"
#include "sani/core/cvar/cvar.hpp"
#include "sani/core/cvar/cvar_file.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

namespace sani {

	namespace engine {

		namespace services {

			class CVarService : public EngineService {
			private:
				std::list<CVarRecord> records;
				std::list<CVar> cvars;

				void handleDocumentMessage(messages::DocumentMessage* const message);
				void handleQueryMessage(messages::QueryMessage* const message);

				void initialize();
				void syncCVars();

				void generateDefaultConfig();
				void loadConfig();

				void compile(std::list<CVarFile>& files);

				void getCVar(messages::QueryMessage* const message);
				
				void containsCVar(messages::QueryMessage* const message);

				void listCVars(messages::DocumentMessage* const message);
			protected:
				void handleStateMessage(StateMessage* const message) final override;
			public:
				CVarService(SaNiEngine* const engine);

				void receive(messages::Message* const message) final override;
			};
		}
	}
}