#include "sani/resource/sprite_font.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {
	namespace resource {

		SpriteFont::SpriteFont(Texture2D* texture, const Glyphs& glyphs, const Characters& characters) 
			: texture(texture), glyphs(glyphs), characters(characters) {

		}

		SpriteFont::~SpriteFont() {

		}

		void SpriteFont::createStaticText(const String& text, graphics::GraphicsDevice* device)
		{
			GLuint fbo;
			GLuint textureBuffer, colorbuf, depthbuf;
			glGenTextures(1, &textureBuffer);
			glBindTexture(GL_TEXTURE_2D, textureBuffer);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				800,
				600,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				nullptr
				);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			device->generateRenderTarget2D(textureBuffer, colorbuf, fbo, depthbuf, 0, 0);
			
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				throw std::runtime_error("asd");
			}

			
		//	glBindTexture(GL_TEXTURE_2D, 0);


		}

	}
}