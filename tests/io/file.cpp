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
	size_t fsize;
	const std::string path("../../tests/test.txt");
	SECTION("File access") {
		CHECK(filemanager.fileExists(path));
		CHECK(filemanager.openFile(path, Filemode::Read | Filemode::Write));
		CHECK(filemanager.openFile(path, Filemode::Read | Filemode::Write));
		CHECK(filemanager.isFileOpen(path));
		CHECK((fsize = filemanager.getFileSize(path)));
	}

	SECTION("File reading") {
		std::vector<unsigned char> out;
		filemanager.getBytes(out, path, 5, fsize - 5);
		CHECK(out.size());
	}

	SECTION("File listing") {
		std::vector<String> files;
		filemanager.listFiles(files, "../../tests");
		CHECK(files.size());
	}

}