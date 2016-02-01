#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#endif
using String16 = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;
using String8 = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
#include "sani/core/memory/memory.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/color.hpp"
#include "sani/graphics/layer.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/debug.hpp"
#include "sani/graphics/camera2d.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/vertex_position_color.hpp"
#include "sani/core/math/vector.hpp"
#include "sani/core/func.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include <random>

#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/resource/resources.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/effect.hpp"
#include "sani/core/math/trigonometric.hpp"

#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderables/circle.hpp"

#include "sani/engine/sani_engine.hpp"

#include "sani/platform/time/engine_time.hpp"

#include "sani/engine/messaging/messages/document_message.hpp"

#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/resource/sprite_font.hpp"
#include "sani/resource/spritefont_content.hpp"
#include <xlocbuf>

using namespace sani::resource;
using namespace sani::graphics;
using namespace sani::engine;
using namespace sani::engine::messages;
using namespace sani::engine::services::renderablemanager;
using namespace sani::engine::services::renderservice;

void initialize(SaNiEngine* const engine);
void update(SaNiEngine* const engine, const sani::EngineTime& time);

#if _DEBUG

FileSystem fileSystem;
ResourceManager* resources;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SaNiEngine engine(hInstance);
	engine.onInitialize += initialize;
	engine.onUpdate += update;

	engine.start();
	
	return 0;
}

void createText(SpriteFont* font, const String16& text, GraphicsDevice* gd, SaNiEngine* const engine, std::vector<sani::graphics::Rectangle*>& rects) {
	float start = 400;
	float offx = start;
	float offy = 0;
	float spacing = font->texture->getHeight();
	for (uint32 i = 0; i < text.size(); ++i) {
		uint32 c = static_cast<uint32>((text[i]));

		switch (c) {
		case '\r':
			continue;
		case '\n':
			offx = start;
			offy += spacing;
			continue;
		default:

			auto it = std::find_if(font->characters.begin(), font->characters.end(), [c](uint32 a) {
				return c == a;
			});


			if (it == font->characters.end()) throw std::runtime_error("asd");

			uint32 index = std::distance(font->characters.begin(), it) - 0;
			GlyphContent& glyph = font->glyphs[index];

			auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
			createElement(createRectangleMessage, ElementType::Rectangle);

			engine->routeMessage(createRectangleMessage);

			auto& rect = glyph.source;
			const uint32 w = rect.w;
			const uint32 h = rect.h;

			const float32 x = offx + glyph.xOffset;
			const float32 y = offy - glyph.yOffset + font->texture->getHeight();

			sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
			NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

			rectangle->texture = font->texture;
			rectangle->fill = color::red;
			rectangle->textureSource = sani::math::Rect32f(rect.x, rect.y, rect.w, rect.h);
			recomputeVertices(*rectangle);
			setupShapeForRendering(rectangle, rectangle->borderThickness);
			// top left x
			float s0 = rect.x / (float)font->texture->getWidth();
			// top left y
			float t0 = rect.y / (float)font->texture->getHeight();
			// bottom right x
			float s1 = (rect.x + rect.w) / (float)font->texture->getWidth();
			// bottom right y
			float t1 = (rect.y + rect.h) / (float)font->texture->getHeight();

			rectangle->renderData.vertices[0].vertexPositionColor = VertexPositionColor{ sani::math::Vec3f(x, y, 0.f), Color(1.f, 0.33f, 0.33f, 1.f) };
			rectangle->renderData.vertices[0].textureCoordinates.x = s0;
			rectangle->renderData.vertices[0].textureCoordinates.y = t1;

			rectangle->renderData.vertices[1].vertexPositionColor = VertexPositionColor{ sani::math::Vec3f(x + w, y, 0.f), Color(0.93f, 0.0f, 0.0f, 1.f) };
			rectangle->renderData.vertices[1].textureCoordinates.x = s1;
			rectangle->renderData.vertices[1].textureCoordinates.y = t1;

			rectangle->renderData.vertices[2].vertexPositionColor = VertexPositionColor{ sani::math::Vec3f(x, y + h, 0.f), Color(0.86f, 0.0f, 0.0f, 1.f) };
			rectangle->renderData.vertices[2].textureCoordinates.x = s0;
			rectangle->renderData.vertices[2].textureCoordinates.y = t0;

			rectangle->renderData.vertices[3].vertexPositionColor = VertexPositionColor{ sani::math::Vec3f(x + w, y + h, 0.f), Color(1.f, 0.33f, 0.33f, 1.f) };
			rectangle->renderData.vertices[3].textureCoordinates.x = s1;
			rectangle->renderData.vertices[3].textureCoordinates.y = t0;


		//	recomputeVertices(*rectangle);
		//	updateRenderData(*rectangle);
			useTexturing(rectangle);

			engine->releaseMessage(createRectangleMessage);

			rects.push_back(rectangle);
			offx += glyph.xAdvance;
		}
		
	}
}

