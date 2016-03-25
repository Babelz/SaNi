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
#include "sani/resource/scene.hpp"
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

void initialize(SaNiEngine* const engine) {
	auto& db = sani::rtti::ReflectionDatabase::getInstance();
	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice, engine, String8("../../assets/"));
	
	auto scene = resources->load<Scene>("helloworldjson");
	scene->initialize();
}

void update(SaNiEngine* const engine, const EngineTime& time) {

}