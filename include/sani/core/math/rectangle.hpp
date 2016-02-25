#pragma once

#include "sani/types.hpp"
#include "vector2.hpp"

namespace sani {
	namespace math {

		/// @class Rectangle rectangle.hpp "sani/core/math/rectangle.hpp"
		/// @author voidbab
		///
		/// Represents a basic, generic rectangle.
		template <typename T>
		class Rectangle {
		public:
			// Fields.

			/// X component.
			T x;
			/// Y component.
			T y;
			/// Width.
			T w;
			/// Height.
			T h;

			template <typename U>
			Rectangle(const U x, const U y, const U w, const U h);

			Rectangle(const T x, const T y, const T w, const T h);
			
			template <typename U>
			Rectangle(const U x, const U y, const U size);

			Rectangle(const T x, const T y, const T size);
			
			Rectangle();

			inline T top() const;
			inline T right() const;

			inline T bottom() const;
			inline T left() const;
			
			inline Vector2<T> center() const;
			inline Vector2<T> position() const;
			inline Vector2<T> size() const;

			inline bool isEmpty() const;
			
			inline bool contains(const T x, const T y) const;
			inline bool contains(const Vector2<T>& v) const;
			
			inline bool intersects(const Rectangle& r) const;
			// Operators.

			inline bool operator ==(const Rectangle& r) const;
			inline bool operator !=(const Rectangle& r) const;
			inline Rectangle& operator =(const Rectangle& r);
		};

		using Rectu32i	= Rectangle<uint32>;
		using Rectu16i	= Rectangle<uint16>;
		using Rectu8i	= Rectangle<uint8>;

		using Rect32i	= Rectangle<int32>;
		using Rect16i	= Rectangle<int16>;
		using Rect8i	= Rectangle<int8>;

		using Rect64f	= Rectangle<float64>;
		using Rect32f	= Rectangle<float32>;
	}
}

#include "impl/rectangle.hpp"