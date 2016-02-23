#pragma once

#include "sani/rtti/object_container.hpp"
#include "sani/types.hpp"

#define DECLARE_STD_VARIANT(type)\
	template <>                                                 \
	class ObjectContainer<type> : public ObjectBase {           \
	public:                                                     \
	     ObjectContainer(const type& value);                    \
		 ObjectContainer(const type&& value);                   \
		 Type getType() const override;                         \
         void* getPointer() const override;                     \
		 ObjectBase* clone() const override;                    \
    private:                                                    \
	     friend class Object;                                   \
		 type value;                                            \
		 ObjectContainer& operator=(const ObjectContainer&) = delete; \
    };

namespace sani {
	namespace rtti {
		template <>
		class ObjectContainer<void> : public ObjectBase{
			ObjectContainer();
			Type getType() const override;
			ObjectBase* clone() const override;
			void* getPointer() const override;
		private:
			friend class Object;
			ObjectContainer& operator=(const ObjectContainer&) = delete;
		};

		/*DECLARE_STD_VARIANT(int32);
		DECLARE_STD_VARIANT(bool);
		DECLARE_STD_VARIANT(float32);
		DECLARE_STD_VARIANT(float64);
		DECLARE_STD_VARIANT(String8);*/
	}
}

