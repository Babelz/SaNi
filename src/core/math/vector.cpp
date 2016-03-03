#include "sani/core/math/vector2.hpp"
#include "sani/core/math/vector3.hpp"
#include "sani/core/math/vector4.hpp"
#include "sani/rtti/argument.hpp"

#define RTTI_DEFINE_VECTOR2(type, name)                   \
		template <>                                       \
		void Vector2<type>::RTTI_Init() {                 \
			RTTI_REGISTER_TYPE(sani::math::name);         \
			RTTI_DEFAULT_CTOR(sani::math::name);          \
			RTTI_CONSTRUCTOR_BODY(sani::math::name, type, type)\
				return sani::math::name(                  \
				   args[0].getValue<type>(),              \
                   args[1].getValue<type>()               \
				   );                                     \
			RTTI_CONSTRUCTOR_END;                         \
			RTTI_PUBLIC_FIELD(sani::math::name, x, type)  \
			RTTI_PUBLIC_FIELD(sani::math::name, y, type)  \
		}                    

#define RTTI_DEFINE_VECTOR3(type, name)                   \
		template <>                                       \
		void Vector3<type>::RTTI_Init() {                 \
			RTTI_REGISTER_TYPE(sani::math::name);         \
			RTTI_DEFAULT_CTOR(sani::math::name);          \
			RTTI_CONSTRUCTOR_BODY(sani::math::name, type, type, type)\
				return sani::math::name(                  \
				   args[0].getValue<type>(),              \
                   args[1].getValue<type>(),              \
				   args[2].getValue<type>()               \
				   );                                     \
			RTTI_CONSTRUCTOR_END;                         \
			RTTI_PUBLIC_FIELD(sani::math::name, x, type)  \
			RTTI_PUBLIC_FIELD(sani::math::name, y, type)  \
			RTTI_PUBLIC_FIELD(sani::math::name, z, type)  \
		}          

#define RTTI_DEFINE_VECTOR4(type, name)                   \
		template <>                                       \
		void Vector4<type>::RTTI_Init() {                 \
			RTTI_REGISTER_TYPE(sani::math::name);         \
			RTTI_DEFAULT_CTOR(sani::math::name);          \
			RTTI_CONSTRUCTOR_BODY(sani::math::name, type, type, type, type)\
				return sani::math::name(                  \
				   args[0].getValue<type>(),              \
                   args[1].getValue<type>(),              \
				   args[2].getValue<type>(),              \
				   args[3].getValue<type>()               \
				   );                                     \
			RTTI_CONSTRUCTOR_END;                         \
			RTTI_PUBLIC_FIELD(sani::math::name, x, type)  \
			RTTI_PUBLIC_FIELD(sani::math::name, y, type)  \
			RTTI_PUBLIC_FIELD(sani::math::name, z, type)  \
			RTTI_PUBLIC_FIELD(sani::math::name, w, type)  \
		}          

namespace sani {
	namespace math {
		namespace {
			auto& db = sani::rtti::TypeDatabase::getInstance();
		}

		RTTI_DEFINE_VECTOR2(float, Vec2f);
		RTTI_DEFINE_VECTOR2(double, Vec2d);
		RTTI_DEFINE_VECTOR2(int, Vec2i);
		RTTI_DEFINE_VECTOR2(unsigned int, Vec2u);

		RTTI_DEFINE_VECTOR3(float, Vec3f);
		RTTI_DEFINE_VECTOR3(double, Vec3d);
		RTTI_DEFINE_VECTOR3(int, Vec3i);
		RTTI_DEFINE_VECTOR3(unsigned int, Vec3u);

		RTTI_DEFINE_VECTOR4(float, Vec4f);
		RTTI_DEFINE_VECTOR4(double, Vec4d);
		RTTI_DEFINE_VECTOR4(int, Vec4i);
		RTTI_DEFINE_VECTOR4(unsigned int, Vec4u);
	}
}

#undef RTTI_DEFINE_VECTOR2
#undef RTTI_DEFINE_VECTOR3
#undef RTTI_DEFINE_VECTOR4