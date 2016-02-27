#pragma once

#include "sani/resource/resource.hpp"
#include "sani/types.hpp"

namespace sani {
	namespace resource {
		class Scene : public Resource {
		private:
			String8 name;
		public:
			Scene(const String8& name);
			~Scene();

			const String8& getName() const;
			
		};
	}
}

