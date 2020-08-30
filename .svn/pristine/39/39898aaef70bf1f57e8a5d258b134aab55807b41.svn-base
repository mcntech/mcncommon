#include "inttypes.h"
#include "common.h"
#include "bitstream.h"
#include "golomb.h"

/**
 * Sequence parameter set
 */
typedef struct tagSPS{
    
    int profile_idc;
    int level_idc;
    int transform_bypass;              ///< qpprime_y_zero_transform_bypass_flag
    int log2_max_frame_num;            ///< log2_max_frame_num_minus4 + 4
    int poc_type;                      ///< pic_order_cnt_type
    int log2_max_poc_lsb;              ///< log2_max_pic_order_cnt_lsb_minus4
    int delta_pic_order_always_zero_flag;
    int offset_for_non_ref_pic;
    int offset_for_top_to_bottom_field;
    int poc_cycle_length;              ///< num_ref_frames_in_pic_order_cnt_cycle
    int ref_frame_count;               ///< num_ref_frames
    int gaps_in_frame_num_allowed_flag;
    int mb_width;                      ///< frame_width_in_mbs_minus1 + 1
    int mb_height;                     ///< frame_height_in_mbs_minus1 + 1
    int frame_mbs_only_flag;
    int mb_aff;                        ///<mb_adaptive_frame_field_flag
    int direct_8x8_inference_flag;
    int crop;                   ///< frame_cropping_flag
    int crop_left;              ///< frame_cropping_rect_left_offset
    int crop_right;             ///< frame_cropping_rect_right_offset
    int crop_top;               ///< frame_cropping_rect_top_offset
    int crop_bottom;            ///< frame_cropping_rect_bottom_offset
    int vui_parameters_present_flag;
    //AVRational sar;
    int timing_info_present_flag;
    uint32_t num_units_in_tick;
    uint32_t time_scale;
    int fixed_frame_rate_flag;
    short offset_for_ref_frame[256]; //FIXME dyn aloc?
    int bitstream_restriction_flag;
    int num_reorder_frames;
    int scaling_matrix_present;
    uint8_t scaling_matrix4[6][16];
    uint8_t scaling_matrix8[2][64];
}SPS;

#define EXTENDED_SAR          255

static __inline void decode_hrd_parameters(GetBitContext *gb, SPS *sps){
    int cpb_count, i;
    cpb_count = get_ue_golomb(gb) + 1;
    get_bits(gb, 4); /* bit_rate_scale */
    get_bits(gb, 4); /* cpb_size_scale */
    for(i=0; i<cpb_count; i++){
        get_ue_golomb(gb); /* bit_rate_value_minus1 */
        get_ue_golomb(gb); /* cpb_size_value_minus1 */
        get_bits1(gb);     /* cbr_flag */
    }
    get_bits(gb, 5); /* initial_cpb_removal_delay_length_minus1 */
    get_bits(gb, 5); /* cpb_removal_delay_length_minus1 */
    get_bits(gb, 5); /* dpb_output_delay_length_minus1 */
    get_bits(gb, 5); /* time_offset_length */
}

