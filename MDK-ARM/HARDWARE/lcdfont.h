#ifndef __LCDFONT_H
#define __LCDFONT_H

extern const unsigned char ascii_1206[95][12];

extern const unsigned char ascii_1608[95][16];
extern const unsigned char ascii_2412[95][48];
extern const unsigned char ascii_3216[95][64];

typedef struct
{
	unsigned char Index[2];
	unsigned char Msk[24];
} typFNT_GB12;

extern const typFNT_GB12 tfont12[5];

typedef struct
{
	unsigned char Index[2];
	unsigned char Msk[32];
} typFNT_GB16;

extern const typFNT_GB16 tfont16[10];

typedef struct
{
	unsigned char Index[2];
	unsigned char Msk[72];
} typFNT_GB24;

extern const typFNT_GB24 tfont24[4];

typedef struct
{
	unsigned char Index[2];
	unsigned char Msk[128];
} typFNT_GB32;

extern const typFNT_GB32 tfont32[5];

#endif
