package sani.android;

import android.opengl.GLSurfaceView;
import android.content.Context;
import android.util.AttributeSet;


public class SaniGLSurfaceView extends GLSurfaceView {
	
	private SaniRenderer saniRenderer;

	public SaniGLSurfaceView(final Context context) {
		super(context);
		initView();
	}
	public SaniGLSurfaceView(final Context context, final AttributeSet attrs) {
		super(context, attrs);
		initView();
	}

	private void initView() {
		this.setEGLContextClientVersion(2);
	}

	// This is used because onSizeChanged is being called at first
	// and its null pointer
	public void setSaniRenderer(final SaniRenderer renderer) {
		saniRenderer = renderer;
		setRenderer(renderer);
	}

	@Override
	protected void onSizeChanged(final int newSurfaceWidth, final int newSurfaceHeight, final int oldSurfaceWidth, final int oldSurfaceHeight) {
		saniRenderer.setScreenDimensions(newSurfaceWidth, newSurfaceHeight);
	}

	@Override
	public void onResume() {
		super.onResume();
	}

	
	@Override
	public void onPause() {
		super.onPause();
	}
}