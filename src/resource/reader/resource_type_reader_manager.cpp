#include "sani/resource/reader/resource_type_reader_manager.hpp"
#include "sani/resource/reader/resource_type_reader.hpp"
#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/effect_reader.hpp"
#include <algorithm>

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
				registerTypeReader<Texture2DReader>();
				registerTypeReader<EffectReader>();
			}

			ResourceTypeReader* ResoureTypeReaderManager::getReaderByName(const String& name) const {
				auto r = std::find_if(typeReaders.begin(), typeReaders.end(), [name](ResourceTypeReader* reader) {
					return reader->getReaderName() == name;
				});

				if (*r) return *r;

				return nullptr;
			}
		}
	}
}