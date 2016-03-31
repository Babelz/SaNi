#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/object.hpp"
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#endif
#include "sani/graphics/renderables/particle_emitter.hpp"
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
#include "sani/hid/raw_input_listener.hpp"
#include "sani/rtti/Reflectable.hpp"
#include "sani/rtti/reflection_database.hpp"
using namespace sani::resource;
using namespace sani::engine;
using namespace sani::graphics;
using namespace sani::engine::messages;
using namespace sani::engine::services::renderablemanager;
using namespace sani::engine::services::renderservice;

void initialize(SaNiEngine* const engine);

namespace sandbox {

	void update(SaNiEngine* const engine, const sani::EngineTime& time);
}

#if 1

FileSystem fileSystem;
ResourceManager* resources;
sani::hid::RawInputListener inputListener;

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "sani/core/logging/system_console_logger.hpp"
#include "sani/platform/console.hpp"

#include "sani/core/logging/log_batcher.hpp"
#include "sani/rtti/type_info.hpp"
#include "sani/preprocessor/rtti_runtime.hpp"
#include "sani/preprocessor/rtti.hpp"
#include "sani/rtti/argument.hpp"
class AATest  {
	DECLARE_REFLECTABLE;
private:
	int kek;
	float topKek;
public:
	void setKek(int v) { kek = v; }
	int getKek() const { return kek; }
	float getTopKek() const { return topKek;  }
	AATest(int g) : kek(g), topKek(1337) {}
	void foo() const { std::cout << "AATest::foo()" << std::endl; }
	int square(int x) const { return x*x; }
};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	sani::console::create(720, 600);
	sani::console::show();

	auto& db = sani::rtti::TypeDatabase::getInstance();
	auto& refDb = sani::rtti::ReflectionDatabase::getInstance();
	RTTI_REGISTER_TYPE(AATest);
	sani::rtti::Arguments gg{ 71.f, 55.f, 17.f };
	auto vec = typeof(sani::math::Vec3f).create(gg);
	
	sani::rtti::Type aaType({ sani::rtti::TypeInfo<AATest>::id });
	RTTI_PROPERTY(AATest, kek, int, getKek, setKek);
	RTTI_READONLY_PROPERTY(AATest, topKek, float, getTopKek);
	db.types[aaType.getID()].addMethod("foo", static_cast<void(AATest::*)(void) const>(&AATest::foo), [](sani::rtti::Object& obj, sani::rtti::Arguments& args) {
		return sani::rtti::Object();
	});
	RTTI_DECLARE_BASECLASSES(AATest, typeof(int), typeof(float));
	db.types[aaType.getID()].addMethod("square", static_cast<int(AATest::*)(int) const>(&AATest::square), [](sani::rtti::Object& obj, sani::rtti::Arguments& args) {
		return sani::rtti::Object(obj.getValue<AATest>().square(args[0].getValue<int>()));
	});
	db.types[aaType.getID()].addConstructor<AATest, int>([](sani::rtti::Arguments& args) {
		return AATest(args[0].getValue<int>());

	}, false);
	db.types[aaType.getID()].addConstructor<AATest, int>([](sani::rtti::Arguments& args) {
		return new AATest(args[0].getValue<int>());
	}, true);
	
	auto field = aaType.getField("kek");

	sani::rtti::Arguments args;
	int arg = 5;
	AATest test(0);
	args.emplace_back(arg);
	{
		sani::rtti::Object obj = aaType.create(args);
		const sani::rtti::Method& square = aaType.getMethod("square");
		sani::rtti::Object ret = square.invoke(obj, args);
		assert(ret.getValue<int>() == 25);
		field.setValue(obj, 715517);
		test = obj.getValue<AATest>();
		auto topkek = aaType.getField("topKek");
		assert(topkek.isValid() && topkek.isReadOnly());
	}
	
	assert(test.getKek() == 715517);


	SaNiEngine engine(hInstance);

	engine.onInitialize += initialize;
	engine.onUpdate += sandbox::update;

	engine.start();
	
	return 0;
}

