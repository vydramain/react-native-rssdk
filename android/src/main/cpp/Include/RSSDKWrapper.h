#ifndef __RSSDKWRAPPER_H__
#define __RSSDKWRAPPER_H__

#ifdef _WIN32
# include <windows.h>
#else
# define  CALLBACK
  typedef void*              HWND;
  typedef unsigned long long ULONGLONG;
#endif
#define RSNET_CALL CALLBACK

#ifndef MACRO_rsFISHEYE_COMB_TYPE_E
#  define MACRO_rsFISHEYE_COMB_TYPE_E
typedef enum rsFISHEYE_COMB_TYPE_E
{
    FISH_CEILING_EYE = 0,		//   [FishEye]
    FISH_CEILING_VR,	        //   [VR]
    FISH_CEILING_CYLIND3D,      //   [Cylinder]
    FISH_CEILING_CYLIND360,		//    [Panorama 360]
    FISH_CEILING_CYLIND180,		//   [Panorama 180]
    FISH_CEILING_2PTZ,			//   [2 PTZ]
    FISH_CEILING_4PTZ,			//   [4 PTZ]
    FISH_CEILING_CYLIND360_1PTZ,//   [Panorama 360 + 1 PTZ]
    FISH_CEILING_CYLIND360_3PTZ,//   [Panorama 360 + 3 PTZ]
    FISH_CEILING_CYLIND360_6PTZ,//   [Panorama 360 + 6 PTZ]
    FISH_CEILING_CYLIND360_8PTZ,//   [Panorama 360 + 8 PTZ]
    FISH_CEILING_EYE_3PTZ,		//    [FishEye + 3 PTZ]
    FISH_CEILING_EYE_8PTZ,		//   [FishEye + 8 PTZ]

    FISH_DESKTOP_EYE,			//   [FishEye]
    FISH_DESKTOP_VR,	        //   [VR]
    FISH_DESKTOP_CYLIND3D,      //   [Cylinder]
    FISH_DESKTOP_CYLIND360,		//   [Panorama 360]
    FISH_DESKTOP_CYLIND180,		//   [Panorama 180]
    FISH_DESKTOP_4PTZ,			//   [4 PTZ]
    FISH_DESKTOP_CYLIND360_1PTZ,//   [Panorama 360 + 1 PTZ]
    FISH_DESKTOP_CYLIND360_3PTZ,//   [Panorama 360 + 3 PTZ]
    FISH_DESKTOP_CYLIND360_6PTZ,//   [Panorama 360 + 6 PTZ]
    FISH_DESKTOP_CYLIND360_8PTZ,//   [Panorama 360 + 8 PTZ]
    FISH_DESKTOP_EYE_3PTZ,		//   [FishEye + 3 PTZ]
    FISH_DESKTOP_EYE_8PTZ,		//   [FishEye + 8 PTZ]

    FISH_WALL_EYE,				// FishEye]
    FISH_WALL_VR,               //   [VR]
    FISH_WALL_NORMAL,			//   [Panorama]
    FISH_WALL_4PTZ,				// 4 [4 PTZ]
    FISH_WALL_NORMAL_3PTZ,		// 4 [Panorama + 3 PTZ]
    FISH_WALL_NORMAL_8PTZ,		// 9 [Panorama + 8 PTZ]
    FISH_WALL_EYE_3PTZ,			// 4 [FishEye + 3 PTZ]
    FISH_WALL_EYE_8PTZ,			// 9 [FishEye + 8 PTZ]

    FISH_TILT_EYE,				//   [FishEye]
    FISH_TILT_VR,               //   [VR]
    FISH_TILT_NORMAL,			//   [Panorama]
    FISH_TILT_4PTZ,				// 4 [4 PTZ]
    FISH_TILT_NORMAL_3PTZ,		// 4 [Panorama + 3 PTZ]
    FISH_TILT_NORMAL_8PTZ,		// 9 [Panorama + 8 PTZ]
    FISH_TILT_EYE_3PTZ,			// 4 [FishEye + 3 PTZ]
    FISH_TILT_EYE_8PTZ,			// 9 [FishEye + 8 PTZ]

    FISH_COMB_TYPE_BUTT
}FISHEYE_COMB_TYPE_E;
#endif

#ifndef MACRO_SDKWRAPPER_DRAW_INFO
#  define MACRO_SDKWRAPPER_DRAW_INFO
typedef struct {
    void*        window_hdc;
    unsigned int width;
    unsigned int height;
    unsigned int left;
    unsigned int top;
    char         reserve[104];
}SDKWRAPPER_DRAW_INFO;
#endif

#ifndef MACRO_PICTURE_RENDER_INFO
#  define MACRO_PICTURE_RENDER_INFO
typedef struct {
    char* data;
    int   data_length;
    unsigned long long frame_time;
    char  reserve[120];
}PICTURE_RENDER_INFO;
#endif

#ifndef MACRO_rs_color
#  define MACRO_rs_color
typedef struct {
    float r; //from 0~1
    float g; //from 0~1
    float b; //from 0~1
}rs_color;
#endif

#ifndef MACRO_rs_rect
#  define MACRO_rs_rect
typedef struct {
    float x1; //from 0~1, 0 means left or top, 1 means right or bottom
    float y1; //from 0~1, 0 means left or top, 1 means right or bottom
    float x2; //from 0~1, 0 means left or top, 1 means right or bottom
    float y2; //from 0~1, 0 means left or top, 1 means right or bottom
}rs_rect;
#endif

#define EXPORT_SDKWRAPPER_AS_DLL
#if defined(EXPORT_SDKWRAPPER_AS_DLL)
#  ifdef _MSC_VER
#    ifdef RSSDKWRAPPER_EXPORTS
#      define RSSDKWRAPPER_API extern "C" __declspec(dllexport)
#    else
#      define RSSDKWRAPPER_API extern "C" __declspec(dllimport)
#      ifdef _WIN64
#        pragma comment(lib, "../Bin64/RSSDKWrapper.lib")
#      else
#        pragma comment(lib, "../Bin/RSSDKWrapper.lib")
#      endif
#    endif
#  else
#    define RSSDKWRAPPER_API
#  endif
#else
#  define RSSDKWRAPPER_API
#endif

typedef void* device_id;
typedef void* session_id;

typedef enum {
    rs_not_support_aac = -20,
    rs_not_support = -19,
    rs_no_permission = -18,
    rs_not_defined = -17,
    rs_unknown_mp4_file = -16,
    rs_hk_mp4_file = -15,
    rs_param_error = -14,
    rs_need_login_first = -13,
    rs_parse_ptz_param_error = -12,
    rs_param_page_not_found = -11,
    rs_need_input_password = -10,
    rs_file_access_error = -9,
    rs_file_not_found = -8,
    rs_record_not_found = -7,
    rs_buffer_too_small = -6,
    rs_session_not_found = -5,
    rs_device_not_found = -4,
    rs_parse_json_error = -3,
    rs_unknown_error = -2,
    rs_fail = -1,
    rs_success = 0
}rs_error_code;

typedef enum {
    rs_channel_unknown = -1,
    rs_channel_offline = 0,
    rs_channel_online = 1,
    rs_channel_wireless_online = rs_channel_offline,
    rs_channel_wireless_sleeping = 3,
}rs_channel_status;

//for query param and set param
#define  QUERY_ALL                  1000
#define  QUERY_ALL2                 1100
#define  QUERY_ALL_DEFAULT          1200
#define  GET_ALL                    1300
#define  SAVE_ALL                   2000
#define  MODIFY_PSW                 800
#define  MODIFY_USER_AND_PSW        801
#define  QUERY_ALL_WITHDATA         900
#define  QUERY_PARAM_INDEX          950

#define  MAX_CHANNEL                255

/*
 * param      ---> "channel number"  : (int) 16,
 *            ---> "device name"     : "HRD-E1630L",
 *            ---> "device type"     : "HRD-E1630L",
 *            ---> "device type ull" : (uint64_t) 5932091752722990336,
 *            ---> "device version"  : "V7.1.0-20160917",
 *            ---> "dns1"            : "",
 *            ---> "dns2"            : "",
 *            ---> "gateway"         : "",
 *            ---> "ip"              : "",
 *            ---> "mac addr"        : "",
 *            ---> "media port"      : (int) 9000,
 *            ---> "netmask"         : "",
 *            ---> "network mode"    : "static",
 *            ---> "p2p id"          : "",
 *            ---> "web port"        : (int) 8000
 * user_param ---> value you pass to function <search_device>
 * attention  ---> if param == NULL, means search done
 */
typedef void (CALLBACK* search_device_callback)(const char* param, void* user_param);

