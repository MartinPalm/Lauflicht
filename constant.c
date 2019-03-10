/*
 * constant.c
 *
 *  Created on: 10.03.2019
 *      Author: palm
 */
#include "constant.h"

const rgb_t farben[8] = {
		RGB(0,   0,   0),
		RGB(0,   0,   255),
		RGB(0,   255, 0),
		RGB(0,   255, 255),
		RGB(255, 0,   0),
		RGB(255, 0,   255),
		RGB(255, 255,   0),
		RGB(255, 255, 255),
};

const uint16 rdmask = 0xF800;
const uint16 gnmask = 0x07E0;
const uint16 blmask = 0x001F;

const uint16 FASTTEST = 750;
const uint16 SLOWEST  = 20;
