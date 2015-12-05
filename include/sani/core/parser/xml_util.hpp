#pragma once
#include "xml_parser.hpp"
#include <limits>
#include <sstream>
#include <type_traits>

namespace sani {
	namespace parser {
		class XmlUtil {
		private:
			template<typename to, typename from>
			static to lexical_cast(from const &x) {
				std::stringstream os;
				to ret;

				os << x;
				os >> ret;

				return ret;
			}
		public:
			template <class T>
			static T get(const XmlAttribute& attr) {
				return lexical_cast<T>(attr.value());
			}

			template <class T>
			static T get(const XmlNode& node) {
				return lexical_cast<T>(node.value());
			}

			template <class T>
			static T get(const XmlNode& node, const char* attrName, T defaultValue) {
				XmlAttribute attr;
				if (!node.attribute(attrName, attr)) return defaultValue;
				return get(attr);
			}

		};
	}
}