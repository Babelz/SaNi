#include "sani/resource/reader/resource_type_reader_manager.hpp"
#include "sani/resource/reader/resource_type_reader.hpp"
#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/effect_reader.hpp"
#include <algorithm>
#include "sani/resource/reader/bitmap_content_reader.hpp"
#include "sani/resource/reader/spritefont_reader.hpp"
#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/argument.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			ResoureTypeReaderManager::~ResoureTypeReaderManager() {
				for (size_t i = 0; i < typeReaders.size(); ++i) {
					delete typeReaders[i];
				}
			}

			void ResoureTypeReaderManager::registerStandardTypes() {
				using namespace sani::resource::reader;
				/*registerTypeReader<Texture2DReader>();
				registerTypeReader<EffectReader>();
				registerTypeReader<BitmapContentReader>();
				registerTypeReader<SpriteFontReader>();
				registerTypeReader<SceneReader>();*/
				auto& derivedClasses = typeof(ResourceTypeReader).getDerivedClasses();
				sani::rtti::Arguments args;
				for (auto& type : derivedClasses) {
					typeReaders.push_back(type.createDynamic(args).getValue<ResourceTypeReader*>());
				}
			}

			ResourceTypeReader* ResoureTypeReaderManager::getReaderByName(const String& name) const {
				auto r = std::find_if(typeReaders.begin(), typeReaders.end(), [name](ResourceTypeReader* reader) {
					return reader->getReaderName() == name;
				});

				if (r != typeReaders.end()) return *r;

				return nullptr;
			}
		}
	}
}