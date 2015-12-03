#include "sani/core/parser/xml_parser.hpp"
#include "sani/platform/file/file_stream.hpp"
#include <vector>
#include <iostream>
namespace sani {
	namespace parser {
		XmlDocument::XmlDocument() {}

		XmlDocument::~XmlDocument() {}

		void XmlDocument::load(io::FileStream* stream) {
			uint32 size = static_cast<uint32>(stream->size());
			sourceText = (std::vector<unsigned char>((size + 1u), '\0'));
			stream->read(sourceText.data(), size);
			
			try {
				document.parse<0>((char*)sourceText.data());
			}
			catch (rapidxml::parse_error& error) {
				throw sani::parser::XmlException(error.what());
			}
		}

		bool XmlDocument::firstNode(const char* name, XmlNode& to) const {
			// not found
			rapidxml::xml_node<>* node;
			if ((node = document.first_node(name)) == nullptr) {
				return false;
			}
			to = XmlNode(node);
			return true;
		}
		
		bool XmlDocument::firstNode(XmlNode& node) const {
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

		bool XmlNode::hasAttributes() const {
			return node->first_attribute() != nullptr;
		}

		bool XmlNode::attribute(const char* attributeName, XmlAttribute& to) const {
			rapidxml::xml_attribute<>* attr;
			if ((attr = node->first_attribute(attributeName)) == nullptr) {
				return false;
			}

			to = XmlAttribute(attr);
			return true;
		}

		bool XmlNode::firstNode(const char* name, XmlNode& to) const {
			rapidxml::xml_node<>* child;
			if ((child = node->first_node()) == nullptr) {
				return false;
			}
			to = XmlNode(child);
			return true;
		}

		bool XmlNode::firstNode(XmlNode& node) const {
			return firstNode(0, node);
		}

		bool XmlNode::getChildNodes(std::vector<XmlNode>& childs) const {
			rapidxml::xml_node<>* child;
			if ((child = node->first_node()) == nullptr) {
				return false;
			}
			childs.push_back(XmlNode(child));
			while ((child = child->next_sibling()) != nullptr) {
				childs.push_back(XmlNode(child));
			}
			return true;
		}

		bool XmlNode::getAttributes(std::vector<XmlAttribute>& attributes) const {
			rapidxml::xml_attribute<>* attribute;
			if ((attribute = node->first_attribute()) == nullptr) {
				return false;
			}
			attributes.push_back(XmlAttribute(attribute));
			while ((attribute = attribute->next_attribute()) != nullptr) {
				attributes.push_back(XmlAttribute(attribute));
			}
			return !attributes.empty();
		}

		String XmlNode::getName() const {
			return node->name();
		}

		XmlAttribute::XmlAttribute()
			: attribute(nullptr) {
		}

		XmlAttribute::XmlAttribute(rapidxml::xml_attribute<>* attr)
			: attribute(attr) {
		}

		String XmlAttribute::value() const {
			return attribute->value();
		}

		void XmlAttribute::setValue(const String& value) {
			attribute->value(value.c_str());
		}

	}
}