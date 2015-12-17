#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

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

using namespace sani::resource;
using namespace sani::graphics;
using namespace sani::engine;
using namespace sani::engine::messages;
using namespace sani::engine::services::renderablemanager;
using namespace sani::engine::services::renderservice;

void initialize(SaNiEngine* const engine);
void update(SaNiEngine* const engine, const sani::EngineTime& time);

//void NO_ENGINE_MAIN(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//	WIN32_ASSERT();
//
//	Window window(hInstance, 1280, 720);
//	window.initialize();
//	window.show();
//
//	WIN32_ASSERT();
//
//	GraphicsDevice graphicsDevice(window.getHandle(), hInstance, 1280, 720);
//	graphicsDevice.initialize();
//
//	Camera2D camera(graphicsDevice.getViewport());
//	camera.computeTransformation();
//	FileSystem fileSystem;
//	ResourceManager resources(&fileSystem, &graphicsDevice);
//	Texture2D* tuksu = resources.load<Texture2D>("../../assets/tuksu.snb");
//	//volatile Effect* effect = resources.load<Effect>("../../assets/polygon.snb");
//
//	window.sizeChanged += SANI_EVENT_HANDLER(void(), ([&window, &graphicsDevice, &camera]() {
//		Viewport viewport;
//
//		viewport.width = window.getClientWidth();
//		viewport.height = window.getClientHeight();
//
//		graphicsDevice.setViewport(viewport);
//
//		graphicsDevice.setBackBufferWidth(viewport.width);
//		graphicsDevice.setBackBufferHeight(viewport.height);
//
//		camera.setViewport(graphicsDevice.getViewport());
//	}));
//
//	Renderer renderer(&graphicsDevice);
//	renderer.initialize();
//
//	std::vector<Triangle> triangles;
//
//	for (uint32 i = 0; i < 3; i++) {
//		for (uint32 j = 0; j < 3; j++) {
//
//			Triangle t(128.0f, 128.0f);
//			t.transform.position.x = j * 256.0f + 128.0f;
//			t.transform.position.y = i * 256.0f + 128.0f;
//
//
//			t.fill = Color(rand() * 0.001f,
//				rand() * 0.0001f,
//				rand() * 0.00001f,
//				0.75f);
//
//			t.borderFill = color::white;
//
//			t.borderThickness = j == 0 ? 16.0f : 0.0f;
//			t.texture = j == 1 ? tuksu : nullptr;
//
//			if (t.texture != nullptr) t.fill = color::white;
//
//			t.textureSource.h = 128.0f;
//			t.textureSource.w = 128.0f;
//
//			t.transform.origin.x = 16.0f;
//			t.transform.origin.y = 0.0f;
//
//			recomputeVertices(t);
//			updateRenderData(t);
//
//			triangles.push_back(t);
//		}
//	}
//
//	std::vector<sani::graphics::Rectangle> rectangles;
//
//	//for (uint32 i = 0; i < 3; i++) {
//	//	for (uint32 j = 0; j < 3; j++) {
//	sani::graphics::Rectangle r(0.0f, 0.0f, tuksu->getWidth(), tuksu->getHeight());
//	//r.borderThickness = 8.0f;
//	r.borderThickness = 16.0f;
//
//	r.transform.origin.x = 0.0f;
//	r.transform.origin.y = 0.0f;
//
//	r.transform.position.x = 300.0f;
//	r.transform.position.y = 100.0f;
//
//	r.texture = tuksu;
//	r.fill = color::white;
//	r.textureSource = Rectf(0.0f, 0.0f, tuksu->getHeight(), tuksu->getWidth());
//
//	recomputeVertices(r);
//	updateRenderData(r);
//
//	rectangles.push_back(r);
//	//	}
//	//}
//
//	std::vector<Circle> circles;
//
//	uint32 verticesCount = 4;
//
//	for (uint32 i = 0; i < 3; i++) {
//		Circle c(700.0f, 100.0f + i * 150.0f, 100.0f, verticesCount);
//
//		c.borderThickness = 12.0f;
//
//		if (i == 1) {
//			c.fill.r = 0.0f;
//			c.fill.g = 0.0f;
//			c.fill.b = 0.0f;
//			c.fill.a = 1.0f;
//		}
//
//		recomputeVertices(c);
//		updateRenderData(c);
//
//		verticesCount += 2;
//
//		circles.push_back(c);
//	}
//
//	while (window.isOpen()) {
//		if (graphicsDevice.hasErrors()) break;
//
//		// Update.
//		window.listen();
//
//		camera.computeTransformation();
//		const sani::math::Mat4f transform = camera.transformation();
//
//		graphicsDevice.clear(0.0f, 0.0f, 0.0f, 1.0f);
//
//		for (Triangle& t : triangles) {
//			t.textureSource.x += 0.1f;
//			t.transform.origin.x = t.localBounds.center().x;
//			t.transform.origin.y = 0.0f;
//			recomputeVertices(t);
//			updateRenderData(t);
//		}
//
//		for (auto& r : rectangles) {
//			recomputeVertices(r);
//			updateRenderData(r);
//		}
//
//		renderer.beginRendering(transform);
//
//		for (sani::graphics::Rectangle& r : rectangles) renderer.renderElement(&r);
////		renderer.renderElement(&rectangles[0]);
//
//		for (Circle& c : circles) renderer.renderElement(&c);
//
//		for (Triangle& t : triangles) renderer.renderElement(&t);
//
//		renderer.endRendering();
//	}
//
//	graphicsDevice.cleanUp();
//}
void ENGINE_MAIN(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SaNiEngine engine(hInstance);

	engine.onInitialize += SANI_EVENT_HANDLER(void(SaNiEngine* const), initialize);
	engine.onUpdate		+= SANI_EVENT_HANDLER(void(SaNiEngine* const, const sani::EngineTime&), update);

	engine.start();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//NO_ENGINE_MAIN(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	
	ENGINE_MAIN(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}

#if _DEBUG

FileSystem fileSystem;
ResourceManager* resources;


void createText(SpriteFont* font, const String& text, GraphicsDevice* gd, SaNiEngine* const engine, std::vector<sani::graphics::Rectangle*>& rects) {
	float offx = 200;
	float offy = 200;
	for (uint32 i = 0; i < text.size(); ++i) {
		unsigned short c = static_cast<unsigned short>(text[i]);
		auto it = std::find_if(font->characters.begin(), font->characters.end(), [c](unsigned short a) {
			return c == a;
		});

		if (it == font->characters.end()) throw std::runtime_error("asd");

		uint32 index = std::distance(font->characters.begin(), it) - 1;
		auto rect = font->glyphs[index];
		auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
		createElement(createRectangleMessage, ElementType::Rectangle);

		engine->routeMessage(createRectangleMessage);

		const float32 w = rect.w * 2;
		const float32 h = rect.h * 2;

		const float32 x = offx;
		const float32 y = offy;

		sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
		SANI_NEW_DYNAMIC(sani::graphics::Rectangle, rectangle,
			x, y, w, h);

		rectangle->texture = font->texture;
		rectangle->fill = color::red;
		rectangle->textureSource = sani::math::Rectf(rect.x, rect.y, rect.h, rect.w);
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

		rectangle->renderData.vertices[0].textureCoordinates.x = s0;
		rectangle->renderData.vertices[0].textureCoordinates.y = t0;

		rectangle->renderData.vertices[1].textureCoordinates.x = s1;
		rectangle->renderData.vertices[1].textureCoordinates.y = t0;

		rectangle->renderData.vertices[2].textureCoordinates.x = s0;
		rectangle->renderData.vertices[2].textureCoordinates.y = t1;

		rectangle->renderData.vertices[3].textureCoordinates.x = s1;
		rectangle->renderData.vertices[3].textureCoordinates.y = t1;

		rectangle->borderFill = color::green;
		rectangle->borderThickness = 64.0f;

		recomputeVertices(*rectangle);
		useTexturing(rectangle);

		engine->releaseMessage(createRectangleMessage);

		rects.push_back(rectangle);
		offx += w;
	}
}


void initialize(SaNiEngine* const engine) {

	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice);
	Texture2D* tuksu = resources->load<Texture2D>("../../assets/tuksu.snb");
	SpriteFont* font = resources->load<SpriteFont>("../../assets/font.snb");

	std::vector<sani::graphics::Rectangle*> rects;
//	font->createStaticText("Pidgin", graphicsDevice); 
	createText(font, "topkekvittusaatana", graphicsDevice, engine, rects);
	/*

	for (uint32 i = 1; i < 8; i++) {
		const float32 w = 64.0f;
		const float32 h = 64.0f;

		const float32 x = i * 64.0f + w;
		const float32 y = i * 64.0f + h;
		
		auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
		createElement(createRectangleMessage, ElementType::Rectangle);
		
		engine->routeMessage(createRectangleMessage);

		sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
		SANI_NEW_DYNAMIC(sani::graphics::Rectangle, rectangle,
						 x, y, w, h);

		rectangle->texture = tuksu;
		rectangle->fill = color::white;
		recomputeVertices(*rectangle);
		updateRenderData(*rectangle);

		engine->releaseMessage(createRectangleMessage);

		rects.push_back(rectangle);
	}
	*/
	auto getLayersMessage = engine->createEmptyMessage<DocumentMessage>();
	getLayers(getLayersMessage);
	engine->routeMessage(getLayersMessage);

	auto layers = static_cast<std::vector<Layer* const>*>(getLayersMessage->getData());
	auto layer = layers->at(0);

	for (sani::graphics::Rectangle* rectangle : rects) layer->add(rectangle);

	engine->releaseMessage(getLayersMessage);
	engine->deallocateShared(layers);
}
void update(SaNiEngine* const engine, const sani::EngineTime& time) {
}
#endif

#endif