#include <jni.h>
#include <android\asset_manager_jni.h>
#include <sani\platform\file_system.hpp>
#include <cassert>
extern "C" {
	JNIEXPORT void JNICALL 
		Java_sani_android_SaniActivity_nativeSetContext(JNIEnv* env, jobject thiz, jobject assetManager, jlong fileSystemPtr) {
		using namespace sani::io;
		FileSystem* fileSystem = reinterpret_cast<FileSystem*>(fileSystemPtr);
		// TODO proper error check
		if (!fileSystem) assert(0);
		AAssetManager* manager = AAssetManager_fromJava(env, assetManager);
		fileSystem->setAssetManager(manager);
	}

	JNIEXPORT jlong JNICALL Java_sani_android_SaniActivity_nativeInitializeFileSystem(JNIEnv*, jobject) {
		using namespace sani::io;
		FileSystem* fs = new FileSystem();
		return (long)fs;
	}
}