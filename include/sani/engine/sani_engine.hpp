#pragma once

namespace sani {

	namespace engine {
		
		/// @class SaNiEngine sani_engine.hpp "sani/engine/sani_engine.hpp"
		/// @author voidbab
		///
		/// The core of the engine. 
		class SaNiEngine {
		private:
			bool running;
		public:
			SaNiEngine();

			/// Initializes the engine.
			bool initialize();
			
			/// Starts the engine.
			void start();
			/// Causes the engine to quit.
			void quit();

			~SaNiEngine();
		};
	}
}