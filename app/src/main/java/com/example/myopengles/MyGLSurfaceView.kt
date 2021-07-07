package com.example.myopengles

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import java.io.IOException
import java.nio.ByteBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLSurfaceView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : GLSurfaceView(context, attrs), GLSurfaceView.Renderer {

    private val mRender = MyGLRender()

    val IMAGE_FORMAT_RGBA = 0x01

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
        loadRGBAImage(R.drawable.front)
    }

    override fun onDrawFrame(gl: GL10?) {
        mRender.onDrawFrame(gl)
    }

    private fun loadRGBAImage(resId: Int): Bitmap? {
        val `is` = this.resources.openRawResource(resId)
        val bitmap: Bitmap?
        try {
            bitmap = BitmapFactory.decodeStream(`is`)
            if (bitmap != null) {
                val bytes = bitmap.byteCount
                val buf = ByteBuffer.allocate(bytes)
                bitmap.copyPixelsToBuffer(buf)
                val byteArray = buf.array()
                mRender.setImageData(IMAGE_FORMAT_RGBA, bitmap.width, bitmap.height, byteArray)
            }
        } finally {
            try {
                `is`.close()
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        return bitmap
    }

}