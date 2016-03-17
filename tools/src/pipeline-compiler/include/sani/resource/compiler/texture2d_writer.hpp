#pragma once

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/resource/texture2d_content.hpp"

namespace sani {

	namespace resource {

		namespace compiler {

			class Texture2DWriter : public ResourceTypeWriter {
			public:
				Texture2DWriter();
					
				~Texture2DWriter();

				void write(ResourceWriter* writer, const void* value) override;

				virtual String getRuntimeReader() const {
					return DeserializableWith<Texture2DContent>::value();
				}
			};
		}
	}
}

#endif