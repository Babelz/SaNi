#include "sani/engine/messaging/recipient_list.hpp"
#include "sani/debug.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		RecipientList::RecipientList() {
		}

		void RecipientList::clear() {
			recipients.clear();
		}
		void RecipientList::addRecipient(const String& recipent) {
			recipients.push_back(recipent);
		}
		void RecipientList::removeRecipient(const String& recipent) {
			auto it = std::find_if(recipients.begin(), recipients.end(), [&recipent](const String& lhs) {
				return lhs == recipent;
			});

			if (it == recipients.end()) return;
			
			recipients.erase(it);
		}

		uint32 RecipientList::recipentsCount() const {
			return recipients.size();
		}

		std::vector<const String>::const_iterator RecipientList::begin() const {
			return recipients.begin();
		}
		std::vector<const String>::const_iterator RecipientList::end() const {
			return recipients.end();
		}

		RecipientList::~RecipientList() {
		}
	}
}