/*
 * param      ---> "status" : "success"
 *                          : "connecting"
 *                          : "close"
 *                          : "unknown error"
 *                          : "user logined"
 *                          : "user or password error"
 *                          : "user no right"
 *                          : "ip filter"
 *                          : "max user"
 *                          : "user disabled"
 *                          : "force change password"
 *                          : "force close brower"
 *                          : "forbidden ip"
 *                          : "p2p mode"
 *                          : "relay mode"
 *                          : "lan mode"
 *            ---> "info"   : a json value, only used when "status" equals "success"
 * user_param ---> value you pass to function <login>
 */
typedef void (CALLBACK* connction_callback)(const char* param, void* user_param);

/*
 * alarm_type ---> "MsgDevPreviewChangeReport" and so on
 * param      ---> a json value to alarm
 * user_param ---> value you pass to function <login>
 * attention  ---> you need to care about these two message, one is "RSSDKChannelStatusEx", the ohter
 *                 is "RSSDKAlarmStatus". The first message tell app about the status of all channels
 *                 of this device. The second message tell app about the alarm of this device
 */
typedef void (CALLBACK* alarm_callback)(const char* alarm_type, const char* param, void* user_param);
typedef void (CALLBACK* alarm_callback_ex)(int msg, void* data, int size, void* user_param);

/*
 * param      ---> "status" : "unknown error"
 *                          : "wait login"
 *                          : "start open stream"
 *                          : "open stream success"
 *                          : "open stream failed"
 *                          : "network frame arrieved"
 *                          : "preivew closed"
 *                          : "max preivew number"
 *                          : "device playback"
 *                          : "not enough bandwidth"
 *                          : "no authority"
 *                          : "preview active failed"
 *                          : "create decoder failed"
 *                          : "fisheye frame"
 *                          : "normal frame"
 * user_param ---> value you pass to function <rs_start_preview>
 */
typedef void (CALLBACK* preivew_callback)(const char* param, void* user_param);

/*
 * param        ---> "month"  : (int) 30, start with 1
 *              ---> "status" : "no authority" or no value
 * user_param   ---> user param
 * attention    ---> if param == NULL, means search done
 */
typedef void (CALLBACK* search_record_month_callback)(const char* param, void* user_param);

/*
 * param      : ---> "index" : (uint32_t) 123
 *              ---> "time"  : "2018-2-7 15:42:58 - 2018-2-7 15:43:14"
 *              ---> "size"  : (int) 456
 *              ---> "type"  : (uint32_t) defined in RSNetProtocol.h line 1225
 *              ---> "status" : "no authority" or no value
 * user_param   ---> user param
 * attention    ---> if param == NULL, means search done
 */
typedef void (CALLBACK* search_record_day_callback)(const char* param, void* user_param);

/*
 * param      ---> "status"  : "hdd format"
 *                           : "device playback"
 *                           : "not enough bandwidth"
 *                           : "no authority"
 *                           : "modify hdd"
 *                           : "download close"
 *                           : "storage record file err"
 *                           : "no file"
 *                           : "download ok"
 *                           : "download percent"
 *                           : "unknown error"
 *            ---> "percent" : (int) from 0 to 100
 * user_param ---> value you pass to function <start_preview>
 */
typedef void (CALLBACK* download_callback)(const char* param, void* user_param);

/*
 * param      ---> "channel" : (uin32_t) 0 1 2 3 4 and so on
 *            ---> "status"  : "create decoder failed"
 *                           : "file play end"
 *                           : "file create failed"
 *                           : "file write failed"
 *                           : "unknown error"
 *                           : "start open stream"
 *                           : "open stream success"
 *                           : "open stream failed"
 *                           : "network frame arrieved"
 *                           : "preivew closed"
 *                           : "device playback"
 *                           : "hdd format"
 *                           : "not enough bandwidth"
 *                           : "no authority"
 *                           : "modify hdd"
 *                           : "preview active failed"
 *                           : "record no data"
 *                           : "record I frame end"
 *                           : "fisheye frame"
 *                           : "normal frame"
 * user_param ---> value you pass to function <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
 */
typedef void (CALLBACK* playback_callback)(const char* param, void* user_param);

/*
 * param      ---> "status" : "talk busy"
 *                          : "talk close"
 * user_param ---> value you pass to function <rs_start_talk>
 */
typedef void (CALLBACK* talk_callback)(const char* param, void* user_param);

/*
 * param      ---> "progress" : (int) from 0 to 100
 * user_param ---> value you pass to function <rs_start_convert_file>
 */
typedef void (CALLBACK* convert_callback)(const char* param, void* user_param);

/*
 * data      ---> picutre data
 * size      ---> picutre size
 * type      ---> picutre type 0:BMP file,1:png file,2:jpg file
 *                          
 * user_param ---> value you pass to function <rs_start_convert_file>
 */
typedef void (CALLBACK* capture_buf_callback)(unsigned char* data, unsigned int size, int type, void* pUuser);

/*
 * msg_type   ---> (unsigned int)
 * param      ---> a json value of remote test, if param == NULL, means fail
 * user_param ---> value you pass to function <rs_remote_test>
 */
typedef void (CALLBACK* remote_test_callback)(unsigned int msg_type, const char* param, void* user_param);

/*
 * param      ---> "callback type" : "day search" or "thumbnail search" or "thumbnail delete"
 *            ---> "file name"     : full name of picture, when "callback type" equals "thumbnail search"
 *            ---> "detail info"   : a json array of search record info
 *                                 ---> "index" : (uint32_t)
 *                                 ---> "time"  : "2018-2-7 15:42:58 - 2018-2-7 15:43:14"
 *                                 ---> "size"  : (int) 456
 *                                 ---> "type"  : (uint32_t) defined in RSNetProtocol.h line 1225
 *                                 ---> "status": "success" or "fail", only used when "callback type" equals "thumbnail delete"
 * user_param ---> value you pass to function <rs_start_playback_thumbnails>
 * attention  ---> if param == NULL, means search done
 */
typedef void (CALLBACK* playback_thumbnails_callback)(const char* param, void* user_param);

/*
 * data       ---> picutre data
 * size       ---> picutre size
 * param      ---> reserve
 * user_param ---> value you pass to function <rs_start_local_playback_thumbnails>
 */
typedef void (CALLBACK* local_playback_thumbnails_callback)(unsigned char* data, unsigned int size, const char* param, void* user_param);

/*
 * data       ---> report data
 * size       ---> length of report data
 * param      ---> "report type" : (int) defined in RSNetProtocol.h line 3028  StreamReportType_E
 *            ---> "version"     : (int)
 * user_param ---> value you pass to function <rs_start_human_face_alarm_report>
 * attention  ---> about how to parse json, see document <intelligent-json-format.txt>
 */
typedef void (CALLBACK* human_face_alarm_report_data_callback)(const char* data, int size, const char* param, void* user_param);

/*
 * param      ---> reserve
 * user_param ---> value you pass to function <rs_start_human_face_alarm_report>
 */
typedef void (CALLBACK* human_face_alarm_report_status_callback)(const char* param, void* user_param);

/*
 * param      ---> a json value
 * size       ---> length of json value
 * user_param ---> value you pass to function <rs_start_human_face_param>
 * attention  ---> about how to parse json, see document <intelligent-json-format.txt>
 */
typedef void (CALLBACK* human_face_param_data_callback)(const char* param, int size, void* user_param);

/*
 * param      ---> "status" : "success"
 *                          : "fail"
 * user_param ---> value you pass to function <rs_start_human_face_param>
 */
typedef void (CALLBACK* human_face_param_status_callback)(const char* param, void* user_param);

/*
* info       ---> not used right now
* user_param ---> user param
 */
typedef void (CALLBACK* draw_callback)(SDKWRAPPER_DRAW_INFO* info, void* user_param);

/*
* info       ---> see <PICTURE_RENDER_INFO>
* user_param ---> user param
 */
typedef void (CALLBACK* picture_callback)(PICTURE_RENDER_INFO* info, void* user_param);

/*
* info       ---> see <PICTURE_RENDER_INFO>
* user_param ---> user param
 */
typedef void (CALLBACK* log_sink_callback)(const char* message, void* reserve);

/*
 * param      ---> "status"  : "upgrade close"
 *                           : "upgrade ok"
 *                           : "read file error"
 *                           : "invalid file"
 *                           : "percent"
 *                           : "ipc upgrade error"
 *                           : "ipc upgrade fail"
 *                           : "ipc upgrade percent"
 *                           : "ipc upgrade success"
 *                           : "ipc upgrade unknown error"
 *                           : "version error"
 *                           : "upgrading"
 *                           : "version same"
 *                           : "language error"
 *                           : "user interface"
 *                           : "write flash progress"
 *                           : "unknown error"
 *            ---> "channel" : if you upgrade ipc through nvr, this value maybe used
 *            ---> "percent" : (int) from 0 to 100
 * reserve    ---> not used for now
 * user_param ---> value you pass to function <rs_start_upgrade>
 */
