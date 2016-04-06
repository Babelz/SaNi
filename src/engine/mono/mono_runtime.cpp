#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_provider.hpp"

#include <mono\metadata\mono-config.h>

#include <sys\types.h>
#include <sys\stat.h>
#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>
#include <mono\metadata\appdomain.h>

#include "sani\core\logging\log.hpp"

namespace sani {

	namespace engine {

		const String MonoAssembliesPath = "\\mono";
		const String MonoLibrariesPath	= "C:\\Program Files (x86)\\Mono\\lib";
		const String MonoConfigPath		= "C:\\Program Files (x86)\\Mono\\etc";
		const String MonoVersion		= "v4.0.30319";
		const String MonoRootDomainName = "SaNi";
		const String MonoAssemblyName	= "\\mono\\sani managed.dll";

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

		bool MonoRuntime::dirExists(const String& dir) const {
			const char* cstr = dir.c_str();
			
			struct stat info;

			if		(stat(cstr, &info) != 0)	return false;
			else if (info.st_mode & S_IFDIR)	return true;
			else								return false;
		}

		bool MonoRuntime::monoLibrariesDirExists() const {
			return dirExists(MonoLibrariesPath);
		}
		bool MonoRuntime::monoConfigDirExists() const {
			return dirExists(MonoConfigPath);
		}
		bool MonoRuntime::assembliesDirExists() const {
			return dirExists(MonoAssembliesPath);
		}

		bool MonoRuntime::initializeRuntime() {
			mono_set_assemblies_path(MonoAssembliesPath.c_str());
			mono_set_dirs(MonoLibrariesPath.c_str(), MonoConfigPath.c_str());

			monoDomain = mono_jit_init_version(MonoRootDomainName.c_str(), MonoVersion.c_str());
			
			monoAssembly = mono_domain_assembly_open(monoDomain, MonoAssemblyName.c_str());

			if (monoAssembly == nullptr) {
				RLOG_ERR(log::OutFlags::All, "MonoRuntime", "could not load sani managed.dll");

				return false;
			}

			monoProvider = new MonoProvider(monoAssembly, monoDomain);

			return true;
		}
		void MonoRuntime::logErrors(std::vector<String>& errors) const {
			for (const auto& str : errors) RLOG_ERR(log::OutFlags::All, "MonoRuntime", str);
		}

		bool MonoRuntime::start() {
			std::vector<String> errors;

			if (!monoLibrariesDirExists()) errors.push_back("Mono libraries dir not found, is Mono installed?"); 

			if (!monoConfigDirExists()) errors.push_back("Mono config dir not found, is Mono installed?");

			if (!assembliesDirExists()) errors.push_back("Mono assemblies dir not found");

			if (errors.empty()) return initializeRuntime();
			else					   logErrors(errors);

			return false;
		}

		void MonoRuntime::shutdown() {
			mono_jit_cleanup(monoDomain);
			mono_assembly_close(monoAssembly);

			delete monoProvider;
		}
	}
}