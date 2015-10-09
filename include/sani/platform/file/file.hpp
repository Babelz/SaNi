#pragma once

namespace sani {
	namespace io {

		/// Specifies how the operating system should open a file
		enum Filemode {
			/// Read only
			Read = 1 << 0,
			/// Write only
			Write = 1 << 1,
			/// I dont know
			Append = 1 << 2
		};

		/// Operator for bitwise or
		inline Filemode operator|(Filemode a, Filemode b) {
			return static_cast<Filemode>(static_cast<int>(a) | static_cast<int>(b));
		}
	}
}

