//
// Created by coocent-camera002 on 2021/7/7.
//

#ifndef MYOPENGLES_LUT3DRENDER_H
#define MYOPENGLES_LUT3DRENDER_H

#include "GLSampleBase.h"
#include "GLUtils.h"

class Lut3dRender : public GLSampleBase {

public:
    Lut3dRender();

    ~Lut3dRender();

    void LoadImage(NativeImage *pImage);

    void LoadLutImage(NativeImage *pImage);

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

private:
    GLuint m_TextureId;
    GLuint m_LutTextureId;
    GLint m_SamplerLoc;
    GLint m_LutSamplerLoc;
    NativeImage m_RenderImage;
    NativeImage m_LutImage;

};


#endif //MYOPENGLES_LUT3DRENDER_H
