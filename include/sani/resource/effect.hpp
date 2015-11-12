#pragma once

#include "sani/types.hpp"
#include "sani/resource/resource.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, resource, reader, EffectReader);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, resource, EffectContent);

namespace sani {
	namespace resource {
		class Effect : public Resource {
		private:
			uint32 id;
		public:
			Effect(graphics::GraphicsDevice* device, const String& code);
		};
	}
}
SANI_DESERIALIZABLE_WITH(sani::resource::EffectContent, sani::resource::reader::EffectReader);