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

		const String Require			= "require";
		const String FileDeclaration	= "\".+\.cfg\"";
		const String Comment			= "//.+";

		/*
			Statements.
		*/

		const String RequireFile		= Require + " *?" + FileDeclaration;

		/*
			Helpers.
		*/

		inline bool containsComment(const String& str) {
			return std::regex_match(str, std::regex(Comment));
		}
		inline void removeComment(String& str) {
			str = str.substr(0, str.find("//"));
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
	}
}