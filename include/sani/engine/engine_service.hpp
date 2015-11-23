#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

namespace sani {

	namespace engine {

		/// @class EngineService engine_service.hpp "sani/engine/engine_service.hpp"
		/// @author voidbab
		///
		/// Represents a shared service inside the engine. 
		/// Services contain a given set of operations and may have some special purpose.
		/// Services can use other services if they require
		/// some given set of operations defined by another service.
		/// Services can work as standalone as well, meaning they don't 
		/// depend on any other services.
		class EngineService {
		private:
			String name;
		protected:
			EngineService(SaNiEngine* engine, );

			virtual ~EngineService();
		};
	}
}