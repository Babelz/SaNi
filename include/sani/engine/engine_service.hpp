#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <stack>

SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);
SANI_FORWARD_DECLARE_1(sani, EngineTime);

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
			static uint32 idGenerator;

			std::stack<String> errors;

			const String name;
			const uint32 id;
		protected:
			SaNiEngine* const getEngine();

			void pushError(const String& error);
		public:
			EngineService(const String& name, SaNiEngine* const engine);

			const String& getName() const;
			const uint32 getID() const;

			bool isUsing(const EngineService* const other) const;
			bool hasHerrors() const;
			
			bool unuse(EngineService* const other);
			bool use(EngineService* const other);

			virtual void update(const EngineTime& time) = 0;

			virtual ~EngineService();

			bool operator = (const EngineService& rhs) const;
			bool operator != (const EngineService& rhs) const;

			/*
				Deleted operators/methods.
			*/

			EngineService(const EngineService&) = delete;
			EngineService(const EngineService&&) = delete;

			void operator =(const EngineService&) = delete;
			void operator =(const EngineService&&) = delete;
		};
	}
}