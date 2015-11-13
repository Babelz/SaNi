#pragma once

#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"
#include <string>

namespace sani {
	namespace resource {
		class EffectContent : public ResourceItem {
		private:
			String code;
		public:
			EffectContent() = default;
			~EffectContent() = default;
			void setEffectCode(const String& code);
			const String& getEffectCode(const String& code) const;
		};
	}
}