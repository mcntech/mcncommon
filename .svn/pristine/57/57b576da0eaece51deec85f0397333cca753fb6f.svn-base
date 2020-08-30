#ifndef __AV_HDR_PARSE__
#define __AV_HDR_PARSE__

#ifdef __cplusplus
extern "C" {
#endif
int h264_decode_seq_parameter_set(
	char	*pSeqHdr,
	long	nSeqHdrLen,
	long	*plWidth,
	long	*plHeight);

int h264_decode_mp4hdr(
	char	*pMp4Hdr,
	long	nMp4HdrLen,
	long	*plWidth,
	long	*plHeight);

int h264_decode_h264_bytestream_hdr(
	char	*pData,
	long	lDataLen,
	long	*plWidth,
	long	*plHeight);


int
aac_decode_hdr(
	char * pHdrData, 
	long lDataLen,
	long *plSampleFreq,
	long *lNumChan);

int flv_h263_decode_picture_header(
	char *pData, 
	long lHdrLen, 
	long *plWidth, 
	long *plHeight);
#ifdef __cplusplus
}
#endif

#endif //__AV_HDR_PARSE__
