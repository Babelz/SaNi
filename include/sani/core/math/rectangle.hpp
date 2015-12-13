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
			/// Height.
			T h;
			/// Width.
			T w;

			template <typename U>
			Rectangle(const U x, const U y, const U h, const U w);

			Rectangle(const T x, const T y, const T h, const T w);
			
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

			inline void include(const Vector2<T>& r);
			// Operators.

			inline bool operator ==(const Rectangle& r) const;
			inline bool operator !=(const Rectangle& r) const;
			inline Rectangle& operator =(const Rectangle& r);
		};
		/* Type definitions */

		typedef Rectangle<uint32> Rectu32;
		typedef Rectangle<uint16> Rectu16;
		typedef Rectangle<uint8> Rectu8;

		typedef Rectangle<int32> Rect32;
		typedef Rectangle<int16> Rect16;
		typedef Rectangle<int8> Rect8;

		typedef Rectangle<float64> Rectd;
		typedef Rectangle<float32> Rectf;
		typedef Rectangle<int32> Recti;

		// Creates new rectangle using "int" as template type.
		typedef Rectangle<int32> Rect;
	}
}

#include "impl/rectangle.hpp"