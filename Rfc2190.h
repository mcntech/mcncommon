#ifndef __RFC_2190_H__
#define __RFC_2190_H__

/**
 * The following header is for LittleEndian.
 */
typedef struct tagRFC2190_PL_HDR1_TYPE
{
	unsigned long tr	: 8;

	unsigned char trb	: 3;
	unsigned char dqb	: 2;
	unsigned char r		: 4;
	unsigned char a		: 1;
	unsigned char s		: 1;
	unsigned char u		: 1;
	unsigned char i		: 1;
	unsigned char src	: 3;

	unsigned char ebit	: 3;
	unsigned char sbit	: 3;
	unsigned char f		: 1;
	unsigned char p		: 1;

} RFC2190_PL_HDR1_TYPE;


#endif //__RFC_2190_H__



