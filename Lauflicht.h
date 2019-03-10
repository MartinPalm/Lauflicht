/*
 * Lauflicht.h
 *
 *  Created on: 09.08.2015
 *      Author: martin
 */
#ifndef LAUFLICHT_H_
#define LAUFLICHT_H_

#include "constant.h"

extern volatile uint8  key;
extern volatile uint16 timer1;
extern volatile uint16 timer2;
extern volatile uint8 sequenznummer;

extern sequenz_t sequenz[NUMSEQUENZ];

extern uint8 GetKeys (void);
extern void Wait( void );
extern void Coldstart (void);
extern void SendSequenz (rgb_t* pLedData, uint8 numleds);
extern void InitLedbuffer (void);
#endif /* LAUFLICHT_H_ */
