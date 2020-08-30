#ifndef __CODEC_TYPES_H__
#define __CODEC_TYPES_H__
typedef enum tagMCN_STRM_TYPE
{
	STRM_TYPE_NONE		= 0x0000,
	STRM_TYPE_YUV_NV12	= 0x0101,				///< Not supported yet
	STRM_TYPE_YUV_420	= 0x0102,				///< Not supported yet
	STRM_TYPE_YUY2		= 0x0103,				///< Not supported yet

	STRM_TYPE_RGB_32	= 0x0110,
	STRM_TYPE_RGB_24	= 0x0111,
	STRM_TYPE_RGB_565	= 0x0112,
	STRM_TYPE_RGB_555	= 0x0113,

	/* Reserved for future use */
	STRM_TYPE_MPEG2  = 0x0201,
	STRM_TYPE_H264	= 0x0202,				///< Not supported yet
	STRM_TYPE_FLVH263= 0x0203,				///< Not supported yet
	STRM_TYPE_MP4	= 0x0204,				///< Not supported yet

	STRM_TYPE_PCM_16LE	= 0x0401

} MCN_STRM_TYPE;

#endif // __CODEC_TYPES_H__