#pragma once

#include "sani/types.hpp"
#include <vector>

namespace sani {

	/// @class CVarFile cvar_file.hpp "sani/core/cvar/cvar_file.hpp"
	/// @author voidbab
	///
	/// Class holding initial string representation of
	/// a CVar file.
	class CVarFile {
	private:
		const String filename;

		std::vector<String> lines;
	public:
		CVarFile(const String& filename, const String& contents);

		/// Returns the filename.
		const String& getFilename() const;
		/// Returns the count of lines.
		const uint32 getLinesCount() const;

		/// Returns given line at given index.
		const String& lineAtIndex(const size_t index) const;
		String& lineAtIndex(const size_t index);

		/// Removes line at given index from the "file".
		void removeLineAtIndex(const size_t index);

		~CVarFile();
	};
}