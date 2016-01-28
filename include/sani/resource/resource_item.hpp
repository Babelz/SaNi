#pragma once

namespace sani {

	namespace resource {

		/// Interface for content processing
		class ResourceItem {
		public:
			ResourceItem() = default;
			virtual ~ResourceItem() = default;
		};
	}
}