             #include "SDKWrapper.h"
#include "../Include/RSSDKWrapper.h"
#include "../Include/RSParameter.h"
#include "../Include/correction_type.h"
#include    "../JsonCpp/json.h"
#include <android/log.h>
/************************************************************************************/
#ifdef __ANDROID__

#define RSPLAY_API
#define RSPLAY_CALL
#define TRACE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "TAG", __VA_ARGS__))

typedef unsigned long RSPlayHandle;

typedef struct _JVMInfo_ {
	void*       jvm;
	const char* jni_class;
	char        reserve[256];
}JVMInfo;

typedef enum {
    rs_mouse_unknown = -1,
    rs_mouse_move = 0,
    rs_mouse_wheel,
    rs_mouse_down,
    rs_mouse_up,
    rs_mouse_double_click
}rs_mouse_event;

/*******************************/
typedef struct {
    int picture_width;
    int picture_height;
    int zoom_left;
    int zoom_top;
    int zoom_width;
    int zoom_height;
    char reserve[64];
}RSPlayZoomCallbackInfo;

typedef void (CALLBACK* RSPLAY_ZOOM_CALLBACK)(const RSPlayZoomCallbackInfo* info, void* user_param);

typedef struct {
    RSPLAY_ZOOM_CALLBACK zoom_cb;
    void*         user_param;
    char          reserve[64];
}RSPlayZoomCallbackParam;
/*******************************/

#ifdef __cplusplus
extern "C" {
#endif

RSPLAY_API void RSPLAY_CALL RSPlayAndroidSetJVM(void* jvm);
RSPLAY_API void RSPLAY_CALL RSPlayAndroidSetJVMInfo(const JVMInfo* info);
RSPLAY_API RSPlayHandle RSPLAY_CALL RSPlayAndroidSurfaceCreate();
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceDestory(RSPlayHandle handle);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceChange(RSPlayHandle handle, int width, int height);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceDraw(RSPlayHandle handle, void* picture);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceDrawWithBlack(RSPlayHandle handle);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceCapturePicture(RSPlayHandle handle, const char* picture_name);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceSetVideoProportion(RSPlayHandle handle, int proportion);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceVideoMouseEvent(RSPlayHandle handle, float x, float y, float s, rs_mouse_event mouse_event);

RSPLAY_API int RSPLAY_CALL RSPlayAndroidSetFishMode(RSPlayHandle handle, FISHEYE_COMB_TYPE_E type);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSetFishContro(RSPlayHandle handle, FISH_CONTROL_REQ_S* req);

RSPLAY_API bool RSPLAY_CALL RSPlayAndroidWindowInZoomStatus(RSPlayHandle handle);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSetScaleSize(RSPlayHandle handle, float scaleSize);
RSPLAY_API void RSPLAY_CALL RSPlayAndroidSetZoomCallback(RSPlayHandle handle, const RSPlayZoomCallbackParam* param);

#ifdef __cplusplus
}
#endif // end of extern "C"

#endif
/************************************************************************************/

#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

#ifndef DISALLOW_COPY_AND_ASSIGN
#  define DISALLOW_COPY_AND_ASSIGN(TypeName) \
       TypeName(const TypeName&); \
       TypeName& operator=(const TypeName&)
#endif

class rs_mutex {
    DISALLOW_COPY_AND_ASSIGN(rs_mutex);
public:
    rs_mutex()                  { pthread_mutex_init(&mCriSec,NULL);                       }
    ~rs_mutex()                 { pthread_mutex_destroy(&mCriSec);                         }
    void lock()                 { pthread_mutex_lock(&mCriSec);                            }
    bool try_lock()             { return !pthread_mutex_trylock(&mCriSec) ? true : false;  }
    void unlock()               { pthread_mutex_unlock(&mCriSec);                          }
    pthread_mutex_t* GetMutex() { return &mCriSec;                                         }
private:
    pthread_mutex_t mCriSec;
};

template <class T>
class rs_lock_guard {
    DISALLOW_COPY_AND_ASSIGN(rs_lock_guard);
public:
    typedef T mutex_type;
    explicit rs_lock_guard(mutex_type &aMutex) : mMutex(aMutex) { mMutex.lock(); }
    ~rs_lock_guard() { mMutex.unlock(); }
    
private:
    mutex_type& mMutex;
};
typedef rs_lock_guard<rs_mutex> rs_scoped_lock;
/************************************************************************************/

typedef struct _JNI_GLOBAL_INFO_{
    JavaVM*   vm;
    jclass    jni_help_class;
    jobject   jni_help_object;

    jmethodID search_device_callback;

    jmethodID connction_callback;
    jmethodID alarm_callback;

    jmethodID preview_callback;

    jmethodID search_record_month_callback;
    jmethodID search_record_day_callback;

    jmethodID download_callback_by_file;
    jmethodID download_callback_by_time;

    jmethodID playback_callback_local;
    jmethodID playback_callback_remote;

    jmethodID remote_test_callback;

    jmethodID talk_callback;

    jmethodID playback_thumbnails_callback;

    jmethodID local_thumbnails_callback;

    jmethodID log_sink_callback;

    jmethodID human_face_alarm_report_data_callback;
    jmethodID human_face_alarm_report_status_callback;
    jmethodID human_face_param_status_callback;
    jmethodID human_face_param_data_callback;

    jmethodID zoom_callback;
}JNI_GLOBAL_INFO;
JNI_GLOBAL_INFO g_ctx;

