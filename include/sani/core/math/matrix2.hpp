#pragma once
#include "vector2.hpp"
namespace sani {
	namespace math {

		/// @class Matrix2 matrix2.hpp "sani/core/math/matrix2.hpp"
		/// @author siquel
		///
		/// Represents a 2x2 matrix
		template <typename T>
		class Matrix2 {
		private:
			/// Row 1
			Vector2<T> row1;
			/// Row 2
			Vector2<T> row2;
		public:
			static const int Rows = 2;
			static const int Columns = 2;
			/// Creates a identity matrix
			Matrix2();

			/// Creates a matrix with specified columns
			/// @param row1 The first row
			/// @param row2 The second row
			Matrix2(const Vector2<T>& row1, const Vector2<T>& row2);

			/// Copies already created matrix
			/// @param mat The matrix
			Matrix2(const Matrix2& mat);

			/// Creates a matrix with specified columns
			/// @param m11 The first column on the first row
			/// @param m12 The second column on the first row
			/// @param m21 The first column on the second row
			/// @param m22 The first column on the second row
			Matrix2(const T& m11, const T& m12, const T& m21, const T& m22);

			/// Copies already created matrix
			/// @param mat The matrix
			template <typename U>
			Matrix2(const Matrix2<U>& mat);

			// Comparison operators

			/// Checks if the matrices are equal
			/// @param rhs The matrix
			bool operator==(const Matrix2& rhs) const;

			/// Checks if the matrices are unequal
			/// @param rhs The matrix
			bool operator!=(const Matrix2& rhs) const;

			// Assignment operators

			/// Assigns the matrix
			/// @param rhs The matrix
			const Matrix2& operator=(const Matrix2& rhs);

			/// Adds two matrices 
			/// @param rhs The matrix
			Matrix2& operator+=(const Matrix2& rhs);

			/// Subtracts two matrices 
			/// @param rhs The matrix
			Matrix2& operator-=(const Matrix2& rhs);

			/// Multiplies matrix by scalar
			/// @param rhs The scalar
			Matrix2& operator*=(const T& rhs);

			/// Multiplies two matrices
			/// @param rhs The matrix
			Matrix2& operator*=(const Matrix2& rhs);

			/// Divides matrix by scalar
			/// @param rhs The scalar
			Matrix2& operator/=(const T& rhs);

			// Arithmetic operators

			/// Adds two matrices 
			/// @param rhs The matrix
			const Matrix2 operator+(const Matrix2& rhs) const;

			/// Subtracts two matrices 
			/// @param rhs The matrix
			const Matrix2 operator-(const Matrix2& rhs) const;

			/// Multiplies two matrices
			/// @param rhs The matrix
			const Matrix2 operator*(const Matrix2& rhs) const;

			/// Multiplies matrix by scalar
			/// @param rhs The scalar
			const Matrix2 operator*(const T& rhs) const;

			/// Multiplies matrix by vector
			/// @param rhs The vector
			const Vector2<T> operator*(const Vector2<T>& rhs) const;

			/// Divides matrix by scalar
			/// @param rhs The scalar
			const Matrix2 operator/(const T& rhs) const;

			// Indexer
			
			/// Returns a mutable reference to row
			/// @param i The row index
			Vector2<T>& operator[](const unsigned int i);

			/// Returns a immutable reference to row
			/// @param i The row index
			const Vector2<T>& operator[](const unsigned int i) const;
		};

		/// Multiplies matrix by scalar
		/// @param lhs The scalar
		/// @param rhs The matrix
		template<typename T>
		const Matrix2<T> operator*(const T& lhs, const Matrix2<T>& rhs);

		/// Multiplies matrix by vector
		/// @param lhs The vector
		/// @param rhs The matrix
		template<typename T>
		const Vector2<T>& operator*=(Vector2<T>& lhs, const Matrix2<T>& rhs);

		typedef Matrix2<float> Mat2;
		typedef Matrix2<float> Mat2f;
		typedef Matrix2<double> Mat2d;
		typedef Matrix2<unsigned int> Mat2u;
		typedef Matrix2<int> Mat2i;
	}
}

#include "impl/matrix2.hpp"