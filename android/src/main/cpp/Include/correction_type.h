#ifndef _CORRECTION_TYPE_H_
#define _CORRECTION_TYPE_H_

#include "common_type.h"
#include <time.h>
#ifndef WINDOWS_PLATFORM
#include <sys/time.h>
//#define CV_PI 3.1415926f
#endif
#define CV_PI 3.1415926f
#ifdef ANDROID_PLATFORM
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#define MAX_FISHEYE_CHN 9	
#define MAX_FISHEYE_DEV 1	

#ifndef RS_HTTP_SDKWRAPPER
#ifndef MACRO_rsFISHEYE_COMB_TYPE_E
#  define MACRO_rsFISHEYE_COMB_TYPE_E
typedef enum rsFISHEYE_COMB_TYPE_E
{
	FISH_CEILING_EYE = 0,		//[FishEye]
	FISH_CEILING_VR,	        //[VR]
	FISH_CEILING_CYLIND3D,      //[Cylinder]
	FISH_CEILING_CYLIND360,		//[Panorama 360]
	FISH_CEILING_CYLIND180,		//[Panorama 180]
	FISH_CEILING_2PTZ,			//[2 PTZ]
	FISH_CEILING_4PTZ,			//[4 PTZ]
	FISH_CEILING_CYLIND360_1PTZ,//[Panorama 360 + 1 PTZ]
	FISH_CEILING_CYLIND360_3PTZ,//[Panorama 360 + 3 PTZ]
	FISH_CEILING_CYLIND360_6PTZ,//[Panorama 360 + 6 PTZ]
	FISH_CEILING_CYLIND360_8PTZ,//[Panorama 360 + 8 PTZ]
	FISH_CEILING_EYE_3PTZ,		//[FishEye + 3 PTZ]
	FISH_CEILING_EYE_8PTZ,		//[FishEye + 8 PTZ]

	FISH_DESKTOP_EYE,			//[FishEye]
	FISH_DESKTOP_VR,	        //[VR]
	FISH_DESKTOP_CYLIND3D,      //[Cylinder]
	FISH_DESKTOP_CYLIND360,		//[Panorama 360]
	FISH_DESKTOP_CYLIND180,		//[Panorama 180]
	FISH_DESKTOP_4PTZ,			//[4 PTZ]
	FISH_DESKTOP_CYLIND360_1PTZ,//[Panorama 360 + 1 PTZ]
	FISH_DESKTOP_CYLIND360_3PTZ,//[Panorama 360 + 3 PTZ]
	FISH_DESKTOP_CYLIND360_6PTZ,//[Panorama 360 + 6 PTZ]
	FISH_DESKTOP_CYLIND360_8PTZ,//[Panorama 360 + 8 PTZ]
	FISH_DESKTOP_EYE_3PTZ,		//[FishEye + 3 PTZ]
	FISH_DESKTOP_EYE_8PTZ,		//[FishEye + 8 PTZ]

	FISH_WALL_EYE,				//[FishEye]
	FISH_WALL_VR,               //[VR]
	FISH_WALL_NORMAL,			//[Panorama]
	FISH_WALL_4PTZ,				//[4 PTZ]
	FISH_WALL_NORMAL_3PTZ,		//[Panorama + 3 PTZ]
	FISH_WALL_NORMAL_8PTZ,		//[Panorama + 8 PTZ]
	FISH_WALL_EYE_3PTZ,			//[FishEye + 3 PTZ]
	FISH_WALL_EYE_8PTZ,			//[FishEye + 8 PTZ]

	FISH_TILT_EYE,				//[FishEye]
	FISH_TILT_VR,               //[VR]
	FISH_TILT_NORMAL,			//[Panorama]
	FISH_TILT_4PTZ,				//[4 PTZ]
	FISH_TILT_NORMAL_3PTZ,		//[Panorama + 3 PTZ]
	FISH_TILT_NORMAL_8PTZ,		//[Panorama + 8 PTZ]
	FISH_TILT_EYE_3PTZ,			//[FishEye + 3 PTZ]
	FISH_TILT_EYE_8PTZ,			//[FishEye + 8 PTZ]

	FISH_COMB_TYPE_BUTT
}FISHEYE_COMB_TYPE_E;
#endif
#endif

typedef enum rsFISHEYE_MOUNT_MODE_E					
{
	RSFISHEYE_CEILING_MOUNT = 0,		
	RSFISHEYE_DESKTOP_MOUNT = 1,		
	RSFISHEYE_WALL_MOUNT    = 2,		
	RSFISHEYE_TILT_MOUNT    = 3,		
	RSFISHEYE_MOUNT_MODE_BUTT
}RSFISHEYE_MOUNT_MODE_E;

typedef enum rsFISHEYE_MODEL_E						
{
	FISHEYE_SPHERE		= 0,		
	FISHEYE_LATITUDE	= 1,		
	FISHEYE_CYLINDER360 = 2,		
	FISHEYE_CYLIND3D    = 3,        
	FISHEYE_SPHERE_VR   = 4,		
	FISHEYE				= 5,        
	FISHEYE_SPHERE_RE   = 6,        
	FISHEYE_BOUNDARY    = 7,        
	FISHEYE_CYLINDER180 = 8,		
//#if !defined (WINDOWS_PLATFORM)
	FISHEYE_FLIP = 9,				
	FISHEYE_ORIGNAL = 10,			
//#endif
	FISHEYE_MODEL_BUTT
}FISHEYE_MODEL_E;

