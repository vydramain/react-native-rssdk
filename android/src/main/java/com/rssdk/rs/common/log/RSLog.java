package com.rssdk.rs.common.log;

import android.content.Context;

import com.monitoring.optimus.xlog.Log;
import com.monitoring.optimus.xlog.Xlog;

public class RSLog {
    private static final String TAG = "RSLog";

    static {
        Log.setLevel(Log.LEVEL_VERBOSE, false);
    }

    public static void init(Context context, String nameprefix, String logPath, boolean write2file) {
        android.util.Log.i(TAG, "init, nameprefix: " + nameprefix + ", logPath: " + logPath);
        String cacheDir = context.getFilesDir() + "/xlog";

        Xlog.open(true, Xlog.LEVEL_VERBOSE, Xlog.AppednerModeAsync, cacheDir, logPath, nameprefix, "");
        Xlog.setConsoleLogOpen(true);

        if (write2file) {
            Log.setLogImp(new Xlog());
        }
    }

    public static void setLevel(final int level) {
        Log.setLevel(level, false);
    }

    public static void appenderFlush() {
        Log.appenderFlush(true);
    }

    public static void close() {
        Log.appenderClose();
    }

    public static void v(String tag, String msg) {
        Log.v(tag, msg);
    }

    public static void v(String tag, final String format, final Object... obj) {
        Log.v(tag, format, obj);
    }

    public static void d(String tag, String msg) {
        Log.d(tag, msg);
    }

    public static void d(String tag, final String format, final Object... obj) {
        Log.d(tag, format, obj);
    }

    public static void i(String tag, String msg) {
        Log.i(tag, msg);
    }

    public static void i(String tag, final String format, final Object... obj) {
        Log.i(tag, format, obj);
    }

    public static void w(String tag, String msg) {
        Log.w(tag, msg);
    }

    public static void w(String tag, final String format, final Object... obj) {
        Log.w(tag, format, obj);
    }

    public static void e(String tag, String msg) {
        Log.e(tag, msg);
    }

    public static void e(String tag, final String format, final Object... obj) {
        Log.e(tag, format, obj);
    }

    public static void e(String tag, Throwable tr, final String format, final Object... obj) {
        Log.printErrStackTrace(tag, tr, format, obj);
    }
}
