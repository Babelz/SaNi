#pragma once
#include "sani/preprocessor/rtti.hpp"

namespace sani {
	namespace math {
		/// @class Vector2 vector2.hpp "sani/core/math/vector2.hpp"
		/// @author siquel
		///
		/// Represents a 2 component vector
		template <typename T>
		class Vector2 {
			DECLARE_REFLECTABLE;
		public:
			/// X component
			T x;
			/// Y component
			T y;

			static const unsigned int Components = 2;
			/// Creates a new two component zero vector
			inline Vector2();
			/// Creates a new two component vector with specified components
			/// @param x x component
			/// @param y y component
			inline Vector2(const T& x, const T& y);
			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			inline Vector2(const Vector2& vector);
			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			template<typename U>
			inline Vector2(const Vector2<U>& vector);
			/// Initializes both components with desired value
			/// @param value The value which is assigned to both components
			inline explicit Vector2(const T& value);
			inline ~Vector2();

			/// Calculates the length of the vector but does not perform square root
			inline double lengthSquared() const;
			/// Calculates the length of the vector
			inline double length() const;

			/// Checks if the vector is unit vector (the length is 1)
			inline bool isNormalized() const;

			// comparison operator overloads

			/// Checks if the vector's components are equal
			/// @param rhs The vector to check against
			inline bool operator==(const Vector2& rhs) const;

			/// Checks if the vector's components are unequal
			/// @param rhs Vector to check against
			inline bool operator!=(const Vector2& rhs) const;

			/// Checks if the vector's length is less than the given vector
			/// @param rhs Vector to check against
			inline bool operator<(const Vector2& rhs) const;

			/// Checks if the vector's length is greater than the given vector
			/// @param rhs Vector to check against
			inline bool operator>(const Vector2& rhs) const;

			/// Checks if the vector's length is less than or equal the given vector
			/// @param rhs Vector to check against
			inline bool operator<=(const Vector2& rhs) const;

			/// Checks if the vector's length is more than or equal the given vector
			/// @param rhs Vector to check against
			inline bool operator>=(const Vector2& rhs) const;

			// Arithmetics

			/// Multiplies vector with the given vector
			/// @param rhs The vector
			inline const Vector2 operator*(const Vector2& rhs) const;

			/// Multiplies vector with the given scalar
			/// @param rhs The vector
			inline const Vector2 operator*(const T& rhs) const;

			/// Adds the given vector
			/// @param rhs The vector
			inline const Vector2 operator+(const Vector2& rhs) const;
			/// Subtracts vector with the given vector
			/// @param rhs The vector
			inline const Vector2 operator-(const Vector2& rhs) const;

			/// Divides vector with the given scalar
			/// @param rhs The scalar
			inline const Vector2 operator/(const T& rhs) const;

			/// Divides vector with the given vector
			/// @param rhs The vector
			inline const Vector2 operator/(const Vector2& rhs) const;

			/// Inverses the vector direction
			inline const Vector2 operator-() const;

			// Assignments

			inline const Vector2& operator=(const Vector2& rhs);

			/// Adds two vectors
			/// @param rhs The vector
			inline Vector2& operator+=(const Vector2& rhs);
			/// Subtracts two vectors
			/// @param rhs The vector
			inline Vector2& operator-=(const Vector2& rhs);
			/// Multiplies two vectors
			/// @param rhs The vector
			inline Vector2& operator*=(const Vector2& rhs);
			/// Divides two vectors
			/// @param rhs The vector
			inline Vector2& operator/=(const Vector2& rhs);
			/// Multiplies vector by scalar
			/// @param rhs The scalar
			inline Vector2& operator*=(const T& rhs);
			/// Divides vector by scalar
			/// @param rhs The scalar
			inline Vector2& operator/=(const T& rhs);

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
		inline const Vector2<T> operator*(const T& lhs, const Vector2<T>& rhs);

		using Vec2f = Vector2<float>;
		using Vec2d = Vector2<double>;
		using Vec2i = Vector2<int>;
		using Vec2u = Vector2<unsigned int>;
	}
	
}

#include "impl/vector2.hpp"