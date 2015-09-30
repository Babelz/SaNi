#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
namespace sani {
	namespace resource {
		namespace compiler {
			void Texture2DWriter::write(ResourceWriter* writer, void* value) {
				Texture2D* tex = static_cast<Texture2D*>(value);
				writer->write(tex->getWidth());
				writer->write(tex->getHeight());
				// todo write pixels and shit
			}
		}
	}
}