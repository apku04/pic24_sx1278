/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
    All rights reserved.
    ============================================================================
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
    ============================================================================
    Revision Information:
        File name: main.h
        Version:   v0.0
        Date:      2019-10-11
    ============================================================================
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define APP_HEADER_SIZE 4
#define NET_HEADER_SIZE 5
#define MAC_HEADER_SIZE 3
#define PACKET_HEADER_SIZE (MAC_HEADER_SIZE+NET_HEADER_SIZE+APP_HEADER_SIZE)
#define META_DATA_SIZE 3
#define DATA_LEN 50

#define BUFFER_DATA_SIZE (META_DATA_SIZE+PACKET_HEADER_SIZE+DATA_LEN)

#define RSSICORR 164

#define SPICSN LATBbits.LATB7
#define RESET LATAbits.LATA4 
#define RF_ON LATBbits.LATB13

#define TRUE 1
#define FALSE 0

typedef struct slme {
    
    uint8_t radio_initialized;
    uint8_t sender_initialized;
    uint8_t receiver_initialized;
    
    int16_t pkt_snr;
    uint8_t pkt_rssi;
    uint8_t rssi;
    
}slme;



extern slme SLME;
extern uint8_t printAllReg, tx_test;

void send_beacon_flag(uint8_t flag);


#endif /* MAIN_H */