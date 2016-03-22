#pragma once

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/resource/scene.hpp"

namespace sani {

	namespace resource {

		namespace compiler {

			class SceneDescriptionWriter : public ResourceTypeWriter {
			public:
				SceneDescriptionWriter();

				~SceneDescriptionWriter();

				void write(ResourceWriter* writer, const void* value) override;

				virtual String getRuntimeReader() const override {
					return DeserializableWith<Scene>::value();
				}
			};
		}
	}
}

#endif