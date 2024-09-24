#pragma once

#ifndef __RS_PARAMETER_H__
#define __RS_PARAMETER_H__



#define NoRecord            0x0
#define NormalRecord        0x1
#define AlarmRecord         0x2
#define MotionRecord        0x4
#define IORecord            0x8
#define PEARecord           0x10   // 
#define PEALineRecord       0x10   // 2015.11.30
#define AVDRecord           0x20
#define OSCRecord           0x40
#define AllIntelliRec       0x80
#define SensorRecord        0x100
#define PEAAreaRecord       0x200   // 2015.11.30/2016.03.09
#define OCCRecord           0x400   //private zone
#define NetbreakRecord      0x800   //netbreak
#define HDRecord            0x1000  // 2016.03.09
#define FDRecord            0x2000  // 2016.03.09
#define PCCRecord           0x4000  // 2016.03.09
#define MothionAndIo        0x8000  // 2017.02.09
#define PIRRecord           0x10000 //2017.05.09
#define SoundRecord         0x20000 //2018.05.03
#define ManualRecord        0x40000 //2018.05.09
#define SmartRecord         0x80000 //2018.05.30
#define PersonAlarmRecord   0x200000 // 2020.05.14
#define INE_ALL_RECORD      (PEARecord|PEALineRecord|AVDRecord|OSCRecord|PEAAreaRecord|HDRecord|FDRecord|PCCRecord|ManualRecord)
#define AlarmAssemble       0x7FFFFFFF//
#define AllRecord           0xFFFFFFFF



#define NormalRec           0x1
#define MotionRec           0x2
#define IORec               0x4
#define PEALineRec          0x8
#define AVDRec              0x10
#define OSCRec              0x20
#define PEAAreaRec          0x40
#define HDRec               0x80 
#define FDRec               0x100 
#define PCCRec              0x200 
#define MotionAndIORec      0x400
#define PIRRec              0x400
#define NetbreakRec         0x800      //2018.08.23
#define SoundRec            0x1000     //2018.08.23
#define ManualRec           0x2000     //capture 2019.06.26
                            
#define PIDRecord           0x200
#define LCDRecord           0x400
#define SODRecord           0x800



#define RS_Open 1
#define RS_Close 0

#define MsgParamIpc                     530
#define MsgParamUser 			        505
#define MsgParamHdd				        503
#define MsgParamSystemBase		        502
#define MsgParamModifyMainStream        570
#define MsgRemoteReboot                 303
#define MsgParamGeneral                 524
#define MsgParamMotion 			        516
#define MsgParamDefault 		        521
#define MsgParamNetworkBase 	        511
#define MsgParamSchedule 		        520
#define MsgParamRecord 			        519
#define MsgParamIPCImageSet             587 
#define MsgJsonTypeMsg                  429
#define MsgDeleteLogAndHdd              374
#define MsgSearchSmartCount             710 
#define MsgZeroChnStatus                336



typedef enum {
    SRT_AISnapPicture,
    SRT_AIFaceAlarm,
    SRT_AIObjectAlarm,
    SRT_Heart,
    SRT_HeatMap,
    SRT_CrossCount,
    SRT_AIScenario,
    SRT_Count
} StreamReportType_E;



/************************************************************************/
/*                                                                      */
typedef    char               S8;
typedef    unsigned char      U8;
typedef    short              S16;
typedef    unsigned short     U16;
typedef    int                S32;
typedef    unsigned int       U32;
typedef    unsigned long long U64;

#ifndef _MSC_VER
#    ifdef __linux__
#      define BOOL                   bool
#    else
#      include <objc/objc.h>           //for BOOL
#    endif

#    define  MAX_PATH                260
#    define  WINAPI
#    define  CALLBACK
#    define  FALSE                   0
#    define  TRUE                    1
#    define  S_OK                   (int)0
#    define  S_FALSE                (int)1
#    define  FILE_BEGIN              SEEK_SET
#    define  FILE_CURRENT            SEEK_CUR
#    define  FILE_END                SEEK_END
#    define  ATLTRACE                printf
#    define  E_OUTOFMEMORY           (int)(-1)

typedef char                    CHAR;
typedef unsigned char           UCHAR;
typedef unsigned char           BYTE;
typedef const char*             PCSTR;
typedef unsigned short          WORD;
typedef unsigned short          USHORT;
typedef unsigned int            DWORD;
typedef unsigned int            UINT;
typedef int                     HRESULT;
typedef long                    LONG;
typedef unsigned int            ULONG;
typedef unsigned long long      ULONGLONG;

