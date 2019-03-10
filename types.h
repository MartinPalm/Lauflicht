/*
 * types.h
 *
 *  Created on: 10.03.2019
 *      Author: palm
 */

#ifndef TYPES_H_
#define TYPES_H_

// Erstmal typen definieren
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

typedef char  int8;
typedef short int16;
typedef long  int32;

typedef uint16 rgb_t;

// 3*uint8 zu RGB 565 wandeln
#define RGB(r, g, b) ((((r) >> 3) & 0x1f) << 11) + ((((g) >> 2) & 0x3f) << 5) + (((b) >> 3) & 0x1f)
// RGB 565 zu 3*uint8 wandeln
#define TC(in,r,g,b) ((r)=((in)>>8) & 0xF8; (g)=((in)>>3) & 0xFC; (b)=((in)<<3) & 0xF8;)

enum {
		black,
		blue,
		green,
		cyan,
		red,
		magenta,
		yellow,
		white,
} grundfarben_t;

typedef struct {
  uint8	 maxschritt;
  rgb_t* pdata;        // Data (see below) or functionpointer)
} sequenz_t;

typedef struct {
	uint8  numleds;
	uint16 numsequence;
	rgb_t  sequencedata[];
} sequence_t;

#endif /* TYPES_H_ */
