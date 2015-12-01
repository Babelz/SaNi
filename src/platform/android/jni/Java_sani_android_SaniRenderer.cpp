#include <jni.h>
#include <GLES2/gl2.h>
#include <sani/platform/graphics/graphics_device.hpp>
#include <android/log.h>
#include "sani/platform/graphics/viewport.hpp"
#include "sani/resource/resource_manager.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/camera2d.hpp"
// TODO test
#define  LOG_TAG    "SaniRenderer"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

sani::resource::Texture2D* texture;
sani::graphics::Renderer* renderer;
sani::graphics::Rectangle* rect;
sani::graphics::Camera2D* camera;
extern "C" {

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeInit(JNIEnv* env, jclass clazz, jint surfaceWidth, jint surfaceHeight, jlong graphicsDevicePtr) {
		using namespace sani::graphics;
		GraphicsDevice* device = reinterpret_cast<GraphicsDevice*>(graphicsDevicePtr);
		if (!device) {
			LOGE("Graphics device is null in C++!");
		}
		device->setBackBufferWidth(surfaceWidth);
		device->setBackBufferHeight(surfaceHeight);
		device->setViewport(Viewport( 0u, 0u, surfaceWidth, surfaceHeight) );
		renderer = new Renderer(*device);
		renderer->initialize();
		auto v = Viewport(0u, 0u, surfaceWidth, surfaceHeight);
		camera = new Camera2D(v);
		camera->computeTransformation();
	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeOnSurfaceChanged(JNIEnv* env, jclass clazz, jint surfaceWidth, jint surfaceHeight) {

	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeRender(JNIEnv* env, jclass clazz, jlong graphicsDevicePtr) {
		using namespace sani::graphics;
		GraphicsDevice* device = reinterpret_cast<GraphicsDevice*>(graphicsDevicePtr);
		device->clear(1.f, 0.f, 0.f, 1.f);

		camera->computeTransformation();
		const sani::math::Mat4f transform = camera->transformation();

		renderer->beginRendering(transform);
		renderer->renderElement(rect);
		renderer->endRendering();
	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_testLoading(JNIEnv*, jobject, jlong ptr) {
		using namespace sani::resource;
		using namespace sani::graphics;
		ResourceManager* manager = reinterpret_cast<ResourceManager*>(ptr);
		texture = manager->load<Texture2D>("assets/tuksu.snb");
		rect = new sani::graphics::Rectangle(0.0f, 0.0f, texture->getWidth(), texture->getHeight());
		rect->transform.origin.x = 0.0f;
		rect->transform.origin.y = 0.0f;

		rect->transform.position.x = 0.f;
		rect->transform.position.y = 0.f;

		rect->texture = texture;
		rect->fill = color::white;
		rect->textureSource = Rectf(0.0f, 0.0f, texture->getHeight(), texture->getWidth());

		recomputeVertices(*rect);
		updateRenderData(*rect);
	}
}