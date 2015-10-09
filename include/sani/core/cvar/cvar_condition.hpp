#pragma once 

#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/types.hpp"
#include <functional>

namespace sani {

	typedef std::function<bool(void)> Condition;

	/// @class CVarCondition cvar_condition.hpp "sani/core/cvar/cvar_condition.hpp"
	/// @author voidbab
	///
	/// Represents a condition that must be met before the 
	/// CVar can be changed.
	class CVarCondition {
	private:
		const Condition condition;
		const cvarlang::LogicalOperators oper;
	public:
		CVarCondition(const cvarlang::LogicalOperators oper, const Condition condition);

		/// Returns the operator.
		cvarlang::LogicalOperators getOperator() const;

		~CVarCondition();

		/// Returns whether the condition was met.
		bool operator()() const;

		bool operator == (const CVarCondition& other) const;
		bool operator != (const CVarCondition& other) const;
	};
}