typedef enum rsFISHEYE_RANGE_TYPE_E
{
	FISHEYE_RANGE_CURVE,				
	FISHEYE_RANGE_RECT,					
	FISHEYE_RANGE_BUTT
}FISHEYE_RANGE_TYPE_E;

typedef enum rsFISH_PROGRAM_E
{
	FISH_PROGRAM_NORMAL,
//	FISH_PROGRAM_SPHEREVR,				
//	FISH_PROGRAM_CYLINDVR,				
	FISH_PROGRAM_SPHERERANGE,			
	FISH_PROGRAM_CYLINDRANGE,			
	FISH_PROGRAM_LATITUERANGE,			
	FISH_PROGRAM_BOUNDARY,				
//#if !defined (WINDOWS_PLATFORM)
	FISH_PROGRAM_FLIP,					
	FISH_PROGRAM_ORIGNAL,				
//#endif
	FISH_PROGRAM_BUTT
}FISH_PROGRAM_E;

typedef enum rsFISH_SNAPSHOT_E
{
	FISH_SNAPSHOT_BMP = 0, //D3DXIFF_BMP
	FISH_SNAPSHOT_JPG = 1, //D3DXIFF_JPG
	FISH_SNAPSHOT_TGA = 2, //D3DXIFF_TGA
	FISH_SNAPSHOT_PNG = 3, //D3DXIFF_PNG
	FISH_SNAPSHOT_DDS = 4, //D3DXIFF_DDS   
	FISH_SNAPSHOT_BUTT
}FISH_SNAPSHOT_E;

typedef enum rsFISH_PTZ_E
{
	FISH_PTZ_LEFT = 0,					
	FISH_PTZ_RIGHT,						
	FISH_PTZ_UP,						
	FISH_PTZ_DOWN,						
	FISH_PTZ_LEFTUP,					
	FISH_PTZ_RIGHTUP,					
	FISH_PTZ_LEFTDOWN,					
	FISH_PTZ_RIGHTDOWN,					
	FISH_PTZ_ZOOMINC,					
	FISH_PTZ_ZOOMDEC,					
	FISH_PTZ_CURISE,					
	FISH_PTZ_BUTT
}FISH_PTZ_E;

#ifdef WINDOWS_PLATFORM
typedef struct rsFISH_SHADER_PATH_S
{
	char* Path[100];
}FISH_SHADER_PATH_S;
typedef struct rsFISH_DEVICE_S
{
	FISH_SHADER_PATH_S* Path;
	HWND hWnd;    // window handle
}FISH_DEV_S;
#endif
typedef struct rsFISH_INTRIC_PARA_S
{
	float r;								
	float cx;								
	float cy;								
	float ang;								
#if defined (HI_PLATFORM) || defined (WINDOWS_PLATFORM)
	int width[3];
	int height[3];							
#endif
#if defined (WINDOWS_PLATFORM)
	HWND hWnd;
#endif
	char resvd[4];
}FISH_INTRIC_PARA_S;	

typedef struct rsFISH_MOVE_S
{
	FISH_PTZ_E ePtz;					
	float dx;							
	float dy;							
	float dk;							

	float v;							

	float x;							
	float y;							
	float k;							

	char CruiseNum;                     
	char EnableNum;                     
	bool bSlowDown;						
	char resvd[1];
}FISH_MOVE_S;

typedef struct rsFISH_ROAM_PARA_S
{
	float x;							
	float y;							
	float k;							
//#if !defined (WINDOWS_PLATFORM)
	bool bFullScreen;					
	bool bCruise;						
//#endif
	bool bDefault;                      
	char resvd[3];
}FISH_ROAM_PARA_S;

typedef struct rsFISH_RENDER_RANGE_S
{
	float x;						
	float y;						
	float w;						
	float h;						
#if defined (WINDOWS_PLATFORM)
	int screen_width;               
	int screen_height;				
#endif
	char resvd[4];
}FISH_RENDER_RANGE_S;

typedef struct rsROMA_ATTR_S
{
	FISHEYE_MODEL_E eModel;           
	FISH_ROAM_PARA_S astRoamPara;     
	FISH_RENDER_RANGE_S stRenderRange;
	OrthoProjInfo_S stOrthoProjInfo;  
	float fAngle;					  
	char resvd[4];
}ROMA_ATTR_S;

typedef struct rsFISHEYE_RANGE_MAP_S
{
	FISH_PROGRAM_E	eFishProgramRange;		
	bool bActivate;							

//#if 0
	//#ifdef WINDOWS_PLATFORM

	//FISHEYE_RANGE_TYPE_E enRangeType;       
	//time_t clickTimeVal;					
	//unsigned char u8DrawScreenNum;		
	//char resvd[2];

	//#else
//#endif

	FISHEYE_MODEL_E	eFishEyeModel;			
#ifdef WINDOWS_PLATFORM
	time_t clickTimeVal;
	//timeval clickTimeVal;
#else
	struct timeval clickTimeVal;			
#endif
	bool bDraw;								
	unsigned char u8SelectScreenNum;		
	unsigned char u8ScreenNum;				
	char resvd[1];

	//#endif

}FISHEYE_RANGE_MAP_S;

