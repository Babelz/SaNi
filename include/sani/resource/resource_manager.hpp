#pragma once
#include "sani/precompiled.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, Resource);
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {
	namespace resource {
		using namespace io;
		using namespace graphics;

		/// Asset manager which holds all the resources loaded
		/// to engine
		///
		/// @author siquel
		class ResourceManager {
		private:
			// these are just for debug and we need service model for actual impl
			const FileSystem* fileSystem;
			GraphicsDevice* graphicsDevice;
		public:
			// TODO services needed, this is for debug
			ResourceManager(const FileSystem* fileSystem, GraphicsDevice* graphicsDevice);
			template <class T>
			T* load(const String& asset) {
				return nullptr;
			}
		};
	}
}