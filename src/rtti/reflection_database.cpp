#include "sani/rtti/reflection_database.hpp"
#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/spritefont_reader.hpp"
#include "sani/resource/reader/scene_reader.hpp"
#include "sani/resource/reader/bitmap_content_reader.hpp"
#include "sani/resource/reader/effect_reader.hpp"

namespace sani {
	namespace rtti {

		ReflectionDatabase::ReflectionDatabase() {
			registerReflection<sani::resource::reader::Texture2DReader>();
			registerReflection<sani::resource::reader::SpriteFontReader>();
			registerReflection<sani::resource::reader::SceneReader>();
			registerReflection<sani::resource::reader::BitmapContentReader>();
			registerReflection<sani::resource::reader::EffectReader>();
		}

	}
}



