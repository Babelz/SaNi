#pragma once

/*
	Contains the regular language of the cvar system.
*/

#include "sani/types.hpp"
#include <functional>
#include <regex>
#include <list>

namespace sani {

	namespace cvarlang {

		// Some type aliases used with some lookup functions.
		using StringPredicate = std::function<bool(const String&)>;

		template <typename T>
		using Token = std::pair<StringPredicate, T>;

		template <typename T>
		using TokenMap = std::list<Token<T>>;

		enum class ConditionalOperators {
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

		enum class ValueType {
			NoValue,

			StringVal,

			// 32-bit integer.
			IntVal,

			// 32-bit floating point number.
			FloatVal,

			// 64-bit floating point number.
			DoubleVal
		};

		enum class LogicalOperators {
			// No operation.
			None,

			// &&
			And,

			// ||
			Or
		};

		enum class TokenType {
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

			const String RequireKeyword = "require";
			const String MessageKeyword = "message";
			const String IncludeKeyword = "include";
			const String VolatileKeyword = "volatile";

			const String Comment = "//";

			const String StringType = "\".+\"";
			const String IntType = "[0-9]+";
			const String DoubleType = "[0-9]+\\.[0-9]+";
			const String FloatType = DoubleType + "f";

			const String ConstValue = "(" + StringType + "|" + IntType + "|" + DoubleType +
				"|" + FloatType + ")";

			const String Message = MessageKeyword + " *(.+)";

			const String Declaration = "[_\\w]+ ";
			const String StringDeclaration = Declaration + StringType;
			const String IntDeclaration = Declaration + IntType;
			const String DoubleDeclaration = Declaration + DoubleType;
			const String FloatDeclaration = DoubleDeclaration + "f";

			const String ValidDeclaration = Declaration + ConstValue;

			// Probably the worst regex EU but w/e. Can't string 
			// like a MLG and bet never will.

			// Does not work with multiple logical operators at this time. Should it?
			const String ValidRequirement = "require\\s*\\(\\s*[\\w\\d]+\\s*(?:(?=<=|>=|==|\\|\\||&&|< |> )(?:.{2}\\s*[\\w\\d]+\\s*\\))|(?:(?=<|>).\\s*[\\w\\d]+\\s*)\\)|\\))";

			/*
				Conditional operators.
			*/

			const String Equal = "==";
			const String NotEqual = "!=";

			const String Smaller = "<";
			const String SmallerOrEqual = "<=";

			const String Greater = ">";
			const String GreaterOrEqual = ">=";

			/*
				Logical operators.
			*/

			const String And = "&&";
			const String Or = "\\|\\|";

			/*
				Misc.
			*/

			const String Tab = "\t";

			/*
				Regular expressions.
			*/

			const static std::regex RequireRegex = std::regex(RequireKeyword + " *");
			const static std::regex DeclarationRegex = std::regex(Declaration);
			const static std::regex ValidDeclarationRegex = std::regex(ValidDeclaration);
			const static std::regex StringDeclarationRegex = std::regex(StringDeclaration);
			const static std::regex IntDeclarationRegex = std::regex(IntDeclaration);
			const static std::regex DoubleDeclarationRegex = std::regex(DoubleDeclaration);
			const static std::regex FloatDeclarationRegex = std::regex(FloatDeclaration);
			const static std::regex ConstValueRegex = std::regex(ConstValue);
			const static std::regex MessageRegex = std::regex(Message);
			const static std::regex ValidRequirementRegex = std::regex(ValidRequirement);

			/*
				Helpers.
			*/

			inline bool isEmptyOrWhitespace(const String& str);

			inline bool startsWithComment(const String& str);
			inline bool containsComment(const String& str);
			inline bool containsTabs(const String& str);

			inline bool startsWithRequire(const String& str);
			inline bool isValidRequire(const String& str);

			inline bool isDeclaration(const String& str);
			inline bool isValidDeclaration(const String& str);

			inline bool isStringDeclaration(const String& str);
			inline bool isIntDeclaration(const String& str);
			inline bool isDoubleDeclaration(const String& str);
			inline bool isFloatDeclaration(const String& str);

			inline bool containsEqualOperator(const String& str);
			inline bool containsNotEqualOperator(const String& str);
			inline bool containsSmallerOperator(const String& str);
			inline bool containsSmallerOrEqualOperator(const String& str);
			inline bool containsGreaterOperator(const String& str);
			inline bool containsGreaterOrEqualOperator(const String& str);
			inline bool containsConditionalOperators(const String& str);

			inline bool containsLogicalOr(const String& str);
			inline bool containsLogicalAnd(const String& str);
			inline bool containsLogicalOperators(const String& str);

			inline bool isConstValue(const String& str);
			inline bool isConstBoolExpression(const String& str);

			inline bool isMessageStatement(const String& str);

			inline bool startsWithInclude(const String& str);

			inline bool isVolatileDeclaration(const String& str);

			/// Used as the default fall back.
			inline static bool invalidDeclaration(const String& str);
		}

		template <typename T>
		inline static T lookup(const TokenMap<T>& map, const String& str);

		inline ValueType resolveType(const String& str);
		inline ConditionalOperators stringToConditionalOperator(const String& str);
		inline LogicalOperators stringToLogicalOperator(const String& str);
	}
}

#include "sani/core/cvar/impl/cvar_lang.inl"