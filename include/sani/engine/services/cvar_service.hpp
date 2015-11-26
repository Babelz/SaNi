#include "sani/engine/engine_service.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar.hpp"

#include <list>

SANI_FORWARD_DECLARE_2(sani, engine, FileSystemService);

namespace sani {

	namespace engine {

		/// @class CVarService cvar_service.hpp "sani/engine/services/cvar_service.hpp"
		/// @author voidbab
		///
		/// Contains and manages cvars. Can be used to run commands as well.
		class CVarService : public EngineService {
		private:
			FileSystemService* fileSystemService;

			std::list<CVarFile> files;
			std::list<CVarRecord> records;
			std::list<CVar> cvars;

			void loadFiles();

			void useUserDefinedConfiguration();
			void useDefaultConfiguration();
			void checkForRequiredCVars();
		protected:
			void onInitialize() override;
			
			void onStop() override;
		public:
			CVarService(SaNiEngine* const engine);

			CVar* const findCVar(const String& name);

			/*
				TODO: add exec interface once it has been implemented.

				void runCommand(const CVarCommand& command);
			*/
		};
	}
}