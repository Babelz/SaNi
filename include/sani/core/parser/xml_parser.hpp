#pragma once

#include <rapidxml/rapidxml.hpp>
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <vector>
SANI_FORWARD_DECLARE_2(sani, io, FileStream);


namespace sani {
	namespace parser {
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
		};
	}
}