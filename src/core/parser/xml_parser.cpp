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

		bool XmlDocument::firstNode(const char* name, XmlNode& to) {
			// not found
			rapidxml::xml_node<>* node;
			if ((node = document.first_node(name)) == nullptr) {
				return false;
			}
			to = XmlNode(node);
			return true;
		}
		
		bool XmlDocument::firstNode(XmlNode& node) {
			return firstNode(0, node);
		}

		XmlNode::XmlNode()
			: node(nullptr) {
		}

		XmlNode::XmlNode(rapidxml::xml_node<>* node) 
			: node(node) {

		}

		String XmlNode::value() const {
			return String(node->value());
		}

		void XmlNode::setValue(const String& value) {
			node->value(value.c_str());
		}

		bool XmlNode::hasChilds() const {
			return node->first_node() != nullptr;
		}

	}
}