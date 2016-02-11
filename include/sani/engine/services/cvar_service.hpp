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
				// We assume we can't sync stuff while running on
				// android so we just set it to false.
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

			/// @class CVarService cvar_service.hpp "sani/engine/service/cvar_service.hpp"
			/// @author voidbab
			///
			/// Service providing access to cvars.
			class CVarService final : public EngineService {
			private:
				const String Config = String("config");
				const String ConfigRoot = String(Config + "\\");

				CVarConfiguration configuration;

				std::list<CVarFile> cvarFiles;
				std::list<CVarRecord> records;
				std::list<CVar> cvars;

				void handleDocumentMessage(messages::DocumentMessage* const message);
				void handleQueryMessage(messages::QueryMessage* const message);

				/// Initialize the service.
				void initialize();
				/// Sync all cvars to a file.
				void syncCVars();

				void syncFile(CVarFile &file, io::FileStream* stream, String currentFilename);

				/// Generate default configuration.
				void generateDefaultConfig();
				/// Load configuration.
				void loadConfig();

				/// Compile given cvar files.
				void compile(std::list<CVarFile>& files);

				/// Returns cvar with given name.
				void getCVar(messages::QueryMessage* const message);
				
				/// Queries for given cvar.
				void containsCVar(messages::QueryMessage* const message);

				/// List all services.
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