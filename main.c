// main file fuer das Lauflicht
//
#include <msp430g2553.h>
#include "Lauflicht.h"
#include "Fixedpgm.h"

const rgb_t white = RGB(255, 255, 255);
const rgb_t black = RGB(0, 0, 0);
const rgb_t red =   RGB(255, 0, 0);
const rgb_t green = RGB(0, 255, 0);
const rgb_t blue =  RGB(0, 0, 255);

const rgb_t data1 [LEDCOUNT][16] = {
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
		{ RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0)},
};

volatile uint8 sequenznummer;

sequenz_t sequenz[NUMSEQUENZ];

uint16 deltatime = 100;

volatile uint16 timer1 = 0;
volatile uint16 timer2 = 0;


//-------------------------------------------------------------------------------------------------
void Wait( void )
{
    timer1 = 20000;
    while( timer1 ) {
    };
}

//-------------------------------------------------------------------------------------------------
static void SendRGBBuffer (uint8 *buf, uint8 count)
{
	// Der letzte Wert in der Kette muss als erster Wert übertragen werden
    for (; count; count--) {
        while  (!(IFG2 & UCA0TXIFG));	//  USCI_A0 TX buffer ready?
        UCA0TXBUF = *(buf+count-1);		//  Send Data to slave
    }
}

//-------------------------------------------------------------------------------------------------
void SendSequenz( rgb_t* pLedData)
{
    static uint8 rgb24buffer[LEDCOUNT*3]; // das gehört nicht auf den Stack

    uint16 i;
    // Umrechnen 16bit 565 in 24bit 888
    for( i = 0; i < sizeof (rgb24buffer); pLedData++) {
        rgb24buffer[i++]  = (*pLedData & rdmask) << 8; // R im MSB
        rgb24buffer[i++] += (*pLedData & gnmask) << 5; // G
        rgb24buffer[i++] += (*pLedData & blmask) << 3; // B im LSB
    }
    __dint(); //
    SendRGBBuffer (rgb24buffer, sizeof (rgb24buffer));
     __eint();
}

//-------------------------------------------------------------------------------------------------
int main( void )
{
    Coldstart();
    sequenznummer = 1;
    sequenz[0].pdata = (void*)data1; 	// erstmal auf den Programmcode stellen
    sequenz[0].maxschritt = 16;
    sequenz[1].pdata = (void*)&fixpgm1; // 1. Fixpgrogrammsequenz
    sequenz[1].maxschritt = 0;
    sequenz[2].pdata = (void*)&fixpgm2; // 2. Fixpgrogrammsequenz
    sequenz[2].maxschritt = 0;
    sequenz[3].pdata = (void*)&fixpgm3; // 3. Fixpgrogrammsequenz
    sequenz[3].maxschritt = 0;
    sequenz[4].pdata = 0;
    sequenz[4].maxschritt = 0;

    do {
    	uint8 i;
        if( sequenz[sequenznummer].maxschritt ) {
            for( i = 0; i < sequenz[sequenznummer & 0x7f].maxschritt; i++ ) {
#if 1
                // Kontrolle für Lauchpad
                P1OUT ^= 0x40;
#endif
                SendSequenz(sequenz[sequenznummer].pdata + i * sizeof(rgb_t));
                Wait();
            }
        } else {
            if (sequenz[sequenznummer].pdata) {
                (*(void (*)(uint8))sequenz[sequenznummer].pdata)(sequenznummer);
            }
        }

        if( !sequenz[sequenznummer].pdata) {
        	sequenznummer = 0;
        }
    } while( 1 );
    return 0;
}
