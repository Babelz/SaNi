#pragma once
#include "sani/resource/resource_manager.hpp"
#include "sani/platform/file/binary_reader.hpp"
#include "sani/resource/reader/resource_type_reader_manager.hpp"
#include "sani/debug.hpp"
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
namespace sani {
	namespace resource {
		namespace reader {
			using namespace graphics;
			using namespace io;
			/// The class that handles reading single asset
			/// 
			/// @author siquel
			class ResourceReader : public io::BinaryReader {
				// TODO add functions to read matrices vectors and stuff
			private:
				ResourceManager& manager;
				GraphicsDevice* graphicsDevice;
				std::vector<ResourceTypeReader*> readers;
			public:
				/// Initializes new resource reader
				ResourceReader(FileStream* stream, ResourceManager& manager, GraphicsDevice* device);
				~ResourceReader();

				/// Gets the global resource manager used in whole engine
				ResourceManager& getResourceManager() const;
				/// Gets the graphics device used in whole engine
				GraphicsDevice* getGraphicsDevice() const;

				template <class ObjectType>
				ObjectType* readObject();

				/// Reads the whole asset, this method assumes the 
				/// type readers are already initialized
				/// @param readers The initialized list of all readers
				void* readAsset(const ResoureTypeReaderManager& readers);
			};
		}
	}
}

// TODO move to inl

template <class ObjectType>
ObjectType* sani::resource::reader::ResourceReader::readObject() {
	uint32 index = static_cast<uint32>(read7BitEncodedInt());
	SANI_ASSERT(index < readers.size());
	ResourceTypeReader* reader = readers[index];
	return static_cast<ObjectType*>(reader->read(this));
}

