#include <jni.h>
#include <string>
#include "render/CoGLRenderContext.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1OnSurfaceCreated(JNIEnv *env, jobject thiz) {
    CoGLRenderContext::getInstance()->onSurfaceCreated();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1Init(JNIEnv *env, jobject thiz) {
    CoGLRenderContext::getInstance();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1OnSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                    jint width, jint height) {
    CoGLRenderContext::getInstance()->onSurfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1OnDrawFrame(JNIEnv *env, jobject thiz) {
    CoGLRenderContext::getInstance()->onDrawFrame();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1UnInit(JNIEnv *env, jobject thiz) {
    CoGLRenderContext::destroyInstance();
}