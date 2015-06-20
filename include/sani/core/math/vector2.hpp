#pragma once

namespace sani {
	namespace math {
		/// @class Vector2 vector2.hpp "sani/core/math/vector2.hpp"
		/// @author siquel
		///
		/// Represents a 2 component vector
		template <typename T>
		class Vector2 {
		public:
			/// X component
			T x;
			/// Y component
			T y;

			/// Creates a new two component zero vector
			Vector2();
			/// Creates a new two component vector with specified components
			/// @param x x component
			/// @param y y component
			Vector2(const T& x, const T& y);
			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			Vector2(const Vector2& vector);
			/// Copies components from already created vector
			/// @param vector a vector where to copy components
			template<typename U>
			Vector2(const Vector2<U>& vector);
			~Vector2();
		};

		typedef Vector2<float> Vec2;
		typedef Vector2<float> Vec2f;
		typedef Vector2<double> Vec2d;
		typedef Vector2<int> Vec2i;
		typedef Vector2<unsigned int> Vec2u;
	}
	
}