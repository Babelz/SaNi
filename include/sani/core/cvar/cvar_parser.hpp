#pragma once

#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/precompiled.hpp"

namespace sani {

	namespace cvarlang {

		struct IntermediateCVar {
			ValueType type;

			String name;
			String value;
			
			IntermediateCVar() : type(ValueType::None) {
			}

			~IntermediateCVar() {
			}
		};

		struct IntermediateRequirement {
			String lhs;
			String rhs;

			bool lhsIsConst;
			bool rhsIsConst;

			LogicalOperators logicalOperator;
			ConditionalOperators conditionalOperator;

			IntermediateRequirement() : lhsIsConst(false),
										rhsIsConst(false),
										logicalOperator(LogicalOperators::None),
										conditionalOperator(ConditionalOperators::None) {
			}

			~IntermediateRequirement() {
			}
		};
	}

	class CVarParser {
	public:
		CVarParser();

		/// Parses intermediate cvar from given string.
		void parseCvar(const String& str, cvarlang::IntermediateCVar& intermediateCVar) const;
		/// Parses intermediate cvar requirement statement from given string.
		void parseRequirement(const String& str, cvarlang::IntermediateRequirement& intermediateRequirement) const;

		~CVarParser();
	};
}