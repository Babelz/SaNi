#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {

		SaNiEngine::SaNiEngine() : running(false) {
		}

		/// Initializes the engine.
		bool SaNiEngine::initialize() {
			return 0;
		}

		/// Starts the engine.
		void SaNiEngine::start() {
		}
		/// Causes the engine to quit.
		void SaNiEngine::quit() {
		}

		SaNiEngine::~SaNiEngine() {
		}
	}
}