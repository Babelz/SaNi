package sani.android;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLSurfaceView.Renderer;
import static android.opengl.GLES20.*;

public class SaniRenderer implements GLSurfaceView.Renderer {

	// Because we need to get these from Java
	private int screenWidth;
	private int screenHeight;

	public void setScreenDimensions(final int surfaceWidth, final int surfaceHeight) {
		screenWidth = surfaceWidth;
		screenHeight = surfaceHeight;
	}

	@Override
	public void onSurfaceCreated(final GL10 gl10, final EGLConfig config) {
		nativeInit(screenWidth, screenHeight);
	}

	@Override
	public void onSurfaceChanged(final GL10 gl10, final int width, final int height) {
		nativeOnSurfaceChanged(width, height);
	}

	@Override
	public void onDrawFrame(final GL10 gl) {
		nativeRender();
	}
	// Initializes the graphics devices
	private static native void nativeInit(final int width, final int height);
	// TODO: Do we need this?
	private static native void nativeOnSurfaceChanged(final int width, final int height);
	// Renders frame
	private static native void nativeRender();
}