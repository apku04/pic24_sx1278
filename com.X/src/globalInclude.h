/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
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
    ============================================================================
    Revision Information:
        File name: globalInclude.h
        Version:   v0.0
        Date:      2012-08-09
    ============================================================================
 */

/*
** ==========================================================================
**                        INCLUDE STATEMENTS
** ==========================================================================
*/

#ifndef GLOB_H
#define	GLOB_H



#include <string.h>
#include <stdint.h>          /* For uint32_t definition */
#include <stdio.h>
#include <stdlib.h>



//#define SIMULATOR 

void op_hexdump(int level, const char *title, const void *buf, size_t len, char newline);
void print_routing_table(void);


/*
** ==========================================================================
**                        DEFINES AND MACROS
** ==========================================================================
*/

#define BUFFER_SIZE 8
#define PACKET_SIZE 70
#define PACKET_BUFFER_SIZE 10
#define SIGNAL_STRENGTH_THRESHOLD -100
#define BROADCAST 255

typedef enum {
    DEVICE_ID = 0,
    RADIO_FREQ1,
    RADIO_FREQ2,
    RADIO_FREQ3,
    RADIO_FREQ4,
    RADIO_DR,
    RADIO_TX_PWR,        
    PARAMETER_N,
    FLASH_SIZE
} addrEnum;

typedef enum {
    DIR_EMPTY,
    OUTGOING,
    INCOMING,
    RETX
} Direction;

typedef enum {
    OWNER_EMPTY,  
    PHY,
    MAC,
    NET,
    APP
} Owner;

typedef enum {
    BEACON,
    PAYLOAD,
    ACK,
    PING,
    PONG
} PacketType;

/**
 * Enumeration containing different return types
*/
typedef enum
{
  DATA_LINK_TRANSMISSION_FAILED = 8,  
  DATA_LINK_ACK_TIMEOUT         = 7, /* Payload sent but did not receive ack */
  DATA_LINK_GOT_ACK             = 6, /* Payload sent and received ack */
  DATA_LINK_CTS_TIMEOUT         = 5, /* RTS sent but did not receive cts*/
  DATA_LINK_GOT_CTS             = 4, /* RTS sent and received cts*/
  DATA_LINK_DIFS_WAIT_OK        = 3, /* Waited DIFS without any CD*/
  DATA_LINK_BACKOFF_OK          = 2, /* Did backoff without CD*/
  DATA_LINK_CARRIER_DETECTED    = 1, /* Carrier detected */

  GLOB_SUCCESS                  = 0,  /* The prosses was prossed with success */
  GLOB_FAILURE                  = -1, /* The prosses was prossed with some or more error */
  GLOB_ERROR_OUT_OF_RANGE_PARAM = -2, /* The parameter passed to the function is outside the valid range */
  GLOB_ERROR_INVALID_MESSAGE    = -3, /* The given message does not identify a valid object */
  GLOB_ERROR_INVALID_PARAM      = -4, /* The parameter passed to the function is invalid*/
  GLOB_ERROR_OUT_OF_HANDLES     = -5, /* There is no free handle available*/
  GLOB_ERROR_INIT               = -6, /* Initialisation when wrong */
  GLOB_ERROR_NETWORK_OUTGOING_FAILED = -7,
  GLOB_ERROR_NETWORK_INCOMING_FAILED = -8,
  GLOB_ERROR_UNKNOWN_DIRECTION = -9,
  GLOB_ERROR_BUFFER_FULL = -10,  
  GLOB_ERROR_BUFFER_EMPTY = -11,
  GLOB_ERROR_WRITE_BUFFER_SIZE_EXCEEDED = -12,
  GLOB_ERROR_WRITE_BUFFER_DATA_SIZE_EXCEEDED = -13,
  GLOB_ERROR_READ_BUFFER_SIZE_EXCEEDED = -14,
  GLOB_ERROR_BUFFER_SIZE_EXCEEDED = -15,
  GLOB_ERROR_BUFFER_SIZE_NEGATIVE = -16,
  GLOB_ERROR_POINTER_MISMATCH = -17,
          
  GLOB_WARNING_PARAM_NOT_SET    = -20, /* There requiret parameter is not set */
  GLOB_ERROR_MEMORY_ALLOCATION  = -21,
  GLOB_ERROR_BEACON_PROCESSING_FAILED = -22        
}GLOB_RET;

 /* ********************** LEDs *********************** */

#define LED_A LATAbits.LATA2
#define LED_A_TOGGLE LED_A   = ~LED_A

#define LED_B LATBbits.LATB14
#define LED_B_TOGGLE LED_B = ~LED_B

#define LED_C LATBbits.LATB5
#define LED_C_TOGGLE LED_C = ~LED_C


 /* ********************** TIMERs  *********************** */

#define TIMER_ONE_SEC 1000
#define TIMER_100_MS   100
#define TIMER_50_MS     50
#define TIMER_10_MS     10
#define TIMER_1_MS       1

#define START_ONE_MILI_TIMER  oneMilliTimer    = 0;
#define START_TIK_TIMER oneTikTimer = 0;

#define NO 0
#define YES 1


/*
** ==========================================================================
**                        STRUCTS
** ==========================================================================
*/


typedef struct {
    uint8_t deviceID;
    uint8_t radioFreq1;
    uint8_t radioFreq2;
    uint8_t radioFreq3;
    uint8_t radioFreq4;
    uint8_t radioDataRate;
    uint8_t radioTxPwr;
    uint8_t paramN;
} deviceData_t;

typedef struct
{
    unsigned volatile int read_pointer;
    unsigned volatile int write_pointer;
    unsigned volatile int data_size;
    uint8_t buffer[BUFFER_SIZE][PACKET_SIZE];
}rBufPar;

typedef struct __attribute__((__packed__)) {
    uint8_t pktDir;
    uint8_t pOwner;
    int16_t rssi;
    int16_t prssi;
    uint8_t rxCnt;
    uint8_t destination_adr; // 0
    uint8_t source_adr; // 1
    uint16_t sequence_num; // 2, 3
    uint8_t control_mac; // 4
    uint8_t protocol_Ver; // 5
    uint8_t TTL; // 6
    uint8_t mesh_dest; // 7
    uint8_t mesh_tbl_entries; // 8
    uint8_t mesh_src; // 9
    uint8_t control_app; // 10
    uint8_t length; // 11
    uint8_t data[50];
} Packet;

typedef struct {
    Packet buffer[PACKET_BUFFER_SIZE];
    int read_pointer;
    int write_pointer;
    int data_size;
} PacketBuffer;

void packet_print_out(int level, const char *title, Packet *packet) ;
/*
** =============================================================================
**                       EXPORTED FUNCTION DECLARATION
** =============================================================================
*/


/*
 ** ==========================================================================
 **                       Extern Global variables
 ** ==========================================================================
 */

// External Timer vars
extern unsigned int oneMilliTimer;
extern unsigned int oneTikTimer;
extern unsigned long long longCounter_MS;


// External nrf config
extern char rxClockOutSize;

extern uint8_t sniffer;

#endif	/* GLOB_H */