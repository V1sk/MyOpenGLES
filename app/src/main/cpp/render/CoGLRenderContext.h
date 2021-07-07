//
// Created by coocent-camera002 on 2021/7/7.
//

#ifndef MYOPENGLES_COGLRENDERCONTEXT_H
#define MYOPENGLES_COGLRENDERCONTEXT_H

#include <GLES3/gl3.h>
#include "GLUtils.h"
#include "GLSampleBase.h"

class CoGLRenderContext {

    CoGLRenderContext();

public:

    void setImageData(int format, int width, int height, uint8_t *pData);

    void onSurfaceCreated();

    void onSurfaceChanged(int width, int height);

    void onDrawFrame();

    static CoGLRenderContext *getInstance();

    static void destroyInstance();

private:
    static CoGLRenderContext *m_pContext;
    int mScreenW;
    int mScreenH;
    GLSampleBase *m_pSample;

};


#endif //MYOPENGLES_COGLRENDERCONTEXT_H
