#pragma once

#include "sani/resource/resource_manager.hpp"
#include "sani/platform/file/binary_reader.hpp"
#include "sani/resource/reader/resource_type_reader_manager.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/core/math/matrix.hpp"
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

				/// Reads int32 rectangle from the stream
				math::Rectangle<int32> readRectangle();

				/// Reads 4x4 float32 matrix from the stream
				math::Matrix4<float32> readMatrix();

				/// Reads the whole asset, this method assumes the 
				/// type readers are already initialized
				/// @param readers The initialized list of all readers
				void* readAsset(const ResoureTypeReaderManager& readers);
			};
		}
	}
}

#include "sani/resource/reader/inl/resource_reader.hpp"