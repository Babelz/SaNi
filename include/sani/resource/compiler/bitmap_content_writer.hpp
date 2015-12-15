#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/resource/bitmap_content.hpp"

namespace sani {
	namespace resource {
		namespace compiler {
			class BitmapContentWriter : public ResourceTypeWriter {
			public:
				BitmapContentWriter() : ResourceTypeWriter() {

				}
				~BitmapContentWriter() {}
				void write(ResourceWriter* writer, const void* value) override;

				virtual String getRuntimeReader() const {
					return DeserializableWith<BitmapContent>::value();
				}
			};
		}
	}
}

#endif