#include "sani/core/cvar/cvar.hpp"

namespace sani {

	CVar::CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			   const String& name, const bool synced, const String& value) : statements(statements),
																			 type(type),
																			 name(name),
																		     synced(synced),
																			 changed(false),
																			 stringVal(value) {
	}

	CVar::CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			   const String& name, const bool synced, const int32 value) : statements(statements),
																		   type(type),
																		   name(name),
																		   synced(synced),
																		   changed(false),
																		   int32Val(value) {
	}

	CVar::CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			   const String& name, const bool synced, const float32 value) : statements(statements),
																			 type(type),
																			 name(name),
																			 synced(synced),
																			 changed(false),
																			 float32Val(value) {
	}

	CVar::CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			   const String& name, const bool synced, const float64 value) : statements(statements),
																			 type(type),
																			 name(name),
																			 synced(synced),
																			 changed(false),
																			 float64Val(value) {
	}

	cvarlang::ValueType CVar::getType() const {
		return type;
	}
	const String& CVar::getName() const {
		return name;
	}

	bool CVar::canWrite() const {
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
		if (type != cvarlang::ValueType::StringVal) return;

		value = stringVal;
	}
	void CVar::read(int32& value) const {
		if (type != cvarlang::ValueType::IntVal) return;

		value = int32Val;
	}
	void CVar::read(float32& value) const {
		if (type != cvarlang::ValueType::FloatVal) return;

		value = float32Val;
	}
	void CVar::read(float64& value) const {
		if (type != cvarlang::ValueType::DoubleVal) return;

		value = float64Val;
	}

	void CVar::write(const String& value) {
		if (type != cvarlang::ValueType::StringVal) return;

		stringVal = value;
		changed = true;
	}
	void CVar::write(int32 value) {
		if (type != cvarlang::ValueType::IntVal) return;

		int32Val = value; 
		changed = true;
	}
	void CVar::write(float32 value) {
		if (type != cvarlang::ValueType::FloatVal) return;

		float32Val = value; 
		changed = true;
	}
	void CVar::write(float64 value) {
		if (type != cvarlang::ValueType::DoubleVal) return;

		float64Val = value; 
		changed = true;
	}

	CVar::~CVar() {
	}

	const bool CVar::operator == (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val = String(""); other.read(val);

			return stringVal == val;
		}
		else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val == val;
		}
		else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val == val;
		}
		else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val == val;
		}

		return false;
	}
	const bool CVar::operator != (const CVar& other) const {
		return !(*this == other);
	}
}