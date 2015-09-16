#pragma once
#include "vector3.hpp"
namespace sani {
	namespace math {

		/// @class Matrix3 Matrix3.hpp "sani/core/math/matrix3.hpp"
		/// @author siquel
		///
		/// Represents a 3x3 matrix
		template <typename T>
		class Matrix3 {
		private:
			/// Row 1
			Vector3<T> row1;
			/// Row 2
			Vector3<T> row2;
			/// Row 3
			Vector3<T> row3;
		public:
			static const int Rows = 3;
			static const int Columns = 3;
			/// Creates a identity matrix
			inline Matrix3();

			/// Creates a matrix with specified columns
			/// @param row1 The first row
			/// @param row2 The second row
			/// @param row3 The third row
			inline Matrix3(const Vector3<T>& row1, const Vector3<T>& row2, const Vector3<T>& row3);

			/// Copies already created matrix
			/// @param mat The matrix
			inline Matrix3(const Matrix3& mat);

			/// Creates a matrix with specified columns
			/// @param m11 The first column on the first row
			/// @param m12 The second column on the first row
			/// @param m13 The third column on the first row
			/// @param m21 The first column on the second row
			/// @param m22 The first column on the second row
			/// @param m23 The third column on the second row
			/// @param m31 The first column on the third row
			/// @param m32 The first column on the third row
			/// @param m33 The first column on the third row
			inline Matrix3(const T& m11, const T& m12, const T& m13, 
							const T& m21, const T& m22, const T& m23,
							const T& m31, const T& m32, const T& m33);

			/// Copies already created matrix
			/// @param mat The matrix
			template <typename U>
			inline Matrix3(const Matrix3<U>& mat);

			// Comparison operators

			/// Checks if the matrices are equal
			/// @param rhs The matrix
			inline bool operator==(const Matrix3& rhs) const;

			/// Checks if the matrices are unequal
			/// @param rhs The matrix
			inline bool operator!=(const Matrix3& rhs) const;

			// Assignment operators

			/// Assigns the matrix
			/// @param rhs The matrix
			inline const Matrix3& operator=(const Matrix3& rhs);

			/// Adds two matrices 
			/// @param rhs The matrix
			inline Matrix3& operator+=(const Matrix3& rhs);

			/// Subtracts two matrices 
			/// @param rhs The matrix
			inline Matrix3& operator-=(const Matrix3& rhs);

			/// Multiplies matrix by scalar
			/// @param rhs The scalar
			inline Matrix3& operator*=(const T& rhs);

			/// Multiplies two matrices
			/// @param rhs The matrix
			inline Matrix3& operator*=(const Matrix3& rhs);

			/// Divides matrix by scalar
			/// @param rhs The scalar
			inline Matrix3& operator/=(const T& rhs);

			// Arithmetic operators

			/// Adds two matrices 
			/// @param rhs The matrix
			inline const Matrix3 operator+(const Matrix3& rhs) const;

			/// Subtracts two matrices 
			/// @param rhs The matrix
			inline const Matrix3 operator-(const Matrix3& rhs) const;

			/// Multiplies two matrices
			/// @param rhs The matrix
			inline const Matrix3 operator*(const Matrix3& rhs) const;

			/// Multiplies matrix by scalar
			/// @param rhs The scalar
			inline const Matrix3 operator*(const T& rhs) const;

			/// Multiplies matrix by vector
			/// @param rhs The vector
			inline const Vector3<T> operator*(const Vector3<T>& rhs) const;

			/// Divides matrix by scalar
			/// @param rhs The scalar
			inline const Matrix3 operator/(const T& rhs) const;

			// Indexer

			/// Returns a mutable reference to row
			/// @param i The row index
			inline Vector3<T>& operator[](const unsigned int i);

			/// Returns a immutable reference to row
			/// @param i The row index
			inline const Vector3<T>& operator[](const unsigned int i) const;
		};

		/// Multiplies matrix by scalar
		/// @param lhs The scalar
		/// @param rhs The matrix
		template<typename T>
		inline const Matrix3<T> operator*(const T& lhs, const Matrix3<T>& rhs);

		/// Multiplies matrix by vector
		/// @param lhs The vector
		/// @param rhs The matrix
		template<typename T>
		inline const Vector3<T>& operator*=(Vector3<T>& lhs, const Matrix3<T>& rhs);

		typedef Matrix3<float> Mat3;
		typedef Matrix3<float> Mat3f;
		typedef Matrix3<double> Mat3d;
		typedef Matrix3<unsigned int> Mat3u;
		typedef Matrix3<int> Mat3i;
	}
}

#include "impl/Matrix3.hpp"