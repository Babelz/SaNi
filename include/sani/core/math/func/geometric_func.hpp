#pragma once

namespace sani {

	namespace math {

		/// Returns a unit vector to same direction as v
		///
		/// @param v The vector
		template <typename T>
		Vector2<T> normalize(const Vector2<T>& v);

		/// Returns a unit vector to same direction as v
		///
		/// @param v The vector
		template <typename T>
		Vector3<T> normalize(const Vector3<T>& v);

		/// Returns a unit vector to same direction as v
		///
		/// @param v The vector
		template <typename T>
		Vector4<T> normalize(const Vector4<T>& v);

		/// Returns the length of v, sqrt(a * a)
		///
		/// @param a The vector
		template <typename T>
		T length(const Vector2<T>& a);

		/// Returns the length of v, sqrt(a * a)
		///
		/// @param a The vector
		template <typename T>
		T length(const Vector3<T>& a);

		/// Returns the length of v, sqrt(a * a)
		///
		/// @param a The vector
		template <typename T>
		T length(const Vector4<T>& a);

		/// Returns the squared length of v, a * a
		///
		/// @param a The vector
		template <typename T>
		T length2(const Vector2<T>& a);

		/// Returns the squared length of v, a * a
		///
		/// @param a The vector
		template <typename T>
		T length2(const Vector3<T>& a);

		/// Returns the squared length of v, a * a
		///
		/// @param a The vector
		template <typename T>
		T length2(const Vector4<T>& a);

		/// Returns the scalar product of two vectors
		///
		/// @param a The first vector
		/// @param b The second vector
		template <typename T>
		T dot(const Vector2<T>& a, const Vector2<T>& b);

		/// Returns the scalar product of two vectors
		///
		/// @param a The first vector
		/// @param b The second vector
		template <typename T>
		T dot(const Vector3<T>& a, const Vector3<T>& b);

		/// Returns the scalar product of two vectors
		///
		/// @param a The first vector
		/// @param b The second vector
		template <typename T>
		T dot(const Vector4<T>& a, const Vector4<T>& b);
		
		template <typename T>
		Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b);
	}
}

#include "geometric_func.inl"