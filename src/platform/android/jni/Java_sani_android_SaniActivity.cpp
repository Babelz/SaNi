#include <jni.h>
#include <android\asset_manager_jni.h>
#include <sani\platform\file_system.hpp>
#include <cassert>
#include <android\log.h>
extern "C" {
	JNIEXPORT void JNICALL 
		Java_sani_android_SaniActivity_nativeSetContext(JNIEnv* env, jobject thiz, jobject assetManager, jlong fileSystemPtr) {
		using namespace sani::io;
		FileSystem* fileSystem = reinterpret_cast<FileSystem*>(fileSystemPtr);
		// TODO proper error check
		if (!fileSystem) assert(0);
		AAssetManager* manager = AAssetManager_fromJava(env, assetManager);
		fileSystem->setAssetManager(manager);
		const std::string path("assets/random.txt");
		bool suc = fileSystem->openFile(path, sani::io::Read);
		std::string contents = fileSystem->getFileDataString(path);
		fileSystem->closeFile(path);
		__android_log_print(ANDROID_LOG_ERROR, "ASD", "%s", contents.c_str());
	}

	JNIEXPORT jlong JNICALL Java_sani_android_SaniActivity_nativeInitializeFileSystem(JNIEnv*, jobject) {
		using namespace sani::io;
		FileSystem* fs = new FileSystem();
		return (long)fs;
	}
}