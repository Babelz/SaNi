#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
#include "sani/resource/compiler/scene_description_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
#include <sstream>

namespace sani {
	namespace resource {
		namespace compiler {

			SceneDescriptionWriter::SceneDescriptionWriter() {

			}

			SceneDescriptionWriter::~SceneDescriptionWriter() {

			}

			void SceneDescriptionWriter::write(ResourceWriter* writer, const void* value) {
				const SceneDescription* content = static_cast<const SceneDescription*>(value);
				writer->write(content->name);
				writer->write(content->json);
			}
		}
	}
}

#endif

