#pragma once

namespace sani {

	namespace engine {

		/// Defines that for how many services the
		/// message should be sent to.
		enum class RecipentsCount {
			/// Single recipent.
			Single,

			/// Multiple recipents.
			Multiple
		};
	}
}