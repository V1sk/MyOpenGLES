package com.example.myopengles

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLSurfaceView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : GLSurfaceView(context, attrs), GLSurfaceView.Renderer {

    private val mRender = MyGLRender()

    init {
        setEGLContextClientVersion(2)
        setEGLConfigChooser(8, 8, 8, 8, 16, 8)
        setRenderer(this)
        renderMode = RENDERMODE_WHEN_DIRTY
        mRender.init()
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        mRender.onSurfaceCreated(gl, config)
        requestRender()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        mRender.onSurfaceChanged(gl, width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        mRender.onDrawFrame(gl)
    }

}