static __inline int decode_vui_parameters(GetBitContext *gb, SPS *sps){
    int aspect_ratio_info_present_flag, aspect_ratio_idc;
    int nal_hrd_parameters_present_flag, vcl_hrd_parameters_present_flag;

    aspect_ratio_info_present_flag= get_bits1(gb);
    
    if( aspect_ratio_info_present_flag ) {
        aspect_ratio_idc= get_bits(gb, 8);
        if( aspect_ratio_idc == EXTENDED_SAR ) {
            /*sps->sar.num= */get_bits(gb, 16);
            /*sps->sar.den=*/ get_bits(gb, 16);
        }else if(aspect_ratio_idc < 14){
            /*sps->sar=  pixel_aspect[aspect_ratio_idc];*/
        }else{
            return -1;
        }
    }else{
        /*sps->sar.num= 
        sps->sar.den= 0;*/
    }
//            s->avctx->aspect_ratio= sar_width*s->width / (float)(s->height*sar_height);

    if(get_bits1(gb)){      /* overscan_info_present_flag */
        get_bits1(gb);      /* overscan_appropriate_flag */
    }

    if(get_bits1(gb)){      /* video_signal_type_present_flag */
        get_bits(gb, 3);    /* video_format */
        get_bits1(gb);      /* video_full_range_flag */
        if(get_bits1(gb)){  /* colour_description_present_flag */
            get_bits(gb, 8); /* colour_primaries */
            get_bits(gb, 8); /* transfer_characteristics */
            get_bits(gb, 8); /* matrix_coefficients */
        }
    }

    if(get_bits1(gb)){      /* chroma_location_info_present_flag */
        get_ue_golomb(gb);  /* chroma_sample_location_type_top_field */
        get_ue_golomb(gb);  /* chroma_sample_location_type_bottom_field */
    }

    sps->timing_info_present_flag = get_bits1(gb);
    if(sps->timing_info_present_flag){
        sps->num_units_in_tick = get_bits_long(gb, 32);
        sps->time_scale = get_bits_long(gb, 32);
        sps->fixed_frame_rate_flag = get_bits1(gb);
    }

    nal_hrd_parameters_present_flag = get_bits1(gb);
    if(nal_hrd_parameters_present_flag)
        decode_hrd_parameters(gb, sps);
    vcl_hrd_parameters_present_flag = get_bits1(gb);
    if(vcl_hrd_parameters_present_flag)
        decode_hrd_parameters(gb, sps);
    if(nal_hrd_parameters_present_flag || vcl_hrd_parameters_present_flag)
        get_bits1(gb);     /* low_delay_hrd_flag */
    get_bits1(gb);         /* pic_struct_present_flag */

    sps->bitstream_restriction_flag = get_bits1(gb);
    if(sps->bitstream_restriction_flag){
        get_bits1(gb);     /* motion_vectors_over_pic_boundaries_flag */
        get_ue_golomb(gb); /* max_bytes_per_pic_denom */
        get_ue_golomb(gb); /* max_bits_per_mb_denom */
        get_ue_golomb(gb); /* log2_max_mv_length_horizontal */
        get_ue_golomb(gb); /* log2_max_mv_length_vertical */
        sps->num_reorder_frames = get_ue_golomb(gb);
        get_ue_golomb(gb); /* max_dec_frame_buffering */
    }

    return 0;
}

static const uint8_t default_scaling4[2][16]={
{   6,13,20,28,
   13,20,28,32,
   20,28,32,37,
   28,32,37,42
},{
   10,14,20,24,
   14,20,24,27,
   20,24,27,30,
   24,27,30,34
}};

static const uint8_t default_scaling8[2][64]={
{   6,10,13,16,18,23,25,27,
   10,11,16,18,23,25,27,29,
   13,16,18,23,25,27,29,31,
   16,18,23,25,27,29,31,33,
   18,23,25,27,29,31,33,36,
   23,25,27,29,31,33,36,38,
   25,27,29,31,33,36,38,40,
   27,29,31,33,36,38,40,42
},{
    9,13,15,17,19,21,22,24,
   13,13,17,19,21,22,24,25,
   15,17,19,21,22,24,25,27,
   17,19,21,22,24,25,27,28,
   19,21,22,24,25,27,28,30,
   21,22,24,25,27,28,30,32,
   22,24,25,27,28,30,32,33,
   24,25,27,28,30,32,33,35
}};

static const uint8_t zigzag_scan[16]={
 0+0*4, 1+0*4, 0+1*4, 0+2*4, 
 1+1*4, 2+0*4, 3+0*4, 2+1*4, 
 1+2*4, 0+3*4, 1+3*4, 2+2*4, 
 3+1*4, 3+2*4, 2+3*4, 3+3*4, 
};

static const uint8_t zigzag_scan8x8[64]={
 0+0*8, 1+0*8, 0+1*8, 0+2*8,
 1+1*8, 2+0*8, 3+0*8, 2+1*8,
 1+2*8, 0+3*8, 0+4*8, 1+3*8,
 2+2*8, 3+1*8, 4+0*8, 5+0*8,
 4+1*8, 3+2*8, 2+3*8, 1+4*8,
 0+5*8, 0+6*8, 1+5*8, 2+4*8,
 3+3*8, 4+2*8, 5+1*8, 6+0*8,
 7+0*8, 6+1*8, 5+2*8, 4+3*8,
 3+4*8, 2+5*8, 1+6*8, 0+7*8,
 1+7*8, 2+6*8, 3+5*8, 4+4*8,
 5+3*8, 6+2*8, 7+1*8, 7+2*8,
 6+3*8, 5+4*8, 4+5*8, 3+6*8,
 2+7*8, 3+7*8, 4+6*8, 5+5*8,
 6+4*8, 7+3*8, 7+4*8, 6+5*8,
 5+6*8, 4+7*8, 5+7*8, 6+6*8,
 7+5*8, 7+6*8, 6+7*8, 7+7*8,
};

