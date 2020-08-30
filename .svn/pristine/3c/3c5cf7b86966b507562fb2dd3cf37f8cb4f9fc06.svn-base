#ifndef __RFC_3984_H__
#define __RFC_3984_H__

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
typedef struct tagRFC3984_NAL_TYPE
{
	unsigned char type	: 5;
	unsigned char nri	: 2;
	unsigned char f		: 1;
} ATTTRIB_PACK RFC3984_NAL_TYPE_T;

typedef struct tagRFC3984_FU_TYPE
{
	unsigned char type	: 5;
	unsigned char r		: 1;
	unsigned char e		: 1;
	unsigned char s		: 1;
} ATTTRIB_PACK RFC3984_FU_TYPE_T;

#ifdef WIN32
#pragma pack(pop)
#endif

#endif //__RFC_2250_H__



