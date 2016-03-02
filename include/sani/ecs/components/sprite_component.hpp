#pragma once

#include "sani/ecs/component.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, Sprite);

namespace sani {

	class SpriteComponent final : public Component {
	public:
		graphics::Sprite* sprite { nullptr };

		SpriteComponent()	= default;
		
		~SpriteComponent()	= default;
	};
}