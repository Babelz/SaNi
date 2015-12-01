package sani.android;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class SaniRenderer implements GLSurfaceView.Renderer {

	// Because we need to get these from Java
	private int screenWidth;
	private int screenHeight;

	private long graphicsDevicePtr;

	public void setScreenDimensions(final int surfaceWidth, final int surfaceHeight) {
		screenWidth = surfaceWidth;
		screenHeight = surfaceHeight;
	}

	public void setGraphicsDevicePointer(final long ptr) {
		graphicsDevicePtr = ptr;
	}

	@Override
	public void onSurfaceCreated(final GL10 gl10, final EGLConfig config) {
		if (graphicsDevicePtr == 0) {
			Log.e("SaniRenderer", "Graphics device is null");
			System.exit(0);
		}
		Log.e("SaniRenderer", "Created gdevice");
		nativeInit(screenWidth, screenHeight, graphicsDevicePtr);
	}

	@Override
	public void onSurfaceChanged(final GL10 gl10, final int width, final int height) {
		nativeOnSurfaceChanged(width, height);
	}

	@Override
	public void onDrawFrame(final GL10 gl) {
		nativeRender(graphicsDevicePtr);
	}

	// Initializes the graphics devices
	private static native void nativeInit(final int width, final int height, long graphicsDevice);
	// TODO: Do we need this?
	private static native void nativeOnSurfaceChanged(final int width, final int height);
	// Renders frame
	private static native void nativeRender(long graphicsDevice);
}