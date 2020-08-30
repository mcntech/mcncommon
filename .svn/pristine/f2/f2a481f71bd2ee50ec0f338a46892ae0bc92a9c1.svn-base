#ifndef __CLNT_COMMANDS_H
#define __CLNT_COMMANDS_H


#ifdef WIN32
#pragma pack(push)
#pragma pack(1)
#define ATTTRIB_PACK
#else // LINUX
#define ATTTRIB_PACK	__attribute__ ((packed))
#endif

#define CTRL_PORT		3456
#define CMD_SYNC			0xAABBCCDD
#define VC_HDR_SYNC		0xFFFFFFF0

#define VC_RTP			0x00
#define VC_CTRL			0x01

/**
 * Enumeration of sub-commands SE_CMD_PLAY i.e.CMD_PKT_T/(Type=SE_CMD_PLAY)
 */
typedef enum SE_PLAY_CMD_T
{
	PLAY_CTRL_NONE,
	PLAY_CTRL_START,
	PLAY_CTRL_PAUSE,
	PLAY_CTRL_STOP,
	PLAY_CTRL_EXIT,
	PLAY_CTRL_FLUSH,
	PLAY_CTRL_VID_EOS,
};

/**
 * Enumeration of sub-commands for SE_STREAM_CTRL i.e.CMD_PKT_T/(Type=SE_STREAM_CTRL)
 */
typedef enum SE_STREAM_CTRL_CMD_T
{
	STREAM_CTRL_NONE,
	STREAM_CTRL_OPEN,
	STREAM_CTRL_CLOSE
};

/**
 * Enumeration of sub-commands for SE_STREAM_CTRL i.e.SE_CMD_AUD_VOL/(Type=SE_CMD_AUD_VOL)
 */
typedef enum tagSE_AUD_CMD_T
{
	AUD_VOL_SET,
	AUD_VOL_GET,
	AUD_BAL_SET,
	AUD_BAL_GET,
} AUD_CMD_T;

/**
 * PLAYBACK_CTRL_T : Parameters for playback commands
 */

typedef struct tagPLAYBACK_CTRL
{
	long	Cmd;
	long	Param1;
	long	Param2;
	long	Reserved;
} ATTTRIB_PACK PLAYBACK_CTRL_T;

/**
 * IDs for specifying Audio/Video streams for the session
 * Used in STREAM_CTRL_T/Param2
 */

#define AUDIO_NONE		0
#define AUDIO_PCM		1
#define AUDIO_MPEG		2
#define AUDIO_AC3		3
#define AUDIO_MPEG_L2	4
#define AUDIO_WMA		5

#define VIDEO_NONE		0
#define VIDEO_MPEG2		1
#define VIDEO_WMV		2
#define MAX_SEQHDR_LEN		64

/**
 * STREAM_CTRL_T : Parameters for Stream config/control commands
 */

typedef struct tagSTREAM_CTRL_T
{
	long	Cmd;
	long	Param1;				// Used to specify transport TCP(0) or UDP(1)
	long	Param2;				// Specify stream options

	/* Sequence header length */
	long lAudSeqHdrLen;
	
	/* Sequence header */
	char AudSeqHdr[MAX_SEQHDR_LEN];

	/* Sequence header length */
	long lVidSeqHdrLen;
	
	/* Sequence header */
	char VidSeqHdr[MAX_SEQHDR_LEN];

} ATTTRIB_PACK STREAM_CTRL_T;

/**
 * VIDEO_RECT_T : Video window coordinate information
 */

typedef struct tagVIDEO_RECT
{
	long	Left;
	long	Top;
	long	Right;
	long	Bottom;

} ATTTRIB_PACK VIDEO_RECT_T;

/**
 * DEPTH_ORDER_T : Video Window Depth order
 */

typedef struct tagDEPTH_ORDER_T
{
	long	DepthOrder;				// Base 1. 1 is topmost
	long	Reserved1;
	long	Reserved2;
	long	Reserved3;

} ATTTRIB_PACK DEPTH_ORDER_T;

/**
 * COLOR_KEY_T : Color key information
 */
typedef struct tagCOLOR_KEY_T
{
	unsigned long	KeyType;
	unsigned long	PaletteIndex;
	unsigned long	HighColorValue;
	unsigned long	LowColorValue;

} ATTTRIB_PACK COLOR_KEY_T;

/**
 * AUD_VOL_T : Audio Voume information
 */
