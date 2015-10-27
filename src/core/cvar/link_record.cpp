#include "sani/core/cvar/link_record.hpp"
#include "sani/core/cvar/cvar_file.hpp"

namespace sani {

	LinkRecord::LinkRecord() : root(nullptr) {
	}

	void LinkRecord::setRoot(CVarFile* root) {
		this->root = root;
	}
	void LinkRecord::recordLink(CVarFile* link) {
		links.push_back(link);
	}

	const CVarFile* LinkRecord::getRoot() const {
		return root;
	}

	uint32 LinkRecord::linksCount() const {
		return links.size();
	}
	CVarFile* LinkRecord::fileAtIndex(const uint32 index) {
		return links[index];
	}

	LinkRecord::~LinkRecord() {
	}
}