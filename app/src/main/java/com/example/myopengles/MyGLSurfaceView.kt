package com.example.myopengles

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet

class MyGLSurfaceView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : GLSurfaceView(context, attrs) {

    private val mRender = MyGLRender()

    init {
        setEGLContextClientVersion(2)
        setEGLConfigChooser(8, 8, 8, 8, 16, 8)
        setRenderer(mRender)
        renderMode = RENDERMODE_WHEN_DIRTY
    }

}