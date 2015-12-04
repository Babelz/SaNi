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
			std::vector<const String> recipents;

			uint32 count;
		public:
			RecipentList();

			void clear();
			void addRecipent(const String& recipent);
			void removeRecipent(const String& recipent);

			std::vector<const String>::const_iterator begin() const;
			std::vector<const String>::const_iterator end() const;

			~RecipentList();
		};
	}
}