#pragma once
#include "../matrix4.hpp"
#include "../vector3.hpp"

namespace sani {
	namespace math {
		template <typename T>
		Matrix4<T> translate(Matrix4<T> const& mat, Vector3<T> const& vec);
	}
}

#include "transform.inl"