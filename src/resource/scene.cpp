#include "sani/resource/scene.hpp"

namespace sani {
	namespace resource {

		SceneDescription::SceneDescription(const String8& name) 
			: name(name) {
		}

		void SceneDescription::addFolder(const AssetFolder& folder) {
			assetFolders.push_back(folder);
		}

		void SceneDescription::addAssetTo(const AssetFolder& folder, const AssetFile& file) {
			assets[folder.id].push_back(file);
		}

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



