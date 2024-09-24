package com.monitoring.optimus.rs;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;

import android.os.Build;
import android.util.Log;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

import com.monitoring.optimus.rs.jni.JniRsSdkCallback;
import com.monitoring.optimus.rs.jni.JniRsSdkWrapper;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;

/**
 * Original library use as device_id value long type.
 * On some exotic CPU archtectures, the alignment requirements for jlong variables and jvalue unions might be different.
 * When you declare a union explicitly, the compiler takes care of that.
 * Also note that C++ long datatype is often 32-bit.
 * `jlong` is 64 bits, on 32-bit platforms the nonstandard C equivalent is long long or __int64.
 * For keeping data consistency all long data with device_id casts to String and parses to Long
 */
@ReactModule(name = "RsSdkReactJavaModule")
public class RsSdkReactJavaModule extends ReactContextBaseJavaModule implements JniRsSdkCallback {
    private static final String TAG = RsSdkReactJavaModule.class.getSimpleName();

    public RsSdkReactJavaModule(ReactApplicationContext context) {
        super(context);
        Log.d(TAG, "RsSdkReactJavaModule constructor was called");

        try {
            int result = JniRsSdkWrapper.rs_sdk_wrapper_init("{}");
            Log.d(TAG, "Called `rs_sdk_wrapper_init` with result: " + result);
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_sdk_wrapper_init` method: " + e);
        }
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            int result = JniRsSdkWrapper.rs_sdk_wrapper_uninit("{}");
            Log.d(TAG, "Called `rs_sdk_wrapper_uninit` with result: " + result);
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_sdk_wrapper_uninit` method: " + e);
        } finally {
            super.finalize();
        }
    }


    @NonNull
    @Override
    public String getName() {
        return TAG;
    }


