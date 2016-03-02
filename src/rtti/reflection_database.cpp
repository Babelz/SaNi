#include "sani/rtti/reflection_database.hpp"
#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/spritefont_reader.hpp"
#include "sani/resource/reader/scene_reader.hpp"
#include "sani/resource/reader/bitmap_content_reader.hpp"
#include "sani/resource/reader/effect_reader.hpp"
#include "sani/core/math/math.hpp"
#include "sani/ecs/components/transform_component.hpp"

namespace sani {
	namespace rtti {

		ReflectionDatabase::ReflectionDatabase() {
			registerReflection<sani::resource::reader::Texture2DReader>();
			registerReflection<sani::resource::reader::SpriteFontReader>();
			registerReflection<sani::resource::reader::SceneReader>();
			registerReflection<sani::resource::reader::BitmapContentReader>();
			registerReflection<sani::resource::reader::EffectReader>();
			registerReflection<sani::math::Vec2f>();
			registerReflection<sani::math::Vec2d>();
			//registerReflection<sani::math::Vec2u>();
			registerReflection<sani::math::Vec2i>();
			registerReflection<sani::math::Vec3f>();
			registerReflection<sani::math::Vec3d>();
			//registerReflection<sani::math::Vec3u>();
			registerReflection<sani::math::Vec3i>();
			registerReflection<sani::math::Vec4f>();
			registerReflection<sani::math::Vec4d>();
			//registerReflection<sani::math::Vec4u>();
			registerReflection<sani::math::Vec4i>();


			// ecs
			registerReflection<sani::Transform>();
		}

	}
}



