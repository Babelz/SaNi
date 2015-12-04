#include "sani/engine/messaging/recipent_list.hpp"

namespace sani {

	namespace engine {

		RecipentList::RecipentList() {
		}

		void RecipentList::clear() {
			recipents.clear();
		}
		void RecipentList::addRecipent(const String& recipent) {
		}
		void RecipentList::removeRecipent(const String& recipent) {
		}

		void RecipentList::getRecipentAtIndex(const uint32 index, String& recipent) const {
			
		}
		uint32 RecipentList::getRecipentsCount() const {
			return 0;
		}

		RecipentList::~RecipentList() {
		}
	}
}