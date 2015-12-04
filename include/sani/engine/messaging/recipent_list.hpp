#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		/// @class RecipentList recipent_list.hpp "sani/engine/messaging/recipent_list.hpp"
		/// @author voidbab
		///
		/// Represents a list of recipents.
		class RecipentList {
		private:
			String recipents;

			uint32 count;
		public:
			RecipentList();

			void setRecipents(const String& recipents);

			void getRecipentAtIndex(const uint32 index, String& recipent) const;
			uint32 getRecipentsCount() const;

			~RecipentList();
		};
	}
}