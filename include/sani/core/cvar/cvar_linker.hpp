#pragma once

#include "sani/core/cvar/cvar_file.hpp"
#include "sani/types.hpp"
#include <stack>
#include <list>

namespace sani {
	
	typedef std::stack<String> ErrorBuffer;

	class LinkRecord;

	/// @class CVarLinker cvar_linker.hpp "sani/core/cvar/cvar_linker.hpp"
	/// @author voidbab
	/// 
	/// Class responsible of linking files with
	/// given root file.
	class CVarLinker {
	private:
		ErrorBuffer errorBuffer;

		LinkRecord* rootRecord;
		uint32 scope;

		CVarFile* const findFile(const String& filename, std::list<CVarFile>& files);
		void linkFiles(CVarFile* const file, std::list<CVarFile>& files);

		void copyContents(CVarFile* const file, const uint32 lineIndex, const String& line, std::list<CVarFile>& files);
		void linkFile(CVarFile* const file, String& line, std::list<CVarFile>& files);

		void updateScope(const String& line);
		
		void pushError(const String& message);
	public:
		CVarLinker();

		bool hasErrors() const;
		String getNextError();

		void link(const String& filename, std::list<CVarFile>& files, LinkRecord* const record);

		~CVarLinker();
	};
}