typedef void (CALLBACK* upgrade_callback)(const char* param, void* reserve, void* user_param);

typedef void (CALLBACK* query_json_callback)(const char* json_data, int json_size, void* user_param);
typedef void (CALLBACK* set_json_callback)(bool success, const char* json_data, int json_size, void* user_param);

/*
 * msg_type   ---> (unsigned int)
 * param      ---> a json value of remote test, if param == NULL, means fail
 * user_param ---> value you pass to function <rs_remote_test>
 */
typedef void (CALLBACK* cms_register_callback)(unsigned int msg_type, const char* param, void* user_param);

/*
 * param      ---> "picture width"  : (int)
 *            ---> "picture height" : (int)
 *            ---> "zoom left"      : (int)
 *            ---> "zoom top"       : (int)
 *            ---> "zoom width"     : (int)
 *            ---> "zoom height"    : (int)
 * user_param ---> user param
 */
typedef void (CALLBACK* zoom_callback)(const char* param, void* user_param);

/*
 * param      ---> "status"  : (int), see p2p_status_error_code in RSNet.h
 * user_param ---> user param
 */
typedef void (CALLBACK* check_p2p_status_callback)(const char* param, void* user_param);

/*
 * param      ---> "status" : "success"
 *                          : "fail"
 * user_param ---> value you pass to function <rs_register_p2p_process_callback>
 */
typedef void (CALLBACK* p2p_process_callback)(const char* param, void* user_param);

/*
 * The APP does the decoding work and passes the decoded data to the SDK
 * return  0: decode success and get one picture
 * return -1: decode failed
 * For details of the structure, please see RSMedia.h
 */
typedef int (CALLBACK* video_decode_callback)(void* /*RS_FRAME_DATA* */ frame, void* /*RS_VIDEO_DATA* */ decoded_frame, void* user_param);

/*
 * return 0: app do the render work themself
 * return 1: the SDK will continue and do the rest
 * For details of the structure, please see RSMedia.h
 */
typedef int (CALLBACK* video_render_callback)(void* /*RS_VIDEO_DATA* */ picture, void* user_param);

/*
 * The APP does the decoding work and passes the decoded data to the SDK
 * return  0: decode success and get one picture
 * return -1: decode failed
 * For details of the structure, please see RSMedia.h
 */
typedef int (CALLBACK* audio_decode_callback)(void* /*RS_FRAME_DATA* */ frame, void* /*RS_AUDIO_DATA* */ decoded_frame, void* user_param);

/*
 * return 0: app do the render work themself
 * return 1: the SDK will continue and do the rest
 * For details of the structure, please see RSMedia.h
 */
typedef int (CALLBACK* audio_render_callback)(void* /*RS_AUDIO_DATA* */ picture, void* user_param);

/*
 * return 0: app do the decode and render work themself
 * return 1: the SDK will continue and do the rest
 * return 2: app do the decode and render work themself. 
 *           for remote playback, 2 means app don't want data right now, call <rs_request_more_frame> for more data
 * For details of the structure, please see RSMedia.h
 */
typedef int (CALLBACK* frame_data_callback)(void* /*RS_FRAME_DATA* */ frame, unsigned int size, void* user_param);

/*
 * param      ---> "status" : "success"
 *                          : "connecting"
 *                          : "close"
 *                          : "unknown error"
 *            ---> "port"   : (int)
 * user_param ---> value you pass to function <rs_start_p2p_tunnel>
 */
typedef void (CALLBACK* p2p_tunnel_callback)(const char* param, void* user_param);

/*
 * param      ---> "status"      : "success" and so on
 *            ---> "http_code"   : (uint32_t), such as 200 or 404
 *            ---> "http_body"   : http body
 * user_param ---> value you pass to function <rs_start_async_http_client>
 */
typedef void (CALLBACK* http_client_callback)(const char* param, void* user_param);

typedef void (CALLBACK* export_callback)(void* param, unsigned int size, void* use_param);

typedef void (CALLBACK* rs_p2p_callback)(void* param, unsigned int size, void* use_param);



/*
* param                      ---> "max hardware decode num" : (int), if you don't know, just ignore this value or fill 0
*                            ---> "vv main server addr"     : the main vv p2p server address, if you don't know, just ignore this value or fill ""
*                            ---> "vv main server port"     : (int), the main vv p2p server port, if you don't know, just ignore this value or fill 0
*                            ---> "vv sub server addr"      : the sub vv p2p server address, if you don't know, just ignore this value or fill ""
*                            ---> "vv sub server port"      : (int), the sub vv p2p server port, if you don't know, just ignore this value or fill 0
*                            ---> "max tutk connection"     : (int), just ignore this value or fill 0
*                            ---> "oem type"                : "default" "B09" "B29" "B14" "B25" "B07" "B02" "B52"
*                            ---> "region"                  : "default" or "region_us", just ignore this value or fill "default"
*                            ---> "disable_tutk_p2p_mode"   : (bool), just ignore this value or fill false
*                            ---> "rs_p2p_callback_msg"     : just ignore this value or fill false
* rs_p2p_callback_fun        ---> see <rs_p2p_callback>, just fill NULL
* rs_p2p_callback_user_param ---> just fill NULL
*/
typedef struct _wrapper_init_param_ {
    const char*     param;
    rs_p2p_callback rs_p2p_callback_fun;
    void*           rs_p2p_callback_user_param;
    char            reserve[256];
}wrapper_init_param;

/*
* param          ---> "directory"       : the directory of log file, such as "D:/hello/world"
*                ---> "max size"        : (int)max size of log file, if the size of log file is bigger than this size,
*                                         sdk will clear the log file, 0 menas unlimited
*                ---> "enable p2p log"  : (bool)
* bugly_callback ---> see <log_sink_callback>
*/
typedef struct {
    const char*       param;
    log_sink_callback bugly_callback;
    char              reserve[256];
}init_log_ex_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "ip or id"              : ""
*              ---> "media port"            : (int) such as 9000, this option has been deprecated, please use "port"
*              ---> "port"                  : (int) such as 80
*              ---> "user"                  : "admin"
*              ---> "password"              : "admin"
*              ---> "ddns id server addr"   : "" or other
*              ---> "p2p type"              : "ip" "id" "tutk" "B02" "vv" "rsvv" "A02" "BO3" "ddns" "shangyun v2" "rs"
*              ---> "oem type"              : "default" "B09" "B29" "B14" "B25" "B07" "B02" "B52"
*              ---> "protocol"              : "auto" "http" "https" "media"
* conn_cb      ---> see <connction_callback>
* alarm_cb     ---> see <alarm_callback>
* user_param   ---> user param
* return value ---> see <rs_error_code>
*/
typedef struct {
    device_id          dev;
    const char*        param;
    connction_callback conn_cb;
    alarm_callback     alarm_cb;
    alarm_callback_ex  alarm_cb_ex;
    void*              user_param;
    char               reserve[256];
}device_login_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"     : (uin32_t) 0 1 2 3 4 and so on
*              ---> "stream type" : "main stream" "sub stream" "mobile stream"
*              ---> "auto connect" : (bool) automatic reconnect or not
*              ---> "cached decoded frame" : (int) for android, just fill 0
*              ---> "disable hardware decode" : (bool) just fill false
* window       ---> the windwow you want to show the video
* preview_cb   ---> see <preivew_callback>
* user_param   ---> user param
*/
typedef struct _preview_param_ {
    device_id             dev;
    const char*           param;
    HWND                  window;
    preivew_callback      preview_cb;
    void*                 preview_user_param;
    draw_callback         draw_cb;//draw something on the picture before render, such as line rect and picture
    picture_callback      picture_cb;//just fill NULL
    const char*           background_picture;//bmp picture, the bmp picture must be 24 bit without compression, just fill NULL
    int                   background_picture_size;//the length of background_picture, just fill 0
    zoom_callback         zoom_cb;//just fill NULL
    video_decode_callback video_decode_cb;//just fill NULL
    video_render_callback video_render_cb;//just fill NULL
    audio_decode_callback audio_decode_cb;//just fill NULL
    audio_render_callback audio_render_cb;//just fill NULL
    frame_data_callback   frame_data_cb;  //just fill NULL
    char                  reserve[180];
}preview_param;

