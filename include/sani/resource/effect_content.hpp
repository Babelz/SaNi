#pragma once

#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"
#include <string>

namespace sani {
	namespace resource {
		class EffectContent : public ResourceItem {
		private:
			String vertexCode;
			String fragmentCode;
			String effectCode;
		public:
			EffectContent() = default;
			~EffectContent() = default;
			void setVertexCode(const String& code);
			void setFragmentCode(const String& code);
			void setEffectCode(const String& code);
			const String& getFragmentCode(const String& code) const;
			const String& getVertexCode(const String& code) const;
			const String& getEffectCode() const;
			bool isCompiled() const;
		};
	}
}