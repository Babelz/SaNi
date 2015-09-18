/*
	Contains the regular language of the cvar system.
*/

#include "sani/precompiled.hpp"
#include <regex>

namespace sani {

	// TODO: is this kind of stuff ok?
	//		 ie consts in some namespace with some helpers (like a util class)

	namespace cvarlang {

		/*
			Words.
		*/

		namespace lang {

			const String Require			= "require *";
			const String Include			= "include *";
			const String FileDeclaration	= "\".+\\.cfg\"";
			const String Comment			= "//.+";

			const String StringType			= "\".+\"";
			const String IntType			= "[0-9]+";
			const String DoubleType			= "[0-9]+\\.[0-9]+";
			const String FloatType			= DoubleType + "f";

			const String Declaration		= "[a-zA-Z_]+ *";
			const String StringDeclaration  = Declaration + StringType;
			const String IntDeclaration		= Declaration + IntType;
			const String DoubleDeclaration  = Declaration + DoubleType;
			const String FloatDeclaration   = DoubleDeclaration + FloatType;

			const String ValidDeclaration	= Declaration + StringType + "|" + IntType + "|" +
											  DoubleType + "|" + FloatType;

			/*
				Statements.
				*/

			const String RequireFile = Include + " *?" + FileDeclaration;

			/*
				Helpers.
				*/

			inline bool startsWithComment(const String& str) {
				if (str.size() >= 2) return str.substr(0, 2) == "//";
				else			     return false;
			}
			inline bool containsComment(const String& str) {
				return std::regex_match(str, std::regex(Comment));
			}
			
			inline bool startsWithRequire(const String& str) {
				return std::regex_match(str, std::regex(Require));
			}
			inline bool isValidRequire(const String& str) {
				const std::regex regex(RequireFile);
				const size_t strLen = str.size();

				// TODO: complete.

				return false;
			}

			inline bool startsWithInclude(const String& str) {
				return std::regex_match(str, std::regex(Include));
			}
			inline bool isValidInclude(const String& str) {
				// TODO: complete.

				return false;
			}

			inline bool isDeclaration(const String& str) {
				return std::regex_match(str, std::regex(Declaration));
			}
			inline bool isValidDeclaration(const String& str) {
				return std::regex_match(str, std::regex(ValidDeclaration));
			}

			inline bool isStringDeclaration(const String& str) {
				return std::regex_match(str, std::regex(StringDeclaration));
			}
			inline bool isIntDeclaration(const String& str) {
				return std::regex_match(str, std::regex(IntDeclaration));
			}
			inline bool isDoubleDeclaration(const String& str) {
				return std::regex_match(str, std::regex(DoubleDeclaration));
			}
			inline bool isFloatDeclaration(const String& str) {
				return std::regex_match(str, std::regex(FloatDeclaration));
			}
		}
	}
}