/*
* param        ---> "file name"  : full path name of record file, such as "C:\record.rf"
*              ---> "file list"  : a json array for more than two files, sush as [{"path":"C:\record1.rf", "begin time":123456789, "end time":987654321}] 
*              ---> "sync play"  : (bool)whether add this session to sync playback, if you don't know, just fill (false) 
*              ---> "cached decoded frame" : (int) for android, just fill 0
*              ---> "disable hardware decode" : (bool) just fill false
* window       ---> the windwow you want to show the video
* playback_cb  ---> see <playback_callback>
* user_param   ---> user param
* attention    ---> whether fill "file name" or "file list", if you fill these two fields, sdk will just use "file name"
*                   the "begin time" and "end time" in "file list" is a uint64_t of microsecond
*/
typedef struct _local_playback_param_ {
    const char*           param;
    HWND                  window;
    playback_callback     playback_cb;
    void*                 playback_user_param;
    draw_callback         draw_cb;
    zoom_callback         zoom_cb;//just fill NULL
    video_decode_callback video_decode_cb;//just fill NULL
    video_render_callback video_render_cb;//just fill NULL
    audio_decode_callback audio_decode_cb;//just fill NULL
    audio_render_callback audio_render_cb;//just fill NULL
    frame_data_callback   frame_data_cb;  //just fill NULL
    char                  reserve[200];
}local_playback_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"     : (uin32_t) 0 1 2 3 4 and so on
*              ---> "stream type" : "main stream" "sub stream" "mobile stream"
*              ---> "record type" : (uint32_t)if it's ipc, defined in RSParameter.h line 38, 
*                                   else defined in RSParameter.h line 8
*              ---> "begin time"  : "2018-02-07 00:00:00"
*              ---> "end time"    : "2018-02-07 23:59:59"
*              ---> "sync play"   : (bool)whether add this session to sync playback, if you don't know, just fill (false) 
*              ---> "cached decoded frame" : (int) for android, just fill 0
*              ---> "disable hardware decode" : (bool) just fill false
* window       ---> the windwow you want to show the video
* playback_cb  ---> see <playback_callback>
* user_param   ---> user param
*/
typedef struct {
    device_id             dev;
    const char*           param;
    HWND                  window;
    playback_callback     playback_cb;
    void*                 playback_user_param;
    draw_callback         draw_cb;
    zoom_callback         zoom_cb;//just fill NULL
    video_decode_callback video_decode_cb;//just fill NULL
    video_render_callback video_render_cb;//just fill NULL
    audio_decode_callback audio_decode_cb;//just fill NULL
    audio_render_callback audio_render_cb;//just fill NULL
    frame_data_callback   frame_data_cb;  //just fill NULL
    char                  reserve[200];
}remote_playback_param;

/*
* sess          ---> an array of <rs_start_remote_playback> or <rs_start_local_playback>, 
* sess_count    ---> the count of sess
* playback_cb   ---> see <playback_callback>
* user_param    ---> user param
*/
typedef struct {
    session_id*           sess;
    int                   sess_count;
    playback_callback     playback_cb;
    void*                 playback_user_param;
    char                  reserve[240];
}sync_playback_param;

/*
* type           ---> 0:BMP file,1:png file,2:jpg file
* capture_buf_cb ---> see <capture_buf_callback>
* user_param     ---> user param
*/
typedef struct{
    int                   type;
	capture_buf_callback  capture_buf_cb;
	void*                 capture_buf_user_param;
    char                  reserve[256];
}capture_picture_buf_param;

/*
* dev             ---> (device_id) see return value of <rs_create_device>
* data_callback   ---> see <human_face_alarm_report_data_callback>
* status_callback ---> see <human_face_alarm_report_status_callback>
* user_param      ---> user param
*/
typedef struct {
    device_id                               dev;
    human_face_alarm_report_data_callback   data_callback;
    human_face_alarm_report_status_callback status_callback;
    void*                                   user_param;
    char                                    reserve[256];
}human_face_alarm_report_param;

typedef struct {
    unsigned int main_msg;
    unsigned int sub_msg;
    void*        param;
    int          param_size;
    char         reserve[256];
}simple_command_param;

/*
* dev             ---> (device_id) see return value of <rs_create_device>
* data_callback   ---> see <human_face_param_data_callback>
* status_callback ---> see <human_face_param_status_callback>
* user_param      ---> user param
*/
typedef struct {
    device_id                               dev;
    human_face_param_data_callback          data_callback;
    human_face_param_status_callback        status_callback;
    void*                                   user_param;
    char                                    reserve[256];
}human_face_param;

typedef struct {
    unsigned int                main_msg;
    const char*                 param;
    int							param_size;
    query_json_callback         callback;
    void*                       user_param;
    char                        erase_after_callback;
    char                        reserve[255];
}async_query_json_param;

typedef struct {
    unsigned int                main_msg;
    const char*                 param;
    int                         param_size;
    set_json_callback           callback;
    void*                       user_param;
    char                        erase_after_callback;
    char                        reserve[247];
}async_set_json_param;

typedef struct {
    ULONGLONG begin_time;
    ULONGLONG end_time;
    char      reserve[256];
}record_ex_param;

typedef struct {
    cms_register_callback register_callback;
    void*                 register_user_param;
    char                  reserve[256];
}cms_register_callback_param;

/*
* param        ---> "url"         : like "http://www.apple.com" or "https://www.apple.com", must be started with "http://" or "https://"
*              ---> "http_method" : "post" or "get"
*              ---> "post_data"   : the data you want to post
* client_cb    ---> see <http_client_callback>
* user_param   ---> user param
*/
typedef struct {
    const char*           param;
    http_client_callback  client_cb;
    void*                 user_param;
    char                  reserve[256];
}http_client_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* buffer       --->imformation of param config
* bufferlen    --->size of import file
*/
typedef struct {
	device_id             dev;
	const char*           buffer;
	int                   bufferlen;
	char                  reserve[256];
}remote_import_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* export_cb    --->see<export_callback>
* user_param   ---> user param
*/
typedef struct {
	device_id             dev;
	export_callback       export_cb;
	void*                 user_param;
	char                  reserve[256];
}remote_export_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "talk mode"      : "old mode" or "analogue audio", if you don't know, just fill "old mode" will be ok
*                   "channel"        : (uint32_t)0 1 2 3 4 and so on, need to fill only when "talk mode" equals "analogue audio"
*                   "sample rate"    : (int) just fill 8000
*                   "enable aec"     : (bool) just fill false, not support
*                   "disable record" : (bool) just fill false
*                   "enable db"      : (bool) just fill false
*                   "audio format"   : "g711a" or "aac lc", the default value is "g711a", just ignore this value or fill ""
* talk_cb      ---> see <talk_callback>
* user_param   ---> user param
* attention    ---> when "talk mode" is "analogue audio", device send audio to app through talk socket, not preview socket
*/
typedef struct {
    device_id             dev;
    const char*           param;
    talk_callback         talk_cb;
    frame_data_callback   frame_data_cb;  //just fill NULL
    void*                 user_param;
    char                  reserve[256];
}talk_to_device_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "talk mode"      : "half duplex" or "full duplex"
*                   "channel"        : (uint32_t)0 1 2 3 4 and so on
*                   "sample rate"    : (int) if it's wireless device, you must fill 16000, else fill 8000
*                   "enable aec"     : (bool) just fill false, not support 
*                   "disable record" : (bool) just fill false
*                   "audio format"   : "g711a" or "aac lc", the default value is "g711a", just ignore this value or fill ""
* talk_cb      ---> see <talk_callback>
* user_param   ---> user param
*/
typedef struct {
    device_id             dev;
    const char*           param;
    talk_callback         talk_cb;
    frame_data_callback   frame_data_cb;  //just fill NULL
    void*                 user_param;
    char                  reserve[256];
}talk_to_channel_param;

/*
* sess                ---> (session_id) see return value of <rs_start_talk_to_device> or <rs_start_talk_to_device_v1> or <rs_start_talk_to_channel> or <rs_start_talk_to_channel_v1>
* raw_pcm_data        ---> the raw pcm data pointer
* raw_pcm_data_length ---> the length of raw pcm data
*/
typedef struct {
    session_id            sess;
    const char*           raw_pcm_data;
    int                   raw_pcm_data_length;
    char                  reserve[256];
}talk_send_record_data_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"   : (uin32_t) 0 1 2 3 4 and so on, for sdk1.1.21 or above, you must input this value
*              ---> "index"     : (uint32_t) see <search_record_day_callback>, means which file you want to download
*              ---> "file name" : full path name of record file, such as "C:\record.rf", support ".rf" or ".mp4"
* download_cb  ---> see <download_callback>
* user_param   ---> user param
* attention    ---> you need to call <rs_search_record_by_day> first, in order to get "index"
*/
typedef struct {
    device_id             dev;
    const char*           param;
    download_callback     download_cb;
    frame_data_callback   frame_data_cb;  //just fill NULL
    void*                 user_param;
    char                  reserve[256];
}download_by_file_param;

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"              : (uin32_t) 0 1 2 3 4 and so on, for sdk1.1.21 or above, you must input this value
*              ---> "index"                : (uint32_t), see <search_record_day_callback>, means which file you want to download
*              ---> "file name"            : full path name of record file, such as "C:\record.rf"
*              ---> "begin time"           : "2018-02-07 04:05:05"
*              ---> "end time"             : "2018-02-07 16:15:16"
*              ---> "max single file size" : (int), the max file size of record file(MB), just ignore or fill 0
* download_cb  ---> see <download_callback>
* user_param   ---> user param
* attention    ---> you need to call <rs_search_record_by_day> first, in order to get "index"
*/
typedef struct {
    device_id             dev;
    const char*           param;
    download_callback     download_cb;
    frame_data_callback   frame_data_cb;  //just fill NULL
    void*                 user_param;
    char                  reserve[256];
}download_by_time_param;



