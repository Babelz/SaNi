#pragma once

#include "sani/precompiled.hpp"
#include <vector>
#include <cstdio>

SANI_FORWARD_DECLARE_2(sani, io, File);

namespace sani {
	namespace io {
		/// @class BaseFileManager base_file_manager.hpp "sani/platform/base_file_manager.hpp"
		/// @author siquel
		/// 
		/// Helper for file access
		class BaseFileManager {
		public:
			/// Default constructor
			BaseFileManager();
			/// Default deconstructor
			virtual ~BaseFileManager();
			
			//void readBytes(File*, size_t offset, size_t size, std::vector<uint8_t>&);
		};
	}
}
