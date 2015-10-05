#include "catch/catch.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/binary_reader.hpp"
#include "sani/platform/file/binary_writer.hpp"

TEST_CASE("File stuff", "[file]") {
	using namespace sani::io;

	FileSystem filemanager;

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
	SECTION("Absolute paths") {
		CHECK(filemanager.isAbsolutePath("C:\\jeesus"));
		CHECK(!filemanager.isAbsolutePath("relative\\path"));
		CHECK(!filemanager.isAbsolutePath("relative/path"));
		CHECK(filemanager.isAbsolutePath("C:/abs/path"));
	}
#else
	SECTION("Absolute paths") {
		CHECK(filemanager.isAbsolutePath("/dev/null"));
		CHECK(!filemanager.isAbsolutePath("test123/sss"));
	}
#endif

	
	SECTION("File access") {
		const std::string path("../../tests/test.txt");
		CHECK(filemanager.fileExists(path));
		CHECK(filemanager.openFile(path, Filemode::Read | Filemode::Write));
		CHECK(filemanager.openFile(path, Filemode::Read | Filemode::Write));
		CHECK(filemanager.isFileOpen(path));
		CHECK(filemanager.getFileSize(path));
		filemanager.closeFile(path);
	}

	SECTION("File reading") {
		const std::string path("../../tests/test.txt");
		size_t fsize = filemanager.getFileSize(path);
		CHECK(filemanager.openFile(path, Filemode::Read | Filemode::Write));
		CHECK(filemanager.getFileDataString(path).size());
		filemanager.closeFile(path);
	}

	SECTION("File listing") {
		const std::string path("../../tests");
		std::vector<String> files;
		filemanager.listFiles(files, path);
		CHECK(files.size());
	}
	
	SECTION("Binary writing") {
		const std::string path("../../tests/teststring.bin");
		CHECK(filemanager.openFile(path, Filemode::Read | Filemode::Write));
		BinaryWriter writer;
		filemanager.getBinaryWriter(path, &writer);
		//writer.write7BitEncodedInt(uint32(1337));
		//writer.write(uint32(1337));
		writer.write("Jeesuksen perse");
		filemanager.closeFile(path);
	}
	
	SECTION("Binary reading") {
		const std::string path("../../tests/teststring.bin");
		CHECK(filemanager.openFile(path, Filemode::Read));
		BinaryReader reader;
		filemanager.getBinaryReader(path, &reader);
		//uint64 byte = reader.readUint64();
		//uint64 byte2 = reader.readUint64();
		//CHECK(byte == uint64(1337));
		//CHECK(byte2 == uint64(715517));
		String gg(reader.readString());
		CHECK(gg == "Jeesuksen perse");
		filemanager.closeFile(path);
	}
}