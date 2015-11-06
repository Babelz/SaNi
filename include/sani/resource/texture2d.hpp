#pragma once
#include "sani/types.hpp"
#include "sani/resource/resource.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, resource, reader, Texture2DReader);
SANI_FORWARD_DECLARE_2(sani, resource, Texture2DContent);
SANI_FORWARD_DECLARE_3(sani, resource, compiler, Texture2DWriter)

namespace sani {
	namespace resource {
		class Texture2D : public Resource {
		private:
			uint32 width;
			uint32 height;

		public:
			Texture2D(const uint32 width, const uint32 height);
			~Texture2D();
			uint32 getWidth() const;
			uint32 getHeight() const;
		};
		
	}
}
// TODO this can be moved to somewhere else?
SANI_DESERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::reader::Texture2DReader);
//SANI_SERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::compiler::Texture2DWriter);

