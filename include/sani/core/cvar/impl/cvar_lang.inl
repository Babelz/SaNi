#pragma once

#include "sani/core/cvar/cvar_lang.hpp"

namespace sani {

	namespace cvarlang {

		namespace lang {

			bool isEmptyOrWhitespace(const String& str) {
				return str.empty();
			}

			bool startsWithComment(const String& str) {
				if (str.size() >= 2) return str.substr(0, 2) == Comment;
				else			     return false;
			}
			bool containsComment(const String& str) {
				return str.find(Comment) != str.npos;
			}
			bool containsTabs(const String& str) {
				return str.find(Tab) != str.npos;
			}

			bool startsWithRequire(const String& str) {
				return str.find(RequireKeyword) == 0;
			}
			bool isValidRequire(const String& str) {
				return std::regex_search(str, ValidRequirementRegex);
			}

			bool isDeclaration(const String& str) {
				return std::regex_search(str, DeclarationRegex);
			}
			bool isValidDeclaration(const String& str) {
				return std::regex_search(str, ValidDeclarationRegex);
			}

			bool isStringDeclaration(const String& str) {
				return std::regex_search(str, StringDeclarationRegex);
			}
			bool isIntDeclaration(const String& str) {
				return std::regex_search(str, IntDeclarationRegex);
			}
			bool isDoubleDeclaration(const String& str) {
				return std::regex_search(str, DoubleDeclarationRegex);
			}
			bool isFloatDeclaration(const String& str) {
				return std::regex_search(str, FloatDeclarationRegex);
			}

			bool containsEqualOperator(const String& str) {
				return str.find(Equal) != str.npos;
			}
			bool containsNotEqualOperator(const String& str) {
				return str.find(NotEqual) != str.npos;
			}
			bool containsSmallerOperator(const String& str) {
				return str.find(Smaller) != str.npos;
			}
			bool containsSmallerOrEqualOperator(const String& str) {
				return str.find(SmallerOrEqual) != str.npos;
			}
			bool containsGreaterOperator(const String& str) {
				return str.find(Greater) != str.npos;
			}
			bool containsGreaterOrEqualOperator(const String& str) {
				return str.find(GreaterOrEqual) != str.npos;
			}
			bool containsConditionalOperators(const String& str) {
				return containsEqualOperator(str) || containsNotEqualOperator(str) ||
					containsSmallerOperator(str) || containsSmallerOrEqualOperator(str) ||
					containsGreaterOperator(str) || containsGreaterOrEqualOperator(str);
			}

			bool containsLogicalOr(const String& str) {
				return str.find(Or) != str.npos;
			}
			bool containsLogicalAnd(const String& str) {
				return str.find(And) != str.npos;
			}
			bool containsLogicalOperators(const String& str) {
				return containsLogicalOr(str) || containsLogicalAnd(str);
			}

			bool isConstValue(const String& str) {
				return std::regex_search(str, ConstValueRegex);
			}
			bool isConstBoolExpression(const String& str) {
				return !containsConditionalOperators(str);
			}

			bool isMessageStatement(const String& str) {
				return std::regex_search(str, MessageRegex);
			}

			bool startsWithInclude(const String& str) {
				return str.find(IncludeKeyword) != str.npos;
			}

			bool isVolatileDeclaration(const String& str) {
				return str.find(VolatileKeyword) == 0;
			}

			/// Used as the default fall back.
			static bool invalidDeclaration(const String& str) {
				return true;
			}
		}

		template <typename T>
		static T lookup(const TokenMap<T>& map, const String& str) {
			for (auto token : map) {
				// Should always return something.
				if (token.first(str)) return token.second;
			}

			// Just abort since the execution of this function
			// should never fall here.
			std::abort();
		}

		ValueType resolveType(const String& str) {
			static TokenMap<ValueType> valueTypeMap =
			{
				{ lang::isStringDeclaration, ValueType::StringVal },
				{ lang::isIntDeclaration, ValueType::IntVal },
				{ lang::isDoubleDeclaration, ValueType::DoubleVal },
				{ lang::isFloatDeclaration, ValueType::StringVal },
				{ lang::invalidDeclaration, ValueType::NoValue }
			};

			return lookup<ValueType>(valueTypeMap, str);
		}
		ConditionalOperators stringToConditionalOperator(const String& str) {
			static TokenMap<ConditionalOperators> conditionalOperatorsMap =
			{
				{ lang::containsEqualOperator, ConditionalOperators::Equal },
				{ lang::containsNotEqualOperator, ConditionalOperators::NotEqual },
				{ lang::containsNotEqualOperator, ConditionalOperators::Smaller },
				{ lang::containsSmallerOperator, ConditionalOperators::SmallerOrEqual },
				{ lang::containsSmallerOrEqualOperator, ConditionalOperators::Greater },
				{ lang::containsGreaterOperator, ConditionalOperators::GreaterOrEqual },
				{ lang::invalidDeclaration, ConditionalOperators::NoOperation }
			};

			return lookup<ConditionalOperators>(conditionalOperatorsMap, str);
		}
		LogicalOperators stringToLogicalOperator(const String& str) {
			static TokenMap<LogicalOperators> logicalOperatorsMap =
			{
				{ lang::containsLogicalOr, LogicalOperators::Or },
				{ lang::containsLogicalAnd, LogicalOperators::And },
				{ lang::invalidDeclaration, LogicalOperators::None }
			};

			return lookup<LogicalOperators>(logicalOperatorsMap, str);
		}
	}
}