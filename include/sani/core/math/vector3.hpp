#pragma once
#include "vector2.hpp"
#include "sani/preprocessor/rtti.hpp"
#include "sani/preprocessor/rtti_runtime.hpp"
namespace sani {
	namespace math {
		/// @class Vector3 vector3.hpp "sani/core/math/vector3.hpp"
		/// @author siquel
		///
		/// Represents a 3 component vector
		template <typename T>
		class Vector3 {
			DECLARE_REFLECTABLE;
		public:
			/// X component
			T x;
			/// Y component
			T y;
			/// Z component
			T z;

			static const unsigned int Components = 3;
			/// Creates a new three component zero vector
			inline Vector3();

			/// Creates a new three component vector with specified components
			/// @param x x component
			/// @param y y component
			/// @param z z component
			inline Vector3(const T& x, const T& y, const T& z);

			/// Creates a new three component vector with specified components
			/// @param vector x and y components
			/// @param z z component
			inline Vector3(const Vector2<T>& vector, const T& z);

			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			inline Vector3(const Vector3& vector);

			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			template<typename U>
			inline Vector3(const Vector3<U>& vector);

			/// Initializes both components with desired value
			/// @param value The value which is assigned to both components
			inline explicit Vector3(const T& value);
			inline ~Vector3();

			/// Calculates the length of the vector but does not perform square root
			inline double lengthSquared() const;
			/// Calculates the length of the vector
			inline double length() const;

			/// Checks if the vector is unit vector (the length is 1)
			inline bool isNormalized() const;

			// comparison operator overloads

			/// Checks if the vector's components are equal
			/// @param rhs The vector to check against
			inline bool operator==(const Vector3& rhs) const;

			/// Checks if the vector's components are unequal
			/// @param rhs Vector to check against
			inline bool operator!=(const Vector3& rhs) const;

			/// Checks if the vector's length is less than the given vector
			/// @param rhs Vector to check against
			inline bool operator<(const Vector3& rhs) const;

			/// Checks if the vector's length is greater than the given vector
			/// @param rhs Vector to check against
			inline bool operator>(const Vector3& rhs) const;

			/// Checks if the vector's length is less than or equal the given vector
			/// @param rhs Vector to check against
			inline bool operator<=(const Vector3& rhs) const;

			/// Checks if the vector's length is more than or equal the given vector
			/// @param rhs Vector to check against
			inline bool operator>=(const Vector3& rhs) const;

			// Arithmetics

			/// Multiplies vector with the given vector
			/// @param rhs The vector
			inline const Vector3 operator*(const Vector3& rhs) const;

			/// Multiplies vector with the given scalar
			/// @param rhs The vector
			inline const Vector3 operator*(const T& rhs) const;

			/// Adds the given vector
			/// @param rhs The vector
			inline const Vector3 operator+(const Vector3& rhs) const;
			/// Subtracts vector with the given vector
			/// @param rhs The vector
			inline const Vector3 operator-(const Vector3& rhs) const;

			/// Divides vector with the given scalar
			/// @param rhs The scalar
			inline const Vector3 operator/(const T& rhs) const;

			/// Divides vector with the given vector
			/// @param rhs The vector
			inline const Vector3 operator/(const Vector3& rhs) const;

			/// Inverses the vector direction
			inline const Vector3 operator-() const;

			// Assignments

			inline const Vector3& operator=(const Vector3& rhs);

			/// Adds two vectors
			/// @param rhs The vector
			inline Vector3& operator+=(const Vector3& rhs);
			/// Subtracts two vectors
			/// @param rhs The vector
			inline Vector3& operator-=(const Vector3& rhs);
			/// Multiplies two vectors
			/// @param rhs The vector
			inline Vector3& operator*=(const Vector3& rhs);
			/// Divides two vectors
			/// @param rhs The vector
			inline Vector3& operator/=(const Vector3& rhs);
			/// Multiplies vector by scalar
			/// @param rhs The scalar
			inline Vector3& operator*=(const T& rhs);
			/// Divides vector by scalar
			/// @param rhs The scalar
			inline Vector3& operator/=(const T& rhs);

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
		inline const Vector3<T> operator*(const T& lhs, const Vector3<T>& rhs);

		using Vec3f = Vector3<float>;
		using Vec3d = Vector3<double>;
		using Vec3i = Vector3<int>;
		using Vec3u = Vector3<unsigned int>;
	}

}

#include "impl/vector3.hpp"