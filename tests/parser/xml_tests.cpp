#include "catch/catch.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/core/parser/xml_parser.hpp"

using namespace sani::io;
using namespace sani::parser;
FileSystem fileSystem;
const std::string Path("../../assets/test_xml.xml");
FileStream* stream;
TEST_CASE("XML parsing", "[xml]") {
	XmlDocument doc;
	XmlNode node;
	std::vector<XmlNode> childs;
	SECTION("Loading") {
		REQUIRE(fileSystem.openFile(Path, Filemode::Read, &stream));
		doc.load(stream);
		CHECK(doc.firstNode(node));
		CHECK(!doc.firstNode("field", node));
		CHECK(node.hasAttributes() == false);

		CHECK(node.hasChilds());
		CHECK(node.getChildNodes(childs));
		
	}

	fileSystem.closeFile(Path);
}