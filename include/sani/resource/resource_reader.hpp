#pragma once
#include <sani/resource/resource_manager.hpp>
#include <sani/platform/binary_reader.hpp>

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
namespace sani {
	namespace resource {
		using namespace graphics;
		using namespace io;
		/// The class that handles reading single asset
		/// 
		/// @author siquel
		class ResourceReader : io::BinaryReader {
		private:
			ResourceManager& manager;
			GraphicsDevice* graphicsDevice;
		public:
			ResourceReader(const FileSystem* fs, const String& file, ResourceManager& manager, GraphicsDevice* device);
			~ResourceReader();

			ResourceManager& getResourceManager() const;
			GraphicsDevice* getGraphicsDevice() const;
		};
	}
}