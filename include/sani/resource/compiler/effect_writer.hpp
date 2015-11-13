#pragma once
#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/resource/effect.hpp"

namespace sani {
	namespace resource {
		namespace compiler {
			class EffectWriter : public ResourceTypeWriter {
			public:
				EffectWriter();
				~EffectWriter();
				void write(ResourceWriter* writer, const void* value) override;

				virtual String getRuntimeReader() const override {
					return DeserializableWith<EffectContent>::value();
				}
			};
		}
	}
}