void createText(SpriteFont* font, const String16& text, GraphicsDevice* gd, SaNiEngine* const engine, std::vector<sani::graphics::Rectangle*>& rects) {
	float start = 400;
	float offx = start;
	float offy = 0;
	float spacing = font->lineSpacing;
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
			const float32 w = (float32)rect.w;
			const float32 h = (float32)rect.h;

			const float32 x = offx + glyph.xOffset;
			const float32 y = offy - glyph.yOffset + spacing; //+ font->texture->getHeight();

			sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
			NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

			rectangle->texture = font->texture;
			rectangle->fill = color::Green;
			rectangle->textureSource = sani::math::Rect32f(rect.x, rect.y, rect.w, rect.h);
			recomputeVertices(*rectangle);
			setupShapeForRendering(rectangle, rectangle->borderThickness);

			rectangle->transform.origin.x = 0.0f;
			rectangle->transform.origin.y = 0.0f;

			recomputeVertices(*rectangle);
			updateRenderData(*rectangle);
			useTexturing(rectangle);

			engine->releaseMessage(createRectangleMessage);

			rects.push_back(rectangle);
			offx += glyph.xAdvance;
		}
	}
}

#include "sani/graphics/renderables/text.hpp"
#include "sani/graphics/renderables/particle_emitter.hpp"
sani::graphics::ParticleEmitter* em;

sani::graphics::Circle* c;
Text* tex;

#include "sani/core/memory/memory.hpp"

String16 gg;