/*
* param        ---> "max hardware decode num" : (int), if you don't know, just ignore this value or fill 0
*              ---> "vv main server addr"     : the main vv p2p server address, if you don't know, just ignore this value or fill ""
*              ---> "vv main server port"     : (int), the main vv p2p server port, if you don't know, just ignore this value or fill 0
*              ---> "vv sub server addr"      : the sub vv p2p server address, if you don't know, just ignore this value or fill ""
*              ---> "vv sub server port"      : (int), the sub vv p2p server port, if you don't know, just ignore this value or fill 0
*              ---> "max tutk connection"     : (int), just ignore this value or fill 0
*              ---> "oem type"                : "default" "B09" "B29" "B14" "B25" "B07" "B02" "B52"
*              ---> "region"                  : "default" or "region_us", just ignore this value or fill "default"
*              ---> "disable_tutk_p2p_mode"   : (bool), just ignore this value or fill false
* return value ---> see <rs_error_code>
* attention    ---> this function must be called before any other function
*/
RSSDKWRAPPER_API rs_error_code rs_sdk_wrapper_init(const char* param);

/*
* param        ---> see <wrapper_init_param>
* return value ---> see <rs_error_code>
* attention    ---> this function must be called before any other function
*/
RSSDKWRAPPER_API rs_error_code rs_sdk_wrapper_init_v1(const wrapper_init_param* param);

/*
* param        ---> a json value, not used for now
* return value ---> see <rs_error_code>
* attention    ---> this function must be called after any other function
*/
RSSDKWRAPPER_API rs_error_code rs_sdk_wrapper_uninit(const char* param);

/*
* param        ---> "directory"       : the directory of log file, such as "D:/hello/world"
*              ---> "max size"        : (int)max size of log file, if the size of log file is bigger than this size,
*                                       sdk will clear the log file, 0 menas unlimited
*              ---> "enable p2p log"        : (bool)
*              ---> "enable main loop log"  : (bool)
*              ---> "enable net log"        : (bool)
*              ---> "enable http log"       : (bool)
* return value ---> see <rs_error_code>
* attention    ---> this function must be called before any other function and after<rs_sdk_wrapper_init>, or never call this function
*/
RSSDKWRAPPER_API rs_error_code rs_init_log(const char* param);

/*
* param        ---> see <init_log_ex_param>
* return value ---> see <rs_error_code>
* attention    ---> this function must be called before any other function and after<rs_sdk_wrapper_init>, or never call this function
*/
RSSDKWRAPPER_API rs_error_code rs_init_log_ex(const init_log_ex_param* param);

/*
* param        ---> "oem type" : "default" "B09" "B29" "B14" "B25" "B07" "B02" "B52"
*              ---> "start ip" : if you use udp point to point search, fill this,
*                                otherwise if you use lan broadcast, just ignore this value or fill ""
*              ---> "stop ip"  : if you use udp point to point search, fill this,
*                                otherwise if you use lan broadcast, just ignore this value or fill ""
* callback     ---> see <search_device_callback>
* user_param   ---> user param
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_search_device(const char* param, search_device_callback callback, void* user_param);

/*
* param        ---> "user"            : "admin"
*              ---> "password"        : "admin"
*              ---> "original ip"     : ""
*              ---> "change ip"       : ""
*              ---> "netmask"         : ""
*              ---> "gateway"         : ""
*              ---> "dns1"            : ""
*              ---> "dns2"            : ""
*              ---> "mac addr"        : see <search_device_callback> -> "mac addr"
*              ---> "device type ull" : (uint64_t) see <search_device_callback> -> "device type ull"
*              ---> "media port"      : (int) 9000
*              ---> "web port"        : (int) 80
*              ---> "network mode"    : "dhcp" "pppoe" "static"
*              ---> "point to point"  : (bool) whether use broadcast(false) or udp point to point(true) to modify device infomation
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_modify_device(const char* param);

/*
* return value ---> ( == 0) means fail, ( > 0) means deivce id
*/
RSSDKWRAPPER_API device_id rs_create_device();

