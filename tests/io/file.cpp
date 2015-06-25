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
	
	File* file = nullptr;
	const std::string path("../../tests/test.txt");
	REQUIRE(filemanager.fileExists(path));
	REQUIRE(filemanager.openFile(&file, path, Filemode::Read | Filemode::Write));
	REQUIRE(filemanager.openFile(&file, path, Filemode::Read | Filemode::Write));
	REQUIRE(filemanager.isFileOpen(file));
	size_t fsize = filemanager.getFileSize(file);
	REQUIRE(fsize);

	std::string lines = filemanager.getFileDataString(file);
	REQUIRE(lines.size());
	printf("%s\n", lines.c_str());

}