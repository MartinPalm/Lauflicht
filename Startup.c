/*
 * Startup.c
 *
 *  Created on: 09.08.2015
 *      Author: martin
 */
#include <msp430g2553.h>

#include "Lauflicht.h"
#include "string.h"

uint8 GetKeys(void)
{
    return ((P1IN & 0x08) ? 0 : 0x08); // P1.3 ist Taster auf Evalboard
}

void Coldstart(void)
{
    // Description: Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
    //  P1.1. DCO is software selectable to 1, 8, 12, or 16Mhz using calibration
    //  contstants in INFOA.
    //
    //  ACLK = LFXT1 = 32768, MCLK = SMCLK = Selectable at 1, 8, 12 or 16Mhz
    //  //* External watch crystal installed on XIN XOUT is required for ACLK *//
    //
    //               MSP430G2xx3
    //             -----------------
    //         /|\|              XIN|-
    //          | |                 | 32kHz
    //          --|RST          XOUT|-
    //            |                 |
    //            |       P1.4/SMCLK|-->SMCLK = Default DCO
    //            |             P1.1|-->MCLK/10 = DCO/10
    //            |        P1.0/ACLK|-->ACLK = 32kHz
    //

    WDTCTL = WDTPW + WDTHOLD;                  // Stop Watchdog Timer
    if (CALBC1_16MHZ == 0xFF || CALDCO_16MHZ == 0xFF) {
        while (1);                               // If calibration constants erased do not load, trap CPU!!
    }

    // 16MHz
    BCSCTL1 = CALBC1_16MHZ;                // Set DCO
    DCOCTL  = CALDCO_16MHZ;                // to 16 MHz

    BCSCTL2 = DIVS_0 + DIVM_0;             // MCLK=DCO/1, SMCLK=DCO/1

    // Flash Memory Controller
    // Flash Timing Generator frequency must be 257-476 kHz.
    // 8 MHZ/35 = 470.59 kHz.   tFTG=2.125 msec.
    // At 470 kHz, byte/word program time is 35*tFTG = 75 usec.
    // Cumulative program time to any 64-byte block (between erasures)
    // must not exceed 4 msec, thus 53 writes at 250 kHz.  Therefore,
    // do not use exclusively byte writes in a 64-byte block.
    // Also, "a flash word (low + high byte) must not
    // be written more than twice between erasures."
    // Program/Erase endurance is 10,000 cycles minimum.
    FCTL1 = FWKEY + 0;                      // write & erase modes OFF
    FCTL2 = FWKEY + FSSEL_2 + FN5 + FN0;    // SMCLK/32+1+1 = 471 kHz
    FCTL3 = FWKEY + LOCK;                   // lock flash memory against writing

    // Digital I/O
    P1OUT  = 0x00;                          // 0,2,4, 6 output
    P1REN  = 0x00;                          // P1.3 pullup enabled
    P1DIR  = 0x55;                          // P1.0, P1.2, P1.4, P1.6 are outputs
    P1IE   = 0x00;                          // no port 1 interrupts
    P1SEL  = 0x00;                          // no special functions
    P1SEL2 = 0x00;

    P2OUT  = 0x00;
    P2DIR  = 0x03;                          // P2.0, P2.1 outputs rest input
    P2REN  = 0x03;                          // Outputs mit Pullup!
    P2IE   = 0x00;                          // no port 2 interrupts
    P2SEL  = 0x00;                          // no functions enabled
    P2SEL2 = 0x00;                          // no functions enabled

    // generell mal die interruts einschalten
    __eint();

    // Setup Timer A
    TACTL = TASSEL_2 + ID_0 + MC_1;           // SMCLK, upmode
    TACCR0 = 20000;                           // 16Mhz , 40000 == 2,5ms
    TACCTL0 = CCIE;                           // CCR0 interrupt enabled

    // Setup SPI
    UCA0CTL1   =   UCSWRST;
    UCA0CTL0   |=  UCCKPH + UCMST + UCMODE_0 + UCSYNC; //  3-pin,  8-bit, SPI master
    UCA0CTL1   |=  UCSSEL_2;   //  SMCLK
    UCA0BR0    |=  0x08;       //  /8   SMCLK/8 == 2 MHz
    UCA0BR1    =   0;          //  CLOCK MSB = 0
    UCA0MCTL   =   0;          //  No  modulation
    P1SEL      =   BIT2 | BIT4; // P1.3 und P1.5 sind die Ausgänge (special functions)
    P1SEL2     =   BIT2 | BIT4;
    UCA0CTL1   &=  ~UCSWRST;   //  **Initialize    USCI    state   machine**

// jetzt erstmal alles duster....
    memset (ledbuffer, 0, sizeof (ledbuffer) );
    SendSequenz(ledbuffer);

}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerIRQ (void)
{
    static uint8 oldkey = 0; // keine Taste gedrückt
    uint8 newkey;
    // 1. Job - Timer weiterstellen
    if (timer1) {
        // decrement timer var
        if (timer1 < deltatime) {
            timer1 = 0;
        } else {
            timer1 = timer1 - deltatime;
        }
    }
    if( timer2 ) {
        if (timer2) timer2--;
    }
    // 2. Job: Keys abfragen
    newkey = GetKeys ();
    if (oldkey != newkey) {
        // Keyhandling faster
        if (newkey & FASTER) {
            if (deltatime < FASTTEST)
                deltatime += 10;
        }
        // Keyhandling slower
        if (newkey & SLOWER) {
            if (deltatime > SLOWEST)
                deltatime -= 10;
        }
        // Blinkmuster weiterschalten
        if (newkey & NEXTPROG) {
            sequenznummer++;
            if( ! sequenz[sequenznummer].pdata) {
            	sequenznummer = 1;
            }
        }
        oldkey = newkey;
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void TasterIRQ (void)
{
}