static void decode_scaling_list(GetBitContext *gb, uint8_t *factors, int size,
                                const uint8_t *jvt_list, const uint8_t *fallback_list){
    int i, last = 8, next = 8;
    const uint8_t *scan = size == 16 ? zigzag_scan : zigzag_scan8x8;
    if(!get_bits1(gb)) /* matrix not written, we use the predicted one */
        memcpy(factors, fallback_list, size*sizeof(uint8_t));
    else
    for(i=0;i<size;i++){
        if(next)
            next = (last + get_se_golomb(gb)) & 0xff;
        if(!i && !next){ /* matrix not written, we use the preset one */
            memcpy(factors, jvt_list, size*sizeof(uint8_t));
            break;
        }
        last = factors[scan[i]] = next ? next : last;
    }
}

static void decode_scaling_matrices(GetBitContext *gb, SPS *sps, int is_sps,
                                   uint8_t (*scaling_matrix4)[16], uint8_t (*scaling_matrix8)[64]){
    int fallback_sps = !is_sps && sps->scaling_matrix_present,i;
    const uint8_t *fallback[4] = {
        fallback_sps ? sps->scaling_matrix4[0] : default_scaling4[0],
        fallback_sps ? sps->scaling_matrix4[3] : default_scaling4[1],
        fallback_sps ? sps->scaling_matrix8[0] : default_scaling8[0],
        fallback_sps ? sps->scaling_matrix8[1] : default_scaling8[1]
    };
    if(get_bits1(gb)){
        sps->scaling_matrix_present |= is_sps;
        decode_scaling_list(gb,scaling_matrix4[0],16,default_scaling4[0],fallback[0]); // Intra, Y
        decode_scaling_list(gb,scaling_matrix4[1],16,default_scaling4[0],scaling_matrix4[0]); // Intra, Cr
        decode_scaling_list(gb,scaling_matrix4[2],16,default_scaling4[0],scaling_matrix4[1]); // Intra, Cb
        decode_scaling_list(gb,scaling_matrix4[3],16,default_scaling4[1],fallback[1]); // Inter, Y
        decode_scaling_list(gb,scaling_matrix4[4],16,default_scaling4[1],scaling_matrix4[3]); // Inter, Cr
        decode_scaling_list(gb,scaling_matrix4[5],16,default_scaling4[1],scaling_matrix4[4]); // Inter, Cb
        if(is_sps ){
            decode_scaling_list(gb,scaling_matrix8[0],64,default_scaling8[0],fallback[2]);  // Intra, Y
            decode_scaling_list(gb,scaling_matrix8[1],64,default_scaling8[1],fallback[3]);  // Inter, Y
        }
    } else if(fallback_sps) {
/*
        memcpy(scaling_matrix4, sps->scaling_matrix4, 6*16*sizeof(uint8_t));
        memcpy(scaling_matrix8, sps->scaling_matrix8, 2*64*sizeof(uint8_t));
*/
    }
    for (i=0;i<64;i++) {
/*
        s->avctx->intra_matrix[i]=scaling_matrix8[0][i];
        s->avctx->inter_matrix[i]=scaling_matrix8[1][i];
*/
    }
    for (i=0;i<16;i++) {
/*
        s->avctx->intra_matrix_luma[i]=scaling_matrix4[0][i];
        s->avctx->inter_matrix_luma[i]=scaling_matrix4[3][i];
        s->avctx->intra_matrix_chroma[i]=scaling_matrix4[1][i];
        s->avctx->inter_matrix_chroma[i]=scaling_matrix4[4][i];
*/
    }
}

