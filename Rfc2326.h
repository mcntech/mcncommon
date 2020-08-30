
#ifndef __RFC_2326_H__
#define __RFC_2326_H__

#ifdef WIN32
#pragma pack(push)
#pragma pack(1)
#define ATTTRIB_PACK
#else // LINUX
#define ATTTRIB_PACK	__attribute__ ((packed))
#endif


/**
 * The following header is for LittleEndian.
 */
typedef struct tagRFC2326_BIN_HDR_T
{
	unsigned char	Dollar;		// $
	unsigned char	Chan;
	unsigned short	LenBytes;	// Network order (Big Endian)
} ATTTRIB_PACK RFC2326_BIN_HDR_T;

#define RFC2326_BIN_HDR_SIZE	4

#ifdef WIN32
#pragma pack(pop)
#endif

#endif //__RFC_2326_H__

