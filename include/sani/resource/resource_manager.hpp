#pragma once

#include "sani/types.hpp"
#include "sani/forward_declare.hpp"
#include "sani/resource/reader/resource_type_reader_manager.hpp"
#include <map>

SANI_FORWARD_DECLARE_2(sani, resource, Resource);
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

namespace sani {

	namespace resource {

		using namespace io;
		using namespace graphics;
		using namespace reader;

		/// Asset manager which holds all the resources loaded
		/// to engine
		///
		/// @author siquel
		class ResourceManager {
		private:
			// these are just for debug and we need service model for actual impl
			FileSystem* fileSystem;
			GraphicsDevice* graphicsDevice;
			std::map<String, Resource*> resources;
			ResoureTypeReaderManager typeReaders;
			String8 contentRoot;
            engine::SaNiEngine* const engine;
			ResourceManager(const ResourceManager& mgr) = delete;
			ResourceManager& operator=(const ResourceManager& mgr) = delete;
		public:
            ResourceManager(FileSystem* fileSystem, GraphicsDevice* graphicsDevice, engine::SaNiEngine* const engine, String8& contentRoot);

			template <class T>
			T* load(const String& asset) {
				return static_cast<T*>(load(asset));
			}

            engine::SaNiEngine* const getEngine() const;

			void* load(const String& asset);

			void unload();
		};
	}
}