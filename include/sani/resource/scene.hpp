#pragma once

#include "sani/resource/resource.hpp"
#include "sani/types.hpp"
#include "resource_item.hpp"
#include <map>
#include <vector>
#include "sani/resource/serialization.hpp"
#include <unordered_map>
#include "sani/rtti/type.hpp"

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
			struct PrimitiveField {
                String8 name;
                String8 value;
				rtti::TypeID type;
                PrimitiveField(const String8& name, const String8& value)
                    : name(name), value(value), type(rtti::Type::Invalid) {}
			};

            struct ObjectField {
                String8 name;
                std::vector<PrimitiveField> fields;
            };
            
			struct Component {
				String8 name;
                std::vector<PrimitiveField> primitiveFields;
                std::vector<ObjectField> objectFields;
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

