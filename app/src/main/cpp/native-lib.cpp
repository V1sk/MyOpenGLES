#include <jni.h>
#include <string>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1OnSurfaceCreated(JNIEnv *env, jobject thiz) {
    // TODO: implement native_OnSurfaceCreated()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1Init(JNIEnv *env, jobject thiz) {
    // TODO: implement native_Init()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1OnSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                    jint width, jint height) {
    // TODO: implement native_OnSurfaceChanged()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1OnDrawFrame(JNIEnv *env, jobject thiz) {
    // TODO: implement native_OnDrawFrame()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1UnInit(JNIEnv *env, jobject thiz) {
    // TODO: implement native_UnInit()
}