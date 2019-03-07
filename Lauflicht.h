/*
 * Lauflicht.h
 *
 *  Created on: 09.08.2015
 *      Author: martin
 */

#ifndef LAUFLICHT_H_
#define LAUFLICHT_H_

// Erstmal typen definieren
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

typedef char  int8;
typedef short int16;
typedef long  int32;

typedef uint16 rgb_t;

#define rdmask 0xf800
#define gnmask 0x07E0
#define blmask 0x001F

// 3*uint8 zu RGB 565 wandeln
#define RGB(r, g, b) ((((r) >> 3) & 0x1f) << 11) + ((((g) >> 2) & 0x3f) << 5) + (((b) >> 3) & 0x1f)

typedef struct {
  uint8	 maxschritt;
  rgb_t* pdata;        // Daten oder Funktionspointer
} sequenz_t;

#define FASTTEST 750
#define SLOWEST 20

#define NUMSEQUENZ 16

#define LEDCOUNT   15

// Bitmask für Keys
#define FASTER 0x08
#define SLOWER 0x02
#define NEXTPROG 0x04

extern volatile uint8  key;
extern volatile uint16 timer1;
extern volatile uint16 timer2;

extern uint16 deltatime;
extern volatile uint8 sequenznummer;
extern rgb_t ledbuffer[LEDCOUNT];
extern sequenz_t sequenz[NUMSEQUENZ];

extern uint8 GetKeys (void);
extern void Wait( void );
extern void Coldstart (void);
//extern void SendRGB(uint32 val);
extern void SendSequenz (rgb_t* pLedData);

#endif /* LAUFLICHT_H_ */
