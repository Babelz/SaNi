#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#endif

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

	for (uint32 i = 1; i < 8; i++) {
		const float32 w = 64.0f;
		const float32 h = 64.0f;

		const float32 x = i * 64.0f + w;
		const float32 y = i * 64.0f + h;
		
		auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
		createElement(createRectangleMessage, ElementType::Rectangle);
		
		engine->routeMessage(createRectangleMessage);

		sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
		NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

		rectangle->texture = tuksu;

		rectangle->fill = color::white;
		recomputeVertices(*rectangle);
		updateRenderData(*rectangle);

		engine->releaseMessage(createRectangleMessage);

		rects.push_back(rectangle);
	}

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
	auto layer = layers->at(0);

	for (sani::graphics::Rectangle* rectangle : rects) layer->add(rectangle);
	layer->add(circle);

	engine->releaseMessage(getLayersMessage);
	engine->deallocateShared(layers);
}
void update(SaNiEngine* const engine, const sani::EngineTime& time) {
	c->transform.rotation += 0.01f;
	recomputeVertices(*c);
	updateRenderData(*c);
}

#endif