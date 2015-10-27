#pragma once

#include "sani/core/cvar/cvar_file.hpp"
#include <vector>

namespace sani {

	class CVarFile;

	/// @class LinkRecord link_record.hpp "sani/core/cvar/link_record.hpp"
	/// @author voidbab
	///
	/// Class used to store information about the file
	/// linkages. Used to compile the files in correct order.
	class LinkRecord {
	private:
		std::vector<CVarFile*> links;
		CVarFile* root;
	public:
		LinkRecord();

		void recordRoot(CVarFile* root);
		void recordLink(CVarFile* link);

		CVarFile* getRoot() const;
		
		bool hasLinks() const;
		CVarFile* getNextLink();

		bool isLinked(CVarFile* link) const;

		~LinkRecord();
	};
}