sani::graphics::Circle* c;

void initialize(SaNiEngine* const engine) {

	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice);
	
	std::vector<sani::graphics::Rectangle*> rects;
	auto tuksu = resources->load<Texture2D>("../../assets/tuksu.snb");
	volatile auto font = resources->load<SpriteFont>("../../assets/font.snb");

	//for (uint32 i = 1; i < 8; i++) {
	//	const float32 w = 64.0f;
	//	const float32 h = 64.0f;

	//	const float32 x = i * 64.0f + w;
	//	const float32 y = i * 64.0f + h;
	//	
	//	auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
	//	createElement(createRectangleMessage, ElementType::Rectangle);
	//	
	//	engine->routeMessage(createRectangleMessage);

	//	sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
	//	NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

	//	rectangle->texture = tuksu;

	//	rectangle->fill = color::white;
	//	recomputeVertices(*rectangle);
	//	updateRenderData(*rectangle);

	//	engine->releaseMessage(createRectangleMessage);

	//	rects.push_back(rectangle);
	//}

	using StringConverter =
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t, std::allocator<wchar_t>, std::allocator<char>>;
	

	StringConverter conv;
	String16 gg = conv.from_bytes("\xc3\xa4\xc3\xb6\xc3\xb5\xc3\xb4\xc3\xb0");
	createText(font, gg, graphicsDevice, engine, rects);

	auto createCircleMessage = engine->createEmptyMessage<DocumentMessage>();
	createElement(createCircleMessage, ElementType::Circle);

	engine->routeMessage(createCircleMessage);

	auto circle = static_cast<sani::graphics::Circle*>(createCircleMessage->getData());
	NEW_DYNAMIC(sani::graphics::Circle, circle, 200, 200, 100, 128);
	
	circle->texture = tuksu;
	circle->fill = color::white;
	circle->textureSource.w = static_cast<float32>(tuksu->getWidth());
	circle->textureSource.h = static_cast<float32>(tuksu->getHeight());

	recomputeVertices(*circle);
	updateRenderData(*circle);

	engine->releaseMessage(createCircleMessage);

	c = circle;

	auto getLayersMessage = engine->createEmptyMessage<DocumentMessage>();
	getLayers(getLayersMessage);
	engine->routeMessage(getLayersMessage);

	auto layers = static_cast<std::vector<Layer* const>*>(getLayersMessage->getData());
	auto layer = layers->operator[](0);

	for (sani::graphics::Rectangle* rectangle : rects) layer->add(rectangle);
	layer->add(circle);

	engine->releaseMessage(getLayersMessage);
	engine->deallocateShared(layers);
}

#include "sani/core/math/trigonometric.hpp"

void update(SaNiEngine* const engine, const sani::EngineTime& time) {
	recomputeVertices(*c);
	updateRenderData(*c);
}

#endif