void initialize(SaNiEngine* const engine) {

	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice, "../../assets/");
	
	std::vector<sani::graphics::Rectangle*> rects;
	auto erkki = resources->load<Texture2D>("tuksu");
	auto tuksu = erkki;//resources->load<Texture2D>("tuksu");
	auto font = resources->load<SpriteFont>("font");

	for (uint32 i = 1; i < 8; i++) {
		const float32 w = 100.0f;
		const float32 h = 100.0f;

		const float32 x = i * 64.0f + w;
		const float32 y = i * 64.0f + h;
		
		auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
		createElement(createRectangleMessage, ElementType::Rectangle);
		
		engine->routeMessage(createRectangleMessage);

		sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
		NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

		rectangle->texture = resources->load<Texture2D>("tuksu");

		rectangle->fill = color::White;
		/*rectangle->textureSource.x = 0.f;
		rectangle->textureSource.y = 0.f;	
		rectangle->textureSource.w = tuksu->getWidth();
		rectangle->textureSource.h = tuksu->getHeight();*/
		
		recomputeVertices(*rectangle);
		updateRenderData(*rectangle);

		engine->releaseMessage(createRectangleMessage);

		rects.push_back(rectangle);
	}

	using StringConverter =
		std::wstring_convert<std::codecvt_utf8_utf16<char16>, char16, std::allocator<char16>, std::allocator<char8>>;
	

	auto createCircleMessage = engine->createEmptyMessage<DocumentMessage>();
	createElement(createCircleMessage, ElementType::Circle);

	engine->routeMessage(createCircleMessage);

	auto circle = static_cast<sani::graphics::Circle*>(createCircleMessage->getData());
	NEW_DYNAMIC(sani::graphics::Circle, circle, 400, 400, 200, 128);
	
	circle->texture = erkki;
	circle->fill = color::White;
	circle->radius = 200;

	recomputeVertices(*circle);
	updateRenderData(*circle);

	engine->releaseMessage(createCircleMessage);

	c = circle;

	auto getLayersMessage = engine->createEmptyMessage<DocumentMessage>();
	getLayers(getLayersMessage);
	engine->routeMessage(getLayersMessage);

	auto layers = static_cast<std::vector<Layer* const>*>(getLayersMessage->getData());
	auto layer = layers->operator[](0);

	layer->add(circle);

	engine->releaseMessage(getLayersMessage);
	engine->deallocateShared(layers);

	em = new ParticleEmitter(erkki, 1024);
	em->transform.position.x = 1280 / 2.0f;
	em->transform.position.y = 600;
	
	ParticleGenerator& gen = em->generator;

	//gen.flags =
	//	GeneratorFlags::VaryingVelocity |
	//	GeneratorFlags::VaryingDecayTime |
	//	GeneratorFlags::VaryingSpawnLocation |
	//	GeneratorFlags::VaryingAngularVelocity |
	//	GeneratorFlags::VaryingScale |
	//	GeneratorFlags::UseScaleVelocity;

	
	gen.flags |= GeneratorFlags::VaryingVelocity;
	gen.flags |= GeneratorFlags::VaryingDecayTime;
	gen.flags |= GeneratorFlags::VaryingSpawnLocation;
	gen.flags |= GeneratorFlags::VaryingAngularVelocity;
	gen.flags |= GeneratorFlags::VaryingScale;
	gen.flags |= GeneratorFlags::UseScaleVelocity;

	gen.startVelocity = { -0.025f, -0.25f };
	gen.velocityVariance = { 0.025f, 0.25f };

	gen.baseDecayTime = 350.0f;
	gen.decayTimeVariance = 350.0f;

	gen.spawnLocationMinOffset = { -32.0f, 0.0f };
	gen.spawnLocationMaxOffset = { 32.0f, 0.0f };

	gen.baseAngularVelocity = 0.001f;
	gen.angularVelocityVariance = 0.01f;

	gen.baseScale = { 1.0f, 1.0f };
	gen.scaleVariance = { 0.5f, 0.5f };

	gen.baseScaleVelocity = { 0.001f, 0.001f };
	gen.scaleVelocityVariance = { 0.005f, 0.005f };

	gen.framesToFade = 16;
	gen.framesToFadeVariance = 4;

	initializeParticles(*em);

	using StringConverter =
		std::wstring_convert<std::codecvt_utf8_utf16<char16>, char16, std::allocator<char16>, std::allocator<char8>>;


	StringConverter conv;
	gg = conv.from_bytes(/*"\xc3\xa4\xc3\xb6\xc3\xb5\xc3\xb4\xc3\xb0"*/"dank memes w erkki?\ncompiling gentoo\nin da club\nmah datanyms");
	//createText(font, gg, graphicsDevice, engine, rects);

	tex = new Text(font, 1920 / 2, 1080 / 2);
	
	setText(*tex, gg, color::White);
	
	for (sani::graphics::Rectangle* rectangle : rects) layer->add(rectangle);

	layer->add(em);
	layer->add(tex);

	inputListener.init();
}

#include "sani/core/math/trigonometric.hpp"
#include "sani/platform/time/engine_time.hpp"

// Horrible as fuck, can we get something "nicer" 
// any time soon?...
namespace sandbox {

	void update(SaNiEngine* const engine, const sani::EngineTime& time) {
		inputListener.update();
		c->transform.rotation += 0.001f;
		c->textureSource.x = (float32)sani::math::cos(time.getTotalTime()) * 32.0f;
		c->textureSource.y = (float32)sani::math::sin(time.getTotalTime()) * 32.0f;
		c->fill.a = 0.5f;

		recomputeVertices(*c);
		updateRenderData(*c);

		recomputeVertices(*em);
		updateRenderData(*em);
		recomputeBounds(*em);
/*
		recomputeVertices(*a);
		recomputeBounds(*a);
*/

		//tex->transform.scale.x = 0.5f;
		//tex->transform.scale.y = 0.5f;
		/*tex->transform.origin.x = tex->globalBounds.w / 2.0f;
		tex->transform.origin.y = tex->globalBounds.h / 2.0f;
*/
		/*tex->transform.origin.x = 0.0f;
		tex->transform.origin.y = 0.0f;
*/
		sani::graphics::update(*em, time);
		//sani::graphics::update(*a, time);

		recomputeBounds(*tex);
		recomputeVertices(*tex);
		updateRenderData(*tex);
	}
}

#endif