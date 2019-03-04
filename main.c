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

uint8 sequenznummer;

static uint8 rgb24buffer[LEDCOUNT*3];

static sequenz_t sequenz[MAXSEQUENZ];

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
static void SendRGBBuffer (void)
{
    uint16 i;
    for (i = 0; i < sizeof (rgb24buffer); i++) {
        while  (!(IFG2 & UCA0TXIFG));    //  USCI_A0 TX buffer ready?
        UCA0TXBUF = rgb24buffer[i];      //  Send Data to slave
    }
}


//-------------------------------------------------------------------------------------------------
void SendSequenz( rgb_t* pLedData)
{
    uint16 i;
    uint16 index = 0;

    // Umrechnen in 24 bit
   for( i = 0; i < LEDCOUNT; i++) {
        rgb24buffer[index++] = ((*pLedData + (i * sizeof (uint32))) & 0xF800) << 8;  // R im MSB
        rgb24buffer[index++] += ((*pLedData + (i * sizeof (uint32))) & 0x07E0) << 5; // G
        rgb24buffer[index++] += ((*pLedData + (i * sizeof (uint32))) & 0x001F) << 3; // B im LSB
    }
    __dint(); //
    for( i = 0; i < LEDCOUNT; i++ ) {
       SendRGBBuffer ();
    }
    __eint();
}

//-------------------------------------------------------------------------------------------------
int main( void )
{
    uint8 i;

    Coldstart();
    sequenznummer = 1;
    sequenz[0].pdata = 0xc000; // erstmal auf den Programmcode stellen
    sequenz[0].maxschritt = 16;
    sequenz[1].pdata = (void*)&fixpgm1;   // 1. Fixpgrogrammsequenz
    sequenz[1].maxschritt = 0;
    sequenz[2].pdata = (void*)&fixpgm2;   // 2. Fixpgrogrammsequenz
    sequenz[2].maxschritt = 0;
    sequenz[3].pdata = (void*)&fixpgm3;   // 3. Fixpgrogrammsequenz
    sequenz[3].maxschritt = 0;

    do {
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

        if( (sequenznummer & 0x7f) >= MAXSEQUENZ ) {
            sequenznummer = 0x80;
        }
    } while( 1 );
    return 0;
}
