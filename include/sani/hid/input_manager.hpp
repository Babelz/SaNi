#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

namespace sani {
	namespace engine {
		namespace services {

			class InputManager : public EngineService {
			private:

			public:
				/// Process all incoming messages.
				virtual void receive(messages::Message* const message) override final;
				/// Can be used to update the services state.
				virtual void update(const EngineTime& time) override final;

				void bindKey();
			};
		}
	}
}