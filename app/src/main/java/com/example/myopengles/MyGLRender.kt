package com.example.myopengles

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRender : GLSurfaceView.Renderer {

    private val mNativeRender: MyNativeRender = MyNativeRender()

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        mNativeRender.native_OnSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        mNativeRender.native_OnSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        mNativeRender.native_OnDrawFrame()
    }

    public fun init() {
        mNativeRender.native_Init()
    }

    public fun unInit() {
        mNativeRender.native_UnInit()
    }

    fun setImageData(format: Int, width: Int, height: Int, bytes: ByteArray) {
        mNativeRender.native_SetImageData(format, width, height, bytes)
    }
}