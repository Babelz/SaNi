#include "sani/core/parser/xml_parser.hpp"
#include "sani/platform/file/file_stream.hpp"
#include <vector>

namespace sani {
	namespace parser {
		XmlDocument::XmlDocument() {}

		XmlDocument::~XmlDocument() {}

		void XmlDocument::load(io::FileStream* stream) {
			int64 size = stream->size();
			sourceText = (std::vector<unsigned char>((size + 1u), '\0'));
			stream->read(sourceText.data(), size);
			
			document.parse<0>((char*)sourceText.data());
		}
	}
}