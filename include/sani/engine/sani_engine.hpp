#pragma once

namespace sani {

	namespace engine {
		
		class SaNiEngine {
		private:
		public:
			SaNiEngine();

			bool initialize();
			
			void start();

			~SaNiEngine();
		};
	}
}