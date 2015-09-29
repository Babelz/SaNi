#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/cvar/cvar_lang.hpp"

namespace sani {

	CVarCompiler::CVarCompiler() : synced(false) {
	}

	void CVarCompiler::copyErrors(CVarParser* parser) {
		while (parser->hasErrors()) errorBuffer.push(parser->getNextError());
	}
	void CVarCompiler::copyErrors(CVarTokenizer* tokenizer) {
		while (tokenizer->hasErrors()) errorBuffer.push(tokenizer->getNextError());
	}

	bool CVarCompiler::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarCompiler::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarCompiler::generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens) {
		// 1) Process token
		// 2) Parse it
		// 3) Check for errors
		// 4) Emit cvar or statement
		// 5) generate record

		CVarParser parser;

		std::list<cvarlang::IntermediateCVar> intermediateCVar;
		std::list<cvarlang::IntermediateRequireStatement> intermediateRequireStatement;
		std::list<CVarRequireStatement> statements;
		// Current scope level. Gets decreased when require keyword is found,
		// and gets increased when require statement is found.
		size_t scope = 0;

		// Go trough each token.
		auto i = tokens.begin();

		while (i != tokens.end()) {
			// Only process declaration and require tokens.
			// Anything but these are just pure garbage.
			// We still keep these tokens for the parsing process.
			// Who knows if we need them some day (when the lexical analyzer evolves OSLT)
			// (and no need to clear the stack until the compilation process is complete)
			if (i->getType() == cvarlang::TokenType::Declaration) {
				cvarlang::IntermediateCVar intermediateCVar;

				parser.parseCvar(i->getLine(), intermediateCVar);

				if (parser.hasErrors()) copyErrors(&parser);

				// Emit cvar.
				generateCVar(cvars, statements, &intermediateCVar);

				if (synced) {
					// Emit record.
					generateRecord(records, *i, cvars.back());
				}
			}
			else if (i->getType() == cvarlang::TokenType::Require) {
				// So, the require token class has 2 variants, the one 
				// that starts a require statement (require([condition]) and 
				// the one that ends a block, that is just the plain require keyword in use.
				// We need to track that the user closes the scopes before the tokens end,
				// or we are fucked.

				cvarlang::IntermediateRequireStatement intermediateRequireStatement;
				String message;

				// Check if the next one is a message statement.
				auto next = std::next(i, 1);

				if (next != tokens.end()) {
					if ((next)->getType() == cvarlang::TokenType::Message) {
						message = (next)->getLine();

						parser.parseRequireStatement(i->getLine(), message, intermediateRequireStatement);

						i++;
					}
				} else {
					parser.parseRequireStatement(i->getLine(), message, intermediateRequireStatement);
				}
				
				if (intermediateRequireStatement.blockEnding) {
					if (scope > 0) {
						statements.remove(statements.back());
						scope--;
					}
				} else {
					generateRequireStatement(statements, cvars, &intermediateRequireStatement);
					scope++;
				}
			}

			// Do not emit warnings for invalid tokens, as the 
			// tokenizer has done this already.
			// (avoid duplicated error messages)

			i++;
		}

		// Emit possible scope errors and 
		// copy possible parsing errors to this level.
		if (scope > 0)			{
			auto last = tokens.begin();
			std::advance(last, tokens.size() - 1);

			errorBuffer.push(SANI_ERROR_MESSAGE("require scope was not closed at the end of require block at file " + last->getFilename()));
		}

		if (parser.hasErrors()) copyErrors(&parser);
	}

	void CVarCompiler::generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar) {
		cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, synced, intermediateCVar->value));
	}
	void CVarCompiler::generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const {
		records.push_back(CVarRecord(token, cvar));
	}

	void CVarCompiler::generateRequireStatement(std::list<CVarRequireStatement>& statements, std::list<CVar>& cvars, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement) {
		std::vector<CVarCondition> conditions;

		/*
			TODO: missing the boolean not (!) operator for bool expressions.
			They could come handy.
		*/

		for (const cvarlang::IntermediateCondition& intermediateCondition : intermediateRequireStatement->conditions) {
			if (intermediateCondition.lhs.size() > 0 || intermediateCondition.rhs.size() > 0) {
				Condition condition;

				if (intermediateCondition.lhs.size() > 0 && intermediateCondition.rhs.size() == 0) {
					// CVar const.
					generateConstCVarBoolExpression(&intermediateCondition, condition, cvars);
				} else if (intermediateCondition.lhs.size() > 0 && intermediateCondition.lhsIsConst && intermediateCondition.rhs.size() == 0) {
					// Const
					generateConstBoolConstExpression(&intermediateCondition, condition, cvars);		 
				} else if (intermediateCondition.lhsIsConst && intermediateCondition.rhsIsConst) {
					// Const oper const
					generateConstConstExpression(&intermediateCondition, condition);				
				} else if (intermediateCondition.rhsIsConst && !intermediateCondition.lhsIsConst) {
					// Const oper cvar
					generateConstCVarExpression(&intermediateCondition, condition, cvars);			 
				} else if (!intermediateCondition.rhsIsConst && intermediateCondition.lhsIsConst) {
					// CVar oper const
					generateCVarConstExpression(&intermediateCondition, condition, cvars);		     
				} else if (!intermediateCondition.rhsIsConst && !intermediateCondition.lhsIsConst) {
					// Cvar oper cvar
					generateCVarCVarExpression(&intermediateCondition, condition, cvars);
				}

				conditions.push_back(CVarCondition(intermediateCondition.logicalOperator, condition));
			}
		}

		statements.push_back(CVarRequireStatement(conditions, intermediateRequireStatement->message));
	}

	void CVarCompiler::generateConstConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition) {
		/*
			TODO: could store temps somewhere in case they are needed?
		*/

		CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);
		CVar rhs(intermediateCondition->rhsType, String("___TEMP_CVAR___"), false, intermediateCondition->rhs);

		condition = [&lhs, &rhs]() {
			return lhs == rhs;
		};
	}
	void CVarCompiler::generateConstCVarExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);
		CVar rhs(intermediateCondition->rhsType, String("___TEMP_CVAR___"), false, intermediateCondition->rhs);

		generateCondition(intermediateCondition, condition, lhs, rhs);
	}
	void CVarCompiler::generateCVarConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar* lhs = findCVar(cvars, intermediateCondition->lhs);
		if (lhs == nullptr) return;

		CVar rhs(intermediateCondition->rhsType, String("___TEMP_CVAR___"), false, intermediateCondition->rhs);

		generateCondition(intermediateCondition, condition, *lhs, rhs);
	}
	void CVarCompiler::generateConstCVarBoolExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);

		CVar* rhs = findCVar(cvars, intermediateCondition->rhs);
		if (rhs == nullptr) return;

		generateCondition(intermediateCondition, condition, lhs, *rhs);
	}
	void CVarCompiler::generateConstBoolConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		if (intermediateCondition->lhsIsConst) {
			CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);
			CVar rhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"));

			condition = [&lhs, &rhs]() {
				return lhs >= rhs;
			};
		}
	}
	void CVarCompiler::generateCVarCVarExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar* lhs = findCVar(cvars, intermediateCondition->lhs);
		if (lhs == nullptr) return;

		CVar* rhs = findCVar(cvars, intermediateCondition->rhs);
		if (rhs == nullptr) return;

		generateCondition(intermediateCondition, condition, *lhs, *rhs);
	}

	void CVarCompiler::generateCondition(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs) {
		if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::Equal) {
			condition = [&lhs, &rhs]() {
				return lhs == rhs;
			};
		} else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::NotEqual) {
			condition = [&lhs, &rhs]() {
				return lhs != rhs;
			};
		} else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::Smaller) {
			condition = [&lhs, &rhs]() {
				return lhs < rhs;
			};
		} else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::SmallerOrEqual) {
			condition = [&lhs, &rhs]() {
				return lhs <= rhs;
			};
		} else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::Greater) {
			condition = [&lhs, &rhs]() {
				return lhs > rhs;
			};
		} else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::GreaterOrEqual) {
			condition = [&lhs, &rhs]() {
				return lhs >= rhs;
			};
		}
	}

	CVar* CVarCompiler::findCVar(std::list<CVar>& cvars, const String& name) {
		for (CVar& cvar : cvars) {
			if (cvar.getName() == name) {
				return &cvar;
			}
		}

		errorBuffer.push(SANI_ERROR_MESSAGE("no cvar with name " + name + " was found at this time"));
		
		return nullptr;
	}

	void CVarCompiler::compile(std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records, const bool synced) {
		this->synced = synced;

		// Generate tokens from lines.
		CVarTokenizer tokenizer;

		std::list<CVarToken> tokens;
		tokenizer.tokenize(files, tokens);

		if (tokenizer.hasErrors()) {
			copyErrors(&tokenizer);

			/*
				Don't stop compiling even if some errors have been found. Just try to compile 
				so that we can find all the possible errors and show them all to the user
				at once.
			*/
		}

		// Try parse and emit.
		generateCVars(cvars, records, tokens);
	}

	CVarCompiler::~CVarCompiler() {
	}
}