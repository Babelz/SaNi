#pragma once

#include <rapidxml/rapidxml.hpp>
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <vector>
#include <stdexcept>
SANI_FORWARD_DECLARE_2(sani, io, FileStream);


namespace sani {
	namespace parser {

		class XmlException : std::runtime_error {
		public:
			XmlException(const std::string& what) 
				: std::runtime_error(what) {}
		};

		class XmlAttribute {
		private:
			rapidxml::xml_attribute<>* attribute;
		public:
			XmlAttribute();
			XmlAttribute(rapidxml::xml_attribute<>*);

			String value() const;

			void setValue(const String& value);
		};

		/// XML node in document
		class XmlNode {
		private:
			rapidxml::xml_node<>* node;
		public:
			/// Default constructor
			XmlNode();
			/// 
			XmlNode(rapidxml::xml_node<>* node);

			String value() const;

			void setValue(const String& value);

			bool hasChilds() const;

			bool hasAttributes() const;

			bool attribute(const char* attributeName, XmlAttribute& to);

			bool getChildNodes(std::vector<XmlNode>& childs) const;
		};

		/// XmlDocument which doesnt support XPath queries
		class XmlDocument {
		private:
			rapidxml::xml_document<> document;
			// rapidxml needs this to be alive (afaik)
			std::vector<unsigned char> sourceText;
		public:

			/// Default constructor
			XmlDocument();

			/// Default destructor
			~XmlDocument();

			/// Loads the xml from stream
			/// 
			/// @param stream The stream opened in read mode
			void load(io::FileStream* stream);

			/// Loads the xml from string
			///
			/// @param xml The string containing the xml
			void loadXml(const String& xml);

			/// Gets first child node
			///
			/// @param node Where to store the node if found
			/// @return true if the node is found, otherwise false
			bool firstNode(XmlNode& node);

			/// Gets first child node matching the name
			///
			/// @param name Null terminated string containing the name
			/// @param node Where to store the node if found
			/// @return true if the node is found, otherwise false
			bool firstNode(const char* name, XmlNode& node);
		};
	}
}