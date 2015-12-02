#include "sani/core/parser/xml_parser.hpp"
#include "sani/platform/file/file_stream.hpp"
#include <vector>
#include <iostream>
namespace sani {
	namespace parser {
		XmlDocument::XmlDocument() {}

		XmlDocument::~XmlDocument() {}

		void XmlDocument::load(io::FileStream* stream) {
			int64 size = stream->size();
			sourceText = (std::vector<unsigned char>((size + 1u), '\0'));
			stream->read(sourceText.data(), size);
			
			try {
				document.parse<0>((char*)sourceText.data());
			}
			catch (rapidxml::parse_error& error) {
				throw sani::parser::XmlException(error.what());
			}
		}
	}
}