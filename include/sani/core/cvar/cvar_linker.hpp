#pragma once

#include "sani/core/interfaces/error_logger.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/types.hpp"
#include <stack>
#include <list>

namespace sani {
	
	class LinkRecord;

	using namespace interfaces;

	/// @class CVarLinker cvar_linker.hpp "sani/core/cvar/cvar_linker.hpp"
	/// @author voidbab
	/// 
	/// Class responsible of linking files with
	/// given root file.
	class CVarLinker final : public ErrorLogger {
	private:
		LinkRecord* rootRecord;
		uint32 scope;

		CVarFile* const findFile(const String& filename, std::list<CVarFile>& files);
		void linkFiles(CVarFile* const file, std::list<CVarFile>& files);

		void copyContents(CVarFile* const file, const uint32 lineIndex, const String& line, std::list<CVarFile>& files);
		void linkFile(CVarFile* const file, String& line, std::list<CVarFile>& files);

		void updateScope(const String& line);	
	public:
		CVarLinker();

		void link(const String& filename, std::list<CVarFile>& files, LinkRecord* const record);

		~CVarLinker();
	};
}