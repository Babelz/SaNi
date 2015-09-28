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
			NoValue,

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
			Require,
			Message
		};

		/*
			Regular language.
		*/

		namespace lang {
			
			/*
				TODO: after the system has been implemented, remove any not
					  needed statements and tokens.
			*/

			const String RequireKeyword		= "require";
			const String MessageKeyword		= "message";

			const String Require			= RequireKeyword + " *";
			const String Comment			= "//";

			const String StringType			= "\".+\"";
			const String IntType			= "[0-9]+";
			const String DoubleType			= "[0-9]+\\.[0-9]+";
			const String FloatType			= DoubleType + "f";

			const String ConstValue			= StringType + "|" + IntType + "|" + DoubleType + 
											  "|" + FloatType;

			const String Message			= MessageKeyword + " *(.+)";

			const String Declaration		= "[a-zA-Z_]+ *";
			const String StringDeclaration  = Declaration + StringType;
			const String IntDeclaration		= Declaration + IntType;
			const String DoubleDeclaration  = Declaration + DoubleType;
			const String FloatDeclaration   = DoubleDeclaration + "f";

			const String ValidDeclaration	= Declaration + ConstValue;

			// Probably the worst regex EU but w/e. Can't string 
			// like a MLG and bet never will.
			const String ValidRequirement   = "((([a-zA-Z]|[0-9])+| *== *| *!= *| *<= *| *< *| *>= *| *> *)|(([a-zA-Z]|[0-9])+| *&& *| *\\|\\| *))+";

			/*
				Conditional operators.
			*/

			const String Equal				= "==";
			const String NotEqual			= "!=";

			const String Smaller			= "<";
			const String SmallerOrEqual		= "<=";

			const String Greater			= ">";
			const String GreaterOrEqual		= ">=";

			/*
				Logical operators.
			*/

			const String And				= "&&";
			const String Or					= "\\|\\|";

			/*
				Helpers.
			*/

			/*
				Bogus regexes.. They don't fucking work, why?!
			*/

			inline bool isEmptyOrWhitespace(const String& str) {
				return str.empty();
			}

			inline bool startsWithComment(const String& str) {
				if (str.size() >= 2) return str.substr(0, 2) == Comment;
				else			     return false;
			}
			inline bool containsComment(const String& str) {
				return str.find(Comment) != str.npos;
			}
			
			inline bool startsWithRequire(const String& str) {
				return std::regex_match(str, std::regex(Require));
			}
			inline bool isValidRequire(const String& str) {
				std::regex regex(ValidDeclaration);
				
				const bool match = std::regex_match(str, regex);
				
				if (!match) return false;
				else	    return match && regex.mark_count() == str.size();
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

			inline bool containsEqualOperator(const String& str) {
				return str.find(Equal) != str.npos;
			}
			inline bool containsNotEqualOperator(const String& str) {
				return str.find(NotEqual) != str.npos;
			}
			inline bool containsSmallerOperator(const String& str) {
				return str.find(Smaller) != str.npos;
			}
			inline bool containsSmallerOrEqualOperator(const String& str) {
				return str.find(SmallerOrEqual) != str.npos;
			}
			inline bool containsGreaterOperator(const String& str) {
				return str.find(Greater) != str.npos;
			}
			inline bool containsGreaterOrEqualOperator(const String& str) {
				return str.find(GreaterOrEqual) != str.npos;
			}
			inline bool containsConditionalOperators(const String& str) {
				return containsEqualOperator(str) || containsNotEqualOperator(str) ||
					   containsSmallerOperator(str) || containsSmallerOrEqualOperator(str) ||
					   containsGreaterOperator(str) || containsGreaterOrEqualOperator(str);
			}

			inline bool containsLogicalOr(const String& str) {
				return str.find(Or) != str.npos;
			}
			inline bool containsLogicalAnd(const String& str) {
				return str.find(And) != str.npos;
			}
			inline bool containsLogicalOperators(const String& str) {
				return containsLogicalOr(str) || containsLogicalAnd(str);
			}

			inline bool isConstValue(const String& str) {
				return std::regex_match(str, std::regex(ConstValue));
			}
			inline bool isConstBoolExpression(const String& str) {
				return !containsConditionalOperators(str);
			}

			inline bool isMessageStatement(const String& str) {
				return std::regex_match(str, std::regex(Message));
			}
		}

		inline ValueType resolveType(const String& str) {
			if		(lang::isStringDeclaration(str))	return ValueType::StringVal;
			else if (lang::isIntDeclaration(str))		return ValueType::IntVal;
			else if (lang::isDoubleDeclaration(str))	return ValueType::DoubleVal;
			else if (lang::isFloatDeclaration(str))		return ValueType::FloatVal;
			else										return ValueType::NoValue;
		}
		inline ConditionalOperators stringToConditionalOperator(const String& str) {
			if		(lang::containsEqualOperator(str))				return ConditionalOperators::Equal;
			else if (lang::containsNotEqualOperator(str))			return ConditionalOperators::NotEqual;
			else if (lang::containsSmallerOperator(str))			return ConditionalOperators::Smaller;
			else if (lang::containsSmallerOrEqualOperator(str))		return ConditionalOperators::SmallerOrEqual;
			else if (lang::containsGreaterOperator(str))			return ConditionalOperators::Greater;
			else if (lang::containsGreaterOrEqualOperator(str))		return ConditionalOperators::GreaterOrEqual;
			else													return ConditionalOperators::NoOperation;
		}
		inline LogicalOperators stringToLogicalOperator(const String& str) {
			if		(lang::containsLogicalOr(str))		return LogicalOperators::Or;
			else if (lang::containsLogicalAnd(str))		return LogicalOperators::And;
			else										return LogicalOperators::None;
		}
	}
}