    @ReactMethod
    public void rs_android_surface_create(Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_android_surface_create();
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_android_surface_destory(long surface_id, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_android_surface_destory(surface_id);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_android_surface_change(long surface_id, int width, int height, long preview_id, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_android_surface_change(surface_id, width, height, preview_id);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_android_surface_draw(long surface_id, long preview_id, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_android_surface_draw(surface_id, preview_id);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_android_surface_set_user_param(long surface_id, Object user_param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_android_surface_set_user_param(surface_id, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_init_log(String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_init_log(param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_init_log_ex(String param, Object user_param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_init_log_ex(param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    List<JSONObject> search_devices_list = new ArrayList<>();
    CompletableFuture<Void> search_devices_future = null;

    /**
     * @param param   Is JSON object with fields:
     *                - "oem type": "default", "optimus"
     *                - "start ip": if you use udp point to point search, fill this, such as "172.18.12.2",
     *                otherwise if you use lan broadcast, just ignore this value or fill ""
     *                - "stop ip": if you use udp point to point search, fill this, such as "172.18.12.254",
     *                otherwise if you use lan broadcast, just ignore this value or fill ""
     * @param promise Promise for returning result to React Native.
     *                For more info how to use look: https://reactnative.dev/docs/native-modules-android#promises
     */
    @ReactMethod
    public void rs_search_device(String param, Promise promise) {
        try {
            search_devices_list.clear();
            search_devices_future = new CompletableFuture<>();
            long result = JniRsSdkWrapper.rs_search_device(param, RsSdkReactJavaModule.this);

            if (result != 0) {
                throw new RuntimeException(String.format("Function `rs_search_device` returned %d error!", result));
            }

            search_devices_future.get();

            JSONArray json_devices_array = new JSONArray();
            search_devices_list.forEach(device -> {
                json_devices_array.put(device);
            });

            JSONObject resultJson = new JSONObject();
            resultJson.put("search_devices_result", result);
            resultJson.put("search_devices_list", json_devices_array);

            promise.resolve(resultJson.toString());
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_search_device` method: " + e);
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function `rs_search_device`: ", e);
        }
    }

    @Override
    public void search_device_callback(String param) {
        Log.d(TAG, "Called search_device_callback with param: " + param);
        if (param == null) {
            search_devices_future.complete(null);
            return;
        }

        try {
            search_devices_list.add(new JSONObject(param));
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while parsing string with found device: " + e);
        }
    }

    @ReactMethod
    public void rs_modify_device(String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_modify_device(param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_create_device(Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_create_device();
            Log.d(TAG, "Called `rs_create_device` with result: " + result);
            String result_string = Long.toString(result);
            promise.resolve(result_string);
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_create_device` method: " + e);
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function `rs_create_device`: ", e);
        }
    }

    @ReactMethod
    public void rs_destroy_device(String dev_long, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_destroy_device(Long.parseLong(dev_long));
            Log.d(TAG, "Called `rs_destroy_device` with result: " + result);
            promise.resolve(result);
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_destroy_device` method: " + e);
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    boolean is_success_received = false;
    List<JSONObject> login_devices_callback_params_list = new ArrayList<>();
    CompletableFuture<Void> login_devices_future = null;

    /**
     * Login device:
     * <p>
     * There are different types of value: `p2p type` for cameras.
     * They all differ slightly with respect to the type of id. He listed three of them:
     * - `tut` - contains 20 characters
     * - `vv` - contains 16 or 17 characters
     * - `srvv` - id necessarily begins with the characters 'RSV'
     * - All other types of id he said should be treated as rs.
     * <p>
     * Also, there are different types of value `oem type`.
     * This field should always keep `optimus` because most of the devices for use works with 'Optimus' OS type.
     *
     * @param dev_long Id of device from `rs_create_device` function
     * @param param    Is JSON object like:
     *                 - "ip or id": "E9N862FV5MG378S4111A",
     *                 - "port": 443,
     *                 - "user": "admin",
     *                 - "password": "Qwerty123",
     *                 - "ddns id server addr": "",
     *                 - "p2p type": "tutk",
     *                 - "oem type": "optimus",
     *                 - "protocol": "auto"
     * @param promise  Promise for returning result to React Native. For more info how to use look: https://reactnative.dev/docs/native-modules-android#promises
     */
    @RequiresApi(api = Build.VERSION_CODES.N)
    @ReactMethod
    public void rs_device_login(String dev_long, String param, Promise promise) {
        try {
            is_success_received = false;
            login_devices_callback_params_list.clear();
            login_devices_future = new CompletableFuture<>();
            int result = JniRsSdkWrapper.rs_device_login(Long.parseLong(dev_long), param, RsSdkReactJavaModule.this);

            login_devices_future.get(10, TimeUnit.SECONDS);

            JSONArray json_devices_array = new JSONArray();
            login_devices_callback_params_list.forEach(json_devices_array::put);

            JSONObject resultJson = new JSONObject();
            resultJson.put("login_devices_result", result);
            resultJson.put("login_devices_callback_params_list", json_devices_array);

            promise.resolve(resultJson.toString());
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_device_login` method: " + e);
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function `rs_device_login`: ", e);
        }
    }

    @Override
    public void connction_callback(String param) {
        JSONObject json = null;
        try {
            json = new JSONObject(param);
        } catch (JSONException e) {
            Log.e(TAG, "Can't parse input param of connction_callback: " + param);
            return;
        }

        String type = json.optString("status");
        JSONObject info = json.optJSONObject("info");
        Log.d(TAG, "Type of param in connction_callback is '" + type + "' Info of param is: '" + info + "'");


        try {
            login_devices_callback_params_list.add(new JSONObject(param));
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while parsing string with found device: " + e);
        }

        switch (type) {
            case "none mode":
            case "lan mode":
            case "first_login_flag":
                break;
            case "close":
                if (is_success_received) {
                    login_devices_future.complete(null);
                }
                break;
            case "success":
                is_success_received = true;
                login_devices_future.complete(null);
                break;
        }

    }

    @Override
    public void alarm_callback(String alarm_type, String param) {
        Log.e(TAG, "Called `alarm_callback` with type: " + alarm_type + " and param: " + param);
    }


    @ReactMethod
    public void rs_device_login_ex(String dev_long, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_device_login_ex(Long.parseLong(dev_long), param, RsSdkReactJavaModule.this);
            Log.d(TAG, "Called `rs_device_login_ex` with result: " + result);
            promise.resolve(result);
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_device_login_ex` method: " + e);
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function `rs_device_login_ex`: ", e);
        }
    }

    @ReactMethod
    public void rs_device_logout(String dev_long, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_device_logout(Long.parseLong(dev_long));
            Log.d(TAG, "Called `rs_device_logout` with result: " + result);
            promise.resolve(result);
        } catch (Exception e) {
            Log.e(TAG, "Error occurred while executing `rs_device_logout` method: " + e);
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_get_login_rsp(long dev, Promise promise) {
        try {
            String result = JniRsSdkWrapper.rs_get_login_rsp(dev);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    /**
     * @param dev     Input device id
     * @param param   Json with parameters:
     *                device_id           dev,
     *                const char*         param,
     *                HWND                window,
     *                preivew_callback    preview_cb,
     *                void*
     *                preview_user_param
     *                draw_callback       draw_cb,
     *                picture_callback    picture_cb,
     *                const char*         background_picture,
     *                int                 background_picture_size,
     *                zoom_callback       zoom_cb,
     *                char                reserve[220],
     * @param promise Result for React Native
     */
    @ReactMethod
    public void rs_start_preview(long dev, int channel, String param, Promise promise) {
        try {
            JSONObject json = new JSONObject();
            json.put("channel", 0);
            json.put("stream type", "sub stream");
            json.put("auto connect", true);
            long preview_sess = JniRsSdkWrapper.rs_start_preview(dev, json.toString(), RsSdkReactJavaModule.this);
            Log.d(TAG, "Called `rs_start_preview` with result: " + preview_sess);
            promise.resolve(preview_sess);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function `rs_start_preview`: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_preview(String session_id, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_preview(Long.parseLong(session_id));
            Log.d(TAG, "Called `rs_stop_preview` with result: " + result);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function `rs_stop_preview`: ", e);
        }
    }

    @ReactMethod
    public void rs_search_record_by_month(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_search_record_by_month(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_search_record_by_day(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_search_record_by_day(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_search_record(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_search_record(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_download_by_file(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_download_by_file(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_download_by_time(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_download_by_time(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_download(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_download(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_local_playback(String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_local_playback(param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_remote_playback(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_remote_playback(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_sync_playback(String user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_sync_playback(user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_playback(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_playback(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_open_sound(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_open_sound(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_close_sound(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_close_sound(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_volume(long sess, int volume, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_volume(sess, volume);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_mute_on(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_mute_on(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_mute_off(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_mute_off(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_record(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_start_record(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_record(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_record(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_capture_picture(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_capture_picture(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_get_file_time(String filename, Promise promise) {
        try {
            String result = JniRsSdkWrapper.rs_get_file_time(filename);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_get_current_time(long sess, Promise promise) {
        try {
            String result = JniRsSdkWrapper.rs_get_current_time(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_get_current_time_millisecond(long sess, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_get_current_time_millisecond(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_seek_by_time(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_seek_by_time(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_get_file_key_frame_count(String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_get_file_key_frame_count(param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_seek_by_key_frame_index(long sess, int key_frame_index, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_seek_by_key_frame_index(sess, key_frame_index);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_switch_stream_type(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_switch_stream_type(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_play_mode(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_play_mode(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_video_proportion(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_video_proportion(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_video_mouse_event(float x, float y, float s, int mode, long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_video_mouse_event(x, y, s, mode, sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_fishsye_mode(long sess, int type, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_fishsye_mode(sess, type);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_fisheye_ptz_control(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_fisheye_ptz_control(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_window_in_zoom_status(long sess, Promise promise) {
        try {
            boolean result = JniRsSdkWrapper.rs_window_in_zoom_status(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_window_set_scale_size(long sess, float scaleSize, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_window_set_scale_size(sess, scaleSize);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_query_param(long dev, String param, Promise promise) {
        try {
            String result = JniRsSdkWrapper.rs_query_param(dev, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_set_param(long dev, String param, String buf, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_set_param(dev, param, buf);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_ptz_control(long dev, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_ptz_control(dev, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_remote_test(long dev, int type, String param, Object user_param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_remote_test(dev, type, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_talk_to_device(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_talk_to_device(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_talk_to_channel(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_talk_to_channel(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_talk(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_talk(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_delete_playback_thumbnails(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_delete_playback_thumbnails(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_playback_thumbnails(long dev, String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_playback_thumbnails(dev, param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_playback_thumbnails(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_playback_thumbnails(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_local_playback_thumbnails(String param, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_local_playback_thumbnails(param, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_input_local_playback_time(long sess, long millisecond, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_input_local_playback_time(sess, millisecond);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_local_playback_thumbnails(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_local_playback_thumbnails(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_reset_connection(long dev, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_reset_connection(dev);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_human_face_alarm_report(long dev, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_human_face_alarm_report(dev, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_human_face_alarm_report(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_human_face_alarm_report(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_start_human_face_param(long dev, Object user_param, Promise promise) {
        try {
            long result = JniRsSdkWrapper.rs_start_human_face_param(dev, user_param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_send_human_face_param(long sess, String param, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_send_human_face_param(sess, param);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_stop_human_face_param(long sess, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_stop_human_face_param(sess);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_send_simple_command(long dev, int main_msg, int sub_msg, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_send_simple_command(dev, main_msg, sub_msg);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_sync_playback_add_session(long sync_sess, long session, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_sync_playback_add_session(sync_sess, session);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @ReactMethod
    public void rs_sync_playback_del_session(long sync_sess, long session, Promise promise) {
        try {
            int result = JniRsSdkWrapper.rs_sync_playback_del_session(sync_sess, session);
            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("RsSdkReactJavaModule error", "Error occurred while executing function ``: ", e);
        }
    }

    @Override
    public void search_record_month_callback(String param) {
        Log.e(TAG, "Called `search_record_month_callback` with param: " + param);
    }

    @Override
    public void search_record_day_callback(String param) {
        Log.e(TAG, "Called `search_record_day_callback` with param: " + param);
    }

    public void preview_callback(String param) {
        Log.e(TAG, "Called `preview_callback` with param: " + param);
    }
}

