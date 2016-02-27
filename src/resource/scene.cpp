#include "sani/resource/scene.hpp"

namespace sani {
	namespace resource {

		Scene::Scene(const String8& name)
			: name(name) {

		}

		Scene::~Scene() {

		}

		const String8& Scene::getName() const {
			return name;
		}

	}
}



