/*
 * Fixedpgm.c
 *
 *  Created on: 14.08.2015
 *      Author: martin
 */
#include "Lauflicht.h"
#include <string.h>

static rgb_t ledbuffer[LEDCOUNT];

//-------------------------------------------------------------------------------------------------
#if 0 // currently not used, keep compiler happy
static void Dim( rgb_t * p, uint8 factor )
{
    // factor nicht größer als 5!
    uint8 r = (*p >> 8) & 0xF8;
    uint8 g = (*p >> 3) & 0xFC;
    uint8 b = *p << 3;
   // keep factor in check
    factor = factor % 5;
    r >>= factor;
    g >>= factor;
    b >>= factor;
    *p = RGB(r, g, b);
}
#endif
//-------------------------------------------------------------------------------------------------
static void ColorChange( rgb_t* p )
{
    uint8 r = (*p >> 8) & 0xF8;
    uint8 g = (*p >> 3) & 0xFC;
    uint8 b = *p << 3;

    r += 0x10;
    if( !r ) {
        g += 0x10;
    }
    if( !g ) {
        b += 0x10;
    }
    *p = RGB(r, g, b);

}

//-------------------------------------------------------------------------------------------------
static void RotUp( rgb_t buffer[], uint8 numleds )
{
    int16 i;
    rgb_t temp = buffer[numleds - 1];
    for( i = numleds - 2; i > 0; i-- ) {
        buffer[i + 1] = buffer[i];
    }
    buffer[0] = temp;
}

//-------------------------------------------------------------------------------------------------
static void RotDown( rgb_t buffer[], uint8 numleds )
{
    uint8 i;
    rgb_t temp = buffer[0];
    for( i = 0; i < (numleds - 2); i++ ) {
        buffer[i] = buffer[i + 1];
    }
    buffer[numleds - 1] = temp;
}

#if 0
//-------------------------------------------------------------------------------------------------
static void MoveUp( rgb_t buffer[], uint8 numleds )
{
    uint8 i;
    for( i = numleds; i; i-- ) {
        buffer[i + 1] = buffer[i];
    }
    buffer[0] = black;
}


//-------------------------------------------------------------------------------------------------
static void MoveDown( rgb_t buffer[], uint8 numleds )
{
    uint8 i;
    for( i = 0; i < (numleds - 2); i++ ) {
        buffer[i] = buffer[i + 1];
    }
    buffer[numleds - 1] = black;
}
#endif
//-------------------------------------------------------------------------------------------------
void fixpgm1( uint8 pgmnum )
{
    uint16 i;
    uint16 j = 0;
    // Create Data
    ledbuffer[0] = RGB(0, 0, 127);
    ledbuffer[1] = RGB(0, 0, 255);
    ledbuffer[2] = RGB(0, 0, 127);
    for( i = 3; i < LEDCOUNT; ) {
        ledbuffer[i++] = ledbuffer[0];
        ledbuffer[i++] = ledbuffer[1];
        ledbuffer[i++] = ledbuffer[2];
    }
    // Loop Data
    do {
#if 0
        if( j == 2 ) {
            // Bei jedem 2. Durchlauf wird die Farbe ein wenig geändert
            j = 0;
            for( i = 0; i < LEDCOUNT; i++ ) {
                ColorChange(&ledbuffer[i]);
            }
        }
#endif
        for( i = 0; i < LEDCOUNT; i++ ) {
            RotDown(ledbuffer, LEDCOUNT);
            SendSequenz(ledbuffer, LEDCOUNT);
            Wait ();
        }
        for( i = 0; i < LEDCOUNT; i++ ) {
            RotUp(ledbuffer, LEDCOUNT);
            SendSequenz(ledbuffer, LEDCOUNT);
            Wait ();
        }
         j++;
    } while( sequenznummer == pgmnum );
}

//-------------------------------------------------------------------------------------------------
void fixpgm2( uint8 pgmnum )
{
    uint16 i = 0;
    // Loop Data
    do {
        uint16 j;
        uint8 k = black;
        if(( i & 0x03 ) == 0) {
            memset (ledbuffer, 0, sizeof (ledbuffer) );
            ledbuffer[7] = farben[k++];
            // Bei jedem 3. Durchlauf wird die Farbe geändert
            if (k > white) k = black;
        }
        for( j = 1; j < 8; i++ ) {
            ledbuffer[7 - j] = ledbuffer [8 - j];
            ledbuffer[7 + j] = ledbuffer [6 + j];
            SendSequenz(ledbuffer, LEDCOUNT);
            Wait ();
        }
        k++;
        i++;
    } while( sequenznummer == pgmnum );
}

//-------------------------------------------------------------------------------------------------
void fixpgm3( uint8 pgmnum )
{
    uint16 i;
    uint16 j = 1;
    // Create Data
    ledbuffer[0] = RGB(0, 0, 85);
    ledbuffer[1] = RGB(0, 0, 170);
    ledbuffer[2] = RGB(0, 0, 255);
    ledbuffer[3] = RGB(0, 0, 170);
    ledbuffer[4] = RGB(0, 0, 85);
    for( i = 5; i < LEDCOUNT; i += 5) {
        memcpy (&ledbuffer[i], &ledbuffer[0], 5*sizeof (rgb_t));
    }
    // Loop Data
    do {
        if( j == 2 ) {
            // Bei jedem 2. Durchlauf wird die Farbe ein wenig geändert
            j = 0;
            for( i = 0; i < LEDCOUNT; i++ ) {
                ColorChange(&ledbuffer[i]);
            }
        }
        for( i = 0; i < LEDCOUNT; i++ ) {
            RotDown(ledbuffer, LEDCOUNT);
            SendSequenz(ledbuffer, LEDCOUNT);
            Wait ();
        }
        for( i = 0; i < LEDCOUNT; i++ ) {
            RotUp(ledbuffer, LEDCOUNT);
            SendSequenz(ledbuffer, LEDCOUNT);
            Wait ();
        }
        j++;
    } while( sequenznummer == pgmnum );
}

//-------------------------------------------------------------------------------------------------
void InitLedbuffer (void)
{
	// jetzt erstmal alles duster....
    memset (ledbuffer, 0x00, LEDCOUNT * sizeof (rgb_t) );
    SendSequenz(ledbuffer, LEDCOUNT);
}
