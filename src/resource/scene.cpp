#include "sani/resource/scene.hpp"

namespace sani {
	namespace resource {

		SceneDescription::SceneDescription(const String8& json) 
			: json(json) {
		}

        Scene::Scene(const String8& name)
            : name(name) {

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



