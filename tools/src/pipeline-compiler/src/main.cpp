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

	ResourceCompiler compiler;
	String root(argv[1]);
	processor::Texture2DProcessor proc;
	pipeline::Texture2DImporter importer;
	try {
		size_t i = 2;
		while (argc-- > 2) {
			compiler.compile(root, argv[i++]);
		}
		
		/*
		Texture2DContent* content = importer.import(filePath, &fs);
		content = proc.process(content);

		namespace sc = sani::resource::compiler;
		FileStream* file = nullptr;

		if (!fs.openFile(outpath, Filemode::Truncate, &file)) {
			std::cerr << "Cant open file " << filePath << std::endl;
			return 1;
		}

		sc::ResourceWriter* writer = new sc::ResourceWriter(file);
		
		writer->writeHeader();
		compiler::Texture2DWriter* textureWriter = new compiler::Texture2DWriter();
		//compiler::Texture2DWriter* textureWriter = static_cast<compiler::Texture2DWriter*>(writer->getWriter<Texture2D>());
		textureWriter->write(writer, content);
		file->flush();
		fs.closeFile(outpath);
		*/
/*		//// READING

		if (!fs.openFile(outpath, Filemode::Read, &file)) {
			throw std::runtime_error("File opening failed!");
		}

		Window*	window = new Window(GetModuleHandle(NULL), 800, 600);
		window->initialize();
		GraphicsDevice* gdevice = new GraphicsDevice(window->getHandle(), GetModuleHandle(NULL), 800, 600);
		gdevice->initialize();
		ResourceManager manager(&fs, gdevice);
		//reader::ResourceReader* reader = new reader::ResourceReader(file, manager, gdevice);
		Texture2D* texture = static_cast<Texture2D*>(manager.load(outpath));*/
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}