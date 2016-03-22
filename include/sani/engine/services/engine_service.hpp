#pragma once

#include "sani/engine/service_state.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <stack>
#include <list>

SANI_FORWARD_DECLARE_3(sani, engine, messages, Message);
SANI_FORWARD_DECLARE_2(sani, engine, StateMessage);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);
SANI_FORWARD_DECLARE_1(sani, EngineTime);

using namespace sani::engine;

namespace sani {

	namespace engine {

		namespace services {

			/// @class EngineService engine_service.hpp "sani/engine/engine_service.hpp"
			/// @author voidbab
			///
			/// Represents a shared service inside the engine. 
			/// Services contain a given set of operations and may have some special purpose.
			/// Services can use other services if they require
			/// some given set of operations defined by another service.
			/// Services can work as standalone as well, meaning they don't 
			/// depend on any other services.
			/// Services control the whole logical flow of the engine and 
			/// can even close the engine.
			class EngineService {
			private:
				static uint32 idGenerator;

				engine::SaNiEngine* const engine;
				ServiceState state;

				// Name of the service.
				const String name;
				// Unique identifier of the service.
				const uint32 id;
			
				void checkIfTerminated(const char* caller);
			protected:
				engine::SaNiEngine* const getEngine();

				EngineService(const String& name, engine::SaNiEngine* const engine);

				/// Internal event called when the service is being started.
				virtual bool onStart();
				/// Internal event called when the service is being resumed.
				virtual bool onResume();
				/// Internal event called when the service is being suspended.
				virtual void onSuspend();
				/// Internal event called when the service is being terminated.
				virtual void onTerminate();
			public:
				/// Starts the service. First call 
				/// allows for service specific initialization.
				bool start();
				/// Suspends the service. While suspended, the service can't
				/// process or send any messages.
				void suspend();
				/// Terminates the service. Services that are
				/// terminated should not be used anymore.
				/// Clears service state and disposes of memory
				/// the service is using.
				void terminate();

				/// Process all incoming messages.
				virtual void receive(messages::Message* const message);
				/// Can be used to update the services state.
				virtual void update(const EngineTime& time);

				ServiceState getState() const;

				const String& getName() const;
				uint32 getID() const;

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
}