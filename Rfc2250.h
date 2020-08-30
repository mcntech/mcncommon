#ifndef __RFC_2250_H__
#define __RFC_2250_H__
#define RTP_HDR_SIZE			12
#define RFC2250_HDR_SIZE		4
#define RFC2250_EXT_HDR_SIZE	4
#define DEF_VID_PL_SIZE		1024
#define DEF_AUD_PL_SIZE		1024

/*
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |    MBZ  |T|         TR        | |N|S|B|E|  P  | | BFC | | FFC |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                   AN              FBV     FFV

        MBZ: Unused. Must be set to zero in current
           specification. This space is reserved for future use.

        T: MPEG-2 (Two) specific header extension present (1 bit).
           Set to 1 when the MPEG-2 video-specific header extension (see
           Section 3.4.1) follows this header. This extension may be
           needed for improved error resilience; however, its inclusion
           in an RTP packet is optional. (See Appendix 1.)

        TR: Temporal-Reference (10 bits). The temporal reference of
           the current picture within the current GOP. This value ranges
           from 0-1023 and is constant for all RTP packets of a given
           picture.

        AN: Active N bit for error resilience (1 bit). Set to 1 when
           the following bit (N) is used to signal changes in the
           picture header information for MPEG-2 payloads. It must be
           set to 0 for MPEG-1 payloads or when N bit is not used.

        N: New picture header (1 bit). Used for MPEG-2 payloads when
           the previous bit (AN) is set to 1. Otherwise, it must be set
           to zero. Set to 1 when the information contained in the
           previously transmitted Picture Headers can't be used to
           reconstruct a header for the current picture. This happens
           when the current picture is encoded using a different set of
           parameters than the previous pictures of the same type. The N
           bit must be constant for all RTP packets that belong to the
           same picture so that receipt of any packet from a picture
           allows detecting whether information necessary for
           reconstruction was contained in that picture (N = 1) or a
           previous one (N = 0).

        S: Sequence-header-present (1 bit). Normally 0 and set to 1 at
           the occurrence of each MPEG sequence header.  Used to detect
           presence of sequence header in RTP packet.

        B: Beginning-of-slice (BS) (1 bit). Set when the start of the
           packet payload is a slice start code, or when a slice start
           code is preceded only by one or more of a
           Video_Sequence_Header, GOP_header and/or Picture_Header.

        E: End-of-slice (ES) (1 bit). Set when the last byte of the
           payload is the end of an MPEG slice.

        P: Picture-Type (3 bits). I (1), P (2), B (3) or D (4). This
           value is constant for each RTP packet of a given picture.
           Value 000B is forbidden and 101B - 111B are reserved to
           support future extensions to the MPEG ES specification.

        FBV: full_pel_backward_vector
        BFC: backward_f_code
        FFV: full_pel_forward_vector
        FFC: forward_f_code
           Obtained from the most recent picture header, and are
           constant for each RTP packet of a given picture. For I frames
           none of these values are present in the picture header and

           they must be set to zero in the RTP header.  For P frames
           only the last two values are present and FBV and BFC must be
           set to zero in the RTP header. For B frames all the four
           values are present.
*/

/**
 * The following header is for LittleEndian.
 */
typedef struct tagRFC2250_MPEG_PL_HDR_T
{
	unsigned long ffc : 3;
	unsigned long ffv : 1;
	unsigned long bfc : 3;
	unsigned long fbv : 1;
	unsigned long p   : 3;
	unsigned long e   : 1;
	unsigned long b   : 1;
	unsigned long s   : 1;
	unsigned long n   : 1;
	unsigned long an  : 1;
	unsigned long tr  : 10;
	unsigned long t   : 1;
	unsigned long mbz : 5;
} RFC2250_VID_HDR_T;

/*
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |X|E|f_[0,0]|f_[0,1]|f_[1,0]|f_[1,1]| DC| PS|T|P|C|Q|V|A|R|H|G|D|
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        X: Unused (1 bit). Must be set to zero in current
           specification. This space is reserved for future use.

        E: Extensions present (1 bit). If set to 1, this header
           extension, including the composite display extension when D =
           1, will be followed by one or more of the following
           extensions: quant matrix extension, picture display
           extension, picture temporal scalable extension, picture
           spatial scalable extension and copyright extension.

           The first byte of these extensions data gives the length of
           the extensions in 32 bit words including the length field
           itself. Zero padding bytes are used at the end if required to
           align the extensions to 32 bit boundary.

           Since they may not be vital in decoding of a picture, the
           inclusion of any one of these extensions in an RTP packet is
           optional even when the MPEG-2 video-specific header extension
           is included in the packet (T = 1). (See Appendix 1.) If
           present, they should be copied from the corresponding
           extensions following the most recent MPEG-2 picture coding
           extension and they remain constant for each RTP packet of a
           given picture.

           The extension start code (32 bits) and the extension start
           code ID (4 bits) are included. Therefore the extensions are
           self identifying.

        f_[0,0]: forward horizontal f_code (4 bits)
        f_[0,1]: forward vertical f_code (4 bits)
        f_[1,0]: backward horizontal f_code (4 bits)
        f_[1,1]: backward vertical f_code (4 bits)
        DC: intra_DC_precision (2 bits)
        PS: picture_structure (2 bits)

        T: top_field_first (1 bit)
        P: frame_predicted_frame_dct (1 bit)
        C: concealment_motion_vectors (1 bit)
        Q: q_scale type (1 bit)
        V: intra_vlc_format (1 bit)
        A: alternate scan (1 bit)
        R: repeat_first_field (1 bit)
        H: chroma_420_type (1 bit)
        G: progressive frame (1 bit)
        D: composite_display_flag (1 bit). If set to 1, next 32 bits
           following this one contains 12 zeros followed by 20 bits
           of composite display information.
*/

typedef struct tagRFC2250_MPEG_PL_EXT_HDR_T
{
	unsigned long d		: 1;
	unsigned long g		: 1;
	unsigned long h		: 1;
	unsigned long r		: 1;
	unsigned long a		: 1;
	unsigned long v		: 1;
	unsigned long q		: 1;
	unsigned long c		: 1;
	unsigned long p		: 1;
	unsigned long t		: 1;
	unsigned long ps	: 2;
	unsigned long dc	: 2;
	unsigned long f_1_1 : 4;
	unsigned long f_1_0 : 4;
	unsigned long f_0_1 : 4;
	unsigned long f_0_0 : 4;
	unsigned long x		: 1;
	unsigned long e		: 1;
} RFC2250_VID_EXT_HDR_T;


typedef struct tagPICTURE_STATE_T{
	unsigned short	TemporalReference;
	unsigned char	PictureCodingType;
	unsigned char	VectorCodeBits; // FBV,BFC,FFV,FFC from RFC 2250, sec. 3.4
} PICTURE_STATE_T;

#define TemoralRef(Rfc2250Hdr) (Rfc2250Hdr >> 16)

#endif //__RFC_2250_H__



