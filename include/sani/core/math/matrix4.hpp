#pragma once

#include "vector4.hpp"
namespace sani {
	namespace math {

		/// @class Matrix4 Matrix4.hpp "sani/core/math/matrix4.hpp"
		/// @author siquel
		///
		/// Represents a 4x4 matrix
		template <typename T>
		class Matrix4 {
		private:
			/// Row 1
			Vector4<T> row1;
			/// Row 2
			Vector4<T> row2;
			/// Row 3
			Vector4<T> row3;
			/// Row 4
			Vector4<T> row4;
		public:
			static const int Rows = 4;
			static const int Columns = 4;
			/// Creates a identity matrix
			inline Matrix4();

			/// Creates a matrix with specified columns
			/// @param row1 The first row
			/// @param row2 The second row
			/// @param row3 The third row
			/// @param row4 The third row
			inline Matrix4(const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3, const Vector4<T>& row4);

			/// Copies already created matrix
			/// @param mat The matrix
			inline Matrix4(const Matrix4& mat);

			/// Creates a matrix with specified columns
			/// @param m11 The first column on the first row
			/// @param m12 The second column on the first row
			/// @param m13 The third column on the first row
			/// @param m14 The fourth column on the first row
			/// @param m21 The first column on the second row
			/// @param m22 The first column on the second row
			/// @param m23 The third column on the second row
			/// @param m24 The fourth column on the second row
			/// @param m31 The first column on the third row
			/// @param m32 The second column on the third row
			/// @param m33 The third column on the third row
			/// @param m34 The fourth column on the third row
			/// @param m41 The first column on the fourth row
			/// @param m42 The second column on the fourth row
			/// @param m43 The third column on the fourth row
			/// @param m44 The fourth column on the fourth row
			inline Matrix4(const T& m11, const T& m12, const T& m13, const T& m14,
				const T& m21, const T& m22, const T& m23, const T& m24,
				const T& m31, const T& m32, const T& m33, const T& m34,
				const T& m41, const T& m42, const T& m43, const T& m44);

			/// Copies already created matrix
			/// @param mat The matrix
			template <typename U>
			inline Matrix4(const Matrix4<U>& mat);

			// Comparison operators

			/// Checks if the matrices are equal
			/// @param rhs The matrix
			inline bool operator==(const Matrix4& rhs) const;

			/// Checks if the matrices are unequal
			/// @param rhs The matrix
			inline bool operator!=(const Matrix4& rhs) const;

			// Assignment operators

			/// Assigns the matrix
			/// @param rhs The matrix
			inline const Matrix4& operator=(const Matrix4& rhs);

			/// Adds two matrices 
			/// @param rhs The matrix
			inline Matrix4& operator+=(const Matrix4& rhs);

			/// Subtracts two matrices 
			/// @param rhs The matrix
			inline Matrix4& operator-=(const Matrix4& rhs);

			/// Multiplies matrix by scalar
			/// @param rhs The scalar
			inline Matrix4& operator*=(const T& rhs);

			/// Multiplies two matrices
			/// @param rhs The matrix
			inline Matrix4& operator*=(const Matrix4& rhs);

			/// Divides matrix by scalar
			/// @param rhs The scalar
			inline Matrix4& operator/=(const T& rhs);

			// Arithmetic operators

			/// Adds two matrices 
			/// @param rhs The matrix
			inline const Matrix4 operator+(const Matrix4& rhs) const;

			/// Subtracts two matrices 
			/// @param rhs The matrix
			inline const Matrix4 operator-(const Matrix4& rhs) const;

			/// Multiplies two matrices
			/// @param rhs The matrix
			inline const Matrix4 operator*(const Matrix4& rhs) const;

			/// Multiplies matrix by scalar
			/// @param rhs The scalar
			inline const Matrix4 operator*(const T& rhs) const;

			/// Multiplies matrix by vector
			/// @param rhs The vector
			inline const Vector4<T> operator*(const Vector4<T>& rhs) const;

			/// Divides matrix by scalar
			/// @param rhs The scalar
			inline const Matrix4 operator/(const T& rhs) const;

			// Indexer

			/// Returns a mutable reference to row
			/// @param i The row index
			inline Vector4<T>& operator[](const unsigned int i);

			/// Returns a immutable reference to row
			/// @param i The row index
			inline const Vector4<T>& operator[](const unsigned int i) const;
		};

		/// Multiplies matrix by scalar
		/// @param lhs The scalar
		/// @param rhs The matrix
		template<typename T>
		inline const Matrix4<T> operator*(const T& lhs, const Matrix4<T>& rhs);

		/// Multiplies matrix by vector
		/// @param lhs The vector
		/// @param rhs The matrix
		template<typename T>
		inline const Vector4<T>& operator*=(Vector4<T>& lhs, const Matrix4<T>& rhs);

		typedef Matrix4<float> Mat4;
		typedef Matrix4<float> Mat4f;
		typedef Matrix4<double> Mat4d;
		typedef Matrix4<unsigned int> Mat4u;
		typedef Matrix4<int> Mat4i;
	}
}

#include "impl/Matrix4.hpp"

