#pragma once

namespace sani {
	namespace math {

		/// Converts degrees to radians and returns the result.
		/// @tparam T Floating-point scalar
		template <typename T>
		T radians(const T& degrees);

		/// Converts radians to degrees and returns the result.
		/// @tparam T Floating-point scalar
		template <typename T>
		T degrees(const T& radians);

		/// The standard trigonometric sine function. 
		template<typename T>
		T sin(const T& angle);

		/// The standard trigonometric cosine function. 
		template<typename T>
		T cos(const T& angle);

		/// The standard trigonometric tangent function. 
		template<typename T>
		T tan(const T& angle);

		/// Arc sine. Returns an angle whose sine is x. 
		template<typename T>
		T asin(const T& x);

		/// Arc cosine. 
		template<typename T>
		T acos(const T& x);

		/// Arc tangent. Returns an angle whose tangent is y/x. 
		template<typename T>
		T atan(const T& y, const T& x);

		/// Arc tangent. 
		template<typename T>
		T atan(const T& yx);
	}
}

#include "trigonometric_func.inl"