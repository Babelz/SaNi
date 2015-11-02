#pragma once
#include "../matrix4.hpp"
#include "../vector3.hpp"

namespace sani {
	namespace math {
		/// Builds a 4x4 translation matrix created from vector of 3 components
		///
		/// @param mat Input matrix multiplied by this translation matrix.
		/// @param vec Coordinates of a translation vector.
		/// @tparam T Value type used to build the matrix. 
		template <typename T>
		Matrix4<T> translate(Matrix4<T> const& mat, Vector3<T> const& vec);

		/// Builds a rotation 4x4 matrix created from an axis vector and an angle. 
		/// 
		/// @param mat Input matrix multiplied by this rotation matrix.
		/// @param angle Rotation angle expressed in RADIANS.
		/// @param axis Rotation axis, MUST BE NORMALIZED
		/// @tparam T Value type used to build the matrix.
		template <typename T>
		Matrix4<T> rotate(Matrix4<T> const& mat, T angle, Vector3<T> const& axis);

		/// Builds a scale 4 * 4 matrix created from 3 scalars. 
		///
		/// @param mat Input matrix multiplied by this scale matrix.
		/// @param vec Ratio of scaling for each axis.
		/// @tparam T Value type used to build the matrix.
		template <typename T>
		Matrix4<T> scale(Matrix4<T> const& mat, Vector3<T> const& vec);

		template <typename T>
		Matrix4<T> ortho(const T left, const T right, const T bottom, const T top, const T zNear, const T zFar);
		
		template <typename T>
		Matrix4<T> perspective(const float fovy, const float ar, const float znear, const float zfar);

		template <typename T>
		Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up);
	}
}

#include "transform.inl"