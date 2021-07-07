//
// Created by coocent-camera002 on 2021/7/7.
//

#include "CoGLRenderContext.h"
#include "TextureSample.h"

CoGLRenderContext *CoGLRenderContext::m_pContext = nullptr;

CoGLRenderContext *CoGLRenderContext::getInstance() {
    if (m_pContext == nullptr) {
        m_pContext = new CoGLRenderContext();
    }
    return m_pContext;
}

void CoGLRenderContext::destroyInstance() {
    if (m_pContext) {
        delete m_pContext;
        m_pContext = nullptr;
    }
}

void CoGLRenderContext::onSurfaceCreated() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void CoGLRenderContext::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    this->mScreenW = width;
    this->mScreenH = height;
}

void CoGLRenderContext::onDrawFrame() {
    if (m_pSample) {
        m_pSample->Draw(this->mScreenW, this->mScreenH);
    }
}

CoGLRenderContext::CoGLRenderContext() {
    this->mScreenW = 0;
    this->mScreenH = 0;
    m_pSample = new TextureSample();
}

void CoGLRenderContext::setImageData(int format, int width, int height, uint8_t *pData) {
    if (m_pSample) {
        NativeImage nativeImage;
        nativeImage.format = format;
        nativeImage.width = width;
        nativeImage.height = height;
        nativeImage.ppPlane[0] = pData;

        switch (format) {
            case IMAGE_FORMAT_NV12:
            case IMAGE_FORMAT_NV21:
                nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
                break;
            case IMAGE_FORMAT_I420:
                nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
                nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
                break;
            default:
                break;
        }
        m_pSample->Init();
        m_pSample->LoadImage(&nativeImage);
    }
}
