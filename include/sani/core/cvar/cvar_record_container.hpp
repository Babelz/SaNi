#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include <list>

namespace sani {

	// TODO: implement.

	class CVarRecordContainer {
	private:
		std::list<CVarRecord> records;
	public:
		CVarRecordContainer(const std::list<CVarRecord>&& records);

		void sync();

		~CVarRecordContainer();

		CVarRecordContainer& operator =(CVarRecordContainer& other) = delete;
		CVarRecordContainer& operator = (CVarRecordContainer&& other) = delete;
		CVarRecordContainer(CVarRecordContainer& other) = delete;
	};
}