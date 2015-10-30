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

static void usage() {
	std::cout << "Insert some help here" << std::endl;
}

int main(int argc, char** argv) {
	using namespace sani::resource;
	using namespace sani::io;

	if (argc <= 1) {
		usage();
		return 1;
	}

	// TODO multiple files
	String filePath(argv[1]);
	String filename(argv[1]);
	String outExtension(".out");

	size_t index = 0;
	if ((index = filePath.rfind(".")) != String::npos) {
		filename = (filename.substr(0, index));
	}

	const String outpath(filename + outExtension);

	FileSystem fs;
	processor::Texture2DProcessor proc;
	pipeline::Texture2DImporter importer;
	try {

		std::cout << "Trying to open file " << filePath << std::endl;
		if (!fs.fileExists(filePath)) {
			std::cerr << filePath << " does not exist!" << std::endl;
			return 1;
		}

		std::cout << "Importing file " << filePath << std::endl;
		// ../../../assets/tuksu.png
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
		compiler::Texture2DWriter textureWriter;
		textureWriter.write(writer, content);
		file->flush();
		fs.closeFile(outpath);

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