typedef struct {
    jobject user_param;
}THIS_TO_JOBJECT;
std::map<session_id, THIS_TO_JOBJECT>   g_this_object;

static void del_object_form_global_map(JNIEnv* env, const THIS_TO_JOBJECT& obj) {
    if (obj.user_param)
        env->DeleteGlobalRef(obj.user_param);
}

#include <set>
#define MAX_PLAYBACK_CHANNEL       64
rs_mutex                           g_render_mutex;
std::map<session_id, RSPlayHandle> g_preview_render; //preview_id -> AndroidRenderES3
std::set<session_id>               g_preview_session_ids;
std::map<session_id, std::vector<session_id>> g_sync_playback_ids;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    RSPlayAndroidSetJVM(vm);

    JVMInfo info = {0};
    info.jvm = vm;
    info.jni_class = JNI_HELP_CLASS;
    RSPlayAndroidSetJVMInfo(&info);

    memset(&g_ctx, 0, sizeof(g_ctx));
    g_ctx.vm = vm;

    JNIEnv* env;
    if ((*vm).GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }

    jclass clz = (*env).FindClass(JNI_HELP_CLASS);
    g_ctx.jni_help_class = (jclass)((*env).NewGlobalRef(clz));

    //all callback function
    g_ctx.search_device_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "search_device_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.connction_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "connction_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.alarm_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "alarm_callback", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.preview_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "preview_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.search_record_month_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "search_record_month_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.search_record_day_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "search_record_day_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.download_callback_by_file = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "download_callback_by_file", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.download_callback_by_time = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "download_callback_by_time", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.playback_callback_local = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "playback_callback_local", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.playback_callback_remote = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "playback_callback_remote", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.remote_test_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "remote_test_callback", "(ILjava/lang/String;Ljava/lang/Object;)V");
    g_ctx.talk_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "talk_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.playback_thumbnails_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "playback_thumbnails_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.local_thumbnails_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "local_thumbnails_callback", "([BLjava/lang/Object;)V");
    g_ctx.log_sink_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "log_sink_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");

    g_ctx.human_face_alarm_report_data_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "human_face_alarm_report_data_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.human_face_alarm_report_status_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "human_face_alarm_report_status_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.human_face_param_status_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "human_face_param_status_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    g_ctx.human_face_param_data_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "human_face_param_data_callback", "([BLjava/lang/Object;)V");

    g_ctx.zoom_callback = (*env).GetStaticMethodID(g_ctx.jni_help_class, \
        "zoom_callback", "(Ljava/lang/String;Ljava/lang/Object;)V");

    return  JNI_VERSION_1_6;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1android_1surface_1create)(JNI_DEFAULT_PARAM) {
    RSPlayHandle render = RSPlayAndroidSurfaceCreate();
    return render;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1destory)(JNI_DEFAULT_PARAM, jlong surface_id) {
    RSPlayHandle render = (RSPlayHandle)surface_id;
    if (render) {
        RSPlayAndroidSurfaceDestory(render);

        std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)render);
        if (itor != g_this_object.end()) {
            const THIS_TO_JOBJECT& obj = itor->second;
            del_object_form_global_map(env, obj);
            g_this_object.erase(itor);
        }
    }
    return 0;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1change)(JNI_DEFAULT_PARAM, jlong surface_id, int width, int height, jlong preview_id) {
    RSPlayHandle render = (RSPlayHandle)surface_id;
    if (render)
        RSPlayAndroidSurfaceChange(render, width, height);
    return 0;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1draw)(JNI_DEFAULT_PARAM, jlong surface_id, jlong preview_id) {
    RSPlayHandle render = (RSPlayHandle)surface_id;
    if (render) {
        {
            rs_scoped_lock lock(g_render_mutex);
            if (render && preview_id) {
                std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)preview_id);
                if (itor == g_preview_render.end()) {
                    g_preview_render.insert(std::make_pair((session_id)preview_id, render));
                } else {
                    if (itor->second != render) {
                        itor->second = render;
                    }
                }
            }

            if (g_preview_session_ids.find((session_id)preview_id) == g_preview_session_ids.end())
                preview_id = 0;
        }
        bool find_preview_session = true;
        void* picture = rs_get_decoded_frame((session_id)preview_id, &find_preview_session);
        if (picture) {
            RSPlayAndroidSurfaceDraw(render, picture);
        } else if (!find_preview_session) {
            RSPlayAndroidSurfaceDrawWithBlack(render);
        } else {
            RSPlayAndroidSurfaceDraw(render, NULL);
        }
    }
    return 0;
}

static void callback_to_app(jmethodID id, const char* param, void* user_param);
static void CALLBACK RSPLAY_ZOOM_CALLBACK_fun(const RSPlayZoomCallbackInfo* info, void* user_param) {
    Json::Value value;
    value["picture width"] = info->picture_width;
    value["picture height"] = info->picture_height;
    value["zoom left"] = info->zoom_left;
    value["zoom top"] = info->zoom_top;
    value["zoom width"] = info->zoom_width;
    value["zoom height"] = info->zoom_height;
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);

    callback_to_app(g_ctx.zoom_callback, param.c_str(), user_param);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1set_1user_1param)(JNI_DEFAULT_PARAM, jlong surface_id, jobject user_param) {
    RSPlayHandle render = (RSPlayHandle)surface_id;
    if (render) {
        THIS_TO_JOBJECT obj = { 0 };
        obj.user_param = env->NewGlobalRef(user_param);

        RSPlayZoomCallbackParam param = { 0 };
        param.zoom_cb = RSPLAY_ZOOM_CALLBACK_fun;
        param.user_param = obj.user_param;
        RSPlayAndroidSetZoomCallback(render, &param);

        g_this_object.insert(std::make_pair((session_id)surface_id, obj));
    }

    return 0;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1destroy_1user_1param)(JNI_DEFAULT_PARAM, jlong surface_id) {
    RSPlayHandle render = (RSPlayHandle)surface_id;
    if (render) {

        std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)render);
        if (itor != g_this_object.end()) {
            const THIS_TO_JOBJECT& obj = itor->second;
            del_object_form_global_map(env, obj);
            g_this_object.erase(itor);
        }
    }
    return 0;
}

