#pragma once

#include "sani/resource/resource.hpp"
#include "sani/types.hpp"
#include "resource_item.hpp"
#include <map>
#include <vector>
#include "sani/resource/serialization.hpp"
#include <unordered_map>

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

		struct SceneDescription : public ResourceItem {
			struct Field {
				String8 name;
				std::unordered_map<String8, String8> keyValues;
			};

			struct Component {
				String8 name;
				std::vector<Field> fields;
			};
			using ComponentDataCollection = std::vector<Component>;

			String8 name;
			std::vector<AssetFolder> assetFolders;
			std::map<uint32, std::vector<AssetFile>> assets;
			ComponentDataCollection components;


			SceneDescription(const String8& name);
			void addFolder(const AssetFolder& folder);
			void addAssetTo(const AssetFolder& folder, const AssetFile& file);
		};

		class Scene : public Resource {
		public:
			using Assets = std::vector < String8 >;
		private:
			String8 name;
			Assets toLoad;
			bool initialized{ false };
		public:
			Scene(const String8& name, const Assets& toLoad);
			~Scene();

			const String8& getName() const;
			void initialize();
		};
	}
}

SANI_DESERIALIZABLE_WITH(sani::resource::Scene, sani::resource::reader::SceneReader);