typedef void*                   WPARAM;
typedef void*                   LPARAM;
typedef void*                   HDC;
typedef void*                   HWND;
typedef void*                   LPVOID;

typedef struct {
    int left;
    int top;
    int right;
    int bottom;
}RECT, *LPRECT;

static inline void SetRectEmpty(LPRECT rect) {
    rect->left = 0;
    rect->top = 0;
    rect->right = 0;
    rect->bottom = 0;
}

static inline bool IsRectEmpty(LPRECT rect) {
    return ((rect->right - rect->left) == 0) || ((rect->bottom - rect->top) == 0);
}

static inline void SetRect(LPRECT rect, int left, int top, int right, int bottom) {
    rect->left = left;
    rect->top = top;
    rect->right = right;
    rect->bottom = bottom;
}

static inline void CopyRect(LPRECT dst, LPRECT src) {
    dst->left = src->left;
    dst->top = src->top;
    dst->right = src->right;
    dst->bottom = src->bottom;
}

static inline bool EqualRect(LPRECT lprc1, LPRECT lprc2) {
    if (lprc1->left == lprc2->left && \
        lprc1->top == lprc2->top  && \
        lprc1->right == lprc2->right && \
        lprc1->bottom == lprc2->bottom)
        return true;
    return false;
}
#endif // end of _MSC_VER
/************************************************************************/

typedef struct {
    BYTE Hour;
    BYTE Minute;
    BYTE Second;
    BYTE rev;
}RSNetTimeSet_t;

typedef struct
{
    UINT StructSize;
    UINT ChannelMask;

    BYTE IRCutMode;			
    BYTE IRCutDelay;		
    BYTE IRCutSensitive;	
    BYTE Mirror;        	

    BYTE Flip;           	
    BYTE Rotate;			

    BYTE BackLightMode;
    BYTE BackLightLevel;

    BYTE R3dnrMode;
    BYTE R3dnrThreshTarget;

    BYTE DwdrMode;
    BYTE DwdrStrength;

    BYTE GainControlMode;

    BYTE WBMode;
    BYTE Rgain;
    BYTE Ggain;

    BYTE Bgain;

    BYTE ShutterMode;
    BYTE IRFuncType;       
    BYTE AgcMode;
    S32  eShutterSpeed;
    BYTE FlickerCtrl;
    BYTE DefogMode;
    BYTE DefogStrength;
    BYTE IRISMode;
    BYTE autoFocus;
    BYTE LEDEnable;
    RSNetTimeSet_t StartTime;
    RSNetTimeSet_t EndTime;
    BYTE HideRotate;
    BYTE GainSwitch;
    BYTE ColorGain;
    BYTE BrightGain;
    BYTE R2dnrMode;
    BYTE DefogFakeLottery;
    BYTE FloodLightMode;
    BYTE FloodLightValue;
    BYTE BackLightZone;
    BYTE AntiShakeEnable;
    BYTE AntiShakeLevel;
    BYTE AntiShakeLevelFlag;
    BYTE BackLightLevelCheck;
    BYTE WDRFlag;
    BYTE HLCSwitch;
    BYTE HLCStrength;
    BYTE IRLEDBrightness;
    BYTE IRLEDStrength;
    BYTE IRLEDStrengthEx;
    BYTE IRLEDNum;
    BYTE reverser2[38];
}RSNetNew_CameraSet_t;

typedef struct {
    UINT StructSize;
    UINT ChannelMask;
    BYTE mode;
    BYTE reverser[15];
    RSNetNew_CameraSet_t cameraSet[3];
}RSNetNew_CameraModeSet_t;

typedef struct
{
    UINT mixZoomPosition;
    UINT maxZoomPosition;
    UINT mixFocusPosition;
    UINT maxFocusPosition;
    BYTE PTZVersion;
    BYTE unused[7];
} AutoFocus_Default_t;
typedef struct
{
    UINT StructSize;
    UINT ChannelMask;
    UINT curZoomValue;
    UINT zoomStep;
    UINT curFocusValue;
    UINT focusStep;
    BYTE autoFocusState;
    char ShiftRange;
    BYTE unused[30];
}AUTOFOCUS_CONTROL_S;

typedef struct
{
    UINT StructSize;
    BYTE ReqType;
    BYTE PreviewMode;
    BYTE EncodeCh;
    BYTE reserved[25];
}ZeroChnStatReq;

#endif
