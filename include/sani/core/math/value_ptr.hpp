#pragma once
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix2.hpp"
#include "matrix3.hpp"
#include "matrix4.hpp"

namespace sani {
	namespace math {
		template <typename T>
		T const* value_ptr(Vector2<T> const& vec);

		template <typename T>
		T const* value_ptr(Vector3<T> const& vec);

		template <typename T>
		T const* value_ptr(Vector4<T> const& vec);

		template <typename T>
		T const* value_ptr(Matrix2<T> const& mat);

		template <typename T>
		T const* value_ptr(Matrix3<T> const& mat);

		template <typename T>
		T const* value_ptr(Matrix4<T> const& mat);
	}
}

#include "value_ptr.inl"