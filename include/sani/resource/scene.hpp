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
			String8 name;
			String8 json;

			SceneDescription(const String8& name, const String8& json);
		};

		class Scene : public Resource {
		public:
		private:
			String8 name;
			bool initialized{ false };
		public:
			Scene(const String8& name);
			~Scene();

			const String8& getName() const;
			void initialize();
		};
	}
}

SANI_DESERIALIZABLE_WITH(sani::resource::Scene, sani::resource::reader::SceneReader);

