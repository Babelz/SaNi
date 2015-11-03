#include "sani/core/cvar/link_record.hpp"

namespace sani {

	LinkRecord::LinkRecord() : root(nullptr) {
	}

	void LinkRecord::recordRoot(CVarFile* const root) {
		this->root = root;
	}
	void LinkRecord::recordLink(CVarFile* const link) {
		links.push_back(link);
	}

	CVarFile* const LinkRecord::getRoot() const {
		return root;
	}

	bool LinkRecord::hasLinks() const {
		return !links.empty();
	}
	CVarFile* const LinkRecord::getNextLink() {
		auto link = links.end();
		links.erase(link);

		return *link;
	}

	bool LinkRecord::isLinked(CVarFile* const link) const {
		return std::find(links.begin(), links.end(), link) != links.end();
	}

	LinkRecord::~LinkRecord() {
	}
}