#pragma once 

#include "sani/precompiled.hpp"
#include <functional>
#include <vector>

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

	/// @class CVarRequireStatement cvar_condition.hpp "sani/core/cvar/cvar_condition.hpp"
	/// @author voidbab
	///
	/// Represents a set of conditions.
	class CVarRequireStatement {
	private:
		std::vector<CVarCondition> statement;
		
		size_t capacity;
	public:
		CVarRequireStatement(const std::vector<CVarCondition>& statement);

		~CVarRequireStatement();

		/// Returns whether the condition was met.
		bool operator()();
	};

	#define CREATE_CONDITION(name, oper, a, b, body) CVarCondition name(cvarlang::Operator::##oper, Condition([a, b] () body))
}