//
// Created by coocent-camera002 on 2021/7/7.
//

#ifndef MYOPENGLES_GLSAMPLEBASE_H
#define MYOPENGLES_GLSAMPLEBASE_H

#include "stdint.h"
#include <GLES3/gl3.h>
#include <ImageDef.h>

class GLSampleBase {

public:
    GLSampleBase() {
        m_ProgramObj = 0;
        m_VertexShader = 0;
        m_FragmentShader = 0;

        m_SurfaceWidth = 0;
        m_SurfaceHeight = 0;
    }

    virtual ~GLSampleBase() {

    }

    virtual void LoadImage(NativeImage *pImage) {};

    virtual void Init() = 0;

    virtual void Draw(int screenW, int screenH) = 0;

    virtual void Destroy() = 0;

protected:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ProgramObj;
    int m_SurfaceWidth;
    int m_SurfaceHeight;

};

#endif //MYOPENGLES_GLSAMPLEBASE_H
