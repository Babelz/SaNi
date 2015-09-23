#include "sani/core/cvar/cvar_condition.hpp"

namespace sani {

	CVarCondition::CVarCondition(const cvarlang::LogicalOperators oper, const Condition condition) : oper(oper),
																							         condition(condition) {
	}

	cvarlang::LogicalOperators CVarCondition::getOperator() const {
		return oper;
	}

	CVarCondition::~CVarCondition() {
	}

	bool CVarCondition::operator()() const {
		return condition();
	}
}