#ifndef __RFC_3640_H__
#define __RFC_3640_H__
typedef enum tagH264NALU_TYPES
{
    H264_NAL_SLICE_NON_IDR = 1,
    H264_NAL_SLICE_A       = 2,
    H264_NAL_SLICE_B       = 3,
    H264_NAL_SLICE_C       = 4,
    H264_NAL_SLICE_IDR     = 5,
    H264_NAL_SLICE_SEI     = 6,
    H264_NAL_SET_SEQ       = 7,
    H264_NAL_SET_PIC       = 8,
    H264_NAL_AU_DEL        = 9,
    H264_NAL_END_SEQ       = 10,
    H264_NAL_END_STM       = 11,
    H264_NAL_FIL_DATA      = 12,
    H264_NAL_SET_SEQ_EXT   = 13,
    H264_NAL_SLICE_NI_05   = 19
} H264NALU_TYPES;

#endif //__RFC_3640_H__



