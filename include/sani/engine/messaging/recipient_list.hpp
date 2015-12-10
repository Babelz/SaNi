#pragma once

#include "sani/types.hpp"

#include <vector>

namespace sani {

	namespace engine {

		/// @class RecipientList recipient_list.hpp "sani/engine/messaging/recipient_list.hpp"
		/// @author voidbab
		///
		/// Represents a list of recipents.
		class RecipientList {
		private:
			std::vector<const String> recipents;

			uint32 count;
		public:
			RecipientList();

			void clear();
			void addRecipent(const String& recipent);
			void removeRecipent(const String& recipent);

			uint32 recipentsCount() const;

			std::vector<const String>::const_iterator begin() const;
			std::vector<const String>::const_iterator end() const;

			~RecipientList();
		};
	}
}