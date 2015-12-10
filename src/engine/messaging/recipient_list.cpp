#include "sani/engine/messaging/recipient_list.hpp"
#include "sani/debug.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		RecipientList::RecipientList() {
		}

		void RecipientList::clear() {
			recipents.clear();
		}
		void RecipientList::addRecipent(const String& recipent) {
			recipents.push_back(recipent);
		}
		void RecipientList::removeRecipent(const String& recipent) {
			auto it = std::find_if(recipents.begin(), recipents.end(), [&recipent](const String& lhs) {
				return lhs == recipent;
			});

			if (it == recipents.end()) return;
			
			recipents.erase(it);
		}

		uint32 RecipientList::recipentsCount() const {
			return recipents.size();
		}

		std::vector<const String>::const_iterator RecipientList::begin() const {
			return recipents.begin();
		}
		std::vector<const String>::const_iterator RecipientList::end() const {
			return recipents.end();
		}

		RecipientList::~RecipientList() {
		}
	}
}