int h264_decode_seq_parameter_set(
	char	*pSeqHdr,
	long	nSeqHdrLen,
	long	*plWidth,
	long	*plHeight)
{
	GetBitContext ByteCtx;
	GetBitContext *gb = &ByteCtx;
    int profile_idc, level_idc;
    int sps_id, i;
	SPS SeqParamSet;
    SPS *sps = &SeqParamSet;
	int poc_cycle_length;
	int nalu;
	init_get_bits(gb, pSeqHdr, nSeqHdrLen * 8);

	nalu = get_bits(gb, 8);

	profile_idc= get_bits(gb, 8);
    get_bits1(gb);   //constraint_set0_flag
    get_bits1(gb);   //constraint_set1_flag
    get_bits1(gb);   //constraint_set2_flag
    get_bits1(gb);   //constraint_set3_flag
    get_bits(gb, 4); // reserved
    level_idc= get_bits(gb, 8);
    sps_id= get_ue_golomb(gb);
    
    
    if(profile_idc >= 100){ //high profile
        if(get_ue_golomb(gb) == 3) //chroma_format_idc
            get_bits1(gb);  //residual_color_transform_flag
        get_ue_golomb(gb);  //bit_depth_luma_minus8
        get_ue_golomb(gb);  //bit_depth_chroma_minus8
        sps->transform_bypass = get_bits1(gb);
        decode_scaling_matrices(gb, sps, 0, 1, sps->scaling_matrix4, sps->scaling_matrix8);
    }

    sps->log2_max_frame_num= get_ue_golomb(gb) + 4;
    sps->poc_type= get_ue_golomb(gb);
    
    if(sps->poc_type == 0)
	{ //FIXME #define
        sps->log2_max_poc_lsb= get_ue_golomb(gb) + 4;
    } else if(sps->poc_type == 1){//FIXME #define
        sps->delta_pic_order_always_zero_flag= get_bits1(gb);
        sps->offset_for_non_ref_pic= get_se_golomb(gb);
        sps->offset_for_top_to_bottom_field= get_se_golomb(gb);
        sps->poc_cycle_length= poc_cycle_length = get_ue_golomb(gb);
        
        for(i=0; i<sps->poc_cycle_length; i++)
            sps->offset_for_ref_frame[i]= get_se_golomb(gb);
    }
    if(sps->poc_type > 2){
        return -1;
    }

    sps->ref_frame_count= get_ue_golomb(gb);
#if 0
    if(sps->ref_frame_count > MAX_PICTURE_COUNT-2){
    }
#endif
    sps->gaps_in_frame_num_allowed_flag= get_bits1(gb);
    sps->mb_width= get_ue_golomb(gb) + 1;
    sps->mb_height= get_ue_golomb(gb) + 1;

    sps->frame_mbs_only_flag= get_bits1(gb);
    if(!sps->frame_mbs_only_flag)
        sps->mb_aff= get_bits1(gb);
    else
        sps->mb_aff= 0;

    sps->direct_8x8_inference_flag= get_bits1(gb);

    sps->crop= get_bits1(gb);
    if(sps->crop){
        sps->crop_left  = get_ue_golomb(gb);
        sps->crop_right = get_ue_golomb(gb);
        sps->crop_top   = get_ue_golomb(gb);
        sps->crop_bottom= get_ue_golomb(gb);
        if(sps->crop_left || sps->crop_top){
        }
    }else{
        sps->crop_left  = 
        sps->crop_right = 
        sps->crop_top   = 
        sps->crop_bottom= 0;
    }

    sps->vui_parameters_present_flag= get_bits1(gb);
    if( sps->vui_parameters_present_flag )
        decode_vui_parameters(gb, sps);
	*plWidth  = sps->mb_width * 16;
	*plHeight  = sps->mb_height * 16;

    return 1;
}

#define D_BYTES_FOR_HEADER_LENGHT	2

