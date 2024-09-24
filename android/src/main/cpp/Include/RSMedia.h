#ifndef __RSMedia_h__
#define __RSMedia_h__

//////////////////////////////////////////////////////////////////////////
//RSFrame

//RSVFrameHead.System
#define RSSystemPAL		'P'
#define RSSystemNTSC	'N'

typedef struct
{
	WORD Width;
	WORD Height;
	BYTE FrameRate;
	BYTE System;
    WORD WaterMark : 1;//2013-03-04 10:37:18  
    WORD bRefFrame : 1;
    WORD IFrameNoOffset : 11;
    WORD bFishEye : 1;
    WORD Reserved : 2;
}RSVideoHead;

typedef struct
{
	UINT SampleRate;
	BYTE Channels;
	BYTE BitsPerSample;
	WORD PackLen;
}RSAudioHead;

typedef struct
{
    BYTE ReportType;
    BYTE Version;
    BYTE Reserved[2];
} RSReportHead;

//RSFrameHead.FrameTag
#define RSFrameTag	*(UINT*)"RSFm"

//RSFrameHead.FrameType
#define RSIFrame	'I'
#define RSPFrame	'P'
#define RSAFrame	'A'
#define RSVFrame    'V'

//RSFrameHead.EncodeType
/* Video */
#define RSVideoEncodeH264	             0x01
#define RSVideoH264FFMPEG	             0x02
#define RSVideoEncodeMPEG4	             0x03
#define RSVideoEncodeMJPEG	             0x04
#define RSVideoEncodeJPEG	             0x05
#define RSVideoEncodeMP4	             0x06
#define RSVideoEncodeH265	             0x07
#define RSVideoH265FFMPEG	             0x08
#define RSVideoCH256H264	             0x09
#define RSVideoCH256H265	             0x0a

/* Audio */
#define RSAudioEncodeG711A	             0x01
#define RSAudioEncodeG711U               0x02
#define RSAudioEncodeADPCM_DVI4			 0x03
#define RSAudioEncodeG726_16KBPS	     0x04
#define RSAudioEncodeG726_24KBPS		 0x05
#define RSAudioEncodeG726_32KBPS		 0x06
#define RSAudioEncodeG726_40KBPS		 0x07
#define RSAudioEncodeAMR                 0x08
#define RSAudioEncodeAMRDTX              0x09
#define RSAudioEncodeAAC                 0x0a
#define RSAudioEncodeAT_10116            0x19  /* 8kbps 10116 rfc1890*/
#define RSAudioEncodeAT_G721             0x1a  /* 8kbps G721  rfc1890 */
#define RSAudioEncodeAT_GSM              0x1b  /* 8kbps Gsm   rfc1890 */
#define RSAudioEncodeAT_LPC              0x1c  /* 8kbps lpc   rfc1890 */
#define RSAudioEncodeAT_G722             0x1e  /* 8kbps G722  rfc1890 */
#define RSAudioEncodeAT_G728             0x1f  /* 8kbps G728  rfc1890 */
#define RSAudioEncodeADPCM_IMA           0x23
#define RSAudioEncodeG726_16KBPS_ASF     0x24  /* G726 16kbps for ASF ... */
#define RSAudioEncodeG726_24KBPS_ASF     0x25  /* G726 24kbps for ASF ... */
#define RSAudioEncodeG726_32KBPS_ASF     0x26  /* G726 32kbps for ASF ... */
#define RSAudioEncodeG726_40KBPS_ASF     0x27  /* G726 40kbps for ASF ... */

typedef struct
{
	UINT FrameTag;

	BYTE FrameType;
	BYTE EncodeType;
	BYTE Channel;
    BYTE bHide : 1;
    BYTE Reserved : 7;

	UINT FrameNo;
	UINT FrameSize;
	ULONGLONG Time; //(microseconds) Time/1000,000 = the number of seconds after January 1, 1970 UTC
	ULONGLONG Pts;

	union
	{
		RSVideoHead VideoHead;
		RSAudioHead AudioHead;
        RSReportHead ReportHead;
	};
}RSFrameHead;

typedef struct __RS_DEC_FRAME_S__
{
    union {
        unsigned char*  pY;                   //Y plane base address of the picture
        char            reserve_y[8];
    };
    union {
        unsigned char*  pU;                   //U plane base address of the picture
        char            reserve_u[8];
    };
    union {
        unsigned char*  pV;                   //V plane base address of the picture
        char            reserve_v[8];
    };
    union {
        unsigned char*  ffmpeg_av_frame;      //Not used
        char            reserve_ffmpeg[8];
    };
    unsigned int        uWidth;               //The width of output picture in pixel
    unsigned int        uHeight;              //The height of output picture in pixel
    unsigned int        uYStride;             //Luma plane stride in pixel
    unsigned int        uUVStride;            //Chroma plane stride in pixel
    char                forbidden_move;
    char                is_rgba32;
    unsigned char       channel;
    char                reserve[5];
} RS_DEC_FRAME_S;

#define MAX_FRAME_SIZE 1024*1024*2
typedef struct __RS_FRAME_S__
{
    RSFrameHead    frame_head;
    unsigned char  frame_data[MAX_FRAME_SIZE];
}RS_FRAME_S;

typedef struct __RS_PICTURE_S__
{
    RSFrameHead    frame_head;
    RS_DEC_FRAME_S dec_frame_head;
    unsigned char  picture_data[8];
}RS_PICTURE_S;

typedef struct __RS_FRAME_DATA__
{
    RSFrameHead    frame_head;
    unsigned char  frame_data[8];
}RS_FRAME_DATA;

typedef struct __RS_VIDEO_DATA_S__
{
    RSFrameHead    frame_head;
    RS_DEC_FRAME_S dec_frame_head;
    unsigned char  picture_data[8];
}RS_VIDEO_DATA;

typedef struct __RS_AUDIO_DATA_S__
{
    RSFrameHead    frame_head;
    int            reserve;
    int            pcm_length;
    unsigned char  pcm_data[8];
}RS_AUDIO_DATA;

#endif
