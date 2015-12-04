#pragma once

#include "sani/types.hpp"

#include <vector>

namespace sani {

	namespace engine {

		/// @class RecipentList recipent_list.hpp "sani/engine/messaging/recipent_list.hpp"
		/// @author voidbab
		///
		/// Represents a list of recipents.
		class RecipentList {
		private:
			std::vector<String> recipents;

			uint32 count;
		public:
			RecipentList();

			void clear();
			void addRecipent(const String& recipent);
			void removeRecipent(const String& recipent);

			void getRecipentAtIndex(const uint32 index, String& recipent) const;
			uint32 getRecipentsCount() const;

			~RecipentList();
		};
	}
}