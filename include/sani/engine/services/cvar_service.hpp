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

			/// Contains runtime information regarding the 
			/// current cvar configuration.
			struct CVarConfiguration {
				// TODO: can we sync shit while running 
				//		 on android?
				const bool canSync;

				bool isDefault;

				CVarConfiguration() : isDefault(false),
									  #if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
										canSync(true)
									  #elif
										canSync(false)
									  #endif 
									  {
				}

				~CVarConfiguration() = default;
			};

			class CVarService : public EngineService {
			private:
				CVarConfiguration configuration;

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