#include "sani/core/cvar/link_record.hpp"

namespace sani {

	LinkRecord::LinkRecord() : root(nullptr) {
	}

	void LinkRecord::recordRoot(CVarFile* root) {
		this->root = root;
	}
	void LinkRecord::recordLink(CVarFile* link) {
		links.push_back(link);
	}

	CVarFile* LinkRecord::getRoot() const {
		return root;
	}

	bool LinkRecord::hasLinks() const {
		return !links.empty();
	}
	CVarFile* LinkRecord::getNextLink() {
		auto link = links.end();
		links.erase(link);

		return *link;
	}

	bool LinkRecord::isLinked(CVarFile* link) const {
		return std::find(links.begin(), links.end(), link) != links.end();
	}

	LinkRecord::~LinkRecord() {
	}
}