/*
* device_id    ---> (int) see return value of <rs_create_device>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_destroy_device(device_id dev);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "ip or id"            : ""
*              ---> "media port"          : (int) such as 9000, this option has been deprecated, please use "port"
*              ---> "port"                : (int) such as 80
*              ---> "user"                : "admin"
*              ---> "password"            : "admin"
*              ---> "ddns id server addr" : "" or other
*              ---> "p2p type"            : "ip" "id" "tutk" "B02" "vv" "rsvv" "A02" "BO3" "ddns" "shangyun v2" "rs"
*              ---> "oem type"            : "default" "B09" "B29" "B14" "B25" "B07" "B02" "B52"
*              ---> "protocol"            : "auto" "http" "https" "media"
* conn_cb      ---> see <connction_callback>
* alarm_cb     ---> see <alarm_callback>
* user_param   ---> user param
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_device_login(device_id dev, const char* param, connction_callback conn_cb, alarm_callback alarm_cb, void* user_param);

/*
* param        ---> see <rs_device_login_ex>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_device_login_ex(const device_login_param* param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_device_logout(device_id dev);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* buf          ---> buffer used to storage a json value to LoginRsp, defined in RSNetProtocol.h
* length       ---> length of buffer
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_get_login_rsp(device_id dev, char* buf, int length);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* return value ---> -1 : error
*                    0 : DEV_DVR
*                    1 : DEV_MVR
*                    2 : DEV_INTEL
*                    3 : DEV_NVR
*                    4 : DEV_IPC
*                    6 : DEV_HDVR
*/
RSSDKWRAPPER_API int rs_get_device_type(device_id dev);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* return value ---> the total channel number of device
*/
RSSDKWRAPPER_API int rs_get_channel_number(device_id dev);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* return value ---> the analogy channel number of device
* attention    ---> digital channel number = rs_get_channel_number() - rs_get_analogy_channel_number()
*/
RSSDKWRAPPER_API int rs_get_analogy_channel_number(device_id dev);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel" : (uin32_t) 0 1 2 3 4 and so on
*                   "term"    : "preview"
*                             : "remote playback"
*                             : "download"
*                             : "ptz"
*/
RSSDKWRAPPER_API bool rs_has_authority(device_id dev, const char* param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel" : (uin32_t) 0 1 2 3 4 and so on
*                   "term"    : "main stream"(need channel)
*                             : "sub stream"(need channel)
*                             : "mobile stream"(need channel)
*                             : "ptz"(need channel)
*                             : "talk to device"(no channel)
*                             : "talk to device analogue audio" (need channel)
*                             : "talk to channel half duplex"(need channel)
*                             : "talk to channel full duplex"(need channel)
*                             : "fisheye"(need channel)
*                             : "reverse playback"(no channel)
*                             : "human face alarm"(no channel)
*                             : "human face param"(no channel)
*                             : "new ptz"(need channel)
*                             : "device wireless"(no channel)
*                             : "channel wireless"(need channel)
*                             : "json hdd"(no channel)
*/
RSSDKWRAPPER_API bool rs_has_ability(device_id dev, const char* param);

/*
* param        ---> see <preview_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_preview(const preview_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_preview(session_id sess);

/*
* sess                 ---> (session_id) see return value of <rs_start_preview>
* find_preview_session ---> whether find sess or not
* return value         ---> a pointer to RS_PICTURE_S
* attention            ---> you shoud never call this function
*/
RSSDKWRAPPER_API void* rs_get_decoded_frame(session_id sess, bool* find_preview_session);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"     : a space-separated string, such as "0 3 6" means channnel (1, 4, 7), "8" means channel 9, "all" means all channels
*              ---> "stream type" : "main stream" "sub stream" "mobile stream"
*              ---> "record type" : (uint32_t)if it's ipc, defined in RSParameter.h line 38, 
*                                   else defined in RSNetProtocol.h line 8
*              ---> "time"        : "2018-02"
* search_cb    ---> see <search_record_month_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_search_record_by_month(device_id dev, const char* param, search_record_month_callback month_cb, void* user_param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"     : (uin32_t) 0 1 2 3 4 and so on
*              ---> "stream type" : "main stream" "sub stream" "mobile stream"
*              ---> "record type" : (uint32_t)if it's ipc, defined in RSParameter.h line 38, 
*                                   else defined in RSNetProtocol.h line 8
*              ---> "begin time"  : "2018-02-07 00:00:00"
*              ---> "end time"    : "2018-02-07 23:59:59"
*              ---> "detail info" : (bool)default value is (false), if you don't know, just fill (false)
*                                   if you want to get thumbnails of records on device, you need 
*                                   to fill (true)
*              ---> "enable_smart_search": (bool) support smart search or not, just just ignore this value or fill false
*              ---> "smart_region": (json array) the region of smart seach, just ignore this value
*              ---> "count"       : (uin32_t), just fill 0, if "count" is not equal to 0, then you don't need
*                                   to fill "begin time", acctually the device just use year month and day
* search_cb    ---> see <search_record_day_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_search_record_by_day(device_id dev, const char* param, search_record_day_callback day_cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_search_record_by_month> or <rs_search_record_by_day>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_search_record(session_id sess);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"   : (uin32_t) 0 1 2 3 4 and so on, for sdk1.1.21 or above, you must input this value
*              ---> "index"     : (uint32_t) see <search_record_day_callback>, means which file you want to download
*              ---> "file name" : full path name of record file, such as "C:\record.rf", support ".rf" or ".mp4"
* download_cb  ---> see <download_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> you need to call <rs_search_record_by_day> first, in order to get "index"
*/
RSSDKWRAPPER_API session_id rs_start_download_by_file(device_id dev, const char* param, download_callback download_cb, void* user_param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"              : (uin32_t) 0 1 2 3 4 and so on, for sdk1.1.21 or above, you must input this value
*              ---> "index"                : (uint32_t), see <search_record_day_callback>, means which file you want to download
*              ---> "file name"            : full path name of record file, such as "C:\record.rf"
*              ---> "begin time"           : "2018-02-07 04:05:05"
*              ---> "end time"             : "2018-02-07 16:15:16"
*              ---> "max single file size" : (int), the max file size of record file(MB), just ignore or fill 0
* download_cb  ---> see <download_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> you need to call <rs_search_record_by_day> first, in order to get "index"
*/
RSSDKWRAPPER_API session_id rs_start_download_by_time(device_id dev, const char* param, download_callback download_cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_download_by_file> or <rs_start_download_by_time>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_download(session_id sess);

/*
* param        ---> see <local_playback_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_local_playback(const local_playback_param* param);

/*
* param        ---> see <remote_playback_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_remote_playback(const remote_playback_param* param);

/*
* param        ---> see <sync_playback_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_sync_playback(const sync_playback_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_playback(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_open_sound(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_close_sound(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* volume       ---> (int) volume value, from 1 to 100
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_set_volume(session_id sess, int volume);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> (int) volume value, from 1 to 100
*/
RSSDKWRAPPER_API int rs_get_volume(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_set_mute_on(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_set_mute_off(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> "file name"            : full path name of record file, such as "C:\record.rf", support ".rf" or ".mp4"
*              ---> "picture name"         : generate a picture of record file, suport png and jpg(jpeg), it can be ""
*              ---> "max single file size" : (int), the max file size of record file(MB), just ignore or fill 0
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_start_record(session_id sess, const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_record(session_id sess);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"         : (uin32_t) 0 1 2 3 4 and so on
*              ---> "picture name"    : full path name of capture file, such as "C:\capture.jpeg", only suport jpg or jpeg
* return value ---> see <rs_error_code>
* attention    ---> this function is blocking
*/
RSSDKWRAPPER_API rs_error_code rs_capture_picture_from_device(device_id dev, const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> "picture name"    : full path name of capture file, such as "C:\capture.png", suport png and jpg(jpeg)
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_capture_picture(session_id sess, const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> see <capture_picture_buf_param>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_capture_picture_to_buf(session_id sess, capture_picture_buf_param* param);

/*
 * file_name   ---> file name, such as "D:\test.rf"
 * buf         ---> a buffer to storage begin time and end time of this file
 *             ---> "begin time"             : "2018-3-16 11:30:22"
 *             ---> "end time"               : "2018-3-16 11:31:22"
 *             ---> "begin time millisecond" : (int64_t)
 *             ---> "end time millisecond"   : (int64_t)
 * length      ---> the length of buf, you must pass this value correctly, because i will call memset to clear this buf
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_get_file_time(const char* file_name, char* buf, int length);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* buf          ---> a buffer to storage time, the current time will be format like this "2018-3-16 11:30:22", it's not a json value
* length       ---> the length of buf, you must pass this value correctly, because i will call memset to clear this buf
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_get_current_time(session_id sess, char* buf, int length);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> return 0 means fail, otherwhise millisecond of current file time
*/
RSSDKWRAPPER_API ULONGLONG rs_get_current_time_millisecond(session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* buf          ---> it's not a json value, a buffer to storage time, the seek time will be format like this "2018-3-16 11:30:22"
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_seek_by_time(session_id sess, const char* param);

/*
 * file_name   ---> file name, such as "D:\test.rf"
 * return value ---> return 0 means fail, otherwhise the key frame count of this file
 */
RSSDKWRAPPER_API int rs_get_file_key_frame_count(const char* file_name);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_seek_by_key_frame_index(session_id sess, int key_frame_index);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> "stream type" : "main stream" "sub stream" "mobile stream"
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_switch_stream_type(session_id sess, const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> "operation type" : "normal"
*                                      "pause"
*                                      "single frame"
*                                      "16 times slower"
*                                      "8 times slower"
*                                      "4 times slower"
*                                      "2 times slower"
*                                      "2 times faster"
*                                      "4 times faster"
*                                      "8 times faster"
*                                      "16 times faster"
*                                      "1 times reverse"
*                                      "2 times reverse"
*                                      "4 times reverse"
*                                      "8 times reverse"
*                                      "16 times reverse"
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_set_play_mode(session_id sess, const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> "proportion" : "full window" "picture proportion" "4:3 proportion" "16:9 proportion"
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_set_video_proportion(session_id sess, const char* param);

/*
 * sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
 * param        ---> defined in correction_type.h line 70
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_set_fishsye_mode(session_id sess, FISHEYE_COMB_TYPE_E type);

/*
 * sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
 * param        ---> "mouse flag"  : "mouse move"
  *                                : "mouse wheel"
 *                                 : "mouse lbutton down"
 *                                 : "mouse lbutton up"
 *                                 : "mouse lbutton dbclick"
 *                                 : "mouse rbutton dbclick"
 *              ---> "mouse x"     : (float) from 0 to 1
 *              ---> "mouse y"     : (float) from 0 to 1
 *              ---> "mouse delta" : (float) only when "mouse flag" equals "mouse wheel"
 * return value ---> see <rs_error_code>
 * attention    ---> for windows or mac system, just call this function when the window is in fisheye mode
 *                   for android, just call <rs_video_mouse_event>, no matter whether the window is in fisheye mode or not
 *                   for ios, sdk will handle the mouse event, you don't need to call this function
 */
RSSDKWRAPPER_API rs_error_code rs_fisheye_mouse_control(session_id sess, const char* param);

/*
 * sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
 * param        ---> "operation" : "left" or "up left" or "up"
 *                                 or "up right" or "right" or "down right"
 *                                 or "down" or "down left" or "zoom out"
 *                                 or "zoom in" or "auto scan"
 *                   "flag"      : "start" or "stop"
 *                   "speed"     : (int), form 0 to 100
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_fisheye_ptz_control(session_id sess, const char* param);

/*
 * sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
 * return value ---> true or false
 */
RSSDKWRAPPER_API bool rs_window_in_zoom_status(session_id sess);

/*
 * dev          ---> (device_id) see return value of <rs_create_device>
 * param        ---> "message" : (int) such as MsgParamPreviewCtrl
 *              ---> "type"    : (int) such as QUERY_ALL, see line 27, just fill QUERY_ALL
 *              ---> "data"    : used by app, just fill ""
 * buf          ---> buffer used to storage a json value of param
 * length       ---> length of buffer
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_query_param(device_id dev, const char* param, char* buf, int length);

/*
 * dev          ---> (device_id) see return value of <rs_create_device>
 * param        ---> "message" : (int) such as MsgParamPreviewCtrl
 *              ---> "type"    : (int) such as SAVE_ALL, see line 27, just fill SAVE_ALL
 * buf          ---> buffer used to storage a json value of param
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_set_param(device_id dev, const char* param, const char* buf);

/*
 * dev          ---> (device_id) see return value of <rs_create_device>
 * param        ---> "ptz type"  : "normal" or "preset" or "cruise" or "set cruise" or "call cruise"
 *                   "channel"   : (uint32_t)0 1 2 3 4 and so on
 *                   "operation" : if "ptz type" equals "normal", it can be one of
 *                                 these values "left" or "up left" or "up"
 *                                 or "up right" or "right" or "down right"
 *                                 or "down" or "down left" or "zoom out"
 *                                 or "zoom in" or "focus near" or "focus far"
 *                                 or "iris open" or "iris close" or "scan line",
 *
 *                                 if "ptz type" equals "preset", it can be one of
 *                                 these values "call" or "set" or "clear"
 *
 *                                 if "ptz type" equals "set_cruise" or "call cruise" should not give value
 *                   "flag"      : "start" or "stop"
 *                   "speed"     : (int), needed by "ptz type" equals "normal"  or "cruise"  or "set cruise", form 0 to 100
 *                   "index"     : (int), needed by "ptz type" equals "preset" only
 *                   "time"      : (int), needed by "ptz type" equals "cruise" only, preset cruise interval time, 0 means 5s, 1 means 10s, 2 means 15s
 *                   "pps"       : (int array), need by "ptz type" equals "set cruise"
 *                   "preset count": (int), need by "ptz type" equals "set cruise"
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_ptz_control(device_id dev, const char* param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "talk mode"   : "old mode" or "analogue audio", if you don't know, just fill "old mode" will be ok
*                   "channel"     : (uint32_t)0 1 2 3 4 and so on, need to fill only when "talk mode" equals "analogue audio"
*                   "sample rate" : (int) just fill 8000 
*                   "enable aec"  : (bool) just fill false, not support
*                   "enable db"   : (bool) just fill false
*                   "audio format" : "g711a" or "aac lc", the default value is "g711a", just ignore this value or fill ""
* talk_cb      ---> see <talk_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> when "talk mode" is "analogue audio", device send audio to app through talk socket, not preview socket 
*/
RSSDKWRAPPER_API session_id rs_start_talk_to_device(device_id dev, const char* param, talk_callback talk_cb, void* user_param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "talk mode"   : "half duplex" or "full duplex"
*                   "channel"     : (uint32_t)0 1 2 3 4 and so on
*                   "sample rate" : (int) if it's wireless device, you must fill 16000, else fill 8000
*                   "enable aec"  : (bool) just fill false, not support
*                   "audio format" : "g711a" or "aac lc", the default value is "g711a", just ignore this value or fill ""
* talk_cb      ---> see <talk_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_talk_to_channel(device_id dev, const char* param, talk_callback talk_cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_talk_to_device> or <rs_start_talk_to_channel>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_talk(session_id sess);

/*
* param        ---> "source file" : full path name of source file, such as "C:\record.rf", only support ".rf" or ".mp4"
*                   "target file" : full path name of target file, such as "C:\record.mp4", only support ".rf" or ".mp4"
* talk_cb      ---> see <convert_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_convert_file(const char* param, convert_callback convert_cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_convert_file>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_convert_file(session_id sess);

/*
* dev            ---> (device_id) see return value of <rs_create_device>
* msg_type       ---> (unsigned int)
* param          ---> a json value of remote test
* remote_test_cb ---> see <remote_test_callback>
* user_param     ---> user param
* return value   ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_remote_test(device_id dev, unsigned int msg_type, const char* param, remote_test_callback remote_test_cb, void* user_param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"          : (uin32_t) 0 1 2 3 4 and so on
*              ---> "stream type"      : "main stream" "sub stream" "mobile stream"
*              ---> "record type"      : (uint32_t)if it's ipc, defined in RSParameter.h line 38, 
*                                        else defined in RSParameter.h line 8
*              ---> "begin time"       : "2018-02-07 00:00:00"
*              ---> "end time"         : "2018-02-07 23:59:59"
*              ---> "file directory"   : the directory you want to save these thumbnails
*              ---> "picture type"     : "jpeg" or "png"
*              ---> "reverse callback" : (bool) true or false
*              ---> "count"            : (uin32_t), just fill 0
* cb           ---> see <playback_thumbnails_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_playback_thumbnails(device_id dev, const char* param, playback_thumbnails_callback cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_playback_thumbnails>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_playback_thumbnails(session_id sess);

/*
* param        ---> "file name"    : full path name of record file, such as "C:\record.rf"
*              ---> "picture type" : "jpeg" or "png"
*              ---> "width"        : (int) the width of thumbnails, 0 means the original width of picture
*              ---> "height"       : (int) the height of thumbnails, 0 means the original height of picture
* cb           ---> see <local_playback_thumbnails_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_local_playback_thumbnails(const char* param, local_playback_thumbnails_callback cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_local_playback_thumbnails>
* millisecond  ---> (uint64_t) millisecond of time
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_input_local_playback_time(session_id sess, ULONGLONG millisecond);

/*
* sess         ---> (session_id) see return value of <rs_start_local_playback_thumbnails>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_local_playback_thumbnails(session_id sess);

/*
* return value ---> see <rs_error_code>
* attention    ---> when ios and android before enter background, app must stop preview and logout device, 
*                   after a few seconds(this is very important), call this function
*/
RSSDKWRAPPER_API rs_error_code rs_destroy_p2p_resource_enter_background();

/*
* param        ---> see <remote_playback_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> if return value is equal to 0, maybe device not support this function or 
*                   you had call <rs_start_human_face_alarm_report> and didn't call 
*                   <rs_stop_human_face_alarm_report>, you must make sure that there is only one 
*                   "human face alarm report" in each device
*/
RSSDKWRAPPER_API session_id rs_start_human_face_alarm_report(const human_face_alarm_report_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_human_face_alarm_report>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_human_face_alarm_report(session_id sess);

/*
* param        ---> see <remote_playback_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> if return value is equal to 0, maybe device not support this function or
*                   you had call <rs_start_human_face_param> and didn't call
*                   <rs_send_human_face_param>, you must make sure that there is only one
*                   "human face param" in each device
*/
RSSDKWRAPPER_API session_id rs_start_human_face_param(const human_face_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_human_face_param>
* param        ---> json value
* param_size   ---> the length of json value
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_send_human_face_param(session_id sess, const char* param, int param_size);

/*
* sess         ---> (session_id) see return value of <rs_start_human_face_param>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_human_face_param(session_id sess);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* return value ---> see <rs_error_code>
* attention    ---> it's just call logout and then call login
*/
RSSDKWRAPPER_API rs_error_code rs_reset_connection(device_id dev);

/*
* dev                  ---> (device_id) see return value of <rs_create_device>
* simple_command_param ---> see <simple_command_param>
* return value         ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_send_simple_command(device_id dev, const simple_command_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* color_value  ---> see <rs_color>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_set_color(session_id sess, const rs_color* color_value);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* line_value   ---> see <rs_rect>
* line_count   ---> how many lines you want to draw
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_draw_line(session_id sess, const rs_rect* line_value, int line_count);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* line_value   ---> see <rs_rect>
* line_count   ---> how many rect you want to draw
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_draw_rect(session_id sess, const rs_rect* rect_value, int rect_count);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* rect_value   ---> see <rs_rect>
* line_count   ---> how many rect you want to draw
* transparency ---> from 0 to 1, 0 menas completely transparent, 1 means completely opaque
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_draw_solid_rect(session_id sess, const rs_rect* rect_value, int rect_count, float transparency);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* rect_value   ---> see <rs_rect>
* line_count   ---> how many circle you want to draw
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_draw_hollow_circle(session_id sess, const rs_rect* rect_value, int rect_count);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* text_value   ---> the text you want to draw
* rect_value   ---> see <rs_rect>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_draw_text(session_id sess, const char* text_value, const rs_rect* rect_value);

/*
* sess            ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* data            ---> the pictrure stored in memory
* size            ---> the size of picture data
* return value    ---> ( == 0) means fail, ( > 0) means session id
* attention       ---> only support png
*/
RSSDKWRAPPER_API session_id rs_upload_picture_from_memory(session_id sess, const char* data, int size);

/*
* sess            ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* picture_sess_id ---> (session_id) see return value of <rs_upload_picture_from_file>
* return value    ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_delete_picture(session_id sess, session_id picture_sess_id);

/*
* sess            ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* picture_sess_id ---> (session_id) see return value of <rs_upload_picture_from_file>
* rect_value      ---> see <rs_rect>
* transparency    ---> from 0 to 1, 0 menas completely transparent, 1 means completely opaque
* return value    ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_draw_picture(session_id sess, session_id picture_sess_id, const rs_rect* rect_value, float transparency);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* width        ---> (int*) used to storage width of frame, provided by user
* width        ---> (int*) used to storage height of frame, provided by user
* return value ---> see <rs_error_code>
* attention    ---> only support windows and mac
*/
RSSDKWRAPPER_API rs_error_code rs_get_frame_width_and_height(session_id sess, int* width, int* height);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* rect_value   ---> see <rs_rect>
* return value ---> see <rs_error_code>
* attention    ---> only support windows and mac and video proportion is "full window"
*/
RSSDKWRAPPER_API rs_error_code rs_adjust_render_frame_rect(session_id sess, const rs_rect* rect_value);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "file name"   : full path name of upgrade file, such as "C:\upgrade.sw"
*                   "file type"   : "normal" or "urmet ipc" or "rs ipc" or "98c" or "srp6", if you don't know, just fill "normal"
*                   "channel"     : a space-separated string, such as "0 3 6" means channnel (1, 4, 7), "8" means channel 9, 
*                                   only needed when "file tpye" is "urmet ipc" or "rs ipc"
*                   "sleep time"  : (int) sleep time for p2p, in millisecond, 0 for not sleep, if you don't know, just fill 0
* cb           ---> see <upgrade_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_upgrade(device_id dev, const char* param, upgrade_callback cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_upgrade>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_upgrade(session_id sess);

/*
* sync_sess    ---> (session_id) see return value of <rs_start_sync_playback>
* sess         ---> (session_id) see return value of <rs_start_local_playback> or <rs_start_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_sync_playback_add_session(session_id sync_sess, session_id sess);

/*
* sync_sess    ---> (session_id) see return value of <rs_start_sync_playback>
* sess         ---> (session_id) see return value of <rs_start_local_playback> or <rs_start_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_sync_playback_del_session(session_id sync_sess, session_id sess);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> see <async_query_json_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_async_query_json(device_id dev, const async_query_json_param* param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> see <async_set_json_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_async_set_json(device_id dev, const async_set_json_param* param);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* sess         ---> (session_id) see return value of <rs_start_async_query_json> or <rs_start_async_set_json>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_async_json(device_id dev,session_id sess);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> "file name"            : full path name of record file, such as "C:\record.rf"
*              ---> "picture name"         : generate a picture of record file, suport png and jpg(jpeg), it can be ""
*              ---> "max single file size" : (int), the max file size of record file(MB), just ignore or fill 0
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_manual_switch_record(session_id sess, const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback> or <rs_start_sync_remote_playback>
* param        ---> see <record_ex_param>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_record_ex(session_id sess, record_ex_param* param);

/*
* dev                         ---> (device_id) see return value of <rs_create_device>
* cms_register_callback_param ---> see <cms_register_callback_param>
* return value                ---> see <rs_error_code>
* attention                   ---> you shoud never call this function
*/
RSSDKWRAPPER_API rs_error_code rs_cms_register_callback(device_id dev, const cms_register_callback_param* param);

/*
 * dev          ---> (device_id) see return value of <rs_create_device>
 * param        ---> "ptz type"  : "normal"
 *                   "channel"   : (uint32_t)0 1 2 3 4 and so on
 *                   "operation" : if "ptz type" equals "normal", it can be one of
 *                                 these values "zoom out" or "zoom in" or 
 *                                 "focus near" or "focus far" or "zoom position"
 *                                 or "focus position" or "auto focus" or 
 *                                 "restore" or "refresh"
 *
 *                   "flag"      : "start" or "stop"
 *                   "speed"     : (int), needed by "ptz type" equals "normal"
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_new_ptz_control(device_id dev, const char* param);

/*
 * param                     ---> "p2p id"   : p2p id
 *                                "p2p type" : "ip" "id" "tutk" "B02" "vv" "rsvv" "A02" "BO3" "ddns" "shangyun v2" "rs"
 *                                "time out" : (uint32_t) in millisecond
 * check_p2p_status_callback ---> see <check_p2p_status_callback>
 * user_param                ---> user param
 * return value              ---> see <rs_error_code>, "rs_success" means p2p online
 * attention                 ---> support tutk and vv
 */
RSSDKWRAPPER_API rs_error_code rs_check_p2p_status(const char* param, check_p2p_status_callback cb, void* user_param);

/*
 * p2p_process_callback      ---> see <p2p_process_callback>
 * user_param                ---> user param
 * return value              ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_register_p2p_process_callback(p2p_process_callback cb, void* user_param);

/*
 * sess        ---> (session_id) see return value of <rs_start_preview> or <rs_start_local_playback> or <rs_start_remote_playback>
 * buf         ---> a buffer to storage frame rate and bir rate of this session
 *             ---> "frame rate"             : (int32_t)
 *             ---> "bit rate"               : (int32_t)
 * length      ---> the length of buf, you must pass this value correctly, because i will call memset to clear this buf
 * return value ---> see <rs_error_code>
 */
RSSDKWRAPPER_API rs_error_code rs_get_stream_info(session_id sess, char* buf, int length);

/*
 * param                     ---> "p2p type" : "ip" "id" "tutk" "B02" "vv" "rsvv" "A02" "BO3" "ddns" "shangyun v2" "rs"
 * return value              ---> see <rs_error_code>
 * attention                 ---> support tutk and vv
 */
RSSDKWRAPPER_API rs_error_code rs_init_p2p_resource_manual(const char* param);

/*
* sess         ---> (session_id) see return value of <rs_start_playback_thumbnails>
* param        ---> "index" : a json array, such as [{"index":[1, 2, 3, 4]}], 
                              see "index" in "detail info" of <playback_thumbnails_callback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_delete_playback_thumbnails(session_id sess, const char* param);

/*
 * sess        ---> (session_id) see return value of <rs_start_preview>
 * buf         ---> a buffer to storage frame rate and bir rate of this session
 *             ---> "frame rate"             : (int32_t)
 *             ---> "bit rate"               : (int32_t)
 * length      ---> the length of buf, you must pass this value correctly, because i will call memset to clear this buf
 * return value ---> see <rs_error_code>
 * attention    ---> only support live preview
 */
RSSDKWRAPPER_API rs_error_code rs_get_net_stream_info(session_id sess, char* buf, int length);

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel"          : (uin32_t) 0 1 2 3 4 and so on
*              ---> "index"            : a json array, such as [{"index":[1, 2, 3, 4]}], 
*                                        you can get these through <rs_search_record_by_day>
*              ---> "file directory"   : the directory you want to save these thumbnails
*              ---> "picture type"     : "jpeg" or "png"
*              ---> "reverse callback" : (bool) true or false
* cb           ---> see <playback_thumbnails_callback>
* user_param   ---> user param
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> you need to call <rs_stop_playback_thumbnails> when it's done
*/
RSSDKWRAPPER_API session_id rs_start_playback_thumbnails_index(device_id dev, const char* param, playback_thumbnails_callback cb, void* user_param);

/*
* param        ---> "ip or id"            : ""
*              ---> "media port"          : (int) 9000
*              ---> "ddns id server addr" : "" or other
*              ---> "p2p type"            : "ip" "id" "tutk" "B02" "vv" "rsvv" "A02" "BO3" "ddns" "shangyun v2" "rs"
* cb           ---> see <p2p_tunnel_callback>
* user_param   ---> user param
* return value ---> (== 0) means fail, (> 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_p2p_tunnel(const char* param, p2p_tunnel_callback cb, void* user_param);

/*
* sess         ---> (session_id) see return value of <rs_start_p2p_tunnel>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_p2p_tunnel(session_id sess);

/*
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_enable_tutk_many_connection(bool enable);

/*
* param        ---> see <async_http_client_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
* attention    ---> you would better never call this function, just implementat it by yourself
*/
RSSDKWRAPPER_API session_id rs_start_http_client(const http_client_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_async_http_client> 
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_stop_http_client(session_id sess);

/*
* buf          ---> a buffer to storage version
* length       ---> the length of buf, you must pass this value correctly, because i will call memset to clear this buf
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_get_sdk_version(char* buf, int length);

/*
* param        ---> see <remote_import_param>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_remote_import(const remote_import_param* param);

/*
* param        ---> see <remote_export_param>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_remote_export(const remote_export_param* param);

/*
* sess         ---> (session_id) see return value of <rs_start_remote_playback>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_request_more_frame(session_id sess);

/*
* param        ---> see <talk_device_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_talk_to_device_v1(const talk_to_device_param* param);

/*
* param        ---> see <talk_channel_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_talk_to_channel_v1(const talk_to_channel_param* param);

/*
* param        ---> see <talk_param>
* return value ---> see <rs_error_code>
*/
RSSDKWRAPPER_API rs_error_code rs_talk_send_record_data(const talk_send_record_data_param* param);

/*
* param        ---> see <download_by_file_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_download_by_file_v1(const download_by_file_param* param);

/*
* param        ---> see <download_by_time_param>
* return value ---> ( == 0) means fail, ( > 0) means session id
*/
RSSDKWRAPPER_API session_id rs_start_download_by_time_v1(const download_by_time_param* param);

#endif // end of __RSSDKWRAPPER_H__
