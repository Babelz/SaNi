/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package sani.android;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.os.Build;
import android.content.res.AssetManager;
import android.content.Context;
import android.app.ActivityManager;
import android.content.pm.ConfigurationInfo;

import android.opengl.GLSurfaceView;

/**
 * This class loads the Java Native Interface (JNI)
 * library, 'libandroid.so', and provides access to the
 * exposed C functions.
 * The library is packaged and installed with the application.
 * See the C file, /jni/android.c file for the
 * implementations of the native methods. 
 * 
 * For more information on JNI, see: http://java.sun.com/docs/books/jni/
 */

public class SaniActivity extends Activity
{

	private AssetManager assetManager;
	private GLSurfaceView glSurfaceView;
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

		final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();

		if (supportsEs2) {
			glSurfaceView = new GLSurfaceView(this);
 
			if (isProbablyEmulator()) {
				// Avoids crashes on startup with some emulator images.
				glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
			}
 
			glSurfaceView.setEGLContextClientVersion(2);
			// glSurfaceView.setRenderer(new XXXXX); ??
			// setContentView(glSurfaceView); ??
		}

		assetManager = this.getAssets();
		setNativeContext(assetManager);
	}

	private boolean isProbablyEmulator() {
		return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
				&& (Build.FINGERPRINT.startsWith("generic")
						|| Build.FINGERPRINT.startsWith("unknown")
						|| Build.MODEL.contains("google_sdk")
						|| Build.MODEL.contains("Emulator")
						|| Build.MODEL.contains("Android SDK built for x86"));
	}

	/* Sets the context to be used in android apps
	 * 
	 */
	public native void setNativeContext(final AssetManager assetManager);

	/* This is the static constructor used to load the
	 * 'android' library when the class is
	 * loaded.
	 */
	static {
		System.loadLibrary("android");
		System.loadLibrary("android-sandbox");
		//System.loadLibrary("sani");
	}
}
