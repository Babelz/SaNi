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

			/// Constructs xml node with specified node pointer
			/// @param[in] node The node queried from DOM
			XmlNode(rapidxml::xml_node<>* node);

			String value() const;

			void setValue(const String& value);

			/// Queries the DOM to check if node has childs
			///
			/// @return true if the node has children
			bool hasChilds() const;

			/// Does the node have attributes
			/// @return true if node has at least 1 attribute
			bool hasAttributes() const;

			/// Get the attribute matching the name
			/// 
			/// @param[in] attributeName The name of the attribute
			/// @param[out] to Where to store the attribute if found
			/// @return true if the attribute exist, otherwise false
			bool attribute(const char* attributeName, XmlAttribute& to) const;

			bool getChildNodes(std::vector<XmlNode>& childs) const;

			/// Gets the XML element name
			///
			/// @return The name of the XML element
			String getName() const;

			/// Gets first child node
			///
			/// @param node Where to store the node if found
			/// @return true if the node is found, otherwise false
			bool firstNode(XmlNode& node) const;

			/// Gets first child node matching the name
			///
			/// @param name Null terminated string containing the name
			/// @param node Where to store the node if found
			/// @return true if the node is found, otherwise false
			bool firstNode(const char* name, XmlNode& node) const;
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
			bool firstNode(XmlNode& node) const;

			/// Gets first child node matching the name
			///
			/// @param name Null terminated string containing the name
			/// @param node Where to store the node if found
			/// @return true if the node is found, otherwise false
			bool firstNode(const char* name, XmlNode& node) const;
		};
	}
}