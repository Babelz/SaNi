#include "catch/catch.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/platform/file_manager.hpp"

TEST_CASE("File stuff", "[file]") {
	using namespace sani::io;
	FileManager filemanager;

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
	REQUIRE(filemanager.isAbsolutePath("C:\\jeesus"));
	REQUIRE(!filemanager.isAbsolutePath("relative\\path"));
	REQUIRE(!filemanager.isAbsolutePath("relative/path"));
	REQUIRE(filemanager.isAbsolutePath("C:/abs/path"));
#else
	REQUIRE(filemanager.isAbsolutePath("/dev/null"));
	REQUIRE(!filemanager.isAbsolutePath("test123/sss"));
#endif
	
	const std::string path("../../tests/test.txt");
	REQUIRE(filemanager.fileExists(path));
	REQUIRE(filemanager.openFile(path, Filemode::Read | Filemode::Write));
	REQUIRE(filemanager.openFile(path, Filemode::Read | Filemode::Write));
	REQUIRE(filemanager.isFileOpen(path));
	size_t fsize = filemanager.getFileSize(path);
	REQUIRE(fsize);
	std::vector<unsigned char> out;
	filemanager.getBytes(out, path, 5, fsize - 5);
	REQUIRE(out.size());
	printf("fropm file %s\n", out.data());
	std::vector<String> files;
	filemanager.listFiles(files, "../../tests");
	printf("file count %d\n", files.size());
	REQUIRE(files.size());

}