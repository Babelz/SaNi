#pragma once

namespace sani {
	namespace hid {
		enum class Key;

		class Keyboard {
		public:
			static const char* keyToName(const Key key);
		};

		enum class Key {
			Void = -1,	  ///< Unknown key
			A = 0,        ///< The A key
			B,            ///< The B key
			C,            ///< The C key
			D,            ///< The D key
			E,            ///< The E key
			F,            ///< The F key
			G,            ///< The G key
			H,            ///< The H key
			I,            ///< The I key
			J,            ///< The J key
			K,            ///< The K key
			L,            ///< The L key
			M,            ///< The M key
			N,            ///< The N key
			O,            ///< The O key
			P,            ///< The P key
			Q,            ///< The Q key
			R,            ///< The R key
			S,            ///< The S key
			T,            ///< The T key
			U,            ///< The U key
			V,            ///< The V key
			W,            ///< The W key
			X,            ///< The X key
			Y,            ///< The Y key
			Z,            ///< The Z key
			D0,           ///< The 0 key
			D1,           ///< The 1 key
			D2,           ///< The 2 key
			D3,           ///< The 3 key
			D4,           ///< The 4 key
			D5,           ///< The 5 key
			D6,           ///< The 6 key
			D7,           ///< The 7 key
			D8,           ///< The 8 key
			D9,           ///< The 9 key
			F1,           ///< The F1 key
			F2,           ///< The F2 key
			F3,           ///< The F3 key
			F4,           ///< The F4 key
			F5,           ///< The F5 key
			F6,           ///< The F6 key
			F7,           ///< The F7 key
			F8,           ///< The F8 key
			F9,           ///< The F9 key
			F10,          ///< The F10 key
			F11,          ///< The F11 key
			F12,          ///< The F12 key
			F13,          ///< The F13 key
			F14,          ///< The F14 key
			F15,          ///< The F15 key
			F16,          ///< The F16 key
			F17,          ///< The F17 key
			F18,          ///< The F18 key
			F19,          ///< The F19 key
			F20,          ///< The F20 key
			F21,          ///< The F21 key
			F22,          ///< The F22 key
			F23,          ///< The F23 key
			F24,          ///< The F24 key
			Numpad0,      ///< The numpad 0 key
			Numpad1,      ///< The numpad 1 key
			Numpad2,      ///< The numpad 2 key
			Numpad3,      ///< The numpad 3 key
			Numpad4,      ///< The numpad 4 key
			Numpad5,      ///< The numpad 5 key
			Numpad6,      ///< The numpad 6 key
			Numpad7,      ///< The numpad 7 key
			Numpad8,      ///< The numpad 8 key
			Numpad9,      ///< The numpad 9 key
			Escape,       ///< The Escape key
			LControl,     ///< The left Control key
			LShift,       ///< The left Shift key
			LAlt,         ///< The left Alt key
			LSystem,      ///< The left OS specific key
			RControl,     ///< The right Control key
			RShift,       ///< The right Shift key
			RAlt,         ///< The right Alt key
			RSystem,      ///< The right OS specific key
			Menu,         ///< The Menu key
			// TODO add more keys
			Count
		};

	}
}