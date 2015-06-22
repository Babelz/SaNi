#pragma once

#include "sani/precompiled.hpp"
#include <vector>


namespace sani {
	namespace io {
		/// @class FileManager file_manager.hpp "sani/platform/file_manager.hpp"
		/// @author siquel
		/// 
		/// Helper for file access
		class FileManager {
		public:
			/// Default constructor
			FileManager();
			/// Default deconstructor
			virtual ~FileManager();
			//virtual void listFiles() const;
		};
	}
}
