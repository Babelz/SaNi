#pragma once

#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/precompiled.hpp"

namespace sani {

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
		struct IntermediateRequirement {
			String lhs;
			String rhs;

			bool lhsIsConst;
			bool rhsIsConst;

			// Logical operator of the expression (|| &&)
			LogicalOperators logicalOperator;
			// Conditional statement of the expression (= != < <= > >=)
			ConditionalOperators conditionalOperator;

			IntermediateRequirement() : lhsIsConst(false),
										rhsIsConst(false),
										logicalOperator(LogicalOperators::None),
										conditionalOperator(ConditionalOperators::NoOperation) {
			}

			~IntermediateRequirement() {
			}
		};

		// Class that contains intermediate require statement representation.
		struct IntermediateRequireStatement {
			std::vector<IntermediateRequirement> requirements;
			String message;

			IntermediateRequireStatement() {
			}

			IntermediateRequireStatement() {
			}
		};
	}

	class CVarParser {
	public:
		CVarParser();

		/// Parses intermediate cvar from given string.
		void parseCvar(String str, cvarlang::IntermediateCVar& intermediateCVar) const;
		/// Parses intermediate cvar requirement statement from given string.
		void parseRequireStatement(String reqStr, const String& msgStr, cvarlang::IntermediateRequireStatement& IntermediateRequireStatement) const;

		~CVarParser();
	};
}