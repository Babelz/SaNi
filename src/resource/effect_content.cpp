#include "sani/resource/effect_content.hpp"
namespace sani {
	namespace resource {

		void EffectContent::setFragmentCode(const String& code) {
			fragmentCode = code;
		}

		void EffectContent::setVertexCode(const String& code) {
			vertexCode = code;
		}
		
		const String& EffectContent::getFragmentCode() const {
			return fragmentCode;
		}
		const String& EffectContent::getVertexCode() const {
			return vertexCode;
		}

		void EffectContent::setEffectCode(const String& code) {
			effectCode = code;
		}

		const String& EffectContent::getEffectCode() const {
			return effectCode;
		}

		bool EffectContent::isCompiled() const {
			return !effectCode.empty();
		}
		
	}
}