package com.monitoring.optimus.rs;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

import com.facebook.react.uimanager.annotations.ReactProp;
import com.monitoring.optimus.rs.glsurface.OpenGLSurfaceView;

public class RsSdkReactOpenGLSurfaceViewManager extends SimpleViewManager<OpenGLSurfaceView> {

    public static final String REACT_CLASS = "RsSdkReactOpenGLSurfaceView";
    ReactApplicationContext mCallerContext;

    public RsSdkReactOpenGLSurfaceViewManager(ReactApplicationContext reactContext) {
        mCallerContext = reactContext;
    }

    @NonNull
    @Override
    public String getName() {
        return REACT_CLASS;
    }

    @NonNull
    @Override
    protected OpenGLSurfaceView createViewInstance(@NonNull ThemedReactContext themedReactContext) {
        return new OpenGLSurfaceView(themedReactContext);
    }

    @ReactProp(name = "previewID")
    public void SetPreviewID(OpenGLSurfaceView view, @Nullable String preview_id) {
        assert preview_id != null;
        view.SetPreviewID(Long.parseLong(preview_id));
    }
}