static jstring getJStringFromCString(JNIEnv *env, const char *str) {
    if (str == NULL) {
        return NULL;
    } else {
        jbyteArray array = env->NewByteArray(strlen(str));
        env->SetByteArrayRegion(array, 0, strlen(str), (const jbyte*)str);
        jstring strEncode = env->NewStringUTF("UTF-8");
        jclass cls = env->FindClass("java/lang/String");
        jmethodID ctor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;)V");
        jstring object = (jstring) env->NewObject(cls, ctor, array, strEncode);

        env->DeleteLocalRef(array);
        env->DeleteLocalRef(strEncode);
        return object;
    }
}

static void callback_to_app(jmethodID id, const char* param, void* user_param) {
    if (id) {
        bool attached = false;
        JNIEnv *env = NULL;
        jint res = (*g_ctx.vm).GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = (*g_ctx.vm).AttachCurrentThread(&env, NULL);
            if (JNI_OK != res)
                return;
            attached = true;
        }

        //jstring _param = (*env).NewStringUTF(param);
        jstring _param = getJStringFromCString(env, param);
        (*env).CallStaticVoidMethod(g_ctx.jni_help_class, id, _param, user_param);
        (*env).DeleteLocalRef(_param);
        if (attached)
            (*g_ctx.vm).DetachCurrentThread();
    }
}

static void callback_to_app(jmethodID id, const char* param1, const char* param2, void* user_param) {
    if (id) {
        bool attached = false;
        JNIEnv *env = NULL;
        jint res = (*g_ctx.vm).GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = (*g_ctx.vm).AttachCurrentThread(&env, NULL);
            if (JNI_OK != res)
                return;
            attached = true;
        }

        //jstring _param1 = (*env).NewStringUTF(param1);
        //jstring _param2 = (*env).NewStringUTF(param2);
        jstring _param1 = getJStringFromCString(env, param1);
        jstring _param2 = getJStringFromCString(env, param2);
        (*env).CallStaticVoidMethod(g_ctx.jni_help_class, id, _param1, _param2, user_param);
        (*env).DeleteLocalRef(_param1);
        (*env).DeleteLocalRef(_param2);
        if (attached)
            (*g_ctx.vm).DetachCurrentThread();
    }
}

static void callback_to_app(jmethodID id, unsigned int param1, const char* param2, void* user_param) {
    if (id) {
        bool attached = false;
        JNIEnv *env = NULL;
        jint res = (*g_ctx.vm).GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = (*g_ctx.vm).AttachCurrentThread(&env, NULL);
            if (JNI_OK != res)
                return;
            attached = true;
        }

        //jstring _param2 = (*env).NewStringUTF(param2);
        jstring _param2 = getJStringFromCString(env, param2);
        (*env).CallStaticVoidMethod(g_ctx.jni_help_class, id, param1, _param2, user_param);
        (*env).DeleteLocalRef(_param2);
        if (attached)
            (*g_ctx.vm).DetachCurrentThread();
    }
}

static void callback_to_app(jmethodID id, unsigned char* data, unsigned int size, const char* param, void* user_param) {
    if (id) {
        bool attached = false;
        JNIEnv *env = NULL;
        jint res = (*g_ctx.vm).GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = (*g_ctx.vm).AttachCurrentThread(&env, NULL);
            if (JNI_OK != res)
                return;
            attached = true;
        }
        jbyteArray temp = (*env).NewByteArray(size);
        (*env).SetByteArrayRegion(temp, 0, size, (jbyte *) data);

        (*env).CallStaticVoidMethod(g_ctx.jni_help_class, id, temp, user_param);
        (*env).DeleteLocalRef(temp);
        if (attached)
            (*g_ctx.vm).DetachCurrentThread();
    }
}

static void callback_to_app(jmethodID id, const char* data, unsigned int size, void* user_param) {
    if (id) {
        bool attached = false;
        JNIEnv *env = NULL;
        jint res = (*g_ctx.vm).GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = (*g_ctx.vm).AttachCurrentThread(&env, NULL);
            if (JNI_OK != res)
                return;
            attached = true;
        }
        jbyteArray  temp = env->NewByteArray(size);
        env->SetByteArrayRegion(temp, 0, size, (jbyte *) data);

        (*env).CallStaticVoidMethod(g_ctx.jni_help_class, id, temp, user_param);
        (*env).DeleteLocalRef(temp);
        if (attached)
            (*g_ctx.vm).DetachCurrentThread();
    }
}

