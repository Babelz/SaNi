#include "sani/engine/services/engine_services.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar.hpp"

#include <list>

namespace sani {

	namespace engine {

		/// @class CVarService cvar_service.hpp "sani/engine/services/cvar_service.hpp"
		/// @author voidbab
		///
		/// Contains and manages cvars. Can be used to run commands as well.
		class CVarService : public EngineService {
		private:
			std::list<CVarRecord> records;
			std::list<CVar> cvars;

			void useUserDefinedConfiguration();
			void useDefaultConfiguration();
			void checkForRequiredCVars();
		protected:
			bool onInitialize() override;
			
			void onStop() override;
		public:
			CVarService(SaNiEngine* const engine);

			CVar* const findCVar(const String& name);

			/*
				TODO: add exec interface once it has been implemented.

				void runCommand(const CVarCommand& command);
			*/

			~CVarService();
		};
	}
}