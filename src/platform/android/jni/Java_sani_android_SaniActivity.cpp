#include <jni.h>
#include <android\asset_manager_jni.h>

extern "C" {
	JNIEXPORT void JNICALL 
		Java_sani_android_SaniActivity_setNativeContext(JNIEnv* env, jobject thiz, jobject assetManager) {
		AAssetManager* manager = AAssetManager_fromJava(env, assetManager);
	}
}