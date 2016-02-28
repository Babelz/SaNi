#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {
	namespace resource {
		namespace reader {

			namespace {
				auto &db = sani::rtti::TypeDatabase::getInstance();
			}
			struct ReflectionInjector {
				ReflectionInjector() {
					RTTI_REGISTER_TYPE(ResourceTypeReader);
				}
			};

			static ReflectionInjector ignoreme;

		}
	}
}

