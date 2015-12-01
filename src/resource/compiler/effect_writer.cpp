#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/compiler/effect_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/effect_content.hpp"
namespace sani {
	namespace resource {
		namespace compiler {
			EffectWriter::EffectWriter() 
				: ResourceTypeWriter() {

			}
			EffectWriter::~EffectWriter() {

			}

			void EffectWriter::write(ResourceWriter* writer, const void* value) {
				const EffectContent* content = static_cast<const EffectContent*>(value);

				// hmm hmm hmm hmm
				bool isCompiled = content->isCompiled();
				writer->write((uint8)isCompiled);

				if (isCompiled) {
					writer->write(content->getEffectCode());
				}
				// fallback
				writer->write(content->getVertexCode());
				writer->write(content->getFragmentCode());
			}
		}
	}
}
#endif