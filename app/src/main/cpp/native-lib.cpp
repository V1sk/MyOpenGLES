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

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myopengles_MyNativeRender_native_1SetImageData(JNIEnv *env, jobject thiz,
                                                                jint format, jint width,
                                                                jint height, jbyteArray imageData) {
    int len = env->GetArrayLength(imageData);
    auto *buf = new uint8_t[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buf));
    CoGLRenderContext::getInstance()->setImageData(format, width, height, buf);
    delete[] buf;
    env->DeleteLocalRef(imageData);
}