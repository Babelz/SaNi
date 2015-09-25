#pragma once
#include "sani/platform/binary_writer.hpp"
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
namespace sani {
	namespace resource {
		namespace compiler {
			class ResourceWriter : io::BinaryWriter {
				// TODO add functions to write matrices vectors and stuff
			};
		}
	}
}