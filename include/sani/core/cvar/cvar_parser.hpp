#pragma once

#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/core/cvar/cvar_token.hpp"
#include "sani/precompiled.hpp"
#include <stack>

namespace sani {

	typedef	std::stack<String> ErrorBuffer;

	namespace cvarlang {

		// Class containing intermediate cvar representation.
		struct IntermediateCVar {
			ValueType type;

			// Name of the var.
			String name;
			// Value string of the val.
			String value;
			
			IntermediateCVar() : type(cvarlang::ValueType::NoValue) {
			}

			~IntermediateCVar() {
			}
		};

		// Class that contains intermediate requirement expression representation
		struct IntermediateCondition{
			String lhs;
			String rhs;

			bool lhsIsConst;
			bool rhsIsConst;

			// Logical operator of the expression (|| &&)
			LogicalOperators logicalOperator;
			// Conditional statement of the expression (= != < <= > >=)
			ConditionalOperators conditionalOperator;

			IntermediateCondition() : lhsIsConst(false),
									  rhsIsConst(false),
									  logicalOperator(LogicalOperators::None),
									  conditionalOperator(ConditionalOperators::NoOperation) {
			}

			~IntermediateCondition() {
			}
		};

		// Class that contains intermediate require statement representation.
		struct IntermediateRequireStatement {
			std::vector<IntermediateCondition> conditions;
			String message;

			IntermediateRequireStatement() {
			}

			~IntermediateRequireStatement() {
			}
		};
	}

	class CVarParser {
	private:

		/*
			TODO: could move these error methods to some
				  common interface?
		*/

		ErrorBuffer errorBuffer;

		void pushError(const String& error);

		/// Finds position of next logical operator in given string.
		void findLogicalOperator(const String& str, size_t& pos) const;
		/// Finds position and length of next conditional operator in given string.
		void findConditionalOperator(const String& str, size_t& pos, size_t& len);

		/// Parses the next conditional expression from given string.
		/// Passes results to given intermediate condition.
		void parseConditionalExpression(String& exprStr, cvarlang::IntermediateCondition& intermediateCondition);
	public:
		CVarParser();

		bool hasErrors() const;
		String getNextError();

		/// Parses intermediate cvar from given string.
		void parseCvar(String str, cvarlang::IntermediateCVar& intermediateCVar);
		/// Parses intermediate cvar requirement statement from given string.
		void parseRequireStatement(String reqStr, const String& msgStr, cvarlang::IntermediateRequireStatement& intermediateRequirementStatement);

		~CVarParser();
	};
}