#pragma once
#include "sani/precompiled.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, ResourceReader);
SANI_FORWARD_DECLARE_2(sani, resource, ResourceTypeReaderManager);
namespace sani {
	namespace resource {
		/// R
		class ResourceTypeReader {
		public:
			/// Default constructor
			ResourceTypeReader() = default;
			/// Default destructor
			virtual ~ResourceTypeReader();
			// TODO is this needed?
			//virtual String getTargetType() const = 0;
			/// Namespace prefixed reader name
			virtual String getReaderName() const = 0;

			/// Initializes the type reader and adds itself to manager
			virtual void initialize(ResourceTypeReaderManager* manager)  {}
			/// Reads the data type
			/// @param reader The content reader which has the stream to read
			virtual void read(ResourceReader* reader) = 0;
		};
	}
}