#include "catch/catch.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/platform/file_manager.hpp"

TEST_CASE("File stuff", "[file]") {
	using namespace sani::io;
	FileManager filemanager;

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
		std::vector<unsigned char> out;
		filemanager.getBytes(out, path, 5, fsize - 5);
		CHECK(out.size());
		filemanager.closeFile(path);
	}

	SECTION("File listing") {
		const std::string path("../../tests");
		std::vector<String> files;
		filemanager.listFiles(files, path);
		CHECK(files.size());
	}

}