/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>

/** This is the C++ implementation of the Java native method.
@param env Pointer to JVM environment
@param thiz Reference to Java this object
*/
extern "C"
JNIEXPORT void JNICALL
Java_com_android_sani_sani_saniNative( JNIEnv* env, jobject thiz )
{
	// Enter code here
}
