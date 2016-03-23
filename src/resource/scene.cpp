#include "sani/resource/scene.hpp"

namespace sani {
	namespace resource {

		SceneDescription::SceneDescription(const String8& name, const String8& json) 
			: name(name), json(json) {
		}

		Scene::Scene(const String8& name, const Assets& toLoad)
			: name(name), toLoad(toLoad) {

		}

		Scene::~Scene() {

		}

		const String8& Scene::getName() const {
			return name;
		}

		void Scene::initialize() {

		}
	}
}



