#pragma once

#include "sani/rtti/object_base.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, rtti, Serializable);

namespace sani {
	namespace rtti {
		class PointerContainer : public ObjectBase {
		public:
			PointerContainer(Serializable* instance);
			virtual ObjectBase* clone() const override;
			Type getType() const override;
			virtual void* getPointer() const override;
		private:
			Serializable* instance;
		};
	}
}

