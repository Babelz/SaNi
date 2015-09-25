#include "sani/resource/resource_type_reader_manager.hpp"
#include "sani/resource/resource_type_reader.hpp"
#include "sani/resource/primitive_readers.hpp"
namespace sani {
	namespace resource {
		ResoureTypeReaderManager::~ResoureTypeReaderManager() {
			for (size_t i = 0; i < typeReaders.size(); ++i) {
				delete typeReaders[i];
			}
		}

		void ResoureTypeReaderManager::registerStandardTypes() {
			registerTypeReader<Uint8Reader>();
			registerTypeReader<Uint16Reader>();
			registerTypeReader<Uint32Reader>();
			registerTypeReader<Uint64Reader>();

			registerTypeReader<Int8Reader>();
			registerTypeReader<Int16Reader>();
			registerTypeReader<Int32Reader>();
			registerTypeReader<Int64Reader>();
			
			registerTypeReader<SingleReader>();
			registerTypeReader<DoubleReader>();

			registerTypeReader<CharReader>();
			registerTypeReader<StringReader>();

			registerTypeReader<ByteReader>();
		}
	}
}