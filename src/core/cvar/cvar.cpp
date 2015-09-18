#include "sani/core/cvar/cvar.hpp"

namespace sani {

	CVar::CVar(const CVarRequireStatement& statement, const cvarlang::ValueType type, 
			   const String& name, const bool synced, void* data) : statement(statement),
																	type(type),
																    name(name),
																	synced(synced),
																	data(data) {
	}

	cvarlang::ValueType CVar::getType() const {
		return type;
	}
	const String& CVar::getName() const {
		return name;
	}

	bool CVar::canWrite() const {
		return statement();
	}
	bool CVar::isSynced() const {
		return synced;
	}

	void* CVar::read() const {
		return data;
	}
	void CVar::write(void* data) {
		this->data = data;
	}

	CVar::~CVar() {
	}
}