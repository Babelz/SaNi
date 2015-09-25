#pragma once
#include "sani/precompiled.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, ResourceReader);
namespace sani {
	namespace resource {
		/// 
		class ResourceTypeReader {
		public:
			ResourceTypeReader() = default;
			virtual ~ResourceTypeReader();

			virtual String getTargetType() const = 0;
			virtual String getReaderName() const = 0;

			// TODO type managers
			virtual void initialize()  {}
			virtual void read(ResourceReader* reader) = 0;
		};
	}
}