typedef struct tagAUD_VOL_T
{
	unsigned long	AudCmd;		// onr of SE_AUD_CMD_T
	unsigned long	Param1;		// Volume of Balance
	unsigned long	Reserved1;	
	unsigned long	Reserved2;
} ATTTRIB_PACK AUD_VOL_T;

/**
 * SE_CMD_T enumerates command types (tags) used with CMD_PKT_T/Type
 */

typedef enum SE_CMD_T
{
	STREAM_CTRL,
	CMD_PLAY,
	CMD_VID_RECT,
	CMD_COLOR_KEY,
	CMD_GET_BUFF_STAT,
	CMD_GET_AUD_CLK,
	CMD_AUD_VOL,
	CMD_OVL_DEPTH_ORDER
};


#define CMD_OPTION_REQ_RESPONSE		0x00000001

/**
 * CMD_PKT_T: Command Packet sent from RDP Redirection filter to playback daemon on session control
 * This is a generic structure used for all commands from server to client 
 */
typedef struct tagCMD_PKT
{
	unsigned long	Sync;
	long			Type;
	long			Len;

	union CmdTag
	{
		PLAYBACK_CTRL_T	PlaybackCtrl;
		STREAM_CTRL_T   StreamCtrl;
		VIDEO_RECT_T	VideoRectT;
		COLOR_KEY_T		ColorKeyT;
		AUD_VOL_T		AudVolCtrl;
		DEPTH_ORDER_T	DepthOrderT;
	} Cmd;
	long			Option;
} ATTTRIB_PACK CMD_PKT_T;

/**
 * STATUS_ID: Enumeration of Status IDs from client (RSP_PKT_T / Status)
 */

typedef enum tagSTATUS_ID {
	CMD_PROGRESS,
	CMD_SUCCESS,
	CMD_FAILED,
	CMD_NOT_VALID
}STATUS_ID;


/**
 * RSP_PKT_T: Response Packet from client to server
 * This is a generic structure used for responses to all commands from client to server
 */

typedef struct tagRSP_PKT_T {
	long CmdStatus;		// Status of Request
	long CmdId;			// Echo Command back
	long Param1;		// Additional Param1
	long Param2;		// Additional Param2
}ATTTRIB_PACK RSP_PKT_T;

/**
 * Channel IDs used in multiplexed stream from Server to Client
 */

#define BS_VID_DATA_CHAN	0
#define BS_VID_CMD_CHAN		1
#define BS_AUD_DATA_CHAN	2
#define BS_AUD_CMD_CHAN		3
#define BS_DEMUX_DATACHAN	4


#define RTP_MARK		0x80
#define PL_MASK			0x7F

/**
 * Payload types used in RTP Packet
 */

typedef enum PAYLOAD_T
{
	PL_AVTYPE_NONE = 0,
	PL_VIDEO_MPG2 = 32	,		// RFC 1890
	PL_AUDIO_MPG2  = 14,		// MPA
	PL_VIDEO_MP2T = 33	,		// MPEG2 Transport
	PL_AUDIO_AC3 = 100,			// Dynamic Pl
	PL_VIDEO_WMV = 101	,		// MPEG2 Transport
	PL_VIDEO_H264 = 102	,		// RFC 3640
	PL_AUDIO_AAC = 103	,		// RFC 33984
	PL_VIDEO_FLVH263 = 104		// RFC 2190
};

/**
 * Modes for data transfer to client
 */
#define TX_RTP_OVER_TCP		0
#define TX_RTP_OVER_UDP		1
#define TX_RTSP_OVER_UDP	2
#define TX_RTSP_OVER_VC		3


/**
 * Enumeration of commands sent on the stream port i.e. commands embedded in the stream
 */
typedef enum SE_STRM_CMD_T
{
	STRM_CMD_NONE,
	STRM_CMD_FLUSH_BEGIN,
	STRM_CMD_FLUSH_END,
	STRM_CMD_DISCONTINUITY,
	STRM_CMD_NEW_SEGMENT,
	STRM_CMD_PAUSE,
	STRM_CMD_RUN,
	STRM_CMD_STOP,
	STRM_CMD_EOS
};

/**
 * STREAM_CMD_T : Structure used for command streams multiplexed with AV Paylaod
 */

typedef struct tagSTREAM_CMD_T
{
	long	Cmd;
	long	Param1;
	long	Param2;
} ATTTRIB_PACK STREAM_CMD_T;

#ifdef WIN32
#pragma pack(pop)
#endif

#endif // __CLNT_COMMANDS_H
