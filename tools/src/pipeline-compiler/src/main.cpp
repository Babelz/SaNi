#include <Magick++.h>
#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/processor/texture2d_processor.hpp"
#include "sani/resource/pipeline/texture2d_importer.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
int main(int argc, char** argv) {
	using namespace sani::resource;
	using namespace sani::io;
	FileSystem fs;
	processor::Texture2DProcessor proc;
	pipeline::Texture2DImporter importer;
	Texture2DContent* content = importer.import("../../../assets/tuksu.png", &fs);
	content = proc.process(content);

	namespace sc = sani::resource::compiler;
	FileStream* file = nullptr;

	const String outpath("binary.out");

	if (!fs.openFile(outpath, Filemode::Truncate, &file)) {
		throw std::runtime_error("File opening failed!");
	}


	sc::ResourceWriter* writer = new sc::ResourceWriter(file);
	writer->writeHeader();
	compiler::Texture2DWriter textureWriter;
	textureWriter.write(writer, content);
	file->flush();
	fs.closeFile(outpath);
	return 0;
}