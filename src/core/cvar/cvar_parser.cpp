#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/utils/string_utils.hpp"
#include "sani/debug.hpp"
#include <list>

namespace sani {

	CVarParser::CVarParser() : ErrorLogger() {
	}

	void CVarParser::findLogicalOperator(const String& str, size_t& pos) const {
		if (cvarlang::lang::containsLogicalAnd(str))	pos = str.find(cvarlang::lang::And);
		if (cvarlang::lang::containsLogicalOr(str))		pos = str.find(cvarlang::lang::Or);
	}

	void CVarParser::findConditionalOperator(const String& str, size_t& pos, size_t& len) {
		if (cvarlang::lang::containsEqualOperator(str)) {
			pos = str.find(cvarlang::lang::Equal);
			len = cvarlang::lang::Equal.size();
		} else if (cvarlang::lang::containsNotEqualOperator(str)) {
			pos = str.find(cvarlang::lang::NotEqual);
			len = cvarlang::lang::NotEqual.size();
		} else if (cvarlang::lang::containsSmallerOrEqualOperator(str)) {
			pos = str.find(cvarlang::lang::SmallerOrEqual);
			len = cvarlang::lang::SmallerOrEqual.size();
		} else if (cvarlang::lang::containsSmallerOperator(str)) {
			pos = str.find(cvarlang::lang::Smaller);
			len = cvarlang::lang::Smaller.size();
		} else if (cvarlang::lang::containsGreaterOrEqualOperator(str)) {
			pos = str.find(cvarlang::lang::GreaterOrEqual);
			len = cvarlang::lang::GreaterOrEqual.size();
		} else if (cvarlang::lang::containsGreaterOperator(str)) {
			pos = str.find(cvarlang::lang::Greater);
			len = cvarlang::lang::Greater.size();
		}

		// Check for errors.
		if (len == 0) ErrorLogger::pushError(SANI_ERROR_MESSAGE("invalid or unsupported operator, skipping compilation, line is \"" + str + "\""));
	}

	void CVarParser::parseConditionalExpression(String& exprStr, cvarlang::IntermediateCondition& intermediateCondition) {
		// Trim the input just to be sure it does not contain any whitespace.
		utils::trim(exprStr);
		// To show in case of errors.
		String origExpr = exprStr;

		if (cvarlang::lang::containsConditionalOperators(exprStr)) {
			// Split by operators.

			size_t conPos = 0;		// Conditional operators position.
			size_t logPos = 0;		// Logical operators position.
			size_t len = 0;			// Lenght of the conditional operator.

			// Find conditional.
			findConditionalOperator(exprStr, conPos, len);

			// Check for logical.
			if (cvarlang::lang::containsLogicalOperators(exprStr)) findLogicalOperator(exprStr, logPos);

			// Get lhs, oper and rhs (example a == b where lhs = a, oper = == and rhs == b)
			String lhs = exprStr.substr(0, conPos);
			String oper = exprStr.substr(conPos, len);
			String rhs = exprStr.substr(conPos + len, logPos - conPos - len);

			// Trim values.
			utils::trim(lhs);
			utils::trim(oper);
			utils::trim(rhs);

			// Fill intermediate representation.
			intermediateCondition.lhs = lhs;
			intermediateCondition.rhs = rhs;
			intermediateCondition.conditionalOperator = cvarlang::stringToConditionalOperator(oper);
			intermediateCondition.lhsIsConst = cvarlang::lang::isConstValue(lhs);
			intermediateCondition.rhsIsConst = cvarlang::lang::isConstValue(rhs);

			// Remove these tokens from the input.
			const size_t subLen = logPos == 0 ? exprStr.size() : logPos;

			exprStr = exprStr.substr(subLen);
		} else {
			// Should be an constant bool expression as there are no operators.
			String lhs;
			
			if (cvarlang::lang::containsLogicalOperators(exprStr)) {
				size_t pos = 0;

				findLogicalOperator(exprStr, pos);

				lhs = exprStr.substr(0, pos);

				exprStr = exprStr.substr(pos);
			} else {
				lhs = exprStr;
			}

			utils::trim(lhs);

			// Fill.
			intermediateCondition.lhs = lhs;
			intermediateCondition.lhsIsConst = cvarlang::lang::isConstValue(lhs);

			// Resolve types.
			intermediateCondition.rhsType = cvarlang::resolveType(intermediateCondition.rhs);
			intermediateCondition.lhsType = cvarlang::resolveType(lhs);

			exprStr = exprStr.substr(lhs.size());

			// Check for type mismatch.
			if (intermediateCondition.rhsType != intermediateCondition.lhsType) {
				ErrorLogger::pushError(SANI_ERROR_MESSAGE("type mismatch between variables in a require statement, expression: " + origExpr));
			}
		}

		// Find the possible logical operator.
		if (cvarlang::lang::containsLogicalOperators(exprStr)) {
			size_t pos = 0;

			findLogicalOperator(exprStr, pos);

			// Const of 2 since all logical have the same lenght of 
			// 2 characters.
			String oper = exprStr.substr(pos, 2);

			intermediateCondition.logicalOperator = cvarlang::stringToLogicalOperator(oper);

			exprStr = exprStr.substr(2);
		}
	}

