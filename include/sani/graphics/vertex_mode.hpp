#pragma once	

namespace sani {

	namespace graphics {

		/// Defines how the vertices should used.
		enum class VertexMode {
			// Vertices are drawn without indexing.
			NoIndexing,
			// Vertices are drawn using indexing. 
			Indexed
		};
	}
}