typedef struct rsFISHEYE_FUNC_S
{
	char String[256];				  
	FISH_SNAPSHOT_E enSnapShotType;   
	bool bIsSnapShot;                 
	bool bIsRender;                   

}FISHEYE_FUNC_S;

typedef struct rsFISHEYE_DYNAMIC_S
{
	ROMA_ATTR_S stRoma0;		
	ROMA_ATTR_S stRoma1;		
	float fCoef;				
	unsigned char u8DynamicType;
	bool bActivate;				
	char resvd[2];

}FISHEYE_DYNAMIC_S;

typedef struct rsFISHEYE_INITANGLE_S
{
	bool bActivate;					
	float x;						
	float y;						
	float w;						
	float h;						
	float fInitAngle;				
	RSFISHEYE_MOUNT_MODE_E enFishMountMode;
}FISHEYE_INITANGLE_S;

typedef struct rsFISHEYE_ATTR_S 
{
	RSFISHEYE_MOUNT_MODE_E enFishMountMode;			
	FISHEYE_COMB_TYPE_E  enFishCombType;		    
	
	unsigned char u8MultiScreen;				    
	unsigned char u8SelectScreenNum;		        
	unsigned char u8FullScreen;						
	char resvd[1];
	ROMA_ATTR_S astRegionAttr[MAX_FISHEYE_CHN];     
	FISH_MOVE_S stFishMove;                         
	FISHEYE_RANGE_MAP_S stFishRangeMap;			    
	FISHEYE_DYNAMIC_S   stFishDynamic;              
	FISHEYE_FUNC_S astFishFunc[MAX_FISHEYE_CHN];    
	FISHEYE_INITANGLE_S stFishInitAngle;			
}RSFISHEYE_ATTR_S; 

typedef struct rsIMAGE_S
{
	FISHEYE_PIXEL_FORMAT_E ePixFormat;					
#if !defined (WINDOWS_PLATFORM)
	FISHEYE_FRAME_FORMAT_E eFrameFormat;				
#endif
	unsigned char* pDataAddr[3];						
	unsigned int u32PhyAddr[3];							
	int width[3];										
	int height[3];										
	int stride[3];										
	int timeRef;										
	void* pPrivate;										
	char resvd[4];
}IMAGE_S;

typedef struct rsFISH_OUT_INFO_S
{
	int imgNum;									
	IMAGE_S stFishImgOut[MAX_FISHEYE_CHN];		
	bool  bSnap;
	char resvd[3];
}FISH_OUT_INFO_S;



	//HGLRC hglrc;  // rendering context
	//HDC   hdc;    // device context


typedef enum rsFISH_MOUSE_E
{
	FISH_MOUSE_MOVE = 0,               
	FISH_MOUSE_WHEEL,                  
	FISH_MOUSE_LBUTTONDOWN,            
	FISH_MOUSE_LBUTTONUP,              
	FISH_MOUSE_LBUTTONDBLCLK,          
	FISH_MOUSE_RBUTTONDBLCLK,          
	FISH_MOUSE_BUTT
}FISH_MOUSE_E;

typedef enum rsFISH_FUNC_E
{
	FISH_FUNC_SNAPSHOT = 0, 		  
	FISH_FUNC_PREVIEW,                
	FISH_FUNC_CHNSELECT,			  
	FISH_FUNC_BUTT
}FISH_FUNC_E;

typedef enum _FishControlFlag_E 
{
    FISH_EYE_PTZ_E   = 0,              
    FISH_EYE_MOUSE_E = 1,              
	FISH_EYE_FUNC_E  = 2,              
    FISH_EYE_BUTT
}FishControlFlag_E;

typedef struct 
{
    FISH_PTZ_E eFlag;                   
    float      speed;                   
	float      k;                       
	bool       bEnable;                 
}FISH_EYE_PTZ_S;

typedef struct 
{
	FISH_MOUSE_E eFlag;                 
    float        x;						
    float        y;						
	float        value;                 
}FISH_EYE_MOUSE_S;

typedef struct
{
	FISH_FUNC_E eFlag;                  
	bool bEnable;                       
	FISH_SNAPSHOT_E enSnapShotType;     
	char String[256];                   
	unsigned char ChnSelect;            
}FISH_EYE_FUNC_S;

typedef struct _FISH_CONTROL_REQ_S_ 
{
    int                 channel;
    FishControlFlag_E   eFlag;
    int                 width;         // UI width
    int                 height;        // UI height
    union 
	{
        FISH_EYE_PTZ_S   stPtz;
        FISH_EYE_MOUSE_S stMouse;
		FISH_EYE_FUNC_S  stFunc;
    };
}FISH_CONTROL_REQ_S;

#endif