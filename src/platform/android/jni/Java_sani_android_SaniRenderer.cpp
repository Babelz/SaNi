#include <jni.h>
#include <GLES2/gl2.h>

extern "C" {
	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeInit(JNIEnv* env, jclass clazz, jint surfaceWidth, jint surfaceHeight) {
		glClearColor(1.f, 0.f, 0.f, 1.f);
	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeOnSurfaceChanged(JNIEnv* env, jclass clazz, jint surfaceWidth, jint surfaceHeight) {

	}

	JNIEXPORT void JNICALL Java_sani_android_SaniRenderer_nativeRender(JNIEnv* env, jclass clazz) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}