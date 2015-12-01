#include <jni.h>
#include <android\asset_manager_jni.h>
#include "sani/platform/file/file_system.hpp"
#include <sani/platform/graphics/graphics_device.hpp>
#include "sani/resource/resource_manager.hpp"
#include "sani/resource/texture2d.hpp"
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
		//const std::string path("assets/random.txt");
		//FileStream* stream = nullptr;
		//bool suc = fileSystem->openFile(path, Filemode::Read, &stream);
		//std::string contents = fileSystem->getFileDataString(path);
		//fileSystem->closeFile(path);
		//__android_log_print(ANDROID_LOG_ERROR, "ASD", "%s", contents.c_str());
	}

	JNIEXPORT jlong JNICALL Java_sani_android_SaniActivity_nativeInitializeFileSystem(JNIEnv*, jobject) {
		using namespace sani::io;
		FileSystem* fs = new FileSystem();
		return (long)fs;
	}

	JNIEXPORT jlong JNICALL Java_sani_android_SaniActivity_nativeInitResourceManager(JNIEnv*, jobject, jlong fileSystemPtr, jlong gdevicePtr) {
		using namespace sani::resource;
		using namespace sani::io;
		using namespace sani::graphics;
		GraphicsDevice* device = reinterpret_cast<GraphicsDevice*>(gdevicePtr);
		FileSystem* fs = reinterpret_cast<FileSystem*>(fileSystemPtr);
		ResourceManager* manager = new ResourceManager(fs, device);
		return (long)manager;
	}

	JNIEXPORT jlong JNICALL Java_sani_android_SaniActivity_nativeInitGraphicsDevice(JNIEnv*, jobject) {
		using namespace sani::graphics;
		GraphicsDevice* device = new GraphicsDevice();
		return (long)device;
	}

}