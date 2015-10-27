#include "sani/core/cvar/link_record.hpp"

namespace sani {

	LinkRecord::LinkRecord() : root(nullptr) {
	}

	void LinkRecord::recordRoot(CVarFile* root) {
		this->root = root;
	}
	void LinkRecord::recordLink(CVarFile* link) {
		links.push(link);
	}

	const CVarFile* LinkRecord::getRoot() const {
		return nullptr;
	}

	bool LinkRecord::hasLinks() const {
		return !links.empty();
	}
	CVarFile* LinkRecord::getNextLink(){
		CVarFile* link = links.top();
		links.pop();

		return link;
	}

	LinkRecord::~LinkRecord() {
	}
}