	void CVarParser::parseCvar(String str, cvarlang::IntermediateCVar& intermediateCVar) {
		// Split into tokens. Should be splitted by whitespace.
		std::vector<String> tokens;

		// Remove tabs.
		while (cvarlang::lang::containsTabs(str)) {
			const size_t pos = str.find(cvarlang::lang::Tab);

			str.erase(pos, 1);
		}

		// Remove any comments, we don't need them here.
		if (cvarlang::lang::containsComment(str)) {
			const size_t len = str.find(cvarlang::lang::Comment);

			str = str.substr(0, len);
		}

		const size_t sepPos = str.find(String("\""));

		// String statement parsing.
		if (sepPos != str.npos) {
			// Check for invalid string declaration.
			if (str[str.size() - 1] != '"') {
				ErrorLogger::pushError(SANI_ERROR_MESSAGE("invalid string declaration, line is " + str));

				return;
			}

			tokens.push_back(str.substr(0, sepPos));
			tokens.push_back(str.substr(sepPos + 1, str.size() - sepPos - 2));
		} else {
			// Split by whitespaces.
			utils::split(str, String(" "), tokens, true);
		}

		utils::trim(str);

		bool isVolatile = false;

		// Volatile, too many or too few tokens.
		if (tokens.size() != 2) {
			// Too few tokens.
			if (tokens.size() < 2) {
				ErrorLogger::pushError(SANI_ERROR_MESSAGE("too few tokens, skipping compilation, line is \"" + str + "\""));

				return;
			} else if (tokens.size() > 2) {
				// Too many tokens.
				if (*tokens.begin() != cvarlang::lang::VolatileKeyword) {
					ErrorLogger::pushError(SANI_ERROR_MESSAGE("too many tokens, skipping compilation, line is \"" + str + "\""));

					return;
				} 

				// Volatile decl.
				tokens.erase(tokens.begin());
				isVolatile = true;
			}
		}

		cvarlang::ValueType type = cvarlang::ValueType::NoValue;
		String name = tokens[0];
		String value = tokens[1];
		
		// Resolve the type of the variable.
		if		(cvarlang::lang::isStringDeclaration(str))		type = cvarlang::ValueType::StringVal;
		else if (cvarlang::lang::isIntDeclaration(str))			type = cvarlang::ValueType::IntVal;
		else if (cvarlang::lang::isFloatDeclaration(str))		type = cvarlang::ValueType::FloatVal;
		else if (cvarlang::lang::isDoubleDeclaration(str))		type = cvarlang::ValueType::DoubleVal;

		// Check for invalid value string.
		if (type == cvarlang::ValueType::NoValue) {
			ErrorLogger::pushError(SANI_ERROR_MESSAGE("unsupported or invalid value declaration, line is \"" + str + "\""));

			return;
		}

		// Trim values.
		utils::trim(name);
		utils::trim(value);

		// Fill the intermediate representation.
		intermediateCVar.name = name;
		intermediateCVar.type = type;
		intermediateCVar.value = value;
		intermediateCVar.isVolatile = isVolatile;
	}
	void CVarParser::parseRequireStatement(String reqStr, String msgStr, cvarlang::IntermediateRequireStatement& intermediateRequirementStatement) {
		// Remove tabs.
		while (cvarlang::lang::containsTabs(reqStr)) {
			const size_t pos = reqStr.find(cvarlang::lang::Tab);

			reqStr.erase(pos);
		}

		// Remove comments from the requirement.
		if (cvarlang::lang::containsComment(reqStr)) {
			const size_t len = reqStr.find(cvarlang::lang::Comment);

			reqStr = reqStr.substr(0, len);
		}

		// Trim and do pre-checks to check if this is
		// the ending of a certain require block.
		utils::trim(reqStr);
		utils::trim(msgStr);

		if (reqStr.size() == cvarlang::lang::RequireKeyword.size()) {
			// Yup, an ending.
			intermediateRequirementStatement.blockEnding = true;

			return;
		}

		// Remove keywords from the reqstr.
		reqStr = reqStr.substr(reqStr.find("(") + 1);
		reqStr = reqStr.substr(0, reqStr.find_last_of(")"));

		// Parse message.
		if (msgStr.size() != 0 && cvarlang::lang::isMessageStatement(msgStr)) {
			msgStr = msgStr.substr(msgStr.find("(") + 1);
			msgStr = msgStr.substr(0, msgStr.find_last_of(")"));

			intermediateRequirementStatement.message = msgStr;
		}

		while (reqStr.size() > 0) {
			intermediateRequirementStatement.conditions.push_back(cvarlang::IntermediateCondition());

			parseConditionalExpression(reqStr, intermediateRequirementStatement.conditions.back());
		}
 	}

	CVarParser::~CVarParser() {
	}
}