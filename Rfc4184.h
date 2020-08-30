#ifndef __RFC_4184_H__
#define __RFC_4184_H__
#ifndef RTP_HDR_SIZE
#define RTP_HDR_SIZE			12
#endif
#define RFC4184_HDR_SIZE		2
#define DEF_VID_PL_SIZE			1024

/*
				  0                   1
                  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                 |    MBZ    | FT|       NF      |
                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   o MBZ (Must Be Zero): Bits marked MBZ SHALL be set to the value zero
     and SHALL be ignored by receivers.  The bits are reserved for
     future extensions.

   o FT (Frame Type): This two-bit field indicates the type of frame(s)
     present in the payload.  It takes the following values:

      0 - One or more complete frames.
      1 - Initial fragment of frame which includes the first 5/8ths of
          the frame.  (See Section 4.2.)
      2 - Initial fragment of frame, which does not include the first
          5/8ths of the frame.
      3 - Fragment of frame other than initial fragment.  (Note that M
          bit in RTP header is set for final fragment).

   o NF (Number of frames/fragments): An 8-bit field whose meaning
     depends on the Frame Type (FT) in this payload.  For complete
     frames (FT of 0), it is used to indicate the number of AC-3 frames
     in the RTP payload.  For frame fragments (FT of 1, 2, or 3), it is
     used to indicate the number fragments (and therefore packets) that
     make up the current frame.  NF MUST be identical for packets
     containing fragments of the same frame.

*/

typedef enum RFC_4184_FRAME_TYPE
{
	FT_0,		// One or morecomplete frame
	FT_1,		// Initial 5/8 of frame
	FT_2,		// Initial fragment,not 5/8
	FT_3		// Not initial fragment
};

typedef struct tagFSC_LIST_ITEM_T {
	long			ScType;
	long			Pos;
	long			Pts;
} FSC_LIST_ITEM_T;

/**
 * The following header is for LittleEndian.
 */
typedef struct tagRFC4184_AUD_HDR_T
{
	unsigned short nf : 8;
	unsigned short ft  : 2;
	unsigned short mbz : 6;
} RFC4184_AUD_HDR_T;

#endif //__RFC_4184_H__


