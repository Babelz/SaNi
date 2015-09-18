#pragma once 

#include "sani/precompiled.hpp"
#include <functional>

namespace sani {

	typedef std::function<bool(void)> Condition;

	namespace cvarlang {

		enum Operator {
			// No operation.
			None,

			// &&
			And,
			
			// ||
			Or
		};
	}

	/// @class CVarCondition cvar_condition.hpp "sani/core/cvar/cvar_condition.hpp"
	/// @author voidbab
	///
	/// Represents a condition that must be met before the 
	/// CVar can be changed.
	class CVarCondition {
	private:
		const Condition condition;
		const cvarlang::Operator oper;
	public:
		CVarCondition(const cvarlang::Operator oper, const Condition condition);

		/// Returns the operator.
		cvarlang::Operator getOperator() const;

		~CVarCondition();

		/// Returns whether the condition was met.
		bool operator()() const;
	};
}