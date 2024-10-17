package com.rssdk;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

import com.facebook.react.uimanager.annotations.ReactProp;
import com.facebook.react.uimanager.annotations.ReactPropGroup;
import com.rssdk.glsurface.OpenGLSurfaceView;

import java.util.Objects;

public class RsSdkReactOpenGLSurfaceViewManager extends SimpleViewManager<OpenGLSurfaceView> {

    public static final String REACT_CLASS = "RsSdkReactOpenGLSurfaceView";
    ReactApplicationContext mCallerContext;
    private int propWidth;
    private int propHeight;

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

    @ReactPropGroup(names = {"width", "height"}, customType = "Style")
    public void setStyle(OpenGLSurfaceView view, int index, Integer value) {
        if (index == 0) {
            propWidth = value;
        }

        if (index == 1) {
            propHeight = value;
        }
    }

    @ReactProp(name = "previewId")
    public void setPreviewId(OpenGLSurfaceView view, String preview_id) {
        view.SetPreviewID(Long.parseLong(Objects.requireNonNull(preview_id)));
    }
}
