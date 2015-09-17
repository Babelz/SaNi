#include "sani/core/cvar/link_record.hpp"

namespace sani {

	LinkRecord::LinkRecord(const String& filename) : filename(filename) {
	}

	bool LinkRecord::recursive(const LinkRecord& other) const {
		// This includes other and other includes this.
		return linked(other.filename) && other.linked(filename);
	}

	void LinkRecord::link(const String& filename) {
		links.push_back(filename);
	}
	bool LinkRecord::linked(const String& filename) const {
		return std::find(links.begin(), links.end(), filename) != links.end();
	}

	LinkRecord::~LinkRecord() {
	}
}