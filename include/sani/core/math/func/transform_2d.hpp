#pragma once
#include "../matrix3.hpp"
#include "../vector2.hpp"
namespace sani {
	namespace math {

		/// Builds a scale 3x3 matrix created from a vector of 2 components.
		///
		/// @param mat Input matrix multiplied by this translation matrix.
		/// @param vec Coordinates of a scale vector.	
		template <typename T>
		Matrix3<T> scale(Matrix3<T> const& mat, Vector2<T> const& vec);

		/// Builds a translation 3x3 matrix created from a vector of 2 components.
		///
		/// @param mat Input matrix multiplied by this translation matrix.
		/// @param vec Coordinates of a translation vector.	
		template<typename T>
		Matrix3<T> translate(Matrix3<T> const& mat, Vector2<T> const& vec);

		/// Builds a rotation 3x3 matrix created from an angle. 
		///
		/// @param mat Input matrix multiplied by this translation matrix.
		/// @param angle Rotation angle expressed in radians.
		template<typename T>
		Matrix3<T> rotate(Matrix3<T> const& mat, T angle);

		/// Builds a horizontal shear 3x3 matrix
		///
		/// @param mat Input matrix multiplied by this translation matrix.
		/// @param y Shear factor.
		template<typename T>
		Matrix3<T> shearX(Matrix3<T> const& mat, T y);

		/// Builds a vertical shear 3x3 matrix
		///
		/// @param mat Input matrix multiplied by this translation matrix.
		/// @param x Shear factor.
		template<typename T>
		Matrix3<T> shearX(Matrix3<T> const& mat, T x);
	}
}

	