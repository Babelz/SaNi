#include "sani/core/cvar/cvar_condition.hpp"

namespace sani {

	CVarCondition::CVarCondition(const cvarlang::Operator oper, const Condition condition) : oper(oper),
																							 condition(condition) {
	}

	cvarlang::Operator CVarCondition::getOperator() const {
		return oper;
	}

	CVarCondition::~CVarCondition() {
	}

	bool CVarCondition::operator()() const {
		return condition();
	}
}