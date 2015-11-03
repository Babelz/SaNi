#pragma once
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
			size_t width;
			size_t height;

		public:
			Texture2D(const size_t width, const size_t height);
			~Texture2D();
			size_t getWidth() const;
			size_t getHeight() const;
		};
		
	}
}
// TODO this can be moved to somewhere else?
SANI_DESERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::reader::Texture2DReader);
//SANI_SERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::compiler::Texture2DWriter);

