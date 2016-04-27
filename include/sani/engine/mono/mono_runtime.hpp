#pragma once

#include "sani\forward_declare.hpp"
#include "sani\types.hpp"

#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>


#include <vector>

SANI_FORWARD_DECLARE_2(sani, engine, MonoProvider)

namespace sani {

	namespace engine {

		/*
		
		*/

		/// @class MonoRuntime mono_runtime.hpp "sani/engine/mono_runtime.hpp"
		/// @author voidbab
		///
		/// Contains all mono related data. Use the provider to
		/// call mono API functions.
		class MonoRuntime final {
		private:
			String monoAssemblyName;
			String monoAssembliesPath;
			String monoLibrariesPath;
			String monoConfigPath;
			String monoDependencies;

			MonoProvider* monoProvider;		// Provider that defines our Mono interface.
			MonoAssembly* monoAssembly;		// Our mono assembly containing the C# code.
			MonoDomain* monoDomain;			// Our mono domain in which all the magic happens.

			MonoRuntime();

			~MonoRuntime();

			bool initializeRuntime(); 
			void logErrors(std::vector<String>& errors) const;

			bool monoLibrariesDirExists() const;
			bool monoConfigDirExists() const;
			bool assembliesDirExists() const;
		public:
			/// Returns the runtime instance.
			static MonoRuntime& instance();	
			/// Returns the runtime provider that contains 
			/// all the mono functions.
			MonoProvider* const provider();

			MonoDomain* domain();

			/// Starts the runtime.
			/// Returns false if errors occurred
			/// while initializing.
			bool start(const String& monoAssembliesPath, const String& monoLibrariesPath, const String& monoConfigPath, const String& monoAssemblyName, const String& monoDependencies);
			/// Shutdowns the runtime. Cleanups all mono related data.
			void shutdown();

			MonoRuntime& operator =(MonoRuntime& other) = delete;
			MonoRuntime& operator =(MonoRuntime&& other) = delete;

			MonoRuntime(MonoRuntime& other) = delete;
			MonoRuntime(MonoRuntime&& other) = delete;
		};
	}
}