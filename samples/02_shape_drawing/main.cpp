#include <Windows.h>
#include "sani/engine/sani_engine.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/resource/resources.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/layer.hpp"
#include "sani/graphics/renderables/circle.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/rtti/reflection_database.hpp"

using namespace sani;
using namespace sani::engine;
using namespace sani::graphics;
using namespace sani::engine::messages;
using namespace sani::resource;
using namespace sani::engine::services::renderablemanager;
using namespace sani::engine::services::renderservice;

namespace sg = sani::graphics;
namespace se = sani::engine;
namespace ses = sani::engine::services;

void initialize(SaNiEngine* const engine);
void update(SaNiEngine* const engine, const EngineTime& time);

static FileSystem fileSystem;
ResourceManager* resources;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SaNiEngine engine(hInstance);
	engine.onInitialize += initialize;
	engine.onUpdate += update;
	engine.start();
	resources->unload();
	delete resources;
	return 0;
};

sg::Rectangle* createDrawableRectangle(SaNiEngine* const engine, const float x, const float y, Texture2D* texture) {
	auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
	createElement(createRectangleMessage, ElementType::Rectangle);

	engine->routeMessage(createRectangleMessage);

	sg::Rectangle* rectangle = static_cast<sg::Rectangle*>(createRectangleMessage->getData());
	const float w = static_cast<float32>(texture->getWidth());
	const float h = static_cast<float32>(texture->getHeight());
	NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);
	rectangle->fill = color::White;
	rectangle->texture = texture; 
	recomputeVertices(*rectangle);
	updateRenderData(*rectangle);

	engine->releaseMessage(createRectangleMessage);

	return rectangle;
}

sg::Circle* createDrawableCircle(SaNiEngine* const engine, const float x, const float y, Texture2D* texture) {
	auto createCircleMessage = engine->createEmptyMessage<DocumentMessage>();
	createElement(createCircleMessage, ElementType::Circle);

	engine->routeMessage(createCircleMessage);

	auto circle = static_cast<sani::graphics::Circle*>(createCircleMessage->getData());
	NEW_DYNAMIC(sani::graphics::Circle, circle, x, y, 200, 128);

	circle->texture = texture;
	circle->fill = color::White;
	
	recomputeVertices(*circle);
	updateRenderData(*circle);

	engine->releaseMessage(createCircleMessage);

	return circle;
}

sg::Triangle* createDrawableTriangle(SaNiEngine* const engine, const float x, const float y, Texture2D* texture) {
	auto createTriangleMessage = engine->createEmptyMessage<DocumentMessage>();
	createElement(createTriangleMessage, ElementType::Triangle);

	engine->routeMessage(createTriangleMessage);

	auto triangle = static_cast<sg::Triangle*>(createTriangleMessage->getData());
	NEW_DYNAMIC(sg::Triangle, triangle, x, y, 200, 200);
	triangle->texture = texture;
	triangle->fill = color::White;
	recomputeVertices(*triangle);
	updateRenderData(*triangle);

	engine->releaseMessage(createTriangleMessage);
	return triangle;
}

sg::Layer* getDefaultLayer(SaNiEngine* const engine) {
	auto getLayersMessage = engine->createEmptyMessage<DocumentMessage>();
	ses::renderservice::getLayers(getLayersMessage);
	engine->routeMessage(getLayersMessage);

	auto layers = static_cast<std::vector<Layer* const>*>(getLayersMessage->getData());
	auto layer = layers->operator[](0);

	engine->releaseMessage(getLayersMessage);
	engine->deallocateShared(layers);

	return layer;
}

void initialize(SaNiEngine* const engine) {
    auto& refdb = sani::rtti::ReflectionDatabase::getInstance();
	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice, engine, String8("../../assets/"));
	
	auto layer = getDefaultLayer(engine);
	auto siqu = resources->load<Texture2D>("siqu");
	auto andy = resources->load<Texture2D>("andy");
	auto dt = resources->load<Texture2D>("ourcore");

	auto drawableSiqu = createDrawableRectangle(engine, siqu->getWidth()/2.f, 300.f, siqu);
	auto drawableAndy = createDrawableCircle(engine, 800.f, 300.f, andy);
	auto drawableDt = createDrawableTriangle(engine, 200, 400, dt);
	
	layer->add(drawableSiqu);
	layer->add(drawableAndy);
	layer->add(drawableDt);
}

void update(SaNiEngine* const engine, const EngineTime& time) {

}