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
		std::vector<CVarFile* const> links;
		CVarFile* root;
	public:
		LinkRecord();

		void recordRoot(CVarFile* const root);
		void recordLink(CVarFile* const link);

		CVarFile* const getRoot() const;
		
		bool hasLinks() const;
		CVarFile* const getNextLink();

		bool isLinked(CVarFile* const link) const;

		~LinkRecord();
	};
}