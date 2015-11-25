#pragma once

#include "sani/engine/service_state.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <stack>
#include <list>

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
			std::list<EngineService*> dependencies;
			
			SaNiEngine* const engine;
			ServiceState state;

			const String name;
			const uint32 id;
		protected:
			virtual bool onInitialize() = 0;
			virtual void onUpdate(const EngineTime& time) = 0;

			virtual void onSuspend();
			virtual bool onResume();
			virtual void onStop();

			SaNiEngine* const getEngine();

			void pushError(const String& error);

			EngineService(const String& name, SaNiEngine* const engine);
		public:
			ServiceState getState() const;
			const String& getName() const;
			const uint32 getID() const;

			/// Suspends the service.
			void suspend();
			/// Starts/resumes the service.
			bool start();
			/// Stops the service and prepares it to be disposed.
			void stop();

			void update(const EngineTime& time);

			/// Returns true if this service is using the given service.
			bool isUsing(const EngineService* const other) const;
			/// Returns true if this service has errors.
			bool hasHerrors() const;
			
			bool unuse(EngineService* const other);
			bool use(EngineService* const other);

			virtual ~EngineService();

			bool operator == (const EngineService& rhs) const;
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