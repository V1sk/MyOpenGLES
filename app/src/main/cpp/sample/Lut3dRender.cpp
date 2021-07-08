//
// Created by coocent-camera002 on 2021/7/7.
//

#include "Lut3dRender.h"

void Lut3dRender::LoadImage(NativeImage *pImage) {
    if (pImage) {
        LOGCATE("TextureMapSample::LoadImage pImage = %p", pImage->ppPlane[0]);
        m_RenderImage.width = pImage->width;
        m_RenderImage.height = pImage->height;
        m_RenderImage.format = pImage->format;
        NativeImageUtil::CopyNativeImage(pImage, &m_RenderImage);
    }
}

void Lut3dRender::Init() {
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glGenTextures(1, &m_LutTextureId);
    glBindTexture(GL_TEXTURE_2D, m_LutTextureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    char vShaderStr[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec2 a_texCoord;   \n"
            "out vec2 v_texCoord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = a_position;               \n"
            "   v_texCoord = a_texCoord;                \n"
            "}                                          \n";

    char fShaderStr[] =
            "#version 300 es                            \n"
            "precision highp float;\n"
            "in vec2 v_texCoord;\n"
            "layout(location = 0) out vec4 outColor;\n"
            "uniform sampler2D s_TextureMap;\n"
            "uniform sampler2D LutImageTexture;\n"
            "\n"
            "void main(){\n"
            "\n"
            "    lowp vec4 color = texture(s_TextureMap, v_texCoord);\n"
            "    mediump float intensity = 1.0f;\n"
            "    mediump float fb = color.b * 15.0;\n"
            "    mediump float fr = color.r * 15.0;\n"
            "    mediump float blockLeft = floor(fb);\n"
            "    mediump float blockRight = ceil(fb);\n"
            "    highp float u  = blockLeft / 15.0 * 240.0;\n"
            "    u  = fr + 0.5 + u;\n"
            "    u /= 256.0;\n"
            "    highp float v  = color.g;\n"
            "    lowp vec4 left = texture(LutImageTexture, vec2(u, v));\n"
            "    u  = blockRight / 15.0 * 240.0;\n"
            "    u  = fr + 0.5 + u;\n"
            "    u /= 256.0;\n"
            "    lowp vec4 right = texture(LutImageTexture, vec2(u, v));\n"
            "    mediump vec4 interp = mix(left, right, fract(color * 15.0));\n"
            "    outColor = clamp(mix(color, interp, intensity), 0.0, 1.0);;\n"
            "}";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
    if (m_ProgramObj) {
        m_SamplerLoc = glGetUniformLocation(m_ProgramObj, "s_TextureMap");
        m_LutSamplerLoc = glGetUniformLocation(m_ProgramObj, "LutImageTexture");
    } else {
        LOGCATE("TextureMapSample::Init create program fail");
    }
}

void Lut3dRender::Draw(int screenW, int screenH) {
    LOGCATE("TextureMapSample::Draw()");

    if (m_ProgramObj == GL_NONE || m_TextureId == GL_NONE) return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    GLfloat verticesCoords[] = {
            -1.0f, 0.5f, 0.0f,  // Position 0
            -1.0f, -0.5f, 0.0f,  // Position 1
            1.0f, -0.5f, 0.0f,   // Position 2
            1.0f, 0.5f, 0.0f,   // Position 3
    };

    GLfloat textureCoords[] = {
            0.0f, 0.0f,        // TexCoord 0
            0.0f, 1.0f,        // TexCoord 1
            1.0f, 1.0f,        // TexCoord 2
            1.0f, 0.0f         // TexCoord 3
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3};

    //upload RGBA image data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_RenderImage.width, m_RenderImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, m_RenderImage.ppPlane[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    //upload RGBA image data
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_LutTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_LutImage.width, m_LutImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, m_LutImage.ppPlane[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);


    // Use the program object
    glUseProgram(m_ProgramObj);

    // Load the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT,
                          GL_FALSE, 3 * sizeof(GLfloat), verticesCoords);
    // Load the texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT,
                          GL_FALSE, 2 * sizeof(GLfloat), textureCoords);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Bind the RGBA map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    // Set the RGBA map sampler to texture unit to 0
    glUniform1i(m_SamplerLoc, 0);
//    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_LutTextureId);
    // Set the RGBA map sampler to texture unit to 0
    glUniform1i(m_LutSamplerLoc, 1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void Lut3dRender::Destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        glDeleteTextures(1, &m_TextureId);
        glDeleteTextures(1, &m_LutTextureId);
        m_ProgramObj = GL_NONE;
    }
}

Lut3dRender::Lut3dRender() {
    m_TextureId = 0;
    m_LutTextureId = 0;
}

Lut3dRender::~Lut3dRender() {
    NativeImageUtil::FreeNativeImage(&m_RenderImage);
}

void Lut3dRender::LoadLutImage(NativeImage *pImage) {
    if (pImage) {
        LOGCATE("TextureMapSample::LoadLutImage pImage = %p", pImage->ppPlane[0]);
        m_LutImage.width = pImage->width;
        m_LutImage.height = pImage->height;
        m_LutImage.format = pImage->format;
        NativeImageUtil::CopyNativeImage(pImage, &m_LutImage);
    }
}
