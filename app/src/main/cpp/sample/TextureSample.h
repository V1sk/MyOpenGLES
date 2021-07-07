//
// Created by coocent-camera002 on 2021/7/7.
//

#ifndef MYOPENGLES_TEXTURESAMPLE_H
#define MYOPENGLES_TEXTURESAMPLE_H

#include "GLSampleBase.h"
#include "GLUtils.h"

class TextureSample : public GLSampleBase {

public:
    TextureSample();

    ~TextureSample();

    void LoadImage(NativeImage *pImage);

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

private:
    GLuint m_TextureId;
    GLint m_SamplerLoc;
    NativeImage m_RenderImage;

};


#endif //MYOPENGLES_TEXTURESAMPLE_H
