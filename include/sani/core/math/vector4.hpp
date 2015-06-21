#pragma once
#include "vector2.hpp"
#include "vector3.hpp"
namespace sani {
	namespace math {
		/// @class Vector4 vector4.hpp "sani/core/math/vector4.hpp"
		/// @author siquel
		///
		/// Represents a 4 component vector
		template <typename T>
		class Vector4 {
		public:
			/// X component
			T x;
			/// Y component
			T y;
			/// Z component
			T z;
			/// W component
			T w;

			static const unsigned int Components = 4;
			/// Creates a new four component zero vector
			Vector4();
			/// Creates a new four component vector with specified components
			/// @param x x component
			/// @param y y component
			/// @param z z component
			/// @param z z component
			Vector4(const T& x, const T& y, const T& z, const T& w);

			/// Creates a new four component vector with specified components
			/// @param vector x and y components
			/// @param z z component
			/// @param w w component
			Vector4(const Vector2<T>& vector, const T& z, const T& w);

			/// Creates a new four component vector with specified components
			/// @param vec1 x and y components
			/// @param vec2 z and w components
			Vector4(const Vector2<T>& vec1, const Vector2<T>& vec2);

			/// Creates a new four component vector with specified components
			/// @param vector x, y and z components
			/// @param w w component
			Vector4(const Vector3<T>& vector, const T& w);

			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			Vector4(const Vector4& vector);
			/// Copies components from already created vector
			/// @param vector a vector where to copy components

			template<typename U>
			Vector4(const Vector4<U>& vector);
			/// Initializes both components with desired value
			/// @param value The value which is assigned to both components
			explicit Vector4(const T& value);
			~Vector4();

			/// Calculates the length of the vector but does not perform square root
			double lengthSquared() const;
			/// Calculates the length of the vector
			double length() const;

			/// Checks if the vector is unit vector (the length is 1)
			bool isNormalized() const;

			// comparison operator overloads

			/// Checks if the vector's components are equal
			/// @param rhs The vector to check against
			bool operator==(const Vector4& rhs) const;

			/// Checks if the vector's components are unequal
			/// @param rhs Vector to check against
			bool operator!=(const Vector4& rhs) const;

			/// Checks if the vector's length is less than the given vector
			/// @param rhs Vector to check against
			bool operator<(const Vector4& rhs) const;

			/// Checks if the vector's length is greater than the given vector
			/// @param rhs Vector to check against
			bool operator>(const Vector4& rhs) const;

			/// Checks if the vector's length is less than or equal the given vector
			/// @param rhs Vector to check against
			bool operator<=(const Vector4& rhs) const;

			/// Checks if the vector's length is more than or equal the given vector
			/// @param rhs Vector to check against
			bool operator>=(const Vector4& rhs) const;

			// Arithmetics

			/// Multiplies vector with the given vector
			/// @param rhs The vector
			const Vector4 operator*(const Vector4& rhs) const;

			/// Multiplies vector with the given scalar
			/// @param rhs The vector
			const Vector4 operator*(const T& rhs) const;

			/// Adds the given vector
			/// @param rhs The vector
			const Vector4 operator+(const Vector4& rhs) const;
			/// Subtracts vector with the given vector
			/// @param rhs The vector
			const Vector4 operator-(const Vector4& rhs) const;

			/// Divides vector with the given scalar
			/// @param rhs The scalar
			const Vector4 operator/(const T& rhs) const;

			/// Divides vector with the given vector
			/// @param rhs The vector
			const Vector4 operator/(const Vector4& rhs) const;

			/// Inverses the vector direction
			const Vector4 operator-() const;

			// Assignments

			const Vector4& operator=(const Vector4& rhs);

			/// Adds two vectors
			/// @param rhs The vector
			Vector4& operator+=(const Vector4& rhs);
			/// Subtracts two vectors
			/// @param rhs The vector
			Vector4& operator-=(const Vector4& rhs);
			/// Multiplies two vectors
			/// @param rhs The vector
			Vector4& operator*=(const Vector4& rhs);
			/// Divides two vectors
			/// @param rhs The vector
			Vector4& operator/=(const Vector4& rhs);
			/// Multiplies vector by scalar
			/// @param rhs The scalar
			Vector4& operator*=(const T& rhs);
			/// Divides vector by scalar
			/// @param rhs The scalar
			Vector4& operator/=(const T& rhs);

			// Indexer
			/// Returns a immutable reference to component
			/// @param i The component index
			const T& operator[](unsigned int i) const;

			/// Returns a mutable reference to component
			/// @param i The component index
			T& operator[](unsigned int i);
		};

		// So we can do scalar * vec
		/// Multiplies vector with scalar value
		/// @param lhs The scalar value
		/// @param rhs The vector which is multiplied
		template <typename T>
		const Vector4<T> operator*(const T& lhs, const Vector4<T>& rhs);

		typedef Vector4<float> Vec4;
		typedef Vector4<float> Vec4f;
		typedef Vector4<double> Vec4d;
		typedef Vector4<int> Vec4i;
		typedef Vector4<unsigned int> Vec4u;
	}

}

#include "impl/vector4.hpp"