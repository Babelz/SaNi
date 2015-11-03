#pragma once
#include <typeindex>
#include <map>
#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/types.hpp"

namespace sani {
	namespace resource {
		namespace compiler {
			class ResourceCompiler {
			private:
				io::FileSystem fileSystem;
				std::map<std::type_index, ResourceTypeWriter*> lookup;
				String filePath;
				String outputPath;
				void initialize();
			public:
				ResourceCompiler();
				~ResourceCompiler();
				// TODO move to inl
				template <class T, class U>
				void map() {
					lookup[std::type_index(typeid(T))] = new U;
				}
				// TODO move to inl
				template <class T>
				ResourceTypeWriter* getWriter() {
					return lookup[std::type_index(typeid(T))];
				}

				void compile(const String& path);

				const String& getFilePath() const;
				const String& getOutputPath() const;
			};
		}
	}
}