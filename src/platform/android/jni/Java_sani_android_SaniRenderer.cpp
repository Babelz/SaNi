#include <jni.h>
#include <GLES2/gl2.h>
#include <sani/platform/graphics/graphics_device.hpp>
#include <android/log.h>
#include <sani/platform/graphics/viewport.hpp>

// TODO test
#define  LOG_TAG    "SaniRenderer"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


extern "C" {

	JNIEXPORT jlong JNICALL Java_sani_android_SaniRenderer_nativeInitGraphicsDevice(JNIEnv*, jobject) {
		using namespace sani::graphics;
		LOGI("Creating Android GLES graphics device...");
		GraphicsDevice* device = new GraphicsDevice();
		return (long)device;
	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeInit(JNIEnv* env, jclass clazz, jint surfaceWidth, jint surfaceHeight, jlong graphicsDevicePtr) {
		using namespace sani::graphics;
		GraphicsDevice* device = reinterpret_cast<GraphicsDevice*>(graphicsDevicePtr);
		if (!device) {
			LOGE("Graphics device is null in C++!");
		}
		device->setBackBufferWidth(surfaceWidth);
		device->setBackBufferHeight(surfaceHeight);
		device->setViewport(Viewport( 0u, 0u, surfaceWidth, surfaceHeight) );
	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeOnSurfaceChanged(JNIEnv* env, jclass clazz, jint surfaceWidth, jint surfaceHeight) {

	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeRender(JNIEnv* env, jclass clazz, jlong graphicsDevicePtr) {
		using namespace sani::graphics;
		GraphicsDevice* device = reinterpret_cast<GraphicsDevice*>(graphicsDevicePtr);
		device->clear(1.f, 0.f, 0.f, 1.f);
	}
}