#pragma once
#include "sani/rtti/object_base.hpp"

namespace sani {
	namespace rtti {

		/// Class that holds the actual data
		template <class T>
		class ObjectContainer : public ObjectBase {
		public:
			ObjectContainer(const T& value);
			ObjectContainer(const T&& value);
			virtual ObjectBase* clone() const override;

			ObjectContainer& operator=(const ObjectContainer&) = delete;
		private:
			T value;
		};
	}
}

#include "inl/object_container.inl"

