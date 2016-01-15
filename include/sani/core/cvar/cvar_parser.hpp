#pragma once

#include "sani/core/interfaces/error_logger.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/core/cvar/cvar_token.hpp"
#include "sani/types.hpp"
#include <stack>

namespace sani {

	typedef	std::stack<String> ErrorBuffer;

	namespace cvarlang {

		// Class containing intermediate cvar representation.
		struct IntermediateCVar {
			cvarlang::ValueType type;

			// Name of the var.
			String name;
			// Value string of the val.
			String value;
			bool isVolatile;
			
			IntermediateCVar() : type(cvarlang::ValueType::NoValue),
							   	 isVolatile(false) {
			}

			~IntermediateCVar() {
			}
		};

		// Class that contains intermediate requirement expression representation
		struct IntermediateCondition {
			String lhs;
			String rhs;

			bool lhsIsConst;
			bool rhsIsConst;

			// Logical operator of the expression (|| &&)
			cvarlang::LogicalOperators logicalOperator;
			// Conditional statement of the expression (= != < <= > >=)
			cvarlang::ConditionalOperators conditionalOperator;

			cvarlang::ValueType lhsType;
			cvarlang::ValueType rhsType;

			IntermediateCondition() : lhsIsConst(false),
									  rhsIsConst(false),
									  logicalOperator(LogicalOperators::None),
									  conditionalOperator(ConditionalOperators::NoOperation),
									  lhsType(cvarlang::ValueType::NoValue),
									  rhsType(cvarlang::ValueType::NoValue) {
			}

			~IntermediateCondition() {
			}
		};

		// Class that contains intermediate require statement representation.
		struct IntermediateRequireStatement {
			std::vector<IntermediateCondition> conditions;
			bool blockEnding;
			String message;

			IntermediateRequireStatement() : blockEnding(false) {
			}

			~IntermediateRequireStatement() {
			}
		};
	}

	/// @class CVarParser cvar_parser.hpp "sani/core/cvar/cvar_parser.hpp"
	/// @author voidbab
	///
	/// Class that is responsible of transforming raw cvar file lines
	/// to intermediate representation of the language. These
	/// intermediate tokens then will be consumed by a emitter
	/// that can generate cvars from them.
	class CVarParser : public interfaces::ErrorLogger {
	private:
		/// Finds position of next logical operator in given string.
		void findLogicalOperator(const String& str, size_t& pos) const;
		/// Finds position and length of next conditional operator in given string.
		void findConditionalOperator(const String& str, size_t& pos, size_t& len);

		/// Parses the next conditional expression from given string.
		/// Passes results to given intermediate condition.
		void parseConditionalExpression(String& exprStr, cvarlang::IntermediateCondition& intermediateCondition);
	public:
		CVarParser();

		/// Parses intermediate cvar from given string.
		void parseCvar(String str, cvarlang::IntermediateCVar& intermediateCVar);
		/// Parses intermediate cvar requirement statement from given string.
		void parseRequireStatement(String reqStr, String msgStr, cvarlang::IntermediateRequireStatement& intermediateRequirementStatement);

		~CVarParser();
	};
}