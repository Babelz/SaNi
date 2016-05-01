#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_provider.hpp"
#include "sani/platform/file/file_system_utils.hpp"

#include <mono/metadata/mono-config.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/appdomain.h>
#include <mono/utils/mono-error.h>

#include "sani/core/logging/log.hpp"

#include "sani/core/utils/string_utils.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			const char* const MonoVersion = "v4.0.30319";
			const char* const MonoRootDomainName = "SaNi";

			MonoRuntime::MonoRuntime() : monoProvider(nullptr),
				monoAssembly(nullptr),
				monoDomain(nullptr) {
			}

			MonoRuntime::~MonoRuntime() {
			}


			MonoRuntime& MonoRuntime::instance() {
				static MonoRuntime runtime;

				return runtime;
			}

			MonoProvider* const MonoRuntime::provider() {
				return monoProvider;
			}

			MonoDomain* MonoRuntime::domain() {
				return monoDomain;
			}

			bool MonoRuntime::monoLibrariesDirExists() const {
				return io::directoryExists(monoLibrariesPath);
			}
			bool MonoRuntime::monoConfigDirExists() const {
				return io::directoryExists(monoConfigPath);
			}
			bool MonoRuntime::assembliesDirExists() const {
				return io::directoryExists(monoAssembliesPath);
			}

			bool MonoRuntime::initializeRuntime() {
				mono_set_assemblies_path(monoAssembliesPath.c_str());
				mono_set_dirs(monoLibrariesPath.c_str(), monoConfigPath.c_str());
				mono_config_parse(NULL);

				monoDomain = mono_jit_init_version(MonoRootDomainName, MonoVersion);
				std::vector<MonoAssembly*> assemblies;

				// Load dependencies (base lib + others).
				std::vector<String> dllNames;
				utils::split(monoDependencies, ",", dllNames, true);

				for (const auto& dll : dllNames) assemblies.push_back(mono_domain_assembly_open(monoDomain, String(monoAssembliesPath + "\\" + dll).c_str()));

				// Load user assembly (game specific code).
				monoAssembly = mono_domain_assembly_open(monoDomain, String(monoAssembliesPath + "\\" + monoAssemblyName).c_str());
				assemblies.push_back(monoAssembly);

				if (monoAssembly == nullptr) {
					RLOG_ERR(log::OutFlags::All, "MonoRuntime", "could not load sani managed .dll");

					return false;
				}

				monoProvider = new MonoProvider(assemblies);

				return true;
			}
			void MonoRuntime::logErrors(std::vector<String>& errors) const {
				for (const auto& str : errors) RLOG_ERR(log::OutFlags::All, "MonoRuntime", str);
			}

			bool MonoRuntime::start(const String& monoAssembliesPath, const String& monoLibrariesPath, const String& monoConfigPath, const String& monoAssemblyName, const String& monoDependencies) {
				String root;
				io::rootDirectory(root);

				this->monoAssembliesPath = root + monoAssembliesPath;
				this->monoLibrariesPath = monoLibrariesPath;
				this->monoConfigPath = monoConfigPath;
				this->monoAssemblyName = monoAssemblyName;
				this->monoDependencies = monoDependencies;

				if (monoAssembliesPath.empty()) { FNCLOG_ERR(log::OutFlags::All, "assemblies path can't be empty"); return false; }
				if (monoLibrariesPath.empty())	{ FNCLOG_ERR(log::OutFlags::All, "libraries path can't be empty"); return false; }
				if (monoConfigPath.empty())		{ FNCLOG_ERR(log::OutFlags::All, "config path can't be empty"); return false; }
				if (monoAssemblyName.empty())   { FNCLOG_ERR(log::OutFlags::All, "assembly name can't be empty"); return false; }

				std::vector<String> errors;

				if (!monoLibrariesDirExists()) errors.push_back("Mono libraries dir not found, is Mono installed?");

				if (!monoConfigDirExists()) errors.push_back("Mono config dir not found, is Mono installed?");

				if (!assembliesDirExists()) errors.push_back("Mono assemblies dir not found");

				if (errors.empty())	return initializeRuntime();
				else				logErrors(errors);

				return false;
			}

			void MonoRuntime::shutdown() {
				mono_jit_cleanup(monoDomain);

				delete monoProvider;
			}
		}
	}
}