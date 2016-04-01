#include "sani/core/cvar/cvar.hpp"

namespace sani {

#define CVAR_WRITE(typeToCheck, fieldToWrite) if (type != typeToCheck) return; fieldToWrite = value; changed = true
#define CVAR_READ(typeToCheck, fieldToRead) if (type != typeToCheck) return; value = fieldToRead

	CVar::CVar(const cvarlang::ValueType type, const String& name, const bool synced, const String& value) : type(type),
																										     name(name),
																											 synced(synced),
																											 changed(false) {
		initialize(value);
	}

	CVar::CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			   const String& name, const bool synced, const String& value) : statements(statements),
																			 type(type),
																			 name(name),
																			 synced(synced),
																			 changed(false) {
		initialize(value);
	}

	CVar::CVar(const cvarlang::ValueType type, const String& name) : type(type),
																	 name(name),
																	 synced(false),
																	 changed(false) {
		// Do default initialization.
		String value = type != cvarlang::ValueType::StringVal ? String("0") : String("");

		initialize(value);
	}

	void CVar::initialize(const String& value) {
		if		(type == cvarlang::ValueType::StringVal)	stringVal	= value.substr(1, value.size() - 2);
		else if (type == cvarlang::ValueType::IntVal)		int32Val	= std::atoi(value.c_str());
		else if (type == cvarlang::ValueType::FloatVal)		float32Val	= static_cast<float32>(std::atof(value.c_str()));
		else if (type == cvarlang::ValueType::DoubleVal)	float64Val	= std::atof(value.c_str());

		SANI_INIT_EVENT(valueChanged, void(CVar* const));
	}

	cvarlang::ValueType CVar::getType() const {
		return type;
	}
	const String& CVar::getName() const {
		return name;
	}

	bool CVar::canWrite() const {
		if (statements.size() == 0) return true;

		for (const CVarRequireStatement& statement : statements) if (!statement()) return false;
 		
		return true;
	}
	
	bool CVar::hasChanged() const {
		return changed;
	}
	bool CVar::isSynced() const {
		return synced;
	}

	void CVar::read(String& value) const {
		CVAR_READ(cvarlang::ValueType::StringVal, stringVal);
	}
	void CVar::read(int32& value) const {
		CVAR_READ(cvarlang::ValueType::IntVal, int32Val);
	}
	void CVar::read(float32& value) const {
		CVAR_READ(cvarlang::ValueType::FloatVal, float32Val);
	}
	void CVar::read(float64& value) const {
		CVAR_READ(cvarlang::ValueType::DoubleVal, float64Val);
	}

	void CVar::write(const String& value) {
		CVAR_WRITE(cvarlang::ValueType::StringVal, stringVal);

		SANI_TRIGGER_EVENT(valueChanged, void(CVar* const), this);
	}
	void CVar::write(const int32 value) {
		CVAR_WRITE(cvarlang::ValueType::IntVal, int32Val);
		
		SANI_TRIGGER_EVENT(valueChanged, void(CVar* const), this);
	}
	void CVar::write(const float32 value) {
		CVAR_WRITE(cvarlang::ValueType::FloatVal, float32Val);
		
		SANI_TRIGGER_EVENT(valueChanged, void(CVar* const), this);
	}
	void CVar::write(const float64 value) {
		CVAR_WRITE(cvarlang::ValueType::DoubleVal, float64Val);

		SANI_TRIGGER_EVENT(valueChanged, void(CVar* const), this);
	}

	void CVar::getRequireStatementMessages(std::vector<String>& messages) {
		for (const CVarRequireStatement& statement : statements) if (!statement()) messages.push_back(statement.getMessage());
	}

	CVar::~CVar() {
	}

	bool CVar::operator == (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal == val;
		} else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val == val;
		} else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val == val;
		} else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val == val;
		}

		return false;
	}
	bool CVar::operator != (const CVar& other) const {
		return !(*this == other);
	}
	bool CVar::operator < (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal.size() < val.size();
		} else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val < val;
		} else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val < val;
		} else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val < val;
		}

		return false;
	}
	bool CVar::operator <= (const CVar& other) const {
		return *this < other || *this == other;
	}
	bool CVar::operator > (const CVar& other) const {
		return !(*this < other);
	}
	bool CVar::operator >= (const CVar& other) const {
		return !(*this < other) || *this == other;
	}
}