#pragma once
#include "sani/precompiled.hpp"
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

		///
		/// @class File file.hpp "sani/platform/file.hpp"
		/// @author siquel
		/// 
		class File {
		private:
			String path;
		public:
			/// Constructs new file
			/// @param path The file path
			File(const String& path);
			/// Default deconstructor
			~File();
			/// Gets the files path
			/// @returns The path of file
			const String& getPath() const;
		};
	}
}

