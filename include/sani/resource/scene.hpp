#pragma once

#include "sani/resource/resource.hpp"
#include "sani/types.hpp"
#include "resource_item.hpp"
#include <map>
#include <vector>

namespace sani {
	namespace resource {

		struct AssetFolder {
			const uint32 id;
			const String8 name;
		};

		struct AssetFile {
			const uint32 id;
			const String8 name;
		};

		class SceneDescription : public ResourceItem {
		private:
			String8 name;
			std::vector<AssetFolder> assetFolders;
			std::map<uint32, std::vector<AssetFile>> assets;
		public:
			SceneDescription(const String8& name);
			void addFolder(const AssetFolder& folder);
			void addAssetTo(const AssetFolder& folder, const AssetFile& file);
		};

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

