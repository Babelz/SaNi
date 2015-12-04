#include <Magick++.h>
#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/processor/texture2d_processor.hpp"
#include "sani/resource/pipeline/texture2d_importer.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/compiler/resource_writer.hpp"

#include "sani/resource/resource_manager.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/resource/compiler/resource_compiler.hpp"

static void usage() {
	std::cout << "Insert some help here" << std::endl;
}

int main(int argc, char** argv) {
	using namespace sani::resource;
	using namespace sani::io;
	using namespace sani::resource::compiler;
	if (argc <= 2) {
		std::cout << argv[1] << std::endl;
		usage();
		return 1;
	}

	
	String root(argv[1]);
	String xmlPath(argv[2]);

	ResourceCompiler compiler;
	compiler.readBuildFile(root, xmlPath);
	try {
		compiler.compileAll(root);
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}