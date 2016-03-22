#include <iostream>
#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>
#include <mono\metadata\mono-config.h>

MonoDomain* domain;

void print(MonoString* str) {
	char* cstr = mono_string_to_utf8(str);

	std::cout << cstr << std::endl;
}

MonoString* getString() {
	MonoString* string = mono_string_new(domain, "THIS IS TEH SRING");

	return string;
}

int main() {
	/*
		TODO: using abs paths just to test this shit.
	*/

	// Set path where managed assemblies live.
	mono_set_assemblies_path("C:\\Users\\Niko\\Source\\Repos\\SaNi\\vs2013\\sanimono\\SaNi\\bin\\Debug");
	// Set Mono library and configuration paths.
	mono_set_dirs("C:\\Program Files (x86)\\Mono\\lib", "C:\\Program Files (x86)\\Mono\\etc");

	// Our application assembly that contains 
	// the code we are going to run.
	domain = mono_jit_init_version("SaNi", "v4.0.30319");
	
	// Our domain in which the code will be 
	// executed.
	MonoAssembly* assembly = mono_domain_assembly_open(domain, "C:\\Users\\Niko\\Source\\Repos\\SaNi\\vs2013\\sanimono\\SaNi\\bin\\Debug\\SaNi.exe");

	if (!assembly) throw std::runtime_error("could not load the given Mono assembly");

	mono_add_internal_call("SaNi.Utils::Print(string)", (void*)print);
	mono_add_internal_call("SaNi.Utils::GetString()", (void*)getString);

	const auto argc = 6;
	char* argv[argc] = { "HELLO", "WORLD", "FROM", "THE", "FUCKING", "MONO" };

	mono_jit_exec(domain, assembly, argc, argv);

	// Clean mono.
	mono_jit_cleanup(domain);

	return 0;
}