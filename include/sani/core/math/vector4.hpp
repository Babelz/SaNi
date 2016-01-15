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
			inline Vector4();
			/// Creates a new four component vector with specified components
			/// @param x X component
			/// @param y Y component
			/// @param z Z component
			/// @param w W component
			inline Vector4(const T& x, const T& y, const T& z, const T& w);

			/// Creates a new four component vector with specified components
			/// @param vector x and y components
			/// @param z z component
			/// @param w w component
			inline Vector4(const Vector2<T>& vector, const T& z, const T& w);

			/// Creates a new four component vector with specified components
			/// @param vec1 x and y components
			/// @param vec2 z and w components
			inline Vector4(const Vector2<T>& vec1, const Vector2<T>& vec2);

			/// Creates a new four component vector with specified components
			/// @param vector x, y and z components
			/// @param w w component
			inline Vector4(const Vector3<T>& vector, const T& w);

			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			inline Vector4(const Vector4& vector);
			/// Copies components from already created vector
			/// @param vector a vector where to copy components

			template<typename U>
			inline Vector4(const Vector4<U>& vector);
			/// Initializes both components with desired value
			/// @param value The value which is assigned to both components
			inline explicit Vector4(const T& value);
			inline ~Vector4();

			/// Calculates the length of the vector but does not perform square root
			inline double lengthSquared() const;
			/// Calculates the length of the vector
			inline double length() const;

			/// Checks if the vector is unit vector (the length is 1)
			inline bool isNormalized() const;

			// comparison operator overloads

			/// Checks if the vector's components are equal
			/// @param rhs The vector to check against
			inline bool operator==(const Vector4& rhs) const;

			/// Checks if the vector's components are unequal
			/// @param rhs Vector to check against
			inline bool operator!=(const Vector4& rhs) const;

			/// Checks if the vector's length is less than the given vector
			/// @param rhs Vector to check against
			inline bool operator<(const Vector4& rhs) const;

			/// Checks if the vector's length is greater than the given vector
			/// @param rhs Vector to check against
			inline bool operator>(const Vector4& rhs) const;

			/// Checks if the vector's length is less than or equal the given vector
			/// @param rhs Vector to check against
			inline bool operator<=(const Vector4& rhs) const;

			/// Checks if the vector's length is more than or equal the given vector
			/// @param rhs Vector to check against
			inline bool operator>=(const Vector4& rhs) const;

			// Arithmetics

			/// Multiplies vector with the given vector
			/// @param rhs The vector
			inline const Vector4 operator*(const Vector4& rhs) const;

			/// Multiplies vector with the given scalar
			/// @param rhs The vector
			inline const Vector4 operator*(const T& rhs) const;

			/// Adds the given vector
			/// @param rhs The vector
			inline const Vector4 operator+(const Vector4& rhs) const;
			/// Subtracts vector with the given vector
			/// @param rhs The vector
			inline const Vector4 operator-(const Vector4& rhs) const;

			/// Divides vector with the given scalar
			/// @param rhs The scalar
			inline const Vector4 operator/(const T& rhs) const;

			/// Divides vector with the given vector
			/// @param rhs The vector
			inline const Vector4 operator/(const Vector4& rhs) const;

			/// Inverses the vector direction
			inline const Vector4 operator-() const;

			// Assignments

			inline const Vector4& operator=(const Vector4& rhs);

			/// Adds two vectors
			/// @param rhs The vector
			inline Vector4& operator+=(const Vector4& rhs);
			/// Subtracts two vectors
			/// @param rhs The vector
			inline Vector4& operator-=(const Vector4& rhs);
			/// Multiplies two vectors
			/// @param rhs The vector
			inline Vector4& operator*=(const Vector4& rhs);
			/// Divides two vectors
			/// @param rhs The vector
			inline Vector4& operator/=(const Vector4& rhs);
			/// Multiplies vector by scalar
			/// @param rhs The scalar
			inline Vector4& operator*=(const T& rhs);
			/// Divides vector by scalar
			/// @param rhs The scalar
			inline Vector4& operator/=(const T& rhs);

			// Indexer
			/// Returns a immutable reference to component
			/// @param i The component index
			inline const T& operator[](unsigned int i) const;

			/// Returns a mutable reference to component
			/// @param i The component index
			inline T& operator[](unsigned int i);
		};

		// So we can do scalar * vec
		/// Multiplies vector with scalar value
		/// @param lhs The scalar value
		/// @param rhs The vector which is multiplied
		template <typename T>
		inline const Vector4<T> operator*(const T& lhs, const Vector4<T>& rhs);

		using Vec4f = Vector4<float>;
		using Vec4d = Vector4<double>;
		using Vec4i = Vector4<int>;
		using Vec4u = Vector4<unsigned int>;
	}

}

#include "impl/vector4.hpp"