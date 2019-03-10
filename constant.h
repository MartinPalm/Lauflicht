/*
 * constant.h
 *
 *  Created on: 10.03.2019
 *      Author: palm
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "types.h"

extern const rgb_t farben[8];

extern const uint16 rdmask;
extern const uint16 gnmask;
extern const uint16 blmask;

extern const uint16 FASTTEST;
extern const uint16 SLOWEST;

#define NUMSEQUENZ 16
#define LEDCOUNT   15

// Bitmask für Keys
#define FASTER 0x08
#define SLOWER 0x02
#define NEXTPROG 0x04

#endif /* CONSTANT_H_ */
