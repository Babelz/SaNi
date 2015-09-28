#pragma once
#include "sani/precompiled.hpp"
#include "sani/forward_declare.hpp"
#include <vector>

SANI_FORWARD_DECLARE_3(sani, resource, reader, ResourceTypeReader);
namespace sani {
	namespace resource {
		namespace reader {
			/// Holds information about type readers to be used for
			/// reading different datatypes
			///
			/// @author siquel
			class ResoureTypeReaderManager {
			private:
				std::vector<ResourceTypeReader*> typeReaders;
			public:
				/// Default constructor
				ResoureTypeReaderManager() = default;
				/// Deletes all the type readers
				~ResoureTypeReaderManager();

				/// Registers new type reader to managers
				/// @tparam T The type of the reader to be registered
				template <class T>
				void registerTypeReader() {
					typeReaders.push_back(new T);
				}
				/// Register all standard type readers to manager
				void registerStandardTypes();

				/// Returns the namespace qualified reader or nullptr
				/// @param name The fully namespace qualified name
				ResourceTypeReader* getReaderByName(const String& name) const;
			};
		}
	}
}