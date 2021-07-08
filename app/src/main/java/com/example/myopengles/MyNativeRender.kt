package com.example.myopengles

class MyNativeRender {

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun native_OnSurfaceCreated()

    external fun native_Init()

    external fun native_OnSurfaceChanged(width: Int, height: Int)

    external fun native_OnDrawFrame()

    external fun native_UnInit()

    external fun native_SetImageData(format: Int, width: Int, height: Int, bytes: ByteArray)

    external fun native_SetLutImageData(format: Int, width: Int, height: Int, bytes: ByteArray)
}