int h264_decode_mp4hdr(
	char	*pMp4Hdr,
	long	nMp4HdrLen,
	long	*plWidth,
	long	*plHeight)
{
	long numOfSequenceParameterSets = 0;
	char *p = pMp4Hdr;
	{
		long configurationVersion = *p;
	}
    p++;
	{
		long AVCProfileIndication = *p;
	}
    p++;
	{
		long profile_compatibility = *p;
	}
    p++;
	{
		long AVCLevelIndication = *p;
	}
    p++;
	{
		long lengthSizeMinusOne = *p;
		//avcRecord.lengthSizeMinusOne <<= 6;
		//avcRecord.lengthSizeMinusOne >>= 6; // remove reserved bits
	}
    p++;
	numOfSequenceParameterSets = *p;
    numOfSequenceParameterSets <<= 3;
    numOfSequenceParameterSets >>= 3;// remove reserved bits
    p++;
	{
		// Skip header bytes
		p  += D_BYTES_FOR_HEADER_LENGHT;
		//int i = 0;
		//for (i =0; i < numOfSequenceParameterSets;i++)
		{
			h264_decode_seq_parameter_set(p,nMp4HdrLen-(p-pMp4Hdr),plWidth,plHeight);
		}
	}
}

int h264_decode_h264_bytestream_hdr(
	char	*pData,
	long	lDataLen,
	long	*plWidth,
	long	*plHeight)
{
	int i = 0;
	while(i < lDataLen - 12){
		if(pData[i] == 0x00 && pData[i+1] == 0x00 && pData[i+2] == 0x01 && (pData[i+3] & 0x1F) == 0x07){
			return h264_decode_seq_parameter_set( pData + i + 3,lDataLen-i,plWidth,plHeight);
		} else {
			i++;
		}
	}
	return 0;
}

static long g_sampling_frequency_table[] =
{
    96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000, 7350, 0, 0, 0
};

int
aac_decode_hdr(
	char * pHdrData, 
	long lDataLen,
	long *plSampleFreq,
	long *lNumChan)
{
	GetBitContext ByteCtx;
	GetBitContext *gb = &ByteCtx;
    long channelConfiguration = 0;
    long samplingFrequency = 0;
	long audioObjectType = 0;
	long samplingFrequencyIndex = 0;
	init_get_bits(gb, pHdrData, lDataLen * 8);

    audioObjectType = get_bits(gb,5);
    samplingFrequencyIndex = get_bits(gb,4);

//    if ( 0x0f == p_data->samplingFrequencyIndex )
//    {
//        p_data->samplingFrequency = get_bits(gb,24);
//   }
    channelConfiguration = get_bits(gb,4);
	*lNumChan = channelConfiguration;
    *plSampleFreq = g_sampling_frequency_table[samplingFrequencyIndex];

}

int flv_h263_decode_picture_header(char *pData, long lHdrLen, long *plWidth, long *plHeight)
{
    int format, width, height;
	int picture_number;
	GetBitContext ByteCtx;
	GetBitContext *gb = &ByteCtx;

	if(!pData)
		return 0;
	init_get_bits(gb, pData, lHdrLen * 8);

    /* picture header */
    if (get_bits_long(gb, 17) != 1) {
        return 0;
    }
    format = get_bits(gb, 5);
    if (format != 0 && format != 1) {
        return 0;
    }

	picture_number = get_bits(gb, 8); /* picture timestamp */
    format = get_bits(gb, 3);
    switch (format) {
    case 0:
        width = get_bits(gb, 8);
        height = get_bits(gb, 8);
        break;
    case 1:
        width = get_bits(gb, 16);
        height = get_bits(gb, 16);
        break;
    case 2:
        width = 352;
        height = 288;
        break;
    case 3:
        width = 176;
        height = 144;
        break;
    case 4:
        width = 128;
        height = 96;
        break;
    case 5:
        width = 320;
        height = 240;
        break;
    case 6:
        width = 160;
        height = 120;
        break;
    default:
        width = height = 0;
        break;
    }
	*plWidth = width;
    *plHeight = height;
#if 0
    s->pict_type = I_TYPE + get_bits(gb, 2);
    s->dropable= s->pict_type > P_TYPE;
    if (s->dropable)
        s->pict_type = P_TYPE;

    skip_bits1(gb);	/* deblocking flag */
    s->chroma_qscale= s->qscale = get_bits(gb, 5);

    s->h263_plus = 0;

    s->unrestricted_mv = 1;
    s->h263_long_vectors = 0;

    /* PEI */
    while (get_bits1(gb) != 0) {
        skip_bits(gb, 8);
    }
    s->f_code = 1;

    
    s->y_dc_scale_table=
    s->c_dc_scale_table= ff_mpeg1_dc_scale_table;
#endif
    return 1;
}
