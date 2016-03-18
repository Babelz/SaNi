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
    auto& ref = sani::rtti::ReflectionDatabase::getInstance();
	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice, "../../assets/");
	
	auto layer = getDefaultLayer(engine);
	auto siqu = resources->load<Texture2D>("siqu");

	auto drawableSiqu = createDrawableRectangle(engine, 500.f, 300.f, siqu);
	layer->add(drawableSiqu);
	
}

void update(SaNiEngine* const engine, const EngineTime& time) {

}