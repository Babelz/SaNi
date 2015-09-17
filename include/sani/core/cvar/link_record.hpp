#pragma once

#include "sani/precompiled.hpp"
#include <list>

namespace sani {

	/// @class LinkRecord link_record.hpp "sani/core/cvar/link_record.hpp"
	/// @author voidbab
	/// 
	/// Used to store linkage information.
	class LinkRecord {
	private:
		std::list<String> links;
		// Name of the file that is associated with.
		String filename;
	public:
		LinkRecord(const String& filename);
		
		/// Returns true if the includes between this and the other 
		/// record cause recursion.
		bool recursive(const LinkRecord& other) const;

		/// Sets given filename to be linked with this record.
		void link(const String& filename);
		/// Returns true of if the given filename is flagged as linked
		/// with this filename.
		bool linked(const String& filename) const;

		~LinkRecord();
	};
}