#pragma once

#include "sani/resource/compiler/resource_compiler.hpp"

namespace sani {

	namespace resource {
		
		namespace compiler {

			template <class T, class U>
			void ResourceCompiler::mapWriter() {
				lookup[std::type_index(typeid(T))] = new U;
			}

			template <class T, class U>
			void ResourceCompiler::mapProcessor() {
				processors[std::type_index(typeid(T))] = new U;
			}
		}
	}
}