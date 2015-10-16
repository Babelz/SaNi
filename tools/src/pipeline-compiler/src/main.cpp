#include <Magick++.h>
#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/processor/texture2d_processor.hpp"
#include "sani/resource/pipeline/texture2d_importer.hpp"
#include "sani/platform/file/file_system.hpp"
int main(int argc, char** argv) {
	using namespace sani::resource;
	using namespace sani::io;
	FileSystem fs;
	compiler::Texture2DWriter writer;
	processor::Texture2DProcessor proc;
	pipeline::Texture2DImporter importer;
	Texture2DContent* content = importer.import("../../../assets/tuksu.png", &fs);
	proc.process(content);
	return 0;
}