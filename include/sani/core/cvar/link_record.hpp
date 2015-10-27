#pragma once

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

		void setRoot(CVarFile* root);
		void recordLink(CVarFile* link);

		const CVarFile* getRoot() const;
		
		uint32 linksCount() const;
		CVarFile* fileAtIndex(const uint32 index);

		~LinkRecord();
	};
}