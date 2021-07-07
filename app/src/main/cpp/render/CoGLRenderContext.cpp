//
// Created by coocent-camera002 on 2021/7/7.
//

#include "CoGLRenderContext.h"
CoGLRenderContext* CoGLRenderContext::m_pContext = nullptr;

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
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ProgramObj;
//    MySyncLock m_Lock;
    int m_SurfaceWidth;
    int m_SurfaceHeight;

    if(m_ProgramObj != 0)
        return;
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

    GLfloat vVertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    if(m_ProgramObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Use the program object
    glUseProgram (m_ProgramObj);

    // Load the vertex data
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray (0);

    glDrawArrays (GL_TRIANGLES, 0, 3);
    glUseProgram (GL_NONE);
}

CoGLRenderContext::CoGLRenderContext() {

}
