#include "sani/engine/services/engine_services.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar.hpp"

#include <list>

namespace sani {

	namespace engine {

		class CVarService : public EngineService {
		private:
			std::list<CVarRecord> records;
			
			std::list<CVar> cvars;
		protected:
			bool onInitialize() override;
			
			void onStop() override;
		public:
			CVarService(SaNiEngine* const engine);

			CVar& getCvar() const;

			~CVarService();
		};
	}
}