static void RSNET_CALL search_device_callback_fun(const char* param, void* user_param) {
    callback_to_app(g_ctx.search_device_callback, param, user_param);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1sdk_1wrapper_1init)(JNI_DEFAULT_PARAM, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_sdk_wrapper_init(native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1sdk_1wrapper_1uninit)(JNI_DEFAULT_PARAM, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_sdk_wrapper_uninit(native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1init_1log)(JNI_DEFAULT_PARAM, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_init_log(native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

static void RSNET_CALL log_sink_callback_fun(const char* param, void* user_param) {
    callback_to_app(g_ctx.log_sink_callback, param, user_param);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1init_1log_1ex)(JNI_DEFAULT_PARAM, jstring param, jobject user_param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);

    init_log_ex_param obj = {0};
    obj.param = native_string;
    obj.bugly_callback = log_sink_callback_fun;

    rs_error_code result = rs_init_log_ex(&obj);
    env->ReleaseStringUTFChars(param, native_string);

    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1search_1device)(JNI_DEFAULT_PARAM, jstring param, jobject user_param) {
    {
        std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)1);
        if (itor != g_this_object.end()) {
            const THIS_TO_JOBJECT& obj = itor->second;
            del_object_form_global_map(env, obj);
            g_this_object.erase(itor);
        }
    }

    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);
    g_this_object.insert(std::make_pair((session_id)1, obj));

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_search_device(native_string, search_device_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1modify_1device)(JNI_DEFAULT_PARAM, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_modify_device(native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1create_1device)(JNI_DEFAULT_PARAM) {
    return (jlong)rs_create_device();
}

JNI_INT_RETURN JNI_FUNCTION(rs_1destroy_1device)(JNI_DEFAULT_PARAM, jlong dev) {
    return rs_destroy_device((device_id)dev);
}

static void RSNET_CALL connction_callback_fun(const char* param, void* user_param) {
//    TRACE("======connction_callback_fun param = %s ,user_param = %s\n",param,user_param);
    callback_to_app(g_ctx.connction_callback, param, user_param);
}

static void RSNET_CALL alarm_callback_fun(const char* alarm_type, const char* param, void* user_param) {
    callback_to_app(g_ctx.alarm_callback, alarm_type, param, user_param);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1device_1login)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_device_login((device_id)dev, native_string, connction_callback_fun, alarm_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (result == rs_success) {
        g_this_object.insert(std::make_pair((device_id)dev, obj));
    }else{
        del_object_form_global_map(env, obj);
    }
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1device_1login_1ex)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

//    sdk_wrapper_log("enter rs_1device_1login_1ex, user_param: %p\n", user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);

    device_login_param login_param = {0};
    login_param.dev = (device_id)dev;
    login_param.conn_cb = connction_callback_fun;
    login_param.alarm_cb = alarm_callback_fun;
//    login_param.alarm_cb_ex = alarm_callback_ex_fun;
    login_param.user_param = obj.user_param;
    login_param.param = native_string;
    rs_error_code result = rs_device_login_ex(&login_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (result == rs_success) {
        g_this_object.insert(std::make_pair((device_id)dev, obj));
    }else{
        del_object_form_global_map(env, obj);
    }
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1device_1logout)(JNI_DEFAULT_PARAM, jlong dev) {
    rs_error_code result = rs_device_logout((device_id)dev);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((device_id)dev);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

JNI_STR_RETURN JNI_FUNCTION(rs_1get_1login_1rsp)(JNI_DEFAULT_PARAM, jlong dev) {
    char* temp = new char[100*1024];
    rs_error_code result = rs_get_login_rsp((device_id)dev, temp, 100*1024);
    jstring login_rsp = (*env).NewStringUTF(temp);
    delete[] temp;
    return login_rsp;
}

static void RSNET_CALL preivew_callback_fun(const char* param, void* user_param) {
    callback_to_app(g_ctx.preview_callback, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1preview)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    preview_param _param = {0};
    _param.dev = (device_id)dev;
    _param.param = native_string;
    _param.window = (HWND)0x1;
    _param.preview_cb = preivew_callback_fun;
    _param.preview_user_param = obj.user_param;
    session_id preview_id = rs_start_preview(&_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (preview_id) {
        g_this_object.insert(std::make_pair(preview_id, obj));
        rs_scoped_lock lock(g_render_mutex);
        g_preview_session_ids.insert(preview_id);
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)preview_id;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1preview)(JNI_DEFAULT_PARAM, jlong sess) {
    {
        rs_scoped_lock lock(g_render_mutex);
        std::set<session_id>::iterator itor = g_preview_session_ids.find((session_id)sess);
        if (itor != g_preview_session_ids.end()) {
            g_preview_session_ids.erase(itor);
        }
    }
    rs_error_code result = rs_stop_preview((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

static void RSNET_CALL search_record_month_callback_fun(const char* param, void* user_param) {
    callback_to_app(g_ctx.search_record_month_callback, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1search_1record_1by_1month)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id search_record_id = rs_search_record_by_month((device_id)dev, native_string, search_record_month_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (search_record_id) {
        g_this_object.insert(std::make_pair(search_record_id, obj));
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)search_record_id;
}

static void RSNET_CALL search_record_day_callback_fun(const char* param, void* user_param) {
    callback_to_app(g_ctx.search_record_day_callback, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1search_1record_1by_1day)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id search_record_id = rs_search_record_by_day((device_id)dev, native_string, search_record_day_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (search_record_id) {
        g_this_object.insert(std::make_pair(search_record_id, obj));
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)search_record_id;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1search_1record)(JNI_DEFAULT_PARAM, jlong sess) {
    rs_error_code result = rs_stop_search_record((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

static void RSNET_CALL download_callback_by_file(const char* param, void* user_param) {
    callback_to_app(g_ctx.download_callback_by_file, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1download_1by_1file)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id download_id = rs_start_download_by_file((device_id)dev, native_string, download_callback_by_file, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (download_id) {
        g_this_object.insert(std::make_pair(download_id, obj));
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)download_id;
}

static void RSNET_CALL download_callback_by_time(const char* param, void* user_param) {
    callback_to_app(g_ctx.download_callback_by_time, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1download_1by_1time)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id download_id = rs_start_download_by_time((device_id)dev, native_string, download_callback_by_time, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (download_id) {
        g_this_object.insert(std::make_pair(download_id, obj));
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)download_id;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1download)(JNI_DEFAULT_PARAM, jlong sess) {
    rs_error_code result = rs_stop_download((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

static void RSNET_CALL playback_callback_local(const char* param, void* user_param) {
    callback_to_app(g_ctx.playback_callback_local, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1local_1playback)(JNI_DEFAULT_PARAM, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    local_playback_param _param = {0};
    _param.param = native_string;
    _param.window = (HWND)0x1;
    _param.playback_cb = playback_callback_local;
    _param.playback_user_param = obj.user_param;
    session_id preview_id = rs_start_local_playback(&_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (preview_id) {
        g_this_object.insert(std::make_pair(preview_id, obj));
        rs_scoped_lock lock(g_render_mutex);
        g_preview_session_ids.insert(preview_id);
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)preview_id;
}

static void RSNET_CALL playback_callback_remote(const char* param, void* user_param) {
    callback_to_app(g_ctx.playback_callback_remote, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1remote_1playback)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    remote_playback_param _param = {0};
    _param.dev = (device_id)dev;
    _param.param = native_string;
    _param.window = (HWND)0x1;
    _param.playback_cb = playback_callback_remote;
    _param.playback_user_param = obj.user_param;
    session_id preview_id = rs_start_remote_playback(&_param);
    env->ReleaseStringUTFChars(param, native_string);

    if (preview_id) {
        g_this_object.insert(std::make_pair(preview_id, obj));
        rs_scoped_lock lock(g_render_mutex);
        g_preview_session_ids.insert(preview_id);
    } else {
        del_object_form_global_map(env, obj);
    }

    return (jlong)preview_id;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1sync_1playback)(JNI_DEFAULT_PARAM, jstring user_param) {
    const char* native_string = env->GetStringUTFChars(user_param, JNI_FALSE);
    Json::Reader reader;
    Json::Value obj;
    if (!reader.parse(native_string, obj)) {
        env->ReleaseStringUTFChars(user_param, native_string);
        return 0;
    }

    std::vector<session_id > sync_session;
    for(int i=0; i<obj["sess"].size(); i++) {
        sync_session.push_back((session_id)obj["sess"][i]["session"].asInt64());
    }
    env->ReleaseStringUTFChars(user_param, native_string);
    if (sync_session.size() > MAX_PLAYBACK_CHANNEL)
        return 0;

    sync_playback_param param = {0};
    param.sess = &(sync_session.at(0));
    param.sess_count = obj["sess"].size();
    session_id preview_id = rs_start_sync_playback(&param);
    if (preview_id && sync_session.size()) {
        g_sync_playback_ids.insert(std::make_pair(preview_id, sync_session));
    }

    return (jlong)preview_id;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1playback)(JNI_DEFAULT_PARAM, jlong sess) {
    {
        std::vector<session_id> sync_session;
        std::map<session_id, std::vector<session_id>>::iterator itor = g_sync_playback_ids.find((session_id)sess);
        if (itor != g_sync_playback_ids.end()) {
            sync_session = itor->second;
            g_sync_playback_ids.erase(itor);
        } else {
            sync_session.push_back((session_id)sess);
        }

        rs_scoped_lock lock(g_render_mutex);
        for (auto& preview_sess : sync_session) {
            std::set<session_id>::iterator itor = g_preview_session_ids.find(preview_sess);
            if (itor != g_preview_session_ids.end()) {
                g_preview_session_ids.erase(itor);
            }
        }
    }

    rs_error_code result = rs_stop_playback((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1open_1sound)(JNI_DEFAULT_PARAM, jlong sess) {
    return rs_open_sound((session_id)sess);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1close_1sound)(JNI_DEFAULT_PARAM, jlong sess) {
    return rs_close_sound((session_id)sess);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1volume)(JNI_DEFAULT_PARAM, jlong sess, jint volume) {
    return rs_set_volume((session_id)sess, volume);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1mute_1on)(JNI_DEFAULT_PARAM, jlong sess) {
    return rs_set_mute_on((session_id)sess);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1mute_1off)(JNI_DEFAULT_PARAM, jlong sess) {
    return rs_set_mute_off((session_id)sess);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1start_1record)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_start_record((session_id)sess, native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1record)(JNI_DEFAULT_PARAM, jlong sess) {
    return rs_stop_record((session_id)sess);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1capture_1picture)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render) {
        const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
        std::string _param = native_string;
        env->ReleaseStringUTFChars(param, native_string);

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, _param, &value, &err))
            return rs_parse_json_error;
        std::string picture_name = value["picture name"].asString();
        int result = RSPlayAndroidSurfaceCapturePicture(render, picture_name.c_str());
        return (result == 0) ? rs_success : rs_fail;
    }
    return rs_fail;
}

JNI_STR_RETURN JNI_FUNCTION(rs_1get_1file_1time)(JNI_DEFAULT_PARAM, jstring filename) {
    char temp[256] = {0};
    const char *path = NULL;
    path = env->GetStringUTFChars(filename, 0);
    rs_error_code result = rs_get_file_time(path, temp, sizeof(temp));
    jstring current_time = (*env).NewStringUTF(temp);
    env->ReleaseStringUTFChars(filename, path);
    return current_time;
}

JNI_STR_RETURN JNI_FUNCTION(rs_1get_1current_1time)(JNI_DEFAULT_PARAM, jlong sess) {
    char temp[128] = {0};
    rs_error_code result = rs_get_current_time((session_id)sess, temp, sizeof(temp));
    if (result == rs_success) {
        jstring current_time = (*env).NewStringUTF(temp);
        return current_time;
    }
    return NULL;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1get_1current_1time_1millisecond)(JNI_DEFAULT_PARAM, jlong sess) {
    jlong result = rs_get_current_time_millisecond((session_id)sess);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1seek_1by_1time)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_seek_by_time((session_id)sess, native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1get_1file_1key_1frame_1count)(JNI_DEFAULT_PARAM, jstring filename) {
    char temp[256] = {0};
    const char *path = NULL;
    path = env->GetStringUTFChars(filename, 0);
    jint result = rs_get_file_key_frame_count(path);
    env->ReleaseStringUTFChars(filename, path);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1seek_1by_1key_1frame_1index)(JNI_DEFAULT_PARAM, jlong sess, jint key_frame_index) {
    rs_error_code result = rs_seek_by_key_frame_index((session_id)sess, key_frame_index);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1switch_1stream_1type)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_switch_stream_type((session_id)sess, native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1play_1mode)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_set_play_mode((session_id)sess, native_string);
    env->ReleaseStringUTFChars(param, native_string);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1video_1proportion)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render) {
        const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
        std::string _param = native_string;
        env->ReleaseStringUTFChars(param, native_string);

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, _param, &value, &err))
            return rs_parse_json_error;

        std::string video_proportion = value["proportion"].asString();
        if (!video_proportion.empty()) {
            int proportion = 0;
            if (video_proportion == "full window")
                proportion = 0;
            else if (video_proportion == "picture proportion")
                proportion = 1;
            else if (video_proportion == "4:3 proportion")
                proportion = 2;
            else if (video_proportion == "16:9 proportion")
                proportion = 3;

            int result = RSPlayAndroidSurfaceSetVideoProportion(render, proportion);
            return (result == 0) ? rs_success : rs_fail;
        }
    }
    return rs_fail;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1video_1mouse_1event)(JNI_DEFAULT_PARAM, jfloat x, jfloat y, jfloat s, jint mouse_event, jlong sess) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render) {
        int result = RSPlayAndroidSurfaceVideoMouseEvent(render, x, y, s, (rs_mouse_event)mouse_event);
        return (result == 0) ? rs_success : rs_fail;
    }

    return rs_fail;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1fishsye_1mode)(JNI_DEFAULT_PARAM, jlong sess, jint type) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render) {
        int result = RSPlayAndroidSetFishMode(render, (FISHEYE_COMB_TYPE_E) type);
        return (result == 0) ? rs_success : rs_fail;
    }
    return rs_fail;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1fisheye_1ptz_1control)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render) {
        const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
        std::string _param = native_string;
        env->ReleaseStringUTFChars(param, native_string);

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, _param, &value, &err))
            return rs_parse_json_error;

        int speed = value["speed"].asInt();
        std::string operation = value["operation"].asString();
        std::string flag = value["flag"].asString();

        FISH_PTZ_E _operation = FISH_PTZ_BUTT;
        if (operation == "left")
            _operation = FISH_PTZ_LEFT;
        else if (operation == "up left")
            _operation = FISH_PTZ_LEFTUP;
        else if (operation == "up")
            _operation = FISH_PTZ_UP;
        else if (operation == "up right")
            _operation = FISH_PTZ_RIGHTUP;
        else if (operation == "right")
            _operation = FISH_PTZ_RIGHT;
        else if (operation == "down right")
            _operation = FISH_PTZ_RIGHTDOWN;
        else if (operation == "down")
            _operation = FISH_PTZ_DOWN;
        else if (operation == "down left")
            _operation = FISH_PTZ_LEFTDOWN;
        else if (operation == "zoom out")
            _operation = FISH_PTZ_ZOOMDEC;
        else if (operation == "zoom in")
            _operation = FISH_PTZ_ZOOMINC;
        else if (operation == "auto scan")
            _operation = FISH_PTZ_CURISE;

        bool _flag = false;
        if (flag == "start")
            _flag = true;
        else if (flag == "stop")
            _flag = false;

        if (_operation == FISH_PTZ_BUTT)
            return rs_parse_json_error;

        FISH_CONTROL_REQ_S req = {0};
        req.eFlag = FISH_EYE_PTZ_E;
        req.stPtz.eFlag = _operation;
        req.stPtz.speed = (float)speed/10;
        if(_operation == FISH_PTZ_ZOOMDEC)
            req.stPtz.k = -1;
        else if(_operation == FISH_PTZ_ZOOMINC)
            req.stPtz.k = 1;
        req.stPtz.bEnable = _flag;
        RSPlayAndroidSetFishContro(render, &req);

        return rs_success;
    }
    return rs_fail;
}

JNI_BOL_RETURN JNI_FUNCTION(rs_1window_1in_1zoom_1status)(JNI_DEFAULT_PARAM, jlong sess) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render)
        return RSPlayAndroidWindowInZoomStatus(render) ? JNI_TRUE : JNI_FALSE;
    return JNI_FALSE;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1window_1set_1scale_1size)(JNI_DEFAULT_PARAM, jlong sess, jfloat scaleSize) {
    RSPlayHandle render = NULL;
    {
        rs_scoped_lock lock(g_render_mutex);
        std::map<session_id, RSPlayHandle>::iterator itor = g_preview_render.find((session_id)sess);
        if (itor != g_preview_render.end())
            render = itor->second;
    }

    if (render) {
        int result = RSPlayAndroidSetScaleSize(render, scaleSize);
        return (result == 0) ? rs_success : rs_fail;
    }
    return rs_fail;
}

JNI_STR_RETURN JNI_FUNCTION(rs_1query_1param)(JNI_DEFAULT_PARAM, jlong dev, jstring param) {
    const char* native_param = env->GetStringUTFChars(param, JNI_FALSE);
    char *temp = new char[5*1024*1024];

    rs_error_code result = rs_query_param((device_id) dev, native_param, temp, 5*1024*1024);
    if (result != rs_success) {
        if (result == rs_no_permission) {
            strcpy(temp, "no_right");
        } else {
            strcpy(temp, "err");
        }
    }
    jstring query_param = (*env).NewStringUTF(temp);

    delete[] temp;
    env->ReleaseStringUTFChars(param, native_param);

    return query_param;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1param)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jstring buf) {
    const char* native_param = env->GetStringUTFChars(param, JNI_FALSE);
    const char* native_buf = env->GetStringUTFChars(buf, JNI_FALSE);

    rs_error_code result = rs_set_param((device_id)dev, native_param, native_buf);

    env->ReleaseStringUTFChars(param, native_param);
    env->ReleaseStringUTFChars(param, native_buf);

    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1ptz_1control)(JNI_DEFAULT_PARAM, jlong dev, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_ptz_control((device_id)dev, native_string);
    env->ReleaseStringUTFChars(param, native_string);

    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1new_1ptz_1control)(JNI_DEFAULT_PARAM, jlong dev, jstring param) {
    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_new_ptz_control((device_id)dev, native_string);
    env->ReleaseStringUTFChars(param, native_string);

    return result;
}

static void RSNET_CALL remote_test_callback_fun(unsigned int type, const char* param, void* user_param) {
    //LOGE("==remote_test_callback===type:%d=param:%s",type, param);
    callback_to_app(g_ctx.remote_test_callback, type, param, user_param);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1remote_1test)(JNI_DEFAULT_PARAM, jlong dev, jint msg_type, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    //obj.user_param = env->NewGlobalRef(user_param);
    obj.user_param = env->NewWeakGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_remote_test((device_id)dev, msg_type, native_string, remote_test_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    return result;
}

static void RSNET_CALL talk_callback_fun(const char* param, void* user_param) {
    //LOGE("==talk_callback_fun====param:%s", param);
    callback_to_app(g_ctx.talk_callback, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1talk_1to_1device)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id result = rs_start_talk_to_device((device_id)dev, native_string, talk_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    return (jlong)result;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1talk_1to_1channel)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id result = rs_start_talk_to_channel((device_id)dev, native_string, talk_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    return (jlong)result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1talk)(JNI_DEFAULT_PARAM, jlong sess) {
    rs_error_code result = rs_stop_talk((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

static void RSNET_CALL playback_thumbnails_callback_fun(const char* param, void* user_param) {
    callback_to_app(g_ctx.playback_thumbnails_callback, param, user_param);
}

JNI_INT_RETURN JNI_FUNCTION(rs_1delete_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong sess, jstring param) {

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    rs_error_code result = rs_delete_playback_thumbnails((session_id)sess, native_string);
    env->ReleaseStringUTFChars(param, native_string);

    return result;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id result = rs_start_playback_thumbnails((device_id)dev, native_string, playback_thumbnails_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    return (jlong)result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong sess) {
    rs_error_code result = rs_stop_playback_thumbnails((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

static void RSNET_CALL local_thumbnails_callback_fun(unsigned char* data, unsigned int size, const char* param, void* user_param) {
    callback_to_app(g_ctx.local_thumbnails_callback, data, size, param, user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1local_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jstring param, jobject user_param) {
    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id result = rs_start_local_playback_thumbnails(native_string, local_thumbnails_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    return (jlong)result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1input_1local_1playback_1time)(JNI_DEFAULT_PARAM, jlong sess, jlong millisecond) {
    int result = rs_input_local_playback_time((session_id)sess, millisecond);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1local_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong sess) {
    rs_error_code result = rs_stop_local_playback_thumbnails((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1reset_1connection)(JNI_DEFAULT_PARAM, jlong dev) {
    int result = rs_reset_connection((device_id)dev);
    return result;
}

static void RSNET_CALL human_face_alarm_report_data_callback_fun(const char *data, int size, const char* param, void *user_param) {
    callback_to_app(g_ctx.human_face_alarm_report_data_callback,data,user_param);
}

static void RSNET_CALL human_face_alarm_report_status_callback_fun(const char *param, void *user_param) {
    callback_to_app(g_ctx.human_face_alarm_report_status_callback,param,user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1human_1face_1alarm_1report)(JNI_DEFAULT_PARAM,jlong dev, jobject user_param) {
    human_face_alarm_report_param param = {0};
    param.dev = (device_id)dev;
    param.user_param = env->NewGlobalRef(user_param);
    param.data_callback = human_face_alarm_report_data_callback_fun;
    param.status_callback = human_face_alarm_report_status_callback_fun;

    session_id result = rs_start_human_face_alarm_report(&param);
    return (jlong)result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1human_1face_1alarm_1report)(JNI_DEFAULT_PARAM,jlong sess) {
    rs_error_code result = rs_stop_human_face_alarm_report((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

static void RSNET_CALL human_face_param_data_callback_fun(const char* param, int size, void* user_param) {
    //LOGE("===========>> human_face_param_data_callback_fun");
    callback_to_app(g_ctx.human_face_param_data_callback,param,size,user_param);
}

static void RSNET_CALL human_face_param_status_callback_fun(const char *param, void *user_param) {
    //LOGE("===========>> human_face_param_status_callback_fun");
    callback_to_app(g_ctx.human_face_param_status_callback,param,user_param);
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1human_1face_1param)(JNI_DEFAULT_PARAM,jlong dev,jobject user_param) {
    human_face_param param = {0};
    param.dev = (device_id)dev;
    param.user_param = env->NewGlobalRef(user_param);
    param.data_callback = human_face_param_data_callback_fun;
    param.status_callback = human_face_param_status_callback_fun;

    session_id result = rs_start_human_face_param(&param);
    return (jlong)result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1send_1human_1face_1param)(JNI_DEFAULT_PARAM,jlong sess,jstring param) {
    const char *native_string = env->GetStringUTFChars(param, JNI_FALSE);
    int result = rs_send_human_face_param((session_id)sess, native_string, strlen(native_string));
    env->ReleaseStringUTFChars(param, native_string);

    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1human_1face_1param)(JNI_DEFAULT_PARAM,jlong sess) {
    rs_error_code result = rs_stop_human_face_param((session_id)sess);
    std::map<session_id, THIS_TO_JOBJECT>::iterator itor = g_this_object.find((session_id)sess);
    if (itor != g_this_object.end()) {
        const THIS_TO_JOBJECT& obj = itor->second;
        del_object_form_global_map(env, obj);
        g_this_object.erase(itor);
    }
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1send_1simple_1command)(JNI_DEFAULT_PARAM, jlong dev, jint main_msg,
                                                       jint sub_msg,
                                                       jstring param) {

        ZeroChnStatReq req;
        memset(&req, 0x0, sizeof(ZeroChnStatReq));

        simple_command_param simple_command_param1 = {0};
        simple_command_param1.main_msg = main_msg;
        simple_command_param1.sub_msg = sub_msg;

        if (MsgZeroChnStatus == main_msg) {

            const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
            Json::Reader reader;
            Json::Value obj;
            if (!reader.parse(native_string, obj)) {
                env->ReleaseStringUTFChars(param, native_string);
                return 0;
            }
            int previewMode = obj["PreviewMode"].asUInt();
            int channel = obj["Channel"].asUInt();

            env->ReleaseStringUTFChars(param, native_string);


            req.StructSize = sizeof(ZeroChnStatReq);
            req.ReqType = 1;
            req.PreviewMode = previewMode;
            if (previewMode) {
                req.EncodeCh = channel;
            } else {
                req.EncodeCh = 200;
            }
            simple_command_param1.param = &req;
            simple_command_param1.param_size = sizeof(ZeroChnStatReq);
        }

        rs_error_code result = rs_send_simple_command((device_id) dev, &simple_command_param1);
        return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1sync_1playback_1add_1session)(JNI_DEFAULT_PARAM, jlong sync_session,
                                                              jlong session) {
    std::map<session_id, std::vector<session_id>>::iterator itor = g_sync_playback_ids.find((session_id)sync_session);
    if (itor != g_sync_playback_ids.end()) {
        auto& vec = itor->second;
        vec.push_back((session_id)session);
    }

    rs_error_code result = rs_sync_playback_add_session((session_id)sync_session, (session_id)session);
    return result;
}

JNI_INT_RETURN JNI_FUNCTION(rs_1sync_1playback_1del_1session)(JNI_DEFAULT_PARAM, jlong sync_session,
                                                              jlong session) {
    {
        rs_scoped_lock lock(g_render_mutex);
        std::set<session_id>::iterator itor = g_preview_session_ids.find((session_id)session);
        if (itor != g_preview_session_ids.end()) {
            g_preview_session_ids.erase(itor);
        }
    }
    
    rs_error_code result = rs_sync_playback_del_session((session_id)sync_session, (session_id)session);
    return result;
}

JNI_STR_RETURN JNI_FUNCTION(rs_1get_1stream_1info)(JNI_DEFAULT_PARAM, jlong sess) {
    int length = 100;
    char *temp = new char[length];

    rs_error_code result = rs_get_stream_info((device_id) sess, temp, length);
    if (result != rs_success) {
        strcpy(temp, "err");
    }
    jstring stream_info = (*env).NewStringUTF(temp);

    delete[] temp;

    return stream_info;
}

JNI_STR_RETURN JNI_FUNCTION(rs_1get_1net_1stream_1info)(JNI_DEFAULT_PARAM, jlong sess) {
    int length = 100;
    char *temp = new char[length];

    rs_error_code result = rs_get_net_stream_info((device_id) sess, temp, length);
    if (result != rs_success) {
        strcpy(temp, "err");
    }
    jstring stream_info = (*env).NewStringUTF(temp);

    delete[] temp;

    return stream_info;
}

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1playback_1thumbnails_1index)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param){

    THIS_TO_JOBJECT obj = {0};
    obj.user_param = env->NewGlobalRef(user_param);

    const char* native_string = env->GetStringUTFChars(param, JNI_FALSE);
    session_id result = rs_start_playback_thumbnails_index((device_id)dev, native_string, playback_thumbnails_callback_fun, obj.user_param);
    env->ReleaseStringUTFChars(param, native_string);

    return (jlong)result;
}