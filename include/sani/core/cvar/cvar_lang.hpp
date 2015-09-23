#pragma once

/*
	Contains the regular language of the cvar system.
*/

#include "sani/precompiled.hpp"
#include <regex>

namespace sani {

	// TODO: is this kind of stuff ok?
	//		 ie consts in some namespace with some helpers (like a util class)

	namespace cvarlang {

		enum ConditionalOperators {
			None,

			NoOperation,

			// ==
			Equal,

			// !=
			NotEqual,

			// <
			Smaller,

			// <=
			SmallerOrEqual,

			// >
			Greater,

			// >=
			GreaterOrEqual
		};

		enum ValueType {
			None,

			StringVal,

			// 32-bit integer.
			IntVal,

			// 32-bit floating point number.
			FloatVal,

			// 64-bit floating point number.
			DoubleVal
		};

		enum LogicalOperators {
			// No operation.
			None,

			// &&
			And,

			// ||
			Or
		};

		enum TokenType {
			Invalid,
			EmptyOrComment,
			Declaration,
			Require
		};

		/*
			Words.
		*/

		namespace lang {

			const String Require			= "require *";
			const String Comment			= "//.+";

			const String StringType			= "\".+\"";
			const String IntType			= "[0-9]+";
			const String DoubleType			= "[0-9]+\\.[0-9]+";
			const String FloatType			= DoubleType + "f";

			const String ConstValue			= StringType + "|" + IntType + "|" + DoubleType + 
											  "|" + FloatType;

			const String Message			= "message(\"[a-zA-Z ]\")";

			const String Declaration		= "[a-zA-Z_]+ *";
			const String StringDeclaration  = Declaration + StringType;
			const String IntDeclaration		= Declaration + IntType;
			const String DoubleDeclaration  = Declaration + DoubleType;
			const String FloatDeclaration   = DoubleDeclaration + FloatType;

			const String ValidDeclaration	= Declaration + ConstValue;

			/*
				Conditional operators.
			*/

			const String Equal				= "==";
			const String NotEqual			= "!=";

			const String Smaller			= "<";
			const String SmallerOrEqual		= "<=";

			const String Greater			= ">";
			const String GreaterOrEqual		= ">=";

			const String ConditionalOper = Equal + "|" + NotEqual + "|" + Smaller + "|" +
										   SmallerOrEqual  + "|" + Greater  + "|" +  
										   GreaterOrEqual;

			/*
				Logical operators.
			*/

			const String And				= "&&";
			const String Or					= "||";

			const String LogicalOper	    = And + "|" + Or;

			/*
				Helpers.
			*/

			inline bool isEmptyOrWhitespace(const String& str) {
				return str.empty();
			}

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
				const std::regex regex(Require);
				const size_t strLen = str.size();

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
			
			inline bool isConstValue(const String& str) {
				return std::regex_match(str, std::regex(ConstValue));
			}

			inline bool containsConditionalOperators(const String& str) {
				return std::regex_match(str, std::regex(ConditionalOper));
			}
			inline bool isConstBoolExpression(const String& str) {
				return !containsConditionalOperators(str);
			}
			inline bool containsLogicalOperators(const String& str) {
				return std::regex_match(str, std::regex(LogicalOper));
			}
		}

		inline ValueType resolveType(const String& str) {
			if		(lang::isStringDeclaration(str))	return ValueType::StringVal;
			else if (lang::isIntDeclaration(str))		return ValueType::IntVal;
			else if (lang::isDoubleDeclaration(str))	return ValueType::DoubleVal;
			else if (lang::isFloatDeclaration(str))		return ValueType::FloatVal;
			else										throw std::logic_error("invalid or unsupported cvar value type");
		}
	}
}