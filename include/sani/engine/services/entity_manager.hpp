#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_1(sani, Entity);

namespace sani {

	namespace engine {

		namespace services {

			/// @class EntityManager entity_manager.hpp "sani/engine/services/cvar_service.hpp"
			/// @author voidbab
			///
			/// Service responsible of managing the entities.
			class EntityManager final : public EngineService {
			private:
			public:
				EntityManager();
				EntityManager();
			};
		}
	}
}