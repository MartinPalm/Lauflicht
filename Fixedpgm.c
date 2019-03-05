/*
 * Fixedpgm.c
 *
 *  Created on: 14.08.2015
 *      Author: martin
 */

#include "Lauflicht.h"
#include <string.h>

rgb_t ledbuffer[LEDCOUNT];

static rgb_t grundfarben[7] = {
        RGB(0,   0,   255),
        RGB(0,   255, 0),
        RGB(0,   255, 255),
        RGB(255, 0,   0),
        RGB(255, 0,   255),
        RGB(255, 255, 0),
        RGB(255, 255, 255)
};

//-------------------------------------------------------------------------------------------------
#if 0 // currently not used, keep compiler happy
static void Dim( rgb_t * p, uint8 factor )
{
    // factor nicht größer als 5!
    uint8 r = *p >> 11;
    uint8 g = (*p >> 5) & 0x3f;
    uint8 b = *p & 0x1f;
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
    uint8 r = *p >> 11;
    uint8 g = (*p >> 5) & 0x3f;
    uint8 b = *p & 0x1f;
    r += 8;
    r &= 0x1f;
    if( !r ) {
        g += 16;
        g &= 0x3f;
    }
    if( !g ) {
        b += 8;
        b &= 0x1f;
    }
    *p = RGB(r, g, b);
}

//-------------------------------------------------------------------------------------------------
static void MoveUp( rgb_t buffer[] )
{
    int16 i;
    rgb_t temp = buffer[LEDCOUNT - 1];
    for( i = LEDCOUNT - 2; i >= 0; i-- ) {
        buffer[i + 1] = buffer[i];
    }
    buffer[0] = temp;
}

//-------------------------------------------------------------------------------------------------
static void MoveDown( rgb_t buffer[] )
{
    uint16 i;
    rgb_t temp = buffer[0];
    for( i = 0; i < (LEDCOUNT - 2); i++ ) {
        buffer[i] = buffer[i + 1];
    }
    buffer[LEDCOUNT - 1] = temp;
}

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
            MoveDown(ledbuffer);
            SendSequenz(ledbuffer);
            Wait ();
        }
        for( i = 0; i < LEDCOUNT; i++ ) {
            MoveUp(ledbuffer);
            SendSequenz(ledbuffer);
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
        uint16 k = 0;
        if(( i & 0x03 ) == 0) {
            memset (ledbuffer, 0, sizeof (ledbuffer) );
            ledbuffer[7] = grundfarben[k++];
            // Bei jedem 3. Durchlauf wird die Farbe geändert
            if (k >= sizeof (grundfarben)) k = 0;
        }
        for( j = 1; j < 8; i++ ) {
            ledbuffer[7 - j] = ledbuffer [8 - j];
            ledbuffer[7 + j] = ledbuffer [6 + j];
            SendSequenz(ledbuffer);
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
    uint16 j = 0;
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
            MoveDown(ledbuffer);
            SendSequenz(ledbuffer);
            Wait ();
        }
        for( i = 0; i < LEDCOUNT; i++ ) {
            MoveUp(ledbuffer);
            SendSequenz(ledbuffer);
            Wait ();
        }
        j++;
    } while( sequenznummer == pgmnum );
}

